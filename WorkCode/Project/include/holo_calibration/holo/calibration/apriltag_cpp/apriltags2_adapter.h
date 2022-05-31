/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file apriltags2_adapter.h
 * @brief This header file defines apriltag adapter.
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-11-03"
 */

#ifndef HOLO_CALIBRATION_APRILTAG_CPP_APRILTAGS2_ADAPTER_H_
#define HOLO_CALIBRATION_APRILTAG_CPP_APRILTAGS2_ADAPTER_H_

#include <memory>
#include <string>
#include <vector>

#include <apriltag.h>
#include <tag16h5.h>
#include <tag25h9.h>
#include <tag36h11.h>
#include <tag36h9.h>
#include <opencv2/opencv.hpp>

#include <holo/calibration/apriltag_cpp/tag_detection.h>
#include <holo/core/types.h>

namespace AprilTags2
{
/*
 * This is a class to wrap AprilTags2 detector in C++ style
 */
class AprilTags2Adapter
{
public:
    typedef holo::float64_t                          Scalar;
    typedef std::shared_ptr<AprilTags2Adapter>       Ptr;
    typedef std::shared_ptr<const AprilTags2Adapter> ConstPtr;
    typedef image_u8_t                               ApriltagImage;
    typedef zarray_t                                 ApriltagArray;
    /*
     * @brief disable default constructor
     */
    AprilTags2Adapter() = delete;

    /*
     * @brief Construct a new April Tags 2 Adapter object
     *
     * @param[in] family_name apriltag family name to be used
     * @param[in] num_threads number of threads to be used in quad detection
     * @param[in] down_sampling image down_sampling ratio: 1.0, 1.5, 2, 3, 4
     * @param[in] image_filter_sigma sigma of gaussian filter
     * @param[in] refine_edges whether refine edges
     * @param[in] decode_sharpening sharpening done to decoded images
     * @param[in] debug whether output debug information
     * @param[in] copy_homography whether copy homography matrix
     */
    AprilTags2Adapter(std::string const& family_name, uint16_t const num_threads = 1, Scalar const down_sampling = 1.0,
                      Scalar const image_filter_sigma = 0.0, bool const refine_edges = true,
                      Scalar const decode_sharpening = 0.25, bool const debug = false,
                      bool const copy_homography = false);

    /*
     * @brief destructor
     */
    virtual ~AprilTags2Adapter();

    /*
     * @brief set number of threads for decoding
     */
    void SetNumThreads(uint16_t const& num_threads);

    /*
     * @brief set ratio of down sampling, only support 1.0, 1.5, 2, 3, 4
     */
    void SetDownSamplingRatio(Scalar const& down_sampling);

    /*
     * @brief set sigma for image filter
     */
    void SetFilterSigma(Scalar const& image_filter_sigma);

    /*
     * @brief set refine edge flag
     */
    void SetRefineEdge(bool const& refine_edges);

    /*
     * @brief Set the Decode Sharpening object
     *
     * @param[in] decode_sharpening
     */
    void SetDecodeSharpening(Scalar const& decode_sharpening);

    /*
     * @brief set debug flag
     */
    void SetDebug(bool const& debug);

    /*
     * @brief set copy homography matrix
     *        if need, each TagDetection will contain a valid homography matrix
     *        else, homography matrix will be zero matrix
     */
    void SetCopyHomography(bool const& copy_homography);

    /*
     * @brief extract tags from image
     * @param[in] gray_image input image to be processed
     * @return TagDetections
     */
    std::vector<AprilTags2::TagDetection> ExtractTags(cv::Mat const& gray_image);

protected:
    /*
     * @biref init apriltag family
     */
    void initTagFamily();

private:
    /*
     * @brief apriltag family name
     */
    std::string family_name_;

    /*
     * @brief apriltag family object
     */
    apriltag_family_t* apriltag_family_;

    /*
     * @brief apriltag detector
     */
    apriltag_detector_t* apriltag_detector_;

    /*
     * @brief whether need copy homography matrix
     * @detial homography matrix is computed by tagdetector,
     *         if do not use in algorithm, set it false will reduce time consumption
     */
    bool copy_homography_;

};  // AprilTags2Adapter
}  // namespace AprilTags2

#endif
