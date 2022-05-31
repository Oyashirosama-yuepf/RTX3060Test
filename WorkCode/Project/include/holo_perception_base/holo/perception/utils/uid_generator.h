/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file uid_generator.h
 * @brief This header file defines uid generator.
 * @author sunzhenqiang(sunzhenqiang@holomaitc.com)
 * @date "2019-12-13"
 */

#ifndef HOLO_PERCEPTION_UTILS_UID_GENERATOR_H_
#define HOLO_PERCEPTION_UTILS_UID_GENERATOR_H_

#include <holo/core/types.h>
#include <atomic>

namespace holo
{
namespace perception
{
/**
 * @addtogroup utils
 *
 * @{
 */

/**
 * @brief This is a singleton class used for generating unique uint64_t number.
 *
 */
class UidGenerator
{
public:
    /**
     * @brief Get UidGenerator instance
     *
     * @return UidGenerator&
     */
    static UidGenerator& GetInstance()
    {
        static UidGenerator generator;
        return generator;
    }

    /**
     * @brief Get next unique id and update internal counter.
     *
     * @return uint64_t next id
     */
    uint64_t GetUid();

    /**
     * @brief Peek uid
     *
     * @return uint64_t
     */
    uint64_t PeekUid();
    UidGenerator(const UidGenerator& other) = delete;
    UidGenerator& operator=(const UidGenerator& other) = delete;

private:
    UidGenerator();
    std::atomic<uint64_t> uid_;
};

inline UidGenerator::UidGenerator() : uid_(0)
{
}

inline uint64_t UidGenerator::GetUid()
{
    return uid_++;
}

inline uint64_t UidGenerator::PeekUid()
{
    return uid_;
}

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_UTILS_UID_GENERATOR_H_
