//
//  main.cpp
//  tesmon
//
//  Tesla monitor and control tool
//
//  Development prototying and experimentation
//
//  Created by Ed Cole on 15/10/2020.
//  Copyright © 2020 colege. All rights reserved.
//
// Initial testing of tesla-api over REST


#include <iostream>
#include <restclient-cpp/connection.h>
#include <restclient-cpp/restclient.h>
#include <nlohmann/json.hpp>
#include "rest.hpp"
#include "vehicle.hpp"
#include "websocket.hpp"
#include "base64.hpp"

#ifndef _DEBUG
#define _DEBUG  true
#endif
bool debug = _DEBUG;


// *******************************
//       main
// *******************************

int main(int argc, const char * argv[]) {
    
    std::vector<Vehicle> cars;      // my cars

    RestAPI *myTesla = new RestAPI; // initiate a REST connection with Tesla
    
    std::string cmd_str("/api/1/vehicles");
    nlohmann::json rj = myTesla->get(cmd_str);
    int nc = rj["count"]; // number of cars
    if(debug) std::cout << nc << " cars found" << std::endl;
    nlohmann::json carsj = rj["response"];
    
    for( auto it = carsj.begin(); it != carsj.end(); ++it){
        Vehicle new_vehicle(myTesla, *it);
        
        //std::cout << "attempting honk" << std::endl;
        //new_vehicle.honk();
        
        if(debug) std::cout << "attempting wakeup" << std::endl;
        new_vehicle.wakeup();
        
        if(debug) std::cout << "pulling data" << std::endl;
        new_vehicle.pullData();
        
        cars.push_back(new_vehicle);
    }//for(carsj)
    
    
    if(debug){
        std::cout     << std::endl << "first vehicle found: "
                            << cars[0].getID()
                            << " " << cars[0].getVIN()
                            << std::endl;
        if(cars[0].getState()){
            std::cout << "Vehicle is online" << std::endl;
        }else{
            std::cout << "Vehicle is offline" << std::endl;
        }
    }//if debug
    
    // finished with this REST connection for now
    delete myTesla;
    
    if(debug) std::cout << "*****************************" << std::endl;
    if(debug) std::cout << "starting streaming connection" << std::endl;
    if(debug) std::cout << "with " << TESLA_STREAMING << std::endl;
    
    MyWebSocket ws;
    ws.setUrl(TESLA_STREAMING);
    
    //std::string auth_str = "colege@gmail.com:Umbert088";
    std::string auth_str = std::string(MYEMAIL) + ":" + std::string(MYPWD);
    std::string auth_tok64 = base64_encode(auth_str, (int)auth_str.size());
    
    
    //std::cout << "base64 token: " << auth_tok64 << std::endl;   // DEBUG
    
    nlohmann::json message;
    //message["uri"]  = "wss://streaming.vn.teslamotors.com/streaming/151975870647/";
    message["msg_type"] = "data:subscribe";
    //message["Connection"] = "keep_alive";
    //message["connection_timeout"] = "200000";
    message["token"] = auth_tok64.c_str();
    
    message["value"] =  "speed,odometer,soc,elevation,est_heading,est_lat,est_lng,power,shift_state,range,est_range,heading";
     
    //message["value"] =  "est_lat,est_lng,power";
    //message["tag"] = cars[0].getIDS().c_str();
    //message["tag"] = cars[0].getID();
    message["tag"] = cars[0].getID();
    
    std::string stream_setup_message = message.dump(4);
    
    //std::cout << stream_setup_message << std::endl;
    //ws = MyWebSocket::WebSocket::from_url("ws://localhost:8126/foo");
    // need to set redirects true
    
    
    // Callback lambda
    ws.setOnMessageCallback([](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Message)
            {
                std::cout << "<< Receiving <<" << msg->str << std::endl;
                
            }
            else if (msg->type == ix::WebSocketMessageType::Open)
            {
                std::cout << std::endl << "Connection established" << std::endl;
            }
        }
    );
    
    ws.start();
    
    while ( ws.getReadyState() != ix::ReadyState::Open ){
        usleep(15000);
        std::cout << "+";
    }; // wait for connection
    std::cout << std::endl;
    std::cout << ">> sending >>" << std::endl;
    std::cout << stream_setup_message << std::endl;
    ws.send(stream_setup_message.c_str());
    
    // loops until connection closed
    while (true) {
      
        
    }
    
    // tidy up
    ws.stop();
    
    
    return 0;
}



