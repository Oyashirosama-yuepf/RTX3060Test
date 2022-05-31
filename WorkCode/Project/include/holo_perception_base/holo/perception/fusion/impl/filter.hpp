/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file filter.hpp
 * @brief The implementation of template class FilterT
 * @author sunzhenqiang(sunzhenqiang@holomaitc.com)
 * @date "2019-12-24"
 */

#ifndef HOLO_PERCEPTION_FUSION_FILTER_HPP_
#define HOLO_PERCEPTION_FUSION_FILTER_HPP_

#include <holo/perception/fusion/filter.h>

namespace holo
{
namespace perception
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t FilterT<T>::FilterByRoi(const Track& track, const ConvexPolygon& roi)
{
    auto        p2 = (*track.GetTrack().begin())->GetPosition().GetPointXY();
    return roi.Contains(p2);
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_FUSION_FILTER_HPP_
