/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file local_map_free_space_v2.h
 * @brief From map in world frame, version 2
 * @author lisong(lisong@holomatic.com)
 * @date 2019-10-31
 */

#ifndef HOLO_FREESPACE_LOCAL_MAP_FREE_SPACE_V2_H_
#define HOLO_FREESPACE_LOCAL_MAP_FREE_SPACE_V2_H_

#include <memory>
#include <vector>

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/geometry/point3.h>

/**
 * @addtogroup holo
 *
 * @{
 */
namespace holo 
{
/**
 * @addtogroup freespace
 *
 * @{
 */

/**
 * @brief Class LocalMapFreeSpaceV2
 */
class LocalMapFreeSpaceV2 
{
public:
    using Coordinate = holo::common::Coordinate;
    using Timestamp  = holo::common::Timestamp;

    /**
     * @brief Smart pointer
     */
    using Ptr = std::shared_ptr<LocalMapFreeSpaceV2>;
    using ConstPtr = std::shared_ptr<const LocalMapFreeSpaceV2>;

    typedef std::vector<holo::geometry::Point3d> LinearRing;
    typedef std::vector<LinearRing> LinearRings;

    /**
     * @brief Enum calss to identify segements type
     */
    enum class SegmentType : holo::uint8_t 
    {
        UNKNOWN = 0,         ///< Unknown type
        TRIVIAL = 1,         ///< Map free space's front and back boundary
        CURB = 2,            ///< Curb
        TRAFFIC_BARRIER = 3, ///< Traffic barrier
        ROAD_BOUNDARY = 4,   ///< Road boundary
        FILL_AREA = 5        ///< Fill area
    };

    /**
     * @brief Describe a segment from free space's exterior ring or interior ring 
     * @details Start_index and end_index is the start point and
     *          end point of one segment from linear ring.
     *          note that one segment'end point is same as it's next segment'start
     *          point, which means the index of those two point are the same.
     */
    struct SegmentInfo 
    {
        /// Segment start point index in freespace
        /// Polygon's exterior ring or interior ring
        std::size_t start_index = 0; 

        /// Segment end point index in freespace
        /// Polygon's exterior ring or interior ring
        std::size_t end_index = 0;

        /// Segment's type, default is UNKNOWN
        SegmentType segment_type = SegmentType::UNKNOWN; 

        /**
         * @brief Default constructor
         */
        SegmentInfo() noexcept = default;

        /**
         * @brief Constructor with parameters
         * @param[in] start_point_index Segment start point index in polygon's exterior ring or interior ring of localmapfreespacev2
         * @param[in] end_point_index Segment end point index in 's polygon's exterior ring or interior ring of localmapfreespacev2
         * @param[in] type Segment' type
         */
        SegmentInfo(std::size_t const start_point_index, 
                    std::size_t const end_point_index,
                    SegmentType const type) noexcept
                  : start_index(start_point_index), 
                    end_index(end_point_index),
                    segment_type(type) 
        {}

        /**
         * @brief Copy constructor
         * @param[in] other Other segmentinfo
         */
        SegmentInfo(SegmentInfo const& other) noexcept
                  : start_index(other.start_index), 
                    end_index(other.end_index),
                    segment_type(other.segment_type) 
        {}

        /**
         * @brief Copy assign operator
         * @param[in] other Other segmentinfo
         * @return segmentinfo&
         */
        SegmentInfo& operator=(SegmentInfo const& other) noexcept 
        {
            if(this != &other) 
            {
                this->start_index = other.start_index;
                this->end_index = other.end_index;
                this->segment_type = other.segment_type;
            }
            return *this;
        }

        /**
         * @brief Equal to operator
         * @param[in] other Other segmentinfo
         * @return True If the two are equal, 
         *         false if the two are not equal
         */
        bool operator==(SegmentInfo const& other) noexcept
        {
            if(this != &other)
            {
                return (start_index == other.start_index) &&
                       (end_index == other.end_index) &&
                       (segment_type == other.segment_type);
            }
            return true;
        }

        /**
         * @brief Not equal to operator
         * @param[in] other Other segmentinfo
         * @return True If the two are not equal, 
         *         false if the two are equal
         */
        bool operator!=(SegmentInfo const& other) noexcept
        {
            return !(*this == other);
        }
    };

    /// Store segments info of polygon's exterior ring or interior ring
    typedef std::vector<SegmentInfo> RingInfo;

    /**
     * @brief Describe a polygon from map free sapce
     * @details One map free space is made of multiple polygons
     *          one map free space polygon is made of multiple linear rings,
     *          each linear ring is made of multiple segments.
     *          the frist element of polygon_info is exterior_ring's segments info,
     *          the rest is those interior_rings's segments info.
     */
    struct FreeSpacePolygon 
    {
        LinearRing exterior_ring;           ///< Free space polygon's exterior ring
        LinearRings interior_rings;         ///< Free space polygon's interioer rings
        std::vector<RingInfo> polygon_info; ///< Free space polygon's info

        /**
         * @brief Default constructor
         */
        FreeSpacePolygon() = default;

        /**
         * @brief Constructor with parameters
         * @param[in] poly_exterior_ring Polygon's exterior ring
         * @param[in] poly_interior_rings Polygon's interior ring vector
         * @param[in] poly_info Polygon's info
         */
        FreeSpacePolygon(LinearRing const& poly_exterior_ring,
                         LinearRings const& poly_interior_rings,
                         std::vector<RingInfo> const& poly_info) noexcept
                       : exterior_ring(poly_exterior_ring), 
                         interior_rings(poly_interior_rings),
                         polygon_info(poly_info) 
        {}

        /**
         * @brief Copy constructor
         * @param[in] other Other freespacepolygon
         */
        FreeSpacePolygon(FreeSpacePolygon const& other) noexcept
                       : exterior_ring(other.exterior_ring),
                         interior_rings(other.interior_rings),
                         polygon_info(other.polygon_info) 
        {}

        /**
         * @brief Move constructor
         * @param[in] other Other freespacepolygon
         */
        FreeSpacePolygon(FreeSpacePolygon&& other) noexcept
                       : exterior_ring(std::move(other.exterior_ring)),
                         interior_rings(std::move(other.interior_rings)),
                         polygon_info(std::move(other.polygon_info)) 
        {}

        /**
         * @brief Copy assign operator
         * @param[in] other Other freespacepolygon
         * @return freespacepolygon&
         */
        FreeSpacePolygon& operator=(FreeSpacePolygon const& other) noexcept 
        {
            if(this != &other) 
            {
                this->exterior_ring = other.exterior_ring;
                this->interior_rings = other.interior_rings;
                this->polygon_info = other.polygon_info;
            }
            return *this;
        }

        /**
         * @brief Move assign operator
         * @param[in] other Other freespacepolygon
         * @return freespacepolygon&
         */
        FreeSpacePolygon& operator=(FreeSpacePolygon&& other) noexcept 
        {
            if(this != &other) 
            {
                exterior_ring.swap(other.exterior_ring);
                interior_rings.swap(other.interior_rings);
                polygon_info.swap(other.polygon_info);
                other.exterior_ring.clear();
                other.interior_rings.clear();
                other.polygon_info.clear();
            }
            return *this;
        }

        /**
         * @brief Equal to operator
         * @param[in] other Other freespacepolygon
         * @return True If the two are equal, 
         *         false if the two are not equal
         */
        bool operator==(FreeSpacePolygon const& other) noexcept
        {
            if(this != &other)
            {
                return (exterior_ring == other.exterior_ring) &&
                       (interior_rings == other.interior_rings) &&
                       (polygon_info == other.polygon_info);
            }
            return true;
        }

        /**
         * @brief Not equal to operator
         * @param[in] other Other freespacepolygon
         * @return True If the two are not equal, 
         *         false if the two are equal
         */
        bool operator!=(FreeSpacePolygon const& other) noexcept
        {
            return !(*this == other);
        }
    };

    /// Map freespace can have more than one polygon
    typedef std::vector<FreeSpacePolygon> MapFreeSpacePolygons;

    /**
     * @brief Default constructor
     */
    LocalMapFreeSpaceV2() = default;

    /**
     * @brief Constructor with parameters
     * @param[in] timestamp Timestamp of freespace
     * @param[in] coordinate Coordinate of freespace
     * @param[in] free_space_polygons Free space polygon vector of freespace
     */
    LocalMapFreeSpaceV2(Timestamp const& timestamp,
                        Coordinate const& coordinate,
                        MapFreeSpacePolygons const& free_space_polygons) noexcept
                      : timestamp_(timestamp), 
                        coordinate_(coordinate),
                        free_space_polygons_(free_space_polygons) 
    {}

    /**
     * @brief Copy constructor
     * @param[in] other Other free space
     */
    LocalMapFreeSpaceV2(LocalMapFreeSpaceV2 const& other) noexcept
                      : timestamp_(other.timestamp_), 
                        coordinate_(other.coordinate_),
                        free_space_polygons_(other.free_space_polygons_) 
    {}

    /**
     * @brief Move constructor
     * @param[in] other Other free space
     */
    LocalMapFreeSpaceV2(LocalMapFreeSpaceV2&& other) noexcept 
                      : timestamp_(other.timestamp_), 
                        coordinate_(other.coordinate_),
                        free_space_polygons_(std::move(other.free_space_polygons_))
    {}

    /**
     * @brief Copy assign operator
     * @param[in] other Other free space
     * @return localmapfreespacev2&
     */
    LocalMapFreeSpaceV2& operator=(LocalMapFreeSpaceV2 const& other) noexcept 
    {
        if(this != &other) 
        {
            this->timestamp_ = other.timestamp_;
            this->coordinate_ = other.coordinate_;
            this->free_space_polygons_ = other.free_space_polygons_;
        }
        return *this;
    }

    /**
     * @brief Move assign operator
     * @param[in] other Other free space
     * @return localmapfreespacev2&
     */
    LocalMapFreeSpaceV2& operator=(LocalMapFreeSpaceV2&& other) noexcept 
    {
        if(this != &other) 
        {
            this->timestamp_ = other.timestamp_;
            this->coordinate_ = other.coordinate_;            
            free_space_polygons_.swap(other.free_space_polygons_);
            other.free_space_polygons_.clear();
        }
        return *this;
    }

    /**
     * @brief Equal to operator
     * @param[in] other Other LocalMapFreeSpaceV2
     * @return True If the two are equal, 
     *         false if the two are not equal
     */
    bool operator==(LocalMapFreeSpaceV2 const& other) noexcept
    {
        if(this != &other)
        {
            return (timestamp_ == other.timestamp_) &&
                   (coordinate_ == other.coordinate_) &&
                   (free_space_polygons_ == other.free_space_polygons_);
        }
        return true;
    }

    /**
     * @brief Not equal to operator
     * @param[in] other Other LocalMapFreeSpaceV2
     * @return True If the two are not equal, 
     *         false if the two are equal
     */
    bool operator!=(LocalMapFreeSpaceV2 const& other) noexcept
    {
        return !(*this == other);
    }

    /**
     * @brief Get timestamp of free space, const version
     * @return timestamp const&
     */
    Timestamp const& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Get timestamp of free space, non-const version
     * @return timestamp&
     */
    Timestamp& GetTimestamp() noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set timestamp of free space
     * @param[in] timestamp Timestamp
     * @return nothing
     */
    void SetTimestamp(Timestamp const& timestamp) noexcept
    {
        this->timestamp_ = timestamp;
    }

    /**
     * @brief Get the coordinate of free space, const version
     * @return coord const&
     */
    Coordinate const& GetCoordinate() const noexcept
    {
        return coordinate_;
    }

    /**
     * @brief Get the coordinate of free space, non-const version
     * @return coord&
     */
    Coordinate& GetCoordinate() noexcept
    {
        return coordinate_;
    }

    /**
     * @brief Set the coordinate of free space
     * @param[in] coord coordinate
     * @return nothing
     */
    void SetCoordinate(Coordinate const& coordinate) noexcept
    {
        this->coordinate_ = coordinate;
    }

    /**
     * @brief Get free space polygon vector, const version
     * @return mapfreespacepolygons const&
     */
    MapFreeSpacePolygons const& GetFreeSpacePolygons() const noexcept 
    {
        return free_space_polygons_;
    }

    /**
     * @brief Get free space polygon vector non-const version
     * @return mapfreespacepolygons&
     */
    MapFreeSpacePolygons& GetFreeSpacePolygons() noexcept 
    {
        return free_space_polygons_;
    }

    /**
     * @brief Set free space polygon vector
     * @param[in] free_space_polygons Given free space polygon vector
     * @return Nothing
     */
    void SetFreeSpacePolygons(MapFreeSpacePolygons const& free_space_polygons) noexcept 
    {
        free_space_polygons_ = free_space_polygons;
    }

    /**
     * @brief Set free space polygon vector, move version
     * @param[in] free_space_polygons Given free space polygon vector
     * @return Nothing
     */
    void SetFreeSpacePolygons(MapFreeSpacePolygons&& free_space_polygons) noexcept 
    {
        free_space_polygons_.swap(free_space_polygons);
        free_space_polygons.clear();
    }

private:
    Timestamp timestamp_;                      ///< Timestamp
    Coordinate coordinate_;                    ///< Coordinate id : UNKNOWN
    MapFreeSpacePolygons free_space_polygons_; ///< Free space polygon vector
}; ///< end for class LocalMapFreeSpaceV2

/**
 * @brief Global equal operator for LocalMapFreeSpaceV2::SegmentInfo
 * @param[in] lhs Given left operand
 * @param[in] rhs Given right operand
 * @return True if the two are equal, 
 *         false if the two are not equal
 */
bool operator==(LocalMapFreeSpaceV2::SegmentInfo const& lhs, LocalMapFreeSpaceV2::SegmentInfo const& rhs)
{
    if(&lhs != &rhs)
    {
        return (lhs.start_index == rhs.start_index) &&
               (lhs.end_index == rhs.end_index) &&
               (lhs.segment_type == rhs.segment_type);
    }
    return true;
}

/**
 * @brief Global not equal operator LocalMapFreeSpaceV2::SegmentInfo
 * @param[in] lhs Given left operand
 * @param[in] rhs Given right operand
 * @return True if the two are not equal, 
 *         false if the two are equal
 */
bool operator!=(LocalMapFreeSpaceV2::SegmentInfo const& lhs, LocalMapFreeSpaceV2::SegmentInfo const& rhs)
{
    return !(lhs == rhs);
}

/**
 * @brief Global equal operator for LocalMapFreeSpaceV2::FreeSpacePolygon
 * @param[in] lhs Given left operand
 * @param[in] rhs Given right operand
 * @return True if the two are equal, 
 *         false if the two are not equal
 */
bool operator==(LocalMapFreeSpaceV2::FreeSpacePolygon const& lhs, LocalMapFreeSpaceV2::FreeSpacePolygon const& rhs)
{
    if(&lhs != &rhs)
    {
        return (lhs.exterior_ring == rhs.exterior_ring) &&
               (lhs.interior_rings == rhs.interior_rings) &&
               (lhs.polygon_info == rhs.polygon_info);
    }
    return true;
}

/**
 * @brief Global not equal operator for LocalMapFreeSpaceV2::FreeSpacePolygon
 * @param[in] lhs Given left operand
 * @param[in] rhs Given right operand
 * @return True if the two are not equal, 
 *         false if the two are equal
 */
bool operator!=(LocalMapFreeSpaceV2::FreeSpacePolygon const& lhs, LocalMapFreeSpaceV2::FreeSpacePolygon const& rhs)
{
    return !(lhs == rhs);
}

/**
 * @brief Global equal operator for LocalMapFreeSpaceV2
 * @param[in] lhs Given left operand
 * @param[in] rhs Given right operand
 * @return True if the two are equal, 
 *         false if the two are not equal
 */
bool operator==(LocalMapFreeSpaceV2 const& lhs, LocalMapFreeSpaceV2 const& rhs)
{
    if(&lhs != &rhs)
    {
        return (lhs.GetTimestamp() == rhs.GetTimestamp()) &&
               (lhs.GetCoordinate() == rhs.GetCoordinate()) &&
               (lhs.GetFreeSpacePolygons() == rhs.GetFreeSpacePolygons());
    }
    return true;
}

/**
 * @brief Global not equal operator for LocalMapFreeSpaceV2
 * @param[in] lhs Given left operand
 * @param[in] rhs Given right operand
 * @return True if the two are not equal, 
 *         false if the two are equal
 */
bool operator!=(LocalMapFreeSpaceV2 const& lhs, LocalMapFreeSpaceV2 const& rhs)
{
    return !(lhs == rhs);
}

/**
 * @}
 */
}  ///< end for namespace holo
/**
 * @}
 */

#endif ///< HOLO_FREESPACE_LOCAL_MAP_FREE_SPACE_V2_H_
