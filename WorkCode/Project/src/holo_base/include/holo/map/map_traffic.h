/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_traffic.h
 * @brief Define traffic infomation which from third-party service.
 * @author wanghaiyang@holomatic.com
 * @date "2020-02-27"
 */

#ifndef HOLO_MAP_MAP_TRAFFIC_H_
#define HOLO_MAP_MAP_TRAFFIC_H_

#include <vector>

#include <holo/common/timestamp.h>
#include <holo/map/common_def.h>

namespace holo
{
namespace map
{

/**
 * @addtogroup map
 * @{
 *
 */

/**
 * @brief Third-party traffic information.
 * 
 * @note Reference to: https://holomatic.feishu.cn/docs/doccnVScrpc7lOlD7TMqGpTW10e.
 */
class MapTraffic
{
public:
    /**
     * @brief Redefine types for inner data.
     */
    using ConfidenceType    = holo::uint8_t;
    using DistanceType      = holo::float32_t;
    using RoadIdType        = holo::uint64_t;

    /**
     * @brief Define the max value for confidence.
     */
    static ConfidenceType const FULL_CONFIDENCE = 100;

    /**
     * @brief Whether or not current traffic is expedited.
     * 
     * @return true: Traffic with expedited.
     *         false: Otherwise.
     */
    bool IsRoadExpedited() const noexcept
    {
        return StatusType::EXPEDITED == this->status_;
    }

    /**
     * @brief Assign traffic status with EXPEDITED.
     * 
     * @param[in] v true: Set traffic status with expedited; 
     *              false: clear status with unknown.
     * @return Nothing.
     */
    void SetRoadExpedited(bool const v = true) noexcept
    {
        this->status_ = v ? StatusType::EXPEDITED : StatusType::UNKNOWN;
    }

    /**
     * @brief Whether or not current traffic is congested.
     * 
     * @return true: Traffic with congested.
     *         false: Otherwise.
     */
    bool IsCongested() const noexcept
    {
        return StatusType::CONGESTED == this->status_;
    }

    /**
     * @brief Assign traffic status with CONGESTED.
     * 
     * @param[in] v true: Set traffic status with congested;
     *              false: clear status with unknown.
     * @return Nothing.
     */
    void SetRoadCongested(bool const v = true) noexcept
    {
        this->status_ = v ? StatusType::CONGESTED : StatusType::UNKNOWN;
    }

    /**
     * @brief Whether or not current traffic is blocked.
     * 
     * @return true: Traffic with blocked.
     *         false: Otherwise.
     */
    bool IsRoadBlocked() const noexcept
    {
        return StatusType::BLOCKED == this->status_;
    }

    /**
     * @brief Assign traffic status with BLOCKED.
     * 
     * @param[in] v true: Set traffic status with blocked;
     *              false: clear status with unknown.
     * @return Nothing.
     */
    void SetRoadBlocked(bool const v = true) noexcept
    {
        this->status_ = v ? StatusType::BLOCKED : StatusType::UNKNOWN;
    }

    /**
     * @brief Whether or not this information is totally confident.
     * 
     * @return true: Current information is fully confident.
     *         false: Otherwise.
     */
    bool IsFullyConfident() const noexcept
    {
        return FULL_CONFIDENCE == this->confidence_;
    }

    /**
     * @brief Access confidence from this information.
     * 
     * @return Confidence value.
     */
    ConfidenceType GetConfidence() const noexcept
    {
        return this->confidence_;
    }

    /**
     * @brief Assign confidence value to this information.
     * 
     * @param[in] c A new confidence value.
     * @return Nothing.
     */
    void SetConfidence(ConfidenceType const c) noexcept
    {
        this->confidence_ = c;
    }

    /**
     * @brief Access start distance.
     * 
     * @return Start distance.
     */
    DistanceType GetStartDistance() const noexcept
    {
        return this->start_distance_;
    }

    /**
     * @brief Assign a start distance.
     * 
     * @param[in] d A distance value.
     * @return
     */
    void SetStartDistance(DistanceType const d) noexcept
    {
        this->end_distance_ = d;
    }

    /**
     * @brief Access end distance.
     * 
     * @return End distance.
     */
    DistanceType GetEndDistance() const noexcept
    {
        return this->end_distance_;
    }

    /**
     * @brief Assign an end distance.
     * 
     * @param[in] d A distance value.
     * @return Nothing.
     */
    void SetEndDistance(DistanceType const d) noexcept
    {
        this->end_distance_ = d;
    }

private:
    /**
     * @brief Traffic status of a road.
     */
    enum class StatusType : uint8_t
    {
        UNKNOWN     = 0, ///< Unknown status.
        EXPEDITED,       ///< Target road is clear.
        CONGESTED,       ///< Target road is congestion.
        BLOCKED,         ///< Target road is blocked.
    };

    StatusType          status_                = StatusType::UNKNOWN; ///< Traffic status.
    ConfidenceType     confidence_             = 0;                   ///< Range: [0~100].

    /// Distance between current car position and start position of the special
    /// interval(Traffic status) of a road. Unit: meters.
    DistanceType   start_distance_          = 0.0f; 

    /// Distance between current car position and end position of the special
    /// interval(Traffic status) of a road. Unit: meters.
    DistanceType   end_distance_            = 0.0f; 
};

/**
 * @brief Third-party traffic message.
 * 
 * @note Reference to: https://holomatic.feishu.cn/docs/doccnVScrpc7lOlD7TMqGpTW10e.
 */
class MapTraffics
{
public:
    /**
     * @brief Define vector type for traffics.
     */
    using VectorTrafficType = std::vector<MapTraffic>;

    /**
     * @brief Access timestamp.
     * 
     * @return A reference of Timestamp.
     */
    Timestamp& GetTimestamp() noexcept
    {
        return this->timestamp_;
    }

    /**
     * @brief Access timestamp.
     * 
     * @return A const reference of Timestamp.
     */
    Timestamp const& GetTimestamp() const noexcept
    {
        return this->timestamp_;
    }

    /**
     * @brief Assign a new timestamp.
     * 
     * @param[in] t A timestamp value.
     * @return Nothing.
     */
    void SetTimestamp(Timestamp const& t)
    {
        this->timestamp_ = t;
    }

    /**
     * @brief Access traffic infosinformations.
     * 
     * @return Traffic informations.
     */
    VectorTrafficType const& GetTraffics() const noexcept
    {
        return this->traffics_;
    }

    /**
     * @brief Assign new traffic informations.
     * 
     * @param[in] ts New traffic informations.
     * @return Nothing.
     */
    void SetTraffics(VectorTrafficType const& ts)
    {
        this->traffics_ = ts;
    }

    /**
     * @brief Assign new traffic informations.
     * 
     * @param[in] ts New traffic informations.
     * @return Nothing.
     */
    void SetTrafficInfos(VectorTrafficType&& ts)
    {
        this->traffics_ = std::move(ts);
    }

private:
    holo::Timestamp         timestamp_;  ///< Timestamp of data sending.
    VectorTrafficType       traffics_;   ///< Traffic infomations.
}; ///< end of class MapTraffic

/**
 * @}
 *
 */

} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_MAP_TRAFFIC_H_ */