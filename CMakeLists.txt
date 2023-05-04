cmake_minimum_required(VERSION 3.0.2)
project(my_package)

find_package(catkin REQUIRED COMPONENTS
  dynamixel_sdk
  roscpp
  std_msgs
  message_generation
)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  Message1.msg
  Message2.msg
  Message3.msg
)

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES my_package dynamixel_sdk
  CATKIN_DEPENDS dynamixel_sdk roscpp std_msgs message_runtime
  DEPENDS system_lib
)


include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)


 add_executable(publisher_node src/publisher_node.cpp)
 add_dependencies(publisher_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
 target_link_libraries(publisher_node ${catkin_LIBRARIES})


 add_executable(subscriber_node src/subscriber_node.cpp)
 add_dependencies(subscriber_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
 target_link_libraries(subscriber_node ${catkin_LIBRARIES})

#  add_executable(${PROJECT_NAME}_node src/client_node.cpp)
#  add_executable(${PROJECT_NAME}_node src/server_node.cpp)

