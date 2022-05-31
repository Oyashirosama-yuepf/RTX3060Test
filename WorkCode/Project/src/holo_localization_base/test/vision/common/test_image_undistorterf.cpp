/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_image_undistortion.cpp
 * @brief test image undistortiond
 * @author duyanwei@holomatic.com
 * @date 2019-12-13
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/common/image_undistorter.h>
#include <holo/localization/vision/common/mask.h>

using namespace holo::localization;
using ImageUndistorterType = ImageUndistorterT<holo::common::details::CameraIntrinsicBaseT<holo::float32_t>>;

#include "../../fixture/test_image_undistorter.h"

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
