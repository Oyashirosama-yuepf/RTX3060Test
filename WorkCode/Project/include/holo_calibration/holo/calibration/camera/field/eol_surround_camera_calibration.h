/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file surround_camera_calibration.h
 * @brief  header file for surround camera calibration
 * @author jiaxing zhao(zhaojiaxing@holomaitc.com)
 * @date "2021-07-31"
 */

#ifndef HOLO_CALIBRATION_CAMERA_FIELD_EOL_SURROUND_CAMERA_CALIBRATION_H_
#define HOLO_CALIBRATION_CAMERA_FIELD_EOL_SURROUND_CAMERA_CALIBRATION_H_

#include <holo/calibration/camera/field/eol_surround_camera_data_container.h>

namespace holo
{
namespace calibration
{
namespace camera
{
/**
 * @brief this class aims to do homography matrix computation
 */
class EOLSurroundCameraCalibration
{
public:
    using Scalar = EOLSurroundCameraDataContainer::Scalar;
    /**
     * @brief Construct a new Surround Camera Calibration object
     *
     * @param[in] containers data containers used to do calibration
     */
    EOLSurroundCameraCalibration(std::vector<EOLSurroundCameraDataContainer> const& containers);

    /**
     * @brief Destroy the Surround Camera Calibration object
     *
     */
    ~EOLSurroundCameraCalibration();

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
    std::vector<EOLSurroundCameraDataContainer> const& GetContainers() const
    {
        return containers_;
    }

    /**
     * @brief save calibration result
     * @param[in] output_dir output directory
     */
    void Save(std::string const& output_dir);

protected:
    /**
     * @brief compute homography matrix     pixel -> world
     * @param[in] container data container
     * @return cv::Mat homography matrix   pixel -> world
     */
    cv::Mat computeHomographyMatrix(EOLSurroundCameraDataContainer const& container) const;

    /**
     * @brief compute pose of the camera in world frame
     * @param[in] container data container
     * @return pose of camera in world frame
     */
    Pose3 computePose(EOLSurroundCameraDataContainer const& container) const;

    /**
     * @brief save a mat in a file
     * @param[in] ofile ofstream object
     * @param[in] matrix target to store
     * @param[in] name the name of the matrix
     */
    template <typename T>
    void saveMat(std::ofstream& ofile, cv::Mat const& matrix, std::string name) const;

private:
    std::vector<EOLSurroundCameraDataContainer> containers_;  ///< data contaienrs

};  // EOLSurroundCameraCalibration
}  // namespace camera
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_CAMERA_FIELD_EOL_SURROUND_CAMERA_CALIBRATION_H_