/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_fusion_json.h
 * @brief This header file defines test obstacle fusion for benchmark.
 * @author yuanfeiyang(yuanfeiyang@holomatic.com)
 * @date "2021-04-09"
 */
#include <vector>
#include <iomanip>

#include <holo/core/types.h>
#include <holo/log/hololog.h>
#include <holo/perception/fusion/fusion_frame_manager.h>

#ifndef HOLO_PERCEPTION_TEST_OBSTACLE_FUSION_FROM_JSON_H_
#define HOLO_PERCEPTION_TEST_OBSTACLE_FUSION_FROM_JSON_H_

namespace holo
{
namespace perception
{
/**
 * @brief test obstacle fusion from json
 *
 * @tparam _FusionType
 */
template <typename _FusionType, typename OdometryType, size_t OutPutSize>
class TestObstacleFusionFromJson
{
public:
    using Timestamp        = common::Timestamp;
    using FusionFrame      = typename FusionFrameManager<OdometryType, OutPutSize>::FusionFrame;
    using FusionFrameList  = typename FusionFrameManager<OdometryType, OutPutSize>::FusionFrameList;

public:
    /**
     * @brief setup
     *
     * @param benchmark_config_json json
     * @return bool_t true if setup success
     */
    bool_t Setup(std::string const& benchmark_config_json);

    /**
     * @brief run test
     *
     */
    void Run();

private:
    /**
     * @brief SetupPipeline
     *
     * @param pipeline_config_yaml
     */
    virtual void setupPipeline(std::string pipeline_config_yaml) = 0;

    /**
     * @brief fusion frame
     *
     * @param frame
     */
    virtual void fusionFrame(FusionFrame& frame) = 0;

    /**
     * @brief parse json file
     *
     * @param jsonfile json file
     * @param root json value
     * @return bool_t true if parse success
     */
    bool_t parseJson(std::string const& jsonfile, Json::Value& root);

protected:
    _FusionType        obstacle_fusion_pipeline_;

private:
    FusionFrameManager<OdometryType, OutPutSize> fusion_frame_manager_;
    std::string const  pipeline_config_json_key_ = "pipeline_config_yaml";
};
}  // namespace perception
}  // namespace holo
#endif
