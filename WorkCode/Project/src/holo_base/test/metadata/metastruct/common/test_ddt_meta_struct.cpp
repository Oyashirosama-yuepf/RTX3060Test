/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_ddt_meta_struct.cpp
 * @brief unit test for ddt meta struct
 * @author zhouhuishuang@holomatic.com
 * @date 2021-01-28
 */

#include <gtest/gtest.h>
#include <holo/common/ddt.h>
#include <holo/metadata/common/ddt_type_description.h>
#include <holo/metadata/meta_struct.h>
#include <holo/utils/buffer.h>

TEST(AppStatusMetaStruct, Decode)
{
    holo::common::DdtStates<4> ddts;
    ddts.SetTimestamp(holo::common::Timestamp(30U, 50U));
    ddts[2].Enable();
    ddts[2].SetAlarm(135U);
    ddts[2].SetPredictedDistance(80);
    ddts[2].EnablePredictedDistance();
    ddts[2].EnablePredictedTime();
    ddts[2].SetPredictedTime(30);

    ddts[5].Enable();
    ddts[5].SetAlarm(135U);
    ddts[5].SetPredictedDistance(100);
    ddts[5].EnablePredictedTime();
    ddts[5].EnablePredictedTime();
    ddts[5].SetPredictedTime(50);

    holo::utils::FixedSizeBuffer<1024> buf;
    holo::utils::Serializer<>          ser(buf);
    ser << ddts;

    std::shared_ptr<holo::metadata::MetaStruct> pmeta =
        holo::metadata::CreateMetaStruct(holo::metadata::TypeDescriptionResolver<holo::common::DdtStates<4U>>::Get());
    pmeta->Decode(buf.GetData(), buf.GetSize(), 0U);
    std::cout << pmeta->PrintToString() << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
