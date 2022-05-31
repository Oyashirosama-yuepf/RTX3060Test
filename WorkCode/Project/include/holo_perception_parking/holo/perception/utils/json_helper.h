/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file json_helper.h
 * @brief This header file defines json reader and writer.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2021-06-01"
 */

#ifndef HOLO_PERCEPTION_3D_UTILS_JSON_HELPER_H_
#define HOLO_PERCEPTION_3D_UITLS_JSON_HELPER_H_

#include <gtest/gtest.h>
#include <fstream>

#include <holo/common/classification.h>
#include <holo/core/types.h>
#include <holo/geometry/box2.h>
#include <holo/geometry/box3.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/geometry/quaternion.h>
#include <holo/geometry/rot3.h>
#include <holo/numerics/matrix.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/common/box2d.h>
#include <holo/perception/common/box3d.h>
#include <holo/perception/common/box_object.h>
#include <holo/perception/common/keypoint.h>
#include <holo/perception/utils/json.h>
#include <holo/vision/keypoint2.h>

namespace holo
{
namespace perception
{
class JsonHelper
{
public:
    using Scalar                = holo::float32_t;
    using Pose3Type             = holo::geometry::Pose3T<Scalar>;
    using Rot3Type              = holo::geometry::Rot3T<Scalar>;
    using Point3Type            = holo::geometry::Point3T<Scalar>;
    using Point2Type            = holo::geometry::Point2T<Scalar>;
    using QuaternionType        = holo::geometry::QuaternionT<Scalar>;
    using Box2TypeBase          = holo::geometry::Box2T<Scalar>;
    using Box3TypeBase          = holo::geometry::Box3T<Scalar>;
    using KeyPoint2Base         = holo::vision::KeyPoint2T<Scalar>;
    using Box2Type              = holo::perception::Box2DT<Scalar>;
    using Box3Type              = holo::perception::Box3DT<Scalar>;
    using KeyPointType          = holo::perception::KeyPointT<Scalar>;
    using Classification        = holo::common::Classification;
    using ObstacleVisionPtrList = holo::obstacle::ObstacleVisionPtrList;
    using Object                = BoxObjectT<Scalar, 8U>;

    struct MetaInfo
    {
        std::string bag_name;
        std::string topic_name;
        std::string camera_name;
        std::string Kstr;
        std::string Dstr;
        std::string Tstr;
        std::string Rstr;
        Pose3Type   Tbody_cam;

        MetaInfo() = default;
    };

    struct FrameInfo
    {
        uint32_t          index;
        std::string       timestamp;
        std::string       image_name;
        std::string       ply_name;
        std::string       radar_name;
        std::list<Object> object_list;

        FrameInfo(uint32_t _index, std::string const& _timestamp, std::string const& _image_name,
                  std::string const& _ply_name, std::string const& _radar_name, std::list<Object> const& _object_list)
          : index(_index)
          , timestamp(_timestamp)
          , image_name(_image_name)
          , ply_name(_ply_name)
          , radar_name(_radar_name)
          , object_list(_object_list)
        {
        }
    };

    JsonHelper();

    ~JsonHelper();

    bool_t Read(std::string const& jsonfile, std::vector<FrameInfo>& frame_obs);

    bool_t Read(std::string const& jsonfile, std::vector<ObstacleVisionPtrList>& frame_obs) const;

    bool_t Write(std::vector<FrameInfo> const& frame_obs, std::string const& jsonfile) const;

    Pose3Type const& GetTbody_cam() const
    {
        return meta_info_.Tbody_cam;
    }

private:
    std::vector<Scalar> parseString(std::string const& str, size_t vec_size) const;

    Pose3Type readPose(std::string const& Rstr, std::string const& Tstr) const;

    void readMetaInfo(Json::Value const& root);

    Classification getClassification(std::string const& category) const;

    holo::perception::ClassifyInfo getClassifyInfo(std::string const& category) const;

    std::string getCategory(Classification const& classification) const;

    std::string getCategory(holo::perception::ClassifyInfo const& cls_info) const;

    Timestamp getTimestamp(std::string const& ts) const;

    Box2TypeBase getBaseBox2(Json::Value const& box2d_json) const;

    Box2Type getPerBox2(Json::Value const& box2d_json) const;

    Box3TypeBase getBaseBox3(Json::Value const& box3d_json) const;

    Box3Type getPerBox3(Json::Value const& box3d_json) const;

    KeyPoint2Base getBaseKeyPoint2(Json::Value const& p_center, float32_t occluded_ratio) const;

    KeyPointType getPerKeyPoint2(Json::Value const& p_center) const;

    KeyPointType getOtherPerKeyPoint2(Json::Value const& kp) const;

private:
    MetaInfo meta_info_;
};

}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_3D_UTILS_JSON_HELPER_H_
