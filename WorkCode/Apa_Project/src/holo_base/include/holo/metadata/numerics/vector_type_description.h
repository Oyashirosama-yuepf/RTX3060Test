#ifndef HOLO_METADATA_NUMERICS_VECTOR_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_NUMERICS_VECTOR_TYPE_DESCRIPTION_H_

#include <holo/numerics/vector.h>
#include "holo/metadata/type_description.h"

namespace holo
{
namespace metadata
{
namespace numerics_type
{
static constexpr char VECTOR_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, int32_t S, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::numerics::VectorT<T, S>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::numerics::VectorT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"data", TypeDescriptionResolver<ArrayTag<TypeReferenceTag<1U, numerics_type::VECTOR_SCALAR_TYPE_NAME>, S>,
                                                  ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::numerics::VectorT<T, -1>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::numerics::VectorT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"data", TypeDescriptionResolver<SequenceTag<TypeReferenceTag<1U, numerics_type::VECTOR_SCALAR_TYPE_NAME>>,
                                                  ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
