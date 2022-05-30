/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mapping_utils.h
 * @brief This header file defines some utils functions of mapping function
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021/05/15
 */

#ifndef HOLO_PARKING_MAPPING_UTILS_H
#define HOLO_PARKING_MAPPING_UTILS_H

#include <chrono>
#include <fstream>
#include <future>
#include <mutex>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include <holo/utils/yaml.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

std::string GetStrFromTerminal(const std::string& command);
void RestartVSLAM(const uint32_t & input_id);
void StartMapping(const uint32_t & input_id);
std::string StopMapping(const uint32_t & input_id);

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

#endif  //HOLO_PARKING_MAPPING_UTILS_H

