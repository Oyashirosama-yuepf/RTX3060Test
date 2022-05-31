#ifndef HOLO_METADATA_COMMON_TIMESTAMP_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_TIMESTAMP_TYPE_DESCRIPTION_H_

#include <holo/common/details/timestamp.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::details::Duration, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::Duration");
        (void)desc->SetTemplates({}).SetMembers(
            {{"sec", TypeDescriptionResolver<holo::int32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"nsec", TypeDescriptionResolver<holo::int32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::details::Timestamp, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::Timestamp");
        (void)desc->SetTemplates({}).SetMembers(
            {{"sec", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"nsec", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
