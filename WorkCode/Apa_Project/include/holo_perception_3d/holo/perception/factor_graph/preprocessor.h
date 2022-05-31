/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file preprocessor.h
 * @brief This header file defines pre-process for the measurements.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2021-06-01"
 */

#ifndef HOLO_PERCEPTION_3D_FACTOR_GRAPH_PREPROCESSOR_H_
#define HOLO_PERCEPTION_3D_FACTOR_GRAPH_PREPROCESSOR_H_

#include <algorithm>
#include <eigen3/Eigen/Dense>

#include <holo/common/camera_fisheye.h>
#include <holo/container/vector.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/io/common/intrinsic.h>
#include <holo/numerics/matrix.h>
#include <holo/perception/common/box3d.h>
#include <holo/perception/common/box_object.h>
#include <holo/perception/factor_graph/advanced_types.h>
#include <holo/perception/factor_graph/factors.h>
#include <holo/perception/space_convertor/ipm_convertor.h>
#include <holo/utils/yaml.h>
#include <holo/utils/yaml_loader.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup factor_graph
 *
 */

/**
 * @brief This class defines preprocess for the object's measurement
 *
 */
class Preprocessor
{
public:
    using Object       = BoxObjectT<Scalar, 128U>;
    using KeyPointType = KeyPointT<Scalar>;
    using Box2Type     = Box2DT<Scalar>;
    using Timestamp    = holo::common::Timestamp;
    using Rot3Type     = holo::geometry::Rot3T<Scalar>;
    using Pose3Type    = holo::geometry::Pose3T<Scalar>;
    using Point2Type   = holo::geometry::Point2T<Scalar>;
    using Point3Type   = holo::geometry::Point3T<Scalar>;

    /**
     * @brief Parameters for preprocess
     *
     */
    struct Parameters
    {
        boost::shared_ptr<Cal3_S2>              K;
        std::shared_ptr<CameraFisheyeT<Scalar>> camera_model;

        Scalar width;
        Scalar height;

        Pose3Type bodyTcam;
        Scalar    bodyH;

        Parameters(std::string const& intrinsic_file, Pose3Type const& _bodyTcam, Scalar _bodyH)
        {
            holo::common::FisheyeIntrinsicT<Scalar> cam_intrinsic;
            try
            {
                holo::yaml::Node cam_node = holo::yaml::LoadFile(holo::GetConfigFileAbsolutePath(intrinsic_file));
                bool_t           flag =
                    holo::utils::YamlLoader<holo::common::FisheyeIntrinsicT<Scalar>>::decode(cam_node, cam_intrinsic);
                if (!flag)
                {
                    cam_intrinsic.SetSensorId(cam_node["sensor_id"].as<uint32_t>());
                    cam_intrinsic.SetDimension(cam_node["width"].as<uint32_t>(), cam_node["height"].as<uint32_t>());
                    cam_intrinsic.SetPrinciplePoint(cam_node["cx"].as<Scalar>(), cam_node["cy"].as<Scalar>());
                    cam_intrinsic.SetSkew(cam_node["skew"].as<Scalar>());
                    cam_intrinsic.SetFocalLength(cam_node["fx"].as<Scalar>(), cam_node["fy"].as<Scalar>());
                    cam_intrinsic.SetDistortionParameter(cam_node["k1"].as<Scalar>(), cam_node["k2"].as<Scalar>(),
                                                         cam_node["k3"].as<Scalar>(), cam_node["k4"].as<Scalar>());
                }

                width                                  = cam_intrinsic.GetWidth();
                height                                 = cam_intrinsic.GetHeight();
                holo::numerics::Matrix3T<Scalar> camK  = cam_intrinsic.GetK();
                holo::numerics::Vector4T<Scalar> camD4 = cam_intrinsic.GetD();
                holo::numerics::Vector8T<Scalar> camD8(camD4[0U], camD4[1U], 0.0, 0.0, camD4[2U], camD4[3U], 0.0, 0.0);
                camera_model = std::make_shared<CameraFisheyeT<Scalar>>(width, height, camK, camD8);
                K = boost::make_shared<Cal3_S2>(camK(0U, 0U), camK(1U, 1U), camK(0U, 1U), camK(0U, 2U), camK(1U, 2U));
            }
            catch (const std::exception& e)
            {
                LOG(INFO) << "construct preprocessor params failed from " << intrinsic_file << e.what();
            }
            bodyTcam = _bodyTcam;
            bodyH    = _bodyH;
        }
    };

    /**
     * @brief Construct a new Preprocessor object
     *
     * @param parameters
     */
    Preprocessor(Parameters const& parameters);

    /**
     * @brief process the center point and vertex
     *
     * @param new_timestamp
     * @param new_object
     * @param old_state
     * @param ego_speed ego car speed
     * @return boost::optional<FactorMeasurements>
     */
    boost::optional<FactorMeasurements> Run(Timestamp const& new_timestamp, Object const& new_object,
                                            SlidingWindowState const& old_state, float32_t ego_speed) const;

    /**
     * @brief process the prior info: yaw and dimension
     *
     * @param new_timestamp
     * @param new_object
     * @param old_state
     * @param ego_speed ego car speed
     * @return boost::optional<FactorMeasurements>
     */
    boost::optional<FactorMeasurements> RunPrior(Timestamp const& new_timestamp, Object const& new_object,
                                                 SlidingWindowState const& old_state, float32_t ego_speed) const;

    Scalar ReviseYaw(Object const& new_object) const;

private:
    /**
     * @brief Check whether the center point is in box2d
     *
     * @param object
     */
    bool_t checkCenterPoint(Object const& object) const;

    /**
     * @brief Check whether the object is valid
     *
     * @param object
     * @return bool_t
     */
    bool_t checkObjectValid(Object const& object) const;

    /**
     * @brief Distort point on image
     *
     * @param input
     * @return Point2
     */
    Point2 distortPoint(Point2 const& input) const;

    /**
     * @brief Undistort point on image
     *
     * @param input
     * @return Point2
     */
    Point2 undistortPoint(Point2 const& input) const;

    /**
     * @brief Predict the initial state
     *
     * @param new_object
     * @return ObjectState
     */
    ObjectState predictState(Object const& new_object, Point3 const& track_position) const;

    /**
     * @brief Compute the IoU between projected box2 and detected box2
     *
     * @param new_object, detected object
     * @param position, predicted position
     * @param cat_id, category id
     * @return Scalar
     */
    Scalar computeProjectedBox2DIoU(Object const& new_object, Point3 const& position, size_t cat_id) const;

    /**
     * @brief Compute the correspondence between vertex and box2d's edge
     *
     * @param new_object
     * @param predicted_position
     * @return holo::container::Vector<Correspondence3d2d, 4U>
     */
    holo::container::Vector<Correspondence3d2d, 4U> computeCorrespondences(Object const& new_object,
                                                                           Point3 const& predicted_position) const;

    /**
     * @brief select ordered vertice
     *
     * @param object
     * @param predicted_position
     * @return holo::container::Vector<uint32_t, 4U>
     */
    holo::container::Vector<uint32_t, 4U> selectOrderedVertices(Object const& object,
                                                                Point3 const& predicted_position) const;

    /**
     * @brief Check whether target point is in image
     *
     * @param pt, target 2d point
     * @param threshold, edge threshold
     * @return bool_t
     */
    bool_t isOnImage(Point2 const& pt, Scalar const threshold = 10.0) const;

    /**
     * @brief Compute the distance between keypoints and corresponding vertexes
     *
     * @param new_object
     * @param pose
     * @param cat
     * @return Scalar
     */
    Scalar kpToVertexError(Object const& new_object, Pose3 const& pose, std::string const& cat) const;

    /**
     * @brief Check whether the object is truncated
     *
     * @param new_object
     * @return bool_t
     */
    bool_t isTruncated(Object const& new_object) const;

    /**
     * @brief Use IPM to predict the position of object in camera coordinate
     *
     * @param new_object, input
     * @param p_cam, output
     * @return bool_t
     */
    bool_t useIPMEstimate(Object const& new_object, Point3& p_cam) const;

    /**
     * @brief get the keypoint correspondences of the truncated object
     *
     * @param new_object
     * @return holo::container::Vector<std::pair<Point3, std::pair<uint32_t, uint32_t>>, 4U>
     */
    holo::container::Vector<std::pair<Point3, std::pair<uint32_t, uint32_t>>, 4U>
    getKpCorrespondences(Object const& new_object) const;

private:
    Parameters parameters_;
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_3D_FACTOR_GRAPH_PREPROCESSOR_H_
