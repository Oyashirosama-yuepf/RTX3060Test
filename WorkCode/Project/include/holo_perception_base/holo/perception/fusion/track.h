/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file track.h
 * @brief This header file defines track interface.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-06-21"
 */

#ifndef HOLO_PERCEPTION_FUSION_TRACK_H_
#define HOLO_PERCEPTION_FUSION_TRACK_H_

#include <unordered_map>

#include <holo/common/timestamp.h>
#include <holo/perception/fusion/track_base.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup fusion
 *
 * @{
 */

/**
 * @brief Track interface
 *
 * @tparam _MeasurementKey measurement key type
 * @tparam _Measurement measurement type
 * @tparam _Hash measurement key hash function
 */
template <typename _MeasurementKey, typename _Measurement, typename _Hash>
class Track : public TrackBase
{
public:
    using MeasurementKey = _MeasurementKey;
    using Measurement    = _Measurement;
    using Hash           = _Hash;
    using MeasurementPtr = std::shared_ptr<Measurement>;
    using MeasurementMap = std::unordered_map<MeasurementKey, MeasurementPtr, Hash>;
    using Timestamp      = holo::common::details::Timestamp;

    /**
     * @brief Construct a new Track object
     *
     * @param track_type track type
     */
    Track(TrackType track_type) : TrackBase(track_type)
    {
    }

    /**
     * @brief predict obstacle state at current timestamp
     *
     * @param current_timestamp current timestamp
     */
    virtual void Predict(Timestamp const& current_timestamp) = 0;

    /**
     * @brief update obstacle state using associated measurements
     *
     * @param measurement_map associated measurements
     */
    virtual void Update(MeasurementMap const& measurement_map) = 0;
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif
