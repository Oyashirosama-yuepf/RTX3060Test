/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gridding_feature_extractor.cpp
 * @brief test gridding feature extractor class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-12-10"
 */

#include <stdexcept>

#include <holo/localization/vision/feature/gridding_feature_extractor.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GriddingFeatureExtractor::Parameters::Parameters(const Feature2DBase::Ptr& _feature_ptr, const uint16_t _image_width,
                                                 const uint16_t _image_height, const uint16_t _grid_x,
                                                 const uint16_t _grid_y, const uint16_t _min_feature_distance)
  : feature_ptr(_feature_ptr)
  , image_size(_image_width, _image_height)
  , grid_x(_grid_x)
  , grid_y(_grid_y)
  , min_feature_distance(_min_feature_distance)
{
    CheckParameters();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GriddingFeatureExtractor::Parameters::CheckParameters()
{
    if (feature_ptr == nullptr)
    {
        std::stringstream ss;
        ss << "GriddingFeatureExtractor --- invalid feature extractor!";
        LOG(ERROR) << ss.str();
        std::string s = ss.str();
        throw std::runtime_error(s);
    }

    if (image_size.GetArea() == 0u)
    {
        std::stringstream ss;
        ss << "GriddingFeatureExtractor --- invalid image size = [" << image_size.GetWidth() << ", "
           << image_size.GetHeight() << "]";
        LOG(ERROR) << ss.str();
        std::string s = ss.str();
        throw std::runtime_error(s);
    }

    if (grid_x == 0u || grid_x <= 2 * min_feature_distance || grid_x > static_cast<uint16_t>(image_size.GetWidth()))
    {
        LOG(WARNING) << "GriddingFeatureExtractor --- invalid grid_x = " << grid_x
                     << "; image_width = " << image_size.GetWidth()
                     << ", 2 * min_feature_distance = " << 2 * min_feature_distance
                     << ", 2 * min_feature_distance < grid_x < image_width is valid"
                     << ", set grid_x = image_width!!!";
        grid_x = static_cast<uint16_t>(image_size.GetWidth());
    }

    if (grid_y == 0 || grid_y <= 2 * min_feature_distance || grid_y > static_cast<uint16_t>(image_size.GetHeight()))
    {
        LOG(WARNING) << "GriddingFeatureExtractor --- invalid grid_y = " << grid_y
                     << "; image_height = " << image_size.GetHeight()
                     << ", 2 * min_feature_distance =" << 2 * min_feature_distance
                     << ", 2 * min_feature_distance < grid_y < image_height is valid"
                     << ", set grid_y = image_height!!!";
        grid_y = static_cast<uint16_t>(image_size.GetHeight());
    }

    if (min_feature_distance == 0)
    {
        LOG(WARNING) << "GriddingFeatureExtractor --- no non-maximum suppresion!!!";
    }

    // compute grid cols and rows
    grid_cols = static_cast<uint16_t>(image_size.GetWidth()) / grid_x;
    grid_rows = static_cast<uint16_t>(image_size.GetHeight()) / grid_y;

    // re-compute grid size with computed grid_cols and grid_rows to extract on whole image
    grid_x = static_cast<uint16_t>(image_size.GetWidth()) / grid_cols;
    grid_y = static_cast<uint16_t>(image_size.GetHeight()) / grid_rows;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GriddingFeatureExtractor::GriddingFeatureExtractor(const Parameters& parameters) noexcept : parameters_(parameters)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GriddingFeatureExtractor::~GriddingFeatureExtractor() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t GriddingFeatureExtractor::Detect(const Mat& image, std::vector<KeyPoint2f>& keypoints,
                                        const uint32_t max_num_features, const holo::OptionalT<Mask>& mask) const
{
    if (image.IsEmpty())
    {
        LOG(WARNING) << "GriddingFeatureExtractor --- empty image!!!";
        return false;
    }

    if (max_num_features == 0u)
    {
        LOG(INFO) << "GriddingFeatureExtractor --- max_num_features = 0!!!";
        return false;
    }

    /// @step1: check image size
    if ((uint16_t)image.GetWidth() != parameters_.image_size.GetWidth() ||
        (uint16_t)image.GetHeight() != parameters_.image_size.GetHeight())
    {
        LOG(ERROR) << "GriddingFeatureExtractor --- please initialize "
                   << "gridding feature extractor with image size: [" << image.GetWidth() << ", " << image.GetHeight()
                   << "]"
                   << ", current image size: [" << parameters_.image_size.GetWidth() << ", "
                   << parameters_.image_size.GetHeight() << "]";
        return false;
    }

    /// @step2: extract key point in each grid
    std::vector<std::vector<KeyPoint2f> > all_keypoints = extractKeyPoints(
        image, parameters_.grid_cols, parameters_.grid_rows, parameters_.grid_x, parameters_.grid_y, mask);

    /// @step3: collect key point from each grid
    // maximum number of keypoints will be extracted in each grid
    const uint16_t num_points_per_grid =
        std::floor(max_num_features / static_cast<uint32_t>(all_keypoints.size())) + 1u;
    keypoints.clear();
    keypoints.reserve(max_num_features);

    for (uint16_t j = 0u; j < static_cast<uint16_t>(all_keypoints.size()); j++)
    {
        if (keypoints.size() >= max_num_features)
        {
            break;
        }

        std::vector<KeyPoint2f>& kpts = all_keypoints.at(j);

        if (kpts.size() != 0)
        {
            // calculate the max number of features will be add in this grid
            // num_features_added = min(kpts.size(), num_points_per_grid,
            //                          max_num_features - keypoints.size())
            uint16_t num_features_added = std::min(std::min(static_cast<uint16_t>(kpts.size()), num_points_per_grid),
                                                   static_cast<uint16_t>(max_num_features - keypoints.size()));

            for (uint16_t k = 0u; k < num_features_added; k++)
            {
                keypoints.push_back(kpts.at(k));
            }
        }
    }

    if (keypoints.size() == 0)
    {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t GriddingFeatureExtractor::Compute(const Mat& image, const std::vector<KeyPoint2f>& keypoints,
                                         std::vector<Descriptor>& descriptors) const
{
    if (image.IsEmpty())
    {
        LOG(WARNING) << "GriddingFeatureExtractor --- empty image!!!";
        return false;
    }

    return parameters_.feature_ptr->Compute(image, keypoints, descriptors);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t GriddingFeatureExtractor::DetectAndCompute(const Mat& image, std::vector<KeyPoint2f>& keypoints,
                                                  std::vector<Descriptor>& descriptors, const uint32_t max_num_features,
                                                  const bool_t compute_keypoint, const bool_t compute_descriptor,
                                                  const holo::OptionalT<Mask>& mask) const
{
    if (!compute_keypoint && !compute_descriptor)
    {
        LOG(WARNING) << "compute_keypoint = false and compute_descriptor = false!!!";
        return false;
    }

    if (image.IsEmpty())
    {
        LOG(WARNING) << "GriddingFeatureExtractor --- empty image!!!";
        return false;
    }

    /// @step 1: detect key points if needed
    if (compute_keypoint)
    {
        /// @brief if failed to detect key points, return false
        if (!Detect(image, keypoints, max_num_features, mask))
        {
            LOG(WARNING) << "Failed to detect key points!!!";
            return false;
        }
    }

    /// @step 2: compute descriptors if needed
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
std::vector<std::vector<KeyPoint2f> > GriddingFeatureExtractor::extractKeyPoints(
    const Mat& image, const uint16_t grid_cols, const uint16_t grid_rows, const uint16_t grid_x, const uint16_t grid_y,
    const holo::OptionalT<Mask>& mask) const
{
    std::vector<std::vector<KeyPoint2f> > all_keypoints(grid_cols * grid_rows);

    // use opencv parallel for
    cv::parallel_for_(cv::Range(0, all_keypoints.size()), [&](const cv::Range& range) {
        for (uint16_t i = range.start; i < range.end; i++)
        {
            const uint16_t grid_col = i % grid_cols;
            const uint16_t grid_row = i / grid_cols;
            const uint16_t left     = grid_col * grid_x;
            const uint16_t top      = grid_row * grid_y;

            // check whether the grid is in the image
            if (left + grid_x > image.GetWidth() || top + grid_y > image.GetHeight())
            {
                continue;
            }

            Rect2i                  rect(left, top, grid_x, grid_y);
            std::vector<KeyPoint2f> keypoints;
            holo::OptionalT<Mask>   mask_i = mask ? holo::OptionalT<Mask>((*mask)(rect)) : holo::optional::none;

            if (!parameters_.feature_ptr->Detect(image(rect), keypoints, mask_i))
            {
                LOG(WARNING) << "GriddingFeatureExtractor --- failed to "
                             << "extract feature at grid "
                             << "[" << grid_row << ", " << grid_col << "]";
                continue;
            }

            all_keypoints.at(i) = filterAndCompensate(keypoints, Point2f(left, top), mask_i);
        }
    });

    return all_keypoints;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<KeyPoint2f> GriddingFeatureExtractor::filterAndCompensate(const std::vector<KeyPoint2f>& keypoints,
                                                                      const Point2f&                 offset,
                                                                      const holo::OptionalT<Mask>&   mask) const
{
    std::vector<KeyPoint2f> sorted_key_points(keypoints);
    std::sort(
        sorted_key_points.begin(), sorted_key_points.end(),
        [](const KeyPoint2f& lhs, const KeyPoint2f& rhs) -> bool { return lhs.GetResponse() > rhs.GetResponse(); });

    /// @brief check whether there is an input mask, if false create a mask to do nonmax suppression with
    /// parameters_.min_feature_distance
    Mask                    valid_mask = mask ? *mask : Mask(parameters_.grid_x, parameters_.grid_y, 255u);
    std::vector<KeyPoint2f> result;

    for (uint16_t i = 0; i < sorted_key_points.size(); i++)
    {
        const KeyPoint2f& kpt = sorted_key_points.at(i);

        if (valid_mask.At(kpt.GetPoint().GetY(), kpt.GetPoint().GetX()) != 0u)
        {
            /// @brief compensate point with offset
            Point2f compensated_pt = kpt.GetPoint() + offset;

            KeyPoint2f compensated_kpt(compensated_pt, kpt.GetSize(), kpt.GetAngle(), kpt.GetResponse(),
                                       kpt.GetOctave(), kpt.GetClassId());
            result.push_back(compensated_kpt);
            // supprese key points around this key point if need
            if (parameters_.min_feature_distance > 0u)
            {
                valid_mask(computeKeyPointMask(kpt, valid_mask.GetWidth(), valid_mask.GetHeight())) = 0u;
            }
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GriddingFeatureExtractor::Rect2i GriddingFeatureExtractor::computeKeyPointMask(const KeyPoint2f& keypoint,
                                                                               const uint16_t    mask_width,
                                                                               const uint16_t    mask_height) const
{
    const uint16_t min_distance = parameters_.min_feature_distance;
    const Point2f  point        = keypoint.GetPoint();
    const uint16_t x            = static_cast<uint16_t>(point.GetX());
    const uint16_t y            = static_cast<uint16_t>(point.GetY());
    const uint16_t left         = x > min_distance ? x - min_distance : 0u;
    const uint16_t top          = y > min_distance ? y - min_distance : 0u;
    const uint16_t right        = x + min_distance < mask_width ? x + min_distance : mask_width - 1;
    const uint16_t bottom       = y + min_distance < mask_height ? y + min_distance : mask_height - 1;
    return Rect2i(left, top, right - left, bottom - top);
}

}  // namespace localization
}  // namespace holo
