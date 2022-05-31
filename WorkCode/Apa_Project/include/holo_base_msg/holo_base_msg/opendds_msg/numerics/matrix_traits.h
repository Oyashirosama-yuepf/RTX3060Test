#ifndef OPENDDS_MSG_NUMERICS_MATRIX_TRAITS_H_
#define OPENDDS_MSG_NUMERICS_MATRIX_TRAITS_H_

#include <opendds_wrapper/traits.h>
#include <holo/numerics/matrix.h>

#include <holo_base_msg/numerics/MatrixC.h>
#include <holo_base_msg/numerics/MatrixS.h>
#include <holo_base_msg/numerics/MatrixTypeSupportC.h>
#include <holo_base_msg/numerics/MatrixTypeSupportS.h>
#include <holo_base_msg/numerics/MatrixTypeSupportImpl.h>



namespace opendds_wrapper
{

/* Matrixf traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Matrixf>
{
    using ValueType = ::holo_base_msg::numerics::Matrixf;
    using MessageType = ::holo_base_msg::numerics::Matrixf;
};

template <>
struct DefaultMessageTraits<::holo::numerics::MatrixT<::holo::float32_t, -1, -1>>
{
    using ValueType = ::holo::numerics::MatrixT<::holo::float32_t, -1, -1>;
    using MessageType = ::holo_base_msg::numerics::Matrixf;
};

/* Matrix22f traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Matrix22f>
{
    using ValueType = ::holo_base_msg::numerics::Matrix22f;
    using MessageType = ::holo_base_msg::numerics::Matrix22f;
};

template <>
struct DefaultMessageTraits<::holo::numerics::MatrixT<::holo::float32_t, 2, 2>>
{
    using ValueType = ::holo::numerics::MatrixT<::holo::float32_t, 2, 2>;
    using MessageType = ::holo_base_msg::numerics::Matrix22f;
};

/* Matrix33f traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Matrix33f>
{
    using ValueType = ::holo_base_msg::numerics::Matrix33f;
    using MessageType = ::holo_base_msg::numerics::Matrix33f;
};

template <>
struct DefaultMessageTraits<::holo::numerics::MatrixT<::holo::float32_t, 3, 3>>
{
    using ValueType = ::holo::numerics::MatrixT<::holo::float32_t, 3, 3>;
    using MessageType = ::holo_base_msg::numerics::Matrix33f;
};

/* Matrix44f traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Matrix44f>
{
    using ValueType = ::holo_base_msg::numerics::Matrix44f;
    using MessageType = ::holo_base_msg::numerics::Matrix44f;
};

template <>
struct DefaultMessageTraits<::holo::numerics::MatrixT<::holo::float32_t, 4, 4>>
{
    using ValueType = ::holo::numerics::MatrixT<::holo::float32_t, 4, 4>;
    using MessageType = ::holo_base_msg::numerics::Matrix44f;
};

/* Matrix55f traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Matrix55f>
{
    using ValueType = ::holo_base_msg::numerics::Matrix55f;
    using MessageType = ::holo_base_msg::numerics::Matrix55f;
};

template <>
struct DefaultMessageTraits<::holo::numerics::MatrixT<::holo::float32_t, 5, 5>>
{
    using ValueType = ::holo::numerics::MatrixT<::holo::float32_t, 5, 5>;
    using MessageType = ::holo_base_msg::numerics::Matrix55f;
};

/* Matrix66f traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Matrix66f>
{
    using ValueType = ::holo_base_msg::numerics::Matrix66f;
    using MessageType = ::holo_base_msg::numerics::Matrix66f;
};

template <>
struct DefaultMessageTraits<::holo::numerics::MatrixT<::holo::float32_t, 6, 6>>
{
    using ValueType = ::holo::numerics::MatrixT<::holo::float32_t, 6, 6>;
    using MessageType = ::holo_base_msg::numerics::Matrix66f;
};


/* Matrixd traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Matrixd>
{
    using ValueType = ::holo_base_msg::numerics::Matrixd;
    using MessageType = ::holo_base_msg::numerics::Matrixd;
};

template <>
struct DefaultMessageTraits<::holo::numerics::MatrixT<::holo::float64_t, -1, -1>>
{
    using ValueType = ::holo::numerics::MatrixT<::holo::float64_t, -1, -1>;
    using MessageType = ::holo_base_msg::numerics::Matrixd;
};

/* Matrix22d traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Matrix22d>
{
    using ValueType = ::holo_base_msg::numerics::Matrix22d;
    using MessageType = ::holo_base_msg::numerics::Matrix22d;
};

template <>
struct DefaultMessageTraits<::holo::numerics::MatrixT<::holo::float64_t, 2, 2>>
{
    using ValueType = ::holo::numerics::MatrixT<::holo::float64_t, 2, 2>;
    using MessageType = ::holo_base_msg::numerics::Matrix22d;
};

/* Matrix33d traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Matrix33d>
{
    using ValueType = ::holo_base_msg::numerics::Matrix33d;
    using MessageType = ::holo_base_msg::numerics::Matrix33d;
};

template <>
struct DefaultMessageTraits<::holo::numerics::MatrixT<::holo::float64_t, 3, 3>>
{
    using ValueType = ::holo::numerics::MatrixT<::holo::float64_t, 3, 3>;
    using MessageType = ::holo_base_msg::numerics::Matrix33d;
};

/* Matrix44d traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Matrix44d>
{
    using ValueType = ::holo_base_msg::numerics::Matrix44d;
    using MessageType = ::holo_base_msg::numerics::Matrix44d;
};

template <>
struct DefaultMessageTraits<::holo::numerics::MatrixT<::holo::float64_t, 4, 4>>
{
    using ValueType = ::holo::numerics::MatrixT<::holo::float64_t, 4, 4>;
    using MessageType = ::holo_base_msg::numerics::Matrix44d;
};

/* Matrix55d traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Matrix55d>
{
    using ValueType = ::holo_base_msg::numerics::Matrix55d;
    using MessageType = ::holo_base_msg::numerics::Matrix55d;
};

template <>
struct DefaultMessageTraits<::holo::numerics::MatrixT<::holo::float64_t, 5, 5>>
{
    using ValueType = ::holo::numerics::MatrixT<::holo::float64_t, 5, 5>;
    using MessageType = ::holo_base_msg::numerics::Matrix55d;
};

/* Matrix66d traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Matrix66d>
{
    using ValueType = ::holo_base_msg::numerics::Matrix66d;
    using MessageType = ::holo_base_msg::numerics::Matrix66d;
};

template <>
struct DefaultMessageTraits<::holo::numerics::MatrixT<::holo::float64_t, 6, 6>>
{
    using ValueType = ::holo::numerics::MatrixT<::holo::float64_t, 6, 6>;
    using MessageType = ::holo_base_msg::numerics::Matrix66d;
};

template<typename T>
struct DefaultConversionTraits<::holo::numerics::MatrixT<T, -1, -1>>
{
    using ValueType = ::holo::numerics::MatrixT<T, -1, -1>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;
    static void Convert(ValueType const& value, MessageType& message)
    {
        message.rows = value.GetRows();
        message.cols = value.GetCols();
        message.data.length(value.GetSize());
        for (size_t idx = 0; idx < value.GetSize(); idx++)
        {
            message.data[idx] = value(idx);
        }
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value.Resize(message.rows, message.cols);
        for (size_t idx = 0; idx < message.data.length(); idx++)
        {
            value(idx) = message.data[idx];
        }
    }
};

template<typename T, int32_t COL>
struct DefaultConversionTraits<::holo::numerics::MatrixT<T, COL, COL>>
{
    using ValueType = ::holo::numerics::MatrixT<T, COL, COL>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;
    static void Convert(ValueType const& value, MessageType& message)
    {
        for (uint16_t row = 0; row < COL; row++)
        {
            for (uint16_t col = 0; col < COL; col++)
            {
                message[row][col] = value(row, col);
            }
        }
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        for (uint16_t row = 0; row < COL; row++)
        {
            for (uint16_t col = 0; col < COL; col++)
            {
                value(row, col) = message[row][col];
            }
        }
    }
};

}//namespace opendds_wrapper

#endif