/*!
 * @brief Defines intention class.
 * @author xieshuai(xieshuai@holomatic.ai)
 * @date "2019-12-05"
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PREDICTION_INTENTION_H_
#define HOLO_PREDICTION_INTENTION_H_

#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace prediction
{
/**
 * @addtogroup prediction
 *
 * @{
 */

/**
 * @brief Intention class
 */
class Intention
{
public:

    using Timestamp = holo::common::Timestamp;
    /**
     * @brief LateralIntention type
     *
     * @details Values greater or equal to INVALID (4u) are invalid. New values
     * should be added before INVALID.
     */
    enum class LateralIntention : uint8_t
    {
        UNKNOWN       = 0,
        LANE_KEEP     = 1,
        CUT_IN_EGO    = 2,
        CUT_IN_OTHERS = 3,
        INVALID       = 4,
    };

    /**
     * @brief LongitudinalIntention type
     *
     * @details Values greater or equal to INVALID (4u) are invalid. New values
     * should be added before INVALID.
     */
    enum class LongitudinalIntention : uint8_t
    {
        UNKNOWN    = 0,
        SPEED_KEEP = 1,
        ACCELERATE = 2,
        DECELERATE = 3,
        INVALID    = 4,
    };

public:
    /**
     * @brief Constructor
     *
     * @details Constructor with no parameter. Zero initializes all class members.
     */
    Intention()
      : stamp_start_(0u, 0u)
      , stamp_end_(0u, 0u)
      , id_(0u)
      , lateral_intention_(LateralIntention::UNKNOWN)
      , longitudinal_intention_(LongitudinalIntention::UNKNOWN)
      , lateral_confidence_(0.0f)
      , longitudinal_confidence_(0.0f)
    {
    }

    /**
     * @brief Constructor with parameters
     *
     * @param stamp_start start of intention life time
     * @param stamp_end end of intention life time
     * @param id obstacle UUID
     * @param lateral_intention lateral intention type
     * @param longitudinal_intention longitudinal intention type
     * @param lateral_confidence lateral_confidence of intention in range: [0.0f, 1.0f]
     */
    Intention(Timestamp const& stamp_start, Timestamp const& stamp_end, uint32_t const& id,
              LateralIntention const& lateral_intention, LongitudinalIntention const& longitudinal_intention,
              float32_t const& lateral_confidence, float32_t const& longitudinal_confidence)
      : stamp_start_(stamp_start), stamp_end_(stamp_end), id_(id)
    {
        if (!IsValidLateralIntention(lateral_intention))
        {
            throw std::runtime_error("Invalid type");
        }
        lateral_intention_ = lateral_intention;
        if (!IsValidLongitudinalIntention(longitudinal_intention))
        {
            throw std::runtime_error("Invalid type");
        }
        longitudinal_intention_ = longitudinal_intention;
        if (!IsValidConfidence(lateral_confidence))
        {
            throw std::runtime_error("Invalid lateral_confidence");
        }
        lateral_confidence_ = lateral_confidence;
        if (!IsValidConfidence(longitudinal_confidence))
        {
            throw std::runtime_error("Invalid longitudinal_confidence");
        }
        longitudinal_confidence_ = longitudinal_confidence;
    }

    /**
     * @brief Constructor with obstacle ID
     *
     * @param id obstacle UUID
     */
    Intention(uint32_t const& id)
      : stamp_start_(0u, 0u)
      , stamp_end_(0u, 0u)
      , id_(id)
      , lateral_intention_(LateralIntention::UNKNOWN)
      , longitudinal_intention_(LongitudinalIntention::UNKNOWN)
      , lateral_confidence_(0.0f)
      , longitudinal_confidence_(0.0f)
    {
    }

    /**
     * @brief Destructor
     */
    ~Intention() noexcept
    {
    }

    /**
     * @brief Get stamp_start
     *
     * @return stamp_start
     */
    Timestamp const& GetStampStart() const noexcept
    {
        return stamp_start_;
    }

    /**
     * @brief Set stamp_start
     *
     * @param stamp stamp
     */
    void SetStampStart(Timestamp const& stamp)
    {
        stamp_start_ = stamp;
    }

    /**
     * @brief Get stamp_end
     *
     * @return stamp_end
     */
    Timestamp const& GetStampEnd() const noexcept
    {
        return stamp_end_;
    }

    /**
     * @brief Set stamp_end
     *
     * @param stamp stamp
     */
    void SetStampEnd(Timestamp const& stamp)
    {
        stamp_end_ = stamp;
    }

    /**
     * @brief Get obstacle UUID
     *
     * @return obstacle UUID
     */
    uint32_t const& GetId() const noexcept
    {
        return id_;
    }

    /**
     * @brief Set id
     *
     * @param id obstacle UUID
     */
    void SetId(uint32_t const& id) noexcept
    {
        id_ = id;
    }

    /**
     * @brief Get lateral intention
     *
     * @return lateral intention
     */
    LateralIntention const& GetLateralIntention() const noexcept
    {
        return lateral_intention_;
    }

    /**
     * @brief Set lateral intention
     *
     * @throw std::runtime_error if input is invalid LateralIntention type.
     *
     * @param lateral_intention lateral intention
     */
    void SetLateralIntention(LateralIntention const& lateral_intention)
    {
        if (!IsValidLateralIntention(lateral_intention))
        {
            throw std::runtime_error("Invalid type");
        }
        lateral_intention_ = lateral_intention;
    }

    /**
     * @brief Get longitudinal intention
     *
     * @return longitudinal intention
     */
    LongitudinalIntention const& GetLongitudinalIntention() const noexcept
    {
        return longitudinal_intention_;
    }

    /**
     * @brief Set longitudinal intention
     *
     * @throw std::runtime_error if input is invalid LongitudinalIntention type.
     *
     * @param longitudinal_intention longitudinal intention
     */
    void SetLongitudinalIntention(LongitudinalIntention const& longitudinal_intention)
    {
        if (!IsValidLongitudinalIntention(longitudinal_intention))
        {
            throw std::runtime_error("Invalid type");
        }
        longitudinal_intention_ = longitudinal_intention;
    }

    /**
     * @brief Get lateral_confidence of intention
     *
     * @return lateral_confidence
     */
    float32_t const& GetLateralConfidence() const noexcept
    {
        return lateral_confidence_;
    }

    /**
     * @brief Set lateral_confidence
     *
     * @throw std::runtime_error if input is not in range: [0.0f, 1.0f].
     *
     * @param lateral_confidence lateral_confidence
     */
    void SetLateralConfidence(float32_t const& lateral_confidence)
    {
        if (!IsValidConfidence(lateral_confidence))
        {
            throw std::runtime_error("Invalid lateral_confidence");
        }
        lateral_confidence_ = lateral_confidence;
    }

    /**
     * @brief Get longitudinal_confidence of intention
     *
     * @return longitudinal_confidence
     */
    float32_t const& GetLongitudinalConfidence() const noexcept
    {
        return longitudinal_confidence_;
    }

    /**
     * @brief Set longitudinal_confidence
     *
     * @throw std::runtime_error if input is not in range: [0.0f, 1.0f].
     *
     * @param longitudinal_confidence longitudinal_confidence
     */
    void SetLongitudinalConfidence(float32_t const& longitudinal_confidence)
    {
        if (!IsValidConfidence(longitudinal_confidence))
        {
            throw std::runtime_error("Invalid longitudinal_confidence");
        }
        longitudinal_confidence_ = longitudinal_confidence;
    }

    /**
     * @brief Compare type
     *
     * @param lateral_intention another LateralIntention type
     *
     * @return return true if current LateralIntention equals to input
     */
    bool_t IsLateralIntentionType(LateralIntention const& lateral_intention) const noexcept
    {
        return lateral_intention_ == lateral_intention;
    }

    /**
     * @brief Compare type
     *
     * @param longitudinal_intention another LongitudinalIntention type
     *
     * @return return true if current LateralIntention equals to input
     */
    bool_t IsLongitudinalIntentionType(LongitudinalIntention const& longitudinal_intention) const noexcept
    {
        return longitudinal_intention_ == longitudinal_intention;
    }

    /**
     * @brief Get string representation of intention object
     *
     * @return string representation of intention object
     */
    std::string ToString() const
    {
        std::stringstream ss;
        ss << "Intention: ("
           << "ID: " << id_ << ", "
           << "lateral: " << static_cast<int32_t>(lateral_intention_) << ", "
           << "confidence: " << lateral_confidence_ << ", "
           << "longitudinal: " << static_cast<int32_t>(longitudinal_intention_) << ", "
           << "confidence: " << longitudinal_confidence_ << ", "
           << "start at: " << stamp_start_.GetSec() << "s " << stamp_start_.GetNsec() << "ns, "
           << "duration: " << (stamp_end_ - stamp_start_).ToSec() << "s"
           << ")";
        return ss.str();
    }

    /**
     * @brief operator<<
     *
     * @param[in, out] target ostream object
     * @param[in] intention object
     */
    friend std::ostream& operator<<(std::ostream& os, Intention const& intention)
    {
        os << intention.ToString();
        return os;
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
        return stamp_start_.GetSerializedSize<ALIGN>() + stamp_end_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(id_, lateral_intention_, longitudinal_intention_,
                                                          longitudinal_confidence_, lateral_confidence_);
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
        serializer << stamp_start_ << stamp_end_ << id_ << static_cast<uint8_t>(lateral_intention_)
                   << static_cast<uint8_t>(longitudinal_intention_) << lateral_confidence_ << longitudinal_confidence_
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
        uint8_t lateral_intention      = 0U;
        uint8_t longitudinal_intention = 0U;
        deserializer >> stamp_start_ >> stamp_end_ >> id_ >> lateral_intention >> longitudinal_intention >>
            lateral_confidence_ >> longitudinal_confidence_ >> holo::serialization::align;
        lateral_intention_      = static_cast<Intention::LateralIntention>(lateral_intention);
        longitudinal_intention_ = static_cast<Intention::LongitudinalIntention>(longitudinal_intention);
    }

protected:
    /**
     * @brief Check if type has invalid enum value
     *
     * @param type intention type
     * @return return true if type is invalid and false if type is valid
     */
    static bool_t IsValidLateralIntention(LateralIntention const& lateral_intention) noexcept
    {
        return static_cast<uint8_t>(lateral_intention) < static_cast<uint8_t>(LateralIntention::INVALID);
    }

    /**
     * @brief Check if type has invalid enum value
     *
     * @param type intention type
     * @return return true if type is invalid and false if type is valid
     */
    static bool_t IsValidLongitudinalIntention(LongitudinalIntention const& longitudinal_intention) noexcept
    {
        return static_cast<uint8_t>(longitudinal_intention) < static_cast<uint8_t>(LongitudinalIntention::INVALID);
    }

    /**
     * @brief Check if confidence has invalid value (out of range [0.0f, 1.0f])
     *
     * @param confidence confidence
     * @return return true if confidence is invalid and false if confidence is valid
     */
    static bool_t IsValidConfidence(float32_t const& confidence) noexcept
    {
        return confidence >= 0.0f && confidence <= 1.0f;
    }

private:
    Timestamp stamp_start_;
    Timestamp stamp_end_;
    uint32_t                id_;
    LateralIntention        lateral_intention_;
    LongitudinalIntention   longitudinal_intention_;
    float32_t               lateral_confidence_;
    float32_t               longitudinal_confidence_;
};

/**
 * @}
 */

}  // namespace prediction
}  // namespace holo

#endif
