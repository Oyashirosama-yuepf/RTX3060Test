/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fast.cpp
 * @brief This file implements fast class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-10"
 */

#include <opencv2/features2d.hpp>

#include <holo/localization/vision/feature/fast.h>

namespace holo
{
namespace localization
{
/**
 * @brief define internal Implementation for FAST
 */
struct FAST::Implementation
{
    /**
     * @brief constructor
     *
     * @param[in] threshold fast corner threshold
     * @param[in] non_max_suppression whether do nonmax suppression
     * @param[in] type fast corner type
     * @throw if the given type is not supported
     */
    Implementation(const int32_t threshold = 10, const bool_t non_max_suppression = true,
                   const FAST::Type type = FAST::Type::TYPE_9_16)
    {
        ffd = cv::FastFeatureDetector::create(threshold, non_max_suppression, cv::FastFeatureDetector::TYPE_9_16);
        SetType(type);
    }

    /**
     * @brief copy constructor
     *
     * @param[in] other the given object
     */
    Implementation(const Implementation& other)
      : Implementation(other.ffd->getThreshold(), other.ffd->getNonmaxSuppression(), other.GetType())
    {
    }

    /**
     * @brief copy assignment operator
     *
     */
    Implementation& operator=(Implementation const&) = default;

    /**
     * @brief set fast corner type
     *
     * @param[in] type fast corner type
     */
    void SetType(const FAST::Type type) const
    {
        if (type == FAST::Type::TYPE_9_16)
        {
            ffd->setType(cv::FastFeatureDetector::TYPE_9_16);
        }
        else if (type == FAST::Type::TYPE_7_12)
        {
            ffd->setType(cv::FastFeatureDetector::TYPE_7_12);
        }
        else if (type == FAST::Type::TYPE_5_8)
        {
            ffd->setType(cv::FastFeatureDetector::TYPE_5_8);
        }
        else
        {
            throw std::runtime_error("unsupported fast corner type");
        }
    }

    /**
     * @brief get type of fast corner detector
     *
     * @return FAST::Type
     */
    FAST::Type GetType() const
    {
        const int32_t type = ffd->getType();

        if (type == cv::FastFeatureDetector::TYPE_9_16)
        {
            return FAST::Type::TYPE_9_16;
        }
        else if (type == cv::FastFeatureDetector::TYPE_7_12)
        {
            return FAST::Type::TYPE_7_12;
        }
        else
        {
            return FAST::Type::TYPE_5_8;
        }
    }

    /**
     * @brief define cv fast pointer
     */
    cv::Ptr<cv::FastFeatureDetector> ffd;
};  // Implementation

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FAST::FAST(const int32_t threshold, const bool_t non_max_suppression, const Type type)
  : Base(), impl_ptr_(new Implementation(threshold, non_max_suppression, type))
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FAST::FAST(const FAST& other) : Base(), impl_ptr_(new Implementation(*(other.impl_ptr_)))
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FAST::~FAST() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FAST::operator=(const FAST& other)
{
    if (this == &other)
    {
        return;
    }

    Base::operator=(other);
    impl_ptr_.reset(new Implementation(*(other.impl_ptr_)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t FAST::Detect(const Mat& image, std::vector<KeyPoint2f>& keypoints, const holo::OptionalT<Mask>& mask) const
{
    std::vector<cv::KeyPoint> cv_keypoints;
    impl_ptr_->ffd->detect(image.GetCvType(), cv_keypoints, mask ? mask->GetCvType() : cv::noArray());

    // convert to holo KeyPoint
    keypoints.reserve(cv_keypoints.size());

    for (uint32_t i = 0u; i < static_cast<uint32_t>(cv_keypoints.size()); i++)
    {
        cv::KeyPoint cv_kpt = cv_keypoints.at(i);
        keypoints.emplace_back(Point2f(cv_kpt.pt.x, cv_kpt.pt.y), cv_kpt.size, cv_kpt.angle, cv_kpt.response,
                               cv_kpt.octave, cv_kpt.class_id);
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FAST::SetThreshold(const int32_t threshold) noexcept
{
    impl_ptr_->ffd->setThreshold(threshold);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t FAST::GetThreshold() const noexcept
{
    return impl_ptr_->ffd->getThreshold();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FAST::SetNonmaxSuppression(const bool_t non_max_suppression) noexcept
{
    impl_ptr_->ffd->setNonmaxSuppression(non_max_suppression);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t FAST::GetNonmaxSuppression() const noexcept
{
    return impl_ptr_->ffd->getNonmaxSuppression();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FAST::SetType(const Type type)
{
    impl_ptr_->SetType(type);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FAST::Type FAST::GetType() const noexcept
{
    return impl_ptr_->GetType();
}

}  // namespace localization
}  // namespace holo
