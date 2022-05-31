/*!
 *  \brief birdview image show
 *  \author liwenhao
 *  \date  2020-8-18
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_CMW_APPS_LOCALIZATION_VISION_BIRDVIEW_BIRDVIEW_SHOW_H_
#define HOLO_CMW_APPS_LOCALIZATION_VISION_BIRDVIEW_BIRDVIEW_SHOW_H_

#include <holo/common/image.h>
#include <holo/common/intrinsic.h>
#include <localization/vision/birdview/birdview_mask.h>

namespace holo
{
namespace vision
{
/**
 * @brief create the birdview image by Splicing the surround camera image
 */
class BirdviewShow
{
public:
    typedef holo::float64_t Scalar;
    typedef holo::common::OmnidirectionalIntrinsicT<Scalar> IntrinsicType;

    /**
     *@brief the necessary parameter for bridview image
     */
    struct BirdviewParameter
    {
        std::vector<cv::Mat> Hs;                // H matrix of all camera    pixel->world
        std::vector<cv::Mat> Ks;                // K matrix of all undistorted image
        std::vector<Scalar>  images_rows;       // row size of all undistorted image
        std::vector<Scalar>  images_cols;       // col size of all undistorted image
        Scalar               min_x;             // x's minimum value of bird view area scope in world frame (unit mm)
        Scalar               max_x;             // x's maximum value of bird view area scope in world frame (unit mm)
        Scalar               min_y;             // y's minimum value of bird view area scope in world frame (unit mm)
        Scalar               max_y;             // x's maximum value of bird view area scope in world frame (unit mm)
        Scalar               car_front_length;  // the distance of car's back wheel to head (unit mm)
        Scalar               car_rear_length;   // the distance of car's back wheel to tail (unit mm)
        Scalar               car_half_width;    // the half distance of car's two back wheel (unit mm)
        Scalar milimeter_per_pixel;  // the resolution of the bird view image (the real distance (unit mm) of one pixel)
    };

    /**
     * @brief construct function
     * @param[in] parameters bridview image parameter
     * @param[in] masks image mask to provide weight of pixel
     * @param[in] intrinsics intrinsic for each camera
     */
    BirdviewShow(BirdviewParameter const& parameters, std::vector<cv::Mat> const& masks,
                 std::vector<IntrinsicType> const& intrinsics = std::vector<IntrinsicType>());

    /**
     * @brief Destroy the BirdviewShow object
     */
    ~BirdviewShow();

    /**
     * @brief create brid view image
     * @param[in] images all images , the number of the input images should equal with Hs.size() in parameters_ and the
     * image should be undistorted
     * @param[out] result image
     */
    cv::Mat Compute(std::vector<cv::Mat> const& images) const;

    /**
     * @brief get the Interpolated pixel value from image
     * @param[in] image source image
     * @param[in] x origin coordinate value x
     * @param[in] y origin coordinate value y
     * @param[out] pixel value after Interpolation
     */
    static cv::Vec3b BilinearInterpolation(cv::Mat const& image, Scalar const& x, Scalar const& y);

protected:
    /**
     * @brief called in construct function, to calculate the Mapping table
     */
    bool init();

    /**
     * @brief Judge whether the coordinate is in camera image area
     * @param[in] x input coordinates x
     * @param[in] y input coordinates y
     * @param[in] max_x max x of the range of area
     * @param[in] max_y max y of the range of area
     * @param[in] min_x min x of the range of area
     * @param[in] min_y min y of the range of area
     * @return true or false
     */
    bool isInArea(Scalar const& x, Scalar const& y, Scalar const& max_x, Scalar const& max_y, Scalar const& min_x = 0,
                  Scalar const& min_y = 0) const;

private:
    BirdviewParameter          parameters_;           // parameter related to bridview
    std::vector<cv::Mat>       maps_row_;             // all map table (row,col) -> (row) for each camera
    std::vector<cv::Mat>       maps_col_;             // all map table (row,col) -> (col) for each camera
    holo::uint16_t             birdview_size_row_;    // birdview image rows num
    holo::uint16_t             birdview_size_col_;    // birdview image cols num
    holo::uint16_t             birdview_center_row_;  // birdview image  center's rows num
    holo::uint16_t             birdview_center_col_;  // birdview image  center's cols num
    std::vector<cv::Mat>       masks_;                // image masks
    std::vector<IntrinsicType> intrinsics_;           // camera intrinsics

};  // BirdviewShow

}  // namespace vision
}  // namespace holo

#endif  // HOLO_VISION_BIRDVIEW_BIRDVIEW_SHOW_H_
