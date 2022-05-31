/**
 * @file storage_options.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the base storage options
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#ifndef _HOLOBAG_INTERFACE_STORAGE_OPTIONS_HPP_
#define _HOLOBAG_INTERFACE_STORAGE_OPTIONS_HPP_

#include <string>

namespace holo
{
namespace bag
{
struct StorageOptions
{
public:
    std::string uri;
    uint64_t    max_bagfile_size      = 0;
    uint64_t    max_bagfile_duration  = 0;
    uint64_t    max_cache_size        = 0;
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_INTERFACE_STORAGE_OPTIONS_HPP_
