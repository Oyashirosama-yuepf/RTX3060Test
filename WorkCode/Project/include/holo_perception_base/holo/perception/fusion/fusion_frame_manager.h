/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fusion_frame_manager.h
 * @brief This header file defines fusion frame manager.
 * @author yuanfeiyang(yuanfeiyang@holomatic.com)
 * @date "2022-04-08"
 */

#ifndef HOLO_PERCEPTION_FUSION_FRAME_MANAGER_H_
#define HOLO_PERCEPTION_FUSION_FRAME_MANAGER_H_

#include <fstream>

#include <holo/perception/fusion/fusion_json_format.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace perception
{
/**
 * @brief frame manager
 *
 */
template<typename _OdometryType, size_t _OutPutSize>
class FusionFrameManager
{
public:
    using Scalar             = float32_t;
    using OdometryType       = holo::common::details::OdometryT<_OdometryType>;
    using LidarMessageType   = holo::obstacle::ObstacleLidarPtrList;
    using RadarMessageType   = holo::obstacle::ObstacleRadarPtrList;
    using UssMessageType     = holo::obstacle::ObstacleUssPtrList;
    using VisionMessageType  = holo::obstacle::ObstacleVisionPtrList;
    using FusedMessageType =
        holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, _OutPutSize>;
    using GeneralMessageType = FusedMessageType;
    using OdometryPtr    = std::shared_ptr<OdometryType>;
    using LidarMessage       = std::shared_ptr<LidarMessageType>;
    using RadarMessage       = std::shared_ptr<RadarMessageType>;
    using UssMessage         = std::shared_ptr<UssMessageType>;
    using GeneralMessage     = std::shared_ptr<GeneralMessageType>;
    using VisionMessage      = std::shared_ptr<VisionMessageType>;
    using OdometryFrameList  = std::vector<OdometryPtr>;
    using LidarFrameList     = std::vector<LidarMessage>;
    using RadarFrameList     = std::vector<RadarMessage>;
    using UssFrameList       = std::vector<UssMessage>;
    using VisionFrameList    = std::vector<VisionMessage>;
    using GeneralFrameList   = std::vector<GeneralMessage>;
    using LidarMessageMap    = std::unordered_map<uint32_t, LidarMessage>;
    using RadarMessageMap    = std::unordered_map<uint32_t, RadarMessage>;
    using UssMessageMap      = std::unordered_map<uint32_t, UssMessage>;
    using VisionMessageMap   = std::unordered_map<uint32_t, VisionMessage>;
    using GeneralMessageMap  = std::unordered_map<uint32_t, GeneralMessage>;

    struct FusionFrame
    {
        OdometryPtr        odometry;
        LidarMessageMap    lidar_msg_map;
        RadarMessageMap    radar_msg_map;
        VisionMessageMap   vision_msg_map;
        UssMessageMap      uss_msg_map;
        GeneralMessageMap  general_msg_map;
        FusedMessageType   output_msg;
        Json::Value        debug_info;
    };
    using FusionFrameList = std::vector<FusionFrame>;

public:
    /**
     * @brief setup
     *
     * @param config_file config file
     * @return success flag
     */
    bool_t Setup(std::string const& config_file);

    /**
     * @brief Get the Frame object
     *
     * @param index frame index
     * @return FusionFrame const& frame
     */
    FusionFrame const& GetFrame(size_t index);

    /**
     * @brief Get the Frame Size object
     *
     * @return size_t total frame num
     */
    size_t GetFrameSize() const
    {
        return fusion_frame_list_.size();
    }

    /**
     * @brief Get the Frame Lists object
     *
     * @return FusionFrameList const&
     */
    FusionFrameList& GetFrameLists();

    /**
     * @brief write obs to json
     *
     */
    void writeObstacleFile();

private:
    /**
     * @brief parse json file
     *
     * @param jsonfile json file
     * @param root json value
     * @return bool_t true if parse success
     */
    bool_t parseJson(std::string const& jsonfile, Json::Value& root);

    /**
     * @brief read odometry json file
     *
     * @param odometry_json odometry json file
     * @return bool_t true if parse success
     */
    bool_t readOdometryJson(std::string const& odometry_json);

    /**
     * @brief read obstacle json file
     *
     * @tparam FrameList frame list type
     * @tparam MessageType message type
     * @tparam ObstacleType obstacle type
     * @param obstacle_json obstacle json file
     * @param frame_list frame list
     * @return bool_t true if read success
     */
    template <class FrameList, class MessageType, class ObstacleType>
    bool_t readObstacleJson(std::string const& obstacle_json, FrameList& frame_list)
    {
        Json::Value root;
        if (!parseJson(obstacle_json, root))
        {
            return false;
        }
        LOG(INFO) << "Reading topic: " << root["topic_name"].asString();
        common::SensorId sensor_id = FusionJsonFormat::GetSensorId(root["sensor_id"]);
        FusionJsonFormat::GetMessageList<FrameList, MessageType, ObstacleType>(root["frame_list"], frame_list,
                                                                               sensor_id);
        return true;
    }

    /**
     * @brief read lidar obstacle json
     *
     * @param obstacle_json obstacle json
     * @return bool_t true if read success
     */
    bool_t readLidarObstacleJson(std::string const& obstacle_json);

    /**
     * @brief read radar obstacle json
     *
     * @param idx radar index
     * @param obstacle_json obstacle json
     * @return bool_t true if read success
     */
    bool_t readRadarObstacleJson(size_t idx, std::string const& obstacle_json);

    /**
     * @brief read uss obstacle json
     *
     * @param idx
     * @param obstacle_json
     * @return bool_t
     */
    bool_t readUssObstacleJson(std::string const& obstacle_json);

    /**
     * @brief read smart camera obstacle json
     *
     * @param obstacle_json obstacle json
     * @return bool_t true if read success
     */
    bool_t readSmartCameraObstacleJson(std::string const& obstacle_json);

    /**
     * @brief read vision obstacle json
     *
     * @param obstacle_json obstacle json
     * @return bool_t true if read success
     */
    bool_t readVisionObstacleJson(std::string const& obstacle_json);

    /**
     * @brief read vision src obstacle json
     *
     * @param obstacle_json
     * @return bool_t
     */
    bool_t readVisionSrcObstacleJson(std::string const& obstacle_json);
    /**
     * @brief read general obstacle json
     *
     * @param obstacle_json
     * @return bool_t
     */
    bool_t readGeneralObstacleJson(std::string const& obstacle_json);

    /**
     * @brief sort frame list in timestamp ascent order
     *
     * @tparam MessageType message type
     * @tparam FrameListType frame list type
     * @param frame_list frame list
     */
    template <class MessageType, class FrameListType>
    void sortFrameList(FrameListType& frame_list)
    {
        std::sort(frame_list.begin(), frame_list.end(),
                  [](MessageType lhs, MessageType rhs) { return lhs->GetTimestamp() < rhs->GetTimestamp(); });
    }

    /**
     * @brief sort all frame list
     *
     */
    void sortFrameLists();

    /**
     * @brief find nearest message
     *
     * @tparam MessageType message type
     * @tparam FrameListType frame list type
     * @param sample_time sample time
     * @param frame_list frame list
     * @param msg message
     * @param index sampled index
     */
    template <class MessageType, class FrameListType>
    void findNearestMessage(float64_t sample_time, FrameListType const& frame_list, MessageType& msg, size_t& index)
    {
        auto dt        = 1.0 / hz_;
        auto best_diff = 1e8;
        for (size_t i = index; i < frame_list.size(); ++i)
        {
            auto diff = frame_list[i]->GetTimestamp().ToSec() - sample_time;
            if (diff > dt)
            {
                continue;
            }
            if (fabsf(diff) < dt && fabsf(diff) < best_diff)
            {
                best_diff = fabsf(diff);
                index     = i;
                msg       = frame_list[i];
                break;
            }
        }
    }

    /**
     * @brief Get the Fusion Frame List object
     *
     */
    void getFusionFrameList();

    /**
     * @brief Get the Timestamp object
     *
     * @param timestamp timestamp
     * @return std::string string
     */
    std::string getTimestamp(common::Timestamp const& timestamp);

    /**
     * @brief Get the Classification object
     *
     * @param classification classification
     * @return std::string string
     */
    std::string getClassification(common::Classification classification);

private:
    size_t                            current_index_ = 0U;
    float32_t                         hz_            = 15.0f;
    uint32_t                          sensor_id_     = 0U;
    std::string                       topic_;
    OdometryFrameList                 odometry_frame_list_;
    LidarFrameList                    lidar_frame_list_;
    std::array<RadarFrameList, 5U>    radar_frame_lists_;
    UssFrameList                      uss_frame_list_;
    VisionFrameList                   smart_camera_frame_list_;
    VisionFrameList                   vision_frame_list_;
    VisionFrameList                   vision_srv_frame_list_;
    GeneralFrameList                  general_frame_list_;
    FusionFrameList                   fusion_frame_list_;
    std::string                       output_json_;
    std::string                       bag_name_;
    bool_t                            use_internal_sensor_id_map_ = true;
    FusionFrame                       empty_frame_;

    std::string const                 output_json_key_          = "fused_obs_json";
    std::string const                 pipeline_config_json_key_ = "pipeline_config_yaml";
    std::string const                 odometry_json_key_        = "odometry_json";
    std::string const                 lidar_json_key_           = "lidar_obs_json";
    std::string const                 smart_camera_json_key_    = "smart_camera_obs_json";
    std::string const                 uss_json_key_             = "uss_obs_json";
    std::string const                 vision_json_key_          = "vision_obs_json";
    std::string const                 vision_srv_json_key_      = "vision_srv_obs_json";
    std::string const                 general_json_key_         = "general_obs_json";
    std::array<std::string, 5U> const radar_json_keys_          = {{
        "front_radar_obs_json",     "corner_left_radar_obs_json", "corner_right_radar_obs_json",
        "rear_left_radar_obs_json", "rear_right_radar_obs_json",
    }};
};

}  // namespace perception
}  // namespace holo

#endif
