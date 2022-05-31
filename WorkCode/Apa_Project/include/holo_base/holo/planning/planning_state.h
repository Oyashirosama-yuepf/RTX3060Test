/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file planning_state.h
 * @brief This header file defines planning state Object.
 * @author Zhang Yuchen(zhangyuchen@holomatic.com)
 * @date 2020-05-09
 */

#ifndef HOLO_PLANNING_PLANNING_STATE_H_
#define HOLO_PLANNING_PLANNING_STATE_H_

#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

#include <vector>

namespace holo
{
namespace planning
{
/**
 * @brief This class represents a period of PlanningState.
 *
 * @deprecated Deprecated soon, please use holo::planning::State
 */
class [[deprecated]] PlanningState
{
public:
    /**
     * @brief default constructor
     */
    PlanningState() : curr_state_(0), activatable_mode_(0)
    {
    }

    /**
     * @brief construct with mode_num
     */
    explicit PlanningState(uint32_t mode_num) : curr_state_(0), activatable_mode_(0), error_code_list_(mode_num, 0)
    {
    }

    /**
     * @brief Destructor
     */
    ~PlanningState() = default;

    /**
     * @brief Get the number of activatable modes
     *
     * @return The number of activatable modes
     */
    uint32_t GetModeNum() const
    {
        return error_code_list_.size();
    }

    /**
     * @brief Set the number of activatable modes and resize error code list
     *
     * @param num The number of activatable modes
     */
    void SetModeNum(uint32_t num)
    {
        error_code_list_.resize(num, 0);
    }

    /**
     * @brief Set current state
     *
     * @param state Current state
     */
    void SetCurrentState(uint32_t state) noexcept
    {
        curr_state_ = state;
    }

    /**
     * @brief Get current state
     *
     * @return Current state
     */
    uint32_t GetCurrentState() const noexcept
    {
        return curr_state_;
    }

    /**
     * @brief Set activatable mode
     *
     * @param mode Whole activatable mode
     */
    void SetActivatableMode(uint32_t mode) noexcept
    {
        activatable_mode_ = mode;
    }

    /**
     * @brief Check if the mode is activatable
     *
     * @param mode_index The index of the mode wanted to check
     *
     * @return true if the mode is activatable, false otherwise
     */
    bool_t IsActivatable(uint32_t mode_index) const noexcept
    {
        if (mode_index < 32)
        {
            return activatable_mode_ & (1 << mode_index);
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief Set error code
     *
     * @param error_code The error code
     * @param mode_index The index of the mode wanted to set
     */
    void SetErrorCode(uint32_t error_code, uint32_t mode_index)
    {
        if (mode_index < error_code_list_.size())
        {
            error_code_list_[mode_index] = error_code;
        }
    }

    /**
     * @brief Get error code
     *
     * @param mode_index The index of the mode wanted to get
     *
     * @return The error code
     */
    uint32_t GetErrorCode(uint32_t mode_index) const
    {
        if (mode_index < error_code_list_.size())
        {
            return error_code_list_[mode_index];
        }
        else
        {
            return 0;
        }
    }

    /**
     * @brief Set following obstacle id list
     *
     * @param list The following obstacle id list
     */
    void SetFollowingObsIds(std::vector<uint32_t> const& list)
    {
        following_obs_ids_ = list;
    }

    /**
     * @brief Get const following obstacle id list
     *
     * @return Const following obstacle id list
     */
    std::vector<uint32_t> const& GetFollowingObsIds() const
    {
        return following_obs_ids_;
    }

    /**
     * @brief Get following obstacle id list
     *
     * @return Following obstacle id list
     */
    std::vector<uint32_t>& GetFollowingObsIds()
    {
        return following_obs_ids_;
    }

    /**
     * @brief Set cut in obstacle id list
     *
     * @param list The cut in obstacle id list
     */
    void SetCutInObsIds(std::vector<uint32_t> const& list)
    {
        cut_in_obs_ids_ = list;
    }

    /**
     * @brief Get const cut in obstacle id list
     *
     * @return Const cut in obstacle id list
     */
    std::vector<uint32_t> const& GetCutInObsIds() const
    {
        return cut_in_obs_ids_;
    }

    /**
     * @brief Get cut in obstacle id list
     *
     * @return Cut in obstacle id list
     */
    std::vector<uint32_t>& GetCutInObsIds()
    {
        return cut_in_obs_ids_;
    }

    /**
     * @brief Set avoiding obstacle id list
     *
     * @param list The avoiding obstacle id list
     */
    void SetAvoidingObsIds(std::vector<uint32_t> const& list)
    {
        avoiding_obs_ids_ = list;
    }

    /**
     * @brief Get const avoiding obstacle id list
     *
     * @return Const avoiding obstacle id list
     */
    std::vector<uint32_t> const& GetAvoidingObsIds() const
    {
        return avoiding_obs_ids_;
    }

    /**
     * @brief Get avoiding obstacle id list
     *
     * @return Avoiding obstacle id list
     */
    std::vector<uint32_t>& GetAvoidingObsIds()
    {
        return avoiding_obs_ids_;
    }

    /**
     * @brief Set lane change obstacle id list
     *
     * @param list The lane change obstacle id list
     */
    void SetLaneChangeObsIds(std::vector<uint32_t> const& list)
    {
        lane_change_obs_ids_ = list;
    }

    /**
     * @brief Get const lane change obstacle id list
     *
     * @return Const lane change obstacle id list
     */
    std::vector<uint32_t> const& GetLaneChangeObsIds() const
    {
        return lane_change_obs_ids_;
    }

    /**
     * @brief Get lane change obstacle id list
     *
     * @return Lane change obstacle id list
     */
    std::vector<uint32_t>& GetLaneChangeObsIds()
    {
        return lane_change_obs_ids_;
    }

    /**
     * @brief Get required buffer size to serialize this object
     *
     * @tparam S Class that used to serializing this object
     * @param serializer The instance of Serializer
     *
     * @return Required buffer size
     */
    template <typename S>
    size_t GetSerializedSize(S const&) const noexcept
    {
        constexpr size_t Alignment = S::GetAlignment();

        // curr state and activatable mode aligned size
        size_t aligned_size = sizeof(curr_state_) + sizeof(activatable_mode_);

        // error_code_list_ aligned size
        aligned_size += sizeof(uint32_t) + error_code_list_.size() * sizeof(uint32_t);

        // following obs ids aligned size
        aligned_size += sizeof(uint32_t) + following_obs_ids_.size() * sizeof(uint32_t);

        // cut in obs ids aligned size
        aligned_size += sizeof(uint32_t) + cut_in_obs_ids_.size() * sizeof(uint32_t);

        // avoiding obs ids aligned size
        aligned_size += sizeof(uint32_t) + avoiding_obs_ids_.size() * sizeof(uint32_t);

        // lane change obs ids aligned size
        aligned_size += sizeof(uint32_t) + lane_change_obs_ids_.size() * sizeof(uint32_t);

        // align
        aligned_size = holo::serialization::AlignedSize<Alignment>(aligned_size);

        return aligned_size;
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
        // set curr state and activatable mode
        serializer << curr_state_ << activatable_mode_;

        // set error code list
        uint32_t error_list_size = error_code_list_.size();
        serializer << error_list_size;
        for (uint32_t i = 0; i < error_list_size; ++i)
        {
            serializer << error_code_list_[i];
        }

        // set follow obs ids
        uint32_t follow_obs_size = following_obs_ids_.size();
        serializer << follow_obs_size;
        for (uint32_t i = 0; i < follow_obs_size; ++i)
        {
            serializer << following_obs_ids_[i];
        }

        // set cut in obs ids
        uint32_t cut_in_obs_size = cut_in_obs_ids_.size();
        serializer << cut_in_obs_size;
        for (uint32_t i = 0; i < cut_in_obs_size; ++i)
        {
            serializer << cut_in_obs_ids_[i];
        }

        // set avoiding obs ids
        uint32_t avoiding_obs_size = avoiding_obs_ids_.size();
        serializer << avoiding_obs_size;
        for (uint32_t i = 0; i < avoiding_obs_size; ++i)
        {
            serializer << avoiding_obs_ids_[i];
        }

        // set lane change obs ids
        uint32_t lane_change_obs_size = lane_change_obs_ids_.size();
        serializer << lane_change_obs_size;
        for (uint32_t i = 0; i < lane_change_obs_size; ++i)
        {
            serializer << lane_change_obs_ids_[i];
        }

        // align
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
        // get curr_state and activatable_mode
        deserializer >> curr_state_ >> activatable_mode_;

        // get error code list
        uint32_t error_list_size = 0;
        deserializer >> error_list_size;
        if (error_list_size != 0)
        {
            error_code_list_.resize(error_list_size, 0);
            for (uint32_t i = 0; i < error_list_size; ++i)
            {
                deserializer >> error_code_list_[i];
            }
        }

        // get follow obs ids
        uint32_t follow_obs_size = 0;
        deserializer >> follow_obs_size;
        if (follow_obs_size != 0)
        {
            following_obs_ids_.resize(follow_obs_size, 0);
            for (uint32_t i = 0; i < follow_obs_size; ++i)
            {
                deserializer >> following_obs_ids_[i];
            }
        }

        // get cut in obs ids
        uint32_t cut_in_obs_size = 0;
        deserializer >> cut_in_obs_size;
        if (cut_in_obs_size != 0)
        {
            cut_in_obs_ids_.resize(cut_in_obs_size, 0);
            for (uint32_t i = 0; i < cut_in_obs_size; ++i)
            {
                deserializer >> cut_in_obs_ids_[i];
            }
        }

        // get avoiding obs ids
        uint32_t avoiding_obs_size = 0;
        deserializer >> avoiding_obs_size;
        if (avoiding_obs_size != 0)
        {
            avoiding_obs_ids_.resize(avoiding_obs_size, 0);
            for (uint32_t i = 0; i < avoiding_obs_size; ++i)
            {
                deserializer >> avoiding_obs_ids_[i];
            }
        }

        // get lane change obs ids
        uint32_t lane_change_obs_size = 0;
        deserializer >> lane_change_obs_size;
        if (lane_change_obs_size != 0)
        {
            lane_change_obs_ids_.resize(lane_change_obs_size, 0);
            for (uint32_t i = 0; i < lane_change_obs_size; ++i)
            {
                deserializer >> lane_change_obs_ids_[i];
            }
        }

        // align
        deserializer >> holo::serialization::align;
    }

private:
    /**
     * @brief Current planning state
     */
    uint32_t curr_state_;

    /**
     * @brief Whole activatable mode
     */
    uint32_t activatable_mode_;

    /**
     * @brief The error code of each mode
     */
    std::vector<uint32_t> error_code_list_;

    /**
     * @brief Following obstacle id list
     */
    std::vector<uint32_t> following_obs_ids_;

    /**
     * @brief Cut in obstacle id list
     */
    std::vector<uint32_t> cut_in_obs_ids_;

    /**
     * @brief Avoiding obstacle id list
     */
    std::vector<uint32_t> avoiding_obs_ids_;

    /**
     * @brief Lane change obstacle id list
     */
    std::vector<uint32_t> lane_change_obs_ids_;
};
}  // namespace planning
}  // namespace holo

#endif
