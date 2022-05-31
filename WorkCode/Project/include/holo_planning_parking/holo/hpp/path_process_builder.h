/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hpp_builder.h
 * @brief the header of path process builder
 * @author lizhao(lizhao@holomatic.com)
 * @date 2021-01-27
 */

#ifndef _HOLO_PLANNING_HPP_BUILDER_H_
#define _HOLO_PLANNING_HPP_BUILDER_H_

#include <holo/utils/yaml.h>

#include <holo/hpp/path_process.h>

namespace holo
{
namespace planning
{
class PathProcessBuilder
{
public:
    /**
     * @brief Create hpp instance
     *
     * @param filepath File path of yaml
     * @param hz Frequence
     *
     * @return Pointer to a hpp instance
     */
    static std::shared_ptr<PathProcess> CreateHpp(const std::string& filepath, float64_t hz = 20);

    /**
     * @brief Parse parameters
     *
     * @param node Node of yaml
     *
     * @return True if parse parameters successfully
     */
    static bool ParseHppParam(const yaml::Node& node, const yaml::Node& vehicle_node);
};
}  // namespace planning
}  // namespace holo

#endif
