/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ublox.cpp
 * @brief the ublox driver
 * @author houyujian@holomatic.com
 * @date 2019-12-12
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#include <holo/sensors/gnss/ublox/ublox_rawbuf.h>
#include <holo/sensors/gnss/ublox/ublox_someip.h>

namespace holo
{
namespace sensors
{
namespace ublox
{
template class UbloxDriverT<RawbufferType>;
template class UbloxDriverT<SomeipPacketType>;

}  // namespace ublox
}  // namespace sensors
}  // namespace holo
