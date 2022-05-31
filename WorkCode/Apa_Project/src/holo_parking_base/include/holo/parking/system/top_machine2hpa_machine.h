#ifndef TOP_MACHINE2HPA_MACHINE_H
#define TOP_MACHINE2HPA_MACHINE_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo {
namespace parking {
namespace system {

class HPAAPAResponse
{
public:
    HPAAPAResponse() noexcept
        : HPA_APA_VD_(0)
        , HPA_APA_St_(0)
    {
    }

    /* data */
    uint8_t GetHPA_APA_VD() const noexcept
    {
        return HPA_APA_VD_;
    }

    void SetHPA_APA_VD(uint8_t const HPA_APA_VD)
    {
        HPA_APA_VD_ = HPA_APA_VD;
    }

    uint8_t GetHPA_APA_St() const noexcept
    {
        return HPA_APA_St_;
    }

    void SetHPA_APA_St(uint8_t const HPA_APA_St)
    {
        HPA_APA_St_ = HPA_APA_St;
    }

    template <size_t ALIGN = 4U> size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(HPA_APA_VD_, HPA_APA_St_);
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
    template <typename S> void Serialize(S &serializer) const
    {
        /* serialize data */
        serializer << HPA_APA_VD_ << HPA_APA_St_ << holo::serialization::align;
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
    template <typename D> void Deserialize(D &deserializer)
    {
        /* deserialize data */
        deserializer >> HPA_APA_VD_ >> HPA_APA_St_ >> holo::serialization::align;
    }

private:
    uint8_t HPA_APA_VD_;
    uint8_t HPA_APA_St_;
};
};      // namespace system
};      // namespace parking
};      // namespace holo
#endif  // TOP_MACHINE2HPA_MACHINE_H
