/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file corrected_imu_filter.h
 * @brief this file defines function to correct and smooth imu data
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2020-12-10"
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_CORRECTED_IMU_FILTER_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_CORRECTED_IMU_FILTER_H_

#include <holo/container/deque.h>
#include <holo/localization/tightly_coupled_fusion/common_types.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @brief this class to correct imu and make the output imu data smoothing
 */
class CorrectedImuFilter
{
public:
    /**
     * @brief method that could be used to process the imu
     * @todo add other method such as low pass filter
     */
    enum class Method
    {
        NEWEST_IMU  = 0u,  ///< return the newest imu
        AVERAGE_IMU = 1u,  ///< return the average of the historical imus
    };

    /**
     * @brief parameters for filter
     */
    struct Parameters
    {
        Method   method;              ///< filter method
        uint16_t filter_window_size;  ///< number of imu used in filter

        /**
         * @brief constructor
         *
         * @param[in] _method method type used to filter imu data
         * @param[in] _filter_window_size filter window size (number of imu used in filter algorithm)
         */
        Parameters(Method const _method = Method::NEWEST_IMU, uint16_t const _filter_window_size = 3u)
          : method(_method), filter_window_size(_filter_window_size)
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
         * @brief output stream for corrected imu filter parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << " CorrectedImuFilter Parameters: "
               << "\n filter method = " << static_cast<uint16_t>(parameters.method)
               << "\n filter window size = " << parameters.filter_window_size << std::endl;
            return os;
        }
    };  // Parameters

    /**
     * @brief construct a new corrected imu filter object
     *
     * @param[in] parameters parameters for filter
     */
    CorrectedImuFilter(Parameters const& parameters);

    /**
     * @brief destroy the corrected imu filter object
     *
     */
    ~CorrectedImuFilter();

    /**
     * @brief update imu buffer and return a filtered imu
     * @details the imu will be corrected by estimated result from vehicle state and smoothed
     *
     * @param[in] new_imu the new imu with bias and gravity
     * @param[in] new_vehicle_state vehicle state corresponding to new_imu
     * @param[in] gravity gravity in world frame
     * @return Imu the filtered imu
     */
    ImuType Run(ImuType const& new_imu, AdvancedNavstateType const& new_vehicle_state,
                Vector3Type const& gravity = Vector3Type(0.0, 0.0, 9.81));

    /**
     * @brief clear the data in this class
     */
    void Reset();

    /**
     * @brief get filter parameters
     *
     * @return Parameters const&
     */
    Parameters const& GetParameters() const;

protected:
    /**
     * @brief Get the Average Imu object
     * @note this function will modify member variables
     *       1. add new corrected imu into imu_buffer_ and remove the imu_buffer_.front() if it's size is larger than
     *          parameters_.filter_window_size
     *       2. update old_average_imu_
     *
     * @param[in] new_corrected_imu the new corrected imu
     * @return Imu average imu
     */
    ImuType getAverageImu(ImuType const& new_corrected_imu);

    /**
     * @brief correct imu by remove bias and gravity
     *
     * @param[in] new_imu the new imu with bias and gravity
     * @param[in] new_vehicle_state vehicle state corresponding to new_imu
     * @param[in] gravity gravity in world frame
     * @return Imu the corrected imu
     */
    ImuType correctImu(ImuType const& imu, AdvancedNavstateType const& vehicle_state, Vector3Type const& gravity) const;

protected:
    Parameters                            parameters_;       ///< parameters for the filter
    holo::container::Deque<ImuType, 100u> imu_buffer_;       ///< imu buffer used in the filter
    ImuType                               old_average_imu_;  ///< average corrected imu

};  // CorrectedImuFilter
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_CORRECTED_IMU_FILTER_H_