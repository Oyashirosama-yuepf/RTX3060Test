/**
 * @file sqlite_wrapper.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the sqlite wrapper
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_STORAGE_SQLITE_WRAPPER_HPP_
#define _HOLOBAG_STORAGE_SQLITE_WRAPPER_HPP_

#include <holo/bag/base/storage_interfaces/base_io_interface.h>
#include <holo/bag/storage/sqlite_statement_wrapper.h>
#include <sqlite3.h>

#include <string>

namespace holo
{
namespace bag
{
using DBPtr = sqlite3*;

class SqliteWrapper
{
public:
    SqliteWrapper(const std::string& uri, storage_interfaces::IOFlag io_flag);
    SqliteWrapper();
    ~SqliteWrapper();

    SqliteStatement PrepareStatement(const std::string& query);

    size_t GetLastInsertId();

    operator bool();

private:
    DBPtr db_ptr;
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_STORAGE_SQLITE_WRAPPER_HPP_
