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

#ifndef _HOLO_SENSORS_USS_USS_BASE_H
#define _HOLO_SENSORS_USS_USS_BASE_H

// #include <holo/sensors/uss/dds_uss_adc_01to9.h>
// #include <holo/sensors/uss/uss_apa01.h>
// #include <holo/sensors/uss/uss_slot_04to07.h>
//#include <holo/sensors/uss.h>
#include <holo/common/uss.h>
namespace holo
{
namespace sensors
{
namespace uss
{
   
/* aceinna imu driver template */
template <typename InType, typename OutType = InType>
class UssAdc01to09DriverT
{
public:
    UssAdc01to09DriverT();
};

template <typename InType, typename OutType = InType>
class UssApa01DriverT
{
public:
    UssApa01DriverT();
};


template <typename InType, typename OutType = InType>
class UssSlot04to07DriverT
{
public:
    UssSlot04to07DriverT();
};
}//namespace uss
}  // namespace sensors
}  // namespace holo

#endif//_HOLO_SENSORS_USS_USS_BASE_H
