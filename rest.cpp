//
//  rest.cpp
//  tesmon
//
//  wrapper class for REST: restclient-cpp
//  
//
//  Created by Ed Cole on 18/10/2020.
//  Copyright © 2020 colege. All rights reserved.
//

#include "rest.hpp"

// Constructor
RestAPI::RestAPI(){
    
    RestClient::init();                             // initialize restclient-cpp
    conn = new RestClient::Connection(TESLA_URI);   // create a connection object
    conn->SetTimeout(45);                            // set connection timeout
    conn->SetUserAgent(MY_REST_UA);                 // set custom user agent
    conn->FollowRedirects(true);                    // enable redirects (default is off)
    conn->FollowRedirects(true, 3);                 // limit number of redirects (default is -1, unlimited)
    send_headers["Accept"] = "application/json";    // set headers
    conn->SetHeaders(send_headers);
    conn->AppendHeader("Content-Type", "application/json"); // append header for POSTs
    nlohmann::json cmdj = R"({"grant_type": "password"})"_json; // assemble auth json command
    cmdj["client_id"] = TESLA_CLIENT_ID;                        // additional elements
    cmdj["client_secret"] = TESLA_CLIENT_SECRET;
    cmdj["email"] = MYEMAIL;
    cmdj["password"] = MYPWD;
    // this is the RestClient::Connection post
    RestClient::Response r = conn->post("/oauth/token?grant_type=password", cmdj.dump());
    
    code = r.code;
    headers = r.headers;
    body = r.body;
    
    nlohmann::json rj = nlohmann::json::parse(body);
    
    access_token = rj["access_token"];
    refresh_token = rj["refresh_token"];
    
    conn->AppendHeader("Authorization",  "Bearer " + access_token);
    

}

//Destructor
RestAPI::~RestAPI(){
    RestClient::disable();
}

nlohmann::json RestAPI::get(std::string url){
    RestClient::Response r = conn->get(url);
    // std::cout << "response code:" << r.code << std::endl;    // DEBUG
    // parse the body into json oject
    code = r.code;
    headers = r.headers;
    nlohmann::json rj = nlohmann::json::parse(r.body);
    return rj;
    
}

nlohmann::json RestAPI::post(std::string url,   nlohmann::json data){
    RestClient::Response r = conn->post(url,data.dump());
    // std::cout << "response code:" << r.code << std::endl;    // DEBUG
    // parse the body into json oject
    code = r.code;
    headers = r.headers;
    nlohmann::json rj = nlohmann::json::parse(r.body);
    return rj;
}

int RestAPI::getCode(){
    return code;
};


