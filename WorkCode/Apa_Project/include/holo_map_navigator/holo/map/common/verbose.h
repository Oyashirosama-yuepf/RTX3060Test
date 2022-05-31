/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file verbose.h
 * @brief Verbose
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-11-08"
 */

#ifndef HOLO_MAP_NAVIGATOR_COMMON_VERBOSE_H_
#define HOLO_MAP_NAVIGATOR_COMMON_VERBOSE_H_

#include <memory>

#include <holo/map/base/feature_id/feature_id.h>
#include <holo/map/common/common_define.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace common
{
/**
 * @addtogroup navigator
 * @{
 *
 */
/**
 * @breif Singleton for verbose to decide to log witch infomation
 */
class Verbose 
{
public:
    using VerboseSPtrType = std::shared_ptr<Verbose>;

    enum class Mode : holo::uint8_t
    {
        UNDEFINED = 0U, 
        NAVIGATION = 1U, 
        LOCAL_MAP_GRAPH = 2U,
        OTHERS = 255
    };

    /**
     * @brief Singleton for verbose
     * 
     * @return Pointer for singleton of verbose
     */
    static VerboseSPtrType Instance();

    /**
     * @brief Set the Enabled 
     * 
     * @param Whether or not to log verbose information
     */
    void SetEnabled(holo::bool_t const enable);

    /**
     * @brief Whether or not to log verbose information
     *
     * @return True, enabled to log; false, disabled
     */
    holo::bool_t Enabled() const;

private:
    Verbose() = default;
    Verbose(Verbose const&) = default;
    Verbose& operator=(Verbose const&) = default;

private:
    /// Singleton for verbose
    static VerboseSPtrType verbose_;
    /// Whether or not to log verbose information
    holo::bool_t enable_ = false;

};
}  // namespace common
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_NAVIGATOR_COMMON_VERBOSE_H_ */
