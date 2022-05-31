/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file odm.h
 * @brief This header file define the ODM(operational domain module) related types.
 * @author wangtao@holomatic.com
 * @author lichao@holomatic.com
 * @author zhangjiannan@holomatic.com
 * @date Feb 07, 2020
 */

#ifndef HOLO_COMMON_ODM_H_
#define HOLO_COMMON_ODM_H_

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
 * @brief this class defines the information of an ODM state field.
 *
 * @details An OdmState is consist of five parts.
 * @verbatim
 * 0                   1                   2                   3
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +---------------+-+-+-------------+-+---------------------------+
 * |      RSV      |E|T|  PRED_TIME  |D|         PRED_DIST         |
 * +---------------+-+-+-------------+-+---------------------------+
 * @endverbatim
 * RSV: Reserved.
 *
 * E: If the DDT is enabled.
 *
 * T: If the PRED_TIME is available.
 *
 * PRED_TIME: Predicted time of the ego car driving to the ODM boundary in the range of [0, 127] seconds.
 *
 * D: If the PRED_DIST is available.
 *
 * PRED_DIST: Predicted distance between current position and the ODM boundary in the range of [0, 16383] meters.
 */
class OdmState
{
public:
    /**
     * @brief Construct a new Odm State object
     *
     */
    OdmState() : pred_dist_(0u), pred_dist_valid_(0u), pred_time_(0u), pred_time_valid_(0u), enable_(0u), reserved_(0u)
    {
    }

    /**
     * @brief Construct a new Odm State object from a uint32_t.
     *
     * @param value the value of ODM state.
     */
    OdmState(uint32_t value) noexcept
      : pred_dist_(value)
      , pred_dist_valid_(value >> 14)
      , pred_time_(value >> 15)
      , pred_time_valid_(value >> 22)
      , enable_(value >> 23)
      , reserved_(value >> 24)
    {
    }

    /**
     * @brief Set the enable to true.
     *
     */
    void Enable() noexcept
    {
        enable_ = 1u;
    }

    /**
     * @brief Set the enable to false.
     *
     */
    void Disable() noexcept
    {
        enable_ = 0u;
    }

    /**
     * @brief Set the Pred Distance object
     *
     * @param dist the predicted distance between current position and the ODM boundary which is in the unit of meters.
     * @throws holo::exception::OutOfRangeException if dist >= the size of predicted distance.
     */
    void SetPredDistance(uint32_t dist)
    {
        // check if the input distance is out of range.
        if (dist >= (1u << 14u))
        {
            throw holo::exception::OutOfRangeException("the input distance is out of range of predicted distance ..");
        }
        pred_dist_valid_ = 1u;
        pred_dist_       = dist;
    }

    /**
     * @brief Set the Pred Time object
     *
     * @param time the predicted time of the ego car driving to the ODM boundary which is in the unit of seconds.
     * @throws holo::exception::OutOfRangeException if time >= the size of predicted time.
     */
    void SetPredTime(uint32_t time)
    {
        // check if the input time duration is out of range.
        if (time >= (1u << 7u))
        {
            throw holo::exception::OutOfRangeException("the input distance is out of range of predicted time ..");
        }
        pred_time_valid_ = 1u;
        pred_time_       = time;
    }

    /**
     * @brief Check if the DDT is enabled.
     *
     * @return true for enabled.
     * @return false for disabled.
     */
    bool_t IsEnabled() const noexcept
    {
        return enable_;
    }

    /**
     * @brief Check if the predicted distance is availabled.
     *
     * @return true for availbled.
     * @return false for unavailabled.
     */
    bool_t IsPredictedDistanceValid() const noexcept
    {
        return pred_dist_valid_;
    }

    /**
     * @brief Check if the predicted time is availabled.
     *
     * @return true for availabled.
     * @return false for unavailabled.
     */
    bool_t IsPredictedTimeValid() const noexcept
    {
        return pred_time_valid_;
    }

    /**
     * @brief Get the Predicted Distance object
     *
     * @return uint32_t the predicted distance between current position and the ODM boundary which is in the unit of
     * meters.
     */
    uint32_t GetPredictedDistance() const noexcept
    {
        return pred_dist_;
    }

    /**
     * @brief Get the Predicted Time object
     *
     * @return uint32_t the predicted time of the ego car driving to the ODM boundary which is in the unit of seconds.
     */
    uint32_t GetPredictedTime() const noexcept
    {
        return pred_time_;
    }

    /**
     * @brief the type cast operator overloading.
     *
     * @return uint32_t the meta data of ODM info.
     */
    explicit operator uint32_t() const noexcept
    {
        return static_cast<uint32_t>(static_cast<uint32_t>(pred_dist_) | static_cast<uint32_t>(pred_dist_valid_) << 14 |
                                     static_cast<uint32_t>(pred_time_) << 15 |
                                     static_cast<uint32_t>(pred_time_valid_) << 22 |
                                     static_cast<uint32_t>(enable_) << 23 | static_cast<uint32_t>(reserved_) << 24);
    }

private:
    uint32_t pred_dist_ : 14;       ///< Predicted distance odm will be disabled.
    uint32_t pred_dist_valid_ : 1;  ///< Predicted distance valid.
    uint32_t pred_time_ : 7;        ///< Predicted time odm will be disabled.
    uint32_t pred_time_valid_ : 1;  ///< Predicted time valid.
    uint32_t enable_ : 1;           ///< Odm enable.
    uint32_t reserved_ : 8;         ///< Reserved.
};

/**
 * @brief This class represents ODM states of DDTs(Dynamic Driving Task).
 */
class OdmStates
{
public:
    /**
     * @brief define the number of DDTs.
     *
     */
    static const size_t kDdtNumValue_ = 9u;

    /**
     * @brief This enum defines HoloMatic internal DDT(Dynamic Driving Task) indeces.
     *
     */
    enum class Ddt : uint32_t
    {
        ICP  = 0,  ///< Intelligent Cruise Pilot
        ICA  = 1,  ///< Intelligent Cruise Assist
        TJP  = 2,  ///< Traffic Jam Pilot
        TJA  = 3,  ///< Traffic Jam Assist
        ALC  = 4,  ///< Active Lane Change
        LC   = 5,  ///< Lane Change
        EMSS = 6,  ///< Emergency Lane Safe Stop
        ACC  = 7,  ///< Adaptive Cruise Control
        HSA  = 8,  ///< Highway Switch Assist
    };

    /**
     * @brief Get const reference of Timestamp
     *
     * @return const reference of Timestamp
     */
    const Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set Timestamp
     *
     * @param timestamp
     */
    void SetTimestamp(const Timestamp& timestamp)
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Access operator overloading.
     *
     * @param ddt Dynamic Driving Task.
     * @return OdmState& reference of OdmState.
     */
    OdmState& operator[](Ddt ddt) noexcept
    {
        return data_[static_cast<uint32_t>(ddt)];
    }

    /**
     * @brief Const access operator overloading.
     *
     * @param ddt Dynamic Driving Task.
     * @return OdmState& const reference of OdmState.
     */
    OdmState const& operator[](Ddt ddt) const noexcept
    {
        return data_[static_cast<uint32_t>(ddt)];
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
               holo::serialization::AlignedSize<ALIGN>(sizeof(OdmState) * kDdtNumValue_);
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
        // Step1, Serialize timestamp.
        serializer << timestamp_;

        // Step2, Serialize OdmState of each DDTs.
        for (size_t i = 0u; i < kDdtNumValue_; ++i)
        {
            serializer << static_cast<uint32_t>(data_[i]);
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
        // Step1, Deserialize timestamp.
        deserializer >> timestamp_;

        // Step2, deserialize OdmState of each DDTs.
        for (size_t i = 0u; i < kDdtNumValue_; ++i)
        {
            uint32_t odmstate;
            deserializer >> odmstate;
            data_[i] = static_cast<OdmState>(odmstate);
        }
        deserializer >> holo::serialization::align;
    }

private:
    Timestamp timestamp_;            ///< the timestamp of ODM which get from localization information.
    OdmState  data_[kDdtNumValue_];  ///< the ODM of DDTs data.
};

/**
 * @}
 *
 */

}  // namespace common
}  // namespace holo

#endif /* HOLO_COMMON_ODM_H_ */
