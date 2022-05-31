/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file control_log.h
 * @brief the header of the control_log
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2020-04-29
 */

#ifndef HOLO_C_CONTROL_LOG_CONTROL_LOG_H_
#define HOLO_C_CONTROL_LOG_CONTROL_LOG_H_

#include <assert.h>
#include <stdarg.h>

#include <holo_c/control/log/logger.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOG(log, ...) logger_print_log(global_logger_pointer, log, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_LOG_CONTROL_LOG_H_ */
