/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file undistort_ocam_image.cpp
 * @brief undistort the input ocam image
 * @author Shuaijie Li @ lishuaijie@holomatic.com
 * @date 2021-07-23
 */

#include <glog/logging.h>

#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <holo/io/common/intrinsic.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <localization/vision/birdview/birdview_image_undistortion.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

using namespace holo::vision;

holo::int32_t main(int argc, char** argv)
{
    cxxopts::Options options("undistort ocam image", "ocam undistorter node");
    options.add_options()("help", "help message")("i,input_image_file",
                                                  "the absolute path of the ocam image that will be undistorted",
                                                  cxxopts::value<std::string>())(
        "o,output_image_file", "the absolute path of the undistorted image", cxxopts::value<std::string>())(
        "c,ocam_intrinsic_file", "the absolute path of the intrinsic file for the ocam image",
        cxxopts::value<std::string>())("w,width", "the width of the output image [pixel]",
                                       cxxopts::value<holo::uint16_t>())(
        "h,height", "the height of the output image [pixel]", cxxopts::value<holo::uint16_t>())(
        "x,cx", "the x coordinate of the principal point", cxxopts::value<holo::float64_t>())(
        "y,cy", "the y coordinate of the principal point", cxxopts::value<holo::float64_t>())(
        "m,fx", "the focal lenght in pixel of x axis", cxxopts::value<holo::float64_t>())(
        "n,fy", "the focal lenght in pixel of y axis", cxxopts::value<holo::float64_t>());

    options.parse(argc, argv);

    if (options.count("help"))
    {
        LOG(INFO) << options.help();
        return 0;
    }

    std::string const input_image_file = options["input_image_file"].as<std::string>();

    if (input_image_file.empty())
    {
        LOG(ERROR) << "the input image file is empty!!!";
        return -1;
    }

    cv::Mat const input_image = cv::imread(input_image_file);

    if (input_image.cols == 0u)
    {
        LOG(ERROR) << "failed to load image from the given path: " << input_image_file;
        return -2;
    }

    std::string const output_image_file = options["output_image_file"].as<std::string>();

    if (output_image_file.empty())
    {
        LOG(ERROR) << "the output image file is empty!!!";
        return -3;
    }

    std::string const ocam_intrinsic_file = options["ocam_intrinsic_file"].as<std::string>();

    if (ocam_intrinsic_file.empty())
    {
        LOG(ERROR) << "the ocam intrinsic file is empty!!!";
        return -4;
    }

    BirdviewImageUndistortion::IntrinsicType intrinsic;

    try
    {
        holo::yaml::Node                         intrinsic_node = holo::yaml::LoadFile(ocam_intrinsic_file);
        intrinsic = intrinsic_node.as<BirdviewImageUndistortion::IntrinsicType>();
    }
    catch (std::exception const& e)
    {
        LOG(ERROR) << "failed to load ocam intrinsic from " << ocam_intrinsic_file << ", error is " << e.what();
    }

    holo::uint16_t const width = options["width"].as<holo::uint16_t>();
    holo::uint16_t const height = options["height"].as<holo::uint16_t>();
    holo::float64_t const cx     = options["cx"].as<holo::float64_t>();
    holo::float64_t const cy     = options["cy"].as<holo::float64_t>();
    holo::float64_t const fx     = options["fx"].as<holo::float64_t>();
    holo::float64_t const fy     = options["fy"].as<holo::float64_t>();
    cv::Mat K = (cv::Mat_<double>(3u, 3u) << fx, 0.0, cx, 0.0, fy, cy, 0.0, 0.0, 1.0);
    LOG(INFO) << "output image width = " << width << "\n output image height = " << height << "\n K = " << K;
    BirdviewImageUndistortion undistorter(intrinsic, K, height, width);
    cv::Mat                   output_image;
    undistorter.Undistort(input_image, output_image);
    cv::imwrite(output_image_file, output_image);
    return 0;
}
