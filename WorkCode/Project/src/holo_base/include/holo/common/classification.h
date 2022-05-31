/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file classification.h
 * @brief This header file defines Classification.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-04
 */

#ifndef HOLO_COMMON_CLASSIFICATION_H_
#define HOLO_COMMON_CLASSIFICATION_H_

#include <holo/common/details/classification.h>
namespace holo
{
namespace common
{
/**
 * @addtogroup common
 * @{
 *
 */

using Classification = details::Classification;

/**
 * @}
 *
 */
}  // namespace common

using Classification[[deprecated]] = common::Classification;

}  // namespace holo

#endif
