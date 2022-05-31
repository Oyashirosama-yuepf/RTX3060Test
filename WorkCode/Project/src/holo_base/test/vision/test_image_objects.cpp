/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_image_object.cpp
 * @brief Uint test for image_objects.h.
 * @author liufangyuan(liufangyuan@holomaitc.com)
 * @date "2020-07-30"
 */

#include <cmath>

#include <gtest/gtest.h>
#include <stdio.h>

#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/vision/image_objects.h>
#include <holo/vision/keypoint2.h>
#include <holo/vision/object.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionImageObjectsKeyPoint2f, DefaultConstructor)
{
    using PointType       = ::holo::vision::KeyPoint2T<::holo::float32_t>;
    using ObjectType      = ::holo::vision::ObjectT<PointType>;
    using ImageObjectType = ::holo::vision::ImageObjectsT<ObjectType>;

    const ::holo::common::SensorId  sensor_id;
    const ::holo::common::Timestamp timestamp;

    // Create image object
    ImageObjectType image_object0;
    ASSERT_EQ(image_object0.size(), 0u);
    ASSERT_EQ(image_object0.GetSensorId(), sensor_id);
    ASSERT_EQ(image_object0.GetTimestamp(), timestamp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionImageObjectsKeyPoint2f, NumberFunction)
{
    using PointType       = ::holo::vision::KeyPoint2T<::holo::float32_t>;
    using ObjectType      = ::holo::vision::ObjectT<PointType>;
    using ImageObjectType = ::holo::vision::ImageObjectsT<ObjectType>;

    const PointType                      point_0(1.0f, 2.0f, 0.9f, true);
    const PointType                      point_1(1.0f, 2.0f, 0.9f, false);
    const ::holo::common::Classification category(0x02u, 0x0001u);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::SensorId       sensor_id(1u);
    const ::holo::common::Timestamp      timestamp(100u, 200u);

    // Create object
    ObjectType object0;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);
    ASSERT_EQ(object0.size(), 2u);
    ASSERT_EQ(object0.GetCategory(), category);
    ASSERT_EQ(object0.GetConfidence(), confidence);

    // Create image object
    ImageObjectType image_object0;
    image_object0.SetTimestamp(timestamp);
    image_object0.SetSensorId(sensor_id);
    image_object0.emplace_back(object0);
    image_object0.emplace_back(object0);
    ASSERT_EQ(image_object0.size(), 2u);
    ASSERT_EQ(image_object0.GetSensorId(), sensor_id);
    ASSERT_EQ(image_object0.GetTimestamp(), timestamp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionImageObjectsPoint2f, DefaultConstructor)
{
    using PointType       = ::holo::geometry::Point2T<::holo::float32_t>;
    using ObjectType      = ::holo::vision::ObjectT<PointType>;
    using ImageObjectType = ::holo::vision::ImageObjectsT<ObjectType>;

    const ::holo::common::SensorId  sensor_id;
    const ::holo::common::Timestamp timestamp;

    // Create image object
    ImageObjectType image_object0;
    ASSERT_EQ(image_object0.size(), 0u);
    ASSERT_EQ(image_object0.GetSensorId(), sensor_id);
    ASSERT_EQ(image_object0.GetTimestamp(), timestamp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionImageObjectsPoint2f, NumberFunction)
{
    using PointType       = ::holo::geometry::Point2T<::holo::float32_t>;
    using ObjectType      = ::holo::vision::ObjectT<PointType>;
    using ImageObjectType = ::holo::vision::ImageObjectsT<ObjectType>;

    const PointType                      point_0(1.0f, 2.0f);
    const PointType                      point_1(1.0f, 2.0f);
    const ::holo::common::Classification category(0x02u, 0x0001u);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::SensorId       sensor_id(1u);
    const ::holo::common::Timestamp      timestamp(100u, 200u);

    // Create object
    ObjectType object0;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);
    ASSERT_EQ(object0.size(), 2u);
    ASSERT_EQ(object0.GetCategory(), category);
    ASSERT_EQ(object0.GetConfidence(), confidence);

    // Create image object
    ImageObjectType image_object0;
    image_object0.SetTimestamp(timestamp);
    image_object0.SetSensorId(sensor_id);
    image_object0.emplace_back(object0);
    image_object0.emplace_back(object0);
    ASSERT_EQ(image_object0.size(), 2u);
    ASSERT_EQ(image_object0.GetSensorId(), sensor_id);
    ASSERT_EQ(image_object0.GetTimestamp(), timestamp);
}

TEST(VisionImageObjectsPoint2f, GetSerializedSize)
{
    using PointType       = ::holo::geometry::Point2T<::holo::float32_t>;
    using ObjectType      = ::holo::vision::ObjectT<PointType>;
    using ImageObjectType = ::holo::vision::ImageObjectsT<ObjectType>;
    ImageObjectType image_object0;

    ASSERT_EQ(16, image_object0.GetSerializedSize<4U>());
    ASSERT_EQ(16, image_object0.GetSerializedSize<8U>());
}

TEST(VisionImageObjectsPoint2f, SerializeAndDeserialize)
{
    using PointType       = ::holo::geometry::Point2T<::holo::float32_t>;
    using ObjectType      = ::holo::vision::ObjectT<PointType>;
    using ImageObjectType = ::holo::vision::ImageObjectsT<ObjectType>;

    const PointType                      point_0(1.0f, 2.0f);
    const PointType                      point_1(1.0f, 2.0f);
    const ::holo::common::Classification category(0x02u, 0x0001u);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::SensorId       sensor_id(1u);
    const ::holo::common::Timestamp      timestamp(100u, 200u);

    ObjectType object0;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);

    ImageObjectType image_object0, image_object1;
    image_object0.SetTimestamp(timestamp);
    image_object0.SetSensorId(sensor_id);
    image_object0.emplace_back(object0);
    image_object0.emplace_back(object0);
    ASSERT_EQ(image_object0.size(), 2u);
    ASSERT_EQ(image_object0.GetSensorId(), sensor_id);
    ASSERT_EQ(image_object0.GetTimestamp(), timestamp);

    uint8_t                           buffer[8192];
    holo::serialization::Serializer<> serializer(buffer, 8192);
    serializer << image_object0;
    ASSERT_EQ(image_object0.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> image_object1;

    ASSERT_EQ(image_object0.GetSensorId(), image_object1.GetSensorId());
    ASSERT_EQ(image_object0.GetTimestamp(), image_object1.GetTimestamp());
    ASSERT_EQ(image_object0.size(), 2u);
    ASSERT_EQ(image_object0.size(), image_object1.size());
    ASSERT_EQ(image_object0[0u], image_object1[0u]);
    ASSERT_EQ(image_object0[1u], image_object1[1u]);
    ASSERT_EQ(image_object1[0u].GetCategory(), category);
    ASSERT_EQ(image_object1[1u].GetCategory(), category);
    ASSERT_EQ(image_object1[0u].GetConfidence(), confidence);
    ASSERT_EQ(image_object1[1u].GetConfidence(), confidence);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionImageObjectsPoint3f, DefaultConstructor)
{
    using PointType       = ::holo::geometry::Point3T<::holo::float32_t>;
    using ObjectType      = ::holo::vision::ObjectT<PointType>;
    using ImageObjectType = ::holo::vision::ImageObjectsT<ObjectType>;

    const ::holo::common::SensorId  sensor_id;
    const ::holo::common::Timestamp timestamp;

    // Create image object
    ImageObjectType image_object0;
    ASSERT_EQ(image_object0.size(), 0u);
    ASSERT_EQ(image_object0.GetSensorId(), sensor_id);
    ASSERT_EQ(image_object0.GetTimestamp(), timestamp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionImageObjectsPoint3f, NumberFunction)
{
    using PointType       = ::holo::geometry::Point3T<::holo::float32_t>;
    using ObjectType      = ::holo::vision::ObjectT<PointType>;
    using ImageObjectType = ::holo::vision::ImageObjectsT<ObjectType>;

    const PointType                      point_0(1.0f, 2.0f, 3.0f);
    const PointType                      point_1(1.0f, 2.0f, 3.0f);
    const ::holo::common::Classification category(0x02u, 0x0001u);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::SensorId       sensor_id(1u);
    const ::holo::common::Timestamp      timestamp(100u, 200u);

    // Create object
    ObjectType object0;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);
    ASSERT_EQ(object0.size(), 2u);
    ASSERT_EQ(object0.GetCategory(), category);
    ASSERT_EQ(object0.GetConfidence(), confidence);

    // Create image object
    ImageObjectType image_object0;
    image_object0.SetTimestamp(timestamp);
    image_object0.SetSensorId(sensor_id);
    image_object0.emplace_back(object0);
    image_object0.emplace_back(object0);
    ASSERT_EQ(image_object0.size(), 2u);
    ASSERT_EQ(image_object0.GetSensorId(), sensor_id);
    ASSERT_EQ(image_object0.GetTimestamp(), timestamp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
