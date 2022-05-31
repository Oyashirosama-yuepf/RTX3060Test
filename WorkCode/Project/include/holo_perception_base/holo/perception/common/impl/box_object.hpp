/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box_object.hpp
 * @brief This file implements a box object.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2020-09-25"
 */

#ifndef HOLO_PERCEPTION_COMMON_BOX_OBJECT_HPP_
#define HOLO_PERCEPTION_COMMON_BOX_OBJECT_HPP_

#include <holo/perception/common/box_object.h>
namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t KeyPointsMaxSize>
BoxObjectT<T, KeyPointsMaxSize>::BoxObjectT(ClassifyInfo const& classify_info, ClassifyInfo const& classify_info2, IdType const id,
                                            AgeType const age, Point3Type const& position, Vector3Type const& velocity,
                                            Box2Type const& box2, Box3Type const& box3,
                                            KeyPoint2DVector const& keypoint2d_vector,
                                            KeyPoint3DVector const& keypoint3d_vector, Timestamp const& timestamp,
                                            float32_t occluded_ratio, bool_t filtered) noexcept
  : classify_info_(classify_info)
  , classify_info2_(classify_info2)
  , object_id_(id)
  , age_(age)
  , position_(position)
  , velocity_(velocity)
  , box2_(box2)
  , box3_(box3)
  , keypoint2d_vector_(keypoint2d_vector)
  , keypoint3d_vector_(keypoint3d_vector)
  , timestamp_(timestamp)
  , occluded_ratio_(occluded_ratio)
  , filtered_(filtered)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t KeyPointsMaxSize>
BoxObjectT<T, KeyPointsMaxSize>::BoxObjectT(const BoxObjectT& detected_object) noexcept
  : classify_info_(detected_object.classify_info_)
  , classify_info2_(detected_object.classify_info2_)
  , object_id_(detected_object.object_id_)
  , age_(detected_object.age_)
  , position_(detected_object.position_)
  , velocity_(detected_object.velocity_)
  , box2_(detected_object.box2_)
  , box3_(detected_object.box3_)
  , keypoint2d_vector_(detected_object.keypoint2d_vector_)
  , keypoint3d_vector_(detected_object.keypoint3d_vector_)
  , timestamp_(detected_object.timestamp_)
  , occluded_ratio_(detected_object.occluded_ratio_)
  , filtered_(detected_object.filtered_)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t KeyPointsMaxSize>
BoxObjectT<T, KeyPointsMaxSize>&
BoxObjectT<T, KeyPointsMaxSize>::operator=(BoxObjectT<Scalar, KeyPointsMaxSize> const& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    classify_info_     = other.classify_info_;
    classify_info2_     = other.classify_info2_;
    object_id_         = other.object_id_;
    age_               = other.age_;
    position_          = other.position_;
    velocity_          = other.velocity_;
    box2_              = other.box2_;
    box3_              = other.box3_;
    keypoint2d_vector_ = other.keypoint2d_vector_;
    keypoint3d_vector_ = other.keypoint3d_vector_;
    timestamp_         = other.timestamp_;
    occluded_ratio_    = other.occluded_ratio_;
    filtered_          = other.filtered_;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t KeyPointsMaxSize>
bool_t BoxObjectT<T, KeyPointsMaxSize>::operator==(BoxObjectT<Scalar, KeyPointsMaxSize> const& other) const noexcept
{
    return (classify_info_ == other.classify_info_) && (classify_info2_ == other.classify_info2_) &&
           (object_id_ == other.object_id_) && (age_ == other.age_) && (position_ == other.position_) &&
           (velocity_ == other.velocity_) && (box2_ == other.box2_) && (box3_ == other.box3_) &&
           (keypoint2d_vector_ == other.keypoint2d_vector_) && (keypoint3d_vector_ == other.keypoint3d_vector_) &&
           (timestamp_ == other.timestamp_) && (occluded_ratio_ == other.occluded_ratio_) &&
           (filtered_ == other.filtered_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t KeyPointsMaxSize>
bool_t BoxObjectT<T, KeyPointsMaxSize>::SortObjectByScore(BoxObjectT<Scalar, KeyPointsMaxSize> box1,
                                                          BoxObjectT<Scalar, KeyPointsMaxSize> box2)
{
    return box1.GetClassifyInfo().GetConfidence() > box2.GetClassifyInfo().GetConfidence() ? true : false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t KeyPointsMaxSize>
bool_t BoxObjectT<T, KeyPointsMaxSize>::SortObjectByScorePtr(std::shared_ptr<BoxObjectT<Scalar, KeyPointsMaxSize>> box1,
                                                             std::shared_ptr<BoxObjectT<Scalar, KeyPointsMaxSize>> box2)
{
    return box1->GetClassifyInfo().GetConfidence() > box2->GetClassifyInfo().GetConfidence() ? true : false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t KeyPointsMaxSize>
bool_t BoxObjectT<T, KeyPointsMaxSize>::SortObjectByArea(BoxObjectT<Scalar, KeyPointsMaxSize> box1,
                                                         BoxObjectT<Scalar, KeyPointsMaxSize> box2)
{
    return box1.GetBox2().GetArea() > box2.GetBox2().GetArea() ? true : false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t KeyPointsMaxSize>
void BoxObjectT<T, KeyPointsMaxSize>::HardNMS(std::list<BoxObjectT<Scalar, KeyPointsMaxSize>>& objects,
                                              float32_t                                        threshold)
{
    objects.sort(SortObjectByScore);
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        auto erase_it = it;
        erase_it++;
        while (erase_it != objects.end())
        {
            // remove box with IOU > threshold
            if ((*it).GetBox2().ComputeIoU((*erase_it).GetBox2()) > threshold)
            {
                erase_it = objects.erase(erase_it);
                continue;
            }

            // go to next box
            erase_it++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t KeyPointsMaxSize>
void BoxObjectT<T, KeyPointsMaxSize>::HardNMS(std::list<std::shared_ptr<BoxObjectT<Scalar, KeyPointsMaxSize>>>& objects,
                                              float32_t threshold)
{
    objects.sort(SortObjectByScorePtr);
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        auto erase_it = it;
        erase_it++;
        while (erase_it != objects.end())
        {
            // remove box with IOU > threshold
            if ((*it)->GetBox2().ComputeIoU((*erase_it)->GetBox2()) > threshold)
            {
                if ((*erase_it)->GetKeyPoint2DVector().size() > 0U && 0U == (*it)->GetKeyPoint2DVector().size())
                {
                    (*it)->SetKeyPoint2DVector((*erase_it)->GetKeyPoint2DVector());
                }
                erase_it = objects.erase(erase_it);
                continue;
            }

            // go to next box
            erase_it++;
        }
    }
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_COMMON_BOX_OBJECT_HPP_
