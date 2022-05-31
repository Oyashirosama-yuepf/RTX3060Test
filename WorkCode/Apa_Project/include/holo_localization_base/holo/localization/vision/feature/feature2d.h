/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file feature2d.h
 * @brief This header file defines feature2d detection and descriptor extraction
 * @author Evan. Du
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2017-11-23"
 */

#ifndef HOLO_LOCALIZATION_VISION_FEATURE_FEATURE2D_H_
#define HOLO_LOCALIZATION_VISION_FEATURE_FEATURE2D_H_

#include <memory>
#include <string>

#include <holo/common/optional.h>
#include <holo/core/types.h>
#include <holo/localization/vision/common/key_point.h>
#include <holo/localization/vision/common/mask.h>
#include <holo/localization/vision/common/mat.h>
#include <holo/numerics/vector.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup vision
 * @{
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define descriptor types
 */
enum class DescriptorType : uint8_t
{

    BINARY   = 0u,    ///< e.g. orb, brief, brisk
    FLOATING = 1u,    ///< e.g. sift, surf
    UNKNOWN  = 255u,  ///< e.g. unknown type
};

/**
 * @brief define descriptor
 */
using Descriptor = std::pair<DescriptorType, holo::numerics::VectorXT<holo::float64_t> >;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief feature 2D base
 */
class Feature2DBase
{
public:
    /// @brief define CV types
    using Mat        = holo::localization::Mat;
    using KeyPoint2f = holo::localization::KeyPoint2f;
    using Mask       = holo::localization::Mask;

    /// @brief smart pointer
    using Ptr      = std::shared_ptr<Feature2DBase>;
    using ConstPtr = std::shared_ptr<const Feature2DBase>;

    /**
     * @brief constructor
     */
    Feature2DBase() noexcept
    {
    }

    /**
     * @brief destructor
     */
    virtual ~Feature2DBase() noexcept
    {
    }

    /**
     * @brief detect key point from the given image
     *
     * @param[in] image the given image
     * @param[out] keypoints detected key points
     * @param[in] mask the given mask to constraint the location of the detected key points
     * @return bool_t true if the key points are detected successfully, false otherwise
     */
    virtual bool_t Detect(const Mat& image, std::vector<KeyPoint2f>& keypoints,
                          const holo::OptionalT<Mask>& mask = holo::optional::none) const;

    /**
     * @brief compute descriptor for each key point on the given image
     *
     * @param[in] image the given image used to compute descriptor
     * @param[in] keypoints the given key points whose decriptor will be computed
     * @param[out] descriptors the computed descriptor
     * @return bool_t true if the descriptors are computed successfully, false otherwise
     */
    virtual bool_t Compute(const Mat& image, const std::vector<KeyPoint2f>& keypoints,
                           std::vector<Descriptor>& descriptors) const;

    /**
     * @brief an unified interface to compute key points and detect descriptor
     *
     * @param[in] image the given image
     * @param[in][out] keypoints the detected key points
     * @param[out] descriptors descriptors corresponding to keypoints
     * @param[in] compute_keypoint whether detect key points
     * @param[in] compute_descriptor whether compute descriptors
     * @param[in] mask the given mask to constraint the location of the detected key points
     * @return bool_t true if key points are detected and descriptors are computed successfully, false otherwise
     */
    virtual bool_t DetectAndCompute(const Mat& image, std::vector<KeyPoint2f>& keypoints,
                                    std::vector<Descriptor>& descriptors, const bool_t compute_keypoint = true,
                                    const bool_t                 compute_descriptor = true,
                                    const holo::OptionalT<Mask>& mask               = holo::optional::none) const;

    /**
     * @brief return the type of descriptor
     */
    virtual DescriptorType GetDescriptorType() const noexcept;

    /**
     * @brief return the size of descriptor
     */
    virtual holo::uint16_t GetDescriptorSize() const noexcept;

protected:
};  // Feature2DBase

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief all keypoint detectors that implement Detect method inherit
 *        FeatureDetector interface
 */
using FeatureDetector = Feature2DBase;

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief all descriptor extractors that implement Compute method inherit
 *        DescriptorExtractor interface
 */
using DescriptorExtractor = Feature2DBase;

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief all features2D algorithms that implement DetectAndCompute method inherit
 *        Feature2D interface
 */
using Feature2D = Feature2DBase;

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_FEATURE_FEATURE2D_H_
