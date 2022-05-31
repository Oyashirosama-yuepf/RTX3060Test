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

#ifndef HOLO_PERCEPTION_COMMON_ROAD_H_
#define HOLO_PERCEPTION_COMMON_ROAD_H_

#include <vector>
#include <array>

#include <holo/common/timestamp.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>

namespace holo
{
namespace perception
{
namespace road
{
template <typename K, typename T>
class KeypointT
{
public:
    using KeyType    = K;
    using ScalarType = T;

    /**
     * @brief Default constructor
     */
    KeypointT() = default;

    /**
     * @brief Constructor
     * @param[in] id
     * @param[in] visibility
     * @param[in] confidence
     */
    KeypointT(KeyType const id, ::holo::bool_t const visibility, ScalarType const confidence);

    /**
     * @brief Default destructor
     */
    virtual ~KeypointT() = 0;

    /**
     * @brief Set id
     * @param[in] id
     */
    void SetId(KeyType const id);

    /**
     * @brief Get id
     * @return id
     */
    KeyType GetId() const;

    /**
     * @brief Set visibility
     * @param[in] visibility
     */
    void SetVisibility(::holo::bool_t const visibility);

    /**
     * @brief Get visibility
     * @return visibility
     */
    ::holo::bool_t GetVisibility() const;

    /**
     * @brief Set confidence
     * @param[in] confidence
     */
    void SetConfidence(ScalarType const confidence);

    /**
     * @brief Get confidence
     * @return confidence
     */
    ScalarType GetConfidence() const;

private:
    KeyType        id_{0};
    ::holo::bool_t visibility_{false};
    ScalarType     confidence_{0};
};

template <typename K, typename T>
class Keypoint2T final : public KeypointT<K, T>
{
public:
    using KeyType    = K;
    using ScalarType = T;
    using BaseType   = KeypointT<KeyType, ScalarType>;
    using Point2Type = ::holo::geometry::Point2T<ScalarType>;

    /**
     * @brief Default constructor
     */
    Keypoint2T() = default;

    /**
     * @brief Constructor
     * @param[in] id
     * @param[in] position
     * @param[in] visibility
     * @param[in] confidence
     */
    Keypoint2T(KeyType const id, Point2Type const& position, ::holo::bool_t const visibility,
               ScalarType const confidence);

    /**
     * @brief Default destructor
     */
    virtual ~Keypoint2T() = default;

    /**
     * @brief Set position
     * @param[in] position
     */
    void SetPosition(Point2Type const& position);

    /**
     * @brief Set position
     * @param[in] position
     */
    void SetPosition(Point2Type&& position);

    /**
     * @brief Get position
     * @return position
     */
    Point2Type const& GetPosition() const;

private:
    Point2Type position_{0, 0};
};

template <typename K, typename T>
class Keypoint3T final : public KeypointT<K, T>
{
public:
    using KeyType    = K;
    using ScalarType = T;
    using BaseType   = KeypointT<KeyType, ScalarType>;
    using Point3Type = ::holo::geometry::Point3T<ScalarType>;

    /**
     * @brief Default constructor
     */
    Keypoint3T() = default;

    /**
     * @brief Constructor
     * @param[in] id
     * @param[in] position
     * @param[in] visibility
     * @param[in] confidence
     */
    Keypoint3T(KeyType const id, Point3Type const& position, ::holo::bool_t const visibility,
               ScalarType const confidence);

    /**
     * @brief Default destructor
     */
    virtual ~Keypoint3T() = default;

    /**
     * @brief Set position
     * @param[in] position
     */
    void SetPosition(Point3Type const& position);

    /**
     * @brief Set position
     * @param[in] position
     */
    void SetPosition(Point3Type&& position);

    /**
     * @brief Get position
     * @return position
     */
    Point3Type const& GetPosition() const;

private:
    Point3Type position_{0, 0, 0};
};

template <typename K, typename T>
using LaneMarking2T = ::std::array<Keypoint2T<K, T>, 4>;

template <typename K, typename T>
using LaneMarking3T = ::std::array<Keypoint3T<K, T>, 4>;

template <typename K, typename T>
using LaneMarkings2T = ::std::vector<LaneMarking2T<K, T>>;

template <typename K, typename T>
using LaneMarkings3T = ::std::vector<LaneMarking3T<K, T>>;

template <typename K, typename T>
using Polyline2T = ::std::vector<Keypoint2T<K, T>>;

template <typename K, typename T>
using Polyline3T = ::std::vector<Keypoint3T<K, T>>;

enum class BoundaryStyle : ::holo::uint16_t
{
    UNKNOWN = 0,
    SOLID   = 1,
    DASHED  = 2
};

enum class BoundaryColor : ::holo::uint16_t
{
    UNKNOWN = 0,
    WHITE   = 1,
    YELLOW  = 2,
    ORANGE  = 3,
    BLUE    = 4
};

template <typename K, typename T>
class LaneBoundaryT
{
public:
    using KeyType    = K;
    using ScalarType = T;
    using StyleType  = BoundaryStyle;
    using ColorType  = BoundaryColor;

    /**
     * @brief Default constructor
     */
    LaneBoundaryT() = default;

    /**
     * @brief Constructor
     * @param[in] id
     * @param[in] style
     * @param[in] color
     */
    LaneBoundaryT(KeyType const id, StyleType const style, ColorType const color);

    /**
     * @brief Destructor
     */
    virtual ~LaneBoundaryT() = 0;

    /**
     * @brief Set if
     * @param[in] id
     */
    void SetId(KeyType const id);

    /**
     * @brief Get id
     * @return id
     */
    KeyType GetId() const;

    /**
     * @brief Set style
     * @param[in] style
     */
    void SetStyle(StyleType const style);

    /**
     * @brief Get style
     * @return style
     */
    StyleType GetStyle() const;

    /**
     * @brief Set color
     * @param[in]  color
     */
    void SetColor(ColorType const Color);

    /**
     * @brief Get color
     * @return color
     */
    ColorType GetColor() const;

private:
    KeyType   id_{0};
    StyleType style_{StyleType::UNKNOWN};
    ColorType color_{ColorType::UNKNOWN};
};

template <typename K, typename T>
class LaneBoundary2T final : public LaneBoundaryT<K, T>
{
public:
    using KeyType           = K;
    using ScalarType        = T;
    using BaseType          = LaneBoundaryT<KeyType, ScalarType>;
    using Polyline2Type     = Polyline2T<KeyType, ScalarType>;
    using LaneMarkings2Type = LaneMarkings2T<KeyType, ScalarType>;

    /**
     * @brief Default constructor
     */
    LaneBoundary2T() = default;

    /**
     * @brief Constructor
     * @param[in] id
     * @param[in] style
     * @param[in] color
     * @param[in] polyline
     * @param[in] lane_markings
     */
    LaneBoundary2T(typename BaseType::KeyType const id, typename BaseType::StyleType const style,
                   typename BaseType::ColorType const color, Polyline2Type const& polyline,
                   LaneMarkings2Type const& lane_markings);

    /**
     * @brief Constructor
     * @param[in] id
     * @param[in] style
     * @param[in] color
     * @param[in] polyline
     * @param[in] lane_markings
     */
    LaneBoundary2T(typename BaseType::KeyType const id, typename BaseType::StyleType const style,
                   typename BaseType::ColorType const color, Polyline2Type&& polyline,
                   LaneMarkings2Type&& lane_markings);

    /**
     * @brief Destructor
     */
    virtual ~LaneBoundary2T() = default;

    /**
     * @brief Set polyline
     * @param[in] polyline
     */
    void SetPolyline(Polyline2Type const& polyline);

    /**
     * @brief Set polyline
     * @param[in] polyline
     */
    void SetPolyline(Polyline2Type&& polyline);

    /**
     * @brief Get polyline
     * @return polyline
     */
    Polyline2Type const& GetPolyline() const noexcept;

    /**
     * @brief Set lane markings
     * @param[in] lane_markings
     */
    void SetLaneMarkings(LaneMarkings2Type const& lane_markings);

    /**
     * @brief Set lane markings
     * @param[in] lane_markings
     */
    void SetLaneMarkings(LaneMarkings2Type&& lane_markings);

    /**
     * @brief Get lane markings
     * @return lane markings
     */
    LaneMarkings2Type const& GetLaneMarkings() const noexcept;

private:
    Polyline2Type     polyline_;
    LaneMarkings2Type lane_markings_;
};

template <typename K, typename T>
class LaneBoundary3T final : public LaneBoundaryT<K, T>
{
public:
    using KeyType           = K;
    using ScalarType        = T;
    using BaseType          = LaneBoundaryT<KeyType, ScalarType>;
    using Polyline3Type     = Polyline3T<KeyType, ScalarType>;
    using LaneMarkings3Type = LaneMarkings3T<KeyType, ScalarType>;

    /**
     * @brief Default constructor
     */
    LaneBoundary3T() = default;

    /**
     * @brief Constructor
     * @param[in] id
     * @param[in] style
     * @param[in] color
     * @param[in] polyline
     * @param[in] lane_markings
     */
    LaneBoundary3T(typename BaseType::KeyType const id, typename BaseType::StyleType const style,
                   typename BaseType::ColorType const color, Polyline3Type const& polyline,
                   LaneMarkings3Type const& lane_markings);

    /**
     * @brief Constructor
     * @param[in] id
     * @param[in] style
     * @param[in] color
     * @param[in] polyline
     * @param[in] lane_markings
     */
    LaneBoundary3T(typename BaseType::KeyType const id, typename BaseType::StyleType const style,
                   typename BaseType::ColorType const color, Polyline3Type&& polyline,
                   LaneMarkings3Type&& lane_markings);

    /**
     * @brief Destructor
     */
    virtual ~LaneBoundary3T() = default;

    /**
     * @brief Set polyline
     * @param[in]  polyline
     */
    void SetPolyline(Polyline3Type const& polyline);

    /**
     * @brief Set polyline
     * @param[in] polyline
     */
    void SetPolyline(Polyline3Type&& polyline);

    /**
     * @brief Get Polyline
     * @param[in] polyline
     */
    Polyline3Type const& GetPolyline() const;

    /**
     * @brief Set lane markings
     * @param[in] lane_markings
     */
    void SetLaneMarkings(LaneMarkings3Type const& lane_markings);

    /**
     * @brief Set lane markings
     * @param[in] lane_markings
     */
    void SetLaneMarkings(LaneMarkings3Type&& lane_markings);

    /**
     * @brief Get lane markings
     * @return lane markings
     */
    LaneMarkings3Type const& GetLaneMarkings() const noexcept;

private:
    Polyline3Type     polyline_;
    LaneMarkings3Type lane_markings_;
};

class Road
{
public:
    using TimestampType = ::holo::common::Timestamp;

    /**
     * @brief Default constructor
     */
    Road() = default;

    /**
     * @brief Constructor
     * @param[in] timestamp
     */
    explicit Road(TimestampType const& timestamp);

    /**
     * @brief Destructor
     */
    virtual ~Road() = 0;

    /**
     * @brief Set timestamp
     * @param[in] timestamp
     */
    void SetTimestamp(TimestampType const& timestamp);

    /**
     * @brief Get timestamp
     * @return timestamp
     */
    TimestampType const& GetTimestamp() const noexcept;

private:
    TimestampType timestamp_;
};

template <typename K, typename T>
class Road2T final : public Road
{
public:
    using KeyType             = K;
    using ScalarType          = T;
    using BaseType            = Road;
    using LaneBoundary2Type   = LaneBoundary2T<KeyType, ScalarType>;
    using LaneBoundaries2Type = ::std::vector<LaneBoundary2Type>;

    /**
     * @brief Default constructor
     */
    Road2T() = default;

    /**
     * @brief Constructor
     * @param[in] timestamp
     * @param[in] lane_boundaries
     */
    Road2T(typename BaseType::TimestampType const& timestamp, LaneBoundaries2Type const& lane_boundaries);

    /**
     * @brief Constructor
     * @param[in] timestamp
     * @param[in] lane_boundaries
     */
    Road2T(typename BaseType::TimestampType const& timestamp, LaneBoundaries2Type&& lane_boundaries);

    /**
     * @brief Destructor
     */
    virtual ~Road2T() = default;

    /**
     * @brief Set lane boundaries
     * @param[in] lane_boundaries
     */
    void SetLaneBoundaries(LaneBoundaries2Type const& lane_boundaries);

    /**
     * @brief Set lane boundaries
     * @param[in] lane_boundaries
     */
    void SetLaneBoundaries(LaneBoundaries2Type&& lane_boundaries);

    /**
     * @brief Get lane boundaries
     * @return lane boundaries
     */
    LaneBoundaries2Type const& GetLaneBoundaries() const noexcept;

private:
    LaneBoundaries2Type lane_boundaries_;
};

template <typename K, typename T>
class Road3T final : public Road
{
public:
    using KeyType             = K;
    using ScalarType          = T;
    using BaseType            = Road;
    using LaneBoundary3Type   = LaneBoundary3T<KeyType, ScalarType>;
    using LaneBoundaries3Type = ::std::vector<LaneBoundary3Type>;

    /**
     * @brief Default constructor
     */
    Road3T() = default;

    /**
     * @brief Constructor
     * @param[in] timestamp
     * @param[in] lane_boundaries
     */
    Road3T(typename BaseType::TimestampType const& timestamp, LaneBoundaries3Type const& lane_boundaries);

    /**
     * @brief Constructor
     * @param[in] timestamp
     * @param[in] lane_boundaries
     */
    Road3T(typename BaseType::TimestampType const& timestamp, LaneBoundaries3Type&& lane_boundaries);

    /**
     * @brief Destructor
     */
    virtual ~Road3T() = default;

    /**
     * @brief Set lane boundaries
     * @param[in] lane_boundaries
     */
    void SetLaneBoundaries(LaneBoundaries3Type const& lane_boundaries);

    /**
     * @brief Set lane boundaries
     * @param[in] lane_boundaries
     */
    void SetLaneBoundaries(LaneBoundaries3Type&& lane_boundaries);

    /**
     * @brief Get lane boundaries
     * @return lane boundaries
     */
    LaneBoundaries3Type const& GetLaneBoundaries() const noexcept;

private:
    LaneBoundaries3Type lane_boundaries_;
};
}  // namespace road
}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_COMMON_ROAD_H_
