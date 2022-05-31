/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tight_fusion_extended_kalman_filter.h
 * @brief This header file defines tight fusion ekf.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-17"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_EXTENDED_KALMAN_FILTER_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_EXTENDED_KALMAN_FILTER_H_

#include <holo/common/classification.h>
#include <holo/common/timestamp.h>
#include <holo/numerics/matrix.h>
#include <holo/perception/fusion/track.h>
#include <holo/perception/obstacle_fusion/fusion_strategy/strategy.h>
#include <holo/perception/obstacle_fusion/tight_fusion_parameter.h>
#include <holo/perception/utils/impl/camera_group.hpp>
#include <holo/perception/utils/sensor_obstacle_track.h>

namespace holo
{
namespace perception
{
/**
 * @brief tight fusion extended kalman filter
 *
 */
class TightFusionExtendedKalmanFilter : public Track<SensorMeasurementKey, TrackBase, SensorMeasurementKeyHash>
{
public:
    static const uint8_t STATE_DIM = 9U;

public:
    using Base                  = Track<SensorMeasurementKey, TrackBase, SensorMeasurementKeyHash>;
    using Scalar                = float32_t;
    using Scalar3               = std::array<Scalar, 3U>;
    using Scalar4               = std::array<Scalar, 4U>;
    using Classification        = common::Classification;
    using Timestamp             = common::Timestamp;
    using MeasurementMap        = Base::MeasurementMap;
    using Matrix4f              = numerics::Matrix4f;
    using MatrixXf              = numerics::MatrixXf;
    using Vector3f              = numerics::Vector3f;
    using StateVector           = MatrixXf;
    using TransitionMatrix      = MatrixXf;
    using ProcessNoiseVar       = std::array<Scalar, STATE_DIM>;
    using JetType               = Jet<Scalar, 7>;
    using Jet4                  = std::array<JetType, 4U>;
    using JetBox2dMap           = std::unordered_map<uint32_t, Jet4>;  // sensor id -> box2 jet
    using Box2dMap              = std::unordered_map<uint32_t, Scalar4>;
    using CameraGroupPtr        = std::shared_ptr<CameraGroup>;
    using MeasurementFilterRule = std::function<void(MeasurementMap const&, MeasurementMap&)>;  // raw -> filtered
    using MeasurementUpdateRule = std::function<bool_t(MeasurementMap const&)>;

private:
    /**
     * @brief a utility to generate innovation, jacobian and measurement noise cov matrix
     *
     */
    struct Observation
    {
        using JacobianRow = std::array<Scalar, STATE_DIM>;

        /**
         * @brief Construct a new Observation object
         *
         */
        Observation();

        /**
         * @brief append a new observation
         *
         * @param innovation innovation
         * @param jacobian jacobian (1 row)
         * @param variance variance
         */
        void Append(Scalar innovation, JacobianRow const& jacobian, Scalar variance);

        /**
         * @brief append a new observation which directily affect state
         *
         * @param innovation innovation
         * @param pos_in_state position in state vector
         * @param variance variance
         */
        void Append(Scalar innovation, uint8_t pos_in_state, Scalar variance);

        /**
         * @brief append a new observation with jets
         *
         * @param innovation innovation
         * @param jet jet
         * @param variance variance
         */
        void Append(Scalar innovation, JetType const& jet, Scalar variance);

        /**
         * @brief Get the innovation vector, jacobian matrix and noise cov matrix
         *
         * @param innovation_vector innovation vector
         * @param jacobian_matrix jacobian matrix
         * @param noise_covariance measurement noise covariance matrix
         */
        void GetMatrices(MatrixXf& innovation_vector, MatrixXf& jacobian_matrix, MatrixXf& noise_covariance);

    private:
        std::vector<Scalar>      innovation_list;
        std::vector<JacobianRow> jacobian_list;
        std::vector<Scalar>      variance_list;
    };
    using ObservationRule = std::function<void(MeasurementMap const&, Observation&)>;

public:
    /**
     * @brief Construct a new Tight Fusion Extended Kalman Filter object
     *
     * @param camera_group camera group
     * @param timestamp timestamp
     * @param id track id
     * @param props obstacle property
     */
    TightFusionExtendedKalmanFilter(CameraGroupPtr const camera_group, Timestamp const& timestamp, uint32_t id,
                                    ObstaclePropertyType const& props);

    /**
     * @brief Set the Body Transformation from last timestamp to current timestamp
     *
     * @param body_transformation body transformation matrix
     */
    void SetBodyTransformation(Matrix4f const& body_transformation)
    {
        body_transformation_ = body_transformation;
    }

    /**
     * @brief Set the body linear velocity
     *
     * @param vel_body body linear velocity
     */
    void SetVelBody(Vector3f const& vel_body)
    {
        vel_body_ = vel_body;
    }

    /**
     * @brief Set the Angular Velocity object
     *
     * @param angular_velocity body yaw velocity
     */
    void SetAngularVelocity(Scalar angular_velocity)
    {
        angular_velocity_ = angular_velocity;
    }

    /**
     * @brief predict
     *
     * @param current_timestamp current timestamp
     */
    void Predict(Timestamp const& current_timestamp) override;

    /**
     * @brief update
     *
     * @param measurement_map measurement map
     */
    void Update(MeasurementMap const& measurement_map) override;

    /**
     * @brief Set the Valid Flag object
     *
     * @param flag valid flag
     */
    void SetValidFlag(bool_t flag)
    {
        valid_flag_ = flag;
    }

    /**
     * @brief Get the Valid Flag object
     *
     * @return bool_t valid flag
     */
    bool_t GetValidFlag()
    {
        return valid_flag_;
    }

    /**
     * @brief Get the Lost Time object
     *
     * @return Scalar lost time in seconds
     */
    Scalar GetLostTime()
    {
        return static_cast<Scalar>((obstacle_property_.t - last_update_timestamp_).ToSec());
    }

    /**
     * @brief Get the Age Time object
     *
     * @return Scalar age time in seconds
     */
    Scalar GetAgeTime()
    {
        return static_cast<Scalar>((last_update_timestamp_ - start_timestamp_).ToSec());
    }

    /**
     * @brief Get the Predicted Box 2d Map object
     *
     * @return JetBox2dMap const& predicted box2d in jets
     */
    JetBox2dMap const& GetPredictedBox2dMap() const
    {
        return predicted_box2d_map_;
    }

    /**
     * @brief Get the Clipped Box 2d Map object
     *
     * @return Box2dMap const& clipped box2d
     */
    Box2dMap const& GetClippedBox2dMap() const
    {
        return clipped_box2d_map_;
    }

    /**
     * @brief Get the State object
     *
     * @return StateVector const& state
     */
    StateVector const& GetState() const
    {
        return X_;
    }

    /**
     * @brief Get the Last Measurement IOU Map object
     *
     * @return std::unordered_map<SensorMeasurementKey, Scalar, SensorMeasurementKeyHash>& last iou map
     */
    std::unordered_map<SensorMeasurementKey, Scalar, SensorMeasurementKeyHash>& GetLastMeasurementIOUMap()
    {
        return last_measurement_iou_map_;
    }

    /**
     * @brief Get the Debug Info Str object
     *
     * @return std::list<std::string>& debug info str list
     */
    static std::list<std::string>& GetDebugInfoStr()
    {
        return debug_info_str_;
    }

private:
    /**
     * @brief project 3d box to camera
     *
     */
    void projectToCamera();

    /**
     * @brief Set the Obstacle Property object
     *
     */
    void setObstacleProperty();

    /**
     * @brief append measurement filter rules
     *
     */
    void appendMeasurementFilterRules();

    /**
     * @brief append measurement update rules
     *
     */
    void appendMeasurementUpdateRules();

    /**
     * @brief append observation rules
     *
     */
    void appendObservationRules();

private:
    CameraGroupPtr camera_group_;
    Matrix4f       body_transformation_;
    Vector3f       vel_body_;
    Scalar         angular_velocity_;
    Timestamp      last_update_timestamp_;
    Timestamp      start_timestamp_;
    bool_t         valid_flag_;
    JetBox2dMap    predicted_box2d_map_;
    Box2dMap       clipped_box2d_map_;

    std::unordered_map<SensorMeasurementKey, Scalar, SensorMeasurementKeyHash> last_measurement_iou_map_;

    StateVector      X_;
    TransitionMatrix F_;  // transition jacobian
    TransitionMatrix P_;  // covariance estimate
    TransitionMatrix Q_;  // transition covariance

    std::list<MeasurementFilterRule> measurement_filter_rule_list_;
    std::list<MeasurementUpdateRule> measurement_update_rule_list_;
    std::list<ObservationRule>       observation_rule_list_;

    /* debug info */
    static std::list<std::string> debug_info_str_;
};

}  // namespace perception
}  // namespace holo

#endif
