//
//  StreamManager.cpp
//  F4C3
//
//  Created by Gaston Gougeon on 02/03/2020.
//  Copyright © 2020 com.example. All rights reserved.
//

#include "StreamManager.hpp"

/* Opening sequence for the video stream */
void StreamManager::openStream(){
    
    archive = true;
    save = true;

    // Keeping track of the saved frame history
    frameHistory = u::retrieveFrameHistory();
    std::cout << frameHistory << '\n';
    
    // Capture width and height
    capWidth = 1280;
    capHeight = 720;
    
    // Config object for a realsense pipeline
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_COLOR, capWidth, capHeight, RS2_FORMAT_BGR8, 30);
    
    // Starting the pipeline
    pipe.start(cfg);
    
    // Creating window
    cv::namedWindow("F4C3", cv::WINDOW_FULLSCREEN);
}


/* Closing sequence for the video stream */
void StreamManager::closeStream(){
    
    // Writing frame history to config file for the next session
    u::writeConfig(frameHistory);
    running = false;
}


/* Stream start and loop */
void StreamManager::start(){
    
    // RINGUNN °_°
    running = true;
    
    // Camera warmup (for auto exposure and such)
    std::cout << "Camera warmup\n";
    for (int i = 0; i < 30; i++){
        frames = pipe.wait_for_frames(); // Waiting for frames
    }
    
    
    
    if (!faceDetector.load("/Users/gastongougeon/Desktop/F4C3/models/haarcascade_frontalface_default.xml")){
        std::cerr << "Detection model is not loaded \n";
        return;
    } else {
        std::cout << "Detection model loaded \n";
    }
    
    std::cout << "Streaming...\n";

    while (running){
        
        // Waiting for frames
        frames = pipe.wait_for_frames();
        // Get color frame from the realsense device
        rs2::frame color_frame = frames.get_color_frame();
        
        // Creating OpenCV image from the camera frame
        cv::Mat color(cv::Size(capWidth, capHeight), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);

        if (color.data){
            // Frame for processing
            procFrame = color;
            // Frame for displaying (bounding boxes and such)
            dispFrame = color.clone();
            // Analyzing frame
            
            analyze();
            
            // Display frame in the window
            u::textOverlay((capWidth/2 - 15), 20, "F4C3", u::GREEN(), 1.3, dispFrame);
            u::textOverlay(20, capHeight - 40, "Quit : 'q'", u::GREEN(), 0.7, dispFrame);
            u::textOverlay(20, capHeight - 60, "Toggle frame archiving : 'a'", u::GREEN(), 0.7, dispFrame);
            u::textOverlay(20, capHeight - 80, "Toggle frame saving : 's'", u::GREEN(), 0.7, dispFrame);

            u::textOverlay(20, 40, "Frame history : ", u::GREEN(), 0.7, dispFrame);
            u::textOverlay(20, 60, "Sharpness : ", u::GREEN(), 0.7, dispFrame);
            u::textOverlay(130, 40, std::to_string(frameHistory), u::GREEN(), 0.7, dispFrame);
            u::textOverlay(20, 80, "Saving frames : ", u::GREEN(), 0.7, dispFrame);
            if(save){
                u::textOverlay(130, 80, "yes", u::GREEN(), 0.7, dispFrame);
            }else if (!save){
                u::textOverlay(130, 80, "no", u::GREEN(), 0.7, dispFrame);
            }
            
            u::textOverlay(20, 100, "Archiving frames : ", u::GREEN(), 0.7, dispFrame);
            if(archive){
                u::textOverlay(130, 100, "yes", u::GREEN(), 0.7, dispFrame);
            }else if (!archive){
                u::textOverlay(130, 100, "no", u::GREEN(), 0.7, dispFrame);
            }

            
            cv::imshow("F4C3", dispFrame);
            
            // Keyboard event
            char key = (char)cv::waitKey(5);
            switch(key)
            {
                // if the user presses 'q', exit loop and finish the program
                case 'q' :
                    closeStream();
                    break;
                    
                case 's' :
                    if(save){
                        save = false;
                    }else if (!save){
                        save = true;
                    }
                    
                case 'a' :
                    if (archive){
                        archive = false;
                    }else if (!archive){
                        archive = true;
                    }
            }
        } else {
            std::cout << "No image data";
            break;
        }
    }
}


/* analyses the image (and saves it if it fits) */
void StreamManager::analyze(){
    
    // Captured frames Save path
    savePath = "/Users/gastongougeon/Desktop/F4C3/face/";
    archRelSavePath = "/face_archive/";
    
    // Captured frames outputs
    faceFileName = "face.png";
    archiveFileName = "archive-face" + std::to_string(frameHistory) + ".png";
    
    // Spawns an image processor instance with the current frame history as its parameter
    ImageProcessor imageProcessor(frameHistory);
    
    // A place for storing faces
    std::vector<cv::Rect> faces;
    
    if (!procFrame.data){
        std::cerr<< "Frame to be analyzed is not loaded \n";
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
        pt1_1 = cv::Point(pt1.x - (faces[0].width * 0.2), pt1.y - (faces[0].height * 0.3));
        pt2_2 = cv::Point(pt2.x + (faces[0].width * 0.2), pt2.y + (faces[0].height * 0.5));
        
        // Drawing bounding boxes
        cv::rectangle(dispFrame, pt1, pt2, u::GREEN(), 1, 0, 0);
        cv::rectangle(dispFrame, pt1_1, pt2_2, u::GREEN(), 2, 0, 0);
        
        // Checking face position in the image
        if (pt1.x < 0 || pt2.x > capWidth || pt1.y - (faces[0].height * 0.3) < 0 || pt2.y + (faces[0].height * 0.5) > capHeight){
            return;
        } else if (faces[0].height > 100 && faces[0].height < 400){
            
            imageProcessor.crop(procFrame, pt1_1.x, pt1_1.y,faces[0].width, faces[0].height + faces[0].height * 0.5);
            
            blurGrade = imageProcessor.varOfLaplacian(imageProcessor.IpFrame);
            // std::cout << blurGrade << '\n';
            
            u::textOverlay(130, 60, (std::to_string(blurGrade)), cv::Scalar(0, 255, 0), 0.7, dispFrame);

            
            if(blurGrade > 100){
                
                if(save){
                    imageProcessor.save(imageProcessor.IpFrame, (savePath + faceFileName), (savePath + archRelSavePath + archiveFileName), archive);
                    if(archive){
                        frameHistory ++;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
                // u::solidOverlay(capWidth, capHeight, cv::Scalar(255, 255, 255), 0.2, dispFrame, dispFrame);
            } else
                return;
        } else
            return;
    } else
        return;
}



