/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file polyfit2.h
 * @brief this class defines a polynomial curve fitting in 2D space
 * @author jiaxing.zhao, duyanwei
 * @date Sep-28-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_POLYFIT2_H_
#define HOLO_GEOMETRY_DETAILS_POLYFIT2_H_

#include <limits>
#include <vector>

#include <holo/core/epsilon.h>
#include <holo/core/types.h>
#include <holo/geometry/pose2.h>
#include <holo/numerics/eigen_solver.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/utility.h>
#include <holo/numerics/vector.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace geometry
{
namespace details
{
/**
 * @addtogroup geometry
 * @{
 */

/**
 * @brief this is a class of polynomial curve fitting in 2D space.
 *
 * @details /f$y = a(n) * x^n + ... + a(2) * x^2 + a(1) * x + a(0)/f$, you can specify any degree.
 *
 * @note
 *       a. Generally, to make the fitting achieve the best performance, the data needs to have more variance in its x
 *          direction than y direction. If doesn't, the results can be unstable and untrusted. !!!
 *       b. Dist() only supports curve of degree less than 3
 */
template <typename T>
class Polyfit2T
{
public:
    using ScalarType  = T;
    using MatrixXType = holo::numerics::MatrixXT<ScalarType>;
    using VectorXType = holo::numerics::VectorXT<ScalarType>;
    using Point2Type  = Point2T<ScalarType>;
    using Rot2Type    = Rot2T<ScalarType>;
    using Pose2Type   = Pose2T<ScalarType>;
    using EpsilonType [[deprecated]] = EpsilonT<ScalarType>;

    /**
     * @brief constructor with specified degree
     *
     * @param degree degree of curve
     */
    Polyfit2T(uint8_t const degree = 1u) noexcept
      : degree_(degree), residual_(static_cast<T>(0.0)), max_x_(static_cast<T>(0.0)), min_x_(static_cast<T>(0.0))
    {
    }

    /**
     * @brief Construct a new Polyfit 2 T object
     *
     * @param coeffs coefficients
     * @throw std::runtime_error if coeffs is empty
     */
    Polyfit2T(VectorXType const& coeffs)
      : residual_(static_cast<T>(0.0))
      , max_x_(std::numeric_limits<T>::max())
      , min_x_(std::numeric_limits<T>::lowest())
      , coeffs_(coeffs)
    {
        if (coeffs_.GetSize() < 1u)
        {
            throw std::runtime_error("Invalid coefficients");
        }

        degree_ = coeffs_.GetSize() - 1u;
    }

    /**
     * @brief destructor
     */
    ~Polyfit2T() noexcept
    {
    }

    /**
     * @brief output operator
     *
     * @param os std::ostream
     * @param pf polyfit2
     * @return std::ostream
     */
    friend std::ostream& operator<<(std::ostream& os, Polyfit2T const& pf) noexcept
    {
        os << pf.ToString();
        return os;
    }

    /**
     * @brief convert data to string
     *
     * @return std::string
     */
    std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "Polyfit2T: \n degree: (" << degree_ << "), residual: (" << residual_ << "), max_x: (" << max_x_
           << "), min_x: (" << min_x_ << "), coeffs: (";

        for (uint32_t i = 0u; i < coeffs_.GetSize(); ++i)
        {
            ss << coeffs_(i) << ", ";
        }
        ss << ")" << std::endl;

        return ss.str();
    }

    /**
     * @brief given a series of point2s to fit polynomial curve in 2D space.
     *
     * @param points fitted points
     * @return true or false
     */
    bool_t Fit(std::vector<Point2Type> const& points) noexcept
    {
        if (points.empty() || points.size() < (degree_ + 1u))
        {
            // "Data set is invalid !"
            return false;
        }

        /* Boundary constraint of interpolation */
        max_x_ = ::std::numeric_limits<ScalarType>::lowest();
        min_x_ = ::std::numeric_limits<ScalarType>::max();
        for (Point2Type const& point : points)
        {
            ScalarType const x = point.GetX();
            if (x > max_x_)
            {
                max_x_ = x;
            }
            if (x < min_x_)
            {
                min_x_ = x;
            }
        }

        /* number of coefficients including a(0), so if degree = n,number of coefficients is n + 1. */
        uint64_t const num_coeffs  = degree_ + 1u;
        uint64_t const num_samples = points.size();
        if (!MatrixXType::IsSizeValid(num_samples, num_coeffs))
        {
            std::cout << "Invalid size to create a matrix: Max allowed (rows, cols) = ("
                      << static_cast<uint64_t>(MatrixXType::MaxRows) << ", "
                      << static_cast<uint64_t>(MatrixXType::MaxCols) << "), actual (rows, cols) = (" << num_samples
                      << ", " << num_coeffs << ")" << std::endl;
            return false;
        }
        MatrixXType mat_x(num_samples, num_coeffs);
        VectorXType vec_y(num_samples);

        /* create y vector */
        for (uint64_t i = 0u; i < num_samples; i++)
        {
            vec_y(i) = points[i].GetY();
        }

        /* create x matrix */
        for (uint64_t n_row = 0u; n_row < num_samples; ++n_row)
        {
            mat_x(n_row, 0u)   = static_cast<T>(1.0);
            ScalarType const x = points[n_row].GetX();
            for (uint64_t n_col = 1u; n_col < num_coeffs; ++n_col)
            {
                mat_x(n_row, n_col) = mat_x(n_row, n_col - 1u) * x;
            }
        }

        /**
         * solve coefficients:
         * QR decompose x * a = y, x = qr, ra = qT * y, coeff order: coefficients a(0) a(1) ... a(n-1) a(n)
         */
        coeffs_ = eigen_solver::SolveLinearSystem<T>(mat_x, vec_y, eigen_solver::Type::COL_PIV_HOUSEHOLDER_QR);

        /* compute residual */
        vec_y -= mat_x * coeffs_;
        residual_ = vec_y.CwiseAbs().Sum() / static_cast<T>(num_samples);

        return coeffs_.GetSize() != 0u;
    }

    /**
     * @brief interpolation
     *
     * @param x x value interpolated point
     * @param point interpolated point
     * @return true or false
     */
    bool_t Interpolate(ScalarType const x, Point2Type& point) const noexcept
    {
        if (coeffs_.GetSize() == 0u)
        {
            // "Invalid fitting!"
            return false;
        }

        if ((x < min_x_) || (x > max_x_))
        {
            // out of boundary
            return false;
        }

        /* create x matrix */
        MatrixXType mat_x(1u, degree_ + 1u);
        ScalarType  value = static_cast<ScalarType>(1.0);
        for (uint8_t n_col = 0u; n_col < (degree_ + 1u); n_col++)
        {
            mat_x(0u, n_col) = value;
            value *= x;
        }

        /* interpolate point */
        point.Set(x, (mat_x * coeffs_)(0u));
        return true;
    }

    /*
     * @brief this function compute point to polynomial least distance in 2d
     *
     * @details
     *        1.construct squared distance equation f = d^2 = (x - x0)^2 +
     *          (y - y0)^2
     *        2.derivative f in order to find extremal point
     *        3.compute polynomial root
     *        4.remove imaginary root
     *        5.compute distance extremal value to find minimum value
     * @ref http://mathworld.wolfram.com/PolynomialRoots.html
     * @note The method only supports curve with degree less than 3
     *       apply to degree less than 3
     *
     * @param point input point
     * @param distance computed distance
     * @param check_boundary if check boundary of fitted line
     * @return true or false
     */
    bool_t ComputePointDistanceToCurve(Point2Type const& point, ScalarType& distance,
                                       bool_t const check_boundary = true) const noexcept
    {
        if (degree_ >= 4u)
        {
            // "This compute point to polynomial distance function require degree less than 3"
            return false;
        }

        // declare a new variable of size 4 (required by the algorithm) to avoid out_of_range issue
        VectorXType new_coeffs(4u);
        for (uint16_t i = 0u; i < coeffs_.GetSize(); ++i)
        {
            new_coeffs(i) = coeffs_(i);
        }

        ScalarType const x = point.GetX();
        ScalarType const y = point.GetY();

        ScalarType const one(static_cast<ScalarType>(1.0));
        ScalarType const two(static_cast<ScalarType>(2.0));
        ScalarType const three(static_cast<ScalarType>(3.0));
        ScalarType const four(static_cast<ScalarType>(4.0));
        ScalarType const five(static_cast<ScalarType>(5.0));

        VectorXType root_coeffs(6u);
        root_coeffs(0u) = one * new_coeffs(0u) * new_coeffs(1u) - one * new_coeffs(1u) * y - one * x;
        root_coeffs(1u) = one * new_coeffs(1u) * new_coeffs(1u) + two * new_coeffs(0u) * new_coeffs(2u) -
                          two * new_coeffs(2u) * y + one;
        root_coeffs(2u) = three * new_coeffs(0u) * new_coeffs(3u) + three * new_coeffs(1u) * new_coeffs(2u) -
                          three * new_coeffs(3u) * y;
        root_coeffs(3u) = four * new_coeffs(1u) * new_coeffs(3u) + two * new_coeffs(2u) * new_coeffs(2u);
        root_coeffs(4u) = five * new_coeffs(2u) * new_coeffs(3u);
        root_coeffs(5u) = three * new_coeffs(3u) * new_coeffs(3u);

        /* compute roots */
        std::set<std::pair<ScalarType, ScalarType> > roots;
        numerics::ComputePolynomialRoots(root_coeffs, roots);

        /* if the computed x is out of range, compute the distance to the boundary points and select the smaller one. */
        typename std::set<std::pair<ScalarType, ScalarType> >::iterator it;
        distance = std::numeric_limits<ScalarType>::max();
        ScalarType min_distance_x(static_cast<ScalarType>(0.0));
        for (it = roots.begin(); it != roots.end(); it++)
        {
            ScalarType const val_x    = it->first;
            ScalarType const val_xx   = val_x * val_x;
            ScalarType const val_xxx  = val_xx * val_x;
            ScalarType const val_dist = static_cast<ScalarType>((std::sqrt(std::pow((val_x - x), 2) +
                                                   std::pow(new_coeffs(0u) + new_coeffs(1u) * val_x +
                                                                new_coeffs(2u) * val_xx + new_coeffs(3u) * val_xxx - y,
                                                            2))));

            if (distance > val_dist)
            {
                distance       = val_dist;
                min_distance_x = val_x;
            }
        }

        if (check_boundary)
        {
            if (min_distance_x < min_x_ || min_distance_x > max_x_)
            {
                Point2Type max_point;
                Point2Type min_point;
                Interpolate(max_x_, max_point);
                Interpolate(min_x_, min_point);
                ScalarType const distance_to_min_point = point.Dist(min_point);
                ScalarType const distance_to_max_point = point.Dist(max_point);
                distance                               = std::min(distance_to_min_point, distance_to_max_point);
            }
        }

        return true;
    }

    /**
     * @brief compute points to polynomial curves
     *
     * @param points input points
     * @param distances computed distance
     * @param check_boundary if check boundary
     * @return bool_t
     */
    bool_t ComputePointDistanceToCurve(std::vector<Point2Type> const& points, std::vector<ScalarType>& distances,
                                       bool_t const check_boundary = true) const noexcept
    {
        if (points.empty())
        {
            // "Data set is empty!"
            return false;
        }

        distances.resize(points.size());
        for (uint64_t i = 0u; i < points.size(); i++)
        {
            const bool_t status = ComputePointDistanceToCurve(points[i], distances[i], check_boundary);
            if (!status)
            {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief get degree
     *
     * @return degree
     */
    inline ScalarType GetDegree() const noexcept
    {
        return degree_;
    }

    /**
     * @brief get residual
     *
     * @return residual
     */
    inline ScalarType GetResidual() const noexcept
    {
        return residual_;
    }

    /**
     * @brief return coeffients in local frame
     *
     */
    inline VectorXType const& GetCoeffs() const noexcept
    {
        return coeffs_;
    }

    /**
     * @brief get max x
     *
     */
    inline ScalarType GetMaxX() const noexcept
    {
        return max_x_;
    }

    /**
     * @brief get min x
     *
     */
    inline ScalarType GetMinX() const noexcept
    {
        return min_x_;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(degree_, residual_, max_x_, min_x_) +
               coeffs_.template GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << degree_ << residual_ << max_x_ << min_x_ << coeffs_;
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
        deserializer >> holo::serialization::align >> degree_ >> residual_ >> max_x_ >> min_x_ >> coeffs_;
    }

private:
    uint8_t     degree_;    ///< the highest degree of its terms
    ScalarType  residual_;  ///< fitted residual
    ScalarType  max_x_;     ///< lower bound of x in local frame
    ScalarType  min_x_;     ///< upper bound of x in local frame
    VectorXType coeffs_;    ///< coefficients in local frame

};  // Polyfit2T

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_POLYFIT2_H_
