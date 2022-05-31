/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file auto_spin_mutex.h
 * @brief Auto spin mutex(CAS)
 * @author wanghaiyang@holomatic.com
 * @date "2019-06-13"
 */

#ifndef HOLO_MAP_COMMON_CLASSES_AUTO_SPIN_MUTEX_H_
#define HOLO_MAP_COMMON_CLASSES_AUTO_SPIN_MUTEX_H_

#include <holo/map/common/classes/spin_mutex.h>

namespace holo
{
namespace map
{

/**
 * @addtogroup map
 * @{
 *
 */

class AutoSpinMutex
{
public:
    AutoSpinMutex(SpinMutex&);
    ~AutoSpinMutex() noexcept;

    AutoSpinMutex(const AutoSpinMutex&) = delete;
    AutoSpinMutex(AutoSpinMutex&&)  = delete;

    AutoSpinMutex& operator = (const AutoSpinMutex&) = delete;
    AutoSpinMutex& operator = (AutoSpinMutex&&) = delete;

private:
    SpinMutex& mutex_;
}; ///< End of class AutoSpinMutex.

/**
 * @}
 *
 */

} ///< namespace map
} ///< namespace holo

#endif // HOLO_MAP_COMMON_CLASSES_AUTO_SPIN_MUTEX_H_


