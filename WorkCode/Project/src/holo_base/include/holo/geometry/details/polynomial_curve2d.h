/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file polynomial_curve2d.h
 * @brief This header file defines PolynomialCurve2DT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-11
 */

#ifndef HOLO_GEOMETRY_DETAILS_POLYNOMIAL_CURVE2D_H_
#define HOLO_GEOMETRY_DETAILS_POLYNOMIAL_CURVE2D_H_

#include <cstring>
#include <string>
#include <vector>

#include <holo/geometry/curve_descriptor.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/pose2.h>
#include <holo/geometry/rot2.h>
#include <holo/numerics/eigen_solver.h>
#include <holo/numerics/matrix.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace geometry
{
namespace details
{
/**
 * @addtogroup geometry
 *
 * @{
 */

/**
 * @brief This class describe curve in 2d with polynomial way
 *
 * @details Polynomial coefficient is represented by a dynamic vector. You can use it for different polynomial, 2nd or
 * 3rd polynomial. If the formulation is y = c0 + c1*x + c2*x^2 + c3*x^3, coeffs_[0] is c0, coeffs_[1] is c1, etc.
 *
 * @tparam T only support float32_t and float64_t
 */
template <typename T>
class PolynomialCurve2DT : public CurveDescriptorT<T>
{
public:
    using ScalarType  = T;
    using VectorXType = holo::numerics::VectorT<ScalarType, -1>;
    using Point2Type  = Point2T<ScalarType>;
    using Rot2Type    = Rot2T<ScalarType>;
    using Pose2Type   = Pose2T<ScalarType>;

    /**
     * @brief Default constructor
     */
    PolynomialCurve2DT() noexcept
      : CurveDescriptorT<T>()
      , degree_(0)
      , region_start_(-std::numeric_limits<ScalarType>::max())
      , region_end_(std::numeric_limits<ScalarType>::max())
    {
    }

    /**
     * @brief Constructor from degree, coefficients, region_start and region_end
     *
     * @param degree polynomial degree
     * @param coeffs polynomial coefficients
     * @param region_start independent variable region start
     * @param region_end independent variable region end
     *
     * @throws runtime_error when the degree is not mathed with coeffs
     */
    PolynomialCurve2DT(uint8_t degree, VectorXType const& coeffs, ScalarType region_start, ScalarType region_end)
      : degree_(degree), region_start_(region_start), region_end_(region_end)
    {
        if (coeffs.GetSize() > (degree + 1U))
        {
            std::string s = "coefficient size should less than degree + 1.";
            // LOG(ERROR) << s;
            throw std::runtime_error(s);
        }

        this->coeffs_ = coeffs;
    }

    /**
     * @brief Copy constructor
     *
     * @param other  other polynomial curve2D
     */
    PolynomialCurve2DT(PolynomialCurve2DT<T> const& other) noexcept
      : degree_(other.degree_)
      , region_start_(other.region_start_)
      , region_end_(other.region_end_)
      , coeffs_(other.coeffs_)
    {
    }

    /**
     * @brief Move constructor
     *
     * @param other other polynomial curve2D
     */
    PolynomialCurve2DT(PolynomialCurve2DT&& other) noexcept
      : degree_(other.degree_)
      , region_start_(other.region_start_)
      , region_end_(other.region_end_)
      , coeffs_(std::move(other.coeffs_))
    {
    }
    /**
     * @brief Destructor
     */
    ~PolynomialCurve2DT() noexcept
    {
    }

    /**
     * @brief Copy assignment
     *
     * @param other other polynomial curve2D
     */
    PolynomialCurve2DT& operator=(PolynomialCurve2DT const& other) noexcept
    {
        degree_       = other.degree_;
        coeffs_       = other.coeffs_;
        region_start_ = other.region_start_;
        region_end_   = other.region_end_;

        return *this;
    }

    /**
     * @brief Move assignment
     *
     * @param other other polynomial curve2D
     */
    PolynomialCurve2DT& operator=(PolynomialCurve2DT&& other) noexcept
    {
        degree_       = other.degree_;
        coeffs_       = std::move(other.coeffs_);
        region_start_ = other.region_start_;
        region_end_   = other.region_end_;

        return *this;
    }

    /**
     * @brief operator==
     *
     * @param other other polynomial curve2D
     */
    bool_t operator==(PolynomialCurve2DT const& other) const noexcept
    {
        if (this->degree_ != other.degree_)
        {
            return false;
        }

        // matrix not overload operator!=
        if (!(this->coeffs_ == other.coeffs_))
        {
            return false;
        }

        if (!ScalarEqualT<T>()(this->region_start_, other.region_start_))
        {
            return false;
        }

        if (!ScalarEqualT<T>()(this->region_end_, other.region_end_))
        {
            return false;
        }

        return true;
    }

    /**
     * @brief operator!=
     *
     * @param other other polynomial curve2D
     */
    bool_t operator!=(PolynomialCurve2DT const& other) const noexcept
    {
        if (this->degree_ != other.degree_)
        {
            return true;
        }

        // matrix not overload operator!=
        if (!(this->coeffs_ == other.coeffs_))
        {
            return true;
        }

        if (!ScalarEqualT<T>()(this->region_start_, other.region_start_))
        {
            return true;
        }

        if (!ScalarEqualT<T>()(this->region_end_, other.region_end_))
        {
            return true;
        }

        return false;
    }

    /**
     * @brief const operator[] to access coefficients
     *
     * @param i index
     *
     * @throws runtime_error when index is invalid
     */
    const ScalarType operator[](uint32_t i) const
    {
        if (i > degree_)
        {
            throw std::runtime_error("Invalid index for accessing!");
        }
        return coeffs_[i];
    }

    /**
     * @brief reference operator[] to access coefficients
     *
     * @param i index
     *
     * @throws runtime_error when index is invalid
     */
    ScalarType& operator[](uint32_t i)
    {
        if (i > degree_)
        {
            throw std::runtime_error("Invalid index for accessing!");
        }
        return coeffs_[i];
    }

    /**
     * @brief Get curve descriptor type
     *
     * @return CurveDescriptorType::POLYNOMIAL2D
     */
    virtual typename CurveDescriptorT<T>::CurveDescriptorType GetCurveType() const noexcept override
    {
        return CurveDescriptorT<T>::CurveDescriptorType::POLYNOMIAL2D;
    }

    /**
     * @brief Get polynomial degree
     *
     * @return degree
     */
    uint8_t GetDegree() const noexcept
    {
        return degree_;
    }

    /**
     * @brief Set polynomial degree
     *
     * @param degree polynomial degree
     */
    void SetDegree(uint8_t const degree) noexcept
    {
        this->degree_ = degree;
    }

    /**
     * @brief Get polynomial coefficients
     *
     * @return coefficient
     */
    VectorXType const& GetCoeffs() const noexcept
    {
        return coeffs_;
    }

    /**
     * @brief Set polynomial coefficients
     *
     * @param coeffs polynomial coefficients
     */
    void SetCoeffs(VectorXType const& coeffs) noexcept
    {
        this->coeffs_ = coeffs;
    }

    /**
     * @brief Get polynomial independent variable start region
     *
     * @return region start
     */
    ScalarType GetRegionStart() const noexcept
    {
        return region_start_;
    }

    /**
     * @brief Set polynomial independent variable start region
     *
     * @param region_start start region
     */
    void SetRegionStart(ScalarType const region_start) noexcept
    {
        this->region_start_ = region_start;
    }

    /**
     * @brief Get polynomial independent variable end region
     *
     * @return region end
     */
    ScalarType GetRegionEnd() const noexcept
    {
        return region_end_;
    }

    /**
     * @brief Set polynomial independent variable end region
     *
     * @param region_end end region
     */
    void SetRegionEnd(ScalarType const region_end) noexcept
    {
        this->region_end_ = region_end;
    }

    /**
     * @brief Serialize content to string
     *
     * @return serialized string
     */
    virtual std::string ToString() const noexcept override
    {
        std::stringstream ss;
        ss << "PolynomialCurve2DT: ("
           << "degree_: " << degree_ << ", coeffs_: " << coeffs_ << ", region_start_: " << region_start_
           << ", region_end_: " << region_end_ << ")" << std::endl;

        return ss.str();
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(degree_, region_start_, region_end_) +
               coeffs_.template GetSerializedSize<ALIGN>();
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
        serializer << holo::serialization::align << degree_ << region_start_ << region_end_ << coeffs_;
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
        deserializer >> holo::serialization::align >> degree_ >> region_start_ >> region_end_ >> coeffs_;
    }

private:
    uint8_t     degree_;        ///< the highest degree of its terms
    ScalarType  region_start_;  ///< independent varible of polynomial start region
    ScalarType  region_end_;    ///< independent varible of polynomial end region
    VectorXType coeffs_;        ///< coefficients in local frame
};                              // PolynomialCurve2DT

/**
 * @}
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // !HOLO_GEOMETRY_DETAILS_POLYNOMIAL_CURVE2D_H_
