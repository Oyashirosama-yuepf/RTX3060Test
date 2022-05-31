/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pilot_state.h
 * @brief This is used to define the state of autopilot
 * @author zhang Yuchen(zhangyuchen@holomatic.com)
 * @date 2020-03-26
 */

#ifndef HOLO_COMMON_PILOT_STATE_H_
#define HOLO_COMMON_PILOT_STATE_H_

#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace common
{
/**
 * @brief This class represents a period of PilotState.
 *
 * @deprecated This class will be deprecated soon
 */
class [[deprecated]] PilotState
{
public:
    /**
     * @brief default constructor
     */
    PilotState() : state_(0)
    {
    }

    PilotState(uint32_t value) : state_(value)
    {
    }

    PilotState& operator=(uint32_t value)
    {
        state_ = value;
        return *this;
    }

    operator uint32_t&() noexcept
    {
        return state_;
    }

    operator uint32_t const&() const noexcept
    {
        return state_;
    }

    /**
     * @brief Get required buffer size to serialize this object
     *
     * @tparam S Class that used to serializing this object
     * @param serializer The instance of Serializer
     *
     * @return Required buffer size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return sizeof(uint32_t);
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
        serializer << state_;
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
        deserializer >> state_;
    }

private:
    uint32_t state_;
};

}  // namespace common
}  // namespace holo
#endif
