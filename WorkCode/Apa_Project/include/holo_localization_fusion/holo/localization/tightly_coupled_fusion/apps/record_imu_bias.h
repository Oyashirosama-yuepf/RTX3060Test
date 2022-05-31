/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file record_imu_bias.h
 * @brief This header file defines record imu bias
 * @author Binbin Wang wangbinbin@holomaitc.com
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2020-12-15"
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_APPS_RECORD_IMU_BIAS_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_APPS_RECORD_IMU_BIAS_H_

#include <fstream>
#include <numeric>

#include <holo/container/deque.h>
#include <holo/localization/tightly_coupled_fusion/common_types.h>
#include <holo/utils/holo_root.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup apps
 * @{
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * @brief define record imu bias class
 */
class RecordImuBias
{
public:
    using DequeType = holo::container::Deque<Vector3Type, 100u>;
    using Ptr       = std::shared_ptr<RecordImuBias>;
    /**
     * @brief record imu bias parameters
     *
     */
    struct Parameters
    {
        ///< imu buffer size for get standard deviation
        uint16_t const imu_bias_buffer_size;

        ///< threshold to check if acc bias is converged, unit, m/s^2
        Scalar const acc_bias_std_threshold;

        ///< threshold to check if gyro bias is converged, unit, degree/s
        Scalar const gyro_bias_std_threshold;

        ///< threshold to check whether acc bias is available, unit, m/s^2
        Scalar const acc_bias_threshold;

        ///< threshold to check whether gyro bias is available, unit, degree/s
        Scalar const gyro_bias_threshold;

        ///< time of bias accumulated convergent duration threshold, unit, s
        Scalar const accumulated_convergent_duration;

        ///< accumulated time since last record, unit, s
        Scalar const record_duration;

        ///< file to read optimized imu bias
        std::string const imu_bias_file_name;

        /**
         * @brief Construct a new Parameters object
         *
         * @param _imu_bias_buffer_size imu buffer size for get std
         * @param _acc_bias_std_threshold threshold to check if imu acc bias is converged, unit, m/s^2
         * @param _gyro_bias_std_threshold threshold to check if imu gyro bias is converged, unit, degree/s
         * @param _acc_bias_threshold threshold to check whether acc bias is available, unit, m/s^2
         * @param _gyro_bias_threshold threshold to check whether gyro bias is available, unit, degree/s
         * @param _accumulated_convergent_duration time of bias accumulated convergent duration threshold, unit, s
         * @param _record_duration accumulated time since last record, unit, s
         */
        Parameters(uint16_t const _imu_bias_buffer_size = 30u, Scalar const _acc_bias_std_threshold = 0.01,
                   Scalar const _gyro_bias_std_threshold = 0.01, Scalar const _acc_bias_threshold = 0.5,
                   Scalar const _gyro_bias_threshold = 0.3, Scalar const _accumulated_convergent_duration = 3.0,
                   Scalar const _record_duration = 600.0, std::string _imu_bias_file_name = "")
          : imu_bias_buffer_size(_imu_bias_buffer_size)
          , acc_bias_std_threshold(_acc_bias_std_threshold)
          , gyro_bias_std_threshold(_gyro_bias_std_threshold)
          , acc_bias_threshold(_acc_bias_threshold)
          , gyro_bias_threshold(_gyro_bias_threshold)
          , accumulated_convergent_duration(_accumulated_convergent_duration)
          , record_duration(_record_duration)
          , imu_bias_file_name(_imu_bias_file_name)
        {
        }

        /**
         * @brief static method to load parameters from yaml
         *
         * @param node yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief static method to generate example parameters for unit test
         *
         * @return the generated parameters for unit test
         */
        static Parameters GenerateExample();

        /**
         * @brief output stream for record imu bias parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << "Record Imu Bias Parameters: "
               << "\n imu_bias_buffer_size = " << parameters.imu_bias_buffer_size
               << "\n acc_bias_std_threshold[m/s^2] = " << parameters.acc_bias_std_threshold
               << "\n gyro_bias_std_threshold[degree/s] = " << parameters.gyro_bias_std_threshold
               << "\n accumulated_convergent_duration[s] = " << parameters.accumulated_convergent_duration
               << "\n record_duration[s] = " << parameters.record_duration
               << "\n imu_bias_file_name = " << parameters.imu_bias_file_name << std::endl;
            return os;
        }
    };

    /**
     * @brief this struct aims to store the variables
     */
    struct State
    {
        bool_t      is_acc_meet;     // if acc bias meet the std threshold requirement
        bool_t      is_gyro_meet;    // if gyro bias meet the std threshold requirement
        Vector3Type last_acc_bias;   // last acc bias
        Vector3Type last_gyro_bias;  // last gyro bias

        /**
         * @brief Construct a new State object
         *
         * @param _is_acc_meet if acc bias meet the std threshold requirement
         * @param _is_gyro_meet if gyro bias meet the std threshold requirement
         * @param _last_acc_bias last acc bias
         * @param _last_gyro_bias last gyro bias
         */
        State(bool_t const _is_acc_meet = false, bool_t const _is_gyro_meet = false,
              Vector3Type const& _last_acc_bias  = Vector3Type::Zero(),
              Vector3Type const& _last_gyro_bias = Vector3Type::Zero())
          : is_acc_meet(_is_acc_meet)
          , is_gyro_meet(_is_gyro_meet)
          , last_acc_bias(_last_acc_bias)
          , last_gyro_bias(_last_gyro_bias)
        {
        }
    };  // State

    /**
     * @brief this struct aims to store the variables about time parameter of record bias
     *
     */
    struct RecordTime
    {
        /// parameters to control the record frequency
        bool_t    is_bias_recorded;       // flag to store whether the bias is recorded until current time
        Timestamp last_record_timestamp;  // store recent timestamp when the bias is recorded, only if
                                          // ${is_bias_recorded} is true

        /// parameters to check whether the converged bias is stable
        bool_t    has_bias_converged;        // flag to store whether the bias is converged in current record cycle
        Timestamp first_converge_timestamp;  // store fist timestamp when the bias is converged in current record cycle,
                                             // only if ${has_bias_converged} is true

        RecordTime(bool_t _is_bias_recorded = false, Timestamp _last_record_timestamp = Timestamp(0, 0),
                   bool_t _has_bias_converged = false, Timestamp _first_converge_timestamp = Timestamp(0, 0))
          : is_bias_recorded(_is_bias_recorded)
          , last_record_timestamp(_last_record_timestamp)
          , has_bias_converged(_has_bias_converged)
          , first_converge_timestamp(_first_converge_timestamp)
        {
        }
    };

    /**
     * @brief constructor
     *
     * @param parameters
     */
    RecordImuBias(Parameters const& parameters);

    /**
     * @brief destructor
     *
     */
    ~RecordImuBias();

    /**
     * @brief Get the Parameters object
     *
     * @return Parameters record imu bias parameters
     */
    Parameters const& GetParameters() const;

    /**
     * @brief record imu bias when it is converged
     *
     * @param[in] newest_acc_bias newest acc bias
     * @param[in] newest_gyro_bias newest gyro bias
     * @param[in] current_time current time
     * @return holo::OptionalT<State>
     *         return holo::optional::none when:
     *         1. new record cycle has not been started
     *         2. size of bias buffer < threshold
     *         3. both acc and gyro are not meet std requirement
     *         4. convergent time is not met
     *         5. imu bias is not updated
     *         otherwise return holo::OptionalT<State>
     */
    holo::OptionalT<State> Run(Vector3Type const& newest_acc_bias, Vector3Type const& newest_gyro_bias,
                               Timestamp const& current_time);

    /**
     * @brief write imu bias to file
     *
     * @param imu_bias_file file path to write imu bias
     * @param state record imu bias state
     */
    void WriteToFile(std::string const& imu_bias_file, State const& state) const;

    /**
     * @brief reset internal variables
     *
     */
    void Reset();

private:
    /**
     * @brief compute imu bias standard deviation from buffer
     * @param bias_buffer imu bias buffer
     *
     * @return standard deviation of imu bias in bias buffer
     */
    Vector3Type computeImuBiasStdFromBuffer(DequeType const& bias_buffer) const;

    Parameters parameters_;        ///< parameters of record imu bias
    DequeType  acc_bias_buffer_;   ///< acc bias buffer used to record acc bias
    DequeType  gyro_bias_buffer_;  ///< gyro bias buffer used to record gyro bias
    RecordTime record_time_;       ///< time state about recording bias
};                                 // RecordImuBias

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_APPS_RECORD_IMU_BIAS_H_