#pragma once
#include <opencv2/opencv.hpp>
#include "cv_bridge/cv_bridge.h"
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <iostream>

class LineDetectorInterface
{
public:
    virtual void DetectLineFeature(cv::Mat img_in) = 0; 
    virtual void ShowDetectedImage(const char* window_title) = 0;

    
    
};