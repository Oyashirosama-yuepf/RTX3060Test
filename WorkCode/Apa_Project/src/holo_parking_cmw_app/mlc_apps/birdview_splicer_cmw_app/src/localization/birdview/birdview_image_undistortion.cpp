/*!
 *  \brief birdview modular for image undistortion
 *  \author liwenhao
 *  \date 2020-8-18
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <localization/vision/birdview/birdview_image_undistortion.h>

namespace holo
{
namespace vision
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BirdviewImageUndistortion::BirdviewImageUndistortion(IntrinsicType const& instrinsic, cv::Mat const& K,
                                                     holo::uint16_t const& height, holo::uint16_t const& width)
  : intrinsic_(instrinsic), K_(K), height_(height), width_(width)
{
    map_row_ = cv::Mat::zeros(height_, width_, CV_32FC1);
    map_col_ = cv::Mat::zeros(height_, width_, CV_32FC1);
    init();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BirdviewImageUndistortion::~BirdviewImageUndistortion()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BirdviewImageUndistortion::init()
{
    cv::Mat inv_K;
    cv::invert(K_, inv_K);  // K^-1

    for (holo::uint16_t row = 0; row < height_; row++)
    {
        for (holo::uint16_t col = 0; col < width_; col++)
        {
            Scalar                    normalize_plane_coord_x = inv_K.at<Scalar>(0, 0) * col + inv_K.at<Scalar>(0, 2);
            Scalar                    normalize_plane_coord_y = inv_K.at<Scalar>(1, 1) * row + inv_K.at<Scalar>(1, 2);
            Scalar                    normalize_plane_coord_z = 1;
            IntrinsicType::Point3Type x_y_z(normalize_plane_coord_x, normalize_plane_coord_y, normalize_plane_coord_z);
            IntrinsicType::Point2Type distorted_u_v;
            intrinsic_.Project(x_y_z, distorted_u_v);
            map_row_.at<holo::float32_t>(row, col) = distorted_u_v.GetY();
            map_col_.at<holo::float32_t>(row, col) = distorted_u_v.GetX();
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BirdviewImageUndistortion::Undistort(cv::Mat const& in, cv::Mat& out) const
{
    // cv::Mat undistorted_img  bgr
    out = cv::Mat::zeros(height_, width_, CV_8UC3);
    cv::remap(in, out, map_col_, map_row_, cv::INTER_LINEAR, cv::BORDER_CONSTANT);
}

}  // namespace vision
}  // namespace holo
