/*!
 * \brief visualizer class cpp file for offline mapping
 * \author Feng. Li, lifeng@holomatic.com
 * \date Mar-22-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/mapping/visualizer.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
namespace mapping
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat Visualizer::VisualizeTracks(const Frame& frame, const uint16_t camera_index,
                                    const IntrinsicBaseTypePtr& intrinsic, const IndexedTracks& track_database) const
{
    auto gray_scale = frame.multi_camera_data.at(camera_index).image;

    if (gray_scale.empty())
    {
        // trying to load image from disk
        const auto& image_name = frame.multi_camera_data.at(camera_index).image_name;
        gray_scale             = cv::imread(image_name, cv::IMREAD_GRAYSCALE);
    }

    if (gray_scale.empty())
    {
        LOG(ERROR) << "VisualizeTracks --- frame " << frame.frame_id << " has no image!";
        throw std::runtime_error("VisualizeTracks --- invalid frame.\n");
    }

    if (track_database.empty())
    {
        throw std::runtime_error("VisualizeTracks --- track_database is empty.\n");
    }

    // convert image to BGR to draw tracks
    cv::Mat new_image;
    cv::cvtColor(gray_scale, new_image, CV_GRAY2BGR);

    // retrieve all features and associated landmark ids
    const auto& features              = frame.multi_camera_data.at(camera_index).features;
    const auto& lm_ids                = frame.multi_camera_data.at(camera_index).associated_landmarks;
    const auto& frame_id              = frame.frame_id;
    const auto& T_wc                  = frame.multi_camera_data.at(camera_index).pose;
    uint64_t    optimized_feature_num = 0;

    // draw all features extracted on this image
    for (size_t i = 0; i < features.size(); i++)
    {
        // draw track position in current new_image
        const auto& cv_m = features.at(i).image_point;
        cv::circle(new_image, cv_m, 3, cv::Scalar(0, 255, 0));  // green

        // check if associated to a landmark
        const auto& lm_id = lm_ids.at(i);
        if (lm_id < 0 || !track_database.count(lm_id))
        {
            continue;
        }

        optimized_feature_num++;

        // retrieve associated track
        const auto& track = track_database.at(lm_id);

        // draw landmark id
        cv::putText(new_image, std::to_string(lm_id), cv_m + cv::Point2f(0, -3), 1, 1, cv::Scalar(0, 255, 0));

        // draw projection
        const Point3 pt_w = holo::localization::HoloGtsam::Convert(track.GetLandmark()->Point());
        const Point3 ptc  = T_wc.Inverse() * pt_w;
        Point2       prediction;
        intrinsic->Project(ptc, prediction);

        if (ptc.GetX() < 0)
        {
            const cv::Point2f offset(2, 2);
            cv::rectangle(new_image, cv_m - offset, cv_m + offset, cv::Scalar(255, 0, 0));
        }
        else
        {
            const cv::Point2f cv_p(prediction.GetX(), prediction.GetY());
            // draw on new_image
            cv::circle(new_image, cv_p, 5, cv::Scalar(0, 0, 255));  // red
            cv::line(new_image, cv_m, cv_p, cv::Scalar(255, 255, 0), 1);
        }

        // draw track path if any
        if (track.Length() > 1u)
        {
            auto measurements = track.Measurements();
            std::sort(measurements.begin(), measurements.end(),
                      [](const FeatureTrack::Measurement& m0, const FeatureTrack::Measurement& m1) {
                          return m0.first < m1.first;
                      });

            for (uint64_t i = 0; i < track.Length() - 1; i++)
            {
                if (measurements.at(i).first >= frame_id)
                {
                    break;
                }

                cv::line(new_image, measurements.at(i).second.at(camera_index).image_point,
                         measurements.at(i + 1).second.at(camera_index).image_point,
                         cv::Scalar(0, 255, 255));  // yellow
            }
        }
    }

    // draw statistics info
    std::stringstream ss;
    ss << "frame_id = " << frame_id;
    cv::putText(new_image, ss.str(), cv::Point2f(10, 30), 1, 1, cv::Scalar(0, 0, 255));  // red

    std::stringstream ss1;
    ss1 << "#_of_observed_landmarks = " << optimized_feature_num;
    cv::putText(new_image, ss1.str(), cv::Point2f(10, 60), 1, 1, cv::Scalar(0, 0, 255));  // red

    return new_image;
}

#ifdef HOLO_VISUALIZE_WITH_PCL
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::DrawLine(const Point3& start, const Point3& end, uint8_t r, uint8_t g, uint8_t b,
                          const PointCloudRGB::Ptr& point_cloud)
{
    float64_t start_x = start.GetX();
    float64_t start_y = start.GetY();
    float64_t start_z = start.GetZ();

    float64_t end_x = end.GetX();
    float64_t end_y = end.GetY();
    float64_t end_z = end.GetZ();

    float64_t inc_x = (end_x - start_x) / 200.0f;
    float64_t inc_y = (end_y - start_y) / 200.0f;
    float64_t inc_z = (end_z - start_z) / 200.0f;
    for (float64_t i = 0; i < 200; i += 1)
    {
        float64_t x = start_x + i * inc_x;
        float64_t y = start_y + i * inc_y;
        float64_t z = start_z + i * inc_z;
        PointRGBT pt(r, g, b);
        pt.x = x / 10;
        pt.y = y / 10;
        pt.z = z / 10;
        point_cloud->points.push_back(pt);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::DrawLandmarks(const std::unordered_map<uint64_t, FeatureTrack>& indexed_tracks,
                               const std::vector<int64_t>& ids, bool draw_local_map)
{
    PointCloudRGB::Ptr new_point_cloud(new PointCloudRGB);
    for (size_t i = 0; i < ids.size(); i++)
    {
        const auto& id = ids.at(i);

        if (id < 0 || !indexed_tracks.count(id))
        {
            continue;
        }

        const auto& point = indexed_tracks.at(id).GetLandmark()->Point();
        PointRGBT   p(255, 255, 255);
        p.x = (point.x() / 10) + 12.0;
        p.y = (point.y() / 10) - 7.0;
        p.z = point.z() / 10;
        if (draw_local_map)
        {
            p.x = (point.x() / 10) - 12.0;
            p.y = (point.y() / 10) - 3.0;
        }
        point_cloud_->points.push_back(p);
        if (draw_local_map)
        {
            std::pair<float, float> x_y = std::make_pair(p.x, p.y);
            if (local_map_landmarks.count(x_y))
            {
                local_map_landmarks[x_y] = p.z;
            }
            else
            {
                local_map_landmarks.emplace(std::make_pair(p.x, p.y), p.z);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::DrawCamera(const Pose3& pose, uint8_t r, uint8_t g, uint8_t b, bool draw_local_map)
{
    Pose3  global_pose(pose.GetRotation(), Point3(pose.GetX() + 120, pose.GetY() - 70, pose.GetZ()));
    Point3 inner_vertex0 = global_pose * Point3(0.2, 0.2, 0);
    Point3 inner_vertex1 = global_pose * Point3(-0.2, 0.2, 0);
    Point3 inner_vertex2 = global_pose * Point3(0.2, -0.2, 0);
    Point3 inner_vertex3 = global_pose * Point3(-0.2, -0.2, 0);

    Point3 outer_vertex0 = global_pose * Point3(0.4, 0.4, 0.2);
    Point3 outer_vertex1 = global_pose * Point3(-0.4, 0.4, 0.2);
    Point3 outer_vertex2 = global_pose * Point3(0.4, -0.4, 0.2);
    Point3 outer_vertex3 = global_pose * Point3(-0.4, -0.4, 0.2);
    if (draw_local_map)
    {
        Pose3 local_pose(pose.GetRotation(), Point3(pose.GetX() - 120, pose.GetY() - 30, pose.GetZ()));
        inner_vertex0 = local_pose * Point3(0.2, 0.2, 0);
        inner_vertex1 = local_pose * Point3(-0.2, 0.2, 0);
        inner_vertex2 = local_pose * Point3(0.2, -0.2, 0);
        inner_vertex3 = local_pose * Point3(-0.2, -0.2, 0);

        outer_vertex0 = local_pose * Point3(0.4, 0.4, 0.2);
        outer_vertex1 = local_pose * Point3(-0.4, 0.4, 0.2);
        outer_vertex2 = local_pose * Point3(0.4, -0.4, 0.2);
        outer_vertex3 = local_pose * Point3(-0.4, -0.4, 0.2);
    }

    PointCloudRGB::Ptr new_point_cloud(new PointCloudRGB);

    DrawLine(inner_vertex0, inner_vertex1, r, g, b, new_point_cloud);
    DrawLine(inner_vertex0, inner_vertex2, r, g, b, new_point_cloud);
    DrawLine(inner_vertex1, inner_vertex3, r, g, b, new_point_cloud);
    DrawLine(inner_vertex2, inner_vertex3, r, g, b, new_point_cloud);

    DrawLine(outer_vertex0, outer_vertex1, r, g, b, new_point_cloud);
    DrawLine(outer_vertex0, outer_vertex2, r, g, b, new_point_cloud);
    DrawLine(outer_vertex1, outer_vertex3, r, g, b, new_point_cloud);
    DrawLine(outer_vertex2, outer_vertex3, r, g, b, new_point_cloud);

    DrawLine(inner_vertex0, outer_vertex0, r, g, b, new_point_cloud);
    DrawLine(inner_vertex1, outer_vertex1, r, g, b, new_point_cloud);
    DrawLine(inner_vertex2, outer_vertex2, r, g, b, new_point_cloud);
    DrawLine(inner_vertex3, outer_vertex3, r, g, b, new_point_cloud);

    camera_cloud_ = new_point_cloud;
}

void Visualizer::DrawTrajectory(const Pose3& pose, uint8_t r, uint8_t g, uint8_t b, bool draw_local_map)
{
    PointRGBT pt(r, g, b);
    pt.x = (pose.GetTranslation().GetX() / 10) + 12.0;
    pt.y = (pose.GetTranslation().GetY() / 10) - 7.0;
    pt.z = pose.GetTranslation().GetZ() / 10;
    if (draw_local_map)
    {
        pt.x = (pose.GetTranslation().GetX() / 10) - 12.0;
        pt.y = (pose.GetTranslation().GetY() / 10) - 3.0;
    }
    poses_cloud_->points.push_back(pt);
    if (draw_local_map)
    {
        std::pair<float, float> x_y = std::make_pair(pt.x, pt.y);
        if (local_map_trajectory.count(x_y))
        {
            local_map_trajectory[x_y] = pt.z;
        }
        else
        {
            local_map_trajectory.emplace(std::make_pair(pt.x, pt.y), pt.z);
        }
    }
}

void Visualizer::DrawLoop(const Pose3& train_pose, const Pose3& query_pose, uint8_t r, uint8_t g, uint8_t b,
                          bool draw_local_map)
{
    auto start = Point3(train_pose.GetX() + 120, train_pose.GetY() - 70, train_pose.GetZ());
    auto end   = Point3(query_pose.GetX() + 120, query_pose.GetY() - 70, query_pose.GetZ());
    if (draw_local_map)
    {
        start = Point3(train_pose.GetX() + 120, train_pose.GetY() - 70, train_pose.GetZ());
        end   = Point3(query_pose.GetX() - 120, query_pose.GetY() - 30, query_pose.GetZ());
    }
    DrawLine(start, end, r, g, b, loop_cloud_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::EraseLocalMap()
{
    // erase landmarks
    PointCloudRGB::Ptr new_point_cloud(new PointCloudRGB);
    std::vector<int>   point_retain_index;
    uint64_t           point_index = 0;
    for (auto it = point_cloud_->points.begin(); it != point_cloud_->points.end(); it++)
    {
        auto                    global_landmark = *it;
        std::pair<float, float> global_x_y      = std::make_pair(global_landmark.x, global_landmark.y);
        if (local_map_landmarks.count(global_x_y) && local_map_landmarks.at(global_x_y) == global_landmark.z)
        {
            point_index++;
            continue;
        }
        else
        {
            point_retain_index.push_back(point_index);
            point_index++;
        }
    }
    pcl::copyPointCloud(*point_cloud_, point_retain_index, *new_point_cloud);

    // erase trajectory
    PointCloudRGB::Ptr new_poses_cloud(new PointCloudRGB);
    std::vector<int>   pose_retain_index;
    uint64_t           pose_index = 0;
    for (auto it = poses_cloud_->points.begin(); it != poses_cloud_->points.end(); it++)
    {
        auto                    global_trajectory = *it;
        std::pair<float, float> global_x_y        = std::make_pair(global_trajectory.x, global_trajectory.y);
        if (local_map_trajectory.count(global_x_y) && local_map_trajectory.at(global_x_y) == global_trajectory.z)
        {
            pose_index++;
            continue;
        }
        else
        {
            pose_retain_index.push_back(pose_index);
            pose_index++;
        }
    }
    pcl::copyPointCloud(*poses_cloud_, pose_retain_index, *new_poses_cloud);

    // erase local loop line
    PointCloudRGB::Ptr new_loop_cloud(new PointCloudRGB);

    point_cloud_ = new_point_cloud;
    poses_cloud_ = new_poses_cloud;
    loop_cloud_  = new_loop_cloud;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::ClearLocalMapRecord()
{
    local_map_landmarks.clear();

    local_map_trajectory.clear();
}

}  // namespace mapping
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
