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

namespace u {

    struct Config {
        int sessionFrameHistory; // Last session's saved frame history
        std::string filePath; // Where the config file path is situated
    };

    
    void loadConfig(Config& config);

    void writeFrameHistory(int frameHistory);

    int retrieveFrameHistory();

}
#endif /* Utils_hpp */
