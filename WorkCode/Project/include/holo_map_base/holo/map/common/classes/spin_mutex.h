/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spin_mutex.h
 * @brief SpinMutex
 * @author wanghaiyang@holomatic.com
 * @date "2019-06-13"
 */

#ifndef HOLO_MAP_COMMON_CLASSES_SPIN_MUTEX_H_
#define HOLO_MAP_COMMON_CLASSES_SPIN_MUTEX_H_

#include <atomic>

#include <holo/map/common/common_type_define.h>

namespace holo
{
namespace map
{

/**
 * @addtogroup map
 * @{
 *
 */

class SpinMutex 
{
public:
    SpinMutex() = default;
    ~SpinMutex() = default;

    SpinMutex(const SpinMutex&) = delete;
    SpinMutex(SpinMutex&&)  = delete;

    SpinMutex& operator = (const SpinMutex&) = delete;
    SpinMutex& operator = (SpinMutex&&) = delete;

    void Lock();
    
    void Unlock();

    /**
     * @brief Access the underlying data.
     
     * @note It's not recommended to call this function, just used in unit tests. 
     * @return The raw data value.
     */
    holo::bool_t GetRawData();

private:
    std::atomic<holo::bool_t> data_{false};   
}; ///< End of class SpinMutex.

/**
 * @}
 *
 */

} ///< namespace map
} ///< namespace holo

#endif // HOLO_MAP_COMMON_CLASSES_SPIN_MUTEX_H_