#ifndef HOLO_METADATA_NUMERICS_UTILITY_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_NUMERICS_UTILITY_TYPE_DESCRIPTION_H_

#include <holo/numerics/utility.h>
#include "holo/metadata/type_description.h"

namespace holo
{
namespace metadata
{
namespace numerics_type
{
static constexpr char UTILITY_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t Degree, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::numerics::Polynomial<T, Degree>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::numerics::Polynomial");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"coefficients", TypeDescriptionResolver<
                                      ArrayTag<TypeReferenceTag<1U, numerics_type::UTILITY_SCALAR_TYPE_NAME>, Degree + 1>,
                                      ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
