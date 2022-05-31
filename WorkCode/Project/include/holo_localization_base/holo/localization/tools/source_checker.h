/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file source_checker.h
 * @brief This header file define source state check.
 * @author lichao@holomatic.com
 * @author Wenzhi Liu(liuwenzhi@holomatic.com)
 * @date Sep 24, 2019
 */

#ifndef HOLO_LOCALIZATION_TOOLS_SOURCE_CHECKER_H_
#define HOLO_LOCALIZATION_TOOLS_SOURCE_CHECKER_H_

#include <functional>

#include <holo/localization/common/types.h>
#include <holo/os/time.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace localization
{
/// state of source
enum class SourceState
{
    GOOD   = 0,
    UNSURE = 1,
    BAD    = 2,
};

/**
 * @brief define the configuration of source checker.
 * @note  You must initialize the member variables in this structure.
 * @details
 * The time interval between two frames of sensor send is sensor_delta_t, the period of sensor is sensor_T.
 * The time interval between two frames of sensor arrival is system_delta_t.
 * max_timestamp_gap_tolerance is the maximum time delay we can tolerate,
 * min_period_multiple_in_normal_consistency and max_period_multiple_in_normal_consistency are thresholds from
 *     normal consistency to abnormal consistency.
 * min_period_multiple_in_low_obstruction is threshold from low blocking to medium blocking.
 * The parameters which are max_timestamp_gap_tolerance，min_period_multiple_in_normal_consistency，
 *     max_period_multiple_in_normal_consistency and min_period_multiple_in_low_obstruction correspond to
 *     the paramters whith the same name in SourceCheckerParameters.
 *
 *
 * rule for InconsistencyLevel
 *  1, (sensor_delta_t - sensor_T > max_timestamp_gap_tolerance || sensor_delta_t < 0) -> InconsistencyLevel::FATAL
 *  2, min_period_multiple_in_normal_consistency*sensor_T < sensor_delta_t <
 * max_period_multiple_in_normal_consistency*sensor_T
 *     -> InconsistencyLevel::NORMAL
 *  3,  other situations is InconsistencyLevel::UNEVEN
 *
 * rule for ObstructionLevel
 *  1, (system_delta_t < 0.001 || |system_delta_t - sensor_delta_t| > max_timestamp_gap_tolerance)
 *     -> ObstructionLevel::HIGH
 *  2, |system_delta_t - sensor_delta_t| < min_period_multiple_in_low_obstruction*sensor_T
 *     -> ObstructionLevel::LOW
 *  3, other situations are ObstructionLevel::MEDIUM
 */
struct SourceCheckerParameters
{
    /* source checker enable flag, default false.
       If you create a obj of source checker and this value is false, the return state of source checker is always GOOD
     */
    bool_t enable_checker = false;

    /* coordinate of source, default unknown */
    CoordinateType coord = CoordinateType();

    /* frequency of source in hz */
    float32_t frequency = std::numeric_limits<float32_t>::quiet_NaN();

    /* the threshold of status counter, When the low blocking state and normal consistency state accumulate to this
       threshold, the SourceState is GOOD. */
    int32_t status_counter_threshold = std::numeric_limits<int32_t>::min();

    /* Maximum time tolerance deviation (unit s) of sensor state in non worst state, If this value is set to a large
       value, the InconsistencyLevel is more difficult to FATAL and the ObstructionLevel is more difficult to HIGH */
    float32_t max_timestamp_gap_tolerance = std::numeric_limits<float32_t>::quiet_NaN();

    /* min period times of sensor consistency at normal,  If this value is set to a small value,
       the InconsistencyLevel is easier to NORMAL */
    float32_t min_period_multiple_in_normal_consistency = std::numeric_limits<float32_t>::quiet_NaN();

    /* max period times of sensor consistency at normal,  If this value is set to a large value,
       the InconsistencyLevel is easier to NORMAL */
    float32_t max_period_multiple_in_normal_consistency = std::numeric_limits<float32_t>::quiet_NaN();

    /* min period times of obstruction state in low, If this value is set to a small value,
       the system is more strict and the ObstructionLevel is more difficult to LOW */
    float32_t min_period_multiple_in_low_obstruction = std::numeric_limits<float32_t>::quiet_NaN();

    /* time interval of compute source frequency (unit s), E.g. The measurement time of IMU is about 10ms, if you want
     * to compute the frequency every 150 observations, you should set this parameter to 1.5 */
    float32_t source_actual_frequency_statistics_interval = std::numeric_limits<float32_t>::quiet_NaN();

    /* log source checker state flag, log information if it is true */
    bool_t enable_log = false;

    /**
     * @brief load yaml static function
     * @param yaml_node yaml node
     * @return source checker parameters read frome the yaml file
     */
    static SourceCheckerParameters LoadYaml(const holo::yaml::Node& yaml_node);
}; /* struct SourceCheckerParameters */

/**
 * @ingroup localization
 * @brief the source checker and sensor state management
 * @details a class to check status of the source measurements. It can update sensor state by the checking result.
 * @tparam T Instantiatable type: imu, chassis_state, gnss_pvt, gnss_position, odometry and camera_lane_boundaries.
 */
template <typename T>
class SourceCheckerT
{
public:
    using Parameters      = SourceCheckerParameters;
    using Ptr             = std::shared_ptr<SourceCheckerT>;
    using ExternalChecker = std::function<bool_t(const T&)>;

    /**
     * @brief inconsistency level definition
     * source timestamp   :...|...|...|...|...|...|....|..|.....|.|..|...|..........|...||...
     * inconsistency levle:   |      normal       |        uneven        |      fatal
     */
    enum InconsistencyLevel
    {
        NORMAL = 0,
        UNEVEN = 1,
        FATAL  = 2,
    };

    /**
     * @brief obstruction level definition
     * sensor timestamp  : ...|...|...|...|...|...|...|...|...|...|...|...|...|...|...|...|...
     * system timestamp  : ...|.............||||..|..|..|....|....|..|....|...|...|...|...|...
     * obstruction level :    |        high       |        medium         |       low
     */
    enum ObstructionLevel
    {
        LOW    = 0,
        MEDIUM = 1,
        HIGH   = 2,
    };

    /**
     * @brief the state of sensor checker
     * @todo consider packet loss rate and failure rate
     * @details The actual_frequency is statistical frequency of the latest time period.
     * E.g. The source frequncy statistics interval is 1s. Source checker counts frequency from 0s,
     *      and completes at 1s. If you want to get the source frequency at 1.5s, it will return a frequency of 0~1s.
     */
    struct State
    {
        int32_t   status_counter               = 0; /* counter of status,  BAD<=(-threshold)<UNSURE<(threshold)<=GOOD */
        uint32_t  frequency_statistics_counter = 0u;                       /* counter of frequency statistics */
        Timestamp last_sensor_timestamp        = Timestamp(0u, 0u);        /* Timestamp of last source */
        Timestamp last_system_timestamp        = Timestamp(0u, 0u);        /* Timestamp of last system */
        Timestamp last_frequency_statistics_timestamp = Timestamp(0u, 0u); /* Timestamp of last frequency statistics */
        InconsistencyLevel inconsistency_level        = InconsistencyLevel::NORMAL; /* inconsistency level of source */
        ObstructionLevel   obstruction_level          = ObstructionLevel::LOW;      /* obstruction level of source */
        bool_t             external_checker_signal    = true;   /* return value of external checker function */
        Scalar             actual_frequency           = 1000.0; /* actual frequency of source */
    };                                                          /* struct State */

    /**
     * @brief delete default constructor
     */
    SourceCheckerT() = delete;

    /**
     * @brief Construct a new Source Checker T object
     * @param params source checker configuration
     * @param source_name This parameter is the name of source. It is used to print info and create log file.
     *                    If you don't set it up, can not create log file. default "".
     * @param function external check function, default blank
     */
    SourceCheckerT(const Parameters& params, const std::string& source_name = std::string(""),
                   const ExternalChecker& function = {});

    /**
     * @brief destructor for source checker
     */
    ~SourceCheckerT() noexcept;

    /**
     * @brief check status of the source
     * @param[in] m the measurement
     * @return the state of source
     */
    SourceState CheckSourceState(const T& m);

    /**
     * @brief check status of the source
     * @return the state of sensor
     */
    SourceState GetSourceState() const
    {
        return DetermineSourceState();
    }

    /**
     * @brief get source inconsistency level
     * @return the inconsistency level of source
     */
    InconsistencyLevel GetSourceInconsistencyLevel() const
    {
        return state_.inconsistency_level;
    }

    /**
     * @brief get source obstruction level
     * @return the obstruction level of source
     */
    ObstructionLevel GetSourceObstructionLevel() const
    {
        return state_.obstruction_level;
    }

    /**
     * @brief get source actual frequency
     * @return the actual frequency of source
     */
    Scalar GetSourceActualFrequency() const
    {
        return state_.actual_frequency;
    }

protected:
    /**
     * @brief check initialization parameters
     * @details if the parameters is not initialized, the close_checker_flag_ is set to true.
     * @param source_name source name
     */
    void CheckInitializationParameters(const std::string& source_name);

    /**
     * @brief initialize output file
     * @param log_path_name the path and name of the log file
     */
    void InitializeOutputLogFile(const std::string& log_path_name);

    /**
     * @brief check consistency of source Timestamp
     * @param Timestamp Timestamp of source
     * @return InconsistencyLevel [NORMAL, MEDIUM, FATAL]
     */
    InconsistencyLevel CheckSourceConsistency(const Timestamp& Timestamp) const;

    /**
     * @brief check source obstruction state
     * @param system_timestamp timestamp of system
     * @param sensor_timestamp timestamp of sensor
     * @return ObstructionLevel [HIGH, MIDDLE, LOW]
     */
    ObstructionLevel CheckSourceObstructionState(const Timestamp& system_timestamp,
                                                 const Timestamp& sensor_timestamp) const;

    /**
     * @brief log source checker information
     * @details If has no unique function output [system_time, source_time, consistency_level, obstruction_level,
     * source_checker_state] Else output [system_time, source_time, consistency_level, obstruction_level, unique_state,
     * source_checker_state]
     * @param system_timestamp timestamp of system
     * @param sensor_timestamp timestamp of sensor
     * @param source_state current source state
     */
    void OutputSourceCheckerInfo(const Timestamp& system_timestamp, const Timestamp& sensor_timestamp,
                                 const SourceState& source_state) const;

    /**
     * @brief increase the counter of the specific sensor status
     */
    void IncStatusCounter();

    /**
     * @brief decrease the counter of the specific sensor status
     */
    void DecStatusCounter();

    /**
     * @brief determine the state of the specific sensor
     * @return the state of sensor
     */
    SourceState DetermineSourceState() const;

    /**
     * @brief Compute source frequency
     * @details 1, if it is the first frame, last_frequency_statistics_timestamp = sensor_timestamp, else to setp 2.
     * 2, If the time interval which are from last_frequency_statistics_timestamp to sensor_timestamp is greater than
     * the set threshold, compute actual frequency and reset last_frequency_statistics_timestamp and
     * frequency_statistics_counter, else the frequency_statistics_counter++.
     * @param sensor_timestamp timestamp of sensor
     */
    void ComputeSourceFrequency(const Timestamp& sensor_timestamp);

private:
    /* state */
    State state_;

    /* parameters */
    Parameters params_;

    /* external function */
    ExternalChecker external_function_;

    /* output file */
    FILE* fp_output_;

}; /* class SourceCheckerT */

using SourceCheckerChassisState         = SourceCheckerT<ChassisState>;
using SourceCheckerGnssPosition         = SourceCheckerT<GnssPosition>;
using SourceCheckerGnssPvtType          = SourceCheckerT<GnssPvtType>;
using SourceCheckerOdometry             = SourceCheckerT<OdometryType>;
using SourceCheckerImu                  = SourceCheckerT<ImuType>;
using SourceCheckerCameraLaneBoundaries = SourceCheckerT<CameraLaneBoundariesType>;
} /* namespace localization */

} /* namespace holo */

#endif  // HOLO_LOCALIZATION_TOOLS_SOURCE_CHECKER_H_
