#ifndef HOLO_METADATA_PREDICTION_INTENTION_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_PREDICTION_INTENTION_TYPE_DESCRIPTION_H_

#include <holo/common/gnss_position.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::prediction::Intention, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto lateral_intention_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::prediction::Intention::LateralIntention");
        (void)lateral_intention_desc
            ->SetEnumerates(
                {{0U, "UNKNOWN"}, {1U, "LANE_KEEP"}, {2U, "CUT_IN_EGO"}, {3U, "CUT_IN_OTHERS"}, {4U, "INVALID"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto longitudinal_intention_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::prediction::Intention::LongitudinalIntention");
        (void)longitudinal_intention_desc
            ->SetEnumerates(
                {{0U, "UNKNOWN"}, {1U, "SPEED_KEEP"}, {2U, "ACCELERATE"}, {3U, "DECELERATE"}, {4U, "INVALID"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::prediction::Intention");
        (void)desc->SetTemplates({}).SetMembers(
            {{"stamp_start", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"stamp_end", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"id", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lateral_intention", lateral_intention_desc},
             {"longitudinal_intention", longitudinal_intention_desc},
             {"lateral_confidence", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"longitudinal_confidence", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
