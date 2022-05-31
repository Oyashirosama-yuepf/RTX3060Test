/**
 * @file info.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the bag info
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_INTERFACE_INFO_HPP_
#define _HOLOBAG_INTERFACE_INFO_HPP_

#include <holo/bag/base/bag_metadata.h>
#include <holo/bag/base/storage_interfaces/read_only_interface.h>
#include <holo/bag/storage/sqlite_storage.h>

#include <string>

namespace holo
{
namespace bag
{
class Info
{
public:
    Info()  = default;
    ~Info() = default;

    BagMetadata ReadMetadata(const std::string& uri);
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_INTERFACE_INFO_HPP_
