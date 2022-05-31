/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_fusion_frame_manager.hpp
 * @brief This header file defines obstacle fusion frame manager.
 * @author yuanfeiyang(yuanfeiyang@holomatic.com)
 * @date "2022-04-08"
 */

#ifndef HOLO_PERCEPTION_FUSION_FRAME_MANAGER_HPP_
#define HOLO_PERCEPTION_FUSION_FRAME_MANAGER_HPP_

#include <holo/perception/fusion/fusion_frame_manager.h>

namespace holo
{
namespace perception
{
template<typename _OdometryType, size_t _OutPutSize>
bool_t FusionFrameManager<_OdometryType, _OutPutSize>::Setup(std::string const& config_file)
{
    try
    {
        Json::Value root;
        if (parseJson(config_file, root))
        {
            if (root.isMember("use_internal_sensor_id_map"))
            {
                use_internal_sensor_id_map_ = root["use_internal_sensor_id_map"].asBool();
            }
            if (root.isMember("hz"))
            {
                hz_ = root["hz"].asFloat();
            }
            if (root.isMember("sensor_id"))
            {
                sensor_id_ = root["sensor_id"].asUInt();
            }
            if (root.isMember("topic"))
            {
                topic_ = root["topic"].asString();
            }
            // read output json
            if (root.isMember(output_json_key_))
            {
                output_json_ = root[output_json_key_].asString();
            }
            else
            {
                LOG(ERROR) << "Require key: " << output_json_key_ << " @ " << config_file;
                return false;
            }
            // read odometry
            if (root.isMember(odometry_json_key_))
            {
                if (!readOdometryJson(root[odometry_json_key_].asString()))
                {
                    LOG(ERROR) << "Read odometry failed";
                    return false;
                }
            }
            else
            {
                LOG(ERROR) << "Require key: " << odometry_json_key_ << " @ " << config_file;
                return false;
            }
            //pilot
            // lidar
            if (root.isMember(lidar_json_key_))
            {
                LOG(INFO) << "Found key: " << lidar_json_key_;
                readLidarObstacleJson(root[lidar_json_key_].asString());
            }
            // radar
            for (size_t i = 0U; i < radar_json_keys_.size(); ++i)
            {
                auto key = radar_json_keys_[i];
                if (root.isMember(key))
                {
                    LOG(INFO) << "Found key: " << key;
                    readRadarObstacleJson(i, root[key].asString());
                }
            }
            //smart camera
            if (root.isMember(smart_camera_json_key_))
            {
                LOG(INFO) << "Found key: " << smart_camera_json_key_;
                readSmartCameraObstacleJson(root[smart_camera_json_key_].asString());
            }

            //vision
            if (root.isMember(vision_json_key_))
            {
                LOG(INFO) << "Found key: " << vision_json_key_;
                readVisionObstacleJson(root[vision_json_key_].asString());
            }

            // parking
            // uss
            if (root.isMember(uss_json_key_))
            {
                LOG(INFO) << "Found key: " << uss_json_key_;
                readUssObstacleJson(root[uss_json_key_].asString());
            }
            //src vision
            if (root.isMember(vision_srv_json_key_))
            {
                LOG(INFO) << "Found key: " << vision_srv_json_key_;
                readVisionSrcObstacleJson(root[vision_srv_json_key_].asString());
            }

            getFusionFrameList();
            LOG(INFO) << "OK";
        }
        else
        {
            holo::yaml::Node node       = holo::yaml::LoadFile(config_file);
            use_internal_sensor_id_map_ = node["use_internal_sensor_id_map"].as<bool_t>();
            hz_                         = node["hz"].as<float32_t>();
            sensor_id_                  = node["sensor_id"].as<int32_t>();
            topic_                      = node["fused_topic"].as<std::string>();
            readOdometryJson(node["odometry_json"].as<std::string>());
            readLidarObstacleJson(node["lidar_json"].as<std::string>());
            readRadarObstacleJson(0U, node["front_radar_json"].as<std::string>());
            readRadarObstacleJson(1U, node["corner_left_radar_json"].as<std::string>());
            readRadarObstacleJson(2U, node["corner_right_radar_json"].as<std::string>());
            readRadarObstacleJson(3U, node["rear_left_radar_json"].as<std::string>());
            readRadarObstacleJson(4U, node["rear_right_radar_json"].as<std::string>());
            readSmartCameraObstacleJson(node["smart_camera_json"].as<std::string>());
            readVisionObstacleJson(node["vision_json"].as<std::string>());
            getFusionFrameList();
            LOG(INFO) << " OK";
        }

    }
    catch (std::exception& e)
    {
        LOG(ERROR) << e.what() << " @ " << config_file;
        throw;
    }
    return true;
}

template<typename _OdometryType, size_t _OutPutSize>
typename FusionFrameManager<_OdometryType, _OutPutSize>::FusionFrame const& FusionFrameManager<_OdometryType, _OutPutSize>::GetFrame(size_t index)
{
    if (index < fusion_frame_list_.size())
    {
        return fusion_frame_list_[index];
    }
    return empty_frame_;
}

template<typename _OdometryType, size_t _OutPutSize>
typename FusionFrameManager<_OdometryType, _OutPutSize>::FusionFrameList& FusionFrameManager<_OdometryType, _OutPutSize>::GetFrameLists()
{
    return fusion_frame_list_;
}

template<typename _OdometryType, size_t _OutPutSize>
bool_t FusionFrameManager<_OdometryType, _OutPutSize>::parseJson(std::string const& jsonfile, Json::Value& root)
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

template<typename _OdometryType, size_t _OutPutSize>
bool_t FusionFrameManager<_OdometryType, _OutPutSize>::readOdometryJson(std::string const& odometry_json)
{
    Json::Value root;
    if (!parseJson(odometry_json, root))
    {
        return false;
    }
    bag_name_ = root["bag_name"].asString();
    LOG(INFO) << "Reading bag: " << bag_name_;
    LOG(INFO) << "Reading odometry topic: " << root["topic_name"].asString();
    FusionJsonFormat::GetOdometryList<OdometryFrameList, OdometryType, _OdometryType>(root["frame_list"],
                                                                                      odometry_frame_list_);
    return true;
}

template<typename _OdometryType, size_t _OutPutSize>
bool_t FusionFrameManager<_OdometryType, _OutPutSize>::readLidarObstacleJson(std::string const& obstacle_json)
{
    return readObstacleJson<LidarFrameList, LidarMessageType, obstacle::ObstacleLidarT<Scalar>>(obstacle_json,
                                                                                                lidar_frame_list_);
}

template<typename _OdometryType, size_t _OutPutSize>
bool_t FusionFrameManager<_OdometryType, _OutPutSize>::readRadarObstacleJson(size_t idx, std::string const& obstacle_json)
{
    return readObstacleJson<RadarFrameList, RadarMessageType, obstacle::ObstacleRadarT<Scalar>>(
        obstacle_json, radar_frame_lists_[idx]);
}

template<typename _OdometryType, size_t _OutPutSize>
bool_t FusionFrameManager<_OdometryType, _OutPutSize>::readUssObstacleJson(std::string const& obstacle_json)
{
    return readObstacleJson<UssFrameList, UssMessageType, obstacle::ObstacleUssT<Scalar>>(
        obstacle_json, uss_frame_list_);
}

template<typename _OdometryType, size_t _OutPutSize>
bool_t FusionFrameManager<_OdometryType, _OutPutSize>::readSmartCameraObstacleJson(std::string const& obstacle_json)
{
    return readObstacleJson<VisionFrameList, VisionMessageType, obstacle::ObstacleVisionT<Scalar>>(
        obstacle_json, smart_camera_frame_list_);
}

template<typename _OdometryType, size_t _OutPutSize>
bool_t FusionFrameManager<_OdometryType, _OutPutSize>::readVisionObstacleJson(std::string const& obstacle_json)
{
    return readObstacleJson<VisionFrameList, VisionMessageType, obstacle::ObstacleVisionT<Scalar>>(obstacle_json,
                                                                                                   vision_frame_list_);
}

template<typename _OdometryType, size_t _OutPutSize>
bool_t FusionFrameManager<_OdometryType, _OutPutSize>::readVisionSrcObstacleJson(std::string const& obstacle_json)
{
    return readObstacleJson<VisionFrameList, VisionMessageType, obstacle::ObstacleVisionT<Scalar>>(obstacle_json,
                                                                                                   vision_srv_frame_list_);
}

template<typename _OdometryType, size_t _OutPutSize>
bool_t FusionFrameManager<_OdometryType, _OutPutSize>::readGeneralObstacleJson(std::string const& obstacle_json)
{
    return readObstacleJson<GeneralFrameList, GeneralMessageType, obstacle::ObstacleGeneralT<Scalar>>(obstacle_json,
                                                                                                   general_frame_list_);
}

template<typename _OdometryType, size_t _OutPutSize>
void FusionFrameManager<_OdometryType, _OutPutSize>::sortFrameLists()
{
    sortFrameList<OdometryPtr, OdometryFrameList>(odometry_frame_list_);
    sortFrameList<LidarMessage, LidarFrameList>(lidar_frame_list_);
    for (size_t i = 0U; i < radar_frame_lists_.size(); ++i)
    {
        sortFrameList<RadarMessage, RadarFrameList>(radar_frame_lists_[i]);
    }
    sortFrameList<VisionMessage, VisionFrameList>(smart_camera_frame_list_);
    sortFrameList<VisionMessage, VisionFrameList>(vision_frame_list_);
}

template<typename _OdometryType, size_t _OutPutSize>
void FusionFrameManager<_OdometryType, _OutPutSize>::getFusionFrameList()
{
    if (odometry_frame_list_.size() > 0U)
    {
        sortFrameLists();
        auto start_time = odometry_frame_list_.front()->GetTimestamp().ToSec();
        auto end_time   = odometry_frame_list_.back()->GetTimestamp().ToSec();
        auto dt         = 1.0 / hz_;
        fusion_frame_list_.reserve(static_cast<size_t>((dt + end_time - start_time) / dt));
        // prepare index
        size_t                 index_odometry = 0U;
        size_t                 index_lidar    = 0U;
        std::array<size_t, 5U> index_radar;
        index_radar.fill(0U);
        size_t index_smart_camera = 0U;
        size_t index_vision       = 0U;
        size_t index_vision_srv   = 0U;       
        size_t index_uss          = 0U;
        for (auto sample_time = start_time; sample_time < end_time + dt * 0.5; sample_time += dt)
        {
            FusionFrame fusion_frame;
            //odometry
            findNearestMessage<OdometryPtr, OdometryFrameList>(sample_time, odometry_frame_list_, fusion_frame.odometry,
                                                               index_odometry);

            //lidar
            LidarMessage lidar_msg = nullptr;
            findNearestMessage<LidarMessage, LidarFrameList>(sample_time, lidar_frame_list_, lidar_msg, index_lidar);
            fusion_frame.lidar_msg_map[0U] = lidar_msg;

            //radar
            for (size_t i = 0U; i < radar_frame_lists_.size(); ++i)
            {
                RadarMessage radar_msg = nullptr;
                findNearestMessage<RadarMessage, RadarFrameList>(sample_time, radar_frame_lists_[i], radar_msg,
                                                                 index_radar[i]);
                fusion_frame.radar_msg_map[i] = radar_msg;
            }
            //vision
            VisionMessage smart_camera_msg = nullptr;
            VisionMessage vision_msg       = nullptr;
            VisionMessage vision_srv_msg    = nullptr;
            findNearestMessage<VisionMessage, VisionFrameList>(sample_time, smart_camera_frame_list_, smart_camera_msg,
                                                               index_smart_camera);
            findNearestMessage<VisionMessage, VisionFrameList>(sample_time, vision_frame_list_, vision_msg,
                                                               index_vision);
            findNearestMessage<VisionMessage, VisionFrameList>(sample_time, vision_srv_frame_list_, vision_srv_msg,
                                                               index_vision_srv);
            fusion_frame.vision_msg_map[0U] = smart_camera_msg;
            fusion_frame.vision_msg_map[1U] = vision_msg;
            fusion_frame.vision_msg_map[2U] = vision_srv_msg;

            //uss
            UssMessage uss_msg = nullptr;
            findNearestMessage<UssMessage, UssFrameList>(sample_time, uss_frame_list_, uss_msg,
                                                               index_uss);
            fusion_frame.uss_msg_map[0U] = uss_msg;

            fusion_frame_list_.push_back(fusion_frame);
        }
    }
}

template<typename _OdometryType, size_t _OutPutSize>
std::string FusionFrameManager<_OdometryType, _OutPutSize>::getTimestamp(common::Timestamp const& timestamp)
{
    std::stringstream ss;
    ss << timestamp.GetSec() << "." << std::setfill('0') << std::setw(9) << timestamp.GetNsec();
    return ss.str();
}

template<typename _OdometryType, size_t _OutPutSize>
std::string FusionFrameManager<_OdometryType, _OutPutSize>::getClassification(common::Classification classification)
{
    if (classification.GetSubType() == Classification::SubType::CAR)
    {
        return "small_car";
    }
    else if (classification.GetSubType() == Classification::SubType::TRUCK)
    {
        return "big_car";
    }
    else if (classification.GetSubType() == Classification::SubType::TRAFFIC_SIGN_BOARD)
    {
        return "sign";
    }
    else if (classification.GetSubType() == Classification::SubType::PEDESTRIAN)
    {
        return "ped";
    }
    else if (classification.GetSubType() == Classification::SubType::TRAFFIC_CONE)
    {
        return "con";
    }
    else if (classification.GetSubType() == Classification::SubType::BICYCLE)
    {
        return "bik";
    }
    else if (classification.GetSubType() == Classification::SubType::TRICYCLE)
    {
        return "tri";
    }
    return "unknown";
}

template<typename _OdometryType, size_t _OutPutSize>
void FusionFrameManager<_OdometryType, _OutPutSize>::writeObstacleFile()
{

    Json::Value root;
    root["bag_name"]   = bag_name_;
    root["topic_name"] = topic_;
    root["hz"]         = hz_;
    root["sensor_id"]  = sensor_id_;
    // get frame list
    Json::Value json_frame_list;
    for (auto const& frame : fusion_frame_list_)
    {
        Json::Value json_frame;
        json_frame["timestamp"] = getTimestamp(frame.output_msg.GetTimestamp());
        Json::Value json_obstacle_list;
        for (size_t i = 0U; i < frame.output_msg.GetSize(); ++i)
        {
            Json::Value json_obstacle;
            auto        obs              = frame.output_msg.GetObstacleList()[i];
            json_obstacle["sensor_id"]   = (uint32_t)obs->GetSensorId();
            json_obstacle["timestamp"]   = getTimestamp(obs->GetTimestamp());
            json_obstacle["obstacle_id"] = obs->GetObstacleId();
            json_obstacle["confidence"]  = obs->GetObstacleExistScore();
            json_obstacle["category"]    = getClassification(obs->GetClassification());
            Json::Value json_velocity;
            json_velocity.append(obs->GetRelativeVelocity()[0U]);
            json_velocity.append(obs->GetRelativeVelocity()[1U]);
            json_velocity.append(obs->GetRelativeVelocity()[2U]);
            json_obstacle["linear_velocity"] = json_velocity;
            Json::Value json_box3d;
            json_box3d["x"]        = obs->GetPosition().GetX();
            json_box3d["y"]        = obs->GetPosition().GetY();
            json_box3d["z"]        = obs->GetPosition().GetZ();
            json_box3d["rx"]       = obs->GetObstacleBBox3D().GetPose().GetRotation().YPR()[2U];
            json_box3d["ry"]       = obs->GetObstacleBBox3D().GetPose().GetRotation().YPR()[1U];
            json_box3d["rz"]       = obs->GetObstacleBBox3D().GetPose().GetRotation().YPR()[0U];
            json_box3d["h"]        = obs->GetObstacleBBox3D().GetHeight();
            json_box3d["w"]        = obs->GetObstacleBBox3D().GetWidth();
            json_box3d["l"]        = obs->GetObstacleBBox3D().GetDepth();
            json_obstacle["box3d"] = json_box3d;
            json_obstacle_list.append(json_obstacle);
        }
        json_frame["obstacle_list"] = json_obstacle_list;
        json_frame_list.append(json_frame);
    }
    root["frame_list"] = json_frame_list;
    // write
    Json::StyledWriter writer;
    std::ofstream      ofs;
    ofs.open(output_json_, std::ios::out);
    if (!ofs.is_open())
    {
        LOG(ERROR) << "Cannot create file: " << output_json_;
    }
    ofs << writer.write(root);
    ofs.close();
    LOG(INFO) << "Write to: " << output_json_;

}

}  // namespace perception
}  // namespace holo
#endif
