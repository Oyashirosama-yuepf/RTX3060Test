/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file birdview_mask.h
 * @brief This header file defines mask of birdview image.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2020-12-21"
 */

#ifndef HOLO_CMW_APPS_LOCALIZATION_VISION_BIRDVIEW_BIRDVIEW_MASK_H_
#define HOLO_CMW_APPS_LOCALIZATION_VISION_BIRDVIEW_BIRDVIEW_MASK_H_

#include <holo/common/image.h>

namespace holo
{
namespace vision
{
/**
 * @brief create the birdview image by Splicing the surround camera image
 */
class BirdviewMask
{
public:
    typedef holo::float64_t Scalar;

    /**
     *@brief the necessary parameter for bridview mask
     */
    struct MaskParameter
    {
        Scalar min_x;                // x's minimum value of bird view area scope in world frame (unit mm)
        Scalar max_x;                // x's maximum value of bird view area scope in world frame (unit mm)
        Scalar min_y;                // y's minimum value of bird view area scope in world frame (unit mm)
        Scalar max_y;                // x's maximum value of bird view area scope in world frame (unit mm)
        Scalar milimeter_per_pixel;  // the resolution of the bird view image (the real distance (unit mm) of one pixel)
        Scalar half_max_theta;       // half of max angle between two boundaries of the overlapping region (unit radian)
    };

    /**
     * @brief Construct a new Birdview Mask object
     *
     * @param[in] parameters
     */
    BirdviewMask(MaskParameter const& parameters);

    /**
     * @brief Destroy the BirdviewShow object
     */
    ~BirdviewMask();

    /**
     * @brief compute the image mask
     *
     * @return cv::Mat
     */
    cv::Mat ComputeImageMask(std::vector<cv::Point> const& points) const;

protected:
    /**
     * @brief calculate the angle corresponding to vertex
     *
     * @param[in] pt1 one of the endpoints of the triangle
     * @param[in] pt2 the vertex of the triangle
     * @param[in] pt3 the other endpoint of the triangle
     * @return Scalar
     */
    Scalar calculateAngle(cv::Point const& pt1, cv::Point const& pt2, cv::Point const& pt3) const;

    /**
     * @brief calculate the point
     *
     * @param[in] point1
     * @param[in] point2
     * @param[in] angle
     * @return cv::Point
     */
    cv::Point calculatePoint(cv::Point const& point1, cv::Point const& point2, Scalar const angle) const;

    /**
     * @brief calculate boundary points
     *
     * @param[in] root_points
     */
    void calculateBoundaryPoints(std::vector<cv::Point>& root_points) const;

private:
    MaskParameter  parameters_;      // parameter related to bridview
    holo::uint16_t image_size_row_;  // birdview image rows num
    holo::uint16_t image_size_col_;  // birdview image cols num

};  // BirdviewMask

}  // namespace vision
}  // namespace holo

#endif