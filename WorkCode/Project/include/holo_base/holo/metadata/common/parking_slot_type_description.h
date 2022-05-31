#ifndef HOLO_METADATA_COMMON_PARKING_SLOT_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_PARKING_SLOT_TYPE_DESCRIPTION_H_

#include <holo/common/parking_slot.h>
#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/geometry/point3_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace common_type
{
static constexpr char PARKING_SLOT_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::ParkingSlotFrameT<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto type_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::ParkingSlotT::Type");
        (void)type_desc
            ->SetEnumerates({{0U, "PERPENDICULAR"}, {1U, "PARALLEL"}, {2U, "ANGLE"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto position_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::ParkingSlotT::Position");
        (void)position_desc
            ->SetEnumerates({{0U, "LEFT"}, {1U, "RIGHT"}, {2U, "FRONT"}, {3U, "BACK"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto status_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::ParkingSlotT::Status");
        (void)status_desc
            ->SetEnumerates({{0U, "UNKNOWN"}, {1U, "FREE"}, {2U, "OCCUPIED"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto parking_slot_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::ParkingSlotT");
        (void)parking_slot_desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"is_valid", TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"is_rear_vertex_available", TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"is_center_vertex_available", TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"is_stopper_available", TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"type", type_desc},
                 {"position", position_desc},
                 {"status", status_desc},
                 {"width", TypeDescriptionResolver<TypeReferenceTag<0U, common_type::PARKING_SLOT_SCALAR_TYPE_NAME>, ALIGN,
                                                   IS_BIG_ENDIAN>::Get()},
                 {"height", TypeDescriptionResolver<TypeReferenceTag<0U, common_type::PARKING_SLOT_SCALAR_TYPE_NAME>, ALIGN,
                                                    IS_BIG_ENDIAN>::Get()},
                 {"angle", TypeDescriptionResolver<TypeReferenceTag<0U, common_type::PARKING_SLOT_SCALAR_TYPE_NAME>, ALIGN,
                                                   IS_BIG_ENDIAN>::Get()},
                 {"confidence", TypeDescriptionResolver<TypeReferenceTag<0U, common_type::PARKING_SLOT_SCALAR_TYPE_NAME>,
                                                        ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"vertices[0]",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, common_type::PARKING_SLOT_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"vertices[1]",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, common_type::PARKING_SLOT_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"vertices[2]",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, common_type::PARKING_SLOT_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"vertices[3]",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, common_type::PARKING_SLOT_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"center_vertex",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, common_type::PARKING_SLOT_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"stopper_vertices[0]",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, common_type::PARKING_SLOT_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"stopper_vertices[1]",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, common_type::PARKING_SLOT_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()}});

        auto parking_slot_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)parking_slot_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(parking_slot_desc);

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::ParkingSlotFrameT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers({{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"parking_slot", parking_slot_sequence_desc}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo
#endif
