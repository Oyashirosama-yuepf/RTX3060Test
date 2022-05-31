/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file yaml_loader.h
 * @brief This header file defines YamlLoader object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-31
 */

#ifndef HOLO_UTILS_IO_HELPER_H_
#define HOLO_UTILS_IO_HELPER_H_

#include <yaml-cpp/yaml.h>

namespace holo
{
namespace utils
{

template <typename T>
using YamlLoader = YAML::convert<T>;

}
}

#endif
