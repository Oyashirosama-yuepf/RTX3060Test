/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_vehicle_body_state_meta_struct.cpp
 * @brief unit test for vehicle_body_state meta struct
 * @author zhouhuishuang@holomatic.com
 * @date 2021-01-28
 */

#include <gtest/gtest.h>
#include <holo/common/vehicle_body_state.h>
#include <holo/metadata/common/vehicle_body_state_type_description.h>
#include <holo/metadata/meta_struct.h>
#include <holo/utils/buffer.h>

TEST(AppStatusMetaStruct, Decode)
{
    holo::common::VehicleBodyState    vbs;

    vbs.SetTimestamp(holo::common::Timestamp(10,20));
    vbs.SetFrontLeftTirePressure(101.0);
    vbs.SetFrontRightTirePressure(102.0);
    vbs.SetRearLeftTirePressure(103.0);
    vbs.SetRearRightTirePressure(104.0);
    vbs.SetDoorState(true, true, true, true, true, true);

    holo::utils::FixedSizeBuffer<1024> buf;
    holo::utils::Serializer<>          ser(buf);
    ser << vbs;

    std::shared_ptr<holo::metadata::MetaStruct> pmeta =
        holo::metadata::CreateMetaStruct(holo::metadata::TypeDescriptionResolver<holo::common::VehicleBodyState>::Get());
    pmeta->Decode(buf.GetData(), buf.GetSize(), 0U);
    std::cout << pmeta->PrintToString() << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
