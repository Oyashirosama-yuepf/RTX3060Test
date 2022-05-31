/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file state.h
 * @brief This header file defines state Object.
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2020-12-04
 */

#ifndef HOLO_PLANNING_STATE_H_
#define HOLO_PLANNING_STATE_H_

#include <exception>

#include <holo/common/alarm.h>
#include <holo/container/details/fixed_size_vector.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace planning
{
/**
 * @addtogroup planning
 * @{
 *
 */

/**
 * @brief This class represents a period of state.
 */
class State
{
public:
    static size_t const VECTOR_SIZE = 8U;
    using VectorType                = holo::container::details::FixedSizeVector<uint32_t, VECTOR_SIZE>;

    /**
     * @brief define MainState enum class
     */
    enum class MainState : uint8_t
    {
        INACTIVE = 0U,
        ACC,
        ACC_HOLD,
        ASSIST,
        ASSIST_HOLD,
        PILOT,
        PILOT_HOLD,
        LLC,
        RLC,
        SAFE_STOP,
        STOP,
        LKA,  // LKA/LDW shall not be used as planning main state. They shall only be used in function state
        LDW,
    };

    /**
     * @brief define LongitudinalState enum class
     */
    enum class LongitudinalState : uint8_t
    {
        NOT_APPLICABLE = 0U,
        ACCELERATE_SPEED,
        UNIFORM_SPEED,
        DECELERATE_SPEED,
        BRAKE,
        STANDSTILL,
        OVERRIDE,
        ABLE_TO_START,
        UNABLE_TO_START,
        ERROR,
    };

    /**
     * @brief define LateralState enum class
     */
    enum class LateralState : uint8_t
    {
        NOT_APPLICABLE = 0U,
        FOLLOW_LANE,
        FOLLOW_VEHICLE,
        FOLLOW_LEFT_BOUND,
        FOLLOW_RIGHT_BOUND,
        OBSTACLE_AVOIDENCE_LEFT,
        OBSTACLE_AVOIDENCE_RIGHT,
        OVERRIDE,
        REQUEST_LANE_CHANGE_LEFT,
        REQUEST_LANE_CHANGE_RIGHT,
        PREPARE_LANE_CHANGE_LEFT,
        PREPARE_LANE_CHANGE_RIGHT,
        CANCEL_LANE_CHANGE_LEFT,
        CANCEL_LANE_CHANGE_RIGHT,
        LANE_CHANGE_LEFT,
        LANE_CHANGE_RIGHT,
        LANE_CORRECTION_LEFT,
        LANE_CORRECTION_RIGHT,
        ERROR,
    };

    /**
     * @brief default constructor
     */
    State()
      : main_state_{MainState::INACTIVE}
      , lateral_state_{LateralState::NOT_APPLICABLE}
      , longitudinal_state_{LongitudinalState::NOT_APPLICABLE}
      , function_total_num_{0}
      , functions_{}
      , following_obs_ids_{}
      , cut_in_obs_ids_{}
      , avoiding_obs_ids_{}
      , lane_change_obs_ids_{}
    {
    }

    /**
     * @brief Set main state
     *
     * @param state main state
     */
    void SetMainState(MainState state) noexcept
    {
        main_state_ = state;
    }

    /**
     * @brief Get main state
     *
     * @return main state
     */
    MainState GetMainState() const noexcept
    {
        return main_state_;
    }

    /**
     * @brief Set lateral state
     *
     * @param state lateral state
     */
    void SetLateralState(LateralState state) noexcept
    {
        lateral_state_ = state;
    }

    /**
     * @brief Set longitudinal state
     *
     * @param state longitudinal state enum
     */
    void SetLongitudinalState(LongitudinalState state) noexcept
    {
        longitudinal_state_ = state;
    }

    /**
     * @brief Get lateral state
     *
     * @return lateral state
     */
    LateralState GetLateralState() const noexcept
    {
        return lateral_state_;
    }

    /**
     * @brief Get longitudinal state
     *
     * @return longitudinal state
     */
    LongitudinalState GetLongitudinalState() const noexcept
    {
        return longitudinal_state_;
    }

    /**
     * @brief Get function state size
     *
     * @return function size
     */
    uint8_t GetFunctionStateSize() const noexcept
    {
        return function_total_num_;
    }

    /**
     * @brief Get function state capacity
     *
     * @return function capacity
     */
    size_t GetFunctionStateCapacity() const noexcept
    {
        return sizeof(functions_) / sizeof(Function);
    }

    /**
     * @brief Get function and alarm pair
     *
     * @param index index element index.
     *
     * @return function and alarm pair
     *
     * @throws throw std::out_of_range exception if index > FunctionStateSize
     */
    std::pair<MainState, holo::common::Alarm> GetFunctionState(size_t index) const
    {
        if (index < GetFunctionStateSize())
        {
            return std::pair<MainState, holo::common::Alarm>(functions_[index].type, functions_[index].alarm);
        }
        else
        {
            throw std::out_of_range("");
        }
    }

    /**
     * @brief Set function alarm
     *
     * @param function function value
     * @param alarm alarm value
     *
     * @throws holo::exception::OutOfRangeException if function num > capacity 16U
     */
    void SetFunctionAlarm(MainState function, holo::common::Alarm alarm)
    {
        for (size_t i = 0; i < function_total_num_; i++)
        {
            if (functions_[i].type == function)
            {
                functions_[i].alarm = alarm;
                return;
            }
        }
        if (function_total_num_ < (sizeof(functions_) / sizeof(Function)))
        {
            functions_[function_total_num_].alarm = alarm;
            functions_[function_total_num_].type  = function;
            function_total_num_ += 1;
        }
        else
        {
            throw holo::exception::OutOfRangeException("");
        }
    }

    /**
     * @brief Get function alarm
     *
     * @param function function value
     *
     * @return alarm return 0xFFFF if if function is not exist
     */
    holo::common::Alarm GetFunctionAlarm(MainState function)
    {
        for (size_t i = 0; i < function_total_num_; i++)
        {
            if (functions_[i].type == function)
            {
                return functions_[i].alarm;
            }
        }
        return 0xFFFF;
    }

    /**
     * @brief Function activable or not
     *
     * @return function activable result
     */
    bool_t IsFunctionActivable(MainState function)
    {
        for (size_t i = 0; i < function_total_num_; i++)
        {
            if (functions_[i].type == function)
            {
                if (static_cast<uint16_t>(functions_[i].alarm) == 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        return false;
    }

    /**
     * @brief Remove function
     *
     * @return remove function result
     */
    bool_t RemoveFunction(MainState function)
    {
        for (size_t i = 0; i < function_total_num_; i++)
        {
            if (functions_[i].type == function)
            {
                (void)std::copy(&functions_[i + 1], &functions_[function_total_num_], &functions_[i]);
                function_total_num_ -= 1;
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Clear function state
     */
    void ClearFunctionState() noexcept
    {
        function_total_num_ = 0U;
    }

    /**
     * @brief Set following obstacle id list with copy construct
     *
     * @param list the following obstacle id list
     */
    void SetFollowingObsIds(VectorType const& list) noexcept
    {
        following_obs_ids_ = list;
    }

    /**
     * @brief Set following obstacle id list with move construct
     *
     * @param list the following obstacle id list
     */
    void SetFollowingObsIds(VectorType&& list) noexcept
    {
        following_obs_ids_ = std::move(list);
    }

    /**
     * @brief Set following obstacle id list with the contents of the range [first, last]
     *
     * @param first start of range to copy elements
     * @param last end of range to copy elements
     *
     * @throws std::bad_alloc if (last - first) > VECTOR_SIZE 8U
     */
    template <typename InputIt>
    void SetFollowingObsIds(InputIt first, InputIt last)
    {
        following_obs_ids_.assign(first, last);
    }

    /**
     * @brief Get const following obstacle id list
     *
     * @return const following obstacle id list
     */
    VectorType const& GetFollowingObsIds() const noexcept
    {
        return following_obs_ids_;
    }

    /**
     * @brief Get following obstacle id list
     *
     * @return following obstacle id list
     */
    VectorType& GetFollowingObsIds() noexcept
    {
        return following_obs_ids_;
    }

    /**
     * @brief Set cut in obstacle id list
     *
     * @param list the cut in obstacle id list
     */
    void SetCutInObsIds(VectorType const& list) noexcept
    {
        cut_in_obs_ids_ = list;
    }

    /**
     * @brief Set cut in obstacle id list
     *
     * @param list the cut in obstacle id list
     */
    void SetCutInObsIds(VectorType&& list) noexcept
    {
        cut_in_obs_ids_ = std::move(list);
    }

    /**
     * @brief Set cut in obstacle id list with the contents of the range [first, last]
     *
     * @param first start of range to copy elements
     * @param last end of range to copy elements
     *
     * @throws std::bad_alloc if (last - first) > VECTOR_SIZE 8U
     */
    template <typename InputIt>
    void SetCutInObsIds(InputIt first, InputIt last)
    {
        cut_in_obs_ids_.assign(first, last);
    }

    /**
     * @brief Get const cut in obstacle id list
     *
     * @return const cut in obstacle id list
     */
    VectorType const& GetCutInObsIds() const noexcept
    {
        return cut_in_obs_ids_;
    }

    /**
     * @brief Get cut in obstacle id list
     *
     * @return cut in obstacle id list
     */
    VectorType& GetCutInObsIds() noexcept
    {
        return cut_in_obs_ids_;
    }

    /**
     * @brief Set avoiding obstacle id list
     *
     * @param list the avoiding obstacle id list
     */
    void SetAvoidingObsIds(VectorType const& list) noexcept
    {
        avoiding_obs_ids_ = list;
    }

    /**
     * @brief Set avoiding obstacle id list
     *
     * @param list the avoiding obstacle id list
     */
    void SetAvoidingObsIds(VectorType&& list) noexcept
    {
        avoiding_obs_ids_ = std::move(list);
    }

    /**
     * @brief Set cut in obstacle id list with the contents of the range [first, last]
     *
     * @param first start of range to copy elements
     * @param last end of range to copy elements
     *
     * @throws std::bad_alloc if (last - first) > VECTOR_SIZE 8U
     */
    template <typename InputIt>
    void SetAvoidingObsIds(InputIt first, InputIt last)
    {
        avoiding_obs_ids_.assign(first, last);
    }

    /**
     * @brief Get const avoiding obstacle id list
     *
     * @return const avoiding obstacle id list
     */
    VectorType const& GetAvoidingObsIds() const noexcept
    {
        return avoiding_obs_ids_;
    }

    /**
     * @brief Get avoiding obstacle id list
     *
     * @return avoiding obstacle id list
     */
    VectorType& GetAvoidingObsIds() noexcept
    {
        return avoiding_obs_ids_;
    }

    /**
     * @brief Set lane change obstacle id list
     *
     * @param list the lane change obstacle id list
     */
    void SetLaneChangeObsIds(VectorType const& list) noexcept
    {
        lane_change_obs_ids_ = list;
    }

    /**
     * @brief Set lane change obstacle id list
     *
     * @param list the lane change obstacle id list
     */
    void SetLaneChangeObsIds(VectorType&& list) noexcept
    {
        lane_change_obs_ids_ = std::move(list);
    }

    /**
     * @brief Set cut in obstacle id list with the contents of the range [first, last]
     *
     * @param first start of range to copy elements
     * @param last end of range to copy elements
     *
     * @throws std::bad_alloc if (last - first) > VECTOR_SIZE 8U
     */
    template <typename InputIt>
    void SetLaneChangeObsIds(InputIt first, InputIt last)
    {
        lane_change_obs_ids_.assign(first, last);
    }

    /**
     * @brief Get const lane change obstacle id list
     *
     * @return const lane change obstacle id list
     */
    VectorType const& GetLaneChangeObsIds() const noexcept
    {
        return lane_change_obs_ids_;
    }

    /**
     * @brief Get lane change obstacle id list
     *
     * @return lane change obstacle id list
     */
    VectorType& GetLaneChangeObsIds() noexcept
    {
        return lane_change_obs_ids_;
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
        return holo::serialization::SerializedSize<ALIGN>(static_cast<uint16_t>(main_state_),
                                                  static_cast<uint8_t>(lateral_state_),
                                                  static_cast<uint8_t>(longitudinal_state_), function_total_num_) +
               holo::serialization::AlignedSize<ALIGN>(sizeof(Function) * function_total_num_) +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(following_obs_ids_.size())) +
               holo::serialization::AlignedSize<ALIGN>(sizeof(VectorType::value_type) * following_obs_ids_.size()) +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(cut_in_obs_ids_.size())) +
               holo::serialization::AlignedSize<ALIGN>(sizeof(VectorType::value_type) * cut_in_obs_ids_.size()) +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(avoiding_obs_ids_.size())) +
               holo::serialization::AlignedSize<ALIGN>(sizeof(VectorType::value_type) * avoiding_obs_ids_.size()) +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(lane_change_obs_ids_.size())) +
               holo::serialization::AlignedSize<ALIGN>(sizeof(VectorType::value_type) * lane_change_obs_ids_.size());
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << static_cast<uint16_t>(main_state_) << static_cast<uint8_t>(lateral_state_)
                   << static_cast<uint8_t>(longitudinal_state_) << function_total_num_;

        for (size_t i = 0; i < function_total_num_; ++i)
        {
            serializer << static_cast<uint16_t>(functions_[i].type) << static_cast<uint16_t>(functions_[i].alarm);
        }

        uint32_t follow_obs_size = following_obs_ids_.size();
        serializer << follow_obs_size;
        for (size_t i = 0; i < follow_obs_size; ++i)
        {
            serializer << following_obs_ids_[i];
        }

        uint32_t cut_in_obs_size = cut_in_obs_ids_.size();
        serializer << cut_in_obs_size;
        for (size_t i = 0; i < cut_in_obs_size; ++i)
        {
            serializer << cut_in_obs_ids_[i];
        }

        uint32_t avoiding_obs_size = avoiding_obs_ids_.size();
        serializer << avoiding_obs_size;
        for (size_t i = 0; i < avoiding_obs_size; ++i)
        {
            serializer << avoiding_obs_ids_[i];
        }

        uint32_t lane_change_obs_size = lane_change_obs_ids_.size();
        serializer << lane_change_obs_size;
        for (size_t i = 0; i < lane_change_obs_size; ++i)
        {
            serializer << lane_change_obs_ids_[i];
        }
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint16_t main_state         = 0U;
        uint8_t  lateral_state      = 0U;
        uint8_t  longitudinal_state = 0U;

        deserializer >> holo::serialization::align >> main_state >> lateral_state >> longitudinal_state >> function_total_num_;

        main_state_         = static_cast<MainState>(main_state);
        lateral_state_      = static_cast<LateralState>(lateral_state);
        longitudinal_state_ = static_cast<LongitudinalState>(longitudinal_state);

        for (size_t i = 0; i < function_total_num_; i++)
        {
            uint16_t main_state_value;
            uint16_t alarm_value;
            deserializer >> main_state_value >> alarm_value;
            functions_[i].type  = static_cast<MainState>(main_state_value);
            functions_[i].alarm = alarm_value;
        }

        uint32_t follow_obs_size = 0;
        deserializer >> follow_obs_size;
        following_obs_ids_.resize(follow_obs_size, 0);
        for (uint32_t i = 0; i < follow_obs_size; i++)
        {
            deserializer >> following_obs_ids_[i];
        }

        uint32_t cut_in_obs_size = 0;
        deserializer >> cut_in_obs_size;
        cut_in_obs_ids_.resize(cut_in_obs_size, 0);
        for (uint32_t i = 0; i < cut_in_obs_size; i++)
        {
            deserializer >> cut_in_obs_ids_[i];
        }

        uint32_t avoiding_obs_size = 0;
        deserializer >> avoiding_obs_size;
        avoiding_obs_ids_.resize(avoiding_obs_size, 0);
        for (uint32_t i = 0; i < avoiding_obs_size; i++)
        {
            deserializer >> avoiding_obs_ids_[i];
        }

        uint32_t lane_change_obs_size = 0;
        deserializer >> lane_change_obs_size;
        lane_change_obs_ids_.resize(lane_change_obs_size, 0);
        for (uint32_t i = 0; i < lane_change_obs_size; i++)
        {
            deserializer >> lane_change_obs_ids_[i];
        }

        deserializer >> holo::serialization::align;
    }

private:
    struct Function
    {
        MainState           type;
        holo::common::Alarm alarm;
    };

    MainState main_state_;  ///< Current planning state

    LateralState      lateral_state_;       ///< Current lateral state
    LongitudinalState longitudinal_state_;  ///< Current longitudinal state

    uint32_t function_total_num_;  ///< total function num
    Function functions_[16U];      ///< function list

    VectorType following_obs_ids_;    ///< Following obstacle id list
    VectorType cut_in_obs_ids_;       ///< Cut in obstacle id list
    VectorType avoiding_obs_ids_;     ///< Avoiding obstacle id list
    VectorType lane_change_obs_ids_;  ///< Lane change obstacle id list
};
/**
 * @}
 *
 */
}  // namespace planning
}  // namespace holo

#endif
