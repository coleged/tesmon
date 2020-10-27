//
//  rest.hpp
//  tesmon
//
//  wrapper class for REST: restclient-cpp
//
//
//  Created by Ed Cole on 18/10/2020.
//  Copyright © 2020 colege. All rights reserved.
//

#ifndef rest_hpp
#define rest_hpp

#include <iostream>
#include <string>
#include <vector>

#include <restclient-cpp/connection.h>
#include <restclient-cpp/restclient.h>

#include <nlohmann/json.hpp>

#define TESLA_URI  "https://owner-api.teslamotors.com"
#define TESLA_STREAMING "wss://streaming.vn.teslamotors.com/streaming/"

#define TESLA_URI_PREFIX "/api/1/vehicles/"
#include "secrets.hpp"


class RestAPI{
    
public:
    
    RestAPI();  // sets up connection and authenticates
    ~RestAPI(); // sends a disable
    
    nlohmann::json get(std::string url);                        // REST GET
    nlohmann::json post(std::string url, nlohmann::json data);  // REST POST
    
    
    int getCode();          // returns code of last REST transaction
    
    
    
    RestClient::Connection* conn;
    
private:
    
    RestClient::HeaderFields send_headers;   // sending headers
    std::string access_token;
    std::string refresh_token;
    
    int code;                           // response code of last response on API
    RestClient::HeaderFields headers;   // headers of last response on API
    std::string body;                   // body of last response on API
        
};

#endif /* rest_hpp */
