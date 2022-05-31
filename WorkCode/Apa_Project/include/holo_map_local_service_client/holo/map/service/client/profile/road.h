/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road.h
 * @brief road.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-26"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_ROAD_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_ROAD_H_

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

class Road : public ProfileBase
{
public:
    Road();
    virtual ~Road();

    static std::string const& Name();

    virtual std::string const& GetName() const;

    virtual ProfileIdVectorType const& GetTileIds() const;

    holo::bool_t IsMotorwayMainRoad() const;

private:
    class RoadInner;
    std::unique_ptr<RoadInner> inner_;
};

using RoadSPtrType = std::shared_ptr<Road>;
using RoadCSPtrType = std::shared_ptr<Road const>;

} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_ROAD_H_ */