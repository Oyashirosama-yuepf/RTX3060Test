/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tag_detection.cc
 * @brief This header file defines tag detection.
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-11-03"
 */

#ifndef HOLO_CALIBRATION_APRILTAG_CPP_TAG_DETECTION_H_
#define HOLO_CALIBRATION_APRILTAG_CPP_TAG_DETECTION_H_

#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <utility>
#include <vector>

#include <holo/calibration/camera/field/types.h>

namespace AprilTags2
{
/*
 * @brief This class is to wrap the detection result from AprilTags2 lib in C++ style
 */
struct TagDetection
{
    typedef holo::bool_t    bool_t;
    typedef holo::float64_t Scalar;
    /**
     * @brief Construct a new Tag Detection object
     *
     */
    TagDetection();

    /**
     * @brief Constructor for manually creating tags in a world map
     *
     * @param[in] id input id
     */
    TagDetection(int64_t id);

    /**
     * @brief Is the detection good enough
     * @details It is valid when refine_pose in tagdetector is true or it is set to false and useless
     */
    bool_t good;

    /**
     * @brief What was the ID of the detected tag
     *
     */
    int64_t id;

    /**
     * @brief The hamming distance between the detected code and the true code
     *
     */
    int64_t hamming;

    /////////////// Fields below are filled in by TagDetector ///////////////

    /**
     * @brief Position (in fractional pixel coordinates) of the detection.
     * @details starting from the same corner of the tag.
     *          counter-clockwise: bottom left, bottom right, top right, top left
     */
    std::pair<Scalar, Scalar> p[4];

    /**
     * @brief Center of tag in pixel coordinates.
     *
     */
    std::pair<Scalar, Scalar> cxy;

    /**
     * @brief A 3x3 homography that computes pixel coordinates from tag-relative coordinates.
     * @details 'y' are pixel coordinates, 'x' are tag-relative coordinates. Tag coordinates span
     *          from (-1,-1) to (1,1). The orientation of the homography reflects the orientation
     *          of the target.
     */
    holo::numerics::MatrixT<Scalar, 3u, 3u> homography;

    /**
     * @brief Draw the detection within the supplied image, including boarders and tag ID.
     *
     * @param[in] image input image
     */
    void draw(cv::Mat& image) const;
};

}  // namespace AprilTags2

#endif
