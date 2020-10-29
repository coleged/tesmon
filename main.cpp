//
//  main.cpp
//  tesmon
//
//  Tesla monitor and control tool
//
//  Development prototying and experimentation
//
//  WORK IN PROGRESS
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
    
    std::vector<Vehicle>* cars;      // my cars
    RestAPI *myTesla = new RestAPI; // initiate a REST connection with Tesla
    cars = getVehicles(myTesla);    // get vector of cars from the API
    for( auto thisCar = cars->begin(); thisCar != cars->end(); ++thisCar){
        if(debug) std::cout << "attempting wakeup" << std::endl;
        thisCar->wakeup();
        if(debug) std::cout << "pulling data" << std::endl;
        thisCar->pullData();
        if(debug){
            std::cout   << std::endl << "vehicle found: "
                        << thisCar->getID()
                        << " " << thisCar->getVIN();
            if(thisCar->getState()){
                std::cout << " Vehicle online" << std::endl;
            }else{
                std::cout << " Vehicle offline" << std::endl;
            }
        }//if debug
    }//for(cars)
    
    // honk the first car on the vector
    Vehicle thisCar = cars->front();
    thisCar.honk();
    
    // finished with this REST connection for now
    delete myTesla;
    
    Vehicle firstCar = (*cars)[0]; // makes copy of Vector element on the stack
    
    if(debug) std::cout << "*****************************" << std::endl;
    if(debug) std::cout << "starting streaming connection" << std::endl;
    if(debug) std::cout << "with " << TESLA_STREAMING << std::endl;
    
    MyWebSocket ws;
    ws.setUrl(TESLA_STREAMING);
    ws.enableAutomaticReconnection();
    //ws.setHeartBeatPeriod( 45 );
    usleep( 20000 );

    
    std::string auth_str = std::string(MYEMAIL) + ":" + std::string(MYPWD);
    std::string auth_tok64 = base64_encode(auth_str, (int)auth_str.size());
    
   
    ix::WebSocketHttpHeaders headers;
    headers["Connection"] = "upgrade";
    headers["Upgrade"] = "HTTP/1.1";
    ws.setExtraHeaders(headers);
    ws.addSubProtocol("HTTP/1.1");
    
    //print sub protocols   // DEBUG
    for(auto it = ws.getSubProtocols().begin(); it != ws.getSubProtocols().end(); ++it){
            std::cout << "SP:" << *it << std::endl;
    }

    
    nlohmann::json message;
    
    message["msg_type"] = "data:subscribe";
    //message["Connection"] = "keep_alive";
    //message["connection_timeout"] = "200000";
    message["token"] = auth_tok64.c_str();
    
    message["value"] =  "speed,odometer,soc,elevation,est_heading,est_lat,est_lng,power,shift_state,range,est_range,heading";
     
    //message["value"] =  "est_lat,est_lng,power";
    //message["tag"] = cars[0].getIDS().c_str();
    //message["tag"] = cars[0].getID();
    message["tag"] = firstCar.getID();
    
    std::string stream_setup_message = message.dump(4);
    
    
    ws.setOnMessageCallback(receiveMessage_cb);
    
    usleep( 20000 );

    ws.start();
    //ws.connect(360);

    
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



