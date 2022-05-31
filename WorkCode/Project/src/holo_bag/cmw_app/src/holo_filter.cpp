/**
 * @file holo_filter.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file is the implement of the holo_filter.h
 * @version 0.1
 * @date 2020-06-08
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd. Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#include <holo_filter.h>
#include <chrono>

namespace holo_cmw
{
HoloFilter::HoloFilter()
  : filter_ptr_(std::make_shared<holo::bag::Filter>()), info_ptr_(std::make_shared<holo::bag::Info>())
{
}

void HoloFilter::Filter(const std::string& input_bag, const std::string output_bag, holo::float64_t start_time,
                        holo::float64_t end_time, const std::vector<std::string>& topics)
{
    holo::bag::StorageFilter filter;

    auto metadata         = info_ptr_->ReadMetadata(input_bag);
    auto start_time_epoch = metadata.starting_time.time_since_epoch();
    auto start_ns         = std::chrono::duration_cast<std::chrono::nanoseconds>(start_time_epoch);

    // relative time, to nanoseconds
    holo::int64_t start_timestamp = (holo::int64_t)(start_time * 1000000000) + start_ns.count();
    holo::int64_t end_timestamp   = -1;  // (holo::int64_t)(end_time * 1000000000);

    if (end_time >= 0)
    {
        if (end_time < start_time)
        {
            throw std::logic_error("the end time must larger than start time");
        }
        end_timestamp = (holo::int64_t)(end_time * 1000000000) + start_ns.count();
    }

    filter.timestamps.push_back(start_timestamp);
    filter.timestamps.push_back(end_timestamp);
    std::vector<std::string> input_topics;
    for (size_t i = 0; i < topics.size(); i++)
    {
        if (topics.at(i) != "")
        {
            input_topics.push_back(topics.at(i));
        }
    }
    filter.topics = input_topics;
    filter_ptr_->Open(output_bag);
    filter_ptr_->SetFilter(filter);
    filter_ptr_->UseFilter(input_bag);
}
}  // namespace holo_cmw
