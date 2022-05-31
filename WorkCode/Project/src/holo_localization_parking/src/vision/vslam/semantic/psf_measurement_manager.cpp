/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file psf_measurement_manager.cpp
 * @brief parking slot fusion measurement manager class
 * @author Feng. Li lifeng@holomatic.com
 * @author Changxi. Cheng chengchangxi@holomatic.com
 * @date 2021-11-04
 */

#include <holo/localization/vision/vslam/semantic/psf_measurement_manager.h>

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
PSFusionMeasurementManager::PSFusionMeasurementManager() : parking_slot_frame_buffer_(5)
{
}

bool_t PSFusionMeasurementManager::AddMeasurement(const ParkingSlotFrameType& m)
{
    std::unique_lock<std::mutex> lock(parking_slot_frame_buffer_mutex_);
    parking_slot_frame_buffer_.push_back(m);
    return true;
}

bool_t PSFusionMeasurementManager::AddMeasurement(const Odometry& m)
{
    std::unique_lock<std::mutex> lock(prior_odometry_buffer_mutex_);
    return insertMeasurementT<OdometryType, kOdometryBufferSize>(m, prior_odometry_buffer_);
}

bool_t PSFusionMeasurementManager::getOldestParkingSlotFrameTimestamp(Timestamp& oldest_parking_slot_frame_timestamp)
{
    if (parking_slot_frame_buffer_.empty())
    {
        return false;
    }
    oldest_parking_slot_frame_timestamp = parking_slot_frame_buffer_.front().GetTimestamp();
    return true;
}

bool_t PSFusionMeasurementManager::getNewestRawMeasurementTimestamp(Timestamp& timestamp)
{
    Timestamp start_odometry_timestamp, end_odometry_timestamp, oldest_parking_slot_frame_timestamp;
    {
        std::unique_lock<std::mutex> lock(prior_odometry_buffer_mutex_);
        if (prior_odometry_buffer_.empty())
        {
            LOG(WARNING) << "PSFMeasurementsManager --- empty prior odometry buffer.";
            return false;
        }
        start_odometry_timestamp = prior_odometry_buffer_.front().GetTimestamp();
        end_odometry_timestamp   = prior_odometry_buffer_.back().GetTimestamp();
    }

    bool_t geted_oldest_parking_slot_frame_timestamp =
        getOldestParkingSlotFrameTimestamp(oldest_parking_slot_frame_timestamp);

    // wait parking slot frame measurement
    while (geted_oldest_parking_slot_frame_timestamp && start_odometry_timestamp >= oldest_parking_slot_frame_timestamp)
    {
        LOG(WARNING) << "PSFMeasurementsManager --- parking slot frame is ahead of odometry time: the oldest odometry "
                        "time = "
                     << start_odometry_timestamp.ToString()
                     << ", the oldest parking slot frame time = " << oldest_parking_slot_frame_timestamp.ToString();

        if (parking_slot_frame_buffer_.empty())
        {
            return false;
        }
        if (parking_slot_frame_buffer_.front().GetTimestamp() <= oldest_parking_slot_frame_timestamp)
        {
            parking_slot_frame_buffer_.pop_front();
        }

        // get oldest_parking_slot_frame_timestamp again
        geted_oldest_parking_slot_frame_timestamp =
            getOldestParkingSlotFrameTimestamp(oldest_parking_slot_frame_timestamp);
    }

    if (!geted_oldest_parking_slot_frame_timestamp)
    {
        LOG(WARNING) << "PSFMeasurementsManager --- failed to get oldest parking slot frame timestamp.";
        return false;
    }

    // wait odometry
    if (end_odometry_timestamp < oldest_parking_slot_frame_timestamp)
    {
        LOG(WARNING) << "PSFMeasurementsManager --- odometry is ahead of parking slot frame"
                        "time: the newest odometry time = "
                     << end_odometry_timestamp.ToString()
                     << ", the oldest parking slot frame time = " << oldest_parking_slot_frame_timestamp.ToString();
        return false;
    }

    /**
     * after rearrange parking_slot_frame_timestamp buffer, the odometry and parking slot frame timestamp is:
     * odometry timestamp                   |||||||||||
     * parking_slot_frame_buffer timestamp     |     |
     */
    timestamp = oldest_parking_slot_frame_timestamp;
    return true;
}

bool_t PSFusionMeasurementManager::getParkingSlotFrame(const Timestamp&      timestamp,
                                                       ParkingSlotFrameType& parking_slot_frame)
{
    std::unique_lock<std::mutex> lock(parking_slot_frame_buffer_mutex_);
    while (!parking_slot_frame_buffer_.empty() && parking_slot_frame_buffer_.front().GetTimestamp() < timestamp)
    {
        LOG(INFO) << "PSFMeasurementsManager --- drop parking-slot frame in this buffer, "
                  << "oldest frame in this buffer is " << parking_slot_frame_buffer_.front().GetTimestamp().ToString()
                  << " , expected oldest parking slot frame timestamp is :" << timestamp.ToString()
                  << ", total buffer size is: " << parking_slot_frame_buffer_.size() << "\n";
        parking_slot_frame_buffer_.pop_front();
    }
    if (parking_slot_frame_buffer_.empty())
    {
        LOG(WARNING) << "PSFMeasurementsManagers -- failed to get parking-slot frame. \n";
    }
    else if (parking_slot_frame_buffer_.front().GetTimestamp() != timestamp)
    {
        LOG(ERROR) << "PSFMeasurementsManager --- somthing must be wrong for time system of of parking-slotframe.\n ";
        LOG(ERROR) << " oldest image timestamp of the frame : "
                   << parking_slot_frame_buffer_.front().GetTimestamp().ToString()
                   << ", expected oldest parking slot frame timestamp is:" << timestamp.ToString() << "\n";
    }
    else
    {
        parking_slot_frame = parking_slot_frame_buffer_.front();
        parking_slot_frame_buffer_.pop_front();
        return true;
    }
    return false;
}

bool_t PSFusionMeasurementManager::getPriorOdometry(const Timestamp& timestamp, Odometry& odometry)
{
    std::unique_lock<std::mutex> lock(prior_odometry_buffer_mutex_);
    return getCurrentMeasurementT<OdometryType, kOdometryBufferSize>(timestamp, prior_odometry_buffer_, odometry);
}

bool_t PSFusionMeasurementManager::GetPSFusionRawMeasurement(PSFusionRawMeasurement& raw_measurement)
{
    Timestamp new_timestamp;

    // step1: trying to get timestamp of the newest available raw measurement
    if (!getNewestRawMeasurementTimestamp(new_timestamp))
    {
        return false;
    }

    // step2: get parking slot frame
    ParkingSlotFrameType parking_slot_frame;
    if (!getParkingSlotFrame(new_timestamp, parking_slot_frame))
    {
        LOG(ERROR) << "PSFMeasurementsManager --- failed to get parking slot frame.\n";
        throw std::runtime_error("can't get parking slot frame!");
    }

    // step3: get odometry
    Odometry prior_odometry;
    if (!getPriorOdometry(new_timestamp, prior_odometry))
    {
        LOG(ERROR) << "PSFMeasurementsManager --- failed to get prior_odometry.\n";
        throw std::runtime_error("can't get prior odometry");
    }

    raw_measurement = PSFusionRawMeasurement(new_timestamp, prior_odometry.GetPose(), parking_slot_frame);
    return true;
}

}  // namespace semantic

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo
