/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file valid_checker.h
 * @brief This header file defines ValidChecker for function safety.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2022-05-09"
 */

#ifndef HOLO_PERCEPTION_UTILS_VALID_CHECKER_H_
#define HOLO_PERCEPTION_UTILS_VALID_CHECKER_H_

#include <holo/core/types.h>

namespace holo
{
namespace perception
{
class ValidChecker
{
public:
    /**
     * @brief Construct a new Valid Checker object
     *
     * @param invalid_count_thresh invalid count thresh
     */
    ValidChecker(uint32_t invalid_count_thresh)
      : valid_flag_(true), invalid_count_(0U), invalid_count_thresh_(invalid_count_thresh)
    {
    }

    /**
     * @brief Update valid state
     *
     * @param is_invalid if it is a invalid message
     * @return bool_t if the message is VALID
     */
    bool_t Update(bool_t is_invalid)
    {
        if (true == is_invalid)
        {
            ++invalid_count_;
            if (invalid_count_ >= invalid_count_thresh_)
            {
                valid_flag_ = false;
            }
        }
        else
        {
            valid_flag_    = true;
            invalid_count_ = 0U;
        }
        return valid_flag_;
    }

private:
    bool_t   valid_flag_;
    uint32_t invalid_count_;
    uint32_t invalid_count_thresh_;
};

}  // namespace perception
}  // namespace holo

#endif
