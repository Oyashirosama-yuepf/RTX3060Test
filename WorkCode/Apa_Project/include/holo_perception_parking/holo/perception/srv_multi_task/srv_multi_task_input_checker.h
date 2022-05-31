/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file srv_multi_task_input_checker.h
 * @brief This header file defines .
 * @author zhouchengwei(zhouchengwei@holomatic.com)
 * @date "2022-03-30"
 */

#ifndef HOLO_PERCEPTION_PARKING_SRV_MULTI_TASK_INPUT_CHECKER_H_
#define HOLO_PERCEPTION_PARKING_SRV_MULTI_TASK_INPUT_CHECKER_H_

#include <holo/common/image.h>
#include <holo/common/imu.h>
#include <holo/common/odometry.h>
#include <holo/perception/utils/timestamp_checker.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <mutex>

namespace holo
{
namespace perception
{
class SrvMultiTaskInputChecker
{
public:
    using Scalar              = float32_t;
    using Timestamp           = holo::common::Timestamp;
    using TimestampPtr        = std::shared_ptr<Timestamp>;
    using ImuType             = holo::common::Imuf;
    using ImuPtr              = std::shared_ptr<ImuType>;
    using ImageType           = holo::Image;
    using ImageVector         = std::vector<ImageType>;
    using TimestampCheckerPtr = std::shared_ptr<TimestampChecker>;

public:
    /**
     * @brief Construct a new SrvMultiTaskInputChecker object
     *
     * @param hz, working frequency of the app
     */
    SrvMultiTaskInputChecker(Scalar const hz);

    /**
     * @brief Set up the checker
     *
     * @param config_file, config file
     */
    void Setup(std::string const& config_file);

    /**
     * @brief Cache Imu message
     *
     * @param imu_msg
     */
    void CacheImu(ImuType const& imu_msg);

    // /**
    //  * @brief Cache image message, check with itself
    //  *
    //  * @param msg
    //  */
    // void CacheSrvImage(ImageVector const& msg);

    /**
     * @brief Cache image tiemstamp, return state.
     *
     * @param current_image_time
     */
    bool CheckImageTimestamp(Timestamp const& current_image_time);

    // /**
    //  * @brief Get the Image Message object
    //  *
    //  * @return ImagePtr
    //  */
    // ImageVector& GetImageMessage();

private:
    /**
     * @brief If it is a message with recover timestamp for imu
     *
     * @param current_timestamp
     * @param last_timestamp
     * @return bool_t
     */
    bool_t isRecoverTimestampImu(Timestamp const& current_timestamp, Timestamp const& last_timestamp);

    /**
     * @brief If it is a message with recover timestamp
     *
     * @param timestamp timestamp of measure
     * @param cycle_time cycle time of this kind of measure
     * @return bool_t
     *
     */
    bool_t isRecoverTimestampMeasure(Timestamp const& timestamp, Scalar cycle_time);

    /**
     * @brief If it is a message with recover timestamp for Image
     *
     * @param current_timestamp
     * @param last_timestamp
     * @return bool_t
     */
    bool_t isRecoverTimestampImage(Timestamp const& current_timestamp, Timestamp const& last_timestamp);

    /**
     * @brief If it is a message with invalid timestamp for imu
     *
     * @param current_timestamp
     * @param last_timestamp
     * @return bool_t
     */
    bool_t isInvalidTimestampImu(Timestamp const& current_timestamp, Timestamp const& last_timestamp);

    /**
     * @brief If it is a message with invalid timestamp for other input
     *
     * @param timestamp
     * @param cycle_time
     * @return bool_t
     */
    bool_t isInvalidTimestampMeasure(Timestamp const& timestamp, Scalar cycle_time);

    /**
     * @brief If it is a message with invalid timestamp for Image
     *
     * @param current_timestamp
     * @param last_timestamp
     * @return bool_t
     */
    bool_t isInvalidTimestampImage(Timestamp const& current_timestamp, Timestamp const& last_timestamp);

    /**
     * @brief Get the Imu object
     *
     * @return ImuPtr
     */
    ImuPtr getImu();

private:
    Scalar     hz_;
    Scalar     cycle_time_;
    std::mutex mutex_;
    ImuPtr     last_imu_msg_;
    Timestamp  last_ret_timestamp_imu_;
    Timestamp  last_ret_timestamp_image_;
    Timestamp  last_image_time_;
    uint32_t   lost_count_imu_;
    uint32_t   lost_count_image_;

    // valid flag
    bool_t flag_recv_imu_;
    bool_t flag_recv_image_;
    bool_t flag_timestamp_imu_;
    bool_t flag_timestamp_image_;

    // params for yaml
    Scalar   timestamp_recover_cycle_time_lower_scale_imu_;
    Scalar   timestamp_recover_cycle_time_upper_scale_imu_;
    Scalar   timestamp_recover_cycle_time_scale_measure_;
    Scalar   timestamp_check_cycle_time_lower_scale_imu_;
    Scalar   timestamp_check_cycle_time_upper_scale_imu_;
    Scalar   timestamp_check_cycle_time_scale_measure_;
    uint32_t count_thresh_timestamp_recover_imu_;
    uint32_t count_thresh_timestamp_recover_measure_;
    uint32_t count_thresh_timestamp_invalid_imu_;
    uint32_t count_thresh_timestamp_invalid_measure_;
    Scalar   cycle_time_imu_;
    Scalar   cycle_time_image_;
    bool_t   check_imu_message_;

    // TimestampChecker
    TimestampCheckerPtr timestamp_checker_imu_;
    TimestampCheckerPtr timestamp_checker_image_;
};

}  // namespace perception
}  // namespace holo

#endif
