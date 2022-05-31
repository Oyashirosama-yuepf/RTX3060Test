/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_builder_utility.h
 * @brief lmg builder utility
 * @author chanqiliang(chanqiliang@holomaitc.com)
 * @date 2021-12-15
 */

namespace holo
{
namespace map
{
namespace navigator
{
namespace graph
{
namespace builder
{
#define AdaptConnectedIds(Feature1, feature2, Feature3, Direction1, Direction2)                                        \
    ({                                                                                                                 \
        bool ok = true;                                                                                                \
        if (ptr_##Feature1 == nullptr)                                                                                 \
        {                                                                                                              \
            LOG(ERROR) << "Get ids failed, input pointer is nullptr!";                                                 \
            ok = false;                                                                                                \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            const std::size_t CIdSize = ptr_##Feature1->GetPtr##Direction1####feature2##Ids()->size();                 \
            Feature3##BuilderType::Feature3##IdVectorType ids;                                                \
            if (ids.capacity() < CIdSize)                                                                              \
            {                                                                                                          \
                LOG(ERROR) << "Size is larger than container's capacity!";                                             \
                ok = false;                                                                                            \
            }                                                                                                          \
            else                                                                                                       \
            {                                                                                                          \
                ids.reserve(CIdSize);                                                                                  \
                for (size_t i = 0; i < CIdSize; ++i)                                                                   \
                {                                                                                                      \
                    ids.push_back(static_cast<Feature3##BuilderType::FeatureIdType>(                          \
                        ptr_##Feature1->GetPtr##Direction1####feature2##Ids()->at(i)));                                \
                }                                                                                                      \
                info->Set##Direction2####Feature3##Ids(ids);                                                           \
            }                                                                                                          \
        }                                                                                                              \
        ok;                                                                                                            \
    })

#define AdaptLaneAssociateObjects(Feature1, Feature2)                                                                  \
    ({                                                                                                                 \
        bool ok = true;                                                                                                \
        if (nullptr == ptr_lane)                                                                                       \
        {                                                                                                              \
            LOG(ERROR) << "Adapt##Feature1##s failed, invalid parameter!";                                             \
            ok = false;                                                                                                \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            if (ptr_lane->GetPtrAssociated##Feature1##s()->empty())                                                    \
            {                                                                                                          \
                ok = true;                                                                                             \
            }                                                                                                          \
            else                                                                                                       \
            {                                                                                                          \
                LaneBuilderType::IntervalInfoVectorType interval_infos;                                       \
                std::size_t const size_interval_infos = ptr_lane->GetPtrAssociated##Feature1##s()->size();             \
                if (size_interval_infos > interval_infos.capacity())                                                   \
                {                                                                                                      \
                    LOG(ERROR) << "Adapt##Feature1##s failed, capacity = " << interval_infos.capacity();               \
                    ok = false;                                                                                        \
                }                                                                                                      \
                else                                                                                                   \
                {                                                                                                      \
                    interval_infos.resize(size_interval_infos);                                                        \
                    for (size_t i = 0; i < size_interval_infos; ++i)                                                   \
                    {                                                                                                  \
                        interval_infos[i].SetDataId(static_cast<LaneBuilderType::IntervalInfoType::IdType>(   \
                            ptr_lane->GetPtrAssociated##Feature1##s()->at(i).GetId()));                                \
                    }                                                                                                  \
                    info->Set##Feature2##Ids(interval_infos);                                                          \
                }                                                                                                      \
            }                                                                                                          \
        }                                                                                                              \
        ok;                                                                                                            \
    })

#define AppendObjectIds(Feature1, Feature2)                                                                            \
    ({                                                                                                                 \
        const auto                     single_objects = *(ptr_lane->GetPtrAssociated##Feature1##s());                  \
        ::std::vector<::std::uint64_t> single_object_ids;                                                              \
        for (const auto& id : single_objects)                                                                          \
        {                                                                                                              \
            single_object_ids.push_back(id.GetId());                                                                   \
        }                                                                                                              \
        holo::map::utility::UniqueAppend(all_##Feature2##_ids_temp, single_object_ids);                                \
    })

#define SwapVecContainerIds(Feature)                                                                                   \
    ({                                                                                                                 \
        if (!all_##Feature##_ids_temp.empty() && all_##Feature##_ids_temp.size() > all_##Feature##_ids.capacity())     \
        {                                                                                                              \
            LOG(ERROR)                                                                                                 \
                << "size is more than holo::container::Vector's capacity, only collect capacity numbers' object!";     \
            for (std::size_t i = 0; i < all_##Feature##_ids.capacity(); ++i)                                           \
            {                                                                                                          \
                all_##Feature##_ids.push_back(all_##Feature##_ids_temp[i]);                                            \
            }                                                                                                          \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            for (const ::std::uint64_t id : all_##Feature##_ids_temp)                                                  \
            {                                                                                                          \
                all_##Feature##_ids.push_back(id);                                                                     \
            }                                                                                                          \
        }                                                                                                              \
    })

}  // namespace builder
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo