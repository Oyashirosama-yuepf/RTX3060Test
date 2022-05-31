/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file state_estimate.h
 * @brief This header file defines .
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2021-06-08"
 */

#ifndef HOLO_PERCEPTION_3D_APP_STATE_ESTIMATE_H_
#define HOLO_PERCEPTION_3D_APP_STATE_ESTIMATE_H_

#include <holo/core/types.h>
#include <holo/geometry/pose3.h>
#include <holo/log/hololog.h>
#include <holo/perception/common/box_object.h>
#include <holo/perception/factor_graph/estimator.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <list>
#include <memory>
#include <unordered_map>

namespace holo
{
namespace perception
{
/**
 * @addtogroup factor_graph
 *
 * @{
 */

/**
 * @brief This class defines a method to estimate 3d info for new frame's detected object list.
 *
 */
class StateEstimate
{
public:
    using Scalar                   = float32_t;
    using CameraDetectedObjectType = BoxObjectT<Scalar, 128U>;
    using CameraDetectedObjectPtr  = std::shared_ptr<CameraDetectedObjectType>;
    using CameraDetectedObjectList = std::list<CameraDetectedObjectPtr>;
    using Pose3Type                = holo::geometry::Pose3T<Scalar>;

    /**
     * @brief Construct a new State Estimate object
     *
     * @param camera_intrinsic_file, target camera's intrinsic file
     * @param node, yaml node
     */
    StateEstimate(std::string const& camera_intrinsic_file, holo::yaml::Node const& node, Pose3Type const& Tbody_cam);

    /**
     * @brief Destroy the State Estimate object
     *
     */
    ~StateEstimate();

    /**
     * @brief estimate the detected object list's 3d info
     *
     * @param det_obj_list
     * @param ego_speed ego car speed
     */
    void DoWork(CameraDetectedObjectList& det_obj_list, float32_t ego_speed = 500.0f);

private:
    /**
     * @brief Initialize the estimator for obj
     *
     * @param det_obj_ptr
     */
    void initialize(CameraDetectedObjectPtr const& det_obj_ptr);

    /**
     * @brief Check whether the object's timestamp is valid
     *
     * @param det_obj_ptr
     * @param min_dt, min delta timestamp between current frame with last frame
     * @param max_dt, max delta timestamp between current frame with last frame
     * @return bool_t
     */
    bool_t checkTimestamp(CameraDetectedObjectPtr const& det_obj_ptr, Scalar min_dt = 0.02f, Scalar max_dt = 0.5f);

    /**
     * @brief Clean the old states
     *
     * @param current_ts, current timestamp
     * @param max_dt, max delta timestamp
     */
    void cleanOldStates(Timestamp const& current_ts, Scalar max_dt = 5.0f);

private:
    Estimator                                        estimator_;
    std::unordered_map<uint32_t, SlidingWindowState> states_prior_;
    std::unordered_map<uint32_t, SlidingWindowState> states_main_;
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_3D_APP_STATE_ESTIMATE_H_
