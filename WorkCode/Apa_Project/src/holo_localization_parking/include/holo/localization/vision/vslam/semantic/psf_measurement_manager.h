/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file psf_measurement_manager.h
 * @brief parking slot fusion measurement manager class
 * @author Feng. Li lifeng@holomatic.com
 * @author Changxi. Cheng chengchangxi@holomatic.com
 * @date 2021-11-04
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PSF_MEASUREMENT_MANAGER_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PSF_MEASUREMENT_MANAGER_H_

#include <boost/circular_buffer.hpp>

#include <holo/localization/common/measurements_manager_base.h>
#include <holo/localization/vision/vslam/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
namespace semantic
{
/**
 * @brief parking slot fusion parameters
 */
struct PSFusionRawMeasurement
{
    /// @brief newest timestamp
    Timestamp newest_timestamp;

    /// @brief gravity-aligned odometry at new timestamp
    Pose3 prior_pose;

    /// @brief parking_slot_frame
    ParkingSlotFrameType parking_slot_frame;

    /**
     * @brief Construct a new Raw Measurement object
     *
     * @param _parking_slot_frame new parking slot frame
     * @param _prior_pose new prior pose from odometry
     */
    PSFusionRawMeasurement(const Timestamp& _newest_timestamp = Timestamp(), const Pose3& _prior_pose = Pose3(),
                           const ParkingSlotFrameType& _parking_slot_frame = ParkingSlotFrameType())
      : newest_timestamp(_newest_timestamp), prior_pose(_prior_pose), parking_slot_frame(_parking_slot_frame)
    {
    }
};

class PSFusionMeasurementManager : public MeasurementsManagerBase
{
public:
    using Ptr                        = std::shared_ptr<PSFusionMeasurementManager>;
    using Base                       = MeasurementsManagerBase;
    using OdometryBufferType         = Base::OdometryBufferType;
    using ParkingSlotFrameBufferType = boost::circular_buffer<ParkingSlotFrameType>;

    /**
     * @brief Construct a new PSFusionMeasurementManager object
     *
     */
    PSFusionMeasurementManager();

    /**
     * @brief add parking slot frame
     *
     * @param m parking slot frame measurement
     * @return bool_t it returns false when fails to add the measurement
     */
    bool_t AddMeasurement(const ParkingSlotFrameType& m);

    /**
     * @brief add prior odometry
     *
     * @param m prior odometry measurement
     * @return bool_t it returns false when fails to add the measurement
     */
    bool_t AddMeasurement(const Odometry& m);

    /**
     * @brief get parking slot fusion measurements (prior_odometry + parking_slot_frame)
     *
     * @details this function will query a latest odometry and parking slot frame measurements
     * @param[out] raw_measurements retrieved parking slot fusion measurements.
     * @return true if success to get raw measurement, else return false.
     */
    bool_t GetPSFusionRawMeasurement(PSFusionRawMeasurement& raw_measurement);

protected:
    /**
     * @brief get timestamp of the newest available raw mesaurement
     */
    bool_t getNewestRawMeasurementTimestamp(Timestamp& new_timestamp);

    /**
     * @brief get oldest parking slot frame timestamp
     */
    bool_t getOldestParkingSlotFrameTimestamp(Timestamp& oldest_parking_slot_frame_timestamp);

    /**
     * @brief get parking slot frame
     */
    bool_t getParkingSlotFrame(const Timestamp& timestamp, ParkingSlotFrameType& parking_slot_frame);

    /**
     * @brief get prior odometry
     *
     */
    bool_t getPriorOdometry(const Timestamp& timestamp, Odometry& odometry);

    /// @brief define parking-slots (per frame) measurement
    std::mutex                 parking_slot_frame_buffer_mutex_;
    ParkingSlotFrameBufferType parking_slot_frame_buffer_;
    /// @brief define prior odometry
    std::mutex         prior_odometry_buffer_mutex_;
    OdometryBufferType prior_odometry_buffer_;
};

}  // namespace semantic

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PSF_MEASUREMENT_MANAGER_H_
