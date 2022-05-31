/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tool_funcs.h
 * @brief This header file defines some tool funcs for class MotionStatus
 * @author zouyi(zouyi@holomatic.com)
 * @date "2022-04-15"
 */

#ifndef HOLO_PERCEPTION_3D_APP_TOOL_FUNCS_
#define HOLO_PERCEPTION_3D_APP_TOOL_FUNCS_

#include <fstream>
#include <vector>

#include <opencv2/opencv.hpp>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/geometry/Rot3.h>

#include <holo/common/camera_fisheye.h>
#include <holo/common/odometry.h>
#include <holo/geometry/plane3.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/app/motion_status.h>
#include <holo/perception/common/box_object.h>

namespace holo
{
namespace perception
{
namespace motion_status
{
#define MAX_ERROR 100
using Scalar    = holo::float32_t;
using Timestamp = holo::common::Timestamp;
using Object    = holo::obstacle::ObstacleVisionT<holo::float32_t>;
using Odometryd = holo::common::Odometryd;
using cv::Point3f;

using std::string;
using std::vector;

/**
 * @brief 3d line: (x - x0) / m = (y - y0) / n = (z - z0) / p
 *
 */
struct Line
{
    Line(holo::float32_t x0, holo::float32_t y0, holo::float32_t z0, holo::float32_t m, holo::float32_t n,
         holo::float32_t p)
    {
        ori       = Point3f(x0, y0, z0);
        direction = Point3f(m, n, p);
    }
    cv::Point3f ori;
    cv::Point3f direction;
};

/**
 * @brief Get the obj from id object
 *
 * @param id
 * @param object_list
 * @param output
 * @return bool_t
 */
bool_t GetObjById(uint32_t id, ObstacleVisionPtrList const& object_list, std::shared_ptr<Object>& output);

/**
 * @brief given a line in camera coordnate in 3d space and the camera pose in dr , return the line in dr coordnate
 *
 * @param line
 * @param camera_pose
 * @return Line
 */
Line RotateLine(Line const& line, holo::geometry::Pose3d const& camera_pose);

/**
 * @brief cal kps prob based on their position
 *
 * @param kps
 * @param kps_is_valid
 * @return std::vector<holo::float32_t>
 */
std::vector<holo::float32_t> CalKPsProb(holo::container::Vector<holo::vision::KeyPoint2f, 8UL> const& kps,
                                        std::vector<bool_t> const&                                    kps_is_valid);

/**
 * @brief given two range , cal their overlap length
 *
 * @param l1
 * @param l2
 * @return holo::float32_t
 */
holo::float32_t CalOverlap(holo::Vector2f const& l1, holo::Vector2f const& l2);

/**
 * @brief convert intrinsic data type
 *
 * @param intrinsic_holo
 * @param intrinsic
 * @param distortion
 */
void IntrinsicHolo2Opencv(holo::common::FisheyeIntrinsicf intrinsic_holo, cv::Mat& intrinsic, cv::Mat& distortion);

/**
 * @brief Get the timestamp string object
 *
 * @param timestamp
 * @return std::string
 */
std::string GetTimestampString(holo::common::Timestamp const& timestamp);

/**
 * @brief find the max and second max value index in the input
 *
 * @param input
 * @param maxind
 * @param secondind
 */
void FindMaxSecond(std::vector<holo::float32_t> const& input, holo::int32_t& maxind, holo::int32_t& secondind);
/**
 * @brief given a line and a point in 3d space ,cal their distance
 *
 * @param line
 * @param point
 * @return holo::float32_t
 */
holo::float32_t PointLineDist(Line line, holo::Point3f point);
/**
 * @brief convert obj data type from first to second
 *
 * @param det_obj
 * @param obs_vis
 */
void ConvertObj(holo::perception::MotionStatus::CameraDetectedObjectType const& det_obj,
                holo::perception::MotionStatus::Object&                         obs_vis);

/**
 * @brief calulate error and dz from  3d lines
 *
 * @param dr_lines
 * @param derror
 * @param center
 * @param error
 * @param dz
 */
void CalculateErrorWithDz(std::vector<Line> const& dr_lines, holo::float32_t const& derror, holo::Point3f& center,
                          float64_t& error, float64_t& dz);

}  // namespace motion_status
}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_3D_APP_TOOL_FUNCS_
