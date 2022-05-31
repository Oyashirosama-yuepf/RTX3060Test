/**
 *
 * @file state_machine_from_gac_apa.h
 * @brief This header file defines top machine from gac apa
 * @author liaozhenyu(liaozhenyu@holomaitc.com)
 * @date 2022-02-15
 */

#ifndef TOP_MACHINE_FROM_GAC_APA_H
#define TOP_MACHINE_FROM_GAC_APA_H

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace parking_manager
{
class StateMchineFromGacAndApa
{
public:
    struct HPA_DecisionAttribute
    {
        uint8_t BrkFlag;
        float   BrkDist;
        float   ExpSpd;
    };

    struct HPA_APA_Res
    {
        uint8_t HPA_APA_VD;
        uint8_t HPA_APA_St;
    };

    struct AlgInterface_apptopstatemachine_swc_status
    {
        uint8_t               FcnSelect;
        uint8_t               FcnState;
        HPA_DecisionAttribute App_DecisionAttribute;
        HPA_APA_Res           hpa_apa_res;
        //   uint8_t                            APA_Blocks_Sts_FromTopSM;
    };

    struct AlgInterface_appapastatemachine_swc_status  // apa state machine add
    {
        uint8_t APA_State;
        uint8_t PAS_APAQuitInd_FromAPA;
        uint8_t PAS_APADrvReq_FromAPA;
        uint8_t PAS_APARecInd_FromAPA;
        uint8_t PAS_APAModeInd_FromAPA;
        uint8_t FAPA_PASRemoteParkingMode_FromAPA;
        uint8_t parkOutDir;
        uint8_t APA_SVODFDNetEnable;
        uint8_t APA_SVODFDEnable;
        uint8_t APA_PSDNetEnable;
        uint8_t APA_PSDEnable;
        uint8_t APA_FusionEnable;
        uint8_t APA_PlanEnable;
        uint8_t APA_PSDOutType;
        uint8_t APA_Enable_Complete;
        uint8_t apa_stApaStep;
    };

    StateMchineFromGacAndApa() noexcept
    {
        // init gac
        state_machine_from_gac_.FcnSelect                     = 0U;
        state_machine_from_gac_.FcnState                      = 0U;
        state_machine_from_gac_.App_DecisionAttribute.BrkFlag = 0U;
        state_machine_from_gac_.App_DecisionAttribute.BrkDist = 0.0f;
        state_machine_from_gac_.App_DecisionAttribute.ExpSpd  = 0.0f;
        state_machine_from_gac_.hpa_apa_res.HPA_APA_VD        = 0U;
        state_machine_from_gac_.hpa_apa_res.HPA_APA_St        = 0U;

        // init apa
        state_machine_from_apa_.APA_State                         = 0U;
        state_machine_from_apa_.PAS_APAQuitInd_FromAPA            = 0U;
        state_machine_from_apa_.PAS_APADrvReq_FromAPA             = 0U;
        state_machine_from_apa_.PAS_APARecInd_FromAPA             = 0U;
        state_machine_from_apa_.PAS_APAModeInd_FromAPA            = 0U;
        state_machine_from_apa_.FAPA_PASRemoteParkingMode_FromAPA = 0U;
        state_machine_from_apa_.parkOutDir                        = 0U;
        state_machine_from_apa_.APA_SVODFDNetEnable               = 0U;
        state_machine_from_apa_.APA_SVODFDEnable                  = 0U;
        state_machine_from_apa_.APA_PSDNetEnable                  = 0U;
        state_machine_from_apa_.APA_PSDEnable                     = 0U;
        state_machine_from_apa_.APA_FusionEnable                  = 0U;
        state_machine_from_apa_.APA_PlanEnable                    = 0U;
        state_machine_from_apa_.APA_PSDOutType                    = 0U;
        state_machine_from_apa_.APA_Enable_Complete               = 0U;
        state_machine_from_apa_.apa_stApaStep                     = 0U;
    }
    // gac
    uint8_t GetStateMchineFromGac_FcnSelect() const noexcept
    {
        return state_machine_from_gac_.FcnSelect;
    }

    void SetStateMchineFromGac_FcnSelect(uint8_t const fcn_select)
    {
        state_machine_from_gac_.FcnSelect = fcn_select;
    }

    uint8_t GetStateMchineFromGac_FcnState() const noexcept
    {
        return state_machine_from_gac_.FcnState;
    }

    void SetStateMchineFromGac_FcnState(uint8_t const fcn_state)
    {
        state_machine_from_gac_.FcnState = fcn_state;
    }

    uint8_t GetStateMchineFromGac_HPA_APA_VD() const noexcept
    {
        return state_machine_from_gac_.hpa_apa_res.HPA_APA_VD;
    }

    void SetStateMchineFromGac_HPA_APA_VD(uint8_t const hpa_apa_vd)
    {
        state_machine_from_gac_.hpa_apa_res.HPA_APA_VD = hpa_apa_vd;
    }

    uint8_t GetStateMchineFromGac_HPA_APA_St() const noexcept
    {
        return state_machine_from_gac_.hpa_apa_res.HPA_APA_St;
    }

    void SetStateMchineFromGac_HPA_APA_St(uint8_t const hpa_apa_st)
    {
        state_machine_from_gac_.hpa_apa_res.HPA_APA_St = hpa_apa_st;
    }
    // apa
    uint8_t GetStateMchineFromApa_APA_Enable_Complete() const noexcept
    {
        return state_machine_from_apa_.APA_Enable_Complete;
    }

    void SetStateMchineFromApa_APA_Enable_Complete(uint8_t const apa_enable_complete)
    {
        state_machine_from_apa_.APA_Enable_Complete = apa_enable_complete;
    }

    uint8_t GetStateMchineFromApa_PAS_APAQuitInd_FromAPA() const noexcept
    {
        return state_machine_from_apa_.PAS_APAQuitInd_FromAPA;
    }

    void SetStateMchineFromApa_PAS_APAQuitInd_FromAPA(uint8_t const pas_apaquitind_fromapa)
    {
        state_machine_from_apa_.PAS_APAQuitInd_FromAPA = pas_apaquitind_fromapa;
    }

    uint8_t GetStateMchineFromApa_PAS_APADrvReq_FromAPA() const noexcept
    {
        return state_machine_from_apa_.PAS_APADrvReq_FromAPA;
    }

    void SetStateMchineFromApa_PAS_APADrvReq_FromAPA(uint8_t const pas_apadrvreq_from_apa)
    {
        state_machine_from_apa_.PAS_APADrvReq_FromAPA = pas_apadrvreq_from_apa;
    }

    uint8_t GetStateMchineFromApa_PAS_APARecInd_FromAPA() const noexcept
    {
        return state_machine_from_apa_.PAS_APARecInd_FromAPA;
    }

    void SetStateMchineFromApa_PAS_APARecInd_FromAPA(uint8_t const pas_aparecind_fromapa)
    {
        state_machine_from_apa_.PAS_APARecInd_FromAPA = pas_aparecind_fromapa;
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
        return holo::serialization::SerializedSize<ALIGN>(
            state_machine_from_gac_.FcnSelect, state_machine_from_gac_.FcnState,
            state_machine_from_gac_.hpa_apa_res.HPA_APA_VD, state_machine_from_gac_.hpa_apa_res.HPA_APA_St,
            state_machine_from_apa_.APA_Enable_Complete);
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
        serializer << state_machine_from_gac_.FcnSelect << state_machine_from_gac_.FcnState
                   << state_machine_from_gac_.hpa_apa_res.HPA_APA_VD << state_machine_from_gac_.hpa_apa_res.HPA_APA_St
                   << state_machine_from_apa_.APA_Enable_Complete << holo::serialization::align;
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
        deserializer >> state_machine_from_gac_.FcnSelect >> state_machine_from_gac_.FcnState >>
            state_machine_from_gac_.hpa_apa_res.HPA_APA_VD >> state_machine_from_gac_.hpa_apa_res.HPA_APA_St >>
            state_machine_from_apa_.APA_Enable_Complete >> holo::serialization::align;
    }

private:
    AlgInterface_apptopstatemachine_swc_status state_machine_from_gac_;
    AlgInterface_appapastatemachine_swc_status state_machine_from_apa_;
};
}  // namespace parking_manager
}  // namespace parking
}  // namespace holo
#endif  // TOP_MACHINE_FROM_HPA_APA_H
