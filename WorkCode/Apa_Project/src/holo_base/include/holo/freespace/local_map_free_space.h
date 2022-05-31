/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file local_map_free_space.h
 * @brief This header file defines LocalMapFreeSpace.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-27
 */

#ifndef HOLO_FREESPACE_LOCAL_MAP_FREE_SPACE_H_
#define HOLO_FREESPACE_LOCAL_MAP_FREE_SPACE_H_

#include <memory>
#include <vector>

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/geometry/point2.h>

using Coordinate = holo::common::Coordinate;

namespace holo
{
/**
 * @addtogroup freespace
 *
 * @{
 */

/**
 * @brief Local map free space
 *
 * @tparam T only support float32_t and float64_t
 */
template <typename T>
class LocalMapFreeSpace
{
public:
    using Contour   = std::vector<holo::geometry::Point2T<T> >;
    using Contours  = std::vector<Contour>;
    using Timestamp = holo::common::Timestamp;

    /**
     * @brief Default constructor
     */
    LocalMapFreeSpace() noexcept;

    /**
     * @brief Construct a new Local Map Free Space object with params
     *
     * @param timestamp timestamp of free space
     * @param coord coord coordinate of free space
     * @param exterior_contour exterior point of free space
     * @param interior_contours interior points of free space
     */
    LocalMapFreeSpace(const Timestamp& timestamp, const Coordinate coord, const Contour& exterior_contour,
                      const Contours& interior_contours) noexcept;

    /**
     * @brief Copy constructor
     *
     * @param other other local map free space
     */
    LocalMapFreeSpace(const LocalMapFreeSpace& other) noexcept;

    /**
     * @brief Move constructor
     *
     * @param other other local map free space
     */
    LocalMapFreeSpace(LocalMapFreeSpace&& other) noexcept;

    /**
     * @brief Copy assignment
     *
     * @param other other local map free space
     * @return new local map free space
     */
    LocalMapFreeSpace& operator=(const LocalMapFreeSpace& other) noexcept;

    /**
     * @brief Move assignment
     *
     * @param other other local map free space
     * @return LocalMapFreeSpace&
     */
    LocalMapFreeSpace& operator=(LocalMapFreeSpace&& other) noexcept;

    /**
     * @brief Get timestamp of local map free space
     *
     * @return timestamp
     */
    const Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set timestamp of local map free space
     *
     * @param timestmap timestamp
     */
    void SetTimestamp(const Timestamp& timestamp) noexcept
    {
        this->timestamp_ = timestamp;
    }

    /**
     * @brief Get the coordinate of local map free space
     *
     * @return coordinate
     */
    Coordinate GetCoordinate() const noexcept
    {
        return coordinate_;
    }

    /**
     * @brief Set the coordinate of local map free space
     *
     * @param coordinate coordinate
     */
    void SetCoordinate(const Coordinate coordinate) noexcept
    {
        this->coordinate_ = coordinate;
    }

    /**
     * @brief Get exterior contour points of local map free space
     *
     * @return exterior contour points
     */
    const Contour& GetExteriorContour() const noexcept
    {
        return exterior_contour_;
    }

    /**
     * @brief Set exterior contour points of local map free space
     *
     * @param exterior_contour exterior contour
     */
    void SetExteriorContour(const Contour& exterior_contour) noexcept
    {
        this->exterior_contour_ = exterior_contour;
    }

    /**
     * @brief Set exterior contour points of local map free space in efficient way
     *
     * @param exterior_contour exterior contour
     */
    void SetExteriorContour(Contour&& exterior_contour) noexcept
    {
        std::swap(this->exterior_contour_, exterior_contour);
    }

    /**
     * @brief Get interior contours of local map free space
     *
     * @return interior contours of local map free space
     */
    const Contours& GetInteriorContours() const noexcept
    {
        return interior_contours_;
    }

    /**
     * @brief Set interior contours of local map free space
     *
     * @param interior_contours interior contours of local map free space
     */
    void SetInteriorContours(const Contours& interior_contours) noexcept
    {
        this->interior_contours_ = interior_contours;
    }

    /**
     * @brief Set interior contours of local map free space
     *
     * @param interior_contours interior contours of local map free space
     */
    void SetInteriorContours(Contours&& interior_contours) noexcept
    {
        std::swap(this->interior_contours_, interior_contours);
    }

private:
    Timestamp  timestamp_;
    Coordinate coordinate_;
    Contour    exterior_contour_;
    Contours   interior_contours_;
};

// Handy typedefs
using LocalMapFreeSpacef = LocalMapFreeSpace<float32_t>;
using LocalMapFreeSpaced = LocalMapFreeSpace<float64_t>;

/**
 * @}
 */

}  // namespace holo

#endif  // !HOLO_FREESPACE_LOCAL_MAP_FREE_SPACE_H_
