/**
 * @file base_info_interface.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the base info interface about the storage
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_BASE_STORAGE_INTERFACE_BASE_INFO_INTERFACE_HPP_
#define _HOLOBAG_BASE_STORAGE_INTERFACE_BASE_INFO_INTERFACE_HPP_

#include <holo/bag/base/bag_metadata.h>

#include <string>

namespace holo
{
namespace bag
{
namespace storage_interfaces
{
class BaseInfoInterface
{
public:
    virtual ~BaseInfoInterface() = default;

    virtual BagMetadata GetMetadata() = 0;

    /**
     * @brief Retrieves the relative path to the backing of the storage plugin.
     *
     * @return string, the relative path.
     */
    virtual std::string GetRelativeFilePath() const = 0;

    /**
     * @brief Returns the size of the bagfile.
     * 
     * @return uint64_t, the size of the bagfile in bytes.
     */
    virtual uint64_t GetBagfileSize() const = 0;

    /**
     * @brief Returns the identifier for the storage plugin.
     * 
     * @return string, the identifier.
     */
    virtual std::string GetStorageIdentifier() const = 0;
};

}  // namespace storage_interfaces
}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_STORAGE_INTERFACE_BASE_INFO_INTERFACE_HPP_
