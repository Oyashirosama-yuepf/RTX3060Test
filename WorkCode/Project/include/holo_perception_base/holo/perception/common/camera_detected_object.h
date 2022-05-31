/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_detected_object.h
 * @brief This header file defines object detected by camera.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2019-12-03"
 */

#ifndef HOLO_PERCEPTION_COMMON_CAMERA_DETECTED_OBJECT_H_
#define HOLO_PERCEPTION_COMMON_CAMERA_DETECTED_OBJECT_H_

#include <vector>

#include <holo/geometry/box2.h>
#include <holo/geometry/box3.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/common/detected_object.h>
#include <holo/vision/keypoint2.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup common
 *
 * @{
 */

/**
 * @brief define camera object
 * @deprecated This class will be deprecated. This class will be replaced with BoxObjectT, which
 * is a more general type.
 *
 * @tparam T data type of boxes points and vectors
 */
template <typename T>
class CameraDetectedObjectT : public DetectedObjectT<T>
{
public:
    using Scalar         = T;
    using Box2Type       = holo::geometry::details::Box2T<Scalar>;
    using Box3Type       = holo::geometry::details::Box3T<Scalar>;
    using Keypoint2Type  = holo::vision::KeyPoint2T<Scalar>;
    using KeypointVector = std::vector<Keypoint2Type>;
    using typename DetectedObjectT<T>::IdType;
    using typename DetectedObjectT<T>::Point3Type;
    using typename DetectedObjectT<T>::Vector3Type;
    using Timestamp      = holo::common::details::Timestamp;
    using Classification = holo::common::Classification;

    /**
     * @brief Default Constructor
     */
    CameraDetectedObjectT() : DetectedObjectT<Scalar>(), box2_(), box3_(), keypoint_vector_()
    {
    }

    /**
     * @brief Constructor
     *
     * @param box2 2d bounding box of the object
     * @param box3 3d target size of the object
     * @param confidence object existence confidence
     * @param classification object classification
     * @param id object track id
     * @param keypoint_vector array of object keypoints
     * @param position object position in 3d space
     * @param velocity object relative velocity in 3d space
     * @param timestamp timestamp of the object
     */
    CameraDetectedObjectT(const Scalar confidence, const Classification& classification, const IdType id,
                          const Point3Type& position, const Vector3Type& velocity, const Timestamp& timestamp,
                          const Box2Type& box2, const Box3Type& box3, const KeypointVector& keypoint_vector);

    /**
     * @brief copy constructor with params
     *
     * @param camera_detected_object camera detected object
     */
    CameraDetectedObjectT(const CameraDetectedObjectT& camera_detected_object) noexcept;

    /**
     * @brief move constructor with params
     *
     * @param camera_detected_object camera detected object
     */
    CameraDetectedObjectT(CameraDetectedObjectT&& camera_detected_object) noexcept;

    /**
     * @brief Destroy the CameraDetectedObjectT
     */
    virtual ~CameraDetectedObjectT();

    /**
     * @brief Copy assign
     *
     * @param other the other CameraDetectedObjectT
     *
     * @return Assigened CameraDetectedObjectT
     */
    CameraDetectedObjectT<Scalar>& operator=(const CameraDetectedObjectT<Scalar>& other);

    /**
     * @brief Move assign
     *
     * @param other the other CameraDetectedObjectT
     *
     * @return Assigned CameraDetectedObjectT
     */
    CameraDetectedObjectT<Scalar>& operator=(CameraDetectedObjectT<Scalar>&& other) noexcept;

    /**
     * @brief Set 2d bounding box
     *
     * @param box2 2d bounding box on image
     */
    void SetBox2(const Box2Type& box2)
    {
        box2_ = box2;
    }

    /**
     * @brief Set 3d size
     *
     * @param box3 3d bouding box, need width, height, and depth
     */
    void SetBox3(const Box3Type& box3)
    {
        box3_ = box3;
    }

    /**
     * @brief Set array of keypoints
     *
     * @param keypoint_vector keypoint array
     */
    void SetKeypointVector(const KeypointVector& keypoint_vector)
    {
        keypoint_vector_ = keypoint_vector;
    }

    /**
     * @brief Get 2d bounding box
     *
     * @return 2d bounding box on image
     */
    const Box2Type& GetBox2() const noexcept
    {
        return box2_;
    }

    /**
     * @brief Get 3d size, including width, height, depth
     *
     * @return object 3d size
     */
    const Box3Type& GetBox3() const noexcept
    {
        return box3_;
    }

    /**
     * @brief Get keypoint array
     *
     * @return keypoint array
     */
    const KeypointVector& GetKeypointVector() const noexcept
    {
        return keypoint_vector_;
    }

private:
    Box2Type       box2_;             ///< object 2d bounding box on image
    Box3Type       box3_;             ///< object 3d size
    KeypointVector keypoint_vector_;  ///< object keypoints
};

using CameraDetectedObjectf       = CameraDetectedObjectT<float32_t>;
using CameraDetectedObjectd       = CameraDetectedObjectT<float64_t>;
using CameraDetectedObjectVectorf = std::vector<CameraDetectedObjectf>;
using CameraDetectedObjectVectord = std::vector<CameraDetectedObjectd>;

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_COMMON_CAMERA_DETECTED_OBJECT_H_
