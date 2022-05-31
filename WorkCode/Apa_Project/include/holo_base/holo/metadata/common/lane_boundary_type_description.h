#ifndef HOLO_METADATA_COMMON_LANE_BOUNDARY_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_LANE_BOUNDARY_TYPE_DESCRIPTION_H_

#include <holo/common/lane_boundary2.h>
#include <holo/metadata/common/alarm_type_description.h>
#include <holo/metadata/common/boundary_feature_type_description.h>
#include <holo/metadata/common/lane_boundary_type_description.h>
#include <holo/metadata/numerics/utility_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace common_type
{
static constexpr char LANE_BOUNDARY_SCALAR_TYPE_NAME[] = "ScalarType";
}

template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::LaneBoundary<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::LaneBoundaryT");
        (void)desc->SetTemplates({}).SetMembers(
            {{"style", TypeDescriptionResolver<holo::common::BoundaryStyle, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"color", TypeDescriptionResolver<holo::common::BoundaryColor, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"width", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"confidence", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <typename T, size_t Degree, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::LaneBoundary<holo::numerics::Polynomial<T, Degree>>, ALIGN, IS_BIG_ENDIAN>
{
    using CurveType = holo::numerics::Polynomial<T, Degree>;
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::LaneBoundaryPolynomialT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"curve",
                  TypeDescriptionResolver<
                      holo::numerics::Polynomial<TypeReferenceTag<1U, common_type::LANE_BOUNDARY_SCALAR_TYPE_NAME>, Degree>,
                      ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"start", TypeDescriptionResolver<TypeReferenceTag<0U, common_type::LANE_BOUNDARY_SCALAR_TYPE_NAME>, ALIGN,
                                                   IS_BIG_ENDIAN>::Get()},
                 {"end", TypeDescriptionResolver<TypeReferenceTag<0U, common_type::LANE_BOUNDARY_SCALAR_TYPE_NAME>, ALIGN,
                                                 IS_BIG_ENDIAN>::Get()},
                 {"style", TypeDescriptionResolver<holo::common::BoundaryStyle, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"color", TypeDescriptionResolver<holo::common::BoundaryColor, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"width", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"confidence", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
