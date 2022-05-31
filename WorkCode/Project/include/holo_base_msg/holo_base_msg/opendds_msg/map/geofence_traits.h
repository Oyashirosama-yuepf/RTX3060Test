#ifndef HOLO_BASE_MSG_OPENDDS_MSG_MAP_GEOFENCE_TRAITS_H_
#define HOLO_BASE_MSG_OPENDDS_MSG_MAP_GEOFENCE_TRAITS_H_

#include <opendds_wrapper/traits.h>
#include <holo/map/geofence.h>

#include <holo_base_msg/map/GeofenceC.h>
#include <holo_base_msg/map/GeofenceS.h>
#include <holo_base_msg/map/GeofenceTypeSupportC.h>
#include <holo_base_msg/map/GeofenceTypeSupportS.h>
#include <holo_base_msg/map/GeofenceTypeSupportImpl.h>


namespace opendds_wrapper
{

template <>
struct DefaultMessageTraits<::holo_base_msg::map::Geofence>
{
    using ValueType = ::holo_base_msg::map::Geofence;
    using MessageType = ::holo_base_msg::map::Geofence;
};

template <>
struct DefaultMessageTraits<::holo::map::Geofence>
{
    using ValueType = ::holo::map::Geofence;
    using MessageType = ::holo_base_msg::map::Geofence;
};

template <>
struct DefaultConversionTraits<::holo::map::Geofence>
{
    using ValueType = ::holo::map::Geofence;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;
    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

template <>
struct DefaultMessageTraits<::holo_base_msg::map::Geofences>
{
    using ValueType = ::holo_base_msg::map::Geofences;
    using MessageType = ::holo_base_msg::map::Geofences;
};

template <>
struct DefaultMessageTraits<::holo::map::Geofences>
{
    using ValueType = ::holo::map::Geofences;
    using MessageType = ::holo_base_msg::map::Geofences;
};

template <>
struct DefaultConversionTraits<::holo::map::Geofences>
{
    using ValueType = ::holo::map::Geofences;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;
    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

}//namespace opendds_wrapper

#endif
