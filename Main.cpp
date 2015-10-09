//
// Created by mereckaj on 07/10/15.
//
#include <opencv2/highgui.hpp>
#include "Utils.h"
#include "Preprocess.h"
#include "KMeansClustering.h"

int main(int argc,char** argv){
    cv::Mat* images;
    cv::Mat samples;
    cv::Mat result;
    int menuChoice;
    int numOfPics = sizeof(imageFiles)/sizeof(imageFiles[0]);

    ParseCommandLineArgument(argc, argv);
    images = LoadImages(imageFiles,IMAGE_LOCATION);
    debug("Loaded all images");
    cv::Mat* results = new cv::Mat[numOfPics];
    debug("Created result matrix");

    for(int i = 0 ; i < numOfPics;i++){
        samples.deallocate();
        debug("Processing image:"+std::to_string(i));
        samples = ConvertToSamples(images[i]);
        debug("Created samples:" + std::to_string(i));
        results[i] = Cluster(images[i],samples,2,1);
        debug("Processed image:" + std::to_string(i));
//        DisplayImage(std::to_string(i),results[i]);
    }
}