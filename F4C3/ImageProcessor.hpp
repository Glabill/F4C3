//
//  ImageProcessor.hpp
//  F4C3
//
//  Created by Gaston Gougeon on 03/03/2020.
//  Copyright © 2020 com.example. All rights reserved.
//

#ifndef ImageProcessor_hpp
#define ImageProcessor_hpp

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#endif /* ImageProcessor_hpp */

class ImageProcessor {
    
public:
    ImageProcessor(int sessionFrameHistory); // Constructor
    void crop(cv::Mat fullFrame, int x, int y, int width, int height); // Crops frame to the detected face's size and poition
    void save(cv::Mat frame, std::string savePath, std::string archSavePath, bool archive); // Saves current frame to the archive folder, and rewrites over the last saved frame.
    int varOfLaplacian(cv::Mat frame);
    
    cv::Mat IpFrame; // TEH FREMA O_o
    cv::Mat LpFrame; // Filtered frame

private:
    int frameHistory; // To track IDs in the archive folder
};
