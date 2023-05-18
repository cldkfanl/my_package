#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <std_msgs/String.h>
#include <sstream>

void pointCloudCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
    float pos_x = msg->pose.pose.position.x;
    float pos_y = msg->pose.pose.position.y;
    float pos_z = msg->pose.pose.position.z;


    std::stringstream ss;
    ss << "Position: (" <<pos_x<<","<<pos_y<<","<<pos_z<<")";

    std_msgs::String string_msg;
    string_msg.data = ss.str();
  // 필요한 코드 작성

    ros::init(argc, argv, "initialpose_publisher")
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<std_msgs::String>("initial_pub", 10);
    pub.publish(string_msg);
}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "initialpose_subscriber");
    ros::NodeHandle nh;
    
    ros::Subscriber sub = nh.subscribe("/initialpose",10,initialCallBack);

    ros::spin();

    return 0;

}

