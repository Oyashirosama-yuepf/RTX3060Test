/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_classification.cpp
 * @brief This file test Classification.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-10-28
 */

#include <gtest/gtest.h>
#include <holo/common/classification.h>
using namespace holo::common;

////////////////////////////////////////////////////////////////////////////////
TEST(ClassificationTest, Constructor)
{
    // Error initialization case with exception
    // Classification cls(9, 15);  // Invalid main type code for Classification
    // Classification cls(1, 15);  // Invalid sub type code for Classification

    // Invalid main type for Classification
    // Classification::MainType main = static_cast<Classification::MainType>(9);
    // Classification           cls(main, Classification::SubType::CAR);

    // Invalid setting
    // Classification::MainType main = static_cast<Classification::MainType>(9);
    // Classification::SubType sub = static_cast<Classification::SubType>(15);
    // Classification          cls;
    // cls.SetMainType(main);  // Invalid main type for Classification
    // cls.SetSubType(sub);    // Invalid sub type for Classification

    Classification cls_with_type(Classification::MainType::VEHICLE, Classification::SubType::CAR);
    Classification cls_with_code(0x02U, 0x0200U);
    ASSERT_EQ(cls_with_type.GetMainType(), Classification::MainType::VEHICLE);
    ASSERT_EQ(cls_with_type.GetSubType(), Classification::SubType::CAR);
    ASSERT_EQ(cls_with_type.GetMainType(), cls_with_code.GetMainType());
    ASSERT_EQ(cls_with_type.GetSubType(), cls_with_code.GetSubType());
}

TEST(ClassificationTest, GetSerializedSize)
{
    Classification cls_with_code(0x02U, 0x0200U);
    ;
    ASSERT_EQ(4, cls_with_code.GetSerializedSize<4U>());
    ASSERT_EQ(4, cls_with_code.GetSerializedSize<8U>());
}

TEST(ClassificationTest, UnderlyingMainType)
{
    Classification cls_with_code(0x02U, 0x0200U);
    uint16_t       num = cls_with_code.UnderlyingMainType();
}

TEST(ClassificationTest, UnderlyingSubType)
{
    Classification cls_with_code(0x02U, 0x0200U);
    uint16_t       num = cls_with_code.UnderlyingSubType();
}

TEST(ClassificationTest, Underlying)
{
    Classification cls_with_code(0x02U, 0x0200U);
    uint32_t       num = cls_with_code.Underlying();
}

TEST(ClassificationTest, ToString)
{
    Classification cls_with_code(0x02U, 0x0200U);
    std::string    str = cls_with_code.ToString();
}

TEST(ClassificationTest, operator)
{
    Classification cls_with_code(0x02U, 0x0200U);
    std::cout << cls_with_code;
}

TEST(ClassificationTest, SerializeAndDeserialize)
{
    Classification classification_input(0x02U, 0x0200U);
    Classification classification_output(0x02U, 0x0200U);

    uint8_t                           buffer[1024];
    holo::serialization::Serializer<> serializer(buffer, 1024);
    serializer << classification_input;
    ASSERT_EQ(classification_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> classification_output;

    ASSERT_EQ(classification_input.GetMainType(), classification_output.GetMainType());
    ASSERT_EQ(classification_input.GetSubType(), classification_output.GetSubType());
    ASSERT_EQ(classification_input.GetMainType(), classification_output.GetMainType());
    ASSERT_EQ(classification_input.GetSubType(), classification_output.GetSubType());
}

TEST(ClassificationTest, IsValidMainTypeAndIsValidSubType)
{
    try
    {
        Classification classification(0xffff, 0xffff);
    }
    catch (...)
    {
    }

    try
    {
        Classification classification(0x02U, 0xffff);
    }
    catch (...)
    {
    }
}

TEST(ClassificationTest, ToMainTypeStringAndToSubTypeString)
{
    Classification classification;
    try
    {
        classification = 0xffffffff;
        classification.ToString();
    }
    catch (...)
    {
    }
    try
    {
        classification = 0x0002ffff;
        classification.ToString();
    }
    catch (...)
    {
    }
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
