/*!
 * \brief test_data_association.cpp
 * \author Yanwei. Du
 * \date April-08-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>
#include <holo/localization/vision/vslam/semantic/data_association.h>

#include <random>

using namespace holo::localization::vision::vslam;
using namespace holo::localization;

namespace internal
{
/**
 * @brief create a series of parking slots a long x-axis, create a sin-wave vehicle path
 *
 * @details define the origin of navigation is attached to ground
 *
 *
 *     y
 *     ^  0   1  0   1  0   1     0   1  0   1  0   1
 *     |  |   |  |   |  |   | ... |   |  |   |  |   |
 *     |  |   |  |   |  |   |     |   |  |   |  |   |
 *     |  3---2  3---2  3---2     3---2  3---2  3---2
 *     o------------------------------------------------------>x
 *      --      --      --      --
 *     -  --  --  --  --  --  --  --       ---> moving forward
 *          --      --      --      --
 *     Vehicle motion: {x = vt, y = A + Bsin(wt), v = 5m/s, A = -1.0m, B = 1m, w = 3rad/s}
 */
class MeasurementsGenerator
{
public:
    struct VehicleTrajectory
    {
        Scalar vx       = 5.0;   // meter
        Scalar A        = -1.0;  // meter
        Scalar B        = 1.0;   // meter
        Scalar w        = 3.0;   // rad/s
        Scalar duration = 6.0;   // s

        Scalar GetX(const Scalar t) const
        {
            return vx * t;
        }

        Scalar GetY(const Scalar t) const
        {
            return A + B * sin(w * t);
        }

        Scalar GetYaw(const Scalar t) const
        {
            return atan2(B * cos(w * t), vx);
        }
    };

    /**
     * @brief Construct a new Measurements Generator object
     *
     */
    MeasurementsGenerator() : distribution_xyz_(0.0, 0.1), distribution_rpy_(0.0, 0.1)
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
        return vehicle_trajectory_.duration;
    }

    /**
     * @brief Get the Pose object
     *
     * @param t timestamp
     * @return Pose
     */
    Pose3 GetPose(const Scalar t) const
    {
        return Pose3(Rot3::Rz(vehicle_trajectory_.GetYaw(t)),
                     Point3(vehicle_trajectory_.GetX(t), vehicle_trajectory_.GetY(t), 0.0));
    }
    /**
     * @brief Get the disturbed Pose object
     *
     * @param t timestamp
     * @return Pose
     */
    Pose3 GetDisturbedPose(const Scalar t)
    {
        const Scalar roll  = distribution_rpy_(generator_);
        const Scalar pitch = distribution_rpy_(generator_);
        const Scalar yaw   = distribution_rpy_(generator_);

        const Scalar x = distribution_xyz_(generator_);
        const Scalar y = distribution_xyz_(generator_);
        const Scalar z = distribution_xyz_(generator_);

        return GetPose(t) * Pose3(Rot3::RzRyRx(roll, pitch, yaw), Point3(x, y, z));
    }

    /**
     * @brief Get the Parking Slot Frame Type object
     *
     * @param t timestamp
     * @param wTb body pose in navigation frame
     * @return ParkingSlotFrameType
     */
    ParkingSlotFrameType GetParkingSlotFrame(const Scalar t, const Pose3& wTb) const
    {
        const Scalar         threshold = 10.0;  // meters
        ParkingSlotFrameType frame(holo::common::Timestamp(t), holo::common::Coordinate::BODY);
        for (const auto& p : parking_slots_)
        {
            if (wTb.GetTranslation().Dist(p.center_vertex) < threshold)
            {
                frame.emplace_back(semantic::Utility::TransformParkingSlot(p, wTb.Inverse()));
            }
        }
        return frame;
    }

private:
    /**
     * @brief create a series of parking slots along
     *
     */
    void createParkingSlotsInNavigationFrame()
    {
        const Scalar intra_distance      = 3.5;  // meter
        const Scalar slot_width          = 3.0;  // meter
        const Scalar slot_height         = 5.0;  // meter
        const Scalar slot_center_y       = 3.0;  // meter
        const Scalar start_slot_center_x = 2.0;  // meter
        const Scalar vertex_ratio[2][4]  = {{-0.5, 0.5, -0.5, 0.5}, {0.5, 0.5, -0.5, -0.5}};
        const size_t num                 = 10u;
        for (size_t i = 0; i < num; i++)
        {
            ParkingSlotType p;
            p.id                         = i;
            p.is_valid                   = true;
            p.type                       = ParkingSlotType::Type::PERPENDICULAR;
            p.position                   = ParkingSlotType::Position::FRONT;
            p.status                     = ParkingSlotType::Status::FREE;
            p.width                      = slot_width;
            p.height                     = slot_height;
            p.angle                      = 0.0;
            p.is_center_vertex_available = true;
            {
                p.center_vertex.SetX(start_slot_center_x + i * intra_distance);
                p.center_vertex.SetY(slot_center_y);
            }
            p.is_rear_vertex_available = true;
            for (size_t j = 0; j < 4u; j++)
            {
                p.vertices[j].SetX(p.center_vertex.GetX() + slot_width * vertex_ratio[0][j]);
                p.vertices[j].SetY(p.center_vertex.GetY() + slot_height * vertex_ratio[1][j]);
            }
            p.is_stopper_available = false;

            parking_slots_.emplace_back(p);
        }
    }

    VehicleTrajectory                vehicle_trajectory_;
    std::vector<ParkingSlotType>     parking_slots_;
    std::default_random_engine       generator_;
    std::normal_distribution<Scalar> distribution_xyz_;
    std::normal_distribution<Scalar> distribution_rpy_;
};
}  // namespace internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(DataAssociation, Run)
{
    // create measurements generator
    internal::MeasurementsGenerator mg;

    // create data association
    semantic::DataAssociation da;

    // compute steps
    const size_t num = 5u;
    const Scalar dt  = mg.GetDuration() / num;
    for (size_t i = 0; i < num; i++)
    {
        const Scalar t = i * dt;
        // const Pose3                wTb   = mg.GetPose(t);
        const Pose3                wTb   = mg.GetDisturbedPose(t);
        const ParkingSlotFrameType frame = mg.GetParkingSlotFrame(t, wTb);
        std::cout << "time = " << t << "s, frame = " << i << ", gt parkingslot ids = [";
        for (const auto& p : frame)
        {
            std::cout << p.id << "\t";
        }
        std::cout << "]" << std::endl;

        // call method
        const semantic::DataAssociation::State state = da.Run(frame, wTb, i);

        // check result
        for (const auto& track : state.tracks)
        {
            std::cout << "gt = " << track.parking_slot.id << ", est = " << track.id << std::endl;
            ASSERT_EQ(track.parking_slot.id, track.id);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
