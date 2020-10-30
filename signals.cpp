//
//  signals.cpp
//  tesmon
//
//  Created by Ed Cole on 30/10/2020.
//  Copyright © 2020 colege. All rights reserved.
//
// Place holder for now. Just verifyng we can trap signals

#include "signals.hpp"

extern bool debug;

int mySignal = 0;

void signalHandler( int signum ) {
    if (debug) {
        std::cout << "Signal (" << signum << ") received.\n";
    }
   mySignal = signum;
   

}
