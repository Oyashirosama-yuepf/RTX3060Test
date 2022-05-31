/*!
 * \brief generate descriptor matcher data for unit test in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date Dec-16-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/vslam/descriptor_matcher.h>

namespace vslam = holo::localization::vision::vslam;

///////////////////////////////////////////////////////////////////////////////
/**
 * @brief test fixture class to generate test data
 *
 * @details generate three set of features with groundtruth match result
 */
class TestFixture : public ::testing::Test
{
public:
    // constructor
    TestFixture()
    {
    }

    // destructor
    virtual ~TestFixture()
    {
    }

    /**
     * @brief main function to generate test data
     */
    virtual void SetUp() override
    {
        // generate camera intrinsic
        intrinsic_.SetDimension(640, 480);
        intrinsic_.SetFocalLength(300, 300);
        intrinsic_.SetPrinciplePoint(320, 240);
        intrinsic_.SetSkew(0);
        const auto& K = intrinsic_.GetK();

        // genarate four 3d points and their descriptor
        vslam::Point3 p0(-10, -10, 50.0);
        cv::Mat       d0 = cv::Mat::zeros(1, 4, CV_32FC1);
        d0.col(0)        = 1;

        vslam::Point3 p1(-10, 10, 50.0);
        cv::Mat       d1 = cv::Mat::zeros(1, 4, CV_32FC1);
        d1.col(1)        = 1;

        vslam::Point3 p2(10, -10, 50.0);
        cv::Mat       d2 = cv::Mat::zeros(1, 4, CV_32FC1);
        d2.col(2)        = 1;

        vslam::Point3 p3(10, 10, 50.0);
        cv::Mat       d3 = cv::Mat::zeros(1, 4, CV_32FC1);
        d3.col(3)        = 1;

        // generate ground truth map
        {
            gt_map_.reserve(4);
            gt_map_.emplace_back(std::make_shared<vslam::MapPoint>(GenerateMappoint(p0, vslam::Pose3::Identity(), d0)));
            gt_map_.emplace_back(std::make_shared<vslam::MapPoint>(GenerateMappoint(p1, vslam::Pose3::Identity(), d1)));
            gt_map_.emplace_back(std::make_shared<vslam::MapPoint>(GenerateMappoint(p2, vslam::Pose3::Identity(), d2)));
            gt_map_.emplace_back(std::make_shared<vslam::MapPoint>(GenerateMappoint(p3, vslam::Pose3::Identity(), d3)));
        }

        // generate first set of features and pose
        {
            gt_pose0_ = vslam::Pose3::Identity();

            gt_features0_.reserve(4);
            gt_features0_.emplace_back(GenerateFeature(p0, gt_pose0_, K, d0));
            gt_features0_.emplace_back(GenerateFeature(p1, gt_pose0_, K, d1));
            gt_features0_.emplace_back(GenerateFeature(p2, gt_pose0_, K, d2));
            gt_features0_.emplace_back(GenerateFeature(p3, gt_pose0_, K, d3));
        }

        // translate camera and generate the second set of features and pose
        {
            vslam::Point3 delta_t(0.0, 0.0, 0.5);
            vslam::Rot3   delta_r = vslam::Rot3::Identity();
            vslam::Pose3  delta_move(delta_r, delta_t);
            gt_pose1_ = gt_pose0_ * delta_move;

            gt_features1_.reserve(4);
            gt_features1_.emplace_back(GenerateFeature(p0, gt_pose1_, K, d0));
            gt_features1_.emplace_back(GenerateFeature(p1, gt_pose1_, K, d1));
            gt_features1_.emplace_back(GenerateFeature(p2, gt_pose1_, K, d2));
            gt_features1_.emplace_back(GenerateFeature(p3, gt_pose1_, K, d3));
        }

        // rotate camera and generate the third set of features and pose
        {
            // pure rotation, used to test EpipolarLineMatching
            vslam::Point3 delta_t(0.0, 0.0, 0.0);
            vslam::Rot3   delta_r = vslam::Rot3::Yaw(holo::Radian(10.0));
            vslam::Pose3  delta_move(delta_r, delta_t);
            gt_pose2_ = gt_pose0_ * delta_move;

            gt_features2_.reserve(4);
            gt_features2_.emplace_back(GenerateFeature(p0, gt_pose2_, K, d0));
            gt_features2_.emplace_back(GenerateFeature(p1, gt_pose2_, K, d1));
            gt_features2_.emplace_back(GenerateFeature(p2, gt_pose2_, K, d2));
            gt_features2_.emplace_back(GenerateFeature(p3, gt_pose2_, K, d3));
        }
    }

    virtual void TearDown() override
    {
    }

    /**
     * @brief generate feature
     *
     * @param[in] point 3d point in "world" frame
     * @param[in] pose pose which can transform a point from camera to "world"
     * @param[in] K camera intrinsic matrix
     * @param[in] d descriptor
     * @return feature
     */
    vslam::Feature GenerateFeature(const vslam::Point3& point, const vslam::Pose3& pose, const vslam::Matrix3& K,
                                   const cv::Mat& d) const
    {
        // transform point from world to camera
        const vslam::Point3 ptc = pose.Inverse() * point;

        // project to normalize plane
        const vslam::Point3 ptn = ptc / ptc.GetZ();

        // project to image plane by pinhole camera model
        const vslam::Vector3 pt_img = K * ptn.ToVector();

        // construct result
        return vslam::Feature(cv::Point2f(pt_img[0], pt_img[1]), d, ptn);
    }

    /**
     * @brief generate mappoint
     *
     * @param[in] point 3d point in "world" frame
     * @param[in] pose pose which can transform a point from camera to "world"
     * @param[in] d descriptor
     * @return new mappoint
     */
    vslam::MapPoint GenerateMappoint(const vslam::Point3& point, const vslam::Pose3& reference_pose,
                                     const cv::Mat& d) const
    {
        vslam::MapPoint mp;
        mp.position       = point;
        mp.descriptor     = d;
        mp.reference_pose = reference_pose;
        mp.direction      = (reference_pose.Inverse() * point).ToVector();
        return mp;
    }

protected:
    /// @brief intrinsic
    holo::localization::vision::vslam::Intrinsic intrinsic_;

    /// @brief ground truth map
    vslam::Map gt_map_;

    /// @brief ground truth pose
    vslam::Pose3 gt_pose0_, gt_pose1_, gt_pose2_;

    /// @brief ground truth features
    vslam::Features gt_features0_, gt_features1_, gt_features2_;
};  // TestFixture
