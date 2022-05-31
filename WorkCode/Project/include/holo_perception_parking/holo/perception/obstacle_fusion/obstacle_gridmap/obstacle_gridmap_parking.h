/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_gridmap_parking.h
 * @brief This header file defines .
 * @author zhangyuqi(zhangyuqi1@holomatic.com)
 * @date "2022-02-21"
 */

#include <holo/perception/obstacle_fusion/obstacle_gridmap/obstacle_gridmap_utils.h>
namespace holo
{
namespace perception
{

/**
 * @brief Occupy status of hide grid map cell
 *
 */
enum class OccStatus : uint8_t
{
    UNKNOWN = 0U,
    OCCUPY  = 1U,
    FREE    = 2U
};

/**
 * @brief Hide grid map cell
 *
 */
class HideGridMapCell
{
public:
    /**
     * @brief Construct a new Hide Grid Map Cell object
     *
     * @param point Grid point
     * @param class_index classification
     * @param m_status motion status
     * @param velocity velocity
     * @param o_status occStatus
     * @param id
     */
    HideGridMapCell(MapPointGrid const& point, Classification const& class_index, MotionStatus const& m_status,
                    MapPoint const& velocity, OccStatus const& o_status, uint32_t id);

    /**
     * @brief Construct a new Hide Grid Map Cell object
     *
     */
    HideGridMapCell();

    /**
     * @brief operator =
     *
     * @param cell
     * @return HideGridMapCell&
     */
    HideGridMapCell& operator=(HideGridMapCell const& cell);

    /**
     * @brief Set the Point object
     *
     * @param point grid point
     */
    void SetPoint(MapPointGrid const& point);

    /**
     * @brief Set the Status object
     *
     * @param status OccStatus
     */
    void SetStatus(OccStatus const& status);

    /**
     * @brief Set the Class Index object
     *
     * @param class_index classification
     * @param statue Motionstatus
     */
    void SetClassIndex(Classification const& class_index, MotionStatus& statue);

    /**
     * @brief Set the Obstacle I D object
     *
     * @param id obstacle id
     */
    void SetObstacleID(uint32_t id);

    /**
     * @brief Set the Velocity object
     *
     * @param velocity Velocity of obstacle
     */
    void SetVelocity(MapPoint const& velocity);

    /**
     * @brief Set the Occupy Status object
     *
     * @param status
     */
    void SetOccupyStatus(OccStatus const& status);

    /**
     * @brief Initialize clssification  Motionstatue occstatus velocity......
     *
     */
    void Initialize();

    /**
     * @brief Get the Velocity object
     *
     * @return Point2f
     */
    Point2f GetVelocity();

public:
    MapPointGrid   point;
    Classification class_index;
    uint32_t       obstacle_id;
    MotionStatus   motionstatus;
    MapPoint       velocity;
    OccStatus      status;
};

/**
 * @brief Hide grid map
 *
 */
class HideGridMap
{
    using Timestamp = holo::common::Timestamp;
    using Obstacle  = holo::obstacle::ObstacleGeneralT<float32_t>;
    using ObstacleGeneralPtrList =
        holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, 128UL>;  // obstacle_list
    using ObstacleGeneralPtrListMessage = std::shared_ptr<ObstacleGeneralPtrList>;
    using Point2f                       = holo::geometry::Point2f;

public:
    /**
     * @brief Construct a new Hide Grid Map object
     *
     * @param param params of map
     */
    HideGridMap(Params const& param);

    /**
     * @brief Construct a new Hide Grid Map object
     *
     */
    HideGridMap();

    /**
     * @brief Destroy the Hide Grid Map object
     *
     */
    ~HideGridMap();

    /**
     * @brief Set the Timestamps object
     *
     * @param time timestamp
     */
    void SetTimestamps(Timestamp const& time);

    /**
     * @brief Set the Params object
     *
     * @param params params
     */
    void SetParams(Params const& params);

    /**
     * @brief Initialize hide grid map include new cell....
     *
     */
    void InitializeMap();

    /**
     * @brief reInitialize master map
     *
     */
    void ReInitialize();

    /**
     * @brief obstacle list to hide grid map cell
     *
     * @param obs_msg
     * @return std::map<uint32_t,HideGridMap*>
     */
    std::map<uint32_t, HideGridMapCell> InputToCell(ObstacleGeneralPtrList const& obs_msg);

    /**
     * @brief update master map using measurement
     *
     */
    void UpdateMap(std::map<uint32_t, HideGridMapCell> const& measure);

    /**
     * @brief Get the Params object
     *
     * @return Params&
     */
    inline Params& GetParams()
    {
        return this->param_;
    }

    /**
     * @brief Get the Timestamp object
     *
     * @return Timestamp&
     */
    inline Timestamp& GetTimestamp()
    {
        return this->timestamp_;
    }

    /**
     * @brief Get the All Map Cell object
     *
     * @return std::vector<HideGridMapCell*>
     */
    std::vector<HideGridMapCell*>& GetAllMapCell()
    {
        return this->grid_map_master_;
    };

private:
    Timestamp                     timestamp_;
    Params                        param_;
    std::vector<HideGridMapCell*> grid_map_master_;
    bool_t                        initialized_;
};

std::vector<Point3f> FindBoundaryPoint(std::vector<Point3f> const& point_vector);

bool_t IsInteriorPoint(MapPointGrid grid_point, std::vector<Point2f> const& corner_vector, float32_t width,
                       float32_t height, float32_t resulution);

std::vector<Point2f> ObstaclePolygon(holo::obstacle::ObstacleGeneralT<float32_t> const& obs);

std::vector<Point2f> GetRectVertex(Point2f center, float32_t theta, float32_t height, float32_t width);

bool_t MergeMap(std::vector<HideGridMapCell*> const&                          static_array,
                holo::common::GridMap<holo::common::GridMapCell, 100U, 250U>& grid_map);

}  // namespace perception
}  // namespace holo
