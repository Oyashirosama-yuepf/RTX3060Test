/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hmi_common_function.h
 * @brief the common fuction of hmi_converter
 * @author yuanjunchao(yuanjunchao@holomatic.com)
 * @date 2022/01/26
 */

#ifndef HOLO_PARKING_HMI_COMMMON_FUNCTION_H_
#define HOLO_PARKING_HMI_COMMMON_FUNCTION_H_

#include <stdio.h>
#include <string.h>

#include <ctime>
#include <string>

#include <glog/logging.h>

namespace holo
{
namespace parking_cmw_app
{
namespace hmi_converter
{
struct CommonFunc
{
    /**
     * @brief run [cmd] by system shell and save std output to [output].
     * @param[0] cmd: system command.
     * @param[1] cmad_len: system command len.
     * @param[2] output: char array to save system output.
     * @param[3] out_len: output array len.
     * @return 0: success, -1: popen failed. -2: output char array is nullptr.
     * @note please may sure output is big enough to store system output. otherwise will clip the output.
     **/
    static int GetSystemCmadOutput(char const* cmd, uint cmad_len, char* output, uint out_len);

    /**
     * @brief run [cmd] by system shell and save std output to [output].
     * @param[0] cmd: system command
     * @param[1] output_array_size: char array to save system output.
     * @param[2] max_cmad_array_size: max system command len limit.
     * @return 0: success, -1: popen failed. -2: output char array is nullptr.
     * @note 1.output_array_size limit output len, max_cmad_array_size limit cmad len(clip when over length).
     **/
    static std::string GetSystemCmadOutput(std::string cmd,
                                           uint        output_array_size   = 1024,
                                           uint        max_cmad_array_size = 256);

    static std::string GetSystemTime();

    static std::string GetSystemDate();

    static std::string GetSystemDateTime();
};

}  // namespace hmi_converter
}  // namespace parking_cmw_app
}  // namespace holo

#endif  // HOLO_PARKING_HMI_COMMMON_FUNCTION_H_
