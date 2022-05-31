/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hpp_builder.h
 * @brief the header of hpp builder
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-09-20
 */

#ifndef _HOLO_PLANNING_HPP_BUILDER_H_
#define _HOLO_PLANNING_HPP_BUILDER_H_

#include <holo/utils/yaml.h>

#include <holo/hpp/hpp.h>

namespace holo
{
namespace planning
{
class HppBuilder
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
    static std::shared_ptr<Hpp> CreateHpp(const std::string& filepath, bool_t is_map_mode, float64_t hz = 20);

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
