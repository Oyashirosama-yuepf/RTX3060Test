/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tight_fusion_parameter.h
 * @brief This header file defines tight fusion parameter.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-12-30"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_PARAMETER_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_PARAMETER_H_

#include <holo/obstacle/obstacle_list.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace perception
{
/**
 * @brief all tight fusion parameter
 *
 */
struct TightFusionParameter
{
    using Scalar  = float32_t;
    using Scalar3 = std::array<Scalar, 3U>;
    using Scalar4 = std::array<Scalar, 4U>;
    using bool_t  = holo::bool_t;

    /**
     * @brief EKF state dim
     *
     */
    static const uint8_t STATE_DIM = 9U;
    using ProcessNoiseVar          = std::array<Scalar, STATE_DIM>;

    /**
     * @brief lidar measurement noise variance
     *
     */
    struct LidarMeasurementNoiseVar
    {
        /**
         * @brief Construct a new Lidar Measurement Noise Var object
         *
         */
        LidarMeasurementNoiseVar();
        Scalar x;
        Scalar y;
        Scalar z;
        Scalar length;
        Scalar width;
        Scalar height;
        Scalar yaw;
        Scalar vx;
        Scalar vy;
    };

    /**
     * @brief radar measurement noise variance
     *
     */
    struct RadarMeasurementNoiseVar
    {
        /**
         * @brief Construct a new Radar Measurement Noise Var object
         *
         */
        RadarMeasurementNoiseVar();
        Scalar x;
        Scalar y;
        Scalar vx;
        Scalar vy;
    };

    /**
     * @brief vision measurement noise variance
     *
     */
    struct VisionMeasurementNoiseVar
    {
        /**
         * @brief Construct a new Vision Measurement Noise Var object
         *
         */
        VisionMeasurementNoiseVar();
        Scalar left;    // box2 left coord
        Scalar top;     // box2 top coord
        Scalar right;   // box2 right coord
        Scalar bottom;  // box2 bottom coord
        Scalar x;
        Scalar y;
        Scalar z;
        Scalar length;
        Scalar width;
        Scalar height;
        Scalar yaw;
        Scalar vx;
        Scalar vy;
    };

    /**
     * @brief setup
     *
     * @param config_file config file
     */
    static void Setup(std::string const& config_file);

    /**
     * @brief get a value from yaml node
     *
     * @tparam ScalarType value data type
     * @param node yaml node
     * @param key string
     * @param val value
     */
    template <typename ScalarType>
    static void Get(yaml::Node const& node, std::string const& key, ScalarType& val)
    {
        auto const& tmp = node[key];
        if (tmp.IsDefined())
        {
            val = tmp.as<ScalarType>();
        }
        else
        {
            std::stringstream ss;
            ss << "key: [ " << key << " ] not found";
            throw std::invalid_argument(ss.str().c_str());
        }
    }

    /**
     * @brief get ScalarType array from yaml node
     *
     * @tparam ScalarType scalar type
     * @tparam N array size
     * @param node yaml node
     * @param key key str
     * @param val scalar type array
     */
    template <typename ScalarType, size_t N>
    static void Get(yaml::Node const& node, std::string const& key, std::array<ScalarType, N>& val)
    {
        auto const& tmp = node[key];
        if (tmp.IsDefined())
        {
            if (tmp.size() == val.size())
            {
                for (size_t i = 0U; i < val.size(); ++i)
                {
                    val[i] = tmp[i].as<ScalarType>();
                }
            }
            else
            {
                std::stringstream ss;
                ss << "key: [ " << key << " ]  must have " << val.size() << " entries";
                throw std::invalid_argument(ss.str().c_str());
            }
        }
        else
        {
            std::stringstream ss;
            ss << "key: [ " << key << " ] not found";
            throw std::invalid_argument(ss.str().c_str());
        }
    }

    /**
     * @brief get lidar measurment noise var from yaml node
     *
     * @param node yaml node
     * @param key key str
     * @param val noise var
     */
    static void Get(yaml::Node const& node, std::string const& key, LidarMeasurementNoiseVar& val);

    /**
     * @brief get radar noise var array from yaml node
     *
     * @param node yaml node
     * @param key key str
     * @param val noise var
     */
    static void Get(yaml::Node const& node, std::string const& key, std::array<RadarMeasurementNoiseVar, 5U>& val);

    /**
     * @brief get vision noise var array from yaml node
     *
     * @param node yaml node
     * @param key key str
     * @param val noise var
     */
    static void Get(yaml::Node const& node, std::string const& key, std::array<VisionMeasurementNoiseVar, 5U>& val);

    /**
     * @brief get smart camera noise var from yaml node
     *
     * @param node yaml node
     * @param key key str
     * @param val noise var
     */
    static void Get(yaml::Node const& node, std::string const& key, VisionMeasurementNoiseVar& val);

    static bool_t                                    use_smart_camera;
    static uint32_t                                  fused_obstacle_sensor_id;
    static uint32_t                                  max_cluster_history;
    static Scalar                                    cluster_history_max_lost_time;
    static Scalar                                    max_dx;
    static Scalar                                    max_dy;
    static Scalar                                    max_dvx;
    static Scalar                                    max_dvy;
    static Scalar                                    max_telephoto_dist;
    static Scalar                                    max_side_front_camera_obs_dist;
    static Scalar                                    min_iou;
    static Scalar                                    default_distance;
    static Scalar                                    similarity_weight;
    static Scalar                                    radar_obs_min_exist_score;
    static Scalar                                    uss_obs_min_exist_score;
    static Scalar                                    radar_obs_min_speed;
    static Scalar                                    publish_min_age_time;
    static Scalar                                    max_lost_time;
    static Scalar                                    confirm_time;
    static Scalar                                    confirm_lost_time;
    static Scalar                                    ekf_measurement_filter_max_dx;
    static Scalar                                    ekf_measurement_filter_max_dy;
    static Scalar                                    ekf_measurement_filter_max_dyaw;
    static Scalar                                    overlap_length_dilation_factor;
    static Scalar                                    overlap_width_dilation_factor;
    static Scalar                                    overlap_x_thresh;
    static Scalar                                    overlap_y_thresh;
    static Scalar                                    side_obs_min_x;
    static Scalar                                    side_obs_max_x;
    static Scalar                                    side_obs_min_abs_y;
    static Scalar                                    side_obs_max_abs_y;
    static Scalar3                                   prior_shape_default;
    static Scalar3                                   prior_shape_truck;
    static Scalar3                                   prior_shape_tricyele;
    static Scalar3                                   prior_shape_bicycle;
    static Scalar3                                   prior_shape_pedestrain;
    static Scalar3                                   prior_shape_traffic_cone;
    static ProcessNoiseVar                           process_noise_var;
    static std::array<uint32_t, 5U>                  sensor_id_radars;
    static Scalar4                                   measurement_box2_valid_coord;
    static LidarMeasurementNoiseVar                  measurement_noise_var_lidar;
    static std::array<RadarMeasurementNoiseVar, 5U>  measurement_noise_var_radars;
    static std::array<VisionMeasurementNoiseVar, 5U> measurement_noise_var_visions;
    static VisionMeasurementNoiseVar                 measurement_noise_var_smart_camera;
    static Scalar                                    measurement_track_max_dvx;
    static Scalar                                    track_lidar_min_iou;
    static Scalar                                    track_vision_max_dx;
    static Scalar                                    track_vision_max_dy;
    static Scalar                                    vision_lidar_max_dy;
    static Scalar                                    measurement_track_max_dyaw;
    static Scalar                                    measurement_track_max_dvy;
    static Scalar                                    vision_uss_max_dx;
    static Scalar                                    vision_uss_max_dy;
    static bool_t                                    output_yaw;
    static Scalar                                    max_front_obs_dist;
    static Scalar                                    max_rear_obs_dist;
    static Scalar                                    max_left_obs_dist;
    static Scalar                                    max_right_obs_dist;
    static Scalar                                    max_track_velocity;
    static Scalar                                    max_front_camera_theta;
    static Scalar                                    min_front_camera_theta;
    static Scalar                                    max_front_camera_distance;
};

}  // namespace perception
}  // namespace holo

#endif
