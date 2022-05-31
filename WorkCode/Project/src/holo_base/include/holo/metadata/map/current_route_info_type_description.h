#ifndef HOLO_METADATA_MAP_CURRENT_ROUTE_INFO_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_CURRENT_ROUTE_INFO_TYPE_DESCRIPTION_H_

#include <holo/map/current_route_info.h>
#include <holo/metadata/map/link_info_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::CurrentRouteInfo, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::CurrentRouteInfo");
        (void)desc->SetTemplates({}).SetMembers(
            {{"vec_links", TypeDescriptionResolver<holo::metadata::SequenceTag<holo::map::LinkInfo, uint32_t>, ALIGN,
                                                   IS_BIG_ENDIAN>::Get()},
             {"vec_rear_links", TypeDescriptionResolver<holo::metadata::SequenceTag<holo::map::LinkInfo, uint32_t>,
                                                        ALIGN, IS_BIG_ENDIAN>::Get()},
             {"vec_objects", TypeDescriptionResolver<holo::metadata::SequenceTag<holo::map::CommonObject, uint32_t>,
                                                     ALIGN, IS_BIG_ENDIAN>::Get()},
             {"status", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
