//
//  StreamManager.cpp
//  F4C3
//
//  Created by Gaston Gougeon on 02/03/2020.
//  Copyright © 2020 com.example. All rights reserved.
//

#include "StreamManager.hpp"
#include "ImageProcessor.hpp"

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
    
    //RINGUNN °_°
    running = true;
    
    // Camera warmup (for auto exposure and such)
    std::cout << "Camera warmup\n";
    for(int i = 0; i < 30; i++){
        frames = pipe.wait_for_frames(); // Waiting for frames
    }
    
    std::cout << "Streaming...\n";

    while(running){
        
        // Waiting for frames
        frames = pipe.wait_for_frames();
        // Get color frame from the realsense device
        rs2::frame color_frame = frames.get_color_frame();
        
        // Creating OpenCV image from the camera frame
        cv::Mat color(cv::Size(capWidth, capHeight), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);

        if(color.data){
            // Frame for processing
            procFrame = color;
            // Frame for displaying (bounding boxes and such)
            dispFrame = color.clone();
            // Analyzing frame
            analyze();
            ImageProcessor imageProcessor;
            // Display frame in the window
            cv::imshow("F4C3", dispFrame);
            // Keyboard event
            char key = (char)cv::waitKey(5);
            switch(key)
            {
                // if the user presses 'q', exit loop and finish the program
                case 'q' :
                    running = false;
                    break;
            }
        }else{
            std::cout << "No image data";
            break;
        }
    }
}

void StreamManager::analyze(){
    
    // Loading the detection model
    if(!faceDetector.load("/Users/gastongougeon/Desktop/F4C3/models/haarcascade_frontalface_default.xml")){
        std::cout << "Detection model is not loaded \n";
        return;
    }
    
    // A place for storing faces
    std::vector<cv::Rect> faces;
    
    if(!procFrame.data){
        std::cout<< "Error : Frame to be analyzed is not loaded \n";
        return;
    }
    
    // Detecting faces
    faceDetector.detectMultiScale(procFrame, faces);
    
    if (faces.size() > 0){
        // Detected face top left corner face
        pt1 = cv::Point(faces[0].x, faces[0].y);
        // Detected face bottom right corner
        pt2 = cv::Point(faces[0].x + faces[0].height, faces[0].y + faces[0].width);

        // New points for a larger Bounding Box
        pt1_1 = cv::Point(pt1.x, pt1.y - (faces[0].height * 0.3));
        pt2_2 = cv::Point(pt2.x, pt2.y + (faces[0].height * 0.5));
        
        cv::rectangle(dispFrame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 0, 0);
        cv::rectangle(dispFrame, pt1_1, pt2_2, cv::Scalar(0,255,0), 2, 0, 0);
    }
}

void StreamManager::playStream(){
    running = true;
}

void StreamManager::pauseStream(){
    running = false;
}
