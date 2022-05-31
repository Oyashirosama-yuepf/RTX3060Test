/**
 * @file parking_obstacle_freespace_fusion.h
 * @author zhang yuqi (zhangyuqi1@holomatic.com)
 * @brief freespace and obstacle list fusion pipline
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_OBSTACLE_FREESPACE_FUSION_PIPLINE_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_OBSTACLE_FREESPACE_FUSION_PIPLINE_H_

#include <holo/perception/obstacle_fusion/obstacle_freespace/parking_obstacle_freespace_fusion.h>
namespace holo
{
namespace perception
{
/**
 * @brief freespace and obstaclelist fusion pipeline
 *
 */
class ObstacleFreespaceParkingPipeline
{
public:
    using Timestamp                     = holo::common::Timestamp;
    using AppStatus                     = holo::uint32_t;
    using Obstacle                      = holo::obstacle::ObstacleGeneralT<float32_t>;
    using ObstacleGeneralPtrList        = holo::obstacle::ObstaclePtrListT<Obstacle, 128UL>;
    using ObstacleGeneralPtrListMessage = std::shared_ptr<ObstacleGeneralPtrList>;
    using Point2f                       = holo::geometry::Point2f;
    using Point3f                       = holo::geometry::Point3f;

    using FreespaceExterior = holo::common::AutoFreespaceExterior<Point3f>;
    using Freespace         = holo::common::AutoFreespace<Point3f>;
    using FreespaceMessage  = std::shared_ptr<Freespace>;

    using OdometryType    = holo::common::Odometryf;
    using OdometryMessage = std::shared_ptr<OdometryType>;

    using VisionObsPtr        = std::shared_ptr<obstacle::ObstacleVisionT<float32_t>>;
    using VisionMessage       = std::shared_ptr<obstacle::ObstacleVisionPtrList>;
    using VisionMessageMap    = std::unordered_map<uint32_t, VisionMessage>;
    using VisionMessageVector = std::vector<VisionObsPtr>;

    using VisionObsFilterRule = std::function<bool_t(VisionObsPtr const)>;

    /**
     * @brief Construct a new Obstacle Freespace Parking Pipeline object
     *
     */
    ObstacleFreespaceParkingPipeline();

    /**
     * @brief Destroy the Obstacle Freespace Parking Pipeline object
     *
     */
    ~ObstacleFreespaceParkingPipeline();

    /**
     * @brief Set the Timestamp object
     *
     * @param current_time
     */
    void SetTimestamp(Timestamp const& current_time);

    /**
     * @brief Main function of  freespace and obstacle list fusion
     *
     * @param freespace_msg freespace input msg
     * @param obstacle_msg obstacle list msg
     * @param freespace_output freespace out put msg
     */
    void Compute(FreespaceMessage const& freespace_msg, VisionMessageMap const& obstacle_msg,
                 Freespace& freespace_output, AppStatus& app_status, Timestamp const& current_time);

    /**
     * @brief Get the Mutex Number object
     *
     * @return uint32_t
     */
    inline uint32_t GetMutexNumber()
    {
        return this->freespace_fusion_->GetMutexNumber_();
    }

    /**
     * @brief determine whether vision obstacle is valid
     *
     * @param obs vision obstacle
     * @return bool_t true if vision obstacle is valid else false
     */
    bool_t isValidVisionObs(VisionObsPtr const obs);

    /**
     * @brief Get the Sur Message object
     *
     * @param vision_obstacle input vision message map
     * @param obstacle_msg out put vision message vector
     */
    void getSurMessage(VisionMessageMap const& vision_obstacle, VisionMessageVector& obstacle_msg);

    /**
     * @brief update app status code according to the freespace and obstacle mutex
     *
     * @param mutex_count mutex count number
     * @param app_status app safety code
     */
    void AppStatusChecker(uint32_t const& mutex_count, AppStatus& app_status);

    /**
     * @brief Abnormal position
     *
     * @return boot_t
     */
    bool_t IsAbnormalPosition()
    {
        return this->abnormal_position_;
    }

private:
    Timestamp timestamp_;

    std::shared_ptr<ParkingFreespaceAndObstacleFusion> freespace_fusion_;

    std::list<VisionObsFilterRule> vision_obs_filter_rule_list_;
    bool_t                         abnormal_position_;
    // freespace Multi frame Association
};
}  // namespace perception
}  // namespace holo
#endif
