#ifndef HOLO_METADATA_GEOMETRY_CURVE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_GEOMETRY_CURVE_TYPE_DESCRIPTION_H_

#include <holo/geometry/curve.h>
#include <holo/geometry/details/curve_traits.h>
#include <holo/metadata/geometry/pose2_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace geometry_type
{
static constexpr char CURVE_BASE_START_TYPE_SIZE_NAME[] = "start_type_size";
static constexpr char CURVE_BASE_END_TYPE_SIZE_NAME[]   = "end_type_size";
static constexpr char     CURVE_POINT_TYPE_NAME[]           = "PointType";
};  // namespace geometry

template <typename Point, size_t SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::geometry::CurveBaseT<Point, SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto enum_type_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::geometry::details::ConditionType");
        (void)enum_type_desc->SetEnumerates({{0U, "DEFAULT"}, {1U, "FIRST_DERIVATIVE"}, {2U, "SECOND_DERIVATIVE"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::geometry::details::CurveBaseT");
        (void)desc->SetTemplates({{"PointType", TypeDescriptionResolver<Point, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"knots",
                  TypeDescriptionResolver<
                      holo::metadata::SequenceTag<TypeReferenceTag<1U, geometry_type::CURVE_POINT_TYPE_NAME>, uint32_t>,
                      ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"start_type", enum_type_desc},
                 {"end_type", enum_type_desc},
                 {"start_type_size", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"end_type_size", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"start_condition",
                  TypeDescriptionResolver<SequenceTag<TypeReferenceTag<1U, geometry_type::CURVE_POINT_TYPE_NAME>,
                                                      ValueReferenceTag<1U, geometry_type::CURVE_BASE_START_TYPE_SIZE_NAME>>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"end_condition",
                  TypeDescriptionResolver<SequenceTag<TypeReferenceTag<1U, geometry_type::CURVE_POINT_TYPE_NAME>,
                                                      ValueReferenceTag<1U, geometry_type::CURVE_BASE_END_TYPE_SIZE_NAME>>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <typename Point, size_t SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::geometry::CurveExplicitBaseT<Point, SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return TypeDescriptionResolver<holo::geometry::CurveBaseT<Point, SIZE>, ALIGN, IS_BIG_ENDIAN>::Get();
    }
};

template <typename Point, size_t SIZE, typename Algorithm, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::geometry::CurveExplicit<Point, SIZE, Algorithm>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return TypeDescriptionResolver<holo::geometry::CurveExplicitBaseT<Point, SIZE>, ALIGN, IS_BIG_ENDIAN>::Get();
    }
};
}  // namespace metadata
}  // namespace holo

#endif
