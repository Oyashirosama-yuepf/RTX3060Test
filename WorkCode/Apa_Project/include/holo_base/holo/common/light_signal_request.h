/**
 * @file light_signal_request.h
 * @brief This is used to describe the light signal request
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2019-11-29
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_COMMON_LIGHT_SIGNAL_REQUEST_H_
#define HOLO_COMMON_LIGHT_SIGNAL_REQUEST_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
/**
 * @ingroup common
 *
 * @brief this class is used to describe the light signal request
 */
class LightSignalRequest
{
public:
    using Timestamp = common::Timestamp;
    /**
     * @brief default constructor
     */
    LightSignalRequest() noexcept : timestamp_(), light_command_(), reserved_{}
    {
    }

    /* timestamp_ */
    const Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    Timestamp& GetTimestamp() noexcept
    {
        return timestamp_;
    }

    void SetTimestamp(const Timestamp& timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    /* left_turn_signal_ */
    bool_t GetLeftTurnSignal() const noexcept
    {
        return light_command_.left_turn_signal_;
    }

    void SetLeftTurnSignal(bool_t left_turn_signal) noexcept
    {
        light_command_.left_turn_signal_ = left_turn_signal;
    }

    /* right_turn_signal_ */
    bool_t GetRightTurnSignal() const noexcept
    {
        return light_command_.right_turn_signal_;
    }

    void SetRightTurnSignal(bool_t right_turn_signal) noexcept
    {
        light_command_.right_turn_signal_ = right_turn_signal;
    }

    /* hazard_flasher_ */
    bool_t GetHazardFlasher() const noexcept
    {
        return light_command_.hazard_flasher_;
    }

    void SetHazardFlasher(bool_t hazard_flasher) noexcept
    {
        light_command_.hazard_flasher_ = hazard_flasher;
    }

    /* brake_light_ */
    bool_t GetBrakeLight() const noexcept
    {
        return light_command_.brake_light_;
    }

    void SetBrakeLight(bool_t brake_light) noexcept
    {
        light_command_.brake_light_ = brake_light;
    }

    /**
     * @brief Get light command.
     *
     * @return Light command.
     */
    holo::uint16_t GetLightCommand() const noexcept
    {
        return static_cast<uint16_t>(static_cast<uint16_t>(light_command_.brake_light_) << 2) |
               static_cast<uint16_t>(static_cast<uint16_t>(light_command_.hazard_flasher_) << 5) |
               static_cast<uint16_t>(static_cast<uint16_t>(light_command_.right_turn_signal_) << 6) |
               static_cast<uint16_t>(static_cast<uint16_t>(light_command_.left_turn_signal_) << 7);
    }

    /**
     * @brief Set light command.
     *
     * @param value Light command.
     */
    void SetLightCommand(holo::uint16_t value) noexcept
    {
        light_command_.brake_light_       = value >> 2;
        light_command_.hazard_flasher_    = value >> 5;
        light_command_.right_turn_signal_ = value >> 6;
        light_command_.left_turn_signal_  = value >> 7;
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
        holo::uint16_t light_command;
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(light_command, reserved_[0], reserved_[1], reserved_[2],
                                                          reserved_[3], reserved_[4], reserved_[5]);
    }

    /**
     * @brief Serialize coordinate to buffer.
     *
     * @param serializer The serializer to use.
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << GetLightCommand() << reserved_[0] << reserved_[1] << reserved_[2] << reserved_[3]
                   << reserved_[4] << reserved_[5] << holo::serialization::align;
    }

    /**
     * @brief Deserialize coordinate from buffer.
     *
     * @param serializer The deserializer to use.
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint16_t tmp;
        deserializer >> timestamp_ >> tmp >> reserved_[0] >> reserved_[1] >> reserved_[2] >> reserved_[3] >>
            reserved_[4] >> reserved_[5] >> holo::serialization::align;
        SetLightCommand(tmp);
    }

private:
    Timestamp timestamp_;  ///< timestamp

    struct
    {
        uint16_t : 1;                     ///< Rear fog light: 1=on, 0=off
        uint16_t : 1;                     ///< Front fog light: 1=on, 0=off
        uint16_t brake_light_ : 1;        ///< Break light signal: 1=on, 0=off
        uint16_t : 1;                     ///< High beam light: 1=on, 0=off
        uint16_t : 1;                     ///< Low beam light: 1=on, 0=off
        uint16_t hazard_flasher_ : 1;     ///< hazard flasher: 1=on, 0=off
        uint16_t right_turn_signal_ : 1;  ///< Right turn signal: 1=on, 0=off
        uint16_t left_turn_signal_ : 1;   ///< Left turn signal: 1=on, 0=off
        uint16_t : 8;
    } light_command_;

    uint8_t reserved_[6];  ///< reserved for data alignment.
};
static_assert(sizeof(LightSignalRequest) == 16, "");

} /* namespace holo */

#endif
