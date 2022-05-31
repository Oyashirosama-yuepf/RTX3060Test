/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bosch_mpc_someip.h
 * @brief A class to receive and construct bosch mpc outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/08/24
 */

#ifndef _HOLO_SENSORS_BOSCH_MPC_BOSCH_MPC_SOMEIP_H
#define _HOLO_SENSORS_BOSCH_MPC_BOSCH_MPC_SOMEIP_H

#include <holo/sensors/format/someip.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_base.h>
#include <holo_c/sensors/mpc/structure/mpc_line.h>
#include <holo_c/sensors/mpc/structure/mpc_object.h>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
using SomeipPacketType = holo::sensors::format::SomeipPacket<1024>;

/* driver based on someip packet */
template <>
class BoschMpcDriverT<SomeipPacketType> : public SmartCameraDriverT<SomeipPacketType>, public BoschMpcDriverBase
{
public:
    BoschMpcDriverT(const Extrinsicf& extrinsic) : SmartCameraDriverT<SomeipPacketType>(), BoschMpcDriverBase(extrinsic)
    {
    }
    /**
     * @brief      convert raw object to obstacle of target coord
     *
     * @param[in]  input      The raw object
     * @param      output     The target output obstacle
     */
    void ConvertToHoloObstacleWithTransform(const struct MpcObjectRawData& input,
                                            std::shared_ptr<ObstacleType>& output) const;
    /**
     * @brief      convert bosch mpc objects to obstacles with extrinsics
     *
     * @param[in]  input   The input in raw format
     * @param      output  The output obstacle list
     */
    void ConvertToObstaclePtrListWithTransform(const struct MpcObjectListRawData& input,
                                               ObstaclePtrListType&               output) const;
    /**
     * @brief      convert line to laneboundary of target coord
     *
     * @param[in]  input   The input raw format line
     * @param      output  The output
     */
    void ConvertToLaneboundaryWithTransform(const struct MpcLineRawData& input, LineType& output);
    /**
     * @brief      convert lane boundary array to road frame with extrinsic
     *
     * @param[in]  input   The input
     * @param      output  The output
     */
    void ConvertToRoadFrameWithTransform(const struct MpcLinesRawData& input, RoadFrameType& output);
    /**
     * @brief      Parse obstacles from raw data
     *
     * @param      data         The data
     * @param[in]  size         The buffer size start from data
     *
     * @return     true if parse ok, else false
     */
    bool_t ParseObstacles(const uint8_t* data, uint32_t size);
    /**
     * @brief      Parse lane boundaries from raw data
     *
     * @param      data       The data
     * @param[in]  size       The buffer size start from data
     *
     * @return     true if parse ok, else false
     */
    bool_t ParseLaneboundaries(const uint8_t* data, uint32_t size);
    /**
     * @brief      Parse data interface
     *
     * @param[in]  data  The data
     */
    void ParseData(const SomeipPacketType& data);
};

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo

#endif
