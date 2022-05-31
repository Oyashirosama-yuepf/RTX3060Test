/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ParkingMapIO.h
 * @brief This header file defines ParkingMapIO.
 * @author guopeikai(guopeikai@holomaitc.com)
 * @date 2022-01-26
 */

#ifndef HOLO_PARKING_MAP_PARKING_MAP_IO_H_
#define HOLO_PARKING_MAP_PARKING_MAP_IO_H_

#include <boost/optional/optional.hpp>
#include <map>
#include <opencv2/core.hpp>
#include <vector>

#include <holo/core/types.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/parking/map/parking_map_common_types.h>

namespace holo
{
namespace parking
{
namespace map
{
/**
 * @brief this class supports to read and write mappoints and keyframes
 *
 */
class ParkingMapIO
{
public:
    ParkingMapIO() : prebuild_map_(nullptr)
    {
    }

    ~ParkingMapIO()
    {
        prebuild_map_ = nullptr;
    }

    /**
     * @brief contain parking slot database and target parking slot id
     */
    struct ParkingSlotData
    {
        /// @brief all optimized parking slot
        std::vector<holo::common::ParkingSlot> parking_slot_database;

        /// @brief target parking slot id
        uint64_t target_parking_slot_id = 0;
    };

    /**
     * @brief load prebuild parking map
     *
     * @param [in] map_file_name the map file path name
     * @param [out] map the loaded map
     * @return true: load successfully
     * @return false: load failed
     */
    static bool LoadPrebuildMap(const std::string& map_file_name, Map& map);

    /**
     * @brief load keyframe database
     *
     * @param [in] keyframes_file_name the keyframe file path name
     * @param [out] keyframe_database the loaded keyframes database
     * @return true: load successfully
     * @return false: load failed
     */
    static bool LoadKeyFramesDatabase(const std::string& keyframes_file_name, KeyFramesDatabase& keyframes_database);

    /**
     * @brief load parking slot database
     *
     * @param [in] parking_slots_file_name the parking slot file path name
     * @param [out] parking_slot_database the loaded parking slot database
     * @return true: load successfully
     * @return false: load failed
     */
    static bool LoadParkingSlotDatabase(const std::string& parking_slots_file_name, ParkingSlotData& parking_slot_data);

private:
    MapPtr            prebuild_map_;        // prebuild map
    KeyFramesDatabase keyframes_database_;  // keyframes database
};

}  // namespace map
}  // namespace parking
}  // namespace holo

#endif  // HOLO_PARKING_MAP_PARKING_MAP_IO_H_
