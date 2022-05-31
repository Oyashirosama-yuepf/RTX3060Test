/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pilot_errorhandle.h
 * @brief header of pilot_errorhandle
 * @author zhengshaoqian(zhengshaoqian@holomatic.com)
 * @date 2020-04-12
 */

#ifndef HOLO_C_CONTROL_PILOT_ERRORHANDLE_H
#define HOLO_C_CONTROL_PILOT_ERRORHANDLE_H

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/control_command.h>
#include <holo_c/common/light_signal_request.h>
#include <holo_c/common/odometry_float32.h>
#include <holo_c/common/path_float32.h>

#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct LastControlInput
{
    struct Pathf last_path;
    struct Odometryf last_odometry;
    struct ChassisState last_chassis_state; 
};

/**
 * @brief update the input
 * 
 * @param last control input pointer to LastControlInput
 * @param path Pointer to Pathf
 * @param odometry Pointer to Odometryf
 * @param chassis_state Pointer to ChassisState
 */
void pilot_errorhandle_update_input(struct LastControlInput* last_input, struct Pathf* planning_path,
                                    struct Odometryf* odometry, struct ChassisState* chassis_state);

#ifdef __cplusplus
}
#endif

#endif //HOLO_C_CONTROL_PILOT_ERRORHANDLE_H
