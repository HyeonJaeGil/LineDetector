#pragma once
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include "cv_bridge/cv_bridge.h"
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <iostream>

class LineDetectorInterface
{
public:
    virtual void DetectLineFeature(cv::Mat img_in) = 0; 
    virtual void ShowDetectedImage(char* window_title) = 0;
    virtual void img_cb(sensor_msgs::ImageConstPtr img_in) = 0;

protected:
    ros::NodeHandle nh;
    std::string in_topic;
    std::string out_topic;
    ros::Subscriber img_sub;
    ros::Publisher img_pub;
    cv_bridge::CvImagePtr cv_ptr;
private:
    
    
};