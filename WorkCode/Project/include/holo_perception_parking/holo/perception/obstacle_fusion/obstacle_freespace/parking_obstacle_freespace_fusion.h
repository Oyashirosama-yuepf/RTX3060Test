/**
 * @file parking_obstacle_freespace_fusion.h
 * @author zhang yuqi (zhangyuqi1@holomatic.com)
 * @brief freespace and obstacle list fusion function
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_OBSTACLE_FREESPACE_FUSION_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_OBSTACLE_FREESPACE_FUSION_H_

#include <glog/logging.h>
#include <holo/common/classification.h>
#include <holo/common/freespace.h>
#include <holo/common/odometry.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/geometry/point2.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/obstacle_fusion/debug_info.h>
#include <holo/perception/obstacle_fusion/obstacle_freespace/parking_obstacle_freespace_fusion.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#define PI 3.1415926f

namespace holo
{
namespace perception
{
/**
 * @brief freespace and obstacle list fusion class
 *
 */
class ParkingFreespaceAndObstacleFusion
{
public:
    /**
     * @brief Position relationship of freesapce boundary and obstacle Fusion
     *
     */
    enum class Relationship
    {
        OUTSIDE  = 0U,
        INSIDE   = 1U,
        BOUNDARY = 2U
    };

    using Timestamp         = holo::common::Timestamp;
    using Point2f           = holo::geometry::Point2f;
    using Point3f           = holo::geometry::Point3f;
    using FreespaceExterior = holo::common::AutoFreespaceExterior<Point3f>;
    using Freespace         = holo::common::AutoFreespace<Point3f>;
    using FreespaceMessage  = std::shared_ptr<Freespace>;

    using VisionObsPtr        = std::shared_ptr<obstacle::ObstacleVisionT<float32_t>>;
    using VisionMessage       = std::shared_ptr<obstacle::ObstacleVisionPtrList>;
    using VisionMessageMap    = std::unordered_map<uint32_t, VisionMessage>;
    using VisionMessageVector = std::vector<VisionObsPtr>;
    /**
     * @brief Construct a new Parking Freespace And Obstacle Fusion object
     *
     */
    ParkingFreespaceAndObstacleFusion();

    /**
     * @brief Destroy the Parking Freespace And Obstacle Fusion object
     *
     */
    ~ParkingFreespaceAndObstacleFusion();

    /**
     * @brief Set the Params object
     *
     * @param m_a Minimum area threshold
     * @param p_n Sampling interval number
     * @param n_o_f Number of output points
     * @param min_s_d min_sample_distance
     * @param max_s_d max_sample_distance
     */
    void Setup(holo::yaml::Node const& node);

    /**
     * @brief Freespace Preprocessing
     *
     * @param freespace_msg freesapce msg
     * @param point_map freesapce map
     */
    void FreespacePreprocessing(FreespaceMessage const& freespace_msg, std::map<uint32_t, float32_t>& point_map);

    /**
     * @brief obstacle and freespace fusion
     *
     * @param obstacle_msg
     * @param freespace_msg
     * @param freesapce_master
     */
    void ObstacleFreespaceFusion(VisionMessageVector const& obstacle_msg, Freespace& freespace_msg,
                                 std::map<uint32_t, float32_t>& freesapce_master);

    /**
     * @brief Get the Mutex Number_ object
     *
     * @return uint32_t
     */
    inline uint32_t GetMutexNumber_()
    {
        return this->freespace_obstacle_;
    }

    /**
     * @brief Abnormal position
     *
     * @return bool_t
     */
    bool_t IsAbnormalPosition();

private:
    /**
     * @brief filling obstacle cornor points into main freesapce
     *
     * @param obs obstacle
     * @param freespace_msg main freespace
     */
    void FreespaceHoleInsertion(VisionObsPtr const& obs, Freespace& freespace_msg);

    /**
     * @brief Fixed freespace boundary
     *
     * @param obs obstacle
     * @param map main freespace
     */
    void FreespaceBoundaryCorrection(VisionObsPtr const& obs, std::map<uint32_t, float32_t>& map);

    /**
     * @brief Generate freesapce area
     *
     * @param map freespace point map
     * @param exterior  freesapce container
     */
    void FreespaceMasterGenerate(std::map<uint32_t, float32_t> const& map, FreespaceExterior& exterior);

    /**
     * @brief insert all points into table
     *
     * @param polygon one of freespace polygon
     * @param map freesapce map
     */
    void InsertTable(std::vector<Point2f> const& polygon, std::map<uint32_t, float32_t>& map);

    /**
     * @brief insert all points into table(FreespaceExterior max size is too small )
     *
     * @param polygon one of freespace polygon
     * @param map freesapce map
     */
    void InsertTable(FreespaceExterior const& polygon, std::map<uint32_t, float32_t>& map);

    /**
     * @brief Fill the freesapce area
     *
     * @param map
     */
    void FreespaceMasterFill(std::map<uint32_t, float32_t>& map);

    /**
     * @brief Get the positional relationship between the obstacle and freesapce
     *
     * @param obs
     * @param map
     * @return Relationship
     */
    Relationship GetObstalceFreespaceRelationship(VisionObsPtr const& obs, std::map<uint32_t, holo::float32_t>& map);

    /**
     * @brief Get the Index of map
     *
     * @param point
     * @return uint32_t
     */
    uint32_t GetIndex(holo::Point2f const point);

    /**
     * @brief Preprocessing input
     *
     * @param freespace_msg  freespace
     * @param polygon
     */
    void InputPreprocessing(FreespaceMessage const& freespace_msg, std::vector<Point2f>& polygon);

    void SpatialSmoothing(std::map<uint32_t, holo::float32_t>& map, std::map<uint32_t, holo::float32_t>& new_map);

private:
    float32_t minimum_area_;
    uint32_t  partition_number_;
    uint32_t  number_of_freespace_;
    uint32_t  freespace_obstacle_;
    float32_t min_sample_distacnce_;
    float32_t max_sample_distance_;
    bool_t    use_input_;
    uint8_t   abnormal_position;
};

}  // namespace perception
}  // namespace holo
#endif
