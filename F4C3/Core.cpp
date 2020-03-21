//
//  Core.cpp
//  F4C3
//
//  Created by Gaston Gougeon on 02/03/2020.
//  Copyright © 2020 com.example. All rights reserved.
//

#include "Core.hpp"

// Paths for the current frame and the archive folder


// Starts the app
void Core::run(){
        
    StreamManager streamManager;
    
    streamManager.openStream();
    streamManager.start();
}
