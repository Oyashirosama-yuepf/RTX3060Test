/**
 *
 * @file handshakea.h
 * @brief This header file defines handshakea from gac
 * @author liaozhenyu(liaozhenyu@holomaitc.com)
 * @date 2022-04-26
 */

#ifndef HANDSHAKEA_H
#define HANDSHAKEA_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace parking_manager
{
class HandShakeA
{
public:
    HandShakeA() noexcept : HandshakeOK_(0U), ArbFault_(0U)
    {
    }

    uint8_t Get_HandshakeOK() const noexcept
    {
        return HandshakeOK_;
    }

    void Set_HandshakeOK(uint8_t const HandshakeOK)
    {
        HandshakeOK_ = HandshakeOK;
    }

    uint8_t Get_ArbFault() const noexcept
    {
        return ArbFault_;
    }

    void Set_ArbFault(uint8_t const ArbFault)
    {
        ArbFault_ = ArbFault;
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
        return holo::serialization::SerializedSize<ALIGN>(HandshakeOK_, ArbFault_);
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
        serializer << HandshakeOK_ << ArbFault_ << holo::serialization::align;
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
        deserializer >> HandshakeOK_ >> ArbFault_ >> holo::serialization::align;
    }

private:
    uint8_t HandshakeOK_;
    uint8_t ArbFault_;
};
}  // namespace parking_manager
}  // namespace parking
}  // namespace holo

#endif  // HANDSHAKEA_H
