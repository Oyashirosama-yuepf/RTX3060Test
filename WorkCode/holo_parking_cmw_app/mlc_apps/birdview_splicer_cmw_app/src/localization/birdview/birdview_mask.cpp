/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file birdview_mask.cpp
 * @brief This header file defines mask of birdview image.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2020-12-21"
 */

#include <holo/geometry/angle.h>
#include <localization/vision/birdview/birdview_mask.h>

namespace holo
{
namespace vision
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BirdviewMask::BirdviewMask(MaskParameter const& parameters) : parameters_(parameters)
{
    image_size_col_ = (parameters_.max_x - parameters_.min_x) / parameters_.milimeter_per_pixel;  // col pixel num
    image_size_row_ = (parameters_.max_y - parameters_.min_y) / parameters_.milimeter_per_pixel;  // row pixel num
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BirdviewMask::~BirdviewMask()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat BirdviewMask::ComputeImageMask(std::vector<cv::Point> const& points) const
{
    std::vector<cv::Point> root_points;  // the input point set

    for (uint8_t i = 0u; i < points.size(); i++)
    {
        cv::Point point_new((points[i].x - parameters_.min_x) / parameters_.milimeter_per_pixel,
                            (-points[i].y + parameters_.max_y) / parameters_.milimeter_per_pixel);

        if (point_new.x < 0)
        {
            point_new.x = 0;
        }

        if (point_new.x >= image_size_col_)
        {
            point_new.x = image_size_col_ - 1;
        }

        if (point_new.y < 0)
        {
            point_new.y = 0;
        }

        if (point_new.y >= image_size_row_)
        {
            point_new.y = image_size_row_ - 1;
        }

        root_points.push_back(point_new);
    }

    calculateBoundaryPoints(root_points);

    uint8_t          size    = root_points.size();
    int32_t          npt[]   = {size};
    const cv::Point* ppt[1u] = {root_points.data()};

    cv::Mat mask(image_size_row_, image_size_col_, CV_64FC1);
    mask.setTo(cv::Scalar::all(0.0));
    cv::fillPoly(mask, ppt, npt, 1, cv::Scalar(1.0));

    for (uint16_t row = 0u; row < mask.rows; row++)
    {
        for (uint16_t col = 0u; col < mask.cols; col++)
        {
            cv::Point point(col, row);

            Scalar angle_left  = calculateAngle(root_points[0u], root_points[1u], point);
            Scalar angle_right = calculateAngle(root_points[3u], root_points[2u], point);

            if (angle_left <= 2 * parameters_.half_max_theta)
            {
                mask.at<Scalar>(row, col) = mask.at<Scalar>(row, col) * angle_left / (2 * parameters_.half_max_theta);
            }

            if (angle_right <= 2 * parameters_.half_max_theta)
            {
                mask.at<Scalar>(row, col) = mask.at<Scalar>(row, col) * angle_right / (2 * parameters_.half_max_theta);
            }
        }
    }

    return mask;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BirdviewMask::Scalar BirdviewMask::calculateAngle(cv::Point const& pt1, cv::Point const& pt2,
                                                  cv::Point const& pt3) const
{
    Scalar distance_12 = cv::norm(pt1 - pt2);
    Scalar distance_23 = cv::norm(pt2 - pt3);
    Scalar distance_31 = cv::norm(pt3 - pt1);

    Scalar numerator   = distance_12 * distance_12 + distance_23 * distance_23 - distance_31 * distance_31;
    Scalar denominator = 2 * distance_12 * distance_23;

    return std::abs(std::acos(numerator / denominator));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Point BirdviewMask::calculatePoint(cv::Point const& point1, cv::Point const& point2, Scalar const angle) const
{
    cv::Point output_point;

    if (point1.y == 0 || point1.y == image_size_row_ - 1)
    {
        Scalar tmp_x = (point1.y - point2.y) * std::tan(angle) + point2.x;

        if (tmp_x >= 0 && tmp_x < image_size_col_)
        {
            output_point.y = point1.y;
            output_point.x = tmp_x;
        }
    }

    if (point1.x == 0 || point1.x == image_size_col_ - 1)
    {
        Scalar tmp_y = (point1.x - point2.x) / std::tan(angle) + point2.y;

        if (tmp_y >= 0 && tmp_y < image_size_row_)
        {
            output_point.x = point1.x;
            output_point.y = tmp_y;
        }
    }

    return output_point;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BirdviewMask::calculateBoundaryPoints(std::vector<cv::Point>& root_points) const
{
    // Compute left point
    int16_t delta_u_left = root_points[0u].y - root_points[1u].y;
    int16_t delta_v_left = root_points[0u].x - root_points[1u].x;
    Scalar  alpha_left   = std::atan2(delta_v_left, delta_u_left) + parameters_.half_max_theta;
    root_points[0u]      = calculatePoint(root_points[0u], root_points[1u], alpha_left);

    // Compute right point
    int16_t delta_u_right = root_points[3u].y - root_points[2u].y;
    int16_t delta_v_right = root_points[3u].x - root_points[2u].x;
    Scalar  alpha_right   = std::atan2(delta_v_right, delta_u_right) - parameters_.half_max_theta;
    root_points[3u]       = calculatePoint(root_points[3u], root_points[2u], alpha_right);
}

}  // namespace vision
}  // namespace holo