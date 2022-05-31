/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file builtin_traits.h
 * @brief This header file defines builtin message traits.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-07
 */

#ifndef OPENDDS_WRAPPER_DETAILS_BUILTIN_TRAITS_H_
#define OPENDDS_WRAPPER_DETAILS_BUILTIN_TRAITS_H_

#include <cstring>

#include "common.h"
#include "traits.h"

namespace opendds_wrapper
{
template <>
struct DefaultMessageTraits<::opendds_wrapper::BuiltinUint8>
{
    using ValueType   = ::opendds_wrapper::BuiltinUint8;
    using MessageType = ::opendds_wrapper::BuiltinUint8;
};

template <>
struct DefaultMessageTraits<::opendds_wrapper::BuiltinUint16>
{
    using ValueType   = ::opendds_wrapper::BuiltinUint16;
    using MessageType = ::opendds_wrapper::BuiltinUint16;
};

template <>
struct DefaultMessageTraits<::opendds_wrapper::BuiltinUint32>
{
    using ValueType   = ::opendds_wrapper::BuiltinUint32;
    using MessageType = ::opendds_wrapper::BuiltinUint32;
};

template <>
struct DefaultMessageTraits<::opendds_wrapper::BuiltinUint64>
{
    using ValueType   = ::opendds_wrapper::BuiltinUint64;
    using MessageType = ::opendds_wrapper::BuiltinUint64;
};

template <>
struct DefaultMessageTraits<::opendds_wrapper::BuiltinFloat32>
{
    using ValueType   = ::opendds_wrapper::BuiltinFloat32;
    using MessageType = ::opendds_wrapper::BuiltinFloat32;
};

template <>
struct DefaultMessageTraits<::opendds_wrapper::BuiltinFloat64>
{
    using ValueType   = ::opendds_wrapper::BuiltinFloat64;
    using MessageType = ::opendds_wrapper::BuiltinFloat64;
};

template <>
struct DefaultMessageTraits<::opendds_wrapper::BuiltinString>
{
    using ValueType   = ::opendds_wrapper::BuiltinString;
    using MessageType = ::opendds_wrapper::BuiltinString;
};

template <>
struct DefaultMessageTraits<::opendds_wrapper::BuiltinBuffer>
{
    using ValueType   = ::opendds_wrapper::BuiltinBuffer;
    using MessageType = ::opendds_wrapper::BuiltinBuffer;
};

template <>
struct DefaultConversionTraits<::opendds_wrapper::BuiltinUint8>
{
    using ValueType   = ::opendds_wrapper::BuiltinUint8;
    using MessageType = ::opendds_wrapper::BuiltinUint8;
};

template <>
struct DefaultConversionTraits<::opendds_wrapper::BuiltinUint16>
{
    using ValueType   = ::opendds_wrapper::BuiltinUint16;
    using MessageType = ::opendds_wrapper::BuiltinUint16;
};

template <>
struct DefaultConversionTraits<::opendds_wrapper::BuiltinUint32>
{
    using ValueType   = ::opendds_wrapper::BuiltinUint32;
    using MessageType = ::opendds_wrapper::BuiltinUint32;
};

template <>
struct DefaultConversionTraits<::opendds_wrapper::BuiltinUint64>
{
    using ValueType   = ::opendds_wrapper::BuiltinUint64;
    using MessageType = ::opendds_wrapper::BuiltinUint64;
};

template <>
struct DefaultConversionTraits<::opendds_wrapper::BuiltinFloat32>
{
    using ValueType   = ::opendds_wrapper::BuiltinFloat32;
    using MessageType = ::opendds_wrapper::BuiltinFloat32;
};

template <>
struct DefaultConversionTraits<::opendds_wrapper::BuiltinFloat64>
{
    using ValueType   = ::opendds_wrapper::BuiltinFloat64;
    using MessageType = ::opendds_wrapper::BuiltinFloat64;
};

template <>
struct DefaultConversionTraits<::opendds_wrapper::BuiltinString>
{
    using ValueType   = ::opendds_wrapper::BuiltinString;
    using MessageType = ::opendds_wrapper::BuiltinString;
};

template <>
struct DefaultConversionTraits<::opendds_wrapper::BuiltinBuffer>
{
    using ValueType   = ::opendds_wrapper::BuiltinBuffer;
    using MessageType = ::opendds_wrapper::BuiltinBuffer;
};

template <>
struct DefaultMessageTraits<bool>
{
    using ValueType   = bool;
    using MessageType = ::opendds_wrapper::BuiltinUint8;
};

template <>
struct DefaultMessageTraits<char>
{
    using ValueType   = char;
    using MessageType = ::opendds_wrapper::BuiltinUint8;
};

template <>
struct DefaultMessageTraits<int8_t>
{
    using ValueType   = int8_t;
    using MessageType = ::opendds_wrapper::BuiltinUint8;
};

template <>
struct DefaultMessageTraits<uint8_t>
{
    using ValueType   = uint8_t;
    using MessageType = ::opendds_wrapper::BuiltinUint8;
};

template <>
struct DefaultMessageTraits<int16_t>
{
    using ValueType   = int16_t;
    using MessageType = ::opendds_wrapper::BuiltinUint16;
};

template <>
struct DefaultMessageTraits<uint16_t>
{
    using ValueType   = uint16_t;
    using MessageType = ::opendds_wrapper::BuiltinUint16;
};

template <>
struct DefaultMessageTraits<int32_t>
{
    using ValueType   = int32_t;
    using MessageType = ::opendds_wrapper::BuiltinUint32;
};

template <>
struct DefaultMessageTraits<uint32_t>
{
    using ValueType   = uint32_t;
    using MessageType = ::opendds_wrapper::BuiltinUint32;
};

template <>
struct DefaultMessageTraits<int64_t>
{
    using ValueType   = int64_t;
    using MessageType = ::opendds_wrapper::BuiltinUint64;
};

template <>
struct DefaultMessageTraits<uint64_t>
{
    using ValueType   = uint64_t;
    using MessageType = ::opendds_wrapper::BuiltinUint64;
};

template <>
struct DefaultMessageTraits<float>
{
    using ValueType   = float;
    using MessageType = ::opendds_wrapper::BuiltinFloat32;
};

template <>
struct DefaultMessageTraits<double>
{
    using ValueType   = double;
    using MessageType = ::opendds_wrapper::BuiltinFloat64;
};

template <>
struct DefaultMessageTraits<std::string>
{
    using ValueType   = std::string;
    using MessageType = ::opendds_wrapper::BuiltinString;
};

template <>
struct DefaultMessageTraits<uint8_t*>
{
    using ValueType   = uint8_t*;
    using MessageType = ::opendds_wrapper::BuiltinBuffer;
};

template <>
struct DefaultConversionTraits<bool>
{
    using ValueType   = bool;
    using MessageType = ::opendds_wrapper::BuiltinUint8;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value;
    }
};

template <>
struct DefaultConversionTraits<char>
{
    using ValueType   = char;
    using MessageType = ::opendds_wrapper::BuiltinUint8;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value;
    }
};

template <>
struct DefaultConversionTraits<int8_t>
{
    using ValueType   = int8_t;
    using MessageType = ::opendds_wrapper::BuiltinUint8;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value;
    }
};

template <>
struct DefaultConversionTraits<uint8_t>
{
    using ValueType   = uint8_t;
    using MessageType = ::opendds_wrapper::BuiltinUint8;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value;
    }
};

template <>
struct DefaultConversionTraits<int16_t>
{
    using ValueType   = int16_t;
    using MessageType = ::opendds_wrapper::BuiltinUint16;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value;
    }
};

template <>
struct DefaultConversionTraits<uint16_t>
{
    using ValueType   = uint16_t;
    using MessageType = ::opendds_wrapper::BuiltinUint16;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value;
    }
};

template <>
struct DefaultConversionTraits<int32_t>
{
    using ValueType   = int32_t;
    using MessageType = ::opendds_wrapper::BuiltinUint32;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value;
    }
};

template <>
struct DefaultConversionTraits<uint32_t>
{
    using ValueType   = uint32_t;
    using MessageType = ::opendds_wrapper::BuiltinUint32;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value;
    }
};

template <>
struct DefaultConversionTraits<int64_t>
{
    using ValueType   = int64_t;
    using MessageType = ::opendds_wrapper::BuiltinUint64;
    
    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value;
    }
};

template <>
struct DefaultConversionTraits<uint64_t>
{
    using ValueType   = uint64_t;
    using MessageType = ::opendds_wrapper::BuiltinUint64;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value;
    }
};

template <>
struct DefaultConversionTraits<float>
{
    using ValueType   = float;
    using MessageType = ::opendds_wrapper::BuiltinFloat32;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value;
    }
};

template <>
struct DefaultConversionTraits<double>
{
    using ValueType   = double;
    using MessageType = ::opendds_wrapper::BuiltinFloat64;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value;
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value;
    }
};

template <>
struct DefaultConversionTraits<std::string>
{
    using ValueType   = std::string;
    using MessageType = ::opendds_wrapper::BuiltinString;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value = value.c_str();
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value = message.value.in();
    }
};

template <>
struct DefaultConversionTraits<uint8_t*>
{
    using ValueType   = uint8_t*;
    using MessageType = ::opendds_wrapper::BuiltinBuffer;
};

}  // namespace opendds_wrapper

#endif
