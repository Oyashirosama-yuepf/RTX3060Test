/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file feature2d.cpp
 * @brief This is implementation file for feature2d
 * @author Evan. Du
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2017-11-23"
 */

#include <holo/localization/vision/feature/feature2d.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t Feature2DBase::Detect(const Mat& image, std::vector<KeyPoint2f>& keypoints,
                             const holo::OptionalT<Mask>& mask) const
{
    (void)image;
    (void)keypoints;
    (void)mask;
    LOG(WARNING) << "Detect is Not Implemented!!!";
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t Feature2DBase::Compute(const Mat& image, const std::vector<KeyPoint2f>& keypoints,
                              std::vector<Descriptor>& descriptors) const
{
    (void)image;
    (void)keypoints;
    (void)descriptors;
    LOG(WARNING) << "Compute is Not Implemented!!!";
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t Feature2DBase::DetectAndCompute(const Mat& image, std::vector<KeyPoint2f>& keypoints,
                                       std::vector<Descriptor>& descriptors, const bool compute_keypoint,
                                       const bool compute_descriptor, const holo::OptionalT<Mask>& mask) const
{
    /// step 0: check whether there are operations will be done in this function
    if (!compute_keypoint && !compute_descriptor)
    {
        LOG(WARNING) << "compute_keypoint = false and compute_descriptor = false!!!";
        return false;
    }

    /// step 1: detect key points if needed
    if (compute_keypoint)
    {
        /// @brief if failed to detect key points, return false
        if (!Detect(image, keypoints, mask))
        {
            LOG(WARNING) << "Failed to detect key points!!!";
            return false;
        }
    }

    /// step 2: compute descriptors if needed
    if (compute_descriptor)
    {
        if (keypoints.size() == 0)
        {
            LOG(WARNING) << "Key Points size = 0!!!";
            return false;
        }

        /// @brief if failed to compute descriptors, return false
        if (!Compute(image, keypoints, descriptors))
        {
            LOG(WARNING) << "Failed to compute descriptors!!!";
            return false;
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DescriptorType Feature2DBase::GetDescriptorType() const noexcept
{
    return DescriptorType::UNKNOWN;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::uint16_t Feature2DBase::GetDescriptorSize() const noexcept
{
    return 0u;
}

}  // namespace localization
}  // namespace holo
