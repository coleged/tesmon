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

    bool Vehicle::setClimate_state(nlohmann::json data){
        climate_state = data["climate_state"];
        // TODO: we need some validation code here
        return true;
    }

    bool Vehicle::setCharge_state(nlohmann::json data){
        charge_state = data["charge_state"];
        // TODO: we need some validation code here
        return true;
    }

    bool Vehicle::setDrive_state(nlohmann::json data){
        drive_state = data["drive_state"];
        // TODO: we need some validation code here
        return true;
    }

    bool Vehicle::setGui_settings(nlohmann::json data){
        gui_settings = data["gui_settings"];
        // TODO: we need some validation code here
        return true;
    }

    bool Vehicle::setVehicle_state(nlohmann::json data){
        vehicle_state = data["vehicle_state"];
        // TODO: we need some validation code here
        return true;
    }

    bool Vehicle::setVehicle_config(nlohmann::json data){
        vehicle_config = data["vehicle_config"];
        // TODO: we need some validation code here
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

// pullers - pull various vehicle state objects from API

    
    
    bool Vehicle::pullData(){
        setVehicle_data(getFromAPI("vehicle_data"));
        if(debug) {
            std::cout   << "pullData(): vehicle_data: response code: "
                        << api->getCode() << std::endl;
        }
        if (api->getCode() == 200){
            return true;
        }else{
            return false;
        }
    }

    bool Vehicle::pullClimateState(){
        setClimate_state(getFromAPI("climate_state"));
        if(debug) {
            std::cout   << "pullData(): climate_state: response code: "
                        << api->getCode() << std::endl;
        }
        if (api->getCode() == 200){
            return true;
        }else{
            return false;
        }
    }

    bool Vehicle::pullChargeState(){
        setCharge_state(getFromAPI("charge_state"));
        if(debug) {
            std::cout   << "pullData(): charge_state: response code: "
                        << api->getCode() << std::endl;
        }
        if (api->getCode() == 200){
            return true;
        }else{
            return false;
        }
    }

    bool Vehicle::pullDriveState(){
        setDrive_state(getFromAPI("drive_state"));
        if(debug) {
            std::cout   << "pullData(): drive_state: response code: "
                        << api->getCode() << std::endl;
        }
        if (api->getCode() == 200){
            return true;
        }else{
            return false;
        }
    }

    bool Vehicle::pullGuiSettings(){
        setGui_settings(getFromAPI("gui_settings"));
        if(debug) {
            std::cout   << "pullData(): gui_settings: response code: "
                        << api->getCode() << std::endl;
        }
        if (api->getCode() == 200){
            return true;
        }else{
            return false;
        }
    }

    bool Vehicle::pullVehicleState(){
        setVehicle_state(getFromAPI("vehicle_state"));
        if(debug) {
            std::cout   << "pullData(): vehicle_state: response code: "
                        << api->getCode() << std::endl;
        }
        if (api->getCode() == 200){
            return true;
        }else{
            return false;
        }
    }

    bool Vehicle::pullVehicleConfig(){
        setVehicle_config(getFromAPI("vehicle_config"));
        if(debug) {
            std::cout   << "pullData(): vehicle_config: response code: "
                        << api->getCode() << std::endl;
        }
        if (api->getCode() == 200){
            return true;
        }else{
            return false;
        }
    }


    
    bool Vehicle::wakeup(){
        // !!!!!!!!!!!!!!!!!!!!!!!!!!
        // !!!!!This doesn't work!!!!
        // !!!!!!!!!!!!!!!!!!!!!!!!!!
        std::string cmd_str = TESLA_URI_PREFIX + getIDS() + "/command/wake_up";
        
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
        std::string cmd_str = TESLA_URI_PREFIX + getIDS() + "/command/honk_horn";
        
        std::string password = MYPWD;
        nlohmann::json data;
        data["password"] = password;
        
        if(debug) std::cout << cmd_str << std::endl;                // DEBUG
        if(debug) std::cout << data << std::endl;                   // DEBUG
        
        nlohmann::json rj = api->post(cmd_str,data);
        if(debug) std::cout << rj.dump(4);                          // DEBUG
        
        return true;
        
    }

    

// PRIVATE METHODS

    nlohmann::json Vehicle::getFromAPI(std::string cmd){
        std::string cmd_str = TESLA_URI_PREFIX + getIDS() + "/" + cmd;
        nlohmann::json rj = api->get(cmd_str);
        if(debug) {
            std::cout << "Vehicle::getFromAPI()" << std::endl;
            std::cout << rj.dump(4) << std::endl;    // DEBUG
        }
        return rj["response"];
    };

    nlohmann::json Vehicle::postToAPI(std::string cmd){
        std::string cmd_str = TESLA_URI_PREFIX + getIDS() + "/command/" + cmd;
        
        nlohmann::json data;
        
        data["client_id"] = TESLA_CLIENT_ID;                        // additional elements
        data["client_secret"] = TESLA_CLIENT_SECRET;
        data["email"] = MYEMAIL;
        data["password"] = MYPWD;
        
        if(debug) std::cout << data.dump(4);                        // DEBUG
        
        nlohmann::json rj = api->post(cmd_str,data);
        return rj["response"];
    };

// NON MEMBER FUNCTIONS

std::vector<Vehicle>* getVehicles(RestAPI* myTesla){
    
    // create vector on the heap
    std::vector<Vehicle>* cars = new std::vector<Vehicle>;
    
        std::string cmd_str(TESLA_URI_PREFIX);
        nlohmann::json rj = myTesla->get(cmd_str);
        if (debug) {
            std::cout << "Recieved Headers" << std::endl;
            std::cout << myTesla->getHeaders().dump(4) << std::endl;
        }
        
        int nc = rj["count"];           // number of cars
    
        if(debug) std::cout << nc << " cars found" << std::endl;
    
        nlohmann::json carsj = rj["response"];
        
        for( auto it = carsj.begin(); it != carsj.end(); ++it){
            Vehicle new_vehicle(myTesla, *it);
            cars->push_back(new_vehicle);
        }//for(carsj)
    
    return cars;
};

   
