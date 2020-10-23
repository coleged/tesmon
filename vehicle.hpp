//
//  vehicle.hpp
// 
//
//  Created by Ed Cole on 18/10/2020.
//  Copyright © 2020 colege. All rights reserved.
//

#ifndef vehicle_hpp
#define vehicle_hpp

#include "rest.hpp"
#include <nlohmann/json.hpp>

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
    bool setDrive_state(nlohmann::json data);
    
    // car query (update) methods
    bool pullData();
    bool pullChargeState();
    bool pullClimateState();
    bool pullDriveState();
    bool pullGUISettings();
    bool pullVehicleState();
    bool pullVehicleConfig();
    bool pullMobileEnabled();
    bool pullNearbyChargingSites();
    
    
    
    
    // command methods
    bool wakeup();
    bool honk();
    bool flash();
    bool remoteStart();
    bool triggerHomelink();
    bool sentryMode(bool action);   // action = true to enable
    
    
private:
    RestAPI* api;           // REST connection to Tesla
    
    nlohmann::json vehicle;
                                /*
                                 {
                                   "id": 12345678901234567,
                                   "vehicle_id": 1234567890,
                                   "vin": "5YJSA11111111111",
                                   "display_name": "Nikola 2.0",
                                   "option_codes": "MDLS,RENA,AF02,APF1,APH2,APPB,AU01,BC0R,BP00,BR00,BS00,CDM0,CH05,PBCW,CW00,DCF0,DRLH,DSH7,DV4W,FG02,FR04,HP00,IDBA,IX01,LP01,ME02,MI01,PF01,PI01,PK00,PS01,PX00,PX4D,QTVB,RFP2,SC01,SP00,SR01,SU01,TM00,TP03,TR00,UTAB,WTAS,X001,X003,X007,X011,X013,X021,X024,X027,X028,X031,X037,X040,X044,YFFC,COUS",
                                   "color": null,
                                   "tokens": ["abcdef1234567890", "1234567890abcdef"],
                                   "state": "online",
                                   "in_service": false,
                                   "id_s": "12345678901234567",
                                   "calendar_enabled": true,
                                   "api_version": 7,
                                   "backseat_token": null,
                                   "backseat_token_updated_at": null
                                 }
                                 */
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


#endif /* vehicle_hpp */
