/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane.h
 * @brief lane.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-26"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_TILE_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_TILE_H_

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

class Tile : public ProfileBase
{
public:
    Tile();
    virtual ~Tile();

    static std::string const& Name();

    virtual std::string const& GetName() const override;

    virtual ProfileIdVectorType const& GetTileIds() const;

    ProfileIdVectorType const& GetProfileIds(ProfileType const type) const;

    
private:
    class TileInner;
    std::unique_ptr<TileInner> inner_;
};

using TileSPtrType = std::shared_ptr<Tile>;
using TileCSPtrType = std::shared_ptr<Tile const>;

} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_TILE_H_ */