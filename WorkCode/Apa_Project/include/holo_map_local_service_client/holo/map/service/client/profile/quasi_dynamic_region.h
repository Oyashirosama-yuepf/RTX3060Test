/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file quasi_dynamic_region.h
 * @brief quasi_dynamic_region.h
 * @author hulingjia@holomatic.com
 * @date "2021-09-28"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_QUASI_DYNAMIC_REGION_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_QUASI_DYNAMIC_REGION_H_

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

class QuasiDynamicRegion : public ProfileBase
{
public:
    using ProfileIdType = holo::map::service::client::profile::ProfileIdType;
    using ProfileIdVectorType = holo::map::service::client::profile::ProfileIdVectorType;

    QuasiDynamicRegion();
    virtual ~QuasiDynamicRegion();

    static std::string const& Name();

    virtual std::string const& GetName() const override;

    virtual ProfileIdVectorType const& GetTileIds() const;

private:
}; ///< End of class QuasiDynamicRegion.

using QuasiDynamicRegionSPtrType   = std::shared_ptr<QuasiDynamicRegion>;
using QuasiDynamicRegionCSPtrType  = std::shared_ptr<QuasiDynamicRegion const>;

/**
 * @}
 *
 */
} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_QUASI_DYNAMIC_REGION_H_ */