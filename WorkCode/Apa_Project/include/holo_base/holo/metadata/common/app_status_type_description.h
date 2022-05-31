#ifndef HOLO_METADATA_COMMON_APP_STATUS_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_APP_STATUS_TYPE_DESCRIPTION_H_

#include <holo/common/app_status.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::AppStatus, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::AppStatus");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"node_id", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"status", TypeDescriptionResolver<holo::metadata::SequenceTag<uint8_t, uint8_t>, sizeof(uint8_t),
                                                IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
