#ifndef HOLO_METADATA_OBSTACLE_FUSED_OBSTACLE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_OBSTACLE_FUSED_OBSTACLE_TYPE_DESCRIPTION_H_

#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/common/sensor_id_type_description.h>
#include <holo/metadata/geometry/point2_type_description.h>
#include <holo/metadata/geometry/point3_type_description.h>
#include <holo/metadata/type_description.h>
#include <holo/obstacle/fused_obstacle.h>

namespace holo
{
namespace metadata
{
namespace obstacle_type
{
static constexpr char FUSED_OBSTACLE_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::gh02::obstacle::FusedObstacleT<T, SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto history_info_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN,
                                                                         "holo::obstacle::FusedObstacleT::HistoryInfo");
        (void)history_info_desc->SetTemplates({}).SetMembers(
            {{"sensor_id", TypeDescriptionResolver<holo::common::SensorId, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"obstacle_id", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"raw_sensor_capture_timestamp",
              TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"sensor_perception_capture_timestamp",
              TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"sensor_perception_output_timestamp",
              TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"fusion_capture_timestamp",
              TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"fusion_output_timestamp",
              TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto history_info_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)history_info_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(history_info_desc);

        auto predict_path_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN,
                                                                         "holo::obstacle::FusedObstacleT::HistoryInfo");
        (void)predict_path_desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<TypeReferenceTag<2U, obstacle_type::FUSED_OBSTACLE_SCALAR_TYPE_NAME>, ALIGN, IS_BIG_ENDIAN>::Get()}}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"position", TypeDescriptionResolver<
                              holo::geometry::Point2T<TypeReferenceTag<1U, obstacle_type::FUSED_OBSTACLE_SCALAR_TYPE_NAME>>,
                              ALIGN, IS_BIG_ENDIAN>::Get()},
             {"heading_angle", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"velocity", TypeDescriptionResolver<
                              holo::geometry::Point2T<TypeReferenceTag<1U, obstacle_type::FUSED_OBSTACLE_SCALAR_TYPE_NAME>>,
                              ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto predict_path_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)predict_path_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(predict_path_desc);

        auto lamp_status_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::obstacle::FusedObstacleT::LampStatus");
        (void)lamp_status_desc
            ->SetEnumerates({{0U, "NONE"},
                             {1U, "LEFT_TURN"},
                             {2U, "RIGHT_TURN"},
                             {3U, "DOUBLE_FLASH"},
                             {4U, "BRAKE"},
                             {5U, "BACKING_UP"},
                             {6U, "HEADLAMP"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto tracking_status_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::obstacle::FusedObstacleT::TrackingStatus");
        (void)tracking_status_desc->SetEnumerates({{0U, "INVALID"}, {1U, "NEW"}, {2U, "UPDATED"}, {3U, "COASTED"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto cut_in_status_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::obstacle::FusedObstacleT::CutInStatus");
        (void)cut_in_status_desc->SetEnumerates({{0U, "UNKNOWN"}, {1U, "CUT_IN"}, {2U, "CUT_OUT"}, {3U, "INVALID"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto moving_status_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::obstacle::FusedObstacleT::MovingStatus");
        (void)moving_status_desc->SetEnumerates({{0U, "STATIC"}, {1U, "MOVING"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::obstacle::FusedObstacleT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"history_info", history_info_sequence_desc},
                 {"obstacle_id", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"classification", TypeDescriptionResolver<holo::common::Classification, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"confidence", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"exist_confidence", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"classification_confidence", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"position",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, obstacle_type::FUSED_OBSTACLE_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"absolute_velocity",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, obstacle_type::FUSED_OBSTACLE_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"relative_velocity",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, obstacle_type::FUSED_OBSTACLE_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"absolute_accelaration",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, obstacle_type::FUSED_OBSTACLE_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},

                 {"heading_angle", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"heading_angular_velocity", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"bbox3d_width", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"bbox3d_height", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"bbox3d_depth", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"heading_angle_std", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"tracking_period", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"is_movable", TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"is_heading_to_ego_car", TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"is_ever_heading_to_ego_car", TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"lamp_status", lamp_status_desc},
                 {"tracking_status", tracking_status_desc},
                 {"cut_in_status", cut_in_status_desc},
                 {"moving_status", moving_status_desc},

                 {"predict_paths", predict_path_sequence_desc}, 
                 {
                     "polygon",
                     TypeDescriptionResolver<
                         holo::metadata::SequenceTag<
                             holo::geometry::Point3T<TypeReferenceTag<2U, obstacle_type::FUSED_OBSTACLE_SCALAR_TYPE_NAME>>,
                             uint32_t>,
                         ALIGN, IS_BIG_ENDIAN>::Get()},

                 {"position_cov",
                  TypeDescriptionResolver<holo::metadata::ArrayTag<holo::metadata::ArrayTag<
                                              TypeReferenceTag<2U, obstacle_type::FUSED_OBSTACLE_SCALAR_TYPE_NAME>, 3U>, 3U>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()},

                 {"velocity_cov",
                  TypeDescriptionResolver<holo::metadata::ArrayTag<holo::metadata::ArrayTag<
                                              TypeReferenceTag<2U, obstacle_type::FUSED_OBSTACLE_SCALAR_TYPE_NAME>, 3U>, 3U>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"accelaration_cov",
                  TypeDescriptionResolver<holo::metadata::ArrayTag<holo::metadata::ArrayTag<
                                              TypeReferenceTag<2U, obstacle_type::FUSED_OBSTACLE_SCALAR_TYPE_NAME>, 3U>, 3U>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"obstacle_size_cov",
                  TypeDescriptionResolver<holo::metadata::ArrayTag<holo::metadata::ArrayTag<
                                              TypeReferenceTag<2U, obstacle_type::FUSED_OBSTACLE_SCALAR_TYPE_NAME>, 3U>, 3U>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
