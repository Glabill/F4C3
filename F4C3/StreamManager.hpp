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

#endif /* StreamManager_hpp */

class StreamManager{
    
public:
    void openStream(); // Opens the video stream
    void start(); // Starts the video stream
    void pauseStream(); // Pauses the video stream
    void playStream(); // Plays the video stream
    int* analyze(); // Analyzes the current frame
    
private:
    int capWidth; // Width of the video stream
    int capHeight; // Height of the video stream
    
    cv::Mat procFrame; // Frame for processing
    cv::Mat dispFrame; // Frame for displaying (bounding boxes and such)
    
    rs2::pipeline pipe; // Realsense pipeline to abstract the device
    rs2::frameset frames; // Realsense frameset to store frames
    
    // Diverse points defining the face's bounding box
    cv::Point pt1;
    cv::Point pt2;
    cv::Point pt1_1;
    cv::Point pt2_2;
    
    bool running; // 2 CHECK IF IT S RUNGHING (°|°)
    
    cv::CascadeClassifier faceDetector; // Face detector
    
};
