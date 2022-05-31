/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_imu_meta_struct.cpp
 * @brief unit test for imu meta struct
 * @author zhouhuishuang@holomatic.com
 * @date 2021-01-28
 */

#include <gtest/gtest.h>
#include <holo/common/imu.h>
#include <holo/metadata/common/imu_type_description.h>
#include <holo/metadata/meta_struct.h>
#include <holo/utils/buffer.h>

TEST(ImuTMetaStruct, Decode_float32)
{
    holo::common::ImuT<holo::float32_t> imu;
    imu.SetTimestamp(holo::common::Timestamp(10,20));
    imu.SetCoordinate(holo::common::Coordinate(10));
    imu.SetStatus(holo::common::ImuT<holo::float32_t>::Status::GYROXERROR);
    imu.SetAngularVelocity(1.0f, 2.0f, 3.0f);
    imu.SetLinearAcceleration(5.0f, 6.0f, 7.0f);

    holo::utils::FixedSizeBuffer<1024> buf;
    holo::utils::Serializer<>          ser(buf);
    ser << imu;

    std::shared_ptr<holo::metadata::MetaStruct> pmeta =
        holo::metadata::CreateMetaStruct(holo::metadata::TypeDescriptionResolver<holo::common::ImuT<holo::float32_t>>::Get());
    pmeta->Decode(buf.GetData(), buf.GetSize(), 0U);
    std::cout << pmeta->PrintToString() << std::endl;
}

TEST(ImuTMetaStruct, Decode_float64)
{
    holo::common::ImuT<holo::float64_t> imu;
    imu.SetTimestamp(holo::common::Timestamp(10,20));
    imu.SetCoordinate(holo::common::Coordinate(10));
    imu.SetStatus(holo::common::ImuT<holo::float64_t>::Status::GYROXERROR);
    imu.SetAngularVelocity(1.0f, 2.0f, 3.0f);
    imu.SetLinearAcceleration(5.0f, 6.0f, 7.0f);

    holo::utils::FixedSizeBuffer<1024> buf;
    holo::utils::Serializer<>          ser(buf);
    ser << imu;

    std::shared_ptr<holo::metadata::MetaStruct> pmeta =
        holo::metadata::CreateMetaStruct(holo::metadata::TypeDescriptionResolver<holo::common::ImuT<holo::float64_t>>::Get());
    pmeta->Decode(buf.GetData(), buf.GetSize(), 0U);
    std::cout << pmeta->PrintToString() << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
