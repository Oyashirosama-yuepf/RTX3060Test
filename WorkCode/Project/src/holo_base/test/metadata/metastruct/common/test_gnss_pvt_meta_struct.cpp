/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_gnss_pvt_meta_struct.cpp
 * @brief unit test for gnss_pvt meta struct
 * @author zhouhuishuang@holomatic.com
 * @date 2021-01-28
 */

#include <gtest/gtest.h>
#include <holo/common/gnss_pvt.h>
#include <holo/metadata/common/gnss_pvt_type_description.h>
#include <holo/metadata/meta_struct.h>
#include <holo/utils/buffer.h>

TEST(AppStatusMetaStruct, Decode)
{
    holo::common::GnssPvt pvt;

    pvt.SetPosition(1, 2, 3);
    pvt.SetVelocity(4, 5, 6);
    pvt.SetPositionCov(7, 8, 9);
    pvt.SetVelocityCov(10, 11, 12);

    holo::utils::FixedSizeBuffer<1024> buf;
    holo::utils::Serializer<>          ser(buf);
    ser << pvt;

    std::shared_ptr<holo::metadata::MetaStruct> pmeta =
        holo::metadata::CreateMetaStruct(holo::metadata::TypeDescriptionResolver<holo::common::GnssPvt>::Get());
    pmeta->Decode(buf.GetData(), buf.GetSize(), 0U);
    std::cout << pmeta->PrintToString() << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
