/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_link.h
 * @brief define link infos for local map graph.
 * @author chanqiliang(chanqiliang@holomaitc.com)
 * @date 2021-12-07
 */

#ifndef HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_LINK_H_
#define HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_LINK_H_

#include <holo/map/feature/local_map_graph/lmg_common.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace graph
{
/**
 * @addtogroup graph
 *
 * @{
 */

/**
 * @brief Define link
 */
template <typename FeatureIdT, size_t LANE_ID_SIZE = 64U, size_t BOUNDARY_SIZE = 128U, size_t LINK_ID_SIZE = 32U>
class Link : public FeatureBase<FeatureIdT>
{
public:
    using FeatureIdType      = FeatureIdT;
    using LaneIdVectorType   = holo::container::Vector<FeatureIdType, LANE_ID_SIZE>;
    using BoundaryVectorType = holo::container::Vector<FeatureIdType, BOUNDARY_SIZE>;
    using LinkIdVectorType   = holo::container::Vector<FeatureIdType, LINK_ID_SIZE>;

    /**
     * @brief Define link type
     */
    enum class LinkType : uint8_t
    {
        LINK_TYPE_UNKNOWN      = 0U,
        LINK_TYPE_MAIN         = 1U,
        LINK_TYPE_AUXILIARY    = 2U,
        LINK_TYPE_ENTRY_RAMP   = 3U,
        LINK_TYPE_EXIT_RAMP    = 4U,
        LINK_TYPE_RAMP         = 5U,
        LINK_TYPE_JCT          = 6U,
        LINK_TYPE_SERVICE      = 7U,
        LINK_TYPE_INTERSECTION = 8U,
        LINK_TYPE_ROUNDABOUT   = 9U,
        LINK_TYPE_PEDESTRIAN   = 10U,
        LINK_TYPE_PARALLEL     = 11U,
        LINK_TYPE_TOLLBOOTH    = 12U,
        LINK_TYPE_OTHERS       = 255U
    };

    /**
     * @brief Define link attribute
     */
    enum class LinkAttribute : uint8_t
    {
        LINK_ATTRIBUTE_UNKNOWN   = 0U,
        LINK_ATTRIBUTE_TUNNEL    = 1U,
        LINK_ATTRIBUTE_BRIDGE    = 2U,
        LINK_ATTRIBUTE_VIADUCT   = 3U,
        LINK_ATTRIBUTE_TOLLGATE  = 4U,
        LINK_ATTRIBUTE_TOLLENTRY = 5U,
        LINK_ATTRIBUTE_TOLLEXIT  = 6U,
        LINK_ATTRIBUTE_BREAKUP   = 7U,
        LINK_ATTRIBUTE_OTHERS    = 255U
    };

    /**
     * @brief Define link class
     */
    enum class LinkClass : uint8_t
    {
        LINK_CLASS_UNKNOWN    = 0U,
        LINK_CLASS_EXPRESSWAY = 1U,
        LINK_CLASS_FREEWAY    = 2U,
        LINK_CLASS_REGULAR    = 3U,
        LINK_CLASS_OTHERS     = 255U
    };

    Link() : FeatureBase<FeatureIdType>(holo::map::navigator::graph::FeatureType::FEATURE_TYPE_LINK)
    {
    }
    ~Link()           = default;
    Link(Link const&) = default;
    Link(Link&&)      = delete;
    Link& operator=(Link const&) = default;
    Link& operator=(Link&&) = delete;

    /**
     * @brief Set link type.
     *
     * @param link_type link type.
     */
    void SetLinkType(LinkType const link_type) noexcept
    {
        this->link_type_ = link_type;
    }

    /**
     * @brief Get link type.
     *
     * @return Link type.
     */
    LinkType GetLinkType() const noexcept
    {
        return this->link_type_;
    }

    /**
     * @brief Set link attribute.
     *
     * @param link_attribute link_attribute.
     */
    void SetLinkAttribute(LinkAttribute const link_attribute) noexcept
    {
        this->link_attribute_ = link_attribute;
    }

    /**
     * @brief Get link attribute.
     *
     * @return Link attribute.
     */
    LinkAttribute GetLinkAttribute() const noexcept
    {
        return this->link_attribute_;
    }

    /**
     * @brief Set link class.
     *
     * @param link_class link_class.
     */
    void SetLinkClass(LinkClass const link_class) noexcept
    {
        this->link_class_ = link_class;
    }

    /**
     * @brief Get link class.
     *
     * @return Link class.
     */
    LinkClass GetLinkClass() const noexcept
    {
        return this->link_class_;
    }

    /**
     * @brief Set length.
     *
     * @param length Link length, unit:centermeter.
     */
    void SetLength(holo::uint32_t const length) noexcept
    {
        this->length_ = length;
    }

    /**
     * @brief Get length.
     *
     * @return Link length, unit:centermeter.
     */
    holo::uint32_t GetLength() const noexcept
    {
        return this->length_;
    }

    /**
     * @brief Set length.
     *
     * @param length Link length, unit:meter.
     */
    void SetLengthWithMeters(holo::float32_t const length) noexcept
    {
        this->length_ = length * 100;
    }

    /**
     * @brief Get length.
     *
     * @return Link length, unit:meter.
     */
    holo::float32_t GetLengthWithMeters() const noexcept
    {
        return this->length_ * 0.01;
    }

    /**
     * @brief Set intersection id.
     *
     * @param intersection_id intersection id.
     */
    void SetIntersectionId(FeatureIdType const intersection_id) noexcept
    {
        this->intersection_id_ = intersection_id;
    }

    /**
     * @brief Get intersection id.
     *
     * @return Intersection id.
     */
    FeatureIdType GetIntersectionId() const noexcept
    {
        return this->intersection_id_;
    }

    /**
     * @brief Set lane ids.
     *
     * @param lane_ids lane ids.
     */
    void SetLaneIds(LaneIdVectorType const& lane_ids) noexcept
    {
        this->lane_ids_ = lane_ids;
    }

    /**
     * @brief Get lane ids.
     *
     * @return Reference of lane ids.
     */
    LaneIdVectorType const& GetLaneIds() const noexcept
    {
        return this->lane_ids_;
    }

    /**
     * @brief Set left boundary ids.
     *
     * @param left_boundary_ids left boundary ids.
     */
    void SetLeftBoundaryIds(BoundaryVectorType const& left_boundary_ids) noexcept
    {
        this->left_boundary_ids_ = left_boundary_ids;
    }

    /**
     * @brief Get left boundary ids.
     *
     * @return Reference of left boundary ids.
     */
    BoundaryVectorType const& GetLeftBoundaryIds() const noexcept
    {
        return this->left_boundary_ids_;
    }

    /**
     * @brief Set right boundary ids.
     *
     * @param right_boundary_ids right boundary ids.
     */
    void SetRightBoundaryIds(BoundaryVectorType const& right_boundary_ids) noexcept
    {
        this->right_boundary_ids_ = right_boundary_ids;
    }

    /**
     * @brief Get right boundary ids.
     *
     * @return Reference of right boundary ids.
     */
    BoundaryVectorType const& GetRightBoundaryIds() const noexcept
    {
        return this->right_boundary_ids_;
    }

    /**
     * @brief Set preceding link ids.
     *
     * @param peceding_link_ids preceding link ids.
     */
    void SetPrecedingLinkIds(LinkIdVectorType const& preceding_link_ids) noexcept
    {
        this->preceding_link_ids_ = preceding_link_ids;
    }

    /**
     * @brief Get preceding link ids.
     *
     * @return Reference of preceding link ids.
     */
    LinkIdVectorType const& GetPrecedingLinkIds() const noexcept
    {
        return this->preceding_link_ids_;
    }

    /**
     * @brief Set succeeding link ids.
     *
     * @param succeeding_link_ids succeeding link ids.
     */
    void SetSucceedingLinkIds(LinkIdVectorType const& succeeding_link_ids) noexcept
    {
        this->succeeding_link_ids_ = succeeding_link_ids;
    }

    /**
     * @brief Get succeeding link ids.
     *
     * @return Reference of succeeding link ids.
     */
    LinkIdVectorType const& GetSucceedingLinkIds() const noexcept
    {
        return this->succeeding_link_ids_;
    }

private:
    LinkType           link_type_       = LinkType::LINK_TYPE_UNKNOWN;            /// enum link type: main road, ramp.
    LinkAttribute      link_attribute_  = LinkAttribute::LINK_ATTRIBUTE_UNKNOWN;  /// enum link attribute.
    LinkClass          link_class_      = LinkClass::LINK_CLASS_UNKNOWN;          /// enum link class.
    holo::uint32_t     length_          = 0U;                                     /// length, unit: cm.
    FeatureIdType      intersection_id_ = static_cast<FeatureIdType>(0);          /// intersection id.
    LaneIdVectorType   lane_ids_;                                                 /// lane ids.
    BoundaryVectorType left_boundary_ids_;                                        /// left boundary ids.
    BoundaryVectorType right_boundary_ids_;                                       /// right boundary ids.
    LinkIdVectorType   preceding_link_ids_;                                       /// preceding link ids.
    LinkIdVectorType   succeeding_link_ids_;                                      /// succeeding link ids.
};

/**
 * @}
 */
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_LINK_H_