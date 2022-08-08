#include "line_detector/elsed_detector.h"

ElsedDetector::ElsedDetector()
{
    img_sub = nh.subscribe(in_topic, 1, &ElsedDetector::img_cb, this);
    img_pub = nh.advertise<sensor_msgs::Image>(out_topic, 10);
}

ElsedDetector::ElsedDetector(std::string in_topic, std::string out_topic)
{
    in_topic = in_topic;
    out_topic = out_topic;
}

void ElsedDetector::DetectLineFeature(cv::Mat img_in)
{
    orig_img = img_in.clone();
    segs = elsed.detect(img_in);
    std::cout << "ELSED detected: " << segs.size() << " (large) segments" << std::endl;

    // cv::imshow("ELSED long", img_in);
}

void ElsedDetector::ShowDetectedImage(char* window_title)
{
    detected_img = orig_img.clone();
    drawSegments(detected_img, segs, CV_RGB(0, 255, 0), 2);
    cv::imshow(window_title, detected_img);

}


void ElsedDetector::img_cb(sensor_msgs::ImageConstPtr img_in)
{
    cv_ptr = cv_bridge::toCvCopy(img_in, sensor_msgs::image_encodings::MONO8);
    assert(!cv_ptr->image.empty());
    DetectLineFeature(cv_ptr->image);
    ShowDetectedImage("window2");
    cv::waitKey(1);
}


// int main( int argc, char** argv )
// {
//     ros::init(argc, argv, "elsed_detector_node");
//     ElsedDetector elsed_detector;
//     ros::spin();
//     return 0;
// }