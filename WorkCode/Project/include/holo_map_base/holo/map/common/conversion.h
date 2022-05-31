/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file conversion.h
 * @brief conversion.h
 * @author wanghaiyang@holomatic.com
 * @date "2021-10-08"
 */

#ifndef HOLO_MAP_FORMAT_CONVERSION_H_
#define HOLO_MAP_FORMAT_CONVERSION_H_

#include <holo/map/format/base/base.h>
#include <holo/map/service/session/task_manager.h>

namespace holo
{
namespace map
{
namespace format
{
namespace conversion
{
/**
 * @addtogroup conversion
 * @{
 *
 */

/// Redefine item type for session.
using SessionItemType = holo::map::service::session::SessionType::ItemFeatureType;

/// Redefine feature type for HD map feature.
using DataFeatureType = holo::map::format::Base::FeatureType;

/**
 * @brief Convert HD map feature type to session item type.
 * 
 * @param[in] type A HD map feature type, refer to holo::map::format::Base::FeatureType
 *            for more details.
 * @return A session item type, refer to holo::map::service::DataPackage::ItemFeatureType
 *         for more details.
 */
SessionItemType Convert(DataFeatureType const type);

/**
 * @brief Convert session item type to HD map feature type.
 * 
 * @param[in] type  A session item type, refer to holo::map::service::DataPackage::ItemFeatureType
 *            for more details.
 * @return A HD map feature type, refer to holo::map::format::Base::FeatureType
 *         for more details.
 */
DataFeatureType Convert(SessionItemType const type);

/**
 * @}
 */
} ///< namespace conversion
} ///< namespace format
} ///< namespace map
} ///< namespace holo


#endif /* HOLO_MAP_FORMAT_CONVERSION_H_ */