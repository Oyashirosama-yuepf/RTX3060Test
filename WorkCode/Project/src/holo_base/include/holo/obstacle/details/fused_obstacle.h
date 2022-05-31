/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fused_obstacle.h
 * @brief This header file defines FusedObstacleT.
 * @author Zhou Huishuang(zhouhuishuang@holomaitc.com)
 * @date 2019-09-03
 */

#ifndef HOLO_OBSTACLE_DETAILS_FUSED_OBSTACLE_H_
#define HOLO_OBSTACLE_DETAILS_FUSED_OBSTACLE_H_

#include <holo/common/classification.h>
#include <holo/common/sensor_id.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/geometry/box3.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace gh02
{    
namespace obstacle
{
namespace details
{
/**
 * @brief Obstacle general2 type
 *
 * @tparam T obstacle type, only support float32_t and float64_t
 * @tparam SIZE path_points attribute vector size in PredictPath type
 * predict_paths, polygon attribute vector size in Obstacle general2 type
 */
template <typename T, size_t SIZE = 256U>
class FusedObstacleT
{
public:
    using ScalarType = T;
    using Point2Type = holo::geometry::Point2T<ScalarType>;
    using Point3Type = holo::geometry::Point3T<ScalarType>;

    /**
     * @brief Define vehicle lamp status types
     */
    enum class LampStatus : uint8_t
    {
        NONE         = 0U,
        LEFT_TURN    = 1U,
        RIGHT_TURN   = 2U,
        DOUBLE_FLASH = 3U,
        BRAKE        = 4U,
        BACKING_UP   = 5U,
        HEADLAMP     = 6U,
    };

    /**
     * @brief Define obstacle moving status types
     */
    enum class MovingStatus : uint8_t
    {
        STATIC = 0U,
        MOVING = 1U,
    };

    /**
     * @brief Define obstacle tracking status types
     */
    enum class TrackingStatus : uint8_t
    {
        INVALID = 0U,
        NEW     = 1U,
        UPDATED = 2U,
        COASTED = 3U,
    };

    /**
     * @brief Define cut in status types
     */
    enum class CutInStatus : uint8_t
    {
        UNKNOWN = 0U,
        CUT_IN  = 1U,
        CUT_OUT = 2U,
        INVALID = 3U,
    };

    /**
     * @brief Define sources of information
     */
    struct HistoryInfo
    {
        HistoryInfo()
          : sensor_id{}
          , obstacle_id{}
          , raw_sensor_capture_timestamp{}
          , sensor_perception_capture_timestamp{}
          , sensor_perception_output_timestamp{}
          , fusion_capture_timestamp{}
          , fusion_output_timestamp{} {};

        template <size_t ALIGN = 4U>
        size_t GetSerializedSize() const noexcept
        {
            return holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(sensor_id), obstacle_id) +
                   raw_sensor_capture_timestamp.GetSerializedSize<ALIGN>() +
                   sensor_perception_capture_timestamp.GetSerializedSize<ALIGN>() +
                   sensor_perception_output_timestamp.GetSerializedSize<ALIGN>() +
                   fusion_capture_timestamp.GetSerializedSize<ALIGN>() +
                   fusion_output_timestamp.GetSerializedSize<ALIGN>();
        }

        template <typename S>
        void Serialize(S& serializer) const
        {
            serializer << holo::serialization::align << static_cast<uint32_t>(sensor_id) << obstacle_id
                       << raw_sensor_capture_timestamp << sensor_perception_capture_timestamp
                       << sensor_perception_output_timestamp << fusion_capture_timestamp << fusion_output_timestamp;
        }

        template <typename D>
        void Deserialize(D& deserializer)
        {
            uint32_t sensor_id_temp = 0U;
            deserializer >> holo::serialization::align >> sensor_id_temp >> obstacle_id >>
                raw_sensor_capture_timestamp >> sensor_perception_capture_timestamp >>
                sensor_perception_output_timestamp >> fusion_capture_timestamp >> fusion_output_timestamp;
            sensor_id = static_cast<holo::common::SensorId>(sensor_id_temp);
        }

        holo::common::SensorId  sensor_id;
        uint32_t                obstacle_id;
        holo::common::Timestamp raw_sensor_capture_timestamp;
        holo::common::Timestamp sensor_perception_capture_timestamp;
        holo::common::Timestamp sensor_perception_output_timestamp;
        holo::common::Timestamp fusion_capture_timestamp;
        holo::common::Timestamp fusion_output_timestamp;
    };

    /**
     * @brief predict path type
     */
    class PredictPath
    {
    public:
        struct PathPoint
        {
            PathPoint() : timestamp{}, position{}, heading_angle{}, velocity{} {};

            template <size_t ALIGN = 4U>
            size_t GetSerializedSize() const noexcept
            {
                return timestamp.GetSerializedSize<ALIGN>() + position.template GetSerializedSize<ALIGN>() +
                       holo::serialization::SerializedSize<ALIGN>(heading_angle) +
                       velocity.template GetSerializedSize<ALIGN>();
            }

            template <typename S>
            void Serialize(S& serializer) const
            {
                serializer << timestamp << position << heading_angle << velocity;
            }

            template <typename D>
            void Deserialize(D& deserializer)
            {
                deserializer >> timestamp >> position >> heading_angle >> velocity;
            }

            holo::common::Timestamp timestamp;
            Point2Type              position;
            float32_t               heading_angle;
            Point2Type              velocity;
        };

        PredictPath() : confidence_{1}, path_points_{} {};

        /**
         * @brief Get confidence
         *
         * @return confidence
         */
        float32_t GetConfidence() const noexcept
        {
            return confidence_;
        }

        /**
         * @brief Set confidence
         *
         * @param confidence
         */
        void SetConfidence(float32_t const confidence) noexcept
        {
            confidence_ = confidence;
        }

        /**
         * @brief Get path points
         *
         * @return Reference of path points
         */
        holo::container::Vector<PathPoint, SIZE>& GetPathPoints() noexcept
        {
            return path_points_;
        }

        /**
         * @brief Get path points
         *
         * @return Const reference of path points
         */
        holo::container::Vector<PathPoint, SIZE> const& GetPathPoints() const noexcept
        {
            return path_points_;
        }

        /**
         * @brief Set path points
         *
         * @param path_points
         */
        void SetPathPoints(holo::container::Vector<PathPoint, SIZE> const& path_points) noexcept
        {
            path_points_ = path_points;
        }

        template <size_t ALIGN = 4U>
        size_t GetSerializedSize() const noexcept
        {
            return holo::serialization::SerializedSize<ALIGN>(confidence_) +
                   path_points_.template GetSerializedSize<ALIGN>();
        }

        template <typename S>
        void Serialize(S& serializer) const
        {
            serializer << holo::serialization::align << confidence_ << path_points_;
        }

        template <typename D>
        void Deserialize(D& deserializer)
        {
            deserializer >> holo::serialization::align >> confidence_ >> path_points_;
        }

    private:
        float32_t                                confidence_;
        holo::container::Vector<PathPoint, SIZE> path_points_;
    };

    /**
     * @brief Default constructor
     */
    FusedObstacleT() noexcept
      : history_info_{}
      , obstacle_id_{0}
      , classification_()
      , confidence_{0}
      , exist_confidence_{0}
      , classification_confidence_{0}
      , position_{}
      , absolute_velocity_{}
      , relative_velocity_{}
      , absolute_accelaration_{}
      , heading_angle_{0}
      , heading_angular_velocity_{0}
      , bbox3d_width_{0}
      , bbox3d_height_{0}
      , bbox3d_depth_{0}
      , position_cov_{}
      , velocity_cov_{}
      , accelaration_cov_{}
      , obstacle_size_cov_{}
      , heading_angle_std_{}
      , tracking_period_{0}
      , is_movable_{false}
      , is_heading_to_ego_car_{false}
      , is_ever_heading_to_ego_car_{false}
      , lamp_status_{LampStatus::NONE}
      , tracking_status_{TrackingStatus::INVALID}
      , cut_in_status_{CutInStatus::UNKNOWN}
      , moving_status_{MovingStatus::STATIC}
      , predict_paths_{}
      , polygon_{}
    {
    }

    /**
     * @brief Get history info
     *
     * @return Reference of history info
     */
    holo::container::Vector<HistoryInfo, 32U>& GetHistoryInfo() noexcept
    {
        return history_info_;
    }

    /**
     * @brief Get history info
     *
     * @return Const reference of history info
     */
    holo::container::Vector<HistoryInfo, 32U> const& GetHistoryInfo() const noexcept
    {
        return history_info_;
    }

    /**
     * @brief Set history info
     *
     * @param history_info
     */
    void SetHistoryInfo(holo::container::Vector<HistoryInfo, 32U> const& history_info) noexcept
    {
        history_info_ = history_info;
    }

    /**
     * @brief Get obstacle id
     *
     * @return obstacle id
     */
    uint32_t GetObstacleId() const noexcept
    {
        return obstacle_id_;
    }

    /**
     * @brief Set obstacle id
     *
     * @param obstacle_id
     */
    void SetObstacleId(uint32_t const obstacle_id) noexcept
    {
        obstacle_id_ = obstacle_id;
    }

    /**
     * @brief Get obstacle classification
     *
     * @return classification of obstacle
     */
    Classification GetClassification() const noexcept
    {
        return classification_;
    }

    /**
     * @brief Set obstacle classfication
     *
     * @param classification classification of obstacle
     */
    void SetClassification(Classification const& classification) noexcept
    {
        classification_ = classification;
    }

    /**
     * @brief Get confidence
     *
     * @return confidence
     */
    float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    /**
     * @brief Set confidence
     *
     * @param confidence
     */
    void SetConfidence(float32_t const confidence) noexcept
    {
        confidence_ = confidence;
    }

    /**
     * @brief Get obstacle exist confidence
     *
     * @return exist confidence
     */
    float32_t GetExistConfidence() const noexcept
    {
        return exist_confidence_;
    }

    /**
     * @brief Set obstacle exist confidence
     *
     * @param exist_confidence
     */
    void SetExistConfidence(float32_t const exist_confidence) noexcept
    {
        exist_confidence_ = exist_confidence;
    }

    /**
     * @brief Get classification confidence
     *
     * @return classification confidence
     */
    float32_t GetClassificationConfidence() const noexcept
    {
        return classification_confidence_;
    }

    /**
     * @brief Set classification confidence
     *
     * @param confidence
     */
    void SetClassificationConfidence(float32_t const confidence) noexcept
    {
        classification_confidence_ = confidence;
    }

    /**
     * @brief Get target position of central geometric point
     *
     * @return Reference of position
     */
    Point3Type& GetPosition() noexcept
    {
        return position_;
    }

    /**
     * @brief Get target position of central geometric point
     *
     * @return Const reference of position
     */
    Point3Type const& GetPosition() const noexcept
    {
        return position_;
    }

    /**
     * @brief Set target position of central geometric point
     *
     * @param position
     */
    void SetPosition(Point3Type const& position) noexcept
    {
        position_ = position;
    }

    /**
     * @brief Get absolute velocity
     *
     * @return Reference of absolute velocity
     */
    Point3Type& GetAbsoluteVelocity() noexcept
    {
        return absolute_velocity_;
    }

    /**
     * @brief Get absolute velocity
     *
     * @return Const reference of absolute velocity
     */
    Point3Type const& GetAbsoluteVelocity() const noexcept
    {
        return absolute_velocity_;
    }

    /**
     * @brief get angular velocity which template OutputType
     *
     * @return template OutputType
     */
    template <typename OutputType>
    OutputType GetAbsoluteVelocity() const noexcept
    {
        return OutputType{absolute_velocity_[0U], absolute_velocity_[1U], absolute_velocity_[2U]};
    }

    /**
     * @brief Set absolute velocity
     *
     * @param absolute_velocity
     */
    void SetAbsoluteVelocity(Point3Type const& absolute_velocity) noexcept
    {
        absolute_velocity_ = absolute_velocity;
    }

    /**
     * @brief set absolute velocity which ScalarType x, y, z
     *
     * @param x,y,z
     */
    void SetAbsoluteVelocity(ScalarType x, ScalarType y, ScalarType z) noexcept
    {
        absolute_velocity_[0U] = x;
        absolute_velocity_[1U] = y;
        absolute_velocity_[2U] = z;
    }

    /**
     * @brief Get relative velocity
     *
     * @return Reference of relative velocity
     */
    Point3Type& GetRelativeVelocity() noexcept
    {
        return relative_velocity_;
    }

    /**
     * @brief Get relative velocity
     *
     * @return Const reference of relative velocity
     */
    Point3Type const& GetRelativeVelocity() const noexcept
    {
        return relative_velocity_;
    }

    /**
     * @brief get relative velocity which template OutputType
     *
     * @return template OutputType
     */
    template <typename OutputType>
    OutputType GetRelativeVelocity() const noexcept
    {
        return OutputType{relative_velocity_[0U], relative_velocity_[1U], relative_velocity_[2U]};
    }

    /**
     * @brief Set relative velocity
     *
     * @param relative_velocity
     */
    void SetRelativeVelocity(Point3Type const& relative_velocity) noexcept
    {
        relative_velocity_ = relative_velocity;
    }

    /**
     * @brief set relative velocity which ScalarType x, y, z
     *
     * @param x,y,z
     */
    void SetRelativeVelocity(ScalarType x, ScalarType y, ScalarType z) noexcept
    {
        relative_velocity_[0U] = x;
        relative_velocity_[1U] = y;
        relative_velocity_[2U] = z;
    }

    /**
     * @brief Get absolute accelaration
     *
     * @return Reference of absolute accelaration
     */
    Point3Type& GetAbsoluteAccelaration() noexcept
    {
        return absolute_accelaration_;
    }

    /**
     * @brief Get absolute accelaration
     *
     * @return Const reference of absolute accelaration
     */
    Point3Type const& GetAbsoluteAccelaration() const noexcept
    {
        return absolute_accelaration_;
    }

    /**
     * @brief get absolute accelaration which template OutputType
     *
     * @return template OutputType
     */
    template <typename OutputType>
    OutputType GetAbsoluteAccelaration() const noexcept
    {
        return OutputType{absolute_accelaration_[0U], absolute_accelaration_[1U], absolute_accelaration_[2U]};
    }

    /**
     * @brief Set absolute accelaration
     *
     * @param absolute_accelaration
     */
    void SetAbsoluteAccelaration(Point3Type const& absolute_accelaration) noexcept
    {
        absolute_accelaration_ = absolute_accelaration;
    }

    /**
     * @brief set absolute accelaration which ScalarType x, y, z
     *
     * @param x,y,z
     */
    void SetAbsoluteAccelaration(ScalarType x, ScalarType y, ScalarType z) noexcept
    {
        absolute_accelaration_[0U] = x;
        absolute_accelaration_[1U] = y;
        absolute_accelaration_[2U] = z;
    }

    /**
     * @brief Get heading angle
     *
     * @return heading angle
     */
    float32_t GetHeadingAngle() const noexcept
    {
        return heading_angle_;
    }

    /**
     * @brief Set heading angle
     *
     * @param heading_angle
     */
    void SetHeadingAngle(float32_t const heading_angle) noexcept
    {
        heading_angle_ = heading_angle;
    }

    /**
     * @brief Get heading angular velocity
     *
     * @return heading angular velocity
     */
    float32_t GetHeadingAngularVelocity() const noexcept
    {
        return heading_angular_velocity_;
    }

    /**
     * @brief Set heading angular velocity
     *
     * @param heading_angular_velocity
     */
    void SetHeadingAngularVelocity(float32_t const heading_angular_velocity) noexcept
    {
        heading_angular_velocity_ = heading_angular_velocity;
    }

    /**
     * @brief Get bbox3d width
     *
     * @return bbox3d width
     */
    float32_t GetBbox3dWidth() const noexcept
    {
        return bbox3d_width_;
    }

    /**
     * @brief Set bbox3d width
     *
     * @param bbox3d_width
     */
    void SetBbox3dWidth(float32_t const bbox3d_width) noexcept
    {
        bbox3d_width_ = bbox3d_width;
    }

    /**
     * @brief Get bbox3d height
     *
     * @return bbox3d height
     */
    float32_t GetBbox3dHeight() const noexcept
    {
        return bbox3d_height_;
    }

    /**
     * @brief Set bbox3d height
     *
     * @param bbox3d_height
     */
    void SetBbox3dHeight(float32_t const bbox3d_height) noexcept
    {
        bbox3d_height_ = bbox3d_height;
    }

    /**
     * @brief Get bbox3d depth
     *
     * @return bbox3d depth
     */
    float32_t GetBbox3dDepth() const noexcept
    {
        return bbox3d_depth_;
    }

    /**
     * @brief Set bbox3d depth
     *
     * @param bbox3d_depth
     */
    void SetBbox3dDepth(float32_t const bbox3d_depth) noexcept
    {
        bbox3d_depth_ = bbox3d_depth;
    }

    /**
     * @brief Get position covariance
     *
     * @return Reference of position covariance
     */
    std::array<std::array<ScalarType, 3U>, 3U>& GetPositionCov() noexcept
    {
        return position_cov_;
    }

    /**
     * @brief Get position covariance
     *
     * @return Const reference of position covariance
     */
    std::array<std::array<ScalarType, 3U>, 3U> const& GetPositionCov() const noexcept
    {
        return position_cov_;
    }

    /**
     * @brief Set position covariance
     *
     * @param position_cov
     */
    void SetPositionCov(std::array<std::array<ScalarType, 3U>, 3U> const& position_cov) noexcept
    {
        position_cov_ = position_cov;
    }

    /**
     * @brief Get velocity covariance
     *
     * @return Reference of velocity covariance
     */
    std::array<std::array<ScalarType, 3U>, 3U>& GetvelocityCov() noexcept
    {
        return velocity_cov_;
    }

    /**
     * @brief Get velocity covariance
     *
     * @return Const reference of velocity covariance
     */
    std::array<std::array<ScalarType, 3U>, 3U> const& GetvelocityCov() const noexcept
    {
        return velocity_cov_;
    }

    /**
     * @brief Set velocity covariance
     *
     * @param velocity_cov
     */
    void SetvelocityCov(std::array<std::array<ScalarType, 3U>, 3U> const& velocity_cov) noexcept
    {
        velocity_cov_ = velocity_cov;
    }

    /**
     * @brief Get accelaration covariance
     *
     * @return Reference of accelaration covariance
     */
    std::array<std::array<ScalarType, 3U>, 3U>& GetAccelarationCov() noexcept
    {
        return accelaration_cov_;
    }

    /**
     * @brief Get accelaration covariance
     *
     * @return Const reference of accelaration covariance
     */
    std::array<std::array<ScalarType, 3U>, 3U> const& GetAccelarationCov() const noexcept
    {
        return accelaration_cov_;
    }

    /**
     * @brief Set accelaration covariance
     *
     * @param accelaration_cov
     */
    void SetAccelarationCov(std::array<std::array<ScalarType, 3U>, 3U> const& accelaration_cov) noexcept
    {
        accelaration_cov_ = accelaration_cov;
    }

    /**
     * @brief Get obstacle size covariance
     *
     * @return Reference of size covariance
     */
    std::array<std::array<ScalarType, 3U>, 3U>& GetSizeCov() noexcept
    {
        return obstacle_size_cov_;
    }

    /**
     * @brief Get obstacle size covariance
     *
     * @return Const reference of size covariance
     */
    std::array<std::array<ScalarType, 3U>, 3U> const& GetSizeCov() const noexcept
    {
        return obstacle_size_cov_;
    }

    /**
     * @brief Set obstacle size covariance
     *
     * @param obstacle_size_cov
     */
    void SetSizeCov(std::array<std::array<ScalarType, 3U>, 3U> const& obstacle_size_cov) noexcept
    {
        obstacle_size_cov_ = obstacle_size_cov;
    }

    /**
     * @brief Get standard deviation of heading angle
     *
     * @return heading angle std
     */
    float32_t GetHeadingAngleStd() const noexcept
    {
        return heading_angle_std_;
    }

    /**
     * @brief Set standard deviation of heading angle
     *
     * @param heading_angle_std
     */
    void SetHeadingAngleStd(float32_t const heading_angle_std) noexcept
    {
        heading_angle_std_ = heading_angle_std;
    }

    /**
     * @brief Get tracking period
     *
     * @return tracking period
     */
    float32_t GetTrackingPeriod() const noexcept
    {
        return tracking_period_;
    }

    /**
     * @brief Set tracking period
     *
     * @param tracking_period
     */
    void SetTrackingPeriod(float32_t const tracking_period) noexcept
    {
        tracking_period_ = tracking_period;
    }

    /**
     * @brief Get movable status
     *
     * @return movable status
     */
    bool_t IsMovable() const noexcept
    {
        return is_movable_;
    }

    /**
     * @brief Set movable status
     *
     * @param status movable status
     */
    void SetMovableStatus(bool_t const status) noexcept
    {
        is_movable_ = status;
    }

    /**
     * @brief Get heading to ego car status
     *
     * @return status
     */
    bool_t IsHeadingToEgoCar() const noexcept
    {
        return is_heading_to_ego_car_;
    }

    /**
     * @brief Set heading to ego car status
     *
     * @param status heading to ego car status
     */
    void SetHeadingToEgoCarStatus(bool_t const status) noexcept
    {
        is_heading_to_ego_car_ = status;
    }

    /**
     * @brief Get ever heading to ego car status
     *
     * @return status
     */
    bool_t IsEverHeadingToEgoCar() const noexcept
    {
        return is_ever_heading_to_ego_car_;
    }

    /**
     * @brief Set ever heading to ego car status
     *
     * @param status ever heading to ego car status
     */
    void SetEverHeadingToEgoCarStatus(bool_t const status) noexcept
    {
        is_ever_heading_to_ego_car_ = status;
    }

    /**
     * @brief Get lamp status
     *
     * @return lamp status
     */
    LampStatus GetLampStatus() const noexcept
    {
        return lamp_status_;
    }

    /**
     * @brief Set lamp status
     *
     * @param lamp_status
     */
    void SetLampStatus(LampStatus const lamp_status) noexcept
    {
        lamp_status_ = lamp_status;
    }

    /**
     * @brief Get tracking status
     *
     * @return tracking status
     */
    TrackingStatus GetTrackingStatus() const noexcept
    {
        return tracking_status_;
    }

    /**
     * @brief Set tracking status
     *
     * @param tracking_status
     */
    void SetTrackingStatus(TrackingStatus const tracking_status) noexcept
    {
        tracking_status_ = tracking_status;
    }

    /**
     * @brief Get cut in status
     *
     * @return cut in status
     */
    CutInStatus GetCutInStatus() const noexcept
    {
        return cut_in_status_;
    }

    /**
     * @brief Set cut in status
     *
     * @param cut_in_status
     */
    void SetCutInStatus(CutInStatus const cut_in_status) noexcept
    {
        cut_in_status_ = cut_in_status;
    }

    /**
     * @brief Get moving status
     *
     * @return moving status
     */
    MovingStatus GetMovingStatus() const noexcept
    {
        return moving_status_;
    }

    /**
     * @brief Set moving status
     *
     * @param moving_status
     */
    void SetMovingStatus(MovingStatus const moving_status) noexcept
    {
        moving_status_ = moving_status;
    }

    /**
     * @brief Get predict path
     *
     * @return Reference of predict path
     */
    holo::container::Vector<PredictPath, SIZE>& GetPredictPath() noexcept
    {
        return predict_paths_;
    }

    /**
     * @brief Get predict path
     *
     * @return Const reference of predict path
     */
    holo::container::Vector<PredictPath, SIZE> const& GetPredictPath() const noexcept
    {
        return predict_paths_;
    }

    /**
     * @brief Set predict path
     *
     * @param predict_path
     */
    void SetPredictPath(holo::container::Vector<PredictPath, SIZE> const& predict_path) noexcept
    {
        predict_paths_ = predict_path;
    }

    /**
     * @brief Get polygon
     *
     * @return reference of polygon
     */
    holo::container::Vector<Point3Type, SIZE>& Getpolygon() noexcept
    {
        return polygon_;
    }

    /**
     * @brief Get polygon
     *
     * @return Const reference of polygon
     */
    holo::container::Vector<Point3Type, SIZE> const& Getpolygon() const noexcept
    {
        return polygon_;
    }

    /**
     * @brief Set polygon
     *
     * @param polygon
     */
    void Setpolygon(holo::container::Vector<Point3Type, SIZE> const& polygon) noexcept
    {
        polygon_ = polygon;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return history_info_.template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(obstacle_id_, static_cast<uint32_t>(classification_),
                                                          confidence_, exist_confidence_, classification_confidence_) +
               position_.template GetSerializedSize<ALIGN>() + absolute_velocity_.template GetSerializedSize<ALIGN>() +
               relative_velocity_.template GetSerializedSize<ALIGN>() +
               absolute_accelaration_.template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(
                   heading_angle_, heading_angular_velocity_, bbox3d_width_, bbox3d_height_, bbox3d_depth_,
                   heading_angle_std_, tracking_period_, is_movable_, is_heading_to_ego_car_,
                   is_ever_heading_to_ego_car_, static_cast<uint8_t>(lamp_status_),
                   static_cast<uint8_t>(tracking_status_), static_cast<uint8_t>(cut_in_status_),
                   static_cast<uint8_t>(moving_status_)) +
               predict_paths_.template GetSerializedSize<ALIGN>() + polygon_.template GetSerializedSize<ALIGN>() +
               holo::serialization::AlignedSize<ALIGN>(
                   36U * sizeof(ScalarType));  ///< position_cov + velocity_cov + accelaration_cov + obstacle_size_cov
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << history_info_ << obstacle_id_ << static_cast<uint32_t>(classification_) << confidence_
                   << exist_confidence_ << classification_confidence_ << position_ << absolute_velocity_
                   << relative_velocity_ << absolute_accelaration_ << heading_angle_ << heading_angular_velocity_
                   << bbox3d_width_ << bbox3d_height_ << bbox3d_depth_ << heading_angle_std_ << tracking_period_
                   << is_movable_ << is_heading_to_ego_car_ << is_ever_heading_to_ego_car_
                   << static_cast<uint8_t>(lamp_status_) << static_cast<uint8_t>(tracking_status_)
                   << static_cast<uint8_t>(cut_in_status_) << static_cast<uint8_t>(moving_status_) << predict_paths_
                   << polygon_;

        for (size_t i = 0; i < 3U; i++)
        {
            for (size_t j = 0; j < 3U; j++)
            {
                serializer << position_cov_[i][j];
            }
        }

        for (size_t i = 0; i < 3U; i++)
        {
            for (size_t j = 0; j < 3U; j++)
            {
                serializer << velocity_cov_[i][j];
            }
        }

        for (size_t i = 0; i < 3U; i++)
        {
            for (size_t j = 0; j < 3U; j++)
            {
                serializer << accelaration_cov_[i][j];
            }
        }

        for (size_t i = 0; i < 3U; i++)
        {
            for (size_t j = 0; j < 3U; j++)
            {
                serializer << obstacle_size_cov_[i][j];
            }
        }

        serializer << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint8_t  lamp_status     = 0U;
        uint8_t  moving_status   = 0U;
        uint8_t  tracking_status = 0U;
        uint8_t  cut_in_status   = 0U;
        uint32_t classification  = 0;

        deserializer >> history_info_ >> obstacle_id_ >> classification >> confidence_ >> exist_confidence_ >>
            classification_confidence_ >> position_ >> absolute_velocity_ >> relative_velocity_ >>
            absolute_accelaration_ >> heading_angle_ >> heading_angular_velocity_ >> bbox3d_width_ >> bbox3d_height_ >>
            bbox3d_depth_ >> heading_angle_std_ >> tracking_period_ >> is_movable_ >> is_heading_to_ego_car_ >>
            is_ever_heading_to_ego_car_ >> lamp_status >> tracking_status >> cut_in_status >> moving_status >>
            predict_paths_ >> polygon_;

        for (size_t i = 0; i < 3U; i++)
        {
            for (size_t j = 0; j < 3U; j++)
            {
                deserializer >> position_cov_[i][j];
            }
        }

        for (size_t i = 0; i < 3U; i++)
        {
            for (size_t j = 0; j < 3U; j++)
            {
                deserializer >> velocity_cov_[i][j];
            }
        }

        for (size_t i = 0; i < 3U; i++)
        {
            for (size_t j = 0; j < 3U; j++)
            {
                deserializer >> accelaration_cov_[i][j];
            }
        }

        for (size_t i = 0; i < 3U; i++)
        {
            for (size_t j = 0; j < 3U; j++)
            {
                deserializer >> obstacle_size_cov_[i][j];
            }
        }

        deserializer >> holo::serialization::align;

        lamp_status_     = static_cast<LampStatus>(lamp_status);
        moving_status_   = static_cast<MovingStatus>(moving_status);
        tracking_status_ = static_cast<TrackingStatus>(tracking_status);
        cut_in_status_   = static_cast<CutInStatus>(cut_in_status);
        classification_  = static_cast<Classification>(classification);
    }

private:
    holo::container::Vector<HistoryInfo, 32U> history_info_;  ///< information about the source of the current element
    uint32_t                                  obstacle_id_;
    Classification                            classification_;
    float32_t                                 confidence_;        ///< total confidence
    float32_t                                 exist_confidence_;  ///< obstacle exist confidence
    uint32_t                                  classification_confidence_;
    Point3Type                                position_;            /// vehicle coordinate system, position is geometric
                                                                    /// center point of target
    Point3Type                                 absolute_velocity_;  ///< velocity relative to the ground
    Point3Type                                 relative_velocity_;
    Point3Type                                 absolute_accelaration_;
    float32_t                                  heading_angle_;
    float32_t                                  heading_angular_velocity_;
    float32_t                                  bbox3d_width_;
    float32_t                                  bbox3d_height_;
    float32_t                                  bbox3d_depth_;
    std::array<std::array<ScalarType, 3U>, 3U> position_cov_;       ///< position covariance
    std::array<std::array<ScalarType, 3U>, 3U> velocity_cov_;       ///< velocity covariance
    std::array<std::array<ScalarType, 3U>, 3U> accelaration_cov_;   ///< accelaration covariance
    std::array<std::array<ScalarType, 3U>, 3U> obstacle_size_cov_;  ///< obstacle size covariance
    float32_t                                  heading_angle_std_;  ///< standard deviation of heading angle
    float32_t                                  tracking_period_;
    bool_t                                     is_movable_;
    bool_t                                     is_heading_to_ego_car_;
    bool_t                                     is_ever_heading_to_ego_car_;
    LampStatus                                 lamp_status_;
    TrackingStatus                             tracking_status_;
    CutInStatus                                cut_in_status_;
    MovingStatus                               moving_status_;
    holo::container::Vector<PredictPath, SIZE> predict_paths_;
    holo::container::Vector<Point3Type, SIZE>  polygon_;
};

}  // namespace details
}  // namespace obstacle
}  // namespace gh02
}  // namespace holo

#endif
