/**
 * @file base_write_interface.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the base write interface about the storage
 * @version 0.1
 * @date 2020-04-27
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_BASE_STORAGE_INTERFACES_BASE_WRITE_INTERFACE_HPP_
#define _HOLOBAG_BASE_STORAGE_INTERFACES_BASE_WRITE_INTERFACE_HPP_

#include <holo/bag/base/param_metadata.h>
#include <holo/bag/base/serialized_bag_message.h>
#include <holo/bag/base/sys_version_metadata.h>
#include <holo/bag/base/tag_metadata.h>
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
class BaseWriteInterface
{
public:
    virtual ~BaseWriteInterface() = default;

    virtual void Write(std::shared_ptr<const SerializedBagMessage> msg) = 0;

    virtual void Write(const std::vector<std::shared_ptr<const SerializedBagMessage>>& msg) = 0;

    virtual void CreateTopic(const TopicMetadata& topic) = 0;

    virtual void RemoveTopic(const TopicMetadata& topic) = 0;

    virtual void WriteAllParams(const std::vector<std::shared_ptr<ParamMetadata>>& params) = 0;

    virtual void WriteVersion(const std::vector<std::shared_ptr<SysVersionMetadata>>& version) = 0;

    virtual void WriteTag(std::shared_ptr<const TagMessage> msg) = 0;
    virtual void WriteTags(const std::vector<std::shared_ptr<const TagMessage>>& tags) = 0;
    virtual void ClearTags() = 0;
};

}  // namespace storage_interfaces
}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_STORAGE_INTERFACES_BASE_WRITE_INTERFACE_HPP_
