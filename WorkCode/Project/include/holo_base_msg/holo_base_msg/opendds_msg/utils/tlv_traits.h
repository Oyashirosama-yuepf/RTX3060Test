#ifndef OPENDDS_MSG_UTILS_TLV_TRAITS_H_
#define OPENDDS_MSG_UTILS_TLV_TRATIS_H_

#include <opendds_wrapper/traits.h>
#include <holo/utils/tlv.h>

#include <opendds_wrapper/builtin/BuiltinC.h>
#include <opendds_wrapper/builtin/BuiltinS.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportC.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportS.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportImpl.h>

namespace opendds_wrapper
{

template<typename Tlv, typename Tlv::TypeType END_TYPE_VALUE>
struct DefaultMessageTraits<::holo::utils::TlvSequence<Tlv, END_TYPE_VALUE>>
{
    using ValueType = ::holo::utils::TlvSequence<Tlv, END_TYPE_VALUE>;
    using MessageType = ::opendds_wrapper::BuiltinBuffer;
};

template<typename Tlv, typename Tlv::TypeType END_TYPE_VALUE>
struct DefaultConversionTraits<::holo::utils::TlvSequence<Tlv, END_TYPE_VALUE>>
{
    using ValueType = ::holo::utils::TlvSequence<Tlv, END_TYPE_VALUE>;
    using MessageType = ::opendds_wrapper::BuiltinBuffer;
    static void Convert(ValueType const& value, MessageType& message)
    {
        message.value.length(value.GetLength());
        std::memcpy(&message.value[0], value.GetData(), message.value.length());
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value = ValueType(const_cast<uint8_t*>(&message.value[0]), message.value.length());
    }
};

}

#endif
