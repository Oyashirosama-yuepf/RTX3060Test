/**
 * @file sqlite_statement_wrapper.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief  this file is the implement of the sqlite statement wrapper
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#include <holo/bag/storage/sqlite_statement_wrapper.h>

#include <cstring>
#include <memory>
#include <sstream>
#include <string>

namespace holo
{
namespace bag
{
SqliteStatementWrapper::SqliteStatementWrapper(sqlite3* database, const std::string& query)
{
    sqlite3_stmt* statement;
    int           return_code = sqlite3_prepare_v2(database, query.c_str(), -1, &statement, nullptr);
    if (return_code != SQLITE_OK)
    {
        std::stringstream errmsg;
        errmsg << "Error when preparing SQL statement '" << query << "'. SQLite error: (" << return_code
               << "): " << sqlite3_errstr(return_code);

        throw SqliteException{errmsg.str()};
    }

    statement_                  = statement;
    last_bound_parameter_index_ = 0;
}

SqliteStatementWrapper::~SqliteStatementWrapper()
{
    if (statement_)
    {
        sqlite3_finalize(statement_);
    }
}

std::shared_ptr<SqliteStatementWrapper> SqliteStatementWrapper::ExecuteAndReset()
{
    int return_code = sqlite3_step(statement_);
    if (!isQueryOk(return_code))
    {
        std::stringstream errmsg;
        errmsg << "Error when processing SQL statement. SQLite error (" << return_code
               << "): " << sqlite3_errstr(return_code);

        throw SqliteException{errmsg.str()};
    }
    return Reset();
}

bool SqliteStatementWrapper::isQueryOk(int return_code)
{
    return return_code == SQLITE_OK || return_code == SQLITE_DONE || return_code == SQLITE_ROW;
}

std::shared_ptr<SqliteStatementWrapper> SqliteStatementWrapper::Bind(int value)
{
    auto return_code = sqlite3_bind_int(statement_, ++last_bound_parameter_index_, value);
    checkAndReportBindError(return_code, value);
    return shared_from_this();
}

std::shared_ptr<SqliteStatementWrapper> SqliteStatementWrapper::Bind(int64_t value)
{
    auto return_code = sqlite3_bind_int64(statement_, ++last_bound_parameter_index_, value);
    checkAndReportBindError(return_code, value);
    return shared_from_this();
}

std::shared_ptr<SqliteStatementWrapper> SqliteStatementWrapper::Bind(double value)
{
    auto return_code = sqlite3_bind_double(statement_, ++last_bound_parameter_index_, value);
    checkAndReportBindError(return_code, value);
    return shared_from_this();
}

std::shared_ptr<SqliteStatementWrapper> SqliteStatementWrapper::Bind(const std::string& value)
{
    auto return_code =
        sqlite3_bind_text(statement_, ++last_bound_parameter_index_, value.c_str(), -1, SQLITE_TRANSIENT);
    checkAndReportBindError(return_code, value);
    return shared_from_this();
}

std::shared_ptr<SqliteStatementWrapper>
SqliteStatementWrapper::Bind(const DataSequenceType& value)
{
    auto return_code = sqlite3_bind_blob(statement_, ++last_bound_parameter_index_, (const void*)(value.data()),
                                         static_cast<int>(value.size()), SQLITE_TRANSIENT);
    checkAndReportBindError(return_code);
    return shared_from_this();
}

std::shared_ptr<SqliteStatementWrapper> SqliteStatementWrapper::Reset()
{
    sqlite3_reset(statement_);
    sqlite3_clear_bindings(statement_);
    last_bound_parameter_index_ = 0;
    return shared_from_this();
}

bool SqliteStatementWrapper::Step()
{
    int return_code = sqlite3_step(statement_);
    if (return_code == SQLITE_ROW)
    {
        return true;
    }
    else if (return_code == SQLITE_DONE)
    {
        return false;
    }
    else
    {
        std::stringstream errmsg;
        errmsg << "Error reading SQL query. SQLite error (" << return_code << "): " << sqlite3_errstr(return_code);

        throw SqliteException{errmsg.str()};
    }
}

void SqliteStatementWrapper::obtainColumnValue(size_t index, int& value) const
{
    value = sqlite3_column_int(statement_, static_cast<int>(index));
}

void SqliteStatementWrapper::obtainColumnValue(size_t index, int64_t& value) const
{
    value = sqlite3_column_int64(statement_, static_cast<int>(index));
}

void SqliteStatementWrapper::obtainColumnValue(size_t index, double& value) const
{
    value = sqlite3_column_double(statement_, static_cast<int>(index));
}

void SqliteStatementWrapper::obtainColumnValue(size_t index, std::string& value) const
{
    value = reinterpret_cast<const char*>(sqlite3_column_text(statement_, static_cast<int>(index)));
}

void SqliteStatementWrapper::obtainColumnValue(size_t index, DataSequenceType& value) const
{
    auto data = sqlite3_column_blob(statement_, static_cast<int>(index));
    auto size = static_cast<size_t>(sqlite3_column_bytes(statement_, static_cast<int>(index)));
    value.resize(size);
    memcpy(static_cast<void*>(value.data()), data, size);
}

void SqliteStatementWrapper::checkAndReportBindError(int return_code)
{
    if (return_code != SQLITE_OK)
    {
        std::stringstream errmsg;
        errmsg << "Error when binding SQL parameter " << last_bound_parameter_index_ << ". SQLite error ("
               << return_code << "): " << sqlite3_errstr(return_code);

        throw SqliteException{errmsg.str()};
    }
}

}  // namespace bag
}  // namespace holo
