/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intersection.h
 * @brief intersection.h
 * @author hulingjia@holomatic.com
 * @date "2022-02-22"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_INTERSECTION_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_INTERSECTION_H_

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

class Intersection : public ProfileBase
{
public:
    using ProfileIdType = holo::map::service::client::profile::ProfileIdType;
    using ProfileIdVectorType = holo::map::service::client::profile::ProfileIdVectorType;

    Intersection();
    virtual ~Intersection();

    static std::string const& Name();

    virtual std::string const& GetName() const override;

    virtual ProfileIdVectorType const& GetTileIds() const;

private:
}; ///< End of class Intersection.

using IntersectionSPtrType   = std::shared_ptr<Intersection>;
using IntersectionCSPtrType  = std::shared_ptr<Intersection const>;

/**
 * @}
 *
 */
} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_INTERSECTION_H_ */