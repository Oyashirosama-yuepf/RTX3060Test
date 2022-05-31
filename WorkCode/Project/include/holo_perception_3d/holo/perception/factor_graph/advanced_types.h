/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file advanced_types.h
 * @brief This header file defines variables used in the factor graph algorithm.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2021-06-01"
 */

#ifndef HOLO_PERCEPTION_3D_FACTOR_GRAPH_ADVANCED_TYPES_H_
#define HOLO_PERCEPTION_3D_FACTOR_GRAPH_ADVANCED_TYPES_H_

#include <holo/perception/factor_graph/gtsam_types.h>

namespace holo
{
namespace perception
{
/**
 * @brief Define the corresponding relation between vertex and box2d's edge
 *
 */
struct Correspondence3d2d
{
    enum Axis : uint32_t
    {
        X = 0U,
        Y = 1U,
    };

    uint32_t index;   ///< vertex index of box3d
    Point2   img_pt;  ///< 2D measurement on image
    Axis     axis;    ///< error dimension (X or Y)

    Correspondence3d2d(uint32_t const _index, Point2 const& _img_pt, Axis const _axis)
      : index(_index), img_pt(_img_pt), axis(_axis)
    {
    }
};

/**
 * @brief define object state which is estimated with factor graph
 *
 */
struct ObjectState
{
    Point3  position  = Point3(0.0, 0.0, 0.0);  ///< position(x, y, z) in camera coordinate
    Vector3 velocity  = Vector3::Zero();        ///< velocity(vx, vy, vz) in camera coordinate
    Vector3 dimension = Vector3::Zero();        ///< box3d(w, h, l) dimension
    Vector1 yaw       = Vector1::Zero();        ///< yaw
};

/**
 * @brief Define the measurements of each object and factor switch
 *
 */
struct FactorMeasurements
{
    Timestamp timestamp;  ///< timestamp of the lastest measurement

    int64_t old_index = -1;
    int64_t new_index = -1;
    Scalar  dt        = -1.0;

    // measured object orientation in radian
    Scalar rx = 0.0;
    Scalar ry = 0.0;
    Scalar rz = 0.0;

    boost::optional<std::pair<Point3, Point2>> center;  ///< 3D center in object coordinate + 2D center in image
                                                        ///< coordinate

    // vertex project factor
    holo::container::Vector<Correspondence3d2d, 4U> correspondences;

    bool_t bad_cp = false;  ///< whether the predicted center point is in the box2d

    // need smooth factor
    bool_t need_smooth_factor = false;

    // need yaw smooth factor
    bool_t need_yaw_smooth_factor = false;

    // need dimension smooth factor
    bool_t need_dimension_smooth_factor = false;

    bool_t                                                                        is_truncated = false;
    holo::container::Vector<std::pair<Point3, std::pair<uint32_t, uint32_t>>, 4U> kp_correspondences;
    uint32_t                                                                      valid_kp_cnt = 0U;

    // predicted object state
    ObjectState prediction;

    // whether object is relative static with ego
    bool_t is_relative_static = false;
};

/**
 * @brief define the problem
 *
 */
struct Problem
{
    NonlinearFactorGraph graph;
    Values               values;
    KeyTimestampMap      key_timestamp;
};

/**
 * @brief define the optimizer and optimized values
 *
 */
struct SlidingWindowState
{
    holo::common::Timestamp timestamp = Timestamp();  ///< timestamp of the lastest state
    int64_t                 index     = -1;           ///< index of the lastest state
    uint64_t                num       = 0;            ///< optimized num
    Scalar                  yaw       = 0;            ///< lastest yaw

    IncrementalFixedLagSmoother smoother = IncrementalFixedLagSmoother(2.0);  ///< smoother takes charge of optimization

    Values values;  ///< values that store all the states in graph

    /**
     * @brief Get the lastest Object State object
     *
     * @return ObjectState
     */
    ObjectState GetTheLastestObjectState() const
    {
        if (index < 0U)
        {
            throw std::runtime_error("system is not initialized.");
        }

        ObjectState s;

        if (values.exists(X(index)))
        {
            s.position = values.at<Point3>(X(index));
        }

        if (values.exists(V(index)))
        {
            s.velocity = values.at<Vector3>(V(index));
        }

        if (values.exists(Y(index)))
        {
            Scalar yaw = values.at<Vector1>(Y(index))[0U];
            if (std::fabs(yaw) > M_PI)
            {
                yaw = yaw > 0 ? (yaw - M_PI * 2.0f) : (yaw + M_PI * 2);
            }

            s.yaw = Vector1(yaw);
        }

        if (values.exists(D(index)))
        {
            s.dimension = values.at<Vector3>(D(index));
        }

        return s;
    }

    /**
     * @brief handy funtion to create a sliding window state
     *
     * @param lag
     * @return SlidingWindowState
     */
    static SlidingWindowState Create(float64_t const lag = 2.0)
    {
        SlidingWindowState state;
        state.timestamp = Timestamp();
        state.index     = -1;
        state.num       = 0U;
        state.yaw       = 0;

        {
            ISAM2Params isam2_params;
            isam2_params.findUnusedFactorSlots = true;

            state.smoother = IncrementalFixedLagSmoother(lag, isam2_params);
        }
        return state;
    }
};

}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_3D_FACTOR_GRAPH_ADVANCED_TYPES_H_
