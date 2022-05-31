/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file source_checker.hpp
 * @brief The implementation of source checker.
 * @author lichao@holomatic.com
 * @author Wenzhi Liu(liuwenzhi@holomatic.com)
 * @date Sep 24, 2019
 */

#include <holo/log/hololog.h>

namespace holo
{
namespace localization
{
/**
 * @brief Template metaprogramming.
 * @note  Check if there is function of GetStatus in the instantiation class
 * @param T is class type to be instantiated
 * @return if T has function of GetStatus, the value is true, otherwise is false
 */
template <typename T>
struct HasFunctionGetStatus
{
private:
    template <typename U>
    static auto check(int) -> decltype(std::declval<U>().GetStatus(), std::true_type());
    template <typename U>
    static std::false_type check(...);

public:
    enum
    {
        value = std::is_same<decltype(check<T>(0)), std::true_type>::value
    };
};

/**
 * @brief Template metaprogramming.
 * @note  Compile this template function if has function of GetStatus.
 *        The definition of source state is 0 in ${holo_base} when the source is all good.
 *        Please change this function when the definition is changed in the future.
 * @param m is source measurement
 * @return if the return value of function GetStatus is 0, return true
 */
template <typename T>
typename std::enable_if<HasFunctionGetStatus<T>::value, bool>::type IsAllGood(const T& m)
{
    return static_cast<uint32_t>(m.GetStatus()) == 0u;
};

/**
 * @brief Template metaprogramming.
 * @note  Compile this template function if hasn't function of GetStatus.
 * @param m is source measurement
 * @return always true
 */
template <typename T>
typename std::enable_if<!HasFunctionGetStatus<T>::value, bool>::type IsAllGood(const T& m)
{
    (void)m;
    return true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
SourceCheckerT<T>::SourceCheckerT(const Parameters& params, const std::string& source_name,
                                  const ExternalChecker& function)
  : params_(params), external_function_(function), fp_output_(nullptr)
{
    if (!params_.enable_checker)
    {
        LOG(WARNING) << source_name << " Checker is disable. If you want to use it, "
                     << "please set 'enable_checker' of 'SourceCheckerParameters' to true" << std::endl;
    }
    else
    {
        LOG(INFO) << "Init source checker";
        /* check for initialization parameters */
        CheckInitializationParameters(source_name);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
SourceCheckerT<T>::~SourceCheckerT() noexcept
{
    if (params_.enable_log && fp_output_)
    {
        (void)fclose(fp_output_);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SourceCheckerT<T>::CheckInitializationParameters(const std::string& source_name)
{
    if (external_function_)
    {
        LOG(INFO) << "Input unique function";
    }

    /* print params */
    LOG(INFO) << source_name << " Checker Params:\n"
              << "coord                                     = " << std::hex << "0x" << (uint32_t)params_.coord << "\n"
              << std::dec << "frequency                                 = " << params_.frequency << "\n"
              << "status counter threshold                  = " << params_.status_counter_threshold << "\n"
              << "max timestamp gap tolerance               = " << params_.max_timestamp_gap_tolerance << "\n"
              << "min period multiple in normal consistency = " << params_.min_period_multiple_in_normal_consistency
              << "\n"
              << "max period multiple in normal consistency = " << params_.max_period_multiple_in_normal_consistency
              << "\n"
              << "min period multiple in low obstruction    = " << params_.min_period_multiple_in_low_obstruction
              << "\n"
              << "enable log information                    = " << static_cast<uint32_t>(params_.enable_log);

    /* check parameter initialization state */
    bool_t parameter_state = (params_.status_counter_threshold != std::numeric_limits<int32_t>::min() &&
                              !std::isnan(params_.frequency) && !std::isnan(params_.max_timestamp_gap_tolerance) &&
                              !std::isnan(params_.min_period_multiple_in_normal_consistency) &&
                              !std::isnan(params_.max_period_multiple_in_normal_consistency) &&
                              !std::isnan(params_.min_period_multiple_in_low_obstruction) &&
                              !std::isnan(params_.source_actual_frequency_statistics_interval));

    if (!parameter_state)
    {
        params_.enable_checker = false;
        LOG(WARNING) << source_name << " Checker params are not initialization! Source Checker will close!";
    }

    /* open output file if choose log information */
    if (params_.enable_log && params_.enable_checker)
    {
        if (source_name.empty())
        {
            params_.enable_log = false;
            LOG(WARNING) << "Your source name setting is invalid! Can not print log file! "
                         << "If you want to create log file, please reset the source name!";
        }
        else
        {
            const std::string log_path_name = "holo_localization_base/source_checker/" + source_name + ".csv";
            InitializeOutputLogFile(log_path_name);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SourceCheckerT<T>::InitializeOutputLogFile(const std::string& log_path_name)
{
    (void)holo::CreateHoloLogSubdirectory(holo::GetParentDirectory(log_path_name));
    fp_output_ = fopen(holo::GetLogFileAbsolutePath(log_path_name).c_str(), "w+");
    LOG(INFO) << "log file's path is " << holo::GetHoloLogRootDirectory() << "/" << log_path_name;

    if (external_function_)
    {
        (void)fprintf(fp_output_, "%s,%s,%s,%s,%s,%s\n", "system_timestamp", "source_timestamp",
                "consistency(0:normal 1:uneven 2:fatal)", "obstruction_state(0:low 1:medium 2:high)",
                "external_checker_signal(0:ok 1:no)", "source_checker_state(0:good 1:unsure 2:bad)");
    }
    else
    {
        (void)fprintf(fp_output_, "%s,%s,%s,%s,%s\n", "system_timestamp", "source_timestamp",
                "consistency(0:normal 1:uneven 2:fatal)", "obstruction_state(0:low 1:medium 2:high)",
                "source_checker_state(0:good 1:unsure 2:bad)");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
SourceState SourceCheckerT<T>::CheckSourceState(const T& m)
{
    if (!params_.enable_checker)
    {
        return SourceState::GOOD;
    }

    /* get current sensor timestamp and system timestamp*/
    const Timestamp& current_sensor_time = m.GetTimestamp();
    uint32_t         system_time_sec;
    uint32_t         system_time_nsec;
    (void)holo::os::GetSystemTime(system_time_sec, system_time_nsec);
    const Timestamp current_system_time(system_time_sec, system_time_nsec);

    /* check source consistency and source obstruction state */
    state_.inconsistency_level = CheckSourceConsistency(current_sensor_time);
    state_.obstruction_level   = CheckSourceObstructionState(current_system_time, current_sensor_time);

    ComputeSourceFrequency(current_sensor_time);

    /* check other unique state of source */
    if (external_function_)
    {
        state_.external_checker_signal = external_function_(m);
    }
    else
    {
        state_.external_checker_signal = true;
    }

    /* update state timestamp */
    state_.last_system_timestamp = current_system_time;
    state_.last_sensor_timestamp = current_sensor_time;

    if (state_.inconsistency_level == InconsistencyLevel::FATAL || state_.obstruction_level == ObstructionLevel::HIGH)
    {
        state_.status_counter = -params_.status_counter_threshold;
        LOG(ERROR) << "CheckSourceState --- 0x" << std::hex << (uint32_t)params_.coord << " "
                   << current_sensor_time.ToString() << " measurements are fatal inconsistency or blocking!";
    }
    else if (state_.inconsistency_level == InconsistencyLevel::UNEVEN ||
             state_.obstruction_level == ObstructionLevel::MEDIUM || !IsAllGood<T>(m))
    {
        DecStatusCounter();
        LOG(WARNING) << "CheckSourceState --- 0x" << std::hex << (uint32_t)params_.coord
                     << " measurements are medium inconsistency or inhomogeneous or not good!"
                     << " The status counter has been decreased, which = " << std::dec << state_.status_counter;
    }
    else
    {
        IncStatusCounter();
    }

    const SourceState source_checker_result = DetermineSourceState();

    /* record source checker information */
    if (params_.enable_log && fp_output_)
    {
        OutputSourceCheckerInfo(current_system_time, current_sensor_time, source_checker_result);
    }

    return source_checker_result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SourceCheckerT<T>::OutputSourceCheckerInfo(const Timestamp& system_timestamp, const Timestamp& sensor_timestamp,
                                                const SourceState& source_state) const
{
    if (external_function_)
    {
        (void)fprintf(fp_output_, "%f,%f,%u,%u,%u,%u\n", system_timestamp.ToSec(), sensor_timestamp.ToSec(),
                state_.inconsistency_level, state_.obstruction_level, !state_.external_checker_signal,
                static_cast<uint32_t>(source_state));
    }
    else
    {
        (void)fprintf(fp_output_, "%f,%f,%u,%u,%u\n", system_timestamp.ToSec(), sensor_timestamp.ToSec(),
                state_.inconsistency_level, state_.obstruction_level, static_cast<uint32_t>(source_state));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
typename SourceCheckerT<T>::InconsistencyLevel
SourceCheckerT<T>::CheckSourceConsistency(const Timestamp& Timestamp) const
{
    /* skip if it's first measurement of sequence */
    if (state_.last_sensor_timestamp.IsZero())
    {
        return InconsistencyLevel::NORMAL;
    }

    /* interval    : ...fatal...|...uneven...|...normal...|...uneven...|...fatal...
     * time(in seconds):        0      min_times*T   max_time*T    max_timestamp
     * which min_times is min_period_multiple_in_normal_consistency, max_time is
     * max_period_multiple_in_normal_consistency, T is measurement period of sensor, max_timestamp is
     * max_timestamp_gap_tolerance plus period.
     * */
    const Scalar interval = (Timestamp - state_.last_sensor_timestamp).ToSec();

    if (interval < 0.0 || interval - 1.0f / params_.frequency > params_.max_timestamp_gap_tolerance)
    {
        LOG(ERROR) << std::setprecision(20) << "CheckConsistency --- 0x" << std::hex << (uint32_t)params_.coord
                   << " measurements are fatal inconsistency! "
                   << "which interval(s) = " << std::dec << interval;
        return InconsistencyLevel::FATAL;
    }
    else if (interval < (params_.min_period_multiple_in_normal_consistency / params_.frequency) ||
             interval > (params_.max_period_multiple_in_normal_consistency / params_.frequency))
    {
        LOG(WARNING) << std::setprecision(20) << "CheckConsistency --- 0x" << std::hex << (uint32_t)params_.coord
                     << " measurements are uneven inconsistency! "
                     << "which interval(s) = " << std::dec << interval << "\t frequency: " << params_.frequency;
        return InconsistencyLevel::UNEVEN;
    }

    return InconsistencyLevel::NORMAL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
typename SourceCheckerT<T>::ObstructionLevel SourceCheckerT<T>::CheckSourceObstructionState(
    const Timestamp& system_timestamp, const Timestamp& sensor_timestamp) const
{
    /* skip if it's first measurement of sequence */
    if (state_.last_sensor_timestamp.IsZero() || state_.last_system_timestamp.IsZero())
    {
        return ObstructionLevel::LOW;
    }

    /* system interval   : ...high obstruction...|...........
     * time(in seconds)  :                     0.001
     * different interval: ....low obstruction...|...medium obstruction...|...high obstruction...
     * time(in seconds)  :                 min_times*T                max_timestamp
     * which min_times is min_period_multiple_in_low_obstruction, max_timestamp is max_timestamp_gap_tolerance,
     *       T is measurement period of sensor.
     * */
    const Scalar system_interval    = (system_timestamp - state_.last_system_timestamp).ToSec();
    const Scalar sensor_interval    = (sensor_timestamp - state_.last_sensor_timestamp).ToSec();
    const Scalar different_interval = std::fabs(system_interval - sensor_interval);

    if (different_interval > params_.max_timestamp_gap_tolerance || system_interval < 0.001)
    {
        LOG(ERROR) << "CheckSourceObstructionState--- 0x" << std::hex << (uint32_t)params_.coord
                   << " arrival time blocking! ";
        return ObstructionLevel::HIGH;
    }
    else if (different_interval > (params_.min_period_multiple_in_low_obstruction / params_.frequency))
    {
        LOG(WARNING) << "CheckSourceObstructionState--- 0x" << std::hex << (uint32_t)params_.coord
                     << " arrival time are inhomogeneous! ";
        return ObstructionLevel::MEDIUM;
    }

    return ObstructionLevel::LOW;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SourceCheckerT<T>::IncStatusCounter()
{
    if (state_.status_counter < 0)
    {
        state_.status_counter = 0;
    }
    else if (state_.status_counter < params_.status_counter_threshold)
    {
        state_.status_counter++;
    }
    else
    {
        state_.status_counter = params_.status_counter_threshold;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SourceCheckerT<T>::DecStatusCounter()
{
    if (state_.status_counter > 0)
    {
        state_.status_counter = 0;
    }
    else if (state_.status_counter > -params_.status_counter_threshold)
    {
        state_.status_counter--;
    }
    else
    {
        state_.status_counter = -params_.status_counter_threshold;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
SourceState SourceCheckerT<T>::DetermineSourceState() const
{
    if (!params_.enable_checker ||
        (state_.status_counter >= params_.status_counter_threshold && state_.external_checker_signal))
    {
        return SourceState::GOOD;
    }
    else if (state_.status_counter <= -params_.status_counter_threshold || !state_.external_checker_signal)
    {
        return SourceState::BAD;
    }

    return SourceState::UNSURE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SourceCheckerT<T>::ComputeSourceFrequency(const Timestamp& sensor_timestamp)
{
    if (state_.last_frequency_statistics_timestamp.IsZero())
    {
        state_.last_frequency_statistics_timestamp = sensor_timestamp;
        state_.frequency_statistics_counter        = 1;
        return;
    }

    const Scalar interval = (sensor_timestamp - state_.last_frequency_statistics_timestamp).ToSec();

    if (interval > params_.source_actual_frequency_statistics_interval)
    {
        state_.actual_frequency                    = state_.frequency_statistics_counter / interval;
        state_.frequency_statistics_counter        = 1;
        state_.last_frequency_statistics_timestamp = sensor_timestamp;
    }
    else
    {
        state_.frequency_statistics_counter++;
    }
}

}  // namespace localization
}  // namespace holo
