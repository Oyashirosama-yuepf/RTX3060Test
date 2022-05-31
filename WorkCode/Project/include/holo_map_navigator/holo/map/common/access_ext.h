/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file access_ext.h
 * @brief Direct access map elements based on retriever without logical calculation.
 * @author dingjing(dingjing@holomaitc.com)
 * @date "2020-03-19"
 */

#ifndef _HOLO_MAP_COMMON_ACCESS_NDS_DATA_H_
#define _HOLO_MAP_COMMON_ACCESS_NDS_DATA_H_

#include <holo/map/common/geometry.h>
#include <holo/map/common/common_define.h>
#include <holo/map/common/math.h>
#include <holo/map/retriever/retriever.h>
/**
 * @addtogroup holo
 *
 * @{
 */
namespace holo
{
/**
 * @addtogroup map
 *
 * @{
 */
namespace map
{
/**
 * @addtogroup access
 *
 * @{
 */
namespace access
{
/**
 * @brief Get Lane width by the percentage of the lane's length.
 *
 * @param[in]  ptr_lane Pointer of lane
 * @param[in]  percent  The percentage of the lane's length.[0, 100]
 * @param[out] width    The precise width. unit: meter
 *
 * @return true  Operation successful.
 * @return false Otherwise.
 */
bool GetLanePreciseWidthByPercent(const format::PtrLane ptr_lane, const holo::float64_t percent,
                                  holo::float64_t& width);

/**
 * @brief Get Lane width by the percentage of the lane's length.
 *
 * @param[in]  ret     Pointer of retriever
 * @param[in]  lane_id Lane id
 * @param[in]  percent The percentage of the lane's length.[0, 100]
 * @param[out] width   The precise width. unit: meter
 *
 * @return true  Operation successful.
 * @return false Otherwise.
 */
bool GetLanePreciseWidthByPercent(const RetrieverSPType ret, const IdType lane_id, const holo::float64_t percent,
                                  holo::float64_t& width);

/**
 * Describe the speed limit information of a lane/road.
 */
struct SpeedLimitType
{
    /**
     * Redefine the inner type.
     */
    using ValueType  = holo::uint16_t;
    using VectorType = std::vector<SpeedLimitType>;

    ValueType min          = 0;    ///< Minimum speed limit value(Uint: km/h).
    ValueType max          = 0;    ///< Maximum speed limit value(Unit: km/h).
    Distance  start_offset = 0.0;  ///< Percent of the length of a lane/road(Unit: %).
    Distance  end_offset   = 0.0;  ///< Percent of the length of a lane/road(Unit: %).

    /**
     * @brief Constructor without parameters.
     */
    SpeedLimitType()
    {
    }

    /**
     * @brief Constructor with parameters.
     *
     * @param[in] vmin The minimum speed limit(Uint: km/h).
     * @param[in] vmax The maximux speed limit(Uint: km/h).
     * @param[in] s_offset Percent of the length of a lane/road(Unit: %).
     * @param[in] e_offset Percent of the length of a lane/road(Unit: %).
     *
     * @return Nothing.
     */
    SpeedLimitType(ValueType const vmin, ValueType const vmax, Distance const s_offset, Distance const e_offset)
      : min(vmin), max(vmax), start_offset(s_offset), end_offset(e_offset)
    {
    }
};

/**
 * @brief Get speed limit information from a lane.
 *
 * @param[in] ret The handle of database engine.
 * @param[in] id The target lane id.
 * @param[out] limits Speed limit information.
 * @return true: No error;
 *         false: An error occurs in this function.
 */
bool GetSpeedLimitByLaneId(RetrieverSPType const ret, IdType const id, SpeedLimitType::VectorType& limits);

/**
 * @brief Get speed limit information from a lane group.
 *
 * @detail Merge all the speed limits from all the lanes in a single container.
 * @param[in] ret The handle of database engine.
 * @param[in] id The target lane group id.
 * @param[out] limits Speed limit information.
 * @return true: No error;
 *         false: An error occurs in this function.
 */
bool GetSpeedLimitByLaneGroupId(RetrieverSPType const ret, IdType const id, SpeedLimitType::VectorType& limits);

};  // namespace access
/**
 * @}
 */
}  // namespace map
/**
 * @}
 */
}  // namespace holo
/**
 * @}
 */
#endif /* _HOLO_MAP_COMMON_ACCESS_NDS_DATA_H_ */
