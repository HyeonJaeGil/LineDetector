#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include "line_detector/elsed_detector.h"
#include "line_detector/lsd_detector.h"

int main( int argc, char** argv )
{
    ros::init(argc, argv, "line_detector_node");
    ElsedDetector elsed_detector("/thermal_8bit/left/image_raw", "/thermal_8bit/left/elsed");
    LsdDetector lsd_detector("/thermal_8bit/left/image_raw", "/thermal_8bit/left/lsd");
    ros::spin();
    return 0;
}

