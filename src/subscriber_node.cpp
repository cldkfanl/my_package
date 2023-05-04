#include <ros/ros.h>
#include <my_package/Message1.h>
#include <dynamixel_sdk/dynamixel_sdk.h>
#include <unistd.h>

using namespace dynamixel;

// Protocol version
#define PROTOCOL_VERSION            1.0

#define BAUDRATE                    115200
#define DEVICE_NAME                  "/dev/ttyUSB0" // Check which port is being used on your controller

// Control table address 
#define ADDR_TORQUE_ENABLE      24
#define ADDR_GOAL_POSITION      30
#define ADDR_MOVING_SPEED       32

// Data Byte Length
#define LEN_TORQUE_ENABLE       1
#define LEN_GOAL_POSITION       2
#define LEN_MOVING_SPEED        2

// Default setting
#define DXL_ID_1                      1         // front
#define DXL_ID_2                      2         // back_up  
#define DXL_ID_3                      3         // back_down

PortHandler * portHandler;
PacketHandler * packetHandler;

// dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICE_NAME);
// dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);


// void messageCallback(const my_package::Message1::ConstPtr& msg)
// {
//     uint16_t goal_position = msg->position;
//     uint8_t dxl_error = 0; 
//     int dxl_comm_result = 0;

//     dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_1, ADDR_GOAL_POSITION, goal_position, &dxl_error);

//     //모터 제어 코드
//     ROS_INFO("Received message:");
//     ROS_INFO("id = %d", msg->id);
//     ROS_INFO("position = %d", msg->position);
//     ROS_INFO("speed = %d", msg->speed);
// }

void mode1Callback(const my_package::Message1::ConstPtr& msg)
{
    uint8_t dxl_error = 0; 
    int dxl_comm_result = 0;

    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_1, ADDR_GOAL_POSITION, 3277200, &dxl_error);
    sleep(3); // wait for 10 seconds
    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_1, ADDR_GOAL_POSITION, 3277000, &dxl_error);
    sleep(3);
    dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_ID_1, ADDR_GOAL_POSITION, 3277350, &dxl_error);



    //모터 제어 코드
    ROS_INFO("Received message:");
    ROS_INFO("id = %d", msg->id);
    ROS_INFO("position = %d", msg->position);
    ROS_INFO("speed = %d", msg->speed);
}

void mode2Callback(const my_package::Message1::ConstPtr& msg)
{
    uint8_t dxl_error = 0; 
    int dxl_comm_result = 0;

   dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, 2, ADDR_GOAL_POSITION, 6554100, &dxl_error);    //655855
  sleep(3); // wait for 5 seconds
   dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, 3, ADDR_GOAL_POSITION, 6553650, &dxl_error);    //655855
  sleep(3);
   dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, 3, ADDR_GOAL_POSITION, 6553800, &dxl_error);    //655855

    //모터 제어 코드
    ROS_INFO("Received message:");
    ROS_INFO("id = %d", msg->id);
    ROS_INFO("position = %d", msg->position);
    ROS_INFO("speed = %d", msg->speed);
}

void mode3Callback(const my_package::Message1::ConstPtr& msg)
{
    uint8_t dxl_error = 0; 
    int dxl_comm_result = 0;

    dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, DXL_ID_3, ADDR_GOAL_POSITION, 3276990, &dxl_error);

    //모터 제어 코드
    ROS_INFO("Received message:");
    ROS_INFO("id = %d", msg->id);
    ROS_INFO("position = %d", msg->position);
    ROS_INFO("speed = %d", msg->speed);
}





int main(int argc, char** argv)
{
    uint8_t dxl_error = 0;
    int dxl_comm_result = COMM_TX_FAIL;


    portHandler = PortHandler::getPortHandler(DEVICE_NAME);
    packetHandler = PacketHandler::getPacketHandler(PROTOCOL_VERSION);

    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID_1, ADDR_TORQUE_ENABLE, 1, &dxl_error);

    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID_2, ADDR_TORQUE_ENABLE, 1, &dxl_error);

    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID_3, ADDR_TORQUE_ENABLE, 1, &dxl_error);

    // Initialize ROS node
    ros::init(argc, argv, "Sub_node");
    ros::NodeHandle nh;

    // Set up subscriber
    std::string topic_name = "set_position";
    // ros::Subscriber sub = nh.subscribe(topic_name, 100, callback);
    ros::Subscriber sub = nh.subscribe("/set_position", 10, mode1Callback);

   
    

    ros::spin();

    return 0;
}   