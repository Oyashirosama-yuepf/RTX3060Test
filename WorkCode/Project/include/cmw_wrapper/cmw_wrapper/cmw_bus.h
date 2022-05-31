#ifndef CMW_WRAPPER_CMW_BUS_H_
#define CMW_WRAPPER_CMW_BUS_H_

#ifdef CMW_WRAPPER_ENABLE_ROS
#include <ros_wrapper/ros_bus.h>
#endif

#ifdef CMW_WRAPPER_ENABLE_OPENDDS
#include <opendds_wrapper/opendds_bus.h>
#endif

#ifdef CMW_WRAPPER_ENABLE_UMB
#include <umb_wrapper/umb_bus.h>
#endif

#ifdef CMW_WRAPPER_ENABLE_DDS_MICRO
#include <dds_micro_wrapper/dds_micro_bus.h>
#endif

#ifdef CMW_WRAPPER_ENABLE_MDC_CM
#include <mdc_cm_wrapper/mdc_cm_bus.h>
#endif

#ifdef CMW_WRAPPER_ENABLE_PPS
#include <pps_wrapper/pps_bus.h>
#endif

namespace cmw_wrapper
{
#if defined(CMW_WRAPPER_ENABLE_ROS) && !defined(CMW_WRAPPER_ENABLE_OPENDDS) && !defined(CMW_WRAPPER_ENABLE_UMB) &&     \
    !defined(CMW_WRAPPER_ENABLE_DDS_MICRO) && !defined(CMW_WRAPPER_ENABLE_MDC_CM) && !defined(CMW_WRAPPER_ENABLE_PPS)
using CmwBus  = ros_wrapper::BusType;
using BusType = CmwBus;
#endif

#if !defined(CMW_WRAPPER_ENABLE_ROS) && defined(CMW_WRAPPER_ENABLE_OPENDDS) && !defined(CMW_WRAPPER_ENABLE_UMB) &&     \
    !defined(CMW_WRAPPER_ENABLE_DDS_MICRO) && !defined(CMW_WRAPPER_ENABLE_MDC_CM) && !defined(CMW_WRAPPER_ENABLE_PPS)
using CmwBus  = opendds_wrapper::BusType;
using BusType = CmwBus;
#endif

#if !defined(CMW_WRAPPER_ENABLE_ROS) && !defined(CMW_WRAPPER_ENABLE_OPENDDS) && defined(CMW_WRAPPER_ENABLE_UMB) &&     \
    !defined(CMW_WRAPPER_ENABLE_DDS_MICRO) && !defined(CMW_WRAPPER_ENABLE_MDC_CM) && !defined(CMW_WRAPPER_ENABLE_PPS)
using CmwBus  = umb_wrapper::BusType;
using BusType = CmwBus;
#endif

#if !defined(CMW_WRAPPER_ENABLE_ROS) && !defined(CMW_WRAPPER_ENABLE_OPENDDS) && !defined(CMW_WRAPPER_ENABLE_UMB) &&    \
    defined(CMW_WRAPPER_ENABLE_DDS_MICRO) && !defined(CMW_WRAPPER_ENABLE_MDC_CM) && !defined(CMW_WRAPPER_ENABLE_PPS)
using CmwBus  = dds_micro_wrapper::BusType;
using BusType = CmwBus;
#endif

#if !defined(CMW_WRAPPER_ENABLE_ROS) && !defined(CMW_WRAPPER_ENABLE_OPENDDS) && !defined(CMW_WRAPPER_ENABLE_UMB) &&    \
    !defined(CMW_WRAPPER_ENABLE_DDS_MICRO) && defined(CMW_WRAPPER_ENABLE_MDC_CM) && !defined(CMW_WRAPPER_ENABLE_PPS)
using CmwBus  = mdc_cm_wrapper::BusType;
using BusType = CmwBus;
#endif

#if !defined(CMW_WRAPPER_ENABLE_ROS) && !defined(CMW_WRAPPER_ENABLE_OPENDDS) && !defined(CMW_WRAPPER_ENABLE_UMB) &&    \
    !defined(CMW_WRAPPER_ENABLE_DDS_MICRO) && !defined(CMW_WRAPPER_ENABLE_MDC_CM) && defined(CMW_WRAPPER_ENABLE_PPS)
using CmwBus  = pps_wrapper::BusType;
using BusType = CmwBus;
#endif

}  // namespace cmw_wrapper

#endif
