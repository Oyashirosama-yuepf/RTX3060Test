/*!
 * \brief VSLAM measurements manager class
 * \author lifeng. lifeng@holomatic.com
 * \date Dec-25-2018
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/measurements_manager_vslam.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeasurementsManagerVSLAM::Parameters MeasurementsManagerVSLAM::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    const uint64_t image_queue_size         = node["image_queue_size"].as<uint64_t>(50);
    const uint64_t point_feature_queue_size = node["point_feature_queue_size"].as<uint64_t>(1);
    const uint64_t gravity_aligned_odometry_buffer_size =
        node["gravity_aligned_odometry_buffer_size"].as<uint64_t>(1000);
    const bool   make_point_features_as_optional = node["make_point_features_as_optional"].as<bool>(false);
    const Scalar maximum_range                   = node["maximum_range"].as<Scalar>(25);
    const Scalar fov                             = node["fov"].as<Scalar>(120.0);

    return Parameters(image_queue_size, point_feature_queue_size, gravity_aligned_odometry_buffer_size,
                      make_point_features_as_optional, maximum_range, fov);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeasurementsManagerVSLAM::Parameters MeasurementsManagerVSLAM::Parameters::Example()
{
    return Parameters(50, 1, 1000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeasurementsManagerVSLAM::MeasurementsManagerVSLAM(const Parameters&            paramters,
                                                   const CameraParameters::Ptr& camera_parameters, const MapPtr& map)
  : gravity_aligned_odometry_buffer_(paramters.gravity_aligned_odometry_buffer_size)
  , parking_slot_frame_buffer_(10)
  , camera_parameters_(camera_parameters)
  , map_(map)
  , parameters_(paramters)
{
    if (camera_parameters_ == nullptr)
    {
        throw std::runtime_error("Failed to construct MeasurementsManagerVSLAM, camera_parameters is nullptr.\n");
    }

    kdtree_ = InitializeMap(map_);

    // initialize image queue size for multi camera system
    for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
    {
        ImageCircularBuffer image_queue(paramters.image_queue_size);
        multi_image_buffer_.emplace(camera_index, image_queue);
    }

    // init point features queue size for multi camera system
    for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
    {
        PointFeaturesCircularBuffer point_feature_queue(paramters.point_feature_queue_size);
        multi_point_feature_buffer_.emplace(camera_index, point_feature_queue);
    }

    // initialize obstacle queue size for multi camera system
    for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
    {
        ObstaclePtrListCircularBuffer obstacle_queue(paramters.image_queue_size);
        multi_obstacle_queue_.emplace(camera_index, obstacle_queue);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeasurementsManagerVSLAM::Reset()
{
    std::unique_lock<std::mutex> lock1(multi_image_buffer_mutex_);
    std::unique_lock<std::mutex> lock2(imu_buffer_mutex_);
    std::unique_lock<std::mutex> lock3(chassis_state_buffer_mutex_);
    std::unique_lock<std::mutex> lock4(gravity_aligned_odometry_buffer_mutex_);
    std::unique_lock<std::mutex> lock5(ground_truth_buffer_mutex_);
    std::unique_lock<std::mutex> lock6(multi_point_feature_buffer_mutex_);
    std::unique_lock<std::mutex> lock7(parking_slot_frame_buffer_mutex_);

    // reset multi image queue
    for (auto& indexed_image_queue : multi_image_buffer_)
    {
        indexed_image_queue.second.clear();
    }

    // reset multi point feature queue
    for (auto& indexed_point_feature_queue : multi_point_feature_buffer_)
    {
        indexed_point_feature_queue.second.clear();
    }

    imu_buffer_.clear();
    chassis_state_buffer_.clear();
    gravity_aligned_odometry_buffer_.clear();
    ground_truth_buffer_.clear();
    parking_slot_frame_buffer_.clear();

    // SourceChecker does not provide a Reset/Clear() function, neither do we
    // need reset it
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::AddMeasurement(const Image& m, const uint16_t camera_index)
{
    std::unique_lock<std::mutex> lock(multi_image_buffer_mutex_);

    ///@todo(Feng. Li 2020-11-20)  check consistency

    cv::Mat gray_mat;
    Image   gray_image = m;

    // convert rgb/bgr to grayscale
    if (m.GetEncoding() == Image::Encoding::UNKNOWN)
    {
        throw std::runtime_error("unknown image encoding!!!");
    }
    else if (m.GetEncoding() == Image::Encoding::RGB)
    {
        cv::cvtColor(m.GetCvType(), gray_mat, CV_RGB2GRAY);
        const uint16_t width       = m.GetWidth();
        const uint16_t height      = m.GetHeight();
        const uint32_t buffer_size = width * height;
        gray_image.SetData(static_cast<uint8_t*>(gray_mat.data), buffer_size, width, height,
                           Image::Encoding::GRAYSCALE);
    }

    multi_image_buffer_.at(camera_index).push_back(gray_image);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::AddMeasurement(PointFeaturefList_ST* const m)
{
    std::unique_lock<std::mutex> lock(multi_point_feature_buffer_mutex_);
    static Timestamp             timestamp = Timestamp(m->timestamp.sec, m->timestamp.nsec);
    static bool                  flag      = true;
    if (flag)
    {
        flag = false;
    }
    else
    {
        if (timestamp == Timestamp(m->timestamp.sec, m->timestamp.nsec))
        {
            LOG(INFO) << "Measurement Manager Vslam --- the time stamp is same as last one !!!!!";
            return false;
        }
    }

    LOG(INFO) << "MeasurementsManagerVSLAM --- get new features, timestamp = " << timestamp.ToSec()
              << ", sensor id = " << static_cast<uint32_t>(m->sensor_id) << "\n";

    if (!camera_parameters_->sensor_id_to_camera_index_map_.count(static_cast<uint32_t>(m->sensor_id)))
    {
        LOG(ERROR) << "MeasurementsManagerVSLAM --- invalid point feature's sensor id.\n";
        LOG(ERROR) << "MeasurementsManagerVSLAM --- given sensor id = " << static_cast<uint32_t>(m->sensor_id) << "\n";
        throw std::runtime_error("invalid point feature's sensor id");
    }

    const auto camera_index =
        camera_parameters_->sensor_id_to_camera_index_map_.at(static_cast<uint32_t>(m->sensor_id));
    multi_point_feature_buffer_.at(camera_index).push_back(m);
    timestamp = Timestamp(m->timestamp.sec, m->timestamp.nsec);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::AddMeasurement(const ChassisState& m)
{
    ChassisState chassis_state(m);

    Scalar sign = 1.0;

    if (chassis_state.GetGearPosition() == ChassisState::GearPosition::R)
    {
        sign = -1.0;
    }

    chassis_state.SetVehicleSpeed(sign * m.GetVehicleSpeed());

    Base::AddMeasurement(chassis_state);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::AddMeasurement(const Imu& m)
{
    /// @todo(Feng. Li 2020-11-20) source checker

    Base::AddMeasurement(m);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::AddMeasurement(const GnssPosition& m)
{
    /// @todo(Heiko. Yu 2020-11-23) source checker

    Base::AddMeasurement(m);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::AddMeasurement(const ObstaclePtrList& m)
{
    std::unique_lock<std::mutex> lock(multi_image_buffer_mutex_);

    /// @todo (guopeikai@holomatic.com) remove sensor id hard code
    const auto camera_index =
        camera_parameters_->sensor_id_to_camera_index_map_.at(static_cast<uint32_t>(SensorId(51381647)));

    if (m.GetTimestamp() > multi_obstacle_queue_.at(camera_index).back().GetTimestamp())
    {
        LOG(INFO) << "MeasurementsManagerVSLAM --- the new ostacle push in quene timestamp: "
                  << m.GetTimestamp().ToString() << "\n";
        multi_obstacle_queue_.at(camera_index).push_back(m);
    }
    else
    {
        LOG(ERROR) << "MeasurementsManagerVSLAM --- new timestamp is equal or smaller than the last one.";
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::AddMeasurement(const ParkingSlotFrameType& m)
{
    std::unique_lock<std::mutex> lock(parking_slot_frame_buffer_mutex_);
    parking_slot_frame_buffer_.push_back(m);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::AddGravityAlignedOdometry(const Odometry& m)
{
    std::unique_lock<std::mutex> lock(gravity_aligned_odometry_buffer_mutex_);
    gravity_aligned_odometry_buffer_.push_back(m);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::IsRawMeasurementAvailable(bool enable_visualizer, bool is_dr_mode,
                                                         bool is_parking_slot_optional)
{
    std::unique_lock<std::mutex> lock_imu(imu_buffer_mutex_);
    std::unique_lock<std::mutex> lock_chassis_state(chassis_state_buffer_mutex_);

    // check if imu is available
    if (imu_buffer_.empty())
    {
        LOG_EVERY_N(ERROR, 500) << "MeasurementsManagerVSLAM --- imu measurement buffer is empty.";
        return false;
    }

    // check if chassis state is available
    if (chassis_state_buffer_.empty())
    {
        LOG_EVERY_N(ERROR, 500) << "MeasurementsManagerVSLAM --- chassis state measurement buffer is empty.";
        return false;
    }

    // checke if parking slot frame is available
    if (!is_parking_slot_optional && parking_slot_frame_buffer_.empty())
    {
        LOG_EVERY_N(ERROR, 500) << "MeasurementsManagerVSLAM --- parking slot frame buffer is empty.";
        return false;
    }

    if (parameters_.make_point_features_as_optional || is_dr_mode)
    {
        return true;
    }

    // check if point features is available
    std::unique_lock<std::mutex> lock_point_feature(multi_point_feature_buffer_mutex_);

    for (const auto& indexed_point_feature_queue : multi_point_feature_buffer_)
    {
        const auto& camera_index = indexed_point_feature_queue.first;

        if (indexed_point_feature_queue.second.empty())
        {
            LOG_EVERY_N(ERROR, 500) << "MeasurementsManagerVSLAM --- Features measurement buffer for camera "
                                    << camera_parameters_->camera_coords.at(camera_index) << " is empty.";
            return false;
        }

        // check if images is available when enable visualizer
        if (enable_visualizer)
        {
            // enable visualizer, image is must have
            std::unique_lock<std::mutex> lock_image(multi_image_buffer_mutex_);

            if (multi_image_buffer_.at(camera_index).empty())
            {
                LOG_EVERY_N(ERROR, 500)
                    << "MeasurementsManagerVSLAM --- Visualizer is enable, but image buffer for camera "
                    << camera_parameters_->camera_coords.at(camera_index)
                    << " is empty. Please check if the images are input.\n";
                return false;
            }
            else if (Timestamp(indexed_point_feature_queue.second.front()->timestamp.sec,
                               indexed_point_feature_queue.second.front()->timestamp.nsec) <
                     multi_image_buffer_.at(camera_index).front().GetTimestamp())
            {
                LOG_EVERY_N(ERROR, 500)
                    << "MeasurementsManagerVSLAM --- Visualizer is enable, but the oldest point feature "
                    << Timestamp(indexed_point_feature_queue.second.front()->timestamp.sec,
                                 indexed_point_feature_queue.second.front()->timestamp.nsec)
                           .ToString()
                    << " is smaller oldest than image "
                    << multi_image_buffer_.at(camera_index).front().GetTimestamp().ToString() << ".";
                return false;
            }
            else if (Timestamp(indexed_point_feature_queue.second.front()->timestamp.sec,
                               indexed_point_feature_queue.second.front()->timestamp.nsec) >
                     multi_image_buffer_.at(camera_index).back().GetTimestamp())
            {
                LOG_EVERY_N(ERROR, 500)
                    << "MeasurementsManagerVSLAM --- Visualizer is enable, but the oldest point feature "
                    << Timestamp(indexed_point_feature_queue.second.front()->timestamp.sec,
                                 indexed_point_feature_queue.second.front()->timestamp.nsec)
                           .ToString()
                    << " is larger than newest image "
                    << multi_image_buffer_.at(camera_index).back().GetTimestamp().ToString()
                    << ". Please check if point feature queue's buffer size is large enough (10 is suggested).";
                return false;
            }
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<Timestamp> MeasurementsManagerVSLAM::GetOldestAlignedPointFeaturesTimestamp()
{
    boost::optional<Timestamp>   optional_timestamp = boost::none;
    std::unique_lock<std::mutex> lock_point_feature(multi_point_feature_buffer_mutex_);

    for (const auto& indexed_point_feature_queue : multi_point_feature_buffer_)
    {
        const auto& point_feature_queue = indexed_point_feature_queue.second;

        if (point_feature_queue.empty())
        {
            return boost::none;
        }

        if (optional_timestamp && *optional_timestamp > Timestamp(point_feature_queue.front()->timestamp.sec,
                                                                  point_feature_queue.front()->timestamp.nsec))
        {
            continue;
        }

        optional_timestamp =
            Timestamp(point_feature_queue.front()->timestamp.sec, point_feature_queue.front()->timestamp.nsec);
    }

    return optional_timestamp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<Timestamp> MeasurementsManagerVSLAM::GetOldestParkingSlotFrameTimestamp()
{
    if (parking_slot_frame_buffer_.empty())
    {
        return boost::none;
    }

    return parking_slot_frame_buffer_.front().GetTimestamp();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::GetNewestRawMeasurementTimestamp(Timestamp& timestamp)
{
    // timestamp checking and point features measurements rearranging
    Timestamp start_imu_timestamp, end_imu_timestamp;
    Timestamp end_chassis_state_timestamp;
    {
        // unlock this mutex before call GetImuMeasurements
        std::unique_lock<std::mutex> lock_imu(imu_buffer_mutex_);

        if (imu_buffer_.empty())
        {
            LOG(WARNING) << "MeasurementsManagerVSLAM --- empty imu buffer.";
            return false;
        }

        start_imu_timestamp = imu_buffer_.front().GetTimestamp();
        end_imu_timestamp   = imu_buffer_.back().GetTimestamp();

        std::unique_lock<std::mutex> lock_via(chassis_state_buffer_mutex_);

        if (chassis_state_buffer_.empty())
        {
            LOG(WARNING) << "MeasurementsManagerVSLAM --- empty chassis_state buffer.";
            return false;
        }

        end_chassis_state_timestamp = chassis_state_buffer_.back().GetTimestamp();
    }

    if (parameters_.make_point_features_as_optional)
    {
        // point features in raw measurement is optional, then the raw measurement's timestamp is aligned with chassis
        // state.
        if (end_chassis_state_timestamp < start_imu_timestamp)
        {
            LOG(WARNING) << "MeasurementsManagerVSLAM --- all chassis_states' timestamp before imus.";
            return false;
        }

        timestamp = (end_chassis_state_timestamp < end_imu_timestamp ? end_chassis_state_timestamp : end_imu_timestamp);
        return true;
    }

    // point features is must have, get oldest point features timestamp
    auto optional_oldest_aligned_point_features_timestamp = GetOldestAlignedPointFeaturesTimestamp();

    // wait point features measurement
    while (optional_oldest_aligned_point_features_timestamp &&
           start_imu_timestamp >= *optional_oldest_aligned_point_features_timestamp)
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- point features is ahead of imu "
                        "time: the oldest imu time = "
                     << start_imu_timestamp.ToString() << ", the oldest point features time = "
                     << optional_oldest_aligned_point_features_timestamp->ToString();

        {
            std::unique_lock<std::mutex> lock_point_feature(multi_point_feature_buffer_mutex_);

            for (auto& indexed_point_feature_queue : multi_point_feature_buffer_)
            {
                auto& point_feature_queue = indexed_point_feature_queue.second;

                if (point_feature_queue.empty())
                {
                    return false;
                }

                if (Timestamp(point_feature_queue.front()->timestamp.sec,
                              point_feature_queue.front()->timestamp.nsec) <=
                    *optional_oldest_aligned_point_features_timestamp)
                {
                    point_feature_queue.pop_front();
                }
            }
        }

        // get oldest_aligned_point_features_timestamp again
        optional_oldest_aligned_point_features_timestamp = GetOldestAlignedPointFeaturesTimestamp();
    }

    if (!optional_oldest_aligned_point_features_timestamp)
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- failed to get oldest aligned point features timestamp.\n";
        return false;
    }

    // wait imu
    if (end_imu_timestamp < *optional_oldest_aligned_point_features_timestamp)
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- imu is ahead of point features "
                        "time: the newest imu time = "
                     << end_imu_timestamp.ToString() << ", the oldest point features time = "
                     << optional_oldest_aligned_point_features_timestamp->ToString();
        return false;
    }

    // wait chassis state
    if (end_chassis_state_timestamp < *optional_oldest_aligned_point_features_timestamp)
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- chassis state is ahead of point features "
                        "time: the newest chassis state time = "
                     << end_chassis_state_timestamp.ToString() << ", the oldest point features time = "
                     << optional_oldest_aligned_point_features_timestamp->ToString();
        return false;
    }

    /**
     * after rearrange point features buffer, the imu and point features timestamp is:
     * imu_queue timestamp              |||||||||||
     * point_features_queue timestamp     |     |
     */

    timestamp = *optional_oldest_aligned_point_features_timestamp;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::GetSemanticNewestRawMeasurementTimestamp(Timestamp& timestamp)
{
    // timestamp checking and point features measurements rearranging
    Timestamp start_imu_timestamp, end_imu_timestamp;
    Timestamp end_chassis_state_timestamp;
    {
        // unlock this mutex before call GetImuMeasurements
        std::unique_lock<std::mutex> lock_imu(imu_buffer_mutex_);

        if (imu_buffer_.empty())
        {
            LOG(WARNING) << "MeasurementsManagerVSLAM --- empty imu buffer.";
            return false;
        }

        start_imu_timestamp = imu_buffer_.front().GetTimestamp();
        end_imu_timestamp   = imu_buffer_.back().GetTimestamp();

        std::unique_lock<std::mutex> lock_via(chassis_state_buffer_mutex_);

        if (chassis_state_buffer_.empty())
        {
            LOG(WARNING) << "MeasurementsManagerVSLAM --- empty chassis_state buffer.";
            return false;
        }

        end_chassis_state_timestamp = chassis_state_buffer_.back().GetTimestamp();
    }

    // get oldest parking slot frame timestamp
    auto optional_oldest_parking_slot_frame_timestamp = GetOldestParkingSlotFrameTimestamp();

    // wait parking slot frame measurement
    while (optional_oldest_parking_slot_frame_timestamp &&
           start_imu_timestamp >= *optional_oldest_parking_slot_frame_timestamp)
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- parking slot frame is ahead of imu "
                        "time: the oldest imu time = "
                     << start_imu_timestamp.ToString() << ", the oldest parking slot frame time = "
                     << optional_oldest_parking_slot_frame_timestamp->ToString();

        if (parking_slot_frame_buffer_.empty())
        {
            return false;
        }
        if (parking_slot_frame_buffer_.front().GetTimestamp() <= *optional_oldest_parking_slot_frame_timestamp)
        {
            parking_slot_frame_buffer_.pop_front();
        }

        // get oldest_parking_slot_frame_timestamp again
        optional_oldest_parking_slot_frame_timestamp = GetOldestParkingSlotFrameTimestamp();
    }

    if (!optional_oldest_parking_slot_frame_timestamp)
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- failed to get oldest parking slot frame timestamp.\n";
        return false;
    }

    // wait imu
    if (end_imu_timestamp < *optional_oldest_parking_slot_frame_timestamp)
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- imu is ahead of point features "
                        "time: the newest imu time = "
                     << end_imu_timestamp.ToString() << ", the oldest point features time = "
                     << optional_oldest_parking_slot_frame_timestamp->ToString();
        return false;
    }

    // wait chassis state
    if (end_chassis_state_timestamp < *optional_oldest_parking_slot_frame_timestamp)
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- chassis state is ahead of point features "
                        "time: the newest chassis state time = "
                     << end_chassis_state_timestamp.ToString() << ", the oldest point features time = "
                     << optional_oldest_parking_slot_frame_timestamp->ToString();
        return false;
    }

    /**
     * after rearrange parking_slot_frame_timestamp buffer, the imu and parking slot frame timestamp is:
     * imu_queue timestamp                   |||||||||||
     * parking_slot_frame_buffer timestamp     |     |
     */

    timestamp = *optional_oldest_parking_slot_frame_timestamp;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::GetDrNewestRawMeasurementTimestamp(Timestamp& timestamp)
{
    // timestamp checking and point features measurements rearranging
    Timestamp start_imu_timestamp, end_imu_timestamp;
    Timestamp end_chassis_state_timestamp;
    {
        // unlock this mutex before call GetImuMeasurements
        std::unique_lock<std::mutex> lock_imu(imu_buffer_mutex_);

        if (imu_buffer_.empty())
        {
            LOG(WARNING) << "MeasurementsManagerVSLAM --- empty imu buffer.";
            return false;
        }

        start_imu_timestamp = imu_buffer_.front().GetTimestamp();
        end_imu_timestamp   = imu_buffer_.back().GetTimestamp();

        std::unique_lock<std::mutex> lock_via(chassis_state_buffer_mutex_);

        if (chassis_state_buffer_.empty())
        {
            LOG(WARNING) << "MeasurementsManagerVSLAM --- empty chassis_state buffer.";
            return false;
        }

        end_chassis_state_timestamp = chassis_state_buffer_.back().GetTimestamp();
    }

    if (end_chassis_state_timestamp < start_imu_timestamp)
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- all chassis_states' timestamp before imus.";
        return false;
    }

    timestamp = (end_chassis_state_timestamp < end_imu_timestamp ? end_chassis_state_timestamp : end_imu_timestamp);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::GetPointFeaturesAt(const Timestamp&                    timestamp,
                                                  std::vector<PointFeaturefList_ST*>& multi_point_feature_list)
{
    multi_point_feature_list.reserve(camera_parameters_->camera_number);

    for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
    {
        std::unique_lock<std::mutex> lock_point_feature(multi_point_feature_buffer_mutex_);
        auto&                        point_features_queue = multi_point_feature_buffer_.at(camera_index);

        while (!point_features_queue.empty() && Timestamp(point_features_queue.front()->timestamp.sec,
                                                          point_features_queue.front()->timestamp.nsec) < timestamp)
        {
            LOG(INFO) << "MeasurementsManagerVSLAM --- drop point features in "
                      << camera_parameters_->camera_coords.at(camera_index)
                      << " buffer, oldest point features in this buffer is "
                      << Timestamp(point_features_queue.front()->timestamp.sec,
                                   point_features_queue.front()->timestamp.nsec)
                             .ToString()
                      << ", expected oldest aligned image timestamp is: " << timestamp.ToString()
                      << ", total buffer size is: " << point_features_queue.size() << "\n";
            point_features_queue.pop_front();
        }

        if (point_features_queue.empty())
        {
            LOG(ERROR) << "MeasurementsManagerVSLAM ---  failed to get point features of camera "
                       << camera_parameters_->camera_coords.at(camera_index) << "\n";
            return false;
        }

        if (Timestamp(point_features_queue.front()->timestamp.sec, point_features_queue.front()->timestamp.nsec) !=
            timestamp)
        {
            LOG(ERROR) << "MeasurementsManagerVSLAM --- somthing must be wrong for time system of multi camera.\n";
            LOG(ERROR) << "oldest point feature timestamp of camera "
                       << camera_parameters_->camera_coords.at(camera_index) << " is: "
                       << Timestamp(point_features_queue.front()->timestamp.sec,
                                    point_features_queue.front()->timestamp.nsec)
                              .ToString()
                       << ", expected oldest aligned point features timestamp is: " << timestamp.ToString() << "\n";
            return false;
        }

        multi_point_feature_list.emplace_back(point_features_queue.front());
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::GetImagesAt(const Timestamp& timestamp, std::vector<Image>& multi_images)
{
    multi_images.reserve(camera_parameters_->camera_number);

    for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
    {
        std::unique_lock<std::mutex> lock_image(multi_image_buffer_mutex_);
        auto&                        image_queue = multi_image_buffer_.at(camera_index);

        while (!image_queue.empty() && image_queue.front().GetTriggerStamp() < timestamp)
        {
            LOG(INFO) << "MeasurementsManagerVSLAM --- drop images in "
                      << camera_parameters_->camera_coords.at(camera_index)
                      << " buffer, oldest image in this buffer is " << image_queue.front().GetTriggerStamp().ToString()
                      << ", expected oldest aligned point features timestamp is: " << timestamp.ToString()
                      << ", total buffer size is: " << image_queue.size() << "\n";
            image_queue.pop_front();
        }

        if (image_queue.empty())
        {
            LOG(INFO) << "MeasurementsManagerVSLAM ---  failed to get image of camera "
                      << camera_parameters_->camera_coords.at(camera_index) << "\n";
            return false;
        }

        if (image_queue.front().GetTriggerStamp() != timestamp)
        {
            LOG(INFO) << "MeasurementsManagerVSLAM --- somthing must be wrong for time system of multi camera.\n";
            LOG(INFO) << "oldest image timestamp of camera " << camera_parameters_->camera_coords.at(camera_index)
                      << " is: " << image_queue.front().GetTriggerStamp().ToString()
                      << ", expected oldest aligned point features timestamp is: " << timestamp.ToString() << "\n";
            return false;
        }

        multi_images.emplace_back(image_queue.front());  // shallow copy
        image_queue.pop_front();
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::GetRawMeasurement(const Timestamp&              old_timestamp,
                                                 const boost::optional<Pose3>& prior_vehicle_pose,
                                                 RawMeasurement&               raw_measurements)
{
    Timestamp new_timestamp;

    // step1: trying to get timestamp of the newest available raw mesaurement
    if (!GetNewestRawMeasurementTimestamp(new_timestamp))
    {
        return false;
    }

    // step2: get point features
    std::vector<PointFeaturefList_ST*> multi_point_feature_list;

    if (!parameters_.make_point_features_as_optional && !GetPointFeaturesAt(new_timestamp, multi_point_feature_list))
    {
        return false;
    }

    // step3: get image
    std::vector<Image> multi_images;
    GetImagesAt(new_timestamp, multi_images);

    // step4: get imu data
    std::vector<Imu> imus;

    // if it is first frame(old_timestamp.IsZero() == true) return empty imus
    // else get imus between previous estimated image and current image
    if (!old_timestamp.IsZero() && !GetImuMeasurements(old_timestamp, new_timestamp, imus))
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- failed to get imus";
        return false;
    }

    // step5: get chassis state
    std::vector<ChassisState> chassis_states;

    if (!old_timestamp.IsZero() && !GetChassisStatesMeasurements(old_timestamp, new_timestamp, chassis_states))
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- failed to get chassis state.\n";
        return false;
    }

    // step6: get prior odometry
    boost::optional<Odometry> optional_odometry = boost::none;
    Odometry                  prior_odo;

    if (Base::GetCurrentGroundTruth(new_timestamp, prior_odo))
    {
        optional_odometry = prior_odo;
    }

    // step7: get visible map points
    const Scalar maximum_range = 25;     // metre
    const Scalar fov           = 120.0;  // degree
    MapPtr       visible_map   = std::make_shared<Map>();

    if (prior_vehicle_pose)
    {
        // get visible map points for each camera
        /// @todo(Feng. Li 2020-06-10) for multi-camera system with large overlapping in fov, query visible map like
        /// this may cause redundant copies, we should optimize this part in future.
        for (uint16_t camera_index = 0; camera_index < camera_parameters_->extrinsics.size(); camera_index++)
        {
            const auto prior_camera_pose = (*prior_vehicle_pose) * camera_parameters_->extrinsics.at(camera_index);
            GetVisibleMap(prior_camera_pose, maximum_range, fov, map_, kdtree_, visible_map);
        }
    }

    // step8:  get gps position
    boost::optional<GnssPosition> optional_position = boost::none;

    // step9: get obstacle
    const auto multi_obstacle_list = GetMultiObstaclePtrList(new_timestamp);

    // step10: get parking slot frame
    boost::optional<ParkingSlotFrameType> optional_parking_slot_frame = boost::none;
    /*
    {
        std::unique_lock<std::mutex> lock_parking_slot_frame(parking_slot_frame_buffer_mutex_);

        while (!parking_slot_frame_buffer_.empty() && parking_slot_frame_buffer_.front().GetTimestamp() < new_timestamp)
        {
            LOG(INFO) << "MeasurementsManagerVSLAM --- drop parking-slot frame in this buffer, "
                      << "oldest frame in this buffer is "
                      << parking_slot_frame_buffer_.front().GetTimestamp().ToString()
                      << " , expected oldest aligned point feature timestamp is :" << new_timestamp.ToString()
                      << ", total buffer size is: " << parking_slot_frame_buffer_.size() << "\n";
            parking_slot_frame_buffer_.pop_front();
        }
        if (parking_slot_frame_buffer_.empty())
        {
            LOG(WARNING) << "MeasurementsManagersVSLAM -- failed to get parking-slot frame. \n";
        }
        else if (parking_slot_frame_buffer_.front().GetTimestamp() != new_timestamp)
        {
            LOG(ERROR)
                << "MeasurementsManagerVSLAM --- somthing must be wrong for time system of of parking-slot frame.\n";
            LOG(ERROR) << "oldest image timestamp of the frame: "
                       << parking_slot_frame_buffer_.front().GetTimestamp().ToString()
                       << ", expected oldest aligned point features timestamp is:" << new_timestamp.ToString() << "\n";
        }
        else
        {
            optional_parking_slot_frame =
                boost::make_optional<ParkingSlotFrameType>(parking_slot_frame_buffer_.front());
            parking_slot_frame_buffer_.pop_front();
        }
    }
    */

    raw_measurements =
        RawMeasurement(new_timestamp, multi_images, multi_point_feature_list, imus, chassis_states, optional_odometry,
                       visible_map, optional_position, multi_obstacle_list, optional_parking_slot_frame);

    // drop first point features if all measurement ready.
    for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
    {
        std::unique_lock<std::mutex> lock_point_feature(multi_point_feature_buffer_mutex_);
        auto&                        point_features_queue = multi_point_feature_buffer_.at(camera_index);

        if (!point_features_queue.empty())
        {
            point_features_queue.pop_front();
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::GetSemanticRawMeasurement(const Timestamp& old_timestamp,
                                                         RawMeasurement&  raw_measurements)
{
    Timestamp new_timestamp;

    // step1: trying to get timestamp of the newest available raw mesaurement
    std::unique_lock<std::mutex> lock_parking_slot_frame(parking_slot_frame_buffer_mutex_);
    if (!GetSemanticNewestRawMeasurementTimestamp(new_timestamp))
    {
        return false;
    }

    // step4: get imu data
    std::vector<Imu> imus;

    // if it is first frame(old_timestamp.IsZero() == true) return empty imus
    // else get imus between previous estimated state and current state
    if (!old_timestamp.IsZero() && !GetImuMeasurements(old_timestamp, new_timestamp, imus))
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- failed to get imus";
        return false;
    }

    // step5: get chassis state
    std::vector<ChassisState> chassis_states;

    if (!old_timestamp.IsZero() && !GetChassisStatesMeasurements(old_timestamp, new_timestamp, chassis_states))
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- failed to get chassis state.\n";
        return false;
    }

    // step10: get parking slot frame
    boost::optional<ParkingSlotFrameType> optional_parking_slot_frame = boost::none;
    if (!GetParkingSlotFrame(new_timestamp, optional_parking_slot_frame))

    {
        LOG(ERROR) << "MeasurementsManagerVSLAM --- failed to get parking slot frame.\n";
        throw std::runtime_error("can't get parking slot frame!");
    }

    raw_measurements = RawMeasurement(new_timestamp, {}, {}, imus, chassis_states, boost::none, {}, boost::none, {},
                                      optional_parking_slot_frame);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeasurementsManagerVSLAM::GetDrRawMeasurement(const Timestamp& old_timestamp, RawMeasurement& raw_measurements)
{
    Timestamp new_timestamp;

    // step1: trying to get timestamp of the newest available raw mesaurement
    if (!GetDrNewestRawMeasurementTimestamp(new_timestamp))
    {
        return false;
    }

    // step4: get imu data
    std::vector<Imu> imus;

    // if it is first frame(old_timestamp.IsZero() == true) return empty imus
    // else get imus between previous estimated image and current image
    if (!old_timestamp.IsZero() && !GetImuMeasurements(old_timestamp, new_timestamp, imus))
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- failed to get imus";
        return false;
    }

    // step5: get chassis state
    std::vector<ChassisState> chassis_states;

    if (!old_timestamp.IsZero() && !GetChassisStatesMeasurements(old_timestamp, new_timestamp, chassis_states))
    {
        LOG(WARNING) << "MeasurementsManagerVSLAM --- failed to get chassis state.\n";
        return false;
    }

    raw_measurements =
        RawMeasurement(new_timestamp, {}, {}, imus, chassis_states, boost::none, {}, boost::none, {}, boost::none);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerVSLAM::GetImuMeasurements(const Timestamp& left_t, const Timestamp& right_t,
                                                    std::vector<Imu>& imus)
{
    Imu newest_imu;

    /// @brief do not extrapolate imu for the left boundary when the newest imu does not arrive
    if (GetLatestMeasurement(newest_imu))
    {
        if (newest_imu.GetTimestamp() < right_t)
        {
            LOG(WARNING) << "MeasurementsManagerVSLAM --- the newest imu is ahead of the retrieved imu, "
                         << "newest imu's timestamp: " << newest_imu.GetTimestamp().ToString()
                         << "retrived imus' right boundary of interval: " << right_t.ToString();
            return false;
        }
    }
    else
    {
        return false;
    }

    return Base::GetAlignedMeasurementsBetween(left_t, right_t, imus);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerVSLAM::GetChassisStatesMeasurements(const Timestamp& left_t, const Timestamp& right_t,
                                                              std::vector<ChassisState>& chassis_states)
{
    ChassisState newest_css;

    /// @brief do not extrapolate chassis state for the left boundary when the newest chassis state does not arrive
    if (GetLatestMeasurement(newest_css))
    {
        if (newest_css.GetTimestamp() < right_t)
        {
            LOG(WARNING)
                << "MeasurementsManagerVio --- the newest chassis state is ahead of the retrieved chassis state, "
                << "newest chassis states's timestamp: " << newest_css.GetTimestamp().ToString()
                << "retrived chassis_states's right boundary of interval: " << right_t.ToString();
            return false;
        }
    }
    else
    {
        return false;
    }

    return Base::GetAlignedMeasurementsBetween(left_t, right_t, chassis_states);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerVSLAM::GetParkingSlotFrame(const Timestamp&                       timestamp,
                                                     boost::optional<ParkingSlotFrameType>& optional_parking_slot_frame)
{
    while (!parking_slot_frame_buffer_.empty() && parking_slot_frame_buffer_.front().GetTimestamp() < timestamp)
    {
        LOG(INFO) << "MeasurementsManagerVSLAM --- drop parking-slot frame in this buffer, "
                  << "oldest frame in this buffer is " << parking_slot_frame_buffer_.front().GetTimestamp().ToString()
                  << " , expected oldest parking slot frame timestamp is :" << timestamp.ToString()
                  << ", total buffer size is: " << parking_slot_frame_buffer_.size() << "\n";
        parking_slot_frame_buffer_.pop_front();
    }
    if (parking_slot_frame_buffer_.empty())
    {
        LOG(WARNING) << "MeasurementsManagersVSLAM -- failed to get parking-slot frame. \n";
    }
    else if (parking_slot_frame_buffer_.front().GetTimestamp() != timestamp)
    {
        LOG(ERROR) << "MeasurementsManagerVSLAM --- somthing must be wrong for time system of of parking-slot frame.\n";
        LOG(ERROR) << "oldest image timestamp of the frame: "
                   << parking_slot_frame_buffer_.front().GetTimestamp().ToString()
                   << ", expected oldest parking slot frame timestamp is:" << timestamp.ToString() << "\n";
    }
    else
    {
        optional_parking_slot_frame = boost::make_optional<ParkingSlotFrameType>(parking_slot_frame_buffer_.front());
        parking_slot_frame_buffer_.pop_front();
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<ParkingSlotFrameType>
MeasurementsManagerVSLAM::GetNewestParkingSlotFrame(const Timestamp& point_feature_timestamp)
{
    std::unique_lock<std::mutex> lock_parking_slot_frame(parking_slot_frame_buffer_mutex_);
    if (parking_slot_frame_buffer_.empty())
    {
        return boost::none;
    }

    auto result = parking_slot_frame_buffer_.back();

    const auto& parking_slot_timestamp = result.GetTimestamp();

    Duration time_interval;
    if (parking_slot_timestamp > point_feature_timestamp)
    {
        time_interval = parking_slot_timestamp - point_feature_timestamp;
    }
    else
    {
        time_interval = point_feature_timestamp - parking_slot_timestamp;
    }

    LOG(INFO)
        << "MeasurementsManagerVSLAM --- time interval between newest point feature and newest parking slot farme : "
        << time_interval.ToSec() << " s";
    if (time_interval < Duration(0.4))
    {
        return result;
    }

    return boost::none;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<ObstaclePtrList> MeasurementsManagerVSLAM::GetMultiObstaclePtrList(const Timestamp& query_timestamp)
{
    std::vector<ObstaclePtrList> multi_obstacle_list;
    multi_obstacle_list.reserve(camera_parameters_->camera_number);

    for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
    {
        std::unique_lock<std::mutex> lock_obstacle(multi_obstacle_queue_mutex_);
        auto&                        obstacle_queue = multi_obstacle_queue_.at(camera_index);

        while (!obstacle_queue.empty() && obstacle_queue.front().GetTimestamp() < query_timestamp)
        {
            LOG(INFO) << "MeasurementsManagerVSLAM --- drop obstacle in "
                      << camera_parameters_->camera_coords.at(camera_index)
                      << " buffer, oldest obstacle in this buffer is " << obstacle_queue.front().GetTimestamp().ToNsec()
                      << ", expected oldest aligned obstacle timestamp is: " << (query_timestamp).ToNsec()
                      << ", total buffer size is: " << obstacle_queue.size() << "\n";
            obstacle_queue.pop_front();
        }

        if (obstacle_queue.empty())
        {
            multi_obstacle_list.clear();
            LOG(INFO) << "MeasurementsManagerVSLAM ---  failed to get obstacle of camera "
                      << camera_parameters_->camera_coords.at(camera_index) << "\n";
            return multi_obstacle_list;
        }

        if (obstacle_queue.front().GetTimestamp() != query_timestamp)
        {
            LOG(INFO) << "oldest obstacle timestamp: " << obstacle_queue.front().GetTimestamp().ToString() << std::endl;
            LOG(INFO) << "oldest image timestamp: " << (query_timestamp).ToString() << std::endl;
            LOG(INFO) << "MeasurementsManagerVSLAM --- multi obstacle thread drop the images.\n";
            LOG(INFO) << "oldest timestamp of ostacle " << camera_parameters_->camera_coords.at(camera_index)
                      << " is: " << obstacle_queue.front().GetTimestamp().ToNsec()
                      << ", expected oldest aligned obstacle timestamp is: " << (query_timestamp).ToNsec() << "\n";
            multi_obstacle_list.clear();
            return multi_obstacle_list;
        }

        multi_obstacle_list.emplace_back(obstacle_queue.front());  // shallow copy
        obstacle_queue.pop_front();
    }

    return multi_obstacle_list;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeasurementsManagerVSLAM::KdTreePtr MeasurementsManagerVSLAM::InitializeMap(const MapPtr& map)
{
    if (!map || map->empty())
    {
        return nullptr;
    }

    size_t        num = map->size();
    PointCloudPtr cloud(new PointCloud(num));

    for (size_t i = 0; i < num; ++i)
    {
        const auto ptw = map->at(i)->reference_pose.GetTranslation();
        float32_t  x   = static_cast<float32_t>(ptw.GetX());
        float32_t  y   = static_cast<float32_t>(ptw.GetY());
        float32_t  z   = static_cast<float32_t>(ptw.GetZ());

        cloud->at(i).Set(x, y, z);
    }

    KdTreePtr kdtree = std::make_shared<KdTree>();
    kdtree->SetInputPointCloud(cloud);
    return kdtree;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeasurementsManagerVSLAM::GetVisibleMap(const Pose3& prior, Scalar maximum_range, Scalar fov, const MapPtr& map,
                                             const KdTreePtr& kdtree, MapPtr& visible_map) const
{
    if (!map || !kdtree || !visible_map)
    {
        return;
    }

    std::vector<size_t> indices;
    std::vector<Scalar> distances;
    Point3              origin = prior.GetTranslation();
    PointType           query;
    query.Set(origin.GetX(), origin.GetY(), origin.GetZ());
    int32_t n = kdtree->RadiusSearch(query, maximum_range, indices, distances);

    if (n <= 0)
    {
        return;
    }

    Rot3         rot               = prior.GetRotation();
    Vector3      view_direction    = rot.ToMatrix().GetCol(2);
    const Scalar margin            = 10.0;  // degree
    const Scalar cos_fov_threshold = std::cos(Radian(fov / 2.0 + margin));
    for (size_t i = 0; i < indices.size(); ++i)
    {
        size_t   idx = indices[i];
        MapPoint p   = *(map->at(idx));
        // vector query -> p
        Vector3 pq = (p.position - origin).ToVector();
        pq.Normalize();
        // check visibility
        Scalar dot = pq.Dot(view_direction);

        if (dot < 0 || dot > 1 || dot < cos_fov_threshold)
        {
            continue;
        }

        // update mappoint state
        if (!map->at(idx)->life_long_states.empty())
        {
            if (map->at(idx)->life_long_states.back() == MapPointState::CANDIDATE)
            {
                map->at(idx)->life_long_states.back() = MapPointState::VISIBLE;
            }
        }

        visible_map->push_back(map->at(idx));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SlotMapPtr MeasurementsManagerVSLAM::QuerySlotMap(const Pose3& prior_vehicle_pose)
{
    if (slot_map_ == nullptr)
    {
        return nullptr;
    }

    SlotMapPtr visible_map = std::make_shared<SlotMap>();

    /// @todo chengchangxi@holomatic.com speed up by kdtree
    for (const auto& slot : *slot_map_)
    {
        if (slot->vertices[0].Dist(prior_vehicle_pose.GetTranslation()) > 20.0)
        {
            continue;
        }
        visible_map->push_back(slot);
    }

    return visible_map;
}
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
