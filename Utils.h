//
// Created by mereckaj on 08/10/15.
//

#ifndef VISIONASSIGNMENT1_UTILS_H
#define VISIONASSIGNMENT1_UTILS_H

#include <stdlib.h>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <opencv2/core/mat.hpp>

#define MENU_CHOICE_EXIT 0
#define MENU_CHOICE_KMEANS 1
#define MENU_CHOICE_HISTOGRAMS 2
#define MENU_CHOICE_EDGE_DETECTION 3

static std::string MENU_STRING_EXIT = "Exit";
static std::string MENU_STRING_KMEANS = "K Means Clustering";
static std::string MENU_STRING_HISTOGRAMS = "Histograms";
static std::string MENU_STRING_EDGE_DETECTION = "Edge Detection";

static const char * IMAGE_LOCATION = "/home/mereckaj/Dev/ClionProjects/VisionAssignment1/Images/";
static const char* imageFiles[] = {
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
void ParseCommandLineArgument(int,char**);
void debug(char**);
void debug(std::string);
int displayMeny();
#endif //VISIONASSIGNMENT1_UTILS_H
