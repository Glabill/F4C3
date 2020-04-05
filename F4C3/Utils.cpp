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
        
        std::istringstream sin(line.substr(line.find("=") + 1));
        
        if (line.find("sessionFrameHistory") != -1)
            sin >> config.sessionFrameHistory;
    }
}

void u::writeFrameHistory(int frameHistory){
    
    Config config;
    config.filePath = "/Users/gastongougeon/Desktop/F4C3/data/config.txt";
    std::ofstream fileout;
    
    fileout.open(config.filePath);
    fileout << "sessionFrameHistory = " << frameHistory;
    fileout.close();
    
    std::cout << config.filePath << " " << frameHistory << '\n';
}

int u::retrieveFrameHistory(){
    Config config;
    loadConfig(config);
    return config.sessionFrameHistory;
}
