/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file quasi_dynamic_lane.h
 * @brief quasi_dynamic_lane.h
 * @author wanghaiyang@holomatic.com
 * @date "2021-09-23"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_QUASI_DYNAMIC_LANE_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_QUASI_DYNAMIC_LANE_H_

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

class QuasiDynamicLane : public ProfileBase
{
public:
    using ProfileIdType = holo::map::service::client::profile::ProfileIdType;
    using ProfileIdVectorType = holo::map::service::client::profile::ProfileIdVectorType;

    QuasiDynamicLane();
    virtual ~QuasiDynamicLane();

    static std::string const& Name();

    virtual std::string const& GetName() const override;

    virtual ProfileIdVectorType const& GetTileIds() const;

private:
}; ///< End of class QuasiDynamicLane.

using QuasiDynamicLaneSPtrType   = std::shared_ptr<QuasiDynamicLane>;
using QuasiDynamicLaneCSPtrType  = std::shared_ptr<QuasiDynamicLane const>;

/**
 * @}
 *
 */
} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_QUASI_DYNAMIC_LANE_H_ */