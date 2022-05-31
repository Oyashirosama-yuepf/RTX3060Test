/**
 * @file holo_filter.h
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief the header of the holo filter class
 * @version 0.1
 * @date 2020-06-05
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd. Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_CMW_APPS_HOLO_FILTER_H_
#define _HOLO_CMW_APPS_HOLO_FILTER_H_

#include <holo/bag/interface/filter.h>
#include <holo/bag/interface/info.h>

#include <memory>
#include <string>
#include <vector>

namespace holo_cmw
{
class HoloFilter
{
public:
    HoloFilter();
    ~HoloFilter() = default;
    void Filter(const std::string& input_bag, const std::string output_bag, holo::float64_t start_time,
                holo::float64_t end_time, const std::vector<std::string>& topics);

private:
    std::shared_ptr<holo::bag::Filter> filter_ptr_;
    std::shared_ptr<holo::bag::Info>   info_ptr_;
};
}  // namespace holo_cmw

#endif  //_HOLO_CMW_APPS_HOLO_FILTER_H_
