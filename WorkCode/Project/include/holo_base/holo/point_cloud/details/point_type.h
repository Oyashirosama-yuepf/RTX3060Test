/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_type.h
 * @brief This header file defines point types used by point cloud.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2020-10-29
 */

#ifndef HOLO_POINT_CLOUD_DETAILS_POINT_TYPE_H_
#define HOLO_POINT_CLOUD_DETAILS_POINT_TYPE_H_

#include <array>
#include <holo/common/timestamp.h>
#include <holo/core/exception.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace point_cloud
{
namespace details
{
/**
 * @brief Default point cloud point element alignment size
 */
static size_t const DEFAULT_ELEMENT_ALIGNMENT_VALUE = 4U;
/**
 * @brief Base class for point cloud point type
 *
 * @tparam T Scalar of point cloud point type
 * @tparam ALIGNMENT Point type element alignment size
 */
template <typename T, size_t ALIGNMENT = DEFAULT_ELEMENT_ALIGNMENT_VALUE>
class PointBase
{
public:
    using ScalarType = T;  ///< Scalar type

    static size_t const SIZE_VALUE              = 3U;         ///< Valid element size
    static size_t const ELEMENT_ALIGNMENT_VALUE = ALIGNMENT;  ///< Element alignment size

    /**
     * @brief Point element access with no bound check.
     *
     * @param index Index of element
     *
     * @return Reference to the element.
     */
    ScalarType const& operator[](size_t index) const noexcept
    {
        assert(index < SIZE_VALUE);
        return data_[index];
    }

    /**
     * @brief Point element access with no bound check.
     *
     * @param index Index of element
     *
     * @return Reference to the element.
     */
    ScalarType& operator[](size_t index) noexcept
    {
        assert(index < SIZE_VALUE);
        return data_[index];
    }

    /**
     * @brief Point element access with bound check.
     *
     * @param index Index of element
     *
     * @return Reference to the element.
     *
     * @throws holo::exception::OutOfRangeException if index >= SIZE_VALUE
     */
    ScalarType const& at(size_t index) const
    {
        if (index >= SIZE_VALUE)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return data_[index];
    }

    /**
     * @brief Point element access with bound check.
     *
     * @param index Index of element
     *
     * @return Reference to the element.
     *
     * @throws holo::exception::OutOfRangeException if index >= SIZE_VALUE
     */
    ScalarType& at(size_t index)
    {
        if (index >= SIZE_VALUE)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return data_[index];
    }

    /**
     * @brief Set x value
     *
     * @param value x value
     */
    void SetX(ScalarType value) noexcept
    {
        data_[0U] = value;
    }

    /**
     * @brief Set y value
     *
     * @param value y value
     */
    void SetY(ScalarType value) noexcept
    {
        data_[1U] = value;
    }

    /**
     * @brief Set z value
     *
     * @param value z value
     */
    void SetZ(ScalarType value) noexcept
    {
        data_[2U] = value;
    }

    /**
     * @brief Set element values
     *
     * @param x x value
     * @param y y value
     * @param z z value
     */
    void Set(ScalarType x, ScalarType y, ScalarType z) noexcept
    {
        data_[0U] = x;
        data_[1U] = y;
        data_[2U] = z;
    }

    /**
     * @brief Set element values from a random accessible data type
     *
     * @tparam InputType Input data type. InputType shall support random element access with operator[](size_t) method.
     * @param value Input data.
     */
    template <typename InputType>
    void Set(InputType const& value) noexcept
    {
        data_[0U] = value[0U];
        data_[1U] = value[1U];
        data_[2U] = value[2U];
    }

    /**
     * @brief Get x value
     *
     * @return  x value
     */
    ScalarType GetX() const noexcept
    {
        return data_[0U];
    }

    /**
     * @brief Get y value
     *
     * @return  y value
     */
    ScalarType GetY() const noexcept
    {
        return data_[1U];
    }

    /**
     * @brief Get z value
     *
     * @return  z value
     */
    ScalarType GetZ() const noexcept
    {
        return data_[2U];
    }

    /**
     * @brief Get values as a custom output type
     *
     * @tparam OutputType Output data type. OutputType shall support construct from x, y, z arguments or construct from
     * initializer list.
     *
     * @return Output data type.
     */
    template <typename OutputType>
    OutputType Get() const noexcept
    {
        return OutputType{data_[0U], data_[1U], data_[2U]};
    }

    template <typename OutputType>
    OutputType As() const noexcept
    {
        return {data_[0U], data_[1U], data_[2U]};
    }

protected:
    /**
     * @brief Default constructor
     */
    PointBase() noexcept : data_{}
    {
    }

    /**
     * @brief Construct from initializer list
     *
     * @param il element initializer list
     */
    PointBase(std::initializer_list<ScalarType> il)
    {
        if (il.size() > SIZE_VALUE)
        {
            (void)std::copy(il.begin(), il.begin() + SIZE_VALUE, data_);
        }
        else
        {
            (void)std::copy(il.begin(), il.end(), data_);
        }
    }

    /**
     * @brief Construct from Scalars
     *
     * @param x x value
     * @param y y value
     * @param z z value
     */
    PointBase(ScalarType x, ScalarType y, ScalarType z) noexcept : data_{x, y, z, static_cast<ScalarType>(0)}
    {
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    constexpr size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::AlignedSize<ALIGN>(sizeof(ScalarType) * SIZE_VALUE);
    }

    /**
     * @brief Serialize to buffer
     *
     * @tparam S Serializer type
     * @param serializer serialier object
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << data_[0U] << data_[1U] << data_[2U] << holo::serialization::align;
    }

    /**
     * @brief Deserialize from buffer
     *
     * @tparam D Deserializer type
     * @param deserializer deserialier object
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> data_[0U] >> data_[1U] >> data_[2U] >> holo::serialization::align;
    }

private:
    ScalarType data_[ELEMENT_ALIGNMENT_VALUE] = {};  ///< Point coordinates
};

/**
 * @brief Point type with x, y, z, intensity, ring number and timestamp
 *
 * @tparam T Scalar type
 * @tparam ALIGNMENT Point coordinate element alignment value.
 */
template <typename T, size_t ALIGNMENT = DEFAULT_ELEMENT_ALIGNMENT_VALUE>
class PointXYZIRSt : public PointBase<T>
{
public:
    using Base       = PointBase<T>;               ///< base class type
    using ScalarType = typename Base::ScalarType;  ///< Scalar type

    static size_t const SIZE_VALUE              = Base::SIZE_VALUE;  ///< Point coordinate element size.
    static size_t const ELEMENT_ALIGNMENT_VALUE =
        Base::ELEMENT_ALIGNMENT_VALUE;  ///< Point coordinate element alignment value.
    /**
     * @brief Default constructor
     */
    PointXYZIRSt() noexcept : Base{}, intensity_{}, ring_{}, stamp_{}
    {
    }

    /**
     * @brief Construct with coordinate values.
     *
     * @param x x value
     * @param y y value
     * @param z z value
     */
    PointXYZIRSt(ScalarType x, ScalarType y, ScalarType z) noexcept : Base{x, y, z}, intensity_{}, ring_{}, stamp_{}
    {
    }

    /**
     * @brief Construct with Input random accessible data type and intensity, ring, timestamp
     *
     * @tparam InputType Input data type used for initialize point coordinate. InputType shall be random accessible with
     * operator[](size_t)
     * @param pt Input random accessible data object.
     * @param intensity Intensity value.
     * @param ring Ring number.
     * @param stamp Timestamp value.
     */
    template <typename InputType>
    PointXYZIRSt(InputType pt, ScalarType intensity, uint32_t ring, holo::common::Timestamp stamp) noexcept
      : Base{pt[0U], pt[1U], pt[2U]}, intensity_{intensity}, ring_{ring}, stamp_{stamp}
    {
    }

    /**
     * @brief Construct from initializer list, intensity, ring and timestamp
     *
     * @param il Initializer list to init point coordinates
     * @param intensity Intensity value.
     * @param ring Ring number.
     * @param stamp Timestamp value.
     */
    PointXYZIRSt(std::initializer_list<ScalarType> il, ScalarType intensity, uint32_t ring,
                 holo::common::Timestamp stamp) noexcept
      : Base{il}, intensity_{intensity}, ring_{ring}, stamp_{stamp}
    {
    }

    /**
     * @brief operator+ to enable PointXYZIRSt + PointXYZIRSt.
     * @details This operation will add coordinates and intensity value of two points.
     *
     * @param rhs right hand side PointXYZIRSt object
     *
     * @return PointXYZIRSt object.
     */
    PointXYZIRSt operator+(PointXYZIRSt const& rhs) const noexcept
    {
        PointXYZIRSt ret(*this);
        ret += rhs;
        return ret;
    }

    /**
     * @brief operator+= to enable PointXYZIRSt += PointXYZIRSt.
     * @details This operation will add coordinates and intensity value of two points.
     *
     * @param rhs right hand side PointXYZIRSt object
     *
     * @return PointXYZIRSt object.
     */
    PointXYZIRSt& operator+=(PointXYZIRSt const& rhs) noexcept
    {
        (*this)[0U] += rhs[0U];
        (*this)[1U] += rhs[1U];
        (*this)[2U] += rhs[2U];
        intensity_ += rhs.intensity_;
        return *this;
    }

    /**
     * @brief operator- to enable PointXYZIRSt - PointXYZIRSt.
     * @details This operation will substract coordinates and intensity value of two points.
     *
     * @param rhs right hand side PointXYZIRSt object
     *
     * @return PointXYZIRSt object.
     */
    PointXYZIRSt operator-(PointXYZIRSt const& rhs) const noexcept
    {
        PointXYZIRSt ret(*this);
        ret -= rhs;
        return ret;
    }

    /**
     * @brief operator-= to enable PointXYZIRSt -= PointXYZIRSt.
     * @details This operation will substract coordinates and intensity value of two points.
     *
     * @param rhs right hand side PointXYZIRSt object
     *
     * @return PointXYZIRSt object.
     */
    PointXYZIRSt& operator-=(PointXYZIRSt const& rhs) noexcept
    {
        (*this)[0U] -= rhs[0U];
        (*this)[1U] -= rhs[1U];
        (*this)[2U] -= rhs[2U];
        intensity_ -= rhs.intensity_;
        return *this;
    }

    /**
     * @brief operator* to enable PointXYZIRSt * ScalarType.
     * @details This operation will multiply coordinates and intensity value of the point by a scalar value.
     *
     * @param rhs right hand side scalar value
     *
     * @return PointXYZIRSt object.
     */
    PointXYZIRSt operator*(ScalarType rhs) const noexcept
    {
        PointXYZIRSt ret(*this);
        ret *= rhs;
        return ret;
    }

    /**
     * @brief operator*= to enable PointXYZIRSt *= ScalarType.
     * @details This operation will multiply coordinates and intensity value of the point by a scalar value.
     *
     * @param rhs right hand side scalar value
     *
     * @return PointXYZIRSt object.
     */
    PointXYZIRSt& operator*=(ScalarType rhs) noexcept
    {
        (*this)[0U] *= rhs;
        (*this)[1U] *= rhs;
        (*this)[2U] *= rhs;
        intensity_ *= rhs;
        return *this;
    }

    /**
     * @brief friend operator* to enable ScalarType * PointXYZIRSt.
     * @details This operation will multiply coordinates and intensity value of the point by a scalar value.
     *
     * @param lhs left hand side scalar value
     * @param rhs right hand side PointXYZIRSt object
     *
     * @return PointXYZIRSt object.
     */
    friend PointXYZIRSt operator*(ScalarType lhs, PointXYZIRSt const& rhs) noexcept
    {
        PointXYZIRSt ret(rhs);
        ret *= lhs;
        return ret;
    }

    /**
     * @brief operator/ to enable PointXYZIRSt / ScalarType.
     * @details This operation will divide coordinates and intensity value of the point by a scalar value.
     *
     * @param rhs right hand side scalar value
     *
     * @return PointXYZIRSt object.
     */
    PointXYZIRSt operator/(ScalarType rhs)
    {
        PointXYZIRSt ret(*this);
        ret /= rhs;
        return ret;
    }

    /**
     * @brief operator/= to enable PointXYZIRSt /= ScalarType.
     * @details This operation will divide coordinates and intensity value of the point by a scalar value.
     *
     * @param rhs right hand side scalar value
     *
     * @return PointXYZIRSt object.
     */
    PointXYZIRSt& operator/=(ScalarType rhs) noexcept
    {
        (*this)[0] /= rhs;
        (*this)[1] /= rhs;
        (*this)[2] /= rhs;
        intensity_ /= rhs;
        return *this;
    }

    /**
     * @brief Get intensity value
     *
     * @return intensity value
     */
    ScalarType GetIntensity() const noexcept
    {
        return intensity_;
    }

    /**
     * @brief Get ring number
     *
     * @return ring number
     */
    uint32_t GetRing() const noexcept
    {
        return ring_;
    }

    /**
     * @brief Get timestamp
     *
     * @return Timestamp
     */
    holo::common::Timestamp GetTimestamp() const noexcept
    {
        return stamp_;
    }

    /**
     * @brief Set intensity value
     *
     * @param value intensity value
     */
    void SetIntensity(ScalarType value) noexcept
    {
        intensity_ = value;
    }

    /**
     * @brief Set ring number
     *
     * @param value Ring number
     */
    void SetRing(uint32_t value) noexcept
    {
        ring_ = value;
    }

    /**
     * @brief Set timestamp value
     *
     * @param value timestamp value
     */
    void SetTimestamp(holo::common::Timestamp value) noexcept
    {
        stamp_ = value;
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
        // FIXME: sizeof(holo::Timestamp) should be stamp.GetSerializedSize<ALIGN>()
        return holo::serialization::AlignedSize<ALIGN>(
            holo::serialization::AlignedSize<ALIGN>(Base::template GetSerializedSize<ALIGN>() 
            + sizeof(ScalarType) + sizeof(uint32_t)) +
            sizeof(holo::common::Timestamp));
    }

    /**
     * @brief Serialize to buffer
     *
     * @tparam S Serializer type
     * @param serializer serialier object
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        Base::Serialize(serializer);
        serializer << intensity_ << ring_ << stamp_ << holo::serialization::align;
    }

    /**
     * @brief Deserialize from buffer
     *
     * @tparam D Deserializer type
     * @param deserializer deserialier object
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        Base::Deserialize(deserializer);
        deserializer >> intensity_ >> ring_ >> stamp_ >> holo::serialization::align;
    }

private:
    ScalarType              intensity_ = static_cast<ScalarType>(0);  ///< intensity value
    uint32_t                ring_      = 0U;                          ///< ring number
    holo::common::Timestamp stamp_     = {0U, 0U};                    ///< timestamp value
};

/**
 * @brief Point type with x, y, z, intensity, ring number, rgb and timestamp
 *
 * @tparam T Scalar type
 * @tparam ALIGNMENT Point coordinate element alignment value.
 */
template <typename T, size_t ALIGNMENT = DEFAULT_ELEMENT_ALIGNMENT_VALUE>
class PointXYZIRRgbSt : public PointBase<T>
{
public:
    using Base       = PointBase<T>;               ///< base class type
    using ScalarType = typename Base::ScalarType;  ///< Scalar type

    static size_t const SIZE_VALUE              = Base::SIZE_VALUE;  ///< Point coordinate element size.
    static size_t const ELEMENT_ALIGNMENT_VALUE =
        Base::ELEMENT_ALIGNMENT_VALUE;  ///< Point coordinate element alignment value.
    /**
     * @brief Default constructor
     */
    PointXYZIRRgbSt() noexcept : Base{}, intensity_{}, ring_{}, rgb_{}, stamp_{}
    {
    }

    /**
     * @brief Construct with coordinate values.
     *
     * @param x x value
     * @param y y value
     * @param z z value
     */
    PointXYZIRRgbSt(ScalarType x, ScalarType y, ScalarType z) noexcept
      : Base{x, y, z}, intensity_{}, ring_{}, rgb_{}, stamp_{}
    {
    }

    /**
     * @brief Construct with Input random accessible data type and intensity, ring, rgb, timestamp
     *
     * @tparam InputType Input data type used for initialize point coordinate. InputType shall be random accessible with
     * operator[](size_t)
     * @param pt Input random accessible data object.
     * @param intensity Intensity value.
     * @param ring Ring number.
     * @param rgb Rgb value.
     * @param stamp Timestamp value.
     */
    template <typename InputType>
    PointXYZIRRgbSt(InputType pt, ScalarType intensity, uint32_t ring, std::array<uint8_t, 3> rgb,
                    holo::common::Timestamp stamp) noexcept
      : Base{pt[0U], pt[1U], pt[2U]}, intensity_{intensity}, ring_{ring}, rgb_{rgb}, stamp_{stamp}
    {
    }

    /**
     * @brief Construct from initializer list, intensity, ring and timestamp
     *
     * @param il Initializer list to init point coordinates
     * @param intensity Intensity value.
     * @param ring Ring number.
     * @param rgb Rgb value.
     * @param stamp Timestamp value.
     */
    PointXYZIRRgbSt(std::initializer_list<ScalarType> il, ScalarType intensity, uint32_t ring,
                    std::array<uint8_t, 3> rgb, holo::common::Timestamp stamp) noexcept
      : Base{il}, intensity_{intensity}, ring_{ring}, rgb_{rgb}, stamp_{stamp}
    {
    }

    /**
     * @brief operator+ to enable PointXYZIRRgbSt + PointXYZIRRgbSt.
     * @details This operation will add coordinates and intensity value of two points.
     *
     * @param rhs right hand side PointXYZIRRgbSt object
     *
     * @return PointXYZIRRgbSt object.
     */
    PointXYZIRRgbSt operator+(PointXYZIRRgbSt const& rhs) const noexcept
    {
        PointXYZIRRgbSt ret(*this);
        ret += rhs;
        return ret;
    }

    /**
     * @brief operator+= to enable PointXYZIRRgbSt += PointXYZIRRgbSt.
     * @details This operation will add coordinates and intensity value of two points.
     *
     * @param rhs right hand side PointXYZIRRgbSt object
     *
     * @return PointXYZIRRgbSt object.
     */
    PointXYZIRRgbSt& operator+=(PointXYZIRRgbSt const& rhs) noexcept
    {
        (*this)[0U] += rhs[0U];
        (*this)[1U] += rhs[1U];
        (*this)[2U] += rhs[2U];
        intensity_ += rhs.intensity_;
        return *this;
    }

    /**
     * @brief operator- to enable PointXYZIRRgbSt - PointXYZIRRgbSt.
     * @details This operation will substract coordinates and intensity value of two points.
     *
     * @param rhs right hand side PointXYZIRRgbSt object
     *
     * @return PointXYZIRRgbSt object.
     */
    PointXYZIRRgbSt operator-(PointXYZIRRgbSt const& rhs) const noexcept
    {
        PointXYZIRRgbSt ret(*this);
        ret -= rhs;
        return ret;
    }

    /**
     * @brief operator-= to enable PointXYZIRRgbSt -= PointXYZIRRgbSt.
     * @details This operation will substract coordinates and intensity value of two points.
     *
     * @param rhs right hand side PointXYZIRRgbSt object
     *
     * @return PointXYZIRRgbSt object.
     */
    PointXYZIRRgbSt& operator-=(PointXYZIRRgbSt const& rhs) noexcept
    {
        (*this)[0U] -= rhs[0U];
        (*this)[1U] -= rhs[1U];
        (*this)[2U] -= rhs[2U];
        intensity_ -= rhs.intensity_;
        return *this;
    }

    /**
     * @brief operator* to enable PointXYZIRRgbSt * ScalarType.
     * @details This operation will multiply coordinates and intensity value of the point by a scalar value.
     *
     * @param rhs right hand side scalar value
     *
     * @return PointXYZIRRgbSt object.
     */
    PointXYZIRRgbSt operator*(ScalarType rhs) const noexcept
    {
        PointXYZIRRgbSt ret(*this);
        ret *= rhs;
        return ret;
    }

    /**
     * @brief operator*= to enable PointXYZIRRgbSt *= ScalarType.
     * @details This operation will multiply coordinates and intensity value of the point by a scalar value.
     *
     * @param rhs right hand side scalar value
     *
     * @return PointXYZIRRgbSt object.
     */
    PointXYZIRRgbSt& operator*=(ScalarType rhs) noexcept
    {
        (*this)[0U] *= rhs;
        (*this)[1U] *= rhs;
        (*this)[2U] *= rhs;
        intensity_ *= rhs;
        return *this;
    }

    /**
     * @brief friend operator* to enable ScalarType * PointXYZIRRgbSt.
     * @details This operation will multiply coordinates and intensity value of the point by a scalar value.
     *
     * @param lhs left hand side scalar value
     * @param rhs right hand side PointXYZIRRgbSt object
     *
     * @return PointXYZIRRgbSt object.
     */
    friend PointXYZIRRgbSt operator*(ScalarType lhs, PointXYZIRRgbSt const& rhs) noexcept
    {
        PointXYZIRRgbSt ret(rhs);
        ret *= lhs;
        return ret;
    }

    /**
     * @brief operator/ to enable PointXYZIRRgbSt / ScalarType.
     * @details This operation will divide coordinates and intensity value of the point by a scalar value.
     *
     * @param rhs right hand side scalar value
     *
     * @return PointXYZIRRgbSt object.
     */
    PointXYZIRRgbSt operator/(ScalarType rhs)
    {
        PointXYZIRRgbSt ret(*this);
        ret /= rhs;
        return ret;
    }

    /**
     * @brief operator/= to enable PointXYZIRRgbSt /= ScalarType.
     * @details This operation will divide coordinates and intensity value of the point by a scalar value.
     *
     * @param rhs right hand side scalar value
     *
     * @return PointXYZIRRgbSt object.
     */
    PointXYZIRRgbSt& operator/=(ScalarType rhs) noexcept
    {
        (*this)[0] /= rhs;
        (*this)[1] /= rhs;
        (*this)[2] /= rhs;
        intensity_ /= rhs;
        return *this;
    }

    /**
     * @brief Get intensity value
     *
     * @return intensity value
     */
    ScalarType GetIntensity() const noexcept
    {
        return intensity_;
    }

    /**
     * @brief Get ring number
     *
     * @return ring number
     */
    uint32_t GetRing() const noexcept
    {
        return ring_;
    }

    /**
     * @brief Get timestamp
     *
     * @return Timestamp
     */
    holo::common::Timestamp GetTimestamp() const noexcept
    {
        return stamp_;
    }

    /**
     * @brief Get rgb value
     *
     * @return rgb value
     */
    std::array<uint8_t, 3> GetRgb() const noexcept
    {
        return rgb_;
    }

    /**
     * @brief Set intensity value
     *
     * @param value intensity value
     */
    void SetIntensity(ScalarType value) noexcept
    {
        intensity_ = value;
    }

    /**
     * @brief Set ring number
     *
     * @param value Ring number
     */
    void SetRing(uint32_t value) noexcept
    {
        ring_ = value;
    }

    /**
     * @brief Set timestamp value
     *
     * @param value timestamp value
     */
    void SetTimestamp(holo::common::Timestamp value) noexcept
    {
        stamp_ = value;
    }

    /**
     * @brief Set rgb value
     *
     * @param value rgb value
     */
    void SetRgb(std::array<uint8_t, 3> value) noexcept
    {
        rgb_ = value;
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
        return holo::serialization::AlignedSize<ALIGN>(
                   holo::serialization::AlignedSize<ALIGN>(Base::template GetSerializedSize<ALIGN>() 
                   + sizeof(ScalarType) + sizeof(uint32_t)) + sizeof(uint8_t) * 3) +
               stamp_.GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize to buffer
     *
     * @tparam S Serializer type
     * @param serializer serialier object
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        Base::Serialize(serializer);
        serializer << intensity_ << ring_ << rgb_[0] << rgb_[1] << rgb_[2] << stamp_;
    }

    /**
     * @brief Deserialize from buffer
     *
     * @tparam D Deserializer type
     * @param deserializer deserialier object
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        Base::Deserialize(deserializer);
        deserializer >> intensity_ >> ring_ >> rgb_[0] >> rgb_[1] >> rgb_[2] >> stamp_;
    }

private:
    ScalarType              intensity_ = static_cast<ScalarType>(0);  ///< intensity value
    uint32_t                ring_      = 0U;                          ///< ring number
    std::array<uint8_t, 3>  rgb_       = {0U, 0U, 0U};                ///< rgb value
    holo::common::Timestamp stamp_     = {0U, 0U};                    ///< timestamp value
};

}  // namespace details
}  // namespace point_cloud
}  // namespace holo

#endif
