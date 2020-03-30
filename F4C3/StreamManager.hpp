//
//  StreamManager.hpp
//  F4C3
//
//  Created by Gaston Gougeon on 02/03/2020.
//  Copyright © 2020 com.example. All rights reserved.
//

#ifndef StreamManager_hpp
#define StreamManager_hpp

#include <iostream>
#include <librealsense2/rs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>

#include "ImageProcessor.hpp"
#include "Utils.hpp"


#endif /* StreamManager_hpp */

/* Stream loop, image analysis, image saving etc.. */
class StreamManager{
    
public:
    
    void openStream(); // Opens the video stream
    void closeStream(); // Closes the video stream
    void start(); // Starts the video stream
    
private:
    
    void analyze(); // Analyzes the current frame
    
    int frameHistory; // Keeps track of the saved frame history in the current session
    
    int capWidth; // Width of the video stream
    int capHeight; // Height of the video stream
    
    rs2::pipeline pipe; // Realsense pipeline to abstract the device
    rs2::frameset frames; // Realsense frameset to store frames
    
    cv::Mat procFrame; // Frame for processing
    cv::Mat dispFrame; // Frame for displaying (bounding boxes and such)
    
    cv::CascadeClassifier faceDetector; // Face detection classifier
    
    // Diverse points defining the face's bounding boxes
    cv::Point pt1;
    cv::Point pt2;
    cv::Point pt1_1;
    cv::Point pt2_2;
    
    std::string savePath; // Global "face" folder path
    std::string archRelSavePath; // "archive" folder path (relative savePath)
    std::string faceFileName; // Frame file name (extension implies codec)
    std::string archiveFileName; // Archive Frame file name (same ^ )
    
    int blurGrade;
        
    bool running; // 2 CHECK IF IT S RUNGHING (°|°)
};
