#ifndef HOLO_METADATA_OBSTACLE_OBSTACLE_BASE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_OBSTACLE_OBSTACLE_BASE_TYPE_DESCRIPTION_H_

#include <holo/metadata/common/classification_type_description.h>
#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/common/sensor_id_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/geometry/point3_type_description.h>
#include <holo/metadata/type_description.h>
#include <holo/obstacle/obstacle_base.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::obstacle::details::CutInCutOut, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::obstacle::details::CutInCutOut");
        (void)desc->SetEnumerates({{0U, "UNKNOWN"},
                             {1U, "HOST_CUT_IN_LEFT"},
                             {2U, "HOST_CUT_IN_RIGHT"},
                             {3U, "HOST_CUT_OUT_LEFT"},
                             {4U, "HOST_CUT_OUT_RIGHT"},
                             {5U, "NEXT_CUT_IN_LEFT"},
                             {6U, "NEXT_CUT_IN_RIGHT"},
                             {7U, "NEXT_CUT_OUT_LEFT"},
                             {8U, "NEXT_CUT_OUT_RIGHT"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::obstacle::details::MotionStatus, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::obstacle::details::MotionStatus");
        (void)desc->SetEnumerates({{0U, "UNKNOWN"},
                             {1U, "MOVING"},
                             {2U, "STATIONARY"},
                             {3U, "ONCOMING"},
                             {4U, "STOPPED"},
                             {5U, "PARKED"},
                             {6U, "CROSSING"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
