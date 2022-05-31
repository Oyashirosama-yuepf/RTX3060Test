/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file graph_builder.h
 * @brief This header file defines factor graph build process.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2021-06-02"
 */

#ifndef HOLO_PERCEPTION_3D_FACTOR_GRAPH_GRAPH_BUILDER_H_
#define HOLO_PERCEPTION_3D_FACTOR_GRAPH_GRAPH_BUILDER_H_

#include <holo/perception/factor_graph/advanced_types.h>
#include <holo/perception/factor_graph/factors.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup factor_graph
 */

/**
 * @brief define graph builder
 *
 */
class GraphBuilder
{
public:
    /**
     * @brief Define parameters for building graph
     *
     */
    struct Parameters
    {
        boost::shared_ptr<Cal3_S2> K;

        bool_t enable_motion_factor;
        bool_t enable_projection_factor;
        bool_t enable_vertex_projection_factor;
        bool_t enable_velocity_smooth_factor;
        bool_t enable_prior_dimension_factor;
        bool_t enable_prior_yaw_factor;
        bool_t enable_keypoint_factor = true;
        bool_t enable_ipm_factor      = true;

        Scalar  sigma_motion            = 1e-4;
        Scalar  sigma_cp_projection     = 1e-2;
        Scalar  sigma_vertex_projection = 1e-2;
        Vector3 sigma_velocity_smooth   = Vector3(1e-2, 1e-3, 1e-2);
        Scalar  sigma_yaw_smooth        = 1e-3;
        Scalar  sigma_prior_yaw         = 1e-2;
        Scalar  sigma_dimension_smooth  = 1e-3;
        Scalar  sigma_prior_dimension   = 1e-2;
        Scalar  sigma_keypoint          = 1e-3;
        Scalar  sigma_ipm               = 1e-2;

        Scalar huber_velocity_k = 4.0;
        bool_t use_x_constraint = true;
        Scalar camH             = 1.3;

        Parameters() = default;

        Parameters(boost::shared_ptr<Cal3_S2> _K, bool_t _enable_motion_factor = true,
                   bool_t _enable_projection_factor = true, bool_t _enable_vertex_projection_factor = true,
                   bool_t _enable_velocity_smooth_factor = true, bool_t _enable_prior_dimension_factor = true,
                   bool_t _enable_prior_yaw_factor = true, bool_t _enable_keypoint_factor = true,
                   bool_t _enable_ipm_factor = true)
          : K(_K)
          , enable_motion_factor(_enable_motion_factor)
          , enable_projection_factor(_enable_projection_factor)
          , enable_vertex_projection_factor(_enable_vertex_projection_factor)
          , enable_velocity_smooth_factor(_enable_velocity_smooth_factor)
          , enable_prior_dimension_factor(_enable_prior_dimension_factor)
          , enable_prior_yaw_factor(_enable_prior_yaw_factor)
          , enable_keypoint_factor(_enable_keypoint_factor)
          , enable_ipm_factor(_enable_ipm_factor)
        {
        }

        Parameters(boost::shared_ptr<Cal3_S2> _K, holo::yaml::Node const& node)
          : K(_K)
          , enable_motion_factor(node["enable_motion_factor"].as<bool_t>())
          , enable_projection_factor(node["enable_projection_factor"].as<bool_t>())
          , enable_vertex_projection_factor(node["enable_vertex_projection_factor"].as<bool_t>())
          , enable_velocity_smooth_factor(node["enable_velocity_smooth_factor"].as<bool_t>())
          , enable_prior_dimension_factor(node["enable_prior_dimension_factor"].as<bool_t>())
          , enable_prior_yaw_factor(node["enable_prior_yaw_factor"].as<bool_t>())
          , enable_keypoint_factor(node["enable_keypoint_factor"].as<bool_t>())
          , enable_ipm_factor(node["enable_ipm_factor"].as<bool_t>())
          , sigma_motion(node["sigma_motion"].as<Scalar>())
          , sigma_cp_projection(node["sigma_cp_projection"].as<Scalar>())
          , sigma_vertex_projection(node["sigma_vertex_projection"].as<Scalar>())
          , sigma_velocity_smooth(node["sigma_velocity_smooth"][0U].as<Scalar>(),
                                  node["sigma_velocity_smooth"][1U].as<Scalar>(),
                                  node["sigma_velocity_smooth"][2U].as<Scalar>())
          , sigma_yaw_smooth(node["sigma_yaw_smooth"].as<Scalar>())
          , sigma_prior_yaw(node["sigma_prior_yaw"].as<Scalar>())
          , sigma_dimension_smooth(node["sigma_dimension_smooth"].as<Scalar>())
          , sigma_prior_dimension(node["sigma_prior_dimension"].as<Scalar>())
          , sigma_keypoint(node["sigma_keypoint"].as<Scalar>())
          , sigma_ipm(node["sigma_ipm"].as<Scalar>())
          , huber_velocity_k(node["huber_velocity_k"].as<Scalar>())
          , use_x_constraint(node["use_x_constraint"].as<bool_t>())
          , camH(node["camH"].as<Scalar>())
        {
        }

        void InitConfig(std::string const& cfg_file);

        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters);
    };

    /**
     * @brief Construct a new Graph Builder object
     *
     * @param parameters
     */
    GraphBuilder(Parameters const& parameters);

    /**
     * @brief Build the main graph
     *
     * @param fm
     * @return Problem
     */
    Problem Run(FactorMeasurements const& fm) const;

    /**
     * @brief Build the prior info graph
     *
     * @param fm
     * @return Problem
     */
    Problem RunPrior(FactorMeasurements const& fm) const;

private:
    Parameters parameters_;
};
/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_3D_FACTOR_GRAPH_GRAPH_BUILDER_H_
