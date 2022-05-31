/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_object.h
 * @brief define object infos for local map graph.
 * @author chanqiliang(chanqiliang@holomaitc.com)
 * @date 2021-12-07
 */

#ifndef HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_OBJECT_H_
#define HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_OBJECT_H_

#include <holo/map/feature/local_map_graph/lmg_common.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace graph
{
/**
 * @addtogroup graph
 *
 * @{
 */

/**
 * @brief Define stopline
 */
template <typename FeatureIdT, typename PointT, size_t LANE_ID_SIZE = 64U, size_t INTERVAL_SIZE = 255U,
          size_t LINE_SIZE = 1024U>
class StopLine : public FeatureBase<FeatureIdT>
{
public:
    using FeatureIdType      = FeatureIdT;
    using PointType          = PointT;
    using LaneIdVectorType   = holo::container::Vector<FeatureIdType, LANE_ID_SIZE>;
    using HistInfoVectorType = holo::container::Vector<HistInfo, INTERVAL_SIZE>;
    using Point3dVectorType  = holo::container::Vector<PointType, LINE_SIZE>;

    StopLine() : FeatureBase<FeatureIdType>(holo::map::navigator::graph::FeatureType::FEATURE_TYPE_STOPLINE)
    {
    }
    ~StopLine()               = default;
    StopLine(StopLine const&) = default;
    StopLine(StopLine&&)      = delete;
    StopLine& operator=(StopLine const&) = default;
    StopLine& operator=(StopLine&&) = delete;

    /**
     * @brief Set lane ids.
     *
     * @param lane_ids lane ids.
     */
    void SetLaneIds(LaneIdVectorType const& lane_ids) noexcept
    {
        this->lane_ids_ = lane_ids;
    }

    /**
     * @brief Get lane ids.
     *
     * @return Lane ids.
     */
    LaneIdVectorType GetLaneIds() const noexcept
    {
        return this->lane_ids_;
    }

    /**
     * @brief Set hist infos.
     *
     * @param hist_infos hist infos.
     */
    void SetHistInfos(HistInfoVectorType const& hist_infos) noexcept
    {
        this->hist_infos_ = hist_infos;
    }

    /**
     * @brief Get hist infos.
     *
     * @return Hist infos.
     */
    const HistInfoVectorType& GetHistInfos() const noexcept
    {
        return this->hist_infos_;
    }

    /**
     * @brief Set stop line.
     *
     * @param stop_line stop line.
     */
    void SetStopLine(Point3dVectorType const& stop_line) noexcept
    {
        this->stop_line_ = stop_line;
    }

    /**
     * @brief Get stop line.
     *
     * @return Stop line.
     */
    Point3dVectorType GetStopLine() const noexcept
    {
        return this->stop_line_;
    }

private:
    HistInfoVectorType hist_infos_;  /// current element hist infos.
    LaneIdVectorType   lane_ids_;    /// lane id sequence.
    Point3dVectorType  stop_line_;   /// points for stop line.
};

/**
 * @brief Define marking
 */
template <typename FeatureIdT, typename PointT, typename PoseT, size_t INTERVAL_SIZE = 255U>
class Marking : public FeatureBase<FeatureIdT>
{
public:
    using FeatureIdType      = FeatureIdT;
    using PointType          = PointT;
    using Bbox3DType         = Bbox3D<PoseT, holo::float32_t>;
    using HistInfoVectorType = holo::container::Vector<HistInfo, INTERVAL_SIZE>;

    /**
     * @brief Define mark type of concrete lane, according to
     * https://holomatic.feishu.cn/sheets/shtcnHUH0QhRQX2y00HMCUBcmAc?sheet=13iIIV
     */
    enum class MarkType : uint8_t
    {
        MARK_TYPE_UNKNOWN                  = 0U,
        MARK_TYPE_TEXT                     = 1U,
        MARK_TYPE_STRAIGHT                 = 2U,
        MARK_TYPE_STRAIGHT_OR_LEFT         = 3U,
        MARK_TYPE_STRAIGHT_OR_RIGHT        = 4U,
        MARK_TYPE_STRAIGHT_U_TURN          = 5U,
        MARK_TYPE_LEFT_TURN                = 6U,
        MARK_TYPE_LEFT_TURN_U_TURN         = 7U,
        MARK_TYPE_LEFT_TURN_AND_INTERFLOW  = 8U,
        MARK_TYPE_RIGHT_TURN               = 9U,
        MARK_TYPE_RIGHT_TURN_AND_INTERFLOW = 10U,
        MARK_TYPE_LEFT_RIGHT_TURN          = 11U,
        MARK_TYPE_U_TURN                   = 12U,
        MARK_TYPE_NO_LEFT_TURN             = 13U,
        MARK_TYPE_NO_RIGHT_TURN            = 14U,
        MARK_TYPE_NO_U_TURN                = 15U,
        MARK_TYPE_STRAIGHT_LEFT_RIGHT      = 16U,
        MARK_TYPE_STRAIGHT_U_LEFT          = 17U,
        MARK_TYPE_RIGHT_U_TURN             = 18U,
        MARK_TYPE_MAX_SPEEDLIMIT           = 19U,
        MARK_TYPE_MIN_SPEEDLIMIT           = 20U,
        MARK_TYPE_TIME                     = 21U,
        MARK_TYPE_CHECK_FOLLOWING_DISTANCE = 22U,
        MARK_TYPE_STOP_TO_GIVEWAY          = 23U,
        MARK_TYPE_SLOWDOWN_TO_GIVEWAY      = 24U,
        MARK_TYPE_STOP_MARK                = 25U,
        MARK_TYPE_NETS                     = 26U,
        MARK_TYPE_OTHERS                   = 255U
    };

    /**
     * @brief Define color type
     */
    enum class ColorType : uint8_t
    {
        COLOR_TYPE_UNKNOWN = 0U,
        COLOR_TYPE_WHITE   = 1U,
        COLOR_TYPE_YELLOW  = 2U,
        COLOR_TYPE_ORANGE  = 3U,
        COLOR_TYPE_BLUE    = 4U,
        COLOR_TYPE_OTHER   = 5U
    };

    /**
     * @brief Define detection status
     */
    enum class DetectionStatus : uint8_t
    {
        PURE_DETECTION = 0U,
        PURE_HD_MAP    = 1U,
        HD_MAP_FUSION  = 2U
    };

    Marking() : FeatureBase<FeatureIdType>(holo::map::navigator::graph::FeatureType::FEATURE_TYPE_MARKING)
    {
    }
    ~Marking()              = default;
    Marking(Marking const&) = default;
    Marking(Marking&&)      = delete;
    Marking& operator=(Marking const&) = default;
    Marking& operator=(Marking&&) = delete;

    /**
     * @brief Set lane id.
     *
     * @param lane_id lane id, invalid lane id: 0.
     */
    void SetLaneId(FeatureIdType const& lane_id) noexcept
    {
        this->lane_id_ = lane_id;
    }

    /**
     * @brief Get lane id.
     *
     * @return Lane id.
     */
    FeatureIdType GetLaneId() const noexcept
    {
        return this->lane_id_;
    }

    /**
     * @brief Set hist infos.
     *
     * @param hist_infos hist infos.
     */
    void SetHistInfos(HistInfoVectorType const& hist_infos) noexcept
    {
        this->hist_infos_ = hist_infos;
    }

    /**
     * @brief Get hist infos.
     *
     * @return Hist infos.
     */
    const HistInfoVectorType& GetHistInfos() const noexcept
    {
        return this->hist_infos_;
    }

    /**
     * @brief Set position.
     *
     * @param position position.
     */
    void SetPosition(PointType const& position) noexcept
    {
        this->position_ = position;
    }

    /**
     * @brief Get position.
     *
     * @return Position.
     */
    PointType GetPosition() const noexcept
    {
        return this->position_;
    }

    /**
     * @brief Set bbox 3d.
     *
     * @param bbox_3d bbox 3d.
     */
    void SetBbox3d(Bbox3DType const& bbox_3d) noexcept
    {
        this->bbox_3d_ = bbox_3d;
    }

    /**
     * @brief Get bbox 3d.
     *
     * @return Bbox 3d.
     */
    const Bbox3DType& GetBbox3d() const noexcept
    {
        return this->bbox_3d_;
    }

    /**
     * @brief Set marking.
     *
     * @param mark marking.
     */
    void SetMark(MarkType const mark) noexcept
    {
        this->mark_ = mark;
    }

    /**
     * @brief Get marking.
     *
     * @return Marking.
     */
    MarkType GetMark() const noexcept
    {
        return this->mark_;
    }

    /**
     * @brief Set color.
     *
     * @param color color.
     */
    void SetColor(ColorType const color) noexcept
    {
        this->color_ = color;
    }

    /**
     * @brief Get color.
     *
     * @return Color.
     */
    ColorType GetColor() const noexcept
    {
        return this->color_;
    }

    /**
     * @brief Set semantic info.
     *
     * @param semantic_info semantic info.
     */
    void SetSemanticInfo(std::string const semantic_info) noexcept
    {
        this->semantic_info_ = semantic_info;
    }

    /**
     * @brief Get semantic info.
     *
     * @return Semantic info.
     */
    std::string GetSemanticInfo() const noexcept
    {
        return this->semantic_info_;
    }

    /**
     * @brief Set confidence.
     *
     * @param confidence confidence.
     */
    void SetConfidence(holo::float32_t const confidence) noexcept
    {
        this->confidence_ = confidence;
    }

    /**
     * @brief Get confidence.
     *
     * @return Confidence.
     */
    holo::float32_t GetConfidence() const noexcept
    {
        return this->confidence_;
    }

    /**
     * @brief Set lane index.
     *
     * @param lane_index lane index.
     */
    void SetLaneIndex(holo::int32_t const lane_index) noexcept
    {
        this->lane_index_ = lane_index;
    }

    /**
     * @brief Get lane index.
     *
     * @return Lane index.
     */
    holo::int32_t GetLaneIndex() const noexcept
    {
        return this->lane_index_;
    }

    /**
     * @brief Set detection status.
     *
     * @param detection_status detection status.
     */
    void SetDetectionStatus(DetectionStatus const detection_status) noexcept
    {
        this->detection_status_ = detection_status;
    }

    /**
     * @brief Get detection status.
     *
     * @return Detection status.
     */
    DetectionStatus GetDetectionStatus() const noexcept
    {
        return this->detection_status_;
    }

private:
    HistInfoVectorType hist_infos_;
    FeatureIdType      lane_id_ = static_cast<FeatureIdType>(0);  /// lane id, invalid lane id: 0.
    PointType          position_;                                 /// marking position.
    Bbox3DType         bbox_3d_;                                  /// bounding box 3d.
    MarkType           mark_  = MarkType::MARK_TYPE_UNKNOWN;      /// marking type.
    ColorType          color_ = ColorType::COLOR_TYPE_UNKNOWN;    /// color type.
    std::string        semantic_info_;                            /// semantic info.
    holo::float32_t    confidence_       = 0.0;
    holo::int32_t      lane_index_       = -1;                            /// marking to lane index.
    DetectionStatus    detection_status_ = DetectionStatus::PURE_HD_MAP;  /// detection status.
};

/**
 * @brief Define sign
 */
template <typename FeatureIdT, typename PointT, size_t INTERVAL_SIZE = 255U>
class Sign : public FeatureBase<FeatureIdT>
{
public:
    using FeatureIdType      = FeatureIdT;
    using PointType          = PointT;
    using HistInfoVectorType = holo::container::Vector<HistInfo, INTERVAL_SIZE>;

    /**
     * @brief Define sign type of object, according to
     *  https://holomatic.feishu.cn/sheets/shtcnHUH0QhRQX2y00HMCUBcmAc?sheet=13iIIV
     */
    enum class SignType : uint8_t
    {
        SIGN_TYPE_UNKNOWN                         = 0U,
        SIGN_TYPE_NO_ENTRY                        = 1U,
        SIGN_TYPE_NO_PARKING                      = 2U,
        SIGN_TYPE_NO_LEFT                         = 3U,
        SIGN_TYPE_NO_RIGHT_TURN                   = 4U,
        SIGN_TYPE_NO_TURN_AROUND                  = 5U,
        SIGN_TYPE_MAX_SPEEDLIMIT_5                = 6U,
        SIGN_TYPE_MAX_SPEEDLIMIT_10               = 7U,
        SIGN_TYPE_MAX_SPEEDLIMIT_20               = 8U,
        SIGN_TYPE_MAX_SPEEDLIMIT_30               = 9U,
        SIGN_TYPE_MAX_SPEEDLIMIT_40               = 10U,
        SIGN_TYPE_MAX_SPEEDLIMIT_50               = 11U,
        SIGN_TYPE_MAX_SPEEDLIMIT_60               = 12U,
        SIGN_TYPE_MAX_SPEEDLIMIT_70               = 13U,
        SIGN_TYPE_MAX_SPEEDLIMIT_80               = 14U,
        SIGN_TYPE_MAX_SPEEDLIMIT_90               = 15U,
        SIGN_TYPE_MAX_SPEEDLIMIT_100              = 16U,
        SIGN_TYPE_MAX_SPEEDLIMIT_110              = 17U,
        SIGN_TYPE_MAX_SPEEDLIMIT_120              = 18U,
        SIGN_TYPE_MIN_SPEEDLIMIT_50               = 19U,
        SIGN_TYPE_MIN_SPEEDLIMIT_60               = 20U,
        SIGN_TYPE_MIN_SPEEDLIMIT_70               = 21U,
        SIGN_TYPE_MIN_SPEEDLIMIT_80               = 22U,
        SIGN_TYPE_MIN_SPEEDLIMIT_90               = 23U,
        SIGN_TYPE_MIN_SPEEDLIMIT_100              = 24U,
        SIGN_TYPE_MIN_SPEEDLIMIT_110              = 25U,
        SIGN_TYPE_REMOVE_MAX_SPEEDLIMIT_10        = 26U,
        SIGN_TYPE_REMOVE_MAX_SPEEDLIMIT_20        = 27U,
        SIGN_TYPE_REMOVE_MAX_SPEEDLIMIT_30        = 28U,
        SIGN_TYPE_REMOVE_MAX_SPEEDLIMIT_40        = 29U,
        SIGN_TYPE_REMOVE_MAX_SPEEDLIMIT_50        = 30U,
        SIGN_TYPE_REMOVE_MAX_SPEEDLIMIT_60        = 31U,
        SIGN_TYPE_REMOVE_MAX_SPEEDLIMIT_70        = 32U,
        SIGN_TYPE_REMOVE_MAX_SPEEDLIMIT_80        = 33U,
        SIGN_TYPE_REMOVE_MAX_SPEEDLIMIT_90        = 34U,
        SIGN_TYPE_REMOVE_MAX_SPEEDLIMIT_100       = 35U,
        SIGN_TYPE_REMOVE_MAX_SPEEDLIMIT_110       = 36U,
        SIGN_TYPE_REMOVE_MAX_SPEEDLIMIT_120       = 37U,
        SIGN_TYPE_NARROW_ON_LEFT                  = 38U,
        SIGN_TYPE_NARROW_ON_RIGHT                 = 39U,
        SIGN_TYPE_NARROW_ON_BOTH_SIDES            = 40U,
        SIGN_TYPE_MERGE_ON_LEFT                   = 41U,
        SIGN_TYPE_MERGE_ON_RIGHT                  = 42U,
        SIGN_TYPE_JUNCTION                        = 43U,
        SIGN_TYPE_LEFT_JUNCTION                   = 44U,
        SIGN_TYPE_RIGHT_JUNCTION                  = 45U,
        SIGN_TYPE_CROSS                           = 46U,
        SIGN_TYPE_ROUNDABOUT                      = 47U,
        SIGN_TYPE_LEFT_SHARP_TURN                 = 48U,
        SIGN_TYPE_RIGHT_SHARP_TURN                = 49U,
        SIGN_TYPE_CONSECUTIVE_CURVES              = 50U,
        SIGN_TYPE_ATTENTION_DANGEROUS             = 51U,
        SIGN_TYPE_ATTENTION_PEDESTRIAN            = 52U,
        SIGN_TYPE_ATTENTION_KIDS                  = 53U,
        SIGN_TYPE_ATTENTION_NONMOTOR_VEHICLE      = 54U,
        SIGN_TYPE_ATTENTION_CROSS_WIND            = 55U,
        SIGN_TYPE_ATTENTION_SIGNAL_LAMP           = 56U,
        SIGN_TYPE_ATTENTION_SLOWDOWN              = 57U,
        SIGN_TYPE_STOP_TO_GIVEWAY                 = 58U,
        SIGN_TYPE_SLOWDOWN_TO_GIVEWAY             = 59U,
        SIGN_TYPE_CAR_MEETING_TO_GIVEWAY          = 60U,
        SIGN_TYPE_NO_PASSING                      = 61U,
        SIGN_TYPE_NO_LONG_DRIVING                 = 62U,
        SIGN_TYPE_NO_MOTOR_VEHICLE                = 63U,
        SIGN_TYPE_NO_TOOTING                      = 64U,
        SIGN_TYPE_MAX_HEADROOM                    = 65U,
        SIGN_TYPE_MAX_WEIGHT                      = 66U,
        SIGN_TYPE_MAX_WIDTH                       = 67U,
        SIGN_TYPE_NO_OVERTAKING                   = 68U,
        SIGN_TYPE_REMOVE_NO_OVERTAKING            = 69U,
        SIGN_TYPE_MERGE                           = 70U,
        SIGN_TYPE_TRAFFIC_GUIDE_PEDESTRIAN        = 71U,
        SIGN_TYPE_LANES_DECREASE                  = 72U,
        SIGN_TYPE_CONSTRUCTION                    = 73U,
        SIGN_TYPE_CHANGE_ROAD                     = 74U,
        SIGN_TYPE_RAMP_SPEEDLIMIT                 = 75U,
        SIGN_TYPE_VARIABLE                        = 76U,
        SIGN_TYPE_COMBINATION_OF_SIGNS            = 77U,
        SIGN_TYPE_CAMELBACK_BRIDGE                = 78U,
        SIGN_TYPE_HIGHWAY_END                     = 79U,
        SIGN_TYPE_RAMP                            = 80U,
        SIGN_TYPE_TUNNEL                          = 81U,
        SIGN_TYPE_TURN_ON_LIGHT_IN_TUNNEL         = 82U,
        SIGN_TYPE_UP_HILL                         = 83U,
        SIGN_TYPE_DOWN_HILL                       = 84U,
        SIGN_TYPE_ACCIDENT_BLACK_SPOT             = 85U,
        SIGN_TYPE_VILLAGE                         = 86U,
        SIGN_TYPE_NO_MOTORCYCLE                   = 87U,
        SIGN_TYPE_NO_TRUCK                        = 88U,
        SIGN_TYPE_NO_BUS                          = 89U,
        SIGN_TYPE_NO_NONMOTORCYCLE                = 90U,
        SIGN_TYPE_NO_VEHICLE_WITH_DANGEROUS_GOODS = 91U,
        SIGN_TYPE_STRAIGHT                        = 92U,
        SIGN_TYPE_TURN_LEFT                       = 93U,
        SIGN_TYPE_TURN_RIGHT                      = 94U,
        SIGN_TYPE_KEEP_TO_RIGHT                   = 95U,
        SIGN_TYPE_KEEP_TO_LEFT                    = 96U,
        SIGN_TYPE_DRIVE_ON_ROUNDABOUT             = 97U,
        SIGN_TYPE_WALK                            = 98U,
        SIGN_TYPE_HONK                            = 99U,
        SIGN_TYPE_MOTOR_VEHICLE                   = 100U,
        SIGN_TYPE_NONMOTOR_VEHICLE                = 101U,
        SIGN_TYPE_PEDESTRIAN_CROSSING             = 102U,
        SIGN_TYPE_U_TURN_LANE                     = 103U,
        SIGN_TYPE_PARKING_LOT                     = 104U,
        SIGN_TYPE_PASSING_BAY                     = 105U,
        SIGN_TYPE_AUXILIARY                       = 106U,
        SIGN_TYPE_ETC_AND_MTC                     = 107U,
        SIGN_TYPE_TURN_LEFT_LANE                  = 108U,
        SIGN_TYPE_TURN_RIGHT_LANE                 = 109U,
        SIGN_TYPE_TURN_AROUND_LANE                = 110U,
        SIGN_TYPE_LEFT_AND_STRAIGHT_LANE          = 111U,
        SIGN_TYPE_RIGHT_AND_STRAIGHT_LANE         = 112U,
        SIGN_TYPE_LEFT_AND_AROUND_LANE            = 113U,
        SIGN_TYPE_MOTOR_VEHICLE_LANE              = 114U,
        SIGN_TYPE_NONMOTOR_VEHICLE_LANE           = 115U,
        SIGN_TYPE_BUS_LANE                        = 116U,
        SIGN_TYPE_HOV_LANE                        = 117U,
        SIGN_TYPE_ROCKS                           = 118U,
        SIGN_TYPE_SCHOOL_ZONE                     = 119U,
        SIGN_TYPE_RANGE_SPEEDLIMIT                = 120U,
        SIGN_TYPE_ELECTRONIC_EYE                  = 121U,
        SIGN_TYPE_ESCAPE_LANE                     = 122U,
        SIGN_TYPE_TRAMCAR_RANGE                   = 123U,
        SIGN_TYPE_ALLOW_TURN_RIGHT_ON_RED_LIGHT   = 124U,
        SIGN_TYPE_NO_TURN_RIGHT_ON_RED_LIGHT      = 125U,
        SIGN_TYPE_TOURIST_SPOT                    = 126U,
        SIGN_TYPE_OTHERS                          = 255U
    };

    /**
     * @brief Define detection status
     */
    enum class DetectionStatus : uint8_t
    {
        PURE_DETECTION = 0U,
        PURE_HD_MAP    = 1U,
        HD_MAP_FUSION  = 2U
    };

    Sign() : FeatureBase<FeatureIdType>(holo::map::navigator::graph::FeatureType::FEATURE_TYPE_SIGN)
    {
    }
    ~Sign()           = default;
    Sign(Sign const&) = default;
    Sign(Sign&&)      = delete;
    Sign& operator=(Sign const&) = default;
    Sign& operator=(Sign&&) = delete;

    /**
     * @brief Set lane id.
     *
     * @param lane_id lane id, invalid lane id: 0.
     */
    void SetLaneId(FeatureIdType const& lane_id) noexcept
    {
        this->lane_id_ = lane_id;
    }

    /**
     * @brief Get lane id.
     *
     * @return Lane id.
     */
    FeatureIdType GetLaneId() const noexcept
    {
        return this->lane_id_;
    }

    /**
     * @brief Set hist infos.
     *
     * @param hist_infos hist infos.
     */
    void SetHistInfos(HistInfoVectorType const& hist_infos) noexcept
    {
        this->hist_infos_ = hist_infos;
    }

    /**
     * @brief Get hist infos.
     *
     * @return Hist infos.
     */
    const HistInfoVectorType& GetHistInfos() const noexcept
    {
        return this->hist_infos_;
    }

    /**
     * @brief Set sign type.
     *
     * @param sign sign type.
     */
    void SetSignType(SignType const sign_type) noexcept
    {
        this->sign_type_ = sign_type;
    }

    /**
     * @brief Get sign type.
     *
     * @return Sign type.
     */
    SignType GetSignType() const noexcept
    {
        return this->sign_type_;
    }

    /**
     * @brief Set position.
     *
     * @param position position.
     */
    void SetPosition(PointType const& position) noexcept
    {
        this->position_ = position;
    }

    /**
     * @brief Get position.
     *
     * @return Position.
     */
    PointType GetPosition() const noexcept
    {
        return this->position_;
    }

    /**
     * @brief Set lane index.
     *
     * @param lane_index lane index.
     */
    void SetLaneIndex(holo::int32_t const lane_index) noexcept
    {
        this->lane_index_ = lane_index;
    }

    /**
     * @brief Get lane index.
     *
     * @return Lane index.
     */
    holo::int32_t GetLaneIndex() const noexcept
    {
        return this->lane_index_;
    }

    /**
     * @brief Set detection status.
     *
     * @param detection_status detection status.
     */
    void SetDetectionStatus(DetectionStatus const detection_status) noexcept
    {
        this->detection_status_ = detection_status;
    }

    /**
     * @brief Get detection status.
     *
     * @return Detection status.
     */
    DetectionStatus GetDetectionStatus() const noexcept
    {
        return this->detection_status_;
    }

private:
    FeatureIdType      lane_id_ = static_cast<FeatureIdType>(0);  /// lane id, invalid lane id: 0.
    HistInfoVectorType hist_infos_;
    SignType           sign_type_ = SignType::SIGN_TYPE_UNKNOWN;          /// sign type.
    PointType          position_;                                         /// sign position.
    holo::int32_t      lane_index_       = -1;                            /// sign to lane index.
    DetectionStatus    detection_status_ = DetectionStatus::PURE_HD_MAP;  /// detection status.
};

/**
 * @brief Define signal
 */
struct Signal
{
    /**
     * @brief Define signal type, according to
     * https://holomatic.feishu.cn/sheets/shtcnHUH0QhRQX2y00HMCUBcmAc?sheet=13iIIV
     */
    enum class SignalType : uint8_t
    {
        SIGNAL_TYPE_UNKNOWN             = 0U,
        SIGNAL_TYPE_CIRCLE              = 1U,
        SIGNAL_TYPE_PEDESTRIAN          = 2U,
        SIGNAL_TYPE_TURN_LEFT           = 3U,
        SIGNAL_TYPE_STRAIGHT            = 4U,
        SIGNAL_TYPE_TURN_RIGHT          = 5U,
        SIGNAL_TYPE_TURN_U              = 6U,
        SIGNAL_TYPE_TURN_LEFT_STRAIGHT  = 7U,
        SIGNAL_TYPE_TURN_LEFT_U         = 8U,
        SIGNAL_TYPE_TURN_RIGHT_STRAIGHT = 9U,
        SIGNAL_TYPE_BICYCLE             = 10U,
        SIGNAL_TYPE_NO_PASSING          = 11U,
        SIGNAL_TYPE_TIMER               = 12U,
        SIGNAL_TYPE_PASSING             = 13U
    };

    /**
     * @brief Define signal status
     */
    enum class SignalStatus : uint8_t
    {
        SIGNAL_STATUS_UNKNOW = 0U,
        SIGNAL_STATUS_BLACK  = 1U,
        SIGNAL_STATUS_GREEN  = 2U,
        SIGNAL_STATUS_YELLOW = 3U,
        SIGANLE_STATUS_RED   = 4U
    };
    SignalType   signal_type   = SignalType::SIGNAL_TYPE_UNKNOWN;
    SignalStatus signal_status = SignalStatus::SIGNAL_STATUS_UNKNOW;
};

/**
 * @brief Define Light
 */
template <typename FeatureIdT, typename PoseT, size_t LANE_ID_SIZE = 64U, size_t INTERVAL_SIZE = 255U,
          size_t SIGNAL_SIZE = 255U>
class Light : public FeatureBase<FeatureIdT>
{
public:
    using FeatureIdType      = FeatureIdT;
    using PoseType           = PoseT;
    using Bbox3DType         = Bbox3D<PoseType, holo::float32_t>;
    using LaneIdVectorType   = holo::container::Vector<FeatureIdType, LANE_ID_SIZE>;
    using HistInfoVectorType = holo::container::Vector<HistInfo, INTERVAL_SIZE>;
    using SignalVectorType   = holo::container::Vector<Signal, SIGNAL_SIZE>;

    Light() : FeatureBase<FeatureIdType>(holo::map::navigator::graph::FeatureType::FEATURE_TYPE_LIGHT)
    {
    }
    ~Light()            = default;
    Light(Light const&) = default;
    Light(Light&&)      = delete;
    Light& operator=(Light const&) = default;
    Light& operator=(Light&&) = delete;

    /**
     * @brief Set lane id.
     *
     * @param lane_id lane id, invalid lane id: 0.
     */
    void SetLaneId(FeatureIdType const& lane_id) noexcept
    {
        this->lane_id_ = lane_id;
    }

    /**
     * @brief Get lane id.
     *
     * @return Lane id.
     */
    FeatureIdType GetLaneId() const noexcept
    {
        return this->lane_id_;
    }

    /**
     * @brief Set lane ids.
     *
     * @param lane_ids lane ids.
     */
    void SetLaneIds(LaneIdVectorType const& lane_ids) noexcept
    {
        this->lane_ids_ = lane_ids;
    }

    /**
     * @brief Get lane ids.
     *
     * @return Lane ids.
     */
    LaneIdVectorType GetLaneIds() const noexcept
    {
        return this->lane_ids_;
    }

    /**
     * @brief Set hist infos.
     *
     * @param hist_infos hist infos.
     */
    void SetHistInfos(HistInfoVectorType const& hist_infos) noexcept
    {
        this->hist_infos_ = hist_infos;
    }

    /**
     * @brief Get hist infos.
     *
     * @return Hist infos.
     */
    const HistInfoVectorType& GetHistInfos() const noexcept
    {
        return this->hist_infos_;
    }

    /**
     * @brief Set is detected by camera.
     *
     * @param detected_by_camera is detected by camera.
     */
    void SetIsDetectedByCamera(holo::bool_t const detected_by_camera) noexcept
    {
        this->detected_by_camera_ = detected_by_camera;
    }

    /**
     * @brief Get is detected by camera.
     *
     * @return Is detected by camera.
     */
    holo::bool_t GetIsDetectedByCamera() const noexcept
    {
        return this->detected_by_camera_;
    }

    /**
     * @brief Set got only by camera.
     *
     * @param got_only_by_camera got only by camera.
     */
    void SetGotOnlyByCamera(holo::bool_t const got_only_by_camera) noexcept
    {
        this->got_only_by_camera_ = got_only_by_camera;
    }

    /**
     * @brief Get got only by camera.
     *
     * @return Got only by camera.
     */
    holo::bool_t GetGotOnlyByCamera() const noexcept
    {
        return this->got_only_by_camera_;
    }

    /**
     * @brief Set count down second.
     *
     * @param count_down_second count down second.
     */
    void SetCountDownSecond(holo::int16_t const count_down_second) noexcept
    {
        this->count_down_second_ = count_down_second;
    }

    /**
     * @brief Get count down second.
     *
     * @return Count down second.
     */
    holo::int16_t GetCountDownSecond() const noexcept
    {
        return this->count_down_second_;
    }

    /**
     * @brief Set confidence.
     *
     * @param confidence confidence.
     */
    void SetConfidence(holo::float32_t const confidence) noexcept
    {
        this->confidence_ = confidence;
    }

    /**
     * @brief Get confidence.
     *
     * @return Confidence.
     */
    holo::float32_t GetConfidence() const noexcept
    {
        return this->confidence_;
    }

    /**
     * @brief Set bbox 3d.
     *
     * @param bbox_3d bbox 3d.
     */
    void SetBbox3d(Bbox3DType const& bbox_3d) noexcept
    {
        this->bbox_3d_ = bbox_3d;
    }

    /**
     * @brief Get bbox 3d.
     *
     * @return Bbox 3d.
     */
    const Bbox3DType& GetBbox3d() const noexcept
    {
        return this->bbox_3d_;
    }

    /**
     * @brief Set signals.
     *
     * @param signals signals.
     */
    void SetSignals(SignalVectorType const& signals) noexcept
    {
        this->signals_ = signals;
    }

    /**
     * @brief Get signals.
     *
     * @return Signals.
     */
    const SignalVectorType& GetSignals() const noexcept
    {
        return this->signals_;
    }

private:
    HistInfoVectorType hist_infos_;
    FeatureIdType      lane_id_ = static_cast<FeatureIdType>(0);
    LaneIdVectorType   lane_ids_;
    holo::bool_t       detected_by_camera_ = true;
    holo::bool_t       got_only_by_camera_ = true;
    holo::int16_t      count_down_second_  = -1;
    holo::float32_t    confidence_         = 0.0;
    Bbox3DType         bbox_3d_;  /// 3d bounding box.
    SignalVectorType   signals_;  /// signal infos.
};

/**
 * @brief Define safe is land
 */
template <typename FeatureIdT, typename PointT, size_t LANE_ID_SIZE = 64U, size_t INTERVAL_SIZE = 255U>
class SafeIsLand : public FeatureBase<FeatureIdT>
{
public:
    using FeatureIdType      = FeatureIdT;
    using PointType          = PointT;
    using Bbox2dType         = BirdViewBbox2D<PointType, holo::float32_t>;
    using LaneIdVectorType   = holo::container::Vector<FeatureIdType, LANE_ID_SIZE>;
    using HistInfoVectorType = holo::container::Vector<HistInfo, INTERVAL_SIZE>;

    SafeIsLand() : FeatureBase<FeatureIdType>(holo::map::navigator::graph::FeatureType::FEATURE_TYPE_SAFEISLAND)
    {
    }
    ~SafeIsLand()                 = default;
    SafeIsLand(SafeIsLand const&) = default;
    SafeIsLand(SafeIsLand&&)      = delete;
    SafeIsLand& operator=(SafeIsLand const&) = default;
    SafeIsLand& operator=(SafeIsLand&&) = delete;

    /**
     * @brief Set lane ids.
     *
     * @param lane_ids lane ids.
     */
    void SetLaneIds(LaneIdVectorType const& lane_ids) noexcept
    {
        this->lane_ids_ = lane_ids;
    }

    /**
     * @brief Get lane ids.
     *
     * @return Lane ids.
     */
    LaneIdVectorType GetLaneIds() const noexcept
    {
        return this->lane_ids_;
    }

    /**
     * @brief Set hist infos.
     *
     * @param hist_infos hist infos.
     */
    void SetHistInfos(HistInfoVectorType const& hist_infos) noexcept
    {
        this->hist_infos_ = hist_infos;
    }

    /**
     * @brief Get hist infos.
     *
     * @return Hist infos.
     */
    const HistInfoVectorType& GetHistInfos() const noexcept
    {
        return this->hist_infos_;
    }

    /**
     * @brief Set bbox 2d.
     *
     * @param bbox_2d bbox 2d.
     */
    void SetBbox2d(Bbox2dType const& bbox_2d) noexcept
    {
        this->bbox_2d_ = bbox_2d;
    }

    /**
     * @brief Get bbox 2d.
     *
     * @return Bbox 2d.
     */
    const Bbox2dType& GetBbox2d() const noexcept
    {
        return this->bbox_2d_;
    }

private:
    HistInfoVectorType hist_infos_;  /// history infos of current element.
    LaneIdVectorType   lane_ids_;    /// lane ids.
    Bbox2dType         bbox_2d_;     /// 2d bounding box.
};

/**
 * @brief Define pedestrian crossing type
 */
template <typename FeatureIdT, typename PointT, size_t LANE_ID_SIZE = 64U, size_t INTERVAL_SIZE = 255U>
class PedestrianCrossing : public FeatureBase<FeatureIdT>
{
public:
    using FeatureIdType      = FeatureIdT;
    using PointType          = PointT;
    using Bbox2dType         = BirdViewBbox2D<PointType, holo::float32_t>;
    using LaneIdVectorType   = holo::container::Vector<FeatureIdType, LANE_ID_SIZE>;
    using HistInfoVectorType = holo::container::Vector<HistInfo, INTERVAL_SIZE>;

    PedestrianCrossing()
      : FeatureBase<FeatureIdType>(holo::map::navigator::graph::FeatureType::FEATURE_TYPE_PEDESTRIAN_CROSSING)
    {
    }
    ~PedestrianCrossing()                         = default;
    PedestrianCrossing(PedestrianCrossing const&) = default;
    PedestrianCrossing(PedestrianCrossing&&)      = delete;
    PedestrianCrossing& operator=(PedestrianCrossing const&) = default;
    PedestrianCrossing& operator=(PedestrianCrossing&&) = delete;

    /**
     * @brief Set lane ids.
     *
     * @param lane_ids lane ids.
     */
    void SetLaneIds(LaneIdVectorType const& lane_ids) noexcept
    {
        this->lane_ids_ = lane_ids;
    }

    /**
     * @brief Get lane ids.
     *
     * @return Lane ids.
     */
    LaneIdVectorType GetLaneIds() const noexcept
    {
        return this->lane_ids_;
    }

    /**
     * @brief Set hist infos.
     *
     * @param hist_infos hist infos.
     */
    void SetHistInfos(HistInfoVectorType const& hist_infos) noexcept
    {
        this->hist_infos_ = hist_infos;
    }

    /**
     * @brief Get hist infos.
     *
     * @return Hist infos.
     */
    const HistInfoVectorType& GetHistInfos() const noexcept
    {
        return this->hist_infos_;
    }

    /**
     * @brief Set bbox 2d.
     *
     * @param bbox_2d bbox 2d.
     */
    void SetBbox2d(Bbox2dType const& bbox_2d) noexcept
    {
        this->bbox_2d_ = bbox_2d;
    }

    /**
     * @brief Get bbox 2d.
     *
     * @return Bbox 2d.
     */
    const Bbox2dType& GetBbox2d() const noexcept
    {
        return this->bbox_2d_;
    }

private:
    HistInfoVectorType hist_infos_;  /// history infos of current element.
    LaneIdVectorType   lane_ids_;    /// lane ids.
    Bbox2dType         bbox_2d_;     /// 2d bounding box.
};

/**
 * @}
 */
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_OBJECT_H_