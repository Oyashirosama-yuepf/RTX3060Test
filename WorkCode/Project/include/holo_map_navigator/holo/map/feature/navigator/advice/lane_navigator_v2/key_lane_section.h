/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file target region.h
 * @brief Target region in new lane path
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-10-08"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_TARGET_REGION_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_TARGET_REGION_H_

#include <queue>
#include <sstream>
#include <vector>

#include <holo/core/types.h>

#include <holo/map/common/common_define.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
namespace scene
{
#define ENUM_SECTION_FORM                                                                                              \
    X(UNDEFINED)                                                                                                       \
    X(CORRESPONDING)                                                                                                   \
    X(DIRECT)                                                                                                          \
    X(PARALLEL)

/**
 * @brief Target region, which describe target region which should be changed to
 *
 *  @details The target region and region model info is ONE to ONE, the expression is as followed:
 *
 *
 *          | LI1 |   LI2 |   LI3  |   LI4   |  LI5   |  LI6  |  LI7   |  LI8   | <-- lane path 1
 *                              |-------region model info--------|
 *
 *          | LI5 |   LI6 |   LI7  |   LI8   |  LI9   |  LI10 |  LI11  |  LI12  | <-- lane path 2
 *                              |-----   target region ----------|
 *
 *          Expression: LT represents Lane Item, LT1 is Lane Item 1
 *
 *          As you can see, the change procedure would be executed from 'region model info' in lane
 *          path 1 to 'target region' in lane path2. So we also consider target region as the
 *          object region for changing lane.
 *          One more word, we could create region model info from target region. And we alse could
 *          create target region from region model info. Seen as followed:
 *
 *          | LI1 |   LI2 |   LI3  |   LI4   |  LI5   |  LI6  |  LI7   |  LI8   | <-- lane path 1
 *               |-----   target region ----------|-------region model info--------|
 *
 *          we could deduce target region from region model info with model type.
 */
class KeyLaneSection
{
public:
    /**
     * @brief Section form
     *
     * @details Section form such as corresponding, direct and
     *          parallel lane segments
     */
    enum class SectionForm : holo::uint8_t
    {
#define X(type) type,
        ENUM_SECTION_FORM
#undef X
    };

public:
    /**
     * @brief Format to JOSN string
     *
     * @param target Target region with respect to scene
     * @return std::string The formated string
     */
    static std::string FormatToString(KeyLaneSection const& target);

    /**
     * @brief Format to JOSN string
     *
     * @param targets
     * @return std::string
     */
    static std::string FormatSequenceToString(std::vector<KeyLaneSection> const& targets);

    KeyLaneSection()                    = default;
    ~KeyLaneSection()                   = default;
    KeyLaneSection(KeyLaneSection const&) = default;
    KeyLaneSection& operator=(KeyLaneSection const&) = default;
    KeyLaneSection(KeyLaneSection&&)                 = default;
    KeyLaneSection& operator=(KeyLaneSection&&) = default;

    VecLaneIdType const& GetLaneIds() const;
    VecLaneIdType&       GetLaneIds();

    VecLaneBoundaryIdType const& GetLeftBoundaryIds() const;
    VecLaneBoundaryIdType&       GetLeftBoundaryIds();

    VecLaneBoundaryIdType const& GetRightBoundaryIds() const;
    VecLaneBoundaryIdType&       GetRightBoundaryIds();

    void            SetBeginLaneOffset(Distance const offset);
    Distance        GetBeginLaneOffset() const;

    void            SetFinishLaneOffset(Distance const offset);
    Distance        GetFinishLaneOffset() const;

    void        SetSectionForm(SectionForm const& form);
    SectionForm GetSectionForm() const;

    void            SetTargetLength(holo::float64_t const len);
    holo::float64_t GetTargetLength() const;

    holo::uint32_t GetPriority() const;

private:
    /// Ids of lanes covered by target region
    VecIdType lane_ids_;
    /// Ids of left boundarys covered by target region,
    /// we could judge neighbor relationship of different
    /// lanes and sections of different lane paths
    VecIdType left_boundary_ids_;
    /// Ids of right boundarys covered by target region
    VecIdType right_boundary_ids_;
    /// Begin offset of first lane
    Distance begin_lane_offset_ = 0.0f;
    /// Finish offset of last lane
    Distance finish_lane_offset_ = 0.0f;
    /// Model type
    SectionForm section_form_;
    /// Calculate length target region
    holo::float64_t region_length_ = 0.0f;
};

char const* const SectionFormNames[4] = {
#define X(name) #name,
    ENUM_SECTION_FORM
#undef X
};
}  // namespace scene
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_LANE_NAVIGATOR_TARGET_REGION2_H_ */