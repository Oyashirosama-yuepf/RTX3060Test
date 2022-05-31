/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sensors_utils.cpp
 * @brief the sensors common utils
 * @author lanpade(yangpeiwen@holomatic.com)
 * @date 2019-12-10
 */

#include <fstream>

#include <holo/sensors/utils/sensors_utils.h>

namespace holo
{
namespace sensors
{
static const std::map<std::string, VehicleLocation::Plane> vehicle_location_plane_map_const = {
    std::pair<std::string, VehicleLocation::Plane>("UNKNOWN", VehicleLocation::Plane::UNKNOWN),
    std::pair<std::string, VehicleLocation::Plane>("FRONT", VehicleLocation::Plane::FRONT),
    std::pair<std::string, VehicleLocation::Plane>("REAR", VehicleLocation::Plane::REAR),
    std::pair<std::string, VehicleLocation::Plane>("LEFT", VehicleLocation::Plane::LEFT),
    std::pair<std::string, VehicleLocation::Plane>("RIGHT", VehicleLocation::Plane::RIGHT),
    std::pair<std::string, VehicleLocation::Plane>("FRONT_WINDOW", VehicleLocation::Plane::FRONT_WINDOW),
    std::pair<std::string, VehicleLocation::Plane>("REAR_WINDOW", VehicleLocation::Plane::REAR_WINDOW),
    std::pair<std::string, VehicleLocation::Plane>("LEFT_WINDOW", VehicleLocation::Plane::LEFT_WINDOW),
    std::pair<std::string, VehicleLocation::Plane>("RIGHT_WINDOW", VehicleLocation::Plane::RIGHT_WINDOW),
    std::pair<std::string, VehicleLocation::Plane>("EIGINE_HOOD", VehicleLocation::Plane::EIGINE_HOOD),
    std::pair<std::string, VehicleLocation::Plane>("ROOF", VehicleLocation::Plane::ROOF),
    std::pair<std::string, VehicleLocation::Plane>("TRUNK_DOOR", VehicleLocation::Plane::TRUNK_DOOR),
    std::pair<std::string, VehicleLocation::Plane>("CHASSIS", VehicleLocation::Plane::CHASSIS),
    std::pair<std::string, VehicleLocation::Plane>("TRUNK", VehicleLocation::Plane::TRUNK),
    std::pair<std::string, VehicleLocation::Plane>("COCKPIT", VehicleLocation::Plane::COCKPIT),
    std::pair<std::string, VehicleLocation::Plane>("GROUND", VehicleLocation::Plane::GROUND),
};

static const std::map<std::string, VehicleLocation::Location> vehicle_location_location_map_const = {
    std::pair<std::string, VehicleLocation::Location>("UNKNOWN", VehicleLocation::Location::UNKNOWN),
    std::pair<std::string, VehicleLocation::Location>("BOTTOM_MOST", VehicleLocation::Location::BOTTOM_MOST),
    std::pair<std::string, VehicleLocation::Location>("REAR_MOST", VehicleLocation::Location::REAR_MOST),
    std::pair<std::string, VehicleLocation::Location>("LEFT_MOST", VehicleLocation::Location::LEFT_MOST),
    std::pair<std::string, VehicleLocation::Location>("BOTTOM", VehicleLocation::Location::BOTTOM),
    std::pair<std::string, VehicleLocation::Location>("REAR", VehicleLocation::Location::REAR),
    std::pair<std::string, VehicleLocation::Location>("LEFT", VehicleLocation::Location::LEFT),
    std::pair<std::string, VehicleLocation::Location>("MIDDLE", VehicleLocation::Location::MIDDLE),
    std::pair<std::string, VehicleLocation::Location>("CENTER", VehicleLocation::Location::CENTER),
    std::pair<std::string, VehicleLocation::Location>("TOP", VehicleLocation::Location::TOP),
    std::pair<std::string, VehicleLocation::Location>("FRONT", VehicleLocation::Location::FRONT),
    std::pair<std::string, VehicleLocation::Location>("RIGHT", VehicleLocation::Location::RIGHT),
    std::pair<std::string, VehicleLocation::Location>("TOP_MOST", VehicleLocation::Location::TOP_MOST),
    std::pair<std::string, VehicleLocation::Location>("FRONT_MOST", VehicleLocation::Location::FRONT_MOST),
    std::pair<std::string, VehicleLocation::Location>("RIGHT_MOST", VehicleLocation::Location::RIGHT_MOST),
};

static const std::map<std::string, SensorId::Category> sensorid_category_const = {
    std::pair<std::string, SensorId::Category>("UNKNOWN", SensorId::Category::UNKNOWN),
    std::pair<std::string, SensorId::Category>("GNSS", SensorId::Category::GNSS),
    std::pair<std::string, SensorId::Category>("IMU", SensorId::Category::IMU),
    std::pair<std::string, SensorId::Category>("CAMERA", SensorId::Category::CAMERA),
    std::pair<std::string, SensorId::Category>("RADAR", SensorId::Category::RADAR),
    std::pair<std::string, SensorId::Category>("USS", SensorId::Category::USS),
    std::pair<std::string, SensorId::Category>("LIDAR", SensorId::Category::LIDAR),
    std::pair<std::string, SensorId::Category>("AUDIO", SensorId::Category::AUDIO),
    std::pair<std::string, SensorId::Category>("JOYSTICK", SensorId::Category::JOYSTICK),
};

static const std::map<std::string, SensorId::Model> sensorid_model_const = {
    std::pair<std::string, SensorId::Model>("UNKNOWN", SensorId::Model::UNKNOWN),
    std::pair<std::string, SensorId::Model>("GNSS_UNKNOWN", SensorId::Model::GNSS_UNKNOWN),
    std::pair<std::string, SensorId::Model>("GNSS_NOVATEL", SensorId::Model::GNSS_NOVATEL),
    std::pair<std::string, SensorId::Model>("GNSS_XSENS", SensorId::Model::GNSS_XSENS),
    std::pair<std::string, SensorId::Model>("GNSS_UBLOX_M8L", SensorId::Model::GNSS_UBLOX_M8L),
    std::pair<std::string, SensorId::Model>("GNSS_UBLOX_M8T", SensorId::Model::GNSS_UBLOX_M8T),
    std::pair<std::string, SensorId::Model>("GNSS_UBLOX_M8Z", SensorId::Model::GNSS_UBLOX_M8Z),
    std::pair<std::string, SensorId::Model>("GNSS_UBLOX_F9", SensorId::Model::GNSS_UBLOX_F9),
    std::pair<std::string, SensorId::Model>("GNSS_QIANXU", SensorId::Model::GNSS_QIANXU),
    std::pair<std::string, SensorId::Model>("GNSS_SCT_LANETO", SensorId::Model::GNSS_SCT_LANETO),
    std::pair<std::string, SensorId::Model>("GNSS_SPATIAL", SensorId::Model::GNSS_SPATIAL),
    std::pair<std::string, SensorId::Model>("GNSS_UNICORE", SensorId::Model::GNSS_UNICORE),
    std::pair<std::string, SensorId::Model>("GNSS_BDSTAR_NPOS220", SensorId::Model::GNSS_BDSTAR_NPOS220),
    std::pair<std::string, SensorId::Model>("IMU_UNKNOWN", SensorId::Model::IMU_UNKNOWN),
    std::pair<std::string, SensorId::Model>("IMU_NOVATEL", SensorId::Model::IMU_NOVATEL),
    std::pair<std::string, SensorId::Model>("IMU_XSENS", SensorId::Model::IMU_XSENS),
    std::pair<std::string, SensorId::Model>("IMU_UBLOX_M8L", SensorId::Model::IMU_UBLOX_M8L),
    std::pair<std::string, SensorId::Model>("IMU_UBLOX_F9K", SensorId::Model::IMU_UBLOX_F9K),
    std::pair<std::string, SensorId::Model>("IMU_ACEINNA_305", SensorId::Model::IMU_ACEINNA_305),
    std::pair<std::string, SensorId::Model>("IMU_ACEINNA_330", SensorId::Model::IMU_ACEINNA_330),
    std::pair<std::string, SensorId::Model>("IMU_MURATA_2230", SensorId::Model::IMU_MURATA_2230),
    std::pair<std::string, SensorId::Model>("CAMERA_UNKNOWN", SensorId::Model::CAMERA_UNKNOWN),
    std::pair<std::string, SensorId::Model>("CAMERA_MOBILEYE_EQ3", SensorId::Model::CAMERA_MOBILEYE_EQ3),
    std::pair<std::string, SensorId::Model>("CAMERA_MOBILEYE_EQ4", SensorId::Model::CAMERA_MOBILEYE_EQ4),
    std::pair<std::string, SensorId::Model>("CAMERA_BOSCH_MPC", SensorId::Model::CAMERA_BOSCH_MPC),
    std::pair<std::string, SensorId::Model>("CAMERA_DELPHI_IFV300", SensorId::Model::CAMERA_DELPHI_IFV300),
    std::pair<std::string, SensorId::Model>("CAMERA_CALMCAR", SensorId::Model::CAMERA_CALMCAR),
    std::pair<std::string, SensorId::Model>("CAMERA_ENTRON_F001R", SensorId::Model::CAMERA_ENTRON_F001R),
    std::pair<std::string, SensorId::Model>("CAMERA_ENTRON_S001R", SensorId::Model::CAMERA_ENTRON_S001R),
    std::pair<std::string, SensorId::Model>("CAMERA_LEOPARD_M021", SensorId::Model::CAMERA_LEOPARD_M021),
    std::pair<std::string, SensorId::Model>("CAMERA_LEOPARD_AR0231", SensorId::Model::CAMERA_LEOPARD_AR0231),
    std::pair<std::string, SensorId::Model>("CAMERA_LEOPARD_OV490", SensorId::Model::CAMERA_LEOPARD_OV490),
    std::pair<std::string, SensorId::Model>("CAMERA_LEOPARD_AP020", SensorId::Model::CAMERA_LEOPARD_AP020),
    std::pair<std::string, SensorId::Model>("RADAR_UNKNOWN", SensorId::Model::RADAR_UNKNOWN),
    std::pair<std::string, SensorId::Model>("RADAR_CONTI_308", SensorId::Model::RADAR_CONTI_308),
    std::pair<std::string, SensorId::Model>("RADAR_CONTI_408", SensorId::Model::RADAR_CONTI_408),
    std::pair<std::string, SensorId::Model>("RADAR_CONTI_430", SensorId::Model::RADAR_CONTI_430),
    std::pair<std::string, SensorId::Model>("RADAR_BOSCH_MRR4", SensorId::Model::RADAR_BOSCH_MRR4),
    std::pair<std::string, SensorId::Model>("RADAR_DELPHI_ESR", SensorId::Model::RADAR_DELPHI_ESR),
    std::pair<std::string, SensorId::Model>("RADAR_DELPHI_RSDS", SensorId::Model::RADAR_DELPHI_RSDS),
    std::pair<std::string, SensorId::Model>("USS_UNKNOWN", SensorId::Model::USS_UNKNOWN),
    std::pair<std::string, SensorId::Model>("USS_BOSCH", SensorId::Model::USS_BOSCH),
    std::pair<std::string, SensorId::Model>("USS_IS", SensorId::Model::USS_IS),
    std::pair<std::string, SensorId::Model>("USS_SOFTEC", SensorId::Model::USS_SOFTEC),
    std::pair<std::string, SensorId::Model>("LIDAR_UNKNOWN", SensorId::Model::LIDAR_UNKNOWN),
    std::pair<std::string, SensorId::Model>("LIDAR_IBEO_SCALA", SensorId::Model::LIDAR_IBEO_SCALA),
    std::pair<std::string, SensorId::Model>("LIDAR_IBEO_LUX", SensorId::Model::LIDAR_IBEO_LUX),
    std::pair<std::string, SensorId::Model>("LIDAR_VLP_16L", SensorId::Model::LIDAR_VLP_16L),
    std::pair<std::string, SensorId::Model>("LIDAR_VLP_16L_HRS", SensorId::Model::LIDAR_VLP_16L_HRS),
    std::pair<std::string, SensorId::Model>("LIDAR_VLP_32L", SensorId::Model::LIDAR_VLP_32L),
    std::pair<std::string, SensorId::Model>("LIDAR_PANDAR_40L", SensorId::Model::LIDAR_PANDAR_40L),
    std::pair<std::string, SensorId::Model>("LIDAR_LIVOX_MID40", SensorId::Model::LIDAR_LIVOX_MID40),
    std::pair<std::string, SensorId::Model>("LIDAR_LIVOX_MID100", SensorId::Model::LIDAR_LIVOX_MID100),
    std::pair<std::string, SensorId::Model>("LIDAR_LEISHEN_8L", SensorId::Model::LIDAR_LEISHEN_8L),
    std::pair<std::string, SensorId::Model>("LIDAR_LEISHEN_16L", SensorId::Model::LIDAR_LEISHEN_16L),
    std::pair<std::string, SensorId::Model>("LIDAR_BENEWAKE", SensorId::Model::LIDAR_BENEWAKE),
    std::pair<std::string, SensorId::Model>("LIDAR_OUSTER", SensorId::Model::LIDAR_OUSTER),
    std::pair<std::string, SensorId::Model>("LIDAR_SURESTAR", SensorId::Model::LIDAR_SURESTAR),
    std::pair<std::string, SensorId::Model>("LIDAR_ROBOSENSE", SensorId::Model::LIDAR_ROBOSENSE),
    std::pair<std::string, SensorId::Model>("AUDIO_UNKNOWN", SensorId::Model::AUDIO_UNKNOWN),
    std::pair<std::string, SensorId::Model>("JOYSTICK_UNKNOWN", SensorId::Model::JOYSTICK_UNKNOWN),
    std::pair<std::string, SensorId::Model>("JOYSTICK_BETOP", SensorId::Model::JOYSTICK_BETOP),
};

std::string GetHoloSensorsLibConfigDirectory()
{
    return GetHoloConfigRootDirectory() + "/holo_sensors/lib_config/";
}

std::string GetHoloSensorsExtrinsicsDirectory()
{
    return GetHoloConfigRootDirectory() + "/holo_sensors/extrinsics/";
}

std::string GetHoloSensorsIntrinsicsDirectory()
{
    return GetHoloConfigRootDirectory() + "/holo_sensors/intrinsics/";
}

VehicleLocation StringToVehicleLocation(const std::string& plane, const std::string& x, const std::string& y)
{
    return VehicleLocation(vehicle_location_plane_map_const.at(plane), vehicle_location_location_map_const.at(x),
                           vehicle_location_location_map_const.at(y));
}

SensorId StringToSensorId(const std::string& category, const std::string& model, const std::string& plane,
                          const std::string& x, const std::string& y)
{
    return SensorId(sensorid_category_const.at(category), sensorid_model_const.at(model),
                    StringToVehicleLocation(plane, x, y));
}

Coordinate StringToVehicleCoordinate(const std::string& category, const std::string& model, const std::string& plane,
                                     const std::string& x, const std::string& y)
{
    return Coordinate::VehicleCoordinate(sensorid_category_const.at(category), sensorid_model_const.at(model),
                                         vehicle_location_plane_map_const.at(plane),
                                         vehicle_location_location_map_const.at(x),
                                         vehicle_location_location_map_const.at(y));
}

static bool_t IsOutOfChina(const float64_t longitude, const float64_t latitude)
{
    if (longitude < 72.004 || longitude > 137.8347)
    {
        return true;
    }
    if (latitude < 0.8293 || latitude > 55.8271)
    {
        return true;
    }
    return false;
}

static float64_t TransformLatitude(const float64_t longitude, const float64_t latitude)
{
    float64_t ret = -100.0 + 2.0 * longitude + 3.0 * latitude + 0.2 * latitude * latitude + 0.1 * longitude * latitude +
                    0.2 * sqrt(abs(longitude));
    ret += (20.0 * sin(6.0 * longitude * M_PI) + 20.0 * sin(2.0 * longitude * M_PI)) * 2.0 / 3.0;
    ret += (20.0 * sin(latitude * M_PI) + 40.0 * sin(latitude / 3.0 * M_PI)) * 2.0 / 3.0;
    ret += (160.0 * sin(latitude / 12.0 * M_PI) + 320 * sin(latitude * M_PI / 30.0)) * 2.0 / 3.0;
    return ret;
}

static float64_t TransformLongitude(const float64_t longitude, const float64_t latitude)
{
    float64_t ret = 300.0 + longitude + 2.0 * latitude + 0.1 * longitude * longitude + 0.1 * longitude * latitude +
                    0.1 * std::sqrt(std::abs(longitude));
    ret += (20.0 * sin(6.0 * longitude * M_PI) + 20.0 * sin(2.0 * longitude * M_PI)) * 2.0 / 3.0;
    ret += (20.0 * sin(longitude * M_PI) + 40.0 * sin(longitude / 3.0 * M_PI)) * 2.0 / 3.0;
    ret += (150.0 * sin(longitude / 12.0 * M_PI) + 300.0 * sin(longitude / 30.0 * M_PI)) * 2.0 / 3.0;
    return ret;
}

bool_t ConvertWgs84ToGcj02(float64_t& lat, float64_t& lon)
{
    if (IsOutOfChina(lon, lat))
    {
        return false;
    }

    float64_t lat_trans  = TransformLatitude(lon - 105.0, lat - 35.0);
    float64_t lon_trans  = TransformLongitude(lon - 105.0, lat - 35.0);
    float64_t radlat     = lat / 180.0 * M_PI;
    float64_t magic      = sin(radlat);
    magic                = 1 - EarthEccentricity * magic * magic;
    float64_t sqrt_magic = sqrt(magic);
    lat_trans            = (lat_trans * 180.0) / ((Radius * (1 - EarthEccentricity)) / (magic * sqrt_magic) * M_PI);
    lon_trans            = (lon_trans * 180.0) / (Radius / sqrt_magic * cos(radlat) * M_PI);
    lat += lat_trans;
    lon += lon_trans;
    return true;
}

void TransformToBody(Imud& imu, const holo::geometry::Pose3d& bTi)
{
    // const Pose3 bTi = extrinsic.GetPose();
    holo::numerics::Matrix3d const bRi = bTi.GetRotation().ToMatrix();
    holo::numerics::Vector3d const av  = bRi * imu.GetAngularVelocity<holo::numerics::Vector3d>();
    holo::numerics::Vector3d       la  = bRi * imu.GetLinearAcceleration<holo::numerics::Vector3d>();
    // Centrifugal acceleration
    holo::geometry::Point3d const  t = bTi.GetTranslation();
    holo::numerics::Vector3d const bti(t[0], t[1], t[2]);
    if (!bti.IsZero())
    {
        // Subtract out the the centripetal acceleration from the unbiased one
        // to get linear acceleration vector in the imu frame:
        holo::numerics::Matrix3d const body_Omega_body = av.ToSkewSymmetric();
        holo::numerics::Vector3d const b_velocity_bs   = body_Omega_body * bti;  // magnitude: omega * arm
        la -= body_Omega_body * b_velocity_bs;
    }
    imu.SetAngularVelocity(av.At(0), av.At(1), av.At(2));
    imu.SetLinearAcceleration(la.At(0), la.At(1), la.At(2));
}

bool_t FileExist(const std::string& filename)
{
    std::fstream check_file;
    check_file.open(filename, std::ios::in);
    if (!check_file)
    {
        return false;
    }
    else
    {
        check_file.close();
    }
    return true;
}
}  // namespace sensors
}  // namespace holo
