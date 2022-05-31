/**
 * @file sqlite_exception.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the sqlite exception
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_STORAGE_SQLITE_EXCEPTION_HPP_
#define _HOLOBAG_STORAGE_SQLITE_EXCEPTION_HPP_

#include <stdexcept>
#include <string>

namespace holo
{
namespace bag
{
class SqliteException : public std::runtime_error
{
public:
    explicit SqliteException(const std::string& message) : runtime_error(message)
    {
    }
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_STORAGE_SQLITE_EXCEPTION_HPP_
