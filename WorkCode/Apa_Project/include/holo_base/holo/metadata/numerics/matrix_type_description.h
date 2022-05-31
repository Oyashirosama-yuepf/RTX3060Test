#ifndef HOLO_METADATA_NUMERICS_MATRIX_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_NUMERICS_MATRIX_TYPE_DESCRIPTION_H_

#include <holo/numerics/matrix.h>
#include "holo/metadata/type_description.h"

namespace holo
{
namespace metadata
{
namespace numerics_type
{
static constexpr char MATRIX_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, int32_t R, int32_t C, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::numerics::MatrixT<T, R, C>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::numerics::MatrixT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"data", TypeDescriptionResolver<Array2DTag<TypeReferenceTag<1U, numerics_type::MATRIX_SCALAR_TYPE_NAME>, R,
                                                             C, TypeDescriptionArray2D::RowMajorTag>,
                                                  ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::numerics::MatrixT<T, -1, -1>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::numerics::MatrixT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"data",
                  TypeDescriptionResolver<Sequence2DTag<TypeReferenceTag<1U, numerics_type::MATRIX_SCALAR_TYPE_NAME>,
                                                        uint32_t, uint32_t, TypeDescriptionSequence2D::RowMajorTag>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
