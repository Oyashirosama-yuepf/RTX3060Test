/**
 *
 * @file hpa_status.h
 * @brief This header file defines hpa status
 * @author liaozhenyu(liaozhenyu@holomaitc.com)
 * @date 2022-04-26
 */

#ifndef HPA_STATUS_H
#define HPA_STATUS_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace parking_manager
{
class HpaStatus
{
public:
    HpaStatus() noexcept : Hpa_State_(0U), PAS_APAModeInd_FromHPA_(0U), HPA_Active_Req_(0U), HPA_ArbState_(0U)
    {
    }

    uint8_t Get_Hpa_State() const noexcept
    {
        return Hpa_State_;
    }

    void Set_Hpa_State(uint8_t const Hpa_State)
    {
        Hpa_State_ = Hpa_State;
    }

    uint8_t Get_PAS_APAModeInd_FromHPA() const noexcept
    {
        return PAS_APAModeInd_FromHPA_;
    }

    void Set_PAS_APAModeInd_FromHPA(uint8_t const PAS_APAModeInd_FromHPA)
    {
        PAS_APAModeInd_FromHPA_ = PAS_APAModeInd_FromHPA;
    }

    uint8_t Get_HPA_Active_Req() const noexcept
    {
        return HPA_Active_Req_;
    }

    void Set_HPA_Active_Req(uint8_t const HPA_Active_Req)
    {
        HPA_Active_Req_ = HPA_Active_Req;
    }

    uint8_t Get_HPA_ArbState() const noexcept
    {
        return HPA_ArbState_;
    }

    void Set_HPA_ArbState(uint8_t const HPA_ArbState)
    {
        HPA_ArbState_ = HPA_ArbState;
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
        return holo::serialization::SerializedSize<ALIGN>(Hpa_State_, PAS_APAModeInd_FromHPA_, HPA_Active_Req_,
                                                          HPA_ArbState_);
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
        serializer << Hpa_State_ << PAS_APAModeInd_FromHPA_ << HPA_Active_Req_ << HPA_ArbState_
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
        /* deserialize data */
        deserializer >> Hpa_State_ >> PAS_APAModeInd_FromHPA_ >> HPA_Active_Req_ >> HPA_ArbState_ >>
            holo::serialization::align;
    }

private:
    uint8_t Hpa_State_;
    uint8_t PAS_APAModeInd_FromHPA_;
    uint8_t HPA_Active_Req_;
    uint8_t HPA_ArbState_;
};
}  // namespace parking_manager
}  // namespace parking
}  // namespace holo

#endif  // HPA_STATUS_H
