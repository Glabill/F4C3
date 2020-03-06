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

#endif /* StreamManager_hpp */

class StreamManager{
    
public:
    void openStream(); // Opens the video stream
    void start(); // Starts the video stream
    void pauseStream(); // Pauses the video stream
    void playStream(); // Plays the video stream
    void analyze(); // Analyzes the current frame
    
private:
    int capWidth; // Width of the video stream
    int capHeight; // Height of the video stream
    
    cv::Mat procFrame; // Frame for processing
    cv::Mat dispFrame; // Frame for displaying (bounding boxes and such)
    
    rs2::pipeline pipe; // Realsense pipeline to abstract the device
    rs2::frameset frames; // Realsense frameset to store frames
    
    bool running; // to check is it's running
    
};
