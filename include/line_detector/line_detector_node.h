#pragma once
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include "line_detector/line_detector_interface.h"
#include "line_detector/elsed_detector.h"
#include "line_detector/lsd_detector.h"

class LineDetectorNode
{
private:
    ros::NodeHandle nh;
    std::string in_topic;
    std::string out_topic;
    ros::Subscriber img_sub;
    ros::Publisher img_pub;
    cv_bridge::CvImagePtr cv_ptr;
    LineDetectorInterface* p_detector;
    std::string cv_window_name;

public:
    LineDetectorNode(LineDetectorInterface* detector_, 
                    std::string in_topic_ = "/img", 
                    std::string out_topic_ = "/detected_img",
                    std::string window_name_ = "detected lines");
    void img_cb(sensor_msgs::ImageConstPtr img_in);
};
