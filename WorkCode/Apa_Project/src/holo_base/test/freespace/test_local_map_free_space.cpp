/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_local_map_free_space.cpp
 * @brief This file test LocalMapFreeSpace.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-27
 */

#include <gtest/gtest.h>
#include <iostream>

#include <holo/freespace/local_map_free_space.h>

using namespace holo;
using holo::common::Timestamp;
using holo::common::Coordinate;

TEST(TestLocalMapFreeSpace, Constructor)
{
    Timestamp                              timestamp(1UL, 0UL);
    Coordinate                             coord(Coordinate::Utm6Coordinate(50U, false)); /* COORD_WORLD */
    LocalMapFreeSpace<float32_t>::Contour  exterior_contour;
    LocalMapFreeSpace<float32_t>::Contours interior_contours;

    for (size_t i = 0UL; i < 8UL; ++i)
    {
        exterior_contour.push_back(Point2f(float32_t(i), float32_t(i)));
    }

    interior_contours.push_back(exterior_contour);

    LocalMapFreeSpace<float32_t> fs;
    fs.SetTimestamp(timestamp);
    fs.SetCoordinate(coord);
    fs.SetExteriorContour(exterior_contour);
    fs.SetInteriorContours(interior_contours);

    ASSERT_EQ(fs.GetTimestamp(), timestamp);
    ASSERT_EQ(fs.GetCoordinate(), coord);
    ASSERT_EQ(fs.GetExteriorContour().size(), 8UL);
    ASSERT_EQ(fs.GetInteriorContours().size(), 1UL);

    LocalMapFreeSpace<float32_t>::Contours interior_contours_ret = fs.GetInteriorContours();
    LocalMapFreeSpace<float32_t>::Contour  exterior_contour_ret  = fs.GetExteriorContour();

    for (size_t i = 0UL; i < exterior_contour_ret.size(); ++i)
    {
        ASSERT_EQ(exterior_contour_ret[i], Point2f(float32_t(i), float32_t(i)));
        ASSERT_EQ(exterior_contour_ret[i], interior_contours_ret[0][i]);
    }

    // test right-value setter function
    fs.SetExteriorContour(std::move(exterior_contour));
    fs.SetInteriorContours(std::move(interior_contours));

    interior_contours_ret = fs.GetInteriorContours();
    exterior_contour_ret  = fs.GetExteriorContour();

    for (size_t i = 0UL; i < exterior_contour_ret.size(); ++i)
    {
        ASSERT_EQ(exterior_contour_ret[i], Point2f(float32_t(i), float32_t(i)));
        ASSERT_EQ(exterior_contour_ret[i], interior_contours_ret[0][i]);
    }

    // constructor with params
    LocalMapFreeSpace<float32_t> fs_with_params(timestamp, coord, exterior_contour, interior_contours);

    ASSERT_EQ(fs_with_params.GetTimestamp(), timestamp);
    ASSERT_EQ(fs_with_params.GetCoordinate(), coord);
    ASSERT_EQ(fs_with_params.GetExteriorContour().size(), 8UL);
    ASSERT_EQ(fs_with_params.GetInteriorContours().size(), 1UL);

    interior_contours_ret = fs_with_params.GetInteriorContours();
    exterior_contour_ret  = fs_with_params.GetExteriorContour();

    for (size_t i = 0UL; i < exterior_contour_ret.size(); ++i)
    {
        ASSERT_EQ(exterior_contour_ret[i], Point2f(float32_t(i), float32_t(i)));
        ASSERT_EQ(exterior_contour_ret[i], interior_contours_ret[0][i]);
    }

    // copy constructor
    LocalMapFreeSpace<float32_t> fs_copy(fs);

    ASSERT_EQ(fs_copy.GetTimestamp(), timestamp);
    ASSERT_EQ(fs_copy.GetCoordinate(), coord);
    ASSERT_EQ(fs_copy.GetExteriorContour().size(), 8UL);
    ASSERT_EQ(fs_copy.GetInteriorContours().size(), 1UL);

    interior_contours_ret = fs_copy.GetInteriorContours();
    exterior_contour_ret  = fs_copy.GetExteriorContour();

    for (size_t i = 0UL; i < exterior_contour_ret.size(); ++i)
    {
        ASSERT_EQ(exterior_contour_ret[i], Point2f(float32_t(i), float32_t(i)));
        ASSERT_EQ(exterior_contour_ret[i], interior_contours_ret[0][i]);
    }

    // move constructor
    LocalMapFreeSpace<float32_t> fs_move(std::move(fs_copy));

    ASSERT_EQ(fs_move.GetTimestamp(), timestamp);
    ASSERT_EQ(fs_move.GetCoordinate(), coord);
    ASSERT_EQ(fs_move.GetExteriorContour().size(), 8UL);
    ASSERT_EQ(fs_move.GetInteriorContours().size(), 1UL);

    interior_contours_ret = fs_move.GetInteriorContours();
    exterior_contour_ret  = fs_move.GetExteriorContour();

    for (size_t i = 0UL; i < exterior_contour_ret.size(); ++i)
    {
        ASSERT_EQ(exterior_contour_ret[i], Point2f(float32_t(i), float32_t(i)));
        ASSERT_EQ(exterior_contour_ret[i], interior_contours_ret[0][i]);
    }
}

TEST(TestLocalMapFreeSpace, ParamsConstructor)
{
    Timestamp                              timestamp(1UL, 0UL);
    Coordinate                             coord(Coordinate::Utm6Coordinate(50U, false)); /* COORD_WORLD */
    LocalMapFreeSpace<float32_t>::Contour  exterior_contour;
    LocalMapFreeSpace<float32_t>::Contours interior_contours;

    for (size_t i = 0UL; i < 8UL; ++i)
    {
        exterior_contour.push_back(Point2f(float32_t(i), float32_t(i)));
    }

    interior_contours.push_back(exterior_contour);

    LocalMapFreeSpace<float32_t> fs0(timestamp, coord, exterior_contour, interior_contours);
    LocalMapFreeSpace<float32_t> fs1;

    // copy assignment
    fs1.operator=(fs0);

    ASSERT_EQ(fs0.GetTimestamp(), timestamp);
    ASSERT_EQ(fs0.GetCoordinate(), coord);
    ASSERT_EQ(fs0.GetExteriorContour().size(), 8UL);
    ASSERT_EQ(fs0.GetInteriorContours().size(), 1UL);

    ASSERT_EQ(fs1.GetTimestamp(), timestamp);
    ASSERT_EQ(fs1.GetCoordinate(), coord);
    ASSERT_EQ(fs1.GetExteriorContour().size(), 8UL);
    ASSERT_EQ(fs1.GetInteriorContours().size(), 1UL);

    LocalMapFreeSpace<float32_t>::Contours interior_contours_ret0 = fs0.GetInteriorContours();
    LocalMapFreeSpace<float32_t>::Contour  exterior_contour_ret0  = fs0.GetExteriorContour();

    for (size_t i = 0UL; i < exterior_contour_ret0.size(); ++i)
    {
        ASSERT_EQ(exterior_contour_ret0[i], Point2f(float32_t(i), float32_t(i)));
        ASSERT_EQ(exterior_contour_ret0[i], interior_contours_ret0[0][i]);
    }

    LocalMapFreeSpace<float32_t>::Contours interior_contours_ret1 = fs1.GetInteriorContours();
    LocalMapFreeSpace<float32_t>::Contour  exterior_contour_ret1  = fs1.GetExteriorContour();

    for (size_t i = 0UL; i < exterior_contour_ret1.size(); ++i)
    {
        ASSERT_EQ(exterior_contour_ret1[i], Point2f(float32_t(i), float32_t(i)));
        ASSERT_EQ(exterior_contour_ret1[i], interior_contours_ret1[0][i]);
    }

    // self copy assignment
    fs1.operator=(fs1);

    interior_contours_ret1 = fs1.GetInteriorContours();
    exterior_contour_ret1  = fs1.GetExteriorContour();

    ASSERT_EQ(fs1.GetTimestamp(), timestamp);
    ASSERT_EQ(fs1.GetCoordinate(), coord);
    ASSERT_EQ(fs1.GetExteriorContour().size(), 8UL);
    ASSERT_EQ(fs1.GetInteriorContours().size(), 1UL);

    for (size_t i = 0UL; i < exterior_contour_ret1.size(); ++i)
    {
        ASSERT_EQ(exterior_contour_ret1[i], Point2f(float32_t(i), float32_t(i)));
        ASSERT_EQ(exterior_contour_ret1[i], interior_contours_ret1[0][i]);
    }

    // self move assignment
    fs1.operator=(std::move(fs1));

    interior_contours_ret1 = fs1.GetInteriorContours();
    exterior_contour_ret1  = fs1.GetExteriorContour();

    ASSERT_EQ(fs1.GetTimestamp(), timestamp);
    ASSERT_EQ(fs1.GetCoordinate(), coord);
    ASSERT_EQ(fs1.GetExteriorContour().size(), 8UL);
    ASSERT_EQ(fs1.GetInteriorContours().size(), 1UL);

    for (size_t i = 0UL; i < exterior_contour_ret1.size(); ++i)
    {
        ASSERT_EQ(exterior_contour_ret1[i], Point2f(float32_t(i), float32_t(i)));
        ASSERT_EQ(exterior_contour_ret1[i], interior_contours_ret1[0][i]);
    }

    // move assignment
    LocalMapFreeSpace<float32_t> fs2;

    fs2.operator=(std::move(fs1));

    ASSERT_EQ(fs2.GetTimestamp(), timestamp);
    ASSERT_EQ(fs2.GetCoordinate(), coord);
    ASSERT_EQ(fs2.GetExteriorContour().size(), 8UL);
    ASSERT_EQ(fs2.GetInteriorContours().size(), 1UL);

    LocalMapFreeSpace<float32_t>::Contours interior_contours_ret2 = fs2.GetInteriorContours();
    LocalMapFreeSpace<float32_t>::Contour  exterior_contour_ret2  = fs2.GetExteriorContour();

    for (size_t i = 0UL; i < exterior_contour_ret2.size(); ++i)
    {
        ASSERT_EQ(exterior_contour_ret2[i], Point2f(float32_t(i), float32_t(i)));
        ASSERT_EQ(exterior_contour_ret2[i], interior_contours_ret2[0][i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}