/*!
 * \brief vslam measurements manager class
 * \author Feng. Li. lifeng@holomatic.com
 * \date Dec-25-2018
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_MEASUREMENTS_MANAGER_VSLAM_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_MEASUREMENTS_MANAGER_VSLAM_H_

#include <holo/3d/common/kdtree.h>
#include <holo/localization/common/measurements_manager_base.h>
#include <holo/localization/tools/source_checker.h>
#include <holo/localization/vision/vslam/common_types.h>

#include <boost/circular_buffer.hpp>

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
 * @brief VSLAM measurements manager class
 *
 * @details this class provides all necessary measurements listed below for
 *          vslam algorithm
 * a. images. main source of a vslam system
 * b. imus. main source of a vslam system
 * c. gravity aligned odometry, served as get initial pose for highway scene,
 *          in this way, the results of the initial frames are poor. Further
 *          we use the gravity alignment odometry of the first frame to search
 *          the local map, then used local map and the first frame to solve PNP
 *          to optimize the initial pose.
 *          which may come from init_alignment_odometry for highway scene.
 * d. vehicle infos, will be tightly-coupled with imu and visual measurements
 * e. ground truth odometry. for vslam results evaluation
 *
 * @note as we only check and log time continuity inside class, basically it
 *       accepts measurements in any time order but outputs measurements
 *       chronologically. It's the user's responsibility to check the
 *       time gap between two adjacent measurements
 */
class MeasurementsManagerVSLAM : public MeasurementsManagerBase
{
public:
    typedef MeasurementsManagerBase                           Base;
    typedef std::shared_ptr<MeasurementsManagerVSLAM>         Ptr;
    typedef std::shared_ptr<const MeasurementsManagerVSLAM>   ConstPtr;
    typedef boost::circular_buffer<Image>                     ImageCircularBuffer;
    typedef boost::circular_buffer<Odometry>                  OdometryBufferType;
    typedef boost::circular_buffer<ParkingSlotFrameType>      ParkingSlotFrameBufferType;
    typedef std::unordered_map<uint16_t, ImageCircularBuffer> MultiImageCircularBuffer;

    using PointType     = holo::point_cloud::PointXYZIRSt<Scalar>;
    using PointCloud    = holo::pointcloud::PointCloudT<PointType>;
    using PointCloudPtr = std::shared_ptr<PointCloud>;
    using KdTree        = holo::pointcloud::KdTreeT<PointType>;
    using KdTreePtr     = std::shared_ptr<KdTree>;

    using PointFeaturesCircularBuffer      = boost::circular_buffer<PointFeaturefList_ST*>;
    using MultiPointFeaturesCircularBuffer = std::unordered_map<uint16_t, PointFeaturesCircularBuffer>;
    using ObstaclePtrListCircularBuffer    = boost::circular_buffer<ObstaclePtrList>;
    using MultiObstacleCircularBuffer      = std::unordered_map<uint16_t, ObstaclePtrListCircularBuffer>;

    /**
     * @brief parameters
     */
    struct Parameters
    {
        const uint64_t image_queue_size;

        const uint64_t point_feature_queue_size;

        const uint64_t gravity_aligned_odometry_buffer_size;

        const bool make_point_features_as_optional;

        const Scalar maximum_range;  // metre

        const Scalar fov;  // degree

        /// @brief constructor
        Parameters(const uint64_t _image_queue_size, const uint64_t _point_feature_queue_size,
                   const uint64_t _gravity_aligned_odometry_buffer_size,
                   const bool _make_point_features_as_optional = false, const Scalar _maximum_range = 25,
                   const Scalar _fov = 120.0)
          : image_queue_size(_image_queue_size)
          , point_feature_queue_size(_point_feature_queue_size)
          , gravity_aligned_odometry_buffer_size(_gravity_aligned_odometry_buffer_size)
          , make_point_features_as_optional(_make_point_features_as_optional)
          , maximum_range(_maximum_range)
          , fov(_fov)
        {
        }

        // output stream
        friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
        {
            os << "MeasurementsManagerVSLAMParameters:\n"
               << " image queue size: " << parameters.image_queue_size
               << "\n point feature queue size: " << parameters.point_feature_queue_size
               << "\n gravity aligned odometry buffer size: " << parameters.gravity_aligned_odometry_buffer_size
               << "\n make_point_features_as_optional: " << parameters.make_point_features_as_optional
               << "\n maximum range : " << parameters.maximum_range << "\n fov : " << parameters.fov << std::endl;
            return os;
        }

        // @brief load parameters from yaml
        static Parameters LoadFromYaml(const holo::yaml::Node& node);

        // @brief an example parameters
        static Parameters Example();
    };  // Parameters

    /**
     * @brief Construct a new MeasurementsManagerVSLAM object
     *
     * @param parameters
     * @param map map points
     */
    MeasurementsManagerVSLAM(const Parameters& paramters, const CameraParameters::Ptr& camera_parameters = nullptr,
                             const MapPtr& map = nullptr);

    /**
     * @brief destructor
     */
    virtual ~MeasurementsManagerVSLAM()
    {
    }

    /**
     * @brief set map
     */
    void SetMap(const MapPtr& map, const SlotMapPtr& slot_map)
    {
        map_    = map;
        kdtree_ = InitializeMap(map_);

        slot_map_ = slot_map;
    }

    /**
     * @brief reset function
     *
     * @details all measurements stored in each queue will be cleared.
     *          You may call this function when rebooting the entire vslam system.
     */
    void Reset();

    /**
     * @brief add image measurement
     * @param[in] m latest image measurement
     */
    virtual bool AddMeasurement(const Image& m, const uint16_t camera_index);

    /**
     * @brief add point feature measurement
     * @param m latest point feature measurement
     */
    virtual bool AddMeasurement(PointFeaturefList_ST* const m);

    /**
     * @brief add chassis state measurement
     * @param[in] latest vechile info measurement
     */
    virtual bool AddMeasurement(const ChassisState& m) override;

    /**
     * @brief add imu measurement
     * @param[in] latest imu measurement
     */
    virtual bool AddMeasurement(const Imu& m) override;

    /**
     * @brief add gnss position
     * @param[in] gps position measurement
     */
    virtual bool AddMeasurement(const GnssPosition& m) override;

    /**
     * @brief add obstacle ptr list
     * @param[in] latest obstacle ptr list measurement
     */
    virtual bool AddMeasurement(const ObstaclePtrList& m);

    /**
     * @brief add parking-slot frame
     * @param[in] latest parking-slot frame measurement
     */
    bool AddMeasurement(const ParkingSlotFrameType& m);

    /**
     * @brief add gravity-aligned odometry
     * @param[in] latest odometry measurement
     */
    bool AddGravityAlignedOdometry(const Odometry& m);

    /**
     * @brief check if vslam measurement is available
     *
     * @details it returns true when image, imu and vehicle info buffer
     *          are NOT empty
     */
    bool IsRawMeasurementAvailable(bool enable_visualizer = false, bool is_dr_mode = false,
                                   bool is_parking_slot_optional = true);

    /**
     * @brief get timestamp of the oldest point feature message
     *
     * @details it returns timestamp of the first aligned point_feature measurement
     */
    boost::optional<Timestamp> GetOldestAlignedPointFeaturesTimestamp();

    /**
     * @brief get timestamp of the oldest Parking slot frame message
     *
     * @details it returns timestamp of the first aligned parking_slot_frame measurement
     */
    boost::optional<Timestamp> GetOldestParkingSlotFrameTimestamp();

    /**
     * @brief get timestamp of the newest available raw mesaurement
     */
    bool GetNewestRawMeasurementTimestamp(Timestamp& timestamp);

    /**
     * @brief get timestamp of the newest available raw mesaurement in dr mode
     */
    bool GetDrNewestRawMeasurementTimestamp(Timestamp& timestamp);

    /**
     * @brief get timestamp of the newset available raw measurement in semantic mode
     */
    bool GetSemanticNewestRawMeasurementTimestamp(Timestamp& timestamp);

    /**
     * @brief get point features measurement at given timestamp
     */
    bool GetPointFeaturesAt(const Timestamp& timestamp, std::vector<PointFeaturefList_ST*>& multi_point_feature_list);

    /**
     * @brief get image measurements at given timestamp
     */
    bool GetImagesAt(const Timestamp& timestamp, std::vector<Image>& multi_images);

    /**
     * @brief get vslam measurements (image + imu + vehicle_velocity + optional(prior_odometry) + optional_map)
     *
     * @details this function will query a latest image and all imu measurements
     *          whose timestamps are between the given time(old_timestamp) and
     *          the lastest image timestamp
     *          In addition, all retrieved imus are pushed in the vector in
     *          chronological order, the timestamp of the last imu in the retrieved imu vector
     *          is aligned with the retrieved image's timestamp
     * @note!!! the retrieved imus will not be removed from imu_buffer_
     * @param[in] old_timestamp the given timestamp which is the timestamp of
     *            the previous image used in last vslam optimization
     * @param[in] prior_vehicle_pose prior vehicle pose, it will be used to query local
     *            feature map
     * @param[out] raw_measurements retrieved vslam measurements.
     * @return true if success to get raw measurement, else return false.
     */
    bool GetRawMeasurement(const Timestamp& old_timestamp, const boost::optional<Pose3>& prior_vehicle_pose,
                           RawMeasurement& raw_measurements);

    /**
     * @brief get vslam measurements in dr mode(imu + chassis_state)
     * @param[in] old_timestamp the given timestamp which is the timestamp of
     *            the previous image used in last vslam optimization
     * @param[in] prior_vehicle_pose prior vehicle pose, it will be used to query local
     *            feature map
     * @param[out] raw_measurements retrieved vslam measurements.
     * @return true if success to get raw measurement, else return false.
     */
    bool GetDrRawMeasurement(const Timestamp& old_timestamp, RawMeasurement& raw_measurements);

    /**
     * @brief get vslam measurements in semantic mode(parking_slot_frame + imu + chassis_state)
     * @param[in] old_timestamp the given timestamp which is the timestamp of
     *            the previous image used in last vslam optimization
     * @param[in] prior_vehicle_pose prior vehicle pose, it will be used to query local
     *            feature map
     * @param[out] raw_measurements retrieved vslam measurements.
     * @return true if success to get raw measurement, else return false.
     */
    bool GetSemanticRawMeasurement(const Timestamp& old_timestamp, RawMeasurement& raw_measurements);

    /**
     * @brief get imu measurements betweeen ${left_t} and ${right_t}
     *
     * @param[in] left_t left timestamp
     * @param[in] right_t right timestamp
     * @param[in] imus retrieved imu measurements
     * @return bool_t false if can find valid imu measurements
     */
    bool_t GetImuMeasurements(const Timestamp& left_t, const Timestamp& right_t, std::vector<Imu>& imus);

    /**
     * @brief Get the Chassis States Measurements betweeen ${left_t} and ${right_t}
     *
     * @param[in] left_t left timestamp
     * @param[in] right_t right timestamp
     * @param[in] chassis_states retrieved chassis_state measurements
     * @return bool_t
     */
    bool_t GetChassisStatesMeasurements(const Timestamp& left_t, const Timestamp& right_t,
                                        std::vector<ChassisState>& chassis_states);

    /**
     * @brief get multi obstacle list with query timestamp
     *
     * @param[in] query_timestamp query timestamp
     * @return multi obstacle list
     */
    std::vector<ObstaclePtrList> GetMultiObstaclePtrList(const Timestamp& query_timestamp);

    /**
     * @brief get parking slot frame at given timestamp
     *
     * @param[in] timestamp query timestamp
     * @param[out] boost::optional<ParkingSlotFrameType>
     * @return bool_t
     */
    bool_t GetParkingSlotFrame(const Timestamp&                       new_timestamp,
                               boost::optional<ParkingSlotFrameType>& optional_parking_slot_frame);

    /**
     * @brief get newest parking slot frame in parking_slot_frame_buffer_
     *
     * @param[in] point_feature_timestamp point feature timestamp
     * @return boost::optional<ParkingSlotFrameType>
     */
    boost::optional<ParkingSlotFrameType> GetNewestParkingSlotFrame(const Timestamp& point_feature_timestamp);

    MapPtr QueryMap(const Pose3& prior_vehicle_pose)
    {
        const Scalar maximum_range = parameters_.maximum_range;  // metre
        const Scalar fov           = parameters_.fov;            // degree
        MapPtr       visible_map   = std::make_shared<Map>();

        // get visible map points for each camera
        /// @todo(Feng. Li 2020-06-10) for multi-camera system with large overlapping in fov, query visible map like
        /// this may cause redundant copies, we should optimize this part in future.
        for (uint16_t camera_index = 0; camera_index < camera_parameters_->extrinsics.size(); camera_index++)
        {
            const auto prior_camera_pose = prior_vehicle_pose * camera_parameters_->extrinsics.at(camera_index);
            GetVisibleMap(prior_camera_pose, maximum_range, fov, map_, kdtree_, visible_map);
        }

        return visible_map;
    }

    /**
     * @brief get the visible map points from prior pose
     *
     * @param[in] prior_vehicle_pose prior vehicle pose
     * @return SlotMapPtr the visible parking slot map
     */
    SlotMapPtr QuerySlotMap(const Pose3& prior_vehicle_pose);

protected:
    /**
     * @brief initialize kdtree for map points
     *
     * @param map
     * @return KdTreePtr
     */
    KdTreePtr InitializeMap(const MapPtr& map);

    /**
     * @brief get the visible map points from prior pose
     *
     * @param[in] prior prior camera pose
     * @param[in] maximum_range max depth
     * @param[in] fov maximum camera fov in vertical and horizontal direction
     * @param[in] map the original map
     * @param[in] kdtree a kdtree built by the original map
     * @param[out] visible_map the visible map
     */
    void GetVisibleMap(const Pose3& prior, Scalar maximum_range, Scalar fov, const MapPtr& map, const KdTreePtr& kdtree,
                       MapPtr& visible_map) const;

    /// @brief define gravity-aligned odometry
    std::mutex         gravity_aligned_odometry_buffer_mutex_;
    OdometryBufferType gravity_aligned_odometry_buffer_;

    /// @brief define multi camera measurement
    std::mutex               multi_image_buffer_mutex_;  ///< image mutex
    MultiImageCircularBuffer multi_image_buffer_;

    /// @brief define multi point features measurement
    std::mutex                       multi_point_feature_buffer_mutex_;  ///< point feature mutex
    MultiPointFeaturesCircularBuffer multi_point_feature_buffer_;

    /// @brief define multi obstacle measurement
    std::mutex                  multi_obstacle_queue_mutex_;
    MultiObstacleCircularBuffer multi_obstacle_queue_;

    /// @brief define parking-slots (per frame) measurement
    std::mutex                 parking_slot_frame_buffer_mutex_;
    ParkingSlotFrameBufferType parking_slot_frame_buffer_;

    /// @brief shared_ptr of camera parameters
    CameraParameters::Ptr camera_parameters_;

    /// @brief visible map points
    MapPtr    map_;
    KdTreePtr kdtree_;

    /// @brief visible parking slot map
    SlotMapPtr slot_map_;

    /// @brief parameters
    Parameters parameters_;
};  // MeasurementsManagerVSLAM

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_MEASUREMENTS_MANAGER_VSLAM_H_
