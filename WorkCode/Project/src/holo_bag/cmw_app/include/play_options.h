/**
 * @file play_options.h
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the play option for holo_replay cmw app
 * @version 0.1
 * @date 2020-05-09
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_CMW_APPS_PLAY_OPTIONS_H_
#define _HOLO_CMW_APPS_PLAY_OPTIONS_H_

#include <holo/core/types.h>

#include <chrono>

namespace holo_cmw
{
struct PlayOptions
{
    holo::uint32_t            read_ahead_queue_size_             = 100;
    holo::float64_t           read_ahead_lower_bound_percentage_ = 0.9;
    holo::float32_t           rate_                              = 1.0;
    holo::float64_t           skip_time_                         = 0.0;
    std::chrono::milliseconds queue_read_wait_period_ = std::chrono::milliseconds(100);
    
};
}  // namespace holo_cmw
#endif  //_HOLO_CMW_APPS_PLAY_OPTIONS_H_
