/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file estimator.h
 * @brief This header file defines the Estimator class with gtsam.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2021-06-02"
 */

#ifndef HOLO_PERCEPTION_3D_FACTOR_GRAPH_ESTIMATOR_H_
#define HOLO_PERCEPTION_3D_FACTOR_GRAPH_ESTIMATOR_H_

#include <holo/geometry/pose3.h>
#include <holo/perception/factor_graph/factors.h>
#include <holo/perception/factor_graph/graph_builder.h>
#include <holo/perception/factor_graph/preprocessor.h>
#include <holo/perception/space_convertor/ipm_convertor.h>
#include <holo/perception/space_convertor/size_convertor.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup factor_graph
 *
 */

/**
 * @brief This class defines a method to estimate 3d position based on factor graph with gtsam.
 *
 */
class Estimator
{
public:
    using Pose3Type   = holo::geometry::Pose3T<Scalar>;
    using Rot3Type    = holo::geometry::Rot3T<Scalar>;
    using Point3Type  = holo::geometry::Point3T<Scalar>;
    using Vector3Type = holo::numerics::Vector3T<Scalar>;

    struct Parameters
    {
        Preprocessor::Parameters preprocessor_parameters;
        GraphBuilder::Parameters graph_builder_parameters;
        Pose3Type                Tbody_cam;
        bool_t                   revise_yaw;
        bool_t                   verbose;
        Scalar                   bodyH;

        /**
         * @brief Construct a new Parameters object
         *
         * @param cam_intrinsic_file, target camera's intrinsic file
         * @param node, yaml node
         * @param _verbose, whether to output the log infos
         */
        Parameters(std::string const& cam_intrinsic_file, holo::yaml::Node const& node, Pose3Type const& _Tbody_cam,
                   bool_t _verbose = true)
          : preprocessor_parameters(cam_intrinsic_file, _Tbody_cam, node["bodyH"].as<Scalar>())
          , graph_builder_parameters(preprocessor_parameters.K, node)
          , Tbody_cam(_Tbody_cam)
          , revise_yaw(node["revise_yaw"].as<bool_t>())
          , verbose(node["verbose"].as<bool_t>(_verbose))
          , bodyH(node["bodyH"].as<Scalar>())
        {
        }
    };

    /**
     * @brief Construct a new Estimator object
     *
     * @param parameters
     */
    Estimator(Parameters const& parameters);

    /**
     * @brief Destroy the Estimator object
     *
     */
    ~Estimator();

    /**
     * @brief estimate the new_object's 3d state
     *
     * @param new_timestamp, new frame's timestamp
     * @param new_object, detected new object
     * @param state, factor graph state
     * @param state, main factor graph state for position, velocity
     * @param ego_speed, ego car speed
     * @return bool_t, true if estimate ok else false
     */
    bool_t RunMain(Timestamp const& new_timestamp, Object& new_object, SlidingWindowState& state,
                   float32_t ego_speed) const;

    /**
     * @brief estimate the new_object's prior state
     *
     * @param new_timestamp, new frame's timestamp
     * @param new_object, detected new object
     * @param state_prior, factor graph state for prior info: yaw and dimension
     * @param ego_speed, ego car speed
     * @return bool_t, true if estimate ok else false
     */
    bool_t RunPrior(Timestamp const& new_timestamp, Object const& new_object, SlidingWindowState& state_prior,
                    float32_t ego_speed) const;

    /**
     * @brief Update Object's position and velocity
     *
     * @param state, current sliding window state
     * @param object, object info
     */
    void UpdateObject(SlidingWindowState const& state, Object& object) const
    {
        ObjectState const object_state = state.GetTheLastestObjectState();

        // position
        holo::geometry::Point3T<Scalar> position_new(object_state.position.x(), object_state.position.y(),
                                                     object_state.position.z());
        object.SetPosition(position_new);
        object.GetBox3().SetCenterPoint(position_new);

        // velocity
        object.SetVelocity(holo::numerics::Vector3T<Scalar>(object_state.velocity.x(), object_state.velocity.y(),
                                                            object_state.velocity.z()));
    }

    /**
     * @brief Update object's prior info: dimension and yaw
     *
     * @param state, current sliding window state for prior info
     * @param object, object info
     */
    void UpdateObjectPriorInfo(SlidingWindowState& state, Object& object) const
    {
        ObjectState const object_state = state.GetTheLastestObjectState();

        // dimension
        if (parameters_.graph_builder_parameters.enable_prior_dimension_factor)
        {
            object.GetBox3().SetXDim(object_state.dimension(0U));
            object.GetBox3().SetYDim(object_state.dimension(1U));
            object.GetBox3().SetZDim(object_state.dimension(2U));
        }

        // yaw
        if (parameters_.graph_builder_parameters.enable_prior_yaw_factor)
        {
            if (state.num < 20U)
            {
                state.yaw = object_state.yaw(0U);
            }
            else if (std::fabs(state.yaw - object_state.yaw(0U)) < M_PI_4)
            {
                state.yaw = object_state.yaw(0U);
            }
            object.GetBox3().SetRy(state.yaw);
        }
    }

    /**
     * @brief convert object from camera to body
     *
     * @param object
     */
    void ConvertToBody(Object& object, bool_t revise_yaw = false) const;

    /**
     * @brief Get whether need smooth dimension and yaw in sub graph
     *
     * @return bool_t
     */
    bool_t IsNeedSmoothPriorInfo() const
    {
        return parameters_.graph_builder_parameters.enable_prior_yaw_factor ||
               parameters_.graph_builder_parameters.enable_prior_dimension_factor;
    }

    /**
     * @brief Estimate the object's position use IPM
     *
     * @param object
     * @return bool_t
     */
    bool_t IPMEstimate(Object& object, bool_t is_vehicle) const;

    /**
     * @brief Estimate the object's position use scale
     *
     * @param object
     * @return bool_t
     */
    bool_t ScaleEstimate(Object& object) const;

private:
    Parameters   parameters_;
    Preprocessor preprocessor_;
    GraphBuilder graph_builder_;
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_3D_FACTOR_GRAPH_ESTIMATOR_H_
