/*!
 * \brief failure detection class header file in VSLAM
 * \author shuaijie.li @ lishuaijie@holomatic.com
 * \date Oct-24-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_FAILURE_DETECTION_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_FAILURE_DETECTION_H_

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/sliding_window_state.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * @brief define failure detection class
 */
class FailureDetection
{
public:
    /**
     * @brief failure detection parameters
     */
    struct Parameters
    {
        /// @brief translation threshold along x axis[m] between two consecutive image frames
        Scalar x_translation_threshold;

        /// @brief translation threshold along y axis[m] between two consecutive image frames
        Scalar y_translation_threshold;

        /// @brief yaw threshold[rad] between two consecutive image frames
        Scalar yaw_threshold;

        /// @brief vehicle speed threshold[m/s]
        Scalar vehicle_speed_threshold;

        /// @brief constructor
        Parameters(const Scalar _x_translation_threshold = 3.3, const Scalar _y_translation_threshold = 0.44,
                   const Scalar _yaw_threshold = 0.55, const Scalar _vehicle_speed_threshold = 33.0)
          : x_translation_threshold(_x_translation_threshold)
          , y_translation_threshold(_y_translation_threshold)
          , yaw_threshold(_yaw_threshold)
          , vehicle_speed_threshold(_vehicle_speed_threshold)
        {
        }

        /// @brief load parameters from yaml
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        /// @brief example
        static Parameters Example();

        /// @brief operator <<
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "Failure Detection Parameters: "
               << "\n x_translation_threshold[m] = " << parameters.x_translation_threshold
               << "\n y_translation_threshold[m] = " << parameters.y_translation_threshold
               << "\n yaw_threshold[rad] = " << parameters.yaw_threshold
               << "\n vehicle_speed_threshold[m/s] = " << parameters.vehicle_speed_threshold << std::endl;
            return os;
        }
    };  // Parameters

    /**
     * @brief constructor
     */
    FailureDetection(const Parameters& parameters) : parameters_(parameters)
    {
    }

    /**
     * @brief judge whether the estimated state is a failure case
     *        failure case: x, y, yaw chage too much or vehicle speed is not reasonable
     * @todo (Feng. Li 2020-02-10) we should carefully design the failure detection and recovery mechanisms. rather than
     * simply detect whether the trajectory is jump with some hard code threshold. it's seems not so much general.
     *
     * @param[in] state the newest estimated sliding window state
     * @param[in] old_timestamp timestamp of the previous SlidingWindowState
     * @param[in] frequency frequency of vio thread
     * @return whether is failure case
     */
    bool Run(const SlidingWindowState& state, const Timestamp& old_timestamp, const Scalar frequency) const;

private:
    // parameters
    Parameters parameters_;

};  // FailureDetection
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_FAILURE_DETECTION_H_
