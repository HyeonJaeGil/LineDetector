#include "line_detector/line_detector_node.h"

LineDetectorNode::LineDetectorNode(LineDetectorInterface* detector_, 
                                    std::string in_topic_, 
                                    std::string out_topic_, 
                                    std::string window_name_)
{
    p_detector = detector_;
    in_topic = in_topic_;
    out_topic = out_topic_;
    img_sub = nh.subscribe(in_topic, 1, &LineDetectorNode::img_cb, this);
    img_pub = nh.advertise<sensor_msgs::Image>(out_topic, 10);
    cv_window_name = window_name_;
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
    LineDetectorNode line_detector_node(&lsd_detector);
    ros::spin();
    return 0;
}
