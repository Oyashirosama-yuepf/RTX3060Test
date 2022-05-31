#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/me3/structure/me3_laneboundary.h>

TEST(MobileyeLaneBoundary, Construtor)
{
    holo::sensors::mobileye::MobileyeLaneBoundary b;

    ASSERT_EQ(b.GetTimestamp().GetSec(), 0u);
    ASSERT_EQ(b.GetTimestamp().GetNsec(), 0u);
}

TEST(MobileyeLaneBoundary, Copy)
{
    holo::sensors::mobileye::MobileyeLaneBoundary b1;
    holo::common::Timestamp                       input_timestamp(222, 333);
    b1.SetTimestamp(input_timestamp);
    b1.SetC0(0.0);
    b1.SetC1(1.1);
    b1.SetC2(2.2);
    b1.SetC3(3.3);
    b1.SetRangeStart(4.4);
    b1.SetRangeEnd(5.5);
    b1.SetMarkWidth(0.15);
    b1.SetTlc(2.0);
    b1.SetLocation(0);
    b1.SetType(1);
    b1.SetColor(2);
    b1.SetQuality(3);
    b1.SetCrossing(false);
    b1.SetPart0Valid(true);
    b1.SetPart1Valid(true);
    b1.SetPart2Valid(true);

    holo::sensors::mobileye::MobileyeLaneBoundary b2(b1);

    ASSERT_EQ(b2.GetTimestamp().GetSec(), 222);
    ASSERT_EQ(b2.GetTimestamp().GetNsec(), 333);
    ASSERT_FLOAT_EQ(b2.GetC0(), 0.0);
    ASSERT_FLOAT_EQ(b2.GetC1(), 1.1);
    ASSERT_FLOAT_EQ(b2.GetC2(), 2.2);
    ASSERT_FLOAT_EQ(b2.GetC3(), 3.3);
    ASSERT_FLOAT_EQ(b2.GetRangeStart(), 4.4);
    ASSERT_FLOAT_EQ(b2.GetRangeEnd(), 5.5);
    ASSERT_FLOAT_EQ(b2.GetMarkWidth(), 0.15);
    ASSERT_FLOAT_EQ(b2.GetTlc(), 2.0);
    ASSERT_EQ(b2.GetLocation(), 0);
    ASSERT_EQ(b2.GetType(), 1);
    ASSERT_EQ(b2.GetColor(), 2);
    ASSERT_EQ(b2.GetQuality(), 3);
    ASSERT_FALSE(b2.GetCrossing());
    ASSERT_TRUE(b2.GetPart0Valid());
    ASSERT_TRUE(b2.GetPart1Valid());
    ASSERT_TRUE(b2.GetPart2Valid());
    ASSERT_TRUE(b2.IsAllPartsValid());
}

TEST(MobileyeLaneBoundary, OpreatorEquale)
{
    holo::sensors::mobileye::MobileyeLaneBoundary b1;
    holo::common::Timestamp                       input_timestamp(222, 333);
    b1.SetTimestamp(input_timestamp);

    holo::sensors::mobileye::MobileyeLaneBoundary b2 = b1;

    ASSERT_EQ(b2.GetTimestamp().GetSec(), 222);
    ASSERT_EQ(b2.GetTimestamp().GetNsec(), 333);
}

using LaneBoundaryTyp = holo::common::LaneBoundary<holo::numerics::Polynomial<float, 3>>;

TEST(MobileyeLaneBoundary, ConvertToHoloLaneBoundary1)
{
    std::shared_ptr<LaneBoundaryTyp>              lbd       = nullptr;
    auto                                          extrinsic = holo::common::Extrinsicf();
    holo::sensors::mobileye::MobileyeLaneBoundary b1;
    b1.SetRangeStart(0.0f);
    b1.SetRangeEnd(0.0f);
    b1.ConvertToHoloLaneBoundary(lbd, extrinsic);
    ASSERT_TRUE(lbd != nullptr);
    auto range = lbd->GetCoordinateRange();
    ASSERT_EQ(0.0, range.first);
    ASSERT_EQ(0.0, range.second);
}

TEST(MobileyeLaneBoundary, ConvertToHoloLaneBoundary2)
{
    std::shared_ptr<LaneBoundaryTyp>              lbd       = nullptr;
    auto                                          extrinsic = holo::common::Extrinsicf();
    holo::sensors::mobileye::MobileyeLaneBoundary b1;
    b1.SetRangeStart(0.0f);
    b1.SetRangeEnd(25.0f);
    b1.ConvertToHoloLaneBoundary(lbd, extrinsic);
    ASSERT_TRUE(lbd != nullptr);
    auto range = lbd->GetCoordinateRange();
    ASSERT_EQ(0.0, range.first);
    ASSERT_EQ(25.0, range.second);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
