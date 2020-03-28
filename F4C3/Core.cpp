//
//  Core.cpp
//  F4C3
//
//  Created by Gaston Gougeon on 02/03/2020.
//  Copyright © 2020 com.example. All rights reserved.
//

#include "Core.hpp"

// Starts the app
void Core::run(){
    
    // StreamManager will handle all the capture
    StreamManager streamManager;
    
    // Opening video stream and starting capture session
    streamManager.openStream();
    streamManager.start();
}
