#include "line_detector/lsd_detector.h"

LsdDetector::LsdDetector(std::string in_topic, std::string out_topic){
    img_sub = nh.subscribe(in_topic, 1, &LsdDetector::img_cb, this);
    img_pub = nh.advertise<sensor_msgs::Image>(out_topic, 10);
    in_topic = in_topic;
    out_topic = out_topic;
    bd = cv::line_descriptor::LSDDetector::createLSDDetector();
    lines.clear();
}


void LsdDetector::DetectLineFeature(cv::Mat img_in){
    orig_img = img_in;
    // img_in.copyTo(orig_img);
    mask = cv::Mat::ones( orig_img.size(), CV_8UC1 );
    lines.clear();
    bd->detect( orig_img, lines, 2, 1, mask );

}

void LsdDetector::ShowDetectedImage(char* window_title)
{
    orig_img.copyTo(detected_img);
    /* draw lines extracted from octave 0 */
    if( detected_img.channels() == 1 )
        cvtColor( detected_img, detected_img, cv::COLOR_GRAY2BGR );
    for ( size_t i = 0; i < lines.size(); i++ )
    {
        cv::line_descriptor::KeyLine kl = lines[i];
        if( kl.octave == 0)
        {
        /* get a random color */
        int R = ( rand() % (int) ( 255 + 1 ) );
        int G = ( rand() % (int) ( 255 + 1 ) );
        int B = ( rand() % (int) ( 255 + 1 ) );
    
        /* get extremes of line */
        cv::Point pt1 = cv::Point2f( kl.startPointX, kl.startPointY );
        cv::Point pt2 = cv::Point2f( kl.endPointX, kl.endPointY );
    
        /* draw line */
        line( detected_img, pt1, pt2, cv::Scalar( B, G, R ), 3 );
        }
    }
        cv::imshow(window_title, detected_img);
}


void LsdDetector::img_cb(sensor_msgs::ImageConstPtr img_in)
{
    cv_ptr = cv_bridge::toCvCopy(img_in, sensor_msgs::image_encodings::MONO8);
    assert(!cv_ptr->image.empty());
    DetectLineFeature(cv_ptr->image);
    ShowDetectedImage("window");
    cv::waitKey(1);
}


// int main( int argc, char** argv )
// {
//     ros::init(argc, argv, "lsd_detector_node");
//     LsdDetector lsd_detector;
//     ros::spin();
//     return 0;
// }
