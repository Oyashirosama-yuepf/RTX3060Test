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

#include <iomanip>
#include <holo/sensors/utils/mdc610_utils.h>

namespace holo
{
namespace mdc610
{
#define CLOCK_ID_DATA       0
#define CLOCK_ID_MANAGMENT  100
#define CLOCK_ID_ALL        101

holo::bool_t GetManagmentLevelTime(holo::common::Timestamp& ts)
{
    struct timespec raw_ts;
    if (0 == clock_gettime(CLOCK_ID_MANAGMENT, &raw_ts))
    {
        ts.SetSec(raw_ts.tv_sec);
        ts.SetNsec(raw_ts.tv_nsec);
        return true;
    }

    ts.SetSec(0);
    ts.SetNsec(0);
    return false;
}

holo::bool_t GetDataLevelTime(holo::common::Timestamp& ts)
{
    struct timespec raw_ts;
    if (0 == clock_gettime(CLOCK_ID_DATA, &raw_ts))
    {
        ts.SetSec(raw_ts.tv_sec);
        ts.SetNsec(raw_ts.tv_nsec);
        return true;
    }
    ts.SetSec(0);
    ts.SetNsec(0);
    return false;
}

holo::bool_t GetAllLevelTime(holo::common::Timestamp& mgt_ts, holo::common::Timestamp& data_ts)
{
    struct timespec raw_ts[2];
    if (0 == clock_gettime(CLOCK_ID_ALL, raw_ts))
    {
        data_ts.SetSec(raw_ts[0].tv_sec);
        data_ts.SetNsec(raw_ts[0].tv_nsec);
        mgt_ts.SetSec(raw_ts[1].tv_sec);
        mgt_ts.SetNsec(raw_ts[1].tv_nsec);
        return true;
    }
    data_ts.SetSec(0);
    data_ts.SetNsec(0);
    mgt_ts.SetSec(0);
    mgt_ts.SetNsec(0);
    return false;
}

holo::bool_t GetTimeDiff(holo::common::Duration& timediff)
{
    holo::common::Timestamp mgt_ts;
    holo::common::Timestamp data_ts;
    if (GetAllLevelTime(mgt_ts, data_ts))
    {
        timediff = mgt_ts - data_ts;
        LOG(INFO) << "mdc610 management_layer_time - data_layer_time = " << std::setprecision(19) << timediff.ToSec();
        return true;
    }
    timediff.SetSec(0);
    timediff.SetNsec(0);
    return false;
}

void GetTimeDiffBlocked(holo::common::Duration& timediff)
{
    holo::common::Timestamp mgt_ts;
    holo::common::Timestamp data_ts;
    holo::Timer timer(10);
    while(!GetAllLevelTime(mgt_ts, data_ts))
    {
        timer.Start();
        LOG(ERROR) << "failed to get mdc610 system time, will retry...";
        timer.Stop();
    }
    timediff = mgt_ts - data_ts;
    LOG(INFO) << "mdc610 management_layer_time - data_layer_time = " << std::setprecision(19) << timediff.ToSec();
}

#if (20220228 == MDC610_VERSION_NUM)
holo::bool_t RegisterMbuf()
{
    if (!ara::rm::RegisterHisiResource()) 
    {
        LOG(ERROR) << "register camera_receive failed!";
        return false;
    }
    
    BuffCfg cfg;
    memset(&cfg, 0x0, sizeof(BuffCfg));

    const int ret = halBuffInit(&cfg);
    if (ret != DRV_ERROR_NONE) 
    {
        if (DRV_ERROR_REPEATED_INIT != ret)
        {
            LOG(ERROR) << "halBuffInit result: " << ret;
            return false;
        }

        LOG(WARNING) << "halBuffInit repeat";
    }

    return true;
}
#endif

}
}
