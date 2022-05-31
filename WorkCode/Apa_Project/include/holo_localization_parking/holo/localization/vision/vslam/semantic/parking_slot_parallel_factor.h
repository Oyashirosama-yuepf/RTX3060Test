/*!
 * \brief VSLAM parkingslot parallel factor
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \author Changxi Cheng, chengchangxi@holomatic.com
 * \date May-10-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_PARALLEL_FACTOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_PARALLEL_FACTOR_H_

#include <holo/localization/vision/vslam/semantic/common_types.h>

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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief vslam parking slot parallel factor
 *
 * @details error = cross(p1-p0, p2-p3) or error = cross(p2-p1, p3-p0)
 *          p0, p1, p2, p3 represent parking slot vertexes in world coordinate.
 */
class ParkingSlotParallelFactor
  : public gtsam::NoiseModelFactor4<gtsam::Point3, gtsam::Point3, gtsam::Point3, gtsam::Point3>
{
public:
    /**
     * @brief smart pointer
     */
    typedef boost::shared_ptr<ParkingSlotParallelFactor>                                         Ptr;
    typedef boost::shared_ptr<const ParkingSlotParallelFactor>                                   ConstPtr;
    typedef gtsam::NoiseModelFactor4<gtsam::Point3, gtsam::Point3, gtsam::Point3, gtsam::Point3> Base;

    /**
     * @brief Construct a new ParkingSlotParallelFactor object
     *
     * @param vertex0_key associated vertex 0 variable key
     * @param vertex1_key associated vertex 1 variable key
     * @param vertex2_key associated vertex 2 variable key
     * @param vertex3_key associated vertex 3 variable key
     * @param model noise model for parking slot parallel constraint, in X-Y-Z
     */
    ParkingSlotParallelFactor(const gtsam::Key& vertex0_key, const gtsam::Key& vertex1_key,
                              const gtsam::Key& vertex2_key, const gtsam::Key& vertex3_key,
                              const gtsam::SharedNoiseModel& model);

    /**
     * @brief deconstructor
     *
     */
    virtual ~ParkingSlotParallelFactor()
    {
    }

    /**
     * @brief error function
     *
     * @param vertex0 vertex0 in world frame
     * @param vertex1 vertex1 in world frame
     * @param vertex2 vertex2 in world frame
     * @param vertex3 vertex3 in world frame
     * @param H0 the optional Jacobian matrix for vertex0
     * @param H1 the optional Jacobian matrix for vertex1
     * @param H2 the optional Jacobian matrix for vertex2
     * @param H3 the optional Jacobian matrix for vertex3
     * @return error
     */
    virtual gtsam::Vector evaluateError(const gtsam::Point3& vertex0, const gtsam::Point3& vertex1,
                                        const gtsam::Point3& vertex2, const gtsam::Point3& vertex3,
                                        boost::optional<gtsam::Matrix&> H0 = boost::none,
                                        boost::optional<gtsam::Matrix&> H1 = boost::none,
                                        boost::optional<gtsam::Matrix&> H2 = boost::none,
                                        boost::optional<gtsam::Matrix&> H3 = boost::none) const override;

private:
};  // class ParkingSlotParallelFactor

typedef ParkingSlotParallelFactor::Ptr ParkingSlotParallelFactorPtr;

}  // namespace semantic
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_PARALLEL_FACTOR_H_