//
// Created by mereckaj on 08/10/15.
//

#include "Utils.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#define FLAG_DEBUG "--debug"

static int DEBUG_MODE;

void ParseCommandLineArgument(int argument_count, char** argument_array){
    DEBUG_MODE = 0;
    for(int i = 1; i < argument_count;i++) {
        if(strcmp(FLAG_DEBUG,argument_array[i])==0){
            DEBUG_MODE = 1;
            debug("Debug Enabled");
        }
    }
}

void debug(char* message){
    debug(std::string(message));
}
void debug(std::string message){
    if(DEBUG_MODE){
        std::cout << message << std::endl;
    }
}

void DisplayImage(std::string title,cv::Mat image){
    imshow(title,image);
    cvWaitKey(0);
    cv::destroyWindow(title);
}