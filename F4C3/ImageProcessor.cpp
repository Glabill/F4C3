//
//  ImageProcessor.cpp
//  F4C3
//
//  Created by Gaston Gougeon on 03/03/2020.
//  Copyright © 2020 com.example. All rights reserved.
//

#include "ImageProcessor.hpp"

ImageProcessor::ImageProcessor(){
    frameHistory = 0;
}

void ImageProcessor::crop(cv::Mat fullFrame, int x, int y, int width, int height){
    
    if(!frame.data){
        std::cout << "Error : source image not loaded \n";
        return;
    }
    // Cropping current frame;
    frame = fullFrame(cv::Rect(x, y, width, height));
}

void ImageProcessor::save(cv::Mat frame, std::string savePath, std::string archSavePath){
    
    if(!frame.data){
        std::cout << "Error : cropped image not loaded \n";
    }
    // Writing frame to the current frame folder
    cv::imwrite(savePath, frame);
    // archiving frame in the archive folder
    cv::imwrite((archSavePath + "face_archive" + std::to_string(frameHistory) + ".png"), frame);
    
    std::cout << "Frame saved. \n";
            
    frameHistory ++;
    
}
