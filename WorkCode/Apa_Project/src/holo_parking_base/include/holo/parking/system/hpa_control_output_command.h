/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file hpa_control_output_command.h
 * @brief This header file defines fapa command
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021-07-29
 */

#ifndef HOLO_PARKING_BASE_SYSTEM_HPA_CONTROL_OUTPUT_COMMAND_H_
#define HOLO_PARKING_BASE_SYSTEM_HPA_CONTROL_OUTPUT_COMMAND_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace system
{
/**
 * @brief This class defines ControlOutput with end status and path id. End status 
 *        represent status of finished route within control, path id represent the path tracked.
 */
class ControlOutput
{
public:
    /**
     * @brief default constructor
     */
    ControlOutput() noexcept
      : timestamp_()
      , control_end_status_(0)
      , control_path_id_(0)
    {
    }

    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /* set timestamp_ data. */
    void SetTimestamp( Timestamp const timestamp )
    {
        timestamp_ = timestamp;
    }

    uint8_t GetControlEndStatus() const noexcept
    {
        return control_end_status_;
    }

    /* set control status data. */
    void SetControlEndStatus(uint8_t status)
    {
        control_end_status_ = status;
    }

    uint8_t GetControlPathId() const noexcept
    {
        return control_path_id_;
    }

    /* set control path id */
    void SetControlPathId( uint8_t path_id )
    {
        control_path_id_ = path_id;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     * @tparam ALIGN Byte alignment value
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
                holo::serialization::SerializedSize<ALIGN>( control_end_status_, control_path_id_);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     * @param serializer The buffer to serializer.
     * @return none.
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        /* serialize data */
        serializer << timestamp_ << control_end_status_ << control_path_id_ << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     * @param deserializer The buffer to deserialize from.
     * @return none.
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        /* deserialize data */
        deserializer >> timestamp_ >> control_end_status_ >> control_path_id_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    uint8_t control_end_status_;         ///< control path status
    uint8_t control_path_id_;            ///< control path id

};

}  // namespace system
}  // namespace parking
}  // namespace holo

#endif // HOLO_PARKING_BASE_SYSTEM_HPA_CONTROL_OUTPUT_COMMAND_H_