/**
 * @file sequential_reader.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file is the implement of the sequential reader
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#include <holo/log/hololog.h>
#include <holo/bag/base/file_system.h>
#include <holo/bag/interface/sequential_reader.h>

#include <stdexcept>

namespace
{
void FillTopicsAndTypes(const holo::bag::BagMetadata& metadata, std::vector<holo::bag::TopicMetadata>& topics_and_types)
{
    topics_and_types.clear();
    topics_and_types.reserve(metadata.topics_with_message_count.size());
    for (const auto& topic_information : metadata.topics_with_message_count)
    {
        topics_and_types.push_back(topic_information.topic_metadata);
    }
}
}  // unnamed namespace

namespace holo
{
namespace bag
{

SequentialReader::SequentialReader() : storage_(std::make_shared<SqliteStorage>())
{
}

SequentialReader::~SequentialReader()
{
    Reset();
}

void SequentialReader::Reset()
{
    if (storage_)
    {
        storage_.reset();
    }
}

void SequentialReader::Open(const StorageOptions& storage_options)
{
    storage_->Open(storage_options.uri, storage_interfaces::IOFlag::READ_ONLY);
    if (!storage_)
    {
        throw std::runtime_error{"No storage could be initialized. Abort"};
    }

    metadata_ = storage_->GetMetadata();
    if (metadata_.relative_file_paths.empty())
    {
        LOG(ERROR) << "No file paths were found in metadata.";
        return;
    }

    file_paths_            = metadata_.relative_file_paths;
    current_file_iterator_ = file_paths_.begin();
    // }

    auto topics = metadata_.topics_with_message_count;
    if (topics.empty())
    {
        LOG(ERROR) << "No topics were listed in metadata.";
        return;
    }
    FillTopicsAndTypes(metadata_, topics_metadata_);

    /// Currently a bag file can only be played if all topics have the same serialization format.
    checkTopicsSerializationFormats(topics);
}

bool SequentialReader::HasNext()
{
    if (storage_)
    {
        bool next_msg_flag = storage_->HasNext();
        /**
         * If there's no new message, check if there's at least another file to read and update storage
         * to read from there. Otherwise, check if there's another message.
         */
        if (!next_msg_flag && HasNextFile())
        {
            loadNextFile();
            storage_->Open(GetCurrentFile(), storage_interfaces::IOFlag::READ_ONLY);
        }

        return next_msg_flag;
    }
    throw std::runtime_error("Bag is not open. Call Open() before reading.");
}

std::shared_ptr<SerializedBagMessage> SequentialReader::ReadNext()
{
    if (storage_)
    {
        auto message = storage_->ReadNext();
        return message;
    }
    throw std::runtime_error("Bag is not open. Call Open() before reading.");
}

const BagMetadata& SequentialReader::GetMetadata() const
{
    return metadata_;
}

std::vector<TopicMetadata> SequentialReader::GetAllTopicsAndTypes() const
{
    return topics_metadata_;
}

void SequentialReader::SetFilter(const StorageFilter& storage_filter)
{
    if (storage_)
    {
        storage_->SetFilter(storage_filter);
        return;
    }
    throw std::runtime_error("Bag is not open. Call Open() before setting filter.");
}

void SequentialReader::ResetFilter()
{
    if (storage_)
    {
        storage_->ResetFilter();
        return;
    }
    throw std::runtime_error("Bag is not open. Call Open() before resetting filter.");
}

std::vector<ParamMetadata> SequentialReader::GetAllParamsFile() const
{
    if (storage_)
    {
        return storage_->GetAllParamsFile();
    }
    throw std::runtime_error("Bag is not open. Call Open() before get all params file.");
}

bool SequentialReader::HasNextFile() const
{
    return current_file_iterator_ + 1 != file_paths_.end();
}

void SequentialReader::loadNextFile()
{
    current_file_iterator_++;
}

std::string SequentialReader::GetCurrentFile() const
{
    return *current_file_iterator_;
}

std::string SequentialReader::GetCurrentUri() const
{
    auto current_file = GetCurrentFile();
    auto current_uri  = fs::RemoveExtension(current_file);
    return current_uri.GetPath();
}

void SequentialReader::checkTopicsSerializationFormats(const std::vector<TopicInformation>& topics)
{
    auto storage_serialization_format = topics[0].topic_metadata.serialization_format;
    for (const auto& topic : topics)
    {
        if (topic.topic_metadata.serialization_format != storage_serialization_format)
        {
            throw std::runtime_error("Topics with different rwm serialization format have been found. "
                                     "All topics must have the same serialization format.");
        }
    }
}

}  // namespace bag
}  // namespace holo
