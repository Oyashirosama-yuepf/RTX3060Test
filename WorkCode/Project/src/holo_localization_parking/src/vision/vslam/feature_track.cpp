/*!
 * \brief feature track class in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Feb-11-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/feature_track.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief initialize next_id_ of FeatureTrack
 */
uint64_t FeatureTrack::next_id_ = 0;

/**
 * @brief initialize feature_track_mutex_ of FeatureTrack
 */
std::mutex FeatureTrack::feature_track_mutex_;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const FeatureTrack::Parameters& FeatureTrack::Params() const
{
    return (*parameters_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CameraParameters::Ptr& FeatureTrack::CameraParams() const
{
    return camera_parameters_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint64_t FeatureTrack::Id() const
{
    return id_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::vector<FeatureTrack::Measurement>& FeatureTrack::Measurements() const
{
    return measurements_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FeatureTrack::State FeatureTrack::GetState() const
{
    return state_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const boost::optional<Landmark>& FeatureTrack::GetLandmark() const
{
    return landmark_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint64_t FeatureTrack::Length() const
{
    return measurements_.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SemanticLabel FeatureTrack::GetLabel() const
{
    std::map<SemanticLabel, uint64_t> category_to_count;
    for (const auto& measurement : measurements_)
    {
        const auto& camera_index_feature_map = measurement.second;

        for (const auto& camera_index_feature : camera_index_feature_map)
        {
            SemanticLabel feature_semantic_label = camera_index_feature.second.semantic_label;
            if (feature_semantic_label != SemanticLabel::UNKNOWN)
            {
                category_to_count[feature_semantic_label]++;
            }
        }
    }

    if (category_to_count.empty())
    {
        return SemanticLabel::UNKNOWN;
    }

    // select the best and better category for a feature track
    std::pair<SemanticLabel, uint64_t> best_category =
        std::make_pair(category_to_count.begin()->first, category_to_count.begin()->second);
    std::pair<SemanticLabel, uint64_t> better_category = best_category;

    for (const auto& item : category_to_count)
    {
        if (item.second > best_category.second)
        {
            better_category = best_category;
            best_category   = item;
        }
    }

    // assign the category to mappoint which satisfies the conditions
    // we only add the static and vehicle mappoint to map for localization
    if (((best_category.first == better_category.first) ||
         (best_category.first != better_category.first && best_category.second > 2 * better_category.second)))
    {
        return best_category.first;
    }
    return SemanticLabel::UNKNOWN;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const FeatureTrack::Measurement& FeatureTrack::Measurements(const uint64_t index) const
{
    assert(index < Length());
    return measurements_.at(index);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const FeatureTrack::Measurement& FeatureTrack::NewestMeasurement() const
{
    return measurements_.back();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const FeatureTrack::Measurement& FeatureTrack::OldestMeasurement() const
{
    return measurements_.front();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FeatureTrack FeatureTrack::CreateNewTrackByAddingNewestMeasurement(const uint64_t frame_id,
                                                                   const Feature& feature) const
{
    std::vector<Measurement> results(measurements_.begin(), measurements_.end());

    // check if this frame id is already exist in old measurements_.
    // this should happen if the feature track can be tracked by defferent camera at the same time in a multi camera
    // vslam system
    auto& newest_measurement = results.back();
    if (frame_id == newest_measurement.first)
    {
        newest_measurement.second.emplace(feature.camera_id, feature);
    }
    else
    {
        CameraIndexedFeature indexed_feature;
        indexed_feature.emplace(feature.camera_id, feature);
        Measurement m = std::make_pair(frame_id, indexed_feature);
        results.push_back(m);
    }

    return FeatureTrack(parameters_, camera_parameters_, id_, results, state_, landmark_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureTrack::AddNewestMeasurement(const uint64_t frame_id, const Feature& feature)
{
    // check if this frame id is already exist in old measurements_.
    // this should happen if the feature track can be tracked by defferent camera at the same time in a multi camera
    // vslam system
    auto& newest_measurement = measurements_.back();

    if (frame_id == newest_measurement.first)
    {
        newest_measurement.second.emplace(feature.camera_id, feature);
    }
    else
    {
        CameraIndexedFeature indexed_feature;
        indexed_feature.emplace(feature.camera_id, feature);
        Measurement m = std::make_pair(frame_id, indexed_feature);
        measurements_.push_back(m);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FeatureTrack FeatureTrack::CreateNewTrackByUpdatingState(const FeatureTrack::State             new_state,
                                                         const boost::optional<gtsam::Point3>& optional_point) const
{
    if (optional_point)
    {
        // create a landmark if landmark_ is invalid
        // else update landmark point
        if (!landmark_)
        {
            return FeatureTrack(parameters_, camera_parameters_, id_, measurements_, new_state,
                                Landmark(*optional_point));
        }
        else
        {
            return FeatureTrack(parameters_, camera_parameters_, id_, measurements_, new_state,
                                landmark_->UpdateLandmark(*optional_point));
        }
    }
    else if (new_state == FeatureTrack::State::FRESH)
    {
        throw std::runtime_error("FeatureTrack --- optional_point is "
                                 "false with state of FRESH");
    }

    return FeatureTrack(parameters_, camera_parameters_, id_, measurements_, new_state, landmark_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureTrack::UpdatingState(const State new_state, const boost::optional<gtsam::Point3>& optional_point)
{
    // update landmark if the input optional point is valid.
    if (optional_point)
    {
        // create a landmark if landmark_ is invalid
        // else update landmark point
        if (!landmark_)
        {
            landmark_ = Landmark(*optional_point);
        }
        else
        {
            landmark_ = landmark_->UpdateLandmark(*optional_point);
        }
    }
    else if (new_state == FeatureTrack::State::FRESH)
    {
        throw std::runtime_error("FeatureTrack --- optional_point is "
                                 "false with state of FRESH");
    }

    // update state
    state_ = new_state;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FeatureTrack FeatureTrack::CreateNewTrack(const Parameters::ConstPtr&  parameters,
                                          const CameraParameters::Ptr& camera_parameters,
                                          const Measurement&           measurement)
{
    std::unique_lock<std::mutex> lock(feature_track_mutex_);
    return FeatureTrack(parameters, camera_parameters, next_id_++, measurement);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::unordered_map<uint16_t, cv::Point2f> FeatureTrack::PredictNewPoints() const
{
    std::unordered_map<uint16_t, cv::Point2f> result;

    if (Length() == 1)
    {
        // only one measurement for this track, return the lastest point
        const auto& newest_indexed_features = NewestMeasurement().second;

        for (const auto& indexed_feature : newest_indexed_features)
        {
            result.emplace(indexed_feature.first, indexed_feature.second.image_point);
        }
    }
    else
    {
        // more than one measurement, predicte new point by flow trace
        // get the lastest two measurements with their camera index
        const auto& newest_indexed_feature        = NewestMeasurement().second;
        const auto& second_newest_indexed_feature = Measurements(Length() - 2).second;

        for (const auto& indexed_feature : newest_indexed_feature)
        {
            const auto& camera_index = indexed_feature.first;

            // check whether this track is also tracked by this camera in second newest measurement
            if (second_newest_indexed_feature.count(camera_index))
            {
                const auto flow_trace =
                    indexed_feature.second.image_point - second_newest_indexed_feature.at(camera_index).image_point;
                result.emplace(camera_index, indexed_feature.second.image_point + flow_trace);
            }
            else
            {
                // do NOT tracked by this camera in second newest measurement
                result.emplace(camera_index, indexed_feature.second.image_point);
            }
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Unit3FactorPtr> FeatureTrack::Unit3Factors(const Values& values,
                                                       const Scalar  minimum_measurement_distance_interval,
                                                       const Scalar  minimum_measurement_angle_interval) const
{
    std::vector<Unit3FactorPtr> factors;

    if (GetState() == FeatureTrack::State::LIVE)
    {
        factors = CreateUnit3Factor(Length() - 1);
    }
    else if (GetState() == FeatureTrack::State::FRESH)
    {
        boost::optional<Pose3> last_key_measurement_pose = boost::none;
        for (uint64_t i = 0; i < Length(); i++)
        {
            boost::optional<Pose3> current_measurement_pose = boost::none;
            const auto             frame_id                 = Measurements(i).first;
            if (values.exists(X(frame_id)))
            {
                current_measurement_pose =
                    HoloGtsam::Convert(values.at(X(Measurements().at(i).first)).cast<gtsam::Pose3>());
            }

            if (last_key_measurement_pose &&
                last_key_measurement_pose->GetTranslation().Dist(current_measurement_pose->GetTranslation()) <
                    minimum_measurement_distance_interval &&
                last_key_measurement_pose->GetRotation().ComputeAngle(current_measurement_pose->GetRotation()) <
                    minimum_measurement_angle_interval)
            {
                continue;
            }
            last_key_measurement_pose = current_measurement_pose;

            const auto sub_factors = CreateUnit3Factor(i);

            for (const auto& factor : sub_factors)
            {
                factors.emplace_back(factor);
            }
        }
    }

    // return projection factor
    return factors;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<EssentialMatrixFactorPtr> FeatureTrack::EssentialMatrixFactors(
    uint64_t current_frame_id, const Values& values, const Scalar minimum_measurement_distance_interval,
    const Scalar maximum_measurement_angle_interval) const
{
    std::vector<EssentialMatrixFactorPtr> result;
    if (Length() < 2)
    {
        return result;
    }
    FeatureTrack::Measurement current_measuremnt = NewestMeasurement();
    if (current_measuremnt.first != current_frame_id)
    {
        return result;
    }

    if (!values.exists(X(current_frame_id)))
    {
        return result;
    }

    result.reserve(Length());
    Pose3 curr_pose = HoloGtsam::Convert(values.at(X(current_frame_id)).cast<gtsam::Pose3>());

    for (int i = Length() - 2; i >= 0; --i)
    {
        FeatureTrack::Measurement last_measuremnt = Measurements(i);

        auto last_frame_id = last_measuremnt.first;
        if (!values.exists(X(last_frame_id)))
        {
            break;
        }

        Pose3 last_pose = HoloGtsam::Convert(values.at(X(last_frame_id)).cast<gtsam::Pose3>());

        if (last_pose.Dist(curr_pose) < minimum_measurement_distance_interval)
        {
            continue;
        }

        const auto lTc = last_pose.Inverse() * curr_pose;

        if (lTc.GetRotation().ComputeAngle() > maximum_measurement_angle_interval)
        {
            continue;
        }

        for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; ++camera_index)
        {
            if (camera_parameters_->intrinsics.at(camera_index)->GetModel() != Model::FISHEYE)
            {
                continue;
            }

            FisheyeIntrinsicType const* fisheye =
                dynamic_cast<FisheyeIntrinsicType const*>(camera_parameters_->intrinsics.at(camera_index).get());

            Scalar fx = fisheye->GetK()(0, 0);
            Scalar fy = fisheye->GetK()(1, 1);
            Scalar f  = 0.5 * (fx + fy);
            // convert sigma uv
            static const Scalar sigma_uv = camera_parameters_->sigma_uv_and_loss.at(camera_index).first / f;

            // create noise model
            static const gtsam::SharedNoiseModel noise_model(gtsam::noiseModel::Isotropic::Sigma(1, sigma_uv));

            // create huber loss
            static const Scalar huber_loss =
                camera_parameters_->sigma_uv_and_loss.at(camera_index).second / (f * sigma_uv);
            // create hub
            const auto huber = gtsam::noiseModel::Robust::Create(
                gtsam::noiseModel::mEstimator::Huber::Create(0.5 * huber_loss * huber_loss), noise_model);

            static const gtsam::Pose3 bTc = HoloGtsam::Convert(camera_parameters_->extrinsics.at(camera_index));

            const auto    p1 = last_measuremnt.second.at(camera_index).normalized_point;
            gtsam::Point3 gt_p1(p1.GetX(), p1.GetY(), p1.GetZ());
            const auto    p2 = current_measuremnt.second.at(camera_index).normalized_point;
            gtsam::Point3 gt_p2(p2.GetX(), p2.GetY(), p2.GetZ());

            result.emplace_back(boost::make_shared<EssentialMatrixFactor>(gt_p1, gt_p2, X(last_frame_id),
                                                                          X(current_frame_id), huber, bTc));
        }
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FeatureTrack::AddUnit3Factor(FactorGraph& graph, const uint64_t index) const
{
    // get this feature track's measurement at given index
    const auto&    m        = Measurements(index);
    const uint64_t frame_id = m.first;

    // get landmark id
    const uint64_t landmark_id = GetLandmark()->Id();

    // prepare result
    std::vector<Unit3FactorPtr> result;
    result.reserve(m.second.size());

    // create projection factor for each camera's measurement
    for (const auto& indexed_feature : m.second)
    {
        // get camera intrinsic and extrinsic
        const auto& camera_index = indexed_feature.first;
        const auto& intrinsic    = camera_parameters_->intrinsics.at(camera_index);
        const auto& T_bc         = camera_parameters_->extrinsics.at(camera_index);

        // get feature
        const auto& feature = indexed_feature.second;

        // get normarlized point
        const gtsam::Point3 point(feature.normalized_point.GetX(), feature.normalized_point.GetY(),
                                  feature.normalized_point.GetZ());

        // convert sigma uv
        static const Scalar sigma_uv = CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(
            intrinsic, camera_parameters_->sigma_uv_and_loss.at(camera_index).first);

        // create noise model
        static const gtsam::SharedNoiseModel noise_model(gtsam::noiseModel::Isotropic::Sigma(2, sigma_uv));

        // create huber loss
        static const Scalar huber_loss = CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(
                                             intrinsic, camera_parameters_->sigma_uv_and_loss.at(camera_index).second) /
                                         sigma_uv;
        const auto huber = gtsam::noiseModel::Robust::Create(
            gtsam::noiseModel::mEstimator::Huber::Create(0.5 * huber_loss * huber_loss), noise_model);

        graph.emplace_shared<Unit3Factor>(point, huber, X(frame_id), L(landmark_id), HoloGtsam::Convert(T_bc));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Unit3FactorPtr> FeatureTrack::CreateUnit3Factor(const uint64_t index) const
{
    // get this feature track's measurement at given index
    const auto&    m        = Measurements(index);
    const uint64_t frame_id = m.first;

    // get landmark id
    const uint64_t landmark_id = GetLandmark()->Id();

    // prepare result
    std::vector<Unit3FactorPtr> result;
    result.reserve(m.second.size());

    // create projection factor for each camera's measurement
    for (const auto& indexed_feature : m.second)
    {
        // get camera intrinsic and extrinsic
        const auto& camera_index = indexed_feature.first;
        const auto& intrinsic    = camera_parameters_->intrinsics.at(camera_index);
        const auto& T_bc         = camera_parameters_->extrinsics.at(camera_index);

        // get feature
        const auto& feature = indexed_feature.second;

        // get normarlized point
        const gtsam::Point3 point(feature.normalized_point.GetX(), feature.normalized_point.GetY(),
                                  feature.normalized_point.GetZ());

        // convert sigma uv
        static const Scalar sigma_uv = CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(
            intrinsic, camera_parameters_->sigma_uv_and_loss.at(camera_index).first);

        // create noise model
        static const gtsam::SharedNoiseModel noise_model(gtsam::noiseModel::Isotropic::Sigma(2, sigma_uv));

        // create huber loss
        static const Scalar huber_loss = CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(
                                             intrinsic, camera_parameters_->sigma_uv_and_loss.at(camera_index).second) /
                                         sigma_uv;
        const auto huber = gtsam::noiseModel::Robust::Create(
            gtsam::noiseModel::mEstimator::Huber::Create(0.5 * huber_loss * huber_loss), noise_model);

        result.emplace_back(
            boost::make_shared<Unit3Factor>(point, huber, X(frame_id), L(landmark_id), HoloGtsam::Convert(T_bc)));
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<Scalar> FeatureTrack::ComputeReprojectionError(const Values& values, int64_t measurement_index,
                                                               int16_t camera_index) const
{
    std::vector<Scalar>      measurement_errors;
    std::vector<Measurement> measurements;

    if (measurement_index >= (int64_t)Measurements().size())
    {
        std::runtime_error("FeatureTrack --- the input measurement index is out of range.");
    }
    if (camera_index >= camera_parameters_->camera_number)
    {
        std::runtime_error("FeatureTrack --- the input camera index is out of range.");
    }

    if (measurement_index < 0)
    {
        measurements = Measurements();
    }
    else
    {
        measurements.emplace_back(Measurements(measurement_index));
    }

    // get feature measurement
    // loop all measurement
    for (const auto& m : measurements)
    {
        // get newest frame id
        const uint64_t frame_id = m.first;

        // loop for all observed camera
        CameraIndexedFeature camera_index_feature_map;

        if (camera_index == -1)
        {
            camera_index_feature_map = m.second;
        }
        else if (m.second.count(camera_index))
        {
            camera_index_feature_map.emplace(std::make_pair(camera_index, m.second.at(camera_index)));
        }
        else
        {
            return boost::none;
        }

        for (const auto& camera_indexed_feature : camera_index_feature_map)
        {
            // get camera index and corresponding extrinsic
            const auto& camera_index = camera_indexed_feature.first;
            const auto& T_bc         = camera_parameters_->extrinsics.at(camera_index);
            const auto& feature      = camera_indexed_feature.second;

            // compute camera pose in world frame
            if (!values.exists(X(frame_id)))
            {
                LOG(ERROR) << "FeatureTrack --- frame id: " << frame_id << " not exist in values.\n";
                throw std::runtime_error("FeatureTrack --- frame id not exist in values.");
            }
            const gtsam::Pose3 T_wb = values.at(X(frame_id)).cast<gtsam::Pose3>();
            const gtsam::Pose3 T_wc = T_wb * holo::localization::HoloGtsam::Convert(T_bc);

            // compute landmark location
            if (!values.exists(L(GetLandmark()->Id())))
            {
                LOG(ERROR) << "FeatureTrack --- landmark id: " << GetLandmark()->Id() << " not exist in values.\n";
                throw std::runtime_error("FeatureTrack --- landmark id not exist in values.");
            }
            gtsam::Point3 landmark = values.at(L((GetLandmark())->Id())).cast<gtsam::Point3>();

            // transform landmark to camera coordinate
            const auto ptc = HoloGtsam::Convert(T_wc.inverse() * landmark);

            // check if behind camera
            const auto&  ray                                        = feature.normalized_point.ToVector();
            const Scalar angle_between_feature_ray_and_optical_axis = holo::Degree(std::acos(ray[2] / ray.GetNorm()));

            if (angle_between_feature_ray_and_optical_axis < 90.0 && ptc.GetZ() < 0)
            {
                // behind camera
                return boost::none;
            }

            // create two vectors
            const gtsam::Unit3 p = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(ptc));
            const gtsam::Unit3 q = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(feature.normalized_point));

            // compute error
            measurement_errors.emplace_back(p.errorVector(q).norm());
        }
    }

    return std::accumulate(measurement_errors.begin(), measurement_errors.end(), 0.0) / measurement_errors.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<Scalar> FeatureTrack::ComputePiexlReprojectionError(const Values& values, int64_t measurement_index,
                                                                    int16_t camera_index) const
{
    std::vector<Scalar>      measurement_errors;
    std::vector<Measurement> measurements;

    if (measurement_index >= (int64_t)Measurements().size())
    {
        std::runtime_error("FeatureTrack --- the input measurement index is out of range.");
    }
    if (camera_index >= camera_parameters_->camera_number)
    {
        std::runtime_error("FeatureTrack --- the input camera index is out of range.");
    }

    if (measurement_index < 0)
    {
        measurements = Measurements();
    }
    else
    {
        measurements.emplace_back(Measurements(measurement_index));
    }

    // get feature measurement
    // loop all measurement
    for (const auto& m : measurements)
    {
        // get newest frame id
        const uint64_t frame_id = m.first;

        // loop for all observed camera
        CameraIndexedFeature camera_index_feature_map;

        if (camera_index == -1)
        {
            camera_index_feature_map = m.second;
        }
        else if (m.second.count(camera_index))
        {
            camera_index_feature_map.emplace(std::make_pair(camera_index, m.second.at(camera_index)));
        }
        else
        {
            return boost::none;
        }

        for (const auto& camera_indexed_feature : camera_index_feature_map)
        {
            // get camera index and corresponding extrinsic and intrinsic
            const auto& camera_index     = camera_indexed_feature.first;
            const auto& T_bc             = camera_parameters_->extrinsics.at(camera_index);
            const auto& camera_intrinsic = camera_parameters_->intrinsics.at(camera_index);
            const auto& feature          = camera_indexed_feature.second;

            // compute camera pose in world frame
            if (!values.exists(X(frame_id)))
            {
                LOG(ERROR) << "FeatureTrack --- frame id: " << frame_id << " not exist in values.\n";
                throw std::runtime_error("FeatureTrack --- frame id not exist in values.");
            }
            const gtsam::Pose3 T_wb = values.at(X(frame_id)).cast<gtsam::Pose3>();
            const gtsam::Pose3 T_wc = T_wb * holo::localization::HoloGtsam::Convert(T_bc);

            // compute landmark location
            if (!values.exists(L(GetLandmark()->Id())))
            {
                LOG(ERROR) << "FeatureTrack --- landmark id: " << GetLandmark()->Id() << " not exist in values.\n";
                throw std::runtime_error("FeatureTrack --- landmark id not exist in values.");
            }
            gtsam::Point3 landmark = values.at(L((GetLandmark())->Id())).cast<gtsam::Point3>();

            // transform landmark to camera coordinate
            const auto ptc = HoloGtsam::Convert(T_wc.inverse() * landmark);

            // check if behind camera
            const auto&  ray                                        = feature.normalized_point.ToVector();
            const Scalar angle_between_feature_ray_and_optical_axis = holo::Degree(std::acos(ray[2] / ray.GetNorm()));

            if (angle_between_feature_ray_and_optical_axis < 90.0 && ptc.GetZ() < 0)
            {
                // behind camera
                return boost::none;
            }

            // compute the reprojection error of this camara measurment at image plane
            Point2d pt_projected;
            camera_intrinsic->Project(ptc, pt_projected);
            const auto& pt_measurment = feature.image_point;
            Vector2d    pt1           = pt_projected.ToVector();
            Vector2d    pt2(pt_measurment.x, pt_measurment.y);
            Vector2d    error(pt1 - pt2);

            measurement_errors.emplace_back(error.GetNorm());
        }
    }

    // compute the mean as the reprojection error result
    return std::accumulate(measurement_errors.begin(), measurement_errors.end(), 0.0) / measurement_errors.size();
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
