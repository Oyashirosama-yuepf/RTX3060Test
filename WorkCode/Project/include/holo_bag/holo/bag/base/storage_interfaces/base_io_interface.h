/**
 * @file base_io_interface.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the base io interface about the sotrage
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_BASE_STORAGE_INTERFACES_BASE_IO_INTERFACE_HPP_
#define _HOLOBAG_BASE_STORAGE_INTERFACES_BASE_IO_INTERFACE_HPP_

#include <string>

namespace holo
{
namespace bag
{
namespace storage_interfaces
{
enum class IOFlag : uint8_t
{
    READ_ONLY  = 0,
    READ_WRITE = 1,
    APPEND     = 2
};

/// When bagfile splitting feature is not enabled or applicable,
/// use 0 as the default maximum bagfile size value.
extern uint64_t const MAX_BAGFILE_SIZE_NO_SPLIT;
extern uint64_t const MAX_BAGFILE_DURATION_NO_SPLIT;

class BaseIOInterface
{
public:
    virtual ~BaseIOInterface() = default;

    /**
     * @brief Opens the storage plugin.
     *
     * @details If IOFlag::READ_ONLY is passed, then only read operations are guaranteed.
     *          The uri passed should be the exact relative path to the bagfile.
     *          If IOFlag::READ_WRITE is passed, then a new bagfile is created with guaranteed read and write
     * operations. 
     *          The storage plugin will append the uri in the case of creating a new bagfile backing.
     * @param uri is the path to the bagfile. Exact behavior depends on the io_flag passed.
     * @param io_flag is a hint for the type of storage plugin to open depending on the io operations requested.
     */
    virtual void Open(const std::string& uri, IOFlag io_flag) = 0;
};

}  // namespace storage_interfaces
}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_STORAGE_INTERFACES_BASE_IO_INTERFACE_HPP_
