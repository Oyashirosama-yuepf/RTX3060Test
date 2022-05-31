/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file path_tree.h
 * @brief This header file defines the ehp pathtree.
 * @author zhengshulei@holomatic.com
 * @date 2021-12-16
 */
#ifndef HOLO_MAP_ADASIS_EHR_PATH_TREE_H_
#define HOLO_MAP_ADASIS_EHR_PATH_TREE_H_

#include <holo/map/adasis/ehr/types.h>
#include <holo/map/adasis/ehr/msg_buffer.h>
#include <holo/map/adasis/ehr/msg_verification.h>

namespace holo
{
namespace map
{
namespace adasis
{
namespace ehr
{

/**
 * @addtogroup ehr
 * @{
 *
 */

/**
 * @brief Definition of link which store all ehp messages in {path_id:[offset,endoffset]}.
 */
class EhpLink
{
public:
    EhpLink(LinkIdentifierPtr& link_identifier) : link_identifier_(link_identifier)
    {
    }
    /**
     * @brief Get LinkIdentifier.
     */
    LinkId GetLinkId();
    /**
     * @brief Get Path Identifier.
     */
    v3_1_1::PathId GetPathId();
    /**
     * @brief Get start offset of link(0 is path start).
     */
    v3_1_1::Offset GetStartPos();
    /**
     * @brief Get end offset of link(0 is path start).
     */
    v3_1_1::Offset GetEndPos();
    v3_1_1::Offset GetLaneGeometryEndPos();
    /**
     * @brief Get LaneModel of link.
     */
    LaneModelPtr GetLaneModel();
    /**
     * @brief Get LaneNum of link.
     */
    NumOfLanePtr GetLaneNum();
    /**
     * @brief Get road class of link.
     */
    FunctionalRoadClassPtr GetRoadClass();
    /**
     * @brief Get road type of link.
     */
    FormOfWayPtr GetFormOfWay();
    /**
     * @brief Get tunnel of link.
     */
    TunnelPtr GetTunnel();
    /**
     * @brief Get LaneConnectivity of link.
     */
    LaneConnectivityPtr GetLaneConnectivity();
    /**
     * @brief Get LinearObject of link.
     */
    LinearObjectPtr GetLinearObject();
    /**
     * @brief Get SpeedLimit of LaneIdx.
     */
    SpeedLimitPtr GetSpeedLimit(holo::uint8_t lane_index);
    /**
     * @brief Get LaneWidth of LaneIdx.
     */
    LaneWidthPtr GetLaneWidth(holo::uint8_t lane_num);
    /**
     * @brief Get Curvature of LaneIdx.
     */
    CurvatureVecContainerType& GetCurvature(holo::uint8_t lane_num);
    /**
     * @brief Get Slope vector of LaneIdx.
     */
    SlopeVecContainerType& GetSlope(holo::uint8_t lane_num);
    /**
     * @brief Get LaneGeometry vector with id.
     * @param[in] linearobj_id liearobject id
     * @param[out] lg lane geometry vector
     */
    holo::bool_t GetLaneGeometry(v3_1_1::LinearObjId linearobj_id, LaneGeometryVecContainerType& lg);
    /**
     * @brief Set LaneModel data of link.
     * @param[in] lane_model lanemodel data.
     */
    void SetLaneModel(LaneModelPtr lane_model);
    /**
     * @brief Set LaneNum data of link.
     * @param[in] lane_num lane number data.
     */
    void SetLaneNum(NumOfLanePtr lane_num);
    /**
     * @brief Set FunctionalRoadClass data of link.
     * @param[in] road_class FunctionalRoadClass data.
     */
    void SetRoadClass(FunctionalRoadClassPtr road_class);
    /**
     * @brief Set FormOfWay data of link.
     * @param[in] form_of_way FormOfWay data.
     */
    void SetFormOfWay(FormOfWayPtr form_of_way);
    /**
     * @brief Set Tunnel data of link.
     * @param[in] tunnel Tunnel data.
     */
    void SetTunnel(TunnelPtr tunnel);
    /**
     * @brief Set LaneConnectivity data of link.
     * @param[in] lane_connectivity lane connectivity data at link's startpos.
     */
    void SetLaneConnectivity(LaneConnectivityPtr lane_connectivity);
    /**
     * @brief Set LinearObject data of link.
     * @param[in] linear_obj linear object data.
     */
    void SetLinearObject(LinearObjectPtr linear_obj);
    /**
     * @brief Set SpeedLimit data of link.
     * @param[in] lane_num laneidx.
     * @param[in] lane_speed_limit lane speed limit.
     */
    void SetSpeedLimit(holo::uint8_t lane_num, SpeedLimitPtr lane_speed_limit);
    /**
     * @brief Set LaneWidth data of link.
     * @param[in] lane_num laneidx.
     * @param[in] lane_width lane width.
     */
    void SetLaneWidth(holo::uint8_t lane_num, LaneWidthPtr lane_width);
    /**
     * @brief Set Curvature data of link.
     * @param[in] lane_num laneidx.
     * @param[in] curvature lane curvature.
     */
    void SetCurvature(holo::uint8_t lane_num, CurvaturePtr curvature);
    /**
     * @brief Set Slope data of link.
     * @param[in] lane_num laneidx.
     * @param[in] slope lane slope.
     */
    void SetSlope(holo::uint8_t lane_num, SlopePtr slope);
    /**
     * @brief Set LaneGeometry of link.
     * @param[in] id linearobject id.
     * @param[in] geometry lane geometry.
     */
    void SetLaneGeometry(v3_1_1::LinearObjId id, LaneGeometryPtr geometry);

     /**
     * @brief Print current path info for debug.
     */
    void CheckState();

private:
    void SetLaneNum(holo::uint8_t num);

private:
    LinkIdentifierPtr link_identifier_     = nullptr;
    LaneModelPtr lane_model_               = nullptr;
    NumOfLanePtr lane_num_                 = nullptr;
    FunctionalRoadClassPtr road_class_     = nullptr;
    FormOfWayPtr form_of_way_              = nullptr;
    TunnelPtr tunnel_                      = nullptr;
    LinearObjectPtr linear_object_         = nullptr;
    LaneConnectivityPtr lane_connectivity_ = nullptr;

    SpeedLimitVecContainerType speed_limit_per_lane_;
    LaneWidthVecContainerType lane_width_per_lane_;
    std::vector<CurvatureVecContainerType> curvature_per_lane_;
    std::vector<SlopeVecContainerType> slope_per_lane_;

    LaneGeometryContainerType lane_geometry_map_;
    v3_1_1::Offset lane_geometry_end_pos = 0;
};

using EhpLinkPtr              = std::shared_ptr<EhpLink>;
using EhpLinkVecContainerType = std::vector<EhpLinkPtr>;
using EhpLinkVecCIterType     = EhpLinkVecContainerType::const_iterator;

/**
 * @brief Definition of link sequece of path.
 * @detail One EHP path is updated by vehicle position,
 *         this is control by profilecontrol message and new link messages
 *         control info include:
 *         1. control_offset_: remove link when link's endoffset <= control_offset
 *         2. receive_ready_pos_: latest link's endoffset
 *         batch update strategy need record last update offset info, include:
 *         1. last_dirty_pos_: link within [last_dirty_pos_,control_offset_] need do delete
 *         2. last_ready_pos_: link within [last_ready_pos_,receive_ready_pos_] need do adapt
 */
class EhpLinkSequence
{
public:
    /**
     * @brief Get status of link sequence.
     * @return true/false link updated or need update.
     */
    holo::bool_t IsUpdated(){ return last_ready_pos_ == receive_ready_pos_;}
    /**
     * @brief Add new link to path.
     * @param[in] link new link.
     */
    holo::bool_t AddLink(EhpLinkPtr link);
    /**
     * @brief Add sub path id to path.
     * @param[in] ptc path control data.
     */
    void AddSubPath(v3_1_1::PathControl const& ptc);
    /**
     * @brief Get sub path ids.
     * @param[in] pos path offset.
     * @param[out] sub_path_ids sub path ids.
     */
    holo::bool_t GetSubPathId(v3_1_1::Offset pos, std::vector<v3_1_1::PathId> & sub_path_ids);
    /**
     * @brief Add node of path.
     * @param[in] node node of path.
     */
    void AddInsection(InsectionPtr node);

    holo::uint32_t GetValidLengthCm();
    /**
     * @brief Get link info by linkid.
     * @param[in] link_id link id.
     * @param[out] link link.
     */
    holo::bool_t GetLink(LinkId const link_id, EhpLinkPtr& link);
    /**
     * @brief Get first link in path.
     * @param[out] link first link in path.
     */
    holo::bool_t GetStartLink(EhpLinkPtr& link);
    /**
     * @brief Get link by offset.
     * @param[in] offset path offset.
     * @param[out] link link that endoffset == offset.
     */
    holo::bool_t GetLinkEndHere(const v3_1_1::Offset offset, EhpLinkPtr& link);
    /**
     * @brief Get all valid links of path.
     * @param[out] path_links all links that's in [control_offset_,last_ready_pos_].
     */
    holo::bool_t GetPathLinks(std::vector<EhpLinkPtr>& path_links);
    /**
     * @brief Get all new links of path.
     * @param[out] links all links that's in [last_ready_pos_,receive_ready_pos_].
     */
    holo::bool_t GetReceivedLinks(std::vector<LinkId>& links);
    /**
     * @brief Get link's precceding/succeding by linkid.
     * @param[in] link_id link id.
     * @param[out] pre_ids link's preccedings.
     * @param[out] suc_ids link's succedings.
     */
    void GetLinkRelation(LinkId const link_id, std::vector<LinkId>& pre_ids, std::vector<LinkId>& suc_ids);
    /**
     * @brief Set profile control pos.
     * @param[in] pos control offset of path.
     */
    void SetProfileControl(v3_1_1::Offset const pos);
    /**
     * @brief Set path id.
     * @param[in] id path id.
     */
    void SetPathId(v3_1_1::PathId const id);
    /**
     * @brief Get path id.
     * @return path id.
     */
    v3_1_1::PathId GetPathId();
    /**
     * @brief Update path lins to profile control pos.
     * @param[out] dirty_link_ids link need remove.
     * @param[in] force if true, remove link from path.
     */
    void ApplyProfileControl(std::vector<LinkId>& dirty_link_ids, holo::bool_t force = false);
    /**
     * @brief Get linksequence status.
     * @return true/false if false, some links missed in path.
     */
    holo::bool_t IsLinkSequenceOk();
    /**
     * @brief Set receive ready pos to latest link's endoffset.
     */
    void UpdateReadyPos();
    /**
     * @brief Set last ready pos after adapt and push data up.
     */
    void SyncReadyPos();
    /**
     * @brief Print current path info for debug.
     */
    void PrintInfo();

    void SetVerbose(holo::bool_t v)
    {
        this->verbose_ = v;
    }

public:
    // std::vector method proxy
    EhpLinkVecCIterType cbegin();
    EhpLinkVecCIterType cend();
    std::size_t size();
    holo::bool_t empty();
    const EhpLinkPtr& operator[](std::size_t i);

private:
    holo::bool_t verbose_  = false;
    v3_1_1::PathId path_id_ = 0;
    // profile control offset from ehp
    v3_1_1::Offset control_offset_ = 0;
    // profile control offset of ehr
    v3_1_1::Offset last_dirty_pos_ = 0;
    v3_1_1::Offset last_ready_pos_ = 0;
    v3_1_1::Offset receive_ready_pos_ = 0;
    v3_1_1::Offset active_receive_ready_pos = 0;
    EhpLinkVecContainerType links_;
    std::vector<v3_1_1::PathControl> sub_paths_;
    std::vector<InsectionPtr> nodes_;
};

using LinkSequencePtr = std::shared_ptr<EhpLinkSequence>;
using EhpPathContainerType = std::map<v3_1_1::PathId, LinkSequencePtr>;
using EhpNodeContainerType = std::map<v3_1_1::PathId, InsectionVecContainerType>;

/**
 * @brief EHP map model.
 */
class EhpMapModel
{
public:
    /**
     * @brief Get main path identifier.
     */
    v3_1_1::PathId GetMainPathId();

    holo::bool_t GetMainPathValidLengthCm(holo::uint32_t& valid_length_cm);
    holo::bool_t GetLink(const LinkId& link_id, EhpLinkPtr& link);
    /**
     * @brief Get path identifier of link.
     * @param[in] link_id link id.
     * @param[out] path_id path id.
     */
    holo::bool_t GetPathIdOfLink(const LinkId link_id, v3_1_1::PathId& path_id);
    /**
     * @brief Get precceding link identifier.
     * @param[in] new_path_id link's path id.
     * @param[in] new_link_id link id.
     * @param[in] init_path_id precceding path id.
     * @param[out] init_link_id precceding link id.
     */
    holo::bool_t GetInitLinkId(
        const v3_1_1::PathId new_path_id, const LinkId new_link_id, 
        const v3_1_1::PathId init_path_id, LinkId& init_link_id);
    /**
     * @brief Get link's pre/sucs relation.
     * @param[in] path_id link's path id.
     * @param[in] link_id link id.
     * @param[out] pre_ids precceding links.
     * @param[out] suc_ids succeding links.
     */
    void GetLinkRelation(
        const v3_1_1::PathId path_id, const LinkId link_id, 
        std::vector<LinkId>& pre_ids, std::vector<LinkId>& suc_ids);
    /**
     * @brief Add ADASIS V3 message.
     * @param[in] buffer message buffer.
     */
    holo::bool_t AddMessage(MessageBuffer& buffer);
    /**
     * @brief Get EHP map's status.
     * @return true/false if true, need update map.
     */
    holo::bool_t NeedUpdateMap();
    /**
     * @brief Get paths that need update.
     * @param[out] paths paths that need update map.
     */
    holo::bool_t GetEhpPathForAdapter(std::vector<LinkSequencePtr>& paths);

    void SetVerbose(holo::bool_t v)
    {
        this->verbose_ = v;
    }

public:
    holo::bool_t GetEHPPositionStatus(holo::int32_t& position_count, HDMapStatus& hdmap_status);

private:
    // vehicle location (path/offset)
    void SetPositon(PositionPtr msg);
    void SetGlobalData(GlobalDataEntry const& msg);
    void SetPathControl(v3_1_1::PathControlMessage const& msg);
    void SetProfileControl(std::vector<v3_1_1::ProfileControl> const& msg);

    holo::bool_t SetIntersection(InsectionPtr node);

    holo::bool_t AddLink(LinkIdentifierPtr link_identifier);
    holo::bool_t UpdateLink(LaneModelPtr lane_model);
    holo::bool_t UpdateLink(NumOfLanePtr lane_num);
    
    holo::bool_t UpdateLink(FormOfWayPtr form_of_way);
    holo::bool_t UpdateLink(FunctionalRoadClassPtr road_class);
    holo::bool_t UpdateLink(TunnelPtr tunnel);

    holo::bool_t UpdateLink(LaneConnectivityPtr lane_connectivity);
    holo::bool_t UpdateLink(LinearObjectPtr linear_obj);
    holo::bool_t UpdateLink(SpeedLimitPtr lane_speed_limit);
    holo::bool_t UpdateLink(LaneWidthPtr lane_width);
    holo::bool_t UpdateLink(LaneGeometryPtr lane_geometry);
    holo::bool_t UpdateLinkCurvature(CurvaturePtr curvature);
    holo::bool_t UpdateLinkSlope(SlopePtr slope);
    void UpdateMapBundle(baidu_v3::MapData const& map_data);

private:
    LinkSequencePtr& AddPathToMap(v3_1_1::PathId path_id);
    holo::bool_t GetLink(const v3_1_1::PathId& path_id, const LinkId& link_id, EhpLinkPtr& link);

private:
    holo::bool_t verbose_  = false;

    v3_1_1::PathId main_path_ = 0;

    PositionPtr positon_ = nullptr;
    GlobalDataPtr global_data_ = nullptr; // globaldata
    PathTreeContainerType path_ctrl_container_;
    ProfileControlContainerType profile_ctrl_container_;

    baidu_v3::MapData map_bundle_;
    EhpPathContainerType ehp_paths_container_;
    std::vector<v3_1_1::PathId> dirty_paths_;

    std::map<LinkId, v3_1_1::PathId> link_path_map_;

    MessageVerification verification_;
};

/**
 * @}
 */

} // namespace ehr
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_EHR_PATH_TREE_H_ */