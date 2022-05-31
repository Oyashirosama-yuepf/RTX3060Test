/**
 * @file bag_metadata.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the base bag metadata
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_BASE_BAG_METADATA_HPP_
#define _HOLOBAG_BASE_BAG_METADATA_HPP_

#include <holo/bag/base/sys_version_metadata.h>
#include <holo/bag/base/topic_metadata.h>

#include <chrono>
#include <string>
#include <vector>

namespace holo
{
namespace bag
{
struct TopicInformation
{
    TopicMetadata topic_metadata;
    size_t        message_count;
};

struct BagMetadata
{
    int                                                         version  = 1;
    uint64_t                                                    bag_size = 0;
    std::string                                                 storage_identifier;
    std::vector<std::string>                                    relative_file_paths;
    std::chrono::nanoseconds                                    duration;
    std::chrono::time_point<std::chrono::high_resolution_clock> starting_time;
    uint64_t                                                    message_count;
    std::vector<TopicInformation>                               topics_with_message_count;
    std::string                                                 compression_format;
    std::string                                                 compression_mode;

    std::vector<SysVersionMetadata>                             version_data;
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_BAG_METADATA_HPP_
