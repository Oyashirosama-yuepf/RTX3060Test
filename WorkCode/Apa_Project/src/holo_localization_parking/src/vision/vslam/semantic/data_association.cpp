/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file data_association.cpp
 * @brief this file defines data association for semantic slam
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @author Changxi Cheng (chengchangxi@holomatic.com)
 * @date 2021-02-25
 */

#include <holo/localization/vision/vslam/semantic/data_association.h>

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
int64_t ParkingSlotTrack::next_id = 0;  ///< define track next id
int64_t Plane::next_id            = 0;  ///< define plane next id

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DataAssociation::Parameters DataAssociation::Parameters::GenerateExample()
{
    Parameters parameters;
    parameters.plane_distance_threshold = 3.0;
    parameters.birdview_parameters      = BirdviewParameters::GenerateExample();
    parameters.show_tracking            = false;
    parameters.show_matching            = false;
    parameters.enable_step              = false;
    return parameters;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DataAssociation::Parameters DataAssociation::Parameters::LoadFromYaml(const yaml::Node& node)
{
    Parameters parameters;
    parameters.plane_distance_threshold = node["plane_distance_threshold"].as<Scalar>(3.0);
    parameters.avm_visible_range        = node["avm_visible_range"].as<Scalar>(12.0);
    parameters.avm_image_width          = node["avm_image_width"].as<Scalar>(640.0);
    parameters.avm_image_height         = node["avm_image_height"].as<Scalar>(640.0);
    parameters.birdview_parameters      = BirdviewParameters::LoadFromYaml(node["birdview_parameters"]);
    parameters.show_tracking            = node["show_tracking"].as<bool_t>(false);
    parameters.show_matching            = node["show_matching"].as<bool_t>(false);
    parameters.enable_step              = node["enable_step"].as<bool_t>(false);
    return parameters;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DataAssociation::DataAssociation(const Parameters& parameters)
  : parameters_(parameters)
  , visualizer_(Visualizer::Parameters(parameters_.birdview_parameters, parameters_.enable_step))
  , associator_(new HungarianAssociator<DistanceMetric>())
{
    if (parameters_.show_matching)
    {
        associator_->SetVisualizationCallback(std::bind(&Visualizer::ShowMatching, &visualizer_, std::placeholders::_1,
                                                        std::placeholders::_2, std::placeholders::_3,
                                                        std::placeholders::_4));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DataAssociation::Run(State& state, const ParkingSlotFrameType& parking_slot_frame, const Pose3& wTb,
                          int64_t frame_id)
{
    // convert parking slot from image plane to body coordinate
    const ParkingSlotFrameType parking_slot_frame_in_body = convertToBody(parking_slot_frame);

    // associate plane
    associatePlane(state, parking_slot_frame_in_body, wTb);

    // associate tracks
    associateTracks(state, parking_slot_frame_in_body, wTb, frame_id, state.current_plane_id);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t DataAssociation::isParkingSlotInAVM(const holo::common::ParkingSlotd& parking_slot) const
{
    if (parking_slot.vertices[0u].GetX() < 0 || parking_slot.vertices[0u].GetY() < 0 ||
        parking_slot.vertices[1u].GetX() < 0 || parking_slot.vertices[1u].GetY() < 0 ||
        parking_slot.vertices[0u].GetX() > parameters_.avm_image_width ||
        parking_slot.vertices[0u].GetY() > parameters_.avm_image_height ||
        parking_slot.vertices[1u].GetX() > parameters_.avm_image_width ||
        parking_slot.vertices[1u].GetY() > parameters_.avm_image_height)
    {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotFrameType DataAssociation::convertToBody(const ParkingSlotFrameType& in) const
{
    if (in.GetCoordinate() == Coordinate::BODY)
    {
        return in;
    }

    ParkingSlotFrameType out(in);
    out.SetCoordinate(Coordinate::BODY);

    auto iter = out.begin();
    while (iter != out.end())
    {
        if (!iter->is_valid)
        {
            iter++;
            continue;
        }

        if (!isParkingSlotInAVM(*iter))
        {
            iter = out.erase(iter);
            continue;
        }

        // width and height
        iter->width  = parameters_.birdview_parameters.pixel_per_meter * iter->width;
        iter->height = parameters_.birdview_parameters.pixel_per_meter * iter->height;

        // @todo need to figure out what does the angle mean???
        // @note negative(-) transforms the angle from left-hand coordinate to right-hand coordinate
        iter->angle = (parameters_.birdview_parameters.bEg.GetRotation() * Rot3::Rz(-iter->angle)).YPR()(0u);

        // front vertices
        iter->vertices[0u] = parameters_.birdview_parameters.convertToBody(iter->vertices[0u].GetPointXY());
        iter->vertices[1u] = parameters_.birdview_parameters.convertToBody(iter->vertices[1u].GetPointXY());

        // rear vertices
        if (iter->is_rear_vertex_available)
        {
            iter->vertices[2u] = parameters_.birdview_parameters.convertToBody(iter->vertices[2u].GetPointXY());
            iter->vertices[3u] = parameters_.birdview_parameters.convertToBody(iter->vertices[3u].GetPointXY());
        }

        // center vertex
        if (iter->is_center_vertex_available)
        {
            iter->center_vertex = parameters_.birdview_parameters.convertToBody(iter->center_vertex.GetPointXY());
        }

        // stopper vertices
        if (iter->is_stopper_available)
        {
            iter->stopper_vertices[0u] =
                parameters_.birdview_parameters.convertToBody(iter->stopper_vertices[0u].GetPointXY());
            iter->stopper_vertices[1u] =
                parameters_.birdview_parameters.convertToBody(iter->stopper_vertices[1u].GetPointXY());
        }
        iter++;
    }

    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<gtsam::OrientedPlane3> DataAssociation::estimatePlane(const ParkingSlotFrameType& parking_slot_frame,
                                                                      const Pose3&                wTb) const
{
    std::vector<Point3> points;
    points.reserve(7 * parking_slot_frame.size());  // a single slot can have as many as 7 vertices
    for (const auto& parking_slot : parking_slot_frame)
    {
        const std::vector<Point3> result = Utility::ConvertToVector(parking_slot);
        points.insert(points.end(), result.begin(), result.end());
    }

    // condition check
    if (points.size() < 3u)
    {
        return boost::none;
    }

    // real math starts here
    gtsam::Matrix mat(points.size(), 3u);
    for (size_t i = 0u; i < points.size(); ++i)
    {
        mat(i, 0) = points.at(i).GetX();
        mat(i, 1) = points.at(i).GetY();
        mat(i, 2) = points.at(i).GetZ();
    }

    // de-mean
    const gtsam::Matrix13 mean = mat.colwise().mean();
    mat                        = mat.rowwise() - mean;
    gtsam::Matrix3 cov         = mat.transpose() * mat;

    // decompose covariance
    Eigen::SelfAdjointEigenSolver<gtsam::Matrix3> es(cov);

    // condition check
    const gtsam::Vector3 eigenvalues = es.eigenvalues();  // ascending order
    if (eigenvalues(0) / eigenvalues(1) > 0.1)
    {
        return boost::none;
    }
    // LOG(INFO) << "eigen values = " << es.eigenvalues().transpose();

    const gtsam::Vector3 n = es.eigenvectors().col(0);
    const Scalar         d = n.dot(mean);

    // LOG(INFO) << "normal = " << n.transpose() << ", d = " << d;

    // return plane in navigation frame
    return gtsam::OrientedPlane3(n(0), n(1), n(2), d).transform(HoloGtsam::Convert(wTb));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DataAssociation::associatePlane(State& state, const ParkingSlotFrameType& parking_slot_frame,
                                     const Pose3& wTb) const
{
    bool is_new_plane = true;

    // check if current vehicle lie on a new plane
    for (const auto& iter : state.plane_id_to_plane)
    {
        const auto& plane   = iter.second;
        const auto  delta_z = std::fabs((plane.reference_pose.Inverse() * wTb).GetZ());

        if (delta_z < parameters_.plane_distance_threshold)
        {
            is_new_plane           = false;
            state.current_plane_id = iter.first;
            break;
        }
    }

    if (!is_new_plane)
    {
        return;
    }

    state.current_plane_id                                 = -1;
    boost::optional<gtsam::OrientedPlane3> estimated_plane = estimatePlane(parking_slot_frame, wTb);

    if (!estimated_plane)
    {
        return;
    }

    Plane new_plane = Plane::Create(*estimated_plane, wTb);
    state.plane_id_to_plane.emplace(new_plane.id, new_plane);
    state.current_plane_id = new_plane.id;

    LOG(INFO) << "DataAssociation --- create a new plane. plane id is: " << new_plane.id << "\n";
    new_plane.data.print("new estimated plane");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DataAssociation::associateTracks(State& state, const ParkingSlotFrameType& parking_slot_frame, const Pose3& wTb,
                                      int64_t frame_id, int64_t plane_id) const
{
    const auto& last_tracks = state.tracks;
    // check if initialized
    if (state.tracks.empty())
    {
        for (const auto& parking_slot : parking_slot_frame)
        {
            if (!parking_slot.is_valid)
            {
                continue;
            }
            state.tracks.emplace_back(
                ParkingSlotTrack::Create(parking_slot_frame.GetTimestamp(), frame_id, plane_id, parking_slot));
        }
    }
    else
    {
        // construct left
        std::vector<ParkingSlotType> left;
        for (const auto& track : state.tracks)
        {
            left.emplace_back(track.optimized_parking_slot);
        }

        // construct right
        std::vector<ParkingSlotType> right;
        for (const auto& parking_slot : parking_slot_frame)
        {
            if (!parking_slot.is_valid)
            {
                continue;
            }
            right.emplace_back(parking_slot);
        }

        // do real association
        std::vector<int32_t> result;
        if (!right.empty() && !left.empty())
        {
            // result has the same size as left
            result = associator_->Run(left, wTb.Inverse(), right);
        }

        // update tracks
        std::vector<int32_t> unmatched(right.size(), 1);
        for (size_t i = 0u; i < result.size(); ++i)
        {
            if (result.at(i) >= 0)  // tracked track
            {
                auto& track     = state.tracks[i];
                track.timestamp = parking_slot_frame.GetTimestamp();
                track.frame_id  = frame_id;
                track.plane_id  = plane_id;
                track.measurements.push_back(
                    std::make_pair(frame_id, std::make_pair(track.timestamp, right.at(result.at(i)))));
                unmatched.at(result.at(i)) = 0;

                // track state transition
                if (track.state == ParkingSlotTrack::State::CANDIDATE)
                {
                    track.state = ParkingSlotTrack::State::FRESH;
                }
            }
        }

        // add new track
        for (size_t i = 0u; i < unmatched.size(); ++i)
        {
            if (unmatched.at(i))
            {
                state.tracks.emplace_back(
                    ParkingSlotTrack::Create(parking_slot_frame.GetTimestamp(), frame_id, plane_id, right.at(i)));
            }
        }
    }
    if (parameters_.show_tracking)
    {
        visualizer_.ShowTracking(last_tracks, state.tracks, frame_id, plane_id);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SlotMapFactorMeasurement DataAssociation::RunParkingSlotGlobalMatching(const SlotMapPtr&           slot_map,
                                                                       const ParkingSlotFrameType& parking_slot_frame,
                                                                       const Pose3& wTb, int64_t frame_id)
{
    const ParkingSlotFrameType parking_slot_frame_in_body = convertToBody(parking_slot_frame);

    // Prepare data for the Hungarian algorithm
    std::vector<ParkingSlotType> left;
    for (const auto& parking_slot : *slot_map)
    {
        left.emplace_back(*parking_slot);
    }

    std::vector<ParkingSlotType> right;
    for (const auto& parking_slot : parking_slot_frame_in_body)
    {
        if (!parking_slot.is_valid)
        {
            continue;
        }
        right.emplace_back(parking_slot);
    }

    // do real association
    std::vector<int32_t> hungarian_result;
    if (!right.empty() && !left.empty())
    {
        // result has the same size as left
        hungarian_result = associator_->Run(left, wTb.Inverse(), right);
    }

    std::vector<SlotMapAssociationResult> measurements;
    for (size_t i = 0u; i < hungarian_result.size(); ++i)
    {
        if (hungarian_result.at(i) >= 0)
        {
            SlotMapAssociationResult matching_result;
            matching_result.train_slot = *(slot_map->at(i));
            matching_result.query_slot = parking_slot_frame_in_body.at(hungarian_result.at(i));
            measurements.push_back(matching_result);
        }
    }

    return SlotMapFactorMeasurement(frame_id, measurements);
}

}  // namespace semantic

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo
