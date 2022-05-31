/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_group.h
 * @brief This header file defines utility for load camera parameters and projection.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-05"
 */

#ifndef HOLO_PERCEPTION_UTILS_CAMERA_GROUP_H_
#define HOLO_PERCEPTION_UTILS_CAMERA_GROUP_H_

#include <holo/common/camera_fisheye.h>
#include <holo/geometry/box3.h>
#include <holo/geometry/pose3.h>
#include <holo/io/common/extrinsic.h>
#include <holo/io/common/intrinsic.h>
#include <holo/log/hololog.h>
#include <holo/perception/math/jet.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo/utils/yaml_loader.h>

#include <fstream>
#include <string>
#include <unordered_map>

namespace holo
{
namespace perception
{
/**
 * @brief camera group of 7v
 *
 */
class CameraGroup
{
public:
    using Scalar  = float32_t;
    using Scalar2 = std::array<Scalar, 2U>;
    using Scalar3 = std::array<Scalar, 3U>;
    using Scalar4 = std::array<Scalar, 4U>;
    using JetType = Jet<Scalar, 7>;

    using IntrinsicPtr              = std::shared_ptr<void>;
    using FisheyeIntrinsicf         = common::FisheyeIntrinsicf;
    using OmnidirectionalIntrinsicf = common::OmnidirectionalIntrinsicf;

    using SensorId   = common::SensorId;
    using Timestamp  = common::Timestamp;
    using Vector3f   = numerics::Vector3f;
    using Matrix3f   = numerics::Matrix3f;
    using Box3f      = geometry::Box3f;
    using Point2f    = geometry::Point2f;
    using Point3f    = geometry::Point3f;
    using Pose3f     = geometry::Pose3f;
    using Plane      = Scalar3;
    using Frustum    = std::array<Plane, 4U>;
    using FrustumMap = std::unordered_map<std::string, Frustum>;

    using CameraParam  = std::pair<IntrinsicPtr, Pose3f>;
    using CameraParams = std::unordered_map<std::string, CameraParam>;

    /**
     * @brief sensor id array
     * @details
     * 0: front center camera FishEye
     * 1: front center srv camera OCAM
     * 2: front left srv camera OCAM
     * 3: front right srv camera OCAM
     * 4: rear center srv camera OCAM
     */
    std::array<uint32_t, 5U> SID = {
        {51381647, 51577231, 51577672, 51578056, 51577487,}
    };

    /**
     * @brief setup
     *
     * @param cfg_file config file
     */
    void Setup(std::string const& cfg_file);

    /**
     * @brief load sensor id array
     *
     * @param cfg_file config file
     * @return std::array<uint32_t, 7U> sensor id array
     */
    static std::array<uint32_t, 5U>
    LoadSensorId(std::string const& cfg_file = "holo_perception_pilot/lib_config/sensor_id_config.yaml");

    bool_t HaveSensorId(uint32_t sensor_id) const
    {
        return SID.end() != std::find(SID.begin(), SID.end(), sensor_id);
    }

    /**
     * @brief Get the Camera Params By Sensorid object
     *
     * @param sid sensor id
     * @return CameraParam camera param pair (intrinsic , extrinsic)
     */
    CameraParam GetCameraParamsBySensorid(SensorId sid);

    /**
     * @brief Get the Frustum By Sensorid object
     *
     * @param sid sensor id
     * @return Frustum frustum
     */
    Frustum GetFrustumBySensorid(SensorId sid);

    /**
     * @brief project obstacle to a camera
     *
     * @tparam ScalarType scalar
     * @tparam N variable number
     * @param x position x
     * @param y position y
     * @param z position z
     * @param length length
     * @param width width
     * @param height height
     * @param yaw yaw
     * @param sid sensor id
     * @param result_box2 box2 in image
     * @return bool_t true if project success
     */
    template <typename ScalarType, int N>
    bool_t ProjectToCamera(Jet<ScalarType, N> const& x, Jet<ScalarType, N> const& y, Jet<ScalarType, N> const& z,
                           Jet<ScalarType, N> const& length, Jet<ScalarType, N> const& width,
                           Jet<ScalarType, N> const& height, Jet<ScalarType, N> const& yaw, SensorId sid,
                           std::array<Jet<ScalarType, N>, 4U>& result_box2);

    /**
     * @brief project obstacle to a camera
     *
     * @param x position x
     * @param y position y
     * @param z position z
     * @param length length
     * @param width width
     * @param height height
     * @param yaw yaw
     * @param sid sensor id
     * @param result_box2 box2 in image
     * @return bool_t true if project succes
     */
    bool_t ProjectToCamera(Scalar x, Scalar y, Scalar z, Scalar length, Scalar width, Scalar height, Scalar yaw,
                           SensorId sid, Scalar4& result_box2);

    /**
     * @brief project box3 to camera
     *
     * @param box3 box3d
     * @param sid sensor id
     * @param result_box2 box2d in image
     * @return bool_t true if project success
     */
    bool_t ProjectToCamera(Box3f const& box3, SensorId sid, Scalar4& result_box2);

private:
    /**
     * @brief load intrinsic
     *
     * @param intrinsic_file intrinsic file
     * @return FisheyeIntrinsicf intrinsic
     */
    bool_t loadCameraIntrinsic(std::string const& intrinsic_file, FisheyeIntrinsicf& intrinsic);

    /**
     * @brief load intrinsic
     *
     * @param intrinsic_file intrinsic file
     * @return OmnidirectionalIntrinsicf intrinsic
     */
    bool_t loadCameraIntrinsic(std::string const& intrinsic_file, OmnidirectionalIntrinsicf& intrinsic);

    /**
     * @brief Get the Plane object
     * @details plane of frustum, Ax + By + Cz = 0
     *
     * @param a point
     * @param b point
     * @return Scalar3 plane [A, B, C]
     */
    Scalar3 getPlane(Point3f const& a, Point3f const& b);

    /**
     * @brief Get the Frustrum object
     *
     * @param intrinsic intrinsic
     * @return Frustum frutum represented by four plane
     */
    Frustum getFrustrum(FisheyeIntrinsicf const& intrinsic);

    /**
     * @brief Get the Frustrum object
     *
     * @param intrinsic intrinsic
     * @return Frustum frutum represented by four plane
     */
    Frustum getFrustrum(OmnidirectionalIntrinsicf const& intrinsic);

    /**
     * @brief if the point is inside frustum
     *
     * @param x point
     * @param frustum frustum
     * @return bool_t true if its in side frustum
     */
    bool_t inFrustum(Point3f const& x, Frustum const& frustum);

    /**
     * @brief generate a box3d
     *
     * @tparam ScalarType scalar
     * @tparam N variable number
     * @param x position x
     * @param y position y
     * @param z position z
     * @param length length
     * @param width width
     * @param height height
     * @param yaw yaw
     * @return std::vector<std::array<Jet<ScalarType, N>, 3U>> 8 corner points (in jets)
     */
    template <typename ScalarType, int N>
    std::vector<std::array<Jet<ScalarType, N>, 3U>>
    genBox3d(Jet<ScalarType, N> const& x, Jet<ScalarType, N> const& y, Jet<ScalarType, N> const& z,
             Jet<ScalarType, N> const& length, Jet<ScalarType, N> const& width, Jet<ScalarType, N> const& height,
             Jet<ScalarType, N> const& yaw);

    /**
     * @brief project a 3d jpoint (in jets) to camera
     *
     * @tparam ScalarType scalar
     * @tparam N variable number
     * @param intrinsic intrinsic
     * @param p3 3d point
     * @param u u coordinate in image
     * @param v v coordinate in image
     * @return bool_t true if project success
     */
    template <typename ScalarType, int N>
    bool_t project(FisheyeIntrinsicf const& intrinsic, std::array<Jet<ScalarType, N>, 3U> const& p3,
                   Jet<ScalarType, N>& u, Jet<ScalarType, N>& v);

    /**
     * @brief project a 3d jpoint (in jets) to camera
     *
     * @tparam ScalarType scalar
     * @tparam N variable number
     * @param intrinsic intrinsic
     * @param p3 3d point
     * @param u u coordinate in image
     * @param v v coordinate in image
     * @return bool_t true if project success
     */
    template <typename ScalarType, int N>
    bool_t project(OmnidirectionalIntrinsicf const& intrinsic, std::array<Jet<ScalarType, N>, 3U> const& p3,
                   Jet<ScalarType, N>& u, Jet<ScalarType, N>& v);

    /**
     * @brief compute intersection of a line segment to plane
     *
     * @tparam ScalarType scalar
     * @tparam N variable number
     * @param x point
     * @param y point
     * @param plane plane
     * @param z intersection point
     * @return bool_t true if have a intersection
     */
    template <typename ScalarType, int N>
    bool_t intersection(std::array<Jet<ScalarType, N>, 3U> const& x, std::array<Jet<ScalarType, N>, 3U> const& y,
                        Plane const& plane, std::array<Jet<ScalarType, N>, 3U>& z);

    /**
     * @brief add intersection point to ret
     *
     * @tparam ScalarType scalar
     * @tparam N variable number
     * @param x point
     * @param y point
     * @param frustum frustum
     * @param ret point list
     */
    template <typename ScalarType, int N>
    void addIntersection(std::array<Jet<ScalarType, N>, 3U> const& x, std::array<Jet<ScalarType, N>, 3U> const& y,
                         Frustum const& frustum, std::vector<std::array<Jet<ScalarType, N>, 3U>>& ret);

    /**
     * @brief generate a box3d
     *
     * @param x position x
     * @param y position y
     * @param z position z
     * @param length length
     * @param width width
     * @param height height
     * @param yaw yaw
     * @return std::vector<Point3f> corner points of box3d
     */
    std::vector<Point3f> GenBox3d(Scalar x, Scalar y, Scalar z, Scalar length, Scalar width, Scalar height, Scalar yaw);

    /**
     * @brief compute intersection of a line segment to plane
     *
     * @param x position x
     * @param y position y
     * @param plane plane
     * @param res intersection point
     * @return bool_t true if have a intersection
     */
    bool_t intersection(Point3f const& x, Point3f const& y, Plane const& plane, Point3f& res);

    /**
     * @brief add intersection point to ret
     *
     * @param x point
     * @param y point
     * @param frustum frustum
     * @param ret point list
     */
    void addIntersection(Point3f const& x, Point3f const& y, Frustum const& frustum, std::vector<Point3f>& ret);

private:
    std::vector<std::string> camera_names_;
    CameraParams             camera_params_;
    FrustumMap               camera_frustum_;
};

}  // namespace perception
}  // namespace holo

#endif
