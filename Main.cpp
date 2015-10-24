//
// Created by mereckaj on 07/10/15.
//
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include "Histograms.cpp"

#define NUMBER_OF_IMAGES 30

cv::Mat * LoadImages(const char* imageFiles[], const char* IMAGE_LOCATION);
void DisplayImage(std::string title,cv::Mat image);

char * IMAGE_LOCATION = "/home/mereckaj/Dev/ClionProjects/VisionAssignment1/Images/";
char* imageFiles[] = {
        "glue-0.png",
        "glue-1.png",
        "glue-2.png",
        "glue-3.png",
        "glue-4.png",
        "glue-5.png",
        "glue-6.png",
        "glue-7.png",
        "glue-8.png",
        "glue-9.png",
        "glue-10.png",
        "glue-11.png",
        "glue-12.png",
        "glue-13.png",
        "glue-14.png",
        "glue-15.png",
        "glue-16.png",
        "glue-17.png",
        "glue-18.png",
        "glue-19.png",
        "glue-20.png",
        "glue-21.png",
        "glue-22.png",
        "glue-23.png",
        "glue-24.png",
        "glue-25.png",
        "glue-26.png",
        "glue-27.png",
        "glue-28.png",
        "glue-29.png"
};

cv::Mat * LoadImages(char* imageFiles[], char* IMAGE_LOCATION,int numberOfImages){
    cv::Mat *images = new cv::Mat[numberOfImages];
    for(int i = 0; i < numberOfImages;i++){
        std::string filename(IMAGE_LOCATION);
        filename.append(imageFiles[i]);
        images[i] = cv::imread(filename, cv::IMREAD_ANYCOLOR);
        if (images[i].empty())
        {
            exit(1);
        }
    }
    return images;
}

void DisplayImage(std::string title,cv::Mat image){
    imshow(title,image);
    cvWaitKey(0);
    cv::destroyWindow(title);
}
/* Crop the image so that the lower half is only shown.
    This will simulate taking a picture of the lower half of the glue bottle (Ignoring the cap)
 */
cv::Mat cropImage(cv::Mat image){
    cv::Rect myROI(0,image.size().height/2,image.size().width,image.size().height/2);
    cv::Mat t(image,myROI);
    return t;
}

int main(int argc,char** argv){
}