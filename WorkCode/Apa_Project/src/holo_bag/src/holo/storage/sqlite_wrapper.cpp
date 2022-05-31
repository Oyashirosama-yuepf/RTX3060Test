/**
 * @file sqlite_wrapper.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file is the implement of the sqlite wrapper
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#include <holo/log/hololog.h>
#include <holo/bag/storage/sqlite_wrapper.h>

#include <iostream>
#include <sstream>
#include <string>

namespace holo
{
namespace bag
{
SqliteWrapper::SqliteWrapper(const std::string& uri, storage_interfaces::IOFlag io_flag) : db_ptr(nullptr)
{
    if (io_flag == storage_interfaces::IOFlag::READ_ONLY)
    {
        int rc = sqlite3_open_v2(uri.c_str(), &db_ptr, SQLITE_OPEN_READONLY | SQLITE_OPEN_NOMUTEX, nullptr);
        if (rc != SQLITE_OK)
        {
            std::stringstream errmsg;
            errmsg << "Could not read-only open database. SQLite error (" << rc << "): " << sqlite3_errstr(rc);
            throw SqliteException{errmsg.str()};
        }
        // throws an exception if the database is not valid.
        PrepareStatement("PRAGMA schema_version;")->ExecuteAndReset();
    }
    else
    {
        int rc = sqlite3_open_v2(uri.c_str(), &db_ptr, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX,
                                 nullptr);
        if (rc != SQLITE_OK)
        {
            std::stringstream errmsg;
            errmsg << "Could not read-write open database. SQLite error (" << rc << "): " << sqlite3_errstr(rc);
            throw SqliteException{errmsg.str()};
        }
        PrepareStatement("PRAGMA journal_mode = PERSIST;")->ExecuteAndReset();
        PrepareStatement("PRAGMA synchronous = OFF;")->ExecuteAndReset();
    }

    sqlite3_extended_result_codes(db_ptr, 1);
}

SqliteWrapper::SqliteWrapper() : db_ptr(nullptr)
{
}

SqliteWrapper::~SqliteWrapper()
{
    const int rc = sqlite3_close(db_ptr);
    if (rc != SQLITE_OK)
    {
        LOG(ERROR) << "Could not close open database. Error code: " << rc << " Error message: " << sqlite3_errstr(rc);
    }
}

SqliteStatement SqliteWrapper::PrepareStatement(const std::string& query)
{
    if (db_ptr == nullptr)
    {
        throw SqliteException("db_ptr is nullptr, please open before use this API");
    }
    return std::make_shared<SqliteStatementWrapper>(db_ptr, query);
}

size_t SqliteWrapper::GetLastInsertId()
{
    return sqlite3_last_insert_rowid(db_ptr);
}

SqliteWrapper::operator bool()
{
    return db_ptr != nullptr;
}

}  // namespace bag
}  // namespace holo
