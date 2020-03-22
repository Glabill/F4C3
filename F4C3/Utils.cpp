//
//  Utils.cpp
//  F4C3
//
//  Created by Gaston Gougeon on 2020-03-21.
//  Copyright © 2020 com.example. All rights reserved.
//

#include "Utils.hpp"

void u::loadConfig(Config& config){
    
    config.filePath = "/Users/gastongougeon/Desktop/F4C3/data/config.txt";
    
    std::ifstream filein(config.filePath);
    std::string line;
    
    while (getline(filein, line)) {
        
        std::istringstream strin(line.substr(line.find("=") + 1));
        
        if (line.find("sessionFrameHistory") != -1)
            strin >> config.sessionFrameHistory;
    }
}

void u::writeFrameHistory(int frameHistory){
    Config config;
    loadConfig(config);
    std::ofstream fileout;
    
    config.sessionFrameHistory = frameHistory;
    
    fileout.open(config.filePath);
    fileout << "sessionFrameHistory = " << config.sessionFrameHistory;
    fileout.close();
}

int u::retrieveFrameHistory(){
    Config config;
    loadConfig(config);
    return config.sessionFrameHistory;
}
