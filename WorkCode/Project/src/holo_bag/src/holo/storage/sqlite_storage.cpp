/**
 * @file sqlite_storage.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file is the implement of the sqlite storage
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#include <holo/log/hololog.h>
#include <holo/bag/base/file_system.h>
#include <holo/bag/storage/sqlite_storage.h>
#include <holo/common/timestamp.h>
#include <sys/stat.h>

#include <chrono>
#include <cstring>

namespace
{
std::string ToString(holo::bag::storage_interfaces::IOFlag io_flag)
{
    switch (io_flag)
    {
        case holo::bag::storage_interfaces::IOFlag::APPEND:
            return "APPEND";
        case holo::bag::storage_interfaces::IOFlag::READ_ONLY:
            return "READ_ONLY";
        case holo::bag::storage_interfaces::IOFlag::READ_WRITE:
            return "READ_WRITE";
        default:
            return "UNKNOWN";
    }
}

bool IsReadWrite(const holo::bag::storage_interfaces::IOFlag io_flag)
{
    return io_flag == holo::bag::storage_interfaces::IOFlag::READ_WRITE;
}

constexpr auto const FILE_EXTENSION = ".holobag";

/// Minimum size of a sqlite3 database file in bytes (84 kiB).
constexpr uint64_t const MIN_SPLIT_FILE_SIZE = 86016;
}  // namespace

namespace holo
{
namespace bag
{
SqliteStorage::~SqliteStorage()
{
    if (active_transaction_)
    {
        commitTransaction();
    }
}

void SqliteStorage::Open(const std::string& uri, storage_interfaces::IOFlag io_flag)
{
    relative_path_ = uri;
    if (IsReadWrite(io_flag))
    {   
        if (!fs::path(relative_path_).Exists())
        {
            relative_path_ = uri + FILE_EXTENSION;
        }
    }
    else
    {
        if (!fs::path(relative_path_).Exists())
        {
            throw std::runtime_error("Failed to read from bag: File '" + relative_path_ + "' does not exist!");
        }
    }

    try
    {
        database_ = std::make_unique<SqliteWrapper>(relative_path_, io_flag);
    }
    catch (const SqliteException& e)
    {
        throw std::runtime_error("Failed to setup storage. Error: " + std::string(e.what()));
    }

    if (IsReadWrite(io_flag))
    {
        initialize();
    }

    read_statement_  = nullptr;
    write_statement_ = nullptr;

    LOG(INFO) << "Opened database " << relative_path_ << " for " << ToString(io_flag) << ".";
}

void SqliteStorage::activateTransaction()
{
    if (active_transaction_)
    {
        return;
    }

    database_->PrepareStatement("BEGIN TRANSACTION;")->ExecuteAndReset();

    active_transaction_ = true;
}

void SqliteStorage::commitTransaction()
{
    if (!active_transaction_)
    {
        return;
    }

    database_->PrepareStatement("COMMIT;")->ExecuteAndReset();

    active_transaction_ = false;
}

void SqliteStorage::Write(std::shared_ptr<const SerializedBagMessage> message)
{
    if (!write_statement_)
    {
        prepareForWriting();
    }
    std::lock_guard<std::mutex> lock(topics_mutex_);
    auto topic_entry = topics_.find(message->topic_name);
    if (topic_entry == end(topics_))
    {
        throw SqliteException("Topic '" + message->topic_name +
                              "' has not been created yet! Call 'CreateTopic' first.");
    }
    write_statement_->Bind(message->time_stamp, topic_entry->second, message->serialized_data);
    write_statement_->ExecuteAndReset();
}

void SqliteStorage::Write(const std::vector<std::shared_ptr<const SerializedBagMessage>>& messages)
{
    if (!write_statement_)
    {
        prepareForWriting();
    }

    activateTransaction();

    for (auto& message : messages)
    {
        Write(message);
    }

    commitTransaction();
}

bool SqliteStorage::HasNext()
{
    if (!read_statement_)
    {
        prepareForReading();
    }

    return current_message_row_ != message_result_.end();
}

std::shared_ptr<SerializedBagMessage> SqliteStorage::ReadNext()
{
    if (!read_statement_)
    {
        prepareForReading();
    }
    std::lock_guard<std::mutex> lock(tag_mutex_);
    auto bag_message = std::make_shared<SerializedBagMessage>();
    auto row = *current_message_row_;

    bag_message->serialized_data = std::get<0>(row);
    bag_message->time_stamp      = std::get<1>(row);
    bag_message->topic_name      = std::get<2>(row);

    ++current_message_row_;
    return bag_message;
}

std::vector<TopicMetadata> SqliteStorage::GetAllTopicsAndTypes()
{
    if (all_topics_and_types_.empty())
    {
        fillTopicsAndTypes();
    }

    return all_topics_and_types_;
}

uint64_t SqliteStorage::GetBagfileSize() const
{
    const auto bag_path = fs::path{GetRelativeFilePath()};
    return bag_path.Exists() ? bag_path.FileSize() : 0u;
}

void SqliteStorage::initialize()
{
    std::string create_stmt = "CREATE TABLE IF NOT EXISTS topics("
                              "id INTEGER PRIMARY KEY,"
                              "name TEXT NOT NULL,"
                              "type TEXT NOT NULL,"
                              "type_version TEXT NOT NULL,"
                              "serialization_format TEXT NOT NULL);";
    database_->PrepareStatement(create_stmt)->ExecuteAndReset();
    create_stmt = "CREATE TABLE IF NOT EXISTS messages("
                  "id INTEGER PRIMARY KEY,"
                  "topic_id INTEGER NOT NULL,"
                  "timestamp INTEGER NOT NULL, "
                  "data BLOB NOT NULL);";
    database_->PrepareStatement(create_stmt)->ExecuteAndReset();
    create_stmt = "CREATE INDEX IF NOT EXISTS msg_timestamp_idx ON messages (timestamp ASC);";
    database_->PrepareStatement(create_stmt)->ExecuteAndReset();
    create_stmt = "CREATE TABLE IF NOT EXISTS params("
                  "id INTEGER PRIMARY KEY,"
                  "path TEXT NOT NULL,"
                  "name TEXT NOT NULL,"
                  "file TEXT NOT NULL);";
    database_->PrepareStatement(create_stmt)->ExecuteAndReset();
    create_stmt = "CREATE TABLE IF NOT EXISTS sys_version("
                  "id INTEGER PRIMARY KEY,"
                  "category TEXT NOT NULL,"
                  "type TEXT NOT NULL,"
                  "version TEXT NOT NULL);";
    database_->PrepareStatement(create_stmt)->ExecuteAndReset();
    create_stmt = "CREATE TABLE IF NOT EXISTS tags("
                  "id INTEGER PRIMARY KEY,"
                  "timestamp INTEGER NOT NULL, "
                  "tag TEXT NOT NULL);";
    database_->PrepareStatement(create_stmt)->ExecuteAndReset();
    create_stmt = "CREATE INDEX IF NOT EXISTS tag_timestamp_idx ON tags (timestamp ASC);";
    database_->PrepareStatement(create_stmt)->ExecuteAndReset();
}

void SqliteStorage::CreateTopic(const TopicMetadata& topic)
{
    std::lock_guard<std::mutex> lock(topics_mutex_);
    if (topics_.find(topic.name) == std::end(topics_))
    {
        auto insert_topic =
            database_->PrepareStatement("INSERT INTO topics (name, type, type_version, serialization_format) "
                                        "VALUES (?, ?, ?, ?)");
        insert_topic->Bind(topic.name, topic.type, topic.type_version, topic.serialization_format);
        insert_topic->ExecuteAndReset();
        topics_.emplace(topic.name, static_cast<int>(database_->GetLastInsertId()));
    }
}

void SqliteStorage::RemoveTopic(const TopicMetadata& topic)
{
    std::lock_guard<std::mutex> lock(topics_mutex_);
    if (topics_.find(topic.name) != std::end(topics_))
    {
        auto delete_topic = database_->PrepareStatement(
            "DELETE FROM topics where name = ? and type = ? and type_version = ? and serialization_format = ?");
        delete_topic->Bind(topic.name, topic.type, topic.type_version, topic.serialization_format);
        delete_topic->ExecuteAndReset();
        topics_.erase(topic.name);
    }
}

void SqliteStorage::prepareForWriting()
{
    write_statement_ =
        database_->PrepareStatement("INSERT INTO messages (timestamp, topic_id, data) VALUES (?, ?, ?);");
}

void SqliteStorage::prepareForReading()
{
    if (!storage_filter_.topics.empty())
    {
        // Construct string for selected topics
        std::string topic_list{""};
        for (auto& topic : storage_filter_.topics)
        {
            topic_list += "'" + topic + "'";
            if (&topic != &storage_filter_.topics.back())
            {
                topic_list += ",";
            }
        }

        read_statement_ = database_->PrepareStatement("SELECT data, timestamp, topics.name "
                                                      "FROM messages JOIN topics ON messages.topic_id = topics.id "
                                                      "WHERE topics.name IN (" +
                                                      topic_list +
                                                      ")"
                                                      "ORDER BY messages.timestamp;");
    }
    else
    {
        read_statement_ = database_->PrepareStatement("SELECT data, timestamp, topics.name "
                                                      "FROM messages JOIN topics ON messages.topic_id = topics.id "
                                                      "ORDER BY messages.timestamp;");
    }
    message_result_ = read_statement_->ExecuteQuery<DataSequenceType, int64_t, std::string>();
    current_message_row_ = message_result_.begin();
}

void SqliteStorage::fillTopicsAndTypes()
{
    auto statement =
        database_->PrepareStatement("SELECT name, type, type_version,serialization_format FROM topics ORDER BY id;");
    auto query_results = statement->ExecuteQuery<std::string, std::string, std::string, std::string>();

    for (auto result : query_results)
    {
        all_topics_and_types_.push_back({
            std::get<0>(result),
            std::get<1>(result),
            std::get<2>(result),
            std::get<3>(result),
        });
    }
}

std::string SqliteStorage::GetStorageIdentifier() const
{
    return "sqlite3";
}

std::string SqliteStorage::GetRelativeFilePath() const
{
    return relative_path_;
}

uint64_t SqliteStorage::GetMinimumSplitFileSize() const
{
    return MIN_SPLIT_FILE_SIZE;
}

BagMetadata SqliteStorage::GetMetadata()
{
    BagMetadata metadata;
    metadata.relative_file_paths = {GetRelativeFilePath()};

    metadata.message_count             = 0;
    metadata.topics_with_message_count = {};

    auto statement = database_->PrepareStatement(
        "SELECT name, type, type_version, serialization_format, COUNT(messages.id), MIN(messages.timestamp), "
        "MAX(messages.timestamp) "
        "FROM messages JOIN topics on topics.id = messages.topic_id "
        "GROUP BY topics.name;");
    auto query_results =
        statement->ExecuteQuery<std::string, std::string, std::string, std::string, int, int64_t, int64_t>();

    int64_t min_time = INT64_MAX;
    int64_t max_time = 0;
    for (auto result : query_results)
    {
        metadata.topics_with_message_count.push_back({{
                                                          std::get<0>(result),
                                                          std::get<1>(result),
                                                          std::get<2>(result),
                                                          std::get<3>(result),
                                                      },
                                                      static_cast<size_t>(std::get<4>(result))});

        metadata.message_count += std::get<4>(result);
        min_time = std::get<5>(result) < min_time ? std::get<5>(result) : min_time;
        max_time = std::get<6>(result) > max_time ? std::get<6>(result) : max_time;
    }

    if (metadata.message_count == 0)
    {
        min_time = 0;
        max_time = 0;
    }

    metadata.starting_time =
        std::chrono::time_point<std::chrono::high_resolution_clock>(std::chrono::nanoseconds(min_time));
    metadata.duration     = std::chrono::nanoseconds(max_time) - std::chrono::nanoseconds(min_time);
    metadata.bag_size     = GetBagfileSize();
    metadata.version_data = GetAllSysVersion();

    return metadata;
}

void SqliteStorage::SetFilter(const StorageFilter& storage_filter)
{
    storage_filter_ = storage_filter;
}

void SqliteStorage::ResetFilter()
{
    storage_filter_ = StorageFilter();
}

bool SqliteStorage::Filter(const std::string& input_holobag)
{
    std::string topic_list{""};
    for (auto& topic : storage_filter_.topics)
    {
        topic_list += "'" + topic + "'";
        if (&topic != &storage_filter_.topics.back())
        {
            topic_list += ",";
        }
    }
    database_->PrepareStatement("ATTACH DATABASE '" + input_holobag + "' AS SOURCE;")->ExecuteAndReset();
    if (storage_filter_.topics.empty())
    {
        database_->PrepareStatement("INSERT INTO topics SELECT * FROM SOURCE.topics;")->ExecuteAndReset();
    }
    else
    {
        database_
            ->PrepareStatement("INSERT INTO topics SELECT * FROM SOURCE.topics WHERE "
                               "topics.name IN (" +
                               topic_list + ") ORDER BY topics.id;")
            ->ExecuteAndReset();
    }
    if (storage_filter_.timestamps.size() != 2)
    {
        throw SqliteException("The filter timestamp must have begin timestamp & end timestamp");
    }

    holo::int64_t start_timestamp = storage_filter_.timestamps.at(0);
    holo::int64_t end_timestamp   = storage_filter_.timestamps.at(1);
    if (end_timestamp < 0)  // end_time < 0 means go to the end of the bag file
    {
        if (storage_filter_.topics.empty())
        {
            database_
                ->PrepareStatement("INSERT INTO messages SELECT * FROM SOURCE.messages WHERE "
                                   "SOURCE.messages.timestamp >= " +
                                   std::to_string(start_timestamp) + ";")
                ->ExecuteAndReset();
        }
        else
        {
            database_
                ->PrepareStatement("INSERT INTO messages SELECT SOURCE.messages.id,SOURCE.messages.topic_id,"
                                   "SOURCE.messages.timestamp,SOURCE.messages.data FROM SOURCE.messages "
                                   "JOIN SOURCE.topics ON SOURCE.messages.topic_id = SOURCE.topics.id "
                                   "WHERE SOURCE.topics.name IN (" +
                                   topic_list +
                                   ")"
                                   " AND SOURCE.messages.timestamp >= " +
                                   std::to_string(start_timestamp) +
                                   " ORDER BY SOURCE.messages.timestamp"
                                   ";")
                ->ExecuteAndReset();
        }
    }
    else
    {
        if (storage_filter_.topics.empty())
        {
            database_
                ->PrepareStatement(
                    "INSERT INTO messages SELECT * FROM SOURCE.messages WHERE SOURCE.messages.timestamp between " +
                    std::to_string(start_timestamp) + " AND " + std::to_string(end_timestamp) + ";")
                ->ExecuteAndReset();
        }
        else
        {
            database_
                ->PrepareStatement("INSERT INTO messages SELECT SOURCE.messages.id,SOURCE.messages.topic_id,"
                                   "SOURCE.messages.timestamp,SOURCE.messages.data FROM SOURCE.messages "
                                   "JOIN SOURCE.topics ON SOURCE.messages.topic_id = SOURCE.topics.id "
                                   "WHERE SOURCE.topics.name IN (" +
                                   topic_list +
                                   ")"
                                   " AND SOURCE.messages.timestamp between " +
                                   std::to_string(start_timestamp) + " AND " + std::to_string(end_timestamp) +
                                   " ORDER BY SOURCE.messages.timestamp"
                                   ";")
                ->ExecuteAndReset();
        }
    }

    if (end_timestamp < 0)  // end_time < 0 means go to the end of the bag file
    {
        database_
            ->PrepareStatement("INSERT INTO tags SELECT * FROM SOURCE.tags WHERE "
                                "SOURCE.tags.timestamp >= " +
                                std::to_string(start_timestamp) + ";")
            ->ExecuteAndReset();
    }
    else
    {
        database_
            ->PrepareStatement(
                "INSERT INTO tags SELECT * FROM SOURCE.tags WHERE SOURCE.tags.timestamp between " +
                std::to_string(start_timestamp) + " AND " + std::to_string(end_timestamp) + ";")
            ->ExecuteAndReset();
    }
    return true;
}

void SqliteStorage::WriteAllParams(const std::vector<std::shared_ptr<ParamMetadata>>& params)
{
    for (auto& param : params)
    {
        auto insert_param = database_->PrepareStatement("INSERT INTO params (path, name, file) "
                                                        "VALUES (?, ?, ?)");
        insert_param->Bind(param->path, param->name, param->file);
        insert_param->ExecuteAndReset();
    }
}

std::vector<ParamMetadata> SqliteStorage::GetAllParamsFile()
{
    std::vector<ParamMetadata> all_params;
    auto                       judge =
        database_->PrepareStatement("SELECT * FROM sqlite_master WHERE type = 'table' AND tbl_name = 'params'");
    auto res = judge->Step();
    if (!res)
    {
        return all_params;
    }
    auto statement     = database_->PrepareStatement("SELECT path, name, file FROM params ORDER BY id;");
    auto query_results = statement->ExecuteQuery<std::string, std::string, std::string>();

    for (auto result : query_results)
    {
        all_params.push_back({
            std::get<0>(result),
            std::get<1>(result),
            std::get<2>(result),
        });
    }
    return all_params;
}

void SqliteStorage::WriteVersion(const std::vector<std::shared_ptr<SysVersionMetadata>>& version)
{
    for (auto& ver : version)
    {
        auto insert_param =
            database_->PrepareStatement("INSERT INTO sys_version (category, type, version) VALUES (?, ?, ?)");
        insert_param->Bind(ver->category, ver->type, ver->version);
        insert_param->ExecuteAndReset();
    }
}

std::vector<SysVersionMetadata> SqliteStorage::GetAllSysVersion()
{
    std::vector<SysVersionMetadata> all_version;
    auto                            judge =
        database_->PrepareStatement("SELECT * FROM sqlite_master WHERE type = 'table' AND tbl_name = 'sys_version'");
    auto res = judge->Step();
    if (!res)
    {
        return all_version;
    }
    auto statement     = database_->PrepareStatement("SELECT category, type, version FROM sys_version ORDER BY id;");
    auto query_results = statement->ExecuteQuery<std::string, std::string, std::string>();

    for (auto result : query_results)
    {
        all_version.push_back({
            std::get<0>(result),
            std::get<1>(result),
            std::get<2>(result),
        });
    }
    return all_version;
}

void SqliteStorage::WriteTag(std::shared_ptr<const TagMessage> tag)
{
    if (!write_tag_statement_)
    {
        prepareForWriteTag();
    }
    std::lock_guard<std::mutex> lock(tag_mutex_);
    write_tag_statement_->Bind(tag->time_stamp, tag->tag);
    write_tag_statement_->ExecuteAndReset();
}
void SqliteStorage::WriteTags(const std::vector<std::shared_ptr<const TagMessage>>& tags)
{
    if (!write_tag_statement_)
    {
        prepareForWriting();
    }

    activateTransaction();

    for (auto& tag : tags)
    {
        WriteTag(tag);
    }

    commitTransaction();
}

void SqliteStorage::prepareForWriteTag()
{
    write_tag_statement_ =
        database_->PrepareStatement("INSERT INTO tags (timestamp, tag) VALUES (?, ?);");
}

void SqliteStorage::ClearTags()
{
    std::string clear_tags = "DROP TABLE if exists tags";
    database_->PrepareStatement(clear_tags)->ExecuteAndReset();
    std::string create_stmt =   "CREATE TABLE IF NOT EXISTS tags("
                                "id INTEGER PRIMARY KEY,"
                                "timestamp INTEGER NOT NULL, "
                                "tag TEXT NOT NULL);";
    database_->PrepareStatement(create_stmt)->ExecuteAndReset();
    create_stmt = "CREATE INDEX IF NOT EXISTS tag_timestamp_idx ON tags (timestamp ASC);";
    database_->PrepareStatement(create_stmt)->ExecuteAndReset();
}

}  // namespace bag
}  // namespace holo
