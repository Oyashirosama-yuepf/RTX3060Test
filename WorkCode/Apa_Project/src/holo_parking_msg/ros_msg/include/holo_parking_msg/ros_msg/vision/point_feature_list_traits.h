/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_feature_list_traits.h
 * @brief This header file defines PointFeaturePtrListTraits.
 * @author lifeng(lifeng@holomaitc.com)
 * @date 2021-01-08
 */

#ifndef HOLO_PARKING_MSG_ROS_MSG_VISION_POINT_FEATURELIST_TRAITS_H_
#define HOLO_PARKING_MSG_ROS_MSG_VISION_POINT_FEATURELIST_TRAITS_H_

#include <holo/parking/vision/point_feature_list.h>

#include <ros_wrapper/traits.h>

#include <holo_parking_msg/PointFeaturef.h>
#include <holo_parking_msg/PointFeaturefList.h>

namespace ros_wrapper
{
/* PointFeature traits */

template <>
struct DefaultMessageTraits<::holo_parking_msg::PointFeaturef>
{
    using ValueType   = ::holo_parking_msg::PointFeaturef;
    using MessageType = ::holo_parking_msg::PointFeaturef;
};

template <>
struct DefaultMessageTraits<::holo::parking::vision::PointFeaturef>
{
    using ValueType   = ::holo::parking::vision::PointFeaturef;
    using MessageType = ::holo_parking_msg::PointFeaturef;
};

template <>
struct DefaultConversionTraits<::holo::parking::vision::PointFeaturef>
{
    using ValueType   = ::holo::parking::vision::PointFeaturef;
    using MessageType = ::holo_parking_msg::PointFeaturef;

    static void Convert(ValueType const& value, MessageType& message);
    static void Convert(MessageType const& message, ValueType& value);
};

/* PointFeaturedList traits */

template <>
struct DefaultMessageTraits<::holo_parking_msg::PointFeaturefList>
{
    using ValueType   = ::holo_parking_msg::PointFeaturefList;
    using MessageType = ::holo_parking_msg::PointFeaturefList;
};

template <>
struct DefaultMessageTraits<::holo::parking::vision::PointFeaturePtrListf>
{
    using ValueType   = ::holo::parking::vision::PointFeaturePtrListf;
    using MessageType = ::holo_parking_msg::PointFeaturefList;
};

template <>
struct DefaultConversionTraits<::holo::parking::vision::PointFeaturePtrListf>
{
    using ValueType   = ::holo::parking::vision::PointFeaturePtrListf;
    using MessageType = ::holo_parking_msg::PointFeaturefList;

    static void Convert(ValueType const& value, MessageType& message)
    {
        // timestamp
        message.stamp.sec  = value.GetTimestamp().GetSec();
        message.stamp.nsec = value.GetTimestamp().GetNsec();

        // sensor_id
        message.sensor_id = value.GetSensorId();

        // point feature list
        message.point_feature_list.resize(value.GetPointFeatureList().size());

        for (size_t i = 0; i < value.GetPointFeatureList().size(); ++i)
        {
            if (value.GetPointFeatureList()[i] == nullptr)
            {
                throw std::runtime_error("ERROR: Invalid nullptr point feature list in convertor!");
            }
            ros_wrapper::DefaultConversionTraits<::holo::parking::vision::PointFeaturef>::Convert(
                *value.GetPointFeatureList()[i], message.point_feature_list[i]);
        }
    }

    static void Convert(MessageType const& message, ValueType& value)
    {
        // timestamp_
        value.SetTimestamp(::holo::Timestamp{message.stamp.sec, message.stamp.nsec});

        // sensor_id_
        value.SetSensorId(message.sensor_id);

        // point feature list
        auto& output_point_feature_list = value.GetPointFeatureList();
        output_point_feature_list.reserve(message.point_feature_list.size());

        for (size_t i = 0; i < message.point_feature_list.size(); ++i)
        {
            ::holo::parking::vision::PointFeaturef tmp_point_feature;
            ros_wrapper::DefaultConversionTraits<::holo::parking::vision::PointFeaturef>::Convert(
                message.point_feature_list[i], tmp_point_feature);
            output_point_feature_list.emplace_back(
                std::make_shared<::holo::parking::vision::PointFeaturef>(tmp_point_feature));
        }
    }
};

}  // namespace ros_wrapper

#endif
