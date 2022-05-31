/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road.h
 * @brief This header file defines road type.
 * @author Yuchao Hu (huyuchao@holomatic.com)
 * @date "2022-03-07"
 */

#ifndef HOLO_PERCEPTION_COMMON_IMPL_ROAD_HPP_
#define HOLO_PERCEPTION_COMMON_IMPL_ROAD_HPP_

#include <holo/perception/common/road.h>

#include <vector>

namespace holo
{
namespace perception
{
namespace road
{
// KeypointT

template <typename K, typename T>
KeypointT<K, T>::KeypointT(KeyType const id, ::holo::bool_t const visibility, ScalarType const confidence)
  : id_(id), visibility_(visibility), confidence_(confidence)
{
}

template <typename K, typename T>
KeypointT<K, T>::~KeypointT() = default;

template <typename K, typename T>
void KeypointT<K, T>::SetId(KeyType const id)
{
    id_ = id;
}

template <typename K, typename T>
typename KeypointT<K, T>::KeyType KeypointT<K, T>::GetId() const
{
    return id_;
}

template <typename K, typename T>
void KeypointT<K, T>::SetVisibility(::holo::bool_t const visibility)
{
    visibility_ = visibility;
}

template <typename K, typename T>
::holo::bool_t KeypointT<K, T>::GetVisibility() const
{
    return visibility_;
}

template <typename K, typename T>
void KeypointT<K, T>::SetConfidence(ScalarType const confidence)
{
    confidence_ = confidence;
}

template <typename K, typename T>
typename KeypointT<K, T>::ScalarType KeypointT<K, T>::GetConfidence() const
{
    return confidence_;
}

// Keypoint2T

template <typename K, typename T>
Keypoint2T<K, T>::Keypoint2T(KeyType const id, Point2Type const& position, ::holo::bool_t const visibility,
                             ScalarType const confidence)
  : BaseType(id, visibility, confidence), position_(position)
{
}

template <typename K, typename T>
void Keypoint2T<K, T>::SetPosition(Point2Type const& position)
{
    position_ = position;
}

template <typename K, typename T>
void Keypoint2T<K, T>::SetPosition(Point2Type&& position)
{
    position_ = position;
}

template <typename K, typename T>
typename Keypoint2T<K, T>::Point2Type const& Keypoint2T<K, T>::GetPosition() const
{
    return position_;
}

// Keypoint3T

template <typename K, typename T>
Keypoint3T<K, T>::Keypoint3T(KeyType const id, Point3Type const& position, ::holo::bool_t const visibility,
                             ScalarType const confidence)
  : BaseType(id, visibility, confidence), position_(position)
{
}

template <typename K, typename T>
void Keypoint3T<K, T>::SetPosition(Point3Type const& position)
{
    position_ = position;
}

template <typename K, typename T>
void Keypoint3T<K, T>::SetPosition(Point3Type&& position)
{
    position_ = position;
}

template <typename K, typename T>
typename Keypoint3T<K, T>::Point3Type const& Keypoint3T<K, T>::GetPosition() const
{
    return position_;
}

// LaneBoundaryT

template <typename K, typename T>
LaneBoundaryT<K, T>::LaneBoundaryT(KeyType const id, StyleType const style, ColorType const color)
  : id_(id), style_(style), color_(color)
{
}

template <typename K, typename T>
LaneBoundaryT<K, T>::~LaneBoundaryT() = default;

template <typename K, typename T>
void LaneBoundaryT<K, T>::SetId(KeyType const id)
{
    id_ = id;
}

template <typename K, typename T>
typename LaneBoundaryT<K, T>::KeyType LaneBoundaryT<K, T>::GetId() const
{
    return id_;
}

template <typename K, typename T>
void LaneBoundaryT<K, T>::SetStyle(StyleType const style)
{
    style_ = style;
}

template <typename K, typename T>
typename LaneBoundaryT<K, T>::StyleType LaneBoundaryT<K, T>::GetStyle() const
{
    return style_;
}

template <typename K, typename T>
void LaneBoundaryT<K, T>::SetColor(ColorType const color)
{
    color_ = color;
}

template <typename K, typename T>
typename LaneBoundaryT<K, T>::ColorType LaneBoundaryT<K, T>::GetColor() const
{
    return color_;
}

// LaneBoundary2T

template <typename K, typename T>
LaneBoundary2T<K, T>::LaneBoundary2T(typename BaseType::KeyType const id, typename BaseType::StyleType const style,
                                     typename BaseType::ColorType const color, Polyline2Type const& polyline,
                                     LaneMarkings2Type const& lane_markings)
  : BaseType(id, style, color), polyline_(polyline), lane_markings_(lane_markings)
{
}

template <typename K, typename T>
LaneBoundary2T<K, T>::LaneBoundary2T(typename BaseType::KeyType const id, typename BaseType::StyleType const style,
                                     typename BaseType::ColorType const color, Polyline2Type&& polyline,
                                     LaneMarkings2Type&& lane_markings)
  : BaseType(id, style, color), polyline_(polyline), lane_markings_(lane_markings)
{
}

template <typename K, typename T>
void LaneBoundary2T<K, T>::SetPolyline(Polyline2Type const& polyline)
{
    polyline_ = polyline;
}

template <typename K, typename T>
void LaneBoundary2T<K, T>::SetPolyline(Polyline2Type&& polyline)
{
    polyline_.swap(polyline);
}

template <typename K, typename T>
typename LaneBoundary2T<K, T>::Polyline2Type const& LaneBoundary2T<K, T>::GetPolyline() const noexcept
{
    return polyline_;
}

template <typename K, typename T>
void LaneBoundary2T<K, T>::SetLaneMarkings(LaneMarkings2Type const& lane_markings)
{
    lane_markings_ = lane_markings;
}

template <typename K, typename T>
void LaneBoundary2T<K, T>::SetLaneMarkings(LaneMarkings2Type&& lane_markings)
{
    lane_markings_.swap(lane_markings);
}

template <typename K, typename T>
typename LaneBoundary2T<K, T>::LaneMarkings2Type const& LaneBoundary2T<K, T>::GetLaneMarkings() const noexcept
{
    return lane_markings_;
}

// LaneBoundary3T

template <typename K, typename T>
LaneBoundary3T<K, T>::LaneBoundary3T(typename BaseType::KeyType const id, typename BaseType::StyleType const style,
                                     typename BaseType::ColorType const color, Polyline3Type const& polyline,
                                     LaneMarkings3Type const& lane_markings)
  : BaseType(id, style, color), polyline_(polyline), lane_markings_(lane_markings)
{
}

template <typename K, typename T>
LaneBoundary3T<K, T>::LaneBoundary3T(typename BaseType::KeyType const id, typename BaseType::StyleType const style,
                                     typename BaseType::ColorType const color, Polyline3Type&& polyline,
                                     LaneMarkings3Type&& lane_markings)
  : BaseType(id, style, color), polyline_(polyline), lane_markings_(lane_markings)
{
}

template <typename K, typename T>
void LaneBoundary3T<K, T>::SetPolyline(Polyline3Type const& polyline)
{
    polyline_ = polyline;
}

template <typename K, typename T>
void LaneBoundary3T<K, T>::SetPolyline(Polyline3Type&& polyline)
{
    polyline_.swap(polyline);
}

template <typename K, typename T>
typename LaneBoundary3T<K, T>::Polyline3Type const& LaneBoundary3T<K, T>::GetPolyline() const
{
    return polyline_;
}

template <typename K, typename T>
void LaneBoundary3T<K, T>::SetLaneMarkings(LaneMarkings3Type const& lane_markings)
{
    lane_markings_ = lane_markings;
}

template <typename K, typename T>
void LaneBoundary3T<K, T>::SetLaneMarkings(LaneMarkings3Type&& lane_markings)
{
    lane_markings_.swap(lane_markings);
}

template <typename K, typename T>
typename LaneBoundary3T<K, T>::LaneMarkings3Type const& LaneBoundary3T<K, T>::GetLaneMarkings() const noexcept
{
    return lane_markings_;
}

// Road

Road::Road(TimestampType const& timestamp) : timestamp_(timestamp)
{
}

Road::~Road() = default;

void Road::SetTimestamp(TimestampType const& timestamp)
{
    timestamp_ = timestamp;
}

Road::TimestampType const& Road::GetTimestamp() const noexcept
{
    return timestamp_;
}

// Road2T

template <typename K, typename T>
Road2T<K, T>::Road2T(typename BaseType::TimestampType const& timestamp, LaneBoundaries2Type const& lane_boundaries)
  : BaseType(timestamp), lane_boundaries_(lane_boundaries)
{
}

template <typename K, typename T>
Road2T<K, T>::Road2T(typename BaseType::TimestampType const& timestamp, LaneBoundaries2Type&& lane_boundaries)
  : BaseType(timestamp), lane_boundaries_(lane_boundaries)
{
}

template <typename K, typename T>
void Road2T<K, T>::SetLaneBoundaries(LaneBoundaries2Type const& lane_boundaries)
{
    lane_boundaries_ = lane_boundaries;
}

template <typename K, typename T>
void Road2T<K, T>::SetLaneBoundaries(LaneBoundaries2Type&& lane_boundaries)
{
    lane_boundaries_.swap(lane_boundaries);
}

template <typename K, typename T>
::std::vector<typename Road2T<K, T>::LaneBoundary2Type> const& Road2T<K, T>::GetLaneBoundaries() const noexcept
{
    return lane_boundaries_;
}

// Road3T

template <typename K, typename T>
Road3T<K, T>::Road3T(typename BaseType::TimestampType const& timestamp, LaneBoundaries3Type const& lane_boundaries)
  : BaseType(timestamp), lane_boundaries_(lane_boundaries)
{
}

template <typename K, typename T>
Road3T<K, T>::Road3T(typename BaseType::TimestampType const& timestamp, LaneBoundaries3Type&& lane_boundaries)
  : BaseType(timestamp), lane_boundaries_(lane_boundaries)
{
}

template <typename K, typename T>
void Road3T<K, T>::SetLaneBoundaries(LaneBoundaries3Type const& lane_boundaries)
{
    lane_boundaries_ = lane_boundaries;
}

template <typename K, typename T>
void Road3T<K, T>::SetLaneBoundaries(LaneBoundaries3Type&& lane_boundaries)
{
    lane_boundaries_.swap(lane_boundaries);
}

template <typename K, typename T>
::std::vector<typename Road3T<K, T>::LaneBoundary3Type> const& Road3T<K, T>::GetLaneBoundaries() const noexcept
{
    return lane_boundaries_;
}
}  // namespace road
}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_COMMON_IMPL_ROAD_HPP_
