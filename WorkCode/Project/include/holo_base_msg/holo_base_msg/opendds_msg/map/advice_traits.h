#ifndef HOLO_BASE_MSG_OPENDDS_MSG_MAP_ADVICE_TRAITS_H_
#define HOLO_BASE_MSG_OPENDDS_MSG_MAP_ADVICE_TRAITS_H_

#include <holo/map/advice.h>
#include <holo/serialization/serialization.h>
#include <opendds_wrapper/builtin/BuiltinC.h>
#include <opendds_wrapper/builtin/BuiltinS.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportC.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportImpl.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
template <>
struct DefaultMessageTraits<::holo::map::Advice>
{
    using ValueType = ::holo::map::Advice;
    using MessageType = ::opendds_wrapper::BuiltinBuffer;
};


template <>
struct DefaultConversionTraits<::holo::map::Advice>
{
    using ValueType   = ::holo::map::Advice;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        size_t size = 0U;
        size_t capacity = value.GetSerializedSize();
        message.value.length(capacity);
        ::holo::serialization::Serializer<> ser(static_cast<::holo::uint8_t*>(&message.value[0U]), capacity, size);
        ser << value;
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        size_t size     = message.value.length();
        size_t capacity = size;
        ::holo::serialization::Deserializer<> des(const_cast<::holo::uint8_t*>(&message.value[0U]), capacity, size);
        des >> value;
    }
};

}

#endif
