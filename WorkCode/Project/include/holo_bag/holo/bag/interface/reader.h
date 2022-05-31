/**
 * @file reader.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the reader interface for the app
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_INTERFACE_READER_HPP_
#define _HOLOBAG_INTERFACE_READER_HPP_

#include <holo/bag/base/bag_metadata.h>
#include <holo/bag/base/serialized_bag_message.h>
#include <holo/bag/base/storage_filter.h>
#include <holo/bag/base/topic_metadata.h>
#include <holo/bag/interface/sequential_reader.h>
#include <holo/bag/interface/storage_options.h>

#include <memory>
#include <string>
#include <vector>

namespace holo
{
namespace bag
{
/**
 * The Reader allows opening and reading messages of a bag.
 */
class Reader final
{
public:
    explicit Reader();

    ~Reader();

    /**
     * @brief Throws if file could not be opened.
     * This must be called before any other function is used.
     * The rosbag is automatically closed on destruction.
     *
     * If the `output_serialization_format` within the `converter_options` is not the same as the
     * format of the underlying stored data, a converter will be used to automatically convert the
     * data to the specified output format.
     * Throws if the converter plugin does not exist.
     *
     * @param storage_options Options to configure the storage
     * @param converter_options Options for specifying the output data format
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
     * @brief Ask bagfile for all topics (including their type identifier) that were recorded.
     *
     * @return std::vector<TopicMetadata>, vector of topics with topic name and type as std::string
     * @throw runtime_error if the Reader is not open.
     */
    std::vector<TopicMetadata> GetAllTopicsAndTypes() const;

    /**
     * @brief Set filters to adhere to during reading.
     *
     * @param storage_filter Filter to apply to reading
     * @throw runtime_error if the Reader is not open.
     */
    void SetFilter(const StorageFilter& storage_filter);

    /**
     * @brief Reset all filters for reading.
     */
    void ResetFilter();

    std::vector<ParamMetadata> GetAllParamsFile() const;

    SequentialReader& GetImplementationHeadle() const
    {
        return *reader_impl_;
    }

private:
    std::unique_ptr<SequentialReader> reader_impl_;
};
}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_INTERFACE_READER_HPP_
