#ifndef OPENDDS_MSG_COMMON_WEATHER_TRAITS_H_
#define OPENDDS_MSG_COMMON_WEATHER_TRAITS_H_

#include <holo/common/weather.h>
#include <holo_base_msg/common/WeatherC.h>
#include <holo_base_msg/common/WeatherS.h>
#include <holo_base_msg/common/WeatherTypeSupportC.h>
#include <holo_base_msg/common/WeatherTypeSupportImpl.h>
#include <holo_base_msg/common/WeatherTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{

template <>
struct DefaultMessageTraits<::holo_base_msg::common::Weather>
{
    using ValueType   = ::holo_base_msg::common::Weather;
    using MessageType = ::holo_base_msg::common::Weather;
};

template <>
struct DefaultMessageTraits<::holo::common::Weather>
{
    using ValueType   = ::holo::common::Weather;
    using MessageType = ::holo_base_msg::common::Weather;
};

template <>
struct DefaultConversionTraits<::holo::common::Weather>
{
    using ValueType   = ::holo::common::Weather;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.stamp.sec   = value.GetTimestamp().GetSec();
        message.stamp.nsec  = value.GetTimestamp().GetNsec();
        message.weather_category  = value.GetAllWeather();
        
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});
        value.SetAllWeather(message.weather_category);
    }
};

}  // namespace opendds_wrapper

#endif
