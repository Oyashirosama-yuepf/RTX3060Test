#ifndef HOLO_METADATA_COMMON_ODM_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_ODM_TYPE_DESCRIPTION_H_

#include <holo/common/odm.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::OdmStates, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto odm_state_desc = std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::OdmState");
        (void)odm_state_desc
            ->SetFields({{"pred_dist", 0, 14, TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"pred_dist_valid", 14, 1, TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"pred_time", 15, 7, TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"pred_time_valid", 22, 1, TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"enable", 23, 1, TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"reserved", 24, 8, TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto odm_state_array_desc = std::make_shared<TypeDescriptionArray>(ALIGN, IS_BIG_ENDIAN);
        (void)odm_state_array_desc->SetSize(9U).SetElementType(odm_state_desc);

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::OdmStates");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"odm_states", odm_state_array_desc}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
