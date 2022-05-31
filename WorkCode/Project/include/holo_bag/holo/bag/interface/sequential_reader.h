/**
 * @file sequential_reader.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the sequential reader
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_INTERFACE_SEQUENTIAL_READER_HPP_
#define _HOLOBAG_INTERFACE_SEQUENTIAL_READER_HPP_

#include <holo/bag/base/storage_filter.h>
#include <holo/bag/base/storage_interfaces/read_only_interface.h>
#include <holo/bag/interface/sequential_reader.h>
#include <holo/bag/interface/storage_options.h>
#include <holo/bag/storage/sqlite_storage.h>

#include <memory>
#include <string>
#include <vector>

namespace holo
{
namespace bag
{
class SequentialReader
{
public:
    SequentialReader();

    ~SequentialReader();

    void Open(const StorageOptions& storage_options);

    void Reset();

    bool HasNext();

    std::shared_ptr<SerializedBagMessage> ReadNext();

    const BagMetadata& GetMetadata() const;

    std::vector<TopicMetadata> GetAllTopicsAndTypes() const;

    void SetFilter(const StorageFilter& storage_filter);

    void ResetFilter();

    std::vector<ParamMetadata> GetAllParamsFile() const;

    /**
     * @brief Ask whether there is another database file to read from the list of relative file paths.
     *
     * @return bool, true if there are still files to read in the list
     */
    virtual bool HasNextFile() const;

    /**
     * @return std::string, the relative file path pointed to by the current file iterator.
     */
    virtual std::string GetCurrentFile() const;

    /**
     * @return std::string, the URI of the current file (i.e. no extensions).
     */
    virtual std::string GetCurrentUri() const;

protected:
    /**
     * @brief Increment the current file iterator to point to the next file in the list of relative file
     * paths.
     *
     * Expected usage:
     * if (HasNextFile()) loadNextFile();
     */
    virtual void loadNextFile();

    /**
     * @brief Checks if all topics in the bagfile have the same RMW serialization format.
     * Currently a bag file can only be played if all topics have the same serialization format.
     *
     * @param topics Vector of TopicInformation with metadata.
     * @throw runtime_error if any topic has a different serialization format from the rest.
     */
    virtual void checkTopicsSerializationFormats(const std::vector<TopicInformation>& topics);

private:
    std::shared_ptr<storage_interfaces::ReadOnlyInterface> storage_{};
    BagMetadata                                            metadata_{};
    std::vector<TopicMetadata>                             topics_metadata_{};
    std::vector<ParamMetadata>                             params_metadata_{};
    std::vector<std::string>                               file_paths_{};             // List of database files.
    std::vector<std::string>::iterator                     current_file_iterator_{};  // Index of file to read from
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_INTERFACE_SEQUENTIAL_READER_HPP_
