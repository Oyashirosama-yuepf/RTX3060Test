/*!
 *  \brief some algorithm toolkit function
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2019-05-17
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_UTILS_ALGORITHM_TOOLKIT_H_
#define HOLO_PERCEPTION_UTILS_ALGORITHM_TOOLKIT_H_

#include <limits>

#include <holo/common/odometry.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/map/current_route_info.h>
#include <holo/perception2/common/camera_model.h>
#include <holo/perception2/common/box2d.h>
#include <holo/numerics/vector.h>

namespace holo
{

namespace perception
{

namespace toolkit
{

/**
 * convert a point in src coordinate to dst coordinate
 * WARNING: just use Point3 not Vector3, because pose multiply
 * operator has different effect on Point3 and Vector3, Vector
 * is just a vector
 * 
 * param[in] pose - pose from source coordinate to dst coordinate
 * param[in] in_point - point from source coordinate 
 * param[return] - point converted to camera coordinate
*/
holo::Point3f ConvertPoint(
    const holo::Pose3& pose,
    const holo::Point3f& in_point);

holo::Vector3f ConvertPoint(
    const holo::Pose3& pose,
    const holo::Vector3f& in_point);

/**
 * find a bounding rectangle from points
 * param[in] points - points in uv coordinate
 * param[out] box2d - bounding box of these points
*/
void FindMax2DBBox(const std::vector<holo::Point2f>& points,
    holo::perception::BBox2f& box2d);

void FindMax2DBBox(const std::vector<holo::Vector2f>& points,
    holo::perception::BBox2f& box2d);

/**
 * project one 3d point in source coordinate to image
 * without camera distortion
 * param[in] pose - pose from source coordinate to camera coordinate
 * param[in] camera_model - camera model with camera intrinsic infromation
 * param[in] in_point - 3d point in source coordinate
 * param[out] out_point - output projected point
 * param[return] - whether the point is front of camera
*/
bool ProjectPoint2Image(
    const holo::Pose3& pose,
    const holo::perception::CameraModel<holo::float32_t>& camera_model,
    const holo::Point3f& in_point,
    holo::Point2f& out_point);

bool ProjectPoint2Image(
    const holo::Pose3& pose,
    const holo::perception::CameraModel<holo::float32_t>& camera_model,
    const holo::Vector3f& in_point,
    holo::Vector2f& out_point);

/**
 * project 3d points in source coordinate to image
 * without camera distortion
 * param[in] pose - pose from source coordinate to camera coordinate
 * param[in] camera_model - camera model with camera intrinsic infromation
 * param[in] in_points - 3d point in source coordinate
 * param[out] out_points - projected points
 * param[out] is_front_of_camera - whether point is front of camera
*/
void ProjectPoints2Image(
    const holo::Pose3& pose,
    const holo::perception::CameraModel<holo::float32_t>& camera_model,
    const std::vector<holo::Point3f>& in_points,
    std::vector<holo::Point2f>& out_points,
    std::vector<bool>& is_front_of_camera);

void ProjectPoints2Image(
    const holo::Pose3& pose,
    const holo::perception::CameraModel<holo::float32_t>& camera_model,
    const std::vector<holo::Vector3f>& in_points,
    std::vector<holo::Vector2f>& out_points,
    std::vector<bool>& is_front_of_camera);

/**
 * generate a 3d bounding box from a center point in body coordinate
 * param[in] w - box width
 * param[in] h - box height
 * param[in] l - box length
 * param[out] out - 3d box points
*/
void Gen3DBoxFromCenter(
    const float32_t w, 
    const float32_t h, 
    const float32_t l, 
    std::vector<holo::Point3f>& out);

void Gen3DBoxFromCenter(
    const float32_t w, 
    const float32_t h, 
    const float32_t l, 
    std::vector<holo::Vector3f>& out);

/**
 * generate a 3d box points from ground in body coordinate
 * param[in] w - box width
 * param[in] h - box height
 * param[in] l - box length
 * param[out] out - 3d box points
*/
void Gen3DBoxFromGround(
    const float32_t w, 
    const float32_t h, 
    const float32_t l, 
    std::vector<holo::Point3f>& out);

void Gen3DBoxFromGround(
    const float32_t w, 
    const float32_t h, 
    const float32_t l, 
    std::vector<holo::Vector3f>& out);

/**
 * calculate ground surface height from map CurrentRouteInfo
 * only calculate height value in y axis in novatel coordinate
 * param[in] route_info - route info from map
 * param[in] odometry - odometry
 * param[in] start_y - start position in y axis in novatel coordinate
 * param[in] end_y - end position in y axis in novate coordinate
 * param[in] step_y - y stride
 * param[out] ground_height - ground surface height vector
*/
void CalGroundSurfaceHeightFromCurrentRouteInfo(
    const holo::map::CurrentRouteInfo& route_info,
    const holo::Odometry& odo,
    holo::float32_t start_y,
    holo::float32_t end_y,
    holo::float32_t step_y,
    std::vector<float32_t>& ground_height);

/**
 * query ground surface height from map, in novatel coordinate
 * param[in] ground_height - ground surface height vector
 * param[in] query_y - y coord to query
 * param[in] start_y - ground height information range start y
 * param[in] end_y - ground height information range end y
 * param[in] step_y - ground height information step
*/
holo::float32_t QueryGroundSurfaceHeightFromMap(
    const std::vector<holo::float32_t>& ground_height,
    holo::float32_t query_y,
    holo::float32_t start_y,
    holo::float32_t end_y,
    holo::float32_t step_y);

}   /// end namespace toolkit

}   /// end namespace perception

}   /// end namespace holo

#endif  // HOLO_PERCEPTION_UTILS_ALGORITHM_TOOLKIT_H_