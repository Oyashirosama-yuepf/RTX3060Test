/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file access.h
 * @brief access.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-09"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_ENGINE_ACCESS_H_
#define HOLO_MAP_SERVICE_CLIENT_ENGINE_ACCESS_H_

#include <holo/map/service/client/profile/base.h>
#include <holo/map/service/client/profile/lane.h>
#include <holo/map/service/client/profile/lane_boundary.h>
#include <holo/map/service/client/profile/lane_group.h>
#include <holo/map/service/client/profile/road.h>
#include <holo/map/service/client/engine/retriever.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace engine
{
namespace access
{

/**
 * @addtogroup access
 * @{
 *
 */

using ProfileType           = holo::map::service::client::engine::Retriever::ProfileType;
using ProfileIdType         = holo::map::service::client::engine::Retriever::ProfileIdType;
using ProfileIdVectorType   = holo::map::service::client::engine::Retriever::ProfileIdVectorType;
using ProfileCSPtrType      = holo::map::service::client::engine::Retriever::ProfileCSPtrType;

using RetrieverSPtrType     = holo::map::service::client::engine::RetrieverSPtrType;

using ProfileRoadType       = holo::map::service::client::profile::Road;
using ProfileLaneGroupType  = holo::map::service::client::profile::LaneGroup;

using ProfileRoadCSPtrType      = holo::map::service::client::profile::RoadCSPtrType;
using ProfileLaneGroupCSPtrType = holo::map::service::client::profile::LaneGroupCSPtrType;

holo::bool_t IsRoadWithMainRoadType(RetrieverSPtrType ret, ProfileIdType const id, holo::bool_t& result);

holo::bool_t IsLaneGroupWithMainRoadType(RetrieverSPtrType ret, ProfileIdType const id, holo::bool_t& result);

/**
 * @}
 *
 */

} ///< namespace access
} ///< namespace engine
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_ENGINE_ACCESS_H_ */
