/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file surround_camera_calibration_visualize.h
 * @brief  header file for EOL Surround Camera Calibration Visualize
 * @author jiaxing zhao(zhaojiaxing@holomaitc.com)
 * @date "2021-08-2"
 */

#ifndef HOLO_CALIBRATION_CAMERA_FIELD_EOL_SURROUND_CAMERA_CALIBRATION_VISUALIZE_H_
#define HOLO_CALIBRATION_CAMERA_FIELD_EOL_SURROUND_CAMERA_CALIBRATION_VISUALIZE_H_

#include <holo/calibration/camera/field/eol_surround_camera_data_container.h>

namespace holo
{
namespace calibration
{
namespace camera
{
/**
 * @brief this class aims to Visualize surround calibration result
 */
class EOLSurroundCameraCalibrationVisualize
{
public:
    using Scalar = EOLSurroundCameraDataContainer::Scalar;
    /**
     * @brief Construct a new Surround Camera Calibration Visualize object
     *
     * @param[in] containers data containers used to do calibration
     */
    EOLSurroundCameraCalibrationVisualize(std::vector<EOLSurroundCameraDataContainer> const& containers);

    /**
     * @brief Destroy the Surround Camera Calibration object
     *
     */
    ~EOLSurroundCameraCalibrationVisualize();

    /**
     * @brief generate bird view image
     *
     * @param[in] min_x the minimum value along x-axis in vehicle frame [unit mm]
     * @param[in] max_x the maximum value along x-axis in vehicle frame [unit mm]
     * @param[in] min_y the minimum value along y-axis in vehicle frame [unit mm]
     * @param[in] max_y the maximum value along y-axis in vehicle frame [unit mm]
     * @param[in] front_length the distance from rear wheel to front [unit mm]
     * @param[in] rear_length the distance from rear wheel to tail [unit mm]
     * @param[in] half_width the distance from car's center to wheel [unit mm]
     * @param[in] milimeter_per_pixel the resolution of the bird view image (the real distance (unit mm) of one pixel)
     *            The larger the value, the smaller the image generated, the lower the resolution.
     * @param[in] visualization visualize aerial view image
     * @return cv::Mat bird view image
     */
    cv::Mat Visualize(Scalar const min_x, Scalar const max_x, Scalar const min_y, Scalar const max_y,
                      Scalar const front_length, Scalar const rear_length, Scalar const half_width,
                      Scalar const milimeter_per_pixel, bool_t const visualization) const;

protected:
    /**
     * @brief change the pixel color channel value
     * @details we change the color channel value of pixel of defferent camera (blue, green, red) for debugging
     * convenience.
     * @param[in] i container index
     * @param[in] containers_size the number of all containers
     * @param[in] pixel_color Modify object
     * @param[in] number_of_color the number of color channel
     * @return modified value
     */
    inline cv::Vec3b changeColorChannel(holo::uint8_t const& i, holo::uint8_t const& containers_size,
                                        cv::Vec3b const& pixel_color, holo::uint8_t const& number_of_color = 3) const;

    /**
     * @brief Judge whether the coordinates are in camera image area
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
    std::vector<EOLSurroundCameraDataContainer> containers_;  ///< data contaienrs

};  // EOLSurroundCameraCalibrationVisualize
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_CAMERA_FIELD_EOL_SURROUND_CAMERA_CALIBRATION_VISUALIZE_H_