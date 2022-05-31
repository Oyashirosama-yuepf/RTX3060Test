/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_fusion_json.hpp
 * @brief This header file defines test obstacle fusion for benchmark.
 * @author yuanfeiyang(yuanfeiyang@holomatic.com)
 * @date "2021-04-09"
 */

#ifndef HOLO_PERCEPTION_TEST_OBSTACLE_FUSION_FROM_JSON_HPP_
#define HOLO_PERCEPTION_TEST_OBSTACLE_FUSION_FROM_JSON_HPP_

#include <holo/perception/fusion/test_fusion_from_json.h>

namespace holo
{
namespace perception
{
template <typename _FusionType, typename OdometryType, size_t OutPutSize>
bool_t TestObstacleFusionFromJson<_FusionType, OdometryType, OutPutSize>::Setup(
    std::string const& benchmark_config_json)
{
    Json::Value root;
    if (!parseJson(benchmark_config_json, root))
    {
        return false;
    }
    if (root.isMember("pipeline_config_yaml"))
    {
        setupPipeline(root["pipeline_config_yaml"].asString());
    }
    else
    {
        LOG(ERROR) << "Require key: " << "pipeline_config_yaml" << " @ " << benchmark_config_json;
        return false;
    }
    bool_t success = fusion_frame_manager_.Setup(benchmark_config_json);
    return success;
}

template <typename _FusionType, typename OdometryType, size_t OutPutSize>
void TestObstacleFusionFromJson<_FusionType, OdometryType, OutPutSize>::Run()
{
    auto& fusion_frame_list = fusion_frame_manager_.GetFrameLists();
    for (auto& frame : fusion_frame_list)
    {
        fusionFrame(frame);
    }
    LOG(INFO) << "write to file";
    fusion_frame_manager_.writeObstacleFile();
}

template <typename _FusionType, typename OdometryType, size_t OutPutSize>
bool_t TestObstacleFusionFromJson<_FusionType, OdometryType, OutPutSize>::parseJson(std::string const& jsonfile,
                                                                                    Json::Value&       root)
{
    Json::Reader  reader;
    std::ifstream infile(jsonfile);
    if (infile.bad())
    {
        LOG(WARNING) << "Bad file: " << jsonfile;
        return false;
    }
    if (!reader.parse(infile, root))
    {
        LOG(WARNING) << "Fail to parse json: " << jsonfile;
        return false;
    }
    return true;
}

} // namespace perception
} // namespace holo

#endif
