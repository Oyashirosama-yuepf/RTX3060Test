/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file scene.h
 * @brief Analysis of the rode scene.
 * @author dingjing(dingjing@holomaitc.com)
 * @date 2020-07-14
 */

#ifndef HOLO_MAP_COMMON_SCENE_H_
#define HOLO_MAP_COMMON_SCENE_H_

#include <map>
#include <vector>

#include <holo/map/common/common_type_define.h>
#include <holo/map/common/common_define.h>
namespace holo
{
namespace map
{
/**
 * @brief Using for analyzing connected type between two lane groups.
 */
class SceneAnalysis
{
public:
    /**
     * @brief Definition of scene type
     *                           ---------------------------->
     *                              No pre
     * ------------------------------------------------------>
     *                        1 TO 1
     * ------------------------------------------------------>
     *                        1 TO 2
     * ------------------------------------------------------>
     *                           \
     *                            \-------------------------->
     *
     * |<------Lane Group 1---->|<------Lane Group 2------->|
     *
     *
     * ------------------------>
     *                 No suc
     * ------------------------------------------------------>
     *                        1 TO 1
     * ------------------------------------------------------>
     *
     * |<------Lane Group 1---->|<------Lane Group 2------->|
     */
    enum class SceneType : uint8_t
    {
        SCENE_TYPE_1_TO_1 = 0U,
        SCENE_TYPE_1_TO_2 = 1U,
        SCENE_TYPE_1_TO_3 = 2U,
        SCENE_TYPE_2_TO_1 = 3U,
        SCENE_TYPE_3_TO_1 = 4U,
        SCENE_TYPE_NO_PRE = 5U,
        SCENE_TYPE_NO_SUC = 6U,
        SCENE_TYPE_2_TO_2 = 7U
    };

    /**
     * @brief Definition of two lane groups' connection
     *
     * ------------------------------------------------------>
     *                               neighbour left: true
     * ------------------------------------------------------>
     *          current       1 TO 2
     * ------------------------------------------------------>  split_middle: false
     *                           \
     *                            \-------------------------->
     *                               neighbour right: false
     *
     * |<------Lane Group 1---->|<------Lane Group 2------->|
     *
     *
     *                            /-------------------------->
     *                           /           Lane 1
     * ------------------------------------------------------>  split_left: false
     *                                       Lane 2
     *     current       1 TO 3  ---------------------------->  split_right: true
     *                           \--------------------------->
     * ------------------------             Lane 3
     *                           \--------------------------->
     *                               neighbour right: false
     *
     * |<------Lane Group 1---->|<------Lane Group 2------->|
     *
     */
    struct RoadScene
    {
        SceneType   type;           ///< Scene type
        VecIdType lane_ids;       ///< Lanes in before Lane Group
        VecIdType next_lane_ids;  ///< Lanes in next Lane Group

        /// If current lane and direct next lane both have left neighbourd lanes and their left lanes are connected.
        bool_t neighbour_left = false;
        /// If current lane and direct next lane both have right neighbourd lanes and their right lanes are connected.
        bool_t neighbour_right = false;

        /// If lanes are split when there are two next lanes.
        bool_t split_middle = false;
        /// If left-most lane and middle lane are split when there are three next lanes.
        bool_t split_left = false;
        /// If right-most lane and middle lane are split when there are three next lanes.
        bool_t split_right = false;
    };

public:
    /**
     * @brief Constructor
     *
     */
    SceneAnalysis() = default;

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
     * @brief disable default copy constructor
     *
     */
    SceneAnalysis(SceneAnalysis const&) = delete;
    SceneAnalysis(SceneAnalysis&&)      = delete;

    /**
     * @brief distable assignment operator
     *
     */
    SceneAnalysis& operator=(SceneAnalysis const&) = delete;
    SceneAnalysis& operator=(SceneAnalysis&&) = delete;

    /**
     * @brief Destructor
     *
     */
    ~SceneAnalysis() = default;

    /**
     * @brief Analyze connected type between two lane groups
     *
     * @param [in] group_id      Before Lane Group id.
     * @param [in] next_group_id Next Lane Group id.
     * @param [out] road_scene   Scene of differeent road connection.
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t Analyze(IdType const group_id, IdType const next_group_id, std::vector<RoadScene>& road_scene);

private:
    /**
     * @brief Analyze scene of 3 lanes to 1 lane.
     *
     * @param [in] ptr_lanes      Before Lanes.
     * @param [in] next_ptr_lanes Next Lanes.
     * @param [out] road_scene    Road Scene.
     * @param [out] selected_ids  Record lane ids have been selected.
     *                            These ids contains both lanes and next lanes.
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t analyzeScene3To1(std::vector<format::PtrLane> const& ptr_lanes,
                            std::vector<format::PtrLane> const& next_ptr_lanes, std::vector<RoadScene>& road_scene,
                            VecIdType& selected_ids);
    /**
     * @brief Analyze scene of 2 lanes to 1 lane.
     *
     * @param [in] ptr_lanes      Before Lanes.
     * @param [in] next_ptr_lanes Next Lanes.
     * @param [out] road_scene    Road Scene.
     * @param [out] selected_ids  Record lane ids have been selected.
     *                            These ids contains both lanes and next lanes.
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t analyzeScene2To1(std::vector<format::PtrLane> const& ptr_lanes,
                            std::vector<format::PtrLane> const& next_ptr_lanes, std::vector<RoadScene>& road_scene,
                            VecIdType& selected_ids);
    /**
     * @brief Analyze scene of 1 lane to 3 lanes.
     *
     * @param [in] ptr_lanes      Before Lanes.
     * @param [in] next_ptr_lanes Next Lanes.
     * @param [out] road_scene    Road Scene.
     * @param [out] selected_ids  Record lane ids have been selected.
     *                            These ids contains both lanes and next lanes.
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t analyzeScene1To3(std::vector<format::PtrLane> const& ptr_lanes,
                            std::vector<format::PtrLane> const& next_ptr_lanes, std::vector<RoadScene>& road_scene,
                            VecIdType& selected_ids);
    /**
     * @brief Analyze scene of 1 lane to 2 lanes.
     *
     * @param [in] ptr_lanes      Before Lanes.
     * @param [in] next_ptr_lanes Next Lanes.
     * @param [out] road_scene    Road Scene.
     * @param [out] selected_ids  Record lane ids have been selected.
     *                            These ids contains both lanes and next lanes.
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t analyzeScene1To2(std::vector<format::PtrLane> const& ptr_lanes,
                            std::vector<format::PtrLane> const& next_ptr_lanes, std::vector<RoadScene>& road_scene,
                            VecIdType& selected_ids);
    /**
     * @brief Analyze scene of 1 lane to 1 lane.
     *
     * @param [in] ptr_lanes      Before Lanes.
     * @param [in] next_ptr_lanes Next Lanes.
     * @param [out] road_scene    Road Scene.
     * @param [out] selected_ids  Record lane ids have been selected.
     *                            These ids contains both lanes and next lanes.
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t analyzeScene1To1(std::vector<format::PtrLane> const& ptr_lanes,
                            std::vector<format::PtrLane> const& next_ptr_lanes, std::vector<RoadScene>& road_scene,
                            VecIdType& selected_ids);

    /**
     * @brief Analyze scene of 2 lane to 2 lane.
     *        This is a special scece.
     *
     * @detail
     *   |           |      /
     *   |   suc1    |suc2 /
     *   |           |    /
     *   |           |   /
     *   |           |  /
     *   |           | /
     *   |           |/
     *   |           |\
     *   |           | \
     *   |           |  \
     *   |           |   \
     *   |           |    \
     *   |   pre1    |pre2 \
     *   |           |      \
     *
     * @param [in] ptr_lanes      Before Lanes.
     * @param [in] next_ptr_lanes Next Lanes.
     * @param [out] road_scene    Road Scene.
     * @param [out] selected_ids  Record lane ids have been selected.
     *                            These ids contains both lanes and next lanes.
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t analyzeScene2To2(std::vector<format::PtrLane> const& ptr_lanes,
                            std::vector<format::PtrLane> const& next_ptr_lanes, std::vector<RoadScene>& road_scene,
                            VecIdType& selected_ids);

    /**
     * @brief Analyze scene of no preceding lanes.
     *
     * @param [in] ptr_lanes      Before Lanes.
     * @param [in] next_ptr_lanes Next Lanes.
     * @param [out] road_scene    Road Scene.
     * @param [out] selected_ids  Record lane ids have been selected.
     *                            These ids contains both lanes and next lanes.
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t analyzeNoPre(std::vector<format::PtrLane> const& lane_ids, std::vector<format::PtrLane> const& next_lane_ids,
                        std::vector<RoadScene>& road_scene, VecIdType& selected_ids);

    /**
     * @brief Analyze scene of no succeeding lanes.
     *
     * @param [in] ptr_lanes      Before Lanes.
     * @param [in] next_ptr_lanes Next Lanes.
     * @param [out] road_scene    Road Scene.
     * @param [out] selected_ids  Record lane ids have been selected.
     *                            These ids contains both lanes and next lanes.
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t analyzeNoSuc(std::vector<format::PtrLane> const& lane_ids, std::vector<format::PtrLane> const& next_lane_ids,
                        std::vector<RoadScene>& road_scene, VecIdType& selected_ids);

    /**
     * @brief Analyze scene if next lanes have neighbour or are splited.
     *
     * @param [in] lane_ids      Before Lane ids.
     * @param [in] next_lane_ids Next Lane ids.
     * @param [out] road_scene   Road Scene.
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t analyzeSceneEnvironment(VecIdType const& lane_ids, VecIdType const& next_lane_ids,
                                   std::vector<RoadScene>& road_scene);

    /**
     * @brief Analyze scene if next lanes have neighbour.
     *
     * @param [in] lane_ids      Before Lane ids.
     * @param [in] next_lane_ids Next Lane ids.
     * @param [out] road_scene   Road Scene.
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t analyzeNeighbour(VecIdType const& lane_ids, VecIdType const& next_lane_ids, RoadScene& road_scene);

    /**
     * @brief Analyze scene if next lanes are splited.
     *
     * @param [in|out] road_scene Road Scene.
     *
     * @return true  Operation successful.
     * @return false Otherwise.
     */
    bool_t analyzeSplit(RoadScene& road_scene);

private:
    RetrieverSPType ret_ = nullptr;  ///< Map data engine.
};

}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_COMMON_SCENE_H_ */