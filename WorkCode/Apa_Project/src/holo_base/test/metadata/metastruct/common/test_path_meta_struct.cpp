/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_path_meta_struct.cpp
 * @brief unit test for path meta struct
 * @author zhouhuishuang@holomatic.com
 * @date 2021-01-28
 */

#include <gtest/gtest.h>
#include <holo/common/path.h>
#include <holo/metadata/common/path_type_description.h>
#include <holo/metadata/meta_struct.h>
#include <holo/utils/buffer.h>

TEST(AppStatusMetaStruct, Decode)
{
    holo::common::PathT<holo::float32_t> path;
    path = {{0, 0, 0,}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}, {4, 1, 1}, {5, 1, 1}};
    path.SetTimestamp({1, 2});
    path.SetCoordinate(holo::common::Coordinate::UtmCoordinate(50, false));
    for (size_t i = 0; i < path.size(); ++i)
    {
        path[i].SetTheta(i);
        path[i].SetCurvature(i);
        path[i].SetSpeed(i);
        path[i].SetAcceleration(i);
    }

    holo::utils::FixedSizeBuffer<1024> buf;
    holo::utils::Serializer<>          ser(buf);
    ser << path;

    std::shared_ptr<holo::metadata::MetaStruct> pmeta =
        holo::metadata::CreateMetaStruct(holo::metadata::TypeDescriptionResolver<holo::common::PathT<holo::float32_t>>::Get());
    pmeta->Decode(buf.GetData(), buf.GetSize(), 0U);
    std::cout << pmeta->PrintToString() << std::endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
