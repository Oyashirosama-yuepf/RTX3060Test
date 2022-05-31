/**
 * @file chassis_state.h
 * @brief This header file defines ChassisState Object.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-10-8
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/common/details/chassis_state.h>

#ifndef HOLO_COMMON_CHASSIS_STATE_H_
#define HOLO_COMMON_CHASSIS_STATE_H_

namespace holo
{
namespace common
{
/**
 * @addtogroup common
 * @{
 */

using ChassisState = details::ChassisState;

/**
 * @}
 */

}  // namespace common

using ChassisState[[deprecated]] = common::details::ChassisState;

}  // namespace holo

#endif
