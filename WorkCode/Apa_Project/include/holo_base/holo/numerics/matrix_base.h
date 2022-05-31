/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file matrix_base.h
 * @brief holo matrix base type
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-16
 */

#ifndef HOLO_NUMERICS_MATRIX_BASE_H_
#define HOLO_NUMERICS_MATRIX_BASE_H_

#include <functional>
#include <memory>
#include <ostream>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cassert>
#include <cmath>

#include <holo/core/epsilon.h>
#include <holo/core/types.h>
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
 * @brief define matrix base class
 *
 * @details it works as base class to provide common APIs for matrix
 * @tparam Scalar only supports float32_t or float64_t
 * @tparam Row real row dimension of matrix, 0 is invalid, -1 means dynamic
 * @tparam Col real col dimension of matrix, 0 is invalid, -1 means dynamic
 */
template <typename Scalar, int32_t Row, int32_t Col>
class MatrixBaseT
{
public:
    /**
     * @brief typedef
     */
    using ScalarType                = Scalar;
    using ColSizeType               = uint8_t;
    using RowSizeType               = uint8_t;
    using SizeType                  = uint16_t;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    static int32_t constexpr RowValue = Row;
    static int32_t constexpr ColValue = Col;

    /**
     * @brief Construct a new Matrix Base T object
     *
     * @details a random-value matrix is created
     * @throw std::bad_alloc when initialization fails
     */
    MatrixBaseT() : impl_ptr_(new Implementation())
    {
    }

    /**
     * @brief Construct a new Matrix Base T object
     *
     * @details a "zero" matrix is created
     * @param row row dimension of matrix
     * @param col column dimension of matrix
     * @throw std::bad_alloc when initialization fails
     */
    MatrixBaseT(const RowSizeType row, const ColSizeType col) : impl_ptr_(new Implementation(row, col))
    {
    }

    /**
     * @brief Construct a new MatrixBaseT object with row, column and element initializer list.
     * @detail Construct a matrix and fill matrix with element initializer list.
     * If size of initilizer list is larger than matrix size, the rest element in initializer list will be ignored.
     * If size of initializer list is smaller than matrix size, the rest element in matrix will be filled with zero.
     * Row will be filled first.
     *
     * @tparam U Type of initializer list. This function is only enabled if U is convertible to ScalarType.
     * @param row Row dimension
     * @param col Column dimension
     * @param il Element initializer list.
     */
    template <typename U, typename std::enable_if<std::is_convertible<U&&, ScalarType>::value, void>::type* = nullptr>
    MatrixBaseT(const RowSizeType row, const ColSizeType col, std::initializer_list<U> il) : MatrixBaseT(row, col)
    {
        auto it = il.begin();
        for (size_t i = 0; i < RowValue; ++i)
        {
            for (size_t j = 0; j < ColValue; ++j)
            {
                this->operator()(i, j) = *it++;
                if (it == il.end())
                {
                    break;
                }
            }
            if (it == il.end())
            {
                break;
            }
        }
    }

    /**
     * @brief Construct a new Matrix Base T object from raw data array (column-majored)
     *
     * @param row row dimension of matrix
     * @param col column dimension of matrix
     * @param array raw data array
     * @param array_size data array size
     * @throw std::bad_alloc when initialization fails
     */
    MatrixBaseT(const RowSizeType row, const ColSizeType col, const ScalarType* array, const uint32_t array_size)
      : impl_ptr_(new Implementation(row, col, array, array_size))
    {
    }

    /**
     * @brief copy constructor
     *
     * @param other input matrix
     * @throw std::bad_alloc when initialization fails
     */
    MatrixBaseT(const MatrixBaseT& other) : impl_ptr_(new Implementation(*(other.impl_ptr_)))
    {
    }

    /**
     * @brief copy assignment
     *
     * @param other input matrix
     * @throw std::bad_alloc when initialization fails
     * @return reference of MatrixBaseT
     */
    MatrixBaseT& operator=(MatrixBaseT const& other)
    {
        impl_ptr_.reset(new Implementation(*(other.impl_ptr_)));
        return *this;
    }

    /**
     * @brief destructor
     */
    ~MatrixBaseT() noexcept
    {
        static_assert(std::is_floating_point<ScalarType>::value, "only floating type matrix is supported!!!");
        static_assert((Row != 0 && Col != 0), "zero dimension matrix is NOT supported!!!");
    }

    /**
     * @brief return raw data
     *
     * @note !!! the raw data stores matrix element as column-majored !!!
     */
    const ScalarType* GetData() const noexcept
    {
        return impl_ptr_->data.data();
    }

    /**
     * @brief return raw data
     *
     * @note !!! the raw data stores matrix element as column-majored !!!
     */
    ScalarType* GetData() noexcept
    {
        return impl_ptr_->data.data();
    }

    /**
     * @brief cast to a different floating type
     *
     * @details float32_t to float64_t or float64_t to float32_t
     * @tparam CastScalar
     */
    template <typename CastScalar,
              typename std::enable_if<!std::is_same<ScalarType, CastScalar>::value, void>::type* = nullptr>
    MatrixBaseT<CastScalar, Row, Col> Cast() const noexcept
    {
        static_assert(std::is_floating_point<CastScalar>::value, "only floating type matrix is supported");
        return MatrixBaseT<CastScalar, Row, Col>(GetRows(), GetCols(), (impl_ptr_->template Cast<CastScalar>()).data(),
                                                 GetSize());
    }

    /**
     * @brief Temp implementation for cast between same scalar type.
     * @deprecated This function will be remove before Feb. 29, 2020. Do not call this function.
     *
     * @tparam CastScalar
     */
    template <typename CastScalar,
              typename std::enable_if<std::is_same<ScalarType, CastScalar>::value, void>::type* = nullptr>
    MatrixBaseT<CastScalar, Row, Col> Cast() const noexcept
    {
        return *this;
    }

    /**
     * @brief return number of rows of a matrix
     */
    RowSizeType GetRows() const noexcept
    {
        return static_cast<RowSizeType>(impl_ptr_->data.rows());
    }

    /**
     * @brief return number of columns of matrix
     */
    ColSizeType GetCols() const noexcept
    {
        return static_cast<ColSizeType>(impl_ptr_->data.cols());
    }

    /**
     * @brief return size of matrix (Rows() x Cols())
     */
    SizeType GetSize() const noexcept
    {
        return static_cast<SizeType>(impl_ptr_->data.size());
    }

    /**
     * @brief access matrix element with bounds check.
     *
     * @param row query row of element
     * @param col query col of element
     * @throw std::out_of_range when query index out of matrix range
     */
    ScalarType const& At(const RowSizeType row, const ColSizeType col) const
    {
        if (row >= GetRows() || col >= GetCols())
        {
            throw std::out_of_range("query index is out of matrix range");
        }
        return impl_ptr_->data(row, col);
    }

    /**
     * @brief access matrix element with bounds check.
     *
     * @param row query row of element
     * @param col query col of element
     * @throw std::out_of_range when query index out of matrix range
     */
    ScalarType& At(const RowSizeType row, const ColSizeType col)
    {
        if (row >= GetRows() || col >= GetCols())
        {
            throw std::out_of_range("query index is out of matrix range");
        }
        return impl_ptr_->data(row, col);
    }

    /**
     * @brief get a specified row
     *
     * @param index index of row
     * @throw std::out_of_range when query index out of matrix range
     */
    MatrixBaseT<ScalarType, 1, Col> GetRow(const RowSizeType index) const
    {
        if (index >= GetRows())
        {
            throw std::out_of_range("query index is out of matrix range");
        }

        MatrixBaseT<ScalarType, 1, Col> out(1u, this->GetCols());
        for (ColSizeType i = 0u; i < this->GetCols(); i++)
        {
            out(0u, i) = this->operator()(index, i);
        }
        return out;
    }

    /**
     * @brief get a specified col
     *
     * @param index index of col
     * @throw std::out_of_range when query index out of matrix range
     */
    MatrixBaseT<ScalarType, Row, 1> GetCol(const ColSizeType index) const
    {
        if (index >= GetCols())
        {
            throw std::out_of_range("query index is out of matrix range");
        }
        return MatrixBaseT<ScalarType, Row, 1>(GetRows(), 1u, impl_ptr_->data.col(index).data(), GetRows());
    }

    /**
     * @brief get block of matrix
     *
     * @param i start row
     * @param j start col
     * @param rows rows of sub-block matrix
     * @param cols cols of sub-block matrix
     * @throw std::runtime_error when sub-block size exceeds matrix range
     */
    MatrixBaseT<ScalarType, -1, -1> GetBlock(const RowSizeType i, const ColSizeType j, const RowSizeType rows,
                                             const ColSizeType cols) const
    {
        if (i >= this->GetRows() || j >= this->GetCols() || rows > this->GetRows() || cols > this->GetCols())
        {
            throw std::runtime_error("sub-block size exceeds matrix range");
        }

        MatrixBaseT<ScalarType, -1, -1> block(rows, cols);
        for (RowSizeType r = 0u; r < rows; r++)
        {
            for (ColSizeType c = 0u; c < cols; c++)
            {
                block(r, c) = this->operator()(r + i, c + j);
            }
        }
        return block;
    }

    /**
     * @brief Set the Block object
     *
     * @tparam DerivedType Derived matrix type, could be fixed-size or dynamic size
     * @todo use traits to ensure only valid DerivedType can be used
     * @param i start row
     * @param j start col
     * @param block sub-block matrix
     * @throw std::runtime_error when sub-block size exceeds matrix range
     */
    template <typename DerivedType>
    void SetBlock(const RowSizeType i, const ColSizeType j, const DerivedType& block)
    {
        if ((i >= this->GetRows()) || (j >= this->GetCols()) || (i + block.GetRows() > this->GetRows()) ||
            (j + block.GetCols() > this->GetCols()))
        {
            throw std::runtime_error("sub-block size exceeds matrix range");
        }
        for (RowSizeType r = 0u; r < block.GetRows(); r++)
        {
            for (ColSizeType c = 0u; c < block.GetCols(); c++)
            {
                this->operator()(r + i, c + j) = block(r, c);
            }
        }
    }

    /**
     * @brief access matrix element without bounds check.
     *
     * @param row query row of element
     * @param col query col of element
     * @throw std::out_of_range when query index out of matrix range
     */
    ScalarType const& operator()(const RowSizeType row, const ColSizeType col) const
    {
        return At(row, col);
    }

    /**
     * @brief access matrix element without bounds check.
     *
     * @param row query row of element
     * @param col query col of element
     * @throw std::out_of_range when query index out of matrix range
     */
    ScalarType& operator()(const RowSizeType row, const ColSizeType col)
    {
        return At(row, col);
    }

    /**
     * @brief access vector element without bounds check.
     *
     * @param index query index of element
     * @throw std::out_of_range when query index out of matrix range
     */
    ScalarType const& operator()(const SizeType index) const
    {
        if (index >= GetSize())
        {
            throw std::out_of_range("query index is out of matrix range");
        }
        return impl_ptr_->data(index);
    }

    /**
     * @brief access vector element without bounds check.
     *
     * @param index query index of element
     * @throw std::out_of_range when query index out of matrix range
     */
    ScalarType& operator()(const SizeType index)
    {
        if (index >= GetSize())
        {
            throw std::out_of_range("query index is out of matrix range");
        }
        return impl_ptr_->data(index);
    }

    /**
     * @brief check if two matrices are equal
     *
     * @param other the other matrix
     */
    bool_t operator==(const MatrixBaseT& other) const noexcept
    {
        return impl_ptr_->data == other.impl_ptr_->data;
    }

    /**
     * @brief add a matrix
     *
     * @param other input matrix
     */
    MatrixBaseT operator+(const MatrixBaseT& other) const noexcept
    {
        return MatrixBaseT(Implementation(impl_ptr_->data + other.impl_ptr_->data));
    }

    /**
     * @brief add a matrix
     *
     * @param other input matrix
     */
    MatrixBaseT& operator+=(const MatrixBaseT& other) noexcept
    {
        impl_ptr_->data += other.impl_ptr_->data;
        return *this;
    }

    /**
     * @brief subtract a matrix
     *
     * @param other input matrix
     */
    MatrixBaseT operator-(const MatrixBaseT& other) const noexcept
    {
        return MatrixBaseT(Implementation(impl_ptr_->data - other.impl_ptr_->data));
    }

    /**
     * @brief subtract a matrix
     *
     * @param other input matrix
     */
    MatrixBaseT& operator-=(const MatrixBaseT& other) noexcept
    {
        impl_ptr_->data -= other.impl_ptr_->data;
        return *this;
    }

    /**
     * @brief multiply a scalar (matrix * s)
     *
     * @param s scalar value
     */
    MatrixBaseT operator*(const ScalarType s) const noexcept
    {
        return MatrixBaseT(Implementation(impl_ptr_->data * s));
    }

    /**
     * @brief multiply by a scalar (s * matrix)
     *
     * @param s scalar value
     * @param self input matrix
     */
    friend MatrixBaseT operator*(const ScalarType s, const MatrixBaseT& self) noexcept
    {
        return MatrixBaseT(typename MatrixBaseT::Implementation(s * self.impl_ptr_->data));
    }

    /**
     * @brief multiply a scalar (matrix *= s)
     *
     * @param s scalar value
     */
    MatrixBaseT& operator*=(const ScalarType s) noexcept
    {
        impl_ptr_->data *= s;
        return *this;
    }

    /**
     * @brief multiply a matrix
     *
     * @tparam T Scalar type
     * @tparam T1 row of left matrix
     * @tparam T2 col of left matrix, row of right matrix
     * @tparam T3 col of right matrix
     * @param left left matrix
     * @param right right matrix
     */
    template <typename T, int32_t T1, int32_t T2, int32_t T3>
    friend MatrixBaseT<T, T1, T3> operator*(const MatrixBaseT<T, T1, T2>& left,
                                            const MatrixBaseT<T, T2, T3>& right) noexcept;

    /**
     * @brief divide by a scalar (matrix / s)
     *
     * @param s scalar value
     * @throw std::runtime_error when s is zero
     */
    MatrixBaseT operator/(const ScalarType s) const
    {
        if (ScalarEqualT<Scalar>()(s, static_cast<ScalarType>(0.0)))
        {
            throw std::runtime_error("divide by zero is not allowed");
        }

        return MatrixBaseT(Implementation(impl_ptr_->data / s));
    }

    /**
     * @brief divide by a scalar (matrix / s)
     *
     * @param s scalar value
     * @throw std::runtime_error when s is zero
     */
    MatrixBaseT& operator/=(const ScalarType s)
    {
        if (ScalarEqualT<Scalar>()(s, static_cast<ScalarType>(0.0)))
        {
            throw std::runtime_error("divide by zero is not allowed");
        }
        impl_ptr_->data /= s;
        return *this;
    }

    /**
     * @brief Negate each element in the matrix.
     *
     * @return Negated matrix;
     */
    MatrixBaseT operator-() noexcept
    {
        using OutType = MatrixBaseT<ScalarType, Row, Col>;
        return OutType(typename OutType::Implementation(static_cast<ScalarType>(-1) * impl_ptr_->data));
    }

    /**
     * @brief output stream
     *
     * @tparam T1 matrix floating type, only supports float32_t or float64_t
     * @tparam T2 row dimension of matrix
     * @tparam T3 col dimension of matrix
     * @param os std::ostream
     * @param matrix matrix
     */
    template <typename T1, int32_t T2, int32_t T3>
    friend std::ostream& operator<<(std::ostream& os, const MatrixBaseT<T1, T2, T3>& matrix) noexcept;

    /**
     * @brief transpose a matrix
     */
    MatrixBaseT<ScalarType, Col, Row> Transpose() const noexcept
    {
        using OutType = MatrixBaseT<ScalarType, Col, Row>;
        return OutType(GetCols(), GetRows(), impl_ptr_->Transpose().data(), GetSize());
    }

    /**
     * @brief construct matrix from vector as diagonal element
     * @deprecated This function will be removed, please don't use it.
     *
     * @return MatrixT
     * @throw std::runtime_error
     */
    MatrixBaseT<ScalarType, Row, Row> AsDiagonal() const
    {
        if (this->GetCols() != 1u)
        {
            throw std::runtime_error("AsDiagonal only supports vector");
        }

        MatrixBaseT<ScalarType, Row, Row> out(this->GetRows(), this->GetRows());
        for (RowSizeType i = 0u; i < this->GetRows(); i++)
        {
            out(i, i) = this->operator()(i, 0u);
        }
        return out;
    }

    /**
     * @brief return the square of Norm()
     */
    ScalarType GetSquaredNorm() const noexcept
    {
        return impl_ptr_->data.squaredNorm();
    }

    /**
     * @brief return the norm of matrix
     *
     * @details return l2-norm for vector, return Frobenius norm for matrix
     */
    ScalarType GetNorm() const noexcept
    {
        return impl_ptr_->data.norm();
    }

    /**
     * @brief check if a matrix is a square matrix
     *
     */
    bool_t IsSquared() const noexcept
    {
        return (GetRows() == GetCols());
    }

    /**
     * @brief check if a matrix is symmetric
     *
     * @return bool_t
     */
    bool_t IsSymmetric() const noexcept
    {
        bool_t flag = true;
        if (!IsSquared())
        {
            flag = false;
        }
        else
        {
            const ScalarType scalar_zero(0.0);
            for (RowSizeType i = 0u; i < GetRows(); i++)
            {
                for (ColSizeType j = i + 1; j < GetCols(); j++)
                {
                    const ScalarType diff = operator()(i, j) - operator()(j, i);
                    if (std::fabs(diff) > scalar_zero)
                    {
                        flag = false;
                        break;
                    }
                }
            }
        }
        return flag;
    }

    /**
     * @brief check if two matrices are close to each other
     *
     * @param other other matrix
     * @param tol approximate tolerance
     * @return bool_t
     */
    bool_t IsApprox(const MatrixBaseT& other, const ScalarType tol = static_cast<ScalarType>(0.0)) const noexcept
    {
        return impl_ptr_->data.isApprox(other.impl_ptr_->data, tol);
    }

    /**
     * @brief compute sum of all the elements
     *
     */
    ScalarType Sum() const noexcept
    {
        return impl_ptr_->data.sum();
    }

    /**
     * @brief compute the mean value
     *
     * @return ScalarType
     */
    ScalarType Mean() const noexcept
    {
        return impl_ptr_->data.mean();
    }

    /**
     * @brief compute the min element
     *
     * @return ScalarType
     */
    ScalarType MinCoeff() const noexcept
    {
        return impl_ptr_->data.minCoeff();
    }

    /**
     * @brief compute the max element
     *
     * @return ScalarType
     */
    ScalarType MaxCoeff() const noexcept
    {
        return impl_ptr_->data.maxCoeff();
    }

    /**
     * @brief Apply operation on each element of matrix.
     *
     * @param operation A callable object with three arguments. The first argument is reference to matrix element.
     * The second argument is element row index. The third argument is the element column index
     *
     * @return Reference to this matrix
     */
    MatrixBaseT& Foreach(std::function<void(ScalarType& value, size_t row, size_t col)> operation)
    {
        for (size_t i = 0; i < static_cast<size_t>(impl_ptr_->data.rows()); ++i)
        {
            for (size_t j = 0; j < static_cast<size_t>(impl_ptr_->data.cols()); ++j)
            {
                operation(impl_ptr_->data(i, j), i, j);
            }
        }
        return *this;
    }

    /**
     * @brief Apply operation on each element in the matrix.
     *
     * @param operation A callable object with three arguments. The first argument is reference to matrix element.
     * The second argument is element row index. The third argument is the element column index. No return.
     *
     * @return Reference to this matrix
     */
    MatrixBaseT const& Foreach(std::function<void(ScalarType const& value, size_t row, size_t col)> operation) const
    {
        for (size_t i = 0; i < static_cast<size_t>(impl_ptr_->data.rows()); ++i)
        {
            for (size_t j = 0; j < static_cast<size_t>(impl_ptr_->data.cols()); ++j)
            {
                operation(impl_ptr_->data(i, j), i, j);
            }
        }
        return *this;
    }

    /**
     * @brief Apply operation on each element in the matrix if the element satisfies criteria.
     *
     * @param operation A callable object with three arguments. The first argument is reference to matrix element.
     * The second argument is element row index. The third argument is the element column index. No return.
     * @param criteria A callable object with three arguments. The first argument is reference to matrix element.
     * The second argument is element row index. The third argument is the element column index. Return true if the
     * element satisfies criteria otherwise false.
     *
     * @return Reference to this matrix.
     */
    MatrixBaseT& Foreach(std::function<void(ScalarType& value, size_t row, size_t col)>       operation,
                         std::function<bool(ScalarType const& value, size_t row, size_t col)> criteria)
    {
        for (size_t i = 0; i < static_cast<size_t>(impl_ptr_->data.rows()); ++i)
        {
            for (size_t j = 0; j < static_cast<size_t>(impl_ptr_->data.cols()); ++j)
            {
                ScalarType& value = impl_ptr_->data(i, j);
                if (criteria(value, i, j))
                {
                    operation(value, i, j);
                }
            }
        }
        return *this;
    }

    /**
     * @brief Apply operation on each element in the matrix if the element satisfies criteria.
     *
     * @param operation A callable object with three arguments. The first argument is reference to matrix element.
     * The second argument is element row index. The third argument is the element column index. No return.
     * @param criteria A callable object with three arguments. The first argument is reference to matrix element.
     * The second argument is element row index. The third argument is the element column index. Return true if the
     * element satisfies criteria otherwise false.
     *
     * @return Reference to this matrix.
     */
    MatrixBaseT const& Foreach(std::function<void(ScalarType const& value, size_t row, size_t col)> operation,
                               std::function<bool(ScalarType const& value, size_t row, size_t col)> criteria) const
    {
        for (size_t i = 0; i < static_cast<size_t>(impl_ptr_->data.rows()); ++i)
        {
            for (size_t j = 0; j < static_cast<size_t>(impl_ptr_->data.cols()); ++j)
            {
                ScalarType& value = impl_ptr_->data(i, j);
                if (criteria(value, i, j))
                {
                    operation(value, i, j);
                }
            }
        }
        return *this;
    }

    /**
     * @brief compute abs value of all the elements
     *
     * @return MatrixBaseT
     */
    MatrixBaseT CwiseAbs() const noexcept
    {
        MatrixBaseT out(GetRows(), GetCols());
        for (RowSizeType i = 0u; i < GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < GetCols(); j++)
            {
                out.operator()(i, j) = std::fabs(this->operator()(i, j));
            }
        }

        return out;
    }

    /**
     * @brief compute the square of absolute value of all the elements
     *
     * @return MatrixBaseT
     */
    MatrixBaseT CwiseAbsSquare() const noexcept
    {
        return CwiseSquare();
    }

    /**
     * @brief take cosin of each element in matrix
     *
     * @rreturn MatrixBaseT
     */
    MatrixBaseT CwiseCos() const noexcept
    {
        MatrixBaseT out(GetRows(), GetCols());
        for (RowSizeType i = 0u; i < GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < GetCols(); j++)
            {
                out.operator()(i, j) = std::cos(this->operator()(i, j));
            }
        }

        return out;
    }

    /**
     * @brief take exponential of each element in matrix
     *
     * @return MatrixBaseT
     */
    MatrixBaseT CwiseExp() const noexcept
    {
        MatrixBaseT out(GetRows(), GetCols());
        for (RowSizeType i = 0u; i < GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < GetCols(); j++)
            {
                out.operator()(i, j) = std::exp(this->operator()(i, j));
            }
        }

        return out;
    }

    /**
     * @brief take the power of p to each element in matrix
     *
     * @param p power value
     * @return MatrixBaseT
     */
    MatrixBaseT CwisePow(const ScalarType p) const noexcept
    {
        MatrixBaseT out(GetRows(), GetCols());
        for (RowSizeType i = 0u; i < GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < GetCols(); j++)
            {
                out.operator()(i, j) = std::pow(this->operator()(i, j), p);
            }
        }

        return out;
    }

    /**
     * @brief take the coefficient-wise product of *this and other
     *
     * @param other other matrix
     * @return MatrixBaseT
     */
    MatrixBaseT CwiseProduct(const MatrixBaseT& other) const noexcept
    {
        MatrixBaseT out(GetRows(), GetCols());
        for (RowSizeType i = 0u; i < GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < GetCols(); j++)
            {
                out.operator()(i, j) = this->operator()(i, j) * other(i, j);
            }
        }

        return out;
    }

    /**
     * @brief take the coefficient-wise division of *this and other (*this/other)
     *
     * @param other other matrix
     * @return MatrixBaseT
     * @throw std::runtime_error if other has element of zero(0)
     */
    MatrixBaseT CwiseQuotient(const MatrixBaseT& other) const
    {
        MatrixBaseT out(GetRows(), GetCols());
        for (RowSizeType i = 0u; i < GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < GetCols(); j++)
            {
                if (other(i, j) == static_cast<ScalarType>(0))
                {
                    throw std::runtime_error("divide by zero is not allowed!");
                }
                out.operator()(i, j) = this->operator()(i, j) / other(i, j);
            }
        }

        return out;
    }

    /**
     * @brief take sin of each element in matrix
     *
     * @return MatrixBaseT
     */
    MatrixBaseT CwiseSin() const noexcept
    {
        MatrixBaseT out(GetRows(), GetCols());
        for (RowSizeType i = 0u; i < GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < GetCols(); j++)
            {
                out.operator()(i, j) = std::sin(this->operator()(i, j));
            }
        }

        return out;
    }

    /**
     * @brief take the square root of each element in matrix
     *
     * @return MatrixBaseT
     * @throw std::runtime_error if any element is less than zero(<0)
     */
    MatrixBaseT CwiseSqrt() const
    {
        MatrixBaseT out(GetRows(), GetCols());
        for (RowSizeType i = 0u; i < GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < GetCols(); j++)
            {
                const ScalarType value = this->operator()(i, j);
                if (value < static_cast<ScalarType>(0))
                {
                    throw std::runtime_error("sqrt of negative value is not supported!");
                }
                out.operator()(i, j) = std::sqrt(value);
            }
        }

        return out;
    }

    /**
     * @brief take the square of each element in matrix
     *
     * @return MatrixBaseT
     */
    MatrixBaseT CwiseSquare() const noexcept
    {
        MatrixBaseT out(GetRows(), GetCols());
        for (RowSizeType i = 0u; i < GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < GetCols(); j++)
            {
                out.operator()(i, j) = this->operator()(i, j) * this->operator()(i, j);
            }
        }

        return out;
    }

    /**
     * @brief take tan of each element in matrix
     *
     * @return MatrixBaseT
     */
    MatrixBaseT CwiseTan() const noexcept
    {
        MatrixBaseT out(GetRows(), GetCols());
        for (RowSizeType i = 0u; i < GetRows(); i++)
        {
            for (ColSizeType j = 0u; j < GetCols(); j++)
            {
                out.operator()(i, j) = std::tan(this->operator()(i, j));
            }
        }

        return out;
    }

    /**
     * @brief set each element to some value
     *
     * @param value
     */
    void Fill(const ScalarType value) noexcept
    {
        impl_ptr_->data.fill(value);
    }

    /**
     * @brief check if all the elements are equal to zero with precision of tol
     *
     * @param tol precision
     * @return bool_t
     */
    bool_t IsZero(const ScalarType tol = static_cast<ScalarType>(0.0)) const noexcept
    {
        return impl_ptr_->data.isZero(tol);
    }

    /**
     * @brief check if all the elements are equal to one with precision of tol
     *
     * @param tol precision
     * @return bool_t
     */
    bool_t IsOne(const ScalarType tol = static_cast<ScalarType>(0.0)) const noexcept
    {
        return impl_ptr_->data.isOnes(tol);
    }

    /**
     * @brief set all elements to zero
     */
    void SetZero() noexcept
    {
        (void)impl_ptr_->data.setZero();
    }

    /**
     * @brief set all elements to one
     */
    void SetOne() noexcept
    {
        (void)impl_ptr_->data.setOnes();
    }

    /**
     * @brief set all elements to some constant value
     */
    void SetConstant(const ScalarType value) noexcept
    {
        impl_ptr_->data.setConstant(value);
    }

    /**
     * @brief set identity
     */
    void SetIdentity() noexcept
    {
        (void)impl_ptr_->data.setIdentity();
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
        return holo::serialization::AlignedSize<ALIGN>(this->GetRows() * this->GetCols() * sizeof(ScalarType));
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
        /* serialize data */
        for (RowSizeType i = 0u; i < MatrixBaseT::GetRows(); ++i)
        {
            for (ColSizeType j = 0u; j < MatrixBaseT::GetCols(); ++j)
            {
                serializer << this->operator()(i, j);
            }
        }
        /* serialize padding */
        serializer << holo::serialization::align;
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
        for (RowSizeType i = 0u; i < this->GetRows(); ++i)
        {
            for (ColSizeType j = 0u; j < this->GetCols(); ++j)
            {
                deserializer >> this->operator()(i, j);
            }
        }
        deserializer >> holo::serialization::align;
    }

    /**
     * @brief zero matrix
     *
     * @return MatrixT
     * @throw std::bad_alloc when initialization fails
     */
    static MatrixBaseT Zero()
    {
        MatrixBaseT mat;
        mat.SetZero();
        return mat;
    }

    /**
     * @brief one matrix
     *
     * @return MatrixT
     * @throw std::bad_alloc when initialization fails
     */
    static MatrixBaseT One()
    {
        MatrixBaseT mat;
        mat.SetOne();
        return mat;
    }

    /**
     * @brief
     *
     * @return MatrixBaseT
     * @throw std::bad_alloc when initialization fails
     */
    static MatrixBaseT Constant(const ScalarType value)
    {
        MatrixBaseT mat;
        mat.SetConstant(value);
        return mat;
    }

    /**
     * @brief return an identity matrix
     *
     * @return MatrixT
     * @throw std::bad_alloc when initialization fails
     */
    static MatrixBaseT Identity()
    {
        MatrixBaseT mat;
        mat.SetIdentity();
        return mat;
    }

protected:
    struct Implementation;

    /**
     * @brief Construct a new Matrix Base T object from impl
     *
     * @param impl
     * @throw std::bad_alloc when initialization fails
     */
    MatrixBaseT(const Implementation& impl) : impl_ptr_(new Implementation(impl))
    {
    }

    /**
     * @brief Assign values start from matrix(R, C) with args. Row is filled first.
     *
     * @tparam R Row number.
     * @tparam C Column number.
     * @tparam T Type of assigned value for matrix(R, C).
     * @tparam Args Type of rest of values to be assigned.
     * @param value Value to assign to matrix(R, C).
     * @param args Rest of values to be assigned.
     */
    template <size_t R, size_t C, typename T, typename... Args,
              typename std::enable_if<(C < ColValue - 1), void>::type* = nullptr>
    void assignValue(T value, Args... args)
    {
        this->operator()(R, C) = static_cast<ScalarType>(value);
        assignValue<R, C + 1, Args...>(std::forward<Args>(args)...);
    }

    /**
     * @brief Assign values start from matrix(R, C) with args. Row is filled first.
     *
     * @tparam R Row number.
     * @tparam C Column number.
     * @tparam T Type of assigned value for matrix(R, C).
     * @tparam Args Type of rest of values to be assigned.
     * @param value Value to assign to matrix(R, C).
     * @param args Rest of values to be assigned.
     */
    template <size_t R, size_t C, typename T, typename... Args,
              typename std::enable_if<(C == ColValue - 1)>::type* = nullptr>
    void assignValue(T value, Args... args)
    {
        this->operator()(R, C) = static_cast<ScalarType>(value);
        assignValue<R + 1, 0, Args...>(std::forward<Args>(args)...);
    }

    /**
     * @brief Assign value to matrix(R, C).
     *
     * @tparam R Row number.
     * @tparam C Column number.
     * @tparam T Type of assigned value for matrix(R, C).
     * @param value Value to assign to matrix(R, C).
     */
    template <size_t R, size_t C, typename T>
    void assignValue(T value)
    {
        this->operator()(R, C) = static_cast<ScalarType>(value);
    }

    /**
     * @brief real implementation
     */
    std::unique_ptr<Implementation> impl_ptr_;

};  // MatrixBaseT

/**
 * @brief define internal implementation of matrix
 *
 * @tparam Scalar
 * @tparam Row
 * @tparam Col
 */
template <typename Scalar, int32_t Row, int32_t Col>
struct MatrixBaseT<Scalar, Row, Col>::Implementation
{
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    using ScalarType  = Scalar;
    using MatrixType  = Eigen::Matrix<ScalarType, Row, Col>;
    using ColSizeType = typename MatrixBaseT<ScalarType, Row, Col>::ColSizeType;
    using RowSizeType = typename MatrixBaseT<ScalarType, Row, Col>::RowSizeType;
    using SizeType    = typename MatrixBaseT<ScalarType, Row, Col>::SizeType;

    /**
     * @brief Construct a new Implementation object
     *
     */
    Implementation() noexcept
    {
    }

    /**
     * @brief Construct a new Implementation object
     *
     * @details a "zero" matrix is created
     * @param row row dimension of matrix
     * @param col column dimension of matrix
     * @throw std::bad_alloc when matrix initialization fails
     */
    Implementation(const RowSizeType row, const ColSizeType col) : data(row, col)
    {
        (void)data.setZero();
    }

    /**
     * @brief Construct a new Implementation object from raw data array (column-majored)
     *
     * @param row row dimension of matrix
     * @param col column dimension of matrix
     * @param array raw data array
     * @param array_size data array size
     * @throw std::runtime_error when array size and matrix size is inconsistent
     */
    Implementation(const RowSizeType row, const ColSizeType col, const ScalarType* array, const uint32_t array_size)
      : data(row, col)
    {
        if (array_size != (SizeType)row * col)
        {
            throw std::runtime_error("matrix and array size is inconsistent");
        }
        (void)memcpy(data.data(), array, sizeof(ScalarType) * array_size);
    }

    /**
     * @brief Construct a new Implementation object from data
     *
     * @param _data matrix data
     */
    Implementation(const MatrixType& _data) noexcept : data(_data)
    {
    }

    /**
     * @brief disable copy constructor
     */
    Implementation(const Implementation& other) noexcept
    {
        data = other.data;
    }

    /**
     * @brief copy assignment operator
     *
     * @param other
     * @return reference of Implementation
     */
    Implementation& operator=(const Implementation& other) noexcept
    {
        data = other.data;
        return *this;
    }

    /**
     * @brief cast to a different type
     *
     * @tparam CastScalar different scalar type
     */
    template <typename CastScalar>
    Eigen::Matrix<CastScalar, Row, Col> Cast() const noexcept
    {
        return data.template cast<CastScalar>();
    }

    /**
     * @brief return the transpose of a matrix
     */
    Eigen::Matrix<ScalarType, Col, Row> Transpose() const noexcept
    {
        return data.transpose();
    }

    /**
     * @brief output stream
     *
     * @param os
     * @param impl
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const Implementation& impl) noexcept
    {
        os << impl.data;
        return os;
    }

    // internally we use eigen matrix
    MatrixType data;

};  // class Implementation

/**
 * @brief multiply a matrix
 *
 * @tparam T Scalar type
 * @tparam T1 row of left matrix
 * @tparam T2 col of left matrix, row of right matrix
 * @tparam T3 col of right matrix
 * @param left left matrix
 * @param right right matrix
 */
template <typename T, int32_t T1, int32_t T2, int32_t T3>
MatrixBaseT<T, T1, T3> operator*(const MatrixBaseT<T, T1, T2>& left, const MatrixBaseT<T, T2, T3>& right) noexcept
{
    return MatrixBaseT<T, T1, T3>(
        typename MatrixBaseT<T, T1, T3>::Implementation(left.impl_ptr_->data * right.impl_ptr_->data));
}

/**
 * @brief output stream
 *
 * @tparam T1 matrix floating type, only supports float32_t or float64_t
 * @tparam T2 row dimension of matrix
 * @tparam T3 col dimension of matrix
 * @param os std::ostream
 * @param matrix matrix
 */
template <typename T1, int32_t T2, int32_t T3>
std::ostream& operator<<(std::ostream& os, const MatrixBaseT<T1, T2, T3>& matrix) noexcept
{
    os << *(matrix.impl_ptr_);
    return os;
}

/**
 * @}
 */
}  // namespace numerics

template <typename ScalarType, int32_t Row, int32_t Col>
using MatrixBaseT[[deprecated]] = numerics::MatrixBaseT<ScalarType, Row, Col>;

}  // namespace holo

#endif  // HOLO_NUMERICS_MATRIX_BASE_H_
