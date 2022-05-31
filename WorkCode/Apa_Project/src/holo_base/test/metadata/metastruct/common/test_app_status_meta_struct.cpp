/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_app_status_meta_struct.cpp
 * @brief unit test for app status meta struct
 * @author zhangjiannan@holomatic.com
 * @date 2021-01-12
 */

#include <gtest/gtest.h>
#include <holo/common/app_status.h>
#include <holo/metadata/common/app_status_type_description.h>
#include <holo/metadata/meta_struct.h>
#include <holo/utils/buffer.h>

TEST(AppStatusMetaStruct, Decode)
{
    holo::common::AppStatus status = {1, 2, 3, 4, 5, 6};
    status.SetNodeId(100);
    status.SetTimestamp({10, 20});

    holo::utils::FixedSizeBuffer<1024> buf;
    holo::utils::Serializer<>          ser(buf);
    ser << status;

    std::shared_ptr<holo::metadata::MetaStruct> pmeta =
        holo::metadata::CreateMetaStruct(holo::metadata::TypeDescriptionResolver<holo::common::AppStatus>::Get());
    pmeta->Decode(buf.GetData(), buf.GetSize(), 0U);
    std::cout << pmeta->PrintToString() << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
