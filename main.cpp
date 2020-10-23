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

static MyWebSocket::WebSocket* ws = nullptr; // WebSocket for streaming

// Handler for receipts on WebSocket
void ws_handler(const std::string & message)
{
    printf(">>> %s\n", message.c_str());
     if (message == "world"){
         // ws->close();
         
     }
    
}


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
    
    /*
     
     ******* HINTS *******
     
     {'uri': s_url + long_vid +'/?values=' + argv.values,
     'method' : 'GET',
     'auth': {'user': creds.username,'pass': token},
     'timeout' : 125000 // a bit more than the expected 2 minute max long poll
     },
     
     var streamdata = {
         id_s : vid.toString(),
         vehicle_id : long_vid,
         timestamp : array[0],
         speed : array[1],
         odometer : array[2],
         soc : array[3],
         elevation : array[4],
         est_heading : array[5],
         est_lat : array[6],
         est_lng : array[7],
         power : array[8],
         shift_state : array[9],
         range : array[10],
         est_range : array[11],
         heading : array[12]
     };

     exports.stream_columns = [ 'speed',
                                'odometer',
                                'soc',
                                'elevation',
                                'est_heading',
                                'est_lat',
                                'est_lng',
                                'power',
                                'shift_state',
                                'range',
                                'est_range',
                                'heading'
                               ];

     exports.stream = function(options, cb) {
       if (!cb) cb = function(error, response, body) {
                //jshint unused: false
       };
     

       request({ method : 'GET',
                 url    : 'https://streaming.vn.teslamotors.com/stream/' + options.vehicle_id + '/?values=' + exports.stream_columns.join(','),
                 gzip: true,
                 auth   :
                 { user : options.email,
                   pass : options.password
                 }
               }, cb);
     };

     "ws://streaming.vn.teslamotors.com/streaming/"
     
     if (this.ws || !this.vid || !this.token) {
             return;
     }
     ulog('opening new websocket, vid=' + this.vid + ', token=' + this.token + ', backoff=' + this.backoff);
     this.ws = new WebSocket('wss://streaming.vn.teslamotors.com/streaming/', {
             followRedirects: true,
     });

     this.ws.on('open', () => {
             const msg = {
                     msg_type: 'data:subscribe',
                     token: new Buffer.from(creds.email + ':' + this.token).toString('base64'),
                     value: teslams.stream_columns.join(','),
                     tag: this.vid,
             };
             this.ws.send(JSON.stringify(msg));
     });

     
     */
    
    // better to do this by building JSON object
    /*
    std::string stream_setup_message =
        R"({"method" : "GET",
          "uri" : "ws://streaming.vn.teslamotors.com/streaming/151975870647/?values=speed,odometer,soc,elevation,est_heading,est_lat,est_lng,power,shift_state,range,est_range,heading",
          "auth"   :
                {   "user" : "colege@gmail.com",
                    "pass" : "Umbert088"
          }
            "timeout" : "125000"
    })";
     
    
    std::string auth_tok = "colege@gmail.com:Umbert088";
    std::vector<BYTE> auth_tok64 = base64_decode(auth_tok);
    std::string auth_tok64s = std::string(auth_tok64.begin(),auth_tok64.end());
    */
    
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



