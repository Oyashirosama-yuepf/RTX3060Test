
/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file configuration.cpp
 * @brief This header file defines method of accessing configuration files
 * @author Zhou Huishuang(zhouhuishuang@holomatic.com)
 * @date 2022-01-20
 */

#include <holo/utils/configuration.h>

namespace holo
{
namespace utils
{
YAML::Node     Configuration::config_;
std::once_flag Configuration::instance_flag_;

}  // namespace utils
}  // namespace holo
