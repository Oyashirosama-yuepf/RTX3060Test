#ifndef HOLO_METADATA_COMMON_ODOMETRY_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_ODOMETRY_TYPE_DESCRIPTION_H_

#include <holo/common/odometry.h>
#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/geometry/pose3_type_description.h>
#include <holo/metadata/geometry/quaternion_type_description.h>
#include <holo/metadata/numerics/matrix_type_description.h>
#include <holo/metadata/numerics/vector_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace common_type
{
static constexpr char ODOMETRY_SCALAR_TYPE_NAME[] = "ScalarType";
}

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::OdometryPrecision, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto precision_enum_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::OdometryPrecision::Precision");
        (void)precision_enum_desc->SetEnumerates({{0U, "UNKNOWN"}, {1U, "LOW"}, {2U, "MEDIUM"}, {3U, "HIGH"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto position_x_enum_desc = precision_enum_desc;
        auto position_y_enum_desc = precision_enum_desc;
        auto position_z_enum_desc = precision_enum_desc;

        auto rotation_x_enum_desc = precision_enum_desc;
        auto rotation_y_enum_desc = precision_enum_desc;
        auto rotation_z_enum_desc = precision_enum_desc;

        auto linear_velocity_x_enum_desc = precision_enum_desc;
        auto linear_velocity_y_enum_desc = precision_enum_desc;
        auto linear_velocity_z_enum_desc = precision_enum_desc;

        auto angular_velocity_x_enum_desc = precision_enum_desc;
        auto angular_velocity_y_enum_desc = precision_enum_desc;
        auto angular_velocity_z_enum_desc = precision_enum_desc;

        auto linear_acceleration_x_enum_desc = precision_enum_desc;
        auto linear_acceleration_y_enum_desc = precision_enum_desc;
        auto linear_acceleration_z_enum_desc = precision_enum_desc;

        auto desc = std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::OdometryPrecision");
        (void)desc
            ->SetFields({{"position_x", 0, 2, position_x_enum_desc},
                         {"position_y", 2, 2, position_y_enum_desc},
                         {"position_z", 4, 2, position_z_enum_desc},
                         {"rotation_x", 6, 2, rotation_x_enum_desc},
                         {"rotation_y", 8, 2, rotation_y_enum_desc},
                         {"rotation_z", 10, 2, rotation_z_enum_desc},
                         {"linear_velocity_x", 12, 2, linear_velocity_x_enum_desc},
                         {"linear_velocity_y", 14, 2, linear_velocity_y_enum_desc},
                         {"linear_velocity_z", 16, 2, linear_velocity_z_enum_desc},
                         {"angular_velocity_x", 18, 2, angular_velocity_x_enum_desc},
                         {"angular_velocity_y", 20, 2, angular_velocity_y_enum_desc},
                         {"angular_velocity_z", 22, 2, angular_velocity_z_enum_desc},
                         {"linear_acceleration_x", 24, 2, linear_acceleration_x_enum_desc},
                         {"linear_acceleration_y", 26, 2, linear_acceleration_y_enum_desc},
                         {"linear_acceleration_z", 28, 2, linear_acceleration_z_enum_desc}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::OdometryT<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto status_desc =
            std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::OdometryT::Status");
        (void)status_desc
            ->SetBits({{0, "SOLUTIONNOGOOD"},
                       {1, "POSITIONINACTIVE"},
                       {2, "ORIENTATIONINACTIVE"},
                       {3, "LINEARVELOCITYINACTIVE"},
                       {4, "ANGULARVELOCITYINACTIVE"},
                       {5, "LINEARACCELERATIONINACTIVE"},
                       {6, "UNKNOWN"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto source_desc =
            std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::OdometryT::Source");
        (void)source_desc
            ->SetBits({{0, "GNSS"},
                       {1, "IMU"},
                       {2, "VISION"},
                       {3, "WHEEL"},
                       {4, "RADAR"},
                       {5, "LIDAR"},
                       {6, "SEMANTIC"},
                       {7, "HD_MAP"},
                       {8, "RTK"},
                       {9, "DETECTED_LANE"},
                       {10, "UNKNOWN"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::OdometryT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"parent_coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"child_coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"status", status_desc},
                 {"source", source_desc},
                 {"precision", TypeDescriptionResolver<holo::common::OdometryPrecision, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"pose", TypeDescriptionResolver<
                              holo::geometry::Pose3T<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>>, ALIGN,
                              IS_BIG_ENDIAN>::Get()},
                 {"velocity", TypeDescriptionResolver<
                                  holo::numerics::VectorT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>, 6u>,
                                  ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"linear_acceleration",
                  TypeDescriptionResolver<
                      holo::numerics::VectorT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>, 3u>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"pose_covariance",
                  TypeDescriptionResolver<
                      holo::numerics::MatrixT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>, 6u, 6u>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"velocity_covariance",
                  TypeDescriptionResolver<
                      holo::numerics::MatrixT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>, 6u, 6u>, ALIGN,
                      IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <typename T, size_t SIZE_VALUE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::LocalMapOdometryT<T, SIZE_VALUE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto status_desc =
            std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::LocalMapOdometryT::Status");
        (void)status_desc
            ->SetBits({{0, "SOLUTIONNOGOOD"},
                       {1, "POSITIONINACTIVE"},
                       {2, "ORIENTATIONINACTIVE"},
                       {3, "LINEARVELOCITYINACTIVE"},
                       {4, "ANGULARVELOCITYINACTIVE"},
                       {5, "LINEARACCELERATIONINACTIVE"},
                       {6, "UNKNOWN"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto source_desc =
            std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::LocalMapOdometryT::Source");
        (void)source_desc
            ->SetBits({{0, "GNSS"},
                       {1, "IMU"},
                       {2, "VISION"},
                       {3, "WHEEL"},
                       {4, "RADAR"},
                       {5, "LIDAR"},
                       {6, "SEMANTIC"},
                       {7, "HD_MAP"},
                       {8, "RTK"},
                       {9, "DETECTED_LANE"},
                       {10, "UNKNOWN"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto local_map_odometry_status_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::LocalMapOdometryT::LocalMapOdometryStatus");
        (void)local_map_odometry_status_desc
            ->SetEnumerates({{0x0000, "UNKNOWN"},
                             {0x0001, "LOW"},
                             {0x0002, "MIDDLE"},
                             {0x0003, "LATERALHIGH"},
                             {0x0004, "LONGITUDINALHIGH"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto matching_results_desc = std::make_shared<TypeDescriptionStruct>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::LocalMapOdometryT::MatchingResult");
        (void)matching_results_desc->SetTemplates({}).SetMembers(
            {{"link_id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lane_id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"longitudinal_off_start", TypeDescriptionResolver<int32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"longitudinal_off_end", TypeDescriptionResolver<int32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"accuracy", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"relative_heading", TypeDescriptionResolver<int32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lateral_off_left", TypeDescriptionResolver<int32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lateral_off_right", TypeDescriptionResolver<int32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lateral_off_middle", TypeDescriptionResolver<int32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"probobility", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto matching_results_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)matching_results_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(matching_results_desc);

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::LocalMapOdometryT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"parent_coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"child_coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"status", status_desc},
                 {"source", source_desc},
                 {"precision", TypeDescriptionResolver<holo::common::OdometryPrecision, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"pose", TypeDescriptionResolver<
                              holo::geometry::Pose3T<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>>, ALIGN,
                              IS_BIG_ENDIAN>::Get()},
                 {"velocity", TypeDescriptionResolver<
                                  holo::numerics::VectorT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>, 6u>,
                                  ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"linear_acceleration",
                  TypeDescriptionResolver<
                      holo::numerics::VectorT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>, 3u>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"pose_covariance",
                  TypeDescriptionResolver<
                      holo::numerics::MatrixT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>, 6u, 6u>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"velocity_covariance",
                  TypeDescriptionResolver<
                      holo::numerics::MatrixT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>, 6u, 6u>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"local_map_odometry_status", local_map_odometry_status_desc},
                 {"vehicle_speed", TypeDescriptionResolver<int16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"vehicle_heading", TypeDescriptionResolver<int32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"is_matching_results_actived", TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"matching_results", matching_results_sequence_desc}});
        return desc;
    }
};

template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::DrOdometryT<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto status_desc =
            std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::DrOdometryT::Status");
        (void)status_desc
            ->SetBits({{0, "SOLUTIONNOGOOD"},
                       {1, "POSITIONINACTIVE"},
                       {2, "ORIENTATIONINACTIVE"},
                       {3, "LINEARVELOCITYINACTIVE"},
                       {4, "ANGULARVELOCITYINACTIVE"},
                       {5, "LINEARACCELERATIONINACTIVE"},
                       {6, "UNKNOWN"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto source_desc =
            std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::DrOdometryT::Source");
        (void)source_desc
            ->SetBits({{0, "GNSS"},
                       {1, "IMU"},
                       {2, "VISION"},
                       {3, "WHEEL"},
                       {4, "RADAR"},
                       {5, "LIDAR"},
                       {6, "SEMANTIC"},
                       {7, "HD_MAP"},
                       {8, "RTK"},
                       {9, "DETECTED_LANE"},
                       {10, "UNKNOWN"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::DrOdometryT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"parent_coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"child_coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"status", status_desc},
                 {"source", source_desc},
                 {"precision", TypeDescriptionResolver<holo::common::OdometryPrecision, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"pose", TypeDescriptionResolver<
                              holo::geometry::Pose3T<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>>, ALIGN,
                              IS_BIG_ENDIAN>::Get()},
                 {"velocity", TypeDescriptionResolver<
                                  holo::numerics::VectorT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>, 6u>,
                                  ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"linear_acceleration",
                  TypeDescriptionResolver<
                      holo::numerics::VectorT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>, 3u>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"pose_covariance",
                  TypeDescriptionResolver<
                      holo::numerics::MatrixT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>, 6u, 6u>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"velocity_covariance",
                  TypeDescriptionResolver<
                      holo::numerics::MatrixT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>, 6u, 6u>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"ground_rotation",
                  TypeDescriptionResolver<
                      holo::geometry::QuaternionT<TypeReferenceTag<1U, common_type::ODOMETRY_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
