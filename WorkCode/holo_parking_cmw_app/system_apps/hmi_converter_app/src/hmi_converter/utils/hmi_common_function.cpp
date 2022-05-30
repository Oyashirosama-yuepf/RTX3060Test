/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hmi_common_function.cpp
 * @brief This cpp file defines common fuction class of hmi_converter
 * @author yuanjunchao(yuanjunchao@holomatic.com)
 * @date 2022/01/26
 */

#include <hmi_converter/utils/hmi_common_function.h>

namespace holo
{
namespace parking_cmw_app
{
namespace hmi_converter
{
int CommonFunc::GetSystemCmadOutput(char const* cmd, uint cmad_len, char* output, uint out_len)
{
    if (output == nullptr)
    {
        return -2;
    }

    char buf[cmad_len];
    memset(buf, 0, cmad_len);

    FILE* fp = nullptr;
    if ((fp = popen(cmd, "r")) == nullptr)
    {
        // LOG(INFO) << "GetSystemCmadOutput(): popen error!";
        return -1;
    }

    uint read_len = 0;
    uint cur_output_len = 0;
    while (fgets(buf, sizeof(buf), fp))
    {
        read_len = strlen(buf);
        if ((cur_output_len + read_len) >= out_len)
        {
            // keep '\0' for the last byte.
            memcpy(output + cur_output_len, buf, (out_len - cur_output_len - 1));
            break;
        }
        else
        {
            strcat(output, buf);
            cur_output_len += read_len;
        }
    }
    pclose(fp);
    LOG(INFO) << "GetSystemCmadOutput(): output: %s\n"<< output;
    return 0;
}

std::string CommonFunc::GetSystemCmadOutput(std::string cmd, uint output_array_size, uint max_cmad_array_size)
{
    uint copy_len = cmd.size();
    if (copy_len > max_cmad_array_size)
    {
        copy_len = max_cmad_array_size;
    }
    char buf[max_cmad_array_size];
    memcpy(buf, cmd.c_str(), copy_len);
    memset(buf + copy_len, 0, max_cmad_array_size - copy_len);

    char output[output_array_size];
    memset(output, 0, output_array_size);
    int result = GetSystemCmadOutput(buf, copy_len, output, sizeof(output));
    if (result == 0)
    {
        return std::string(output);
    }
    return "";
}

std::string CommonFunc::GetSystemTime()
{
    char       time_array[100] = {0};
    time_t     time;
    struct tm* p = nullptr;
    std::time(&time);
    p = localtime(&time);
    if (p != nullptr)
    {
        sprintf(time_array, "%02d:%02d:%02d", p->tm_hour, p->tm_min, p->tm_sec);
    }
    return std::string(time_array);
}

std::string CommonFunc::GetSystemDate()
{
    char       time_array[100] = {0};
    time_t     time;
    struct tm* p = nullptr;
    std::time(&time);
    p = localtime(&time);
    if (p != nullptr)
    {
        sprintf(time_array, "%04d-%02d-%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday);
    }
    return std::string(time_array);
}

std::string CommonFunc::GetSystemDateTime()
{
    return GetSystemDate() + "_" + GetSystemTime();
}

}  // namespace hmi_converter
}  // namespace parking_cmw_app
}  // namespace holo
