/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vector.h
 * @brief holo vector type
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-07-09
 */

#ifndef HOLO_NUMERICS_VECTOR_H_
#define HOLO_NUMERICS_VECTOR_H_

#include <holo/numerics/matrix.h>
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
 * @brief define column vector base class
 *
 * @details partial template specialization of MatrixBaseT class
 */
template <typename Scalar, int32_t Row>
class VectorBaseT : public MatrixBaseT<Scalar, Row, 1>
{
public:
    using MatrixBaseT<Scalar, Row, 1>::MatrixBaseT;

    using Base = MatrixBaseT<Scalar, Row, 1>;

    using ScalarType  = typename Base::ScalarType;
    using RowSizeType = typename Base::RowSizeType;
    using ColSizeType = typename Base::ColSizeType;
    using SizeType    = RowSizeType;

    static int32_t constexpr RowValue  = Base::RowValue;
    static int32_t constexpr ColValue  = Base::ColValue;
    static int32_t constexpr SizeValue = Base::RowValue;

    /**
     * @brief Construct a new Vector object
     *
     * @throw std::bad_alloc when initialization fails
     */
    VectorBaseT() = default;

    /**
     * @brief Construct a new vector object
     *
     * @details it provides an API for dynamic-size vector
     * @param size size of the whole vector
     * @throw std::bad_alloc when initialization fails
     */
    VectorBaseT(const SizeType size) : Base(size, 1U)
    {
    }

    /**
     * @brief Construct a new Matrix T object
     *
     * @param base matrix base object
     * @throw std::bad_alloc when initialization fails
     */
    VectorBaseT(const Base& base) : Base(base)
    {
    }

    /**
     * @brief copy constructor
     *
     * @param other the other vector
     * @throw std::bad_alloc when initialization fails
     */
    VectorBaseT(const VectorBaseT& other) = default;

    /**
     * @brief copy assignment
     *
     * @param other the other vector
     * @throw std::bad_alloc when initialization fails
     * @return reference of VectorBaseT
     */
    VectorBaseT& operator=(VectorBaseT const& other) = default;

    /**
     * @brief destructor
     */
    virtual ~VectorBaseT() noexcept = default;

    /**
     * @brief element access
     *
     * @param index query index of element
     * @throw std::out_of_range when query index is out of matrix size
     */
    Scalar const& operator[](const SizeType index) const
    {
        return Base::operator()(index, 0U);
    }

    /**
     * @brief element access
     *
     * @param index query index of element
     * @throw std::out_of_range when query index is out of matrix size
     */
    Scalar& operator[](const SizeType index)
    {
        return Base::operator()(index, 0U);
    }

    /**
     * @brief access matrix element, default column is 0
     *
     * @param index
     * @return Scalar
     * @throw std::out_of_range if query index is out of matrix range
     */
    Scalar const& At(const SizeType index) const
    {
        return Base::At(index, 0U);
    }

    /**
     * @brief access matrix element, default column is 0
     *
     * @param index
     * @return Scalar&
     * @throw std::out_of_range if query index is out of matrix range
     */
    Scalar& At(const SizeType index)
    {
        return Base::At(index, 0U);
    }

    /**
     * @brief Dot product
     *
     * @param other the other vector
     * @throw std::runtime_error when matrix size is not consistent
     */
    Scalar Dot(const VectorBaseT& other) const
    {
        if (this->GetSize() != other.GetSize())
        {
            throw std::runtime_error("matrix size is inconsistent");
        }
        return impl_ptr_->data.dot(other.impl_ptr_->data);
    }

    /**
     * @brief normalize a vector
     */
    void Normalize() noexcept
    {
        impl_ptr_->data.normalize();
    }

    /**
     * @brief return the normalized vector
     */
    VectorBaseT GetNormalized() const noexcept
    {
        return VectorBaseT(Implementation(impl_ptr_->data.normalized()));
    }

    /**
     * @brief get segment
     *
     * @param index start index
     * @param length segment length
     * @throw std::runtimer_error when segment size exceeds vector range
     */
    VectorBaseT<Scalar, -1> GetSegment(const SizeType index, const SizeType length) const
    {
        if ((index >= Base::GetSize()) ||
            (static_cast<uint64_t>(index) + static_cast<uint64_t>(length) > static_cast<uint64_t>(Base::GetSize())))
        {
            throw std::runtime_error("segment size exceeds vector range");
        }
        VectorBaseT<Scalar, -1> segment(length);
        for (SizeType i = 0u; i < length; i++)
        {
            segment(i) = this->operator()(i + index, 0u);
        }
        return segment;
    }

    /**
     * @brief set segment
     *
     * @param index start index
     * @param segment segment vector
     * @throw std::runtimer_error when segment size exceeds vector range
     */
    template <typename DerivedType>
    void SetSegment(const SizeType index, const DerivedType& segment)
    {
        if ((index >= Base::GetSize()) || (static_cast<uint64_t>(index) + static_cast<uint64_t>(segment.GetSize()) >
                                           static_cast<uint64_t>(Base::GetSize())))
        {
            throw std::runtime_error("segment size exceeds vector range");
        }
        for (SizeType i = 0u; i < segment.GetSize(); i++)
        {
            this->operator()(index + i, 0u) = segment(i);
        }
    }

    /**
     * @brief get head
     *
     * @param length segment length
     * @throw std::runtimer_error when segment size exceeds vector range
     */
    VectorBaseT<Scalar, -1> GetHead(const SizeType length) const
    {
        return GetSegment(0u, length);
    }

    /**
     * @brief set head
     *
     * @param segment segment vector
     * @throw std::runtimer_error when segment size exceeds vector range
     */
    template <typename DerivedType>
    void SetHead(const DerivedType& segment)
    {
        SetSegment(0u, segment);
    }

    /**
     * @brief get tail
     *
     * @param length segment length
     * @throw std::runtimer_error when segment size exceeds vector range
     */
    VectorBaseT<Scalar, -1> GetTail(const SizeType length) const
    {
        if (length > this->GetSize())
        {
            throw std::runtime_error("segment size exceeds vector range");
        }
        return GetSegment(this->GetSize() - length, length);
    }

    /**
     * @brief set tail
     *
     * @param segment segment vector
     * @throw std::runtimer_error when segment size exceeds vector range
     */
    template <typename DerivedType>
    void SetTail(const DerivedType& segment)
    {
        if (segment.GetSize() > this->GetSize())
        {
            throw std::runtime_error("segment size exceeds vector range");
        }
        SetSegment(this->GetSize() - segment.GetSize(), segment);
    }

    using Base::At;

protected:
    using Base::impl_ptr_;
    using typename Base::Implementation;

    /**
     * @brief Construct a new Matrix T object
     *
     * @param impl
     */
    VectorBaseT(const Implementation& impl) : Base(impl)
    {
    }
};

/**
 * @brief define fixed-size vector class
 *
 * @details derived from VectorBaseT class
 */
template <typename Scalar, int32_t Row>
class VectorT : public VectorBaseT<Scalar, Row>
{
public:
    /**
     * @brief typedef
     */
    using Base     = VectorBaseT<Scalar, Row>;
    using BaseBase = typename Base::Base;

    using ScalarType  = typename Base::ScalarType;
    using RowSizeType = typename Base::RowSizeType;
    using ColSizeType = typename Base::ColSizeType;
    using SizeType    = typename Base::RowSizeType;

    static int32_t constexpr RowValue  = Base::RowValue;
    static int32_t constexpr ColValue  = Base::ColValue;
    static int32_t constexpr SizeValue = Base::RowValue;

    /**
     * @brief default constructor
     *
     * @details a zero vector is constructed
     * @throw std::bad_alloc when initialization fails
     */
    VectorT() : Base(Row)
    {
    }

    /**
     * @brief Construct a new Vector T object
     *
     * @param base_base
     * @throw std::bad_alloc when initialization fails
     */
    VectorT(const BaseBase& base_base) : Base(base_base)
    {
    }

    /**
     * @brief Construct a new VectorT object with initializer list. Row will be filled first.
     *
     * @tparam U Type of initializer list. This function is only enabled if U is convertible to Scalar.
     * @param il Element initializer list.
     */
    template <typename U, typename std::enable_if<std::is_convertible<U&&, Scalar>::value, void>::type* = nullptr>
    VectorT(std::initializer_list<U> il) : Base(Row, 1, il)
    {
    }

    /**
     * @brief Construct a new VectorT object with element values. Row will be filled first.
     *
     * @tparam Args Type of input arguments.
     * @param args Value of element values.
     */
    template <typename... Args, typename std::enable_if<(sizeof...(Args) <= Row) &&
                                                            And<std::is_convertible<Args, Scalar>::value...>::value,
                                                        void>::type* = nullptr>
    VectorT(Args... args)
    {
        BaseBase::template assignValue<0, 0, Args...>(std::forward<Args>(args)...);
    }

    /**
     * @brief Construct a new Vector T object
     *
     * @param base
     * @throw std::bad_alloc when initialization fails
     */
    VectorT(const Base& base) : Base(base)
    {
    }

    /**
     * @brief copy constructor
     * @throw std::bad_alloc when initialization fails
     */
    VectorT(const VectorT& other) = default;


    /**
     * @brief copy assignment
     * @throw std::bad_alloc when initialization fails
     * @return reference of VectorT
     */
    VectorT& operator=(VectorT const& other) = default;

    /**
     * @brief Construct a new vector T object from a dynamic object
     *
     * @param other dynamic vector
     * @throw std::runtime_error if matrix size is inconsistent
     */
    VectorT(const MatrixBaseT<Scalar, -1, 1>& other) : Base(Row)
    {
        if ((Base::GetRows() != other.GetRows()) || (Base::GetCols() != other.GetCols()))
        {
            throw std::runtime_error("inconsistent vector dimension");
        }

        for (SizeType i = 0u; i < Base::GetSize(); i++)
        {
            Base::operator()(i, 0u) = other(i);
        }
    }

    /**
     * @brief Construct a new vector T object from a dynamic object
     *
     * @param other dynamic vector
     * @throw std::runtime_error if matrix size is inconsistent
     * @return reference of VectorT
     */
    VectorT& operator=(const MatrixBaseT<Scalar, -1, 1>& other)
    {
        if ((Base::GetRows() != other.GetRows()) || (Base::GetCols() != other.GetCols()))
        {
            throw std::runtime_error("inconsistent vector dimension");
        }

        for (SizeType i = 0u; i < Base::GetSize(); i++)
        {
            Base::operator()(i, 0u) = other(i);
        }

        return *this;
    }

    /**
     * @brief Destroy the Vector T object
     *
     */
    virtual ~VectorT() noexcept = default;

    /**
     * @brief construct matrix from vector as diagonal element
     *
     * @return MatrixT
     */
    MatrixT<Scalar, Row, Row> AsDiagonal() const
    {
        MatrixT<Scalar, Row, Row> out;
        for (RowSizeType i = 0u; i < out.GetRows(); i++)
        {
            out(i, i) = this->operator()(i, 0u);
        }
        return out;
    }

protected:
    using Base::impl_ptr_;
    using typename Base::Implementation;

    /**
     * @brief Construct a new Matrix T object
     *
     * @param impl
     */
    VectorT(const Implementation& impl) : Base(impl)
    {
    }

};  // VectorT

/**
 * @brief define 3x1 vector
 */
template <typename Scalar>
class VectorT<Scalar, 3> : public VectorBaseT<Scalar, 3>
{
public:
    /**
     * @brief typedef
     */
    using Base     = VectorBaseT<Scalar, 3>;
    using BaseBase = typename Base::Base;

    using ScalarType  = typename Base::ScalarType;
    using RowSizeType = typename Base::RowSizeType;
    using ColSizeType = typename Base::ColSizeType;
    using SizeType    = typename Base::RowSizeType;

    static int32_t constexpr RowValue  = Base::RowValue;
    static int32_t constexpr ColValue  = Base::ColValue;
    static int32_t constexpr SizeValue = Base::RowValue;

    /**
     * @brief default constructor

     * @details a zero vector is constructed
     * @throw std::bad_alloc when initialization fails
     */
    VectorT() : Base(3U)
    {
    }

    /**
     * @brief Construct a new VectorT object from initializer list. Row will be filled first.
     *
     * @tparam U Type of initializer list. This function is only enabled if U is convertible to Scalar.
     * @param il The initializer list
     */
    template <typename U, typename std::enable_if<std::is_convertible<U&&, Scalar>::value, void>::type* = nullptr>
    VectorT(std::initializer_list<U> il)
      : Base(static_cast<RowSizeType>(3), static_cast<ColSizeType>(1), std::forward<std::initializer_list<U>>(il))
    {
    }

    /**
     * @brief Construct a new VectorT object with element values. Row will be filled first.
     *
     * @tparam Args Type of input arguments.
     * @param args Value of element values.
     */
    template <typename... Args,
              typename std::enable_if<(sizeof...(Args) <= 3) && And<std::is_convertible<Args, Scalar>::value...>::value,
                                      void>::type* = nullptr>
    VectorT(Args... args)
    {
        BaseBase::template assignValue<0, 0, Args...>(std::forward<Args>(args)...);
    }

    /**
     * @brief Construct a new Vector T object
     *
     * @param base_base
     * @throw std::bad_alloc when initialization fails
     */
    VectorT(const BaseBase& base_base) : Base(base_base)
    {
    }

    /**
     * @brief Construct a new Vector T object
     *
     * @param base
     * @throw std::bad_alloc when initialization fails
     */
    VectorT(const Base& base) : Base(base)
    {
    }

    /**
     * @brief copy constructor
     * @throw std::bad_alloc when initialization fails
     */
    VectorT(const VectorT& other) = default;

    /**
     * @brief copy assignment
     * @throw std::bad_alloc when initialization fails
     * @return reference of VectorT
     */
    VectorT& operator=(VectorT const& other) = default;

    /**
     * @brief Construct a new vector T object from a dynamic object
     *
     * @param other dynamic vector
     * @throw std::runtime_error if matrix size is inconsistent
     */
    VectorT(const MatrixBaseT<Scalar, -1, 1>& other) : Base(3u)
    {
        if ((Base::GetRows() != other.GetRows()) || (Base::GetCols() != other.GetCols()))
        {
            throw std::runtime_error("inconsistent vector dimension");
        }

        for (SizeType i = 0u; i < Base::GetSize(); i++)
        {
            Base::operator()(i, 0u) = other(i);
        }
    }

    /**
     * @brief Construct a new vector T object from a dynamic object
     *
     * @param other dynamic vector
     * @throw std::runtime_error if matrix size is inconsistent
     * @return reference of VectorT
     */
    VectorT& operator=(const MatrixBaseT<Scalar, -1, 1>& other)
    {
        if ((Base::GetRows() != other.GetRows()) || (Base::GetCols() != other.GetCols()))
        {
            throw std::runtime_error("inconsistent vector dimension");
        }

        for (SizeType i = 0u; i < (SizeType)(Base::GetSize()); i++)
        {
            Base::operator()(i, 0u) = other(i);
        }

        return *this;
    }

    /**
     * @brief Destroy the Vector T object
     *
     */
    virtual ~VectorT() noexcept = default;

    /**
     * @brief cross product
     *
     * @param other the other vector
     * @return VectorT
     */
    VectorT Cross(const VectorT& other) const noexcept
    {
        return VectorT(Implementation(impl_ptr_->data.cross(other.impl_ptr_->data)));
    }

    /**
     * @brief to skew symmetric
     *
     * @return skew symmetric
     */
    MatrixT<Scalar, 3, 3> ToSkewSymmetric() const noexcept
    {
        const Scalar wx = (*this)(0u), wy = (*this)(1u), wz = (*this)(2u);
        const Scalar scalar_zero(0.0);
        return MatrixT<Scalar, 3, 3>(scalar_zero, -wz, wy, wz, scalar_zero, -wx, -wy, wx, scalar_zero);
    }

    /**
     * @brief construct matrix from vector as diagonal element
     *
     * @return MatrixT
     */
    MatrixT<Scalar, 3, 3> AsDiagonal() const
    {
        MatrixT<Scalar, 3, 3> out;
        for (uint16_t i = 0u; i < 3u; i++)
        {
            out(i, i) = this->operator()(i, 0u);
        }
        return out;
    }

protected:
    using Base::impl_ptr_;
    using typename Base::Implementation;

    /**
     * @brief Construct a new Matrix T object
     *
     * @param impl
     */
    VectorT(const Implementation& impl) : Base(impl)
    {
    }

};  // VectorT

/**
 * @brief define dynamic-size vector class
 *
 * @details derived from VectorBaseT class
 */
template <typename Scalar>
class VectorT<Scalar, -1> : public VectorBaseT<Scalar, -1>
{
public:
    /**
     * @brief typedef
     */
    using Base     = VectorBaseT<Scalar, -1>;
    using BaseBase = typename Base::Base;

    using ScalarType  = typename Base::ScalarType;
    using RowSizeType = typename Base::RowSizeType;
    using ColSizeType = typename Base::ColSizeType;
    using SizeType    = typename Base::RowSizeType;

    static int32_t constexpr RowValue  = Base::RowValue;
    static int32_t constexpr ColValue  = Base::ColValue;
    static int32_t constexpr SizeValue = Base::RowValue;

    static RowSizeType constexpr MaxRows = std::numeric_limits<RowSizeType>::max();
    static ColSizeType constexpr MaxCols = 1u;
    static SizeType constexpr MaxSize    = MaxRows * MaxCols;
    /**
     * @brief Construct a new Vector T object
     *
     * @throw std::bad_alloc when initialization fails
     */
    VectorT() : Base()
    {
    }

    /**
     * @brief Construct a new Vector T object
     *
     * @details a zero vector is constructed
     * @param size size of the whole vector
     * @throw std::out_of_range when initialization fails
     */
    VectorT(const int32_t size) : Base(size)
    {
        if (!VectorT::IsSizeValid(size))
        {
            std::stringstream ss;
            ss << "Invalid size to create a vector: expected size = " << static_cast<int32_t>(VectorT::MaxRows)
               << ", actual size = " << size << std::endl;
            throw std::out_of_range(ss.str());
        }
    }

    /**
     * @brief Construct a new Vector T object
     *
     * @param base_base
     * @throw std::bad_alloc when initialization fails
     */
    VectorT(const BaseBase& base_base) : Base(base_base)
    {
    }

    /**
     * @brief Construct a new Vector T object
     *
     * @param base
     * @throw std::bad_alloc when initialization fails
     */
    VectorT(const Base& base) : Base(base)
    {
    }

    /**
     * @brief copy constructor
     * @throw std::bad_alloc when initialization fails
     */
    VectorT(const VectorT& other) = default;

    /**
     * @brief copy assignment
     * @throw std::out_of_range if the other size is out of range
     * @return reference of VectorT
     */
    VectorT& operator=(VectorT const& other) = default;

    /**
     * @brief Destroy the Vector T object
     *
     */
    virtual ~VectorT() noexcept = default;

    /**
     * @brief resize a vector
     *
     * @param size new size
     * @throw std::out_of_range if the new size is out of range
     */
    void Resize(const int32_t size)
    {
        if (!VectorT::IsSizeValid(size))
        {
            std::stringstream ss;
            ss << "Invalid size to create a vector: expected size = " << static_cast<int32_t>(VectorT::MaxRows)
               << ", actual size = " << size << std::endl;
            throw std::out_of_range(ss.str());
        }
        impl_ptr_->data.resize(size);
    }

    /**
     * @brief construct matrix from vector as diagonal element
     *
     * @return MatrixT
     */
    MatrixT<Scalar, -1, -1> AsDiagonal() const
    {
        RowSizeType             row = this->GetRows();
        MatrixT<Scalar, -1, -1> out(row, row);
        for (RowSizeType i = 0u; i < row; i++)
        {
            out(i, i) = this->operator()(i, 0u);
        }
        return out;
    }

    /**
     * @brief zero vector
     *
     * @param size vector size
     * @return VectorT
     * @throw std::bad_alloc when initialization fails
     */
    static VectorT Zero(const int32_t size)
    {
        VectorT vec(size);
        vec.SetZero();
        return vec;
    }

    /**
     * @brief one vector
     *
     * @param size vector size
     * @return VectorT
     * @throw std::bad_alloc when initialization fails
     */
    static VectorT One(const int32_t size)
    {
        VectorT vec(size);
        vec.SetOne();
        return vec;
    }

    /**
     * @brief constant-value vector
     *
     * @param size vector size
     * @param value vector element
     * @return VectorT
     * @throw std::bad_alloc when initialization fails
     */
    static VectorT Constant(const int32_t size, const Scalar value)
    {
        VectorT vec(size);
        vec.SetConstant(value);
        return vec;
    }

    /**
     * @brief check if the vector size is valid
     *
     * @param rows rows of target vector
     * @return bool_t
     */
    static bool_t IsSizeValid(int32_t rows)
    {
        return (rows >= 0) && (rows <= static_cast<int32_t>(MaxRows));
    }

    /**
     * @brief to skew symmetric
     *
     * @return skew symmetric
     * @throw std::runtime_error when matrix size is not three
     */
    MatrixT<Scalar, 3, 3> ToSkewSymmetric() const
    {
        if (Base::GetRows() != 3u)
        {
            throw std::runtime_error("skew symmetric only supports vector of size 3");
        }

        const Scalar wx = (*this)(0u), wy = (*this)(1u), wz = (*this)(2u);
        const Scalar scalar_zero(0.0);
        return MatrixT<Scalar, 3, 3>(scalar_zero, -wz, wy, wz, scalar_zero, -wx, -wy, wx, scalar_zero);
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
        return holo::serialization::SerializedSize<ALIGN>(this->GetRows()) + Base::template GetSerializedSize<ALIGN>();
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
        serializer << holo::serialization::align << static_cast<uint32_t>(this->GetRows());

        BaseBase::Serialize(serializer);
    }

    /**
     * @brief Deserialize vector object from "deserilizer".
     *
     * @param deserilizer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @note Exception safety: Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t row;

        deserializer >> holo::serialization::align >> row;

        this->Resize(row);

        BaseBase::Deserialize(deserializer);
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
    VectorT(const Implementation& impl) : Base(impl)
    {
    }

};  // VectorT

template <typename Scalar>
using Vector1T = VectorT<Scalar, 1>;
using Vector1f = Vector1T<float32_t>;
using Vector1d = Vector1T<float64_t>;
using Vector1  = Vector1T<float64_t>;

template <typename Scalar>
using Vector2T = VectorT<Scalar, 2>;
using Vector2f = Vector2T<float32_t>;
using Vector2d = Vector2T<float64_t>;
using Vector2  = Vector2T<float64_t>;

template <typename Scalar>
using Vector3T = VectorT<Scalar, 3>;
using Vector3f = Vector3T<float32_t>;
using Vector3d = Vector3T<float64_t>;
using Vector3  = Vector3T<float64_t>;

template <typename Scalar>
using Vector4T = VectorT<Scalar, 4>;
using Vector4f = Vector4T<float32_t>;
using Vector4d = Vector4T<float64_t>;
using Vector4  = Vector4T<float64_t>;

template <typename Scalar>
using Vector5T = VectorT<Scalar, 5>;
using Vector5f = Vector5T<float32_t>;
using Vector5d = Vector5T<float64_t>;
using Vector5  = Vector5T<float64_t>;

template <typename Scalar>
using Vector6T = VectorT<Scalar, 6>;
using Vector6f = Vector6T<float32_t>;
using Vector6d = Vector6T<float64_t>;
using Vector6  = Vector6T<float64_t>;

template <typename Scalar>
using Vector7T = VectorT<Scalar, 7>;
using Vector7f = Vector7T<float32_t>;
using Vector7d = Vector7T<float64_t>;
using Vector7  = Vector7T<float64_t>;

template <typename Scalar>
using Vector8T = VectorT<Scalar, 8>;
using Vector8f = Vector8T<float32_t>;
using Vector8d = Vector8T<float64_t>;
using Vector8  = Vector8T<float64_t>;

template <typename Scalar>
using Vector9T = VectorT<Scalar, 9>;
using Vector9f = Vector9T<float32_t>;
using Vector9d = Vector9T<float64_t>;
using Vector9  = Vector9T<float64_t>;

/**
 * @brief handy typedefs, dynamic-size vector
 */
template <typename Scalar>
using VectorXT = VectorT<Scalar, -1>;
using VectorXf = VectorXT<float32_t>;
using VectorXd = VectorXT<float64_t>;
using VectorX  = VectorXd;

/**
 * @}
 *
 */
}  // namespace numerics

template <typename Scalar, int32_t Row>
using VectorT [[deprecated]] = numerics::VectorT<Scalar, Row>;

template <typename Scalar>
using Vector1T [[deprecated]] = numerics::VectorT<Scalar, 1>;
using Vector1f [[deprecated]] = numerics::Vector1T<float32_t>;
using Vector1d [[deprecated]] = numerics::Vector1T<float64_t>;
using Vector1 [[deprecated]]  = numerics::Vector1T<float64_t>;

template <typename Scalar>
using Vector2T [[deprecated]] = numerics::VectorT<Scalar, 2>;
using Vector2f [[deprecated]] = numerics::Vector2T<float32_t>;
using Vector2d [[deprecated]] = numerics::Vector2T<float64_t>;
using Vector2 [[deprecated]]  = numerics::Vector2T<float64_t>;

template <typename Scalar>
using Vector3T [[deprecated]] = numerics::VectorT<Scalar, 3>;
using Vector3f [[deprecated]] = numerics::Vector3T<float32_t>;
using Vector3d [[deprecated]] = numerics::Vector3T<float64_t>;
using Vector3 [[deprecated]]  = numerics::Vector3T<float64_t>;

template <typename Scalar>
using Vector4T [[deprecated]] = numerics::VectorT<Scalar, 4>;
using Vector4f [[deprecated]] = numerics::Vector4T<float32_t>;
using Vector4d [[deprecated]] = numerics::Vector4T<float64_t>;
using Vector4 [[deprecated]]  = numerics::Vector4T<float64_t>;

template <typename Scalar>
using Vector5T [[deprecated]] = numerics::VectorT<Scalar, 5>;
using Vector5f [[deprecated]] = numerics::Vector5T<float32_t>;
using Vector5d [[deprecated]] = numerics::Vector5T<float64_t>;
using Vector5 [[deprecated]]  = numerics::Vector5T<float64_t>;

template <typename Scalar>
using Vector6T [[deprecated]] = numerics::VectorT<Scalar, 6>;
using Vector6f [[deprecated]] = numerics::Vector6T<float32_t>;
using Vector6d [[deprecated]] = numerics::Vector6T<float64_t>;
using Vector6 [[deprecated]]  = numerics::Vector6T<float64_t>;

template <typename Scalar>
using Vector7T [[deprecated]] = numerics::VectorT<Scalar, 7>;
using Vector7f [[deprecated]] = numerics::Vector7T<float32_t>;
using Vector7d [[deprecated]] = numerics::Vector7T<float64_t>;
using Vector7 [[deprecated]]  = numerics::Vector7T<float64_t>;

template <typename Scalar>
using Vector8T [[deprecated]] = numerics::VectorT<Scalar, 8>;
using Vector8f [[deprecated]] = numerics::Vector8T<float32_t>;
using Vector8d [[deprecated]] = numerics::Vector8T<float64_t>;
using Vector8 [[deprecated]]  = numerics::Vector8T<float64_t>;

template <typename Scalar>
using Vector9T [[deprecated]] = numerics::VectorT<Scalar, 9>;
using Vector9f [[deprecated]] = numerics::Vector9T<float32_t>;
using Vector9d [[deprecated]] = numerics::Vector9T<float64_t>;
using Vector9 [[deprecated]]  = numerics::Vector9T<float64_t>;

template <typename Scalar>
using VectorXT [[deprecated]] = numerics::VectorT<Scalar, -1>;
using VectorXf [[deprecated]] = numerics::VectorXT<float32_t>;
using VectorXd [[deprecated]] = numerics::VectorXT<float64_t>;
using VectorX [[deprecated]]  = numerics::VectorXd;

}  // namespace holo

#endif  // HOLO_NUMERICS_VECTOR_H_
