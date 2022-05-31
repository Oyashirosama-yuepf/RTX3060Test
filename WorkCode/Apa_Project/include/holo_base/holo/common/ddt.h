; /*
   * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
   * Unauthorized copying of this file, via any medium is strictly prohibited
   * Proprietary and confidential
   */

/**
 * @file ddt.h
 * @brief This header file define the ODM(operational domain module) related types.
 * @author zhouhuishuang(zhouhuishuang@holomatic.com)
 * @date 2020-11-16
 */
#ifndef HOLO_COMMON_DDT_H_
#define HOLO_COMMON_DDT_H_

#include <holo/common/alarm.h>
#include <holo/common/timestamp.h>
#include <holo/core/exception.h>

namespace holo
{
namespace common
{
/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief This class represents a period of DDT.
 */
class DdtState
{
public:
    /**
     * @brief Get DDT Type
     *
     * @return DDT type
     */
    uint8_t GetType() const noexcept
    {
        return type_;
    }

    /**
     * @brief Get DDT enabled status
     *
     * @return enabled status
     */
    bool_t IsEnabled() const noexcept
    {
        return static_cast<bool_t>(flags_ & DDT_ENABLE_FLAG);
    }

    /**
     * @brief Get predicted distance enabled status
     *
     * @return enabled status
     */
    bool_t IsPredictedDistanceEnabled() const noexcept
    {
        return static_cast<bool_t>(flags_ & PRED_DISTANCE_VALID_FLAG);
    }

    /**
     * @brief Get predicted time enabled status
     *
     * @return enabled status
     */
    bool_t IsPredictedTimeEnabled() const noexcept
    {
        return static_cast<bool_t>(flags_ & PRED_TIME_VALID_FLAG);
    }

    uint8_t GetFlags() const noexcept
    {
        return flags_;
    }

    /**
     * @brief Get alarm
     *
     * @return alarm value
     */
    Alarm GetAlarm() const noexcept
    {
        return alarm_;
    }

    /**
     * @brief Get predicted distance
     *
     * @return predicted distance
     */
    uint16_t GetPredictedDistance() const noexcept
    {
        return pred_distance_;
    }

    /**
     * @brief Get predicted time
     *
     * @return predicted time
     */
    uint16_t GetPredictedTime() const noexcept
    {
        return pred_time_;
    }

    /**
     * @brief enable DDT
     */
    void Enable() noexcept
    {
        flags_ |= DDT_ENABLE_FLAG;
    }

    /**
     * @brief disable DDT
     */
    void Disable() noexcept
    {
        flags_ &= ~DDT_ENABLE_FLAG;
    }

    /**
     * @brief Enable predicted distance
     */
    void EnablePredictedDistance() noexcept
    {
        flags_ |= PRED_DISTANCE_VALID_FLAG;
    }

    /**
     * @brief Disable predicted distance
     */
    void DisablePredictedDistance() noexcept
    {
        flags_ &= ~PRED_DISTANCE_VALID_FLAG;
    }

    /**
     * @brief Enable predicted time
     */
    void EnablePredictedTime() noexcept
    {
        flags_ |= PRED_TIME_VALID_FLAG;
    }

    /**
     * @brief Disable predicted time
     */
    void DisablePredictedTime() noexcept
    {
        flags_ &= ~PRED_TIME_VALID_FLAG;
    }

    void SetFlags(uint8_t value) noexcept
    {
        flags_ = value;
    }

    /**
     * @brief Set alarm
     */
    void SetAlarm(holo::common::Alarm alarm) noexcept
    {
        alarm_ = alarm;
    }

    /**
     * @brief Set predicted distance
     */
    void SetPredictedDistance(uint16_t distance) noexcept
    {
        pred_distance_ = distance;
    }

    /**
     * @brief Set predicted time
     */
    void SetPredictedTime(uint16_t time) noexcept
    {
        pred_time_ = time;
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
        return sizeof(DdtState);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << type_ << flags_ << static_cast<uint16_t>(alarm_) << pred_distance_ << pred_time_;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint16_t alarm;
        deserializer >> type_ >> flags_ >> alarm >> pred_distance_ >> pred_time_;
        SetAlarm(alarm);
    }

    template <size_t SIZE>
    friend class DdtStates;

private:
    DdtState() : type_{0U}, flags_{0U}, alarm_{0U}, pred_distance_{0U}, pred_time_{0U}
    {
    }

    DdtState(uint8_t type) : type_{type}, flags_{0U}, alarm_{0U}, pred_distance_{0U}, pred_time_{0U}
    {
    }

    ~DdtState() = default;

    enum FlagBit
    {
        DDT_ENABLE_FLAG          = 1U << 0U,
        PRED_DISTANCE_VALID_FLAG = 1U << 1U,
        PRED_TIME_VALID_FLAG     = 1U << 2U,
    };

    uint8_t  type_;
    uint8_t  flags_;
    Alarm    alarm_;
    uint16_t pred_distance_;
    uint16_t pred_time_;
};

/**
 * @brief This class represents a period of ODM.
 *
 * @tparam SIZE The maximum number of DDT states in DdtStates
 */
template <size_t SIZE>
class DdtStates
{
public:
    static size_t const MAX_SIZE_VALUE = SIZE;
    using const_iterator               = DdtState const*;
    using iterator                     = DdtState*;

    /**
     * @brief default constructor
     */
    DdtStates() : timestamp_{}, ddt_total_num_{0U}, ddts_{}
    {
    }

    /**
     * @brief Get timestamp
     *
     * @return Timestamp
     */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set timestamp
     *
     * @param timestamp
     */
    void SetTimestamp(Timestamp timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Get or create DdtStatus of specific ddt type
     *
     * @param ddt DDT type
     *
     * @return reference of DdtState
     *
     * @throws std::bad_alloc if ddt num > maximum of capacity
     */
    DdtState& operator[](uint8_t ddt)
    {
        for (size_t index = 0; index < ddt_total_num_; index++)
        {
            if (ddt == ddts_[index].GetType())
            {
                return ddts_[index];
            }
        }
        if (ddt_total_num_ < SIZE)
        {
            ddts_[ddt_total_num_].type_ = ddt;
            ddt_total_num_ += 1;
            return ddts_[ddt_total_num_ - 1];
        }
        else
        {
            throw std::bad_alloc();
        }
    }

    /**
     * @brief Get DdtStatus of specific ddt type
     *
     * @param ddt DDT type
     *
     * @return reference of DdtState
     *
     * @throws std::bad_alloc if ddt num > maximum of capacity
     */
    DdtState const& operator[](uint8_t ddt) const
    {
        for (size_t index = 0; index < ddt_total_num_; index++)
        {
            if (ddt == ddts_[index].GetType())
            {
                return ddts_[index];
            }
        }
        throw std::bad_alloc();
    }

    /**
     * @brief  Get DdtStatus of specific ddt type
     *
     * @param ddt DDT type
     *
     * @return reference of DdtState
     *
     * @throws holo::exception::OutOfRangeException if ddt is not exist
     */
    DdtState& at(uint8_t ddt)
    {
        for (size_t index = 0; index < ddt_total_num_; index++)
        {
            if (ddt == ddts_[index].GetType())
            {
                return ddts_[index];
            }
        }
        throw holo::exception::OutOfRangeException("");
    }

    /**
     * @brief  Get DdtStatus of specific ddt type
     *
     * @param ddt DDT type
     *
     * @return reference of DdtState
     *
     * @throws holo::exception::OutOfRangeException if ddt is not exist
     */
    DdtState const& at(uint8_t ddt) const
    {
        for (size_t index = 0; index < ddt_total_num_; index++)
        {
            if (ddt == ddts_[index].GetType())
            {
                return ddts_[index];
            }
        }
        throw holo::exception::OutOfRangeException("");
    }

    iterator begin() noexcept
    {
        return &ddts_[0];
    }

    const_iterator begin() const noexcept
    {
        return &ddts_[0];
    }

    const_iterator cbegin() const noexcept
    {
        return &ddts_[0];
    }

    iterator end() noexcept
    {
        return &ddts_[ddt_total_num_];
    }

    const_iterator end() const noexcept
    {
        return &ddts_[ddt_total_num_];
    }

    const_iterator cend() const noexcept
    {
        return &ddts_[ddt_total_num_];
    }

    /**
     * @brief get DDT size
     *
     * @return DDT size
     */
    size_t size() const noexcept
    {
        return ddt_total_num_;
    }

    constexpr size_t capacity() const noexcept
    {
        return MAX_SIZE_VALUE;
    }

    void clear() noexcept
    {
        ddt_total_num_ = 0U;
    }

    /**
     * @brief Has ddt state or not
     *
     * @return Has ddt state result
     */
    bool_t HasDdtState(uint8_t ddt) const noexcept
    {
        for (size_t index = 0; index < ddt_total_num_; index++)
        {
            if (ddt == ddts_[index].GetType())
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Remove ddt state
     *
     * @return Remove ddt state result
     */
    bool_t RemoveDdtState(uint8_t ddt) noexcept
    {
        for (size_t index = 0; index < ddt_total_num_; index++)
        {
            if (ddt == ddts_[index].GetType())
            {
                (void)std::copy(&ddts_[index + 1], &ddts_[ddt_total_num_], &ddts_[index]);
                ddt_total_num_ -= 1;
                return true;
            }
        }
        return false;
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
        return timestamp_.GetSerializedSize<ALIGN>() + holo::serialization::SerializedSize<ALIGN>(ddt_total_num_) +
               holo::serialization::AlignedSize<ALIGN>(sizeof(DdtState) * ddt_total_num_);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << ddt_total_num_;

        for (size_t index = 0U; index < ddt_total_num_; index++)
        {
            serializer << ddts_[index];
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
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> timestamp_ >> ddt_total_num_;
        for (size_t index = 0U; index < ddt_total_num_; index++)
        {
            deserializer >> ddts_[index];
        }
        deserializer >> holo::serialization::align;
    }

private:
    Timestamp timestamp_;
    uint8_t   ddt_total_num_;
    DdtState  ddts_[SIZE];
};

/**
 * @}
 *
 */

}  // namespace common
}  // namespace holo

#endif /* HOLO_COMMON_DDT_H_ */
