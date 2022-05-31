/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_global_relozalization.cpp
 * @brief Unit test for relocation in initializer
 * @author chenbin@holomatic.com
 * @date 2022-03-02
 */

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/localization/localization.h>
#include <holo/localization/vision/vslam/mapping/map_database_manager.h>
#include <holo/localization/vision/vslam/localization/relocalization.h>

using namespace holo;
using namespace holo::localization::vision::vslam;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief load features from file.
 * 
 * @details this function copy from MapDatabaseManager::LoadFeatures
 */
FrameIndexedFeatures LoadFeatures(const std::string& file_name)
{
    if (!boost::filesystem::exists(file_name))
    {
        LOG(ERROR) << "MapDatabaseManager --- features file: " << file_name << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    LOG(INFO) << "MapDatabaseManager --- trying to load features from " << file_name << "\n";
    std::ifstream        ifs(file_name, std::fstream::in);
    FrameIndexedFeatures frame_indexed_features;

    // read image
    while (ifs.good())
    {
        // frame_id camera_index image_name
        uint64_t    frame_id          = 0;
        uint16_t    camera_index      = 0;
        std::string feature_file_name = "";

        ifs >> frame_id >> camera_index >> feature_file_name;

        if (ifs.fail())
        {
            break;
        }

        // load features
        std::ifstream fin(feature_file_name);

        if (!fin)
        {
            LOG(ERROR) << "MapDatabaseManager --- LoadFeatures, could not open " << feature_file_name;
            throw std::runtime_error("MapDatabaseManager --- LoadFeatures, no such file or directory.\n");
        }

        // total feature number
        uint16_t features_num;
        fin.read((char*)&features_num, sizeof(uint16_t));

        // descriptor dimension
        uint16_t descriptor_dimension;
        fin.read((char*)&descriptor_dimension, sizeof(uint16_t));

        Features features;
        features.reserve(features_num);

        // read features
        for (uint16_t i = 0; i < features_num; i++)
        {
            // read image point
            Scalar img_pt_x = 0.0;
            Scalar img_pt_y = 0.0;
            fin.read((char*)&img_pt_x, sizeof(Scalar));
            fin.read((char*)&img_pt_y, sizeof(Scalar));

            // read normalized point
            Scalar normalized_point_x = 0.0;
            Scalar normalized_point_y = 0.0;
            Scalar normalized_point_z = 0.0;
            fin.read((char*)&normalized_point_x, sizeof(Scalar));
            fin.read((char*)&normalized_point_y, sizeof(Scalar));
            fin.read((char*)&normalized_point_z, sizeof(Scalar));

            // read category
            SemanticLabel semantic_label;
            fin.read((char*)&semantic_label, sizeof(SemanticLabel));

            // read descriptor
            cv::Mat descriptor;
            descriptor.create(1, descriptor_dimension, CV_32FC1);

            for (uint16_t j = 0; j < descriptor_dimension; j++)
            {
                fin.read((char*)&descriptor.at<float32_t>(0, j), sizeof(float32_t));
            }

            // load camera id
            uint16_t camera_id;
            fin.read((char*)&camera_id, sizeof(uint16_t));

            // load score
            Scalar score = -1.0;
            fin.read((char*)&score, sizeof(Scalar));
            // stores this feature
            features.emplace_back(cv::Point2f(img_pt_x, img_pt_y), descriptor,
                                  Point3(normalized_point_x, normalized_point_y, normalized_point_z), camera_id, score,
                                  semantic_label);
        }
        frame_indexed_features[frame_id].emplace(camera_index, features);
    }

    LOG(INFO) << "MapDatabaseManager --- load features done. total frames: " << frame_indexed_features.size() << "\n";

    return frame_indexed_features;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Relocalization, Run)
{
    /**
     * @brief Evaluate the relocalization success rate about current method
     * 
     * @details main ideal about this problem:
     * 
     *  [1]: loading map_database in current map using MapDatabaseManager (for get KeyFrame database)
     *  [2]: create relocalization class and set keyframe database which from MapDatabaseManager
     *  [3]: load frame features from offline mapping storge data 
     *  [4]: get the ground truth pose about current frame from offline mapping datas
     *  [5]: do relocation method using frame features and get the return pose, we compare it and relocalization
     *       return pose, if the difference was within the expected range, we think relocalization sucessful.
     */
    std::string holo_config_root = "/home/holo/holo_space/holo_parking_gh01_develop/output/native/release/target/config/";
    std::string config_file      = holo_config_root + "holo_localization_parking/app_config/vslam/localization.yaml";
    holo::yaml::Node const node = holo::yaml::LoadFile(config_file);

    /// @brief Step-1: Load parameters from yaml file
    auto const localization_parameters = Localization::Parameters::LoadFromYaml(node);

    MapDatabaseManager::Ptr map_database_manager = 
                                            std::make_shared<MapDatabaseManager>(localization_parameters.mdm_params);

    /// @brief Step-2: Create relocalization class using parameters and camera parameters
    Relocalization::Ptr relocalization_ptr =
        std::make_shared<Relocalization>(localization_parameters.reloc_params, localization_parameters.camera_params);
    Relocalization::bow_vocabulary_ = std::make_shared<DBoW3::Vocabulary>(holo_config_root +
                                                        "holo_localization_parking/app_config/vslam/small_voc.yml.gz");
    relocalization_ptr->SetKeyFramesDbowVector(map_database_manager->GetKeyframesBowVector());
    relocalization_ptr->SetKeyFramesDatabase(map_database_manager->GetKeyframes());
    relocalization_ptr->Stop();

    /// @brief Step-3: load frame featues using mapping database
    std::string map_name      = localization_parameters.mdm_params.map_names.at(0u);
    std::string features_path = localization_parameters.mdm_params.map_data_dir + "/" + map_name + "/features.txt";
    FrameIndexedFeatures frameID_features = LoadFeatures(features_path);

    /// @brief Step-4: get the ground truth pose about current frame from offline mapping datas
    std::vector<Odometry> ground_truth = map_database_manager->GetLearnedPath();

    if (ground_truth.size() != frameID_features.size())
    {
        LOG(ERROR) << "Size of ground_truth and Estimate is not equal!";
    }

    /// @brief Step-5: do relocation method using frame features and get the return pose, we compare it and relocalization
    ///       if the difference between ground truth and estimated was within the expected range,
    ///           we think relocalization sucessful
    boost::optional<Pose3> prior_T_wb          = boost::none;
    boost::optional<Pose3> relocalization_T_wb = boost::none;

    for (auto iter = frameID_features.cbegin(); iter != frameID_features.cend(); ++iter)
    {
        std::vector<Features> multi_camera_features;
        uint64_t              frame_id              = iter->first;
        CameraIndexedFeatures camera_index_features = iter->second;

        // 5.1: Collect the descriptor(Features) information of each image frame
        for (auto feature_iter = camera_index_features.cbegin(); feature_iter != camera_index_features.cend(); ++feature_iter)
        {
            multi_camera_features.push_back(feature_iter->second);
        }

        // 5.2: relocalization using current features and mapdatabase
        LOG(INFO) << "Current query Frame ID is: " << frame_id;
        relocalization_T_wb = relocalization_ptr->RunSynchronously(multi_camera_features, prior_T_wb);

        // 5.3: compare the estimated result and ground truth
        if (relocalization_T_wb)
        {
            ///@note all pose is in vehicle body coordinates
            Pose3 estimate_pose = *relocalization_T_wb;
            Pose3 ground_pose   = ground_truth.at(frame_id).GetPose();

            LOG(INFO) << "Estimate_pose: " << estimate_pose;
            LOG(INFO) << "Ground_pose: " << ground_pose;
            LOG(INFO) << "Distance between Estimate_pose and Ground_pose: " << estimate_pose.Dist(ground_pose);
        }
        else
        {
            LOG(ERROR) << "Relocalization failuer using frame_" << frame_id << "'s features";
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
