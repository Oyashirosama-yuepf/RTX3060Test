/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file visualizer.h
 * @brief this file defines visualizer for semantic slam
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @author Changxi Cheng (chengchangxi&holomatic.com)
 * @date 2021-05-14
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_VISUALIZER_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_VISUALIZER_H_

#include <holo/localization/vision/vslam/semantic/common_types.h>

#include <opencv2/opencv.hpp>
#include <unordered_map>

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
/**
 * @brief visualizer
 *
 */
class Visualizer
{
public:
    using Ptr      = std::shared_ptr<Visualizer>;
    using ConstPtr = std::shared_ptr<const Visualizer>;

    /**
     * @brief
     *
     */
    struct Parameters
    {
        BirdviewParameters birdview_parameters;
        bool_t             enable_step;

        /**
         * @brief Construct a new Parameters object
         *
         * @param _birdview_parameters
         * @param _enable_step
         */
        Parameters(const BirdviewParameters& _birdview_parameters, const bool_t _enable_step = false)
          : birdview_parameters(_birdview_parameters), enable_step(_enable_step)
        {
        }

        /**
         * @brief
         *
         * @return Parameters
         */
        static Parameters GenerateExample()
        {
            return Parameters(BirdviewParameters::GenerateExample(), false);
        }
    };

    /**
     * @brief Construct a new Visualizer object
     *
     * @param parameters
     */
    Visualizer(const Parameters& parameters);

    /**
     * @brief
     *
     * @param old_tracks
     * @param new_tracks
     * @param frame_id
     * @param plane_id
     */
    void ShowTracking(const std::vector<ParkingSlotTrack>& old_tracks, const std::vector<ParkingSlotTrack>& new_tracks,
                      int64_t frame_id, int64_t plane_id) const;

    /**
     * @brief Construct a new Show object
     *
     * @param left
     * @param right
     * @param dist
     * @param result
     */
    void ShowMatching(const std::vector<ParkingSlotType>& left, const std::vector<ParkingSlotType>& right,
                      const MatrixX& dist, const std::vector<int32_t>& result) const;

private:
    /**
     * @brief
     *
     * @param in
     * @param downscale
     * @return ParkingSlotType
     */
    ParkingSlotType convertToImage(const ParkingSlotType& in, const Scalar downscale = 1.0) const;

    /**
     * @brief
     *
     * @param image
     * @param offset
     * @param parking_slot
     * @param index
     * @param color
     */
    void drawParkingSlot(cv::Mat& image, const cv::Point2f& offset, const ParkingSlotType& ps, const int64_t index,
                         const cv::Scalar& color) const;

    /**
     * @brief
     *
     * @param in
     * @return cv::Point2f
     */
    cv::Point2f toCvPoint(const Point3& in) const
    {
        return cv::Point2f(in.GetX(), in.GetY());
    }

    Parameters parameters_;
};

}  // namespace semantic

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_VISUALIZER_H_
