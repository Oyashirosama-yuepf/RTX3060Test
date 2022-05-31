/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_utils.h
 * @brief define the mdc610 utils
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2020-10-15
 */

#ifndef HOLO_SENSORS_BASE_INCLUDE_INTERFACE_MDC610_MDC610_UTILS_H
#define HOLO_SENSORS_BASE_INCLUDE_INTERFACE_MDC610_MDC610_UTILS_H

#include <holo/log/hololog.h>
#include <holo/common/timestamp.h>
#include <holo/os/timer.h>
#if (MDC610_VERSION_NUM == 20210430)
#include <time.h>
#elif (MDC610_VERSION_NUM == 20210830)
#include <sys_ctr.h>
#else
#endif

namespace holo
{
namespace mdc610
{

holo::bool_t GetManagmentLevelTime(holo::common::Timestamp& ts);
holo::bool_t GetDataLevelTime(holo::common::Timestamp& ts);
holo::bool_t GetAllLevelTime(holo::common::Timestamp& mgt_ts, holo::common::Timestamp& data_ts);
holo::bool_t GetTimeDiff(holo::common::Duration& timediff);
void GetTimeDiffBlocked(holo::common::Duration& timediff);

}
}

#endif