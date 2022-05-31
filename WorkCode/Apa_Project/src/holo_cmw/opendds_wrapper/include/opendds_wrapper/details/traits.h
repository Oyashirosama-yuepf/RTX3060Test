/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file traits.h
 * @brief This header file defines type traits for builtin topic types.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-08
 */

#ifndef OPENDDS_WRAPPER_DETAILS_TRAITS_H_
#define OPENDDS_WRAPPER_DETAILS_TRAITS_H_

#include <dds/DCPS/TypeSupportImpl.h>
#include <holo/serialization/serialization.h>
#include <string>
#include <type_traits>

namespace opendds_wrapper
{
template <class T, std::size_t = sizeof(T)>
std::true_type is_complete_impl(T*);

std::false_type is_complete_impl(...);

template <class T>
using IsComplete = decltype(is_complete_impl(std::declval<T*>()));

template <typename V>
struct DefaultMessageTraits;

template <typename V, typename M = typename DefaultMessageTraits<V>::MessageType>
struct DefaultConversionTraits;

template <typename V, typename Serializer = holo::serialization::Serializer<>,
          typename Deserializer = holo::serialization::Deserializer<>, typename SFINAE = void>
struct SerializationTraits;

template <typename V, typename Serializer, typename Deserializer>
struct SerializationTraits<V, Serializer, Deserializer,
                           typename std::enable_if<!IsComplete<OpenDDS::DCPS::DDSTraits<V>>::value &&
                                                   (std::is_arithmetic<V>::value || std::is_enum<V>::value)>::type>
{
    using ValueType   = V;
    using MessageType = opendds_wrapper::BuiltinBuffer;

    using SerializerType   = Serializer;
    using DeserializerType = Deserializer;

    static void Convert(ValueType const& value, MessageType& message)
    {
        static const size_t ALIGN = SerializerType::ALIGNMENT_VALUE;
        message.value.length(
            holo::serialization::AlignedSize<ALIGN>(sizeof(ValueType)));
        SerializerType s(&message.value[0], message.value.length());
        s << value << holo::serialization::align;
        assert(message.value.length() == s.GetSize());
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        DeserializerType d(&message.value[0], message.value.length());
        d >> value >> holo::serialization::align;
        assert(message.value.length() == d.GetOffset());
    }
};

template <typename V, typename Serializer, typename Deserializer>
struct SerializationTraits<V, Serializer, Deserializer,
                           typename std::enable_if<!IsComplete<OpenDDS::DCPS::DDSTraits<V>>::value &&
                                                   (std::is_class<V>::value || std::is_union<V>::value)>::type>
{
    using ValueType   = V;
    using MessageType = opendds_wrapper::BuiltinBuffer;

    using SerializerType   = Serializer;
    using DeserializerType = Deserializer;

    static void Convert(ValueType const& value, MessageType& message)
    {
        static const size_t ALIGN = SerializerType::ALIGNMENT_VALUE;
        message.value.length(
            holo::serialization::AlignedSize<ALIGN>(value.template GetSerializedSize<ALIGN>()));
        SerializerType s(&message.value[0], message.value.length());
        s << value << holo::serialization::align;
        assert(message.value.length() == s.GetSize());
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        DeserializerType d(&message.value[0], message.value.length());
        d >> value >> holo::serialization::align;
        assert(message.value.length() == d.GetOffset());
    }
};

template <typename Serializer, typename Deserializer>
struct SerializationTraits<std::string, Serializer, Deserializer>
{
    using ValueType   = std::string;
    using MessageType = opendds_wrapper::BuiltinBuffer;

    using SerializerType   = Serializer;
    using DeserializerType = Deserializer;

    static void Convert(ValueType const& value, MessageType& message)
    {
        static const size_t ALIGN = SerializerType::ALIGNMENT_VALUE;
        message.value.length(
            holo::serialization::AlignedSize<ALIGN>(value.size() + 1U));
        SerializerType s(&message.value[0], message.value.length());
        s << value << holo::serialization::align;
        assert(message.value.length() == s.GetSize());
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        DeserializerType d(&message.value[0], message.value.length());
        d >> value >> holo::serialization::align;
        assert(message.value.length() == d.GetOffset());
    }
};

template <typename V, typename Serializer, typename Deserializer>
struct SerializationTraits<V, Serializer, Deserializer,
                           typename std::enable_if<IsComplete<OpenDDS::DCPS::DDSTraits<V>>::value>::type>
{
    using ValueType   = V;
    using MessageType = V;
};

template <typename V, typename SFINAE = void>
struct MemcpyTraits;

template <typename V>
struct MemcpyTraits<V, typename std::enable_if<!IsComplete<OpenDDS::DCPS::DDSTraits<V>>::value &&
                                               std::is_standard_layout<V>::value>::type>
{
    using ValueType   = V;
    using MessageType = opendds_wrapper::BuiltinBuffer;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value.length(sizeof(value));
        std::memcpy(&message.value[0], &value, sizeof(value));
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        std::memcpy(&value, &message.value[0], sizeof(value));
    }
};

template <typename V>
struct MemcpyTraits<V, typename std::enable_if<IsComplete<OpenDDS::DCPS::DDSTraits<V>>::value>::type>
{
    using ValueType   = V;
    using MessageType = V;
};

}  // namespace opendds_wrapper

#endif
