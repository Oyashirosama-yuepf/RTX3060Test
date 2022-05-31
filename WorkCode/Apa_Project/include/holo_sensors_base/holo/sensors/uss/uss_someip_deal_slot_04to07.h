/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file aceinna.h
 * @brief This header file define the function of aceinna driver
 * @author guoguangchao@holomatic.com
 * @date 2020-08-21
 */

#ifndef _HOLO_SENSORS_USS_USS_SLOT_04TO07_H
#define _HOLO_SENSORS_USS_USS_SLOT_04TO07_H
//#include <holo/log/hololog.h>
#include <holo/sensors/uss/uss_base.h>
#include <holo/common/uss.h>
#include <holo/core/types.h>
#include <holo/sensors/common/device.h>
#include <holo/sensors/format/someip.h>
#include <functional>
//#include <holo_c/common/uss/uss_someip_apa_park_slot_04to07.h>
#include"holo_c/common/uss/uss_info.h"

namespace holo
{
namespace sensors
{
namespace uss
{
using SomeipPacketType = holo::sensors::format::SomeipPacket<512>;
using holo::common::Timestamp;
using holo::common::DDSUSSApaParkSlot04To07;
/* aceinna imu driver based on someip packet */
//const unsigned int ARRAY_SIZE = 7;
template <>
class UssSlot04to07DriverT<SomeipPacketType, SomeipPacketType>
{
public:
    using InType                = SomeipPacketType;
    using CallbackType =  std::function<void(const DDSUSSApaParkSlot04To07&)>;
    UssSlot04to07DriverT();
    ~UssSlot04to07DriverT();
    void ParseData(const SomeipPacketType& data);
    void InstallCallback(const CallbackType& callback);
    CallbackType uss_callback_;
};
}// namespace uss
}  // namespace sensors
}  // namespace holo

#endif//_HOLO_SENSORS_USS_USS_SLOT_04TO07_H
