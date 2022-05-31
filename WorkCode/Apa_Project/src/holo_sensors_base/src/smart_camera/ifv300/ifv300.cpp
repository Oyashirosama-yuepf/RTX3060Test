/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300.c
 * @brief A class to receive and construct ifv300 outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/07
 */

#include <holo/sensors/smart_camera/ifv300/ifv300_holocan.h>
#include <holo/sensors/smart_camera/ifv300/ifv300_someip.h>

namespace holo
{
namespace sensors
{
namespace ifv300
{
template class Ifv300DriverT<HoloCanPacket>;
template class Ifv300DriverT<SomeipPacketType>;

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo
