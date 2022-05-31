/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file alarm.h
 * @brief This header file defines Alarm class
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-11-25
 */
#ifndef HOLO_COMMON_ALARM_H_
#define HOLO_COMMON_ALARM_H_

#include <type_traits>

#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

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
 * @brief This class represents a period of alarm.
 */
class Alarm
{
public:
    using UnderlyingType = uint16_t;

    /**
     * @brief define Level enum class
     */
    enum class Level : UnderlyingType
    {
        NORMAL = 0U,
        MINOR,
        MODERATE,
        FATAL_1,
        FATAL_2,
    };

    /**
     * @brief default constructor
     */
    Alarm() : Alarm{0U}
    {
    }

    /**
     * @brief construct a new Alarm object with UnderlyingType value
     *
     * @param value underlying type value
     */
    Alarm(UnderlyingType value)
      : code_{static_cast<UnderlyingType>(value >> CODE_OFFSET)}
      , level_{static_cast<UnderlyingType>(value >> LEVEL_OFFSET)}
    {
    }

    /**
     * @brief = operator overloading
     *
     * @param value right hand side value with underlying type value
     *
     * @return reference to Alarm object
     */
    Alarm& operator=(UnderlyingType value) noexcept
    {
        level_ = value >> LEVEL_OFFSET;
        code_  = value >> CODE_OFFSET;
        return *this;
    }

    /**
     * @brief == operator overloading
     *
     * @param lhs left hand side UnderlyingType value
     * @param rhs right hand side Alarm object
     *
     * @return true if the lhs is equivalent to rhs.
     * @return false if the lhs isn't equivalent to rhs.
     */
    friend bool_t operator==(UnderlyingType lhs, Alarm rhs) noexcept
    {
        return rhs == lhs;
    }

    /**
     * @brief == operator overloading
     *
     * @param rhs right hand side UnderlyingType value
     *
     * @return true if the alarm is equivalent to rhs.
     * @return false if the alarm isn't equivalent to rhs.
     */
    bool_t operator==(UnderlyingType const rhs) const noexcept
    {
        return static_cast<UnderlyingType>(*this) == rhs;
    }

    /**
     * @brief == operator overloading
     *
     * @param rhs right hand side Alarm object
     *
     * @return true if the alarm is equivalent to rhs.
     * @return false if the alarm isn't equivalent to rhs.
     */
    bool_t operator==(Alarm const rhs) const noexcept
    {
        return static_cast<UnderlyingType>(*this) == static_cast<UnderlyingType>(rhs);
    }

    /**
     * @brief != operator overloading
     *
     * @param lhs left hand side UnderlyingType value
     * @param rhs right hand side Alarm object
     *
     * @return true if the lhs isn't equivalent to rhs.
     * @return false if the lhs is equivalent to rhs.
     */
    friend bool_t operator!=(UnderlyingType const lhs, Alarm const rhs) noexcept
    {
        return !(lhs == rhs);
    }

    /**
     * @brief != operator overloading
     *
     * @param rhs right hand side UnderlyingType value
     *
     * @return true if the alarm isn't equivalent to rhs.
     * @return false if the alarm is equivalent to rhs.
     */
    bool_t operator!=(UnderlyingType const rhs) const noexcept
    {
        return !(*this == rhs);
    }

    /**
     * @brief != operator overloading
     *
     * @param rhs right hand side Alarm object
     *
     * @return true if the alarm isn't equivalent to rhs.
     * @return false if the alarm is equivalent to rhs.
     */
    bool_t operator!=(Alarm const rhs) const noexcept
    {
        return !(*this == rhs);
    }

    /**
     * @brief Convert to uint16_t
     */
    operator UnderlyingType() const noexcept
    {
        UnderlyingType level = static_cast<UnderlyingType>(level_) << LEVEL_OFFSET;
        return level + code_;
    }

    /**
     * @brief get level
     *
     * @return Level
     */
    Level GetLevel() const noexcept
    {
        return static_cast<Level>(static_cast<UnderlyingType>(level_));
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
        return sizeof(UnderlyingType);
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
        UnderlyingType value = static_cast<UnderlyingType>(level_) << LEVEL_OFFSET;
        value                = value | code_;
        serializer << value;
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
        UnderlyingType value;
        deserializer >> value;
        level_ = value >> LEVEL_OFFSET;
        code_  = value;
    }

private:
    enum FieldWidth : uint8_t
    {
        LEVEL_WIDTH  = 3U,
        LEVEL_OFFSET = 13U,
        CODE_WIDTH   = 13U,
        CODE_OFFSET  = 0U,
    };

    UnderlyingType code_ : CODE_WIDTH;
    UnderlyingType level_ : LEVEL_WIDTH;
};

/**
 * @}
 *
 */
}  // namespace common
}  // namespace holo
#endif
