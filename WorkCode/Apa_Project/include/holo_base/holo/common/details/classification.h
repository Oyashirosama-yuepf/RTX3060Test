/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file classification.h
 * @brief This header file defines Classification.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-04
 */

#ifndef HOLO_COMMON_DETAILS_CLASSIFICATION_H_
#define HOLO_COMMON_DETAILS_CLASSIFICATION_H_

#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace common
{
namespace details
{
/**
 * @addtogroup common
 *
 * @{
 */

/**
 * @brief Object classification
 *
 * @details Classification is composed of a main type and sub type which are hex code type.
 * Please add more classes as append style
 *
 * SubType code distribution:
 * - 00xx : code block for UNKNOWN main type
 * - 01xx : code block for PEDESTRIAN main type
 * - 02xx : code block for VEHICLE main type
 * - 03xx : code block for BIKE main type
 * - 04xx : code block for TRAFFIC_SIGN main type
 * - 05xx : code block for ANIMAL main type
 *
 * @note If you want to add a new type, pls add the kClassificationMainTypeNum, kClassificationSubTypeNum, new type in
 * Value and new name in kMainTypeStringArray, kSubTypeStringArray simultaneously
 */
class Classification
{
public:
    /**
     * @brief Object main type enum class
     */
    enum class MainType : uint16_t
    {
        UNKNOWN      = 0x00U,
        PEDESTRIAN   = 0x01U,
        VEHICLE      = 0x02U,
        BIKE         = 0x03U,
        TRAFFIC_SIGN = 0x04U,
        ANIMAL       = 0x05U,
        SPEED_HUMP   = 0x06U,
    };

    /**
     * @brief Object sub type enum class
     */
    enum class SubType : uint16_t
    {
        // UNKNOWN
        UNKNOWN = 0x0000U,
        UNKNOWN_MOVABLE,
        UNKNOWN_UNMOVABLE,

        // PEDESTRAIN
        PEDESTRIAN = 0x0100U,

        // VEHICLE
        CAR = 0x0200U,
        TRUCK,
        VAN,
        BUS,

        // BIKE
        BICYCLE = 0x0300U,
        TRICYCLE,
        MOTOBIKE,

        // TRAFFIC SIGN
        TRAFFIC_LED_BOARD = 0x0400U,
        TRAFFIC_SIGN_BOARD,
        TRAFFIC_CONE,
        TRAFFIC_POLE,
        TRAFFIC_LANE,
        TRAFFIC_CURB,
        TRAFFIC_LIGHT,
        TRAFFIC_CROSSING,
        TRAFFIC_MARKER,
        WATER_HORSE,
        COLLISION_SPHERE,
        COLLISION_POST,
        COLLISION_BAR,
        GROUND_LOCK,
        AUTO_GATE,
        WHEEL_CHOCK,
        NO_PARKING,
        SPEED_HUMP,

        // ANIMAL
        ANIMAL_DOG = 0x0500U,
        ANIMAL_CAT,
        ANIMAL_COW,
        ANIMAL_SHEEP,
    };

    /**
     * @brief Constructor
     */
    Classification() noexcept : main_type_{MainType::UNKNOWN}, sub_type_{SubType::UNKNOWN}
    {
    }

    /**
     * @brief Constructor from main sub type
     *
     * @param main_type object main class enum.
     * @param sub_type object sub class enum.
     */
    Classification(const MainType main_type, const SubType sub_type) noexcept
    {
        main_type_ = main_type;
        sub_type_  = sub_type;
    }

    /**
     * @brief Constructor from main sub type underlying
     *
     * @param main_type object main class code.
     * @param sub_type object sub class code.
     *
     * @throws std::runtime_error thrown if main_type or sub_type underlying code is invalid
     */
    Classification(const uint16_t main_type, const uint16_t sub_type)
    {
        if (IsValidMainType(main_type) == false)
        {
            throw std::runtime_error("Invalid main type code for Classification");
        }

        if (IsValidSubType(sub_type) == false)
        {
            throw std::runtime_error("Invalid sub type code for Classification");
        }

        main_type_ = static_cast<MainType>(main_type);
        sub_type_  = static_cast<SubType>(sub_type);
    }

    /**
     * @brief Construct from uin32 value
     *
     * @param value classification value
     */
    Classification(uint32_t value)
      : main_type_(static_cast<MainType>(value >> 16)), sub_type_(static_cast<SubType>(value & 0xffff))
    {
    }

    /**
     * @brief operator ==
     *
     * @param other other classification
     * @return return true if current classification equal to other otherwise false
     */
    bool_t operator==(const Classification& other) const noexcept
    {
        return ((main_type_ == other.main_type_) && (sub_type_ == other.sub_type_));
    }

    /**
     * @brief operator !=
     *
     * @param other other Classification
     * @return return true if current classification is not equal to other otherwise false
     */
    bool_t operator!=(const Classification& other) const noexcept
    {
        return !((main_type_ == other.main_type_) && (sub_type_ == other.sub_type_));
    }

    /**
     * @brief = operator overloading
     *
     * @param value right hand side value with uint32_t type
     * @return reference to Classification object
     */
    Classification& operator=(uint32_t value) noexcept
    {
        main_type_ = static_cast<MainType>(value >> 16);
        sub_type_  = static_cast<SubType>(value & 0xffff);
        return *this;
    }

    /**
     * @brief Get classification main type underlying code.
     *
     * @return main type underlying code
     */
    uint16_t UnderlyingMainType() const noexcept
    {
        return static_cast<std::underlying_type<MainType>::type>(main_type_);
    }

    /**
     * @brief Get classification sub type underlying code.
     *
     * @return sub type underlying code
     */
    uint16_t UnderlyingSubType() const noexcept
    {
        return static_cast<std::underlying_type<SubType>::type>(sub_type_);
    }

    /**
     * @brief Get classification type underlying code.
     *
     * @return type underlying code
     */
    uint32_t Underlying() const noexcept
    {
        uint32_t n_main_type = static_cast<uint32_t>(UnderlyingMainType()) << 16U;
        uint32_t n_sub_type  = static_cast<uint32_t>(UnderlyingSubType());
        return ((0xffff0000 & n_main_type) | (0x0000ffff & n_sub_type));
    }

    /**
     * @brief Get main type of classification
     *
     * @return main type of classification
     */
    MainType GetMainType() const noexcept
    {
        return main_type_;
    }

    /**
     * @brief Set main type of classification
     *
     * @param main_type - main type of classification
     */
    void SetMainType(const MainType main_type) noexcept
    {
        main_type_ = main_type;
    }

    /**
     * @brief Get sub type of classification
     *
     * @return sub type of classification
     */
    SubType GetSubType() const noexcept
    {
        return sub_type_;
    }

    /**
     * @brief Set sub type of classification
     *
     * @param sub_type sub type of classification
     */
    void SetSubType(const SubType sub_type) noexcept
    {
        sub_type_ = sub_type;
    }

    /**
     * @brief Cast to uint32 type
     *
     * @return uint32 value
     */
    operator uint32_t() const noexcept
    {
        return static_cast<uint32_t>(main_type_) << 16 | static_cast<uint32_t>(sub_type_);
    }

    /**
     * @brief Get human readable classification string
     *
     * @return readable string for classification
     */
    std::string ToString() const
    {
        std::stringstream ss;
        ss << "Classification: (type: " << Underlying() << ", main_type: " << UnderlyingMainType() << "-"
           << ToMainTypeString() << ", sub_type: " << UnderlyingSubType() << "-" << ToSubTypeString() << ")"
           << std::endl;
        return ss.str();
    }

    /**
     * @brief operator<<
     *
     * @param[in, out] os target ostream
     * @param[in] c classification
     */
    friend std::ostream& operator<<(std::ostream& os, const Classification& c)
    {
        os << c.ToString();
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
        return sizeof(uint32_t);
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
        serializer << static_cast<uint32_t>(*this);
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
        uint32_t value;
        deserializer >> value;
        *this = value;
    }

protected:
    /**
     * @brief whether a main type enum is valid
     *
     * @param main_type_code underlying code of MainType enum
     * @return return true if enum is valid for type_code otherwise false
     */
    bool_t IsValidMainType(const uint16_t type_code) noexcept
    {
        auto it = std::find_if(kMainTypeStringArray.begin(), kMainTypeStringArray.end(),
                               [type_code](const std::pair<MainType, std::string>& ele) {
                                   return static_cast<uint16_t>(ele.first) == type_code;
                               });
        if (it != kMainTypeStringArray.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief whether a sub type enum is valid
     *
     * @param type_code underlying code of SubType enum
     * @return return true if enum is valid for type_code otherwise false
     */
    bool_t IsValidSubType(const uint16_t type_code) noexcept
    {
        auto it = std::find_if(kSubTypeStringArray.begin(), kSubTypeStringArray.end(),
                               [type_code](const std::pair<SubType, std::string>& ele) {
                                   return static_cast<uint16_t>(ele.first) == type_code;
                               });
        if (it != kSubTypeStringArray.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief Get human readable main type string
     *
     * @return readable string for main type
     *
     * @throws runtime_error when main type is an illegal type
     */
    std::string ToMainTypeString() const
    {
        auto it =
            std::find_if(kMainTypeStringArray.begin(), kMainTypeStringArray.end(),
                         [this](const std::pair<MainType, std::string>& ele) { return ele.first == this->main_type_; });
        if (it != kMainTypeStringArray.end())
        {
            return it->second;
        }
        else
        {
            throw std::runtime_error("Invalid main type of Classification");
        }
    }

    /**
     * @brief Get human readable sub type string
     *
     * @return readable string for sub type
     *
     * @throws runtime_error when sub type is an illegal type
     */
    std::string ToSubTypeString() const
    {
        auto it =
            std::find_if(kSubTypeStringArray.begin(), kSubTypeStringArray.end(),
                         [this](const std::pair<SubType, std::string>& ele) { return ele.first == this->sub_type_; });
        if (it != kSubTypeStringArray.end())
        {
            return it->second;
        }
        else
        {
            throw std::runtime_error("Invalid sub type of Classification");
        }
    }

private:
    MainType main_type_;
    SubType  sub_type_;

    static const uint8_t kClassificationMainTypeNum = 7U;
    static const uint8_t kClassificationSubTypeNum  = 32U;
    static const std::array<std::pair<MainType, std::string>, kClassificationMainTypeNum> kMainTypeStringArray;
    static const std::array<std::pair<SubType, std::string>, kClassificationSubTypeNum>   kSubTypeStringArray;
};

/**
 * @}
 */
}  // namespace details
}  // namespace common
}  // namespace holo
#endif
