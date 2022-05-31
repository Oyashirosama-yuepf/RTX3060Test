/**
 * @file writer.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the writer interface for app
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_INTERFACE_WRITER_HPP_
#define _HOLOBAG_INTERFACE_WRITER_HPP_

#include <holo/bag/base/serialized_bag_message.h>
#include <holo/bag/base/topic_metadata.h>
#include <holo/bag/interface/sequential_writer.h>
#include <holo/bag/interface/storage_options.h>

#include <memory>
#include <vector>

namespace holo
{
namespace bag
{
/**
 * The Writer allows writing messages to a new bag. For every topic, information about its type
 * needs to be added before writing the first message.
 */
class Writer final
{
public:
    explicit Writer();

    ~Writer();

    /**
     * @brief Opens a new bagfile and prepare it for writing messages. The bagfile must not exist.
     * This must be called before any other function is used.
     *
     * @param storage_options Options to configure the storage
     * @param converter_options options to define in which format incoming messages are stored
     */
    void Open(const StorageOptions& storage_options);
    /**
     * @brief Ask whether the underlying bagfile contains at least one more message.
     *
     * @return bool, true if storage contains at least one more message
     * @throw runtime_error if the Reader is not open.
     */
    bool HasNext();

    /**
     * Read next message from storage. Will throw if no more messages are available.
     * The message will be serialized in the format given to `open`.
     *
     * Expected usage:
     * if (writer.HasNext()) message = writer.ReadNext();
     *
     * @return std::shared_ptr<SerializedBagMessage>, next message in serialized form
     * @throw runtime_error if the Reader is not open.
     */
    std::shared_ptr<SerializedBagMessage> ReadNext();

    /**
     * @brief Ask bagfile for its full metadata.
     *
     * @return BagMetadata, a const reference to a BagMetadata owned by the Reader
     * @throw runtime_error if the Reader is not open.
     */
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

    void Write(std::vector<std::shared_ptr<const SerializedBagMessage>> messages);

    void WriteAllParams(const std::vector<std::shared_ptr<ParamMetadata>>& params);

    void WriteVersion(const std::vector<std::shared_ptr<SysVersionMetadata>>& version);

    void WriteTag(std::shared_ptr<const TagMessage> tag);

    void ClearTags();

    SequentialWriter& GetImplementationHeadle() const
    {
        return *writer_impl_;
    }

    std::pair<::holo::bool_t, ::holo::bool_t> ShouldSplitBagFile();

private:
    std::unique_ptr<SequentialWriter> writer_impl_;
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_INTERFACE_WRITER_HPP_
