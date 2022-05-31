/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file path.h
 * @brief This header file defines path
 * @author songbo(songbo@holomaitc.com)
 * @date 2022-04-07
 */

#ifndef HOLO_PARKING_BASE_PLANNING_PATH_H_
#define HOLO_PARKING_BASE_PLANNING_PATH_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/parking/planning/path_point.h>

namespace holo
{
namespace parking
{
namespace planning
{
/**
 * @brief This class defines path attribute
 */
class Path
{
public:
    using PathPoints = holo::parking::planning::Path_Point;
    /**
     * @brief default constructor
     */
    Path() noexcept
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
      , road_turning_(0)
      , read_file_status_(0)
      , path_points_()
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
    uint16_t GetPathSize() const noexcept
    {
        return path_size_;
    }

    void SetPathSize(uint16_t const path_size)
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

    /* road_turning */
    uint8_t GetRoadTurning() const noexcept
    {
        return road_turning_;
    }

    void SetRoadTurning(uint8_t const road_turning)
    {
        road_turning_ = road_turning;
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

    const std::vector<PathPoints>& GetPathPoints() const noexcept
    {
        return path_points_;
    }

    void SetPathPoints(const std::vector<PathPoints>& value) noexcept
    {
        path_points_ = value;
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
               holo::serialization::SerializedSize<ALIGN>(
                   path_gear_, path_id_, path_type_, path_size_, plan_complete_, plan_error_, path_len_,
                   remain_path_len_, brk_flag_, brk_dist_, speed_limit_, lamp_req_, road_turning_, read_file_status_);
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
                   << road_turning_ << read_file_status_ << holo::serialization::align;
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
        deserializer >> timestamp_ >> path_gear_ >> path_id_ >> path_type_ >> path_size_ >> plan_complete_ >>
            plan_error_ >> path_len_ >> remain_path_len_ >> brk_flag_ >> brk_dist_ >> speed_limit_ >> lamp_req_ >>
            road_turning_ >> read_file_status_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;
    uint8_t                 path_gear_;
    uint8_t                 path_id_;
    uint8_t                 path_type_;
    uint16_t                path_size_;
    uint8_t                 plan_complete_;
    uint8_t                 plan_error_;
    float32_t               path_len_;
    float32_t               remain_path_len_;
    uint8_t                 brk_flag_;
    float32_t               brk_dist_;
    float32_t               speed_limit_;
    uint8_t                 lamp_req_;
    uint8_t                 road_turning_;
    uint8_t                 read_file_status_;
    std::vector<PathPoints> path_points_;
};

}  // namespace planning
}  // namespace parking
}  // namespace holo

#endif
