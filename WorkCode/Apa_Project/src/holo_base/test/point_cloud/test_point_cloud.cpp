/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_point_type.cpp
 * @brief Unit test for point cloud point types.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-11-02
 */

#include <gtest/gtest.h>

#include <holo/core/types.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/point_cloud/point_cloud.h>

using PointType = holo::geometry::Point3T<holo::float32_t>;
using PcdType   = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(), sizeof(PointType)>;

/**
 * @brief Test PointCloudBaseT default constructor
 */
TEST(PointCloudBase, DefaultConstructor)
{
    PcdType pcd;
    ASSERT_EQ(0, pcd.size());
    ASSERT_EQ((holo::common::Timestamp{}), pcd.GetTimestamp());
    ASSERT_EQ((holo::common::Coordinate{}), pcd.GetCoordinate());
    ASSERT_EQ((PcdType::PoseType{}), pcd.GetPose());
    ASSERT_FALSE(pcd.IsDense());
}

/**
 * @brief Test PointCloudBaseT::operator()(size_t idx)
 */
TEST(PointCloudBase, OperatorBrace_1)
{
    PcdType pcd = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    ASSERT_EQ((PointType{1, 1, 1}), pcd(0));
    ASSERT_EQ((PointType{2, 2, 2}), pcd(1));
    ASSERT_EQ((PointType{3, 3, 3}), pcd(2));
}

/**
 * @brief Test PointCloudBaseT::operator()(size_t idx) const
 */
TEST(PointCloudBase, OperatorBrace_2)
{
    PcdType const pcd = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    ASSERT_EQ((PointType{1, 1, 1}), pcd(0));
    ASSERT_EQ((PointType{2, 2, 2}), pcd(1));
    ASSERT_EQ((PointType{3, 3, 3}), pcd(2));
}

/**
 * @brief Test PointCloudBaseT::GetTimestamp()/SetTimestamp(value)
 */
TEST(PointCloudBase, SetGetTimestamp)
{
    PcdType pcd = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    ASSERT_EQ((holo::common::Timestamp{}), pcd.GetTimestamp());
    pcd.SetTimestamp(holo::common::Timestamp{1, 1});
    ASSERT_EQ((holo::common::Timestamp{1, 1}), pcd.GetTimestamp());
}

/**
 * @brief Test PointCloudBaseT::GetCoordinate()/SetCoordinate(value)
 */
TEST(PointCloudBase, SetGetPose)
{
    PcdType pcd = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    ASSERT_EQ(PcdType::PoseType{}, pcd.GetPose());

    PcdType::PoseType pose;
    pose.SetTranslation({1, 2, 3});
    pcd.SetPose(pose);
    ASSERT_EQ(pose, pcd.GetPose());

    pcd.GetPose().SetTranslation({3, 4, 5});
    pose.SetTranslation({3, 4, 5});
    ASSERT_EQ(pose, pcd.GetPose());
}

/**
 * @brief Test PointCloudBaseT::IsDense()/SetDense(value)
 */
TEST(PointCloudBase, IsDenseSetDense)
{
    PcdType pcd = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    ASSERT_FALSE(pcd.IsDense());
    pcd.SetDense(true);
    ASSERT_TRUE(pcd.IsDense());
}

/**
 * @brief Test PointCloudBaseT::GetSerializedSize
 */
TEST(PointCloudBase, GetSerializedSize)
{
    PcdType pcd = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};

    ASSERT_EQ(104U, pcd.GetSerializedSize<4U>());
    ASSERT_EQ(128U, pcd.GetSerializedSize<8U>());
}

/**
 * @brief Test PointCloudBaseT::Serialize and Deserialize
 */
TEST(PointCloudBase, SerializeAndDeserialize)
{
    PcdType pcd_input = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    PcdType pcd_output;

    uint8_t buffer[1280];
    holo::serialization::Serializer<> serializer(buffer, 1280);
    serializer << pcd_input;
    ASSERT_EQ(pcd_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> pcd_output;

    ASSERT_EQ(pcd_input.size(), pcd_output.size());
    ASSERT_EQ(pcd_input.GetTimestamp(), pcd_output.GetTimestamp());
    ASSERT_EQ(pcd_input.GetCoordinate(), pcd_output.GetCoordinate());
    ASSERT_EQ(pcd_input.GetPose(), pcd_output.GetPose());
    ASSERT_EQ(pcd_input.IsDense(), pcd_output.IsDense());
}

using UnorganizedPcdType =
    holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(), sizeof(PointType), holo::point_cloud::UnorganizedLayoutTag>;

/**
 * @brief Test unorganized PointCloudT::GetWidth
 */
TEST(PointCloudUnorganized, GetWidth)
{
    UnorganizedPcdType pcd;
    ASSERT_EQ(0U, pcd.GetWidth());
}

/**
 * @brief Test unorganized PointCloudT::GetHeight
 */
TEST(PointCloudUnorganized, GetHeight)
{
    UnorganizedPcdType pcd;
    ASSERT_EQ(1U, pcd.GetHeight());
}

using OrganizedPcdType =
    holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(), 16U, holo::point_cloud::OrganizedLayoutTag>;
/**
 * @brief Test organized PointCloudT::operator(row, column)
 */
TEST(PointCloudOrganized, OperatorBrace_1)
{
    OrganizedPcdType pcd = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    ASSERT_EQ((PointType{1, 1 ,1}), pcd(0, 0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd(0, 1));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd(0, 2));

    pcd.SetDimension(1, 3);
    ASSERT_EQ((PointType{1, 1 ,1}), pcd(0, 0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd(1, 0));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd(2, 0));

    pcd.SetDimension(2, 2);
    ASSERT_EQ((PointType{1, 1 ,1}), pcd(0, 0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd(0, 1));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd(1, 0));
}

/**
 * @brief Test organized PointCloudT::operator(row, column) const
 */
TEST(PointCloudOrganized, OperatorBrace_2)
{
    OrganizedPcdType base = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    OrganizedPcdType const& pcd = base;
    ASSERT_EQ((PointType{1, 1 ,1}), pcd(0, 0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd(0, 1));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd(0, 2));

    base.SetDimension(1, 3);
    ASSERT_EQ((PointType{1, 1 ,1}), pcd(0, 0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd(1, 0));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd(2, 0));

    base.SetDimension(2, 2);
    ASSERT_EQ((PointType{1, 1 ,1}), pcd(0, 0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd(0, 1));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd(1, 0));
}

/**
 * @brief Test organized PointCloudT::at(row, column)
 */
TEST(PointCloudOrganized, at_1)
{
    OrganizedPcdType pcd = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    ASSERT_EQ((PointType{1, 1 ,1}), pcd.at(0, 0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd.at(0, 1));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd.at(0, 2));
    EXPECT_THROW(pcd.at(1, 0), std::out_of_range);
    EXPECT_THROW(pcd.at(0, 3), std::out_of_range);

    pcd.SetDimension(1, 3);
    ASSERT_EQ((PointType{1, 1 ,1}), pcd.at(0, 0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd.at(1, 0));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd.at(2, 0));
    EXPECT_THROW(pcd.at(0, 1), std::out_of_range);
    EXPECT_THROW(pcd.at(4, 0), std::out_of_range);

    pcd.SetDimension(2, 2);
    ASSERT_EQ((PointType{1, 1 ,1}), pcd.at(0, 0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd.at(0, 1));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd.at(1, 0));
    EXPECT_THROW(pcd.at(1, 1), std::out_of_range);
}

/**
 * @brief Test organized PointCloudT::at(row, column) const
 */
TEST(PointCloudOrganized, at_2)
{
    OrganizedPcdType base = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    OrganizedPcdType const& pcd = base;
    ASSERT_EQ((PointType{1, 1 ,1}), pcd.at(0, 0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd.at(0, 1));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd.at(0, 2));
    EXPECT_THROW(pcd.at(1, 0), std::out_of_range);
    EXPECT_THROW(pcd.at(0, 3), std::out_of_range);

    base.SetDimension(1, 3);
    ASSERT_EQ((PointType{1, 1 ,1}), pcd.at(0, 0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd.at(1, 0));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd.at(2, 0));
    EXPECT_THROW(pcd.at(0, 1), std::out_of_range);
    EXPECT_THROW(pcd.at(4, 0), std::out_of_range);

    base.SetDimension(2, 2);
    ASSERT_EQ((PointType{1, 1 ,1}), pcd.at(0, 0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd.at(0, 1));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd.at(1, 0));
    EXPECT_THROW(pcd.at(1, 1), std::out_of_range);
}

/**
 * @brief Test organized PointCloudT::at(idx)
 */
TEST(PointCloudOrganized, at_3)
{
    OrganizedPcdType pcd = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    ASSERT_EQ((PointType{1, 1 ,1}), pcd.at(0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd.at(1));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd.at(2));
    EXPECT_THROW(pcd.at(3), std::out_of_range);
}

/**
 * @brief Test organized PointCloudT::at(idx) const
 */
TEST(PointCloudOrganized, at_4)
{
    OrganizedPcdType base = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    OrganizedPcdType const& pcd = base;
    ASSERT_EQ((PointType{1, 1 ,1}), pcd.at(0));
    ASSERT_EQ((PointType{2, 2 ,2}), pcd.at(1));
    ASSERT_EQ((PointType{3, 3 ,3}), pcd.at(2));
    EXPECT_THROW(pcd.at(3), std::out_of_range);
}

/**
 * @brief Test organized PointCloudT::GetWidth
 */
TEST(PointCloudOrganized, GetWidth)
{
    OrganizedPcdType pcd;
    ASSERT_EQ(0U, pcd.GetWidth());
    pcd.SetDimension(3);
    ASSERT_EQ(3U, pcd.GetWidth());

    pcd.SetDimension(10, 10);
    ASSERT_EQ(10U, pcd.GetWidth());
}

/**
 * @brief Test organized PointCloudT::GetHeight
 */
TEST(PointCloudOrganized, GetHeight)
{
    OrganizedPcdType pcd;
    ASSERT_EQ(1U, pcd.GetHeight());
    pcd.SetDimension(10, 10);
    ASSERT_EQ(10U, pcd.GetHeight());
}

/**
 * @brief Test organized PointCloudT::SetDimension
 */
TEST(PointCloudOrganized, SetDimension)
{
    OrganizedPcdType pcd;
    pcd.SetDimension(10U);
    ASSERT_EQ(10U, pcd.GetWidth());
    ASSERT_EQ(1U, pcd.GetHeight());

    pcd.SetDimension(20U, 20U);
    ASSERT_EQ(20U, pcd.GetWidth());
    ASSERT_EQ(20U, pcd.GetHeight());

    pcd.SetDimension(0U);
    ASSERT_EQ(0U, pcd.GetWidth());
    ASSERT_EQ(1U, pcd.GetHeight());
}

/**
 * @brief Test organized PointCloudT::GetSerializedSize
 */
TEST(PointCloudOrganized, GetSerializedSize)
{
    OrganizedPcdType pcd;

    ASSERT_EQ(76U, pcd.GetSerializedSize<4U>());
    ASSERT_EQ(88U, pcd.GetSerializedSize<8U>());
}

/**
 * @brief Test organized PointCloudT::Serialize and Deserialize
 */
TEST(PointCloudOrganized, SerializeAndDeserialize)
{
    OrganizedPcdType pcd_input = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    OrganizedPcdType pcd_output;

    pcd_input.SetDimension(2U);

    uint8_t buffer[2560];
    holo::serialization::Serializer<> serializer(buffer, 2560);
    serializer << pcd_input;
    ASSERT_EQ(pcd_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> pcd_output;

    ASSERT_EQ(pcd_input.size(), pcd_output.size());
    ASSERT_EQ(pcd_input.GetWidth(), pcd_output.GetWidth());
    ASSERT_EQ(pcd_input.GetHeight(), pcd_output.GetHeight());
    ASSERT_EQ(pcd_input(0, 0), pcd_output(0, 0));
    ASSERT_EQ(pcd_input(0, 1), pcd_output(0, 1));
    ASSERT_EQ(pcd_input(0, 2), pcd_output(0, 2));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
