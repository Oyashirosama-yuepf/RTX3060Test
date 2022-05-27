/*!
 *  \brief source file of birdview image show
 *  \author liwenhao
 *  \date 2020-8-18
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <glog/logging.h>
#include <localization/vision/birdview/birdview_image_undistortion.h>
#include <localization/vision/birdview/birdview_show.h>

namespace holo
{
namespace vision
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BirdviewShow::BirdviewShow(BirdviewParameter const& parameters, std::vector<cv::Mat> const& masks,
                           std::vector<IntrinsicType> const& intrinsics)
  : parameters_(parameters), masks_(masks), intrinsics_(intrinsics)
{
    birdview_size_col_   = (parameters_.max_x - parameters_.min_x) / parameters_.milimeter_per_pixel;  // col pixel num
    birdview_size_row_   = (parameters_.max_y - parameters_.min_y) / parameters_.milimeter_per_pixel;  // row pixel num
    birdview_center_col_ = (-parameters_.min_x) / parameters_.milimeter_per_pixel;
    birdview_center_row_ = parameters_.max_y / parameters_.milimeter_per_pixel;
    init();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BirdviewShow::~BirdviewShow()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BirdviewShow::init()
{
    bool const           use_original_image = !intrinsics_.empty();
    std::vector<cv::Mat> inv_Hs;
    std::vector<cv::Mat> inv_Ks;

    for (holo::uint16_t i = 0u; i < parameters_.Hs.size(); i++)
    {
        cv::Mat init_map(birdview_size_row_, birdview_size_col_, CV_64FC1, cv::Scalar(-1));
        maps_row_.push_back(init_map.clone());
        maps_col_.push_back(init_map.clone());

        // world -> pixel
        cv::Mat inv_H;
        cv::invert(parameters_.Hs[i], inv_H);
        inv_Hs.push_back(inv_H);

        // inv camera matrix
        if (use_original_image)
        {
            cv::Mat inv_K;
            cv::invert(parameters_.Ks[i], inv_K);
            inv_Ks.push_back(inv_K);
        }
    }

    // find the right camera viewpoint for each pixel
    for (holo::uint16_t row = 0u; row < birdview_size_row_; row++)  // row
    {
        for (holo::uint16_t col = 0u; col < birdview_size_col_; col++)  // col
        {
            // Convert the pixel pos of aerial_view img to world coordinates
            cv::Mat world_coords(3, 1, CV_64FC1);  // x,y,1
            world_coords.at<Scalar>(0, 0) = (col - birdview_center_col_) * parameters_.milimeter_per_pixel;
            world_coords.at<Scalar>(1, 0) = (birdview_center_row_ - row) * parameters_.milimeter_per_pixel;
            world_coords.at<Scalar>(2, 0) = 1;

            // skip this pixel if the coordinates fall into car area
            if (isInArea(world_coords.at<Scalar>(0, 0), world_coords.at<Scalar>(1, 0), parameters_.car_half_width,
                         parameters_.car_front_length, -parameters_.car_half_width, -parameters_.car_rear_length))
            {
                continue;
            }

            // world -> camera_pixel
            // check all the H matrix, and find the right one
            for (holo::uint16_t i = 0u; i < parameters_.Hs.size(); i++)
            {
                cv::Mat pixel_coords(3, 1, CV_64FC1);
                pixel_coords = inv_Hs[i] * world_coords;  // inv_Hs : world -> pixel  ,  pixel_coords: x-cols, y-rows
                // filter the incorrect point, because we have set H=-H while pixel_coords.at<Scalar>(2, 0) < 0,
                // so the pixel_coords.at<Scalar>(2, 0)<0 is impossible, unless it is a wrong case. e.g. (z<0, x,y<0)
                if (pixel_coords.at<Scalar>(2, 0) < 0)
                {
                    continue;
                }

                // normalize
                pixel_coords.at<Scalar>(0, 0) = pixel_coords.at<Scalar>(0, 0) / pixel_coords.at<Scalar>(2, 0);
                pixel_coords.at<Scalar>(1, 0) = pixel_coords.at<Scalar>(1, 0) / pixel_coords.at<Scalar>(2, 0);

                // Judge whether the coordinates are correct
                if (isInArea(pixel_coords.at<Scalar>(0, 0), pixel_coords.at<Scalar>(1, 0),
                             parameters_.images_cols[i] - 1, parameters_.images_rows[i] - 1))
                {
                    if (use_original_image)
                    {
                        cv::Mat const& inv_K = inv_Ks.at(i);
                        Scalar         normalize_plane_coord_x =
                            inv_K.at<Scalar>(0, 0) * pixel_coords.at<Scalar>(0, 0) + inv_K.at<Scalar>(0, 2);
                        Scalar normalize_plane_coord_y =
                            inv_K.at<Scalar>(1, 1) * pixel_coords.at<Scalar>(1, 0) + inv_K.at<Scalar>(1, 2);
                        Scalar                    normalize_plane_coord_z = 1;
                        IntrinsicType::Point3Type x_y_z(normalize_plane_coord_x, normalize_plane_coord_y,
                                                        normalize_plane_coord_z);
                        IntrinsicType::Point2Type distorted_u_v;
                        intrinsics_.at(i).Project(x_y_z, distorted_u_v);
                        maps_col_[i].at<Scalar>(row, col) = distorted_u_v.GetX();
                        maps_row_[i].at<Scalar>(row, col) = distorted_u_v.GetY();
                    }
                    else
                    {
                        maps_col_[i].at<Scalar>(row, col) = pixel_coords.at<Scalar>(0, 0);
                        maps_row_[i].at<Scalar>(row, col) = pixel_coords.at<Scalar>(1, 0);
                    }
                }
            }
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat BirdviewShow::Compute(std::vector<cv::Mat> const& images) const
{
    if (images.size() != parameters_.Hs.size())
    {
        LOG(ERROR) << "Images number is not enoungh!";
        std::runtime_error("Images input error");
    }

    cv::Mat bird_view_img(birdview_size_row_, birdview_size_col_, CV_8UC3, cv::Scalar(0, 0, 0));

    // find the right camera viewpoint for each pixel
    for (holo::uint16_t row = 0u; row < birdview_size_row_; row++)  // row
    {
        for (holo::uint16_t col = 0u; col < birdview_size_col_; col++)  // col
        {
            cv::Vec3d pixel_sum_value(0, 0, 0);
            Scalar    weight_sum = 0.0;

            for (holo::uint16_t id = 0u; id < maps_col_.size(); id++)
            {
                if (maps_col_[id].at<Scalar>(row, col) >= 0 && maps_row_[id].at<Scalar>(row, col) >= 0)
                {
                    Scalar const weight_i = masks_[id].at<Scalar>(row, col);
                    weight_sum += weight_i;
                    pixel_sum_value += weight_i * BilinearInterpolation(images[id], maps_col_[id].at<Scalar>(row, col),
                                                                        maps_row_[id].at<Scalar>(row, col));
                }
            }

            bird_view_img.at<cv::Vec3b>(row, col) = pixel_sum_value / weight_sum;
        }
    }

    return bird_view_img;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BirdviewShow::isInArea(Scalar const& x, Scalar const& y, Scalar const& max_x, Scalar const& max_y,
                            Scalar const& min_x, Scalar const& min_y) const
{
    return x <= max_x && x >= min_x && y <= max_y && y >= min_y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Vec3b BirdviewShow::BilinearInterpolation(cv::Mat const& image, Scalar const& x, Scalar const& y)
{
    holo::uint16_t image_height = image.rows;
    holo::uint16_t image_width  = image.cols;
    holo::int16_t  low_x        = cvFloor(x);
    Scalar         dx           = x - low_x;

    if (low_x > image_width - 2)
    {
        low_x = image_width - 2;
    }
    else if (low_x < 0)
    {
        low_x = 0;
    }

    holo::int16_t low_y = cvFloor(y);
    Scalar        dy    = y - low_y;

    if (low_y > image_height - 2)
    {
        low_y = image_height - 2;
    }
    else if (low_y < 0)
    {
        low_y = 0;
    }

    holo::uint16_t k_x[2];
    holo::uint16_t k_y[2];
    // Multiply 2048 to convert a variable from a floating to an integer, it could accelerate the calculation
    k_x[0] = cv::saturate_cast<holo::uint16_t>((1.0 - dx) * 2048);
    k_x[1] = 2048 - k_x[0];
    k_y[0] = cv::saturate_cast<holo::uint16_t>((1.0 - dy) * 2048);
    k_y[1] = 2048 - k_y[0];

    cv::Vec3b result_pixel;
    result_pixel[0] = (image.at<cv::Vec3b>(low_y, low_x)[0] * k_x[0] * k_y[0] +
                       image.at<cv::Vec3b>(low_y, low_x + 1)[0] * k_x[1] * k_y[0] +
                       image.at<cv::Vec3b>(low_y + 1, low_x)[0] * k_x[0] * k_y[1] +
                       image.at<cv::Vec3b>(low_y + 1, low_x + 1)[0] * k_x[1] * k_y[1]) >>
                      22;
    result_pixel[1] = (image.at<cv::Vec3b>(low_y, low_x)[1] * k_x[0] * k_y[0] +
                       image.at<cv::Vec3b>(low_y, low_x + 1)[1] * k_x[1] * k_y[0] +
                       image.at<cv::Vec3b>(low_y + 1, low_x)[1] * k_x[0] * k_y[1] +
                       image.at<cv::Vec3b>(low_y + 1, low_x + 1)[1] * k_x[1] * k_y[1]) >>
                      22;
    result_pixel[2] = (image.at<cv::Vec3b>(low_y, low_x)[2] * k_x[0] * k_y[0] +
                       image.at<cv::Vec3b>(low_y, low_x + 1)[2] * k_x[1] * k_y[0] +
                       image.at<cv::Vec3b>(low_y + 1, low_x)[2] * k_x[0] * k_y[1] +
                       image.at<cv::Vec3b>(low_y + 1, low_x + 1)[2] * k_x[1] * k_y[1]) >>
                      22;

    return result_pixel;
}

}  // namespace vision
}  // namespace holo
