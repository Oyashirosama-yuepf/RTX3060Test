/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file participant_group.h
 * @brief A group of participants
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-02-24
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_PARTICIPANT_GROUP_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_PARTICIPANT_GROUP_H_

#include <vector>

#include <holo/map/common/common_define.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/participant.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
class ParticipantGroup
{
public:
    static std::string FormatToString(ParticipantGroup const& group);

    ParticipantGroup()                        = default;
    ParticipantGroup(ParticipantGroup const&) = default;
    ParticipantGroup(ParticipantGroup&&)      = default;
    ParticipantGroup& operator=(ParticipantGroup const&) = default;
    ParticipantGroup& operator=(ParticipantGroup&&) = default;

    /**
     * @brief Clear all participants
     * 
     */
    void Clear();

    /**
     * @brief Add 
     * 
     * @param behavior 
     */
    void Admit(Participant participant);

    /**
     * @brief Load from a vector of participants
     * 
     */
    holo::bool_t Load(std::vector<Participant> const&);

    /**
     * @brief Get the Expected Participants 
     * 
     * @return Expected participants 
     */
    std::vector<Participant> const GetExpectedParticipants() const;

    /**
     * @brief Get all the Participants 
     * 
     * @return All the participants
     */
    std::vector<Participant>& GetParticipants();

    /**
     * @brief Whether or not the group has expected participants
     *
     * @return holo::bool_t True, has it; false, none
     */
    holo::bool_t HasExpected() const;

    /**
     * @brief Rollback history
     * 
     * @return holo::bool_t 
     */
    holo::bool_t RollBack();

private:
    void resetAllParticipantsExpected();

private:
    /// A group of participants
    std::vector<Participant> participants_;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_EXPECT_EVALUATE_PARTICIPANT_GROUP_H_ */