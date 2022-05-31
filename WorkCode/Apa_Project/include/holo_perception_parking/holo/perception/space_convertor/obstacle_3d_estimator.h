/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file estimate_3d_with_box2d.h
 * @brief This header file defines the class obstacle_3d_estimator.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2022-03-06"
 */

#ifndef HOLO_PERCEPTION_SPACE_CONVERTOR_OBSTACLE_3D_ESTIMATOR_H_
#define HOLO_PERCEPTION_SPACE_CONVERTOR_OBSTACLE_3D_ESTIMATOR_H_

#include <holo/log/hololog.h>
#include <algorithm>
#include <cmath>
#include <deque>
#include <list>
#include <set>
#include <unordered_map>

#include <holo/common/camera_fisheye.h>
#include <holo/container/vector.h>
#include <holo/filters/kalman_filter.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/rot3.h>
#include <holo/io/common/extrinsic.h>
#include <holo/io/common/intrinsic.h>
#include <holo/numerics/eigen_solver.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>
#include <holo/perception/common/box2d.h>
#include <holo/perception/common/box3d.h>
#include <holo/perception/common/box_object.h>
#include <holo/perception/space_convertor/ipm_convertor.h>
#include <holo/perception/utils/valid_checker.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace perception
{

class Obstacle3DEstimator
{
public:
    using Scalar                   = holo::float32_t;
    using CameraTypePtr            = std::shared_ptr<CameraFisheyeT<Scalar>>;
    using Box2Type                 = Box2DT<Scalar>;
    using Box3Type                 = Box3DT<Scalar>;
    using CameraDetectedObject     = BoxObjectT<Scalar, 8U>;
    using CameraDetectedObjectPtr  = std::shared_ptr<CameraDetectedObject>;
    using CameraDetectedObjectList = std::list<CameraDetectedObjectPtr>;
    using Vector1Type              = holo::numerics::Vector1T<Scalar>;
    using Vector3Type              = holo::numerics::Vector3T<Scalar>;
    using Vector4Type              = holo::numerics::Vector4T<Scalar>;
    using Vector6Type              = holo::numerics::Vector6T<Scalar>;
    using Matrix6Type              = holo::numerics::Matrix6T<Scalar>;
    using Point3Type               = holo::geometry::Point3T<Scalar>;
    using Point2Type               = holo::geometry::Point2T<Scalar>;
    using Rot3Type                 = holo::geometry::Rot3T<Scalar>;
    using Pose3Type                = holo::geometry::Pose3T<Scalar>;
    using Timestamp                = holo::common::Timestamp;
    using Plane                    = std::array<holo::float32_t, 3U>;
    using Frustum                  = std::array<Plane, 4U>;

    Obstacle3DEstimator(std::string const& camera_intrinsic_file, Pose3Type const& bodyTcam, Scalar bodyH,
                        std::set<uint32_t> const& vehicle_cat_ids, std::set<uint32_t> const& nomotor_cat_ids,
                        uint32_t speed_bump_cat_id, float32_t occlude_thresh);

    Obstacle3DEstimator(std::string const& camera_intrinsic_file, Pose3Type const& camTbody,
                        Pose3Type const& camTground, std::set<uint32_t> const& vehicle_cat_ids,
                        std::set<uint32_t> const& nomotor_cat_ids, uint32_t speed_bump_cat_id,
                        float32_t occlude_thresh);

    Obstacle3DEstimator(holo::yaml::Node const& node);

    uint32_t DoWork(CameraDetectedObjectList& det_obj_list, uint32_t app_stauts);

    uint32_t DoWorkWithKp(CameraDetectedObjectList& det_obj_list, uint32_t app_status);

private:
    /**
     * @brief Get the Corner Points of the box in object frame, object's center is coordinate origin
     *
     * @param[in] height box's height
     * @param[in] width box's width
     * @param[in] length box's length
     * @param[out] corner_points box's 8 corner points
     */
    void getCornerPoints(Scalar height, Scalar width, Scalar length,
                         holo::container::Vector<Point3Type, 8U>& corner_points) const;

    /**
     * @brief Get the Candidate Points of object
     *
     * @param[in] hwl, [height, width, length] of the object
     * @param[in] rx box3d's rotation angle in x-aixs, in radian
     * @param[in] ry box3d's rotation angle in y-axis, in radian
     * @param[in] rz box3d's rotation angle in z-axis, in radian
     * @param[in] project_2d, box3d's center point's projected 2d points
     * @param[in] bbox_xyxy [x1, y1, x2, y2] of the object
     * @param[in] use_box2d_cp, whether use the box2d's corners to compute the center_point as project_2d
     * @param[out] candidate_3d_points 3d points of object which can be projected on the box_2d's sides
     */
    void getCandidatePoints(Vector3Type const& hwl, Scalar rx, Scalar ry, Scalar rz, Point2Type const& project_2d,
                            Vector4Type const&                       bbox_xyxy,
                            holo::container::Vector<Point3Type, 4U>& candidate_3d_points) const;

    /**
     * @brief Check whether target point is in image
     *
     * @param pt, target 2d point
     * @param threshold, edge threshold
     * @return bool_t
     */
    bool_t isOnImage(Point2Type const& pt, Scalar threshold = 5.0) const;

    /**
     * @brief Check whether the object is truncated
     *
     * @param new_object
     * @return bool_t
     */
    bool_t isTruncated(CameraDetectedObject const& new_object) const;

    /**
     * @brief Revise the box3 dim and yaw for non-vehicle
     *
     * @param new_object
     */
    void reviseBox3(CameraDetectedObject& new_object) const;

    /**
     * @brief Use IPM to predict the position of object in camera coordinate
     *
     * @param new_object, input
     * @param position_cam, output
     * @return bool_t
     */
    bool_t useIPMEstimate(CameraDetectedObject const& new_object, Point3Type& position_cam) const;

    /**
     * @brief Use IPM to predict the position of object's keypoint
     *
     * @param kp
     * @param new_object
     * @param app_status
     * @param filter, whether filter obj when ipm failed
     * @return uint32_t
     */
    uint32_t kpIPMEstimate(KeyPointf const& kp, CameraDetectedObject& new_object, uint32_t app_status,
                           bool_t filter = false) const;

    /**
     * @brief Update box3d center with 3d keypoints
     *
     * @param new_object
     */
    void updateBox3WithKp3d(CameraDetectedObjectPtr& obj_ptr) const;

    /**
     * @brief Get the Undistorted BBox
     *
     * @param[in] box2d 2d bounding box
     * @return Vector4Type undistorted bbox, in [x1, y1, x2, y2]
     */
    Vector4Type getUndistortedBBox(Box2Type const& box2d) const;

    /**
     * @brief convert object from camera to body
     *
     * @param object
     */
    void transformToBody(CameraDetectedObjectPtr obj) const;

    Point3Type computeXYZ(Vector4Type const& bbox_xyxy, Vector3Type const& hwl, Point2Type const& project_2d, Scalar rx,
                          Scalar ry, Scalar rz, bool_t use_horizon) const;

    Vector3Type computeVelocity(std::deque<std::pair<Point3Type, Timestamp>> const& positions) const;

    void cleanPositionMap();

    Plane getPlane(Point3Type const& a, Point3Type const& b) const;

    bool_t inFrustum(Point3Type const& x) const;

private:
    Pose3Type          bodyTcam_;           ///< pose from camera to body
    Pose3Type          camTground_;         ///< pose from ground to camera
    float32_t          occlude_thresh_;     ///< occlude ratio threshold with all constraints
    std::set<uint32_t> vehicle_cat_ids_;    ///< vehicle category ids
    std::set<uint32_t> nomotor_cat_ids_;    ///< no-motor vehicle category ids, like bike
    uint32_t           speed_bump_cat_id_;  ///< spped hump category id

    uint32_t      image_width_;   ///< image's width resolution
    uint32_t      image_height_;  ///< image's height resolution
    CameraTypePtr camera_model_;  ///< camera's intrinsic model
    Frustum       cam_frustum_;

    std::shared_ptr<ValidChecker> position_checker_;

    Timestamp                                                                  current_timestamp_;
    std::unordered_map<uint32_t, std::deque<std::pair<Point3Type, Timestamp>>> id_positions_;
};

}  // namespace perception
}  // namespace holo
#endif  // !HOLO_PERCEPTION_SPACE_CONVERTOR_OBSTACLE_3D_ESTIMATOR_H_
