/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file yaml_helper.h
 * @brief this file defines help functions to load and save Vector to file
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-03-26"
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_YAML_HELPER_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_YAML_HELPER_H_

#include <holo/localization/sam/sam.h>
#include <holo/numerics/vector.h>
#include <holo/utils/yaml.h>

namespace YAML
{
/**
 * @brief yaml convert for holo::numerics::VectorT<T, Row>
 *
 * @tparam T scalar type
 * @tparam Row rows of the vector
 */
template <typename T, int32_t Row>
struct convert<holo::numerics::VectorT<T, Row>>
{
    using ScalarType = T;
    using ValueType  = holo::numerics::VectorT<ScalarType, Row>;

    static Node encode(ValueType const& rhs)
    {
        Node node;

        for (int32_t i = 0u; i < Row; i++)
        {
            node.push_back(rhs[i]);
        }

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            assert(node.size() == rhs.GetSize());

            for (int32_t i = 0u; i < static_cast<int32_t>(node.size()); i++)
            {
                rhs[i] = node[i].as<ScalarType>();
            }

            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};

/**
 * @brief yaml convert for gtsam vector type
 */
template <>
struct convert<holo::localization::GTVector>
{
    using ScalarType = holo::localization::GTScalar;
    using ValueType  = holo::localization::GTVector;

    static Node encode(ValueType const& rhs)
    {
        Node node;

        for (int32_t i = 0u; i < rhs.rows(); i++)
        {
            node.push_back(rhs[i]);
        }

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.resize(node.size());

            for (int32_t i = 0u; i < static_cast<int32_t>(node.size()); i++)
            {
                rhs[i] = node[i].as<ScalarType>();
            }

            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};
}  // namespace YAML
#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_YAML_HELPER_H_
