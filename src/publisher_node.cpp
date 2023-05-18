#include <ros/ros.h>
#include <std_msgs/String.h>
#include <my_package/Message1.h>
#include <iostream>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/CompressedImage.h>
#include <time.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    
    // std::string topic_name = "map_Image";
    // image_transport::ImageTransport it(nh);
    // image_transport::Publisher pub = it.advertise("image", 1);

    ros::Publisher pub = nh.advertise<sensor_msgs::CompressedImage>("pgm_image", 1);
    cv::Mat image;
    image = cv::imread("/home/choi/map.pgm", cv::IMREAD_GRAYSCALE);
    std::vector<uchar> buffer;
    cv::imencode(".jpg", image, buffer);
    sensor_msgs::CompressedImagePtr compressed_image_msg(new sensor_msgs::CompressedImage);
    compressed_image_msg->header.stamp = ros::Time::now();
    compressed_image_msg->format = "jpeg";
    compressed_image_msg->data = buffer;
    while(ros::ok()){
        pub.publish(compressed_image_msg);
        ros::Duration(1.0).sleep();
    }

    return 0;

}

