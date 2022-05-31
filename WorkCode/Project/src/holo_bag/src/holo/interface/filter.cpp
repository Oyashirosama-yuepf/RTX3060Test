/**
 * @file reader.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file is the implement of the reader
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#include <holo/bag/interface/filter.h>

namespace holo
{
namespace bag
{
Filter::Filter() : storage_(std::make_shared<SqliteStorage>())
{
}

Filter::~Filter()
{
    storage_.reset();
}

void Filter::Open(const std::string& uri)
{
    storage_->Open(uri, storage_interfaces::IOFlag::READ_WRITE);
    if (!storage_)
    {
        throw std::runtime_error{"No storage could be initialized. Abort"};
    }
}

void Filter::SetFilter(const StorageFilter& storage_filter)
{
    storage_->SetFilter(storage_filter);
}

void Filter::ResetFilter()
{
    storage_->ResetFilter();
}

void Filter::UseFilter(const std::string& source_uri)
{
    storage_->Filter(source_uri);
}

}  // namespace bag
}  // namespace holo
