/*!
 * \brief visualization in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Jan-15-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_VISUALIZER_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_VISUALIZER_H_

#include <thread>

#ifdef HOLO_VISUALIZE_WITH_PANGOLIN
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/pangolin.h>
#include <pangolin/plot/plotter.h>
#endif

#include <holo/localization/vision/vslam/feature_track.h>
#include <holo/localization/vision/vslam/json_saver.h>
#include <holo/localization/vision/vslam/semantic/data_association.h>
#include <holo/localization/vision/vslam/sliding_window_state.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup localization
 * @brief visualization with opencv
 * @note The visualizer depends on OpenCV's gtk, please make sure the gtk of OpenCV
 *       in holo_3rdparty is enabled or manually enable it.
 *       lishuaijie@holomatic.com(09-04-2019)
 */
class Visualizer
{
public:
    /**
     * @brief visualizer state
     * @details It contains all the variables used for visualization
     */
    struct VisualizerStates
    {
        /// @brief new sliding window state
        SlidingWindowState sliding_window_state;

        /// @brief all global mappoints
        std::unordered_map<uint64_t, MapPoint> indexed_mappoints;

        /// @brief all global parking slots
        std::unordered_map<uint64_t, ParkingSlotType> indexed_parking_slots;

        /// @brief new updated image
        std::vector<Image> images;

        /// @brief new matching result of visible slot map and current frame
        SlotMapFactorMeasurement sfm;

        /// @brief visiabel map in current state
        MapPtr visiable_map;

        VisualizerStates(const SlidingWindowState&                            _sliding_window_state,
                         const std::unordered_map<uint64_t, MapPoint>&        _indexed_mappoints,
                         const std::unordered_map<uint64_t, ParkingSlotType>& _indexed_parking_slots,
                         const std::vector<Image>& _images, const SlotMapFactorMeasurement& _sfm = {},
                         const MapPtr& _visiable_map = nullptr)
          : sliding_window_state(_sliding_window_state)
          , indexed_mappoints(_indexed_mappoints)
          , indexed_parking_slots(_indexed_parking_slots)
          , images(_images)
          , sfm(_sfm)
          , visiable_map(_visiable_map)
        {
        }
    };

    struct Parameters
    {
        /// @brief flag which indicate whether save image with track infos or not
        const bool save_image;

        /// @brief flat which indicate whether save factor graph to json file or not
        const bool save_graph;

        /// @brief directory inwhich the images and factor graph will be saved.
        const std::string folder_name;

        std::string window_name;      ///< window name
        Scalar      loop_rate;        ///< main loop rate in hz (1 / second)
        Size2d      window_position;  ///< main window position
        Size2d      window_size;      ///< opengl panel size
        Size2d      image_dimension;  ///< image dimension

        Scalar view_x, view_y, view_z, view_f;  ///< view port
        Scalar camera_size;                     ///< camera size
        Scalar line_width;                      ///< line width in panel
        Scalar point_size;                      ///< point size in panel
        bool   enable_camera_following;         ///< if follows camera
        bool   enable_show_keyframes;           ///< if show keyframes

        /// @brief constructor
        Parameters(const bool _save_image = false, const bool _save_graph = false,
                   const std::string& _folder_name = "/tmp",
                   const std::string& _window_name = "LocalizationParkingVisualization",
                   const Scalar& _loop_rate = 10.0, const Size2d& _window_position = Size2d(20, 20),
                   const Size2d& _window_size = Size2d(640, 360), const Size2d& _image_dimension = Size2d(1280, 720),
                   const Scalar& _view_x = -50.0, const Scalar& _view_y = 0.0, const Scalar& _view_z = 100,
                   const Scalar& _view_f = 1000.0, const Scalar& _camera_size = 2.0, const Scalar& _line_width = 3.0,
                   const Scalar& _point_size = 3.0, const bool _enable_camera_following = true,
                   const bool _enable_show_keyframes = false)
          : save_image(_save_image)
          , save_graph(_save_graph)
          , folder_name(_folder_name)
          , window_name(_window_name)
          , loop_rate(_loop_rate)
          , window_position(_window_position)
          , window_size(_window_size)
          , image_dimension(_image_dimension)
          , view_x(_view_x)
          , view_y(_view_y)
          , view_z(_view_z)
          , view_f(_view_f)
          , camera_size(_camera_size)
          , line_width(_line_width)
          , point_size(_point_size)
          , enable_camera_following(_enable_camera_following)
          , enable_show_keyframes(_enable_show_keyframes)
        {
        }

        /**
         * @brief output stream
         *
         */
        friend std::ostream& operator<<(std::ostream& os, const Parameters& params)
        {
            os << "VisualizerParameters:\n"
               << "save_image: " << params.save_image << "\n save_graph: " << params.save_graph
               << "\n folder_name: " << params.folder_name << "\n window_name: " << params.window_name
               << "\n loop_rate: " << params.loop_rate << "\n view_x: " << params.view_x
               << "\n view_y: " << params.view_y << "\n view_z: " << params.view_z << "\n view_f: " << params.view_f
               << "\n camera_size: " << params.camera_size << "\n line_width: " << params.line_width
               << "\n point_size: " << params.point_size
               << "\n enable_camera_following: " << params.enable_camera_following
               << "\n enable_show_keyframes: " << params.enable_show_keyframes
               << "\n window_position: " << params.window_position.GetCvType()
               << "\n window_size: " << params.window_size.GetCvType()
               << "\n image_dimension: " << params.image_dimension.GetCvType() << std::endl;
            return os;
        }

        /**
         * @brief load parameters from yaml
         *
         */
        static Parameters LoadFromYaml(const holo::yaml::Node& node);
    };

    /**
     * @brief define visualization status
     */
    enum class Status
    {
        PAUSE = 0,
        SPIN  = 1,
        STOP  = 2,
    };

    /**
     * @brief constructor
     */
    Visualizer(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters);

    /**
     * @brief destructor
     */
    ~Visualizer();

    /**
     * @brief set status to spin
     */
    void Spin()
    {
        status_ = Status::SPIN;
    }

    /**
     * @brief set status to pause
     * @details could be called by other thread and it only returns when the
     *          internal thread stops running
     */
    void Pause()
    {
        status_ = Status::PAUSE;

        while (IsInternalThreadRunning())
        {
            usleep(1e3);
        }
    }

    /**
     * @brief set status to stop
     * @details could be called by other thread and it only returns when the
     *          internal thread stops running
     */
    void Stop()
    {
        status_ = Status::STOP;

        while (IsInternalThreadRunning())
        {
            usleep(1e3);
        }
    }

    /// @brief get status
    Status GetStatus() const
    {
        return status_;
    }

    /// @brief in mapping mode, global indexed mappoints and parking slots will be constanly updated
    void UpdateGlobalMap(std::unordered_map<uint64_t, MapPoint>        indexed_mappoints,
                         std::unordered_map<uint64_t, ParkingSlotType> indexed_parking_slots)
    {
        if (!indexed_mappoints.empty())
        {
            global_indexed_mappoints_ = indexed_mappoints;
        }
        if (!indexed_parking_slots.empty())
        {
            global_indexed_parking_slots_ = indexed_parking_slots;
        }
    };

    /**
     * @brief process visualizer state
     */
    int32_t ProcessSlidingWindowState(const VisualizerStates& visualizer_states);

    /**
     * @brief set prebuilt parking slot map in localization mode
     */
    void SetPrebuiltSlotMap(const SlotMapPtr& prebuilt_slot_map);

    /**
     * @brief set prebuilt map in localization mode
     */
    void SetPrebuiltMap(const MapPtr& prebuilt_map);

private:
    /**
     * @brief check internal vio visualization state
     * @details variable "is_running" is set to be "true" at the beginning of
     *          the while loop inside the internal thread and be "false"
     *          at the end of the loop
     */
    bool IsInternalThreadRunning() const
    {
        return is_running_;
    }

    /**
     * @brief internal thread
     * @details implements the main pipeline of visualization
     */
    void InternalThreadFunction();

    /**
     * @brief draw all tracks which is tracked on current images
     *
     * @param tracker_state tracker state which contain lost of feature tracks
     * @param values optimized values
     * @param timestamp timestamp
     * @return images from multi camera with feature tracks' statistic information
     */
    std::vector<cv::Mat> DrawAllTracks(const Tracker::State& tracker_state, const Values& values,
                                       const Timestamp& timestamp) const;

    /**
     * @brief draw track's trace
     *
     * @param track processed feature track
     * @param image raw image, feature track's trajectory will be draw on this image
     * @param camera_index camera index does this image comes from
     * @return image with feature track's trajectory
     */
    cv::Mat DrawTrace(const FeatureTrack& track, const cv::Mat& image, const uint16_t camera_index) const;

    /**
     * @brief draw landmark projection
     *
     * @param track processed feature track
     * @param values optimized values
     * @param T_mc camera pose in vslam map frame
     * @param image feature track's projection information will be draw on this image
     * @param frame_id frame id
     * @param camera_index camera index does this image comes from
     * @return image with feature track's projection information
     */
    cv::Mat DrawProjectedLandmark(const FeatureTrack& track, const Values& values, const gtsam::Pose3& T_mc,
                                  const cv::Mat& image, const uint64_t frame_id, const uint16_t camera_index) const;

    /**
     * @brief draw statistics info
     *
     * @param frame_id frame id
     * @param timestamp timestamp
     * @param optimized_feature_num number of optimized features extracted on given image
     * @param image all statistics information will be draw on this image
     * @return image with statistics information
     */
    cv::Mat DrawStatisticsInfo(const uint64_t frame_id, const Timestamp& timestamp,
                               const uint64_t optimized_feature_num, const cv::Mat& image) const;

#ifdef HOLO_VISUALIZE_WITH_PANGOLIN
    /**
     * @brief draw map
     *
     * @details including frames in sliding window, point landmarks
     */
    void DrawMap();

    /**
     * @brief draw visiable map in current state
     *
     */
    void DrawVisiableMap();

    /**
     * @brief draw estimate trajectory
     *
     * @details it will call DrawTrajectory() internally
     */
    void DrawEstimateTrajectory();

    /**
     * @brief draw all parking slots
     *
     * @details including parking slots in global
     */
    void DrawParkingSlots();

    void DrawParkingSlotsAssociation();

    /**
     * @brief draw parking slot
     *
     * @details Draw a colored parking slot
     */
    void DrawParkingSlot(const ParkingSlotType& parking_slot, const Scalar r, const Scalar g, const Scalar b,
                         const Scalar line_width);

    /**
     * @brief utility function - draw trajectory opengl
     *
     * @param[in] traj trajectory
     * @param[in] r red (0~1)
     * @param[in] g green (0~1)
     * @param[in] b blue (0~1)
     */
    void DrawTrajectory(const std::vector<Pose3>& traj, const Scalar r, const Scalar g, const Scalar b) const;

    /**
     * @brief utility function - draw camera opengl
     *
     * @param[in] pose camera pose
     * @param[in] r red (0~1)
     * @param[in] g green (0~1)
     * @param[in] b blue (0~1)
     */
    void DrawCamera(const Pose3& pose, const Scalar r, const Scalar g, const Scalar b) const;

    /// @brief utility function - convert holo pose to opengl type
    pangolin::OpenGlMatrix ConvertHoloPoseToOpenGlPose(const Pose3& pose) const;

    /**
     * @brief check if button pushed then toggle, adjust plotter position and show text
     *
     * @details it will call AdjustPlotterPosition() and ShowSideText() internally
     *
     * @param[in] button
     * @param[in] view
     * @param[in] num_visible_plotter the number of visible plotter
     * @param[in] lable slide text
     */
    void ShowPlotter(pangolin::Var<bool>& button, pangolin::View& view, size_t& num_visible_plotters,
                     const std::string& lable);

    /**
     * @brief adjust plotter position
     *
     * @details it will call ComputePlotterBottomPosition() internally
     *
     * @param[in] view
     * @param[in] num_visible_plotter the number of visible plotter
     */
    void AdjustPlotterPosition(pangolin::View& view, size_t& num_visible_plotters);

    /**
     * @brief compute plotter bottom position
     *
     * @param[in] num_visible_plotter the number of visible plotter
     * @param[in] plotter_height height of plotter
     * return Scalar bottom position
     */
    Scalar ComputePlotterBottomPosition(const size_t& num_visible_plotters, const Scalar plotter_height);

    /**
     * @brief compute local mappoint color prameter
     *
     * @details color from matlab hsv
     *
     * @param[in] z depth of feature points
     * @return Point3 (r, g, b) r(0~1) g(0~1) b(0~1)
     */
    Point3 ComputeColor(const Scalar z) const;

    /**
     * @brief show text beside plotter
     *
     * @param[in] view
     * @param[in] text name of view
     */
    void ShowSideText(const pangolin::View& view, const std::string& text) const;

    /**
     * @brief get static text of time monitor
     *
     * @details string type text to gltext
     *
     * @param[in] text static text
     * @return pangolin::GlText gl type text
     */
    pangolin::GlText GetStaticText(const std::string& text) const;

#endif

    /// @brief parameters
    Parameters parameters_;

    /// @brief shared_ptr of camera parameters
    CameraParameters::Ptr camera_parameters_;

    /// @brief peocessed variable in the newest updated visualzer state
    Tracker::State     newest_updated_tracker_state_;  ///< tracker state
    Values             newest_updated_values_;         ///< values
    FactorGraph        newest_updated_factor_graph_;   ///< factor graph
    Timestamp          newest_updated_timestamp_;      ///< timestamp
    std::vector<Image> newest_updated_images_;         ///< images

    std::atomic<Status>                           status_;                        ///< status
    std::atomic<bool>                             is_running_;                    ///< internal thread state
    std::atomic<bool>                             is_image_updated_;              ///< image rendering flag
    bool                                          is_state_updated_;              ///< if state updated
    std::vector<Pose3>                            es_traj_;                       ///< estimated camera trajectory
    SlidingWindowState                            sliding_window_state_;          ///< sliding window state
    std::unordered_map<uint64_t, MapPoint>        global_indexed_mappoints_;      ///< all global mappoints
    std::unordered_map<uint64_t, ParkingSlotType> global_indexed_parking_slots_;  ///< all global parking slots

    std::shared_ptr<std::thread> thread_ptr_;  ///< internal thread pointer
    std::mutex                   mutex_;       ///< multi-thread supporting

    SlotMapFactorMeasurement sfm_;  ///< the association result of parking slots

    MapPtr visiable_map_;  ///< visiable map in current state

};  // class Visualizer

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_VISUALIZER_H_
