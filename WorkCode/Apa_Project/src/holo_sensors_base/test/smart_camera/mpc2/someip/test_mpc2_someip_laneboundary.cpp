#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_someip.h>

using namespace holo;
using namespace holo::sensors::bosch_mpc;

/* obstacle alias */
using ObjectType   = holo::sensors::bosch_mpc::BoschMpcObstacle;
using ObstacleType = holo::obstacle::ObstacleVisionT<float32_t>;
using ObstaclePtrListType =
    holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY>;
using ObstacleListCallback = std::function<void(const ObstaclePtrListType&)>;
/* lane boundary alias */
using MpcBoundaryType   = holo::sensors::bosch_mpc::BoschMpcLaneBoundary;
using LaneboundaryType  = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;
using RoadFrameType     = holo::common::RoadFrame<holo::numerics::Polynomial<float32_t, 3>, 8>;
using RoadFrameCallback = std::function<void(const RoadFrameType&)>;

TEST(BoschMpcDriverSomeip, ConvertToLaneboundaryWithTransform)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    struct MpcLineRawData             input;
    input.timestamp.sec  = 1;
    input.timestamp.nsec = 2;
    input.confidence     = 32;          // x/64=0.5
    input.id             = 10;          // 10
    input.type           = 2;           // BoundaryStyle::DASHED
    input.width          = 256;         // x/256-0.5=0
    input.color          = 1;           // BoundaryColor::WHITE
    input.dx_begin       = 4;           // x/4=1
    input.dx_end         = 100;         // x/4=25
    input.dy             = 2048 + 512;  // x/256-8=2
    input.angle_diff     = 2048;        // x/2048-1=0
    input.horizon_curve  = 2048;        // x-2047=1
    MpcBoundaryType output;
    driver.ConvertToLaneboundaryWithTransform(input, output);
    ASSERT_EQ(output.GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output.GetTimestamp().GetNsec(), 2);
    ASSERT_EQ(output.GetLineNumber(), 10);
    ASSERT_EQ(output.GetLineType(), 2);
    ASSERT_EQ(output.GetLineColor(), 1);
    ASSERT_EQ(output.GetHorizonCurvature(), 1);
    ASSERT_FLOAT_EQ(output.GetDxBegin(), 1.0f);
    ASSERT_FLOAT_EQ(output.GetDxEnd(), 25.0f);
    ASSERT_FLOAT_EQ(output.GetDy(), 2.0f);
    ASSERT_FLOAT_EQ(output.GetAngleDiff(), 0.0f);
    ASSERT_FLOAT_EQ(output.GetLineWidth(), 0.5f);
    ASSERT_FLOAT_EQ(output.GetConfidence(), 0.5f);
    ASSERT_TRUE(output.IsValid());
    ASSERT_TRUE(output.GetPartAValid());
    ASSERT_TRUE(output.GetPartBValid());
}

TEST(BoschMpcDriverSomeip, ConvertToRoadFrameWithTransform)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    struct MpcLinesRawData            input;
    (void)memset(&input, 0, sizeof(struct MpcLinesRawData));
    input.left_left_line.timestamp.sec    = 1;
    input.left_left_line.timestamp.nsec   = 2;
    input.left_left_line.confidence       = 32;                 // x/64=0.5
    input.left_left_line.id               = 9;                  // 9
    input.left_left_line.type             = 2;                  // BoundaryStyle::DASHED
    input.left_left_line.width            = 256;                // x/256-0.5=0.5
    input.left_left_line.color            = 1;                  // BoundaryColor::WHITE
    input.left_left_line.dx_begin         = 4;                  // x/4=1
    input.left_left_line.dx_end           = 100;                // x/4=25
    input.left_left_line.dy               = 2048 + 512 + 1024;  // x/256-8=6
    input.left_left_line.angle_diff       = 2048;               // x/2048-1=0
    input.left_left_line.horizon_curve    = 2048;               // x-2047=1
    input.left_line.timestamp.sec         = 1;
    input.left_line.timestamp.nsec        = 2;
    input.left_line.confidence            = 32;          // x/64=0.5
    input.left_line.id                    = 10;          // 10
    input.left_line.type                  = 2;           // BoundaryStyle::DASHED
    input.left_line.width                 = 256;         // x/256-0.5=0.5
    input.left_line.color                 = 1;           // BoundaryColor::WHITE
    input.left_line.dx_begin              = 4;           // x/4=1
    input.left_line.dx_end                = 100;         // x/4=25
    input.left_line.dy                    = 2048 + 512;  // x/256-8=2
    input.left_line.angle_diff            = 2048;        // x/2048-1=0
    input.left_line.horizon_curve         = 2048;        // x-2047=1
    input.right_line.timestamp.sec        = 1;
    input.right_line.timestamp.nsec       = 2;
    input.right_line.confidence           = 32;          // x/64=0.5
    input.right_line.id                   = 11;          // 11
    input.right_line.type                 = 2;           // BoundaryStyle::DASHED
    input.right_line.width                = 256;         // x/256-0.5=0.5
    input.right_line.color                = 1;           // BoundaryColor::WHITE
    input.right_line.dx_begin             = 4;           // x/4=1
    input.right_line.dx_end               = 100;         // x/4=25
    input.right_line.dy                   = 2048 - 512;  // x/256-8=-2
    input.right_line.angle_diff           = 2048;        // x/2048-1=0
    input.right_line.horizon_curve        = 2048;        // x-2047=1
    input.right_right_line.timestamp.sec  = 1;
    input.right_right_line.timestamp.nsec = 2;
    input.right_right_line.confidence     = 32;                 // x/64=0.5
    input.right_right_line.id             = 12;                 // 12
    input.right_right_line.type           = 2;                  // BoundaryStyle::DASHED
    input.right_right_line.width          = 256;                // x/256-0.5=0.5
    input.right_right_line.color          = 1;                  // BoundaryColor::WHITE
    input.right_right_line.dx_begin       = 4;                  // x/4=1
    input.right_right_line.dx_end         = 100;                // x/4=25
    input.right_right_line.dy             = 2048 - 512 - 1024;  // x/256-8=-6
    input.right_right_line.angle_diff     = 2048;               // x/2048-1=0
    input.right_right_line.horizon_curve  = 2048;               // x-2047=1
    RoadFrameType output;
    driver.ConvertToRoadFrameWithTransform(input, output);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetSec(), 0);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetNsec(), 0);
    auto lbd = output.at(1);
    ASSERT_EQ(lbd.GetStyle(), holo::common::BoundaryStyle::DASHED);
    ASSERT_EQ(lbd.GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(lbd.GetConfidence(), 50);
    std::pair<float32_t, float32_t> range = lbd.GetCoordinateRange();
    ASSERT_FLOAT_EQ(range.first, 1);
    ASSERT_FLOAT_EQ(range.second, 25);
    ASSERT_EQ(lbd.GetWidth(), 50);
    holo::geometry::Point2f p0 = lbd.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), 2.0f);
}

TEST(BoschMpcDriverSomeip, ConvertToRoadFrameWithTransform2)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    /* CHANGE TO LEFT */
    struct MpcLinesRawData input;
    (void)memset(&input, 0, sizeof(struct MpcLinesRawData));
    input.left_left_line.timestamp.sec    = 1;
    input.left_left_line.timestamp.nsec   = 2;
    input.left_left_line.confidence       = 32;                 // x/64=0.5
    input.left_left_line.id               = 9;                  // 9
    input.left_left_line.type             = 2;                  // BoundaryStyle::DASHED
    input.left_left_line.width            = 256;                // x/256-0.5=0.5
    input.left_left_line.color            = 1;                  // BoundaryColor::WHITE
    input.left_left_line.dx_begin         = 4;                  // x/4=1
    input.left_left_line.dx_end           = 100;                // x/4=25
    input.left_left_line.dy               = 2048 + 512 + 1024;  // x/256-8=6
    input.left_left_line.angle_diff       = 2048;               // x/2048-1=0
    input.left_left_line.horizon_curve    = 2048;               // x-2047=1
    input.left_line.timestamp.sec         = 1;
    input.left_line.timestamp.nsec        = 2;
    input.left_line.confidence            = 32;         // x/64=0.5
    input.left_line.id                    = 10;         // 10
    input.left_line.type                  = 2;          // BoundaryStyle::DASHED
    input.left_line.width                 = 256;        // x/256-0.5=0.5
    input.left_line.color                 = 1;          // BoundaryColor::WHITE
    input.left_line.dx_begin              = 4;          // x/4=1
    input.left_line.dx_end                = 100;        // x/4=25
    input.left_line.dy                    = 2048 + 64;  // x/256-8=0.25
    input.left_line.angle_diff            = 2048;       // x/2048-1=0
    input.left_line.horizon_curve         = 2048;       // x-2047=1
    input.right_line.timestamp.sec        = 1;
    input.right_line.timestamp.nsec       = 2;
    input.right_line.confidence           = 32;          // x/64=0.5
    input.right_line.id                   = 11;          // 11
    input.right_line.type                 = 2;           // BoundaryStyle::DASHED
    input.right_line.width                = 256;         // x/256-0.5=0.5
    input.right_line.color                = 1;           // BoundaryColor::WHITE
    input.right_line.dx_begin             = 4;           // x/4=1
    input.right_line.dx_end               = 100;         // x/4=25
    input.right_line.dy                   = 2048 - 512;  // x/256-8=-2
    input.right_line.angle_diff           = 2048;        // x/2048-1=0
    input.right_line.horizon_curve        = 2048;        // x-2047=1
    input.right_right_line.timestamp.sec  = 1;
    input.right_right_line.timestamp.nsec = 2;
    input.right_right_line.confidence     = 32;                 // x/64=0.5
    input.right_right_line.id             = 12;                 // 12
    input.right_right_line.type           = 2;                  // BoundaryStyle::DASHED
    input.right_right_line.width          = 256;                // x/256-0.5=0.5
    input.right_right_line.color          = 1;                  // BoundaryColor::WHITE
    input.right_right_line.dx_begin       = 4;                  // x/4=1
    input.right_right_line.dx_end         = 100;                // x/4=25
    input.right_right_line.dy             = 2048 - 512 - 1024;  // x/256-8=-6
    input.right_right_line.angle_diff     = 2048;               // x/2048-1=0
    input.right_right_line.horizon_curve  = 2048;               // x-2047=1
    RoadFrameType output;
    driver.ConvertToRoadFrameWithTransform(input, output);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetSec(), 0);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetNsec(), 0);
    auto lbd = output.at(1);
    ASSERT_EQ(lbd.GetStyle(), holo::common::BoundaryStyle::DASHED);
    ASSERT_EQ(lbd.GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(lbd.GetConfidence(), 50);
    std::pair<float32_t, float32_t> range = lbd.GetCoordinateRange();
    ASSERT_FLOAT_EQ(range.first, 1);
    ASSERT_FLOAT_EQ(range.second, 25);
    ASSERT_EQ(lbd.GetWidth(), 50);
    holo::geometry::Point2f p0 = lbd.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), 0.25f);
    /* KEEP */
    (void)memset(&input, 0, sizeof(struct MpcLinesRawData));
    input.left_left_line.timestamp.sec    = 1;
    input.left_left_line.timestamp.nsec   = 2;
    input.left_left_line.confidence       = 32;                 // x/64=0.5
    input.left_left_line.id               = 9;                  // 9
    input.left_left_line.type             = 2;                  // BoundaryStyle::DASHED
    input.left_left_line.width            = 256;                // x/256-0.5=0.5
    input.left_left_line.color            = 1;                  // BoundaryColor::WHITE
    input.left_left_line.dx_begin         = 4;                  // x/4=1
    input.left_left_line.dx_end           = 100;                // x/4=25
    input.left_left_line.dy               = 2048 + 512 + 1024;  // x/256-8=6
    input.left_left_line.angle_diff       = 2048;               // x/2048-1=0
    input.left_left_line.horizon_curve    = 2048;               // x-2047=1
    input.left_line.timestamp.sec         = 1;
    input.left_line.timestamp.nsec        = 2;
    input.left_line.confidence            = 32;           // x/64=0.5
    input.left_line.id                    = 10;           // 10
    input.left_line.type                  = 2;            // BoundaryStyle::DASHED
    input.left_line.width                 = 256;          // x/256-0.5=0.5
    input.left_line.color                 = 1;            // BoundaryColor::WHITE
    input.left_line.dx_begin              = 4;            // x/4=1
    input.left_line.dx_end                = 100;          // x/4=25
    input.left_line.dy                    = 2048 + 1024;  // x/256-8=4
    input.left_line.angle_diff            = 2048;         // x/2048-1=0
    input.left_line.horizon_curve         = 2048;         // x-2047=1
    input.right_line.timestamp.sec        = 1;
    input.right_line.timestamp.nsec       = 2;
    input.right_line.confidence           = 32;          // x/64=0.5
    input.right_line.id                   = 11;          // 11
    input.right_line.type                 = 2;           // BoundaryStyle::DASHED
    input.right_line.width                = 256;         // x/256-0.5=0.5
    input.right_line.color                = 1;           // BoundaryColor::WHITE
    input.right_line.dx_begin             = 4;           // x/4=1
    input.right_line.dx_end               = 100;         // x/4=25
    input.right_line.dy                   = 2048 - 120;  // x/256-8=-0.46875
    input.right_line.angle_diff           = 2048;        // x/2048-1=0
    input.right_line.horizon_curve        = 2048;        // x-2047=1
    input.right_right_line.timestamp.sec  = 1;
    input.right_right_line.timestamp.nsec = 2;
    input.right_right_line.confidence     = 32;                 // x/64=0.5
    input.right_right_line.id             = 12;                 // 12
    input.right_right_line.type           = 2;                  // BoundaryStyle::DASHED
    input.right_right_line.width          = 256;                // x/256-0.5=0.5
    input.right_right_line.color          = 1;                  // BoundaryColor::WHITE
    input.right_right_line.dx_begin       = 4;                  // x/4=1
    input.right_right_line.dx_end         = 100;                // x/4=25
    input.right_right_line.dy             = 2048 - 512 - 1024;  // x/256-8=-6
    input.right_right_line.angle_diff     = 2048;               // x/2048-1=0
    input.right_right_line.horizon_curve  = 2048;               // x-2047=1
    RoadFrameType output2;
    driver.ConvertToRoadFrameWithTransform(input, output2);
    ASSERT_FLOAT_EQ(output2.GetTimestamp().GetSec(), 0);
    ASSERT_FLOAT_EQ(output2.GetTimestamp().GetNsec(), 0);
    auto lbd2 = output2.at(1);
    ASSERT_EQ(lbd2.GetStyle(), holo::common::BoundaryStyle::DASHED);
    ASSERT_EQ(lbd2.GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(lbd2.GetConfidence(), 50);
    std::pair<float32_t, float32_t> range2 = lbd2.GetCoordinateRange();
    ASSERT_FLOAT_EQ(range2.first, 1);
    ASSERT_FLOAT_EQ(range2.second, 25);
    ASSERT_EQ(lbd2.GetWidth(), 50);
    p0 = lbd2.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), -0.46875f);
    /* CHANGE TO RIGHT */
    (void)memset(&input, 0, sizeof(struct MpcLinesRawData));
    input.left_left_line.timestamp.sec    = 1;
    input.left_left_line.timestamp.nsec   = 2;
    input.left_left_line.confidence       = 32;                 // x/64=0.5
    input.left_left_line.id               = 9;                  // 9
    input.left_left_line.type             = 2;                  // BoundaryStyle::DASHED
    input.left_left_line.width            = 256;                // x/256-0.5=0.5
    input.left_left_line.color            = 1;                  // BoundaryColor::WHITE
    input.left_left_line.dx_begin         = 4;                  // x/4=1
    input.left_left_line.dx_end           = 100;                // x/4=25
    input.left_left_line.dy               = 2048 + 512 + 1024;  // x/256-8=6
    input.left_left_line.angle_diff       = 2048;               // x/2048-1=0
    input.left_left_line.horizon_curve    = 2048;               // x-2047=1
    input.left_line.timestamp.sec         = 1;
    input.left_line.timestamp.nsec        = 2;
    input.left_line.confidence            = 32;          // x/64=0.5
    input.left_line.id                    = 10;          // 10
    input.left_line.type                  = 2;           // BoundaryStyle::DASHED
    input.left_line.width                 = 256;         // x/256-0.5=0.5
    input.left_line.color                 = 1;           // BoundaryColor::WHITE
    input.left_line.dx_begin              = 4;           // x/4=1
    input.left_line.dx_end                = 100;         // x/4=25
    input.left_line.dy                    = 2048 + 512;  // x/256-8=2
    input.left_line.angle_diff            = 2048;        // x/2048-1=0
    input.left_line.horizon_curve         = 2048;        // x-2047=1
    input.right_line.timestamp.sec        = 1;
    input.right_line.timestamp.nsec       = 2;
    input.right_line.confidence           = 32;         // x/64=0.5
    input.right_line.id                   = 11;         // 11
    input.right_line.type                 = 2;          // BoundaryStyle::DASHED
    input.right_line.width                = 256;        // x/256-0.5=0.5
    input.right_line.color                = 1;          // BoundaryColor::WHITE
    input.right_line.dx_begin             = 4;          // x/4=1
    input.right_line.dx_end               = 100;        // x/4=25
    input.right_line.dy                   = 2048 - 64;  // x/256-8=-0.25
    input.right_line.angle_diff           = 2048;       // x/2048-1=0
    input.right_line.horizon_curve        = 2048;       // x-2047=1
    input.right_right_line.timestamp.sec  = 1;
    input.right_right_line.timestamp.nsec = 2;
    input.right_right_line.confidence     = 32;                 // x/64=0.5
    input.right_right_line.id             = 12;                 // 12
    input.right_right_line.type           = 2;                  // BoundaryStyle::DASHED
    input.right_right_line.width          = 256;                // x/256-0.5=0.5
    input.right_right_line.color          = 1;                  // BoundaryColor::WHITE
    input.right_right_line.dx_begin       = 4;                  // x/4=1
    input.right_right_line.dx_end         = 100;                // x/4=25
    input.right_right_line.dy             = 2048 - 512 - 1024;  // x/256-8=-6
    input.right_right_line.angle_diff     = 2048;               // x/2048-1=0
    input.right_right_line.horizon_curve  = 2048;               // x-2047=1
    RoadFrameType output3;
    driver.ConvertToRoadFrameWithTransform(input, output3);
    ASSERT_FLOAT_EQ(output3.GetTimestamp().GetSec(), 0);
    ASSERT_FLOAT_EQ(output3.GetTimestamp().GetNsec(), 0);
    auto lbd3 = output3.at(2);
    ASSERT_EQ(lbd3.GetStyle(), holo::common::BoundaryStyle::DASHED);
    ASSERT_EQ(lbd3.GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(lbd3.GetConfidence(), 50);
    std::pair<float32_t, float32_t> range3 = lbd3.GetCoordinateRange();
    ASSERT_FLOAT_EQ(range3.first, 1);
    ASSERT_FLOAT_EQ(range3.second, 25);
    ASSERT_EQ(lbd3.GetWidth(), 50);
    p0 = lbd3.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), -0.25f);
    /*  */
    (void)memset(&input, 0, sizeof(struct MpcLinesRawData));
    input.left_left_line.timestamp.sec    = 1;
    input.left_left_line.timestamp.nsec   = 2;
    input.left_left_line.confidence       = 0;            // x/64=0
    input.left_left_line.id               = 9;            // 9
    input.left_left_line.type             = 2;            // BoundaryStyle::DASHED
    input.left_left_line.width            = 256;          // x/256-0.5=0.5
    input.left_left_line.color            = 1;            // BoundaryColor::WHITE
    input.left_left_line.dx_begin         = 4;            // x/4=1
    input.left_left_line.dx_end           = 100;          // x/4=25
    input.left_left_line.dy               = 2048 + 1024;  // x/256-8=4
    input.left_left_line.angle_diff       = 2048;         // x/2048-1=0
    input.left_left_line.horizon_curve    = 2048;         // x-2047=1
    input.left_line.timestamp.sec         = 1;
    input.left_line.timestamp.nsec        = 2;
    input.left_line.confidence            = 32;          // x/64=0.5
    input.left_line.id                    = 10;          // 10
    input.left_line.type                  = 2;           // BoundaryStyle::DASHED
    input.left_line.width                 = 256;         // x/256-0.5=0.5
    input.left_line.color                 = 1;           // BoundaryColor::WHITE
    input.left_line.dx_begin              = 4;           // x/4=1
    input.left_line.dx_end                = 100;         // x/4=25
    input.left_line.dy                    = 2048 - 120;  // x/256-8=-0.46875
    input.left_line.angle_diff            = 2048;        // x/2048-1=0
    input.left_line.horizon_curve         = 2048;        // x-2047=1
    input.right_line.timestamp.sec        = 1;
    input.right_line.timestamp.nsec       = 2;
    input.right_line.confidence           = 32;          // x/64=0.5
    input.right_line.id                   = 11;          // 11
    input.right_line.type                 = 2;           // BoundaryStyle::DASHED
    input.right_line.width                = 256;         // x/256-0.5=0.5
    input.right_line.color                = 1;           // BoundaryColor::WHITE
    input.right_line.dx_begin             = 4;           // x/4=1
    input.right_line.dx_end               = 100;         // x/4=25
    input.right_line.dy                   = 2048 - 512;  // x/256-8=-2
    input.right_line.angle_diff           = 2048;        // x/2048-1=0
    input.right_line.horizon_curve        = 2048;        // x-2047=1
    input.right_right_line.timestamp.sec  = 1;
    input.right_right_line.timestamp.nsec = 2;
    input.right_right_line.confidence     = 32;                 // x/64=0.5
    input.right_right_line.id             = 12;                 // 12
    input.right_right_line.type           = 2;                  // BoundaryStyle::DASHED
    input.right_right_line.width          = 256;                // x/256-0.5=0.5
    input.right_right_line.color          = 1;                  // BoundaryColor::WHITE
    input.right_right_line.dx_begin       = 4;                  // x/4=1
    input.right_right_line.dx_end         = 100;                // x/4=25
    input.right_right_line.dy             = 2048 - 512 - 1024;  // x/256-8=-6
    input.right_right_line.angle_diff     = 2048;               // x/2048-1=0
    input.right_right_line.horizon_curve  = 2048;               // x-2047=1
    RoadFrameType output4;
    driver.ConvertToRoadFrameWithTransform(input, output4);
    ASSERT_FLOAT_EQ(output4.GetTimestamp().GetSec(), 0);
    ASSERT_FLOAT_EQ(output4.GetTimestamp().GetNsec(), 0);
    auto lbd4 = output4.at(2);
    ASSERT_EQ(lbd4.GetStyle(), holo::common::BoundaryStyle::DASHED);
    ASSERT_EQ(lbd4.GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(lbd4.GetConfidence(), 50);
    std::pair<float32_t, float32_t> range4 = lbd4.GetCoordinateRange();
    ASSERT_FLOAT_EQ(range4.first, 1);
    ASSERT_FLOAT_EQ(range4.second, 25);
    ASSERT_EQ(lbd4.GetWidth(), 50);
    p0 = lbd4.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), -0.46875f);
}

TEST(BoschMpcDriverSomeip, ConvertToRoadFrameWithTransform3)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    struct MpcLinesRawData            input;
    (void)memset(&input, 0, sizeof(struct MpcLinesRawData));
    input.left_left_line.timestamp.sec    = 1;
    input.left_left_line.timestamp.nsec   = 2;
    input.left_left_line.confidence       = 32;                 // x/64=0.5
    input.left_left_line.id               = 9;                  // 9
    input.left_left_line.type             = 2;                  // BoundaryStyle::DASHED
    input.left_left_line.width            = 256;                // x/256-0.5=0.5
    input.left_left_line.color            = 1;                  // BoundaryColor::WHITE
    input.left_left_line.dx_begin         = 4;                  // x/4=1
    input.left_left_line.dx_end           = 100;                // x/4=25
    input.left_left_line.dy               = 2048 + 512 + 1024;  // x/256-8=6
    input.left_left_line.angle_diff       = 2048;               // x/2048-1=0
    input.left_left_line.horizon_curve    = 2048;               // x-2047=1
    input.left_line.timestamp.sec         = 1;
    input.left_line.timestamp.nsec        = 2;
    input.left_line.confidence            = 0;           // x/64=0
    input.left_line.id                    = 10;          // 10
    input.left_line.type                  = 2;           // BoundaryStyle::DASHED
    input.left_line.width                 = 256;         // x/256-0.5=0.5
    input.left_line.color                 = 1;           // BoundaryColor::WHITE
    input.left_line.dx_begin              = 4;           // x/4=1
    input.left_line.dx_end                = 100;         // x/4=25
    input.left_line.dy                    = 2048 + 512;  // x/256-8=2
    input.left_line.angle_diff            = 2048;        // x/2048-1=0
    input.left_line.horizon_curve         = 2048;        // x-2047=1
    input.right_line.timestamp.sec        = 1;
    input.right_line.timestamp.nsec       = 2;
    input.right_line.confidence           = 0;           // x/64=0
    input.right_line.id                   = 11;          // 11
    input.right_line.type                 = 2;           // BoundaryStyle::DASHED
    input.right_line.width                = 256;         // x/256-0.5=0.5
    input.right_line.color                = 1;           // BoundaryColor::WHITE
    input.right_line.dx_begin             = 4;           // x/4=1
    input.right_line.dx_end               = 100;         // x/4=25
    input.right_line.dy                   = 2048 - 512;  // x/256-8=-2
    input.right_line.angle_diff           = 2048;        // x/2048-1=0
    input.right_line.horizon_curve        = 2048;        // x-2047=1
    input.right_right_line.timestamp.sec  = 1;
    input.right_right_line.timestamp.nsec = 2;
    input.right_right_line.confidence     = 32;                 // x/64=0.5
    input.right_right_line.id             = 12;                 // 12
    input.right_right_line.type           = 2;                  // BoundaryStyle::DASHED
    input.right_right_line.width          = 256;                // x/256-0.5=0.5
    input.right_right_line.color          = 1;                  // BoundaryColor::WHITE
    input.right_right_line.dx_begin       = 4;                  // x/4=1
    input.right_right_line.dx_end         = 100;                // x/4=25
    input.right_right_line.dy             = 2048 - 512 - 1024;  // x/256-8=-6
    input.right_right_line.angle_diff     = 2048;               // x/2048-1=0
    input.right_right_line.horizon_curve  = 2048;               // x-2047=1
    RoadFrameType output;
    driver.ConvertToRoadFrameWithTransform(input, output);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetSec(), 0);
    ASSERT_FLOAT_EQ(output.GetTimestamp().GetNsec(), 0);
    auto lbd = output.at(0);
    ASSERT_FLOAT_EQ(lbd.GetConfidence(), 50);
    holo::geometry::Point2f p0 = lbd.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p0.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p0.GetY(), 6.0f);
    auto lbd2 = output.at(3);
    ASSERT_FLOAT_EQ(lbd2.GetConfidence(), 50);
    holo::geometry::Point2f p1 = lbd2.GetSampleByCoordinate(0.0f);
    ASSERT_FLOAT_EQ(p1.GetX(), 0.0f);
    ASSERT_FLOAT_EQ(p1.GetY(), -6.0f);
}

static void RfCallback(const RoadFrameType& roadframe, RoadFrameType& copy, bool& called)
{
    copy   = roadframe;
    called = true;
}

TEST(BoschMpcDriverSomeip, ParseLaneboundaries)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    RoadFrameType                     roadframe;
    bool                              called = false;
    auto h = std::bind(&RfCallback, std::placeholders::_1, std::ref(roadframe), std::ref(called));
    driver.InstallCallback(h);
    uint8_t data[1024] = {0};
    (void)std::memset(data, 0x00, sizeof(data));
    bool b = driver.ParseLaneboundaries(data, 100);
    ASSERT_FALSE(b);
    ASSERT_FALSE(called);
    struct MpcLinesRawData test_lines;
    (void)memset(&test_lines, 0, sizeof(struct MpcLinesRawData));
    test_lines.left_line.timestamp.sec  = 1;
    test_lines.left_line.timestamp.nsec = 2;
    test_lines.left_line.confidence     = 32;          // x/64=0.5
    test_lines.left_line.id             = 10;          // 10
    test_lines.left_line.type           = 2;           // BoundaryStyle::DASHED
    test_lines.left_line.width          = 256;         // x/256-0.5=0.5
    test_lines.left_line.color          = 1;           // BoundaryColor::WHITE
    test_lines.left_line.dx_begin       = 4;           // x/4=1
    test_lines.left_line.dx_end         = 100;         // x/4=25
    test_lines.left_line.dy             = 2048 + 512;  // x/256-8=2
    test_lines.left_line.angle_diff     = 2048;        // x/2048-1=0
    test_lines.left_line.horizon_curve  = 2048;        // x-2047=1
    mpc_lines_raw_data_serialize(&test_lines, data, sizeof(data));
    b = driver.ParseLaneboundaries(data, sizeof(data));
    ASSERT_TRUE(b);
    ASSERT_TRUE(called);
    ASSERT_FLOAT_EQ(roadframe.GetTimestamp().GetSec(), 1);
    ASSERT_FLOAT_EQ(roadframe.GetTimestamp().GetNsec(), 2);
    auto lbd = roadframe.at(1);
    ASSERT_EQ(lbd.GetStyle(), holo::common::BoundaryStyle::DASHED);
    ASSERT_EQ(lbd.GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_EQ(lbd.GetConfidence(), 50);
    std::pair<float32_t, float32_t> range = lbd.GetCoordinateRange();
    ASSERT_FLOAT_EQ(range.first, 1);
    ASSERT_FLOAT_EQ(range.second, 25);
    ASSERT_EQ(lbd.GetWidth(), 50);
}

TEST(BoschMpcDriverSomeip, ParseData)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    RoadFrameType                     roadframe;
    bool                              called = false;
    auto h = std::bind(&RfCallback, std::placeholders::_1, std::ref(roadframe), std::ref(called));
    driver.InstallCallback(h);
    uint8_t data[1024];
    (void)std::memset(data, 0x00, sizeof(data));
    SomeipPacketType packet;
    packet.SetMethodId(0x20);
    packet.SetMsgLength(8 + sizeof(data));
    packet.SetPayload(0, data, sizeof(data));
    driver.ParseData(packet);
    ASSERT_TRUE(called);
    ASSERT_EQ(roadframe.at(0).GetConfidence(), 0);
    ASSERT_EQ(roadframe.at(1).GetConfidence(), 0);
    ASSERT_EQ(roadframe.at(2).GetConfidence(), 0);
    ASSERT_EQ(roadframe.at(3).GetConfidence(), 0);
    struct MpcLinesRawData test_lines;
    (void)memset(&test_lines, 0, sizeof(struct MpcLinesRawData));
    test_lines.left_line.timestamp.sec  = 1;
    test_lines.left_line.timestamp.nsec = 2;
    test_lines.left_line.confidence     = 32;          // x/64=0.5
    test_lines.left_line.id             = 10;          // 10
    test_lines.left_line.type           = 2;           // BoundaryStyle::DASHED
    test_lines.left_line.width          = 256;         // x/256-0.5=0.5
    test_lines.left_line.color          = 1;           // BoundaryColor::WHITE
    test_lines.left_line.dx_begin       = 4;           // x/4=1
    test_lines.left_line.dx_end         = 100;         // x/4=25
    test_lines.left_line.dy             = 2048 + 512;  // x/256-8=2
    test_lines.left_line.angle_diff     = 2048;        // x/2048-1=0
    test_lines.left_line.horizon_curve  = 2048;        // x-2047=1
    uint32_t ser_size                   = mpc_lines_raw_data_serialize(&test_lines, data, sizeof(data));
    ASSERT_TRUE(ser_size > 0);
    packet.SetMethodId(0x20);
    packet.SetMsgLength(8 + 4 + ser_size);
    packet.SetPayload(4, data, ser_size);
    driver.ParseData(packet);
    ASSERT_TRUE(called);
    ASSERT_FLOAT_EQ(roadframe.GetTimestamp().GetSec(), 1);
    ASSERT_FLOAT_EQ(roadframe.GetTimestamp().GetNsec(), 2);
    auto lbd = roadframe.at(1);
    ASSERT_EQ(lbd.GetStyle(), holo::common::BoundaryStyle::DASHED);
    ASSERT_EQ(lbd.GetColor(), holo::common::BoundaryColor::WHITE);
    ASSERT_FLOAT_EQ(lbd.GetConfidence(), 50);
}

TEST(BoschMpcDriverSomeip, ParseDataNull)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    uint8_t                           data[1024];
    (void)std::memset(data, 0x00, sizeof(data));
    SomeipPacketType packet;
    packet.SetMethodId(0x00);
    ASSERT_NO_THROW(driver.ParseData(packet));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
