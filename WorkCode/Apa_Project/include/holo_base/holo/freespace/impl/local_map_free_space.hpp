/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file local_map_free_space.hpp
 * @brief This hpp file implements LocalMapFreeSpace.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-27
 */

#ifndef HOLO_FREESPACE_LOCAL_MAP_FREE_SPACE_HPP_
#define HOLO_FREESPACE_LOCAL_MAP_FREE_SPACE_HPP_

#include <holo/freespace/local_map_free_space.h>

namespace holo
{
template <typename T>
LocalMapFreeSpace<T>::LocalMapFreeSpace() noexcept : timestamp_{}, coordinate_(Coordinate::UNKNOWN)
{
}

template <typename T>
LocalMapFreeSpace<T>::LocalMapFreeSpace(const Timestamp& timestamp, const Coordinate coord, const Contour& exterior_contour,
                                        const Contours& interior_contours) noexcept
  : timestamp_(timestamp), coordinate_(coord), exterior_contour_(exterior_contour), interior_contours_(interior_contours)
{
}

template <typename T>
LocalMapFreeSpace<T>::LocalMapFreeSpace(const LocalMapFreeSpace<T>& other) noexcept
  : timestamp_(other.timestamp_)
  , coordinate_(other.coordinate_)
  , exterior_contour_(other.exterior_contour_)
  , interior_contours_(other.interior_contours_)
{
}

template <typename T>
LocalMapFreeSpace<T>::LocalMapFreeSpace(LocalMapFreeSpace<T>&& other) noexcept
  : timestamp_(other.timestamp_)
  , coordinate_(other.coordinate_)
  , exterior_contour_(std::move(other.exterior_contour_))
  , interior_contours_(std::move(other.interior_contours_))
{
}

template <typename T>
LocalMapFreeSpace<T>& LocalMapFreeSpace<T>::operator=(const LocalMapFreeSpace<T>& other) noexcept
{
    if (this != &other)
    {
        this->timestamp_         = other.timestamp_;
        this->coordinate_        = other.coordinate_;
        this->exterior_contour_  = other.exterior_contour_;
        this->interior_contours_ = other.interior_contours_;
    }

    return *this;
}

template <typename T>
LocalMapFreeSpace<T>& LocalMapFreeSpace<T>::operator=(LocalMapFreeSpace<T>&& other) noexcept
{
    // avoid self = std::move(self)
    if (this != &other)
    {
        this->timestamp_         = other.timestamp_;
        this->coordinate_        = other.coordinate_;
        this->exterior_contour_  = std::move(other.exterior_contour_);
        this->interior_contours_ = std::move(other.interior_contours_);
    }

    return *this;
}
}  // namespace holo

#endif  // !HOLO_FREESPACE_LOCAL_MAP_FREE_SPACE_HPP_
