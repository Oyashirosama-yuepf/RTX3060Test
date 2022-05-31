/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common.h
 * @brief This header file defines some helper functions
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-11-30
 */

#ifndef HOLO_3D_COMMON_DETAILS_COMMON_H_
#define HOLO_3D_COMMON_DETAILS_COMMON_H_

#include <holo/3d/common/point_traits.h>
#include <holo/3d/common/point_cloud.h>
#include <holo/3d/common/point_types.h>

namespace holo
{
namespace pointcloud
{
namespace internal
{
/**
 * @brief Copy Point Helper
 *
 * @tparam PointInT
 * @tparam PointOutT
 * @tparam Condition
 */
template <typename PointInT, typename PointOutT, typename Condition = void>
struct CopyPointFunctor
{
};

/**
 * @brief CopyPointFunctor for same point type
 *
 * @tparam PointInT
 * @tparam PointOutT
 */
template <typename PointInT, typename PointOutT>
struct CopyPointFunctor<PointInT, PointOutT, typename std::enable_if<std::is_same<PointInT, PointOutT>::value>::type>
{
    inline void operator()(const PointInT& pi, PointOutT& po) const
    {
        memcpy(&po, &pi, sizeof(PointInT));
    }
};

/**
 * @brief CopyPointFunctor for different point type
 *
 * @details only copy common geometry parts
 * @tparam PointInT
 * @tparam PointOutT
 */
template <typename PointInT, typename PointOutT>
struct CopyPointFunctor<PointInT, PointOutT, typename std::enable_if<!std::is_same<PointInT, PointOutT>::value>::type>
{
    inline void operator()(const PointInT& pi, PointOutT& po) const
    {
        // only copy common geometry part
        constexpr size_t dim =
            PointInT::SIZE_VALUE < PointOutT::SIZE_VALUE ? PointInT::SIZE_VALUE : PointOutT::SIZE_VALUE;

        for (size_t i = 0U; i < dim; ++i)
        {
            po[i] = pi[i];
        }
    }
};

/**
 * @brief Tranform point cloud helper
 *
 * @tparam PointT
 * @tparam Condition
 */
template <typename PointT, typename Condition = void>
struct TransformFunctor
{
};

/**
 * @brief TransformFunctor for point types without normal
 *
 * @tparam PointT
 */
template <typename PointT>
struct TransformFunctor<PointT, typename std::enable_if<!traits::HasNormal<PointT>::value>::type>
{
    template <typename T>
    void operator()(PointCloudT<PointT> const& input, geometry::Pose3T<T> const& pose, PointCloudT<PointT>& output)
    {
        using Point3Type = geometry::Point3T<typename PointT::ScalarType>;
        using PoseType   = geometry::Pose3T<typename PointT::ScalarType>;

        PoseType pose_t = (PoseType)pose;
        output.SetTimestamp(input.GetTimestamp());
        output.SetCoordinate(input.GetCoordinate());
        output.SetDense(input.IsDense());
        output.SetPose(input.GetPose());
        output.resize(input.size());

        for (size_t i = 0; i < input.size(); ++i)
        {
            PointT const& p = input[i];
            output[i]       = p;
            Point3Type pt   = pose_t.TransformFrom(Point3Type(p[0], p[1], p[2]));
            output[i].Set(pt[0], pt[1], pt[2]);
        }
    }

    template <typename T>
    void operator()(PointCloudT<PointT> const& input, std::vector<size_t> const& indices,
                    geometry::Pose3T<T> const& pose, PointCloudT<PointT>& output)
    {
        using Point3Type = geometry::Point3T<typename PointT::ScalarType>;
        using PoseType   = geometry::Pose3T<typename PointT::ScalarType>;

        PoseType pose_t = (PoseType)pose;
        output.SetTimestamp(input.GetTimestamp());
        output.SetCoordinate(input.GetCoordinate());
        output.SetDense(input.IsDense());
        output.SetPose(input.GetPose());
        output.resize(indices.size());

        for (size_t i = 0; i < indices.size(); ++i)
        {
            PointT const& p = input[indices[i]];
            output[i]       = p;
            Point3Type pt   = pose_t.TransformFrom(Point3Type(p[0], p[1], p[2]));
            output[i].Set(pt[0], pt[1], pt[2]);
        }
    }
};

/**
 * @brief TransformFunctor for point types with normal
 *
 * @tparam PointT
 */
template <typename PointT>
struct TransformFunctor<PointT, typename std::enable_if<traits::HasNormal<PointT>::value>::type>
{
    template <typename T>
    void operator()(PointCloudT<PointT> const& input, geometry::Pose3T<T> const& pose, PointCloudT<PointT>& output)
    {
        using ScalarType  = typename PointT::ScalarType;
        using Point3Type  = geometry::Point3T<ScalarType>;
        using Vector3Type = numerics::Vector3T<ScalarType>;
        using PoseType    = geometry::Pose3T<ScalarType>;

        PoseType pose_t = (PoseType)pose;
        output.SetTimestamp(input.GetTimestamp());
        output.SetCoordinate(input.GetCoordinate());
        output.SetDense(input.IsDense());
        output.SetPose(input.GetPose());
        output.resize(input.size());

        for (size_t i = 0; i < input.size(); ++i)
        {
            PointT const& pi = input[i];
            output[i]        = pi;

            Point3Type  pt = pose_t.TransformFrom(Point3Type(pi[0], pi[1], pi[2]));
            Vector3Type nt = pose_t.TransformFrom(pi.GetNormal());
            output[i].Set(pt[0], pt[1], pt[2]);
            output[i].SetNormal(nt);
        }
    }

    template <typename T>
    void operator()(PointCloudT<PointT> const& input, std::vector<size_t> const& indices,
                    geometry::Pose3T<T> const& pose, PointCloudT<PointT>& output)
    {
        using ScalarType  = typename PointT::ScalarType;
        using Point3Type  = geometry::Point3T<ScalarType>;
        using Vector3Type = numerics::Vector3T<ScalarType>;
        using PoseType    = geometry::Pose3T<ScalarType>;

        PoseType pose_t = (PoseType)pose;
        output.SetTimestamp(input.GetTimestamp());
        output.SetCoordinate(input.GetCoordinate());
        output.SetDense(input.IsDense());
        output.SetPose(input.GetPose());
        output.resize(indices.size());

        for (size_t i = 0; i < indices.size(); ++i)
        {
            PointT const& pi = input[indices[i]];
            output[i]        = pi;

            Point3Type  pt = pose_t.TransformFrom(Point3Type(pi[0], pi[1], pi[2]));
            Vector3Type nt = pose_t.TransformFrom(pi.GetNormal());
            output[i].Set(pt[0], pt[1], pt[2]);
            output[i].SetNormal(nt);
        }
    }
};

namespace hash_matrix
{
template <typename T>
struct hash
{
    size_t operator()(T const& matrix) const
    {
        size_t seed = 0;
        // https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
        for (int32_t i = 0; i < (int32_t)matrix.GetSize(); ++i)
        {
            auto element = *(matrix.GetData() + i);
            seed ^= std::hash<typename T::ScalarType>()(element) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        return seed;
    }
};
}  // namespace hash_matrix

namespace hash_eigen
{
template <typename T>
struct hash
{
    size_t operator()(T const& v) const
    {
        size_t seed = 0;
        // https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
        for (int32_t i = 0; i < (int32_t)v.size(); ++i)
        {
            auto element = *(v.data() + i);
            seed ^= std::hash<typename T::value_type>()(element) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        return seed;
    }
};
}  // namespace hash_eigen
}  // namespace internal
}  // namespace pointcloud
}  // namespace holo

#endif
