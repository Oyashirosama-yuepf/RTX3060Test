/**
 *
 * @file parking_manager_command.h
 * @brief This header file defines parking manager command
 * @author liaozhenyu(liaozhenyu@holomaitc.com)
 * @date 2022-02-15
 */

#ifndef PARKING_MANAGER_COMMAND_H
#define PARKING_MANAGER_COMMAND_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
namespace holo
{
namespace parking
{
namespace parking_manager
{
class ParkingManagerCommand
{
public:
    ParkingManagerCommand() noexcept
      : timestamp_()
      , hpa_command_(0U)
      , route_id_(0U)
      , slot_send_en_(0U)
      , vslam_command_(0U)
      , hpa_tidl_command_(0U)
      , avm_command_(0U)
      , slot_mang_command_(0U)
      , map_server_command_(0U)
      , park_type_(0U)
    {
    }
    // timestamp
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    void SetTimestamp(Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }
    // hpa command
    uint8_t GetHpaCommand() const noexcept
    {
        return hpa_command_;
    }

    void SetHpaCommand(uint8_t const hpa_command)
    {
        hpa_command_ = hpa_command;
    }
    // route id
    uint8_t GetRouteId() const noexcept
    {
        return route_id_;
    }

    void SetRouteId(uint8_t const route_id)
    {
        route_id_ = route_id;
    }
    // slot send en
    uint8_t GetSlotSendEN() const noexcept
    {
        return slot_send_en_;
    }

    void SetSlotSendEN(uint8_t const slot_send_en)
    {
        slot_send_en_ = slot_send_en;
    }
    // vslam command
    uint8_t GetVSlamCommand() const noexcept
    {
        return vslam_command_;
    }

    void SetVSlamCommand(uint8_t const vslam_command)
    {
        vslam_command_ = vslam_command;
    }
    // hpa tidl command
    uint8_t GetHpaTidlCommand() const noexcept
    {
        return hpa_tidl_command_;
    }

    void SetHpaTidlCommand(uint8_t const hpa_tidl_command)
    {
        hpa_tidl_command_ = hpa_tidl_command;
    }
    // avm command
    uint8_t GetAvmCommand() const noexcept
    {
        return avm_command_;
    }

    void SetAvmCommand(uint8_t const avm_command)
    {
        avm_command_ = avm_command;
    }
    // slot mang command
    uint8_t GetSlotMangCommand() const noexcept
    {
        return slot_mang_command_;
    }

    void SetSlotMangCommand(uint8_t const slot_mang_command)
    {
        slot_mang_command_ = slot_mang_command;
    }
    // map server command
    uint8_t GetMapServerCommand() const noexcept
    {
        return map_server_command_;
    }

    void SetMapServerCommand(uint8_t const map_server_command)
    {
        map_server_command_ = map_server_command;
    }

    // park type
    uint8_t GetParkType() const noexcept
    {
        return park_type_;
    }

    void SetParkType(uint8_t const park_type)
    {
        park_type_ = park_type;
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
               holo::serialization::SerializedSize<ALIGN>(hpa_command_, route_id_, slot_send_en_, vslam_command_,
                                                          hpa_tidl_command_, avm_command_, slot_mang_command_,
                                                          map_server_command_, park_type_);
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
        serializer << timestamp_ << hpa_command_ << route_id_ << slot_send_en_ << vslam_command_ << hpa_tidl_command_
                   << avm_command_ << slot_mang_command_ << map_server_command_ << park_type_ << holo::serialization::align;
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
        /* deserialize data */
        deserializer >> timestamp_ >> hpa_command_ >> route_id_ >> slot_send_en_ >> vslam_command_ >>
            hpa_tidl_command_ >> avm_command_ >> slot_mang_command_ >> map_server_command_ >>
            park_type_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;

    uint8_t hpa_command_;
    uint8_t route_id_;
    uint8_t slot_send_en_;
    uint8_t vslam_command_;
    uint8_t hpa_tidl_command_;
    uint8_t avm_command_;
    uint8_t slot_mang_command_;
    uint8_t map_server_command_;
    uint8_t park_type_;
};
}  // namespace parking_manager
}  // namespace parking
}  // namespace holo
#endif  // PARKING_MANAGER_COMMAND_H
