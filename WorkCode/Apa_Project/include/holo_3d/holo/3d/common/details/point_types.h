/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_types.h
 * @brief This header file defines point types used by point cloud.
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-11-29
 */
#ifndef HOLO_3D_COMMON_DETAILS_POINT_TYPES_H_
#define HOLO_3D_COMMON_DETAILS_POINT_TYPES_H_

#include <assert.h>

#include <holo/numerics/vector.h>
#include <holo/point_cloud/details/point_type.h>
#include <holo/utils/buffer.h>

namespace holo
{
namespace point_cloud
{
namespace details
{
/**
 * @brief Point type with x, y, z, nx, ny, nz.
 *
 * @tparam T Scalar type
 * @tparam ALIGNMENT Point coordinate element alignment value.
 */
template <typename T, size_t ALIGNMENT = DEFAULT_ELEMENT_ALIGNMENT_VALUE>
class PointXYZNormalt : public PointBase<T>
{
public:
    using Base        = PointBase<T>;               ///< base class type
    using ScalarType  = typename Base::ScalarType;  ///< Scalar type
    using Vector3Type = numerics::Vector3T<ScalarType>;

    static size_t const SIZE_VALUE = Base::SIZE_VALUE;  ///< Point coordinate element size.
    static size_t const ELEMENT_ALIGNMENT_VALUE =
        Base::ELEMENT_ALIGNMENT_VALUE;  ///< Point coordinate element alignment value.

    /**
     * @brief Default constructor
     */
    PointXYZNormalt() noexcept : Base{}, normal_{}
    {
    }

    /**
     * @brief Construct with coordinate values.
     *
     * @param x x value
     * @param y y value
     * @param z z value
     */
    PointXYZNormalt(ScalarType x, ScalarType y, ScalarType z) noexcept : Base{x, y, z}, normal_{}
    {
    }

    /**
     * @brief Construct with Input random accessible data type and nx, ny, nz
     *
     * @tparam InputType Input data type used for initialize point coordinate. InputType shall be random accessible with
     * operator[](size_t)
     * @param pt Input random accessible data object.
     * @param nx normal x.
     * @param ny normal y.
     * @param nz normal z.
     */
    template <typename InputType>
    PointXYZNormalt(InputType pt, ScalarType nx, ScalarType ny, ScalarType nz) noexcept
      : Base{pt[0U], pt[1U], pt[2U]}, normal_{nx, ny, nz}
    {
    }

    /**
     * @brief Construct with Input random accessible data type and normal type
     *
     * @tparam InputType Input data type used for initialize point coordinate. InputType shall be random accessible with
     * operator[](size_t)
     * @tparam NormalType Input data type used for initialize point normal. NormalType shall be random accessible with
     * operator[](size_t)
     * @param pt Input random accessible data object.
     * @param n Input random accessible normal object.
     */
    template <typename InputType, typename NormaType>
    PointXYZNormalt(InputType pt, NormaType n) noexcept
      : Base{pt[0U], pt[1U], pt[2U]}, normal_{n[0U], n[1U], n[2U], static_cast<ScalarType>(0)}
    {
    }

    /**
     * @brief Construct from initializer list, nx, ny and nz
     *
     * @param il Initializer list to init point coordinates
     * @param nx normal x.
     * @param ny normal y.
     * @param nz normal z.
     */
    PointXYZNormalt(std::initializer_list<ScalarType> il, ScalarType nx, ScalarType ny, ScalarType nz) noexcept
      : Base{il}, normal_{nx, ny, nz, static_cast<ScalarType>(0)}
    {
    }

    /**
     * @brief operator+ to enable PointXYZNormalt + PointXYZNormalt.
     * @details This operation will add coordinates and normal of two points.
     *
     * @param rhs right hand side PointXYZNormalt object
     *
     * @return PointXYZNormalt object.
     */
    PointXYZNormalt operator+(PointXYZNormalt const& rhs) const noexcept
    {
        PointXYZNormalt ret(*this);
        ret += rhs;
        return ret;
    }

    /**
     * @brief operator+= to enable PointXYZNormalt += PointXYZNormalt.
     * @details This operation will add coordinates and normal value of two points.
     *
     * @param rhs right hand side PointXYZNormalt object
     *
     * @return PointXYZNormalt object.
     */
    PointXYZNormalt& operator+=(PointXYZNormalt const& rhs) noexcept
    {
        (*this)[0U] += rhs[0U];
        (*this)[1U] += rhs[1U];
        (*this)[2U] += rhs[2U];

        normal_[0U] += rhs.normal_[0U];
        normal_[1U] += rhs.normal_[1U];
        normal_[2U] += rhs.normal_[2U];
        return *this;
    }

    /**
     * @brief operator- to enable PointXYZNormalt - PointXYZNormalt.
     * @details This operation will substract coordinates value of two points.
     *
     * @param rhs right hand side PointXYZNormalt object
     *
     * @return PointXYZNormalt object.
     */
    PointXYZNormalt operator-(PointXYZNormalt const& rhs) const noexcept
    {
        PointXYZNormalt ret(*this);
        ret -= rhs;
        return ret;
    }

    /**
     * @brief operator-= to enable PointXYZNormalt -= PointXYZNormalt.
     * @details This operation will substract coordinates of two points.
     *
     * @param rhs right hand side PointXYZNormalt object
     *
     * @return PointXYZNormalt object.
     */
    PointXYZNormalt& operator-=(PointXYZNormalt const& rhs) noexcept
    {
        (*this)[0U] -= rhs[0U];
        (*this)[1U] -= rhs[1U];
        (*this)[2U] -= rhs[2U];
        return *this;
    }

    /**
     * @brief operator* to enable PointXYZNormalt * ScalarType.
     * @details This operation will multiply coordinates and normal value of the point by a scalar value.
     *
     * @param rhs right hand side scalar value
     *
     * @return PointXYZNormalt object.
     */
    PointXYZNormalt operator*(ScalarType rhs) const noexcept
    {
        PointXYZNormalt ret(*this);
        ret *= rhs;
        return ret;
    }

    /**
     * @brief operator*= to enable PointXYZNormalt *= ScalarType.
     * @details This operation will multiply coordinates and normal value of the point by a scalar value.
     *
     * @param rhs right hand side scalar value
     *
     * @return PointXYZNormalt object.
     */
    PointXYZNormalt& operator*=(ScalarType rhs) noexcept
    {
        (*this)[0U] *= rhs;
        (*this)[1U] *= rhs;
        (*this)[2U] *= rhs;
        normal_[0U] *= rhs;
        normal_[1U] *= rhs;
        normal_[2U] *= rhs;
        return *this;
    }

    /**
     * @brief friend operator* to enable ScalarType * PointXYZNormalt.
     * @details This operation will multiply coordinates and normal value of the point by a scalar value.
     *
     * @param lhs left hand side scalar value
     * @param rhs right hand side PointXYZNormalt object
     *
     * @return PointXYZNormalt object.
     */
    friend PointXYZNormalt operator*(ScalarType lhs, PointXYZNormalt const& rhs) noexcept
    {
        PointXYZNormalt ret(rhs);
        ret *= lhs;
        return ret;
    }

    /**
     * @brief operator/ to enable PointXYZNormalt / PointXYZNormalt.
     * @details This operation will divide coordinates and normal value of the point by a scalar value.
     *
     * @param rhs right hand side scalar value
     *
     * @return PointXYZNormalt object.
     */
    PointXYZNormalt operator/(ScalarType rhs)
    {
        PointXYZNormalt ret(*this);
        ret /= rhs;
        return ret;
    }

    /**
     * @brief operator/= to enable PointXYZNormalt /= ScalarType.
     * @details This operation will divide coordinates and normal value of the point by a scalar value.
     *
     * @param rhs right hand side scalar value
     *
     * @return PointXYZNormalt object.
     */
    PointXYZNormalt& operator/=(ScalarType rhs) noexcept
    {
        (*this)[0U] /= rhs;
        (*this)[1U] /= rhs;
        (*this)[2U] /= rhs;
        normal_[0U] /= rhs;
        normal_[1U] /= rhs;
        normal_[2U] /= rhs;
        return *this;
    }

    /**
     * @brief Get normal x value
     *
     * @return normal x value
     */
    ScalarType GetNormalX() const noexcept
    {
        return normal_[0U];
    }

    /**
     * @brief Set normal x value
     *
     * @param nx normal x value
     */
    void SetNormalX(ScalarType nx) noexcept
    {
        normal_[0U] = nx;
    }

    /**
     * @brief Get normal y value
     *
     * @return normal y value
     */
    ScalarType GetNormalY() const noexcept
    {
        return normal_[1U];
    }

    /**
     * @brief Set normal y value
     *
     * @param ny normal y value
     */
    void SetNormalY(ScalarType ny) noexcept
    {
        normal_[1U] = ny;
    }

    /**
     * @brief Get normal z value
     *
     * @return normal z value
     */
    ScalarType GetNormalZ() const noexcept
    {
        return normal_[2U];
    }

    /**
     * @brief Set normal z value
     *
     * @param nz normal z value
     */
    void SetNormalZ(ScalarType nz) noexcept
    {
        normal_[2U] = nz;
    }

    /**
     * @brief Set normal values
     *
     * @param nx normal x value
     * @param ny normal y value
     * @param nz normal z value
     */
    void SetNormal(ScalarType nx, ScalarType ny, ScalarType nz) noexcept
    {
        normal_[0U] = nx;
        normal_[1U] = ny;
        normal_[2U] = nz;
    }

    /**
     * @brief Get the Normal Vector
     *
     * @return Vector3T<ScalarType>
     */
    Vector3Type GetNormal() const noexcept
    {
        return Vector3Type(normal_[0U], normal_[1U], normal_[2U]);
    }

    /**
     * @brief Set normal values from a random accessible data type
     *
     * @tparam InputType Input data type. InputType shall support random element access with operator[](size_t) method.
     * @param value Input data.
     */
    template <typename InputType>
    void SetNormal(InputType const& value) noexcept
    {
        normal_[0U] = value[0U];
        normal_[1U] = value[1U];
        normal_[2U] = value[2U];
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
    OutputType GetNormal() const noexcept
    {
        return OutputType{normal_[0U], normal_[1U], normal_[2U]};
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
        return holo::utils::AlignedSize<ALIGN>(holo::utils::AlignedSize<ALIGN>(
            Base::template GetSerializedSize<ALIGN>() + ELEMENT_ALIGNMENT_VALUE * sizeof(ScalarType)));
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
        serializer << normal_[0U] << normal_[1U] << normal_[2U] << holo::utils::align;
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
        deserializer >> normal_[0U] >> normal_[1U] >> normal_[2U] >> holo::utils::align;
    }

private:
    ScalarType normal_[ELEMENT_ALIGNMENT_VALUE] = {};  ///< Point normal
};

}  // namespace details
}  // namespace point_cloud
}  // namespace holo

#endif
