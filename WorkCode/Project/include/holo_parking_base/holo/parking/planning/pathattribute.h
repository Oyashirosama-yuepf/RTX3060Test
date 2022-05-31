/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file hpapathattribute.h
 * @brief This header file defines path attribute
 * @author fanhaowei(fanhaowei@holomaitc.com)
 * @date 2022-04-02
 */

#ifndef HOLO_PARKING_BASE_PLANNING_PATHATTRIBUTE_H_
#define HOLO_PARKING_BASE_PLANNING_PATHATTRIBUTE_H_

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
class HpaPathAttribute
{
public:
    /**
     * @brief default constructor
     */
    HpaPathAttribute() noexcept
      : timestamp_()
      , path_gear_(0)
      , path_id_(0)
      , path_type_(0)
      , path_size_(0)
      , plan_complete_(0)
      , plan_error_(0)
      , path_len_(0.0)
      , remain_path_len_(0.0)
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

    void SetRemainPathLen(float32_t const path_remain_len)
    {
        remain_path_len_ = path_remain_len;
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
                                                          plan_error_, path_len_, remain_path_len_);
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
                   << path_len_ << remain_path_len_ << holo::serialization::align;
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
            plan_error_ >> path_len_ >> remain_path_len_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    ///  the path attribute is valid when path id not 0
    uint8_t   path_gear_;        ///< 1: D; 2: N; 3: R; 4: P
    uint8_t   path_id_;          ///< path id
    uint8_t   path_type_;        ///< reserved
    uint16_t  path_size_;        ///< valid path size of current piecewise
    uint8_t   plan_complete_;    ///< 0: not complete; 1: complete
    uint8_t   plan_error_;       ///< 0: no error; 1: error
    float32_t path_len_;         ///< total length of path from start to end
    float32_t remain_path_len_;  ///< Path length not sent to control module
};

}  // namespace planning
}  // namespace parking
}  // namespace holo

#endif
