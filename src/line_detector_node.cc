#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include "line_detector/elsed_detector.h"
#include "line_detector/lsd_detector.h"
#include "line_detector/line_detector_node.h"

LineDetectorNode::LineDetectorNode(LineDetectorInterface& detector, 
                                    std::string in_topic, std::string out_topic, std::string window_name)
{
    p_detector = &detector;
    in_topic = in_topic;
    out_topic = out_topic;
    img_sub = nh.subscribe(in_topic, 1, &LineDetectorNode::img_cb, this);
    img_pub = nh.advertise<sensor_msgs::Image>(out_topic, 10);
    cv_window_name = window_name;
}


void LineDetectorNode::img_cb(sensor_msgs::ImageConstPtr img_in)
{
    cv_ptr = cv_bridge::toCvCopy(img_in, sensor_msgs::image_encodings::MONO8);
    assert(!cv_ptr->image.empty());
    p_detector->DetectLineFeature(cv_ptr->image);
    p_detector->ShowDetectedImage(cv_window_name.c_str());
    cv::waitKey(1);
}


int main( int argc, char** argv )
{
    ros::init(argc, argv, "line_detector_node");
    ElsedDetector elsed_detector;
    LsdDetector lsd_detector;
    LineDetectorNode(elsed_detector, "/img", "/detected_img", "elsed lines");
    ros::spin();
    return 0;
}
