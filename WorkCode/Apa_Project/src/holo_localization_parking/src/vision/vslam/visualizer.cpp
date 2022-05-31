/*!
 * \brief visualization in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Jan-15-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/visualizer.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Visualizer::Visualizer(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters)
  : parameters_(parameters)
  , camera_parameters_(camera_parameters)
  , status_(Status::PAUSE)
  , is_running_(false)
  , is_image_updated_(false)
{
    // reserve camera trajectory buffer
    es_traj_.reserve(10000);

    // start visualization thread
    thread_ptr_ = std::make_shared<std::thread>(std::bind(&Visualizer::InternalThreadFunction, this));
    pthread_setname_np(thread_ptr_->native_handle(), "VslamVisualizerThread");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Visualizer::~Visualizer()
{
    // stop the thread
    Stop();

    if (thread_ptr_)
    {
        thread_ptr_->join();
    }

    LOG(INFO) << "VSLAM Visualizer --- finished!";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Visualizer::Parameters Visualizer::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    const bool        save_image              = node["save_image"].as<bool>(false);
    const bool        save_graph              = node["save_graph"].as<bool>(false);
    const std::string folder_name             = node["folder_name"].as<std::string>("/tmp");
    const std::string window_name             = node["window_name"].as<std::string>("LocalizationParkingVisualization");
    const Scalar      loop_rate               = node["loop_rate"].as<Scalar>(10.0);
    const Scalar      view_x                  = node["view_x"].as<Scalar>(0.0);
    const Scalar      view_y                  = node["view_y"].as<Scalar>(-100.0);
    const Scalar      view_z                  = node["view_z"].as<Scalar>(-0.1);
    const Scalar      view_f                  = node["view_f"].as<Scalar>(1000.0);
    const Scalar      camera_size             = node["camera_size"].as<Scalar>(2.0);
    const Scalar      line_width              = node["line_width"].as<Scalar>(3.0);
    const Scalar      point_size              = node["point_size"].as<Scalar>(3.0);
    const bool        enable_camera_following = node["enable_camera_following"].as<bool>(true);
    const bool        enable_show_keyframes   = node["enable_show_keyframes"].as<bool>(false);

    const holo::yaml::Node window_position_node = node["window_position"].as<holo::yaml::Node>(holo::yaml::Node());
    const Size2d           window_position =
        Size2d(window_position_node[0].as<Scalar>(20), window_position_node[1].as<Scalar>(20));
    const holo::yaml::Node window_size_node = node["window_size"].as<holo::yaml::Node>(holo::yaml::Node());
    const Size2d window_size = Size2d(window_size_node[0].as<Scalar>(640), window_size_node[1].as<Scalar>(360));
    const holo::yaml::Node image_dimension_node = node["window_position"].as<holo::yaml::Node>(holo::yaml::Node());
    const Size2d           image_dimension =
        Size2d(image_dimension_node[0].as<Scalar>(1280), image_dimension_node[1].as<Scalar>(720));

    return Parameters(save_image, save_graph, folder_name, window_name, loop_rate, window_position, window_size,
                      image_dimension, view_x, view_y, view_z, view_f, camera_size, line_width, point_size,
                      enable_camera_following, enable_show_keyframes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t Visualizer::ProcessSlidingWindowState(const VisualizerStates& visualizer_states)
{
    std::unique_lock<std::mutex> lock(mutex_);
    sliding_window_state_         = visualizer_states.sliding_window_state;
    newest_updated_tracker_state_ = sliding_window_state_.static_tracker_state;
    newest_updated_factor_graph_  = sliding_window_state_.static_smoother.getFactors();
    newest_updated_values_        = sliding_window_state_.values;
    newest_updated_timestamp_     = sliding_window_state_.GetTimestamp();
    newest_updated_images_        = visualizer_states.images;
    is_image_updated_             = true;
    is_state_updated_             = true;
    es_traj_.push_back(sliding_window_state_.NewestVehicleState().Pose() * camera_parameters_->extrinsics.at(0));

    UpdateGlobalMap(visualizer_states.indexed_mappoints, visualizer_states.indexed_parking_slots);

    sfm_ = visualizer_states.sfm;

    visiable_map_ = visualizer_states.visiable_map;

    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<cv::Mat> Visualizer::DrawAllTracks(const Tracker::State& tracker_state, const Values& values,
                                               const Timestamp& timestamp) const
{
    std::vector<cv::Mat> result;
    result.reserve(newest_updated_images_.size());

    // get frame id
    const uint64_t frame_id = tracker_state.frame_id;

    // loop for all images, draw tracks one by one
    for (size_t camera_index = 0; camera_index < newest_updated_images_.size(); camera_index++)
    {
        const auto& image = newest_updated_images_.at(camera_index).GetCvType();
        cv::Mat     image_with_track;

        // convert image to BGR to draw tracks
        cv::cvtColor(image, image_with_track, CV_GRAY2BGR);

        // get camera pose
        const auto&        T_bc = camera_parameters_->extrinsics.at(camera_index);
        const gtsam::Pose3 T_mc =
            values.at(X(frame_id)).cast<gtsam::Pose3>() * holo::localization::HoloGtsam::Convert(T_bc);

        uint64_t optimized_feature_num = 0;
        for (const auto& track : tracker_state.tracks)
        {
            const auto& track_state = track.GetState();

            if (track_state == FeatureTrack::State::DEAD)
            {
                continue;
            }

            if (track_state == FeatureTrack::State::FRESH || track_state == FeatureTrack::State::LIVE ||
                track_state == FeatureTrack::State::BAD_AFTER_OPTIMIZATION)
            {
                optimized_feature_num++;
            }

            if (track.NewestMeasurement().first == frame_id && track.NewestMeasurement().second.count(camera_index))
            {
                image_with_track = DrawTrace(track, image_with_track, camera_index);
                image_with_track = DrawProjectedLandmark(track, values, T_mc, image_with_track, frame_id, camera_index);
            }
        }

        // draw statistics info
        result.emplace_back(DrawStatisticsInfo(frame_id, timestamp, optimized_feature_num, image_with_track));
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat Visualizer::DrawTrace(const FeatureTrack& track, const cv::Mat& image, const uint16_t camera_index) const
{
    cv::Mat           new_image = image;
    const cv::Point2f cv_m      = track.NewestMeasurement().second.at(camera_index).image_point;
    // draw track position in current new_image
    cv::circle(new_image, cv_m, 3, cv::Scalar(0, 255, 0));  // green

    // draw track path if any
    // @todo(Feng. Li. 2020-02-14) if a feature_track can be tracked by different camera, the trajectory of this track
    // can not be drawed like this, we should come back to fix it.
    if (track.Length() > 1u)
    {
        const uint64_t num = track.Length() - 1;

        for (uint64_t i = 0; i < num; i++)
        {
            // @todo(Feng. Li) be carefull!!! the i's measurement of this track may not contain given camera_index.
            cv::line(new_image, track.Measurements(i).second.at(camera_index).image_point,
                     track.Measurements(i + 1).second.at(camera_index).image_point, cv::Scalar(0, 255, 255));  // yellow
        }
    }

    return new_image;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat Visualizer::DrawProjectedLandmark(const FeatureTrack& track, const Values& values, const gtsam::Pose3& T_mc,
                                          const cv::Mat& image, const uint64_t frame_id,
                                          const uint16_t camera_index) const
{
    const auto& track_state = track.GetState();

    if (!track.GetLandmark())
    {
        return image;
    }

    cv::Mat           new_image   = image;
    const cv::Point2f cv_m        = track.NewestMeasurement().second.at(camera_index).image_point;
    const uint64_t    landmark_id = track.GetLandmark()->Id();

    if (!values.exists(L(landmark_id)))
    {
        return image;
    }

    // draw landmark id
    cv::putText(new_image, std::to_string(landmark_id), cv_m + cv::Point2f(0, -3), 1, 1, cv::Scalar(0, 255, 0));

    // draw projection
    gtsam::Point3 ptm = values.at(L(landmark_id)).cast<gtsam::Point3>();
    const Point3  pt_m(ptm.x(), ptm.y(), ptm.z());
    Point3        ptc = HoloGtsam::Convert(T_mc).Inverse() * pt_m;
    Point2        prediction;
    camera_parameters_->intrinsics.at(camera_index)->Project(ptc, prediction);

    if (ptc.GetZ() < 0)
    {
        std::stringstream ss;
        ss << "Landmark behind camera: track_id = " << track.Id() << ", landmark_id = " << landmark_id
           << ", frame_id = " << frame_id;
        LOG(ERROR) << ss.str();
        const cv::Point2f offset(2, 2);
        cv::rectangle(new_image, cv_m - offset, cv_m + offset, cv::Scalar(255, 0, 0));
    }
    else
    {
        cv::Scalar color(0, 0, 255);

        switch (track_state)
        {
            case FeatureTrack::State::BAD_BEFORE_OPTIMIZATION: {
                color = cv::Scalar(255, 0, 0);  // blue
                break;
            }
            case FeatureTrack::State::BAD_AFTER_OPTIMIZATION: {
                color = cv::Scalar(255, 0, 255);  // pink
                break;
            }
            default: {
                break;
            }
        }

        const cv::Point2f cv_p(prediction.GetX(), prediction.GetY());
        // draw on new_image
        cv::circle(new_image, cv_p, 5, color);  // red
        cv::line(new_image, cv_m, cv_p, cv::Scalar(255, 255, 0), 1);
    }

    return new_image;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat Visualizer::DrawStatisticsInfo(const uint64_t frame_id, const Timestamp& timestamp,
                                       const uint64_t optimized_feature_num, const cv::Mat& image) const
{
    cv::Mat new_image = image;

    {
        // frame id
        std::stringstream ss;
        ss << "frame_id = " << frame_id;
        cv::putText(new_image, ss.str(), cv::Point2f(10, 30), 1, 1, cv::Scalar(0, 0, 255));  // red
    }

    {
        std::stringstream ss;
        ss << "timestamp = " << std::fixed << timestamp.ToSec();
        cv::putText(new_image, ss.str(), cv::Point2f(10, 45), 1, 1, cv::Scalar(0, 0, 255));  // red
    }

    {
        std::stringstream ss;
        ss << "#_of_observed_landmarks = " << optimized_feature_num;
        cv::putText(new_image, ss.str(), cv::Point2f(10, 60), 1, 1, cv::Scalar(0, 0, 255));  // red
    }

    return new_image;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::SetPrebuiltSlotMap(const SlotMapPtr& prebuilt_slot_map)
{
    // @todo can we only save parking slots, don't save index. (chengchangxi@holomatic.com)
    int i = 0;
    for (const auto& parking_slot : *prebuilt_slot_map)
    {
        global_indexed_parking_slots_.emplace(i++, *parking_slot);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::SetPrebuiltMap(const MapPtr& prebuilt_map)
{
    // @todo can we only save parking slots, don't save index. (chengchangxi@holomatic.com)
    int i = 0;
    for (const auto& map_point : *prebuilt_map)
    {
        global_indexed_mappoints_.emplace(i++, *map_point);
    }
}

#ifdef HOLO_VISUALIZE_WITH_PANGOLIN
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Point3 Visualizer::ComputeColor(const Scalar z) const
{
    Scalar index = z / 200.0 * 60.0;                         // index-> 0 ~ 60
    index        = index > 60 ? 60 : index;                  // z > 200, index = 60
    Scalar c     = ((int64_t)index % 20) * 0.0938;           // c = 0 ~ 1   gradually increase
    Scalar d     = 1 - ((int64_t)index % 20 - 10) * 0.0938;  // d = 0 ~ 1   gradually decreasing

    // when z < 66m
    if (index <= 20)
    {
        // z < 33m
        if (index <= 10)
        {
            return (Point3(1.0, c, 0.0));
        }
        // 33 < z < 66
        else
            return (Point3(d, 1.0, 0.0));
    }
    // when z < 132
    if (index <= 40)
    {
        // 66 < z < 99
        if (index <= 30)
        {
            return (Point3(0.0, 1.0, c));
        }
        // 99 < z < 132
        else
            return (Point3(0.0, d, 1.0));
    }
    else
    {  // 132 < z < 165
        if (index <= 50)
        {
            return (Point3(c, 0.0, 1.0));
        }
        // z > 165
        else
            return (Point3(1.0, 0.0, d));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pangolin::OpenGlMatrix Visualizer::ConvertHoloPoseToOpenGlPose(const Pose3& pose) const
{
    // assign to opengl type (both are column major)
    pangolin::OpenGlMatrix T;
    memcpy(T.m, pose.ToMatrix().GetData(), sizeof(Pose3::ScalarType) * 16);
    return T;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::DrawMap()
{
    std::unique_lock<std::mutex> lock(mutex_);
    {
        std::vector<Point3> local_mappoints;

        for (const auto& key : sliding_window_state_.values.keys())
        {
            const gtsam::Symbol symbol(key);

            if (symbol.chr() == 'l')
            {
                local_mappoints.emplace_back(HoloGtsam::Convert(sliding_window_state_.values.at<gtsam::Point3>(key)));
            }
        }

        glPointSize(parameters_.point_size * 1.5);
        glBegin(GL_POINTS);
        const Pose3& T_wc = es_traj_.back();

        // draw local map points
        for (const auto& local_mappoint : local_mappoints)
        {
            Point3d pts     = T_wc.TransformTo(local_mappoint);
            Point3d p_color = ComputeColor(pts.GetZ());
            glColor3f(p_color.GetX(), p_color.GetY(), p_color.GetZ());
            glVertex3f(local_mappoint.GetX(), local_mappoint.GetY(), local_mappoint.GetZ());
        }

        // draw global map points
        for (const auto& global_indexed_mappoint : global_indexed_mappoints_)
        {
            Point3d global_mappoint = global_indexed_mappoint.second.position;
            /// compute point color
            // Point3d pts             = T_wc.TransformTo(global_mappoint);
            // Point3d p_color         = ComputeColor(pts.GetZ());
            // glColor3f(p_color.GetX(), p_color.GetY(), p_color.GetZ());
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(global_mappoint.GetX(), global_mappoint.GetY(), global_mappoint.GetZ());
        }

        glEnd();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::DrawVisiableMap()
{
    std::unique_lock<std::mutex> lock(mutex_);
    {
        if (visiable_map_ == nullptr)
        {
            return;
        }
        glPointSize(parameters_.point_size * 2);
        glBegin(GL_POINTS);
        const auto visiable_map = *visiable_map_;
        // draw global map points
        for (const auto& visiable_mappoint : visiable_map)
        {
            Point3d mappoint = visiable_mappoint->position;
            /// compute point color
            // Point3d pts             = T_wc.TransformTo(global_mappoint);
            // Point3d p_color         = ComputeColor(pts.GetZ());
            // glColor3f(p_color.GetX(), p_color.GetY(), p_color.GetZ());
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(mappoint.GetX(), mappoint.GetY(), mappoint.GetZ());
        }
        glEnd();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::DrawParkingSlots()
{
    std::unique_lock<std::mutex> lock(mutex_);
    {
        for (const auto& global_indexed_parking_slot : global_indexed_parking_slots_)
        {
            const auto global_parking_slot = global_indexed_parking_slot.second;
            DrawParkingSlot(global_parking_slot, 1.0, 1.0, 1.0, parameters_.line_width);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::DrawParkingSlotsAssociation()
{
    std::unique_lock<std::mutex> lock(mutex_);
    {
        for (const auto& association_measurement : sfm_.measurements)
        {
            const auto train_slot = association_measurement.train_slot;
            DrawParkingSlot(train_slot, 1.0, 0.0, 0.0, parameters_.line_width * 3);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::DrawParkingSlot(const ParkingSlotType& parking_slot, const Scalar r, const Scalar g, const Scalar b,
                                 const Scalar line_width)
{
    glLineWidth(line_width);
    glColor3f(r, g, b);

    // draw parking slot skeleton
    glBegin(GL_LINES);
    glVertex3f(parking_slot.vertices[1].GetX(), parking_slot.vertices[1].GetY(), parking_slot.vertices[1].GetZ());
    glVertex3f(parking_slot.vertices[2].GetX(), parking_slot.vertices[2].GetY(), parking_slot.vertices[2].GetZ());
    glVertex3f(parking_slot.vertices[2].GetX(), parking_slot.vertices[2].GetY(), parking_slot.vertices[2].GetZ());
    glVertex3f(parking_slot.vertices[3].GetX(), parking_slot.vertices[3].GetY(), parking_slot.vertices[3].GetZ());
    glVertex3f(parking_slot.vertices[3].GetX(), parking_slot.vertices[3].GetY(), parking_slot.vertices[3].GetZ());
    glVertex3f(parking_slot.vertices[0].GetX(), parking_slot.vertices[0].GetY(), parking_slot.vertices[0].GetZ());
    glEnd();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::DrawEstimateTrajectory()
{
    std::unique_lock<std::mutex> lock(mutex_);
    DrawTrajectory(es_traj_, 1.0, 0.0, 0.0);  // red
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::DrawTrajectory(const std::vector<Pose3>& traj, const Scalar r, const Scalar g, const Scalar b) const
{
    const size_t num = traj.size();
    if (num == 0)
    {
        return;
    }

    // 1. first draw trajectory
    // draw single point
    glPointSize(parameters_.point_size * 2);
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    for (size_t i = 0; i < num; i++)
    {
        glVertex3f(traj[i].GetX(), traj[i].GetY(), traj[i].GetZ());
    }
    glEnd();

    // draw line
    if (num > 1)
    {
        glLineWidth(parameters_.line_width);
        glColor3f(r, g, b);
        glBegin(GL_LINES);
        for (size_t i = 0; i < num - 1; i++)
        {
            glVertex3f(traj[i].GetX(), traj[i].GetY(), traj[i].GetZ());
            glVertex3f(traj[i + 1].GetX(), traj[i + 1].GetY(), traj[i + 1].GetZ());
        }
        glEnd();
    }

    // 2. second draw camera skeleton
    if (parameters_.enable_show_keyframes)
    {
        // only draw keyframes in sliding window
        for (const auto& key : sliding_window_state_.compensated_values.keys())
        {
            const gtsam::Symbol symbol(key);

            if (symbol.chr() == 'x')
            {
                const auto T_wc = HoloGtsam::Convert(sliding_window_state_.compensated_values.at<gtsam::Pose3>(key)) *
                                  camera_parameters_->extrinsics.at(0);
                DrawCamera(T_wc, r, g, b);
            }
        }
    }
    else
        DrawCamera(traj.back(), r, g, b);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::DrawCamera(const Pose3& pose, const Scalar r, const Scalar g, const Scalar b) const
{
    // construct camera size
    const Scalar w = parameters_.camera_size; /* camera width  */
    const Scalar h = w * 0.75;                /* camera height */
    const Scalar z = w * 0.6;                 /* camera depth  */

    // model view matrix
    glPushMatrix();

    // set current camera matrix
    pangolin::OpenGlMatrix T = ConvertHoloPoseToOpenGlPose(pose);
    glMultMatrixd(T.m);
    glLineWidth(parameters_.line_width);
    glColor3f(r, g, b);

    // draw camera skeleton
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(w, h, z);
    glVertex3f(0, 0, 0);
    glVertex3f(w, -h, z);
    glVertex3f(0, 0, 0);
    glVertex3f(-w, -h, z);
    glVertex3f(0, 0, 0);
    glVertex3f(-w, h, z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(w, h, z);
    glVertex3f(w, -h, z);
    glVertex3f(-w, -h, z);
    glVertex3f(-w, h, z);
    glEnd();

    // draw axis
    const Scalar axis_length = w;
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(axis_length, 0, 0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, axis_length, 0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, axis_length);
    glEnd();
    glPopMatrix();
}

///////////////////////////////////////////////////////////////////////////////
void Visualizer::ShowPlotter(pangolin::Var<bool>& button, pangolin::View& view, size_t& num_visible_plotters,
                             const std::string& lable)
{
    // check if button pushed?
    if (pangolin::Pushed(button))
    {
        view.ToggleShow();
    }
    AdjustPlotterPosition(view, num_visible_plotters);
    ShowSideText(view, std::string(lable));
}

///////////////////////////////////////////////////////////////////////////////
void Visualizer::AdjustPlotterPosition(pangolin::View& view, size_t& num_visible_plotters)
{
    static Scalar plotter_height = 0.25;
    static Scalar plotter_left   = 0.125;
    static Scalar plotter_width  = 0.25;
    if (view.IsShown())
    {
        Scalar plotter_bottom = ComputePlotterBottomPosition(num_visible_plotters, plotter_height);
        view.SetBounds(plotter_bottom, plotter_bottom + plotter_height, plotter_left, plotter_left + plotter_width);
        num_visible_plotters++;
    }
}

///////////////////////////////////////////////////////////////////////////////
Scalar Visualizer::ComputePlotterBottomPosition(const size_t& num_visible_plotters, const Scalar plotter_height)
{
    size_t plotter_rows = (size_t)(1.0 / plotter_height);
    Scalar bottom       = 1.0 - (num_visible_plotters % plotter_rows + 1) * plotter_height;
    return bottom;
}

///////////////////////////////////////////////////////////////////////////////
void Visualizer::ShowSideText(const pangolin::View& view, const std::string& text) const
{
    if (view.IsShown())
    {
        const pangolin::Viewport& v         = view.v;
        pangolin::GlText          side_text = GetStaticText(text);
        GLfloat                   offset_w  = v.l + v.w;
        GLfloat                   offset_h  = v.b + 0.5 * v.h;
        side_text.DrawWindow(offset_w, offset_h, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////
pangolin::GlText Visualizer::GetStaticText(const std::string& text) const
{
    pangolin::GlText gltext = pangolin::GlFont::I().Text(text);
    return gltext;
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Visualizer::InternalThreadFunction()
{
    // create opencv windows name
    for (size_t i = 0; i < camera_parameters_->camera_coords.size(); i++)
    {
        cv::namedWindow(camera_parameters_->camera_coords.at(i), CV_WINDOW_KEEPRATIO);
    }

    // StorageManager
    StorageManager storage_manager;

#ifdef HOLO_VISUALIZE_WITH_PANGOLIN
    // begin configure pangolin
    // use pangolin to create window
    pangolin::CreateWindowAndBind(parameters_.window_name, parameters_.window_size.GetWidth(),
                                  parameters_.window_size.GetHeight());

    // enable buffers
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // define camera render object
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(parameters_.window_size.GetWidth(), parameters_.window_size.GetHeight(),
                                   parameters_.view_f,                                        /* fx    */
                                   parameters_.view_f,                                        /* fy    */
                                   parameters_.window_size.GetWidth() / 2,                    /* cx    */
                                   parameters_.window_size.GetHeight() / 2,                   /* cy    */
                                   0.1,                                                       /* z_near*/
                                   1000000),                                                  /* z_far */
        pangolin::ModelViewLookAt(parameters_.view_x, parameters_.view_y, parameters_.view_z, /*camera position*/
                                  0, 0, 0,       /* camera point to position*/
                                  0.0, 0.0, 1.0) /* camera up direction */
    );

    // add named opengl viewport to window and provide 3d handler
    pangolin::View& d_cam =
        pangolin::CreateDisplay().SetBounds(0.0, 1.0, 0.0, 1.0).SetHandler(new pangolin::Handler3D(s_cam));

    // create pannel and add buttons
    pangolin::CreatePanel("ui").SetBounds(0.0, 1.0, 0.0, 0.125).SetLock(pangolin::LockLeft, pangolin::LockTop);

    // disable ON/OFF and SEQ_ERROR
    // pangolin::Var<bool> pause_button("ui.ON/OFF", false, false);
    pangolin::Var<bool> follow_camera_button("ui.FOLLOW CAMERA", false, false);
    pangolin::Var<bool> reset_button("ui.RESET VIEW", false, false);
    pangolin::Var<bool> screen_shot_button("ui.SCREENSHOT", false, false);
    pangolin::Var<bool> show_keyframes("ui.KEYFRAMES", false, false);
#endif

    // Timer to control the frequency of the thread
    Timer timer(parameters_.loop_rate);  // 10hz

    // start loop
    while (status_ != Status::STOP)
    {
        // check if state update
        if (is_state_updated_)
        {
            // update_plotter    = is_state_updated_;
            is_state_updated_ = false;
        }

        timer.Start();

        // status checking
        if (status_ == Status::PAUSE)
        {
            is_running_ = false;
            usleep(1e3);
            continue;
        }

        // set running
        is_running_ = true;

        auto frame_id = newest_updated_tracker_state_.frame_id;

        // generally, it means LocalizationVio is reset,
        // when SlidingWindowState is updated by LocalizationVio and frame_id == 0;
        // clear internal variable when it happens
        // @TODO check whehter LocalizationVio in the other way if it is necessary
        //       lishuaijie@holomatic.com
        if (is_image_updated_ && frame_id == 0)
        {
            LOG(WARNING) << "Visualizer --- reset StorageManager!!!";
            storage_manager = StorageManager();
        }

#ifdef HOLO_VISUALIZE_WITH_PANGOLIN
        // starts pangolin drawing
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // check if following camera
        if (parameters_.enable_camera_following)
        {
            std::unique_lock<std::mutex> lock(mutex_);
            pangolin::OpenGlMatrix       T_wc = ConvertHoloPoseToOpenGlPose(es_traj_.back());
            s_cam.Follow(T_wc);
        }
        d_cam.Activate(s_cam);

        // clear panel
        glClearColor(0.0, 0.008375209, 0.058823529, 1.0);

        // draw mappoints
        DrawMap();

        DrawVisiableMap();

        // draw trajectory
        DrawEstimateTrajectory();

        // draw parking slots
        DrawParkingSlots();

        DrawParkingSlotsAssociation();

        // check reset button pushed?
        if (pangolin::Pushed(reset_button))
        {
            LOG(INFO) << "Visualization --- reset viewer pose";

            s_cam.SetModelViewMatrix(pangolin::ModelViewLookAt(parameters_.view_x, parameters_.view_y,
                                                               parameters_.view_z, /*camera position*/
                                                               0, 0, 0,            /* camera point to position*/
                                                               0.0, 0.0, 1.0));    /* camera up direction */
        }

        // check screen shot bottun pushed?
        if (pangolin::Pushed(screen_shot_button))
        {
            static size_t     ss_num = 0;
            std::stringstream ss;
            ss << "vio_screenshot_" << std::setfill('0') << std::setw(3) << ss_num++;
            LOG(INFO) << "Visualization --- saved screenshot " << ss.str();
            pangolin::SaveWindowOnRender(ss.str());
        }

        // check if show keyframes button pushed?
        if (pangolin::Pushed(show_keyframes))
        {
            parameters_.enable_show_keyframes = !parameters_.enable_show_keyframes;
        }

        // check follow camera button pushed?
        if (pangolin::Pushed(follow_camera_button))
        {
            parameters_.enable_camera_following = !parameters_.enable_camera_following;
        }

        // swap frames and process events
        pangolin::FinishFrame();
#endif

        // opencv visualize
        if (is_image_updated_)
        {
            std::unique_lock<std::mutex> lock(mutex_);
            const auto                   images =
                DrawAllTracks(newest_updated_tracker_state_, newest_updated_values_, newest_updated_timestamp_);
            for (size_t camera_index = 0; camera_index < images.size(); camera_index++)
            {
                cv::imshow(camera_parameters_->camera_coords.at(camera_index), images.at(camera_index));
            }

            if (parameters_.save_image)
            {
                for (size_t camera_index = 0; camera_index < images.size(); camera_index++)
                {
                    std::string file_name =
                        camera_parameters_->camera_coords.at(camera_index) + "_" + std::to_string(frame_id) + ".png";
                    cv::imwrite(parameters_.folder_name + "/" + file_name, images.at(camera_index));
                }
            }

            if (parameters_.save_graph)
            {
                std::string   file_name = std::to_string(frame_id) + ".json";
                std::ofstream ofile(parameters_.folder_name + "/" + file_name);

                if (ofile.is_open())
                {
                    StorageManager updated_storage_manager;
                    updated_storage_manager = storage_manager.UpdateValues(newest_updated_values_);
                    updated_storage_manager.SaveFactorGraphSequence(newest_updated_factor_graph_, ofile,
                                                                    newest_updated_values_);
                    storage_manager = updated_storage_manager;
                }
                else
                {
                    LOG(WARNING) << "Visualizer --- can not open file " << file_name;
                }
            }

            cv::waitKey(1);
            is_image_updated_ = false;
        }

        timer.Stop();
        // update_plotter = false;
    }
    // set running false
    is_running_ = false;

    cv::destroyAllWindows();
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
