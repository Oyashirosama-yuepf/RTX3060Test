/*!
 * \brief test_semantic_mapping.cpp
 * \author Yanwei. Du
 * \date April-08-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>
#include <holo/localization/vision/vslam/mapping/mapping.h>

#include <random>

#include "measurements_generator.h"

using namespace holo::localization::vision::vslam;
using namespace holo::localization;

////////////////////////////////////////////////////////////////////////////////
TEST(SemanticMapping, Normal)
{
    // create mg, providing parking slots
    internal::MeasurementsGenerator mg(10.0, 5.0, 0.15, 0.1, 0.1);

    // create data association
    semantic::DataAssociation::Parameters parameters;
    parameters.birdview_parameters =
        internal::MeasurementsGenerator::GenerateBirdviewParameters(mg.GetSensingDistance(), mg.GetVehicleHeight());
    parameters.show_tracking = false;
    parameters.show_matching = true;
    parameters.enable_step   = false;
    semantic::DataAssociation da(parameters);

    // create graph builder
    GraphBuilder builder(internal::MeasurementsGenerator::GenerateGraphBuilderParameters(), nullptr);

    // create smoother
    gtsam::ISAM2 isam;

    // estimated values
    Values estimated;

    // construct ground truth
    internal::GroundTruth gt;

    std::vector<Pose3>           input_poses;
    std::vector<ParkingSlotType> input_parkingslots;
    std::unordered_set<uint64_t> observed_parkingslots_ids;

    // loop to add measurements
    const Scalar dt  = 0.1;  // camera frequency
    const size_t num = size_t(mg.GetDuration() / dt);
    for (size_t i = 0u; i < num; i++)
    {
        const Scalar right = i * dt;
        const Scalar left  = (i == 0) ? right : right - dt;

        // create factor measurements (imu, wheel, predicted values)
        auto fm = mg.GetFactorMeasurements(left, right, i);
        {
            // get semantic measurements (parking slot frame)
            const Pose3                gt_wTb             = mg.GetPose(right);
            const ParkingSlotFrameType parking_slot_frame = mg.GetDisturbedParkingSlotFrame(right, gt_wTb);

            // do tracking to construct semantic state
            // @todo do not disturbe the first pose
            const Pose3 disturbed_wTb = mg.GetDisturbedPose(right);
            fm.semantic_state         = da.Run(parking_slot_frame, disturbed_wTb, i);
            fm.predicted_values.update(X(i), HoloGtsam::Convert(disturbed_wTb));

            // save ground truth for evaluation
            gt.multi_wTb.emplace_back(gt_wTb);
            for (const auto& track : fm.semantic_state.tracks)
            {
                gt.world_id_to_track_id[track.parking_slot.id] = track.id;
            }

            // save input data for comparision
            input_poses.emplace_back(disturbed_wTb);
            for (const auto& ps : parking_slot_frame)
            {
                if (observed_parkingslots_ids.count(ps.id))
                {
                    continue;
                }
                observed_parkingslots_ids.insert(ps.id);
                input_parkingslots.emplace_back(semantic::Utility::TransformParkingSlot(ps, disturbed_wTb));
            }
        }

        // build the problem
        GraphBuilder::Problem problem = (i == 0) ? (builder.Initialize(fm, i)) : (builder.Run(fm, {}, i));

        // problem.factor_graph.print();

        // update and optimize
        isam.update(problem.factor_graph, problem.values);
        estimated = isam.calculateEstimate();
    }

    // check result
    std::unordered_map<int64_t, ParkingSlotType> gt_indexed_parking_slots;
    for (const auto& ps : mg.GetAllParkingSlots())
    {
        gt_indexed_parking_slots[ps.id] = ps;
    }

    // check pose
    std::vector<Pose3> est_poses;
    for (size_t i = 0; i < gt.multi_wTb.size(); ++i)
    {
        const Pose3& expected = gt.multi_wTb.at(i);
        const Pose3  actual   = HoloGtsam::Convert(estimated.at<gtsam::Pose3>(X(i)));
        est_poses.emplace_back(actual);
        LOG(INFO) << "expected = " << expected.GetTranslation() << ", actual = " << actual.GetTranslation();
    }

    // check parkingslots
    std::vector<ParkingSlotType> est_parkingslots;
    for (const auto& v : gt.world_id_to_track_id)
    {
        est_parkingslots.emplace_back(gt_indexed_parking_slots[v.first]);
        const std::vector<Point3> expected = semantic::Utility::ConvertToVector(gt_indexed_parking_slots[v.first]);

        for (size_t i = 0u; i < expected.size(); ++i)
        {
            uint64_t id = Utility::HashId(v.second, i);
            if (!estimated.exists(S(id)))
            {
                throw std::runtime_error("no parking slot is optimized");
            }

            const Point3 actual = HoloGtsam::Convert(estimated.at<gtsam::Point3>(S(id)));

            if (i < 4)
            {
                est_parkingslots.back().vertices[i] = actual;
            }
            else if (i == 4)
            {
                est_parkingslots.back().center_vertex = actual;
            }

            LOG(INFO) << "parking slot world id = " << v.first << ", track id = " << v.second << ", vertex id = " << i;

            LOG(INFO) << "expected = " << expected[i] << ", actual = " << actual;
        }
    }

    // save for visualization
    mg.Save(gt.multi_wTb, mg.GetAllParkingSlots(), "./gt");
    mg.Save(est_poses, est_parkingslots, "./est");
    mg.Save(input_poses, input_parkingslots, "./input");
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}