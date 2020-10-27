//
//  websocket.cpp
//  git_test
//  tesmon
//
//  WebSocket Wrapper class: IXWebSocket
//
//  Created by Ed Cole on 20/10/2020.
//  Copyright © 2020 colege. All rights reserved.
//

#include <iostream>
#include "websocket.hpp"



// there are no overloaded or suplimentary class member methods

void printMsgHeaders(const ix::WebSocketMessagePtr& msg){
    for (auto it : msg->openInfo.headers)
    {
        std::cout << it.first << ": " << it.second << std::endl;
    }
}

void receiveMessage_cb(const ix::WebSocketMessagePtr& msg){
    
    printMsgHeaders(msg);
    
    if (msg->type == ix::WebSocketMessageType::Message)
    {
        std::cout << "received message: " << msg->str << std::endl;
    }
    else if (msg->type == ix::WebSocketMessageType::Open)
    {
        std::cout << "Connection established" << std::endl;
    }
    if (msg->type == ix::WebSocketMessageType::Error)
        {
            std::cout << "Error message received" << std::endl;
        }
   
    
    
    
    
}
