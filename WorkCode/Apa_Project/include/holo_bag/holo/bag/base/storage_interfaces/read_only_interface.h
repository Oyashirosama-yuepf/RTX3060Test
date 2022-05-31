/**
 * @file read_only_interface.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the read only interface about the storage
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_BASE_STORAGE_INTERFACES_READ_ONLY_INTERFACE_HPP_
#define _HOLOBAG_BASE_STORAGE_INTERFACES_READ_ONLY_INTERFACE_HPP_

#include <holo/bag/base/storage_filter.h>
#include <holo/bag/base/storage_interfaces/base_info_interface.h>
#include <holo/bag/base/storage_interfaces/base_io_interface.h>
#include <holo/bag/base/storage_interfaces/base_read_interface.h>

#include <string>

namespace holo
{
namespace bag
{
namespace storage_interfaces
{
class ReadOnlyInterface : public BaseInfoInterface, public BaseIOInterface, public BaseReadInterface
{
public:
    virtual ~ReadOnlyInterface() = default;

    void Open(const std::string& uri, IOFlag io_flag = IOFlag::READ_ONLY) override = 0;

    uint64_t GetBagfileSize() const override = 0;

    std::string GetStorageIdentifier() const override = 0;

    virtual void SetFilter(const StorageFilter& storage_filter) = 0;

    virtual void ResetFilter() = 0;
};

}  // namespace storage_interfaces
}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_STORAGE_INTERFACES_READ_ONLY_INTERFACE_HPP_
