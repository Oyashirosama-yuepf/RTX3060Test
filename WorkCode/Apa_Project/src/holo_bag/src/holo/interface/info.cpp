/**
 * @file info.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file is the implement of the info
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#include <holo/bag/interface/info.h>

#include <memory>
#include <stdexcept>
#include <string>

namespace holo
{
namespace bag
{
BagMetadata Info::ReadMetadata(const std::string& uri)
{
    std::shared_ptr<holo::bag::storage_interfaces::ReadOnlyInterface> storage_;
    storage_ = std::make_shared<holo::bag::SqliteStorage>();
    storage_->Open(uri, holo::bag::storage_interfaces::IOFlag::READ_ONLY);
    if (!storage_)
    {
        throw std::runtime_error{"No storage could be Read. Abort"};
    }
    auto bag_metadata = storage_->GetMetadata();
    return bag_metadata;
}

}  // namespace bag
}  // namespace holo
