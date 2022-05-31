/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_frame_helper.h
 * @brief Make Road Frame by map data.
 * @author dingjing(dingjing@holomaitc.com)
 * @date 2020-07-24
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_SERVICE_ROAD_FRAME_HELPER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_SERVICE_ROAD_FRAME_HELPER_H_

#include <holo/map/advice.h>

#include <holo/map/common/common_type_define.h>
#include <holo/map/common/scene.h>
#include <holo/map/common/match_info.h>
#include <holo/map/common/common_define.h>
namespace holo
{
namespace map
{
/**
 * @brief Make RoadFrame by map data.
 */
class RoadFrameHelper
{
public:
    using RoadFrameType = holo::map::Advice::RoadFrameType;
    using FeatureID     = holo::map::service::client::engine::Retriever::ProfileIdType;

public:
    /**
     * @brief Constructor.
     */
    RoadFrameHelper() = default;

    /**
     * @brief Destructor.
     */
    ~RoadFrameHelper() = default;

    /**
     * @brief Initializer
     *
     * @param [in] ret Pointer of retriever
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t Init(RetrieverSPType const ret);

    /**
     * @brief Disable default copy constructor
     *
     */
    RoadFrameHelper(RoadFrameHelper const&) = delete;
    RoadFrameHelper(RoadFrameHelper&&)      = delete;

    /**
     * @brief Distable assignment operator
     *
     */
    RoadFrameHelper& operator=(RoadFrameHelper const&) = delete;
    RoadFrameHelper& operator=(RoadFrameHelper&&) = delete;

    /**
     * @brief Make road graph rely on Lane Group Ids of driving route.
     *
     * @param[in]  lane_group_ids   All Lane Group ids on the route.
     * @param[out] road_frame Logic Graph in Map Advice.
     *
     * @return true Operation successful;
     *         false Otherwise.
     */
    bool_t MakeRoadGraph(map::VecIdType const& lane_group_ids, RoadFrameType& road_frame);
private:
    /**
     * @brief Make nodes by first lane group in first level.
     *
     * @param[in]     lane_group_id First Lane Group id.
     * @param[in,out] road_frame    Logic Graph in Map Advice.
     * @param[out]    current_level_node
     *
     * @return true Operation successful;
     *         false Otherwise.
     */
    bool_t makeNodesInFirstLevel(FeatureID const lane_group_id, RoadFrameType& road_frame,
                                 std::map<FeatureID, size_t>& current_level_node);

    /**
     * @brief Make nodes by two connected lane groups.
     *
     * @tparam TRoadFrame RoadFrame2 with different template.
     * @param[in]     group_id      Before Lane Group id.
     * @param[in]     next_group_id Next Lane Group id.
     * @param[in,out] current_level_node  Node address for preceding Lane Group, save nodes in last line.
     * @param[in,out] road_frame    Logic Graph in Map Advice.
     *
     * @return true Operation successful;
     *         false Otherwise.
     */
    bool_t makeNodesByConnectedLaneGroups(IdType const group_id, IdType const next_group_id,
                                          std::map<FeatureID, size_t>& current_level_node, RoadFrameType& road_frame);

    /**
     * @brief Assign Road Frame value by specific scene.
     *
     * @tparam TRoadFrame RoadFrame2 with different template.
     * @param[in] scene                 Specific scene
     * @param[in,out] current_level_node All node address for before Lane Group Record new node.
     * @param[in,out] next_level_node   All node address for next Lane Group. Record new node.
     * @param[in,out] road_frame        Templat Road Frame
     *
     * @return true Operation successful;
     *         false Otherwise.
     */
    bool_t assignValueForLogicGraph(SceneAnalysis::RoadScene const&    scene,
                                    std::map<FeatureID, size_t> const& current_level_node,
                                    std::map<FeatureID, size_t>& next_level_node, RoadFrameType& road_frame);

    /**
     * @brief Assign Road Frame value for no connected lanes
     *
     * @tparam TRoadFrame RoadFrame2 with different template.
     * @param[in] lane_ids         No connected lanes
     * @param[in,out] next_level_node All node address for Lane Group of no connected lane
     * @param[in,out] road_frame   Templat Road Frame
     *
     * @return true Operation successful;
     *         false Otherwise.
     */
    bool_t assignNoConnectedValue(VecIdType const& lane_ids, std::map<FeatureID, size_t>& next_level_node,
                                  RoadFrameType& road_frame);

private:
    RetrieverSPType ptr_ret_ = nullptr;  ///< Pointer of retriever.

    /// Tools for analyze two connected Lane Groups.
    std::shared_ptr<SceneAnalysis> ptr_scene_analysis_ = nullptr;
};

typedef std::shared_ptr<RoadFrameHelper> PtrRoadFrameHelper;

}  // namespace map
}  // namespace holo
#endif /* HOLO_MAP_FEATURE_NAVIGATOR_SERVICE_ROAD_FRAME_HELPER_H_ */
