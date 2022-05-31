/**
 * @file writer.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file is the implement of the writer
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#include <holo/bag/interface/writer.h>

namespace holo
{
namespace bag
{
Writer::Writer()
{
    writer_impl_ = std::make_unique<SequentialWriter>();
}

Writer::~Writer()
{
    writer_impl_->Reset();
}

void Writer::Open(const StorageOptions& storage_options)
{
    writer_impl_->Open(storage_options);
}

bool Writer::HasNext()
{
    return writer_impl_->HasNext();
}

std::shared_ptr<SerializedBagMessage> Writer::ReadNext()
{
    return writer_impl_->ReadNext();
}

const BagMetadata& Writer::GetMetadata() const
{
    return writer_impl_->GetMetadata();
}

void Writer::CreateTopic(const TopicMetadata& topic_with_type)
{
    writer_impl_->CreateTopic(topic_with_type);
}

void Writer::RemoveTopic(const TopicMetadata& topic_with_type)
{
    writer_impl_->RemoveTopic(topic_with_type);
}

void Writer::Write(std::shared_ptr<SerializedBagMessage> message)
{
    writer_impl_->Write(message);
}

void Writer::Write(std::vector<std::shared_ptr<const SerializedBagMessage>> messages)
{
    writer_impl_->Write(messages);
}

void Writer::WriteAllParams(const std::vector<std::shared_ptr<ParamMetadata>>& params)
{
    writer_impl_->WriteAllParams(params);
}

void Writer::WriteVersion(const std::vector<std::shared_ptr<SysVersionMetadata>>& version)
{
    writer_impl_->WriteVersion(version);
}

void Writer::WriteTag(std::shared_ptr<const TagMessage> tag)
{
    writer_impl_->WriteTag(tag);
}

void Writer::ClearTags()
{
    writer_impl_->ClearTags();
}

std::pair<::holo::bool_t, ::holo::bool_t> Writer::ShouldSplitBagFile()
{
    return writer_impl_->ShouldSplit();
}

}  // namespace bag
}  // namespace holo
