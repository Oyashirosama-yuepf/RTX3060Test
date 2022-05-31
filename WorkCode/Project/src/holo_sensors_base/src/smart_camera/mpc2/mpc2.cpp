/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bosch_mpc.c
 * @brief A class to receive and construct bosch mpc outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/07
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_holocan.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_someip.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
template class BoschMpcDriverT<HoloCanPacket>;
template class BoschMpcDriverT<SomeipPacketType>;

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo
