//
// Created by mereckaj on 09/10/15.
//

#include "KMeansClustering.h"

cv::Mat ConvertToSamples(cv::Mat image){
    debug("\tConvertToSamples");
    cv::Mat samples(image.rows*image.cols,3,CV_32F);
    debug("Created samples matrix");
    float* sample = samples.ptr<float>(0);
    debug("Created pointer");
    for(int row = 0; row < image.rows;row++){
        for(int col=0; col < image.cols; col++){
            for(int channel =0 ; channel < CHANNEL_COUNT;channel++){
                samples.at<float>(row*image.cols+col,channel) = (uchar) image.at<cv::Vec3b>(row,col)[channel];
            }
        }
    }
    debug("Processed all the samples");
    return samples;
}
cv::Mat Cluster(cv::Mat image,cv::Mat samples,int k,int iterations){
    debug("\tCluster");
    cv::Mat resultImage;
    cv::Mat labels, centres;
    debug("Created temp matrices");
    cv::kmeans(samples,k,labels,cv::TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,0.0001,10000),iterations,cv::KMEANS_PP_CENTERS,centres);
    debug("\tkmeans success");
    resultImage = cv::Mat(image.size(),image.type());
    debug("Created result matrix");
    for(int row = 0; row < image.rows;row++){
        for(int col=0; col < image.cols; col++){
            for(int channel =0 ; channel < CHANNEL_COUNT;channel++){
                resultImage.at<cv::Vec3b>(row,col)[channel] = (uchar) centres.at<float>(*(labels.ptr<int>(row*image.cols +col)),channel);
            }
        }
    }
    debug("Filled result matrix");
    return resultImage;
}