/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file osqp_config.h
 * @brief The config of OSQP solver
 * @author jiangshunchang(jiangshunchang@holomatic.com)
 * @date 2022-02-08
 */

#ifndef _HOLO_PLANNING_OSQP_CONFIG_H_
#define _HOLO_PLANNING_OSQP_CONFIG_H_

#include <holo/core/types.h>

namespace holo
{
namespace planning
{

struct OsqpConfig
{
    uint32_t  check_termination;
    bool_t    verbose;
    bool_t    scaled_termination;
    bool_t    warm_start;
    bool_t    polish;
    float64_t time_limit;
    uint32_t  scaling;
    uint32_t  max_iter;
};

}  // namespace planning
}  // namespace holo

#endif  //_HOLO_PLANNING_OSQP_CONFIG_H_
