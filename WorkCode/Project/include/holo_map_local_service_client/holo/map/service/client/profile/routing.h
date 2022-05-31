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

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_ROUTING_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_ROUTING_H_

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

class RoutingPathElement
{
public:
    using DistanceCMType = holo::uint32_t;

    ProfileIdType id_ = 0;
    DistanceCMType length_ = 0;
    holo::bool_t ready_ = false;
};

class RoutingPath : public ProfileBase
{
public: 
    using DistanceCMType = RoutingPathElement::DistanceCMType;
    using RoutingPathElementType = RoutingPathElement;
    using RoutingPathElementVectorType = std::vector<RoutingPathElement>;

    RoutingPath();
    virtual ~RoutingPath();

    static std::string const& Name();

    virtual std::string const& GetName() const;

    virtual ProfileIdVectorType const& GetTileIds() const;

    holo::bool_t IsOnRoutingPath(ProfileIdType const id, std::size_t& index) const;
    holo::bool_t IsComplete() const;

    ProfileIdType GetStartId() const;
    ProfileIdType GetEndId() const;

    ProfileIdVectorType const& GetNextPaths() const;

    DistanceCMType GetDistanceToStart(std::size_t const index, DistanceCMType const offset) const;
    DistanceCMType GetReadyDistanceToStart(std::size_t const index, DistanceCMType const offset) const;
    DistanceCMType GetDistanceToEnd(std::size_t const index, DistanceCMType const offset) const;
    DistanceCMType GetReadyDistanceToEnd(std::size_t const index, DistanceCMType const offset) const;

    holo::bool_t IsAssociatedFeature(RawFeatureType const type, ProfileIdType const id);

private:
    class RoutingPathInner;
    std::unique_ptr<RoutingPathInner> inner_;
};

using RoutingPathPtrType = std::shared_ptr<RoutingPath>;
using RoutingPathCSPtrType = std::shared_ptr<RoutingPath const>;

} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_ROUTING_H_ */