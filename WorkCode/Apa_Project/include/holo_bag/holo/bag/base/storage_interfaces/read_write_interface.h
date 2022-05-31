/**
 * @file read_write_interface.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the read write interface about the storage
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_BASE_STORAGE_INTERFACES_READ_WRITE_INTERFACE_HPP_
#define _HOLOBAG_BASE_STORAGE_INTERFACES_READ_WRITE_INTERFACE_HPP_

#include <holo/bag/base/storage_filter.h>
#include <holo/bag/base/storage_interfaces/base_write_interface.h>
#include <holo/bag/base/storage_interfaces/read_only_interface.h>

#include <string>

namespace holo
{
namespace bag
{
namespace storage_interfaces
{
class ReadWriteInterface : public ReadOnlyInterface, public BaseWriteInterface
{
public:
    ~ReadWriteInterface() override = default;

    void Open(const std::string& uri, IOFlag io_flag = IOFlag::READ_WRITE) override = 0;

    uint64_t GetBagfileSize() const override = 0;

    std::string GetStorageIdentifier() const override = 0;

    virtual uint64_t GetMinimumSplitFileSize() const = 0;

    void SetFilter(const StorageFilter& storage_filter) override = 0;

    void ResetFilter() override = 0;

    virtual bool Filter(const std::string& output_holobag) = 0;

    

};

}  // namespace storage_interfaces
}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_STORAGE_INTERFACES_READ_WRITE_INTERFACE_HPP_
