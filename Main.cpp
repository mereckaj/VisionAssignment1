//
// Created by mereckaj on 07/10/15.
//
#include <opencv2/highgui.hpp>
#include <iostream>

//
// Created by mereckaj on 09/10/15.
//
cv::Mat ConvertToSamples(cv::Mat image);
cv::Mat Cluster(cv::Mat image,cv::Mat samples,int k,int iterations);
cv::Mat * LoadImages(const char* imageFiles[], const char* IMAGE_LOCATION);
void ParseCommandLineArgument(int argument_count, char** argument_array);
void debug(std::string message);
void DisplayImage(std::string title,cv::Mat image);

#define CHANNEL_COUNT 3
#define FLAG_DEBUG "--debug"

static int DEBUG_MODE;
const char * IMAGE_LOCATION = "/home/mereckaj/Dev/ClionProjects/VisionAssignment1/Images/";
const char* imageFiles[] = {
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
cv::Mat * LoadImages(const char* imageFiles[], const char* IMAGE_LOCATION){

    int numberOfImages = (sizeof(imageFiles)/sizeof(imageFiles[0]));
    debug("NumberOfImages: " + std::to_string(numberOfImages));
    cv::Mat *images = new cv::Mat[numberOfImages];
    for(int i = 0; i < numberOfImages;i++){
        std::string filename(IMAGE_LOCATION);
        filename.append(imageFiles[i]);
        images[i] = cv::imread(filename, cv::IMREAD_ANYCOLOR);
        if (images[i].empty())
        {
            debug("Could not open: " + filename);
            exit(1);
        }else{
            DisplayImage(std::to_string(i),images[i]);
        }

    }
    return images;
}

void ParseCommandLineArgument(int argument_count, char** argument_array){
    DEBUG_MODE = 0;
    for(int i = 1; i < argument_count;i++) {
        if(strcmp(FLAG_DEBUG,argument_array[i])==0){
            DEBUG_MODE = 1;
            debug("Debug Enabled");
        }
    }
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
int main(int argc,char** argv){
    cv::Mat *images;
    int menuChoice;
    int numOfPics = sizeof(imageFiles)/sizeof(imageFiles[0]);

    ParseCommandLineArgument(argc, argv);
    images = LoadImages(imageFiles,IMAGE_LOCATION);
    debug("Loaded all images");
    cv::Mat* results = new cv::Mat[numOfPics];
    debug("Created result matrix");

    exit(0);
    for(int i = 0 ; i < numOfPics;i++){
        cv::Mat samples;
        debug("Processing image:"+std::to_string(i));
        samples = ConvertToSamples(images[i]);
        debug("Created samples:" + std::to_string(i));
        results[i] = Cluster(images[i],samples,2,1);
        debug("Processed image:" + std::to_string(i));
        DisplayImage(std::to_string(i),results[i]);
    }
}