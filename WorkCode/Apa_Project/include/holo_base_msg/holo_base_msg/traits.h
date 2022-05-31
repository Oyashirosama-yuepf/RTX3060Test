#ifndef HOLO_BASE_MSG_TRAITS_H_
#define HOLO_BASE_MSG_TRAITS_H_

#ifdef CMW_WRAPPER_ENABLE_ROS
#include <holo_base_msg/ros_msg/traits.h>
#endif

#ifdef CMW_WRAPPER_ENABLE_OPENDDS
#include <holo_base_msg/opendds_msg/traits.h>
#endif

#ifdef CMW_WRAPPER_ENABLE_UMB
#include <holo_base_msg/umb_msg/traits.h>
#endif

#endif
