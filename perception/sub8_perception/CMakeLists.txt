cmake_minimum_required(VERSION 2.8.3)
project(sub8_perception)

# If you need to deviate from these defaults, override the flags for your specific target
#  using target_compile_options()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -g -rdynamic -Wall -std=c++11 ")

find_package(catkin
  REQUIRED COMPONENTS
    roscpp
    rospy
    eigen_conversions
    rostime
    image_transport
    image_geometry
    cv_bridge
    sub8_msgs
    message_generation
    std_msgs
    geometry_msgs
    mil_vision
)

catkin_python_setup()

# find_package(PCL 1.7 REQUIRED)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    sub8_vision_lib
  CATKIN_DEPENDS
    roscpp
    rospy
    message_runtime
    image_transport
    image_geometry
    cv_bridge
    sub8_msgs
    std_msgs
    geometry_msgs
    mil_vision
)

include_directories(
    include
  SYSTEM
    # ${PCL_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIR}
    ${catkin_INCLUDE_DIRS}
)

# link_directories(${PCL_LIBRARY_DIRS})
# add_definitions(${PCL_DEFINITIONS})

add_library(sub8_vision_lib
    # src/sub8_vision_lib/align.cc
    src/sub8_vision_lib/cv_utils.cc
    # src/sub8_vision_lib/cv_param_helpers.cc
    src/sub8_vision_lib/visualization.cc
    # src/sub8_vision_lib/object_finder.cc
)

target_link_libraries(
  sub8_vision_lib
    ${catkin_LIBRARIES}
    # ${PCL_COMMON_LIBRARIES}
    # ${PCL_IO_LIBRARIES}
    # ${PCL_LIBRARIES}
    ${Boost_LIBRARIES}
)

add_executable(torpedos_cpp
  nodes/torpedo_board.cc
)
add_dependencies(torpedos_cpp
  sub8_msgs_generate_messages_cpp
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(torpedos_cpp
  sub8_vision_lib
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(sample_mission
  nodes/sample_mission.cpp
)
add_dependencies(sample_mission
  sub8_msgs_generate_messages_cpp
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(sample_mission
  sub8_vision_lib
  mil_vision_lib
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
  ${OpenCV_INCLUDE_DIRS}
)

