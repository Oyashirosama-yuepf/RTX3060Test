/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file map_path_process.h
 * @brief This header file defines map path process function
 * @author lizhao(lizhao@holomaitc.com)
 * @date 2022-02-11
 */

#ifndef HOLO_PARKING_BASE_PLANNING_PATH_PROCESS_H_
#define HOLO_PARKING_BASE_PLANNING_PATH_PROCESS_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/parking/map/hpp_path_data.h>

namespace holo
{
namespace parking
{
namespace map
{
/**
 * @brief This class defines path attribute
 */
class MapPathProcess
{
public:
    /**
     * @brief default constructor
     */
    MapPathProcess() = default;

    /**
     * @brief Save ParkingPath to file.
     *
     * @param[in] park_path The parking path data.
     * @param[in] file_path The save file directory.
     *
     * @return True if save succeeds, false otherwise.
     */
    bool_t SaveParkingPath2File(ParkingPath& parking_path, std::string const file_path);

    /**
     * @brief Load file to ParkingPath.
     *
     * @param[in] file_path The save file directory.
     * @param[in] parking_Path park_path The parking path data.
     *
     * @return True if load succeeds, false otherwise.
     */
    bool_t LoadFile2ParkingPath(std::string const file_path, ParkingPath& parking_Path);

private:
};

}  // namespace map
}  // namespace parking
}  // namespace holo

#endif
