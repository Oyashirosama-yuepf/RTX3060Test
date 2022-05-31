/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_attributes_extrator.h
 * @brief Extract attributes from HD map.
 * @author wanghaiyang(wanghaiyang@holomaitc.com)
 * @date "2020-07-16"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ATTRIBUTE_MAP_ATTRIBUTES_EXTRACTOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ATTRIBUTE_MAP_ATTRIBUTES_EXTRACTOR_H_

#include <holo/map/common/common_define.h>
#include <holo/map/common/match_info.h>
#include <holo/map/feature/map_attributor/road_attributes/road_attribute.h>
#include <holo/map/feature/navigator/router/route_info.h>
#include <holo/map/service/client/engine/helper.h>
#include <holo/map/service/client/matcher/matcher.h>
namespace holo
{
namespace map
{
namespace navigator
{
namespace attributes
{
/**
 * @addtogroup attributes
 * @{
 *
 */

/**
 * @brief An extractor for map attributes.
 *
 * @detail Reference to: https://holomatic.feishu.cn/docs/doccn9ynSedyL6uy7qUbUo5HHrb.
 */
class MapAttributesExtractor
{
public:
    /**
     * @brief Constructor.
     *
     * @return Nothing.
     */
    MapAttributesExtractor() = default;

    /**
     * @brief Destructor.
     *
     * @return Nothing.
     */
    ~MapAttributesExtractor() = default;

    /**
     * @brief Copy constructor.
     */
    MapAttributesExtractor(MapAttributesExtractor const&) = delete;

    /**
     * @brief Move constructor.
     */
    MapAttributesExtractor(MapAttributesExtractor&&) = delete;

    /**
     * @brief Copy assignment.
     */
    MapAttributesExtractor& operator=(MapAttributesExtractor const&) = delete;

    /**
     * @brief Move assignment.
     */
    MapAttributesExtractor& operator=(MapAttributesExtractor&&) = delete;

    /**
     * @brief Init a map attributes extractor.
     *
     * @param[in] ret A handle of map database engine.
     * @param[in] segs Configration for the extractor, it will extract road attributes
     *                 based on that segment info.
     * @return true: Initialize successfully;
     *         false: An error occurs in this function.
     */
    bool Init(RetrieverSPType const ret,
              std::vector<holo::float32_t> const&                                    segs);

    /**
     * @brief Extract road attributes by current matching result and current routing path.
     *
     * @param[in] matching_info Matching result from matcher::MapMatcher.
     * @param[in] routing_info Routing path from RouteInfo2.
     * @param[out] attributes Road attributes distribute with configuration initialized in Init().
     * @return true: No error even though the output is empty.
     *         false: An error occurs in this function.
     */
    bool ExtractRoadAttributes(MapMatchInfo const& matching_info, RouteInfo2 const& routing_info,
                               RoadAttribute::VectorType& attributes);

    /**
     * @brief Extract road attributes by road path.
     * @param[in] front_path Routing path with road ids in front of current position,
     *                       the first item of the path will contains the projection of current position.
     *                       Note: the road path items should be connected.
     * @param[in] current_position Current car postion with HD localization result.
     * @param[out] attributes Road attributes distribute with configuration initialized in Init().
     * @return true: No error even though the output is empty.
     *         false: An error occurs in this function.
     */
    bool ExtractRoadAttributesByRoadIds(
        holo::map::service::client::engine::helper::raw::RawFeatureIdVectorTypeV0 const& front_path,
        holo::map::service::client::engine::helper::raw::RawGeoPointTypeV0 const&        current_position,
        RoadAttribute::VectorType&                                                       attributes);

    /**
     * @brief Extract road attributes by lane group path.
     * @param[in] front_path Routing path with lane group ids in front of current position,
     *                       the first item of the path will contains the projection of current position.
     *                       Note: the lane group path items should be connected.
     * @param[in] current_position Current car postion with HD localization result..
     * @param[out] attributes Road attributes distribute with configuration initialized in Init().
     * @return true: No error even though the output is empty.
     *         false: An error occurs in this function.
     */
    bool ExtractRoadAttributesByLaneGroupIds(
        holo::map::service::client::engine::helper::raw::RawFeatureIdVectorTypeV0 const& front_path,
        holo::map::service::client::engine::helper::raw::RawGeoPointTypeV0 const&        current_position,
        RoadAttribute::VectorType&                                                       attributes);

private:
    /// Indicate this extractor whether or not initialized.
    bool initialized_ = false;
    /// The handle of database engine.
    RetrieverSPType ret_ = nullptr;
    /// Configrations for road road attributes.
    std::vector<holo::float32_t> road_attribute_segments_;
};  ///< End of class MapAttributesExtractor.

/// Redefine shared pointer for MapAttributesExtractor.
using MapAttributesExtractorSPtrType = std::shared_ptr<MapAttributesExtractor>;
/// Redefine unique pointer for MapAttributesExtractor.
using MapAttributesExtractorUPtrType = std::unique_ptr<MapAttributesExtractor>;

/**
 * @}
 *
 */

}  // namespace attributes
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ATTRIBUTE_MAP_ATTRIBUTES_EXTRACTOR_H_ */
