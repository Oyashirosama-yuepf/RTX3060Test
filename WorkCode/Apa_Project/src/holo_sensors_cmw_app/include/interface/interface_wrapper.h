/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file interface_wrapper.h
 * @brief A wrapper of communication interface
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021/09/26
 */

#ifndef HOLO_CMW_APPS_INTERFACE_WRAPPER_H
#define HOLO_CMW_APPS_INTERFACE_WRAPPER_H

#include <holo/sensors/interface/tcpcli_interface.h>
#include <holo/sensors/interface/udp_interface.h>
// #include <holo/sensors/interface/umb_interface.h>
#if !defined(DISABLE_V4L2_INTERFACE)
#include <holo/sensors/interface/v4l2_interface.h>
#endif
#if defined(ENABLE_MDC300_CAN_INTERFACE)
#include <holo/sensors/interface/mdc300_can_interface.h>
#endif
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
#include <holo/sensors/interface/mdc610_camera_interface.h>
#endif
#if defined(ENABLE_MDC610_LIDAR_INTERFACE)
#include <holo/sensors/interface/mdc610_lidar_interface.h>
#endif

namespace holo_cmw
{
/* socket */
using SocketAddr = holo::sensors::interface::SocketAddr;

/* udp server */
using UdpInterfaceParam = holo::sensors::interface::UdpInterfaceParam;
template <typename T>
using UdpInterface = holo::sensors::interface::UdpInterface<T>;

/* tcpcli */
using TcpcliInterfaceParam = holo::sensors::interface::TcpcliInterfaceParam;
template <typename T>
using TcpcliInterface      = holo::sensors::interface::TcpcliInterface<T>;
using RecvDataCallbackType = holo::sensors::interface::tcpcli::RecvDataCallbackType;

#if !defined(DISABLE_V4L2_INTERFACE)
/* v4l2 */
using V4l2InterfaceParam = holo::sensors::interface::V4l2InterfaceParam;
template <typename T>
using V4l2Interface     = holo::sensors::interface::V4l2Interface<T>;
using CameraV4l2General = holo::sensors::interface::CameraV4l2General;
using CameraM021        = holo::sensors::interface::CameraM021;
using CameraAR0231      = holo::sensors::interface::CameraAR0231;
using CameraOV490       = holo::sensors::interface::CameraOV490;
using CameraAP020       = holo::sensors::interface::CameraAP020;
#endif

// /* umb */
// using UmbInterfaceParam = holo::sensors::interface::UmbInterfaceParam;
// template <typename T>
// using UmbInterface = holo::sensors::interface::UmbInterface<T>;

/* mdc300 can */
#if defined(ENABLE_MDC300_CAN_INTERFACE)
using MdcCanInterfaceParam = holo::sensors::interface::MdcCanInterfaceParam;
template <typename T>
using MdcCanInterface = holo::sensors::interface::MdcCanInterface<T>;
#endif

/* mdc610 camera */
#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
using Mdc610CameraInterfaceParam = holo::sensors::interface::Mdc610CameraInterfaceParam;
template <typename T>
using Mdc610CameraInterface = holo::sensors::interface::Mdc610CameraInterface<T>;
using decodedProxy = holo::sensors::interface::decodedProxy;
using encodedProxy = holo::sensors::interface::encodedProxy;
#endif

/* mdc610 lidar */
#if defined(ENABLE_MDC610_LIDAR_INTERFACE)
using Mdc610LidarInterfaceParam = holo::sensors::interface::Mdc610LidarInterfaceParam;
using Mdc610LidarInterface      = holo::sensors::interface::Mdc610LidarInterface;
#endif

}  // namespace holo_cmw

#endif
