/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file fapa_command.h
 * @brief This header file defines fapa command
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021-05-29
 */

#ifndef HOLO_PARKING_BASE_SYSTEM_FAPA_COMMAND_H_
#define HOLO_PARKING_BASE_SYSTEM_FAPA_COMMAND_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace system
{
/**
 * @brief This class defines OneByte class for fapa related signals
 */
class OneByte
{
public:
    /**
     * @brief default constructor
     */
    OneByte() noexcept : data_(0)
    {
    }

    /* data */
    uint8_t GetData() const noexcept
    {
        return data_;
    }

    void SetData(uint8_t const data)
    {
        data_ = data;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(data_);
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
        serializer << data_ << holo::serialization::align;
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
        deserializer >> data_ >> holo::serialization::align;
    }

private:
    uint8_t data_;
};

/**
 * @brief This class defines fapa command
 */
class FapaCommand
{
public:
    /**
     * @brief default constructor
     */
    FapaCommand() noexcept
      : timestamp_()
      , remote_parking_mode_(0)
      , remote_parking_enable_(0)
      , apa_act_func_ind_(0)
      , apa_authst_(0)
      , command_doors_unlock_(0)
      , rpa_ready_(0)
      , pgear_req_(0)
      , pgear_Req_enable_(0)
      , rpa_short_pres_supp_st_(0)
      , sbm_challenge1_(0)
      , sbm_challenge2_(0)
      , apa_quit_ind_(0)
      , apa_rec_ind_(0)
      , apa_drv_req_(0)
      , apa_state_(0)
      , hpa_voice_req_(0)
      , rear_mirror_unfold_req_(0)
      , rear_mirror_fold_req_(0)
      , igoff_req_enable_(0)
      , apa_pwr_mode_req_(0)
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

    /* remote_parking_mode_ */
    uint8_t GetRemoteParkingMode() const noexcept
    {
        return remote_parking_mode_;
    }

    void SetRemoteParkingMode(uint8_t const remote_parking_mode)
    {
        remote_parking_mode_ = remote_parking_mode;
    }

    /* remote_parking_enable_ */
    uint8_t GetRemoteParkingEnable() const noexcept
    {
        return remote_parking_enable_;
    }

    void SetRemoteParkingEnable(uint8_t const remote_parking_enable)
    {
        remote_parking_enable_ = remote_parking_enable;
    }

    /* apa_act_func_ind_ */
    uint8_t GetApaActFuncInd() const noexcept
    {
        return apa_act_func_ind_;
    }

    void SetApaActFuncInd(uint8_t const apa_act_func_ind)
    {
        apa_act_func_ind_ = apa_act_func_ind;
    }

    /* apa_authst_ */
    uint8_t GetApaAuthst() const noexcept
    {
        return apa_authst_;
    }

    void SetApaAuthst(uint8_t const apa_authst)
    {
        apa_authst_ = apa_authst;
    }

    /* command_doors_unlock_ */
    uint8_t GetCommandDoorsUnlock() const noexcept
    {
        return command_doors_unlock_;
    }

    void SetCommandDoorsUnlock(uint8_t const command_doors_unlock)
    {
        command_doors_unlock_ = command_doors_unlock;
    }

    /* rpa_ready_ */
    uint8_t GetRpaReady() const noexcept
    {
        return rpa_ready_;
    }

    void SetRpaReady(uint8_t const rpa_ready)
    {
        rpa_ready_ = rpa_ready;
    }

    /* pgear_req_ */
    uint8_t GetPgearReq() const noexcept
    {
        return pgear_req_;
    }

    void SetPgearReq(uint8_t const pgear_req)
    {
        pgear_req_ = pgear_req;
    }

    /* pgear_Req_enable_ */
    uint8_t GetPgearReqEnable() const noexcept
    {
        return pgear_Req_enable_;
    }

    void SetPgearReqEnable(uint8_t const pgear_Req_enable)
    {
        pgear_Req_enable_ = pgear_Req_enable;
    }

    /* rpa_short_pres_supp_st_ */
    uint8_t GetRpaShortPresSuppSt() const noexcept
    {
        return rpa_short_pres_supp_st_;
    }

    void SetRpaShortPresSuppSt(uint8_t const rpa_short_pres_supp_st)
    {
        rpa_short_pres_supp_st_ = rpa_short_pres_supp_st;
    }

    /*sbm_challenge1_*/
    uint8_t GetSbmChallenge1() const noexcept
    {
        return sbm_challenge1_;
    }

    void SetSbmChallenge1(uint8_t const sbm_challenge1)
    {
        sbm_challenge1_ = sbm_challenge1;
    }

    /*sbm_challenge2_*/
    uint8_t GetSbmChallenge2() const noexcept
    {
        return sbm_challenge2_;
    }

    void SetSbmChallenge2(uint8_t const sbm_challenge2)
    {
        sbm_challenge2_ = sbm_challenge2;
    }

    /*apa_quit_ind_*/
    uint8_t GetApaQuitInd() const noexcept
    {
        return apa_quit_ind_;
    }

    void SetApaQuitInd(uint8_t const apa_quit_ind)
    {
        apa_quit_ind_ = apa_quit_ind;
    }

    /*apa_rec_ind_*/
    uint8_t GetApaRecInd() const noexcept
    {
        return apa_rec_ind_;
    }

    void SetApaRecInd(uint8_t const apa_rec_ind)
    {
        apa_rec_ind_ = apa_rec_ind;
    }

    /*apa_drv_req_*/
    uint8_t GetApaDrvReq() const noexcept
    {
        return apa_drv_req_;
    }

    void SetApaDrvReq(uint8_t const apa_drv_req)
    {
        apa_drv_req_ = apa_drv_req;
    }

    /*apa_state_*/
    uint8_t GetApaState() const noexcept
    {
        return apa_state_;
    }

    void SetApaState(uint8_t const apa_state)
    {
        apa_state_ = apa_state;
    }

    /*hpa_voice_req_ */
    uint8_t GetHpaVoiceReq() const noexcept
    {
        return hpa_voice_req_;
    }

    void SetHpaVoiceReq(uint8_t const hpa_voice_req)
    {
        hpa_voice_req_ = hpa_voice_req;
    }

    /*rear_mirror_unfold_req_*/
    uint8_t GetRearMirrorUnfoldReq() const noexcept
    {
        return rear_mirror_unfold_req_;
    }

    void SetRearMirrorUnfoldReq(uint8_t const rear_mirror_unfold_req)
    {
        rear_mirror_unfold_req_ = rear_mirror_unfold_req;
    }

    /*rear_mirror_fold_req_*/
    uint8_t GetRearMirrorFoldReq() const noexcept
    {
        return rear_mirror_fold_req_;
    }

    void SetRearMirrorFoldReq(uint8_t const rear_mirror_fold_req)
    {
        rear_mirror_fold_req_ = rear_mirror_fold_req;
    }

    /*igoff_req_enable_*/
    uint8_t GetIgoffReqEnable() const noexcept
    {
        return igoff_req_enable_;
    }

    void SetIgoffReqEnable(uint8_t const igoff_req_enable)
    {
        igoff_req_enable_ = igoff_req_enable;
    }

    /*apa_pwr_mode_req_*/
    uint8_t GetPwrModeReq() const noexcept
    {
        return apa_pwr_mode_req_;
    }

    void SetPwrModeReq(uint8_t const apa_pwr_mode_req)
    {
        apa_pwr_mode_req_ = apa_pwr_mode_req;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(
                   remote_parking_mode_, remote_parking_enable_, apa_act_func_ind_, apa_authst_, command_doors_unlock_,
                   rpa_ready_, pgear_req_, pgear_Req_enable_, rpa_short_pres_supp_st_, sbm_challenge1_, sbm_challenge2_,
                   apa_quit_ind_, apa_rec_ind_, apa_drv_req_, apa_state_, hpa_voice_req_, rear_mirror_unfold_req_,
                   rear_mirror_fold_req_, igoff_req_enable_, apa_pwr_mode_req_);
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
        serializer << timestamp_ << remote_parking_mode_ << remote_parking_enable_ << apa_act_func_ind_ << apa_authst_
                   << command_doors_unlock_ << rpa_ready_ << pgear_req_ << pgear_Req_enable_ << rpa_short_pres_supp_st_
                   << sbm_challenge1_ << sbm_challenge2_ << apa_quit_ind_ << apa_rec_ind_ << apa_drv_req_ << apa_state_
                   << hpa_voice_req_ << rear_mirror_unfold_req_ << rear_mirror_fold_req_ << igoff_req_enable_
                   << apa_pwr_mode_req_ << holo::serialization::align;
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
        deserializer >> timestamp_ >> remote_parking_mode_ >> remote_parking_enable_ >> apa_act_func_ind_ >>
            apa_authst_ >> command_doors_unlock_ >> rpa_ready_ >> pgear_req_ >> pgear_Req_enable_ >>
            rpa_short_pres_supp_st_ >> sbm_challenge1_ >> sbm_challenge2_ >> apa_quit_ind_ >> apa_rec_ind_ >>
            apa_drv_req_ >> apa_state_ >> hpa_voice_req_ >> rear_mirror_unfold_req_ >> rear_mirror_fold_req_ >>
	    igoff_req_enable_ >> apa_pwr_mode_req_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp
    uint8_t remote_parking_mode_;        // PAS Remote parking Mode. 0: default; 1: remote_parking; 2: automatic_parking
    uint8_t remote_parking_enable_;      // FAPA PAS Remote Parking Enable. 0: disable; 1: enable
    uint8_t apa_act_func_ind_;           // 0: no_active; 1: automatic_cross_park_in; 2: automatic_parallel_park_in; 3:
                                // automatic_cross_park_out; 4: automatic_parallel_park_out; 5: remote_cross_park_in; 6:
                                // remote_parallel_park_in; 7: remote_cross_POC; 8: remote_parallel_POC; 9:
                                // remote_front_out; 10: remote_back_out; 11~15: reserved
    uint8_t apa_authst_;            // APA Authst with SBM. 0: default; 1: fail; 2: pass; 3: not_used
    uint8_t command_doors_unlock_;  // FAPA PAS command for door unlock. 0: no_command; 1: command
    uint8_t rpa_ready_;             // 0:disable 2:enable
    uint8_t pgear_req_;
    uint8_t pgear_Req_enable_;
    uint8_t rpa_short_pres_supp_st_;
    uint8_t sbm_challenge1_;  // RPA Challenge SBM Singal1
    uint8_t sbm_challenge2_;  // RPA Challenge SBM Singal2
    uint8_t apa_quit_ind_;
    uint8_t apa_rec_ind_;
    uint8_t apa_drv_req_;
    uint8_t apa_state_;
    uint8_t hpa_voice_req_;
    uint8_t rear_mirror_unfold_req_;
    uint8_t rear_mirror_fold_req_;
    uint8_t igoff_req_enable_;
    uint8_t apa_pwr_mode_req_;
};

}  // namespace system
}  // namespace parking
}  // namespace holo

#endif
