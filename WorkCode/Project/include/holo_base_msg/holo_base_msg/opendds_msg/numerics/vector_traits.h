#ifndef OPENDDS_MSG_NUMERICS_VECTOR_TRAITS_H_
#define OPENDDS_MSG_NUMERICS_VECTOR_TRAITS_H_

#include <opendds_wrapper/traits.h>
#include <holo/numerics/vector.h>

#include <holo_base_msg/numerics/VectorC.h>
#include <holo_base_msg/numerics/VectorS.h>
#include <holo_base_msg/numerics/VectorTypeSupportC.h>
#include <holo_base_msg/numerics/VectorTypeSupportS.h>
#include <holo_base_msg/numerics/VectorTypeSupportImpl.h>


namespace opendds_wrapper
{

/* Vectorf traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vectorf>
{
    using ValueType = ::holo_base_msg::numerics::Vectorf;
    using MessageType = ::holo_base_msg::numerics::Vectorf;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float32_t, -1>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float32_t, -1>;
    using MessageType = ::holo_base_msg::numerics::Vectorf;
};

/* Vector2f traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector2f>
{
    using ValueType = ::holo_base_msg::numerics::Vector2f;
    using MessageType = ::holo_base_msg::numerics::Vector2f;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float32_t, 2>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float32_t, 2>;
    using MessageType = ::holo_base_msg::numerics::Vector2f;
};


/* Vector3f traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector3f>
{
    using ValueType = ::holo_base_msg::numerics::Vector3f;
    using MessageType = ::holo_base_msg::numerics::Vector3f;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float32_t, 3>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float32_t, 3>;
    using MessageType = ::holo_base_msg::numerics::Vector3f;
};

/* Vector4f traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector4f>
{
    using ValueType = ::holo_base_msg::numerics::Vector4f;
    using MessageType = ::holo_base_msg::numerics::Vector4f;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float32_t, 4>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float32_t, 4>;
    using MessageType = ::holo_base_msg::numerics::Vector4f;
};

/* Vector5f traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector5f>
{
    using ValueType = ::holo_base_msg::numerics::Vector5f;
    using MessageType = ::holo_base_msg::numerics::Vector5f;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float32_t, 5>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float32_t, 5>;
    using MessageType = ::holo_base_msg::numerics::Vector5f;
};

/* Vector6f traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector6f>
{
    using ValueType = ::holo_base_msg::numerics::Vector6f;
    using MessageType = ::holo_base_msg::numerics::Vector6f;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float32_t, 6>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float32_t, 6>;
    using MessageType = ::holo_base_msg::numerics::Vector6f;
};

/* Vector7f traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector7f>
{
    using ValueType = ::holo_base_msg::numerics::Vector7f;
    using MessageType = ::holo_base_msg::numerics::Vector7f;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float32_t, 7>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float32_t, 7>;
    using MessageType = ::holo_base_msg::numerics::Vector7f;
};

/* Vector8f traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector8f>
{
    using ValueType = ::holo_base_msg::numerics::Vector8f;
    using MessageType = ::holo_base_msg::numerics::Vector8f;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float32_t, 8>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float32_t, 8>;
    using MessageType = ::holo_base_msg::numerics::Vector8f;
};

/* Vectord traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vectord>
{
    using ValueType = ::holo_base_msg::numerics::Vectord;
    using MessageType = ::holo_base_msg::numerics::Vectord;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float64_t, -1>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float64_t, -1>;
    using MessageType = ::holo_base_msg::numerics::Vectord;
};

/* Vector2d traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector2d>
{
    using ValueType = ::holo_base_msg::numerics::Vector2d;
    using MessageType = ::holo_base_msg::numerics::Vector2d;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float64_t, 2>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float64_t, 2>;
    using MessageType = ::holo_base_msg::numerics::Vector2d;
};

/* Vector3d traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector3d>
{
    using ValueType = ::holo_base_msg::numerics::Vector3d;
    using MessageType = ::holo_base_msg::numerics::Vector3d;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float64_t, 3>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float64_t, 3>;
    using MessageType = ::holo_base_msg::numerics::Vector3d;
};

/* Vector4d traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector4d>
{
    using ValueType = ::holo_base_msg::numerics::Vector4d;
    using MessageType = ::holo_base_msg::numerics::Vector4d;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float64_t, 4>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float64_t, 4>;
    using MessageType = ::holo_base_msg::numerics::Vector4d;
};

/* Vector5d traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector5d>
{
    using ValueType = ::holo_base_msg::numerics::Vector5d;
    using MessageType = ::holo_base_msg::numerics::Vector5d;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float64_t, 5>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float64_t, 5>;
    using MessageType = ::holo_base_msg::numerics::Vector5d;
};

/* Vector6d traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector6d>
{
    using ValueType = ::holo_base_msg::numerics::Vector6d;
    using MessageType = ::holo_base_msg::numerics::Vector6d;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float64_t, 6>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float64_t, 6>;
    using MessageType = ::holo_base_msg::numerics::Vector6d;
};

/* Vector7d traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector7d>
{
    using ValueType = ::holo_base_msg::numerics::Vector7d;
    using MessageType = ::holo_base_msg::numerics::Vector7d;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float64_t, 7>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float64_t, 7>;
    using MessageType = ::holo_base_msg::numerics::Vector7d;
};

/* Vector8d traits */
template <>
struct DefaultMessageTraits<::holo_base_msg::numerics::Vector8d>
{
    using ValueType = ::holo_base_msg::numerics::Vector8d;
    using MessageType = ::holo_base_msg::numerics::Vector8d;
};

template <>
struct DefaultMessageTraits<::holo::numerics::VectorT<::holo::float64_t, 8>>
{
    using ValueType = ::holo::numerics::VectorT<::holo::float64_t, 8>;
    using MessageType = ::holo_base_msg::numerics::Vector8d;
};

template<typename T>
struct DefaultConversionTraits<::holo::numerics::VectorT<T, -1>>
{
    using ValueType = ::holo::numerics::VectorT<T, -1>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.length(value.GetSize());
        for(size_t idx = 0U; idx < value.GetSize(); ++idx)
        {
            message[idx] = value[idx];
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.Resize(message.length());
        for(size_t idx = 0U; idx < message.length(); ++idx)
        {
            value[idx] = message[idx];
        }
    }
};

template<typename T, int32_t COL>
struct DefaultConversionTraits<::holo::numerics::VectorT<T, COL>>
{
    using ValueType = ::holo::numerics::VectorT<T, COL>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        for (size_t idx = 0; idx < COL; idx++)
        {
            message[idx] = value[idx];
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        for (size_t idx = 0; idx < COL; idx++)
        {
            value[idx] = message[idx];
        }
    }
};

}

#endif
