#include <gtest/gtest.h>
#include <holo/sensors/novatel/novatel.h>

using namespace holo;
using namespace holo::sensors::format;
using namespace holo::sensors::novatel;

using Odometryd     = holo::common::Odometryd;
using Imud          = holo::common::Imud;
using GnssPvt       = holo::common::GnssPvt;
using Coordinate    = holo::common::Coordinate;
using RawbufferType = holo::sensors::format::Rawbuffer<8192>;

static const uint8_t inspva_msg[104] = {
    0xAA, 0x44, 0x13, 0x58, 0xFC, 0x01, 0x28, 0x08, 0xE8, 0x0D, 0xC7, 0x0B, 0x28, 0x08, 0x00, 0x00, 0xCD, 0xCC,
    0xCC, 0xCC, 0xD4, 0x1E, 0x08, 0x41, 0x8C, 0x53, 0xAD, 0x25, 0x3A, 0x05, 0x44, 0x40, 0xA0, 0x5F, 0xD2, 0xAB,
    0x4A, 0x20, 0x5D, 0x40, 0x00, 0x00, 0x74, 0x7A, 0x69, 0x67, 0x3B, 0x40, 0x34, 0xD2, 0x12, 0xAD, 0xF9, 0xC2,
    0xB1, 0x3F, 0x6A, 0x50, 0xD1, 0xFF, 0x58, 0x4B, 0x23, 0x40, 0xD8, 0xAC, 0x79, 0x99, 0x39, 0x4E, 0x78, 0xBF,
    0x9E, 0x6A, 0xE2, 0x76, 0x18, 0x1C, 0xE3, 0x3F, 0xFE, 0x61, 0x1C, 0x9E, 0x15, 0x2B, 0xAB, 0x3F, 0x6D, 0xF8,
    0xF6, 0x75, 0xCA, 0xBB, 0x56, 0x40, 0x03, 0x00, 0x00, 0x00, 0xE2, 0x54, 0x65, 0x7E};

static const uint8_t inscov_msg[244] = {
    0xAA, 0x44, 0x13, 0xE4, 0x40, 0x01, 0x28, 0x08, 0x78, 0x0F, 0xC7, 0x0B, 0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xD8, 0x1E, 0x08, 0x41, 0x80, 0xD7, 0x54, 0x92, 0x51, 0xD0, 0xF8, 0x3F, 0x97, 0xFB, 0x01, 0x3C, 0xD5, 0xFC,
    0xD0, 0x3F, 0xAE, 0x1B, 0x1C, 0x03, 0x16, 0xA3, 0xD1, 0xBF, 0x97, 0xFB, 0x01, 0x3C, 0xD5, 0xFC, 0xD0, 0x3F, 0xF9,
    0xB2, 0x8C, 0x3C, 0xF9, 0xD6, 0xF3, 0x3F, 0x8C, 0x2C, 0x4C, 0xEE, 0x9B, 0x48, 0xD4, 0xBF, 0xAE, 0x1B, 0x1C, 0x03,
    0x16, 0xA3, 0xD1, 0xBF, 0x8C, 0x2C, 0x4C, 0xEE, 0x9B, 0x48, 0xD4, 0xBF, 0x1C, 0xC9, 0xC4, 0x76, 0xC8, 0xBD, 0xFA,
    0x3F, 0x84, 0xCD, 0x95, 0x3F, 0x0E, 0x69, 0x55, 0x3F, 0xF6, 0xB5, 0x7D, 0x88, 0xD0, 0x5E, 0x0A, 0x3F, 0xD1, 0x3A,
    0xC1, 0xA1, 0x09, 0xCC, 0x3B, 0x3F, 0xF6, 0xB5, 0x7D, 0x88, 0xD0, 0x5E, 0x0A, 0x3F, 0xD3, 0x12, 0x99, 0xEB, 0xE0,
    0x69, 0x53, 0x3F, 0x6E, 0xB7, 0x7E, 0xB6, 0x5D, 0x5F, 0x3F, 0x3F, 0xD1, 0x3A, 0xC1, 0xA1, 0x09, 0xCC, 0x3B, 0x3F,
    0x6E, 0xB7, 0x7E, 0xB6, 0x5D, 0x5F, 0x3F, 0x3F, 0xB9, 0xAB, 0x7A, 0xF9, 0x99, 0x7C, 0x9D, 0x3F, 0x56, 0xA0, 0xE7,
    0x42, 0xE1, 0x2E, 0x21, 0x3F, 0x46, 0x41, 0xDC, 0x84, 0xB3, 0xDD, 0xFA, 0xBE, 0x44, 0x37, 0xEB, 0xE0, 0x87, 0x21,
    0xE6, 0xBE, 0x46, 0x41, 0xDC, 0x84, 0xB3, 0xDD, 0xFA, 0xBE, 0x3F, 0x77, 0x4A, 0xBB, 0x1D, 0xA9, 0x14, 0x3F, 0x72,
    0x87, 0xFA, 0x56, 0x77, 0xC7, 0xE0, 0xBE, 0x44, 0x37, 0xEB, 0xE0, 0x87, 0x21, 0xE6, 0xBE, 0x72, 0x87, 0xFA, 0x56,
    0x77, 0xC7, 0xE0, 0xBE, 0xA9, 0xDC, 0x0F, 0x9D, 0x58, 0xF6, 0x1A, 0x3F, 0x84, 0x98, 0xD7, 0xCC};

static const uint8_t bestpos_msg[104] = {
    0xAA, 0x44, 0x12, 0x1C, 0x2A, 0x00, 0x00, 0xA0, 0x48, 0x00, 0x00, 0x00, 0x81, 0xB4, 0x28, 0x08, 0x60, 0x13,
    0xC7, 0x0B, 0x08, 0x80, 0x00, 0x02, 0xF6, 0xB1, 0x7A, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00,
    0xD3, 0xC2, 0xFB, 0x20, 0x22, 0x05, 0x44, 0x40, 0x1A, 0x51, 0x5D, 0x21, 0x4D, 0x20, 0x5D, 0x40, 0x00, 0x00,
    0xDA, 0x52, 0xAB, 0xC3, 0x42, 0x40, 0x00, 0x00, 0x18, 0xC1, 0x3D, 0x00, 0x00, 0x00, 0x97, 0x85, 0x9F, 0x3F,
    0xE9, 0x75, 0x8E, 0x3F, 0xFA, 0x7E, 0xA5, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x19, 0x16, 0x16, 0x16, 0x00, 0x86, 0x30, 0x33, 0x6B, 0xCE, 0x06, 0x2C};

static const uint8_t rawimu_msg[56] = {
    0xAA, 0x44, 0x13, 0x28, 0xB6, 0x05, 0x29, 0x08, 0x18, 0x67, 0x7A, 0x01, 0x00, 0x20, 0x29, 0x08, 0x3D, 0x26, 0xF7,
    0xE0, 0xBE, 0x37, 0xD8, 0x40, 0x00, 0x00, 0x0B, 0x0F, 0xAF, 0x06, 0x05, 0x00, 0x62, 0x08, 0x00, 0x00, 0x30, 0xE8,
    0xFF, 0xFF, 0x6F, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x54, 0xFF, 0xFF, 0xFF, 0x8B, 0xE5, 0x61, 0x0C};

TEST(InsPositionVelocityAttitudeShort, All)
{
    InsPositionVelocityAttitudeShort inspvas;
    ASSERT_EQ(inspvas.GetSerializedSize(), sizeof(inspva_msg));
    ASSERT_EQ(inspvas.Deserialize(inspva_msg, sizeof(inspva_msg) - 1), 0);
    ASSERT_EQ(inspvas.Deserialize(inspva_msg, sizeof(inspva_msg)), sizeof(inspva_msg));
}

TEST(InsCovarianceShort, All)
{
    InsCovarianceShort inscov;
    ASSERT_EQ(inscov.GetSerializedSize(), sizeof(inscov_msg));
    ASSERT_EQ(inscov.Deserialize(inscov_msg, sizeof(inscov_msg) - 1), 0);
    ASSERT_EQ(inscov.Deserialize(inscov_msg, sizeof(inscov_msg)), sizeof(inscov_msg));
}

TEST(BestPosition, All)
{
    BestPosition bestpos;
    ASSERT_EQ(bestpos.GetSerializedSize(), sizeof(bestpos_msg));
    ASSERT_EQ(bestpos.Deserialize(bestpos_msg, sizeof(bestpos_msg) - 1), 0);
    ASSERT_EQ(bestpos.Deserialize(bestpos_msg, sizeof(bestpos_msg)), sizeof(bestpos_msg));
}

TEST(RawImuShortExtended, All)
{
    RawImuShortExtended rawimu;
    ASSERT_EQ(rawimu.GetSerializedSize(), sizeof(rawimu_msg));
    ASSERT_EQ(rawimu.Deserialize(rawimu_msg, sizeof(rawimu_msg) - 1), 0);
    ASSERT_EQ(rawimu.Deserialize(rawimu_msg, sizeof(rawimu_msg)), sizeof(rawimu_msg));
}

static void BufferCallback(const uint8_t* input, uint32_t size, Rawbuffer<8192>& output, bool& called)
{
    ASSERT_TRUE(size <= 8192);
    uint32_t des_size = output.Deserialize(input, size);
    ASSERT_EQ(des_size, size);
    ASSERT_EQ(des_size, output.size());
    called = true;
}

static void OdometryCallback(const holo::common::Odometryd& input, holo::common::Odometryd& output, bool& called)
{
    output.SetCoordinate(input.GetCoordinate());
    output.SetChildCoordinate(input.GetChildCoordinate());
    output.SetTimestamp(input.GetTimestamp());
    output.SetStatus(input.GetStatus());
    output.SetSource(input.GetSource());
    output.SetPose(input.GetPose());
    output.SetPoseCovariance(input.GetPoseCovariance());
    output.SetVelocity(input.GetVelocity());
    output.SetVelocityCovariance(input.GetVelocityCovariance());
    called = true;
}

static void ImuCallback(const Imud& input, Imud& output, bool& called)
{
    output.SetCoordinate(input.GetCoordinate());
    output.SetTimestamp(input.GetTimestamp());
    output.SetStatus(input.GetStatus());
    output.SetAngularVelocity(input.GetAngularVelocity<holo::geometry::Point3d>());
    output.SetLinearAcceleration(input.GetLinearAcceleration<holo::geometry::Point3d>());
    called = true;
}

static void PositionCallback(const holo::common::GnssPvt& input, holo::common::GnssPvt& output, bool& called)
{
    output.SetCoordinate(input.GetCoordinate());
    output.SetTimestamp(input.GetTimestamp());
    output.SetMode(input.GetMode());
    output.SetValidFlags(input.IsPositionValid(), input.IsVelocityValid(), input.IsPositionCovValid(),
                         input.IsVelocityCovValid());
    output.SetLatitude(input.GetLatitude());
    output.SetLongitude(input.GetLongitude());
    output.SetHeight(input.GetHeight());
    output.SetLatitudeCov(input.GetLatitudeCov());
    output.SetLongitudeCov(input.GetLongitudeCov());
    output.SetHeightCov(input.GetHeightCov());
    output.SetVelocityNorth(input.GetVelocityNorth());
    output.SetVelocityEast(input.GetVelocityEast());
    output.SetVelocityUp(input.GetVelocityUp());
    output.SetVelocityNorthCov(input.GetVelocityNorthCov());
    output.SetVelocityEastCov(input.GetVelocityEastCov());
    output.SetVelocityUpCov(input.GetVelocityUpCov());
    called = true;
}

TEST(NovatelDriver, All)
{
    holo::common::Extrinsicf extrinsic;
    NovatelDriver            driver(extrinsic);

    Rawbuffer<8192> buffer0;
    bool            called0 = false;
    auto            handler0 =
        std::bind(&BufferCallback, std::placeholders::_1, std::placeholders::_2, std::ref(buffer0), std::ref(called0));
    driver.SetInsPvaSCallback(handler0);
    Rawbuffer<8192> buffer1;
    bool            called1 = false;
    auto            handler1 =
        std::bind(&BufferCallback, std::placeholders::_1, std::placeholders::_2, std::ref(buffer1), std::ref(called1));
    driver.SetBestPositionCallback(handler1);
    Rawbuffer<8192> buffer2;
    bool            called2 = false;
    auto            handler2 =
        std::bind(&BufferCallback, std::placeholders::_1, std::placeholders::_2, std::ref(buffer2), std::ref(called2));
    driver.SetInsCovSCallback(handler2);
    Rawbuffer<8192> buffer3;
    bool            called3 = false;
    auto            handler3 =
        std::bind(&BufferCallback, std::placeholders::_1, std::placeholders::_2, std::ref(buffer3), std::ref(called3));
    driver.SetRawImuSXCallback(handler3);

    Odometryd odo1;
    bool      called5  = false;
    auto      handler5 = std::bind(&OdometryCallback, std::placeholders::_1, std::ref(odo1), std::ref(called5));
    driver.SetOdometryCallback(handler5);
    Odometryd odo2;
    bool      called6  = false;
    auto      handler6 = std::bind(&OdometryCallback, std::placeholders::_1, std::ref(odo2), std::ref(called6));
    driver.SetOdometryTranslationCallback(handler6);
    Imud imu;
    bool called7  = false;
    auto handler7 = std::bind(&ImuCallback, std::placeholders::_1, std::ref(imu), std::ref(called7));
    driver.SetImuCallback(handler7);
    GnssPvt pos;
    bool    called8  = false;
    auto    handler8 = std::bind(&PositionCallback, std::placeholders::_1, std::ref(pos), std::ref(called8));
    driver.SetPositionCallback(handler8);

    Rawbuffer<8192> data;
    uint8_t         data0[8];
    (void)std::memset(data0, 0, sizeof(data0));
    data.Deserialize(data0, sizeof(data0));
    ASSERT_EQ(data.size(), sizeof(data0));
    ASSERT_NO_THROW(driver.ParseData(data));

    uint8_t data1[1024];
    (void)std::memset(data1, 0, sizeof(data1));
    data1[0] = SYNC_BYTE_1;
    data1[1] = SYNC_BYTE_2;
    data1[2] = SYNC_BYTE_3;
    data.Deserialize(data1, sizeof(data1));
    ASSERT_EQ(data.size(), sizeof(data1));
    ASSERT_NO_THROW(driver.ParseData(data));

    uint32_t des_size;
    /* inscov */
    des_size = data.Deserialize(inscov_msg, sizeof(inscov_msg));
    ASSERT_EQ(des_size, sizeof(inscov_msg));
    ASSERT_NO_THROW(driver.ParseData(data));
    ASSERT_TRUE(called2);

    /* inspva */
    des_size = data.Deserialize(inspva_msg, sizeof(inspva_msg));
    ASSERT_EQ(des_size, sizeof(inspva_msg));
    ASSERT_NO_THROW(driver.ParseData(data));
    ASSERT_TRUE(called0);
    ASSERT_TRUE(called5);
    ASSERT_TRUE(called6);

    float64_t               latitude  = 40.040837;
    float64_t               longitude = 116.504558;
    float64_t               height    = 27.403953;
    float64_t               roll      = 0.59717965;
    float64_t               pitch     = 0.053063083;
    float64_t               azimuth   = 90.934232;
    holo::geometry::Point2d xy;
    holo::GeographicalTransformation::LL2UTM(longitude, latitude, xy);
    holo::geometry::Point3d p(xy.GetX(), xy.GetY(), height);
    holo::geometry::Rot3    Nov_World = holo::geometry::Rot3::Rz(holo::geometry::Radian<float64_t>(-azimuth)) *
                                     holo::geometry::Rot3::Rx(holo::geometry::Radian<float64_t>(pitch)) *
                                     holo::geometry::Rot3::Ry(holo::geometry::Radian<float64_t>(roll));
    holo::geometry::Pose3d pose = holo::geometry::Pose3d(Nov_World, p);
    // Calculation extrinsic body to novatel
    holo::geometry::Pose3d  pose_body;
    holo::geometry::Point3d p_body(0, 0, 0);
    holo::geometry::Rot3    r_body = holo::geometry::Rot3::Rz(holo::geometry::Radian<float64_t>(0.0f)) *
                                  holo::geometry::Rot3::Rx(holo::geometry::Radian<float64_t>(0.0f)) *
                                  holo::geometry::Rot3::Ry(holo::geometry::Radian<float64_t>(0.0f));
    pose_body = holo::geometry::Pose3d(r_body, p_body).Inverse();
    pose      = pose * pose_body;
    ASSERT_FLOAT_EQ(odo1.GetPose().GetRotation().YPR()[2], pose.GetRotation().YPR()[2]);
    ASSERT_FLOAT_EQ(odo1.GetPose().GetRotation().YPR()[1], pose.GetRotation().YPR()[1]);
    ASSERT_FLOAT_EQ(odo1.GetPose().GetRotation().YPR()[0], pose.GetRotation().YPR()[0]);
    ASSERT_FLOAT_EQ(odo1.GetPose().GetX(), pose.GetX());
    ASSERT_FLOAT_EQ(odo1.GetPose().GetY(), pose.GetY());
    ASSERT_FLOAT_EQ(odo1.GetPose().GetZ(), pose.GetZ());

    ASSERT_FLOAT_EQ(odo1.GetVelocity()[0], 9.647163);
    ASSERT_FLOAT_EQ(odo1.GetVelocity()[1], 0.069381334);
    ASSERT_FLOAT_EQ(odo1.GetVelocity()[2], -0.0059339763);

    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(0, 0), 1.550859);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(0, 1), 0.2654317);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(0, 2), -0.275579);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(1, 0), 0.2654317);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(1, 1), 1.239984);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(1, 2), -0.31693169);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(2, 0), -0.275579);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(2, 1), -0.31693169);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(2, 2), 1.671334);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(3, 3), 2.280771e-5);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(3, 4), 8.7785679e-07);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(3, 5), 7.4027948e-06);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(4, 3), 8.7785679e-07);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(4, 4), 2.0680605e-05);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(4, 5), 8.3550085e-06);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(5, 3), 7.4027948e-06);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(5, 4), 8.3550085e-06);
    ASSERT_FLOAT_EQ(odo1.GetPoseCovariance()(5, 5), 0.00050257856);

    ASSERT_FLOAT_EQ(odo1.GetVelocityCovariance()(0, 0), 0.00013109684);
    ASSERT_FLOAT_EQ(odo1.GetVelocityCovariance()(0, 1), -2.5621433e-05);
    ASSERT_FLOAT_EQ(odo1.GetVelocityCovariance()(0, 2), -1.0552873e-05);
    ASSERT_FLOAT_EQ(odo1.GetVelocityCovariance()(1, 0), -2.5621433e-05);
    ASSERT_FLOAT_EQ(odo1.GetVelocityCovariance()(1, 1), 7.8813973e-05);
    ASSERT_FLOAT_EQ(odo1.GetVelocityCovariance()(1, 2), -8.0009295e-06);
    ASSERT_FLOAT_EQ(odo1.GetVelocityCovariance()(2, 0), -1.0552873e-05);
    ASSERT_FLOAT_EQ(odo1.GetVelocityCovariance()(2, 1), -8.0009295e-06);
    ASSERT_FLOAT_EQ(odo1.GetVelocityCovariance()(2, 2), 0.00010285297);

    called0 = false;
    called5 = false;
    called6 = false;
    /* bestpos */
    des_size = data.Deserialize(bestpos_msg, sizeof(bestpos_msg));
    ASSERT_EQ(des_size, sizeof(bestpos_msg));
    ASSERT_NO_THROW(driver.ParseData(data));
    ASSERT_TRUE(called1);
    ASSERT_TRUE(called8);

    float64_t               gps_sec = static_cast<float64_t>(2088 * 604800 + 197596);
    holo::common::Timestamp gps_stamp;
    gps_stamp.SetSec(gps_sec);
    holo::common::Timestamp utc_stamp;
    holo::common::Timestamp::GpsToUtc(gps_stamp, utc_stamp);
    ASSERT_FLOAT_EQ(pos.GetTimestamp().ToSec(), utc_stamp.ToSec());
    ASSERT_EQ(pos.GetMode(), GnssPvt::Mode::SINGLE_FIX);
    ASSERT_EQ(pos.IsPositionValid(), true);
    ASSERT_EQ(pos.IsVelocityValid(), true);
    ASSERT_EQ(pos.IsPositionCovValid(), true);
    ASSERT_EQ(pos.IsVelocityCovValid(), true);
    float64_t lat        = 40.040104;
    float64_t lon        = 116.50471;
    float64_t hei        = 37.528667;
    float64_t undulation = -9.500001;
    ASSERT_FLOAT_EQ(pos.GetLatitude(), lat);
    ASSERT_FLOAT_EQ(pos.GetLongitude(), lon);
    ASSERT_FLOAT_EQ(pos.GetHeight(), hei + undulation);
    float32_t lat_std = 1.246264;
    float32_t lon_std = 1.112973;
    float32_t hei_std = 1.292938;
    ASSERT_FLOAT_EQ(pos.GetLatitudeCov(), lat_std);
    ASSERT_FLOAT_EQ(pos.GetLongitudeCov(), lon_std);
    ASSERT_FLOAT_EQ(pos.GetHeightCov(), hei_std);
    float32_t vel_east  = 9.647163;
    float32_t vel_north = 0.069381334;
    float32_t vel_up    = -0.0059339763;
    ASSERT_FLOAT_EQ(pos.GetVelocityEast(), vel_east);
    ASSERT_FLOAT_EQ(pos.GetVelocityNorth(), vel_north);
    ASSERT_FLOAT_EQ(pos.GetVelocityUp(), vel_up);
    ASSERT_EQ(pos.GetCoordinate(), Coordinate::Wgs84Coordinate());

    called1 = false;
    called8 = false;
    /* rawimu */
    des_size = data.Deserialize(rawimu_msg, sizeof(rawimu_msg));
    ASSERT_EQ(des_size, sizeof(rawimu_msg));
    ASSERT_NO_THROW(driver.ParseData(data));
    ASSERT_TRUE(called3);
    ASSERT_TRUE(called7);

    uint32_t sec = (*(const uint16_t*)(rawimu_msg + 6)) * 7 * 24 * 3600 + (*(const uint32_t*)(rawimu_msg + 8)) / 1000;
    gps_stamp.SetSec(sec);
    holo::common::Timestamp::GpsToUtc(gps_stamp, utc_stamp);
    ASSERT_EQ(imu.GetStatus(), holo::common::Imud::Status::ALLGOOD);
    ASSERT_FLOAT_EQ(imu.GetTimestamp().GetSec(), utc_stamp.GetSec());
    EXPECT_FLOAT_EQ(imu.GetAngularVelocity<holo::geometry::Point3d>()[0], -6.4498599e-5);
    EXPECT_FLOAT_EQ(imu.GetAngularVelocity<holo::geometry::Point3d>()[1], 0.0001789316);
    EXPECT_FLOAT_EQ(imu.GetAngularVelocity<holo::geometry::Point3d>()[2], 0.0001154733);
    EXPECT_FLOAT_EQ(imu.GetLinearAcceleration<holo::geometry::Point3d>()[0], -0.063955091);
    EXPECT_FLOAT_EQ(imu.GetLinearAcceleration<holo::geometry::Point3d>()[1], 0.18167299);
    EXPECT_FLOAT_EQ(imu.GetLinearAcceleration<holo::geometry::Point3d>()[2], 9.8165102);

    called3 = false;
    called7 = false;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
