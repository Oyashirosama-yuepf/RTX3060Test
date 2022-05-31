/**
 * @file storage_filter.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the storage filter
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#ifndef _HOLOBAG_BASE_STORAGE_FILTER_HPP_
#define _HOLOBAG_BASE_STORAGE_FILTER_HPP_

#include <string>
#include <vector>

namespace holo
{
namespace bag
{
struct StorageFilter
{
    /** 
     * Topic names to whitelist when reading a bag. Only messages matching these
     * specified topics will be returned. If list is empty, the filter is ignored
     * and all messages are returned.
     */
    std::vector<std::string> topics;
    std::vector<int64_t>     timestamps;
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_STORAGE_FILTER_HPP_
