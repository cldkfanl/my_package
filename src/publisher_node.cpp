#include <ros/ros.h>
#include <std_msgs/String.h>
#include <my_package/Message1.h>
#include <iostream>


int main(int argc, char** argv)
{
    ros::init(argc, argv, "Pub_node");
    ros::NodeHandle nh;
    
    std::string topic_name = "set_position";
    ros::Publisher pub = nh.advertise<my_package::Message1>(topic_name, 100);
    ros::Rate loop_rate(10);



    while (ros::ok())
    {
        my_package::Message1 msg;
         int key_input; // = std::getchar();
        std::cin >> key_input;

        if (key_input == 1){    // 모드1 : 배변 처리
            msg.id = 1;
            msg.position = 400;
            msg.speed = 50;
        } else if (key_input == 2){     //모드2 : 사료주기
            msg.id = 2;
            msg.position = 400;
            msg.speed = 50;
        } else if (key_input == 3){     // 모드3 : 사료닫기
            msg.id = 3;
            msg.position = 400;
            msg.speed = 50;
        }
        
        

         ROS_INFO("msg.id = %d",msg.id);
         ROS_INFO("msg.position= %d",msg.position);
         ROS_INFO("msg.speed = %d",msg.speed);

        pub.publish(msg);
        loop_rate.sleep();
    }

}
