/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file det_postprocess.h
 * @brief This header file defines freespace common post process.
 */

#ifndef _HOLO_PERCEPTION_COMMON_DET_POSTPROCESS_H_
#define _HOLO_PERCEPTION_COMMON_DET_POSTPROCESS_H_

#include <assert.h>
#include <holo/common/freespace.h>
#include <holo/common/image.h>
#include <holo/perception/algorithm/ipm.h>
#include <holo/perception/algorithm/tracking/camera_tracking_algorithm.h>
#include <holo/perception/common/box_object.h>
#include <holo/perception/common/image_bbox2d.h>
#include <holo/perception/common/params_loader.h>
#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/space_convertor/obstacle_3d_smoother.h>
#include <holo/perception/utils/class_registry.h>
#include <holo/perception/utils/dg_port.h>
#include <holo/perception/utils/utility.h>
#include <sys/time.h>

#include <boost/bimap.hpp>
#include <cmath>
#include <mutex>
#include <queue>

#include "holo/perception/common/camera_config_ex.h"

namespace holo
{
namespace perception
{
class DetPostProcess
{
    typedef typename holo::ObstaclePtrListT<ObstacleVisionT<float32_t>, holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY>
        CameraObstacleList;
    typedef typename holo::ObstaclePtrListT<holo::ObstacleGeneralT<holo::float32_t>,
                                            holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY>
                                                     ObstacleGeneralList;
    typedef std::function<void(CameraObstacleList&)> ObstacleDetectionCallback;

public:
    using Scalar                       = holo::float32_t;
    using IntrinsicBaseType            = holo::common::details::CameraIntrinsicBaseT<Scalar>;
    using IntrinsicBaseTypePtr         = std::shared_ptr<IntrinsicBaseType>;
    using FisheyeIntrinsicType         = holo::common::details::FisheyeIntrinsicT<Scalar>;
    using PinholeIntrinsicType         = holo::common::details::PinholeIntrinsicT<Scalar>;
    using OmnidirectionalIntrinsicType = holo::common::details::OmnidirectionalIntrinsicT<Scalar>;
    using CameraTrackingAlgorithmType  = CameraTrackingAlgorithmT<Scalar>;
    using TrackingAlgorithmPtr         = std::shared_ptr<CameraTrackingAlgorithmType>;
    using TrackingAlgorithmType        = CameraTrackingAlgorithmT<Scalar>;

    using CameraDetectedObjectType    = BoxObjectT<Scalar, 8U>;
    using CameraDetectedObjectPtr     = std::shared_ptr<CameraDetectedObjectType>;
    using CameraDetectedObjectList    = std::list<CameraDetectedObjectPtr>;
    using CameraDetectedObjectListMap = std::unordered_map<std::string, CameraDetectedObjectList>;

    using ObstacleVisionType = holo::obstacle::ObstacleVisionT<Scalar>;
    using ObstacleVisionPtr  = std::shared_ptr<holo::obstacle::ObstacleVisionT<Scalar>>;

    using OdometryType          = holo::common::Odometryf;
    using OdometryPtr           = std::shared_ptr<holo::common::Odometryf>;
    using Obstacle3DSmootherPtr = std::shared_ptr<Obstacle3DSmoother>;

    using Box2Type = Box2DT<Scalar>;
    using Box3Type = Box3DT<Scalar>;

    typedef std::vector<std::vector<cv::Point>> CV_ContoursT;
    typedef std::vector<cv::Vec4i>              CV_ContoursHierarchyT;

    typedef typename holo::common::AutoFreespace<holo::geometry::Point3f> FreespaceType;
    typedef std::function<void(FreespaceType&)>                           FreespaceCallback;

public:
    DetPostProcess(Parameters::Ptr parameters);

    void SetDetCallback(ObstacleDetectionCallback det_callback);

    bool_t InFrustum(const std::string camera_name, Point3f const& x) const;

    void Get3DPoints(const std::vector<cv::Point3f>& ground_points, holo::Point3T<holo::float32_t>& center,
                     holo::geometry::Box3f& bounding_box3d, holo::uint32_t& category_id);

    CameraDetectedObjectPtr GetObjectWithBBox(float32_t left, float32_t top, float32_t width, float32_t height);

    void SetTimeStamp(holo::common::Timestamp time_stamp);

    void DumpDebugImage(const CameraObstacleList& camera_obstacle_vision_list);

    void SetObstacleSmoother(uint32_t smooth_win_size);

    uint32_t Run(const Srv_Result::Ptr srv_result);

    /**
     * @brief srv view postprocessing: 2d-3d and smoothing
     *
     * @param srv_result    detection results
     * @param odom_ptr  current odometry
     * @return uint32_t
     */
    uint32_t DoWork(const Srv_Result::Ptr srv_result, OdometryPtr const& odom_ptr);

private:
    Parameters::Ptr                                        parameters_;
    uint32_t                                               camera_obs_num_;
    uint32_t                                               det_state_;
    Srv_Result::Ptr                                        srv_result_;
    std::vector<std::pair<std::string, SensorId>>          camera_sensor_id_;
    std::vector<std::string>                               camera_postprocess_vector_;
    std::shared_ptr<IpmApp>                                ipm_ptr_;
    TrackingAlgorithmPtr                                   tracking_algorithm_ptr_;
    holo::common::Timestamp                                time_stamp_;
    CameraObstacleList                                     camera_obstacle_vision_list_;
    ObstacleDetectionCallback                              detection_callback_;
    std::unordered_map<std::string, Obstacle3DSmootherPtr> map_camera_to_obstacle_smooth_ptr_;  // map from camera name
                                                                                                // to obstacle smoother

    // width, height, depth
    std::vector<std::vector<float32_t>> prior_3dbox_list{
        {1.8, 1.5, 4.8}, {2.5, 3.0, 8.0}, {2.5, 3.0, 8.0}, {1.0, 1.4, 3.0},
        {0.5, 1.0, 2.0}, {0.5, 1.0, 2.0}, {0.5, 1.6, 0.5}, {0.5, 1.5, 2.0},
    };
    boost::bimap<std::string, holo::common::VehicleLocation::Plane> name_location_;

    uint32_t broadcastObstacleList();

    void convertBboxList(const std::vector<std::list<holo::perception::BoxObjectf>>& detection_obs_results,
                         std::vector<ImageBBoxList>&                                 image_bbox_list);

    void convertDetectionObject(const std::vector<std::list<holo::perception::BoxObjectf>>& detection_obs_results,
                                const std::vector<std::string>&                             camera_names,
                                CameraDetectedObjectListMap&                                det_obj_list_map);

    void convertObjectTo3D(CameraDetectedObjectList& det_obj_list, const std::string& camera_name,
                           OdometryPtr const& odom, CameraDetectedObjectList& det_obj_original_list);

    void convertKeypointsTo3DBox(const CameraDetectedObjectPtr& det_obj, const std::string& camera_name,
                                 holo::Point3T<holo::float32_t>& center, holo::geometry::Box3f& bounding_box3d);

    ObstacleVisionPtr convertToObstacleVisionObj(CameraDetectedObjectPtr& det_obj, const std::string& camera_name);

    holo::common::SensorId getSensorIdByCameraName(std::string const& camera_name);

    bool_t fetchDetectedObject(CameraDetectedObjectListMap& det_obj_list_map);

    /**
     * @brief save detected object list to txt file
     *
     * @param camera_name
     * @param det_obj_list, detected object list
     */
    void saveToTxt(std::string const& res_filepath, CameraDetectedObjectList const& det_obj_list,
                   std::string const& debug_num) const;
};

}  // namespace perception
}  // namespace holo
#endif
