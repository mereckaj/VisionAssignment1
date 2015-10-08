//
// Created by mereckaj on 07/10/15.
//
#include "Utils.h"
#include "Preprocess.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc,char** argv){
    cv::Mat* images;
    int menuChoice;

    ParseCommandLineArgument(argc, argv);
    images = LoadImages(imageFiles,IMAGE_LOCATION);
}