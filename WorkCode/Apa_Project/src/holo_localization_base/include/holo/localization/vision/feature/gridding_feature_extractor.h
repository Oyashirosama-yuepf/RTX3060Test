/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gridding_feature_extractor.h
 * @brief This file defines gridding feature extractor class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-10-15"
 */

#ifndef HOLO_LOCALIZATION_VISION_FEATURE_GRIDDING_FEATURE_EXTRACTOR_H_
#define HOLO_LOCALIZATION_VISION_FEATURE_GRIDDING_FEATURE_EXTRACTOR_H_

#include <holo/localization/vision/common/rect.h>
#include <holo/localization/vision/common/size.h>
#include <holo/localization/vision/feature/feature2d.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup vision
 * {
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief this class aims to detect features which are evenly distributed on the image
 */
class GriddingFeatureExtractor
{
public:
    /// @brief define CV types
    using Mat        = holo::localization::Mat;
    using KeyPoint2f = holo::localization::KeyPoint2f;
    using Point2f    = typename KeyPoint2f::Point2f;
    using Mask       = holo::localization::Mask;
    using Size2i     = holo::localization::Size2i;
    using Rect2i     = holo::localization::Rect2i;
    using Descriptor = holo::localization::Descriptor;

    /// @brief define smart pointer
    using Ptr      = std::shared_ptr<GriddingFeatureExtractor>;
    using ConstPtr = std::shared_ptr<GriddingFeatureExtractor>;

    /**
     * @brief define parameters for GriddingFeatureExtractor
     */
    struct Parameters
    {
        /**
         * @brief feature extractor
         */
        Feature2DBase::Ptr feature_ptr;

        /**
         * @brief image size
         */
        Size2i image_size;

        /**
         * @brief grid size in x and y axis in pixel
         */
        uint16_t grid_x;
        uint16_t grid_y;

        /**
         * @brief number of grid along x and y axis
         */
        uint16_t grid_cols;
        uint16_t grid_rows;

        /**
         * @brief feature distance in pixel
         */
        uint16_t min_feature_distance;

        /**
         * @brief constructor
         *
         * @throw 1. feature_ptr is nullptr 2. image_size.GetHeight() == 0u or image_size.GetWidth() == 0u
         */
        Parameters(const Feature2DBase::Ptr& _feature_ptr, const uint16_t _image_width, const uint16_t _image_height,
                   const uint16_t _grid_x = 100u, const uint16_t _grid_y = 100u,
                   const uint16_t _min_feature_distance = 10u);

        /**
         * @brief check and calculate parameters
         *
         * @throw 1. feature_ptr is nullptr 2. image_size.GetHeight() == 0u or image_size.GetWidth() == 0u
         */
        void CheckParameters();
    };  // Parameters

    /**
     * @brief constructor
     *
     * @param[in] parameters parameters
     */
    GriddingFeatureExtractor(const Parameters& parameters) noexcept;

    /**
     * @brief desctrctor
     */
    ~GriddingFeatureExtractor() noexcept;

    /**
     * @brief detect keypoints
     *
     * @param[in] image the given image
     * @param[out] keypoints detected keypoints
     * @param[in] max_num_features maximum number of key points that will extracted from the given image
     * @param[in] mask mask to constraint key points' location
     * @return bool_t true if the key points are detected successfully, false otherwise
     */
    bool_t Detect(const Mat& image, std::vector<KeyPoint2f>& keypoints, const uint32_t max_num_features = 1000u,
                  const holo::OptionalT<Mask>& mask = holo::optional::none) const;

    /**
     * @brief compute descriptors for the given key points
     *
     * @param[in] image the given image
     * @param[in] keypoints the given key points
     * @param[out] descriptors descriptors for the given key points
     * @return bool_t true if the descriptors are computed successfully, false otherwise
     */
    bool_t Compute(const Mat& image, const std::vector<KeyPoint2f>& keypoints,
                   std::vector<Descriptor>& descriptors) const;

    /**
     * @brief detect key points and compute descriptors
     *
     * @param[in] image the given image
     * @param[in][out] keypoints the detected key points
     * @param[out] descriptors descriptors corresponding to keypoints
     * @param[in] max_num_features maximum number of key points that will extracted from the given image
     * @param[in] compute_keypoint whether detect key points
     * @param[in] compute_descriptor whether compute descriptors
     * @param[in] mask the given mask to constraint the location of the detected key points
     * @return bool_t true if key points are detected and descriptors are computed successfully, false otherwise
     */
    bool_t DetectAndCompute(const Mat& image, std::vector<KeyPoint2f>& keypoints, std::vector<Descriptor>& descriptors,
                            const uint32_t max_num_features = 1000u, const bool_t compute_keypoint = true,
                            const bool_t                 compute_descriptor = true,
                            const holo::OptionalT<Mask>& mask               = holo::optional::none) const;

private:
    /**
     * @brief extract key points in each grid
     *
     * @param[in] image the given image
     * @param[in] grid_cols grid number along x-axis
     * @param[in] grid_rows grid number along y-axis
     * @param[in] grid_x grid size along x-axis
     * @param[in] grid_y grid size along y-axis
     * @param[in] holo::OptionalT<Mask> mask
     * @return std::vector<std::vector<KeyPoint2f> > the extracted key points from each grid
     */

    std::vector<std::vector<KeyPoint2f> >
    extractKeyPoints(const Mat& image, const uint16_t grid_cols, const uint16_t grid_rows, const uint16_t grid_x,
                     const uint16_t grid_y, const holo::OptionalT<Mask>& mask = holo::optional::none) const;

    /**
     * @brief filter key points with mask and compensate point offset by each grid
     *
     * @param[in] keypoints key points extracted from a grid
     * @param[in] offset offset of the grid in whole image
     * @param[in] mask mask for the grid
     * @return std::vector<KeyPoint2f> the filtered after non-maximum suppression and compensated key points
     */
    std::vector<KeyPoint2f> filterAndCompensate(const std::vector<KeyPoint2f>& keypoints, const Point2f& offset,
                                                const holo::OptionalT<Mask>& mask = holo::optional::none) const;

    /**
     * @brief compute mask rect around a key point with parameters_.min_feature_distance in the whole mask
     *
     * @param[in] keypoint the given key points
     * @param[in] mask_width width of the mask
     * @param[in] mask_height height of the mask
     * @return Rect2i a rect around the given key point
     */
    Rect2i computeKeyPointMask(const KeyPoint2f& keypoint, const uint16_t mask_width, const uint16_t mask_height) const;

    /**
     * @brief parameters
     */
    const Parameters parameters_;

};  // GriddingFeatureExtractor

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_VISION_FEATURE_GRIDDING_FEATURE_EXTRACTOR_H_
