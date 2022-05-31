/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file horizon_matrix2.c
 * @brief A class to receive and construct horizon matrix2 outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/07
 */

#include <holo/sensors/smart_camera/matrix2/matrix2_holocan.h>

namespace holo
{
namespace sensors
{
namespace horizon_matrix2
{
template class HorizonMatrix2DriverT<HoloCanPacket>;

}  // namespace horizon_matrix2
}  // namespace sensors
}  // namespace holo
