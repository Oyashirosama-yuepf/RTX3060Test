#ifndef HOLO_METADATA_PREDICTION_INTENTIONS_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_PREDICTION_INTENTIONS_TYPE_DESCRIPTION_H_

#include <holo/common/gnss_position.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::prediction::Intentions, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::prediction::Intentions");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"data", TypeDescriptionResolver<holo::metadata::SequenceTag<holo::prediction::Intention, uint32_t>, ALIGN,
                                              IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
