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
#include <holo/bag/interface/reader.h>

namespace holo
{
namespace bag
{
Reader::Reader() : reader_impl_(std::make_unique<SequentialReader>())
{
}

Reader::~Reader()
{
    reader_impl_->Reset();
}

void Reader::Open(const StorageOptions& storage_options)
{
    reader_impl_->Open(storage_options);
}

bool Reader::HasNext()
{
    return reader_impl_->HasNext();
}

std::shared_ptr<SerializedBagMessage> Reader::ReadNext()
{
    return reader_impl_->ReadNext();
}

const BagMetadata& Reader::GetMetadata() const
{
    return reader_impl_->GetMetadata();
}

std::vector<TopicMetadata> Reader::GetAllTopicsAndTypes() const
{
    return reader_impl_->GetAllTopicsAndTypes();
}

void Reader::SetFilter(const StorageFilter& storage_filter)
{
    reader_impl_->SetFilter(storage_filter);
}

void Reader::ResetFilter()
{
    reader_impl_->ResetFilter();
}

std::vector<ParamMetadata> Reader::GetAllParamsFile() const
{
    return reader_impl_->GetAllParamsFile();
}

}  // namespace bag
}  // namespace holo
