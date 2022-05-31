/**
 * @file sequential_writer.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the sequential writer
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#ifndef _HOLOBAG_INTERFACE_SEQUENTIAL_WRITER_HPP_
#define _HOLOBAG_INTERFACE_SEQUENTIAL_WRITER_HPP_

#include <holo/bag/base/storage_interfaces/read_write_interface.h>
#include <holo/bag/interface/storage_options.h>
#include <holo/bag/storage/sqlite_storage.h>

#include <condition_variable>
#include <functional>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace holo
{
namespace bag
{
struct MutexCondition
{
    std::mutex              mt_;
    std::condition_variable cv_;
};
/**
 * The Writer allows writing messages to a new bag. For every topic, information about its type
 * needs to be added before writing the first message.
 */
class SequentialWriter
{
public:
    using SerializedMessagePtrVec = std::vector<std::shared_ptr<const SerializedBagMessage>>;
    explicit SequentialWriter();

    ~SequentialWriter();

    /**
     * @brief Opens a new bagfile and prepare it for writing messages. The bagfile must not exist.
     * This must be called before any other function is used.
     *
     * @param storage_options Options to configure the storage
     * @param converter_options options to define in which format incoming messages are stored
     **/
    void Open(const StorageOptions& storage_option);

    void Reset();

    bool HasNext();

    std::shared_ptr<SerializedBagMessage> ReadNext();

    const BagMetadata& GetMetadata() const;

    /**
     * @brief Create a new topic in the underlying storage. Needs to be called for every topic used within
     * a message which is passed to write(...).
     *
     * @param topic_with_type name and type identifier of topic to be created
     * @throw runtime_error if the Writer is not open.
     */
    void CreateTopic(const TopicMetadata& topic_with_type);

    /**
     * @brief Remove a new topic in the underlying storage.
     * If creation of subscription fails remove the topic
     * from the db (more of cleanup)
     *
     * @param topic_with_type name and type identifier of topic to be created
     * @throw runtime_error if the Writer is not open.
     */
    void RemoveTopic(const TopicMetadata& topic_with_type);

    /**
     * @brief Write a message to a bagfile. The topic needs to have been created before writing is possible.
     *
     * @param message to be written to the bagfile
     * @throw runtime_error if the Writer is not open.
     */
    void Write(std::shared_ptr<SerializedBagMessage> message);
    /**
     * @brief Write a message to a bagfile. The topic needs to have been created before writing is possible.
     *
     * @param message to be written to the bagfile
     * @throw runtime_error if the Writer is not open.
     */
    void Write(SerializedMessagePtrVec messages);

    void WriteAllParams(std::vector<std::shared_ptr<ParamMetadata>> params);

    void WriteVersion(std::vector<std::shared_ptr<SysVersionMetadata>> version);

    void WriteTag(std::shared_ptr<const TagMessage> tag);
    void ClearTags();

    std::pair<::holo::bool_t, ::holo::bool_t> ShouldSplit();

private:
    void cacheSwitch();
    void processCache();

private:
    std::string   base_folder_;
    uint64_t      max_bagfile_size_;
    uint64_t      max_bagfile_duration_;
    uint64_t      max_cache_size_;
    std::mutex    mutex_write_bag_;
    volatile bool running_;

    MutexCondition          mc_read_;
    MutexCondition          mc_write_;
    MutexCondition          mc_switch_;
    SerializedMessagePtrVec cache_read_;
    SerializedMessagePtrVec cache_write_;

    BagMetadata                                             metadata_{};
    std::unordered_map<std::string, TopicInformation> topics_names_to_info_;
    std::shared_ptr<storage_interfaces::ReadWriteInterface> storage_;
    std::shared_ptr<std::thread> switch_thread_;
    std::shared_ptr<std::thread> process_thread_;

    std::chrono::time_point<std::chrono::high_resolution_clock> start_timestamp_;
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_INTERFACE_SEQUENTIAL_WRITER_HPP_
