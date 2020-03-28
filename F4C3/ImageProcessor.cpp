//
//  ImageProcessor.cpp
//  F4C3
//
//  Created by Gaston Gougeon on 03/03/2020.
//  Copyright © 2020 com.example. All rights reserved.
//

#include "ImageProcessor.hpp"

// ImageProcessor's constructor takes the frame history as its only parameter
ImageProcessor::ImageProcessor(int sessionFrameHistory){
    // set IP's frame history to the scurrent frame history value
    frameHistory = sessionFrameHistory;
}


/* Crops an image */
void ImageProcessor::crop(cv::Mat fullFrame, int x, int y, int width, int height){
    
    if(!fullFrame.data){
        std::cout << "Error : source image not loaded \n";
        return;
    }
    
    // Cropping current frame;
    IpFrame = fullFrame(cv::Rect(x, y, width, height));
}


/* Saves and archives an image */
void ImageProcessor::save(cv::Mat frame, std::string savePath, std::string archSavePath){
    
    if(!frame.data){
        std::cout << "Error : cropped image not loaded \n";
        return;
    }
    // Writing frame to the current frame folder
    cv::imwrite(savePath, frame);
    // Archiving frame in the archive folder
    cv::imwrite(archSavePath, frame);
    
    std::cout << "Frame saved. \n";
            
    frameHistory ++;
}

/**/
int ImageProcessor::varOfLaplacian(cv::Mat frame){
    
    cv::Mat gray;
    cv::Mat laplace;
    
    cv::cvtColor(frame, gray, cv::COLOR_RGB2GRAY);
    
    cv::Scalar mean;
    cv::Scalar stdDev;
    
    // Computes the Laplacian of the input image
    cv::Laplacian(gray, laplace, 5);
    cv::meanStdDev(laplace, mean, stdDev);
    
    return stdDev[0] * stdDev[0];
};
