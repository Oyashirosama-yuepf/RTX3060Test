/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file remote_control_signal.h
 * @brief This header file defines remote control signal
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021-05-29
 */

#ifndef HOLO_PARKING_BASE_SYSTEM_REMOTE_CONTROL_SIGNAL_H_
#define HOLO_PARKING_BASE_SYSTEM_REMOTE_CONTROL_SIGNAL_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace system
{
/**
 * @brief This class defines sbm signal
 */
class SbmSignal
{
public:
    /**
     * @brief default constructor
     */
    SbmSignal() noexcept
      : timestamp_()
      , rpa_direction_sel_(0)
      , rpa_device_st_(0)
      , phone_batt_(100)
      , phone_connectingst_(0)
      , rpa_check_req_(0)
      , rpa_key_pst_st_(0)
      , rpa_device_fail_reason_(0)
      , rpa_btn_st_(0)
      , rpa_btn_st_vd_(0)
      , init_gesture_st_(0)
      , rpa_cancel_btn_st_(0)
      , rpa_cancel_btn_st_vd_(0)
      , path_select_(0)
      , rpa_bounces_st_(0)
      , rpa_challenge_response_(0)
      , finger_position_x_(0.0)
      , finger_position_y_(0.0)
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

    /* rpa_direction_sel_ */
    uint8_t GetRpaDirectionSel() const noexcept
    {
        return rpa_direction_sel_;
    }

    void SetRpaDirectionSel(uint8_t const rpa_direction_sel)
    {
        rpa_direction_sel_ = rpa_direction_sel;
    }

    /* rpa_device_st_ */
    uint8_t GetRpaDeviceSt() const noexcept
    {
        return rpa_device_st_;
    }

    void SetRpaDeviceSt(uint8_t const rpa_device_st)
    {
        rpa_device_st_ = rpa_device_st;
    }

    /*phone_connectingst_*/
    uint8_t GetPhoneConnectintst() const noexcept
    {
        return phone_connectingst_;
    }

    void SetPhoneConnectintst(uint8_t const phone_connectingst)
    {
        phone_connectingst_ = phone_connectingst;
    }

    /* phone_batt_ */
    uint8_t GetPhoneBatt() const noexcept
    {
        return phone_batt_;
    }

    void SetPhoneBatt(uint8_t const phone_batt)
    {
        phone_batt_ = phone_batt;
    }

    /* rpa_check_req_ */
    uint8_t GetRpaCheckReq() const noexcept
    {
        return rpa_check_req_;
    }

    void SetRpaCheckReq(uint8_t const rpa_check_req)
    {
        rpa_check_req_ = rpa_check_req;
    }

    /* rpa_key_pst_st_ */
    uint8_t GetRpaKeyPstSt() const noexcept
    {
        return rpa_key_pst_st_;
    }

    void SetRpaKeyPstSt(uint8_t const rpa_key_pst_st)
    {
        rpa_key_pst_st_ = rpa_key_pst_st;
    }

    /* rpa_device_fail_reason_ */
    uint8_t GetRpaDeviceFailReason() const noexcept
    {
        return rpa_device_fail_reason_;
    }

    void SetRpaDeviceFailReason(uint8_t const rpa_device_fail_reason)
    {
        rpa_device_fail_reason_ = rpa_device_fail_reason;
    }

    /* rpa_device_fail_reason_ */
    uint8_t GetForRpaFailReason() const noexcept
    {
        return for_rpa_fail_reason_;
    }

    void SetForRpaFailReason(uint8_t const for_rpa_fail_reason)
    {
        for_rpa_fail_reason_ = for_rpa_fail_reason;
    }

    /* rpa_btn_st_ */
    uint8_t GetRpaBtnSt() const noexcept
    {
        return rpa_btn_st_;
    }

    void SetRpaBtnSt(uint8_t const rpa_btn_st)
    {
        rpa_btn_st_ = rpa_btn_st;
    }

    /* rpa_btn_st_vd_ */
    uint8_t GetRpaBtnStVd() const noexcept
    {
        return rpa_btn_st_vd_;
    }

    void SetRpaBtnStVd(uint8_t const rpa_btn_st_vd)
    {
        rpa_btn_st_vd_ = rpa_btn_st_vd;
    }

    /* init_gesture_st_ */
    uint8_t GetInitGestureSt() const noexcept
    {
        return init_gesture_st_;
    }

    void SetInitGestureSt(uint8_t const init_gesture_st)
    {
        init_gesture_st_ = init_gesture_st;
    }

    /* rpa_cancel_btn_st_ */
    uint8_t GetRpaCancelBtnSt() const noexcept
    {
        return rpa_cancel_btn_st_;
    }

    void SetRpaCancelBtnSt(uint8_t const rpa_cancel_btn_st)
    {
        rpa_cancel_btn_st_ = rpa_cancel_btn_st;
    }

    /* rpa_cancel_btn_st_vd_ */
    uint8_t GetRpaCancelBtnStVd() const noexcept
    {
        return rpa_cancel_btn_st_vd_;
    }

    void SetRpaCancelBtnStVd(uint8_t const rpa_cancel_btn_st_vd)
    {
        rpa_cancel_btn_st_vd_ = rpa_cancel_btn_st_vd;
    }

    /* path_select_ */
    uint8_t GetPathSelect() const noexcept
    {
        return path_select_;
    }

    void SetPathSelect(uint8_t const path_select)
    {
        path_select_ = path_select;
    }

    /* finger_position_x_ */
    float64_t GetFingerPositionX() const noexcept
    {
        return finger_position_x_;
    }

    void SetFingerPositionX(float64_t const finger_position_x)
    {
        finger_position_x_ = finger_position_x;
    }

    /* finger_position_y_ */
    float64_t GetFingerPositionY() const noexcept
    {
        return finger_position_y_;
    }

    void SetFingerPositionY(float64_t const finger_position_y)
    {
        finger_position_y_ = finger_position_y;
    }

    uint8_t GetRpaComSDKUBouncesSt() const noexcept
    {
        return rpa_bounces_st_;
    }

    void SetRpaComSDKUBouncesSt(uint8_t const rpa_bounces_st)
    {
        rpa_bounces_st_ = rpa_bounces_st;
    }

    uint8_t GetSbmChallengeResp() const noexcept
    {
        return rpa_challenge_response_;
    }

    void SetSbmChallengeResp(uint8_t const rpa_challenge_response)
    {
        rpa_challenge_response_ = rpa_challenge_response;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(
                   rpa_direction_sel_, rpa_device_st_, phone_batt_, phone_connectingst_, rpa_check_req_,
                   rpa_key_pst_st_, rpa_device_fail_reason_, for_rpa_fail_reason_, rpa_btn_st_, init_gesture_st_,
                   rpa_cancel_btn_st_, rpa_cancel_btn_st_vd_, path_select_, rpa_bounces_st_, rpa_challenge_response_,
                   finger_position_x_, finger_position_y_);
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
        serializer << timestamp_ << rpa_direction_sel_ << rpa_device_st_ << phone_batt_ << phone_connectingst_
                   << rpa_check_req_ << rpa_key_pst_st_ << rpa_device_fail_reason_ << for_rpa_fail_reason_
                   << rpa_btn_st_ << rpa_btn_st_vd_ << init_gesture_st_ << rpa_cancel_btn_st_ << rpa_cancel_btn_st_vd_
                   << path_select_ << rpa_bounces_st_ << rpa_challenge_response_ << finger_position_x_
                   << finger_position_y_ << holo::serialization::align;
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
        deserializer >> timestamp_ >> rpa_direction_sel_ >> rpa_device_st_ >> phone_batt_ >> phone_connectingst_ >>
            rpa_check_req_ >> rpa_key_pst_st_ >> rpa_device_fail_reason_ >> rpa_btn_st_ >> rpa_btn_st_vd_ >>
            init_gesture_st_ >> rpa_cancel_btn_st_ >> rpa_cancel_btn_st_vd_ >> path_select_ >> rpa_bounces_st_ >>
            rpa_challenge_response_ >> finger_position_x_ >> finger_position_y_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    uint8_t rpa_direction_sel_;         // 0: no_parkslot; 1: cross_left_out; 2: parallel_left_out; 3: front_out; 4:
                                        // cross_right_out 5: parallel_right_out; 6: rear_out; 7: reserved;
    uint8_t rpa_device_st_;             // 0: rd_inactive; 1: rd_ready; 2: rd_active; 3~7: reserved
    uint8_t phone_batt_;                // current phone battery
    uint8_t phone_connectingst_;        // 0:Defaule;1:Disconnecting;2:Pair Not auth;3:Pair and auth
    uint8_t rpa_check_req_;             // 0: not_active; 1: request
    uint8_t rpa_key_pst_st_;            // 0: in_the_car; 1: range_too_close; 2: normally_range; 3: range_too_far
    uint8_t rpa_device_fail_reason_;    // 0: rd_no_failure; 1: rd_offline; 2: rd_out_of_range; 3: rd_low_batt;
                                        // 4:other_failures; 5~15: reserved
    uint8_t   for_rpa_fail_reason_;     //  0: no_failure
    uint8_t   rpa_btn_st_;              // 0: not_pressed; 1: pressed
    uint8_t   rpa_btn_st_vd_;           // 0: invalid; 1: valid
    uint8_t   init_gesture_st_;         // 0: invalid; 1: valid
    uint8_t   rpa_cancel_btn_st_;       // 0: not_pressed; 1: pressed
    uint8_t   rpa_cancel_btn_st_vd_;    // 0: invalid; 1: valid
    uint8_t   path_select_;             // 0: no command; 1~10: path index
    uint8_t   rpa_bounces_st_;          // heartbeat:x
    uint8_t   rpa_challenge_response_;  // sbm_challenge:x
    float64_t finger_position_x_;       // x coordinate
    float64_t finger_position_y_;       // y coordinate
};

/**
 * @brief This class defines tbox signal
 */
class TboxSignal
{
public:
    /**
     * @brief default constructor
     */
    TboxSignal() noexcept
      : timestamp_()
      , err_st_to_avp_(0)
      , avp_device_st_(0)
      , avp_btn_st_(0)
      , avp_btn_st_vd_(0)
      , cancel_parking_(0)
      , path_select_(0)
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

    /* err_st_to_avp_ */
    uint8_t GetErrStToAvp() const noexcept
    {
        return err_st_to_avp_;
    }

    void SetErrStToAvp(uint8_t const err_st_to_avp)
    {
        err_st_to_avp_ = err_st_to_avp;
    }

    /* avp_device_st_ */
    uint8_t GetAvpDeviceSt() const noexcept
    {
        return avp_device_st_;
    }

    void SetAvpDeviceSt(uint8_t const avp_device_st)
    {
        avp_device_st_ = avp_device_st;
    }

    /* avp_btn_st_ */
    uint8_t GetAvpBtnSt() const noexcept
    {
        return avp_btn_st_;
    }

    void SetAvpBtnSt(uint8_t const avp_btn_st)
    {
        avp_btn_st_ = avp_btn_st;
    }

    /* avp_btn_st_vd_ */
    uint8_t GetAvpBtnStVd() const noexcept
    {
        return avp_btn_st_vd_;
    }

    void SetAvpBtnStVd(uint8_t const avp_btn_st_vd)
    {
        avp_btn_st_vd_ = avp_btn_st_vd;
    }

    /* cancel_parking_ */
    uint8_t GetCancelParking() const noexcept
    {
        return cancel_parking_;
    }

    void SetCancelParking(uint8_t const cancel_parking)
    {
        cancel_parking_ = cancel_parking;
    }

    /* path_select_ */
    uint8_t GetPathSelect() const noexcept
    {
        return path_select_;
    }

    void SetPathSelect(uint8_t const path_select)
    {
        path_select_ = path_select;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(err_st_to_avp_, avp_device_st_, avp_btn_st_, avp_btn_st_vd_,
                                                          cancel_parking_, path_select_);
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
        serializer << timestamp_ << err_st_to_avp_ << avp_device_st_ << avp_btn_st_ << avp_btn_st_vd_ << cancel_parking_
                   << path_select_ << holo::serialization::align;
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
        deserializer >> timestamp_ >> err_st_to_avp_ >> avp_device_st_ >> avp_btn_st_ >> avp_btn_st_vd_ >>
            cancel_parking_ >> path_select_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    uint8_t err_st_to_avp_;   // 0: no error; 1: internal error; 2: disconnected;
    uint8_t avp_device_st_;   // 0: inactive; 1: ready;
    uint8_t avp_btn_st_;      // 0: no pressed; 1: pressed
    uint8_t avp_btn_st_vd_;   // 0: invalid; 1: valid
    uint8_t cancel_parking_;  // 0: no comment; 1: cancel;
    uint8_t path_select_;     // 0: no command; 1~10: path index
};

/**
 * @brief This class defines remote control signal
 */
class RemoteControlSignal
{
public:
    /**
     * @brief default constructor
     */
    RemoteControlSignal() noexcept : timestamp_(), sbm_signal_(), tbox_signal_()
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

    /* sbm_signal_ */
    SbmSignal GetSbmSignal() const noexcept
    {
        return sbm_signal_;
    }

    void SetSbmSignal(SbmSignal const sbm_signal)
    {
        sbm_signal_ = sbm_signal;
    }

    /* tbox_signal_ */
    TboxSignal GetTboxSignal() const noexcept
    {
        return tbox_signal_;
    }

    void SetTboxSignal(TboxSignal const tbox_signal)
    {
        tbox_signal_ = tbox_signal;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(sbm_signal_, tbox_signal_);
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
        serializer << timestamp_ << sbm_signal_ << tbox_signal_ << holo::serialization::align;
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
        deserializer >> timestamp_ >> sbm_signal_ >> tbox_signal_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp
    SbmSignal               sbm_signal_;
    TboxSignal              tbox_signal_;
};

}  // namespace system
}  // namespace parking
}  // namespace holo

#endif
