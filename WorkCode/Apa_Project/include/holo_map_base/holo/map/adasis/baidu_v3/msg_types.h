/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file msg_types.h
 * @brief This header file defines the baidu serializer / deserializer.
 * @author zhengshulei@holomatic.com
 * @date 2021-11-1
 */
#ifndef HOLO_MAP_ADASIS_BAIDU_V3_MSG_TYPES_H_
#define HOLO_MAP_ADASIS_BAIDU_V3_MSG_TYPES_H_

#include <holo/map/adasis/baidu_v3/msg_header.h>
#include <holo/map/adasis/baidu_v3/msg_payload.h>
#include <holo/map/adasis/baidu_v3/msg_position.h>
#include <holo/map/adasis/serialization/serialization.h>

namespace holo
{
namespace map
{
namespace adasis
{
namespace baidu_v3
{

/**
 * @addtogroup baidu_v3
 * @{
 *
 */

using BDSerializer   = holo::map::adasis::serialization::BufferSerializer;
/**
 * @brief Buffer Deserializer for Baidu-EHP tx package.
 */
using BDDeserializer = holo::map::adasis::serialization::BufferDeserializer;

/**
 * @brief Baidu-EHP MLM_LOC TX package of ADASIS V3 position message.
 */
using MLM_LOC  = PositionMessage;
/**
 * @brief Baidu-EHP MLM_GLBD TX package of ADASIS V3 globaldata message.
 */
using MLM_GLBD = OneMessageOnBus<GlobalDataMessage>;
/**
 * @brief Baidu-EHP MLM_PTC TX package of ADASIS V3 path control message.
 */
using MLM_PTC  = OneMessageOnBus<v3_1_1::PathControlMessage>;
/**
 * @brief Baidu-EHP MLM_PFC TX package of ADASIS V3 profile control message.
 */
using MLM_PFC  = MultiMessageOnBus<v3_1_1::ProfileControl>;

/**
 * @brief Definition of Node profile entry.
 */
using InsectionEntry        = MultiProfileEntry<v3_1_1::NodeArm>;
/**
 * @brief Definition of LaneModel profile entry.
 */
using LaneModelEntry        = MultiProfileEntry<BDLaneInfo>;
/**
 * @brief Definition of LaneConnectivity profile entry.
 */
using LaneConnectivityEntry = MultiProfileEntry<v3_1_1::LaneConnectivityPair>;
/**
 * @brief Definition of LinearObject profile entry.
 */
using LinearObjectEntry     = MultiProfileEntry<v3_1_1::LinearObject>;
/**
 * @brief Definition of LineGeometry profile entry.
 */
using LineGeometryEntry     = MultiProfileEntry<v3_1_1::LineGeometry>;
/**
 * @brief Definition of Curvature profile entry.
 */
using CurvatureEntry        = MultiProfileEntry<v3_1_1::OffsetFloatEntry>;
/**
 * @brief Definition of Slope profile entry.
 */
using SlopeEntry            = MultiProfileEntry<v3_1_1::OffsetFloatEntry>;

/**
 * @brief Definition of SpeedLimit profile entry.
 */
using SpeedLimitEntry = OneProfileEntry<v3_1_1::Speed>;
/**
 * @brief Definition of Geometry profile entry.
 */
using GeometryEntry   = OneProfileEntry<v3_1_1::Curve>;

/**
 * @brief Definition of NumberOfLanes profile entry.
 */
using NumberOfLanesEntry       = OneProfileEntry<NumberOfLanesPerDirection>;
/**
 * @brief Definition of LinkIdentifier profile entry.
 */
using LinkIdentifierEntry      = OneProfileEntry<LinkIdentifier>;
/**
 * @brief Definition of FunctionalRoadClass profile entry.
 */
using FunctionalRoadClassEntry = OneProfileEntry<FunctionalRoadClass>;
/**
 * @brief Definition of FormOfWay profile entry.
 */
using FormOfWayEntry           = OneProfileEntry<BDFormOfWay>;
/**
 * @brief Definition of Tunnel profile entry.
 */
using TunnelEntry              = OneProfileEntry<Tunnel>;

using NumberOfLanesEntryVec       = std::vector<NumberOfLanesEntry>;
using LinkIdentifierEntryVec      = std::vector<LinkIdentifierEntry>;
using FunctionalRoadClassEntryVec = std::vector<FunctionalRoadClassEntry>;
using FormOfWayEntryVec           = std::vector<FormOfWayEntry>;
using TunnelEntryVec              = std::vector<TunnelEntry>;

/**
 * @brief Definition of LaneWidth profile entry.
 */
using LaneWidthEntry = OneProfileEntry<v3_1_1::LaneWidthProfileValue>;

/**
 * @brief Baidu-EHP MLM_PFN TX package of ADASIS V3 Node profile message.
 */
using MLM_PFN  = OneMessageOnBus<MultiProfileEntry<v3_1_1::NodeArm>>;
/**
 * @brief Baidu-EHP MLM_PFLC TX package of ADASIS V3 LaneModel profile message.
 */
using MLM_PFLM = OneMessageOnBus<MultiProfileEntry<BDLaneInfo>>;
/**
 * @brief Baidu-EHP MLM_PFLC TX package of ADASIS V3 LaneConnectivity profile message.
 */
using MLM_PFLC = OneMessageOnBus<MultiProfileEntry<v3_1_1::LaneConnectivityPair>>;
/**
 * @brief Baidu-EHP MLM_PFLO TX package of ADASIS V3 LinearObject profile message.
 */
using MLM_PFLO = OneMessageOnBus<MultiProfileEntry<v3_1_1::LinearObject>>;
/**
 * @brief Baidu-EHP MLM_PFLG TX package of ADASIS V3 LaneGeometry profile message.
 */
using MLM_PFLG = OneMessageOnBus<MultiProfileEntry<v3_1_1::LineGeometry>>;
/**
 * @brief Baidu-EHP MLM_PFCV TX package of ADASIS V3 Curvature profile message.
 */
using MLM_PFCV = OneMessageOnBus<MultiProfileEntry<v3_1_1::OffsetFloatEntry>>;
/**
 * @brief Baidu-EHP MLM_PFSP TX package of ADASIS V3 Slope profile message.
 */
using MLM_PFSP = OneMessageOnBus<MultiProfileEntry<v3_1_1::OffsetFloatEntry>>;

/**
 * @brief Baidu-EHP MLM_PFSL TX package of ADASIS V3 SpeedLimit profile message.
 */
using MLM_PFSL = OneMessageOnBus<OneProfileEntry<v3_1_1::Speed>>;
/**
 * @brief Baidu-EHP MLM_PFRG TX package of ADASIS V3 RoadGeometry profile message.
 */
using MLM_PFRG = OneMessageOnBus<OneProfileEntry<v3_1_1::Curve>>;

/**
 * @brief Baidu-EHP MLM_PFLI1 TX package of ADASIS V3 NumberOfLanesPerDirection profile message.
 */
using MLM_PFLI1 = MultiMessageOnBus<OneProfileEntry<NumberOfLanesPerDirection>>;
/**
 * @brief Baidu-EHP MLM_PFLI2 TX package of ADASIS V3 LinkIdentifier profile message.
 */
using MLM_PFLI2 = MultiMessageOnBus<OneProfileEntry<LinkIdentifier>>;
/**
 * @brief Baidu-EHP MLM_PFLI3 TX package of ADASIS V3 FunctionalRoadClass profile message.
 */
using MLM_PFLI3 = MultiMessageOnBus<OneProfileEntry<FunctionalRoadClass>>;
/**
 * @brief Baidu-EHP MLM_PFLI4 TX package of ADASIS V3 FormOfWay profile message.
 */
using MLM_PFLI4 = MultiMessageOnBus<OneProfileEntry<BDFormOfWay>>;
/**
 * @brief Baidu-EHP MLM_PFLI5 TX package of ADASIS V3 Tunnel profile message.
 */
using MLM_PFLI5 = MultiMessageOnBus<OneProfileEntry<Tunnel>>;

/**
 * @brief Baidu-EHP MLM_PFLW TX package of ADASIS V3 LaneWidth profile message.
 */
using MLM_PFLW = OneMessageOnBus<OneProfileEntry<v3_1_1::LaneWidthProfileValue>>;

/**
 * @}
 */

} // namespace baidu_v3
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_BAIDU_V3_MSG_TYPES_H_ */