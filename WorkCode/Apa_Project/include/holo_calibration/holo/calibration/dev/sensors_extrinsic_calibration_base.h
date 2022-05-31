/*
 * Copyright (C) HoloMatic Technology (Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sensors_extrinsic_calibration_base.h
 * @brief Base class for sensors extrinsic calibration
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2021-11-29
 */

#ifndef HOLO_CALIBRATION_DEV_SENSORS_EXTRINSIC_CALIBRATION_BASE_H_
#define HOLO_CALIBRATION_DEV_SENSORS_EXTRINSIC_CALIBRATION_BASE_H_

#include <holo/3d/common/common.h>
#include <holo/3d/common/kdtree.h>
#include <holo/calibration/dev/common_function.h>
#include <holo/calibration/dev/common_types.h>
#include <holo/common/details/extrinsic.h>
#include <holo/core/types.h>

namespace holo
{
namespace calibration
{
/**
 * @brief Base class for sensors extrinsic calibration
 *
 */
class SensorsExtrinsicCalibrationBase
{
public:
    /**
     * @brief Disable default constructor
     */
    SensorsExtrinsicCalibrationBase() = delete;

    /**
     * @brief Advanced constructor
     *
     * @param[in] verbose Whether print verbose log.
     * @param[in] visualize Whether visualize crucial processes.
     */
    explicit SensorsExtrinsicCalibrationBase(bool_t const verbose = false, bool_t const visualize = false)
      : is_init_extrinsic_(false), extrinsic_(Pose3::Identity()), verbose_(verbose), visualize_(visualize)
    {
        LOG_IF(INFO, verbose_) << "SensorsExtrinsicCalibrationBase --- Call advanced constructor";
    }

    /**
     * @brief Destructor
     */
    virtual ~SensorsExtrinsicCalibrationBase() noexcept = default;

    /**
     * @brief Interface for extrinsic calibration
     *
     * @return True, if success, otherwise, false.
     */
    virtual bool_t Compute() = 0;

    /**
     * @brief Set extrinsic
     *
     * @param[in] extrinsic Extrinsic of a pair of sensors
     */
    void SetExtrinsic(Pose3 const& extrinsic)
    {
        extrinsic_         = extrinsic;
        is_init_extrinsic_ = true;
    }

    /**
     * @brief Get extrinsic
     *
     * @return Extrinsic of a pair of sensors
     */
    Pose3 GetExtrinsic() const
    {
        return extrinsic_;
    }

    /**
     * @brief Save extrinsic to file
     *
     * @param[in] file_name Path of extrinsic file
     * @param[in] parent_coordinate parent sensor coordinate
     * @param[in] child_coordinate child sensor coordinate
     */
    void SaveExtrinsic(std::string const& file_path, uint32_t const parent_coordinate,
                       uint32_t const child_coordinate) const;

protected:
    bool_t is_init_extrinsic_;  ///< Whether initialized extrinsic.
    Pose3  extrinsic_;          ///< Extrinsic of a pair of sensors
    bool_t verbose_;            ///< Whether print verbose log.
    bool_t visualize_;          ///< Whether visualize crucial processes.
};
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_SENSORS_EXTRINSIC_CALIBRATION_BASE_H_
