/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_navstate.h
 * @brief test for navstatef
 * @author lichao@holomatic.com
 * @date Oct 08, 2019
 */

#include <gtest/gtest.h>
#include <holo/localization/common/navstate.h>

using NavstateType                 = holo::localization::Navstatef;
NavstateType::ScalarType tolerance = 1e-6;
#include "../fixture/test_navstate.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
