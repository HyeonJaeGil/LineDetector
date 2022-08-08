#pragma once
#include <ros/ros.h>
#include "line_detector/line_detector_interface.h"

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
    LineDetectorNode(LineDetectorInterface& detector, 
                    std::string in_topic = "/img", 
                    std::string out_topic = "/detected_img",
                    std::string window_name = "detected lines");
    LineDetectorNode()=delete;
    void img_cb(sensor_msgs::ImageConstPtr img_in);
};
