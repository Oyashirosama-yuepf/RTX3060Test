/*!
 *  \brief Base, provide map matching related service
 *  \author Liu Qikang (liuqikang@holomaitc.com)
 *  \date 2021-09-23
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
 */

#ifndef HOLO_MAP_COMMON_STRUCT_H_
#define HOLO_MAP_COMMON_STRUCT_H_

#include <holo/common/odometry.h>
#include <holo/map/common/common_macro.h>
#include <holo/map/common/marshal.h>
#include <holo/map/common/common_define.h>

namespace holo
{
namespace map
{
// Check whether the target point is between two lane marks from detected lanes
enum class IndividualCheckResult
{
    kUndefined,  // no lanemarks detected at either one side or both sides
    kTrue,       // point is between two associated lane marks
    kFalse       // point is outside two associated lane marks
};

// Check result
enum class CheckResult
{
    NO_RESULT,
    BEST_CANDIDATE_SAFE,
    BEST_CANDIDATE_UNSAFE
};

// match type
enum class MatchType
{
    TYPE_LINK_MATCH,
    TYPE_LANE_MATCH
};

class IndividualMatchResults
{
public:
    // Constructor
    IndividualMatchResults();
    // Destructor
    ~IndividualMatchResults() = default;

    /**
     * @param [in] _r Another IndividualMatchResults;
     * @return true: if this result is more reliable than r;
     *         false: otherwise.
     */
    bool operator>(const IndividualMatchResults& _r) const;

    /**
     * @param [in] r Another IndividualMatchResults;
     * @return true: if this result is less reliable than r;
     *         false: otherwise.
     */
    bool operator<(const IndividualMatchResults& _r) const;

    /**
     * @brief set match result
     * @param _link_id [in] link id
     * @param _lane_id [in] lane id
     * @param _distance [in] distance
     * @param _match_type [in] match type
     * @param _check_result [in] check result
     */
    void SetMatchResult(const IdType _link_id, const IdType _lane_id, const Distance _distance,
                        const MatchType _match_type, const IndividualCheckResult _check_result);

    // set match link id
    void SetMatchLinkId(const IdType _link_id);
    // get match link id
    IdType GetMatchLinkId() const;

    // set match lane id
    void SetMatchLaneId(const IdType _lane_id);
    // get match lane id
    IdType GetMatchLaneId() const;

    /// set succeeding link ids.
    void SetMatchLinkSucceedings(const VecIdType& _ids);
    /// get succeeding link ids.
    const VecIdType& GetMatchLinkSucceedings() const;

    ///  Set preceding link ids.
    void SetMatchLinkPrecedings(const VecIdType& _ids);
    /// Get preceding link ids.
    const VecIdType& GetMatchLinkPrecedings() const;

    /// set preceding lane ids.
    void SetMatchLanePrecedings(const VecIdType& _ids);
    /// get preceding lane ids
    const VecIdType& GetMatchLanePrecedings() const;

    /// set succeeding lane ids.
    void SetMatchLaneSucceedings(const VecIdType& _ids);
    /// get succeeding lane ids.
    const VecIdType& GetMatchLaneSucceedings() const;

    // set match distance
    void SetMatchDistance(const Distance _distance);
    // get match distance
    Distance GetMatchDistance() const;

    // set match type
    void SetMatchType(const MatchType _match_type);
    // get match type
    MatchType GetMatchType() const;

    // set match check result
    void SetMatchCheckResult(const IndividualCheckResult _check_result);
    // get match check result
    IndividualCheckResult GetMatchCheckResult() const;

    /**
     * @brief Check if target link is connected with current map-matched result.
     * @param [in] _id Target link id.
     * @return true Target link is connected with current map-matched result;
     *         false Otherwise.
     */
    bool IsLinkConnected(const IdType _id);

    /**
     * @brief Check if target lane is connected with current map-matched result.
     * @param [in] _id Target lane id.
     * @return true Target lane is connected with current amp-matched result;
     *         false Otherwise.
     */
    bool IsLaneConnected(const IdType _id);

private:
    IdType link_id_;
    IdType lane_id_;

    /// Preceding link ids of matched link.
    VecIdType link_precedings_;
    /// Succeeding link ids of matched link.
    VecIdType link_succeedings_;

    /// Preceding lane ids of matched lane.
    VecIdType lane_precedings_;
    /// Succeding lane ids of matched lane.
    VecIdType lane_succeedings_;

    /**
     * when match_type is link match,  the distance means
     * the length of ccp to link center line's projective point
     */
    Distance distance_;
    // when current link have no lanes, match_type will be set up TYPE_LINK_MATCH
    MatchType             match_type_;
    IndividualCheckResult check_result_;
};
/**
 * @brief A package for map matching info.
 */
struct MapMatchInfo
{
    bool     on_map      = false;  ///< True: the target point is matched on map, False: otherwise.
    IdType link_id     = 0UL;    ///< Current link id;
    IdType lane_id     = 0UL;    ///< Current lane id;
    SeqNumber sequence    = 0;      ///< Current lane sequence;
    Distance distance    = 0.0;    ///< Distance between current position and current link end;
    Distance link_length = 0.0;    ///< Length of current link.
    Distance  dist_to_middle = 0.0f; ///> Distnace to middle line
    Distance  dist_to_begin  = 0.0f; ///> Distance to begin of link
    Distance  dist_to_end    = 0.0f;  ///> Distance to begin of link

    holo::map::format::GeoPoint point;     ///< Current position of car.
    holo::common::Coordinate    coord;     ///< Coordinate reference system.
    holo::common::Odometryd     odometry;  ///< Odometry of position

    /**
     * @brief Format MapMatchInfo object to json string.
     * @param [in] _info MapMatchInfo object from best result of map matcher.
     * @return Json string.
     */
    static std::string FormatToString(const MapMatchInfo& _info)
    {
        std::stringstream stream;
        stream << "{"
               << "\"lane_id\": " << _info.lane_id << ", \"link_id\": " << _info.link_id
               << ", \"link_length\": " << _info.link_length << ", \"point\": " << marshal::FormatToString(_info.point)
               << ", \"distance\":" << _info.distance;
        stream << "}";
        return stream.str();
    }
};

// Information for lane match result
class MatchedResult
{
public:
    MatchedResult() : trustable_(CheckResult::NO_RESULT)
    {
    }

    void clear()
    {
        results_.clear();
        trustable_ = CheckResult::NO_RESULT;
    }

    std::vector<IndividualMatchResults> results_;
    CheckResult                         trustable_;
};
typedef std::shared_ptr<MatchedResult> PtrMatchedResult;
/**
 * @brief Class map matcher for map matching related service
 *
 */
struct MapMatcher
{
    /**
     * @brief Definition of map matcher input
     *
     */
    struct Input
    {
        /// Odometryd
        holo::common::Odometryd odo;
        // To string
        std::string ToString() const
        {
            std::ostringstream oss;
            oss << "Position: (" << odo.GetPose().GetTranslation().GetX() << ", "
                << odo.GetPose().GetTranslation().GetY() << ", " << odo.GetPose().GetTranslation().GetZ() << ")";
            return oss.str();
        }
    };

    /**
     * @brief Definition of map matcher output
     *
     */
    struct Output
    {
        /// Matched result
        PtrMatchedResult ptr_match_result = nullptr;
        /// Whether current position is on map or not
        bool on_map = false;
        /// Whether current matched result is safe (with high certainty) or not
        bool result_safe = false;
        /// Lane id
        IdType lane_id = 0UL;
        /// Link id
        IdType link_id = 0UL;
        /// Odometryd
        ::holo::common::Odometryd odometry;
        // To string
        std::string ToString() const
        {
            std::ostringstream oss;
            oss << "on_map: " << on_map << "; ";
            oss << " result_safe: " << result_safe;
            oss << " link_id: " << link_id << "; ";
            oss << " lane_id: " << lane_id;
            return oss.str();
        }
    };
    /**
     * @brief Format Output object to a JSON string.
     *
     * @param[in] output Output object.
     * @return A JSON string.
     */
    static std::string FormatToString(const MapMatcher::Output& output)
    {
        std::stringstream stream;
        stream << "{\"onmap\":" << output.on_map << ", \"reliable\":" << output.result_safe
               << ", \"link_id\":" << output.link_id << ", \"lane_id\":" << output.lane_id
               << ", \"point\":" << marshal::FormatToString(output.odometry.GetPose().GetTranslation()) << "}";
        return stream.str();
    }
};

typedef std::shared_ptr<MapMatcher> PtrMapMatcher;

}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_COMMON_STRUCT_H_ */