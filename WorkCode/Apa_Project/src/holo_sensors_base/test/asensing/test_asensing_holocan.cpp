#include <gtest/gtest.h>
#include <holo/sensors/asensing/asensing_holocan.h>
#include <holo/sensors/utils/sensors_utils.h>

using namespace holo;
using namespace holo::sensors::asensing;
using holo::sensors::asensing::GpsFlag;
using holo::sensors::asensing::InitStatusAll;

static void Callback0(const holo::common::Imud& input, holo::common::Imud& output, bool& called)
{
    output = input;
    called = true;
}

static void PositionCallback0(const holo::common::GnssPvt& input, holo::common::GnssPvt& output, bool& called)
{
    output = input;
    called = true;
}

static void PositionCallback1(const holo::common::GnssPvt& input, holo::common::GnssPvt& output, bool& called)
{
    output = input;
    called = true;
}

static void FillAcc(uint8_t* FillData, uint16_t Acc_x, uint16_t Acc_y, uint16_t Acc_z)
{
    if (FillData == NULL)
    {
        return;
    }

    /* ID */
    FillData[0] = (0x500 >> 24) & 0xff;
    FillData[1] = (0x500 >> 16) & 0xff;
    FillData[2] = (0x500 >> 8) & 0xff;
    FillData[3] = (0x500 >> 0) & 0xff;

    FillData[4]  = (Acc_x >> 8) & 0xff;
    FillData[5]  = (Acc_x >> 0) & 0xff;
    FillData[6]  = (Acc_y >> 8) & 0xff;
    FillData[7]  = (Acc_y >> 0) & 0xff;
    FillData[8]  = (Acc_z >> 8) & 0xff;
    FillData[9]  = (Acc_z >> 0) & 0xff;
    FillData[10] = 0;
    FillData[11] = 0;
}

static void FillGYRO(uint8_t* FillData, uint16_t GYRO_x, uint16_t GYRO_y, uint16_t GYRO_z)
{
    if (FillData == NULL)
    {
        return;
    }

    /* ID */
    FillData[0] = (0x501 >> 24) & 0xff;
    FillData[1] = (0x501 >> 16) & 0xff;
    FillData[2] = (0x501 >> 8) & 0xff;
    FillData[3] = (0x501 >> 0) & 0xff;

    FillData[4]  = (GYRO_x >> 8) & 0xff;
    FillData[5]  = (GYRO_x >> 0) & 0xff;
    FillData[6]  = (GYRO_y >> 8) & 0xff;
    FillData[7]  = (GYRO_y >> 0) & 0xff;
    FillData[8]  = (GYRO_z >> 8) & 0xff;
    FillData[9]  = (GYRO_z >> 0) & 0xff;
    FillData[10] = 0;
    FillData[11] = 0;
}

static void FillHeadingPitchRoll(uint8_t* FillData, uint16_t PitchAngle, uint16_t RollAngle, uint16_t HeadingAngle)
{
    if (FillData == NULL)
    {
        return;
    }

    /* ID */
    FillData[0] = (0x502 >> 24) & 0xff;
    FillData[1] = (0x502 >> 16) & 0xff;
    FillData[2] = (0x502 >> 8) & 0xff;
    FillData[3] = (0x502 >> 0) & 0xff;

    FillData[4]  = (PitchAngle >> 8) & 0xff;
    FillData[5]  = (PitchAngle >> 0) & 0xff;
    FillData[6]  = (RollAngle >> 8) & 0xff;
    FillData[7]  = (RollAngle >> 0) & 0xff;
    FillData[8]  = (HeadingAngle >> 8) & 0xff;
    FillData[9]  = (HeadingAngle >> 0) & 0xff;
    FillData[10] = 0;
    FillData[11] = 0;
}

static void FillHeightAndTime(uint8_t* FillData, uint32_t Height, uint32_t Time)
{
    if (FillData == NULL)
    {
        return;
    }

    /* ID */
    FillData[0] = (0x503 >> 24) & 0xff;
    FillData[1] = (0x503 >> 16) & 0xff;
    FillData[2] = (0x503 >> 8) & 0xff;
    FillData[3] = (0x503 >> 0) & 0xff;

    FillData[4]  = (Height >> 24) & 0xff;
    FillData[5]  = (Height >> 16) & 0xff;
    FillData[6]  = (Height >> 8) & 0xff;
    FillData[7]  = (Height >> 0) & 0xff;
    FillData[8]  = (Time >> 24) & 0xff;
    FillData[9]  = (Time >> 16) & 0xff;
    FillData[10] = (Time >> 8) & 0xff;
    FillData[11] = (Time >> 0) & 0xff;
}

static void FillLatitudeLongitude(uint8_t* FillData, uint32_t Latitude, uint32_t Longitude)
{
    if (FillData == NULL)
    {
        return;
    }

    /* ID */
    FillData[0] = (0x504 >> 24) & 0xff;
    FillData[1] = (0x504 >> 16) & 0xff;
    FillData[2] = (0x504 >> 8) & 0xff;
    FillData[3] = (0x504 >> 0) & 0xff;

    FillData[4]  = (Latitude >> 24) & 0xff;
    FillData[5]  = (Latitude >> 16) & 0xff;
    FillData[6]  = (Latitude >> 8) & 0xff;
    FillData[7]  = (Latitude >> 0) & 0xff;
    FillData[8]  = (Longitude >> 24) & 0xff;
    FillData[9]  = (Longitude >> 16) & 0xff;
    FillData[10] = (Longitude >> 8) & 0xff;
    FillData[11] = (Longitude >> 0) & 0xff;
}

static void FillSpeed(uint8_t* FillData, uint16_t NorthSpeed, uint16_t EastSpeed, uint16_t ToGroundSpeed)
{
    if (FillData == NULL)
    {
        return;
    }

    /* ID */
    FillData[0] = (0x505 >> 24) & 0xff;
    FillData[1] = (0x505 >> 16) & 0xff;
    FillData[2] = (0x505 >> 8) & 0xff;
    FillData[3] = (0x505 >> 0) & 0xff;

    FillData[4]  = (NorthSpeed >> 8) & 0xff;
    FillData[5]  = (NorthSpeed >> 0) & 0xff;
    FillData[6]  = (EastSpeed >> 8) & 0xff;
    FillData[7]  = (EastSpeed >> 0) & 0xff;
    FillData[8]  = (ToGroundSpeed >> 8) & 0xff;
    FillData[9]  = (ToGroundSpeed >> 0) & 0xff;
    FillData[10] = 0;
    FillData[11] = 0;
}

static void FillDataInfo(uint8_t* FillData, uint8_t GpsFlgPos, uint8_t NumSV, uint8_t GpsFlgHeading, uint8_t GpsAge,
                         uint8_t CarStatus, uint8_t InsStatus)
{
    if (FillData == NULL)
    {
        return;
    }

    /* ID */
    FillData[0] = (0x506 >> 24) & 0xff;
    FillData[1] = (0x506 >> 16) & 0xff;
    FillData[2] = (0x506 >> 8) & 0xff;
    FillData[3] = (0x506 >> 0) & 0xff;

    FillData[4]  = GpsFlgPos;
    FillData[5]  = NumSV;
    FillData[6]  = GpsFlgHeading;
    FillData[7]  = GpsAge;
    FillData[8]  = CarStatus;
    FillData[9]  = 0;
    FillData[10] = 0;
    FillData[11] = InsStatus;
}

static void FillStd(uint8_t* FillData, uint16_t StdLat, uint16_t StdLon, uint16_t StdHeight, uint16_t StdHeading)
{
    if (FillData == NULL)
    {
        return;
    }

    /* ID */
    FillData[0] = (0x507 >> 24) & 0xff;
    FillData[1] = (0x507 >> 16) & 0xff;
    FillData[2] = (0x507 >> 8) & 0xff;
    FillData[3] = (0x507 >> 0) & 0xff;

    FillData[4]  = (StdLat >> 8) & 0xff;
    FillData[5]  = (StdLat >> 0) & 0xff;
    FillData[6]  = (StdLon >> 8) & 0xff;
    FillData[7]  = (StdLon >> 0) & 0xff;
    FillData[8]  = (StdHeight >> 8) & 0xff;
    FillData[9]  = (StdHeight >> 0) & 0xff;
    FillData[10] = (StdHeading >> 8) & 0xff;
    FillData[11] = (StdHeading >> 0) & 0xff;
}

static void FillHeightAndGpsWeek(uint8_t* FillData, uint32_t GpsWeek)
{
    if (FillData == NULL)
    {
        return;
    }

    /* ID */
    FillData[0] = (0x50A >> 24) & 0xff;
    FillData[1] = (0x50A >> 16) & 0xff;
    FillData[2] = (0x50A >> 8) & 0xff;
    FillData[3] = (0x50A >> 0) & 0xff;

    FillData[4]  = 0;
    FillData[5]  = 0;
    FillData[6]  = 0;
    FillData[7]  = 0;
    FillData[8]  = (GpsWeek >> 24) & 0xff;
    FillData[9]  = (GpsWeek >> 16) & 0xff;
    FillData[10] = (GpsWeek >> 8) & 0xff;
    FillData[11] = (GpsWeek >> 0) & 0xff;
}

static void FillInvalidId(uint8_t* FillData, uint32_t CanId)
{
    if (FillData == NULL)
    {
        return;
    }

    /* ID */
    FillData[0] = (CanId >> 24) & 0xff;
    FillData[1] = (CanId >> 16) & 0xff;
    FillData[2] = (CanId >> 8) & 0xff;
    FillData[3] = (CanId >> 0) & 0xff;

    FillData[4]  = (20 >> 8) & 0xff;
    FillData[5]  = (20 >> 0) & 0xff;
    FillData[6]  = (30 >> 8) & 0xff;
    FillData[7]  = (30 >> 0) & 0xff;
    FillData[8]  = (40 >> 8) & 0xff;
    FillData[9]  = (40 >> 0) & 0xff;
    FillData[10] = (50 >> 8) & 0xff;
    FillData[11] = (50 >> 0) & 0xff;
}

TEST(AsensingDriverT0, AsensingDriverT_HoloCanPacket0)
{
    Extrinsicf                                     extrinsic;
    AsensingDriverT<HoloCanPacket>                 driver(extrinsic);
    holo::common::Imud                             imu_out;
    holo::common::GnssPvt                          pvt_wgs_out;
    holo::common::GnssPvt                          pvt_gcj_out;
    bool                                           imu_called  = false;
    bool                                           pos0_called = false;
    bool                                           pos1_called = false;
    std::function<void(const holo::common::Imud&)> imu_handler =
        std::bind(&Callback0, std::placeholders::_1, std::ref(imu_out), std::ref(imu_called));
    driver.InstallCallback(imu_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_wgs_handler =
        std::bind(&PositionCallback0, std::placeholders::_1, std::ref(pvt_wgs_out), std::ref(pos0_called));
    driver.InstallPositionCallback(pvt_wgs_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_gcj_handler =
        std::bind(&PositionCallback1, std::placeholders::_1, std::ref(pvt_gcj_out), std::ref(pos1_called));
    driver.InstallPositionTranslationCallback(pvt_gcj_handler);

    uint8_t raw_data[28];
    (void)std::memcpy(raw_data, "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    /* sec_ */
    raw_data[20] = (12345678 >> 24) & 0xff;
    raw_data[21] = (12345678 >> 16) & 0xff;
    raw_data[22] = (12345678 >> 8) & 0xff;
    raw_data[23] = (12345678 >> 0) & 0xff;

    /* nsec_ */
    raw_data[24] = (87654321 >> 24) & 0xff;
    raw_data[25] = (87654321 >> 16) & 0xff;
    raw_data[26] = (87654321 >> 8) & 0xff;
    raw_data[27] = (87654321 >> 0) & 0xff;

    /* param is net value */
    FillAcc(&raw_data[8], 10000, 20000, 30000);
    HoloCanPacket packet;
    uint32_t      des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillGYRO(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeadingPitchRoll(&raw_data[8], 0, 0, 0);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeightAndTime(&raw_data[8], 20000000, 5);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillLatitudeLongitude(&raw_data[8], 2300000000, 2800000000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillDataInfo(&raw_data[8], static_cast<uint8_t>(GpsFlag::NARROW), 20, static_cast<uint8_t>(GpsFlag::NARROW), 4, 1,
                 static_cast<uint8_t>(InitStatusAll::ALL_INIT));
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillSpeed(&raw_data[8], 7000, 8000, 9000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillStd(&raw_data[8], 500, 600, 700, 800);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillHeightAndGpsWeek(&raw_data[8], 2159);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    static float64_t constexpr G_ACCEL_T = 9.8;
    static int32_t const NSEC_PER_MSEC   = 1000000;
    static int32_t const MSEC_PER_SEC    = 1000;

    ASSERT_TRUE(imu_called);
    ASSERT_EQ(imu_out.GetCoordinate(), static_cast<holo::common::Coordinate>(holo::common::Coordinate::BODY));
    ASSERT_EQ(imu_out.GetTimestamp().GetSec(), 12345678);
    ASSERT_EQ(imu_out.GetTimestamp().GetNsec(), 87654321);

    ASSERT_FLOAT_EQ(imu_out.GetLinearAcceleration<holo::geometry::Point3d>()[0], -2.779296875 * G_ACCEL_T);
    ASSERT_FLOAT_EQ(imu_out.GetLinearAcceleration<holo::geometry::Point3d>()[1], -1.55859375 * (-G_ACCEL_T));
    ASSERT_FLOAT_EQ(imu_out.GetLinearAcceleration<holo::geometry::Point3d>()[2], -0.337890625 * (-G_ACCEL_T));
    ASSERT_FLOAT_EQ(imu_out.GetAngularVelocity<holo::geometry::Point3d>()[0],
                    holo::geometry::Radian<float64_t>(-173.707));
    ASSERT_FLOAT_EQ(imu_out.GetAngularVelocity<holo::geometry::Point3d>()[1],
                    holo::geometry::Radian<float64_t>(97.414));
    ASSERT_FLOAT_EQ(imu_out.GetAngularVelocity<holo::geometry::Point3d>()[2],
                    holo::geometry::Radian<float64_t>(21.121));

    ASSERT_TRUE(pos0_called);
    ASSERT_EQ(pvt_wgs_out.GetCoordinate(), holo::common::Coordinate::Wgs84Coordinate());
    ASSERT_EQ(pvt_wgs_out.GetMode(), GnssPvt::Mode::RTK_INT_FIX);
    ASSERT_TRUE(pvt_wgs_out.IsCovValid() && pvt_wgs_out.IsValid());
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetHeight(), 10000);

    holo::common::Timestamp gps_stamp(SEC_PER_WEEK * 2159 + 5 / MSEC_PER_SEC, (5 % MSEC_PER_SEC) * NSEC_PER_MSEC);
    holo::common::Timestamp utc_stamp;
    holo::common::Timestamp::GpsToUtc(gps_stamp, utc_stamp);
    ASSERT_EQ(pvt_wgs_out.GetTimestamp().GetSec(), utc_stamp.GetSec());
    ASSERT_EQ(pvt_wgs_out.GetTimestamp().GetNsec(), utc_stamp.GetNsec());

    ASSERT_FLOAT_EQ(pvt_wgs_out.GetLatitude(), 50);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetLongitude(), 100);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetVelocityEast(), -75.5864);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetVelocityNorth(), -78.6381);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetVelocityUp(), 72.5347);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetLatitudeCov(), 0.5);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetLongitudeCov(), 0.6);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetHeightCov(), 0.7);

    ASSERT_TRUE(pos1_called);
    ASSERT_EQ(pvt_gcj_out.GetCoordinate(),
              static_cast<holo::common::Coordinate>(holo::common::Coordinate::Gcj02Coordinate()));
    float64_t lat = 50;
    float64_t lon = 100;
    ASSERT_TRUE(holo::sensors::ConvertWgs84ToGcj02(lat, lon));
    ASSERT_FLOAT_EQ(pvt_gcj_out.GetLatitude(), lat);
    ASSERT_FLOAT_EQ(pvt_gcj_out.GetLongitude(), lon);
}

TEST(AsensingDriverT1, AsensingDriverT_HoloCanPacket1)
{
    Extrinsicf                                     extrinsic;
    AsensingDriverT<HoloCanPacket>                 driver(extrinsic);
    holo::common::Imud                             imu_out;
    holo::common::GnssPvt                          pvt_wgs_out;
    holo::common::GnssPvt                          pvt_gcj_out;
    bool                                           imu_called  = false;
    bool                                           pos0_called = false;
    bool                                           pos1_called = false;
    std::function<void(const holo::common::Imud&)> imu_handler =
        std::bind(&Callback0, std::placeholders::_1, std::ref(imu_out), std::ref(imu_called));
    driver.InstallCallback(imu_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_wgs_handler =
        std::bind(&PositionCallback0, std::placeholders::_1, std::ref(pvt_wgs_out), std::ref(pos0_called));
    driver.InstallPositionCallback(pvt_wgs_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_gcj_handler =
        std::bind(&PositionCallback1, std::placeholders::_1, std::ref(pvt_gcj_out), std::ref(pos1_called));
    driver.InstallPositionTranslationCallback(pvt_gcj_handler);

    uint8_t raw_data[28];
    (void)std::memcpy(raw_data, "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    /* sec_ */
    raw_data[20] = (12345678 >> 24) & 0xff;
    raw_data[21] = (12345678 >> 16) & 0xff;
    raw_data[22] = (12345678 >> 8) & 0xff;
    raw_data[23] = (12345678 >> 0) & 0xff;

    /* nsec_ */
    raw_data[24] = (87654321 >> 24) & 0xff;
    raw_data[25] = (87654321 >> 16) & 0xff;
    raw_data[26] = (87654321 >> 8) & 0xff;
    raw_data[27] = (87654321 >> 0) & 0xff;

    HoloCanPacket packet;
    uint32_t      des_size = 0;
    /* param is net value */
    FillAcc(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillInvalidId(&raw_data[8], 0x300);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillGYRO(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeadingPitchRoll(&raw_data[8], 0, 0, 0);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeightAndTime(&raw_data[8], 20000000, 5);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillLatitudeLongitude(&raw_data[8], 2300000000, 2800000000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillDataInfo(&raw_data[8], static_cast<uint8_t>(GpsFlag::NARROW), 20, static_cast<uint8_t>(GpsFlag::NARROW), 4, 1,
                 static_cast<uint8_t>(InitStatusAll::NONE));
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillSpeed(&raw_data[8], 7000, 8000, 9000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillStd(&raw_data[8], 500, 600, 700, 800);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillHeightAndGpsWeek(&raw_data[8], 2159);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    static float64_t constexpr G_ACCEL_T = 9.8;
    static int32_t const NSEC_PER_MSEC   = 1000000;
    static int32_t const MSEC_PER_SEC    = 1000;

    ASSERT_TRUE(imu_called);
    ASSERT_EQ(imu_out.GetCoordinate(), static_cast<holo::common::Coordinate>(holo::common::Coordinate::BODY));
    ASSERT_EQ(imu_out.GetTimestamp().GetSec(), 12345678);
    ASSERT_EQ(imu_out.GetTimestamp().GetNsec(), 87654321);

    ASSERT_FLOAT_EQ(imu_out.GetLinearAcceleration<holo::geometry::Point3d>()[0], -2.779296875 * G_ACCEL_T);
    ASSERT_FLOAT_EQ(imu_out.GetLinearAcceleration<holo::geometry::Point3d>()[1], -1.55859375 * (-G_ACCEL_T));
    ASSERT_FLOAT_EQ(imu_out.GetLinearAcceleration<holo::geometry::Point3d>()[2], -0.337890625 * (-G_ACCEL_T));
    ASSERT_FLOAT_EQ(imu_out.GetAngularVelocity<holo::geometry::Point3d>()[0],
                    holo::geometry::Radian<float64_t>(-173.707));
    ASSERT_FLOAT_EQ(imu_out.GetAngularVelocity<holo::geometry::Point3d>()[1],
                    holo::geometry::Radian<float64_t>(97.414));
    ASSERT_FLOAT_EQ(imu_out.GetAngularVelocity<holo::geometry::Point3d>()[2],
                    holo::geometry::Radian<float64_t>(21.121));

    ASSERT_TRUE(pos0_called);
    ASSERT_EQ(pvt_wgs_out.GetCoordinate(), holo::common::Coordinate::Wgs84Coordinate());
    ASSERT_EQ(pvt_wgs_out.GetMode(), GnssPvt::Mode::NO_POSITION);
    ASSERT_TRUE(!(pvt_wgs_out.IsCovValid() || pvt_wgs_out.IsValid()));
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetHeight(), 10000);

    holo::common::Timestamp gps_stamp(SEC_PER_WEEK * 2159 + 5 / MSEC_PER_SEC, (5 % MSEC_PER_SEC) * NSEC_PER_MSEC);
    holo::common::Timestamp utc_stamp;
    holo::common::Timestamp::GpsToUtc(gps_stamp, utc_stamp);
    ASSERT_EQ(pvt_wgs_out.GetTimestamp().GetSec(), utc_stamp.GetSec());
    ASSERT_EQ(pvt_wgs_out.GetTimestamp().GetNsec(), utc_stamp.GetNsec());

    ASSERT_FLOAT_EQ(pvt_wgs_out.GetLatitude(), 50);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetLongitude(), 100);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetVelocityEast(), -75.5864);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetVelocityNorth(), -78.6381);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetVelocityUp(), 72.5347);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetLatitudeCov(), 0.5);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetLongitudeCov(), 0.6);
    ASSERT_FLOAT_EQ(pvt_wgs_out.GetHeightCov(), 0.7);

    ASSERT_TRUE(pos1_called);
    ASSERT_EQ(pvt_gcj_out.GetCoordinate(),
              static_cast<holo::common::Coordinate>(holo::common::Coordinate::Gcj02Coordinate()));
    float64_t lat = 50;
    float64_t lon = 100;
    ASSERT_TRUE(holo::sensors::ConvertWgs84ToGcj02(lat, lon));
    ASSERT_FLOAT_EQ(pvt_gcj_out.GetLatitude(), lat);
    ASSERT_FLOAT_EQ(pvt_gcj_out.GetLongitude(), lon);
}

TEST(AsensingDriverT2, AsensingDriverT_HoloCanPacket2)
{
    Extrinsicf                                     extrinsic;
    AsensingDriverT<HoloCanPacket>                 driver(extrinsic);
    holo::common::Imud                             imu_out;
    holo::common::GnssPvt                          pvt_wgs_out;
    holo::common::GnssPvt                          pvt_gcj_out;
    bool                                           imu_called  = false;
    bool                                           pos0_called = false;
    bool                                           pos1_called = false;
    std::function<void(const holo::common::Imud&)> imu_handler =
        std::bind(&Callback0, std::placeholders::_1, std::ref(imu_out), std::ref(imu_called));
    driver.InstallCallback(imu_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_wgs_handler =
        std::bind(&PositionCallback0, std::placeholders::_1, std::ref(pvt_wgs_out), std::ref(pos0_called));
    driver.InstallPositionCallback(pvt_wgs_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_gcj_handler =
        std::bind(&PositionCallback1, std::placeholders::_1, std::ref(pvt_gcj_out), std::ref(pos1_called));
    driver.InstallPositionTranslationCallback(pvt_gcj_handler);

    uint8_t raw_data[28];
    (void)std::memcpy(raw_data, "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    /* sec_ */
    raw_data[20] = (12345678 >> 24) & 0xff;
    raw_data[21] = (12345678 >> 16) & 0xff;
    raw_data[22] = (12345678 >> 8) & 0xff;
    raw_data[23] = (12345678 >> 0) & 0xff;

    /* nsec_ */
    raw_data[24] = (87654321 >> 24) & 0xff;
    raw_data[25] = (87654321 >> 16) & 0xff;
    raw_data[26] = (87654321 >> 8) & 0xff;
    raw_data[27] = (87654321 >> 0) & 0xff;

    HoloCanPacket packet;
    uint32_t      des_size = 0;
    /* param is net value */
    FillAcc(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillInvalidId(&raw_data[8], 0x300);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillGYRO(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeadingPitchRoll(&raw_data[8], 0, 0, 0);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeightAndTime(&raw_data[8], 20000000, 5);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillLatitudeLongitude(&raw_data[8], 2300000000, 2800000000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillDataInfo(&raw_data[8], static_cast<uint8_t>(GpsFlag::FIXEDHEIGHT), 20,
                 static_cast<uint8_t>(GpsFlag::FIXEDHEIGHT), 4, 1, static_cast<uint8_t>(InitStatusAll::ALL_INIT));
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillSpeed(&raw_data[8], 7000, 8000, 9000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillStd(&raw_data[8], 500, 600, 700, 800);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillHeightAndGpsWeek(&raw_data[8], 2159);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    ASSERT_EQ(pvt_wgs_out.GetMode(), GnssPvt::Mode::NO_POSITION);
    ASSERT_TRUE(!(pvt_wgs_out.IsCovValid() || pvt_wgs_out.IsValid()));
}

TEST(AsensingDriverT3, AsensingDriverT_HoloCanPacket3)
{
    Extrinsicf                     extrinsic;
    AsensingDriverT<HoloCanPacket> driver(extrinsic);
    holo::common::Imud             imu_out;
    holo::common::GnssPvt          pvt_wgs_out;
    holo::common::GnssPvt          pvt_gcj_out;
    bool                           imu_called  = false;
    bool                           pos0_called = false;

    std::function<void(const holo::common::Imud&)> imu_handler =
        std::bind(&Callback0, std::placeholders::_1, std::ref(imu_out), std::ref(imu_called));
    driver.InstallCallback(imu_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_wgs_handler =
        std::bind(&PositionCallback0, std::placeholders::_1, std::ref(pvt_wgs_out), std::ref(pos0_called));
    driver.InstallPositionCallback(pvt_wgs_handler);

    uint8_t raw_data[28];
    (void)std::memcpy(raw_data, "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    /* sec_ */
    raw_data[20] = (12345678 >> 24) & 0xff;
    raw_data[21] = (12345678 >> 16) & 0xff;
    raw_data[22] = (12345678 >> 8) & 0xff;
    raw_data[23] = (12345678 >> 0) & 0xff;

    /* nsec_ */
    raw_data[24] = (87654321 >> 24) & 0xff;
    raw_data[25] = (87654321 >> 16) & 0xff;
    raw_data[26] = (87654321 >> 8) & 0xff;
    raw_data[27] = (87654321 >> 0) & 0xff;

    HoloCanPacket packet;
    uint32_t      des_size = 0;
    /* param is net value */
    FillAcc(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillInvalidId(&raw_data[8], 0x300);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillGYRO(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeadingPitchRoll(&raw_data[8], 0, 0, 0);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeightAndTime(&raw_data[8], 20000000, 5);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillLatitudeLongitude(&raw_data[8], 2300000000, 2800000000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillDataInfo(&raw_data[8], static_cast<uint8_t>(GpsFlag::DOPPLER_VELOCITY), 20,
                 static_cast<uint8_t>(GpsFlag::DOPPLER_VELOCITY), 4, 1, static_cast<uint8_t>(InitStatusAll::ALL_INIT));
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillSpeed(&raw_data[8], 7000, 8000, 9000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillStd(&raw_data[8], 500, 600, 700, 800);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillHeightAndGpsWeek(&raw_data[8], 2159);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    ASSERT_EQ(pvt_wgs_out.GetMode(), GnssPvt::Mode::TIMING_ONLY);
    ASSERT_TRUE(pvt_wgs_out.IsCovValid() && pvt_wgs_out.IsValid());
}

TEST(AsensingDriverT4, AsensingDriverT_HoloCanPacket4)
{
    Extrinsicf                                     extrinsic;
    AsensingDriverT<HoloCanPacket>                 driver(extrinsic);
    holo::common::Imud                             imu_out;
    holo::common::GnssPvt                          pvt_wgs_out;
    holo::common::GnssPvt                          pvt_gcj_out;
    bool                                           imu_called  = false;
    bool                                           pos0_called = false;
    bool                                           pos1_called = false;
    std::function<void(const holo::common::Imud&)> imu_handler =
        std::bind(&Callback0, std::placeholders::_1, std::ref(imu_out), std::ref(imu_called));
    driver.InstallCallback(imu_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_wgs_handler =
        std::bind(&PositionCallback0, std::placeholders::_1, std::ref(pvt_wgs_out), std::ref(pos0_called));
    driver.InstallPositionCallback(pvt_wgs_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_gcj_handler =
        std::bind(&PositionCallback1, std::placeholders::_1, std::ref(pvt_gcj_out), std::ref(pos1_called));
    driver.InstallPositionTranslationCallback(pvt_gcj_handler);

    uint8_t raw_data[28];
    (void)std::memcpy(raw_data, "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    /* sec_ */
    raw_data[20] = (12345678 >> 24) & 0xff;
    raw_data[21] = (12345678 >> 16) & 0xff;
    raw_data[22] = (12345678 >> 8) & 0xff;
    raw_data[23] = (12345678 >> 0) & 0xff;

    /* nsec_ */
    raw_data[24] = (87654321 >> 24) & 0xff;
    raw_data[25] = (87654321 >> 16) & 0xff;
    raw_data[26] = (87654321 >> 8) & 0xff;
    raw_data[27] = (87654321 >> 0) & 0xff;

    HoloCanPacket packet;
    uint32_t      des_size = 0;
    /* param is net value */
    FillAcc(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillInvalidId(&raw_data[8], 0x300);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillGYRO(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeadingPitchRoll(&raw_data[8], 0, 0, 0);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeightAndTime(&raw_data[8], 20000000, 5);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillLatitudeLongitude(&raw_data[8], 2300000000, 2800000000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    // FillDataInfo(&raw_data[8], static_cast<uint8_t>(GpsFlag::NARROW), 20,
    // static_cast<uint8_t>(GpsFlag::NARROW), 4, 1,
    //              static_cast<uint8_t>(InitStatusAll::ALL_INIT));
    FillDataInfo(&raw_data[8], static_cast<uint8_t>(GpsFlag::SINGLE), 20, static_cast<uint8_t>(GpsFlag::SINGLE), 4, 1,
                 static_cast<uint8_t>(InitStatusAll::ALL_INIT));
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillSpeed(&raw_data[8], 7000, 8000, 9000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillStd(&raw_data[8], 500, 600, 700, 800);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillHeightAndGpsWeek(&raw_data[8], 2161);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    ASSERT_EQ(pvt_wgs_out.GetMode(), GnssPvt::Mode::SINGLE_FIX);
    ASSERT_TRUE(pvt_wgs_out.IsCovValid() && pvt_wgs_out.IsValid());
}

TEST(AsensingDriverT5, AsensingDriverT_HoloCanPacket5)
{
    Extrinsicf                                     extrinsic;
    AsensingDriverT<HoloCanPacket>                 driver(extrinsic);
    holo::common::Imud                             imu_out;
    holo::common::GnssPvt                          pvt_wgs_out;
    holo::common::GnssPvt                          pvt_gcj_out;
    bool                                           imu_called  = false;
    bool                                           pos0_called = false;
    bool                                           pos1_called = false;
    std::function<void(const holo::common::Imud&)> imu_handler =
        std::bind(&Callback0, std::placeholders::_1, std::ref(imu_out), std::ref(imu_called));
    driver.InstallCallback(imu_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_wgs_handler =
        std::bind(&PositionCallback0, std::placeholders::_1, std::ref(pvt_wgs_out), std::ref(pos0_called));
    driver.InstallPositionCallback(pvt_wgs_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_gcj_handler =
        std::bind(&PositionCallback1, std::placeholders::_1, std::ref(pvt_gcj_out), std::ref(pos1_called));
    driver.InstallPositionTranslationCallback(pvt_gcj_handler);

    uint8_t raw_data[28];
    (void)std::memcpy(raw_data, "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    /* sec_ */
    raw_data[20] = (12345678 >> 24) & 0xff;
    raw_data[21] = (12345678 >> 16) & 0xff;
    raw_data[22] = (12345678 >> 8) & 0xff;
    raw_data[23] = (12345678 >> 0) & 0xff;

    /* nsec_ */
    raw_data[24] = (87654321 >> 24) & 0xff;
    raw_data[25] = (87654321 >> 16) & 0xff;
    raw_data[26] = (87654321 >> 8) & 0xff;
    raw_data[27] = (87654321 >> 0) & 0xff;

    HoloCanPacket packet;
    uint32_t      des_size = 0;
    /* param is net value */
    FillAcc(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillInvalidId(&raw_data[8], 0x300);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillGYRO(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeadingPitchRoll(&raw_data[8], 0, 0, 0);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeightAndTime(&raw_data[8], 20000000, 5);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillLatitudeLongitude(&raw_data[8], 2300000000, 2800000000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillDataInfo(&raw_data[8], static_cast<uint8_t>(GpsFlag::PSRDIFF), 20, static_cast<uint8_t>(GpsFlag::PSRDIFF), 4, 1,
                 static_cast<uint8_t>(InitStatusAll::ALL_INIT));
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillSpeed(&raw_data[8], 7000, 8000, 9000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillStd(&raw_data[8], 500, 600, 700, 800);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillHeightAndGpsWeek(&raw_data[8], 2161);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    ASSERT_EQ(pvt_wgs_out.GetMode(), GnssPvt::Mode::DIFF_POSITION);
    ASSERT_TRUE(pvt_wgs_out.IsCovValid() || pvt_wgs_out.IsValid());
}

TEST(AsensingDriverT6, AsensingDriverT_HoloCanPacket6)
{
    Extrinsicf                                     extrinsic;
    AsensingDriverT<HoloCanPacket>                 driver(extrinsic);
    holo::common::Imud                             imu_out;
    holo::common::GnssPvt                          pvt_wgs_out;
    holo::common::GnssPvt                          pvt_gcj_out;
    bool                                           imu_called  = false;
    bool                                           pos0_called = false;
    bool                                           pos1_called = false;
    std::function<void(const holo::common::Imud&)> imu_handler =
        std::bind(&Callback0, std::placeholders::_1, std::ref(imu_out), std::ref(imu_called));
    driver.InstallCallback(imu_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_wgs_handler =
        std::bind(&PositionCallback0, std::placeholders::_1, std::ref(pvt_wgs_out), std::ref(pos0_called));
    driver.InstallPositionCallback(pvt_wgs_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_gcj_handler =
        std::bind(&PositionCallback1, std::placeholders::_1, std::ref(pvt_gcj_out), std::ref(pos1_called));
    driver.InstallPositionTranslationCallback(pvt_gcj_handler);

    uint8_t raw_data[28];
    (void)std::memcpy(raw_data, "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    /* sec_ */
    raw_data[20] = (12345678 >> 24) & 0xff;
    raw_data[21] = (12345678 >> 16) & 0xff;
    raw_data[22] = (12345678 >> 8) & 0xff;
    raw_data[23] = (12345678 >> 0) & 0xff;

    /* nsec_ */
    raw_data[24] = (87654321 >> 24) & 0xff;
    raw_data[25] = (87654321 >> 16) & 0xff;
    raw_data[26] = (87654321 >> 8) & 0xff;
    raw_data[27] = (87654321 >> 0) & 0xff;

    HoloCanPacket packet;
    uint32_t      des_size = 0;
    /* param is net value */
    FillAcc(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillInvalidId(&raw_data[8], 0x300);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillGYRO(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeadingPitchRoll(&raw_data[8], 0, 0, 0);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeightAndTime(&raw_data[8], 20000000, 5);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillLatitudeLongitude(&raw_data[8], 2300000000, 2800000000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillDataInfo(&raw_data[8], static_cast<uint8_t>(GpsFlag::SBAS_SBAS), 20, static_cast<uint8_t>(GpsFlag::SBAS_SBAS),
                 4, 1, static_cast<uint8_t>(InitStatusAll::ALL_INIT));
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillSpeed(&raw_data[8], 7000, 8000, 9000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillStd(&raw_data[8], 500, 600, 700, 800);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillHeightAndGpsWeek(&raw_data[8], 2161);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    ASSERT_EQ(pvt_wgs_out.GetMode(), GnssPvt::Mode::RTK_FLOAT_FIX);
    ASSERT_TRUE(pvt_wgs_out.IsCovValid() || pvt_wgs_out.IsValid());
}

TEST(AsensingDriverT7, AsensingDriverT_HoloCanPacket7)
{
    Extrinsicf                                     extrinsic;
    AsensingDriverT<HoloCanPacket>                 driver(extrinsic);
    holo::common::Imud                             imu_out;
    holo::common::GnssPvt                          pvt_wgs_out;
    holo::common::GnssPvt                          pvt_gcj_out;
    bool                                           imu_called  = false;
    bool                                           pos0_called = false;
    bool                                           pos1_called = false;
    std::function<void(const holo::common::Imud&)> imu_handler =
        std::bind(&Callback0, std::placeholders::_1, std::ref(imu_out), std::ref(imu_called));
    driver.InstallCallback(imu_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_wgs_handler =
        std::bind(&PositionCallback0, std::placeholders::_1, std::ref(pvt_wgs_out), std::ref(pos0_called));
    driver.InstallPositionCallback(pvt_wgs_handler);

    std::function<void(const holo::common::GnssPvt&)> pvt_gcj_handler =
        std::bind(&PositionCallback1, std::placeholders::_1, std::ref(pvt_gcj_out), std::ref(pos1_called));
    driver.InstallPositionTranslationCallback(pvt_gcj_handler);

    uint8_t raw_data[28];
    (void)std::memcpy(raw_data, "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    /* sec_ */
    raw_data[20] = (12345678 >> 24) & 0xff;
    raw_data[21] = (12345678 >> 16) & 0xff;
    raw_data[22] = (12345678 >> 8) & 0xff;
    raw_data[23] = (12345678 >> 0) & 0xff;

    /* nsec_ */
    raw_data[24] = (87654321 >> 24) & 0xff;
    raw_data[25] = (87654321 >> 16) & 0xff;
    raw_data[26] = (87654321 >> 8) & 0xff;
    raw_data[27] = (87654321 >> 0) & 0xff;

    HoloCanPacket packet;
    uint32_t      des_size = 0;
    /* param is net value */
    FillAcc(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillInvalidId(&raw_data[8], 0x300);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillGYRO(&raw_data[8], 10000, 20000, 30000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeadingPitchRoll(&raw_data[8], 0, 0, 0);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    FillHeightAndTime(&raw_data[8], 20000000, 5);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillDataInfo(&raw_data[8], static_cast<uint8_t>(GpsFlag::L1_INT_L1), 20, static_cast<uint8_t>(GpsFlag::L1_INT_L1),
                 4, 1, static_cast<uint8_t>(InitStatusAll::ALL_INIT));
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillSpeed(&raw_data[8], 7000, 8000, 9000);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillStd(&raw_data[8], 500, 600, 700, 800);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    FillHeightAndGpsWeek(&raw_data[8], 2161);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    ASSERT_EQ(pvt_wgs_out.GetMode(), GnssPvt::Mode::NO_POSITION);
    ASSERT_TRUE(!(pvt_wgs_out.IsCovValid() || pvt_wgs_out.IsValid()));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}