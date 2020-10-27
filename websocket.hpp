//
//  websocket.hpp
//  tesmon
//
//  WebSocket Wrapper class: IXWebSocket
//
//  Created by Ed Cole on 20/10/2020.
//  Copyright © 2020 colege. All rights reserved.
//

#ifndef websocket_hpp
#define websocket_hpp

#include <stdio.h>


#define TESLA_WS_URI "wss://streaming.vn.teslamotors.com/streaming/"

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>

class MyWebSocket: public ix::WebSocket{
    
};

void receiveMessage_cb(const ix::WebSocketMessagePtr& msg);
    
   

#endif /* websocket_hpp */
