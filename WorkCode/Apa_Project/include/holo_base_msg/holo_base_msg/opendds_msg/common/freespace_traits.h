#ifndef OPENDDS_MSG_COMMON_FREESPACE_TRAITS_H_
#define OPENDDS_MSG_COMMON_FREESPACE_TRAITS_H_

#include <holo/common/freespace.h>

#include <opendds_wrapper/traits.h>

#include <holo_base_msg/common/FreespaceC.h>
#include <holo_base_msg/common/FreespaceS.h>
#include <holo_base_msg/common/FreespaceTypeSupportC.h>
#include <holo_base_msg/common/FreespaceTypeSupportS.h>
#include <holo_base_msg/common/FreespaceTypeSupportImpl.h>
#include <holo_base_msg/opendds_msg/geometry/point_traits.h>

namespace opendds_wrapper
{
namespace freespace
{
template <typename PointType>
struct IdlTypeTraits;

template <>
struct IdlTypeTraits<holo::geometry::Point3f>
{
    using InteriorType = ::holo_base_msg::common::freespace3f::FreespaceInterior;
    using ExteriorType = ::holo_base_msg::common::freespace3f::FreespaceExterior;
    using MessageType  = ::holo_base_msg::common::freespace3f::Freespace;
};

template <>
struct IdlTypeTraits<holo::geometry::Point3d>
{
    using InteriorType = ::holo_base_msg::common::freespace3d::FreespaceInterior;
    using ExteriorType = ::holo_base_msg::common::freespace3d::FreespaceExterior;
    using MessageType  = ::holo_base_msg::common::freespace3d::Freespace;
};
}  // namespace freespace

template <typename PointType, size_t POINT_SIZE>
struct DefaultMessageTraits<::holo::common::details::FreespaceInteriorPolygon<PointType, POINT_SIZE>>
{
    using ValueType   = ::holo::common::details::FreespaceInteriorPolygon<PointType, POINT_SIZE>;
    using MessageType = typename freespace::IdlTypeTraits<PointType>::InteriorType;
};

template <typename PointType, size_t POINT_SIZE>
struct DefaultConversionTraits<::holo::common::details::FreespaceInteriorPolygon<PointType, POINT_SIZE>>
{
    using ValueType   = ::holo::common::details::FreespaceInteriorPolygon<PointType, POINT_SIZE>;
    using MessageType = typename freespace::IdlTypeTraits<PointType>::InteriorType;
    static void Convert(ValueType const& value, MessageType& message)
    {
        message.boundaries.length(value.GetBoundarySize());
        for (size_t i = 0; i < value.GetBoundarySize(); i++)
        {
            message.boundaries[i].start = value.GetBoundaryRangeByIndex(i).first;
            message.boundaries[i].end   = value.GetBoundaryRangeByIndex(i).second;
            message.boundaries[i].type  = value.GetBoundaryTypeByIndex(i);
        }
        message.points.length(value.size());
        for (size_t i = 0; i < value.size(); i++)
        {
            DefaultConversionTraits<PointType>::Convert(value[i], message.points[i]);
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.resize(message.points.length());
        for (size_t i = 0; i < message.boundaries.length(); i++)
        {
            value.SetBoundaryType(message.boundaries[i].start, message.boundaries[i].end, message.boundaries[i].type);
        }
        for (size_t i = 0; i < message.points.length(); i++)
        {
            DefaultConversionTraits<PointType>::Convert(message.points[i], value[i]);
        }
    }
};

template <typename PointType, size_t POINT_SIZE, size_t INTERIOR_SIZE>
struct DefaultMessageTraits<::holo::common::FreespaceExterior<PointType, POINT_SIZE, INTERIOR_SIZE>>
{
    using ValueType   = ::holo::common::FreespaceExterior<PointType, POINT_SIZE, INTERIOR_SIZE>;
    using MessageType = typename freespace::IdlTypeTraits<PointType>::ExteriorType;
};

template <typename PointType, size_t POINT_SIZE, size_t INTERIOR_SIZE>
struct DefaultConversionTraits<::holo::common::FreespaceExterior<PointType, POINT_SIZE, INTERIOR_SIZE>>
{
    using ValueType   = ::holo::common::FreespaceExterior<PointType, POINT_SIZE, INTERIOR_SIZE>;
    using MessageType = typename freespace::IdlTypeTraits<PointType>::ExteriorType;
    static void Convert(ValueType const& value, MessageType& message)
    {
        message.boundaries.length(value.GetBoundarySize());
        for (size_t i = 0; i < value.GetBoundarySize(); i++)
        {
            message.boundaries[i].start = value.GetBoundaryRangeByIndex(i).first;
            message.boundaries[i].end   = value.GetBoundaryRangeByIndex(i).second;
            message.boundaries[i].type  = value.GetBoundaryTypeByIndex(i);
        }
        message.points.length(value.size());
        for (size_t i = 0; i < value.size(); i++)
        {
            DefaultConversionTraits<PointType>::Convert(value[i], message.points[i]);
        }
        message.interiors.length(value.GetInteriorSize());
        for (size_t i = 0; i < value.GetInteriorSize(); i++)
        {
            opendds_wrapper::DefaultConversionTraits<typename ValueType::InteriorType>::Convert(value.GetInterior(i),
                                                                                                message.interiors[i]);
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        for (size_t i = 0; i < message.boundaries.length(); i++)
        {
            value.SetBoundaryType(message.boundaries[i].start, message.boundaries[i].end, message.boundaries[i].type);
        }
        value.resize(message.points.length());
        for (size_t i = 0; i < message.points.length(); i++)
        {
            DefaultConversionTraits<PointType>::Convert(message.points[i], value[i]);
        }

        for (size_t i = 0; i < message.interiors.length(); i++)
        {
            typename ValueType::InteriorType interior_tmp;
            opendds_wrapper::DefaultConversionTraits<typename ValueType::InteriorType>::Convert(message.interiors[i],
                                                                                                interior_tmp);
            value.AddInterior(std::move(interior_tmp));
        }
    }
};

template <typename Exterior, size_t SIZE>
struct DefaultMessageTraits<::holo::common::Freespace<Exterior, SIZE>>
{
    using ValueType   = ::holo::common::Freespace<Exterior, SIZE>;
    using MessageType = typename freespace::IdlTypeTraits<typename Exterior::PointType>::MessageType;
};

template <typename Exterior, size_t SIZE>
struct DefaultConversionTraits<::holo::common::Freespace<Exterior, SIZE>>
{
    using ValueType   = ::holo::common::Freespace<Exterior, SIZE>;
    using MessageType = typename freespace::IdlTypeTraits<typename Exterior::PointType>::MessageType;
    static void Convert(ValueType const& value, MessageType& message)
    {
        message.stamp =
            ::holo_base_msg::common::Timestamp{value.GetTimestamp().GetSec(), value.GetTimestamp().GetNsec()};
        message.coordinate = static_cast<uint32_t>(value.GetCoordinate());
        message.exteriors.length(value.size());
        for (size_t i = 0; i < value.size(); i++)
        {
            opendds_wrapper::DefaultConversionTraits<Exterior>::Convert(value[i], message.exteriors[i]);
        }
    }
    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp(::holo::common::Timestamp{message.stamp.sec, message.stamp.nsec});
        value.SetCoordinate(message.coordinate);
        value.resize(message.exteriors.length());
        for (size_t i = 0; i < message.exteriors.length(); i++)
        {
            opendds_wrapper::DefaultConversionTraits<Exterior>::Convert(message.exteriors[i], value[i]);
        }
    }
};
}  // namespace opendds_wrapper

#endif
