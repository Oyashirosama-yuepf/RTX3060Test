/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file quasi_dynamic_lane_group.h
 * @brief quasi_dynamic_lane_group.h
 * @author wanghaiyang@holomatic.com
 * @date "2021-09-23"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_QUASI_DYNAMIC_LANE_GROUP_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_QUASI_DYNAMIC_LANE_GROUP_H_

#include <string>

#include <holo/map/service/client/profile/base.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace profile
{
/**
 * @addtogroup profile
 * @{
 *
 */

class QuasiDynamicLaneGroup : public ProfileBase
{
public:
    using ProfileIdType = holo::map::service::client::profile::ProfileIdType;
    using ProfileIdVectorType = holo::map::service::client::profile::ProfileIdVectorType;

    QuasiDynamicLaneGroup();
    virtual ~QuasiDynamicLaneGroup();

    static std::string const& Name();

    virtual std::string const& GetName() const override;

    virtual ProfileIdVectorType const& GetTileIds() const;

private:
}; ///< End of class QuasiDynamicLaneGroup.

using QuasiDynamicLaneGroupSPtrType   = std::shared_ptr<QuasiDynamicLaneGroup>;
using QuasiDynamicLaneGroupCSPtrType  = std::shared_ptr<QuasiDynamicLaneGroup const>;

/**
 * @}
 *
 */

} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_QUASI_DYNAMIC_LANE_GROUP_H_ */