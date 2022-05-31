/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box_object.h
 * @brief This header file defines detected object with box and keypoints.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2020-09-25"
 */

#ifndef HOLO_PERCEPTION_COMMON_BOX_OBJECT_H_
#define HOLO_PERCEPTION_COMMON_BOX_OBJECT_H_

#include <holo/common/timestamp.h>
#include <holo/container/list.h>
#include <holo/container/vector.h>
#include <holo/numerics/vector.h>
#include <holo/perception/common/box2d.h>
#include <holo/perception/common/box3d.h>
#include <holo/perception/common/classify_info.h>
#include <holo/perception/common/keypoint.h>

namespace holo
{
/**
 * @addtogroup common
 *
 * @{
 */

/**
 * @brief define BoxObject, which contains detected box and keypoints.
 *
 * @tparam T data type, only support float32_t and float64_t now
 * @tparam KeyPointsMaxSize the max_size of keypoints, only support 128U now
 */
namespace perception
{
template <typename T, size_t KeyPointsMaxSize>
class BoxObjectT
{
public:
    using Scalar           = T;
    using IdType           = holo::uint32_t;
    using AgeType          = holo::uint32_t;
    using Point3Type       = holo::geometry::details::Point3T<Scalar>;
    using Vector3Type      = holo::numerics::Vector3T<Scalar>;
    using Box2Type         = holo::perception::Box2DT<Scalar>;
    using Box3Type         = holo::perception::Box3DT<Scalar>;
    using KeyPointType     = holo::perception::KeyPointT<Scalar>;
    using KeyPoint2DVector = holo::container::Vector<KeyPointType, KeyPointsMaxSize>;
    using KeyPoint3DVector = holo::container::Vector<KeyPointType, KeyPointsMaxSize>;
    using Timestamp        = holo::common::details::Timestamp;

    /**
     * @brief Default constructor
     *
     */
    BoxObjectT() noexcept
      : classify_info_()
      , classify_info2_()
      , object_id_(0U)
      , age_(0U)
      , position_(Point3Type::Zero())
      , velocity_(Vector3Type::Zero())
      , box2_()
      , box3_()
      , keypoint2d_vector_()
      , keypoint3d_vector_()
      , timestamp_()
      , occluded_ratio_(0.0f)
      , filtered_(false)
    {
    }

    /**
     * @brief Constructor with params
     *
     * @param classify_info, category_id and confidence of the object
     * @param classify_info2, category2_id and confidence of the object(reserved for additional classify attribute)
     * @param id, object track id
     * @param position, object position in 3d space
     * @param velocity, object velocity in 3d space
     * @param box2, 2d bounding box of the object, [x, y, w, h]
     * @param box3, 3d bounding box of the object
     * @param keypoint_vector, object's keypoints vector
     * @param timestamp, timestamp
     */
    BoxObjectT(ClassifyInfo const& classify_info, ClassifyInfo const& classify_info2, IdType const id, AgeType const age,
               Point3Type const& position, Vector3Type const& velocity, Box2Type const& box2, Box3Type const& box3,
               KeyPoint2DVector const& keypoint2d_vector, KeyPoint3DVector const& keypoint3d_vector,
               Timestamp const& timestamp, float32_t occluded_ratio = 0.0f, bool_t filtered = false) noexcept;

    /**
     * @brief copy contructor
     *
     * @param box_object, another box_object
     */
    BoxObjectT(BoxObjectT const& box_object) noexcept;

    /**
     * @brief Destructor
     *
     */
    ~BoxObjectT()
    {
    }

    /**
     * @brief Copy assign operator
     *
     * @param other another detected object
     * @return BoxObjectT<Scalar, KeyPointsMaxSize>&
     */
    BoxObjectT<Scalar, KeyPointsMaxSize>& operator=(BoxObjectT<Scalar, KeyPointsMaxSize> const& other) noexcept;

    /**
     * @brief operator ==, check if two BoxObject are equal
     *
     * @param other
     * @return bool_t, true is same, false is different
     */
    bool_t operator==(BoxObjectT<Scalar, KeyPointsMaxSize> const& other) const noexcept;

    /**
     * @brief Set the ClassifyInfo of the BoxObject
     *
     * @param classify_info, including category_id and confidence
     */
    void SetClassifyInfo(ClassifyInfo const& classify_info) noexcept
    {
        classify_info_ = classify_info;
    }

    /**
     * @brief Set the ClassifyInfo2 of the BoxObject(reserved for additional classify attribute)
     *
     * @param classify_info2, including category2_id(additional) and confidence
     */
    void SetClassifyInfo2(ClassifyInfo const& classify_info2) noexcept
    {
        classify_info2_ = classify_info2;
    }

    /**
     * @brief Set the track id of the DetectedObject
     *
     * @param id, track id of the object
     */
    void SetObjectId(IdType const id) noexcept
    {
        object_id_ = id;
    }

    /**
     * @brief Set the Position of the object
     *
     * @param position, object position in 3d space
     */
    void SetPosition(Point3Type const& position) noexcept
    {
        position_ = position;
    }

    /**
     * @brief Set the Velocity of the object
     *
     * @param velocity, object velocity in 3d space
     */
    void SetVelocity(Vector3Type const& velocity) noexcept
    {
        velocity_ = velocity;
    }

    /**
     * @brief Set the 2d bounding box of the object
     *
     * @param box2, [x, y, w, h, r]
     */
    void SetBox2(Box2Type const& box2) noexcept
    {
        box2_ = box2;
    }

    /**
     * @brief Set the 3d bounding box of the object
     *
     * @param box3, [center_point, x_dim, y_dim, z_dim, yaw, pitch, roll]
     */
    void SetBox3(Box3Type const& box3) noexcept
    {
        box3_ = box3;
    }

    /**
     * @brief Set array of 2d keypoints
     *
     * @param keypoint_vector, keypoint array
     */
    void SetKeyPoint2DVector(KeyPoint2DVector const& keypoint2d_vector) noexcept
    {
        keypoint2d_vector_ = keypoint2d_vector;
    }

    /**
     * @brief Set array of 3d keypoints
     *
     * @param keypoint_vector, keypoint array
     */
    void SetKeyPoint3DVector(KeyPoint3DVector const& keypoint3d_vector) noexcept
    {
        keypoint3d_vector_ = keypoint3d_vector;
    }

    /**
     * @brief Set timestamp of the object
     *
     * @param timestamp
     */
    void SetTimestamp(Timestamp const& timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Set the occluded ratio of the object
     *
     * @param occluded_ratio
     */
    void SetOccludedRatio(float32_t occluded_ratio) noexcept
    {
        occluded_ratio_ = occluded_ratio;
    }

    /**
     * @brief Set the filtered flag of the object
     *
     * @param flag
     */
    void SetFiltered(bool_t flag) noexcept
    {
        filtered_ = flag;
    }

    /**
     * @brief Get the classify info of the object
     *
     * @return ClassifyInfo const&
     */
    ClassifyInfo const& GetClassifyInfo() const noexcept
    {
        return classify_info_;
    }

    /**
     * @brief Get the classify info2(additional) of the object
     *
     * @return ClassifyInfo const&
     */
    ClassifyInfo const& GetClassifyInfo2() const noexcept
    {
        return classify_info2_;
    }

    /**
     * @brief Get the track id of the object
     *
     * @return IdType
     */
    IdType GetObjectId() const noexcept
    {
        return object_id_;
    }

    /**
     * @brief Get the 3d position of the object
     *
     * @return Point3Type const&
     */
    Point3Type const& GetPosition() const noexcept
    {
        return position_;
    }

    /**
     * @brief Get the 3d velocity of the object
     *
     * @return Vector3Type const&
     */
    Vector3Type const& GetVelocity() const noexcept
    {
        return velocity_;
    }

    /**
     * @brief Get the 2d bounding box of the object
     *
     * @return Box2Type const&
     */
    Box2Type const& GetBox2() const noexcept
    {
        return box2_;
    }

    /**
     * @brief Get the 3d bounding box of the object
     *
     * @return Box3Type const&
     */
    Box3Type const& GetBox3() const noexcept
    {
        return box3_;
    }

    Box3Type& GetBox3() noexcept
    {
        return box3_;
    }

    /**
     * @brief Get the 2d keypoints array of the object
     *
     * @return KeyPoint2DVector const&
     */
    KeyPoint2DVector const& GetKeyPoint2DVector() const noexcept
    {
        return keypoint2d_vector_;
    }

    /**
     * @brief Get the 2d keypoints array of the object
     *
     * @return KeyPointVector&
     */
    KeyPoint2DVector& GetKeyPoint2DVector()
    {
        return keypoint2d_vector_;
    }

    /**
     * @brief Get the 3d keypoints array of the object
     *
     * @return KeyPoint2DVector const&
     */
    KeyPoint3DVector const& GetKeyPoint3DVector() const noexcept
    {
        return keypoint3d_vector_;
    }

    /**
     * @brief Get the 3d keypoints array of the object
     *
     * @return KeyPointVector&
     */
    KeyPoint3DVector& GetKeyPoint3DVector()
    {
        return keypoint3d_vector_;
    }

    /**
     * @brief Get the timestamp of the object
     *
     * @return Timestamp const&
     */
    Timestamp const& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Get the occluded_ratio of the object
     *
     * @return float32_t
     */
    float32_t GetOccludedRatio() const noexcept
    {
        return occluded_ratio_;
    }

    /**
     * @brief Get the filtered flag of the object
     *
     * @return bool_t
     */
    bool_t IsFiltered() const noexcept
    {
        return filtered_;
    }

    /**
     * @brief Sorted the object by score
     *
     * @param box1, object1
     * @param box2, object2
     * @return bool_t
     */
    static bool_t SortObjectByScore(BoxObjectT<Scalar, KeyPointsMaxSize> box1,
                                    BoxObjectT<Scalar, KeyPointsMaxSize> box2);

    /**
     * @brief Sorted the object by score
     *
     * @param box1, object1
     * @param box2, object2
     * @return bool_t
     */
    static bool_t SortObjectByScorePtr(std::shared_ptr<BoxObjectT<Scalar, KeyPointsMaxSize>> box1,
                                       std::shared_ptr<BoxObjectT<Scalar, KeyPointsMaxSize>> box2);

    /**
     * @brief Sorted the object by area
     *
     * @param box1, object1
     * @param box2, object2
     * @return bool_t
     */
    static bool_t SortObjectByArea(BoxObjectT<Scalar, KeyPointsMaxSize> box1,
                                   BoxObjectT<Scalar, KeyPointsMaxSize> box2);

    /**
     * @brief NMS
     *
     * @param objects, vec_boxs
     * @param threshold, threshold
     */
    static void HardNMS(std::list<BoxObjectT<Scalar, KeyPointsMaxSize>>& objects, float32_t threshold);

    /**
     * @brief NMS
     *
     * @param objects, vec_boxs
     * @param threshold, threshold
     */
    static void HardNMS(std::list<std::shared_ptr<BoxObjectT<Scalar, KeyPointsMaxSize>>>& objects, float32_t threshold);

    /**
     * @brief Set the Age of the object
     *
     * @param age
     */
    void SetAge(AgeType const age) noexcept
    {
        age_ = age;
    }

    /**
     * @brief Get the Age of the object
     *
     * @return AgeType
     */
    AgeType GetAge() const noexcept
    {
        return age_;
    }

private:
    ClassifyInfo     classify_info_;      ///< object's classify_info: [category_id, confidence]
    ClassifyInfo     classify_info2_;     ///< object's classify_info2: reserved for additional classify attribute
    IdType           object_id_;          ///< object's track id
    AgeType          age_;                ///< object's exist age
    Point3Type       position_;           ///< object's position in 3d space
    Vector3Type      velocity_;           ///< object's velocity in 3d space
    Box2Type         box2_;               ///< object's 2d bounding box
    Box3Type         box3_;               ///< object's 3d bounding box
    KeyPoint2DVector keypoint2d_vector_;  ///< object's 2d keypoints array
    KeyPoint3DVector keypoint3d_vector_;  ///< object's 3d keypoints array
    Timestamp        timestamp_;          ///< object's timestamp
    float32_t        occluded_ratio_;     ///< object's occluded ratio
    bool_t           filtered_;           ///< object's filtered flag
};

/**
 * @brief handy typedefs
 *
 */
using BoxObjectf = BoxObjectT<float32_t, 128U>;
using BoxObjectd = BoxObjectT<float64_t, 128U>;

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_COMMON_BOX_OBJECT_H_
