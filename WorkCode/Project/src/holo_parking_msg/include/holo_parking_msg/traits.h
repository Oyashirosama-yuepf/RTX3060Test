#ifndef HOLO_PARKING_MSG_TRAITS_H_
#define HOLO_PARKING_MSG_TRAITS_H_

#ifdef CMW_WRAPPER_ENABLE_ROS
#include <holo_parking_msg/ros_msg/traits.h>
#endif

#ifdef CMW_WRAPPER_ENABLE_OPENDDS
#include <holo_parking_msg/opendds_msg/traits.h>
#endif

#ifdef CMW_WRAPPER_ENABLE_DDS_MICRO
#include <holo_parking_msg/dds_micro_msg/traits.h>
#endif

#endif
