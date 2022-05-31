#ifndef HOLO_METADATA_MAP_MAP_NAVIGATION_REQUEST_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_MAP_NAVIGATION_REQUEST_TYPE_DESCRIPTION_H_

#include <holo/map/map_navigation_request.h>
#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/geometry/point3_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t POINT_SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::RoutingSearchRequestT<POINT_SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto layer_id_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationPoint::LayerId");
        (void)layer_id_desc
            ->SetEnumerates({{0U, "UNKNOWN"},
                             {1U, "POI"},
                             {2U, "ROAD"},
                             {3U, "PARKING_FLOOR"},
                             {4U, "PARKING_LOT"},
                             {5U, "PARKING_SPACE"},
                             {200U, "RESERVED_1"},
                             {201U, "RESERVED_2"},
                             {202U, "RESERVED_3"},
                             {203U, "RESERVED_4"},
                             {204U, "RESERVED_5"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto navigation_point_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::NavigationPoint");
        (void)navigation_point_desc->SetTemplates({}).SetMembers(
            {{"layer_id", layer_id_desc},
             {"element_id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"position", TypeDescriptionResolver<holo::geometry::Point3T<float32_t>, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto policy_desc = std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN,
                                                                      "holo::map::RoutingSearchRequestT::Policy");
        (void)policy_desc
            ->SetEnumerates({{0U, "DEFAULT"},
                             {1U, "SHORTEST_DISTANCE"},
                             {2U, "SHORTEST_TIME"},
                             {3U, "SHORTEST_TOLL"},
                             {4U, "SHORTEST_HIGHWAY"},
                             {5U, "SHORTEST_MORE_PARKINGSPACE"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::RoutingSearchRequestT");
        (void)desc->SetTemplates({}).SetMembers(
            {{"navigation_points", navigation_point_desc},
             {"request_id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"policy", policy_desc}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
