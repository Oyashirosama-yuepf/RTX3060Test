/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pair_creation_functor.h
 * @brief This header file defines pair creation functor class
 * @author zhaojiaxing(zhaojiaxing@holomatic.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-03-16
 */

#ifndef HOLO_3D_REGISTRATION_DETAILS_PAIR_CREATION_FUNCTOR_H_
#define HOLO_3D_REGISTRATION_DETAILS_PAIR_CREATION_FUNCTOR_H_

#include <holo/3d/common/common.h>
#include <holo/3d/common/point_cloud.h>
#include <holo/geometry/sphere.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace pointcloud
{
namespace internal
{
/**
 * @brief Pair creation functor
 *
 * @tparam PointT
 * @tparam Scalar
 */
template <typename PointT, typename Scalar = float64_t>
class PairCreationFunctorT
{
public:
    using Sphere3Type   = geometry::Sphere3T<Scalar>;
    using BBoxType      = BBox<PointT, 3>;
    using Point3Type    = geometry::Point3T<Scalar>;
    using Vector3Type   = holo::numerics::Vector3T<Scalar>;
    using PointCloud    = PointCloudT<PointT>;
    using PointCloudPtr = std::shared_ptr<PointCloud>;
    using PairsVector   = std::vector<std::pair<size_t, size_t> >;

    /**
     * @brief Construct a new Pair Creation Functor object from source point cloud
     *
     */
    PairCreationFunctorT()
    {
    }

    /**
     * @brief Destroy the Pair Creation Functor object
     *
     */
    ~PairCreationFunctorT() = default;

    /**
     * @brief Normalize world point
     *
     * @param[in] p input point
     * @return Point3Type
     */
    Point3Type WorldToUnit(Point3Type const& p) const
    {
        return (p - center) / ratio + half;
    }

    /**
     * @brief unit point to world point
     *
     * @param[in] p input point
     * @return Point3Type
     */
    Point3Type UnitToWorld(Point3Type const& p) const
    {
        return (p - half) * ratio + center;
    }

    /**
     * @brief unit distance to world distance
     *
     * @param[in] d input distance
     * @return Scalar
     */
    Scalar UnitToWorld(Scalar const d) const
    {
        return d * ratio;
    }

    /**
     * @brief Get the Point In World Coord
     *
     * @param[in] id point index in points vector
     * @return Point3Type
     */
    Point3Type GetPointInWorldCoord(size_t const id) const
    {
        return UnitToWorld(points[id]);
    }

    /**
     * @brief Get the normalized epsilon
     *
     * @param eps
     * @return Scalar
     */
    Scalar GetNormalizedEpsilon(Scalar const eps)
    {
        return eps / ratio;
    }

    /**
     * @brief Initialize internal data structure
     *
     * @param[in] cloud source point cloud
     * @param[in] indices source point indices
     */
    void Initialize(PointCloudPtr const& cloud, std::vector<size_t> const& indices)
    {
        source         = cloud;
        source_indices = indices;
        points.clear();
        primitives.clear();

        PointT   min_pt, max_pt, center_pt;
        BBoxType bbox;
        bbox(*source, min_pt, max_pt);

        center_pt           = (min_pt + max_pt) / 2;
        Point3Type diagonal = (max_pt - min_pt).template As<Point3Type>();

        // add a delta to avoid to have elements with coordinate = 1
        ratio = std::max(std::max(diagonal[0], diagonal[1]), diagonal[2]) + 0.001;

        size_t const num_points = source_indices.size();
        points.resize(num_points);
        primitives.resize(num_points);
        ids.resize(num_points);

        for (size_t i = 0; i < num_points; ++i)
        {
            points[i]     = WorldToUnit(source->at(source_indices[i]).template As<Point3Type>());
            primitives[i] = Sphere3Type(points[i], 1.0);
            ids[i]        = i;
        }
    }

    /**
     * @brief Set the Radius object
     *
     * @param radius
     */
    void SetRadius(Scalar const radius)
    {
        Scalar const normalized_radius = radius / ratio;

        for (size_t i = 0; i < primitives.size(); ++i)
        {
            primitives[i].SetRadius(normalized_radius);
        }
    }

    /**
     * @brief Set the Base Quadrilateral point
     *
     * @param _base_point1
     * @param _base_point2
     */
    void SetBase(Vector3Type const& _base_point1, Vector3Type const& _base_point2)
    {
        base_point1 = _base_point1;
        base_point2 = _base_point2;
    }

    /**
     * @brief Process source pairs
     *
     * @param[in] i the first point index
     * @param[in] j the second point index
     */
    void ProcessPairs(size_t const i, size_t const j)
    {
        size_t const num_points = points.size();

        if (i >= num_points || j >= num_points)
        {
            LOG(ERROR) << "input index out of bound: " << num_points;
            return;
        }

        if (i <= j)
        {
            LOG(WARNING) << "input index i: " << i << " should larger than j: " << j;
            return;
        }

        Vector3Type  segment1      = base_point2 - base_point1;
        Scalar const pair_distance = segment1.GetNorm();

        segment1.Normalize();

        Vector3Type const& p = source->at(source_indices[i]).template As<Vector3Type>();
        Vector3Type const& q = source->at(source_indices[j]).template As<Vector3Type>();

        // Compute the distance and two normal angles to ensure working with
        // wrong orientation. We want to verify that the angle between the
        // normals is close to the angle between normals in the base. This can be
        // checked independent of the full rotation angles which are not yet
        // defined by segment matching alone..
        Scalar const dist = (q - p).GetNorm();

        if (std::fabs(dist - pair_distance) > max_pair_diff)
        {
            return;
        }

        if (max_translation_distance > 0)
        {
            Scalar const dist_p    = (p - base_point1).GetNorm();
            Scalar const dist_q    = (q - base_point2).GetNorm();
            bool_t const dist_good = dist_p < max_translation_distance && dist_q < max_translation_distance;

            if (!dist_good)
            {
                return;
            }
        }

        if (max_angle > 0)
        {
            Vector3Type segment2 = q - p;
            segment2.Normalize();

            if (std::acos(segment1.Dot(segment2)) < geometry::Radian(max_angle))
            {
                pairs.emplace_back(j, i);
            }

            if (std::acos(segment1.Dot(-segment2)) < geometry::Radian(max_angle))
            {
                pairs.emplace_back(i, j);
            }
            return;
        }

        pairs.emplace_back(j, i);
        pairs.emplace_back(i, j);

        return;
    }

    Scalar max_pair_diff;             ///< max segment difference between base segment and source segment
    Scalar max_translation_distance;  ///< max distance between source point and base point
    Scalar max_angle;                 ///< max angle between base segment and source segment

    PointCloudPtr            source;          ///< source point cloud
    std::vector<size_t>      source_indices;  ///< source point indices
    std::vector<Point3Type>  points;          ///< unit source points
    std::vector<Sphere3Type> primitives;      ///< spheres of points
    Vector3Type              base_point1;     ///< base segment point1
    Vector3Type              base_point2;     ///< base segment point2
    PairsVector              pairs;           ///< output source pairs
    std::vector<size_t>      ids;             ///< indices of points
    Point3Type               center;          ///< center point
    Scalar                   ratio;           ///< max diagonal value of bounding box

    Point3Type const half = Point3Type(0.5, 0.5, 0.5);
};
}  // namespace internal
}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_REGISTRATION_DETAILS_PAIR_CREATION_FUNCTOR_H_
