/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file matrix.h
 * @brief holo matrix type
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-07-09
 */

#ifndef HOLO_NUMERICS_MATRIX_H_
#define HOLO_NUMERICS_MATRIX_H_

#include <cassert>

#include <holo/core/type_traits.h>
#include <holo/numerics/matrix_base.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace numerics
{
/**
 * @addtogroup numerics
 * @{
 */

/**
 * @brief define fixed-size matrix class
 *
 * @details derived from MatrixBaseT class
 */
template <typename Scalar, int32_t Row, int32_t Col>
class MatrixT : public MatrixBaseT<Scalar, Row, Col>
{
public:
    using Base = MatrixBaseT<Scalar, Row, Col>;

    using ScalarType  = typename Base::ScalarType;
    using ColSizeType = typename Base::ColSizeType;
    using RowSizeType = typename Base::RowSizeType;
    using SizeType    = typename Base::SizeType;

    static int32_t constexpr RowValue = Base::RowValue;
    static int32_t constexpr ColValue = Base::ColValue;

    /**
     * @brief Construct a new Matrix T object
     *
     * @details a zero matrix is constructed
     * @throw std::bad_alloc when initialization fails
     */
    MatrixT() : Base(Row, Col)
    {
    }

    /**
     * @brief Construct a new MatrixT object with element initializer list. Row will be filled first.
     *
     * @param il Element initializer list.
     * @throw std::bad_alloc when initialization fails
     */
    template <typename U, typename std::enable_if<std::is_convertible<U&&, Scalar>::value, void>::type* = nullptr>
    MatrixT(std::initializer_list<U> il) : Base(Row, Col, il)
    {
    }

    /**
     * @brief Construct a new MatrixT object with element values. Row will be filled first.
     *
     * @tparam Args Type of input arguments.
     * @param args Value of element values.
     */
    template <typename... Args, typename std::enable_if<(sizeof...(Args) <= (Row * Col)) &&
                                                            And<std::is_convertible<Args, Scalar>::value...>::value,
                                                        void>::type* = nullptr>
    MatrixT(Args... args) : Base(Row, Col)
    {
        Base::template assignValue<0, 0, Args...>(std::forward<Args>(args)...);
    }

    /**
     * @brief Construct a new Matrix T object
     *
     * @param base matrix base object
     * @throw std::bad_alloc when initialization fails
     */
    MatrixT(const Base& base) : Base(base)
    {
    }

    /**
     * @brief Construct a new Matrix T object
     *
     * @param other the other matrix
     * @throw std::bad_alloc when initialization fails
     */
    MatrixT(const MatrixT& other) = default;

    /**
     * @brief Copy assignment operator
     *
     * @param other the other matrix
     * @throw std::bad_alloc when initialization fails
     * @return reference of MatrixT
     */
    MatrixT& operator=(MatrixT const& other) = default;

    /**
     * @brief Construct a new Matrix T object from a dynamic object
     *
     * @param other dynamic matrix
     * @throw std::runtime_error when matrix size is inconsistent
     */
    MatrixT(const MatrixBaseT<Scalar, -1, -1>& other) : Base(Row, Col)
    {
        if ((Base::GetRows() != other.GetRows()) || (Base::GetCols() != other.GetCols()))
        {
            throw std::runtime_error("inconsistent matrix dimension");
        }

        for (RowSizeType i = 0u; i < Base::GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < Base::GetCols(); j++)
            {
                Base::operator()(i, j) = other(i, j);
            }
        }
    }

    /**
     * @brief Construct a new Matrix T object from a dynamic object
     *
     * @param other dynamic matrix
     * @throw std::runtime_error when matrix size is inconsistent
     * @return reference of MatrixT
     */
    MatrixT& operator=(const MatrixBaseT<Scalar, -1, -1>& other)
    {
        if ((Base::GetRows() != other.GetRows()) || (Base::GetCols() != other.GetCols()))
        {
            throw std::runtime_error("inconsistent matrix dimension");
        }

        for (RowSizeType i = 0u; i < Base::GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < Base::GetCols(); j++)
            {
                Base::operator()(i, j) = other(i, j);
            }
        }

        return *this;
    }

    /**
     * @brief Destroy the Matrix T object
     *
     */
    virtual ~MatrixT() noexcept = default;
protected:
    /**
     * @brief using Base members
     *
     */
    using Base::impl_ptr_;
    using typename Base::Implementation;

    /**
     * @brief Construct a new Matrix T object
     *
     * @param impl
     */
    MatrixT(const Implementation& impl) : Base(impl)
    {
    }

};  // MatrixT

/**
 * @brief define fixed-size square-matrix class
 *
 * @details partial template specialization of MatrixT class
 */
template <typename Scalar, int32_t Dim>
class MatrixT<Scalar, Dim, Dim> : public MatrixBaseT<Scalar, Dim, Dim>
{
public:
    using Base = MatrixBaseT<Scalar, Dim, Dim>;

    using ScalarType  = typename Base::ScalarType;
    using ColSizeType = typename Base::ColSizeType;
    using RowSizeType = typename Base::RowSizeType;
    using SizeType    = typename Base::SizeType;

    static int32_t constexpr RowValue = Base::RowValue;
    static int32_t constexpr ColValue = Base::ColValue;

    /**
     * @brief Construct a new Matrix T object
     *
     * @details a zero matrix is constructed
     * @throw std::bad_alloc when initialization fails
     *
     */
    MatrixT() : Base(Dim, Dim)
    {
    }

    /**
     * @brief Construct a new Matrix T object
     *
     * @param base matrix base object
     * @throw std::bad_alloc when initialization fails
     */
    MatrixT(const Base& base) : Base(base)
    {
    }

    /**
     * @brief Construct a new MatrixT object with element initializer list. Row will be filled first.
     *
     * @tparam U Type of initializer list. This function is only enabled if U is convertible to Scalar.
     * @param il Element initializer list.
     * @throw std::bad_alloc when initialization fails
     */
    template <typename U, typename std::enable_if<std::is_convertible<U&&, Scalar>::value, void>::type* = nullptr>
    MatrixT(std::initializer_list<U> il) : Base(Dim, Dim, il)
    {
    }

    /**
     * @brief Construct a new MatrixT object with element values. Row will be filled first.
     *
     * @tparam Args Type of input arguments.
     * @param args Value of element values.
     */
    template <typename... Args, typename std::enable_if<(sizeof...(Args) <= (Dim * Dim)) &&
                                                            And<std::is_convertible<Args, Scalar>::value...>::value,
                                                        void>::type* = nullptr>
    MatrixT(Args... args) : Base(Dim, Dim)
    {
        Base::template assignValue<0, 0, Args...>(std::forward<Args>(args)...);
    }

    /**
     * @brief Construct a new Matrix T object
     *
     * @param other the other matrix
     * @throw std::bad_alloc when initialization fails
     */
    MatrixT(const MatrixT& other) = default;

    /**
     * @brief Copy assignment operator
     *
     * @param other the other matrix
     * @throw std::bad_alloc when initialization fails
     * @return reference of MatrixT
     */
    MatrixT& operator=(MatrixT const& other) = default;

    /**
     * @brief Construct a new Matrix T object from a dynamic object
     *
     * @param other
     * @throw std::runtime_error when matrix size is inconsistent
     */
    MatrixT(const MatrixBaseT<Scalar, -1, -1>& other)
    {
        if ((Base::GetRows() != other.GetRows()) || (Base::GetCols() != other.GetCols()))
        {
            throw std::runtime_error("inconsistent matrix dimension");
        }

        impl_ptr_.reset(new Implementation());

        for (RowSizeType i = 0u; i < Base::GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < Base::GetCols(); j++)
            {
                Base::operator()(i, j) = other(i, j);
            }
        }
    }

    /**
     * @brief Construct a new Matrix T object from a dynamic object
     *
     * @param other dynamic matrix
     * @throw std::runtime_error when matrix size is inconsistent
     * @return reference of MatrixT
     */
    MatrixT& operator=(const MatrixBaseT<Scalar, -1, -1>& other)
    {
        if ((Base::GetRows() != other.GetRows()) || (Base::GetCols() != other.GetCols()))
        {
            throw std::runtime_error("inconsistent matrix dimension");
        }

        for (RowSizeType i = 0u; i < Base::GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < Base::GetCols(); j++)
            {
                Base::operator()(i, j) = other(i, j);
            }
        }

        return *this;
    }

    /**
     * @brief Destroy the Matrix T object
     *
     */
    virtual ~MatrixT() noexcept
    {
        static_assert(Dim > 0, "only fixe-size square-matrix is supported!!!");
    }

    /**
     * @brief take inverse of MatrixT
     *
     * @return MatrxiT
     */
    MatrixT Inverse() const
    {
        return MatrixT(Implementation(impl_ptr_->data.inverse()));
    }

    /**
     * @brief take determinant of MatrixT
     *
     */
    Scalar GetDeterminant() const
    {
        return impl_ptr_->data.determinant();
    }

    /**
     * @brief get diagonal element as a column vector
     *
     */
    MatrixT<Scalar, Dim, 1> GetDiagonal() const
    {
        MatrixT<Scalar, Dim, 1> out;
        for (size_t i = 0u; i < Dim; i++)
        {
            out(i, 0u) = this->operator()(i, i);
        }
        return out;
    }

    /**
     * @brief trace of a matrix
     *
     */
    Scalar GetTrace() const noexcept
    {
        return impl_ptr_->data.trace();
    }

protected:
    /**
     * @brief using Base members
     *
     */
    using Base::impl_ptr_;
    using typename Base::Implementation;

    /**
     * @brief Construct a new Matrix T object
     *
     * @param impl
     */
    MatrixT(const Implementation& impl) : Base(impl)
    {
    }

};  // MatrixT

/**
 * @brief define dynamic-matrix class
 *
 * @details partial template specialization of MatrixT class
 */
template <typename Scalar>
class MatrixT<Scalar, -1, -1> : public MatrixBaseT<Scalar, -1, -1>
{
public:
    using Base = MatrixBaseT<Scalar, -1, -1>;

    using ScalarType  = typename Base::ScalarType;
    using ColSizeType = typename Base::ColSizeType;
    using RowSizeType = typename Base::RowSizeType;
    using SizeType    = typename Base::SizeType;

    static int32_t constexpr RowValue = Base::RowValue;
    static int32_t constexpr ColValue = Base::ColValue;

    static RowSizeType constexpr MaxRows = std::numeric_limits<RowSizeType>::max();
    static ColSizeType constexpr MaxCols = std::numeric_limits<ColSizeType>::max();
    static SizeType constexpr MaxSize    = MaxRows * MaxCols;
    /**
     * @brief default constructor
     *
     * @throw std::bad_alloc when initialization fails
     */
    MatrixT() : Base()
    {
    }

    /**
     * @brief Construct a new Matrix object
     *
     * @details a "zero" matrix is created
     * @param[in] row row dimension of matrix
     * @param[in] col column dimension of matrix
     * @throw std::out_of_range when initialization fails
     */
    MatrixT(const int32_t row, const int32_t col) : Base(row, col)
    {
        if (!MatrixT::IsSizeValid(row, col))
        {
            std::stringstream ss;
            ss << "Invalid size to create a matrix: expected (rows, cols) = (" << static_cast<int32_t>(MatrixT::MaxRows)
               << ", " << static_cast<int32_t>(MatrixT::MaxCols) << "), actual (rows, cols) = (" << row << ", " << col
               << ")" << std::endl;
            throw std::out_of_range(ss.str());
        }
    }

    /**
     * @brief Construct a new Matrix T object
     *
     * @param base matrix base object
     * @throw std::bad_alloc when initialization fails
     */
    MatrixT(const Base& base) : Base(base)
    {
    }

    /**
     * @brief Construct a new Matrix T object
     *
     * @param other the other matrix
     * @throw std::bad_alloc when initialization fails
     */
    MatrixT(const MatrixT& other) = default;

    /**
     * @brief Copy assignment operator
     *
     * @param other the other matrix
     * @throw std::out_of_range when the new size if out of range
     * @return reference of MatrixT
     */
    MatrixT& operator=(MatrixT const& other) = default;

    /**
     * @brief Destroy the Matrix T object
     *
     */
    virtual ~MatrixT() noexcept = default;

    /**
     * @brief take inverse of MatrixT, only works with square matrix
     *
     * @return MatrxiT
     * @throw std::runtime_error when matrix is not square
     */
    MatrixT Inverse() const
    {
        if (this->GetRows() != this->GetCols())
        {
            throw std::runtime_error("matrix is not square!!!");
        }
        return MatrixT(Implementation(impl_ptr_->data.inverse()));
    }

    /**
     * @brief take determinant of MatrixT, only works with square matrix
     *
     * @throw std::runtime_error when matrix is not square
     */
    Scalar GetDeterminant() const
    {
        if (this->GetRows() != this->GetCols())
        {
            throw std::runtime_error("matrix is not square!!!");
        }
        return impl_ptr_->data.determinant();
    }

    /**
     * @brief get diagonal element as a column vector
     *
     */
    MatrixBaseT<Scalar, -1, 1> GetDiagonal() const
    {
        if (this->GetRows() != this->GetCols())
        {
            throw std::runtime_error("diagonal only supports square matrix");
        }
        MatrixBaseT<Scalar, -1, 1> out(this->GetRows(), 1u);
        for (size_t i = 0u; i < this->GetRows(); i++)
        {
            out(i, 0u) = this->operator()(i, i);
        }
        return out;
    }

    /**
     * @brief trace of a matrix, only works with square matrix
     *
     */
    Scalar GetTrace() const noexcept
    {
        return impl_ptr_->data.trace();
    }

    /**
     * @brief resize a matrix
     *
     * @param row new row
     * @param col rew col
     * @throw std::out_of_range when the new size if out of range
     */
    void Resize(const int32_t row, const int32_t col)
    {
        if (!MatrixT::IsSizeValid(row, col))
        {
            std::stringstream ss;
            ss << "Invalid size to create a matrix: expected (rows, cols) = (" << static_cast<int32_t>(MatrixT::MaxRows)
               << ", " << static_cast<int32_t>(MatrixT::MaxCols) << "), actual (rows, cols) = (" << row << ", " << col
               << ")" << std::endl;
            throw std::out_of_range(ss.str());
        }
        impl_ptr_->data.resize(row, col);
    }

    /**
     * @brief Get serialized size with given alignment value
     *
     * @tparam ALIGN Buffer alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(this->GetRows(), this->GetCols()) +
               Base::template GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize to serializer.
     *
     * @tparam S Serializer type.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << static_cast<uint32_t>(this->GetRows())
                   << static_cast<uint32_t>(this->GetCols());
        Base::Serialize(serializer);
    }

    /**
     * @brief Deserialize from deserializer.
     *
     * @tparam D Deserializer type
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
        uint32_t row;
        uint32_t col;

        deserializer >> holo::serialization::align >> row >> col;

        this->Resize(row, col);

        Base::Deserialize(deserializer);
    }

    /**
     * @brief zero matrix
     *
     * @param rows matrix rows
     * @param cols matrix cols
     * @return MatrixT
     * @throw std::bad_alloc when initialization fails
     */
    static MatrixT Zero(const int32_t rows, const int32_t cols)
    {
        MatrixT mat(rows, cols);
        mat.SetZero();
        return mat;
    }

    /**
     * @brief one matrix
     *
     * @param rows matrix rows
     * @param cols matrix cols
     * @return MatrixT
     * @throw std::bad_alloc when initialization fails
     */
    static MatrixT One(const int32_t rows, const int32_t cols)
    {
        MatrixT mat(rows, cols);
        mat.SetOne();
        return mat;
    }

    /**
     * @brief constant-value matrix
     *
     * @param rows matrix rows
     * @param cols matrix cols
     * @param value matrix element
     * @return MatrixT
     * @throw std::bad_alloc when initialization fails
     */
    static MatrixT Constant(const int32_t rows, const int32_t cols, const Scalar value)
    {
        MatrixT mat(rows, cols);
        mat.SetConstant(value);
        return mat;
    }

    /**
     * @brief identity matrix
     *
     * @param dim matrix dimension
     * @return MatrixT
     * @throw std::bad_alloc when initialization fails
     */
    static MatrixT Identity(const int32_t dim)
    {
        MatrixT mat(dim, dim);
        mat.SetIdentity();
        return mat;
    }

    /**
     * @brief check if the matrix size is valid
     *
     * @param rows rows of target matrix
     * @param cols cols of target matrix
     * @return bool_t
     */
    static bool_t IsSizeValid(int32_t rows, int32_t cols)
    {
        return (rows >= 0) && (rows <= static_cast<int32_t>(MaxRows)) && (cols >= 0) &&
               (cols <= static_cast<int32_t>(MaxCols));
    }

protected:
    /**
     * @brief using Base members
     *
     */
    using Base::impl_ptr_;
    using typename Base::Implementation;

    /**
     * @brief Construct a new Matrix T object
     *
     * @param impl
     */
    MatrixT(const Implementation& impl) : Base(impl)
    {
    }
};  // MatrixT

template <typename Scalar>
using Matrix1T = MatrixT<Scalar, 1, 1>;
using Matrix1f = Matrix1T<float32_t>;
using Matrix1d = Matrix1T<float64_t>;
using Matrix1  = Matrix1T<float64_t>;
template <typename Scalar>
using RowVector1T = MatrixT<Scalar, 1, 1>;
using RowVector1f = RowVector1T<float32_t>;
using RowVector1d = RowVector1T<float64_t>;
using RowVector1  = RowVector1T<float64_t>;

template <typename Scalar>
using Matrix2T = MatrixT<Scalar, 2, 2>;
using Matrix2f = Matrix2T<float32_t>;
using Matrix2d = Matrix2T<float64_t>;
using Matrix2  = Matrix2T<float64_t>;
template <typename Scalar>
using RowVector2T = MatrixT<Scalar, 1, 2>;
using RowVector2f = RowVector2T<float32_t>;
using RowVector2d = RowVector2T<float64_t>;
using RowVector2  = RowVector2T<float64_t>;

template <typename Scalar>
using Matrix3T = MatrixT<Scalar, 3, 3>;
using Matrix3f = Matrix3T<float32_t>;
using Matrix3d = Matrix3T<float64_t>;
using Matrix3  = Matrix3T<float64_t>;
template <typename Scalar>
using RowVector3T = MatrixT<Scalar, 1, 3>;
using RowVector3f = RowVector3T<float32_t>;
using RowVector3d = RowVector3T<float64_t>;
using RowVector3  = RowVector3T<float64_t>;

template <typename Scalar>
using Matrix4T = MatrixT<Scalar, 4, 4>;
using Matrix4f = Matrix4T<float32_t>;
using Matrix4d = Matrix4T<float64_t>;
using Matrix4  = Matrix4T<float64_t>;
template <typename Scalar>
using RowVector4T = MatrixT<Scalar, 1, 4>;
using RowVector4f = RowVector4T<float32_t>;
using RowVector4d = RowVector4T<float64_t>;
using RowVector4  = RowVector4T<float64_t>;

template <typename Scalar>
using Matrix5T = MatrixT<Scalar, 5, 5>;
using Matrix5f = Matrix5T<float32_t>;
using Matrix5d = Matrix5T<float64_t>;
using Matrix5  = Matrix5T<float64_t>;
template <typename Scalar>
using RowVector5T = MatrixT<Scalar, 1, 5>;
using RowVector5f = RowVector5T<float32_t>;
using RowVector5d = RowVector5T<float64_t>;
using RowVector5  = RowVector5T<float64_t>;

template <typename Scalar>
using Matrix6T = MatrixT<Scalar, 6, 6>;
using Matrix6f = Matrix6T<float32_t>;
using Matrix6d = Matrix6T<float64_t>;
using Matrix6  = Matrix6T<float64_t>;
template <typename Scalar>
using RowVector6T = MatrixT<Scalar, 1, 6>;
using RowVector6f = RowVector6T<float32_t>;
using RowVector6d = RowVector6T<float64_t>;
using RowVector6  = RowVector6T<float64_t>;

template <typename Scalar>
using Matrix7T = MatrixT<Scalar, 7, 7>;
using Matrix7f = Matrix7T<float32_t>;
using Matrix7d = Matrix7T<float64_t>;
using Matrix7  = Matrix7T<float64_t>;
template <typename Scalar>
using RowVector7T = MatrixT<Scalar, 1, 7>;
using RowVector7f = RowVector7T<float32_t>;
using RowVector7d = RowVector7T<float64_t>;
using RowVector7  = RowVector7T<float64_t>;

template <typename Scalar>
using Matrix8T = MatrixT<Scalar, 8, 8>;
using Matrix8f = Matrix8T<float32_t>;
using Matrix8d = Matrix8T<float64_t>;
using Matrix8  = Matrix8T<float64_t>;
template <typename Scalar>
using RowVector8T = MatrixT<Scalar, 1, 8>;
using RowVector8f = RowVector8T<float32_t>;
using RowVector8d = RowVector8T<float64_t>;
using RowVector8  = RowVector8T<float64_t>;

template <typename Scalar>
using Matrix9T = MatrixT<Scalar, 9, 9>;
using Matrix9f = Matrix9T<float32_t>;
using Matrix9d = Matrix9T<float64_t>;
using Matrix9  = Matrix9T<float64_t>;
template <typename Scalar>
using RowVector9T = MatrixT<Scalar, 1, 9>;
using RowVector9f = RowVector9T<float32_t>;
using RowVector9d = RowVector9T<float64_t>;
using RowVector9  = RowVector9T<float64_t>;

/**
 * @brief handy typedefs, dynamic-size matrix
 */
template <typename Scalar>
using MatrixXT = MatrixT<Scalar, -1, -1>;
using MatrixXf = MatrixXT<float32_t>;
using MatrixXd = MatrixXT<float64_t>;
using MatrixX  = MatrixXd;

/**
 * @}
 *
 */
}  // namespace numerics

template <typename Scalar, int32_t Row, int32_t Col>
using MatrixT [[deprecated]] = numerics::MatrixT<Scalar, Row, Col>;

template <typename Scalar>
using Matrix1T [[deprecated]] = numerics::MatrixT<Scalar, 1, 1>;
using Matrix1f [[deprecated]] = numerics::Matrix1T<float32_t>;
using Matrix1d [[deprecated]] = numerics::Matrix1T<float64_t>;
using Matrix1 [[deprecated]]  = numerics::Matrix1T<float64_t>;
template <typename Scalar>
using RowVector1T [[deprecated]] = numerics::MatrixT<Scalar, 1, 1>;
using RowVector1f [[deprecated]] = numerics::RowVector1T<float32_t>;
using RowVector1d [[deprecated]] = numerics::RowVector1T<float64_t>;
using RowVector1 [[deprecated]]  = numerics::RowVector1T<float64_t>;

template <typename Scalar>
using Matrix2T [[deprecated]] = numerics::MatrixT<Scalar, 2, 2>;
using Matrix2f [[deprecated]] = numerics::Matrix2T<float32_t>;
using Matrix2d [[deprecated]] = numerics::Matrix2T<float64_t>;
using Matrix2 [[deprecated]]  = numerics::Matrix2T<float64_t>;
template <typename Scalar>
using RowVector2T [[deprecated]] = numerics::MatrixT<Scalar, 1, 2>;
using RowVector2f [[deprecated]] = numerics::RowVector2T<float32_t>;
using RowVector2d [[deprecated]] = numerics::RowVector2T<float64_t>;
using RowVector2 [[deprecated]]  = numerics::RowVector2T<float64_t>;

template <typename Scalar>
using Matrix3T [[deprecated]] = numerics::MatrixT<Scalar, 3, 3>;
using Matrix3f [[deprecated]] = numerics::Matrix3T<float32_t>;
using Matrix3d [[deprecated]] = numerics::Matrix3T<float64_t>;
using Matrix3 [[deprecated]]  = numerics::Matrix3T<float64_t>;
template <typename Scalar>
using RowVector3T [[deprecated]] = numerics::MatrixT<Scalar, 1, 3>;
using RowVector3f [[deprecated]] = numerics::RowVector3T<float32_t>;
using RowVector3d [[deprecated]] = numerics::RowVector3T<float64_t>;
using RowVector3 [[deprecated]]  = numerics::RowVector3T<float64_t>;

template <typename Scalar>
using Matrix4T [[deprecated]] = numerics::MatrixT<Scalar, 4, 4>;
using Matrix4f [[deprecated]] = numerics::Matrix4T<float32_t>;
using Matrix4d [[deprecated]] = numerics::Matrix4T<float64_t>;
using Matrix4 [[deprecated]]  = numerics::Matrix4T<float64_t>;
template <typename Scalar>
using RowVector4T [[deprecated]] = numerics::MatrixT<Scalar, 1, 4>;
using RowVector4f [[deprecated]] = numerics::RowVector4T<float32_t>;
using RowVector4d [[deprecated]] = numerics::RowVector4T<float64_t>;
using RowVector4 [[deprecated]]  = numerics::RowVector4T<float64_t>;

template <typename Scalar>
using Matrix5T [[deprecated]] = numerics::MatrixT<Scalar, 5, 5>;
using Matrix5f [[deprecated]] = numerics::Matrix5T<float32_t>;
using Matrix5d [[deprecated]] = numerics::Matrix5T<float64_t>;
using Matrix5 [[deprecated]]  = numerics::Matrix5T<float64_t>;
template <typename Scalar>
using RowVector5T [[deprecated]] = numerics::MatrixT<Scalar, 1, 5>;
using RowVector5f [[deprecated]] = numerics::RowVector5T<float32_t>;
using RowVector5d [[deprecated]] = numerics::RowVector5T<float64_t>;
using RowVector5 [[deprecated]]  = numerics::RowVector5T<float64_t>;

template <typename Scalar>
using Matrix6T [[deprecated]] = numerics::MatrixT<Scalar, 6, 6>;
using Matrix6f [[deprecated]] = numerics::Matrix6T<float32_t>;
using Matrix6d [[deprecated]] = numerics::Matrix6T<float64_t>;
using Matrix6 [[deprecated]]  = numerics::Matrix6T<float64_t>;
template <typename Scalar>
using RowVector6T [[deprecated]] = numerics::MatrixT<Scalar, 1, 6>;
using RowVector6f [[deprecated]] = numerics::RowVector6T<float32_t>;
using RowVector6d [[deprecated]] = numerics::RowVector6T<float64_t>;
using RowVector6 [[deprecated]]  = numerics::RowVector6T<float64_t>;

template <typename Scalar>
using Matrix7T [[deprecated]] = numerics::MatrixT<Scalar, 7, 7>;
using Matrix7f [[deprecated]] = numerics::Matrix7T<float32_t>;
using Matrix7d [[deprecated]] = numerics::Matrix7T<float64_t>;
using Matrix7 [[deprecated]]  = numerics::Matrix7T<float64_t>;
template <typename Scalar>
using RowVector7T [[deprecated]] = numerics::MatrixT<Scalar, 1, 7>;
using RowVector7f [[deprecated]] = numerics::RowVector7T<float32_t>;
using RowVector7d [[deprecated]] = numerics::RowVector7T<float64_t>;
using RowVector7 [[deprecated]]  = numerics::RowVector7T<float64_t>;

template <typename Scalar>
using Matrix8T [[deprecated]] = numerics::MatrixT<Scalar, 8, 8>;
using Matrix8f [[deprecated]] = numerics::Matrix8T<float32_t>;
using Matrix8d [[deprecated]] = numerics::Matrix8T<float64_t>;
using Matrix8 [[deprecated]]  = numerics::Matrix8T<float64_t>;
template <typename Scalar>
using RowVector8T [[deprecated]] = numerics::MatrixT<Scalar, 1, 8>;
using RowVector8f [[deprecated]] = numerics::RowVector8T<float32_t>;
using RowVector8d [[deprecated]] = numerics::RowVector8T<float64_t>;
using RowVector8 [[deprecated]]  = numerics::RowVector8T<float64_t>;

template <typename Scalar>
using Matrix9T [[deprecated]] = numerics::MatrixT<Scalar, 9, 9>;
using Matrix9f [[deprecated]] = numerics::Matrix9T<float32_t>;
using Matrix9d [[deprecated]] = numerics::Matrix9T<float64_t>;
using Matrix9 [[deprecated]]  = numerics::Matrix9T<float64_t>;
template <typename Scalar>
using RowVector9T [[deprecated]] = numerics::MatrixT<Scalar, 1, 9>;
using RowVector9f [[deprecated]] = numerics::RowVector9T<float32_t>;
using RowVector9d [[deprecated]] = numerics::RowVector9T<float64_t>;
using RowVector9 [[deprecated]]  = numerics::RowVector9T<float64_t>;

template <typename Scalar>
using MatrixXT [[deprecated]] = numerics::MatrixT<Scalar, -1, -1>;
using MatrixXf [[deprecated]] = numerics::MatrixXT<float32_t>;
using MatrixXd [[deprecated]] = numerics::MatrixXT<float64_t>;
using MatrixX [[deprecated]]  = numerics::MatrixXd;

}  // namespace holo

#endif  // HOLO_NUMERICS_MATRIX_H_
