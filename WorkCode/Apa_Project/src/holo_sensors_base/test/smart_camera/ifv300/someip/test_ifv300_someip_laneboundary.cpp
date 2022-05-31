#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/ifv300/ifv300_someip.h>

TEST(Ifv300DriverInt, All)
{
    ASSERT_TRUE(true);
}

#if 0
TEST(Ifv300Lbd, ConvertToLaneboundaryWithTransform)
{
    auto driver = std::make_shared<Ifv300Test>();
    struct IfvLineInfoCurve input;
    input.mark_color = 2; // LaneBoundary::LaneMarkColor::WHITE
    input.a0         = 1600+9; // (x-1600)/100
    input.a1         = 1000+200; // 9*(x-1000)/10000
    input.a2         = 2000-1000; // (x-2000)/200000
    input.a3         = 17000+10000; // (x-17000)/100000000
    input.range      = 66*4; // x/4
    IfvBoundaryType output;
    driver->ConvertToLaneboundaryWithTransform(input, output);
    ASSERT_EQ(output.GetTimestamp().GetSec(), 0);
    ASSERT_EQ(output.GetTimestamp().GetNsec(), 0);
    ASSERT_EQ(output.GetA0(), 0.09f);
    ASSERT_EQ(output.GetA1(), 0.18f);
    ASSERT_EQ(output.GetA2(), -0.005f);
    ASSERT_EQ(output.GetA3(), 0.0001f);
    ASSERT_EQ(output.GetRange(), 66.0f);
    ASSERT_EQ(output.GetType(), 0);
    ASSERT_EQ(output.GetColor(), 2);
    ASSERT_EQ(output.GetQuality(), 0);
    ASSERT_EQ(output.GetValid(), true);
}

TEST(Ifv300Lbd, ConvertToRoadFrameWithTransform)
{
    auto driver = std::make_shared<Ifv300Test>();
    struct IfvLinesRawData input;
    (void)memset(&input, 0, sizeof(struct IfvLinesRawData));
    input.timestamp.sec = 1;
    input.timestamp.nsec = 2;
    input.line_head.lane_change         = 0;           // unused
    input.line_head.left_left_type      = 8;           // LaneBoundary::LaneBoundaryType::DOUBLE_LANE
    input.line_head.left_type           = 1;           // LaneBoundary::LaneBoundaryType::SOLID
    input.line_head.right_right_type    = 2;           // LaneBoundary::LaneBoundaryType::DASHED
    input.line_head.right_type          = 4;           // LaneBoundary::LaneBoundaryType::BOTTS_DOT
    input.line_head.left_left_lkaconf   = 0;           // 0.25f
    input.line_head.left_lkaconf        = 1;           // 0.50f
    input.line_head.right_right_lkaconf = 2;           // 0.75f
    input.line_head.right_lkaconf       = 3;           // 1.00f
    input.line_head.reserved            = 0;           // unused
    input.left_left.mark_color          = 0;           // LaneBoundary::LaneMarkColor::INVALID
    input.left_left.a0                  = 1600+400;    // (x-1600)/100=4
    input.left_left.a1                  = 1000+100;    // 9*(x-1000)/10000=0.09
    input.left_left.a2                  = 2000-2000;   // (x-2000)/200000=-0.01
    input.left_left.a3                  = 17000+20000; // (x-17000)/100000000=0.0002
    input.left_left.range               = 33*4;        // x/4=33
    input.left.mark_color               = 1;           // LaneBoundary::LaneMarkColor::YELLOW
    input.left.a0                       = 1600+150;    // (x-1600)/100=1.5
    input.left.a1                       = 1000+200;    // 9*(x-1000)/10000=0.18
    input.left.a2                       = 2000-1000;   // (x-2000)/200000=-0.05
    input.left.a3                       = 17000+10000; // (x-17000)/100000000=0.0001
    input.left.range                    = 44*4;        // x/4=44
    input.right.mark_color              = 2;           // LaneBoundary::LaneMarkColor::WHITE
    input.right.a0                      = 1600-200;    // (x-1600)/100=-2
    input.right.a1                      = 1000-200;    // 9*(x-1000)/10000=-0.18
    input.right.a2                      = 2000+1000;   // (x-2000)/200000=0.005
    input.right.a3                      = 17000-10000; // (x-17000)/100000000=-0.0001
    input.right.range                   = 55*4;        // x/4=55
    input.right_right.mark_color        = 3;           // LaneBoundary::LaneMarkColor::BLUE
    input.right_right.a0                = 1600-550;    // (x-1600)/100=-5.5
    input.right_right.a1                = 1000-300;    // 9*(x-1000)/10000=-0.03
    input.right_right.a2                = 2000+3000;   // (x-2000)/200000=0.015
    input.right_right.a3                = 17000-20000; // (x-17000)/100000000=-0.0002
    input.right_right.range             = 77*4;        // x/4=77
    RoadFrameType output;
    driver->ConvertToRoadFrameWithTransform(input, output);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetNsec(), 2);
    auto lbd = output.at(1);
    ASSERT_EQ(lbd.GetStyle(), holo::common::BoundaryStyle::SOLID);
    ASSERT_EQ(lbd.GetColor(), holo::common::BoundaryColor::YELLOW);
    ASSERT_FLOAT_EQ(lbd.GetConfidence(), 50);
}

static void RfCallback(const RoadFrameType& roadframe, RoadFrameType& copy)
{
    copy = roadframe;
}

TEST(Ifv300Lbd, ParseLaneboundaries)
{
    auto driver = std::make_shared<Ifv300Test>();
    RoadFrameType roadframe;
    auto h = std::bind(&RfCallback, std::placeholders::_1, std::ref(roadframe));
    driver->InstallCallback(h);
    struct IfvLinesRawData raw_lines;
    uint8_t data[1024] = {0};
    (void)std::memset(data, 0x00, sizeof(data));
    bool b = driver->ParseLaneboundaries(data, 10, raw_lines); // min=50bytes
    ASSERT_FALSE(b);
    struct IfvLinesRawData test_lines;
    (void)memset(&test_lines, 0, sizeof(struct IfvLinesRawData));
    test_lines.timestamp.sec = 1;
    test_lines.timestamp.nsec = 2;
    test_lines.line_head.lane_change         = 0;           // unused
    test_lines.line_head.left_left_type      = 8;           // LaneBoundary::LaneBoundaryType::DOUBLE_LANE
    test_lines.line_head.left_type           = 1;           // LaneBoundary::LaneBoundaryType::SOLID
    test_lines.line_head.right_right_type    = 2;           // LaneBoundary::LaneBoundaryType::DASHED
    test_lines.line_head.right_type          = 4;           // LaneBoundary::LaneBoundaryType::BOTTS_DOT
    test_lines.line_head.left_left_lkaconf   = 0;           // 0.25f
    test_lines.line_head.left_lkaconf        = 1;           // 0.50f
    test_lines.line_head.right_right_lkaconf = 2;           // 0.75f
    test_lines.line_head.right_lkaconf       = 3;           // 1.00f
    test_lines.line_head.reserved            = 0;           // unused
    test_lines.left_left.mark_color          = 0;           // LaneBoundary::LaneMarkColor::INVALID
    test_lines.left_left.a0                  = 1600+400;    // (x-1600)/100=4
    test_lines.left_left.a1                  = 1000+100;    // 9*(x-1000)/10000=0.09
    test_lines.left_left.a2                  = 2000-2000;   // (x-2000)/200000=-0.01
    test_lines.left_left.a3                  = 17000+20000; // (x-17000)/100000000=0.0002
    test_lines.left_left.range               = 33*4;        // x/4=33
    test_lines.left.mark_color               = 1;           // LaneBoundary::LaneMarkColor::YELLOW
    test_lines.left.a0                       = 1600+150;    // (x-1600)/100=1.5
    test_lines.left.a1                       = 1000+200;    // 9*(x-1000)/10000=0.18
    test_lines.left.a2                       = 2000-1000;   // (x-2000)/200000=-0.05
    test_lines.left.a3                       = 17000+10000; // (x-17000)/100000000=0.0001
    test_lines.left.range                    = 44*4;        // x/4=44
    test_lines.right.mark_color              = 2;           // LaneBoundary::LaneMarkColor::WHITE
    test_lines.right.a0                      = 1600-200;    // (x-1600)/100=-2
    test_lines.right.a1                      = 1000-200;    // 9*(x-1000)/10000=-0.18
    test_lines.right.a2                      = 2000+1000;   // (x-2000)/200000=0.005
    test_lines.right.a3                      = 17000-10000; // (x-17000)/100000000=-0.0001
    test_lines.right.range                   = 55*4;        // x/4=55
    test_lines.right_right.mark_color        = 3;           // LaneBoundary::LaneMarkColor::BLUE
    test_lines.right_right.a0                = 1600-550;    // (x-1600)/100=-5.5
    test_lines.right_right.a1                = 1000-300;    // 9*(x-1000)/10000=-0.03
    test_lines.right_right.a2                = 2000+3000;   // (x-2000)/200000=0.015
    test_lines.right_right.a3                = 17000-20000; // (x-17000)/100000000=-0.0002
    test_lines.right_right.range             = 77*4;        // x/4=77
    ifv_lines_raw_data_serialize(&test_lines, data, sizeof(data));
    b = driver->ParseLaneboundaries(data, sizeof(data), raw_lines);
    ASSERT_TRUE(b);
    ASSERT_FLOAT_EQ(roadframe.GetTimestamp().GetSec(), 1);
    ASSERT_FLOAT_EQ(roadframe.GetTimestamp().GetNsec(), 2);
    auto lbd = roadframe.at(2);
    ASSERT_EQ(lbd.GetStyle(), holo::common::BoundaryStyle::BOTTS_DOT);
    ASSERT_EQ(lbd.GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(lbd.GetConfidence(), 100);
}
#endif
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
