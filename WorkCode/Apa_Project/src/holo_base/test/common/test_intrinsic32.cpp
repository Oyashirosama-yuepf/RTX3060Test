/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @brief unit test for intrinsic class
 * @author lichao@holomatic.com
 * @date Sep 18, 2019
 */

#include <gtest/gtest.h>
#include <holo/common/intrinsic.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorDefaultTest, NormalInput)
{
    /* Create a Intrinsic by default constructor */
    const holo::Intrinsicf intrinsic;

    /* Test default constructor */
    ASSERT_TRUE(0x00000000 == intrinsic.GetCoordinate());
    ASSERT_TRUE(holo::CameraModel::UNKNOWN == intrinsic.GetModel());
    ASSERT_TRUE(holo::Intrinsicf::Vector2(1u, 1u) == intrinsic.GetDimension());
    ASSERT_TRUE(holo::Intrinsicf::Matrix3::Identity() == intrinsic.GetK());
    ASSERT_TRUE(holo::Intrinsicf::Vector8::Zero() == intrinsic.GetD());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorTest, NormalInput)
{
    /* Generate expected values */
    const holo::common::Coordinate expected_coord(
        0x13060177);  // VEHICLE_CAMERA_CAMERA_ENTRON_F001R_FRONT_MIDDLE_CENTER
    const holo::CameraModel         expected_model = holo::CameraModel::PINHOLE;
    const holo::Intrinsicf::Vector2 expected_size  = holo::Intrinsicf::Vector2(1920u, 1080u);
    const holo::Intrinsicf::Matrix3 expected_K     = holo::Intrinsicf::Matrix3::Identity();
    const holo::Intrinsicf::Vector8 expected_D     = holo::Intrinsicf::Vector8::Zero();

    /* Create a Intrinsic by default constructor */
    const holo::Intrinsicf intrinsic(expected_coord, expected_model, expected_size, expected_K, expected_D);

    /* Test default constructor */
    ASSERT_TRUE(expected_coord == intrinsic.GetCoordinate());
    ASSERT_TRUE(expected_model == intrinsic.GetModel());
    ASSERT_TRUE(expected_size == intrinsic.GetDimension());
    ASSERT_TRUE(expected_K == intrinsic.GetK());
    ASSERT_TRUE(expected_D == intrinsic.GetD());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Intrinsicf32Test, GetSerializedSize)
{
    holo::Intrinsicf intrinsic;
    ASSERT_EQ(68, intrinsic.GetSerializedSize<4U>());
    ASSERT_EQ(72, intrinsic.GetSerializedSize<8U>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Intrinsicf32Test, SerializeAndDeserialize)
{
    srand(time(0));
    holo::Intrinsicf input_intrinsic_f, output_intrinsic_f;

    const holo::common::Coordinate  coord(holo::common::Coordinate::BODY);
    const holo::CameraModel         model = holo::CameraModel::PINHOLE;
    const holo::Intrinsicf::Vector2 size(1920u, 1080u);
    const holo::Intrinsicf::Matrix3 K(0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9);
    const holo::Intrinsicf::Vector8 D(0.8, -0.7, 0.6, -0.5, 0.4, -0.3, 0.2, -0.1);
    input_intrinsic_f = holo::Intrinsicf(coord, model, size, K, D);

    uint8_t buffer[1280];
    holo::serialization::Serializer<>          serializer(buffer, 1280);
    serializer << input_intrinsic_f;
    ASSERT_EQ(input_intrinsic_f.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> output_intrinsic_f;

    ASSERT_EQ(input_intrinsic_f.GetCoordinate(), output_intrinsic_f.GetCoordinate());
    ASSERT_EQ(input_intrinsic_f.GetDimension(), output_intrinsic_f.GetDimension());
    ASSERT_EQ(input_intrinsic_f.GetK(), output_intrinsic_f.GetK());
    ASSERT_EQ(input_intrinsic_f.GetD(), output_intrinsic_f.GetD());
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
