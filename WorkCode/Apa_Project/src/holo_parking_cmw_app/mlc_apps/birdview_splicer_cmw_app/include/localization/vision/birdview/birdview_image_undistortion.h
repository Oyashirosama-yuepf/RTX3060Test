/*
 *  \brief image undistortion for birdview modular
 *  \author liwenhao
 *  \date  2020-8-18
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_CMW_APPS_LOCALIZATION_VISION_BIRDVIEW_BIRDVIEW_IMAGE_UNDISTORTION_H_
#define HOLO_CMW_APPS_LOCALIZATION_VISION_BIRDVIEW_BIRDVIEW_IMAGE_UNDISTORTION_H_

#include <opencv2/imgproc.hpp>

#include <holo/common/intrinsic.h>

namespace holo
{
namespace vision
{
/**
 * @brief Used to remove distortion for surround camera image
 */
class BirdviewImageUndistortion
{
public:
    typedef holo::float64_t Scalar;
    typedef holo::common::OmnidirectionalIntrinsicT<Scalar> IntrinsicType;

    /**
     * @brief Construct a new Birdview Image Undistortion object
     *
     * @param[in] instrinsic image intrinsic parameter
     * @param[in] K camera project matrix
     * @param[in] height image size of height
     * @param[in] width image size of width
     */
    BirdviewImageUndistortion(IntrinsicType const& instrinsic, cv::Mat const& K,
                              holo::uint16_t const& height, holo::uint16_t const& width);
    /**
     * @brief Destroy the Birdview Image Undistortion object
     *
     */
    ~BirdviewImageUndistortion();

    /**
     * @brief get undistorted image
     * @param[in] in source image
     * @param[in] out undistorted image
     */
    void Undistort(cv::Mat const& in, cv::Mat& out) const;

protected:
    /**
     * @brief called in construct function, to calculate the Mapping table
     */
    bool init();

private:
    /// @brief intrinsic parameters
    IntrinsicType intrinsic_;

    /// @brief project matrix
    cv::Mat K_;

    /// @brief image size
    holo::uint16_t height_, width_;

    /// @brief mapping matrix
    cv::Mat map_row_, map_col_;

};  // BirdviewImageUndistortion
}  // namespace vision
}  // namespace holo

#endif  // HOLO_VISION_BIRDVIEW_BIRDVIEW_IMAGE_UNDISTORTION_H_