/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file data_engine.h
 * @brief Data engine for obtaining map data
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-10-08"
 */

#ifndef HOLO_MAP_NAVIGATOR_ADAPTION_DATA_ENGINE_H_
#define HOLO_MAP_NAVIGATOR_ADAPTION_DATA_ENGINE_H_

#include <memory>
#include <vector>

#include <type_traits>

#include <holo/map/base/feature_id/boundary_id.h>
#include <holo/map/base/feature_id/lane_id.h>
#include <holo/map/base/feature_id/link_id.h>
#include <holo/map/common/common_define.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace adaptation
{
template <typename T>
class IdTraits
{
public:
    using ValueType = T;
    IdTraits(T instance)
    {
        this->value_ = instance;
    }
    T Value()
    {
        return this->value_;
    }

private:
    T value_;
};

template <>
class IdTraits<format::PtrLane>
{
public:
    using ValueType = base::LaneId;
    IdTraits(format::PtrLane instance)
    {
        if (nullptr == instance)
        {
            LOG(ERROR) << "";
            return;
        }
        this->value_ = instance->GetLaneId();
    }
    base::LaneId Value()
    {
        return this->value_;
    }

private:
    base::LaneId value_;
};

template <>
struct IdTraits<format::PtrLaneGroup>
{
    using ValueType = base::LinkId;
};

template <>
struct IdTraits<format::PtrLaneBoundary>
{
    using ValueType = base::BoundaryId;
};

class DataEngine
{
public:
    using DataEngineSPtrType    = std::shared_ptr<DataEngine>;
    using GeoPointType          = holo::map::format::GeoPoint;
    using GeoPointVecType       = std::vector<GeoPointType>;

public:
    static DataEngineSPtrType Instance();

    holo::bool_t Init(RetrieverSPType ret);

    template<typename T>
    holo::bool_t GetSuccessiveIds(T id, std::vector<T>& ids)
    {
        ids.clear();
        using IdType = typename IdTraits<T>::ValueType;

        IdTraits<T> id_traits(id);
        IdType      feature_id = id_traits.Value();

        if (std::is_same<IdType, base::LaneId>::value)
        {
            format::PtrLane lane = nullptr;
            if (!DataEngine::retriver_->GetLaneById(feature_id.Value(), lane))
            {
                LOG(ERROR) << "";
                return false;
            }
            std::vector<holo::uint64_t> const& succ_lanes = *lane->GetPtrSuccLaneIds();
            ids.insert(ids.end(), succ_lanes.begin(), succ_lanes.end());
        }
        if (std::is_same<IdType, base::LinkId>::value)
        {
            format::PtrLaneGroup group = nullptr;
            if (!DataEngine::retriver_->GetLaneGroupById(feature_id.Value(), group))
            {
                LOG(ERROR) << "";
                return false;
            }
            std::vector<holo::uint64_t> succ_link_ids = *group->GetPtrSucceedingLaneGroupIds();
            ids.insert(ids.end(), succ_link_ids.begin(), succ_link_ids.end());
        }
        if (std::is_same<IdType, base::BoundaryId>::value)
        {
            format::PtrLaneBoundary boundary = nullptr;
            if (!DataEngine::retriver_->GetLaneBoundaryById(feature_id.Value(), boundary))
            {
                LOG(ERROR) << "";
                return false;
            }
            std::vector<holo::uint64_t> succ_boundary_ids = *boundary->GetPtrSuccLaneBoundaryIds();
            ids.insert(ids.end(), succ_boundary_ids.begin(), succ_boundary_ids.end());
        }
        return true;
    }

    template <typename ID1, typename ID2>
    ID2 GetLeftBoundaryId(ID1 const id1){}

    template <typename ID1, typename ID2>
    ID2 GetRightBoundaryId(ID1 const id1){}

    RetrieverSPType GetRetriver();

    holo::bool_t GetLaneIdsByLinkId(IdType const link_id, std::vector<IdType>& lane_ids);

    holo::bool_t GetLinkStartOrEndPoint(IdType const link_id,
                                        holo::bool_t const start_or_end, format::GeoPoint& geo_point);

    holo::bool_t GetLaneStartOrEndPoint(IdType const lane_id,
                                        holo::bool_t const start_or_end, format::GeoPoint& geo_point);

    holo::bool_t GetSuccLaneIds(IdType const lane_id, std::vector<IdType>& succ_lane_ids);
    holo::bool_t GetSuccLinkIds(IdType const lane_id, std::vector<IdType>& succ_link_ids);

    holo::bool_t GetSuccLanes(IdType const lane_id, std::vector<format::PtrLane>& succ_lanes);

    holo::bool_t GetPrevLaneIds(IdType const lane_id, std::vector<IdType>& prev_lane_ids);
    holo::bool_t GetPrevLinkIds(IdType const lane_id, std::vector<IdType>& prev_link_ids);

    holo::bool_t GetBoundaryGeoPoints(IdType const boundary_id, GeoPointVecType& pts);

    holo::bool_t GetPtrLanesByLinkId(IdType const link_id, std::vector<format::PtrLane>& lanes);

private:
    static std::shared_ptr<DataEngine> data_engine_;
    RetrieverSPType    retriver_    = nullptr;
};
}  // namespace base
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_NAVIGATOR_BASE_DATA_ENGINE_H_ */
