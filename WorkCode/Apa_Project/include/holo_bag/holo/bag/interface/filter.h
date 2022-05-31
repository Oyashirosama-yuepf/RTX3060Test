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

#ifndef _HOLOBAG_INTERFACE_FILTER_HPP_
#define _HOLOBAG_INTERFACE_FILTER_HPP_

#include <holo/bag/base/storage_filter.h>
#include <holo/bag/base/storage_interfaces/read_write_interface.h>
#include <holo/bag/storage/sqlite_storage.h>

#include <memory>
#include <string>

namespace holo
{
namespace bag
{
/**
 * The Filter allows opening and reading messages of a bag.
 */
class Filter final
{
public:
    explicit Filter();

    ~Filter();

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
    void Open(const std::string& uri);

    /**
     * @brief Set filters to adhere to during reading.
     *
     * @param storage_filter Filter to apply to reading
     * @throw runtime_error if the Filter is not open.
     */
    void SetFilter(const StorageFilter& storage_filter);

    /**
     * @brief Reset all filters for reading.
     */
    void ResetFilter();

    /**
     * @brief call filter, original name is 'filter', use 'Filter' will produce Error
     */
    void UseFilter(const std::string& dest_uri);

private:
    std::shared_ptr<storage_interfaces::ReadWriteInterface> storage_{};
};
}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_INTERFACE_FILTER_HPP_
