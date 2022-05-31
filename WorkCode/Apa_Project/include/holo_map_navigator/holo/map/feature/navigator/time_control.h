/*!
 *  \brief Time control
 *  \author Hao Wentian(haowentian@holomaitc.com)
 *  \date 2017-09-29
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_TIME_CONTROL_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_TIME_CONTROL_H_

#include <iostream>
#include <vector>

#include <holo/common/timestamp.h>

#include <holo/map/common/common_type_define.h>

// define it if you need debug log
//#define DEBUG_MAP_TIME_STAMPS

namespace holo
{
namespace map
{
/**
 * @brief Class time control
 *
 */
class TimeControl
{
public:
    /**
     * Names of map functions to be managed by this function
     */
    enum class TimeStampItems : holo::int8_t
    {
        ////////// Update here if new module is added ///////////
        MAP_MATCHER                  = 0,   // MapMatcher
        POSITIONER                   = 1,   // Positioner
        ADVISOR                      = 2,   // Advisor
        MAP_INFO                     = 3,   // MapInfo
        GLOBAL_LANE_BOUNDARIES       = 4,   // GlobalLaneBoundaries
        GUIDE_LINE                   = 5,   // GuideLine
        LANE_BOUNDARIES              = 6,   // RoadFrame
        LANE_RECOMMENDER             = 7,   // LaneRecommender
        POI                          = 8,   // POI
        LOCAL_MAP_FREE_SPACE         = 9,   // LocalMapFreeSpaced
        CURRENT_ROAD_INFO            = 10,  // CurrentRoadInfo
        BENCHMARK                    = 11,  // Benchmark
        ROUTING_PREDICT              = 12,  // RoutingPredict
        LANE_FUSION                  = 13,  // LaneFusion
        GEOFENCE_EXTRACTOR           = 14,  // GeofenceExtractor
        ROAD_TYPE_INTERVAL_EXTRACTOR = 15,  // Road type interval extractor
        LAST                         = 16   // Last
        /////////////////////////////////////////////////////////
    };

    /**
     * @brief Constructor
     *
     */
    TimeControl();

    /**
     * @brief Destructor
     *
     */
    ~TimeControl();

    /**
     * @brief Set period of given item
     *
     * @param [in] _type item name
     * @param [in] _period period in units of seconds
     */
    void SetPeriod(const TimeStampItems _type, const double _period);

    /**
     * @brief Get period by time stamp item
     *
     * @param [in] _type time stamp item
     * @return double
     */
    double GetPeriod(const TimeStampItems _type) const;

    /**
     * @brief If time control is initialized
     *
     * @return true
     * @return false
     */
    bool IsTimeControlInitialized();

    /**
     * @brief Check if this is a time epoch to trigger a specific function
     * @param [in] _type function item name
     * @param [in] current_time current time epoch
     * @param [in] _update true if the "last epoch" of this item will be
     *             replaced by current time epoch; false if we only check
     *             without update
     * @return true if we shall trigger this function at current epoch
     */
    bool IsTimerTriggered(const TimeStampItems _type,
                          const holo::common::Timestamp& current_time,
                          const bool _update = true);

private:
    /**
     * @brief Get index from the given item names. This is used to quickly
     *        access the associated item by index
     * @param _type item names
     * @return index of this item in the vector
     */
    Size Index(const TimeStampItems _type) const;

    /**
     * @brief Set time stamp of given item
     * Note the time epoch will be adapted to its period in order to tolerate
     * the late-coming measurements
     *
     * @param [in] _type name of specific item
     * @param [in] _current_time current time epoch
     */
    void SetLastTimeStamp(const TimeStampItems _type,
                          const holo::common::Timestamp& _current_time);

private:
    /// last used time stamps of map functions
    std::vector<holo::common::Timestamp> stamps_;
    /// periods of map functions
    std::vector<double> periods_;
    /// minimal allowed period. Functions lower than this period will not be
    /// invoked.
    const double MIN_PERIOD = 0.005;
    /// names of functions
    std::vector<std::string> names_;
    /// indicator of whether or not the time stamp of each function has been
    /// initialized
    std::vector<bool> initialized_;
    /// stores the first epoch of each function. mainly for debug/test purpose.
    std::vector<holo::common::Timestamp> first_stamps_;
};

inline void TimeControl::SetPeriod(const TimeStampItems _type,
                                   const double _period)
{
    periods_[Index(_type)] = _period;
}

inline double TimeControl::GetPeriod(const TimeStampItems _type) const
{
    return periods_[Index(_type)];
}

inline Size TimeControl::Index(const TimeStampItems _type) const
{
    return static_cast<holo::map::Size>(_type);
}

}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_TIME_CONTROL_H_ */
