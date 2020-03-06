//
//  main.cpp
//  F4C3
//
//  Created by Gaston Gougeon on 29/02/2020.
//  Copyright © 2020 com.example. All rights reserved.
//
#include <opencv2/core.hpp>
#include <librealsense2/rs.hpp>
#include <iostream>
#include "Core.hpp"

int main(int argc, const char * argv[]) {
    
    Core core;
    std::cout << "Hello" << std::endl;
    core.run(); // Starts the app
    
}
