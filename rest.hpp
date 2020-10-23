//
//  rest.hpp
//
//
//  Created by Ed Cole on 18/10/2020.
//  Copyright © 2020 colege. All rights reserved.
//

#ifndef rest_hpp
#define rest_hpp

#include <iostream>
#include <string>

#include <restclient-cpp/connection.h>
#include <restclient-cpp/restclient.h>

#include <nlohmann/json.hpp>

#define TESLA_URI  "https://owner-api.teslamotors.com"
#define TESLA_STREAMING "wss://streaming.vn.teslamotors.com/streaming/"
#include "secrets.hpp"

class RestAPI{
    
public:
    
    RestAPI();  // sets up connection and authenticates
    ~RestAPI(); // sends a disable
    
    nlohmann::json get(std::string url);
    nlohmann::json post(std::string url, nlohmann::json data);
    
    int getCode();
    
    RestClient::Connection* conn;
    
private:
    
    RestClient::HeaderFields send_headers;   // sending headers
    std::string access_token;
    std::string refresh_token;
    
    int code;               // response code of last response on API
    RestClient::HeaderFields headers;    // headers of last response on API
    std::string body;       // body of last response on API
        
};

#endif /* rest_hpp */
