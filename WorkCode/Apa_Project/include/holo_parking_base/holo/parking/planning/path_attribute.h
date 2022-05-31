/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file path_attribute.h
 * @brief This header file defines path attribute
 * @author zhangchun(zhangchun@holomaitc.com)
 * @date 2021-05-18
 */

#ifndef HOLO_PARKING_BASE_PLANNING_PATH_ATTRIBUTE_H_
#define HOLO_PARKING_BASE_PLANNING_PATH_ATTRIBUTE_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace planning
{
/**
 * @brief This class defines path attribute
 */
class PathAttribute
{
public:
    /**
     * @brief default constructor
     */
    PathAttribute() noexcept
      : timestamp_()
      , path_gear_(0)
      , path_id_(0)
      , path_type_(0)
      , path_size_(0)
      , plan_complete_(0)
      , plan_error_(0)
      , path_len_(0.0)
      , remain_path_len_(0.0)
      , brk_flag_(0)
      , brk_dist_(0.0)
      , speed_limit_(0.0)
      , lamp_req_(0)
      , read_file_status_(0)
      , ref_lat_error_(0.0)
      , ref_heading_error_(0.0)
      , road_curvature_(0.0)
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

    /* path_gear_ */
    uint8_t GetPathGear() const noexcept
    {
        return path_gear_;
    }

    void SetPathGear(uint8_t const path_gear)
    {
        path_gear_ = path_gear;
    }

    /* path_id_ */
    uint8_t GetPathId() const noexcept
    {
        return path_id_;
    }

    void SetPathId(uint8_t const path_id)
    {
        path_id_ = path_id;
    }

    /* path_type_ */
    uint8_t GetPathType() const noexcept
    {
        return path_type_;
    }

    void SetPathType(uint8_t const path_type)
    {
        path_type_ = path_type;
    }

    /* path_size_ */
    uint8_t GetPathSize() const noexcept
    {
        return path_size_;
    }

    void SetPathSize(uint8_t const path_size)
    {
        path_size_ = path_size;
    }

    /* plan_complete_ */
    uint8_t GetPathComplete() const noexcept
    {
        return plan_complete_;
    }

    void SetPathComplete(uint8_t const plan_complete)
    {
        plan_complete_ = plan_complete;
    }

    /* plan_error_ */
    uint8_t GetPlanError() const noexcept
    {
        return plan_error_;
    }

    void SetPlanError(uint8_t const plan_error)
    {
        plan_error_ = plan_error;
    }

    /* path_len_ */
    float32_t GetPathLen() const noexcept
    {
        return path_len_;
    }

    void SetPathLen(float32_t const path_len)
    {
        path_len_ = path_len;
    }

    /* remain_path_len_ */
    float32_t GetRemainPathLen() const noexcept
    {
        return remain_path_len_;
    }

    void SetRemainPathLen(float32_t const remain_path_len)
    {
        remain_path_len_ = remain_path_len;
    }

    /* brk_flag_ */
    uint8_t GetBrkFlag() const noexcept
    {
        return brk_flag_;
    }

    void SetBrkFlag(uint8_t const brk_flag)
    {
        brk_flag_ = brk_flag;
    }

    /* brk_dist_ */
    float32_t GetBrkDist() const noexcept
    {
        return brk_dist_;
    }

    void SetBrkDist(float32_t const brk_dist)
    {
        brk_dist_ = brk_dist;
    }

    /* speed_limit_ */
    float32_t GetSpeedLimit() const noexcept
    {
        return speed_limit_;
    }

    void SetSpeedLimit(float32_t const speed_limit)
    {
        speed_limit_ = speed_limit;
    }

    /* lamp_req_ */
    uint8_t GetLampReq() const noexcept
    {
        return lamp_req_;
    }

    void SetLampReq(uint8_t const lamp_req)
    {
        lamp_req_ = lamp_req;
    }

    /* read_file_status_ */
    uint8_t GetReadFileStatus() const noexcept
    {
        return read_file_status_;
    }

    void SetReadFileStatus(uint8_t const read_file_status)
    {
        read_file_status_ = read_file_status;
    }

    /* ref_lat_error_ */
    float32_t GetRefLatError() const noexcept
    {
        return ref_lat_error_;
    }

    void SetRefLatError(float32_t const ref_lat_error)
    {
        ref_lat_error_ = ref_lat_error;
    }

    /* ref_heading_error_ */
    float32_t GetRefHeadingError() const noexcept
    {
        return ref_heading_error_;
    }

    void SetRefHeadingError(float32_t const ref_heading_error)
    {
        ref_heading_error_ = ref_heading_error;
    }

    /* road_curvature_ */
    float32_t GetRoadCurvature() const noexcept
    {
        return road_curvature_;
    }

    void SetRoadCurvature(float32_t const road_curvature)
    {
        road_curvature_ = road_curvature;
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
               holo::serialization::SerializedSize<ALIGN>(path_gear_, path_id_, path_type_, path_size_, plan_complete_,
                                                          plan_error_, path_len_, remain_path_len_, brk_flag_,
                                                          brk_dist_, speed_limit_, lamp_req_, read_file_status_,
                                                          ref_lat_error_, ref_heading_error_, road_curvature_);
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
        serializer << timestamp_ << path_gear_ << path_id_ << path_type_ << path_size_ << plan_complete_ << plan_error_
                   << path_len_ << remain_path_len_ << brk_flag_ << brk_dist_ << speed_limit_ << lamp_req_
                   << read_file_status_ << ref_lat_error_ << ref_heading_error_ << road_curvature_
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
        deserializer >> timestamp_ >> path_gear_ >> path_id_ >> path_type_ >> path_size_ >> plan_complete_ >>
            plan_error_ >> path_len_ >> remain_path_len_ >> brk_flag_ >> brk_dist_ >> speed_limit_ >> lamp_req_ >>
            read_file_status_ >> ref_lat_error_ >> ref_heading_error_ >> road_curvature_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    ///  the path attribute is valid when path id not 0
    uint8_t   path_gear_;          ///< 0: unknown(ex: not in task); 1: P; 2: R; 3: N; 4: D
    uint8_t   path_id_;            ///< path id, 0 if not in task
    uint8_t   path_type_;          ///< reserved
    uint8_t   path_size_;          ///< valid path size of current piecewise
    uint8_t   plan_complete_;      ///< 0: not complete; 1: complete
    uint8_t   plan_error_;         ///< 0: no error; 1: error
    float32_t path_len_;           ///< total paths length addition
    float32_t remain_path_len_;    ///< current piecewise path remain distance
    uint8_t   brk_flag_;           ///< reserved
    float32_t brk_dist_;           ///< stop distance decided from min of collision check and path remain
    float32_t speed_limit_;        ///< speed limit
    uint8_t   lamp_req_;           ///< reserved
    uint8_t   read_file_status_;   ///< 0: no error; 1: error
    float32_t ref_lat_error_;      ///< lateral error with reference(m)
    float32_t ref_heading_error_;  ///< heading error with reference(degree)
    float32_t road_curvature_;     ///< reference point curvature(1/m)
};

}  // namespace planning
}  // namespace parking
}  // namespace holo

#endif
