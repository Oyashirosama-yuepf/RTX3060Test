
/*!
 *  \brief ODMManager, provide odm related information
 *  \author Liu Qikang(liuqikang@holomatic.com)
 *  \date 2021-09-24
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
 */
#ifndef HOLO_MAP_FEATURE_ATTRIBUTOR_H_
#define HOLO_MAP_FEATURE_ATTRIBUTOR_H_

#include <holo/map/common/common_define.h>
#include <holo/map/feature/map_attributor/geofence/geofence_extractor.h>
#include <holo/map/feature/map_attributor/geofence/map_geofence_cache.h>
#include <holo/map/feature/map_attributor/road_attributes/map_attributes_extractor.h>
#include <holo/map/feature/map_attributor/road_attributes/road_attribute.h>
#include <holo/map/feature/map_attributor/road_type_intervals/common.h>
#include <holo/map/feature/map_attributor/road_type_intervals/road_type_interval_extractor.h>
#include <holo/map/feature/navigator/navigator_config.h>
#include <holo/map/geofence.h>

namespace holo
{
namespace map
{
/**
 * @addtogroup map
 *
 * @{
 */

/**
 * @brief Attributor manager.
 */
class Attributor
{
public:
    using RoadTypeIntervalExtractorSPtrType = attribute::road_type::RoadTypeIntervalExtractorSPtrType;
    using MapAttributesExtractorUPtrType    = navigator::attributes::MapAttributesExtractorUPtrType;
    using GeofenceExtractorUPtrType         = geofence::GeofenceExtractorUPtrType;

    struct Output
    {
        Geofences                                geofences;
        RoadRefPointAttributes<RoadScs>          road_attributes;
        RoadRefPointAttributes<RoadTypeInterval> road_type_intervals;
    };

    struct ODMExtractor
    {
        GeofenceExtractorUPtrType         geofence_extractor_ptr_           = nullptr;
        RoadTypeIntervalExtractorSPtrType road_type_interval_extractor_ptr_ = nullptr;
        MapAttributesExtractorUPtrType    map_attributes_extractor_ptr_     = nullptr;
    };

public:
    Attributor()  = default;
    ~Attributor() = default;

    /**
     * @brief Init odm config.
     * @param[in] ptr_ret Retriever pointer.
     * @param[in] ptr_config: Odm config.
     * @return True if successful,False if failed.
     */
    holo::bool_t Init(RetrieverSPType const& ptr_ret, navigator::config::NavigatorConfigSPtr const& ptr_config);

    /**
     * @brief Get ODM extractor.
     * @return ODM extractor.
     */
    ODMExtractor const& GetODMExtractor() const noexcept;

private:
    RetrieverSPType                        ptr_ret_ = nullptr;
    ODMExtractor                           odm_extractor_;
    navigator::config::NavigatorConfigSPtr ptr_config_ = nullptr;
};

using AttributorSPtrType = std::shared_ptr<Attributor>;

/**
 * @}
 */
}  //< namespace map
}  //< namespace holo

#endif  /* HOLO_MAP_FEATURE_ATTRIBUTOR_H_ */