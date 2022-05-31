/*!
 * \brief VSLAM parking slot vertex factor header file
 * \author Heiko Yu, yuchangsong@holomatic.com
 * \author Changxi Cheng, chengchangxi@holomatic.com
 * \date June-02-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_VERTEX_FACTOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_VERTEX_FACTOR_H_

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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief vslam parking slot vertex factor
 * @details error = Inverse(T_wb) * P_w - P_b
 *                  P_b represents parking-spot vertex in body coordinate, observation,
 *                  P_w represents parking-spot vertex in world coordinate, first estimated value,
 *                  T_wb represents pose from body to world coordinate, second estimated value.
 */
class ParkingSlotVertexFactor : public gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Point3>
{
public:
    /**
     * @brief smart pointer
     */
    typedef boost::shared_ptr<ParkingSlotVertexFactor>            Ptr;
    typedef boost::shared_ptr<const ParkingSlotVertexFactor>      ConstPtr;
    typedef gtsam::NoiseModelFactor2<gtsam::Pose3, gtsam::Point3> Base;

    /**
     * @brief Construct a new ParkingSlotFactor object
     *
     * @param pose_key key of estimated pose, T_wb1
     * @param vertex_key key of estimated vertex in world coordinate, P_w
     * @param measurement measurement (vertex) in body coordinate, P_b1
     * @param model noise model
     */
    ParkingSlotVertexFactor(const gtsam::Key& pose_key, const gtsam::Key& vertex_key, const gtsam::Point3& measurement,
                            const gtsam::SharedNoiseModel& model);

    /**
     * @brief deconstructor
     */
    virtual ~ParkingSlotVertexFactor()
    {
    }

    /**
     * @brief Get the parking-spot vertex measurement object
     *
     * @return const gtsam::Point3
     */
    const gtsam::Point3& GetParkingSlotVertexMeasurement() const;

    /**
     * @brief error function
     *
     * @param T_wb body pose in world frame
     * @param P_w the parking-spot vertex in world frame
     * @param H1 the optional Jacobian matrix for pose from body into world
     * @param H2 the optional Jacobian matrix for parking-spot vertex in the world
     * @return gtsam::Vector
     */
    virtual gtsam::Vector evaluateError(const gtsam::Pose3& T_wb, const gtsam::Point3& P_w,
                                        boost::optional<gtsam::Matrix&> H1 = boost::none,
                                        boost::optional<gtsam::Matrix&> H2 = boost::none) const override;

private:
    /// @brief measurement parking-spot vertex in body frame
    gtsam::Point3 parking_slot_vertex_measurement_;
};  // class ParkingSlotVertexFactor
typedef ParkingSlotVertexFactor::Ptr ParkingSlotVertexFactorPtr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief point only parking slot vertex factor
 * @details error = Inverse(T_wb) * P_w - P_b
 *                  P_b represents parking-spot vertex in body coordinate, observation,
 *                  P_w represents parking-spot vertex in world coordinate, first estimated value,
 *                  T_wb represents pose from body to world coordinate, observation.
 */
class PointOnlySlotVertexFactor : public gtsam::NoiseModelFactor1<gtsam::Point3>
{
public:
    /**
     * @brief smart pointer
     */
    typedef boost::shared_ptr<PointOnlySlotVertexFactor>       Ptr;
    typedef boost::shared_ptr<const PointOnlySlotVertexFactor> ConstPtr;
    typedef gtsam::NoiseModelFactor1<gtsam::Point3>            Base;

    /**
     * @brief Construct a new ParkingSlotFactor object
     *
     * @param pose_key key of estimated pose, T_wb1
     * @param vertex_key key of estimated vertex in world coordinate, P_w
     * @param measurement measurement (vertex) in body coordinate, P_b1
     * @param model noise model
     */
    PointOnlySlotVertexFactor(const gtsam::Key& vertex_key, const gtsam::Pose3& measurement_wTb,
                              const gtsam::Point3& measurement_pb, const gtsam::SharedNoiseModel& model);

    /**
     * @brief deconstructor
     */
    virtual ~PointOnlySlotVertexFactor()
    {
    }

    /**
     * @brief Get the parking-spot vertex measurement object
     *
     * @return const gtsam::Point3
     */
    const gtsam::Point3& GetParkingSlotVertexMeasurement() const;

    /**
     * @brief error function
     *
     * @param P_w the parking-spot vertex in world frame
     * @param H_vertex the optional Jacobian matrix for parking-spot vertex in the world
     * @return gtsam::Vector
     */
    virtual gtsam::Vector evaluateError(const gtsam::Point3&            P_w,
                                        boost::optional<gtsam::Matrix&> H_vertex = boost::none) const override;

private:
    /// @brief measurement parking-spot vertex in body frame
    gtsam::Pose3  measurement_wTb_;
    gtsam::Point3 measurement_Pb_;
};  // class PointOnlySlotVertexFactor

typedef PointOnlySlotVertexFactor::Ptr PointOnlySlotVertexFactorPtr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief pose only parking slot vertex factor
 * @details error = Inverse(T_wb) * P_w - P_b
 *                  P_b represents parking-spot vertex in body coordinate, observation,
 *                  P_w represents parking-spot vertex in world coordinate, first estimated value,
 *                  T_wb represents pose from body to world coordinate, observation.
 */
class PoseOnlySlotVertexFactor : public gtsam::NoiseModelFactor1<gtsam::Pose3>
{
public:
    /**
     * @brief smart pointer
     */
    typedef boost::shared_ptr<PoseOnlySlotVertexFactor>       Ptr;
    typedef boost::shared_ptr<const PoseOnlySlotVertexFactor> ConstPtr;
    typedef gtsam::NoiseModelFactor1<gtsam::Pose3>            Base;

    /**
     * @brief Construct a new ParkingSlotFactor object
     *
     * @param pose_key key of estimated pose, T_wb1
     * @param measurement_Pw measurement (vertex) in world coordinate, P_w
     * @param measurement_Pb measurement (vertex) in body coordinate, P_b
     * @param model noise model
     */
    PoseOnlySlotVertexFactor(const gtsam::Key& pose_key, const gtsam::Point3& measurement_Pw,
                             const gtsam::Point3& measurement_Pb, const gtsam::SharedNoiseModel& model);

    /**
     * @brief deconstructor
     */
    virtual ~PoseOnlySlotVertexFactor()
    {
    }

    /**
     * @brief Get the parking-spot vertex measurement object
     *
     * @return a pair of vertices are in the world frame and body frame
     */
    const std::pair<gtsam::Point3, gtsam::Point3> GetParkingSlotVertexMeasurement() const;

    /**
     * @brief error function
     *
     * @param wTb body pose in world frame
     * @param H_pose the optional Jacobian matrix for pose from body into world
     * @return gtsam::Vector
     */
    virtual gtsam::Vector evaluateError(const gtsam::Pose3&                   wTb,
                                        const boost::optional<gtsam::Matrix&> H_pose = boost::none) const override;

private:
    /// @brief measurement parking-spot vertex in world frame
    gtsam::Point3 measurement_Pw_;
    /// @brief measurement parking-spot vertex in body frame
    gtsam::Point3 measurement_Pb_;
};  // class PointOnlySlotVertexFactor

typedef PoseOnlySlotVertexFactor::Ptr PoseOnlySlotVertexFactorPtr;

}  // namespace semantic
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_VERTEX_FACTOR_H_