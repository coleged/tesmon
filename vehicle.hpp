//
//  vehicle.hpp
//  tesmon
//
//  Tesla Vehicle Class
//
//  Created by Ed Cole on 18/10/2020.
//  Copyright © 2020 colege. All rights reserved.
//

#ifndef vehicle_hpp
#define vehicle_hpp

#include <nlohmann/json.hpp>
#include "rest.hpp"

class Vehicle {
    
public:
    Vehicle();
    Vehicle(RestAPI* connection, nlohmann::json new_car);
    
    // Getters
    long getID();
    std::string getIDS();
    bool getState();
    std::string getVIN();
    
    // Setters
    bool setVehicle_data(nlohmann::json data);
    bool setClimate_state(nlohmann::json data);
    bool setCharge_state(nlohmann::json data);
    bool setDrive_state(nlohmann::json data);
    bool setGui_settings(nlohmann::json data);
    bool setVehicle_state(nlohmann::json data);
    bool setVehicle_config(nlohmann::json data);
    
    // car query (update) methods
    bool pullData();
    bool pullChargeState();
    bool pullClimateState();
    bool pullDriveState();
    bool pullGuiSettings();
    bool pullVehicleState();
    bool pullVehicleConfig();
    bool pullMobileEnabled();       // TO BE IMPLIMENTED
    bool pullNearbyChargingSites(); // TO BE IMPLIMENTED
    
    // command methods
    bool wakeup();
    bool honk();
    bool flash();
    bool remoteStart();
    bool triggerHomelink();
    bool sentryMode(bool action);   // action = true to enable
    
    
private:
    
    nlohmann::json getFromAPI(std::string cmd);
    nlohmann::json postToAPI(std::string cmd);
    
    RestAPI* api;           // REST connection to Tesla
    
    nlohmann::json vehicle;
                                
    nlohmann::json vehicle_data;
    // it would seem there is quite a lot of overlap in this data. e.g.
    // charge_state, climate_state, drive_state, gui_settings, vehicle_state & vehicle_config
    // are all contained in the json response for vehicle_data
    nlohmann::json charge_state;
    nlohmann::json climate_state;
    nlohmann::json drive_state;
    nlohmann::json gui_settings;
    nlohmann::json vehicle_state;
    nlohmann::json vehicle_config;
    bool mobile_enable;
    
};

std::vector<Vehicle>* getVehicles(RestAPI* myTesla);


#endif /* vehicle_hpp */
