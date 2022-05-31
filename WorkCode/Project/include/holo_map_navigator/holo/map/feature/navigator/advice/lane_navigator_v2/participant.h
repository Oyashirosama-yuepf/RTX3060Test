/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file participant.h
 * @brief Participant to be expected or evaluated
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-02-25
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_PARTICIPANT_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_PARTICIPANT_H_

#include <vector>

#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/common/common_define.h>
#include <holo/map/common/match_info.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class ParticipantGroup;

class Participant
{
public:
    using LanePathSPtrType = std::shared_ptr<holo::map::navigator::advice::LanePath>;

    struct ScoreRecord
    {
        IdType scene_link_id_begin = 0U;
        IdType scene_link_id_end = 0U;
        holo::int32_t score               = 0U;
        ScoreRecord(IdType const& b, IdType const& e, holo::int32_t const& s)
        {
            this->scene_link_id_begin = b;
            this->scene_link_id_end   = e;
            this->score               = s;
        }
        static std::string FormatToString(ScoreRecord const& record)
        {
            std::stringstream ss;
            ss << "{";
            ss << " \"s_link\":\"" << record.scene_link_id_begin;
            ss << "\", \"e_link\":\"" << record.scene_link_id_end;
            ss << "\", \"score\":\"" << record.score;
            ss << "\"}";
            return ss.str();
        }
    };

    static std::string FormatToString(Participant const& participant);

    Participant(LanePathSPtrType path);

    /**
     * @brief Check whethor or not the lane path could going passed the link
     *
     * @param link_id The certain link id
     * @return holo::bool_t True, succeed; false, fails.
     */
    holo::bool_t SucceedToGoPassLink(IdType const link_id) const;

    /**
     * @brief Check whether or not the lane path has avoid passing certain lane
     * 
     * @param lane_id Lane ids needed to be avoid  
     * @return holo::bool_t 
     */
    holo::bool_t PassAvoidLanes(std::vector<IdType> const& lane_ids) const;

    /**
     * @brief Get the Tail Distance 
     * 
     * @return holo::bool_t 
     */
    holo::float64_t GetTailDistance() const;

    /**
     * @brief Roll back for expected history
     *
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t RollBack();

    /**
     * @brief Get the Id of lane path
     * 
     * @return holo::uint64_t 
     */
    holo::uint64_t GetId() const;

    void AddRecord(ScoreRecord const& record);

    holo::int32_t GetScore() const;

    holo::bool_t GoThroughLanes(std::vector<IdType> const&) const;

    void AddExpected(holo::bool_t expected);
    holo::bool_t GetExpected() const;

    holo::bool_t HasLeftBoundaryIds(std::vector<IdType> const& ids, holo::bool_t const strict) const;
    holo::bool_t HasRightBoundaryIds(std::vector<IdType> const& ids, holo::bool_t const strict) const;

    holo::bool_t GoThroughLane(IdType const lane_id) const;
    holo::bool_t SetRelateEndpoint(std::vector<IdType> const& ids) const;
    holo::bool_t SetRelatePathId(IdType const id) const;

    holo::uint8_t GetLevel() const;
    void SetLevelZero();

public:
    friend class ParticipantGroup;

private:
    /// Lane path
    LanePathSPtrType lane_path_ = nullptr;
    /// Whethor or not is expected
    std::deque<holo::bool_t> expected_history_;
    /// Score for scene history
    std::deque<ScoreRecord> score_history_;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_PARTICIPANT_H_ */
