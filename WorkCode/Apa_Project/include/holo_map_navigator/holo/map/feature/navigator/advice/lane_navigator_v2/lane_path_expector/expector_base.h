/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file expector.h
 * @brief Expector is used to recommend lane path
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-01-27
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_EXPECTOR_EXPECTOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_EXPECTOR_EXPECTOR_H_

#include <vector>

#include <holo/map/feature/navigator/advice/lane_navigator_v2/participant_group.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class ExpectorManager;
class ExpectorBase
{
public:
    using ParticipantGroupType   = holo::map::navigator::advice::ParticipantGroup;
    using ExpectorSPtrType       = std::shared_ptr<ExpectorBase>;
    using SceneSketchType        = scene::SceneSketch;
    using SceneSketchSPtrType    = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType = std::vector<SceneSketchSPtrType>;

    using RouteSceneType     = scene::RouteScene;
    using RouteSceneSPtrType = std::shared_ptr<RouteSceneType>;

public:
    virtual ~ExpectorBase() = default;

public:
    /**
     * @brief Initialize function
     * 
     * @return holo::bool_t 
     */
    virtual holo::bool_t Init() = 0;

    /**
     * @brief Whether or not the expector is enabled
     *
     * @return holo::bool_t
     */
    virtual holo::bool_t Enabled() = 0;

    /**
     * @brief Calculate to recommend different lane paths in participant group
     *
     * @param group Participant group containing participants, where one
     *              participant correspond to one lane path
     * @return holo::bool_t True, succeed; false otherwise
     */
    virtual holo::bool_t Recommend(ParticipantGroupType& group) = 0;

    /**
     * @brief Whether or not terminate recommending calculation
     *
     * @return holo::bool_t True, need terminating; false, execute
     *                      next Expector calcuation
     */
    virtual holo::bool_t Terminate() = 0;

    holo::float64_t GetMaxExpectedDistance() const
    {
        return this->max_expected_distance_;
    }
    void SetMaxExpectedDistance(holo::float64_t max_expected_distance_meters)
    {
        this->max_expected_distance_ = max_expected_distance_meters;
    }

public:
    friend class ExpectorManager;

protected:
    /// Scene sketch
    SceneSketchSPtrType scene_sketch_ = nullptr;
    RouteSceneSPtrType  rout_scene_   = nullptr;
    /// Index absolutely
    std::size_t index_absolute_ = 0U;
    /// Index in same expect type
    std::size_t index_homogeneous_ = 0U;
    /// Maximum lane path expected distance
    holo::float64_t max_expected_distance_ = 1500.0f;
};

class CompositeExpectorBase : public ExpectorBase
{
public:
private:
    std::deque<ExpectorSPtrType> expectors_;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_EXPECT_EVALUATE_EXPECTOR_EXPECTOR_H_ */