//
//  vehicle.cpp
//  tesmon
//
//  Tesla Vehicle Class
//  
//
//  Created by Ed Cole on 18/10/2020.
//  Copyright © 2020 colege. All rights reserved.
//

#include <iostream>

#include "vehicle.hpp"

extern bool debug;


    Vehicle::Vehicle(){};
    Vehicle::Vehicle(RestAPI* connection, nlohmann::json new_car): vehicle{new_car}, api{connection}{
        // further constructor code
    };
    
    bool Vehicle::setVehicle_data(nlohmann::json data){
        vehicle_data = data;
        climate_state = data["climate_state"];
        charge_state = data["charge_state"];
        drive_state = data["drive_state"];
        gui_settings = data["gui_settings"];
        vehicle_state = data["vehicle_state"];
        vehicle_config = data["vehicle_config"];
        
        // TODO: we need some velidation code here
        return true;
    }

    bool Vehicle::setDrive_state(nlohmann::json data){
        drive_state = data["drive_state"];
        
        // TODO: we need some velidation code here
        return true;
    }
    
    long Vehicle::getID(){
        return vehicle["id"];
    }
    
    std::string Vehicle::getIDS(){
        return vehicle["id_s"];
    }
    
    bool Vehicle::getState(){
        if(vehicle_data["state"] == "online") return true;
        return false;
    }
    
    std::string Vehicle::getVIN(){
        return vehicle["vin"];
        
    }
    
    bool Vehicle::pullData(){
        std::string cmd_str = "/api/1/vehicles/" + getIDS() + "/vehicle_data";
        
        nlohmann::json rj = api->get(cmd_str);
        if(debug) std::cout << rj.dump(4) << std::endl;    // DEBUG
        setVehicle_data(rj["response"]);
        if(debug) std::cout << "vehicle_data: response code: " << api->getCode() << std::endl;    // DEBUG
        return true;
    }

    bool Vehicle::pullDriveState(){
        std::string cmd_str = "/api/1/vehicles/" + getIDS() + "/drive_state";
        
        nlohmann::json rj = api->get(cmd_str);
        if(debug) std::cout << rj.dump(4);                          // DEBUG
        setDrive_state(rj["response"]);
        if(debug) std::cout << "vehicle_data: response code: "
                            << api->getCode() << std::endl;         // DEBUG
        return true;
        
    };
    
    bool Vehicle::wakeup(){
        // !!!!!!!!!!!!!!!!!!!!!!!!!!
        // !!!!!This doesn't work!!!!
        // !!!!!!!!!!!!!!!!!!!!!!!!!!
        std::string cmd_str = "/api/1/vehicles/" + getIDS() + "/command/wake_up";
        
        nlohmann::json data;
        
        data["client_id"] = TESLA_CLIENT_ID;                        // additional elements
        data["client_secret"] = TESLA_CLIENT_SECRET;
        data["email"] = MYEMAIL;
        data["password"] = MYPWD;
        
        if(debug) std::cout << data.dump(4);                        // DEBUG
        
        nlohmann::json rj = api->post(cmd_str,data);
        if(debug) std::cout << rj.dump(4);                          // DEBUG
        if(debug) std::cout << "wake_up: response code: "
                    << api->getCode() << std::endl;                 // DEBUG
        return true;
        
    }
    
    bool Vehicle::honk(){
        std::string cmd_str = "/api/1/vehicles/" + getIDS() + "/command/honk_horn";
        
        std::string password = MYPWD;
        nlohmann::json data;
        data["password"] = password;
        
        if(debug) std::cout << cmd_str << std::endl;                // DEBUG
        if(debug) std::cout << data << std::endl;                   // DEBUG
        
        nlohmann::json rj = api->post(cmd_str,data);
        if(debug) std::cout << rj.dump(4);                          // DEBUG
        
        return true;
        
    }

    std::vector<Vehicle>* getVehicles(RestAPI* myTesla){
        
        std::vector<Vehicle>* cars = new std::vector<Vehicle>;
        
            std::string cmd_str("/api/1/vehicles");
            nlohmann::json rj = myTesla->get(cmd_str);
            
            int nc = rj["count"];           // number of cars
        
            if(debug) std::cout << nc << " cars found" << std::endl;
        
            nlohmann::json carsj = rj["response"];
            
            for( auto it = carsj.begin(); it != carsj.end(); ++it){
                Vehicle new_vehicle(myTesla, *it);
                cars->push_back(new_vehicle);
            }//for(carsj)
        
        return cars;
    };

   
