/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_local_map_free_space_v2.cpp
 * @brief LocalMapFreeSpaceV2 unit test.
 * @author lisong(lisong@holomaitc.com)
 * @date 2019-12-20
 */

#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include <holo/freespace/local_map_free_space_v2.h>

using FSP = holo::LocalMapFreeSpaceV2;
using Coordinate = holo::common::Coordinate;

TEST(TestSegmentInfo, TestConstructor)
{
    FSP::SegmentInfo segmentinfo_a;
    ASSERT_EQ(segmentinfo_a.start_index, 0UL);
    ASSERT_EQ(segmentinfo_a.end_index, 0UL);
    ASSERT_EQ(segmentinfo_a.segment_type, FSP::SegmentType::UNKNOWN);

    FSP::SegmentInfo segmentinfo_b(1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER);
    ASSERT_EQ(segmentinfo_b.start_index, 1UL);
    ASSERT_EQ(segmentinfo_b.end_index, 2UL);
    ASSERT_EQ(segmentinfo_b.segment_type, FSP::SegmentType::TRAFFIC_BARRIER);

    FSP::SegmentInfo segmentinfo_c(segmentinfo_b);
    ASSERT_EQ(segmentinfo_c.start_index, segmentinfo_b.start_index);
    ASSERT_EQ(segmentinfo_c.end_index, segmentinfo_b.end_index);
    ASSERT_EQ(segmentinfo_c.segment_type, segmentinfo_b.segment_type);
}

TEST(TestSegmentInfo, TestEqualToOperator)
{
    FSP::SegmentInfo segmentinfo_a;
    FSP::SegmentInfo segmentinfo_b;
    ASSERT_TRUE(segmentinfo_a == segmentinfo_a);
    ASSERT_TRUE(segmentinfo_a == segmentinfo_b);
    
    FSP::SegmentInfo segmentinfo_c(1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER);
    ASSERT_FALSE(segmentinfo_a == segmentinfo_c);
}

TEST(TestSegmentInfo, TestNotEqualToOperator)
{
    FSP::SegmentInfo segmentinfo_a;
    FSP::SegmentInfo segmentinfo_b;
    ASSERT_FALSE(segmentinfo_a != segmentinfo_b);
    
    FSP::SegmentInfo segmentinfo_c(1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER);
    ASSERT_EQ(segmentinfo_a != segmentinfo_c, true);

    EXPECT_FALSE(operator!=(segmentinfo_a, segmentinfo_b));
}

TEST(TestSegmentInfo, TestAssignOperator)
{
    FSP::SegmentInfo segmentinfo_a;
    FSP::SegmentInfo segmentinfo_b(1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER);
    segmentinfo_a = segmentinfo_b;

    ASSERT_EQ(segmentinfo_a, segmentinfo_b);
    ASSERT_EQ(segmentinfo_a, segmentinfo_a);
}

TEST(TestFreeSpacePolygon, TestConstructor)
{
    FSP::FreeSpacePolygon  freespacepolygon_a;
    ASSERT_TRUE(freespacepolygon_a.exterior_ring.empty());
    ASSERT_TRUE(freespacepolygon_a.interior_rings.empty());
    ASSERT_TRUE(freespacepolygon_a.polygon_info.empty());

    FSP::LinearRing exterior_ring{{0L,0L,0L},{3L,0L,0L},{3L,3L,0L},{0L,3L,0L}};
    FSP::LinearRing interior_ring{{1L,1L,0L},{1L,2L,0L},{2L,2L,0L},{2L,1L,0L}};
    FSP::LinearRings interior_rings{interior_ring};
    FSP::RingInfo exterior_ring_info{
        {0UL,1UL,FSP::SegmentType::TRIVIAL},
        {1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER},
        {2UL,3UL,FSP::SegmentType::TRIVIAL},
        {3UL,0UL,FSP::SegmentType::TRAFFIC_BARRIER}
    };
    FSP::RingInfo interior_ring_info{{0UL,0UL,FSP::SegmentType::TRIVIAL}};
    std::vector<FSP::RingInfo> polygon_info{exterior_ring_info,interior_ring_info};

    FSP::FreeSpacePolygon  freespacepolygon_b(exterior_ring,interior_rings,polygon_info);
    ASSERT_EQ(freespacepolygon_b.exterior_ring,exterior_ring);
    ASSERT_EQ(freespacepolygon_b.interior_rings,interior_rings);
    ASSERT_EQ(freespacepolygon_b.polygon_info,polygon_info);

    FSP::FreeSpacePolygon  freespacepolygon_c(freespacepolygon_b);
    ASSERT_EQ(freespacepolygon_c.exterior_ring,freespacepolygon_b.exterior_ring);
    ASSERT_EQ(freespacepolygon_c.interior_rings,freespacepolygon_b.interior_rings);
    ASSERT_EQ(freespacepolygon_c.polygon_info,freespacepolygon_b.polygon_info);

    FSP::FreeSpacePolygon freespacepolygon_d(std::move(freespacepolygon_b));
    ASSERT_EQ(freespacepolygon_d.exterior_ring,freespacepolygon_c.exterior_ring);
    ASSERT_EQ(freespacepolygon_d.interior_rings,freespacepolygon_c.interior_rings);
    ASSERT_EQ(freespacepolygon_d.polygon_info,freespacepolygon_c.polygon_info);
}

TEST(TestFreeSpacePolygon, TestEqualToOperator)
{
    FSP::FreeSpacePolygon  freespacepolygon_a;
    FSP::FreeSpacePolygon  freespacepolygon_b;

    ASSERT_TRUE(freespacepolygon_a == freespacepolygon_b);
    ASSERT_TRUE(freespacepolygon_a == freespacepolygon_a);
    ASSERT_TRUE(operator==(freespacepolygon_a, freespacepolygon_a));

    FSP::LinearRing exterior_ring{{0L,0L,0L},{3L,0L,0L},{3L,3L,0L},{0L,3L,0L}};
    FSP::LinearRing interior_ring{{1L,1L,0L},{1L,2L,0L},{2L,2L,0L},{2L,1L,0L}};
    FSP::LinearRings interior_rings{interior_ring};
    FSP::RingInfo exterior_ring_info{
        {0UL,1UL,FSP::SegmentType::TRIVIAL},
        {1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER},
        {2UL,3UL,FSP::SegmentType::TRIVIAL},
        {3UL,0UL,FSP::SegmentType::TRAFFIC_BARRIER}
    };
    FSP::RingInfo interior_ring_info{{0UL,0UL,FSP::SegmentType::TRIVIAL}};
    std::vector<FSP::RingInfo> polygon_info{exterior_ring_info,interior_ring_info};

    FSP::FreeSpacePolygon  freespacepolygon_c(exterior_ring,interior_rings,polygon_info);

    ASSERT_FALSE(freespacepolygon_a == freespacepolygon_c);
}

TEST(TestFreeSpacePolygon, TestNotEqualToOperator)
{
    FSP::FreeSpacePolygon  freespacepolygon_a;
    FSP::FreeSpacePolygon  freespacepolygon_b;

    ASSERT_FALSE(freespacepolygon_a != freespacepolygon_b);

    FSP::LinearRing exterior_ring{{0L,0L,0L},{3L,0L,0L},{3L,3L,0L},{0L,3L,0L}};
    FSP::LinearRing interior_ring{{1L,1L,0L},{1L,2L,0L},{2L,2L,0L},{2L,1L,0L}};
    FSP::LinearRings interior_rings{interior_ring};
    FSP::RingInfo exterior_ring_info{
        {0UL,1UL,FSP::SegmentType::TRIVIAL},
        {1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER},
        {2UL,3UL,FSP::SegmentType::TRIVIAL},
        {3UL,0UL,FSP::SegmentType::TRAFFIC_BARRIER}
    };
    FSP::RingInfo interior_ring_info{{0UL,0UL,FSP::SegmentType::TRIVIAL}};
    std::vector<FSP::RingInfo> polygon_info{exterior_ring_info,interior_ring_info};

    FSP::FreeSpacePolygon  freespacepolygon_c(exterior_ring,interior_rings,polygon_info);

    ASSERT_TRUE(freespacepolygon_a != freespacepolygon_c);
    ASSERT_TRUE(operator!=(freespacepolygon_a, freespacepolygon_c));
}

TEST(TestFreeSpacePolygon, TestAssignOperator)
{
    FSP::FreeSpacePolygon  freespacepolygon_a;
    FSP::LinearRing exterior_ring{{0L,0L,0L},{3L,0L,0L},{3L,3L,0L},{0L,3L,0L}};
    FSP::LinearRing interior_ring{{1L,1L,0L},{1L,2L,0L},{2L,2L,0L},{2L,1L,0L}};
    FSP::LinearRings interior_rings{interior_ring};
    FSP::RingInfo exterior_ring_info{
        {0UL,1UL,FSP::SegmentType::TRIVIAL},
        {1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER},
        {2UL,3UL,FSP::SegmentType::TRIVIAL},
        {3UL,0UL,FSP::SegmentType::TRAFFIC_BARRIER}
    };
    FSP::RingInfo interior_ring_info{{0UL,0UL,FSP::SegmentType::TRIVIAL}};
    std::vector<FSP::RingInfo> polygon_info{exterior_ring_info,interior_ring_info};

    FSP::FreeSpacePolygon  freespacepolygon_b(exterior_ring,interior_rings,polygon_info);

    freespacepolygon_a = freespacepolygon_b;
    ASSERT_EQ(freespacepolygon_a,freespacepolygon_b);

    FSP::FreeSpacePolygon  freespacepolygon_c;
    freespacepolygon_c = std::move(freespacepolygon_b);
    ASSERT_EQ(freespacepolygon_c,freespacepolygon_a);
}

TEST(TestLocalMapFreeSpaceV2, TestConstructor)
{
    holo::common::Timestamp timestamp;
    Coordinate coordinate = holo::common::Coordinate(Coordinate::UNKNOWN); // COORD_UNKNOWN
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_a;
    ASSERT_EQ(localmapfreespacev2_a.GetTimestamp(),timestamp);
    ASSERT_EQ(localmapfreespacev2_a.GetCoordinate(),coordinate);
    ASSERT_TRUE(localmapfreespacev2_a.GetFreeSpacePolygons().empty());

    FSP::LinearRing exterior_ring{{0L,0L,0L},{3L,0L,0L},{3L,3L,0L},{0L,3L,0L}};
    FSP::LinearRing interior_ring{{1L,1L,0L},{1L,2L,0L},{2L,2L,0L},{2L,1L,0L}};
    FSP::LinearRings interior_rings{interior_ring};
    FSP::RingInfo exterior_ring_info{
        {0UL,1UL,FSP::SegmentType::TRIVIAL},
        {1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER},
        {2UL,3UL,FSP::SegmentType::TRIVIAL},
        {3UL,0UL,FSP::SegmentType::TRAFFIC_BARRIER}
    };
    FSP::RingInfo interior_ring_info{{0UL,0UL,FSP::SegmentType::TRIVIAL}};
    std::vector<FSP::RingInfo> polygon_info{exterior_ring_info,interior_ring_info};

    FSP::FreeSpacePolygon  freespacepolygon_a(exterior_ring,interior_rings,polygon_info);
    
    FSP::MapFreeSpacePolygons mapfreespacepolygons{freespacepolygon_a};

    holo::common::Timestamp timestamp_a(5u,6000u);
    Coordinate coordinate_a(Coordinate::Utm6Coordinate(50U, false)); // COORD_WORLD
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_b(timestamp_a,coordinate_a,mapfreespacepolygons);
    ASSERT_EQ(localmapfreespacev2_b.GetTimestamp(),timestamp_a);
    ASSERT_EQ(localmapfreespacev2_b.GetCoordinate(),coordinate_a);
    ASSERT_EQ(localmapfreespacev2_b.GetFreeSpacePolygons(),mapfreespacepolygons);

    holo::LocalMapFreeSpaceV2 localmapfreespacev2_c(localmapfreespacev2_b);
    ASSERT_EQ(localmapfreespacev2_c.GetTimestamp(),localmapfreespacev2_b.GetTimestamp());
    ASSERT_EQ(localmapfreespacev2_c.GetCoordinate(),localmapfreespacev2_b.GetCoordinate());
    ASSERT_EQ(localmapfreespacev2_c.GetFreeSpacePolygons(),localmapfreespacev2_b.GetFreeSpacePolygons());

    holo::LocalMapFreeSpaceV2 localmapfreespacev2_d(std::move(localmapfreespacev2_b));
    ASSERT_EQ(localmapfreespacev2_d.GetTimestamp(),localmapfreespacev2_c.GetTimestamp());
    ASSERT_EQ(localmapfreespacev2_d.GetCoordinate(),localmapfreespacev2_c.GetCoordinate());
    ASSERT_EQ(localmapfreespacev2_d.GetFreeSpacePolygons(),localmapfreespacev2_c.GetFreeSpacePolygons());    
}

TEST(TestLocalMapFreeSpaceV2, TestEqualToOperator)
{
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_a;
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_b;

    ASSERT_TRUE(localmapfreespacev2_a == localmapfreespacev2_b);
    ASSERT_TRUE(localmapfreespacev2_a == localmapfreespacev2_a);
    ASSERT_TRUE(operator==(localmapfreespacev2_a, localmapfreespacev2_a));

    FSP::LinearRing exterior_ring{{0L,0L,0L},{3L,0L,0L},{3L,3L,0L},{0L,3L,0L}};
    FSP::LinearRing interior_ring{{1L,1L,0L},{1L,2L,0L},{2L,2L,0L},{2L,1L,0L}};
    FSP::LinearRings interior_rings{interior_ring};
    FSP::RingInfo exterior_ring_info{
        {0UL,1UL,FSP::SegmentType::TRIVIAL},
        {1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER},
        {2UL,3UL,FSP::SegmentType::TRIVIAL},
        {3UL,0UL,FSP::SegmentType::TRAFFIC_BARRIER}
    };
    FSP::RingInfo interior_ring_info{{0UL,0UL,FSP::SegmentType::TRIVIAL}};
    std::vector<FSP::RingInfo> polygon_info{exterior_ring_info,interior_ring_info};

    FSP::FreeSpacePolygon  freespacepolygon_a(exterior_ring,interior_rings,polygon_info);
    
    FSP::MapFreeSpacePolygons mapfreespacepolygons{freespacepolygon_a};

    holo::common::Timestamp timestamp_a(5u,6000u);
    Coordinate coordinate_a(Coordinate::Utm6Coordinate(50U, false)); // COORD_WORLD
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_c(timestamp_a,coordinate_a,mapfreespacepolygons);

    ASSERT_FALSE(localmapfreespacev2_a == localmapfreespacev2_c);
}

TEST(TestLocalMapFreeSpaceV2, TestNotEqualToOperator)
{
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_a;
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_b;

    ASSERT_FALSE(localmapfreespacev2_a != localmapfreespacev2_b);
    ASSERT_FALSE(operator!=(localmapfreespacev2_a, localmapfreespacev2_b));

    FSP::LinearRing exterior_ring{{0L,0L,0L},{3L,0L,0L},{3L,3L,0L},{0L,3L,0L}};
    FSP::LinearRing interior_ring{{1L,1L,0L},{1L,2L,0L},{2L,2L,0L},{2L,1L,0L}};
    FSP::LinearRings interior_rings{interior_ring};
    FSP::RingInfo exterior_ring_info{
        {0UL,1UL,FSP::SegmentType::TRIVIAL},
        {1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER},
        {2UL,3UL,FSP::SegmentType::TRIVIAL},
        {3UL,0UL,FSP::SegmentType::TRAFFIC_BARRIER}
    };
    FSP::RingInfo interior_ring_info{{0UL,0UL,FSP::SegmentType::TRIVIAL}};
    std::vector<FSP::RingInfo> polygon_info{exterior_ring_info,interior_ring_info};

    FSP::FreeSpacePolygon  freespacepolygon_a(exterior_ring,interior_rings,polygon_info);
    
    FSP::MapFreeSpacePolygons mapfreespacepolygons{freespacepolygon_a};

    holo::common::Timestamp timestamp_a(5u,6000u);
    Coordinate coordinate_a(Coordinate::Utm6Coordinate(50U, false)); // COORD_WORLD
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_c(timestamp_a,coordinate_a,mapfreespacepolygons);

    ASSERT_TRUE(localmapfreespacev2_a != localmapfreespacev2_c);
}

TEST(TestLocalMapFreeSpaceV2, TestAssignOperator)
{
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_a;

    FSP::LinearRing exterior_ring{{0L,0L,0L},{3L,0L,0L},{3L,3L,0L},{0L,3L,0L}};
    FSP::LinearRing interior_ring{{1L,1L,0L},{1L,2L,0L},{2L,2L,0L},{2L,1L,0L}};
    FSP::LinearRings interior_rings{interior_ring};
    FSP::RingInfo exterior_ring_info{
        {0UL,1UL,FSP::SegmentType::TRIVIAL},
        {1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER},
        {2UL,3UL,FSP::SegmentType::TRIVIAL},
        {3UL,0UL,FSP::SegmentType::TRAFFIC_BARRIER}
    };
    FSP::RingInfo interior_ring_info{{0UL,0UL,FSP::SegmentType::TRIVIAL}};
    std::vector<FSP::RingInfo> polygon_info{exterior_ring_info,interior_ring_info};

    FSP::FreeSpacePolygon  freespacepolygon_a(exterior_ring,interior_rings,polygon_info);
    
    FSP::MapFreeSpacePolygons mapfreespacepolygons{freespacepolygon_a};

    holo::common::Timestamp timestamp_a(5u,6000u);
    Coordinate coordinate_a(Coordinate::Utm6Coordinate(50U, false)); // COORD_WORLD
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_b(timestamp_a,coordinate_a,mapfreespacepolygons);

    localmapfreespacev2_a = localmapfreespacev2_b;
    ASSERT_EQ(localmapfreespacev2_a,localmapfreespacev2_b);
 
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_c;
    localmapfreespacev2_c = std::move(localmapfreespacev2_b);
    ASSERT_EQ(localmapfreespacev2_c,localmapfreespacev2_a);
}

TEST(TestLocalMapFreeSpaceV2, TestGetTimestamp)
{
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_a;
    holo::common::Timestamp timestamp_a;
    ASSERT_EQ(localmapfreespacev2_a.GetTimestamp(), timestamp_a);

    holo::common::Timestamp timestamp_b(5u,6000u);
    holo::LocalMapFreeSpaceV2 const localmapfreespacev2_b(timestamp_b,Coordinate(Coordinate::UNKNOWN),{}); // COORD_UNKNOWN
    ASSERT_EQ(localmapfreespacev2_b.GetTimestamp(), timestamp_b);
}

TEST(TestLocalMapFreeSpaceV2, TestSetTimestamp)
{
    holo::common::Timestamp timestamp_a(5u,6000u);
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_a;
    localmapfreespacev2_a.SetTimestamp(timestamp_a);
    ASSERT_EQ(localmapfreespacev2_a.GetTimestamp(), timestamp_a);
}

TEST(TestLocalMapFreeSpaceV2, TestGetCoord)
{
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_a;
    Coordinate coordinate_a = Coordinate(Coordinate::UNKNOWN); // COORD_UNKNOWN
    ASSERT_EQ(localmapfreespacev2_a.GetCoordinate(), coordinate_a);

    Coordinate coordinate_b = Coordinate::Utm6Coordinate(50U, false); // COORD_WORLD
    holo::LocalMapFreeSpaceV2 const localmapfreespacev2_b({5u,6000u},Coordinate::Utm6Coordinate(50U, false),{}); // COORD_WORLD
    ASSERT_EQ(localmapfreespacev2_b.GetCoordinate(), coordinate_b);
}

TEST(TestLocalMapFreeSpaceV2, TestSetCoord)
{
    Coordinate coordinate_a = Coordinate::Utm6Coordinate(50U, false); // COORD_WORLD
    holo::LocalMapFreeSpaceV2 localmapfreespacev2_a;
    localmapfreespacev2_a.SetCoordinate(coordinate_a);
    ASSERT_EQ(localmapfreespacev2_a.GetCoordinate(), coordinate_a);
}

TEST(TestLocalMapFreeSpaceV2, TestGetFreeSpacePolygons)
{
    FSP::LinearRing exterior_ring{{0L,0L,0L},{3L,0L,0L},{3L,3L,0L},{0L,3L,0L}};
    FSP::LinearRing interior_ring{{1L,1L,0L},{1L,2L,0L},{2L,2L,0L},{2L,1L,0L}};
    FSP::LinearRings interior_rings{interior_ring};
    FSP::RingInfo exterior_ring_info{
        {0UL,1UL,FSP::SegmentType::TRIVIAL},
        {1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER},
        {2UL,3UL,FSP::SegmentType::TRIVIAL},
        {3UL,0UL,FSP::SegmentType::TRAFFIC_BARRIER}
    };
    FSP::RingInfo interior_ring_info{{0UL,0UL,FSP::SegmentType::TRIVIAL}};
    std::vector<FSP::RingInfo> polygon_info{exterior_ring_info,interior_ring_info};

    FSP::FreeSpacePolygon  freespacepolygon(exterior_ring,interior_rings,polygon_info);
    
    FSP::MapFreeSpacePolygons mapfreespacepolygons{freespacepolygon};

    holo::LocalMapFreeSpaceV2 localmapfreespacev2_a({5u,6000u},Coordinate(Coordinate::UNKNOWN),mapfreespacepolygons); // COORD_UNKNOWN
    ASSERT_EQ(localmapfreespacev2_a.GetFreeSpacePolygons(), mapfreespacepolygons);

    holo::LocalMapFreeSpaceV2 const localmapfreespacev2_b({5u,6000u},Coordinate(Coordinate::UNKNOWN),mapfreespacepolygons); // COORD_UNKNOWN
    ASSERT_EQ(localmapfreespacev2_b.GetFreeSpacePolygons(), mapfreespacepolygons);
}

TEST(TestLocalMapFreeSpaceV2, TestSetFreeSpacePolygons)
{
    FSP::LinearRing exterior_ring{{0L,0L,0L},{3L,0L,0L},{3L,3L,0L},{0L,3L,0L}};
    FSP::LinearRing interior_ring{{1L,1L,0L},{1L,2L,0L},{2L,2L,0L},{2L,1L,0L}};
    FSP::LinearRings interior_rings{interior_ring};
    FSP::RingInfo exterior_ring_info{
        {0UL,1UL,FSP::SegmentType::TRIVIAL},
        {1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER},
        {2UL,3UL,FSP::SegmentType::TRIVIAL},
        {3UL,0UL,FSP::SegmentType::TRAFFIC_BARRIER}
    };
    FSP::RingInfo interior_ring_info{{0UL,0UL,FSP::SegmentType::TRIVIAL}};
    std::vector<FSP::RingInfo> polygon_info{exterior_ring_info,interior_ring_info};

    FSP::FreeSpacePolygon  freespacepolygon(exterior_ring,interior_rings,polygon_info);
    
    FSP::MapFreeSpacePolygons mapfreespacepolygons{freespacepolygon};

    holo::LocalMapFreeSpaceV2 localmapfreespacev2_a;
    localmapfreespacev2_a.SetFreeSpacePolygons(mapfreespacepolygons);
    ASSERT_EQ(localmapfreespacev2_a.GetFreeSpacePolygons(), mapfreespacepolygons);

    FSP::LinearRing exterior_ring_a{{0L,0L,0L},{4L,0L,0L},{4L,4L,0L},{0L,4L,0L}};
    FSP::LinearRing interior_ring_a{{1L,1L,0L},{1L,3L,0L},{3L,3L,0L},{3L,1L,0L}};
    FSP::LinearRings interior_rings_a{interior_ring_a};
    FSP::RingInfo exterior_ring_info_a{
        {0UL,1UL,FSP::SegmentType::TRIVIAL},
        {1UL,2UL,FSP::SegmentType::TRAFFIC_BARRIER},
        {2UL,3UL,FSP::SegmentType::TRIVIAL},
        {3UL,0UL,FSP::SegmentType::TRAFFIC_BARRIER}
    };
    FSP::RingInfo interior_ring_info_a{{0UL,0UL,FSP::SegmentType::TRIVIAL}};
    std::vector<FSP::RingInfo> polygon_info_a{exterior_ring_info_a,interior_ring_info_a};

    FSP::FreeSpacePolygon  freespacepolygon_a(exterior_ring_a,interior_rings_a,polygon_info_a);
    
    FSP::MapFreeSpacePolygons mapfreespacepolygons_a{freespacepolygon_a};

    localmapfreespacev2_a.SetFreeSpacePolygons({mapfreespacepolygons_a});
    ASSERT_EQ(localmapfreespacev2_a.GetFreeSpacePolygons(), mapfreespacepolygons_a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}