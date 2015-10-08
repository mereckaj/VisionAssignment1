//
// Created by mereckaj on 08/10/15.
//
#include "Preprocess.h"
#include "Utils.h"

cv::Mat* LoadImages(const char* imageFiles[], const char* IMAGE_LOCATION){

    int numberOfImages = (sizeof(imageFiles)/sizeof(*imageFiles));
    cv::Mat* images = new cv::Mat[numberOfImages];
    for(int i = 0; i < numberOfImages;i++){
        std::string filename(IMAGE_LOCATION);
        filename.append(imageFiles[i]);
        images[i] = cv::imread(filename, cv::IMREAD_ANYCOLOR);
        if (images[i].empty())
        {
            debug("Could not open: " + filename);
            exit(1);
        }
    }
    return images;
}
