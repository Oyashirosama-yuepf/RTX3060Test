/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_msg_base.h
 * @brief Base class of all map message, store uint32/float32/bool vector.
 * @note: Only can be used in holo_cmw convert function.
 * @author zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-11-26"
 */

#ifndef HOLO_MAP_MAP_MSG_BASE_H__
#define HOLO_MAP_MAP_MSG_BASE_H__

#include <bitset>
#include <vector>

#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace map
{
/**
 * @addtogroup map
 * @{
 *
 */
class MapMsgBase
{
public:
    /**
     * @hideinitializer
     */
    static const ::holo::uint8_t kHoloMapBitset_32 = 32U;  /// use for 32 bitset

public:
    /**
     * @brief Construct a new map msg base object
     *
     * @param[in] indicator_size Be used to init indicators_
     * @param[in] uint32_size Be used to resize uint32_value_
     * @param[in] float32_size Be used to resize float32_value_
     */
    MapMsgBase(::holo::uint8_t indicator_size, ::holo::uint8_t uint32_size, ::holo::uint8_t float32_size) noexcept
      : valid_indicator_size_(indicator_size)
      , indicator_value_max_size_(indicator_size)
      , indicators_(0U)
      , valid_uint32_size_(uint32_size)
      , uint32_value_max_size_(uint32_size)
      , uint32_values_(static_cast<::std::size_t>(uint32_value_max_size_), 0U)
      , valid_float32_size_(float32_size)
      , float32_values_max_size_(float32_size)
      , float32_values_(static_cast<::std::size_t>(float32_values_max_size_), 0U)
    {
    }

    /**
     * @brief Destructor
     *
     */
    virtual ~MapMsgBase() = default;

    /**
     * @brief Copy constructor.
     *
     * @param[in] other
     */
    MapMsgBase(const MapMsgBase& other) noexcept
      : valid_indicator_size_(other.valid_indicator_size_)
      , indicator_value_max_size_(other.indicator_value_max_size_)
      , indicators_(other.indicators_)
      , valid_uint32_size_(other.valid_uint32_size_)
      , uint32_value_max_size_(other.uint32_value_max_size_)
      , uint32_values_(other.uint32_values_)
      , valid_float32_size_(other.valid_float32_size_)
      , float32_values_max_size_(other.float32_values_max_size_)
      , float32_values_(other.float32_values_)
    {
    }

    /**
     * @brief Copy constructor by r-value
     *
     * @param[in] other
     */
    MapMsgBase(MapMsgBase&& other) noexcept
      : valid_indicator_size_(other.valid_indicator_size_)
      , indicator_value_max_size_(other.indicator_value_max_size_)
      , indicators_(other.indicators_)
      , valid_uint32_size_(other.valid_uint32_size_)
      , uint32_value_max_size_(other.uint32_value_max_size_)
      , uint32_values_(std::move(other.uint32_values_))
      , valid_float32_size_(other.valid_float32_size_)
      , float32_values_max_size_(other.float32_values_max_size_)
      , float32_values_(std::move(other.float32_values_))
    {
    }

    /**
     * @brief Assignment operator
     *
     * @param[in] other
     * @return MapMsgBase&
     */
    MapMsgBase& operator=(const MapMsgBase& other) noexcept
    {
        if (this != &other)
        {
            this->indicators_     = other.indicators_;
            this->uint32_values_  = other.uint32_values_;
            this->float32_values_ = other.float32_values_;

            this->valid_float32_size_   = other.valid_float32_size_;
            this->valid_indicator_size_ = other.valid_indicator_size_;
            this->valid_uint32_size_    = other.valid_uint32_size_;
        }
        return *this;
    }

    /**
     * @brief Assignment operator by r-value
     *
     * @param[in] other
     * @return MapMsgBase&
     */
    MapMsgBase& operator=(MapMsgBase&& other) noexcept
    {
        if (this != &other)
        {
            this->indicators_ = other.indicators_;
            ::std::swap(this->uint32_values_, other.uint32_values_);
            ::std::swap(this->float32_values_, other.float32_values_);
            this->valid_float32_size_   = other.valid_float32_size_;
            this->valid_indicator_size_ = other.valid_indicator_size_;
            this->valid_uint32_size_    = other.valid_uint32_size_;
        }
        return *this;
    }

    /**
     * @brief Clear member variables
     *
     */
    void Clear()
    {
        (void)this->indicators_.reset();
        this->uint32_values_.clear();
        this->uint32_values_.resize(static_cast<::std::size_t>(uint32_value_max_size_), 0U);
        this->float32_values_.clear();
        this->float32_values_.resize(static_cast<::std::size_t>(float32_values_max_size_), 0U);
    }

    /**
     * @brief Set the indicators by value, NOTE: Only can be used in holo_cmw convert function.
     *
     * @param[in] value Long value for indicator
     */
    void SetIndicatorsByValue(const ::holo::uint32_t value) noexcept
    {
        this->indicators_ = static_cast<::std::bitset<kHoloMapBitset_32>>(value);
    }

    /**
     * @brief Set the indicators, NOTE: Only can be used in holo_cmw convert function.
     *
     * @param[in] value Bitset value for indicator
     */
    void SetIndicators(const ::std::bitset<kHoloMapBitset_32>& value) noexcept
    {
        this->indicators_ = value;
    }

    /**
     * @brief Get the indicators as value, NOTE: Only can be used in holo_cmw convert function.
     *
     * @return the indicators as value
     */
    ::holo::uint32_t GetIndicatorsByValue() const noexcept
    {
        return static_cast<::holo::uint32_t>(this->indicators_.to_ulong());
    }

    /**
     * @brief Set the values float32 , NOTE: Only can be used in holo_cmw convert function.
     *
     * @param[in] value float32 values
     */
    void SetValuesFloat32(const ::std::vector<::holo::float32_t>& value) noexcept
    {
        this->float32_values_ = value;
    }

    /**
     * @brief Set the values float32 by r-value, NOTE: Only can be used in holo_cmw convert function.
     *
     * @param[in] value float32 values
     */
    void SetValuesFloat32(::std::vector<::holo::float32_t>&& value) noexcept
    {
        ::std::swap(this->float32_values_, value);
    }

    /**
     * @brief Get the values float32 reference, NOTE: Only can be used in holo_cmw convert function.
     *
     * @return const ::std::vector<::holo::float32_t>&
     */
    const ::std::vector<::holo::float32_t>& GetValuesFloat32() const noexcept
    {
        return this->float32_values_;
    }

    /**
     * @brief Set the values uint32_t , NOTE: Only can be used in holo_cmw convert function.
     *
     * @param[in] value uint32 values
     */
    void SetValuesUint32(const ::std::vector<::holo::uint32_t>& value) noexcept
    {
        this->uint32_values_ = value;
    }

    /**
     * @brief Set the Values uint32_t by r-value, NOTE: Only can be used in holo_cmw convert function.
     *
     * @param[in] value uint32 values
     */
    void SetValuesUint32(::std::vector<::holo::uint32_t>&& value) noexcept
    {
        ::std::swap(this->uint32_values_, value);
    }

    /**
     * @brief Get the Values int32 reference, NOTE: Only be used in holo_cmw convert function.
     *
     * @return const ::std::vector<::holo::uint32_t>&
     */
    const ::std::vector<::holo::uint32_t>& GetValuesUint32() const noexcept
    {
        return this->uint32_values_;
    }

    /**
     * @brief Judge if code version matchs bag,
     *
     * @return bool_t
     */
    bool_t IsValid() const noexcept
    {
        return (this->valid_indicator_size_ == this->indicator_value_max_size_) &&
               (this->valid_float32_size_ == this->float32_values_max_size_) &&
               (this->valid_uint32_size_ == this->uint32_value_max_size_);
    }

    /**
     * @brief Set the indicator valid size in message
     *
     * @param[in] value indicator size
     */
    void SetValidIndicatorSize(const ::holo::uint8_t value) noexcept
    {
        this->valid_indicator_size_ = value;
    }
    /**
     * @brief Set the float32 buffer valid size in message
     *
     * @param[in] value valid float32 size
     */
    void SetValidFloat32Size(const ::holo::uint8_t value) noexcept
    {
        this->valid_float32_size_ = value;
    }
    /**
     * @brief Set the uint32 buffer valid size in message
     *
     * @param[in] value valid uint32 size
     */
    void SetValidUint32Size(const ::holo::uint8_t value) noexcept
    {
        this->valid_uint32_size_ = value;
    }
    /**
     * @brief Get the indicator valid size in message
     *
     * @return ::holo::uint8_t
     */
    ::holo::uint8_t GetValidIndicatorSize() const noexcept
    {
        return this->valid_indicator_size_;
    }
    /**
     * @brief Get the float32 buffer valid size in message
     *
     * @return ::holo::uint8_t
     */
    ::holo::uint8_t GetValidFloat32Size() const noexcept
    {
        return this->valid_float32_size_;
    }
    /**
     * @brief Get the uint32 buffer valid size in message
     *
     * @return ::holo::uint8_t
     */
    ::holo::uint8_t GetValidUint32Size() const noexcept
    {
        return this->valid_uint32_size_;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::AlignedSize<ALIGN>(
            holo::serialization::AlignedSize<ALIGN>(sizeof(::holo::uint8_t) + sizeof(::holo::uint8_t) +
                                            sizeof(::holo::uint8_t)) +
            sizeof(uint32_t) + sizeof(uint32_t) + uint32_values_.size() * sizeof(uint32_t) + sizeof(uint32_t) +
            float32_values_.size() * sizeof(holo::float32_t));
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        uint32_t vec_size = static_cast<uint32_t>(uint32_values_.size());
        serializer << valid_indicator_size_ << valid_uint32_size_ << valid_float32_size_ << holo::serialization::align
                   << GetIndicatorsByValue() << vec_size;
        for (size_t i = 0; i < vec_size; ++i)
        {
            serializer << uint32_values_[i];
        }
        vec_size = static_cast<uint32_t>(float32_values_.size());
        serializer << vec_size;
        for (size_t i = 0; i < vec_size; ++i)
        {
            serializer << float32_values_[i];
        }
        serializer << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        ::holo::uint32_t indicator_value;
        ::holo::uint32_t vec_size;

        deserializer >> valid_indicator_size_ >> valid_uint32_size_ >> valid_float32_size_ >> indicator_value >>
            vec_size;
        SetIndicatorsByValue(indicator_value);
        uint32_values_.resize(vec_size);
        for (size_t i = 0U; i < vec_size; ++i)
        {
            deserializer >> uint32_values_[i];
        }
        deserializer >> vec_size;
        float32_values_.resize(vec_size);
        for (size_t i = 0U; i < vec_size; ++i)
        {
            deserializer >> float32_values_[i];
        }
        deserializer >> holo::serialization::align;
    }

protected:
    /// this->indicators_ of message, refer to "XXXInfoIndicatorType" in derive class for details.
    ::holo::uint8_t                  valid_indicator_size_{0U};
    const ::holo::uint8_t            indicator_value_max_size_{0U};
    ::std::bitset<kHoloMapBitset_32> indicators_;
    /// int32 value aggregation, refer to "XXXValuesUint32" in derive class for details.
    ::holo::uint8_t                 valid_uint32_size_{0U};
    const ::holo::uint8_t           uint32_value_max_size_{0U};
    ::std::vector<::holo::uint32_t> uint32_values_;
    /// float32 value aggregation, refer to "XXXaluesFloat" in derive class for details.
    ::holo::uint8_t                  valid_float32_size_{0U};
    const ::holo::uint8_t            float32_values_max_size_{0U};
    ::std::vector<::holo::float32_t> float32_values_;
};  // class MapMsgBase

/**
 * @}
 *
 */
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_MAP_MSG_BASE_H__
