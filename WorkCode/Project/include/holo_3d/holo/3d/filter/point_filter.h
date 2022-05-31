/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_filter.h
 * @brief This header file defines simple filter to check point properties
 * @author luopei(luopei@holomaitc.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-12-02
 */

#ifndef HOLO_3D_FILTER_POINT_FILTER_H_
#define HOLO_3D_FILTER_POINT_FILTER_H_

#include <holo/3d/filter/filter.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief point checker base
 *
 * @tparam PointT
 */
template <typename PointT>
struct PointCheckerT
{
    using Ptr      = std::shared_ptr<PointCheckerT>;
    using ConstPtr = std::shared_ptr<const PointCheckerT>;

    virtual bool operator()(PointT const&) = 0;

    virtual ~PointCheckerT()
    {
    }
};

/**
 * @brief Nan point checker
 *
 * @tparam PointT
 */
template <typename PointT>
struct NaNPointCheckerT : public PointCheckerT<PointT>
{
    NaNPointCheckerT()
    {
        static_assert(PointT::SIZE_VALUE == 3, "point must has x, y and z fields!");
    }

    virtual bool operator()(PointT const& p)
    {
        if (!std::isfinite(p[0]) || !std::isfinite(p[1]) || !std::isfinite(p[2]))
        {
            return true;
        }

        return false;
    }
};

/**
 * @brief Distance point checker
 *
 * @tparam PointT
 */
template <typename PointT>
struct DistancePointCheckerT : public PointCheckerT<PointT>
{
    using Scalar      = typename PointT::ScalarType;
    using Vector3Type = holo::numerics::Vector3T<Scalar>;

    DistancePointCheckerT(Scalar _distance) : distance(_distance)
    {
        static_assert(PointT::SIZE_VALUE == 3, "point must have x, y and z fields!");
    }

    virtual bool operator()(PointT const& p)
    {
        if (p.template As<Vector3Type>().GetNorm() <= distance)
        {
            return true;
        }

        return false;
    }

protected:
    Scalar distance;
};

/**
 * @brief Zero point checker
 *
 * @tparam PointT
 */
template <typename PointT>
struct ZeroPointCheckerT : public DistancePointCheckerT<PointT>
{
    using Base = DistancePointCheckerT<PointT>;

    ZeroPointCheckerT() : Base(0.0)
    {
    }

    virtual bool operator()(PointT const& p)
    {
        return Base::operator()(p);
    }
};

/**
 * @brief Point filter
 *
 * @tparam PointT
 */
template <typename PointT>
class PointFilterT : public FilterBaseT<PointT>
{
public:
    using PointChecker    = PointCheckerT<PointT>;
    using PointCheckerPtr = typename PointChecker::Ptr;
    using Base            = FilterBaseT<PointT>;

    using Base::cloud_;
    using Base::PostCompute;
    using Base::PreCompute;
    using typename Base::PointCloud;
    using typename Base::PointCloudPtr;

    /**
     * @brief Construct a new Point Filter
     *
     * @param[in] cloud the input point cloud
     */
    PointFilterT(PointCloudPtr cloud) : Base(cloud)
    {
    }

    /**
     * @brief Compute filtered point cloud
     *
     * @return PointCloudPtr
     */
    virtual PointCloudPtr Compute() override;

    /**
     * @brief Add point checker
     *
     * @param[in] checker point checker
     */
    void AddChecker(PointCheckerPtr checker)
    {
        checkers_.push_back(checker);
    }

private:
    std::vector<PointCheckerPtr> checkers_;
};

}  // namespace pointcloud
}  // namespace holo
#endif  // HOLO_3D_FILTER_POINT_FILTER_
