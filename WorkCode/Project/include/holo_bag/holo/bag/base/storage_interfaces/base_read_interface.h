/**
 * @file base_read_interface.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the base read interface about the storage
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_BASE_STORAGE_INTERFACES_BASE_READ_INTERFACE_HPP_
#define _HOLOBAG_BASE_STORAGE_INTERFACES_BASE_READ_INTERFACE_HPP_

#include <holo/bag/base/sys_version_metadata.h>
#include <holo/bag/base/param_metadata.h>
#include <holo/bag/base/serialized_bag_message.h>
#include <holo/bag/base/topic_metadata.h>

#include <memory>
#include <string>
#include <vector>

namespace holo
{
namespace bag
{
namespace storage_interfaces
{
class BaseReadInterface
{
public:
    virtual ~BaseReadInterface() = default;

    virtual bool HasNext() = 0;

    virtual std::shared_ptr<SerializedBagMessage> ReadNext() = 0;

    virtual std::vector<TopicMetadata> GetAllTopicsAndTypes() = 0;

    virtual std::vector<ParamMetadata> GetAllParamsFile() = 0;

    virtual std::vector<SysVersionMetadata> GetAllSysVersion() = 0;
};

}  // namespace storage_interfaces
}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_STORAGE_INTERFACES_BASE_READ_INTERFACE_HPP_
