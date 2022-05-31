/*!
 * \brief visual slam descriptor matcher class cpp file
 * \author Feng.Li lifeng@holomatic.com
 * \date Nov-13-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/descriptor_matcher.h>
#ifdef HOLO_LOCALIZATION_BUILD_WITH_TIDL
#include "holo/localization/vision/tidl/app_nms.h"
#endif

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
#ifdef HOLO_LOCALIZATION_BUILD_WITH_TIDL
struct DescriptorMatcherKernel
{
    // the input and output data num, now default is: 2000 * 128
    static int data_size_tmp;

    // now the size is 4, the first two is input, the last two is ouput, every data in vector represents the num of
    // input or output
    static std::vector<int> data_len;

    // now the size is 4, the first two is input, the last two is ouput, every data in vector represents the type of
    //  input or output ---> 1 2 4 （int8, int16, float32）
    // input1: desc_a_list and desc_b_list;
    // input2: a_list_size, b_list_size, top_match_num
    static std::vector<int> data_type_tmp;

    // tidl des matching kernel
    static std::shared_ptr<AppSelfKernel> tidl_desc_matcher;

    // tidl init flag
    static bool is_kernel_init;
};

/**
 * @brief initialize static member variable
 */
int              DescriptorMatcherKernel::data_size_tmp = 2000 * 128;
std::vector<int> DescriptorMatcherKernel::data_len      = {data_size_tmp, data_size_tmp, data_size_tmp, data_size_tmp};
std::vector<int> DescriptorMatcherKernel::data_type_tmp = {4, 2, 2, 4};  // 1 2 4 （int8, int16, float32）
std::shared_ptr<AppSelfKernel> DescriptorMatcherKernel::tidl_desc_matcher = nullptr;
bool                           DescriptorMatcherKernel::is_kernel_init    = false;
#endif

///////////////////////////////////////////////////////////////////////////////
void DescriptorMatcher::InitKernel()
{
#ifdef HOLO_LOCALIZATION_BUILD_WITH_TIDL

    if (!DescriptorMatcherKernel::is_kernel_init)
    {
        LOG(INFO) << "Begin to init desc matching kernel ...";
        DescriptorMatcherKernel::tidl_desc_matcher =
            std::make_shared<AppSelfKernel>(DescriptorMatcherKernel::data_len, DescriptorMatcherKernel::data_type_tmp);
        DescriptorMatcherKernel::is_kernel_init = true;
        LOG(INFO) << "Init desc matching kernel Done !!!";
    }

#endif
}

///////////////////////////////////////////////////////////////////////////////
bool DescriptorMatcher::IsKernelInit()
{
#ifdef HOLO_LOCALIZATION_BUILD_WITH_TIDL
    return DescriptorMatcherKernel::is_kernel_init;
#endif

    return false;
}

///////////////////////////////////////////////////////////////////////////////
Scalar DescriptorMatcher::DescriptorDistance(const cv::Mat& d1, const cv::Mat& d2)
{
    /**
     * @brief comput the euclidean distance between d1 and d2
     * @details we assume d1 and d2 have already been normalized.
     *          result^2 = (d1 - d2)^T * (d1 - d2)
                         = (d1^T)(d1) + (d2^T)(d2) - 2 * (d1^T) * d2
                         = 1 + 1 - 2 * d1.dot(d2)
                         = 2 - 2 * d1.dot(d2);
     */
    float32_t distance = (float32_t)d1.dot(d2);
    distance           = std::sqrt(2 - 2 * distance);
    return distance;
}

///////////////////////////////////////////////////////////////////////////////
DescriptorMatcher::MatchPairs
DescriptorMatcher::OneToOneFiltering(const MatchPairsWithDistance& many_to_one_match_result)
{
    // one to one matching filter
    MatchPairsWithDistance one_to_one_match_result;

    for (const auto& result : many_to_one_match_result)
    {
        const uint16_t& index_i = result.first;
        const uint16_t& index_j = result.second.first;
        const Scalar&   dist    = result.second.second;

        if (one_to_one_match_result.count(index_j))
        {
            const Scalar old_dist = one_to_one_match_result.at(index_j).second;

            if (dist > old_dist)
            {
                continue;
            }
        }

        one_to_one_match_result[index_j] = std::make_pair(index_i, dist);
    }

    // construct final match pairs
    MatchPairs match_pairs;
    match_pairs.reserve(one_to_one_match_result.size());

    for (const auto& result : one_to_one_match_result)
    {
        match_pairs.emplace_back(result.second.first, result.first);
    }

    return match_pairs;
}

///////////////////////////////////////////////////////////////////////////////
DescriptorMatcher::MatchPairs DescriptorMatcher::BruteForceMatching(const std::vector<cv::Mat>& desc1,
                                                                    const std::vector<cv::Mat>& desc2, Scalar dist_th,
                                                                    Scalar ratio_test_th)
{
    // define temporary match result.(many to one)
    MatchPairsWithDistance many_to_one_match_result;

    // loop all descriptor in desc1
    for (uint16_t i = 0; i < desc1.size(); i++)
    {
        const auto& d1 = desc1.at(i);

        // define matching message
        MatchingMessage matching_message(d1, i);

        // loop all descriptor in desc2
        for (uint16_t j = 0; j < desc2.size(); j++)
        {
            // check descriptor distance
            const auto& d2 = desc2.at(j);

            // update matching message
            matching_message = matching_message.UpdateMessage(matching_message, d2, j);
        }

        // check if acceptable
        if (matching_message.IsMatchingAcceptable(dist_th, ratio_test_th))
        {
            many_to_one_match_result.emplace(
                matching_message.train_index,
                std::make_pair(matching_message.best_query_index, matching_message.minimum_distance));
        }
    }

    // one to one matching filter
    return OneToOneFiltering(many_to_one_match_result);
}

///////////////////////////////////////////////////////////////////////////////
DescriptorMatcher::MatchPairs DescriptorMatcher::FlowMatching(const Features& features1, const Features& features2,
                                                              const uint16_t window_size, Scalar dist_th,
                                                              Scalar ratio_test_th)
{
    // define temporary match result.(many to one)
    MatchPairsWithDistance many_to_one_match_result;

    // loop all descriptor in features1
    for (uint16_t i = 0; i < features1.size(); i++)
    {
        const auto& d1 = features1.at(i).optional_descriptor;

        if (!d1)
        {
            throw std::runtime_error("DescriptorMatcher --- calling FlowMatching while input feature1 "
                                     "without descriptor.\n");
        }

        const auto& pt1 = features1.at(i).image_point;

        const auto pt_1_x_lower_boundary = pt1.x - window_size;
        const auto pt_1_x_upper_boundary = pt1.x + window_size;
        const auto pt_1_y_lower_boundary = pt1.y - window_size;
        const auto pt_1_y_upper_boundary = pt1.y + window_size;

        // define matching message
        MatchingMessage matching_message(*d1, i);

        // loop all descriptor in features2
        for (uint16_t j = 0; j < features2.size(); j++)
        {
            // check descriptor distance
            const auto& d2 = features2.at(j).optional_descriptor;

            if (!d2)
            {
                throw std::runtime_error("DescriptorMatcher --- calling FlowMatching while input feature2 "
                                         "without descriptor.\n");
            }

            const auto& pt2 = features2.at(j).image_point;

            // discard features who is out of searched window size
            if (pt2.x > pt_1_x_upper_boundary || pt2.x < pt_1_x_lower_boundary || pt2.y < pt_1_y_lower_boundary ||
                pt2.y > pt_1_y_upper_boundary)
            {
                continue;
            }

            // update matching message
            matching_message = matching_message.UpdateMessage(matching_message, *d2, j);
        }

        // check if acceptable
        if (matching_message.IsMatchingAcceptable(dist_th, ratio_test_th))
        {
            many_to_one_match_result.emplace(
                matching_message.train_index,
                std::make_pair(matching_message.best_query_index, matching_message.minimum_distance));
        }
    }

    // one to one matching filter
    return OneToOneFiltering(many_to_one_match_result);
}

///////////////////////////////////////////////////////////////////////////////
DescriptorMatcher::MatchPairs DescriptorMatcher::MappointsToFeaturesMatching(
    const ConstMapPtr& map, const Features& features, const IntrinsicBaseTypePtr& intrinsic, const Pose3& T_wc,
    Scalar window_size, Scalar descriptor_dist_th, Scalar ratio_test_th, Scalar view_distance_th,
    Scalar view_direction_th, bool use_kernel)
{
    if (use_kernel)
    {
#ifdef HOLO_LOCALIZATION_BUILD_WITH_TIDL
        if (!DescriptorMatcherKernel::is_kernel_init)
        {
            LOG(ERROR) << "DescriptorMatcher --- You should init kernel first before use it.\n";
            throw std::runtime_error("kernel usage error.");
        }

        // define temporary match result.(many to one)
        MatchPairsWithDistance many_to_one_match_result;

        // define temporary match result.(one to one)
        DescriptorMatcher::MatchPairs one_to_one_match_result;

        const auto  cos_theta_threshold = std::cos(holo::Radian(view_direction_th));
        TicTocTimer matcher_time;
        matcher_time.Tic();

        // prepare query and train desc for matching
        for (uint16_t i = 0; i < map->size(); i++)
        {
            // map and features desc mat
            cv::Mat maps_and_features_desc_mat;

            // check camera distance
            if (map->at(i)->reference_pose.Dist(T_wc) > view_distance_th)
            {
                continue;
            }

            // project into query_frame
            const Point3& ptw = map->at(i)->position;
            const auto    ptc = T_wc.Inverse() * ptw;

            if (ptc.GetZ() < 0)
            {
                continue;
            }

            // project mappoint onto image plane
            Point2 pt_i;
            intrinsic->Project(ptc, pt_i);

            // check if out of image boundary
            // note: if map point and predicted pose are both unperfect, we project this point by the pose may out of
            // the raw image boundary. an we think we should still give it a chance to matching. so we extend the image
            // size to raw_image_size + 2 * window_size.
            if ((pt_i.GetX() < -1.0 * window_size) || (pt_i.GetX() > intrinsic->GetWidth() + window_size) ||
                (pt_i.GetY() < -1.0 * window_size) || (pt_i.GetY() > intrinsic->GetHeight() + window_size))
            {
                continue;
            }

            const cv::Mat& desc_i           = map->at(i)->descriptor;
            const Vector3& direction_i      = map->at(i)->direction;
            const auto     direction_i_norm = direction_i.GetNorm();

            const auto pt_i_x_lower_boundary = pt_i.GetX() - window_size;
            const auto pt_i_x_upper_boundary = pt_i.GetX() + window_size;
            const auto pt_i_y_lower_boundary = pt_i.GetY() - window_size;
            const auto pt_i_y_upper_boundary = pt_i.GetY() + window_size;

            maps_and_features_desc_mat.push_back(desc_i);

            // loop all descriptor in features
            uint32_t              candidate_feature_num = 0;
            std::vector<uint16_t> candidate_feature_index;
            for (uint16_t j = 0; j < features.size(); j++)
            {
                const auto optional_descriptor = features.at(j).optional_descriptor;

                if (!optional_descriptor)
                {
                    throw std::runtime_error(
                        "DescriptorMatcher --- calling MappointsToFeaturesMatching while input feature "
                        "without descriptor.\n");
                }

                // discard features who is out of searched window size
                if (features.at(j).image_point.x > pt_i_x_upper_boundary ||
                    features.at(j).image_point.x < pt_i_x_lower_boundary ||
                    features.at(j).image_point.y > pt_i_y_upper_boundary ||
                    features.at(j).image_point.y < pt_i_y_lower_boundary)
                {
                    continue;
                }

                // get current feature's view direction in world frame
                const Vector3 direction_j = T_wc.GetRotation().Rotate(features.at(j).normalized_point.ToVector());

                // check angle between two view direction
                const Scalar cos_theta = direction_i.Dot(direction_j) / (direction_i_norm * direction_j.GetNorm());

                if (cos_theta < cos_theta_threshold)
                {
                    continue;
                }
                candidate_feature_num++;
                maps_and_features_desc_mat.push_back(*optional_descriptor);
                candidate_feature_index.push_back(j);
            }

            // desc matcher params  1. map size 2. feature size 3.match top num
            /// @todo the top match num is hardcode temporarily
            uint16_t desc_matcher_params[3] = {1, (uint16_t)candidate_feature_num, (uint16_t)350};

            if ((uint64_t)maps_and_features_desc_mat.rows != (1 + candidate_feature_num))
            {
                LOG(ERROR) << "DescriptorMatcher --- the candidate map size is: " << 1
                           << ", the feaure size is: " << candidate_feature_num
                           << ", but desc mat size is(rows, cols): " << maps_and_features_desc_mat.rows << " "
                           << maps_and_features_desc_mat.cols;
                throw std::runtime_error("DescriptorMatcher --- the desc data size is not equal to mat rows.\n");
            }

            // set data into kernel for desc matching
            DescriptorMatcherKernel::tidl_desc_matcher->setdata((int8_t*)maps_and_features_desc_mat.data,
                                                                maps_and_features_desc_mat.cols *
                                                                    maps_and_features_desc_mat.rows * sizeof(float));
            DescriptorMatcherKernel::tidl_desc_matcher->setdata((int8_t*)desc_matcher_params, 3 * sizeof(uint16_t), 1);

            uint16_t matching_result_data[desc_matcher_params[2] * 3];
            float    score_result_data[desc_matcher_params[2]];

            // get matching result from kernel
            DescriptorMatcherKernel::tidl_desc_matcher->getdata((int8_t*)matching_result_data,
                                                                (desc_matcher_params[2] * sizeof(uint16_t) * 3), 0);
            DescriptorMatcherKernel::tidl_desc_matcher->getdata((int8_t*)score_result_data,
                                                                (desc_matcher_params[2] * sizeof(float)), 1);

            uint16_t matched_pair_size = matching_result_data[0];

            // Print matching index for debug
            for (int index = 1; index <= matched_pair_size; index++)
            {
                // LOG(INFO) << "map index: " << matching_result_data[index]
                //           << ", feature index: " << matching_result_data[matched_pair_size + index]
                //           << ", matching score: " << score_result_data[index - 1];

                // check if acceptable
                if (score_result_data[index - 1] > descriptor_dist_th)
                {
                    continue;
                }

                many_to_one_match_result.emplace(
                    i, std::make_pair(candidate_feature_index[matching_result_data[matched_pair_size + index]],
                                      score_result_data[index - 1]));
            }

            if (matcher_time.Elapsed() * 1e3 > 500)
            {
                LOG(INFO) << "DescriptorMatcher --- the mappint to feauture matching time used is over 500 ms";
                return OneToOneFiltering(many_to_one_match_result);
            }
        }
        return OneToOneFiltering(many_to_one_match_result);
        (void)ratio_test_th;
#else
        LOG(ERROR) << "DescriptorMatcher --- Wanna use kernel while compiler options disable "
                      "HOLO_LOCALIZATION_BUILD_WITH_TIDL.\n";
        throw std::runtime_error("kernel usage error.");
#endif
    }

    // define temporary match result.(many to one)
    MatchPairsWithDistance many_to_one_match_result;

    const auto cos_theta_threshold = std::cos(holo::Radian(view_direction_th));
    const auto T_wc_inv            = T_wc.Inverse();

    // loop all descriptor in map
    for (uint16_t i = 0; i < map->size(); i++)
    {
        // check camera distance
        if (map->at(i)->reference_pose.Dist(T_wc) > view_distance_th)
        {
            continue;
        }

        // project into query_frame
        const Point3& ptw = map->at(i)->position;
        const auto    ptc = T_wc_inv * ptw;

        if (ptc.GetZ() < 0)
        {
            continue;
        }

        // project mappoint onto image plane
        Point2 pt_i;
        intrinsic->Project(ptc, pt_i);

        // check if out of image boundary
        // note: if map point and predicted pose are both unperfect, we project this point by the pose may out of the
        // raw image boundary. an we think we should still give it a chance to matching. so we extend the image size to
        // raw_image_size + 2 * window_size.
        if ((pt_i.GetX() < -1.0 * window_size) || (pt_i.GetX() > intrinsic->GetWidth() + window_size) ||
            (pt_i.GetY() < -1.0 * window_size) || (pt_i.GetY() > intrinsic->GetHeight() + window_size))
        {
            continue;
        }

        const cv::Mat& desc_i           = map->at(i)->descriptor;
        const Vector3& direction_i      = map->at(i)->direction;
        const auto     direction_i_norm = direction_i.GetNorm();

        const auto pt_i_x_lower_boundary = pt_i.GetX() - window_size;
        const auto pt_i_x_upper_boundary = pt_i.GetX() + window_size;
        const auto pt_i_y_lower_boundary = pt_i.GetY() - window_size;
        const auto pt_i_y_upper_boundary = pt_i.GetY() + window_size;

        // define matching message
        MatchingMessage matching_message(desc_i, i);

        // loop all descriptor in features
        for (uint16_t j = 0; j < features.size(); j++)
        {
            const auto optional_descriptor = features.at(j).optional_descriptor;

            if (!optional_descriptor)
            {
                throw std::runtime_error(
                    "DescriptorMatcher --- calling MappointsToFeaturesMatching while input feature "
                    "without descriptor.\n");
            }

            // discard features who is out of searched window size
            if (features.at(j).image_point.x > pt_i_x_upper_boundary ||
                features.at(j).image_point.x < pt_i_x_lower_boundary ||
                features.at(j).image_point.y > pt_i_y_upper_boundary ||
                features.at(j).image_point.y < pt_i_y_lower_boundary)
            {
                continue;
            }

            // get current feature's view direction in world frame
            const Vector3 direction_j = T_wc.GetRotation().Rotate(features.at(j).normalized_point.ToVector());

            // check angle between two view direction
            const Scalar cos_theta = direction_i.Dot(direction_j) / (direction_i_norm * direction_j.GetNorm());

            if (cos_theta < cos_theta_threshold)
            {
                continue;
            }

            // update matching message
            matching_message = matching_message.UpdateMessage(matching_message, *optional_descriptor, j);
        }

        // check if acceptable
        if (matching_message.IsMatchingAcceptable(descriptor_dist_th, ratio_test_th))
        {
            many_to_one_match_result.emplace(
                matching_message.train_index,
                std::make_pair(matching_message.best_query_index, matching_message.minimum_distance));
        }
    }

    // one to one matching filter
    return OneToOneFiltering(many_to_one_match_result);
}

///////////////////////////////////////////////////////////////////////////////
DescriptorMatcher::MatchPairs DescriptorMatcher::EpipolarLineMatching(const FeaturesWithObservedPoses& first_data,
                                                                      const FeaturesWithObservedPoses& second_data,
                                                                      Scalar                           epipolar_dist_th,
                                                                      Scalar descriptor_dist_th, Scalar ratio_test_th)
{
    std::map<std::pair<Pose3, Pose3>, Matrix3, ComparePose3Pair> pose_pair_to_essential_matrix;

    // define temporary match result.(many to one)
    MatchPairsWithDistance many_to_one_match_result;

    // loop all features in first_data
    for (size_t i = 0; i < first_data.size(); i++)
    {
        const auto   desc_i = first_data.at(i).first.optional_descriptor;
        const Point3 ptn_i  = first_data.at(i).first.normalized_point;
        const Pose3  Twc_i  = first_data.at(i).second;

        if (!desc_i)
        {
            throw std::runtime_error("DescriptorMatcher --- calling EpipolarLineMatching while input first_data "
                                     "without descriptor.\n");
        }

        // define matching message
        MatchingMessage matching_message(*desc_i, i);

        // loop all features in second_data
        for (size_t j = 0; j < second_data.size(); j++)
        {
            // get desc_j and nomarlized point j
            const auto   desc_j = second_data.at(j).first.optional_descriptor;
            const Point3 ptn_j  = second_data.at(j).first.normalized_point;
            const Pose3  Twc_j  = second_data.at(j).second;

            // check valid of descriptor
            if (!desc_j)
            {
                throw std::runtime_error("DescriptorMatcher --- calling EpipolarLineMatching while input second_data "
                                         "without descriptor.\n");
            }

            // check if can serve as candidate correspondence
            if (Twc_j.Dist(Twc_i) < 1e-3)
            {
                // pure rotation, degenerated case
                // rotate two camera view direction to world frame
                const Vector3 view_direction_i = Twc_i.GetRotation().Rotate(ptn_i.ToVector());
                const Vector3 view_direction_j = Twc_j.GetRotation().Rotate(ptn_j.ToVector());

                // compute angle between view_direction_i and view_direction_j
                const Scalar cos_theta =
                    view_direction_i.Dot(view_direction_j) / (view_direction_i.GetNorm() * view_direction_j.GetNorm());

                // check angle
                const Scalar angle_th = 1.0;  // degree.

                if (cos_theta < std::cos(holo::Radian(angle_th)))
                {
                    continue;
                }
            }
            else
            {
                Vector3 epipolar_line;
                if (!pose_pair_to_essential_matrix.count(std::pair<Pose3, Pose3>{Twc_i, Twc_j}))
                {
                    const std::pair<Pose3, Pose3> pose_pair = std::make_pair(Twc_i, Twc_j);
                    pose_pair_to_essential_matrix[pose_pair] =
                        holo::localization::vision::vslam::Utility::EssentialMatrixFromPoses(Twc_i, Twc_j);
                }
                epipolar_line =
                    pose_pair_to_essential_matrix.at(std::pair<Pose3, Pose3>{Twc_i, Twc_j}) * ptn_i.ToVector();

                // compute distance between ptn_j and epipolar_line
                // l: Ax + By + C = 0; p: (x0, y0); distance = |A * x0 + B * y0 + C| / sqrt(A^2 + B^2);
                const Scalar epipolar_distance =
                    std::fabs(ptn_j.ToVector().Dot(epipolar_line)) / epipolar_line.GetBlock(0, 0, 2, 1).GetNorm();

                // reject if epipolar_distance large than threshold
                if (epipolar_distance > epipolar_dist_th)
                {
                    continue;
                }
            }

            // update matching message
            matching_message = matching_message.UpdateMessage(matching_message, *desc_j, j);
        }

        // check if acceptable
        if (matching_message.IsMatchingAcceptable(descriptor_dist_th, ratio_test_th))
        {
            many_to_one_match_result.emplace(
                matching_message.train_index,
                std::make_pair(matching_message.best_query_index, matching_message.minimum_distance));
        }
    }

    // one to one matching filter
    return OneToOneFiltering(many_to_one_match_result);
}

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo
