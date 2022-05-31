/*
 * Copyright (C) HoloMatic Technology (Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file distortion_coefficients_fitting.h
 * @brief Fitting distortion coefficients of different camera models by camera's datasheet
 * @author chenbin@holomatic.com (Bin Chen)
 * @date 2021-11-08
 */

#ifndef HOLO_CALIBRATION_DEV_DISTORTION_COEFFICIENTS_FITTING_H_
#define HOLO_CALIBRATION_DEV_DISTORTION_COEFFICIENTS_FITTING_H_

#include <holo/calibration/camera/field/types.h>

namespace holo
{
namespace calibration
{
namespace camera
{

/**
 * @addtogroup camera
 * @{
 *
 */

/**
 * @brief A class aims at fit distortion coefficients of different camera models by 
 *  camera's datasheet(usually supplied by the camera manufacturer)
 * 
 * @details currently, only the FISHEYE and OMNIDIRECTIONAL camera model are supported.
 *  for OMNIDIRECTIONAL the forward/inverse polynomial coefficients will be fitted!!!
 */

class DistortionCoefficientsFitter
{
public:
    using uint16_t               = ::holo::uint16_t;
    using CameraIntrinsicBasePtr = std::shared_ptr<CameraIntrinsicBase>;

    /**
     * @brief Calibration result
     */
    struct Result
    {
        CameraIntrinsicBasePtr intrinsic_ptr;          ///< camera's intrisnic
        Scalar                 average_fitting_error;  ///< fitting error (unit pixel)
        bool_t                 is_fitting_success;     ///< distortion coefficients fitting flag

        /**
         * @brief Constructor
         * 
         * @param[in] _intrinsic_ptr camera's intrisnic
         * @param[in] _average_fitting_error distortion coefficients fitting error
         * @param[in] _is_fitting_success whether the fitting is successful
         */
        Result(CameraIntrinsicBasePtr const _intrinsic_ptr,
               Scalar const _average_fitting_error, bool_t const _is_fitting_success)
        : intrinsic_ptr(_intrinsic_ptr)
        , average_fitting_error(_average_fitting_error)
        , is_fitting_success(_is_fitting_success)
        {
        }

    }; /// Result

    /**
     * @brief Constructor
     * 
     * @param[in] camera_model fitting camera model, such as FISHEYE, OMNIDIRECTIONAL and PINHOLE(supported later)
     */
    DistortionCoefficientsFitter(CameraModel const& camera_model)
    : camera_model_(camera_model)
    {
    }

    /**
     * @brief Destructor
     */
    ~DistortionCoefficientsFitter() noexcept
    {
    }

    /**
     * @brief Core function about distortion coefficients fitting, you can get the distortion coefficient 
     *  of this camera by calling this function
     * 
     * @param[in] multi_theta angle between the principal axis and the incoming ray [unit: degree]
     * @param[in] multi_img_real_height real image height in sensor plane [unit: metric, such as mm]
     * @param[in] focal_length camera focal length [unit: metric, such as mm]
     * @param[in] pixel_size size of camera's pixel, usually expressed in microns [unit: um/pixel]
     * @param[in] order taylor order for OMNIDIRECTIONAL and number of k for FISHEYE
     * @param[in] error_threshold threshold value of fitting error
     * 
     * @return distortion coefficients fitting result and fitting error(in pixel)
     * 
     * @warning For FISHEYE model, the maximum number of distortion coefficients is 4 (number_of_k <=4 )
     *          For OMNIDIRECTIONAL model, the maximum order is 5 and minimum order is 3
     */
    Result Run(std::vector<Scalar> const& multi_theta, std::vector<Scalar> const& multi_img_real_height,
               Scalar const focal_length, Scalar const pixel_size,
               uint16_t const order, Scalar const error_threshold) const;

    /**
     * @brief \overload function about distortion coefficients fitting, you can get the distortion coefficient 
     *  of this camera by calling this function
     * 
     * @param[in] multi_theta angle between the principal axis and the incoming ray [unit: rad]
     * @param[in] multi_normalized_real_height real image height in normalized plane [unit: NULL]
     * @param[in] focal_length_in_pixel focal length which is discretized in pixel [unit: pixel]
     * @param[in] order taylor order for OMNIDIRECTIONAL and number of k for FISHEYE
     * @param[in] error_threshold threshold value of fitting error
     * 
     * @return distortion coefficients fitting result and fitting error(in pixel)
     * 
     * @warning For FISHEYE model, the maximum number of distortion coefficients is 4 (number_of_k <=4 )
     *          For OMNIDIRECTIONAL model, the maximum order is 5 and minimum order is 3
     */
    Result Run(std::vector<Scalar> const& multi_theta, std::vector<Scalar> const& multi_normalized_real_height,
               Scalar const focal_length_in_pixel, uint16_t const order, Scalar const error_threshold) const;

private:
    /**
     * @brief Fisheye camera's distortion coefficients fitting
     * 
     * @param[in] multi_theta angle between the principal axis and the incoming ray [unit: rad]
     * @param[in] multi_normalized_real_height real image height in normalized plane [unit: NULL]
     * @param[in] order number of k for FISHEYE
     * @param[in] error_threshold threshold value of fitting error
     * 
     * @return distortion coefficients fitting result and fitting error(in pixel)
     * 
     * @warning the maximum number of distortion coefficients is 4 (number_of_k <=4 )
     */
    Result fitFisheyeModel(std::vector<Scalar> const& multi_theta,
                           std::vector<Scalar> const& multi_normalized_real_height,
                           uint16_t const number_of_k, Scalar const error_threshold) const;

    /**
     * @brief OMNIDIRECTIONAL camera's distortion coefficients fitting
     * 
     * @param[in] multi_theta angle between the principal axis and the incoming ray [unit: rad]
     * @param[in] multi_normalized_real_height real image height in normalized plane [unit: NULL]
     * @param[in] focal_length_in_pixel focal length which is discretized in pixel [unit: pixel]
     * @param[in] order taylor order for OMNIDIRECTIONAL
     * @param[in] error_threshold threshold value of fitting error
     * 
     * @return distortion coefficients fitting result and fitting error(in pixel)
     * 
     * @warning the maximum order of distortion coefficients is 5 and minimum order is 3
     */
    Result fitOcamModel(std::vector<Scalar> const& multi_theta,
                        std::vector<Scalar> const& multi_normalized_real_height, Scalar const focal_length_in_pixel,
                        uint16_t const taylor_order, Scalar const error_threshold) const;

    /**
     * @brief camera model
     */
    CameraModel const camera_model_;

}; // DistortionCoefficientsFitter

/**
 * @}
 *
 */

} // namespace camera
} // namespace calibration
} // namespace holo

#endif // HOLO_CALIBRATION_DEV_DISTORTION_COEFFICIENTS_FITTING_H_