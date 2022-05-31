/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_object.cpp
 * @brief Uint test for vision/object.h.
 * @author liufangyuan(liufangyuan@holomaitc.com)
 * @date "2020-07-30"
 */

#include <cmath>

#include <gtest/gtest.h>
#include <stdio.h>

#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/vision/keypoint2.h>
#include <holo/vision/object.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionObjectKeyPoint2f, DefaultConstructor)
{
    using PointType  = ::holo::vision::KeyPoint2T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      pt0;
    const ::holo::float32_t              confidence = 0.0f;
    const ::holo::common::Classification category;

    ObjectType object0;

    ASSERT_EQ(object0.size(), 0u);
    ASSERT_EQ(object0.GetCategory(), category);
    ASSERT_EQ(object0.GetConfidence(), confidence);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionObjectKeyPoint2f, NumberFunction)
{
    using PointType  = ::holo::vision::KeyPoint2T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      point_0(1.0f, 2.0f, 0.9f, true);
    const PointType                      point_1(1.0f, 2.0f, 0.9f, false);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::Classification category(0x02u, 0x0001u);

    ObjectType object0;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);

    // check results
    ASSERT_EQ(object0.GetCategory(), category);
    ASSERT_EQ(object0.GetConfidence(), confidence);
    ASSERT_EQ(object0[0u], point_0);
    ASSERT_EQ(object0[1u], point_1);
    ASSERT_EQ(object0[0u].IsVisible(), true);
    ASSERT_EQ(object0[1u].IsVisible(), false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionObjectKeyPoint2f, Serialize_DeSerialize_4Byte)
{
    using PointType  = ::holo::vision::KeyPoint2T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      point_0(1.0f, 2.0f, 0.9f, true);
    const PointType                      point_1(1.0f, 2.0f, 0.9f, false);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::Classification category(0x02u, 0x0001u);

    ObjectType object0, object1;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);

    static const uint32_t                     SERIALIZED_BUF_LEN = 2048u;
    uint8_t                                   buffer[SERIALIZED_BUF_LEN];
    holo::serialization::Serializer<true, 4u> serializer(buffer, 2048);
    object0.Serialize(serializer);
    holo::serialization::Deserializer<true, 4u> Deserializer(buffer, serializer.GetSize());
    object1.Deserialize(Deserializer);

    ASSERT_EQ(object0.GetCategory(), object1.GetCategory());
    ASSERT_EQ(object0.GetConfidence(), object1.GetConfidence());
    ASSERT_EQ(object0.size(), 2u);
    ASSERT_EQ(object0.size(), object1.size());
    ASSERT_EQ(object0[0u].GetX(), point_0[0u]);
    ASSERT_EQ(object0[0u].GetX(), object1[0u].GetX());
    ASSERT_EQ(object0[1u].IsVisible(), false);
    ASSERT_EQ(object0[1u].IsVisible(), object1[1u].IsVisible());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionObjectKeyPoint2f, Serialize_DeSerialize_8Byte)
{
    using PointType  = ::holo::vision::KeyPoint2T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      point_0(1.0f, 2.0f, 0.9f, true);
    const PointType                      point_1(1.0f, 2.0f, 0.9f, false);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::Classification category(0x02U, 0x0001U);

    ObjectType object0;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);

    static const uint32_t                     SERIALIZED_BUF_LEN = 2048U;
    uint8_t                                   buffer[SERIALIZED_BUF_LEN];
    holo::serialization::Serializer<true, 8u> serializer(buffer, SERIALIZED_BUF_LEN);
    object0.Serialize(serializer);

    ObjectType                                  object1;
    holo::serialization::Deserializer<true, 8u> Deserializer(buffer, serializer.GetSize());
    object1.Deserialize(Deserializer);

    ASSERT_EQ(object0.GetCategory(), object1.GetCategory());
    ASSERT_EQ(object0.GetConfidence(), object1.GetConfidence());
    ASSERT_EQ(object0.size(), 2u);
    ASSERT_EQ(object0.size(), object1.size());
    ASSERT_EQ(object0[0u].GetX(), point_0[0u]);
    ASSERT_EQ(object0[0u].GetX(), object1[0u].GetX());
    ASSERT_EQ(object0[1u].IsVisible(), false);
    ASSERT_EQ(object0[1u].IsVisible(), object1[1u].IsVisible());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionObjectPoint2f, DefaultConstructor)
{
    using PointType  = ::holo::geometry::Point2T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      pt0;
    const ::holo::float32_t              confidence = 0.0f;
    const ::holo::common::Classification category;

    ObjectType object0;

    ASSERT_EQ(object0.size(), 0u);
    ASSERT_EQ(object0.GetCategory(), category);
    ASSERT_EQ(object0.GetConfidence(), confidence);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionObjectPoint2f, NumberFunction)
{
    using PointType  = ::holo::geometry::Point2T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      point_0(1.0f, 2.0f);
    const PointType                      point_1(1.0f, 2.0f);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::Classification category(0x02u, 0x0001u);

    ObjectType object0;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);

    // check results
    ASSERT_EQ(object0.GetCategory(), category);
    ASSERT_EQ(object0.GetConfidence(), confidence);
    ASSERT_EQ(object0[0u], point_0);
    ASSERT_EQ(object0[1u], point_1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionObjectPoint2f, Serialize_DeSerialize_4Byte)
{
    using PointType  = ::holo::geometry::Point2T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      point_0(1.0f, 2.0f);
    const PointType                      point_1(1.0f, 2.0f);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::Classification category(0x02u, 0x0001u);

    ObjectType object0;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);

    static const uint32_t                     SERIALIZED_BUF_LEN = 2048u;
    uint8_t                                   buffer[SERIALIZED_BUF_LEN];
    holo::serialization::Serializer<true, 4u> serializer(buffer, SERIALIZED_BUF_LEN);
    object0.Serialize(serializer);

    ObjectType                                  object1;
    holo::serialization::Deserializer<true, 4u> Deserializer(buffer, serializer.GetSize());
    object1.Deserialize(Deserializer);

    ASSERT_EQ(object0.GetCategory(), object1.GetCategory());
    ASSERT_EQ(object0.GetConfidence(), object1.GetConfidence());
    ASSERT_EQ(object0.size(), 2u);
    ASSERT_EQ(object0.size(), object1.size());
    ASSERT_EQ(object0[0u].GetX(), point_0[0u]);
    ASSERT_EQ(object0[0u].GetX(), object1[0u].GetX());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionObjectPoint2f, Serialize_DeSerialize_8Byte)
{
    using PointType  = ::holo::geometry::Point2T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      point_0(1.0f, 2.0f);
    const PointType                      point_1(1.0f, 2.0f);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::Classification category(0x02u, 0x0001u);

    ObjectType object0;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);

    static const uint32_t                     SERIALIZED_BUF_LEN = 2048u;
    uint8_t                                   buffer[SERIALIZED_BUF_LEN];
    holo::serialization::Serializer<true, 8u> serializer(buffer, SERIALIZED_BUF_LEN);
    object0.Serialize(serializer);

    ObjectType                                  object1;
    holo::serialization::Deserializer<true, 8u> Deserializer(buffer, serializer.GetSize());
    object1.Deserialize(Deserializer);

    ASSERT_EQ(object0.GetCategory(), object1.GetCategory());
    ASSERT_EQ(object0.GetConfidence(), object1.GetConfidence());
    ASSERT_EQ(object0.size(), 2u);
    ASSERT_EQ(object0.size(), object1.size());
    ASSERT_EQ(object0[0u].GetX(), point_0[0u]);
    ASSERT_EQ(object0[0u].GetX(), object1[0u].GetX());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionObjectPoint3f, DefaultConstructor)
{
    using PointType  = ::holo::geometry::Point3T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      pt0;
    const ::holo::float32_t              confidence = 0.0f;
    const ::holo::common::Classification category;

    ObjectType object0;

    ASSERT_EQ(object0.size(), 0u);
    ASSERT_EQ(object0.GetCategory(), category);
    ASSERT_EQ(object0.GetConfidence(), confidence);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionObjectPoint3f, NumberFunction)
{
    using PointType  = ::holo::geometry::Point3T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      point_0(1.0f, 2.0f, 3.0f);
    const PointType                      point_1(1.0f, 2.0f, 3.0f);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::Classification category(0x02u, 0x0001u);

    ObjectType object0;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);

    // check results
    ASSERT_EQ(object0.GetCategory(), category);
    ASSERT_EQ(object0.GetConfidence(), confidence);
    ASSERT_EQ(object0[0u], point_0);
    ASSERT_EQ(object0[1u], point_1);
}

TEST(VisionObjectPoint3f, GetSerializedSize)
{
    using PointType  = ::holo::geometry::Point3T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;
    ObjectType object0;

    ASSERT_EQ(12, object0.GetSerializedSize<4U>());
    ASSERT_EQ(16, object0.GetSerializedSize<8U>());
}

TEST(VisionObjectPoint3f, SerializeAndDeserialize)
{
    using PointType  = ::holo::geometry::Point3T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      point_0(1.0f, 2.0f, 3.0f);
    const PointType                      point_1(1.0f, 2.0f, 3.0f);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::Classification category(0x02u, 0x0001u);

    ObjectType object0, object1;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);

    uint8_t                           buffer[2048U];
    holo::serialization::Serializer<> serializer(buffer, 2048);
    serializer << object0;
    ASSERT_EQ(object0.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> object1;

    ASSERT_EQ(object0.GetCategory(), object1.GetCategory());
    ASSERT_EQ(object0.GetConfidence(), object1.GetConfidence());
    ASSERT_EQ(object0.size(), 2u);
    ASSERT_EQ(object0.size(), object1.size());
    ASSERT_EQ(object0[0u].GetX(), point_0[0u]);
    ASSERT_EQ(object0[0u].GetX(), object1[0u].GetX());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionObjectPoint3f, Serialize_DeSerialize_8Byte)
{
    using PointType  = ::holo::geometry::Point3T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      point_0(1.0f, 2.0f, 3.0f);
    const PointType                      point_1(1.0f, 2.0f, 3.0f);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::Classification category(0x02u, 0x0001u);

    ObjectType object0;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);

    static const uint32_t                     SERIALIZED_BUF_LEN = 2048u;
    uint8_t                                   buffer[SERIALIZED_BUF_LEN];
    holo::serialization::Serializer<true, 8u> serializer(buffer, SERIALIZED_BUF_LEN);
    object0.Serialize(serializer);

    ObjectType                                  object1;
    holo::serialization::Deserializer<true, 8u> Deserializer(buffer, serializer.GetSize());
    object1.Deserialize(Deserializer);

    ASSERT_EQ(object0.GetCategory(), object1.GetCategory());
    ASSERT_EQ(object0.GetConfidence(), object1.GetConfidence());
    ASSERT_EQ(object0.size(), 2u);
    ASSERT_EQ(object0.size(), object1.size());
    ASSERT_EQ(object0[0u].GetX(), point_0[0u]);
    ASSERT_EQ(object0[0u].GetX(), object1[0u].GetX());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VisionObjectPoint3f, Serialize_DeSerialize_4Byte)
{
    using PointType  = ::holo::geometry::Point3T<::holo::float32_t>;
    using ObjectType = ::holo::vision::ObjectT<PointType>;

    const PointType                      point_0(1.0f, 2.0f, 3.0f);
    const PointType                      point_1(1.0f, 2.0f, 3.0f);
    const ::holo::float32_t              confidence(0.9f);
    const ::holo::common::Classification category(0x02u, 0x0001u);

    ObjectType object0;
    object0.SetCategory(category);
    object0.SetConfidence(confidence);
    object0.emplace_back(point_0);
    object0.emplace_back(point_1);

    static const uint32_t                     SERIALIZED_BUF_LEN = 2048u;
    uint8_t                                   buffer[SERIALIZED_BUF_LEN];
    holo::serialization::Serializer<true, 4u> serializer(buffer, SERIALIZED_BUF_LEN);
    object0.Serialize(serializer);

    ObjectType                                  object1;
    holo::serialization::Deserializer<true, 4u> Deserializer(buffer, serializer.GetSize());
    object1.Deserialize(Deserializer);

    ASSERT_EQ(object0.GetCategory(), object1.GetCategory());
    ASSERT_EQ(object0.GetConfidence(), object1.GetConfidence());
    ASSERT_EQ(object0.size(), 2u);
    ASSERT_EQ(object0.size(), object1.size());
    ASSERT_EQ(object0[0u].GetX(), point_0[0u]);
    ASSERT_EQ(object0[0u].GetX(), object1[0u].GetX());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
