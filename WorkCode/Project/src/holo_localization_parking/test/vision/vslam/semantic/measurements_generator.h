/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file measurements_generator.h
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @author Changxi Cheng (chengchangxi@holomatic.com)
 * @brief
 * @version 0.1
 * @date 2021-04-29
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <holo/localization/vision/vslam/mapping/mapping.h>

using namespace holo::localization::vision::vslam;
using namespace holo::localization;

namespace internal
{
/**
 * @brief create a parkinglot on ground, and create a sin-wave vehicle path
 *
 * @details
 *   a. the origin of navigation frame is attached to ground
 *   b. the vehicle has the height of some value
 *
 *
 *                  (perpendicular parkingslots)
 *  y
 *  ^       2--3 2--3 2--3       2--3 2--3 2--3
 *  |      |    |    |    | ... |    |    |    |
 *  |      |    |    |    |     |    |    |    |
 *  |       1  0 1  0 1  0       1  0 1  0 1  0
 *  |
 *  |                     (vehicle motion sin-save path)
 *  | {x = vt, y = A + Bsin(wt), z = C;  v = 5m/s, A = 0.0m, B = 1m, w = 3rad/s, C = 0.4m}
 *  |          --      --      --      --
 *  o-------  -  --  --  --  --  --  --  --       ------------->x
 *  |              --      --      --      --
 *  |
 *  |                  (parallel parkingslots)
 *  |      0        1 0        1        0        1 0         1
 *  |     |          |          | ...  |          |           |
 *  |      3--------2 3--------2        3--------2 3---------2
 *
 */

/**
 * @brief define vehicle trajectory
 *
 */
class VehicleTrajectory
{
public:
    /**
     * @brief Get the Translation object
     *
     * @param t
     * @return Point3
     */
    Point3 GetTranslation(const Scalar t) const
    {
        Scalar x = vx_ * t;
        Scalar y = A_ + B_ * std::sin(w_ * t);
        Scalar z = C_;
        return Point3(x, y, z);
    }

    /**
     * @brief Get the Rotation object
     *
     * @param t
     * @return Rot3
     */
    Rot3 GetRotation(const Scalar t) const
    {
        return Rot3::Rz(GetYaw(t));
    }

    /**
     * @brief Get the Yaw object
     *
     * @param t
     * @return Scalar
     */
    Scalar GetYaw(const Scalar t) const
    {
        return std::atan2(B_ * std::cos(w_ * t), vx_);
    }

    /**
     * @brief Get the Velocity object
     *
     * @param t
     * @return Vector3
     */
    Vector3 GetVelocity(const Scalar t) const
    {
        return Vector3(vx_, w_ * B_ * std::cos(w_ * t), 0.0);
    }

    /**
     * @brief Get the Velocity In Body object
     *
     * @param t
     * @return Vector3
     */
    Vector3 GetVelocityInBody(const Scalar t) const
    {
        return GetRotation(t).Transpose() * GetVelocity(t);
    }

    /**
     * @brief Get the Acceleration In Body object
     *
     * @param t
     * @return Vector3
     */
    Vector3 GetAccelerationInBody(const Scalar t) const
    {
        return GetRotation(t).Transpose() * Vector3(0.0, -w_ * w_ * B_ * std::sin(w_ * t), 0.0);
    }

    /**
     * @brief Get the Gravity Compensated Acceleration In Body object
     *
     * @param t
     * @return Vector3
     */
    Vector3 GetGravityCompensatedAccelerationInBody(const Scalar t, const Scalar g = 9.81) const
    {
        return GetRotation(t).Transpose() * Vector3(0.0, -w_ * w_ * B_ * sin(w_ * t), g);
    }

    /**
     * @brief Get the Angular Velocity object
     *
     * @param t
     * @return Vector3
     */
    Vector3 GetAngularVelocity(const Scalar t) const
    {
        const Scalar dt       = 1e-2;
        const Scalar yaw_rate = (GetYaw(t + dt) - GetYaw(t - dt)) / (2.0 * dt);
        return Vector3(0.0, 0.0, yaw_rate);
    }

    /**
     * @brief Get the Vehicle Height object
     *
     * @return Scalar
     */
    Scalar GetVehicleHeight() const
    {
        return C_;
    }

private:
    Scalar vx_ = 5.0;  // meter
    Scalar A_  = 0.0;  // meter
    Scalar B_  = 1.0;  // meter
    Scalar C_  = 0.4;  // meter
    Scalar w_  = 3.0;  // rad/s
};

/**
 * @brief
 *
 */
class MeasurementsGenerator
{
public:
    /**
     * @brief Construct a new Measurements Generator object
     *
     * @param duration duration in seconds
     * @param sensing_distance distance in meters
     * @param xy_noise
     * @param z_noise
     * @param rpy_noise
     * @param vertex_noise
     */
    MeasurementsGenerator(const Scalar duration = 10.0, const Scalar sensing_distance = 10.0,
                          const Scalar xy_noise = 0.1, const Scalar z_noise = 0.1, const Scalar rpy_noise = 0.1,
                          const Scalar vertex_noise = 0.05)
      : duration_(duration)
      , vehicle_trajectory_()
      , sensing_distance_(sensing_distance)
      , parking_slots_()
      , distribution_xy_(0.0, xy_noise)
      , distribution_z_(0.0, z_noise)
      , distribution_rpy_(0.0, rpy_noise)
      , distribution_vertex_(0.0, vertex_noise)
    {
        createParkingSlotsInNavigationFrame();
    }

    /**
     * @brief Get the Duration object
     *
     * @return Scalar
     */
    Scalar GetDuration() const
    {
        return duration_;
    }

    /**
     * @brief Get the Vehicle Height object
     *
     * @return Scalar
     */
    Scalar GetVehicleHeight() const
    {
        return vehicle_trajectory_.GetVehicleHeight();
    }

    /**
     * @brief Get the Sensing Distance object
     *
     * @return Scalar
     */
    Scalar GetSensingDistance() const
    {
        return sensing_distance_;
    }

    /**
     * @brief Get the Pose object
     *
     * @param t timestamp
     * @return Pose
     */
    Pose3 GetPose(const Scalar t) const
    {
        return Pose3(vehicle_trajectory_.GetRotation(t), vehicle_trajectory_.GetTranslation(t));
    }

    /**
     * @brief Get the disturbed Pose object
     *
     * @param t timestamp
     * @return Pose
     */
    Pose3 GetDisturbedPose(const Scalar t)
    {
        const Scalar roll  = distribution_rpy_(noise_generator_);
        const Scalar pitch = distribution_rpy_(noise_generator_);
        const Scalar yaw   = distribution_rpy_(noise_generator_);

        const Scalar x = distribution_xy_(noise_generator_);
        const Scalar y = distribution_xy_(noise_generator_);
        const Scalar z = distribution_z_(noise_generator_);

        return GetPose(t) * Pose3(Rot3::RzRyRx(roll, pitch, yaw), Point3(x, y, z));
    }

    /**
     * @brief Get the Factor Measurements object\
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param frame index
     * @return FactorMeasurements
     */
    FactorMeasurements GetFactorMeasurements(const Scalar left, const Scalar right, const uint64_t index) const
    {
        FactorMeasurements fm;

        // get velocity measurement
        fm.vm.timestamp   = holo::common::Timestamp(right);
        fm.vm.velocity    = GetVelocityInBody(right);
        fm.vm.reliability = VelocityMeasurementReliability::HIGH;

        // get predicted values
        fm.predicted_values.insert(X(index), HoloGtsam::Convert(GetPose(right)));
        fm.predicted_values.insert(V(index), HoloGtsam::Convert(GetVelocity(right)));
        fm.predicted_values.insert(B(index), gtsam::imuBias::ConstantBias());

        // get pim
        static boost::shared_ptr<gtsam::PreintegrationParams> const pim_params =
            gtsam::PreintegrationParams::MakeSharedU();
        if (left < right)
        {
            fm.pim = CreatePIM(GetImus(left, right), pim_params, gtsam::imuBias::ConstantBias());
        }

        return fm;
    }

    /**
     * @brief Get the Parking Slot Frame Type object
     *
     * @param t timestamp
     * @param wTb pose of body in navigation frame
     * @param threshold distance threshold to create the observable measurements
     * @return ParkingSlotFrameType
     */
    ParkingSlotFrameType GetParkingSlotFrame(const Scalar t, const Pose3& wTb) const
    {
        ParkingSlotFrameType frame(holo::common::Timestamp(t), holo::common::Coordinate::BODY);
        for (const auto& p : parking_slots_)
        {
            if (wTb.GetTranslation().Dist(p.center_vertex) < sensing_distance_)
            {
                frame.emplace_back(semantic::Utility::TransformParkingSlot(p, wTb.Inverse()));
            }
        }
        return frame;
    }

    /**
     * @brief Get the Disturbed Parking Slot Frame object
     *
     * @param t
     * @param wTb
     * @return ParkingSlotFrameType
     */
    ParkingSlotFrameType GetDisturbedParkingSlotFrame(const Scalar t, const Pose3& wTb)
    {
        return DisturbParkingSlotFrame(GetParkingSlotFrame(t, wTb));
    }

    /**
     * @brief Get the Parking Slot Frames object
     *
     * @return const std::vector<ParkingSlotFrameType>&
     */
    const std::vector<ParkingSlotType>& GetAllParkingSlots() const
    {
        return parking_slots_;
    }

    /**
     * @brief
     *
     * @param poses
     * @param parking_slots
     * @param name
     */
    void Save(const std::vector<Pose3>& poses, const std::vector<ParkingSlotType>& parking_slots,
              const std::string& prefix = "./")
    {
        // save pose
        std::ofstream myfile(prefix + "_trajectory.txt");
        for (const auto& pose : poses)
        {
            const Point3& trans = pose.GetTranslation();
            myfile << trans.GetX() << " " << trans.GetY() << " " << trans.GetZ() << "\n";
        }
        myfile.close();

        //　save parkingslots
        myfile.open(prefix + "_parkinglot.txt");
        for (const auto& m : parking_slots)
        {
            myfile << m.id << " ";
            for (size_t i = 0; i < 4u; i++)
            {
                myfile << m.vertices[i].GetX() << " " << m.vertices[i].GetY() << " " << m.vertices[i].GetZ() << " ";
            }
            myfile << static_cast<uint32_t>(m.type) << "\n";
        }
        myfile.close();
    }

    /**
     * @brief
     *
     * @return GraphBuilder::Parameters
     */
    static GraphBuilder::Parameters GenerateGraphBuilderParameters()
    {
        PriorVehicleStateNoise prior_state_noise(Vector6::Constant(0.01), Vector3::Constant(0.01),
                                                 Vector6::Constant(0.01));

        Vector6 bias_between_sigma(0.01, 0.01, 0.01, 0.01, 0.01, 0.01);
        Vector3 velocity_factor_sigma(0.01, 0.01, 0.01);
        Vector3 velocity_factor_sigma_when_turns(0.1, 0.1, 0.1);
        Vector3 low_precision_velocity_factor_sigma(0.34, 034, 0.1);
        Vector2 pose_only_unit3_factor_sigma(0.1, 0.1);
        Vector6 zero_velocity_between_pose_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
        Vector6 gt_pose_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
        Scalar  pose_only_huber_loss(0.5);

        return GraphBuilder::Parameters(prior_state_noise, bias_between_sigma, velocity_factor_sigma,
                                        velocity_factor_sigma_when_turns, low_precision_velocity_factor_sigma,
                                        pose_only_unit3_factor_sigma, zero_velocity_between_pose_sigma, gt_pose_sigma,
                                        pose_only_huber_loss, true, false, true, false, false, false, false);
    }

    /**
     * @brief
     *
     * @return semantic::DataAssociation::BirdviewParameters
     */
    static semantic::BirdviewParameters GenerateBirdviewParameters(const Scalar sensing_distance,
                                                                   const Scalar vehicle_height)
    {
        semantic::BirdviewParameters parameters;

        parameters.meter_per_pixel = 0.01;

        parameters.bEg =
            Pose3(Rot3::RzRyRx(M_PI, 0.0, -M_PI / 2.0), Point3(sensing_distance, sensing_distance, -vehicle_height));
        return parameters;
    }

private:
    /**
     * @brief create a series of parking slots along
     *
     */
    void createParkingSlotsInNavigationFrame()
    {
        const Scalar slot_width  = 2.5;  // meter
        const Scalar slot_height = 5.0;  // meter

        const Scalar length = vehicle_trajectory_.GetTranslation(duration_).GetX();
        parking_slots_.clear();
        parking_slots_ =
            createParkingSlots(length, 0u, slot_width / 2.0, 1.5 + slot_height / 2.0, slot_width, slot_height,
                               ParkingSlotType::Type::PERPENDICULAR, ParkingSlotType::Position::LEFT);
        auto more_slots =
            createParkingSlots(length, parking_slots_.size(), slot_height / 2.0, -1.5 - slot_width / 2.0, slot_height,
                               slot_width, ParkingSlotType::Type::PARALLEL, ParkingSlotType::Position::RIGHT);

        std::copy(more_slots.begin(), more_slots.end(), std::back_inserter(parking_slots_));
    }

    /**
     * @brief Create a Parking Slots object
     *
     * @param length
     * @param start_id
     * @param first_center_vertex_x
     * @param first_center_vertex_y
     * @param slot_width
     * @param slot_height
     * @param slot_type
     */
    std::vector<ParkingSlotType>
    createParkingSlots(const Scalar length, const size_t start_id, const Scalar first_center_vertex_x,
                       const Scalar first_center_vertex_y, const Scalar slot_width, const Scalar slot_height,
                       const ParkingSlotType::Type     slot_type,
                       const ParkingSlotType::Position slot_position = ParkingSlotType::Position::RIGHT) const
    {
        Scalar vertex_ratio[2][4] = {{-0.5, 0.5, 0.5, -0.5}, {0.5, 0.5, -0.5, -0.5}};
        Scalar sign               = slot_position == ParkingSlotType::Position::LEFT ? -1.0 : 1.0;

        const size_t num = size_t(length / slot_width);

        std::vector<ParkingSlotType> slots;
        for (size_t i = 0; i < num; i++)
        {
            ParkingSlotType p;
            p.id                         = start_id + i;
            p.is_valid                   = true;
            p.type                       = slot_type;
            p.position                   = slot_position;
            p.status                     = ParkingSlotType::Status::FREE;
            p.width                      = slot_width;
            p.height                     = slot_height;
            p.angle                      = 0.0;
            p.is_center_vertex_available = true;
            {
                p.center_vertex.SetX(first_center_vertex_x + i * slot_width);
                p.center_vertex.SetY(first_center_vertex_y);
            }
            p.is_rear_vertex_available = true;
            for (size_t j = 0; j < 4u; j++)
            {
                p.vertices[j].SetX(p.center_vertex.GetX() + slot_width * vertex_ratio[0][j] * sign);
                p.vertices[j].SetY(p.center_vertex.GetY() + slot_height * vertex_ratio[1][j] * sign);
            }
            p.is_stopper_available = false;

            slots.emplace_back(p);
        }
        return slots;
    }

    /**
     * @brief Get the Velocity object
     *
     * @param t
     * @return Vector3
     */
    Vector3 GetVelocity(const Scalar t) const
    {
        return vehicle_trajectory_.GetVelocity(t);
    }

    /**
     * @brief Get the Velocity In Body object
     *
     * @param t
     * @return Vector3
     */
    Vector3 GetVelocityInBody(const Scalar t) const
    {
        return vehicle_trajectory_.GetVelocityInBody(t);
    }

    /**
     * @brief
     *
     * @param multi_imu
     * @param pim_params
     * @param imu_bias
     * @return gtsam::PreintegratedImuMeasurements
     */
    gtsam::PreintegratedImuMeasurements CreatePIM(std::vector<Imu> const&                               multi_imu,
                                                  boost::shared_ptr<gtsam::PreintegrationParams> const& pim_params,
                                                  gtsam::imuBias::ConstantBias const&                   imu_bias) const
    {
        LOG_IF(FATAL, multi_imu.size() < 2u)
            << "CreatePIM --- Failed to create PIM due to no enought imu data!!! number of imu = " << multi_imu.size();

        gtsam::PreintegratedImuMeasurements pim(pim_params, imu_bias);
        for (uint16_t index = 1u; index < static_cast<uint16_t>(multi_imu.size()); index++)
        {
            Imu const&           lhs = multi_imu.at(index - 1u);
            Imu const&           rhs = multi_imu.at(index);
            gtsam::Vector3 const mid_omega(
                (lhs.GetAngularVelocity<gtsam::Vector3>() + rhs.GetAngularVelocity<gtsam::Vector3>()) * 0.5);
            gtsam::Vector3 const mid_acc(
                (lhs.GetLinearAcceleration<gtsam::Vector3>() + rhs.GetLinearAcceleration<gtsam::Vector3>()) * 0.5);
            Scalar const delta_t = rhs.GetTimestamp().ToSec() - lhs.GetTimestamp().ToSec();
            pim.integrateMeasurement(mid_acc, mid_omega, delta_t);
        }

        return pim;
    }

    /**
     * @brief Get the Imus object 100hz
     *
     * @param left
     * @param right
     * @return std::vector<Imu>
     */
    std::vector<Imu> GetImus(const Scalar left, const Scalar right) const
    {
        std::vector<Imu> imus;
        for (Scalar t = left; t <= right; t += 0.01)
        {
            Imu imu;
            imu.SetTimestamp(holo::common::Timestamp(t));
            imu.SetLinearAcceleration(vehicle_trajectory_.GetGravityCompensatedAccelerationInBody(t));
            imu.SetAngularVelocity(vehicle_trajectory_.GetAngularVelocity(t));
            imus.emplace_back(imu);
        }
        return imus;
    }

    /**
     * @brief
     *
     * @param in
     * @return ParkingSlotFrameType
     */
    ParkingSlotFrameType DisturbParkingSlotFrame(const ParkingSlotFrameType& in)
    {
        ParkingSlotFrameType out(in.GetTimestamp(), in.GetCoordinate());

        for (const auto& ps_in : in)
        {
            ParkingSlotType ps_out = ps_in;
            ps_out.vertices[0]     = DisturbVertex(ps_in.vertices[0]);
            ps_out.vertices[1]     = DisturbVertex(ps_in.vertices[1]);

            if (ps_in.is_rear_vertex_available)
            {
                ps_out.vertices[2] = DisturbVertex(ps_in.vertices[2]);
                ps_out.vertices[3] = DisturbVertex(ps_in.vertices[3]);
            }

            if (ps_in.is_center_vertex_available)
            {
                ps_out.center_vertex = DisturbVertex(ps_in.center_vertex);
            }

            if (ps_in.is_stopper_available)
            {
                ps_out.stopper_vertices[0] = DisturbVertex(ps_in.stopper_vertices[0]);
                ps_out.stopper_vertices[1] = DisturbVertex(ps_in.stopper_vertices[1]);
            }
            out.emplace_back(ps_out);
        }

        return out;
    }

    /**
     * @brief
     *
     * @param in
     * @return Point3
     */
    Point3 DisturbVertex(const Point3& in)
    {
        const Scalar x = distribution_vertex_(noise_generator_);
        const Scalar y = distribution_vertex_(noise_generator_);
        return in + Point3(x, y, 0.0);
    }

    Scalar                           duration_;
    VehicleTrajectory                vehicle_trajectory_;
    Scalar                           sensing_distance_;
    std::vector<ParkingSlotType>     parking_slots_;
    std::normal_distribution<Scalar> distribution_xy_;
    std::normal_distribution<Scalar> distribution_z_;
    std::normal_distribution<Scalar> distribution_rpy_;
    std::normal_distribution<Scalar> distribution_vertex_;
    std::default_random_engine       noise_generator_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct GroundTruth
{
    std::vector<Pose3>                   multi_wTb;
    std::unordered_map<int64_t, int64_t> world_id_to_track_id;
};

}  // namespace internal