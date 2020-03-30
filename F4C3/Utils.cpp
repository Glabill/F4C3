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
            strin >> config.SFH;
            config.SFHLabel = "sessionFrameHistory";
    }
}

void u::writeConfig(int frameHistory){
    Config config;
    loadConfig(config);
    std::ofstream fileout;
    
    config.SFH = frameHistory;
    
    fileout.open(config.filePath);
    fileout << config.SFHLabel << " = " << config.SFH;
    fileout.close();
}

int u::retrieveFrameHistory(){
    Config config;
    loadConfig(config);
    return config.SFH;
}

void u::solidOverlay(int width, int height, cv::Scalar color, float alpha, cv::Mat input, cv::Mat output){
    cv::Point oPt1;
    cv::Point oPt2;
                
    oPt1.x = 0;
    oPt1.y = 0;
                
    oPt2.x = width;
    oPt2.y = height;
    
    cv::Mat overlay;
                                            
    input.copyTo(overlay);
                
    cv::rectangle(overlay, oPt1, oPt2, color, -1, 0, 0);
                
    cv::addWeighted(overlay, alpha, input, 1 - alpha, 0, output);
}

void u::textOverlay(int x, int y, std::string text, cv::Scalar color, double fontScale, cv::Mat frame){
    
    cv::putText(frame, text, cv::Point(x, y), cv::FONT_HERSHEY_PLAIN, fontScale, color, 1, cv::FILLED);
}
