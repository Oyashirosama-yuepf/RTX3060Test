/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file surround_camera_calibration_with_ocam.h
 * @brief  header file for surround camera calibration
 * @author jiaxing zhao(zhaojiaxing@holomaitc.com)
 * @date "2021-07-31"
 */

#ifndef HOLO_CALIBRATION_CAMERA_FIELD_EOL_PROJECT_EOL_SURROUND_CAMERA_CALIBRATION_WITH_OCAM_H_
#define HOLO_CALIBRATION_CAMERA_FIELD_EOL_PROJECT_EOL_SURROUND_CAMERA_CALIBRATION_WITH_OCAM_H_

#include <holo/calibration/camera/field/eol_project/eol_surround_camera_data_container_with_ocam.h>

namespace holo
{
namespace calibration
{
namespace camera
{
/**
 * @brief this class aims to do extrinsic and homography matrix computation
 */
class EOLSurroundCameraCalibrationWithOcam
{
public:
    using Scalar = EOLSurroundCameraCalibrationDataContainer::Scalar;

    /**
     * @brief Construct a new Surround Camera Calibration object
     *
     * @param[in] containers data containers used to do calibration
     */
    EOLSurroundCameraCalibrationWithOcam(std::vector<EOLSurroundCameraCalibrationDataContainer> const& containers);

    /**
     * @brief Destroy the Surround Camera Calibration object
     *
     */
    ~EOLSurroundCameraCalibrationWithOcam();

    /**
     * @brief calculate Homography matrix
     *
     * @return true the calibration succeed
     * @return false the calibration failed
     */
    bool_t Compute();

    /**
     * @brief Get containers
     *
     * @true containers
     */
    std::vector<EOLSurroundCameraCalibrationDataContainer> const& GetContainers() const
    {
        return containers_;
    }

    /**
     * @brief save calibration result
     * @param[in] output_dir output directory
     */
    bool_t Save(std::string const& output_dir);

    /**
     * @brief Get the App Error Status object
     *
     * @param status
     * @return uint32_t
     */
    AppErrorStatus GetAppErrorStatus()
    {
        return app_error_status_;
    }

protected:
    /**
     * @brief compute homography matrix     pixel -> world
     * @param[in] container data container
     * @return cv::Mat homography matrix   pixel -> world
     */
    cv::Mat computeHomographyMatrix(EOLSurroundCameraCalibrationDataContainer const& container) const;

    /**
     * @brief compute pose of the camera in world frame
     * @param[in] container data container
     * @return pose of camera in world frame
     */
    Pose3 computePose(EOLSurroundCameraCalibrationDataContainer const& container) const;

    /**
     * @brief save a mat in a file
     * @param[in] ofile ofstream object
     * @param[in] matrix target to store
     * @param[in] name the name of the matrix
     */
    template <typename T>
    void saveMat(std::ofstream& ofile, cv::Mat const& matrix, std::string name) const;

private:
    /**
     * @brief data contaienrs
     *
     */
    std::vector<EOLSurroundCameraCalibrationDataContainer> containers_;

    /**
     * @brief app error status
     *
     */
    AppErrorStatus app_error_status_;

};  // EOLSurroundCameraCalibrationWithOcam
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_CAMERA_FIELD_EOL_PROJECT_EOL_SURROUND_CAMERA_CALIBRATION_WITH_OCAM_H_