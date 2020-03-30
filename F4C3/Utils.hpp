//
//  Utils.hpp
//  F4C3
//
//  Created by Gaston Gougeon on 2020-03-21.
//  Copyright © 2020 com.example. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <opencv2/imgproc.hpp>

namespace u {

    struct Config {
        int SFH; // Last session's saved frame history
        std::string SFHLabel;
        std::string filePath; // Where the config file path is situated
    };

    
    void loadConfig(Config& config);

    std::string readConfig(Config& config);

    void writeConfig(int frameHistory);

    int retrieveFrameHistory();

    void solidOverlay(int with, int height, cv::Scalar color, float alpha, cv::Mat input, cv::Mat output);

void textOverlay(int x, int y, std::string text, cv::Scalar color, double fontScale,cv::Mat frame);

}
#endif /* Utils_hpp */
