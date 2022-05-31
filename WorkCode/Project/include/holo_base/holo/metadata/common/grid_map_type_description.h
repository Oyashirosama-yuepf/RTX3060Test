#ifndef HOLO_METADATA_COMMON_GRID_MAP_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_GRID_MAP_TYPE_DESCRIPTION_H_

#include <holo/common/grid_map.h>
#include <holo/metadata/common/classification_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/geometry/point2_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace common_type
{
static constexpr char GRID_MAP_CELL_TYPE_NAME[] = "CellType";
}  // namespace common

template <typename Cell, size_t W, size_t H, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::GridMap<Cell, W, H>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::GridMap");
        (void)desc->SetTemplates({{"CellType", TypeDescriptionResolver<Cell, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"resolution", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"origin_x", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"origin_y", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"cells",
                  TypeDescriptionResolver<
                      holo::metadata::SequenceTag<TypeReferenceTag<1U, common_type::GRID_MAP_CELL_TYPE_NAME>, uint32_t>,
                      ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::GridMapCell, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto motion_status_type_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::GridMapCell::MotionStatusType");
        (void)motion_status_type_desc
            ->SetEnumerates({{0U, "UNKNOWN"},
                             {1U, "MOVING"},
                             {2U, "STATIONARY"},
                             {3U, "ONCOMING"},
                             {4U, "STOPPED"},
                             {5U, "PARKED"},
                             {6U, "CROSSING"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::GridMapCell");
        (void)desc->SetTemplates({}).SetMembers(
            {{"center", TypeDescriptionResolver<holo::geometry::Point2T<holo::float32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"relative_velocity",
              TypeDescriptionResolver<holo::geometry::Point2T<holo::float32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"classification", TypeDescriptionResolver<holo::common::Classification, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"obstacle_id", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"is_occupied", TypeDescriptionResolver<holo::bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"motion_status", motion_status_type_desc}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
