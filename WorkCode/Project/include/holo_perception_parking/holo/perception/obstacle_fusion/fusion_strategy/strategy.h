/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file strategy.h
 * @brief This header file defines .
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-12-24"
 */

#ifndef HOLO_PERCEPTION_URBAN_FUSION_STRATEGY_STRATEGY_H_
#define HOLO_PERCEPTION_URBAN_FUSION_STRATEGY_STRATEGY_H_

#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/fusion/track_base.h>
#include <holo/perception/obstacle_fusion/tight_fusion_parameter.h>
#include <holo/perception/utils/obstacle_property.h>

namespace holo
{
namespace perception
{
/**
 * @brief a static class contains common strategies
 *
 */
class Strategy
{
public:
    using Scalar       = float32_t;
    using Scalar3      = std::array<Scalar, 3U>;
    using Scalar4      = std::array<Scalar, 4U>;
    using VisionObsPtr = std::shared_ptr<obstacle::ObstacleVisionT<Scalar>>;
    using Box2dMap     = std::unordered_map<uint32_t, std::array<Scalar, 4U>>;

    /**
     * @brief Get the Prior Shape object
     *
     * @param cls classification
     * @return Scalar3 [length, width, height]
     */
    static Scalar3 GetPriorShape(common::Classification const& cls);

    /**
     * @brief determine if the obs is a smart camera obs
     *
     * @param obs obs
     * @return bool_t true if it is a smart camera obs
     */
    static bool_t IsSmartCameraObs(VisionObsPtr const obs);

    /**
     * @brief determine if the sensor id belongs to smart camera
     *
     * @param sid sensor id
     * @return bool_t true if it is a smart camera sensor id
     */
    static bool_t IsSmartCameraSensorId(common::SensorId const sid);

    /**
     * @brief compute iou of box2
     *
     * @param lhs scalar4
     * @param rhs scalar4
     * @return Scalar iou
     */
    static Scalar ComputeIOU(Scalar4 const& lhs, Scalar4 const& rhs);

    /**
     * @brief determine if box2d map are compatible
     *
     * @param lhs_box2d_map box2d map
     * @param rhs_box2d_map box2d map
     * @param need_same_image bool
     * @return bool_t true if they are compatible
     */
    static bool_t IsBox2dCompatible(Box2dMap const& lhs_box2d_map, Box2dMap const& rhs_box2d_map,
                                    bool_t need_same_image);

    /**
     * @brief determine if classifications are compatible
     *
     * @param lhs obstacle property
     * @param rhs obstacle property
     * @return bool_t true if compatible
     */
    static bool_t IsClassificationCompatible(ObstacleProperty<Scalar> const& lhs, ObstacleProperty<Scalar> const& rhs);

    /**
     * @brief determine if positions are compatible
     *
     * @param lhs obstacle property
     * @param rhs obstacle property
     * @return bool_t true if compatible
     */
    static bool_t IsPositionCompatible(ObstacleProperty<Scalar> const& lhs, ObstacleProperty<Scalar> const& rhs);

    /**
     * @brief determine if position and velocity are compatible
     *
     * @param lhs obstacle property
     * @param rhs obstacle property
     * @return bool_t true if compatible
     */
    static bool_t IsPositionVelocityCompatible(ObstacleProperty<Scalar> const& lhs,
                                               ObstacleProperty<Scalar> const& rhs);

    /**
     * @brief Get the Absolute Vx object
     *
     * @param relative_vx obs's relative velocity of x
     * @param body_vx body's velocity of x
     * @param y obs's y coordinate in body frame
     * @param angular_velocity body's yaw velocity
     * @return Scalar obs's absolute velocity of x
     */
    static Scalar GetAbsoluteVx(Scalar relative_vx, Scalar body_vx, Scalar y, Scalar angular_velocity);

    /**
     * @brief Get the Absolute Vy object
     *
     * @param relative_vy obs's relative velocity of y
     * @param body_vy body's velocity of y
     * @param x obs's x coordinate in body frame
     * @param angular_velocity body's yaw velocity
     * @return Scalar obs's absolute velocity of y
     */
    static Scalar GetAbsoluteVy(Scalar relative_vy, Scalar body_vy, Scalar x, Scalar angular_velocity);

    /**
     * @brief determine if the obs is side obs
     *
     * @param obs obstacle property
     * @return bool_t true if it is a side obs
     */
    static bool_t IsSideObs(ObstacleProperty<Scalar> const& obs);

    /**
     * @brief determine if two obs's rectangle in bev is overlap
     *
     * @param lhs obstacle property
     * @param rhs obstacle property
     * @param length_dilation_factor length dilation factor
     * @param width_dilation_factor width dilation factor
     * @param x_thresh x threshold
     * @param y_thresh y threshold
     * @return bool_t true if they are overlap
     */
    static bool_t IsOverlap(ObstacleProperty<Scalar> const& lhs, ObstacleProperty<Scalar> const& rhs,
                            Scalar length_dilation_factor = 1.0f, Scalar width_dilation_factor = 1.0f,
                            Scalar x_thresh = 0.0f, Scalar y_thresh = 0.0f);

    /**
     * @brief judge whether one is telephoto, another is non camera osbtacle(include smart camera)
     *
     * @param lhs_sensor_id sensor id of lhs
     * @param lhs_cls track type of lhs
     * @param rhs_sensor_id sensor id of rhs
     * @param rhs_cls track type of rhs
     * @param telephoto_sensor_id telephoto sensor id
     * @return bool_t true one is telephoto, another is non camera osbtacle else false
     */
    static bool_t IsTelePhotoAndNonCamera(const common::SensorId& lhs_sensor_id, const TrackType& lhs_cls,
                                          const common::SensorId& rhs_sensor_id, const TrackType& rhs_cls,
                                          Scalar telephoto_sensor_id);
};

}  // namespace perception
}  // namespace holo

#endif
