#include <holo/common/alarm.h>
#include <holo/common/apa_control_command.h>
#include <holo/common/app_status.h>
#include <holo/common/camera_lane_boundary.h>
#include <holo/common/chassis_state.h>
#include <holo/common/control_command.h>
#include <holo/common/coordinate.h>
#include <holo/common/ddt.h>
#include <holo/common/freespace.h>
#include <holo/common/gnss_position.h>
#include <holo/common/gnss_pvt.h>
#include <holo/common/gnss_raw_measurement.h>
#include <holo/common/grid_map.h>
#include <holo/common/imu.h>
#include <holo/common/imu_bias.h>
#include <holo/common/lane_boundary2.h>
#include <holo/common/lane_scene.h>
#include <holo/common/light_signal_request.h>
#include <holo/common/odm.h>
#include <holo/common/odometry.h>
#include <holo/common/parking_slot.h>
#include <holo/common/path.h>
#include <holo/common/perception_ability.h>
#include <holo/common/road_frame2.h>
#include <holo/common/road_type.h>
#include <holo/common/sensor_id.h>
#include <holo/common/timestamp.h>
#include <holo/common/vehicle_body_state.h>
#include <holo/common/vehicle_location.h>
#include <holo/common/weather.h>

#include <holo/map/advice.h>
#include <holo/map/common_object.h>
#include <holo/map/current_route_info.h>
#include <holo/map/geofence.h>
#include <holo/map/lane_info.h>
#include <holo/map/lane_mark_info.h>
#include <holo/map/lane_path.h>
#include <holo/map/link_info.h>
#include <holo/map/map_navigation_request.h>
#include <holo/map/map_navigation_response.h>
#include <holo/map/navigation.h>
#include <holo/map/road_ref_point_attributes.h>
#include <holo/map/road_speed_limits.h>

#include <holo/planning/state.h>

#include <holo/vision/image_objects.h>
#include <holo/vision/keypoint2.h>
#include <holo/vision/object.h>

#include <holo/prediction/intention.h>
#include <holo/prediction/intentions.h>

#include <holo/obstacle/fused_obstacle.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/obstacle/obstacle_radar.h>
#include <holo/obstacle/obstacle_uss.h>
#include <holo/obstacle/obstacle_vision.h>

#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>

#include <holo/metadata/common/alarm_type_description.h>
#include <holo/metadata/common/apa_control_command_type_description.h>
#include <holo/metadata/common/app_status_type_description.h>
#include <holo/metadata/common/camera_lane_boundary_type_description.h>
#include <holo/metadata/common/chassis_state_type_description.h>
#include <holo/metadata/common/control_command_type_description.h>
#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/common/ddt_type_description.h>
#include <holo/metadata/common/freespace_type_description.h>
#include <holo/metadata/common/gnss_position_type_description.h>
#include <holo/metadata/common/gnss_pvt_type_description.h>
#include <holo/metadata/common/gnss_raw_measurement_type_description.h>
#include <holo/metadata/common/grid_map_type_description.h>
#include <holo/metadata/common/imu_bias_type_description.h>
#include <holo/metadata/common/imu_type_description.h>
#include <holo/metadata/common/lane_boundary_type_description.h>
#include <holo/metadata/common/lane_scene_type_description.h>
#include <holo/metadata/common/light_signal_request_type_description.h>
#include <holo/metadata/common/odm_type_description.h>
#include <holo/metadata/common/odometry_type_description.h>
#include <holo/metadata/common/parking_slot_type_description.h>
#include <holo/metadata/common/path_type_description.h>
#include <holo/metadata/common/perception_ability_type_description.h>
#include <holo/metadata/common/road_frame_type_description.h>
#include <holo/metadata/common/road_type_type_description.h>
#include <holo/metadata/common/sensor_id_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/common/vehicle_body_state_type_description.h>
#include <holo/metadata/common/vehicle_location_type_description.h>
#include <holo/metadata/common/weather_type_description.h>

#include <holo/metadata/map/advice_type_description.h>
#include <holo/metadata/map/common_object_type_description.h>
#include <holo/metadata/map/current_route_info_type_description.h>
#include <holo/metadata/map/geofence_type_description.h>
#include <holo/metadata/map/lane_info_type_description.h>
#include <holo/metadata/map/lane_mark_info_type_description.h>
#include <holo/metadata/map/lane_path_type_description.h>
#include <holo/metadata/map/link_info_type_description.h>
#include <holo/metadata/map/map_navigation_request_type_description.h>
#include <holo/metadata/map/map_navigation_response_type_description.h>
#include <holo/metadata/map/navigation_type_description.h>
#include <holo/metadata/map/road_ref_point_attributes_type_description.h>
#include <holo/metadata/map/road_speed_limits_type_description.h>
#include <holo/metadata/planning/state_type_description.h>
#include <holo/metadata/vision/image_objects_type_description.h>
#include <holo/metadata/vision/key_ponit2_type_description.h>
#include <holo/metadata/vision/object_type_description.h>

#include <holo/metadata/prediction/intention_type_description.h>
#include <holo/metadata/prediction/intentions_type_description.h>

#include <holo/metadata/obstacle/fused_obstacle_type_description.h>
#include <holo/metadata/obstacle/obstacle_general_type_description.h>
#include <holo/metadata/obstacle/obstacle_list_type_description.h>
#include <holo/metadata/obstacle/obstacle_radar_type_description.h>
#include <holo/metadata/obstacle/obstacle_uss_type_description.h>
#include <holo/metadata/obstacle/obstacle_vision_type_description.h>

#include <holo/metadata/point_cloud/point_cloud_type_description.h>
#include <holo/metadata/point_cloud/point_type_type_description.h>

#include <holo/metadata/type_description.h>

#include <sys/stat.h>
#include <fstream>
#include <map>

static std::string version = "v0_12";

using ScalarType = holo::float32_t;
using Point2Type = holo::geometry::Point2T<ScalarType>;
using CurveType  = holo::geometry::CurvePolynomial<Point2Type, 0U, 3U>;
using Point3Type = holo::geometry::Point3T<ScalarType>;

using ObjectType      = ::holo::vision::ObjectT<holo::vision::KeyPoint2T<ScalarType>, 8U>;
using ImageObjectType = ::holo::vision::ImageObjectsT<ObjectType, 128U>;

static std::map<std::string, holo::metadata::TypeDescription::PtrType> td_map = {
    {version + "/common/Alarm", holo::metadata::TypeDescriptionResolver<holo::common::Alarm>::Get()},
    {version + "/common/ApaControlCommand",
     holo::metadata::TypeDescriptionResolver<holo::common::ApaControlCommand>::Get()},
    {version + "/common/AppStatus", holo::metadata::TypeDescriptionResolver<holo::common::AppStatus>::Get()},
    {version + "/common/CameraLaneBoundariesT",
     holo::metadata::TypeDescriptionResolver<
         holo::common::CameraLaneBoundariesT<holo::common::CameraLaneBoundaryT<ScalarType, 3U, 4U>>, 16U>::Get()},
    {version + "/common/ChassisState", holo::metadata::TypeDescriptionResolver<holo::common::ChassisState>::Get()},
    {version + "/common/ControlCommand", holo::metadata::TypeDescriptionResolver<holo::common::ControlCommand>::Get()},
    {version + "/common/Coordinate", holo::metadata::TypeDescriptionResolver<holo::common::Coordinate>::Get()},
    {version + "/common/DdtStates", holo::metadata::TypeDescriptionResolver<holo::common::DdtStates<0U>>::Get()},
    {version + "/common/FreespaceT",
     holo::metadata::TypeDescriptionResolver<holo::common::Freespace<Point2Type, 0U>>::Get()},
    {version + "/common/GnssPosition", holo::metadata::TypeDescriptionResolver<holo::GnssPosition>::Get()},
    {version + "/common/GnssPvt", holo::metadata::TypeDescriptionResolver<holo::common::GnssPvt>::Get()},
    {version + "/common/GnssRawMeasurement",
     holo::metadata::TypeDescriptionResolver<holo::common::GnssRawMeasurement>::Get()},
    {version + "/common/GridMap",
     holo::metadata::TypeDescriptionResolver<holo::common::GridMap<holo::common::GridMapCell, 128U, 128U>>::Get()},
    {version + "/common/ImuBiasT", holo::metadata::TypeDescriptionResolver<holo::common::ImuBiasf>::Get()},
    {version + "/common/ImuT", holo::metadata::TypeDescriptionResolver<holo::common::Imuf>::Get()},
    {version + "/common/LaneBoundaryT",
     holo::metadata::TypeDescriptionResolver<holo::common::LaneBoundary<CurveType>>::Get()},
    {version + "/common/LaneScene", holo::metadata::TypeDescriptionResolver<holo::common::LaneScene>::Get()},
    {version + "/common/LightSignalRequest", holo::metadata::TypeDescriptionResolver<holo::LightSignalRequest>::Get()},
    {version + "/common/OdmStates", holo::metadata::TypeDescriptionResolver<holo::common::OdmStates>::Get()},
    {version + "/common/OdometryT", holo::metadata::TypeDescriptionResolver<holo::common::Odometryf>::Get()},
    {version + "/common/ParkingSlotFrameT",
     holo::metadata::TypeDescriptionResolver<holo::common::ParkingSlotFrameT<holo::float32_t>>::Get()},
    {version + "/common/PathT", holo::metadata::TypeDescriptionResolver<holo::common::Pathf>::Get()},
    {version + "/common/PerceptionAbility",
     holo::metadata::TypeDescriptionResolver<holo::common::PerceptionAbility>::Get()},
    {version + "/common/RoadFrameT",
     holo::metadata::TypeDescriptionResolver<holo::common::RoadFrame<CurveType>>::Get()},
    {version + "/common/RoadFramePolynomialT",
     holo::metadata::TypeDescriptionResolver<
         holo::common::RoadFrame<holo::numerics::Polynomial<holo::float32_t, 0U>>>::Get()},
    {version + "/common/RoadType", holo::metadata::TypeDescriptionResolver<holo::common::RoadType>::Get()},
    {version + "/common/LaneType", holo::metadata::TypeDescriptionResolver<holo::common::LaneType>::Get()},
    {version + "/common/SensorId", holo::metadata::TypeDescriptionResolver<holo::common::SensorId>::Get()},
    {version + "/common/Timestamp", holo::metadata::TypeDescriptionResolver<holo::common::Timestamp>::Get()},
    {version + "/common/VehicleBodyState",
     holo::metadata::TypeDescriptionResolver<holo::common::VehicleBodyState>::Get()},
    {version + "/common/VehicleLocation",
     holo::metadata::TypeDescriptionResolver<holo::common::VehicleLocation>::Get()},
    {version + "/common/Weather", holo::metadata::TypeDescriptionResolver<holo::common::Weather>::Get()},

    {version + "/map/Advice", holo::metadata::TypeDescriptionResolver<holo::map::Advice>::Get()},
    {version + "/map/CommonObject", holo::metadata::TypeDescriptionResolver<holo::map::CommonObject>::Get()},
    {version + "/map/CurrentRouteInfo", holo::metadata::TypeDescriptionResolver<holo::map::CurrentRouteInfo>::Get()},
    {version + "/map/Geofence", holo::metadata::TypeDescriptionResolver<holo::map::Geofences>::Get()},
    {version + "/map/LaneInfo", holo::metadata::TypeDescriptionResolver<holo::map::LaneInfo>::Get()},
    {version + "/map/LaneMarkInfo", holo::metadata::TypeDescriptionResolver<holo::map::LaneMarkInfo>::Get()},
    {version + "/map/LanePath", holo::metadata::TypeDescriptionResolver<holo::map::AdviceT<32U, 32U, 32U>>::Get()},
    {version + "/map/LinkInfo", holo::metadata::TypeDescriptionResolver<holo::map::LinkInfo>::Get()},
    {version + "/map/NavigationT",
     holo::metadata::TypeDescriptionResolver<holo::map::NavigationT<16U, 32U, 64U>>::Get()},
    {version + "/map/RoutingSearchRequestT",
     holo::metadata::TypeDescriptionResolver<holo::map::RoutingSearchRequestT<128U>>::Get()},
    {version + "/map/RoutingSearchResponseT",
     holo::metadata::TypeDescriptionResolver<holo::map::RoutingSearchResponseT<128U>>::Get()},
    {version + "/map/RoadRefPointAttributes",
     holo::metadata::TypeDescriptionResolver<holo::map::RoadRefPointAttributes<holo::map::RoadScs, 1024U>>::Get()},
    {version + "/map/RoadSpeedLimits", holo::metadata::TypeDescriptionResolver<holo::map::RoadSpeedLimits>::Get()},

    {version + "/planning/State", holo::metadata::TypeDescriptionResolver<holo::planning::State>::Get()},

    {version + "/vision/KeyPoint2T",
     holo::metadata::TypeDescriptionResolver<holo::vision::KeyPoint2T<holo::float32_t>>::Get()},
    {version + "/vision/ImageObjectsT", holo::metadata::TypeDescriptionResolver<ImageObjectType>::Get()},
    {version + "/vision/ObjectT", holo::metadata::TypeDescriptionResolver<ObjectType>::Get()},

    {version + "/prediction/intention", holo::metadata::TypeDescriptionResolver<holo::prediction::Intention>::Get()},
    {version + "/prediction/intentions", holo::metadata::TypeDescriptionResolver<holo::prediction::Intentions>::Get()},

    {version + "/obstacle/FusedObstacleT",
     holo::metadata::TypeDescriptionResolver<holo::gh02::obstacle::FusedObstacleT<holo::float32_t, 256U>>::Get()},
    {version + "/obstacle/ObstacleGeneralT",
     holo::metadata::TypeDescriptionResolver<holo::obstacle::ObstacleGeneralT<holo::float32_t>>::Get()},
    {version + "/obstacle/ObstacleRadarT",
     holo::metadata::TypeDescriptionResolver<holo::obstacle::ObstacleRadarT<holo::float32_t>>::Get()},
    {version + "/obstacle/ObstacleVisionT",
     holo::metadata::TypeDescriptionResolver<holo::obstacle::ObstacleVisionT<holo::float32_t, 8U>>::Get()},
    {version + "/obstacle/ObstacleUssT",
     holo::metadata::TypeDescriptionResolver<holo::obstacle::ObstacleUssT<holo::float32_t>>::Get()},
    {version + "/obstacle/ObstaclePtrListT",
     holo::metadata::TypeDescriptionResolver<
         holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleVisionT<holo::float32_t, 8U>, 0>>::Get()},

    {version + "/point_cloud/PointXYZIRStT",
     holo::metadata::TypeDescriptionResolver<holo::point_cloud::PointXYZIRSt<holo::float32_t>>::Get()},
    {version + "/point_cloud/PointXYZIRRgbStT",
     holo::metadata::TypeDescriptionResolver<holo::point_cloud::PointXYZIRRgbSt<holo::float32_t>>::Get()},
    {version + "/point_cloud/PointCloudT",
     holo::metadata::TypeDescriptionResolver<holo::point_cloud::PointCloudT<Point3Type, 0>>::Get()},
};

int createDirectory(std::string const& relpath)
{
    size_t end = 0;
    while (end != std::string::npos)
    {
        end     = relpath.find_first_of("/", end + 1);
        int ret = mkdir(relpath.substr(0, end).c_str(), 0755);
        if (ret != 0)
        {
            if (errno != EEXIST)
            {
                return -1;
            }
            else
            {
                struct stat s;
                if (stat(relpath.substr(0, end).c_str(), &s) == 0)
                {
                    if (s.st_mode & S_IFDIR)
                    {
                        continue;
                    }
                    else
                    {
                        return -2;
                    }
                }
                else
                {
                    return -3;
                }
            }
        }
    }
    return 0;
}

int main()
{
    for (auto const& value : td_map)
    {
        std::string relpath = "metadata/" + value.first + ".yaml";
        if (relpath.find_last_of("/") != std::string::npos)
        {
            if (createDirectory(relpath.substr(0, relpath.find_last_of("/"))) != 0)
            {
                continue;
            }
        }
        std::ofstream of;
        of.open(relpath);
        of << value.second->ToYaml() << std::endl;
        of.close();
    }
    return 0;
}
