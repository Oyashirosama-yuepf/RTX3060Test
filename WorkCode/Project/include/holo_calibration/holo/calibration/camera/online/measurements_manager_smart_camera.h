/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file measurements_manager_smart_camera.h
 * @author jiaxing. zhao
 * @brief main function for smart camera calibration
 * @date 2020-08-25
 */

#ifndef HOLO_CALIBRATION_CAMERA_ONLINE_MEASUREMENTS_MANAGER_SMART_CAMERA_H_
#define HOLO_CALIBRATION_CAMERA_ONLINE_MEASUREMENTS_MANAGER_SMART_CAMERA_H_

#include <mutex>

#include <holo/calibration/camera/online/types.h>
#include <holo/localization/common/measurements_manager_base.h>

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
 * @brief Manage measurement queues of smart camera calibration online
 *
 */
class MeasurementsManagerSmartCamera : public holo::localization::MeasurementsManagerBase
{
public:
    using Base                = holo::localization::MeasurementsManagerBase;
    using RoadFrameBufferType = Base::RoadFrameBufferType;
    using Ptr                 = std::shared_ptr<MeasurementsManagerSmartCamera>;
    using ConstPtr            = std::shared_ptr<const MeasurementsManagerSmartCamera>;

    /**
     * @brief measurement manager parameters
     */
    struct Parameters
    {
    };

    /**
     * @brief Construct a new Measurements Manager object
     */
    MeasurementsManagerSmartCamera();

    /**
     * @brief Destroy the Measurements Manager object
     */
    virtual ~MeasurementsManagerSmartCamera() noexcept;

    /**
     * @brief Push the smart road frames into queue, pop out outdated measurements, then sort them in
     * temporal order
     *
     * @param m road frames which to be joined into queue
     * @return true for add road frames successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    virtual bool_t AddSmartRoadFrame(const RoadFrameType& m);

    /**
     * @brief Push the holo road frames into queue, pop out outdated measurements, then sort them in
     * temporal order
     *
     * @param m road frames which to be joined into queue
     * @return true for add road frames successfully
     * @return false otherwise
     * @note the reptition Timestamp case isn't taken into account
     */
    virtual bool_t AddHoloRoadFrame(const RoadFrameType& m);

    /**
     * @brief Retrieve an patch of holo road frames
     * @return std::vector<RoadFrameType> return holo road frames measurements
     */
    std::vector<RoadFrameType> GetHoloRoadFrameMeasurements();

    /**
     * @brief Retrieve an patch of smart road frames
     * @return std::vector<RoadFrameType> return smart road frames measurements
     */
    std::vector<RoadFrameType> GetSmartRoadFrameMeasurements();

    /**
     * @brief Clear holo road frame buffer
     */
    void ClearHoloRoadFrame();

    /**
     * @brief Clear smart road frame buffer
     */
    void ClearSmartRoadFrame();

    /**
     * @brief Set the Parameters object
     *
     * @param params
     */
    void SetParameters(Parameters const& params)
    {
        params_ = params;
    }

private:
    /**
     * @brief internal data declaration
     */
    RoadFrameBufferType holo_road_frame_buffer_;

    /**
     * @brief internal data declaration
     */
    RoadFrameBufferType smart_road_frame_buffer_;

    /**
     * @brief holo road frame buffer mutex_
     */
    std::mutex holo_road_frame_buffer_mutex_;

    /**
     * @brief smart road frame buffer mutex_
     */
    std::mutex smart_road_frame_buffer_mutex_;

    /**
     * @brief measurements params
     */
    Parameters params_;

};  // class MeasurementsManagerSmartCamera

/**
 * @}
 *
 */

}  // namespace camera

}  // namespace calibration

}  // namespace holo

#endif  // HOLO_CALIBRATION_CAMERA_ONLINE_MEASUREMENTS_MANAGER_SMART_CAMERA_H_
