//
//  StreamManager.cpp
//  F4C3
//
//  Created by Gaston Gougeon on 02/03/2020.
//  Copyright © 2020 com.example. All rights reserved.
//

#include "StreamManager.hpp"

/* Opens the video stream */
void StreamManager::openStream(){
    
    capWidth = 1280;
    capHeight = 720;
    
    rs2::config cfg; // Config object for a realsense pipeline
    cfg.enable_stream(RS2_STREAM_COLOR, capWidth, capHeight, RS2_FORMAT_BGR8, 30); // Config of the config object
    
    pipe.start(cfg); // Starting the pipeline
    cv::namedWindow("F4C3", cv::WINDOW_FULLSCREEN); // Creating window
}


void StreamManager::start(){
    
    running = true;
    
    
    // Camera warmup (for auto exposure and such)
    std::cout << "Camera warmup" << std::endl;
    for(int i = 0; i < 30; i++){
        frames = pipe.wait_for_frames(); // Waiting for frames
    }
    
    std::cout << "Streaming..." << std::endl;

    while(running){

        frames = pipe.wait_for_frames(); // Waiting for frames
        rs2::frame color_frame = frames.get_color_frame(); // Get color frame from the realsense device

        cv::Mat color(cv::Size(capWidth, capHeight), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP); // Creating frame

        if(color.data){
            
            // Frame for processing
            procFrame = color;
            
            // Frame for displaying (bounding boxes and such)
            dispFrame = color.clone();
            
            analyze(); // Analyzing frame

                
            cv::imshow("F4C3", dispFrame); // Display frame in the window
            char key = (char)cv::waitKey(5); // Keyboard event
            
            switch(key)
            {
                // if the user presses 'q', exit loop and finish the program
                case 'q' :
                    running = false;
                    break;
            }
            
        }else{
            break;
        }
    }
    
}

void StreamManager::analyze(){
    
}

void StreamManager::playStream(){
    
}

void StreamManager::pauseStream(){
    
}
