/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_obstacle.c
 * @brief To receive and construct mobileye outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/05/26
 */

#include <holo/sensors/smart_camera/me3/me3_holocan.h>
#include <holo/sensors/smart_camera/me3/me3_someip.h>

namespace holo
{
namespace sensors
{
namespace mobileye
{
template class MobileyeDriverT<HoloCanPacket>;
template class MobileyeDriverT<SomeipPacketType>;

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo
