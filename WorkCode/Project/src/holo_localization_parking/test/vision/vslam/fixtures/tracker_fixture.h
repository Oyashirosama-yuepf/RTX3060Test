/*!
 * \brief generate tracker with descriptor data for unit test in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date Dec-16-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/feature_track.h>
#include <holo/localization/vision/vslam/tracker.h>

namespace vslam = holo::localization::vision::vslam;

///////////////////////////////////////////////////////////////////////////////
/**
 * @brief test fixture class to generate test data
 *
 * @details generate an 3d rectangular plane located in front of camera. and keep the camera moving forward.
 *          then generate a set of feature track's measurement by projecting the vertices of the rectangle onto each
 *          image.
 */
class TestFixture : public ::testing::Test
{
public:
    // constructor
    TestFixture()
      : camera_index_(0)
      , camera_parameters_(vslam::CameraParameters::Example())
      , parameters_(vslam::Tracker::Parameters::Example())
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
        // get center point of image
        const vslam::Point2 center_point(camera_parameters_->intrinsics.at(camera_index_).GetWidth() / 2.0,
                                         camera_parameters_->intrinsics.at(camera_index_).GetHeight() / 2.0);

        // generate a 2d rectangular plane on image
        vslam::Point2 top_left_corner     = center_point + vslam::Point2(-50.0, -50.0);
        vslam::Point2 bottom_left_corner  = center_point + vslam::Point2(-50.0, 50.0);
        vslam::Point2 top_right_corner    = center_point + vslam::Point2(50.0, -50.0);
        vslam::Point2 bottom_right_corner = center_point + vslam::Point2(50.0, 50.0);

        // generate depth of 3d rectangular
        const vslam::Scalar depth = 50.0;

        // generate four vertices of 3d rectangular plane
        vslam::Pose3  T_wc = vslam::Pose3::Identity();
        vslam::Point3 top_left_corner_3d =
            BackProject(top_left_corner, depth, T_wc, camera_parameters_->intrinsics.at(camera_index_).GetK());
        vslam::Point3 bottom_left_corner_3d =
            BackProject(bottom_left_corner, depth, T_wc, camera_parameters_->intrinsics.at(camera_index_).GetK());
        vslam::Point3 top_right_corner_3d =
            BackProject(top_right_corner, depth, T_wc, camera_parameters_->intrinsics.at(camera_index_).GetK());
        vslam::Point3 bottom_right_corner_3d =
            BackProject(bottom_right_corner, depth, T_wc, camera_parameters_->intrinsics.at(camera_index_).GetK());
        points_.reserve(4);
        points_.emplace_back(top_left_corner_3d);
        points_.emplace_back(bottom_left_corner_3d);
        points_.emplace_back(top_right_corner_3d);
        points_.emplace_back(bottom_right_corner_3d);

        // moving camera forward and generate a set of track measurement
        uint16_t image_num = 10;
        images_and_features_and_pose_.reserve(image_num);

        // generate motion info
        vslam::Pose3 delta_move(vslam::Rot3::Identity(), vslam::Point3(0.0, 0.0, 1.5));

        // generate descriptors of four vertices
        cv::Mat top_left_corner_desc     = cv::Mat::zeros(1, 4, CV_32FC1);
        top_left_corner_desc.col(0)      = 1;
        cv::Mat bottom_left_corner_desc  = cv::Mat::zeros(1, 4, CV_32FC1);
        bottom_left_corner_desc.col(1)   = 1;
        cv::Mat top_right_corner_desc    = cv::Mat::zeros(1, 4, CV_32FC1);
        top_right_corner_desc.col(2)     = 1;
        cv::Mat bottom_right_corner_desc = cv::Mat::zeros(1, 4, CV_32FC1);
        bottom_right_corner_desc.col(3)  = 1;

        // generate images and features
        for (uint64_t i = 0; i < image_num; i++)
        {
            // compute current camera pose
            T_wc = T_wc * delta_move;

            // generate four features
            const vslam::Feature top_left_feature =
                GenerateFeature(top_left_corner_3d, T_wc, camera_parameters_->intrinsics.at(camera_index_).GetK(),
                                top_left_corner_desc);
            const vslam::Feature bottom_left_feature =
                GenerateFeature(bottom_left_corner_3d, T_wc, camera_parameters_->intrinsics.at(camera_index_).GetK(),
                                bottom_left_corner_desc);
            const vslam::Feature top_right_feature =
                GenerateFeature(top_right_corner_3d, T_wc, camera_parameters_->intrinsics.at(camera_index_).GetK(),
                                top_right_corner_desc);
            const vslam::Feature bottom_right_feature =
                GenerateFeature(bottom_right_corner_3d, T_wc, camera_parameters_->intrinsics.at(camera_index_).GetK(),
                                bottom_right_corner_desc);
            vslam::Features features;
            features.emplace_back(top_left_feature);
            features.emplace_back(bottom_left_feature);
            features.emplace_back(top_right_feature);
            features.emplace_back(bottom_right_feature);

            // generate image
            cv::Mat img(camera_parameters_->intrinsics.at(camera_index_).GetHeight(),
                        camera_parameters_->intrinsics.at(camera_index_).GetWidth(), CV_8UC1, cv::Scalar(255));
            img.at<uint8_t>(top_left_feature.image_point)     = 0;
            img.at<uint8_t>(bottom_left_feature.image_point)  = 0;
            img.at<uint8_t>(top_right_feature.image_point)    = 0;
            img.at<uint8_t>(bottom_right_feature.image_point) = 0;

            vslam::Image image(img.cols, img.rows, vslam::Image::Encoding::GRAYSCALE);
            image.SetTriggerStamp(holo::Timestamp(i));
            /// @todo(Feng. Li 2020-11-19) How to set a cv::Mat to a holo::Image directly?

            // store image and features and camera pose
            images_and_features_and_pose_.emplace_back(image, features, T_wc);
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
        return vslam::Feature(cv::Point2f(pt_img[0], pt_img[1]), d, ptn, camera_index_);
    }

    /**
     * @brief back project a 2d point to 3d space in "world" frame
     *
     * @param[in] point 2d point on image
     * @param[in] depth depth of the point in camera
     * @param[in] pose pose which can transform a point from camera to "world"
     * @param[in] K camera intrinsic matrix
     * @return 3d point in "world" frame
     */
    vslam::Point3 BackProject(const vslam::Point2& point, const vslam::Scalar depth, const vslam::Pose3& pose,
                              const vslam::Matrix3& K)
    {
        const vslam::Point3 ptc = vslam::Point3((K.Inverse() * point.Homogeneous()) * depth);
        return pose * ptc;
    }

    /**
     * @brief brief utility function to sort tracks w.r.t their oldest feature position
     *
     * @param[in] left left feature track
     * @param[in] right right feature track
     * @return true if left feture track is at left top of the right feature track, otherwise false
     */
    static bool SortTracks(const vslam::FeatureTrack& left, const vslam::FeatureTrack& right)
    {
        const auto& point1 = left.OldestMeasurement().second.begin()->second.image_point;
        const auto& point2 = right.OldestMeasurement().second.begin()->second.image_point;

        if (point1.x > point2.x)
        {
            return false;
        }
        else if (point1.x == point2.x)
        {
            if (point1.y > point2.y)
            {
                return false;
            }
        }

        return true;
    }

protected:
    /// @brief camera id
    uint16_t camera_index_;

    /// @brief camera parameters
    vslam::CameraParameters::Ptr camera_parameters_;

    /// @brief tracker parameters
    const vslam::Tracker::Parameters parameters_;

    /// @brief a set of images and features extracted on that image and camera pose
    std::vector<std::tuple<vslam::Image, vslam::Features, vslam::Pose3> > images_and_features_and_pose_;

    /// @brief landmarks position
    std::vector<vslam::Point3> points_;
};  // TestFixture
