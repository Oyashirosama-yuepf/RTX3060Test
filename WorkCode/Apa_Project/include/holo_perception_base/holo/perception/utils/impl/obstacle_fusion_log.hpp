/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_fusion_log.hpp
 * @brief This header file defines .
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-08-26"
 */

#ifndef HOLO_PERCEPTION_UTILS_OBSTACLE_FUSION_LOG_HPP_
#define HOLO_PERCEPTION_UTILS_OBSTACLE_FUSION_LOG_HPP_

#include <holo/perception/utils/obstacle_fusion_log.h>

namespace holo
{
namespace perception
{
template <typename ObstacleList>
void ObstacleFusionLog::WriteObstacleList(ObstacleList const& obs_list)
{
    auto iter = ss_map_.find("input");
    if (ss_map_.end() != iter)
    {
        *(iter->second) << (uint32_t)obs_list.GetSensorId() << " " << obs_list.GetTimestamp().ToNsec() << "\n";
    }
}

template <typename ClusterMap>
void ObstacleFusionLog::WriteClusterResult(ClusterMap const& cluster_map)
{
    auto iter = ss_map_.find("cluster");
    if (ss_map_.end() != iter)
    {
        for (auto pc : cluster_map)
        {
            auto cluster = pc.second;
            *(iter->second) << "C" << cluster->id << " ";
            for (auto pt : cluster->track_map)
            {
                auto track = pt.second;
                *(iter->second) << "T" << track->GetObstacleId() << " ";
            }
            for (auto pm : cluster->measurement_map)
            {
                auto measure = pm.second;
                *(iter->second) << "M" << (uint32_t)measure->GetSensorId() << "_" << measure->GetObstacleId() << " ";
            }
            *(iter->second) << "\n";
        }
    }
}

}  // namespace perception
}  // namespace holo

#endif
