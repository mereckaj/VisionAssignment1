//
// Created by mereckaj on 07/10/15.
//
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc.hpp>

#define NUMBER_OF_IMAGES 30

/*
 * For metric assessments
 */
int number_of_true_positives = 0;
int number_of_true_negatives = 0;
int number_of_false_positives = 0;
int number_of_false_negatives = 0;

/*
 * Change the path
 */
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

/*
 * Function used for displaying images, of no relevance to the project
 */
void DisplayImage(std::string title,cv::Mat image,int x, int y,bool block){
    cv::imshow(title, image);
    cv::moveWindow(title,x,y);
    if(block)
        cv::waitKey(0);
}

/*
 * Function to load all of the imgaes. Returns an array of cv::Mat's with the imges inside them
 */
cv::Mat* LoadImages(char* imageFiles[], char* IMAGE_LOCATION,int numberOfImages){
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

/*
 * This function will discard the top half of the bottles image, then will crop the remainder
 * disregarding 20 pixels in each way. This in theory removes the background around the bottle.
 *
 * Returns the cropped image
 */
 cv::Mat CropImage(cv::Mat image){
    cv::Rect myROI(0,image.size().height/2,image.size().width,image.size().height/2);
    cv::Mat lowerHalf = cv::Mat(image,myROI);
    cv::Rect inner(20,20,lowerHalf.size().width-40,lowerHalf.size().height-40);
    cv::Mat end = cv::Mat(lowerHalf,inner);
    return end;
}

/*
 * Given a vector of cv;:Mats where each matrix is a single HLS channel, it will compute the
 * standard devitation on the saturation channel
 */
double GetSaturationSD(std::vector<cv::Mat> vector){
    cv::Mat sd,mean;
    cv::meanStdDev(vector[2],mean,sd,cv::Mat());
    return sd.at<double>(0,0);
}

/*
 * Given any image this function will split it into a vector of matrices for each channel
 */
std::vector<cv::Mat> SplitChannels(cv::Mat image){
    std::vector<cv::Mat> result(image.channels());
    cv::split(image,result);
    return result;
}

/*
 * Given an array of glue bottles with labels and an array of glue bottles without labels this method will
 * compute:
 *      the smalled standard deviation of the labeled bottles
 *      the biggest standard deviation of the unlabled bottles
 *      return the value in between these standard deviations
 *
 * Realistically the test sample should be big, at least 30 images of each kind, this would allow the
 * algorithm to pick a value that is best suited for the matching of labels
 *
 * For this project I pass in 8 labeled and 4 unlabeled images
 */
int TrainProgram(cv::Mat*labeledImages, int numberOfLabeledImages,cv::Mat* unlabledImages, int numberOfUnlabeledImages){
    int sdMinLabels = std::numeric_limits<int>::max();
    int sdMaxNoLabel = 0;
    int sdVal;
    int result;
    cv::Mat imgHls;
    std::vector<cv::Mat> imgChannels;
    for(int i = 0; i < numberOfLabeledImages; i++){
        labeledImages[i] = CropImage(labeledImages[i]);
        cv::cvtColor(labeledImages[i],imgHls,CV_RGB2HLS);
        imgChannels = SplitChannels(imgHls);
        sdVal = (int)GetSaturationSD(imgChannels);
        if(sdVal < sdMinLabels){
            sdMinLabels = sdVal;
        }
    }
    for(int i = 0; i < numberOfUnlabeledImages;i++){
        unlabledImages[i] = CropImage(unlabledImages[i]);
        cv::cvtColor(unlabledImages[i],imgHls,CV_RGB2HLS);
        imgChannels = SplitChannels(imgHls);
        sdVal = (int)GetSaturationSD(imgChannels);
        if(sdVal > sdMaxNoLabel){
            sdMaxNoLabel = sdVal;
        }
    }
    result = (sdMinLabels+sdMaxNoLabel)/2;
    std::cout << "Choosing cutoff value of: " << std::to_string(result) << std::endl;
    return result;
}

/*
 * Function which will determine if the bottle images contains a label
 *
 * it takes in an image of a full bottle (not cropped) and a SD cutoff value and returns
 * true if it thinks the bottle contains a label, false otherwise
 *
 * Algorithm:
 *      Crop the image, this discards a lot of useless information about the image (background mainly)
 *      Convert the image to HLS colour space
 *      Calculate the standard deviation on the saturation channel
 *          -- Noticed white creating the program that the saturation channel almost all of the time indicated
 *          if a label is present.
 *      Check if standard deviation is above the cut off value
 *      Return result based on previous
 */
bool ContainsLabel(cv::Mat image,int sdCutOffValue){
    std::vector<cv::Mat> imageChannels;
    cv::Mat imageHLS;
    image = CropImage(image);
    cv::cvtColor(image, imageHLS,CV_RGB2HLS);
    imageChannels = SplitChannels(imageHLS);
    double sd = GetSaturationSD(imageChannels);
    if(sd<sdCutOffValue){
        return true;
    }else{
        return false;
    }
}

/*
 * Self explanatory
 */
double CalculateRecall(){
    return ((double)number_of_true_positives/(double)(number_of_true_positives+number_of_false_negatives));
}
double CalculatePrecision(){
    return ((double)number_of_true_positives/(double)(number_of_true_positives+number_of_false_positives));
}
double CalculateAccuracy(){
    return ((double)(number_of_true_positives + number_of_true_negatives)/(double)NUMBER_OF_IMAGES);
}
double CalculateSpecificity(){
    return ((double)number_of_true_negatives/(double)(number_of_false_positives+number_of_true_negatives));
}
double CalculateFone(){
    return (1+(1*1)) * ((CalculatePrecision() * CalculateRecall()) / (((1*1)*CalculatePrecision())+CalculateRecall()));
}

/*
 * If it doesn't work: "It should be working" is all that I could say.
 */
int main(int argc,char** argv){
    int sdCutoffPoint;
    // Load Images, allocate test data sets
    cv::Mat* images = LoadImages(imageFiles,IMAGE_LOCATION,NUMBER_OF_IMAGES);
    cv::Mat*labeledImages = new cv::Mat[8];
    cv::Mat*unlabeledImages = new cv::Mat[4];

    // Fill test data sets with data
    labeledImages[0] = images[11];
    labeledImages[1] = images[25];
    labeledImages[2] = images[18];
    labeledImages[3] = images[24];
    labeledImages[4] = images[27];
    labeledImages[5] = images[2];
    labeledImages[6] = images[14];
    labeledImages[7] = images[7];
    unlabeledImages[0] =images[4];
    unlabeledImages[1] =images[29];
    unlabeledImages[2] =images[16];
    unlabeledImages[3] =images[17];

    //Call the training method, this will return a value under which the values bottles will be separates
    sdCutoffPoint =  TrainProgram(labeledImages,8,unlabeledImages,4);

    // Loop over every single image and check if it matched or not
    for(int i = 0; i < NUMBER_OF_IMAGES;i++){
        bool identification = ContainsLabel(images[i],sdCutoffPoint);

        /*
         * Print the info about the images classification
         * Uncomment for extra info
         */
//        if(identification){
//            std::cout << std::to_string(i) << " YES" << std::endl;
//        }else{
//            std::cout << std::to_string(i) << " NO" << std::endl;
//        }

        /*
         * Metrics
         */
        if(identification){
            if(i==4 ||i==6 ||i==13 ||i==16 ||i==17 ||i==20 ||i==23 ||i==29){
                number_of_true_positives++;
            }else{
                number_of_false_positives++;
            }
        }else{
            if(i==4 ||i==6 ||i==13 ||i==16 ||i==17 ||i==20 ||i==23 ||i==29){
                number_of_false_negatives++;
            }else{
                number_of_true_negatives++;
            }
        }
    }
    std::cout << std::endl;
    std::cout << "TP: " << std::to_string(number_of_true_positives) << std::endl;
    std::cout << "TN: " << std::to_string(number_of_true_negatives)<< std::endl;
    std::cout << "FP: " << std::to_string(number_of_false_positives)<< std::endl;
    std::cout << "FN: " << std::to_string(number_of_false_negatives)<< std::endl;
    std::cout << "Recal: " << std::to_string(CalculateRecall()) << std::endl;
    std::cout << "Precision: " << std::to_string(CalculatePrecision()) << std::endl;
    std::cout << "Accuracy: " << std::to_string(CalculateAccuracy()) << std::endl;
    std::cout << "Specificity: " << std::to_string(CalculateSpecificity()) << std::endl;
    std::cout << "Fone: " << std::to_string(CalculateFone()) << std::endl;
    return 0;
}