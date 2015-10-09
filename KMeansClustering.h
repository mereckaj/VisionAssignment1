//
// Created by mereckaj on 09/10/15.
//

#ifndef VISIONASSIGNMENT1_KMEANSCLUSTERING_H
#define VISIONASSIGNMENT1_KMEANSCLUSTERING_H
#include "Utils.h"
#define CHANNEL_COUNT 3

cv::Mat ConvertToSamples(cv::Mat);
cv::Mat Cluster(cv::Mat,cv::Mat,int,int);
#endif //VISIONASSIGNMENT1_KMEANSCLUSTERING_H
