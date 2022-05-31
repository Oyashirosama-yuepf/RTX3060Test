/**
 * @file sqlite_storage.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the sqlite storage
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_STORAGE_SQLITE_STORAGE_HPP_
#define _HOLOBAG_STORAGE_SQLITE_STORAGE_HPP_

#include <holo/bag/base/topic_metadata.h>
#include <holo/bag/base/param_metadata.h>
#include <holo/bag/base/serialized_bag_message.h>
#include <holo/bag/base/sys_version_metadata.h>
#include <holo/bag/base/storage_filter.h>
#include <holo/bag/base/storage_interfaces/read_write_interface.h>
#include <holo/bag/storage/sqlite_wrapper.h>

#include <atomic>
#include <memory>
#include <unordered_map>
#include <vector>
#include <mutex>

namespace holo
{
namespace bag
{
class SqliteStorage : public storage_interfaces::ReadWriteInterface
{
public:
    using DataSequenceType = holo::container::Vector<uint8_t, std::numeric_limits<size_t>::max()>;

    SqliteStorage() = default;

    ~SqliteStorage();

    void Open(const std::string&         uri,
              storage_interfaces::IOFlag io_flag = storage_interfaces::IOFlag::READ_WRITE) override;

    void RemoveTopic(const TopicMetadata& topic) override;

    void CreateTopic(const TopicMetadata& topic) override;

    void Write(std::shared_ptr<const SerializedBagMessage> message) override;

    void Write(const std::vector<std::shared_ptr<const SerializedBagMessage>>& messages) override;

    bool HasNext() override;

    std::shared_ptr<SerializedBagMessage> ReadNext() override;

    std::vector<TopicMetadata> GetAllTopicsAndTypes() override;

    BagMetadata GetMetadata() override;

    std::string GetRelativeFilePath() const override;

    uint64_t GetBagfileSize() const override;

    std::string GetStorageIdentifier() const override;

    uint64_t GetMinimumSplitFileSize() const override;

    bool Filter(const std::string& input_holobag) override;

    void WriteAllParams(const std::vector<std::shared_ptr<ParamMetadata>>& params) override;

    std::vector<ParamMetadata> GetAllParamsFile() override;

    void WriteVersion(const std::vector<std::shared_ptr<SysVersionMetadata>>& version) override;

    std::vector<SysVersionMetadata> GetAllSysVersion() override;

    void SetFilter(const StorageFilter& storage_filter) override;

    void ResetFilter() override;

    void WriteTag(std::shared_ptr<const TagMessage> msg) override;
    void WriteTags(const std::vector<std::shared_ptr<const TagMessage>>& tags) override;
    void ClearTags();

private:
    void initialize();
    void prepareForWriting();
    void prepareForReading();
    void fillTopicsAndTypes();
    void activateTransaction();
    void commitTransaction();
    void prepareForWriteTag();

    using ReadQueryResult =
        SqliteStatementWrapper::QueryResult<DataSequenceType, int64_t, std::string>;

    std::shared_ptr<SqliteWrapper> database_;
    SqliteStatement                write_statement_{};
    SqliteStatement                read_statement_{};
    SqliteStatement                write_tag_statement_{};
    ReadQueryResult                message_result_{nullptr};
    ReadQueryResult::Iterator      current_message_row_{nullptr,
                                                   SqliteStatementWrapper::QueryResult<>::Iterator::POSITION_END};

    std::mutex                           topics_mutex_;
    std::mutex                           tag_mutex_;
    std::unordered_map<std::string, int> topics_;
    std::vector<TopicMetadata>           all_topics_and_types_;
    std::string                          relative_path_;
    std::atomic_bool                     active_transaction_{false};
    StorageFilter                        storage_filter_{};
};

}  // namespace bag
}  // namespace holo

#endif  // #define _HOLOBAG_STORAGE_SQLITE_STORAGE_HPP_
