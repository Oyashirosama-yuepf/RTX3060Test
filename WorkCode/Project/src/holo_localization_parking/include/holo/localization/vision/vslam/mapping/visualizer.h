/*!
 * \brief visualizer class header file for offline mapping
 * \author Feng. Li, lifeng@holomatic.com
 * \date Mar-22-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_VISUALIZER_H
#define HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_VISUALIZER_H

#ifdef HOLO_VISUALIZE_WITH_PCL
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/visualization/cloud_viewer.h>
#endif

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/feature_track.h>
#include <holo/localization/vision/vslam/mapping/common_types.h>

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
/**
 * @ingroup localization
 * @brief visualizer class for offline mapping
 * @note The visualizer depends on OpenCV's gtk and pcl, please make sure the gtk of OpenCV and pcl
 *       in holo_3rdparty is enabled or manually enable it.
 */
class Visualizer
{
public:
    /// handy typedef
    typedef std::shared_ptr<Visualizer>                Ptr;
    typedef std::unordered_map<uint64_t, FeatureTrack> IndexedTracks;

    /**
     * @brief draw feature tracks
     */
    cv::Mat VisualizeTracks(const Frame& frame, const uint16_t camera_index, const IntrinsicBaseTypePtr& intrinsic,
                            const IndexedTracks& track_database) const;

#ifdef HOLO_VISUALIZE_WITH_PCL
    typedef pcl::PointXYZRGB           PointRGBT;
    typedef pcl::PointCloud<PointRGBT> PointCloudRGB;

    /**
     * @brief constructor
     */
    Visualizer(const std::string& window_name = "Holo Visual Mapping APP")
      : viewer_(window_name)
      , point_cloud_(new PointCloudRGB)
      , poses_cloud_(new PointCloudRGB)
      , loop_cloud_(new PointCloudRGB)
      , camera_cloud_(new PointCloudRGB)
      , all_(new PointCloudRGB)
    {
    }

    /**
     * @brief draw camera
     */
    void DrawCamera(const Pose3& pose, uint8_t r, uint8_t g, uint8_t b, bool draw_local_map = false);

    /**
     * @brief draw trajectory
     */
    void DrawTrajectory(const Pose3& pose, uint8_t r, uint8_t g, uint8_t b, bool draw_local_map = false);

    /**
     * @brief draw loop edge
     */
    void DrawLoop(const Pose3& train_pose, const Pose3& query_pose, uint8_t r, uint8_t g, uint8_t b,
                  bool draw_local_map = false);

    /**
     * @brief draw landmarks
     */
    void DrawLandmarks(const std::unordered_map<uint64_t, FeatureTrack>& indexed_tracks,
                       const std::vector<int64_t>& ids, bool draw_loacal_map = false);

    /**
     * @brief show all points
     */
    void Update()
    {
        *all_ = *poses_cloud_ + *loop_cloud_;
        *all_ = *all_ + *point_cloud_;
        *all_ = *all_ + *camera_cloud_;
        viewer_.showCloud(all_);
    }

    /**
     * @brief erase loacal map
     */
    void EraseLocalMap();

#endif

    /**
     * @brief clear record of landmark and trajectory in local map
     */
    void ClearLocalMapRecord();

    // the position of landmarks in local map
    std::unordered_map<std::pair<float, float>, float, pair_hash> local_map_landmarks;

    // the position of trajectory in local map
    std::unordered_map<std::pair<float, float>, float, pair_hash> local_map_trajectory;

#ifdef HOLO_VISUALIZE_WITH_PCL
protected:
    /**
     * @brief draw line between two point
     */
    void DrawLine(const Point3& start, const Point3& end, uint8_t r, uint8_t g, uint8_t b,
                  const PointCloudRGB::Ptr& point_cloud);

private:
    /// @brief pcl viewer
    pcl::visualization::CloudViewer viewer_;

    /// @brief record all mappoint
    PointCloudRGB::Ptr point_cloud_;

    /// @brief record trajectory
    PointCloudRGB::Ptr poses_cloud_;

    /// @brief record loop edge
    PointCloudRGB::Ptr loop_cloud_;

    /// @brief used to draw camera
    PointCloudRGB::Ptr camera_cloud_;

    /// @brief put all close together to show
    PointCloudRGB::Ptr all_;
#endif
};

}  // namespace mapping
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_MAPPING_VISUALIZER_H
