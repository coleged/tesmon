//
//  websocket.hpp
//  git_test
//
//  Created by Ed Cole on 20/10/2020.
//  Copyright © 2020 colege. All rights reserved.
//

#ifndef websocket_hpp
#define websocket_hpp

#include <stdio.h>

/*
#include "easywsclient.hpp"

#define TESLA_WS_URI "ws://streaming.vn.teslamotors.com/streaming/"

class MyWebSocket: public easywsclient::WebSocket{
    
};
 */

#define TESLA_WS_URI "wss://streaming.vn.teslamotors.com/streaming/"

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>

class MyWebSocket: public ix::WebSocket{
    
};


#endif /* websocket_hpp */
