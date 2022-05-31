#ifndef OPENDDS_MSG_PREDICTION_INTENTION_TRAITS_H_
#define OPENDDS_MSG_PREDICTION_INTENTION_TRAITS_H_

#include <opendds_wrapper/traits.h>
#include <holo/prediction/intention.h>
#include <holo/prediction/intentions.h>

#include <holo_base_msg/prediction/IntentionC.h>
#include <holo_base_msg/prediction/IntentionS.h>
#include <holo_base_msg/prediction/IntentionTypeSupportC.h>
#include <holo_base_msg/prediction/IntentionTypeSupportS.h>
#include <holo_base_msg/prediction/IntentionTypeSupportImpl.h>


namespace opendds_wrapper
{

template <>
struct DefaultMessageTraits<::holo_base_msg::prediction::Intention>
{
    using ValueType = ::holo_base_msg::prediction::Intention;
    using MessageType = ::holo_base_msg::prediction::Intention;
};

template <>
struct DefaultMessageTraits<::holo::prediction::Intention>
{
    using ValueType = ::holo::prediction::Intention;
    using MessageType = ::holo_base_msg::prediction::Intention;
};

template <>
struct DefaultConversionTraits<::holo::prediction::Intention>
{
    using ValueType = ::holo::prediction::Intention;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;
    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};


template <>
struct DefaultMessageTraits<::holo_base_msg::prediction::Intentions>
{
    using ValueType = ::holo_base_msg::prediction::Intentions;
    using MessageType = ::holo_base_msg::prediction::Intentions;
};

template <>
struct DefaultMessageTraits<::holo::prediction::Intentions>
{
    using ValueType = ::holo::prediction::Intentions;
    using MessageType = ::holo_base_msg::prediction::Intentions;
};

template <>
struct DefaultConversionTraits<::holo::prediction::Intentions>
{
    using ValueType = ::holo::prediction::Intentions;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;
    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

}//namespace opendds_wrapper

#endif