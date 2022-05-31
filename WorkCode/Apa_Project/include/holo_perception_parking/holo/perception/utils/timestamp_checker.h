/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file timestamp_checker.h
 * @brief This header file defines timestamp checker with state transition.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-12-09"
 */

#ifndef HOLO_PERCEPTION_UTILS_TIMESTAMP_CHECKER_H_
#define HOLO_PERCEPTION_UTILS_TIMESTAMP_CHECKER_H_

#include <holo/obstacle/obstacle_list.h>

namespace holo
{
namespace perception
{
/**
 * @brief Timestamp checker, define a state transitio rule
 * @ref https://holomatic.feishu.cn/docs/doccn8qrabpjy4kyTBpVcZEfFBh
 */
class TimestampChecker
{
public:
    /**
     * @brief Construct a new Timestamp Checker object
     *
     * @param recover_count_thresh recover count thresh
     * @param invalid_count_thresh invalid count thresh
     */
    TimestampChecker(uint32_t recover_count_thresh, uint32_t invalid_count_thresh)
      : valid_flag_(false)
      , recover_count_(0U)
      , invalid_count_(0U)
      , recover_count_thresh_(recover_count_thresh)
      , invalid_count_thresh_(invalid_count_thresh)
    {
    }

    /**
     * @brief Update state
     *
     * @param recv_msg if recv a new message
     * @param is_recover if it is a recover message
     * @param is_invalid if it is a invalid message
     * @return bool_t if the message timestamp is VALID
     */
    bool_t Update(bool_t recv_msg, bool_t is_recover, bool_t is_invalid)
    {
        if (false == valid_flag_)
        {
            if (recv_msg)
            {
                if (is_recover)
                {
                    ++recover_count_;
                    if (recover_count_ >= recover_count_thresh_)
                    {
                        invalid_count_ = 0U;
                        valid_flag_    = true;
                    }
                }
                else
                {
                    recover_count_ = 0U;
                }
            }
            else
            {
                recover_count_ = 0U;
            }
        }
        else
        {
            if (recv_msg)
            {
                if (is_invalid)
                {
                    ++invalid_count_;
                    if (invalid_count_ >= invalid_count_thresh_)
                    {
                        recover_count_ = 0U;
                        valid_flag_    = false;
                    }
                }
                else
                {
                    invalid_count_ = 0U;
                }
            }
            else
            {
                ++invalid_count_;
            }
        }
        return valid_flag_;
    }

    /**
     * @brief Get the Valid Flag
     *
     * @return bool_t true if the timestamp of message is valid
     */
    bool_t GetValidFlag() const
    {
        return valid_flag_;
    }

private:
    bool_t   valid_flag_;
    uint32_t recover_count_;
    uint32_t invalid_count_;
    uint32_t recover_count_thresh_;
    uint32_t invalid_count_thresh_;
};
}  // namespace perception
}  // namespace holo

#endif
