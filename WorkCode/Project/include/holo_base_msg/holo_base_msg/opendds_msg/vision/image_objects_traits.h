#ifndef HOLO_BASE_MSG_OPENDDS_MSG_VISION_IMAGE_OBJECTS_TRATIS_H_
#define HOLO_BASE_MSG_OPENDDS_MSG_VISION_IMAGE_OBJECTS_TRATIS_H_

#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/vision/image_objects.h>
#include <holo/vision/keypoint2.h>
#include <holo/vision/object.h>
#include <opendds_wrapper/traits.h>

#include <holo_base_msg/opendds_msg/geometry/point_traits.h>
#include <holo_base_msg/vision/ImageObjectsC.h>
#include <holo_base_msg/vision/ImageObjectsS.h>
#include <holo_base_msg/vision/ImageObjectsTypeSupportC.h>
#include <holo_base_msg/vision/ImageObjectsTypeSupportImpl.h>
#include <holo_base_msg/vision/ImageObjectsTypeSupportS.h>

namespace opendds_wrapper
{
// keypoint2

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::KeyPoint2f>
{
    using ValueType   = ::holo_base_msg::vision::KeyPoint2f;
    using MessageType = ::holo_base_msg::vision::KeyPoint2f;
};

template <>
struct DefaultMessageTraits<::holo::vision::KeyPoint2T<::holo::float32_t>>
{
    using ValueType   = ::holo::vision::KeyPoint2T<::holo::float32_t>;
    using MessageType = ::holo_base_msg::vision::KeyPoint2f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::KeyPoint2d>
{
    using ValueType   = ::holo_base_msg::vision::KeyPoint2d;
    using MessageType = ::holo_base_msg::vision::KeyPoint2d;
};

template <>
struct DefaultMessageTraits<::holo::vision::KeyPoint2T<::holo::float64_t>>
{
    using ValueType   = ::holo::vision::KeyPoint2T<::holo::float64_t>;
    using MessageType = ::holo_base_msg::vision::KeyPoint2d;
};

// Vision object keypoint2

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::ObjectKeyPoint2f>
{
    using ValueType   = ::holo_base_msg::vision::ObjectKeyPoint2f;
    using MessageType = ::holo_base_msg::vision::ObjectKeyPoint2f;
};

template <size_t PT_SIZE>
struct DefaultMessageTraits<::holo::vision::ObjectT<::holo::vision::KeyPoint2T<::holo::float32_t>, PT_SIZE>>
{
    using ValueType   = ::holo::vision::ObjectT<::holo::vision::KeyPoint2T<::holo::float32_t>, PT_SIZE>;
    using MessageType = ::holo_base_msg::vision::ObjectKeyPoint2f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::ObjectKeyPoint2d>
{
    using ValueType   = ::holo_base_msg::vision::ObjectKeyPoint2d;
    using MessageType = ::holo_base_msg::vision::ObjectKeyPoint2d;
};

template <size_t PT_SIZE>
struct DefaultMessageTraits<::holo::vision::ObjectT<::holo::vision::KeyPoint2T<::holo::float64_t>, PT_SIZE>>
{
    using ValueType   = ::holo::vision::ObjectT<::holo::vision::KeyPoint2T<::holo::float64_t>, PT_SIZE>;
    using MessageType = ::holo_base_msg::vision::ObjectKeyPoint2d;
};

// Vision object point2

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::ObjectPoint2f>
{
    using ValueType   = ::holo_base_msg::vision::ObjectPoint2f;
    using MessageType = ::holo_base_msg::vision::ObjectPoint2f;
};

template <size_t PT_SIZE>
struct DefaultMessageTraits<::holo::vision::ObjectT<::holo::geometry::Point2T<::holo::float32_t>, PT_SIZE>>
{
    using ValueType   = ::holo::vision::ObjectT<::holo::geometry::Point2T<::holo::float32_t>, PT_SIZE>;
    using MessageType = ::holo_base_msg::vision::ObjectPoint2f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::ObjectPoint2d>
{
    using ValueType   = ::holo_base_msg::vision::ObjectPoint2d;
    using MessageType = ::holo_base_msg::vision::ObjectPoint2d;
};

template <size_t PT_SIZE>
struct DefaultMessageTraits<::holo::vision::ObjectT<::holo::geometry::Point2T<::holo::float64_t>, PT_SIZE>>
{
    using ValueType   = ::holo::vision::ObjectT<::holo::geometry::Point2T<::holo::float64_t>, PT_SIZE>;
    using MessageType = ::holo_base_msg::vision::ObjectPoint2d;
};

// Vision object point3

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::ObjectPoint3f>
{
    using ValueType   = ::holo_base_msg::vision::ObjectPoint3f;
    using MessageType = ::holo_base_msg::vision::ObjectPoint3f;
};

template <size_t PT_SIZE>
struct DefaultMessageTraits<::holo::vision::ObjectT<::holo::geometry::Point3T<::holo::float32_t>, PT_SIZE>>
{
    using ValueType   = ::holo::vision::ObjectT<::holo::geometry::Point3T<::holo::float32_t>, PT_SIZE>;
    using MessageType = ::holo_base_msg::vision::ObjectPoint3f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::ObjectPoint3d>
{
    using ValueType   = ::holo_base_msg::vision::ObjectPoint3d;
    using MessageType = ::holo_base_msg::vision::ObjectPoint3d;
};

template <size_t PT_SIZE>
struct DefaultMessageTraits<::holo::vision::ObjectT<::holo::geometry::Point3T<::holo::float64_t>, PT_SIZE>>
{
    using ValueType   = ::holo::vision::ObjectT<::holo::geometry::Point3T<::holo::float64_t>, PT_SIZE>;
    using MessageType = ::holo_base_msg::vision::ObjectPoint3d;
};

// Vision ImageObjects KeyPoint2

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::ImageObjectsKeyPoint2f>
{
    using ValueType   = ::holo_base_msg::vision::ImageObjectsKeyPoint2f;
    using MessageType = ::holo_base_msg::vision::ImageObjectsKeyPoint2f;
};

template <size_t PT_SIZE, size_t OBJ_SIZE>
struct DefaultMessageTraits<::holo::vision::ImageObjectsT<
    ::holo::vision::ObjectT<::holo::vision::KeyPoint2T<::holo::float32_t>, PT_SIZE>, OBJ_SIZE>>
{
    using ValueType =
        ::holo::vision::ImageObjectsT<::holo::vision::ObjectT<::holo::vision::KeyPoint2T<::holo::float32_t>, PT_SIZE>,
                                      OBJ_SIZE>;
    using MessageType = ::holo_base_msg::vision::ImageObjectsKeyPoint2f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::ImageObjectsKeyPoint2d>
{
    using ValueType   = ::holo_base_msg::vision::ImageObjectsKeyPoint2d;
    using MessageType = ::holo_base_msg::vision::ImageObjectsKeyPoint2d;
};

template <size_t PT_SIZE, size_t OBJ_SIZE>
struct DefaultMessageTraits<::holo::vision::ImageObjectsT<
    ::holo::vision::ObjectT<::holo::vision::KeyPoint2T<::holo::float64_t>, PT_SIZE>, OBJ_SIZE>>
{
    using ValueType =
        ::holo::vision::ImageObjectsT<::holo::vision::ObjectT<::holo::vision::KeyPoint2T<::holo::float64_t>, PT_SIZE>,
                                      OBJ_SIZE>;
    using MessageType = ::holo_base_msg::vision::ImageObjectsKeyPoint2d;
};

// Vision ImageObjects Point2

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::ImageObjectsPoint2f>
{
    using ValueType   = ::holo_base_msg::vision::ImageObjectsPoint2f;
    using MessageType = ::holo_base_msg::vision::ImageObjectsPoint2f;
};

template <size_t PT_SIZE, size_t OBJ_SIZE>
struct DefaultMessageTraits<::holo::vision::ImageObjectsT<
    ::holo::vision::ObjectT<::holo::geometry::Point2T<::holo::float32_t>, PT_SIZE>, OBJ_SIZE>>
{
    using ValueType =
        ::holo::vision::ImageObjectsT<::holo::vision::ObjectT<::holo::geometry::Point2T<::holo::float32_t>, PT_SIZE>,
                                      OBJ_SIZE>;
    using MessageType = ::holo_base_msg::vision::ImageObjectsPoint2f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::ImageObjectsPoint2d>
{
    using ValueType   = ::holo_base_msg::vision::ImageObjectsPoint2d;
    using MessageType = ::holo_base_msg::vision::ImageObjectsPoint2d;
};

template <size_t PT_SIZE, size_t OBJ_SIZE>
struct DefaultMessageTraits<::holo::vision::ImageObjectsT<
    ::holo::vision::ObjectT<::holo::geometry::Point2T<::holo::float64_t>, PT_SIZE>, OBJ_SIZE>>
{
    using ValueType =
        ::holo::vision::ImageObjectsT<::holo::vision::ObjectT<::holo::geometry::Point2T<::holo::float64_t>, PT_SIZE>,
                                      OBJ_SIZE>;
    using MessageType = ::holo_base_msg::vision::ImageObjectsPoint2d;
};

// Vision ImageObjects Point3

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::ImageObjectsPoint3f>
{
    using ValueType   = ::holo_base_msg::vision::ImageObjectsPoint3f;
    using MessageType = ::holo_base_msg::vision::ImageObjectsPoint3f;
};

template <size_t PT_SIZE, size_t OBJ_SIZE>
struct DefaultMessageTraits<::holo::vision::ImageObjectsT<
    ::holo::vision::ObjectT<::holo::geometry::Point3T<::holo::float32_t>, PT_SIZE>, OBJ_SIZE>>
{
    using ValueType =
        ::holo::vision::ImageObjectsT<::holo::vision::ObjectT<::holo::geometry::Point3T<::holo::float32_t>, PT_SIZE>,
                                      OBJ_SIZE>;
    using MessageType = ::holo_base_msg::vision::ImageObjectsPoint3f;
};

template <>
struct DefaultMessageTraits<::holo_base_msg::vision::ImageObjectsPoint3d>
{
    using ValueType   = ::holo_base_msg::vision::ImageObjectsPoint3d;
    using MessageType = ::holo_base_msg::vision::ImageObjectsPoint3d;
};

template <size_t PT_SIZE, size_t OBJ_SIZE>
struct DefaultMessageTraits<::holo::vision::ImageObjectsT<
    ::holo::vision::ObjectT<::holo::geometry::Point3T<::holo::float64_t>, PT_SIZE>, OBJ_SIZE>>
{
    using ValueType =
        ::holo::vision::ImageObjectsT<::holo::vision::ObjectT<::holo::geometry::Point3T<::holo::float64_t>, PT_SIZE>,
                                      OBJ_SIZE>;
    using MessageType = ::holo_base_msg::vision::ImageObjectsPoint3d;
};

template <typename T>
struct DefaultConversionTraits<::holo::vision::KeyPoint2T<T>>
{
    using ValueType   = ::holo::vision::KeyPoint2T<T>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.Set(message.x, message.y);
        value.SetConfidence(message.confidence);
        value.SetVisibility(message.visibility);
    }

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.x          = value.GetX();
        message.y          = value.GetY();
        message.confidence = value.GetConfidence();
        message.visibility = value.IsVisible();
    }
};

template <typename PointType, size_t PT_SIZE>
struct DefaultConversionTraits<::holo::vision::ObjectT<PointType, PT_SIZE>>
{
    using ValueType   = ::holo::vision::ObjectT<PointType, PT_SIZE>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.resize(message.points.length());
        for (size_t i = 0U; i < message.points.length(); ++i)
        {
            DefaultConversionTraits<PointType>::Convert(message.points[i], value[i]);
        }
        value.SetCategory(::holo::common::Classification(message.category));
        value.SetConfidence(message.confidence);
    }

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.points.length(value.size());
        for (size_t i = 0U; i < value.size(); ++i)
        {
            DefaultConversionTraits<PointType>::Convert(value[i], message.points[i]);
        }
        message.category   = static_cast<uint32_t>(value.GetCategory());
        message.confidence = value.GetConfidence();
    }
};

template <typename Object, size_t OBJ_SIZE>
struct DefaultConversionTraits<::holo::vision::ImageObjectsT<Object, OBJ_SIZE>>
{
    using ValueType   = ::holo::vision::ImageObjectsT<Object, OBJ_SIZE>;
    using MessageType = typename DefaultMessageTraits<ValueType>::MessageType;

    static void Convert(MessageType const& message, ValueType& value)
    {
        value.SetTimestamp({message.stamp.sec, message.stamp.nsec});
        value.SetSensorId(static_cast<::holo::common::SensorId>(message.sensor_id));
        value.resize(message.objects.length());
        for (size_t i = 0U; i < message.objects.length(); ++i)
        {
            DefaultConversionTraits<Object>::Convert(message.objects[i], value[i]);
        }
    }

    static void Convert(ValueType const& value, MessageType& message)
    {
        message.stamp.sec  = value.GetTimestamp().GetSec();
        message.stamp.nsec = value.GetTimestamp().GetNsec();
        message.sensor_id  = static_cast<::holo_base_msg::common::SensorId>(value.GetSensorId());
        message.objects.length(value.size());
        for (size_t i = 0U; i < value.size(); ++i)
        {
            DefaultConversionTraits<Object>::Convert(value[i], message.objects[i]);
        }
    }
};

}  // namespace opendds_wrapper

#endif
