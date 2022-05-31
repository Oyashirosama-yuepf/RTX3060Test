/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file generator.h
 * @brief This header file defines details of the generator
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-04
 */

#ifndef HOLO_3D_COMMON_DETAILS_GENERATOR_H_
#define HOLO_3D_COMMON_DETAILS_GENERATOR_H_

#include <holo/3d/common/common.h>

namespace holo
{
namespace pointcloud
{
namespace internal
{
/**
 * @brief Cube point cloud helper
 *
 * @tparam PointT
 * @tparam PointT::ScalarType
 * @tparam Condition
 */
template <typename PointT, typename Scalar = typename PointT::ScalarType, typename Condition = void>
struct CubeFunctor
{
};

/**
 * @brief CubeFunctor for point types without normal
 *
 * @tparam PointT
 */
template <typename PointT, typename Scalar>
struct CubeFunctor<PointT, Scalar, typename std::enable_if<!traits::HasNormal<PointT>::value>::type>
{
    void operator()(Scalar const d, Scalar const r, PointCloudT<PointT>& output)
    {
        size_t steps = static_cast<size_t>(std::floor(d / r));
        output.clear();
        output.reserve(6 * (steps + 1) * (steps + 1));

        // x-y plane
        for (int32_t k = -1; k < 2; k += 2)
        {
            Scalar z = k * (d / 2.0);

            for (size_t i = 0U; i <= steps; ++i)
            {
                Scalar x = -d / 2.0 + i * r;

                for (size_t j = 0U; j <= steps; ++j)
                {
                    Scalar y = -d / 2.0 + j * r;
                    output.push_back(PointT(x, y, z));
                }
            }
        }

        // x-z plane
        for (int32_t k = -1; k < 2; k += 2)
        {
            Scalar y = k * (d / 2.0);

            for (size_t i = 0U; i <= steps; ++i)
            {
                Scalar x = -d / 2.0 + i * r;

                for (size_t j = 1U; j < steps; ++j)
                {
                    Scalar z = -d / 2.0 + j * r;
                    output.push_back(PointT(x, y, z));
                }
            }
        }

        // y-z plane
        for (int32_t k = -1; k < 2; k += 2)
        {
            Scalar x = k * (d / 2.0);

            for (size_t i = 1U; i < steps; ++i)
            {
                Scalar y = -d / 2.0 + i * r;

                for (size_t j = 1U; j < steps; ++j)
                {
                    Scalar z = -d / 2.0 + j * r;
                    output.push_back(PointT(x, y, z));
                }
            }
        }
    }
};

/**
 * @brief CubeFunctor for point types with normal
 *
 * @tparam PointT
 */
template <typename PointT, typename Scalar>
struct CubeFunctor<PointT, Scalar, typename std::enable_if<traits::HasNormal<PointT>::value>::type>
{
    void operator()(Scalar const d, Scalar const r, PointCloudT<PointT>& output)
    {
        size_t steps = static_cast<size_t>(std::floor(d / r));
        output.clear();
        output.reserve(6 * (steps + 1) * (steps + 1));

        // x-y plane
        PointT pt;

        for (int32_t k = -1; k < 2; k += 2)
        {
            Scalar z = k * (d / 2.0);
            Scalar n = k < 0 ? -1.0 : 1.0;

            for (size_t i = 0U; i <= steps; ++i)
            {
                Scalar x = -d / 2.0 + i * r;

                for (size_t j = 0U; j <= steps; ++j)
                {
                    Scalar y = -d / 2.0 + j * r;
                    pt.Set(x, y, z);
                    pt.SetNormal(0, 0, n);
                    output.push_back(pt);
                }
            }
        }

        // x-z plane
        for (int32_t k = -1; k < 2; k += 2)
        {
            Scalar y = k * (d / 2.0);
            Scalar n = k < 0 ? -1.0 : 1.0;

            for (size_t i = 0U; i <= steps; ++i)
            {
                Scalar x = -d / 2.0 + i * r;

                for (size_t j = 1U; j < steps; ++j)
                {
                    Scalar z = -d / 2.0 + j * r;
                    pt.Set(x, y, z);
                    pt.SetNormal(0, n, 0);
                    output.push_back(pt);
                }
            }
        }

        // y-z plane
        for (int32_t k = -1; k < 2; k += 2)
        {
            Scalar x = k * (d / 2.0);
            Scalar n = k < 0 ? -1.0 : 1.0;

            for (size_t i = 1U; i < steps; ++i)
            {
                Scalar y = -d / 2.0 + i * r;

                for (size_t j = 1U; j < steps; ++j)
                {
                    Scalar z = -d / 2.0 + j * r;
                    pt.Set(x, y, z);
                    pt.SetNormal(n, 0, 0);
                    output.push_back(pt);
                }
            }
        }
    }
};

}  // namespace internal
}  // namespace pointcloud
}  // namespace holo

#endif
