/**
 * @file sequential_writer.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file is the implement of the sequential writer
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#include <holo/log/hololog.h>
#include <holo/bag/base/file_system.h>
#include <holo/bag/base/storage_interfaces/base_io_interface.h>
#include <holo/bag/interface/info.h>
#include <holo/bag/interface/sequential_writer.h>
#include <holo/bag/interface/storage_options.h>

#include <chrono>
#include <memory>
#include <stdexcept>

namespace holo
{
namespace bag
{
SequentialWriter::SequentialWriter() : running_(true)
{
    storage_        = std::make_shared<SqliteStorage>();
    switch_thread_  = std::make_shared<std::thread>(&SequentialWriter::cacheSwitch, this);
    process_thread_ = std::make_shared<std::thread>(&SequentialWriter::processCache, this);
}

SequentialWriter::~SequentialWriter()
{
    Reset();
}

void SequentialWriter::Open(const StorageOptions& storage_options)
{
    base_folder_          = storage_options.uri;
    max_cache_size_       = storage_options.max_cache_size;
    max_bagfile_size_     = storage_options.max_bagfile_size;
    max_bagfile_duration_ = storage_options.max_bagfile_duration;
    start_timestamp_      = std::chrono::high_resolution_clock::now();

    cache_read_.reserve(max_cache_size_);
    cache_write_.reserve(max_cache_size_);

    if (!CreateDirectories(fs::path(base_folder_).ParentPath()))
    {
        throw std::runtime_error("Can not create uri path. Abort");
    }

    storage_->Open(base_folder_, storage_interfaces::IOFlag::READ_WRITE);
    metadata_ = storage_->GetMetadata();
    if (!storage_)
    {
        throw std::runtime_error("No storage could be initialized. Abort");
    }
}

void SequentialWriter::Reset()
{
    running_ = false;
    mc_write_.mt_.unlock();
    mc_write_.cv_.notify_all();
    mc_read_.mt_.unlock();
    mc_read_.cv_.notify_all();
    mc_switch_.mt_.unlock();
    mc_switch_.cv_.notify_all();
    if (switch_thread_ && switch_thread_->joinable())
    {
        switch_thread_->join();
        switch_thread_.reset();
    }
    if (process_thread_ && process_thread_->joinable())
    {
        process_thread_->join();
        process_thread_.reset();
    }
    if (cache_write_.size() > 0)
    {
        storage_->Write(cache_write_);
        cache_write_.clear();
    }
    if (cache_read_.size() > 0)
    {
        storage_->Write(cache_read_);
        cache_read_.clear();
    }
    storage_.reset();
}

bool SequentialWriter::HasNext()
{
    if (storage_)
    {
        return storage_->HasNext();
    }
    throw std::runtime_error("Bag is not open. Call Open() before reading.");
}

std::shared_ptr<SerializedBagMessage> SequentialWriter::ReadNext()
{
    if (storage_)
    {
        auto message = storage_->ReadNext();
        return message;
    }
    throw std::runtime_error("Bag is not open. Call Open() before reading.");
}

const BagMetadata& SequentialWriter::GetMetadata() const
{
    return metadata_;
}

void SequentialWriter::CreateTopic(const TopicMetadata& topic_with_type)
{
    if (!storage_)
    {
        throw std::runtime_error("Bag is not open. Call open() before writing.");
    }

    if (topics_names_to_info_.find(topic_with_type.name) == topics_names_to_info_.end())
    {
        TopicInformation info{};
        info.topic_metadata = topic_with_type;

        auto const insert_res = topics_names_to_info_.insert(std::make_pair(topic_with_type.name, info));

        if (!insert_res.second)
        {
            std::stringstream errmsg;
            errmsg << "Failed to insert topic \"" << topic_with_type.name << "\"!";

            throw std::runtime_error(errmsg.str());
        }

        storage_->CreateTopic(topic_with_type);
    }
}

void SequentialWriter::RemoveTopic(const TopicMetadata& topic_with_type)
{
    if (!storage_)
    {
        throw std::runtime_error("Bag is not open. Call open() before removing.");
    }

    if (topics_names_to_info_.erase(topic_with_type.name) > 0)
    {
        storage_->RemoveTopic(topic_with_type);
    }
    else
    {
        std::stringstream errmsg;
        errmsg << "Failed to remove the non-existing topic \"" << topic_with_type.name << "\"!";

        throw std::runtime_error(errmsg.str());
    }
}

void SequentialWriter::Write(std::shared_ptr<SerializedBagMessage> message)
{
    if (!storage_)
    {
        throw std::runtime_error("Bag is not open. Call open() before writing.");
    }

    if (cache_write_.size() <= 0 && topics_names_to_info_.at(message->topic_name).message_count <= 0)
    {
        start_timestamp_ = std::chrono::high_resolution_clock::now();
        LOG(INFO) << "Get the first time.";
    }

    // Update the message count for the Topic.
    ++topics_names_to_info_.at(message->topic_name).message_count;

    // if cache size is set to zero, we directly call write
    if (max_cache_size_ == 0u)
    {
        std::lock_guard<std::mutex> guard(mutex_write_bag_);
        storage_->Write(message);
    }
    else
    {
        std::unique_lock<std::mutex> ulgw(mc_write_.mt_);
        cache_write_.push_back(message);
        if (cache_write_.size() >= max_cache_size_ * 0.8)
        {
            mc_write_.cv_.notify_one();
        }
    }
}

void SequentialWriter::Write(std::vector<std::shared_ptr<const SerializedBagMessage>> messages)
{
    if (!storage_)
    {
        throw std::runtime_error("Bag is not open. Call open() before writing.");
    }
    for (auto message : messages)
    {
        // Update the message count for the Topic.
        ++topics_names_to_info_.at(message->topic_name).message_count;
    }
    std::lock_guard<std::mutex> guard(mutex_write_bag_);
    storage_->Write(messages);
}

void SequentialWriter::WriteAllParams(std::vector<std::shared_ptr<ParamMetadata>> params)
{
    if (!storage_)
    {
        throw std::runtime_error("Bag is not open. Call open() before writing.");
    }
    std::lock_guard<std::mutex> guard(mutex_write_bag_);
    storage_->WriteAllParams(params);
}

void SequentialWriter::WriteVersion(std::vector<std::shared_ptr<SysVersionMetadata>> version)
{
    if (!storage_)
    {
        throw std::runtime_error("Bag is not open. Call open() before writing.");
    }
    std::lock_guard<std::mutex> guard(mutex_write_bag_);
    storage_->WriteVersion(version);
}

void SequentialWriter::WriteTag(std::shared_ptr<const TagMessage> tag)
{
    if (!storage_)
    {
        throw std::runtime_error("Bag is not open. Call open() before writing.");
    }
    std::lock_guard<std::mutex> guard(mutex_write_bag_);
    storage_->WriteTag(tag);
}

void SequentialWriter::ClearTags()
{
    if (!storage_)
    {
        throw std::runtime_error("Bag is not open. Call open() before writing.");
    }
    storage_->ClearTags();
}

std::pair<::holo::bool_t, ::holo::bool_t> SequentialWriter::ShouldSplit()
{
    // Assume we aren't splitting
    std::pair<::holo::bool_t, ::holo::bool_t> should_split = std::make_pair(false, false);
    //bool                                      should_split = false;

    // Splitting by size
    if (max_bagfile_size_ != holo::bag::storage_interfaces::MAX_BAGFILE_SIZE_NO_SPLIT)
    {
        should_split.first  = should_split.first || (storage_->GetBagfileSize() > max_bagfile_size_);
        should_split.second = should_split.second || (storage_->GetBagfileSize() > (max_bagfile_size_ * 0.95));
    }

    // Splitting by time
    if (max_bagfile_duration_ != holo::bag::storage_interfaces::MAX_BAGFILE_DURATION_NO_SPLIT)
    {
        std::chrono::duration<::holo::float64_t> time_diff = std::chrono::high_resolution_clock::now() - start_timestamp_;
        should_split.first  = should_split.first || (time_diff.count() > max_bagfile_duration_);
        should_split.second = should_split.second || ((time_diff.count() + 2) > max_bagfile_duration_);
    }
    return should_split;
}

void SequentialWriter::cacheSwitch()
{
    while (running_)
    {
        {
            std::unique_lock<std::mutex> ulgw(mc_write_.mt_);
            while (cache_write_.size() < max_cache_size_ * 0.5)
            {
                mc_write_.cv_.wait(ulgw);
                if (!running_)
                {
                    break;
                }
            }
            std::lock_guard<std::mutex> ulgr(mc_read_.mt_);
            std::swap(cache_read_, cache_write_);
            if (!cache_read_.empty())
            {
                mc_read_.cv_.notify_one();
            }
        }
        std::unique_lock<std::mutex> ulgs(mc_switch_.mt_);
        while (!cache_read_.empty() && running_)
        {
            mc_switch_.cv_.wait(ulgs);
        }
    }
}

void SequentialWriter::processCache()
{
    while (running_)
    {
        std::unique_lock<std::mutex> ulgr(mc_read_.mt_);
        while (cache_read_.empty())
        {
            mc_read_.cv_.wait(ulgr);
            if (!running_)
            {
                break;
            }
        }
        // deal data
        while (!cache_read_.empty())
        {
            std::lock_guard<std::mutex> guard(mutex_write_bag_);
            storage_->Write(cache_read_);
            cache_read_.clear();
        }
        mc_switch_.cv_.notify_one();
    }
}

}  // namespace bag
}  // namespace holo
