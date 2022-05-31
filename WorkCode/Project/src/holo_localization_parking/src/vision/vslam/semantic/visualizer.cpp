/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file visualizer.cpp
 * @brief this file defines visualizer for semantic slam
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @date 2021-05-14
 */

#include <holo/localization/vision/vslam/semantic/visualizer.h>

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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Visualizer::Visualizer(const Parameters& parameters) : parameters_(parameters)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::ShowTracking(const std::vector<ParkingSlotTrack>& old_tracks,
                              const std::vector<ParkingSlotTrack>& new_tracks, int64_t frame_id, int64_t plane_id) const
{
    const Scalar downscale = 1.5;

    // create image dimension
    size_t dim = 2000u;
    {
        const Point3 trans = parameters_.birdview_parameters.bEg.GetTranslation();

        dim = 2 * std::round(std::max(std::fabs(trans.GetX()), std::fabs(trans.GetY())) /
                             parameters_.birdview_parameters.pixel_per_meter);
    }
    const size_t      rows       = dim;
    const size_t      cols       = dim * 2;
    const cv::Point2f offset[2u] = {cv::Point2f(0.0f, 0.0f), cv::Point2f(cols - dim, 0.0f)};

    // create whiteboard
    cv::Mat image(rows, cols, CV_8UC3, cv::Scalar(255, 255, 255));

    // draw tracks (left -> old tracks, right -> new tracks)
    std::unordered_map<size_t, cv::Point2f> track_id_to_center;
    for (size_t i = 0u; i < 2u; ++i)
    {
        const auto& tracks = (i == 0) ? old_tracks : new_tracks;
        for (const auto& track : tracks)
        {
            const cv::Scalar      color(i * 255, 0, (1 - i) * 255);
            const ParkingSlotType ps_on_image = convertToImage(track.measurements.back().second.second, downscale);
            drawParkingSlot(image, offset[i], ps_on_image, track.id, color);

            // record track id
            if (i == 0)
            {
                const auto center_point      = 0.25 * (ps_on_image.vertices[0] + ps_on_image.vertices[1] +
                                                  ps_on_image.vertices[2] + ps_on_image.vertices[3]);
                track_id_to_center[track.id] = toCvPoint(center_point) + offset[i];
            }
            else if (i == 1)
            {
                if (track_id_to_center.count(track.id))
                {
                    // draw connection between tracks
                    const auto center_point = 0.25 * (ps_on_image.vertices[0] + ps_on_image.vertices[1] +
                                                      ps_on_image.vertices[2] + ps_on_image.vertices[3]);
                    cv::line(image, track_id_to_center.at(track.id), toCvPoint(center_point) + offset[i],
                             cv::Scalar(0, 0, 128), 2);
                }
            }
        }
    }

    // draw meta data
    {
        std::stringstream ss;
        ss << "frame id = " << frame_id << ", plane id = " << plane_id;
        cv::putText(image, ss.str(), cv::Point2f(dim - 100, 40), 1, 2, cv::Scalar(0, 255, 0));
        cv::putText(image, "old", cv::Point2f(dim / 2.0, 40), 1, 2, cv::Scalar(0, 0, 0));
        cv::putText(image, "new", cv::Point2f(dim + dim / 2.0, 40), 1, 2, cv::Scalar(0, 0, 0));
    }

    cv::namedWindow("parkingslots", CV_WINDOW_NORMAL);
    cv::imshow("parkingslots", image);
    if (parameters_.enable_step)
    {
        cv::waitKey();
    }
    else
    {
        cv::waitKey(100);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::ShowMatching(const std::vector<ParkingSlotType>& left, const std::vector<ParkingSlotType>& right,
                              const MatrixX& dist, const std::vector<int32_t>& result) const
{
    const Scalar downscale = 1.0;

    // create image dimension
    size_t dim = 1000u;
    {
        // const Point3 trans = parameters_.birdview_parameters.bEg.GetTranslation();
        static Pose3 gEa(Rot3::Rx(holo::Radian(180.0)), Point3(-6.0, 6.0, 0.0));
        const Point3 trans = (parameters_.birdview_parameters.bEg * gEa).GetTranslation();

        dim = 2 * std::round(std::max(std::fabs(trans.GetX()), std::fabs(trans.GetY())) /
                             parameters_.birdview_parameters.pixel_per_meter);
    }
    dim                          = 2000u;
    const size_t      rows       = dim;
    const size_t      cols       = dim * 2;
    const cv::Point2f offset[2u] = {cv::Point2f(0.0f, 0.0f), cv::Point2f(cols - dim, 0.0f)};

    // create whiteboard
    cv::Mat    image(rows, cols, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Scalar text_color(0, 0, 0);
    cv::putText(image, "RED: (old, prediction, rows);     Blue: (new, measurement, cols)", cv::Point2f(100.0, 20.0), 1,
                1, text_color);

    // draw parkingslot from two groups
    for (size_t i = 0; i < 2u; ++i)
    {
        const auto&      slots = (i == 0) ? left : right;
        const cv::Scalar color(i * 255, 0, (1 - i) * 255);

        size_t j = 0;
        for (const auto& ps : slots)
        {
            if (!ps.is_valid)
            {
                LOG(FATAL) << "terrible, we have bad ps";
            }
            const auto ps_on_image = convertToImage(ps, downscale);
            drawParkingSlot(image, offset[i], ps_on_image, j++, color);
        }
    }

    // draw dist matrix
    cv::putText(image, "distance matrix", cv::Point2f(20.0, dim - (dist.GetRows() + 1) * 20.0), 1, 1, text_color);
    for (size_t r = 0u; r < dist.GetRows(); ++r)
    {
        std::stringstream ss;
        for (size_t c = 0u; c < dist.GetCols(); ++c)
        {
            ss << dist.At(r, c) << " ";
        }
        cv::putText(image, ss.str(), cv::Point2f(20.0, dim - (dist.GetRows() - r) * 20.0), 1, 1, text_color);
    }

    // draw result
    for (size_t i = 0u; i < result.size(); ++i)
    {
        if (result.at(i) < 0)
        {
            continue;
        }

        const auto ps1            = convertToImage(left.at(i), downscale);
        const auto ps2            = convertToImage(right.at(result.at(i)), downscale);
        Point3     center_vertex1 = 0.25 * (ps1.vertices[0] + ps1.vertices[1] + ps1.vertices[2] + ps1.vertices[3]);
        Point3     center_vertex2 = 0.25 * (ps2.vertices[0] + ps2.vertices[1] + ps2.vertices[2] + ps2.vertices[3]);
        cv::line(image, toCvPoint(center_vertex1) + offset[0], toCvPoint(center_vertex2) + offset[1],
                 cv::Scalar(0, 255, 0));
    }

    cv::namedWindow("data association", CV_WINDOW_NORMAL);
    cv::imshow("data association", image);
    if (parameters_.enable_step)
    {
        cv::waitKey();
    }
    else
    {
        cv::waitKey(100);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParkingSlotType Visualizer::convertToImage(const ParkingSlotType& in, const Scalar downscale) const
{
    ParkingSlotType out(in);

    // width and height
    out.width  = in.width / parameters_.birdview_parameters.pixel_per_meter / downscale;
    out.height = in.height / parameters_.birdview_parameters.pixel_per_meter / downscale;

    // @todo ignore angle

    // front vertices
    out.vertices[0u] = parameters_.birdview_parameters.convertToImage(in.vertices[0u], downscale);
    out.vertices[1u] = parameters_.birdview_parameters.convertToImage(in.vertices[1u], downscale);

    // rear vertices
    if (in.is_rear_vertex_available)
    {
        out.vertices[2u] = parameters_.birdview_parameters.convertToImage(in.vertices[2u], downscale);
        out.vertices[3u] = parameters_.birdview_parameters.convertToImage(in.vertices[3u], downscale);
    }

    // center vertex
    if (in.is_center_vertex_available)
    {
        out.center_vertex = parameters_.birdview_parameters.convertToImage(in.center_vertex, downscale);
    }

    // stopper vertices
    if (in.is_stopper_available)
    {
        out.stopper_vertices[0u] = parameters_.birdview_parameters.convertToImage(in.stopper_vertices[0u], downscale);
        out.stopper_vertices[1u] = parameters_.birdview_parameters.convertToImage(in.stopper_vertices[1u], downscale);
    }

    return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::drawParkingSlot(cv::Mat& image, const cv::Point2f& offset, const ParkingSlotType& ps,
                                 const int64_t index, const cv::Scalar& color) const
{
    // draw edge 1-2, 2-3, 3-0
    cv::line(image, toCvPoint(ps.vertices[1]) + offset, toCvPoint(ps.vertices[2]) + offset, color, 2);
    cv::line(image, toCvPoint(ps.vertices[2]) + offset, toCvPoint(ps.vertices[3]) + offset, color, 2);
    cv::line(image, toCvPoint(ps.vertices[3]) + offset, toCvPoint(ps.vertices[0]) + offset, color, 2);

    // draw entrance 0-1
    const cv::Scalar entrance_color(255, 255, 0);  // light blue
    cv::line(image, toCvPoint(ps.vertices[0]) + offset, toCvPoint(ps.vertices[1]) + offset, entrance_color, 2);

    // draw center
    const cv::Scalar center_color(0, 255, 0);  // red
    Point3           center_vertex = 0.25 * (ps.vertices[0] + ps.vertices[1] + ps.vertices[2] + ps.vertices[3]);
    cv::circle(image, toCvPoint(center_vertex) + offset, 5.0, cv::Scalar(0, 0, 255), 2);
    cv::circle(image, toCvPoint(ps.vertices[0]) + offset, 5.0, center_color, 2);
    cv::circle(image, toCvPoint(ps.vertices[1]) + offset, 5.0, center_color, 2);
    cv::circle(image, toCvPoint(ps.vertices[2]) + offset, 5.0, center_color, 2);
    cv::circle(image, toCvPoint(ps.vertices[3]) + offset, 5.0, center_color, 2);

    // draw track id
    std::stringstream ss;
    ss << "index = " << index;
    cv::putText(image, ss.str(), toCvPoint(ps.center_vertex) + offset, 1, 1, color);

    // draw world id if any (ground truth)
    ss.str("");
    ss << "world id = " << ps.id;
    cv::putText(image, ss.str(), toCvPoint(ps.center_vertex) + offset + cv::Point2f(0, 20), 1, 1, color);
}

}  // namespace semantic

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo
