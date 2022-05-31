/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file tbox_command.h
 * @brief This header file defines tbox command
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021-09-18
 */

#ifndef HOLO_PARKING_BASE_SYSTEM_TBOX_COMMAND_H_
#define HOLO_PARKING_BASE_SYSTEM_TBOX_COMMAND_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace system
{
/**
 * @brief This class defines tbox command
 */
class TboxCommand
{
public:
    struct PathInfo
    {
        uint8_t  path_num;
        uint8_t  path_type;
        uint8_t  lot_type;
        uint8_t  path_state;
        uint8_t  path_learning_rate;
        uint8_t  path_source;
        uint16_t path_distance;
        uint8_t  path_match_gps_success;
    };

    struct PathInfoList
    {
        PathInfo path_info[10];
    };

    /**
     * @brief default constructor
     */
    TboxCommand() noexcept
      : timestamp_()
      , avp_st_(0)
      , avp_drv_req_(0)
      , avp_rec_ind_(0)
      , avp_quit_ind_(0)
      , avp_fct_st_(0)
      , avp_ctrl_sig_src_(0)
      , igoff_req_enable_(0)
      , igoff_req_enable_vd_(0)
      , remote_parking_mode_(0)
      , command_doors_lock_(0)
      , rear_mirror_unfold_req_(0)
      , path_upload_mode_(0)
      , path_info_list_()
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

    /* avp_st_ */
    uint8_t GetAvpSt() const noexcept
    {
        return avp_st_;
    }

    void SetAvpSt(uint8_t const avp_st)
    {
        avp_st_ = avp_st;
    }

    /* avp_drv_req_ */
    uint8_t GetAvpDrvReq() const noexcept
    {
        return avp_drv_req_;
    }

    void SetAvpDrvReq(uint8_t const avp_drv_req)
    {
        avp_drv_req_ = avp_drv_req;
    }

    /* avp_rec_ind_ */
    uint8_t GetAvpRecInd() const noexcept
    {
        return avp_rec_ind_;
    }

    void SetAvpRecInd(uint8_t const avp_rec_ind)
    {
        avp_rec_ind_ = avp_rec_ind;
    }

    /* avp_quit_ind_ */
    uint8_t GetAvpQuitInd() const noexcept
    {
        return avp_quit_ind_;
    }

    void SetAvpQuitInd(uint8_t const avp_quit_ind)
    {
        avp_quit_ind_ = avp_quit_ind;
    }

    /* avp_fct_st_ */
    uint8_t GetAvpFctSt() const noexcept
    {
        return avp_fct_st_;
    }

    void SetAvpFctSt(uint8_t const avp_fct_st)
    {
        avp_fct_st_ = avp_fct_st;
    }

    /* avp_ctrl_sig_src_ */
    uint8_t GetAvpCtrlSigSrc() const noexcept
    {
        return avp_ctrl_sig_src_;
    }

    void SetAvpCtrlSigSrc(uint8_t const avp_ctrl_sig_src)
    {
        avp_ctrl_sig_src_ = avp_ctrl_sig_src;
    }

    /* apa_voice_reminder_ */
    uint8_t GetApaVoiceReminder() const noexcept
    {
        return apa_voice_reminder_;
    }

    void SetApaVoiceReminder(uint8_t const apa_voice_reminder)
    {
        apa_voice_reminder_ = apa_voice_reminder;
    }

    /* igoff_req_enable_ */
    uint8_t GetFapaIgoffReqEnable() const noexcept
    {
        return igoff_req_enable_;
    }

    void SetFapaIgoffReqEnable(uint8_t const igoff_req_enable)
    {
        igoff_req_enable_ = igoff_req_enable;
    }

    /* igoff_req_enable_vd_ */
    uint8_t GetFapaIgoffReqEnableVD() const noexcept
    {
        return igoff_req_enable_vd_;
    }

    void SetFapaIgoffReqEnableVD(uint8_t const igoff_req_enable_vd)
    {
        igoff_req_enable_vd_ = igoff_req_enable_vd;
    }

    /* remote_parking_mode_ */
    uint8_t GetFapaPasRemoteParkingMode() const noexcept
    {
        return remote_parking_mode_;
    }

    void SetFapaPasRemoteParkingMode(uint8_t const pas_remote_parking_mode)
    {
        remote_parking_mode_ = pas_remote_parking_mode;
    }
    /* command_doors_lock_ */
    uint8_t GetFapaPasCommandDoorsLock() const noexcept
    {
        return command_doors_lock_;
    }

    void SetFapaPasCommandDoorsLock(uint8_t const pas_command_doors_lock)
    {
        command_doors_lock_ = pas_command_doors_lock;
    }

    /* rear_mirror_unfold_req_ */
    uint8_t GetFapaRearMirrorUnFoldReq() const noexcept
    {
        return rear_mirror_unfold_req_;
    }

    void SetFapaRearMirrorUnFoldReq(uint8_t const rear_mirror_unfold_req)
    {
        rear_mirror_unfold_req_ = rear_mirror_unfold_req;
    }

    /* path_upload_mode_ */
    uint8_t GetPathUploadMode() const noexcept
    {
        return path_upload_mode_;
    }

    void SetPathUploadMode(uint8_t path_upload_mode)
    {
        path_upload_mode_ = path_upload_mode;
    }

    /* path_num */
    uint8_t GetPathNum(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_num;
    }

    void SetPathNum(uint8_t const path_num, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_num = path_num;
    }

    /* path_type */
    uint8_t GetPathType(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_type;
    }

    void SetPathType(uint8_t const path_type, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_type = path_type;
    }

    /* lot_type */
    uint8_t GetLotType(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].lot_type;
    }

    void SetLotType(uint8_t const lot_type, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].lot_type = lot_type;
    }

    /* path_state */
    uint8_t GetPathState(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_state;
    }

    void SetPathState(uint8_t const path_state, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_state = path_state;
    }

    /* path_learning_rate */
    uint8_t GetPathLearningRate(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_learning_rate;
    }

    void SetPathLearningRate(uint8_t const path_learning_rate, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_learning_rate = path_learning_rate;
    }

    /* path_source */
    uint8_t GetPathSource(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_source;
    }

    void SetPathSource(uint8_t const path_source, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_source = path_source;
    }

    /* path_distance */
    uint16_t GetPathDistance(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_distance;
    }

    void SetPathDistance(uint16_t const path_distance, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_distance = path_distance;
    }

    /* path_match_gps_success */
    uint8_t GetPathMatchGpsSuccess(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_match_gps_success;
    }

    void SetPathMatchGpsSuccess(uint8_t const path_match_gps_success, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_match_gps_success = path_match_gps_success;
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
        size_t aligned_size = timestamp_.GetSerializedSize<ALIGN>() +
                              holo::serialization::SerializedSize<ALIGN>(
                                  avp_st_, avp_drv_req_, avp_rec_ind_, avp_quit_ind_, avp_fct_st_, avp_ctrl_sig_src_,
                                  igoff_req_enable_, igoff_req_enable_vd_, remote_parking_mode_, command_doors_lock_,
                                  rear_mirror_unfold_req_, path_upload_mode_);
        for (size_t i = 0U; i < 10U; i++)
        {
            aligned_size += path_info_list_.path_info[i].path_num;
            aligned_size += path_info_list_.path_info[i].path_type;
            aligned_size += path_info_list_.path_info[i].lot_type;
            aligned_size += path_info_list_.path_info[i].path_state;
            aligned_size += path_info_list_.path_info[i].path_learning_rate;
            aligned_size += path_info_list_.path_info[i].path_source;
            aligned_size += path_info_list_.path_info[i].path_distance;
            aligned_size += path_info_list_.path_info[i].path_match_gps_success;
        }
        return aligned_size;
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
        serializer << timestamp_ << avp_st_ << avp_drv_req_ << avp_rec_ind_ << avp_quit_ind_ << avp_fct_st_
                   << avp_ctrl_sig_src_ << igoff_req_enable_ << igoff_req_enable_vd_ << remote_parking_mode_
                   << command_doors_lock_ << rear_mirror_unfold_req_ << path_upload_mode_;
        for (size_t i = 0U; i < 10U; i++)
        {
            serializer << path_info_list_.path_info[i].path_num;
            serializer << path_info_list_.path_info[i].path_type;
            serializer << path_info_list_.path_info[i].lot_type;
            serializer << path_info_list_.path_info[i].path_state;
            serializer << path_info_list_.path_info[i].path_learning_rate;
            serializer << path_info_list_.path_info[i].path_source;
            serializer << path_info_list_.path_info[i].path_distance;
            serializer << path_info_list_.path_info[i].path_match_gps_success;
        }
        serializer << holo::serialization::align;
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
        deserializer >> timestamp_ >> avp_st_ >> avp_drv_req_ >> avp_rec_ind_ >> avp_quit_ind_ >> avp_fct_st_ >>
            avp_ctrl_sig_src_ >> igoff_req_enable_ >> igoff_req_enable_vd_ >> remote_parking_mode_ >>
            command_doors_lock_ >> rear_mirror_unfold_req_ >> path_upload_mode_;
        for (size_t i = 0U; i < 10U; i++)
        {
            deserializer >> path_info_list_.path_info[i].path_num;
            deserializer >> path_info_list_.path_info[i].path_type;
            deserializer >> path_info_list_.path_info[i].lot_type;
            deserializer >> path_info_list_.path_info[i].path_state;
            deserializer >> path_info_list_.path_info[i].path_learning_rate;
            deserializer >> path_info_list_.path_info[i].path_source;
            deserializer >> path_info_list_.path_info[i].path_distance;
            deserializer >> path_info_list_.path_info[i].path_match_gps_success;
        }
        deserializer >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp
    uint8_t      avp_st_;  // 0: Off; 1: Standby; 2: Checking; 3: HAVP Active; 4: Completed; 5: Terminated; 6: Failure;
    uint8_t      avp_drv_req_;
    uint8_t      avp_rec_ind_;
    uint8_t      avp_quit_ind_;
    uint8_t      avp_fct_st_;          // 0: No request; 1: APA; 2: RPA; 3: HAVP; 4: PAVP; 5: RA;
    uint8_t      avp_ctrl_sig_src_;    // 0: No comment; 1: IHU control mode; 2: APP control mode;
    uint8_t      apa_voice_reminder_;  // voice boardcast content index;
    uint8_t      igoff_req_enable_;
    uint8_t      igoff_req_enable_vd_;
    uint8_t      remote_parking_mode_;
    uint8_t      command_doors_lock_;
    uint8_t      rear_mirror_unfold_req_;
    uint8_t      path_upload_mode_;  // 0: don't uplad path, 1: first part, 2: second part, 3: third part
    PathInfoList path_info_list_;
};

}  // namespace system
}  // namespace parking
}  // namespace holo

#endif
