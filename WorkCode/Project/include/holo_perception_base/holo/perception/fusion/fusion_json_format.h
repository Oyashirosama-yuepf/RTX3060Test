/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fusion_json_format.h
 * @brief This header file defines fusion input & output message json format.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2022-03-23"
 */

#ifndef HOLO_PERCEPTION_FUSION_JSON_FORMAT_H_
#define HOLO_PERCEPTION_FUSION_JSON_FORMAT_H_

#include <holo/common/odometry.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/utils/json.h>

namespace holo
{
namespace perception
{
/**
 * @brief convert between holo struct & json value
 * @details General name rules:
 * getter convert json value -> holo struct
 * setter convert holo struct -> json value
 *
 */
class FusionJsonFormat
{
public:
    using Scalar            = float32_t;
    using LidarMessageType  = holo::obstacle::ObstacleLidarPtrList;
    using RadarMessageType  = holo::obstacle::ObstacleRadarPtrList;
    using VisionMessageType = holo::obstacle::ObstacleVisionPtrList;
    using UssMessageType    = holo::obstacle::ObstacleUssPtrList;
    using FusedMessageType  = holo::obstacle::ObstacleGeneralPtrList;
    using LidarMessage      = std::shared_ptr<LidarMessageType>;
    using RadarMessage      = std::shared_ptr<RadarMessageType>;
    using VisionMessage     = std::shared_ptr<VisionMessageType>;
    using UssMessage        = std::shared_ptr<UssMessageType>;
    using LidarFrameList    = std::vector<LidarMessage>;
    using RadarFrameList    = std::vector<RadarMessage>;
    using VisionFrameList   = std::vector<VisionMessage>;
    using UssFrameList      = std::vector<UssMessage>;
    using LidarMessageMap   = std::unordered_map<uint32_t, LidarMessage>;
    using RadarMessageMap   = std::unordered_map<uint32_t, RadarMessage>;
    using VisionMessageMap  = std::unordered_map<uint32_t, VisionMessage>;
    using UssMessageMap     = std::unordered_map<uint32_t, UssMessage>;
    using KeyPoint2Type     = holo::vision::KeyPoint2T<Scalar>;
    using KeyPoint2Vec      = holo::container::Vector<KeyPoint2Type, 8U>;
    using KeyPoint3Type     = holo::vision::KeyPoint3T<Scalar>;
    using KeyPoint3Vec      = holo::container::Vector<KeyPoint3Type, 8U>;

public:
    /**
     * @brief Get the Sensor Id object
     *
     * @param value json value
     * @return common::SensorId sensor id
     */
    static common::SensorId GetSensorId(Json::Value const& value);

    /**
     * @brief Set the Sensor Id object
     *
     * @param root json value
     * @param sid sensor id
     * @param key json key
     */
    static void SetSensorId(Json::Value& root, common::SensorId const& sid, std::string const& key = "sensor_id");

    /**
     * @brief Get the Timestamp object
     *
     * @param value json value
     * @return common::Timestamp timestamp
     */
    static common::Timestamp GetTimestamp(Json::Value const& value);

    /**
     * @brief Set the Timestamp object
     *
     * @param root json value
     * @param timestamp timestamp
     * @param key json key
     */
    static void SetTimestamp(Json::Value& root, common::Timestamp const& timestamp,
                             std::string const& key = "timestamp");

    /**
     * @brief get uint32_t from json value
     *
     * @param value json value
     * @return uint32_t uint value
     */
    static uint32_t GetUInt32(Json::Value const& value);

    /**
     * @brief set uint32_t to json value
     *
     * @param root json value
     * @param x uint32_t value
     * @param key json key
     */
    static void SetUInt32(Json::Value& root, uint32_t x, std::string const& key);

    /**
     * @brief Get float from json value
     *
     * @param value json value
     * @return float32_t float
     */
    static float32_t GetFloat32(Json::Value const& value);

    /**
     * @brief Set the float to json value
     *
     * @param root json value
     * @param x float
     * @param key json key
     */
    static void SetFloat32(Json::Value& root, float32_t x, std::string const& key);

    /**
     * @brief Get the Vector3f object from json value
     *
     * @param value json value
     * @return numerics::Vector3f vector3
     */
    static numerics::Vector3f GetVector3f(Json::Value const& value);

    /**
     * @brief Set the Vector3f object
     *
     * @param root json value
     * @param vec vector3
     * @param key json key
     */
    static void SetVector3f(Json::Value& root, numerics::Vector3f const& vec, std::string const& key);

    /**
     * @brief Get the Point3f object
     *
     * @param value json value
     * @return geometry::Point3f point3
     */
    static geometry::Point3f GetPoint3f(Json::Value const& value);

    /**
     * @brief Set the Point3f object
     *
     * @param root json value
     * @param point point3
     * @param key json key
     */
    static void SetPoint3f(Json::Value& root, geometry::Point3f const& point, std::string const& key);

    /**
     * @brief Get the Box2 object
     *
     * @param box2d_info json value
     * @return geometry::Box2f box2f
     */
    static geometry::Box2f GetBox2(Json::Value const& box2d_info);

    /**
     * @brief Set the Box2 object
     *
     * @param root json value
     * @param box2d box2
     * @param key json key
     */
    static void SetBox2(Json::Value& root, geometry::Box2f const& box2d, std::string const& key = "box2d");

    /**
     * @brief Get the Box3 object
     *
     * @param value json value
     * @return geometry::Box3f box3f
     */
    static geometry::Box3f GetBox3(Json::Value const& value);

    /**
     * @brief Set the Box3 object
     *
     * @param root json value
     * @param box3d box3
     * @param key json key
     */
    static void SetBox3(Json::Value& root, geometry::Box3f const& box3d, std::string const& key = "box3d");

    /**
     * @brief Set the Box3 object
     *
     * @param root json value
     * @param position position
     * @param shape shape[width, height, length]
     * @param key json key
     */
    static void SetBox3(Json::Value& root, geometry::Point3f const& position, numerics::Vector3f const& shape,
                        std::string const& key = "box3d");

    /**
     * @brief Get the Shape object
     *
     * @param value json value
     * @return numerics::Vector3f shape
     */
    static numerics::Vector3f GetShape(Json::Value const& value);

    /**
     * @brief Get the Classification object
     *
     * @param value json value
     * @return common::Classification classification
     */
    static common::Classification GetClassification(Json::Value const& value);

    /**
     * @brief Set the Classification object
     *
     * @param root json value
     * @param classification classification
     * @param key json key
     */
    static void SetClassification(Json::Value& root, common::Classification classification,
                                  std::string const& key = "category");

    /**
     * @brief Set the Key Points 2D object
     *
     * @param root json value
     * @param
     *
     */
    static void SetKeyPoints2D(Json::Value& root, KeyPoint2Vec kp2, std::string key="keypoint2d");

    /**
     * @brief Set the Key Points 3D object
     *
     * @param root
     * @param obs
     */
    static void SetKeyPoints3D(Json::Value& root, KeyPoint3Vec kp3, std::string key="keypoint3d");

    /**
     * @brief Get the Pose3T object
     *
     * @param value json value
     * @return geometry::Pose3d pose3d
     */
    template <typename T>
    static geometry::Pose3T<T> GetPose3T(Json::Value const& value)
    {
        auto const&       rotation    = value["rotation"];
        auto const&       translation = value["translation"];
        geometry::Rot3T<T>  rot(rotation[0U].asDouble(), rotation[1U].asDouble(), rotation[2U].asDouble(),
                            rotation[3U].asDouble(), rotation[4U].asDouble(), rotation[5U].asDouble(),
                            rotation[6U].asDouble(), rotation[7U].asDouble(), rotation[8U].asDouble());
        geometry::Point3T<T> trans(translation[0U].asDouble(), translation[1U].asDouble(), translation[2U].asDouble());
        return geometry::Pose3T<T>(rot, trans);
    }

    /**
     * @brief Set the Pose 3T object
     *
     * @param root json value
     * @param pose pose
     * @param key json key
     */
    template <typename T>
    static void SetPose3T(Json::Value& root, geometry::Pose3T<T> const& pose, std::string const& key = "pose")
    {
        Json::Value value, rotation, translation;
        auto const& m = pose.ToMatrix();
        for (uint8_t i = 0U; i < 3U; ++i)
        {
            for (uint8_t j = 0U; j < 3U; ++j)
            {
                rotation.append(m(i, j));
            }
            translation.append(m(i, 3U));
        }
        value["rotation"]    = rotation;
        value["translation"] = translation;
        root[key]            = value;
    }

    /**
     * @brief Get the Vector 6T object
     *
     * @param linear_velocity json value
     * @param angular_velocity json value
     * @return numerics::Vector6d vector6d
     */
    template <typename T>
    static numerics::Vector6T<T> GetVector6T(Json::Value const& linear_velocity, Json::Value const& angular_velocity)
    {
        numerics::Vector6T<T> velocity;
        velocity(0U) = linear_velocity[0U].asDouble();
        velocity(1U) = linear_velocity[1U].asDouble();
        velocity(2U) = linear_velocity[2U].asDouble();
        velocity(3U) = angular_velocity[0U].asDouble();
        velocity(4U) = angular_velocity[1U].asDouble();
        velocity(5U) = angular_velocity[2U].asDouble();
        return velocity;
    }

    /**
     * @brief Set the Linear Velocity object
     *
     * @param root json value
     * @param vel velocity
     * @param key json key
     */
    template <typename T>
    static void SetLinearVelocity(Json::Value& root, numerics::Vector6T<T> const& vel,
                                  std::string const& key = "linear_velocity")
    {
        Json::Value value;
        for (uint8_t i = 0U; i < 3U; ++i)
        {
            value.append(vel(i));
        }
        root[key] = value;
    }

    /**
     * @brief Set the Angular Velocity object
     *
     * @param root json value
     * @param vel velocity
     * @param key json key
     */
    template <typename T>
    static void SetAngularVelocity(Json::Value& root, numerics::Vector6T<T> const& vel,
                                   std::string const& key = "angular_velocity")
    {
        Json::Value value;
        for (uint8_t i = 0U; i < 3U; ++i)
        {
            value.append(vel(3U + i));
        }
        root[key] = value;
    }

    /**
     * @brief Get the Odometry object
     *
     * @param value json value
     * @return OdometryPtr odometry
     */
    template <typename OdometryType, typename T>
    static std::shared_ptr<OdometryType> GetOdometry(Json::Value const& value)
    {
        std::shared_ptr<OdometryType> odometry = std::make_shared<OdometryType>();
        odometry->SetTimestamp(GetTimestamp(value["timestamp"]));
        odometry->SetPose(GetPose3T<T>(value["pose"]));
        odometry->SetVelocity(GetVector6T<T>(value["linear_velocity"], value["angular_velocity"]));
        return odometry;
    }

    /**
     * @brief Set the Odometry object
     *
     * @param value json value
     * @param odometry odometry
     */
    template <typename OdometryType, typename T>
    static void SetOdometry(Json::Value& value, OdometryType const odometry)
    {
        SetTimestamp(value, odometry.GetTimestamp());
        SetPose3T<T>(value, odometry.GetPose());
        SetLinearVelocity<T>(value, odometry.GetVelocity());
        SetAngularVelocity<T>(value, odometry.GetVelocity());
    }

    /**
     * @brief Get the Odometry List object
     *
     * @param odometry_list json value
     * @param odo_list odometry list
     */

    template<typename OdometryFrameListType, typename OdometryType, typename T>
    static void GetOdometryList(Json::Value const& odometry_list, OdometryFrameListType& odo_list)
    {
        for (auto info : odometry_list)
        {
            odo_list.push_back(GetOdometry<OdometryType, T>(info));
        }
    }

    /**
     * @brief Set the Odometry List object
     *
     * @param odometry_list json value
     * @param odo_list odometry list
     */
    template <typename OdometryFrameListType, typename OdometryType, typename T>
    static void SetOdometryList(Json::Value& odometry_list, OdometryFrameListType const& odo_list)
    {
        for (auto odo : odo_list)
        {
            Json::Value value;
            SetOdometry<OdometryType, T>(value, *odo);
            odometry_list.append(value);
        }
    }

    /**
     * @brief Get the Obstacle object
     *
     * @tparam ObstacleType obstacle type
     * @param value json value
     * @param sensor_id sensor id
     * @param timestamp timestamp
     * @return std::shared_ptr<ObstacleType> obstacle pointer
     */
    template <class ObstacleType>
    static std::shared_ptr<ObstacleType> GetObstacle(Json::Value const& value, common::SensorId const& sensor_id,
                                                     common::Timestamp const& timestamp)
    {
        auto obs = std::make_shared<ObstacleType>();
        if (value.isMember("sensor_id"))
        {
            obs->SetSensorId(GetSensorId(value["sensor_id"]));
        }
        else
        {
            obs->SetSensorId(sensor_id);
        }
        if (value.isMember("timestamp"))
        {
            obs->SetTimestamp(GetTimestamp(value["timestamp"]));
        }
        else
        {
            obs->SetTimestamp(timestamp);
        }
        obs->SetObstacleId(GetUInt32(value["obstacle_id"]));
        obs->SetObstacleExistScore(GetFloat32(value["confidence"]));
        obs->SetClassification(GetClassification(value["category"]));
        obs->SetRelativeVelocity(GetVector3f(value["linear_velocity"]));
        if (value.isMember("acceleration"))
        {
            obs->SetAcceleration(GetVector3f(value["acceleration"]));
        }
        if (value.isMember("box2d"))
        {
            getObstacleBox2<ObstacleType>(obs, value["box2d"]);
        }
        auto const& box3d_info = value["box3d"];
        obs->SetPosition(GetPoint3f(box3d_info));
        getObstacleBox3<ObstacleType>(obs, box3d_info);

        if (value.isMember("keypoint2d"))
        {
            getKeypoint2D<ObstacleType>(obs, value["keypoint2d"]);
        }

        if (value.isMember("keypoint3d"))
        {
            getKeypoint3D<ObstacleType>(obs, value["keypoint3d"]);
        }

        return obs;
    }

    /**
     * @brief Set the Obstacle object
     *
     * @tparam ObstacleType obstacle type
     * @param value json value
     * @param obs obstacle pointer
     */
    template <class ObstacleType>
    static void SetObstacle(Json::Value& value, std::shared_ptr<ObstacleType> const obs)
    {
        SetSensorId(value, obs->GetSensorId());
        SetTimestamp(value, obs->GetTimestamp());
        SetUInt32(value, obs->GetObstacleId(), "obstacle_id");
        SetFloat32(value, obs->GetObstacleExistScore(), "confidence");
        SetClassification(value, obs->GetClassification());
        SetVector3f(value, obs->GetRelativeVelocity(), "linear_velocity");
        setObstacleBox2<ObstacleType>(value, obs);
        setObstacleBox3<ObstacleType>(value, obs);
        setObstacleKeypoint<ObstacleType>(value, obs);
    }

    /**
     * @brief Get the Message object
     *
     * @tparam MessageType message type
     * @tparam ObstacleType obstacle type
     * @param frame json value
     * @param sensor_id sensor id
     * @return std::shared_ptr<MessageType> message pointer
     */
    template <class MessageType, class ObstacleType>
    static std::shared_ptr<MessageType> GetMessage(Json::Value const& frame, common::SensorId const& sensor_id)
    {
        auto msg = std::make_shared<MessageType>();
        msg->SetSensorId(sensor_id);
        auto timestamp = GetTimestamp(frame["timestamp"]);
        msg->SetTimestamp(timestamp);
        size_t cnt = 0U;
        for (auto const& info : frame["obstacle_list"])
        {
            msg->GetObstacleList()[cnt++] = GetObstacle<ObstacleType>(info, sensor_id, timestamp);
        }
        msg->SetSize(cnt);
        return msg;
    }

    /**
     * @brief Set the Message object
     *
     * @tparam MessageType message type
     * @tparam ObstacleType obstacle type
     * @param frame json value
     * @param msg message
     */
    template <class MessageType, class ObstacleType>
    static void SetMessage(Json::Value& frame, MessageType const& msg)
    {
        SetSensorId(frame, msg.GetSensorId());
        SetTimestamp(frame, msg.GetTimestamp());
        for (size_t i = 0U; i < msg.GetSize(); ++i)
        {
            auto        obs = msg.GetObstacleList()[i];
            Json::Value info;
            SetObstacle(info, obs);
            frame["obstacle_list"].append(info);
        }
    }

    /**
     * @brief Get the Message List object
     *
     * @tparam MessageListType message list type
     * @tparam MessageType message type
     * @tparam ObstacleType obstacle type
     * @param frame_list json value
     * @param msg_list message list
     * @param sensor_id sensor id
     */
    template <class MessageListType, class MessageType, class ObstacleType>
    static void GetMessageList(Json::Value const& frame_list, MessageListType& msg_list,
                               common::SensorId const& sensor_id)
    {
        for (auto const& frame : frame_list)
        {
            msg_list.push_back(GetMessage<MessageType, ObstacleType>(frame, sensor_id));
        }
    }

    /**
     * @brief Set the Message List object
     *
     * @tparam MessageListType message list type
     * @tparam MessageType message type
     * @tparam ObstacleType obstacle type
     * @param frame_list json value
     * @param msg_list message list
     */
    template <class MessageListType, class MessageType, class ObstacleType>
    static void SetMessageList(Json::Value& frame_list, MessageListType const& msg_list)
    {
        for (auto msg : msg_list)
        {
            Json::Value frame;
            SetMessage(frame, *msg);
            frame_list.append(frame);
        }
    }

private:
    /**
     * @brief Get the Obstacle Box2 object
     *
     * @tparam ObstacleType obstacle type
     * @param obs obstacle
     * @param value json value
     */
    template <class ObstacleType>
    static void getObstacleBox2(std::shared_ptr<ObstacleType> obs, Json::Value const& value)
    {
        (void)obs;
        (void)value;
    }

    /**
     * @brief Get the Obstacle Box3 object
     *
     * @tparam ObstacleType obstacle type
     * @param obs obstacle
     * @param value json value
     */
    template <class ObstacleType>
    static void getObstacleBox3(std::shared_ptr<ObstacleType> obs, Json::Value const& value)
    {
        obs->SetObstacleBBox3D(GetBox3(value));
    }

    /**
     * @brief Set the Obstacle Box2 object
     *
     * @tparam ObstacleType obstacle type
     * @param root json value
     * @param obs obstacle
     */
    template <class ObstacleType>
    static void setObstacleBox2(Json::Value& root, std::shared_ptr<ObstacleType> const obs)
    {
        (void)root;
        (void)obs;
    }

    /**
     * @brief Set the Obstacle Box3 object
     *
     * @tparam ObstacleType obstacle type
     * @param root json value
     * @param obs obstacle
     */
    template <class ObstacleType>
    static void setObstacleBox3(Json::Value& root, std::shared_ptr<ObstacleType> const obs)
    {
        SetBox3(root, obs->GetObstacleBBox3D());
    }

    template <class ObstacleType>
    static void getKeypoint2D(std::shared_ptr<ObstacleType> obs, Json::Value const& value)
    {
        (void)value;
        (void)obs;
    }

    template <class ObstacleType>
    static void getKeypoint3D(std::shared_ptr<ObstacleType> obs, Json::Value const& value)
    {
        (void)value;
        (void)obs;
    }

    template <class ObstacleType>
    static void setObstacleKeypoint(Json::Value& value, std::shared_ptr<ObstacleType> const obs)
    {
        (void)value;
        (void)obs;
    }
};

/* inline specialize to avoid multiply definition */

/**
 * @brief get obstacle from uss obstacle
 *
 * @tparam
 * @param json value
 * @param sensor_id
 * @param timestamp
 * @return std::shared_ptr<obstacle::ObstacleUssT<float32_t>>
 */
template <>
inline std::shared_ptr<obstacle::ObstacleUssT<float32_t>> FusionJsonFormat::GetObstacle(
    Json::Value const& value, common::SensorId const& sensor_id, common::Timestamp const& timestamp)
{
    auto obs = std::make_shared<obstacle::ObstacleUssT<float32_t>>();
    if (value.isMember("sensor_id"))
    {
        obs->SetSensorId(GetSensorId(value["sensor_id"]));
    }
    else
    {
        obs->SetSensorId(sensor_id);
    }
    if (value.isMember("timestamp"))
    {
        obs->SetTimestamp(GetTimestamp(value["timestamp"]));
    }
    else
    {
        obs->SetTimestamp(timestamp);
    }
    obs->SetObstacleId(GetUInt32(value["obstacle_id"]));
    obs->SetObstacleExistScore(GetFloat32(value["confidence"]));
    obs->SetClassification(GetClassification(value["category"]));

    if (value.isMember("box2d"))
    {
        getObstacleBox2<obstacle::ObstacleUssT<float32_t>>(obs, value["box2d"]);
    }
    auto const& box3d_info = value["box3d"];
    obs->SetPosition(GetPoint3f(box3d_info));
    return obs;
}

/**
 * @brief set uss obstacle for uss obs
 *
 * @tparam
 * @param json value
 * @param uss obs
 */
template <>
inline void FusionJsonFormat::SetObstacle(Json::Value& value, std::shared_ptr<obstacle::ObstacleUssT<float32_t>> const obs)
{
    SetSensorId(value, obs->GetSensorId());
    SetTimestamp(value, obs->GetTimestamp());
    SetUInt32(value, obs->GetObstacleId(), "obstacle_id");
    SetFloat32(value, obs->GetObstacleExistScore(), "confidence");
    SetClassification(value, obs->GetClassification());
    setObstacleBox2<obstacle::ObstacleUssT<float32_t>>(value, obs);
    SetBox3(value, obs->GetPosition(), numerics::Vector3f(0.f, 0.f, 0.f));
}

/**
 * @brief get obstacle box2 for vision obstacle
 *
 * @tparam
 * @param obs vision obs
 * @param value json value
 */
template <>
inline void FusionJsonFormat::getObstacleBox2<obstacle::ObstacleVisionT<float32_t>>(
    std::shared_ptr<obstacle::ObstacleVisionT<float32_t>> obs, Json::Value const& value)
{
    obs->SetImageBBox2D(GetBox2(value));
}

/**
 * @brief get obstacle shape for radar obs
 *
 * @tparam
 * @param obs radar obs
 * @param value json value
 */
template <>
inline void FusionJsonFormat::getObstacleBox3<obstacle::ObstacleRadarT<float32_t>>(
    std::shared_ptr<obstacle::ObstacleRadarT<float32_t>> obs, Json::Value const& value)
{
    obs->SetObstacleShape(GetShape(value));
}

/**
 * @brief set obstacle box2 for vision obs
 *
 * @tparam
 * @param root json value
 * @param obs vision obs
 */
template <>
inline void FusionJsonFormat::setObstacleBox2<obstacle::ObstacleVisionT<float32_t>>(
    Json::Value& root, std::shared_ptr<obstacle::ObstacleVisionT<float32_t>> const obs)
{
    SetBox2(root, obs->GetImageBBox2D());
}

/**
 * @brief set obstacle shape for radar obs
 *
 * @tparam
 * @param root json value
 * @param obs radar obs
 */
template <>
inline void FusionJsonFormat::setObstacleBox3<obstacle::ObstacleRadarT<float32_t>>(
    Json::Value& root, std::shared_ptr<obstacle::ObstacleRadarT<float32_t>> const obs)
{
    SetBox3(root, obs->GetPosition(), obs->GetObstacleShape());
}

template <>
inline void FusionJsonFormat::getKeypoint2D<obstacle::ObstacleVisionT<float32_t>>
    (std::shared_ptr<obstacle::ObstacleVisionT<float32_t>> obs, Json::Value const& value)
{
    KeyPoint2Vec kp2_vec;
    for (auto info : value)
    {
        float32_t     x          = info["x"].asFloat();
        float32_t     y          = info["y"].asFloat();
        float32_t     confidence = info["confidence"].asFloat();
        bool_t        visible    = info["visible"].asBool();
        KeyPoint2Type kp(x, y, confidence, visible);
        kp2_vec.push_back(kp);
    }
    obs->SetKeyPoints2D(kp2_vec);
}

template <>
inline void FusionJsonFormat::getKeypoint3D<obstacle::ObstacleVisionT<float32_t>>
    (std::shared_ptr<obstacle::ObstacleVisionT<float32_t>> obs, Json::Value const& value)
{
    KeyPoint3Vec kp3_vec;
    for (auto info : value)
    {
        float32_t     x          = info["x"].asFloat();
        float32_t     y          = info["y"].asFloat();
        float32_t     confidence = info["confidence"].asFloat();
        bool_t        visible    = info["visible"].asBool();
        KeyPoint3Type kp(x, y, 0.f, confidence, visible);
        kp3_vec.push_back(kp);
    }
    obs->SetKeyPoints3D(kp3_vec);
}

/**
 * @brief set obstacle shape for vision obs
 *
 * @tparam
 * @param value json value
 * @param obs radar obs
 */
template <>
inline void FusionJsonFormat::setObstacleKeypoint<obstacle::ObstacleVisionT<float32_t>>(
    Json::Value& value, std::shared_ptr<obstacle::ObstacleVisionT<float32_t>> const obs)
{

    auto kp2 = obs->GetKeyPoints2D();
    auto kp3 = obs->GetKeyPoints3D();
    SetKeyPoints2D(value, kp2);
    SetKeyPoints3D(value, kp3);
}

}  // namespace perception
}  // namespace holo

#endif
