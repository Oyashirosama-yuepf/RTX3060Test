/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file hpa_event_request.h
 * @brief This header file defines hpa event request
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021-05-29
 */

#ifndef HOLO_PARKING_BASE_SYSTEM_HPA_EVENT_REQUEST_H_
#define HOLO_PARKING_BASE_SYSTEM_HPA_EVENT_REQUEST_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace system
{
/**
 * @brief This class defines hpa event request
 */
class HpaEventRequest
{
public:

    enum class HpaEventType : uint8_t
    {
        NO_EVENT             = 0U,
        ENTER_HPA            = 1U,
        QUIT_BUTTON          = 2U,
        RETURN_BUTTON        = 3U,
        RECEIVE_ACCEPT       = 4U,
        START_USE            = 5U,
        CREATE_PATH_PARK_IN  = 6U,
        CREATE_PATH_PARK_OUT = 7U,
        SAVE_PATH            = 8U,
        DELETE_PATH          = 9U,
        EDIT_PATH            = 10U,
        START_PARKING        = 11U,
        RESUME_PARKING       = 12U,
        SET_START_POINT      = 13U,
        SET_END_POINT        = 14U,
        SET_SUCCESS          = 15U,
        RETRY                = 16U,
        CHANGE_PATH          = 17U,
        CONDITION_CHECK      = 18U,
        PATH_MATCHED         = 19U,
        PATH_LEARNING        = 20U,
    };

    /**
     * @brief default constructor
     */
    HpaEventRequest() noexcept
      : timestamp_()
      , park_type_(0)
      , park_mode_(0)
      , event_id_(HpaEventType::NO_EVENT)
      , path_index_(0)
      , path_slot_(0)
    {
    }

    /* timestamp_ */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    void SetTimestamp(Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    /* park_type_ */
    uint8_t GetParkType() const noexcept
    {
        return park_type_;
    }

    void SetParkType(uint8_t const park_type)
    {
        park_type_ = park_type;
    }

    /* park_mode_ */
    uint8_t GetParkMode() const noexcept
    {
        return park_mode_;
    }

    void SetParkMode(uint8_t const park_mode)
    {
        park_mode_ = park_mode;
    }

    /* event_id_ */
    HpaEventType GetEventId() const noexcept
    {
        return event_id_;
    }

    void SetEventId(HpaEventType const event_id)
    {
        event_id_ = event_id;
    }

    /* path_index_ */
    uint8_t GetPathIndex() const noexcept
    {
        return path_index_;
    }

    void SetPathIndex(uint8_t const path_index)
    {
        path_index_ = path_index;
    }

    /* path_slot_ */
    uint8_t GetPathSlot() const noexcept
    {
        return path_slot_;
    }

    void SetPathSlot(uint8_t const path_slot)
    {
        path_slot_ = path_slot;
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
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(park_type_, park_mode_, static_cast<uint8_t>(event_id_), path_index_, path_slot_);
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
        /* serialize data */
        serializer << timestamp_ << park_type_ << park_mode_ << static_cast<uint8_t>(event_id_) << path_index_ << path_slot_
                   << holo::serialization::align;
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
        uint8_t event_id;
        /* deserialize data */
        deserializer >> timestamp_ >> park_type_ >> park_mode_ >> event_id >> path_index_ >> path_slot_
                     >> holo::serialization::align;
        event_id_ = static_cast<HpaEventType>(event_id);
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    uint8_t      park_type_; // 0: apa; 1: avm; 2: hpa
    uint8_t      park_mode_; // 0: parkin; 1: parkout
    HpaEventType event_id_;; // 0: cross; 1: parallel
    uint8_t      path_index_; // 1~10: path index
    uint8_t      path_slot_; // 0: fixed; 1: passingby
};

}  // namespace system
}  // namespace parking
}  // namespace holo

#endif
