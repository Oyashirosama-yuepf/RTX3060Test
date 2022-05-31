/**
 * @file parking_obstacle_input_preprocess.h
 * @author Zhang yuqi (zhangyuqi1@holomatic.com)
 * @brief Input forward-looking obstacle preprocessing
 * @version 0.1
 * @date 2022-04-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef HOLO_PERCEPTION_PARKING_OBSTACLE_FUSION_PARKING_OBSTACLE_INPUT_PREPROCESS_H_
#define HOLO_PERCEPTION_PARKING_OBSTACLE_FUSION_PARKING_OBSTACLE_INPUT_PREPROCESS_H_

#include <glog/logging.h>
#include <holo/common/odometry.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/utils/sensor_obstacle_track.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <map>
#include <opencv2/opencv.hpp>
namespace holo
{
namespace perception
{
class ParkingObstacleInputPreprocess
{
public:
    using Timestamp = holo::common::Timestamp;
    using Scalar    = float32_t;
    using Vector3f  = holo::numerics::Vector3f;
    using ObstacleGeneralPtrList =
        holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, 128UL>;
    using ObstacleVisionPtrList = holo::obstacle::ObstacleVisionPtrList;
    using ClassificationKey =
        std::pair<holo::common::details::Classification::MainType, holo::common::details::Classification::SubType>;

    using VisionObsType = holo::obstacle::ObstacleVisionT<Scalar>;
    using VisionObsPtr  = std::shared_ptr<VisionObsType>;

    using VisionMessage = std::shared_ptr<ObstacleVisionPtrList>;

    using VisionMessageMap = std::unordered_map<uint32_t, VisionMessage>;

    using VisionMeasurementMap = std::unordered_map<SensorMeasurementKey, VisionObsPtr, SensorMeasurementKeyHash>;

    using OdometryType    = holo::common::Odometryf;
    using OdometryMessage = std::shared_ptr<OdometryType>;
    using OdometryCache   = std::deque<OdometryMessage>;

    /**
     * @brief Compare the distance of points
     *
     */
    class NearestPoint
    {
    public:
        /**
         * @brief operator ()
         *
         * @param a point a
         * @param b point b
         * @return bool_t whether a is father than b
         */
        bool_t operator()(Point3f const& a, Point3f const& b)
        {
            if (a.Dist(Point3f(0, 0, 0)) > b.Dist(Point3f(0, 0, 0)))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };

    /**
     * @brief Construct a new Parking Obstacle Input Preprocess object
     *
     */
    ParkingObstacleInputPreprocess();

    /**
     * @brief Set parameters
     *
     */
    void Setup();

    /**
     * @brief Main function
     *
     * @param vision_measurement_map input measurement map
     */
    void DoWork(VisionMeasurementMap& vision_measurement_map, OdometryCache const& odo_cache);

private:
    /**
     * @brief Set parameters of vehicle type
     *
     * @param obstalce vision obstacle
     * @param timestamp camera time
     */
    void assignmentVehicleProperty(VisionObsPtr& obstalce);

    /**
     * @brief Specific outcome scenarios for srv obstacles
     *
     * @param obstalces input
     * @param timestamp srv camera time
     */
    void assignmentVehiclePropertySRV(VisionObsPtr& obstalces);

    /**
     * @brief Set parameters of other type
     *
     * @param obstalce input
     */
    void assignmentOtherProperty(VisionObsPtr& obstalce);

    /**
     * @brief conculate 3d boundingbox
     *
     * @param obstalce input
     */
    void conculate3DBox(VisionObsPtr& obstalce);

    /**
     * @brief  Calculate the original 3D box of Forward looking camera
     *
     * @param obstalce input
     */
    void conculateOriginal3DBox(VisionObsPtr& obstalce);

    /**
     * @brief Calculate the original 3D box of Forward srv camera
     *
     * @param obstalce input
     */
    void conculateOriginal3DBoxSRV(VisionObsPtr& obstalce);

    /**
     * @brief Calculate the min 3D box of Forward looking camera
     *
     * @param obstalce input
     */
    void conculateMin3DBox(VisionObsPtr& obstalce);

    /**
     * @brief Calculate the min 3D box of Forward srv camera
     *
     * @param obstalce
     */
    void conculateMin3DBoxSRV(VisionObsPtr& obstalce);

    /**
     * @brief conculate yaw by vote
     *
     * @param obstalce obstacle
     * @param center_point center points
     * @return Scalar
     */
    Scalar conculateYaw(VisionObsPtr const& obstalce, Point3f const& center_point);

    /**
     * @brief conculate center points
     *
     * @param obstalce
     * @return Point3f
     */
    Point3f conculateCenterPoint(VisionObsPtr const& obstalce);

    /**
     * @brief Is it an effective look around obstacle
     *
     * @param obstalce
     * @return bool_t
     */
    bool_t IsVaildObstacle(VisionObsPtr const& obstalce);

    /**
     * @brief Is it a valid forward-looking obstacle
     *
     * @param obstalce
     * @return bool_t
     */
    bool_t IsVaildSRVObstacle(VisionObsPtr const& obstalce);

    /**
     * @brief Synchronization timestamp
     *
     * @param vision_measurement_map vision obstacle
     * @param odo_cache odometry cahce
     * @param camera_time camera timestamp
     * @param srv_camera_time srv camera timestamp
     */
    void timestampCompensation(VisionMeasurementMap& vision_measurement_map, OdometryCache const& odo_cache,
                               Timestamp const& camera_time, Timestamp const& srv_camera_time);

    /**
     * @brief Discard obstacles in abnormal positions
     *
     * @param vision_measurement_map measuremnet map
     */
    void discardAbnormalObstacle(VisionMeasurementMap& vision_measurement_map);

    /**
     * @brief Calculate minimum area rectangle
     *
     * @param obstalce
     */
    void conculateMinArea3DBox(VisionObsPtr& obstalce);

private:
    Scalar                                           abnormal_distance_;
    Scalar                                           abnormal_srv_distance_;
    Scalar                                           timestamp_threshold_;
    bool_t                                           is_position_correction_;
    std::map<ClassificationKey, std::vector<Scalar>> obstacle_size_map_;
};

}  // namespace perception
}  // namespace holo
#endif
