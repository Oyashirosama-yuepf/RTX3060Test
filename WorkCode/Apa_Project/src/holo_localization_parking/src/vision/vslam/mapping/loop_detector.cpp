/*!
 * \brief loop detector class implementation file in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date Mar-02-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/mapping/loop_detector.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
#ifdef HOLO_LOOP_WITH_NETVLAD
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LoopDetector::Parameters LoopDetector::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // netvlad feature extractor parameters
    const holo::yaml::Node          netvlad_node   = node["netvlad_params"];
    const deep::NetVlad::Parameters netvlad_params = deep::NetVlad::Parameters::LoadFromYaml(netvlad_node);

    const auto loop_detection_method = node["loop_detection_method"].as<std::string>("byPose");
    return Parameters(netvlad_params, loop_detection_method);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LoopDetector::Parameters LoopDetector::Parameters::Example()
{
    // create netvlad_params
    const auto        netvlad_params        = deep::NetVlad::Parameters::Example();
    const std::string loop_detection_method = "byPose";

    return Parameters(netvlad_params, loop_detection_method);
}
#else
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LoopDetector::Parameters LoopDetector::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    const auto loop_detection_method = node["loop_detection_method"].as<std::string>("byPose");
    return Parameters(loop_detection_method);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LoopDetector::Parameters LoopDetector::Parameters::Example()
{
    const std::string loop_detection_method = "byPose";
    return Parameters(loop_detection_method);
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LoopDetector::LoopDetector(const Parameters& parameters, const FramesDatabase& frames_database)
  : parameters_(parameters), frames_database_(frames_database)
{
#ifdef HOLO_LOOP_WITH_NETVLAD
    // create netvlad database
    if (parameters_.loop_detection_method == "byNetVlad")
    {
        // init netvlad feature extractor
        const std::string& deeplearn_framework = parameters.netvlad_params.framework;

        if (deeplearn_framework == "pytorch")
        {
            netvlad_extractor_.reset(new deep::PTNetVlad(parameters.netvlad_params));
        }
        else
        {
            LOG(ERROR) << "GlobalOptimizer --- invalid deep framework: " << deeplearn_framework;
            throw std::runtime_error("GlobalOptimizer --- invalid deep framework.\n");
        }

        LOG(INFO) << "LoopDetector --- create netvlad database, this would take a while ...";
        CreateNetvladDatabase(frames_database);
        ImageFeatureMatPreprocess(netvlad_database_, 1).copyTo(netvlad_database_expand_);
        LOG(INFO) << "LoopDetector --- create netvlad database done.";
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LoopDetector::CandidatesLoop LoopDetector::Run(const Frame& query_frame, uint16_t query_camera_id,
                                               uint32_t query_number) const
{
    if (parameters_.loop_detection_method == "byPose")
    {
        return QueryCandidateByPose(query_frame, query_camera_id, query_number);
    }
#ifdef HOLO_LOOP_WITH_NETVLAD
    else if (parameters_.loop_detection_method == "byNetVlad")
    {
        return QueryCandidateByNetvlad(query_frame, query_camera_id, query_number);
    }
#endif
    else
    {
        LOG(ERROR) << "LoopDetector --- unsupported loop detection method: " << parameters_.loop_detection_method
                   << "\n";
        throw std::runtime_error("LoopDetector --- unsupported loop detection method.");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LoopDetector::CandidatesLoop LoopDetector::QueryCandidateByPose(const Frame& query_frame, uint16_t query_camera_id,
                                                                uint32_t query_number) const
{
    // check valid of query data
    if (query_frame.multi_camera_data.size() <= query_camera_id)
    {
        LOG(ERROR) << "LoopDetector --- QueryCandidateByPose: invalid input camera id. " << query_camera_id << "\n";
        throw std::runtime_error("LoopDetector --- QueryCandidateByPose: invalid input camera id.");
    }

    CandidatesLoop candidates;
    candidates.query_frame = std::make_pair(query_frame.frame_id, query_camera_id);

    // retrieve query pose
    const auto& query_pose = query_frame.multi_camera_data.at(query_camera_id).pose;

    // loop all database
    for (const auto& indexed_train_frame : frames_database_.GetAllFrames())
    {
        if (indexed_train_frame.second.frame_id == query_frame.frame_id)
        {
            continue;
        }

        // retrieve train pose
        const auto& train_pose = indexed_train_frame.second.multi_camera_data.at(query_camera_id).pose;

        // compute delta pose
        const Pose3 delta_pose = query_pose.Inverse() * train_pose;
        Scalar      t          = delta_pose.GetTranslation().ToVector().GetNorm();
        Scalar      angle      = delta_pose.GetRotation().ComputeAngle();

        if (t > 10.0 || angle > 15)
        {
            continue;
        }

        candidates.train_frames.push_back(std::make_pair(indexed_train_frame.second.frame_id, query_camera_id));
        candidates.scores.push_back(t);

        if (candidates.train_frames.size() >= query_number)
        {
            break;
        }
    }

    return candidates;
}

#ifdef HOLO_LOOP_WITH_NETVLAD
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LoopDetector::CandidatesLoop LoopDetector::QueryCandidateByNetvlad(const Frame& query_frame, uint16_t query_camera_id,
                                                                   uint32_t query_number) const
{
    CandidatesLoop candidates;
    candidates.query_frame = std::make_pair(query_frame.frame_id, query_camera_id);

    const auto& image_name = query_frame.multi_camera_data.at(query_camera_id).image_name;
    cv::Mat     image_rgb  = cv::imread(image_name, cv::IMREAD_COLOR);
    if (image_rgb.empty())
    {
        LOG(INFO) << "Read image failed in LoopDetector !!!";
    }
    // extract query image feature by netvlad
    auto image_feature = netvlad_extractor_->Run(image_rgb);

    // convert vector to cv::Mat
    cv::Mat query_image_feature_mat(1, image_feature.size(), cv::DataType<float>::type, image_feature.data());
    cv::Mat query_feature_mat_expand = ImageFeatureMatPreprocess(query_image_feature_mat, netvlad_database_.rows);

    // Calculate the distance mat
    cv::Mat dis_mat = (query_feature_mat_expand + netvlad_database_expand_.t()) -
                      2 * (query_image_feature_mat * netvlad_database_.t());

    cv::Mat_<float> dis_sortArr;
    cv::Mat_<int>   dis_sortIdxArr;
    cv::sort(dis_mat, dis_sortArr, CV_SORT_EVERY_ROW + CV_SORT_ASCENDING);
    cv::sortIdx(dis_mat, dis_sortIdxArr, CV_SORT_EVERY_ROW + CV_SORT_ASCENDING);

    for (uint32_t recall_num = 0; recall_num < query_number; recall_num++)
    {
        const auto train_frame_index = dis_sortIdxArr.at<int>(0, recall_num);
        candidates.train_frames.push_back(frame_id_and_camera_id_.at(train_frame_index));
        candidates.scores.push_back(dis_sortArr.at<int>(0, recall_num));
    }

    return candidates;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LoopDetector::CreateNetvladDatabase(const FramesDatabase& frames_database)
{
    uint64_t                        processed_frame = 0;
    std::vector<std::vector<float>> images_features;
    // create netvlad database
    for (const auto& indexed_frame : frames_database.GetAllFrames())
    {
        const auto& frame = indexed_frame.second;

        // loop all camera
        for (size_t camera_index = 0; camera_index < frame.multi_camera_data.size(); camera_index++)
        {
            const auto& image_name = frame.multi_camera_data.at(camera_index).image_name;
            cv::Mat     image_rgb  = cv::imread(image_name, cv::IMREAD_COLOR);
            if (image_rgb.empty())
            {
                continue;
            }

            const auto image_feature = netvlad_extractor_->Run(image_rgb);
            images_features.push_back(image_feature);
            frame_id_and_camera_id_.push_back(std::make_pair(frame.frame_id, camera_index));
        }
        processed_frame++;
        LOG_EVERY_N(INFO, 50) << "LoopDetector --- CreateNetvladDatabase is running, processed frames:"
                              << processed_frame << ", total frames: " << frames_database.Size()
                              << ", Progress: " << 100.0 * processed_frame / frames_database.Size() << " %.\n";
    }

    // covert vector of vector to cv::Mat
    // Create a new, _empty_ cv::Mat with the row size of image feature
    cv::Mat images_features_mat(0, images_features[0].size(), cv::DataType<float>::type);

    for (unsigned int i = 0; i < images_features.size(); ++i)
    {
        // Make a temporary cv::Mat row and add to NewSamples _without_ data copy
        cv::Mat Sample(1, images_features[0].size(), cv::DataType<float>::type, images_features[i].data());

        // The added element must be a Mat with the same number of columns as the container matrix:
        images_features_mat.push_back(Sample);
    }

    images_features_mat.copyTo(netvlad_database_);
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat LoopDetector::ImageFeatureMatPreprocess(const cv::Mat& image_feature_mat, uint64_t expand_cols) const
{
    cv::Mat mat_pow;
    cv::pow(image_feature_mat, 2, mat_pow);

    cv::Mat mat_row_sum;
    cv::reduce(mat_pow, mat_row_sum, 1, CV_REDUCE_SUM);

    cv::Mat mat_expand(image_feature_mat.rows, expand_cols, CV_32F);
    for (uint64_t i = 0; i < expand_cols; i++)
    {
        mat_row_sum.col(0).copyTo(mat_expand.col(i));
    }
    return mat_expand;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
