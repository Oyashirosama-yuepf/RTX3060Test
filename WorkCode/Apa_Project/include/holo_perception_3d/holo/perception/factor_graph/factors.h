/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file factors.h
 * @brief This header file defines the factors type.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2021-06-01"
 */

#ifndef HOLO_PERCEPTION_3D_FACTOR_GRAPH_FACTORS_H_
#define HOLO_PERCEPTION_3D_FACTOR_GRAPH_FACTORS_H_

#include <holo/perception/factor_graph/advanced_types.h>
#include <cmath>

namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class YawSmoothFactor : public gtsam::NoiseModelFactor2<Vector1, Vector1>
{
public:
    using Base = gtsam::NoiseModelFactor2<Vector1, Vector1>;

    /**
     * @brief Construct a new Yaw Smooth Factor object
     *
     * @param noiseModel
     * @param y1, key of yaw at t1
     * @param y2, key of yaw at t2
     * @param dt, duration between t1 and t2
     */
    YawSmoothFactor(SharedNoiseModel const& noiseModel, Key y1, Key y2, Scalar dt);

    /**
     * @brief Destroy the Yaw Smooth Factor object
     *
     */
    virtual ~YawSmoothFactor();

    /**
     * @brief error = cos(yaw1)*sin(yaw2) - sin(yaw1)*cos(yaw2)
     *
     * @param y1, yaw at t1
     * @param y2, yaw at t2
     * @param Hy1, Jacobian matrix about yaw1
     * @param Hy2, Jacobian matrix about yaw2
     * @return Vector
     */
    virtual Vector evaluateError(Vector1 const& y1, Vector1 const& y2, boost::optional<Matrix&> Hy1 = boost::none,
                                 boost::optional<Matrix&> Hy2 = boost::none) const override;

private:
    Scalar dt_;  ///< delta time between two position
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DimensionSmoothFactor : public gtsam::NoiseModelFactor2<Vector3, Vector3>
{
public:
    using Base = gtsam::NoiseModelFactor2<Vector3, Vector3>;

    /**
     * @brief Construct a new Dimension Smooth Factor object
     *
     * @param noiseModel
     * @param d1, key of dimension at t1
     * @param d2, key of dimension at t2
     * @param dt, duration between t1 and t2
     */
    DimensionSmoothFactor(SharedNoiseModel const& noiseModel, Key d1, Key d2, Scalar const dt);

    /**
     * @brief Destroy the Dimension Smooth Factor object
     *
     */
    virtual ~DimensionSmoothFactor();

    /**
     * @brief error = (d2 - d1) / dt
     *
     * @param d1, dimension at t1
     * @param d2, dimension at t2
     * @param Hd1, Jacobian matrix about d1
     * @param Hd2, Jacobian matrix about d2
     * @return Vector
     */
    virtual Vector evaluateError(Vector3 const& d1, Vector3 const& d2, boost::optional<Matrix&> Hd1 = boost::none,
                                 boost::optional<Matrix&> Hd2 = boost::none) const override;

private:
    Scalar dt_;  ///< delta time between two position
};

class MotionFactor : public gtsam::NoiseModelFactor3<Point3, Vector3, Point3>
{
public:
    using Base = gtsam::NoiseModelFactor3<Point3, Vector3, Point3>;

    /**
     * @brief Construct a new Motion Factor object
     *
     * @param noiseModel
     * @param x1, key of position at t1
     * @param v2, key of velocity at t1
     * @param x2, key of position at t2
     * @param dt, duration between t1 and t2
     */
    MotionFactor(SharedNoiseModel const& noiseModel, Key x1, Key v2, Key x2, Scalar const dt);

    /**
     * @brief Destroy the Motion Factor object
     *
     */
    virtual ~MotionFactor();

    /**
     * @brief error = p2 - p1 - v2 * dt
     *
     * @param p1, position at t1
     * @param v2, velocity at t2
     * @param p2, position at t2
     * @param Hp1, Jacobian matrix about p1
     * @param Hv2, Jacobian matrix about v2
     * @param Hp2, Jacobian matrix about p2
     * @return Vector
     */
    virtual Vector evaluateError(Point3 const& p1, Vector3 const& v2, Point3 const& p2,
                                 boost::optional<Matrix&> Hp1 = boost::none, boost::optional<Matrix&> Hv2 = boost::none,
                                 boost::optional<Matrix&> Hp2 = boost::none) const override;

private:
    Scalar dt_;  ///< delta time between two position
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StaticMotionFactor : public gtsam::NoiseModelFactor2<Point3, Point3>
{
public:
    using Base = gtsam::NoiseModelFactor2<Point3, Point3>;

    StaticMotionFactor(SharedNoiseModel const& noiseModel, Key x1, Key x2);

    virtual ~StaticMotionFactor();

    virtual Vector evaluateError(Point3 const& p1, Point3 const& p2, boost::optional<Matrix&> Hp1 = boost::none,
                                 boost::optional<Matrix&> Hp2 = boost::none) const override;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class VelocitySmoothFactor : public gtsam::NoiseModelFactor2<Vector3, Vector3>
{
public:
    using Base = gtsam::NoiseModelFactor2<Vector3, Vector3>;

    /**
     * @brief Construct a new Velocity Smooth Factor object
     *
     * @param noiseModel
     * @param v1, key of velocity at t1
     * @param v2, key of velocity at t2
     * @param dt, duration between t1 and t2
     */
    VelocitySmoothFactor(SharedNoiseModel const& noiseModel, Key v1, Key v2, Scalar const dt);

    /**
     * @brief Destroy the Velocity Smooth Factor object
     *
     */
    virtual ~VelocitySmoothFactor();

    /**
     * @brief acc = (v2 - v1) / dt, acc should be small
     *
     * @param v1, velocity at t1
     * @param v2, velocity at t2
     * @param Hv1, Jacobian matrix about v1
     * @param Hv2, Jacobian matrix about v2
     * @return Vector
     */
    virtual Vector evaluateError(Vector3 const& v1, Vector3 const& v2, boost::optional<Matrix&> Hv1 = boost::none,
                                 boost::optional<Matrix&> Hv2 = boost::none) const override;

private:
    Scalar dt_;  ///< delta time between two position
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ProjectionFactor : public gtsam::NoiseModelFactor1<Point3>
{
public:
    using Base = gtsam::NoiseModelFactor1<Point3>;

    /**
     * @brief Construct a new Projection Factor object
     *
     * @param noiseModel
     * @param key1, key of position
     * @param img_pt, predicted center point on image
     * @param K, intrisic params of camera
     */
    ProjectionFactor(SharedNoiseModel const& noiseModel, Key key1, Point2 const& img_pt, boost::shared_ptr<Cal3_S2> K);

    /**
     * @brief Destroy the Projection Factor object
     *
     */
    virtual ~ProjectionFactor();

    /**
     * @brief error = unprojected(p) - img_pt
     *
     * @param p, position
     * @param H, Jacobian about p
     * @return Vector
     */
    virtual Vector evaluateError(Point3 const& p, boost::optional<Matrix&> H = boost::none) const override;

private:
    Point2                     img_pt_;  ///< center point on image plane
    boost::shared_ptr<Cal3_S2> K_;       ///< intrinsic param of camera
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class VertexProjectionFactor : public gtsam::NoiseModelFactor1<Point3>
{
public:
    using Base = gtsam::NoiseModelFactor1<Point3>;

    /**
     * @brief Construct a new Vertex Projection Factor object
     *
     * @param noiseModel
     * @param key1, key of position
     * @param index, index of vertex points, in [0, 7]
     * @param img_pt, corresponding image point of the vertex
     * @param axis, corresponded axis
     * @param rx, angle around x axis in radian
     * @param ry, angle around y axis in radian
     * @param rz, angle around z axis in raidan
     * @param K, camera intrinsic
     * @param dimension, dimension of the object
     */
    VertexProjectionFactor(SharedNoiseModel const& noiseModel, Key key1, uint32_t const index, Point2 const& img_pt,
                           Correspondence3d2d::Axis const axis, Scalar const rx, Scalar const ry, Scalar const rz,
                           boost::shared_ptr<Cal3_S2> K, Vector const& dimension);

    /**
     * @brief Destroy the Vertex Projection Factor object
     *
     */
    virtual ~VertexProjectionFactor();

    /**
     * @brief error = img_pt[axis] - unproject(vertex)[axis]
     *
     * @param position, object's position
     * @param Hp, Jacobian matrix about position
     * @return Vector
     */
    virtual Vector evaluateError(Point3 const& position, boost::optional<Matrix&> Hp = boost::none) const override;

    /**
     * @brief Get the Vertex object
     *
     * @param index
     * @param dimension object dimension [w, h, l]
     * @return Point3 specified vertex coordinate
     */
    static Point3 GetVertex(uint32_t const index, Vector3 const& dimension);

private:
    uint32_t                   index_;      ///< index of the vertex
    Point2                     img_pt_;     ///< corresponded image point
    Correspondence3d2d::Axis   axis_;       ///< x or y direction
    Rot3                       R_;          ///< rotaion of box in camera coordinate
    boost::shared_ptr<Cal3_S2> K_;          ///< camera intrinsic
    Vector3                    dimension_;  ///< object dimension [w, h, l]
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class KeypointProjectionFactor : public gtsam::NoiseModelFactor1<Point3>
{
public:
    using Base = gtsam::NoiseModelFactor1<Point3>;

    /**
     * @brief Construct a new Keypoint Projection Factor object
     *
     * @param noiseModel
     * @param key1, key of position
     * @param kp_3d, keypoint 3d position in camera coordinate
     * @param vertex_index, the two endpoint indexes of the corresponding edge
     * @param rx, angle around x axis in radian
     * @param ry, angle around y axis in radian
     * @param rz, angle around z axis in radian
     * @param K, camera intrinsic
     * @param dimension, dimension of the object [w, h, l]
     */
    KeypointProjectionFactor(SharedNoiseModel const& noiseModel, Key key1, Point3 const& kp_3d,
                             std::pair<uint32_t, uint32_t> const vertex_index, Scalar const rx, Scalar const ry,
                             Scalar const rz, boost::shared_ptr<Cal3_S2> K, Vector const& dimension);

    /**
     * @brief Destroy the Keypoint Projection Factor object
     *
     */
    virtual ~KeypointProjectionFactor();

    /**
     * @brief error is distance from kp_3d to the corresponding edge
     *
     * @param position, object's position
     * @param Hp, Jacobian matrix about position
     * @return Vector
     */
    virtual Vector evaluateError(Point3 const& position, boost::optional<Matrix&> Hp = boost::none) const override;

private:
    Point3                        kp_3d_;         ///< keypoint 3d position in camera
    std::pair<uint32_t, uint32_t> vertex_index_;  ///< indexs of the vertex
    Rot3                          R_;             ///< rotation of box in camera coordinate
    boost::shared_ptr<Cal3_S2>    K_;             ///< camera intrinsic
    Vector3                       dimension_;     ///< object dimension [w, h, l]
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IPMFactor : public gtsam::NoiseModelFactor1<Point3>
{
public:
    using Base = gtsam::NoiseModelFactor1<Point3>;

    /**
     * @brief Construct a new IPMFactor object
     *
     * @param noiseModel
     * @param key1, key of position
     * @param index, index of bottom vertex points, in set[0, 1, 4, 5]
     * @param rx, angle around x axis in radian
     * @param ry, angle around y axis in radian
     * @param rz, angle around z axis in radian
     * @param K, camera intrinsic
     * @param dimension, dimension of the object [w, h, l]
     * @param camH, camera height from ground
     */
    IPMFactor(SharedNoiseModel const& noiseModel, Key key1, uint32_t index, Scalar const rx, Scalar const ry,
              Scalar const rz, boost::shared_ptr<Cal3_S2> K, Vector const& dimension, Scalar camH);

    /**
     * @brief Destroy the IPMFactor object
     *
     */
    virtual ~IPMFactor();

    /**
     * @brief error = bottom_vertex.y() - camH
     *
     * @param position, object's position
     * @param Hp, Jacobian matrix about position
     * @return Vector
     */
    virtual Vector evaluateError(Point3 const& position, boost::optional<Matrix&> Hp = boost::none) const override;

private:
    uint32_t                   index_;      ///< index of the vertex
    Rot3                       R_;          ///< rotation of box in camera coordinate
    boost::shared_ptr<Cal3_S2> K_;          ///< camera intrinsic
    Vector3                    dimension_;  ///< object dimension [w, h, l]
    Scalar                     camH_;       ///< cam height from ground
};

}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_3D_FACTORS_H_
