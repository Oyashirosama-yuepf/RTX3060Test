/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file db_engine.h
 * @brief This header file defines database engine that with addition, deletion, modification and query operations.
 * @author lisong@holomatic.com
 * @date 2020-05-29
 */

#ifndef HOLO_MAP_DATABASE_DB_ENGINE_H_
#define HOLO_MAP_DATABASE_DB_ENGINE_H_

#include <functional>
#include <iomanip>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <holo/log/hololog.h>
#include <sqlite3.h>

#include <holo/core/types.h>
#include <holo/map/common_def.h>

#include <holo/map/geofence/geofence_common.h>

#define DEBUG_MAP_DATABASE_ENGINE 0

namespace holo
{
/**
 * @addtogroup holo
 *
 * @{
 */
namespace map
{
/**
 * @addtogroup map
 *
 * @{
 */

/**
 * @brief this class defines a wrapper of sqlite3.
 *
 */
class DBEngine
{
public:
    using PreparedSqlStmtSPtrType  = std::shared_ptr<sqlite3_stmt>;
    using PreparedSqlStmtCSPtrType = std::shared_ptr<sqlite3_stmt const>;

    /**
     * @brief Constructor
     */
    DBEngine() = default;

    /**
     * @brief Destructor
     */
    virtual ~DBEngine() = default;

    /// DBEngine object can not be copied and moved.
    DBEngine(DBEngine const& other) = delete;
    DBEngine& operator=(DBEngine const& other) = delete;

    DBEngine(DBEngine&& other) = delete;
    DBEngine& operator=(DBEngine&& other) = delete;

    /**
     * @brief Open a new DB, suit for file DB
     *
     * @param[in] db_path DB file path
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Open(std::string const& db_path);

    /**
     * @brief Close DB
     */
    void Close()
    {
        if (sqlitedb_ptr_ == nullptr)
        {
            LOG(ERROR) << "DBEngine::Close, derlying sqlite db pointer is null.";
            return;
        }
        sqlitedb_ptr_.reset();
    }

    /**
     * @brief Execute sql
     * @note Every sql statement must end with ";"
     *
     * @param[in] sql_str Sql str
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t ExecSql(std::string const& sql_str)
    {
        if (sql_str.empty())
        {
            LOG(ERROR) << "DBEngine::ExecSql, empty sql statement.";
            return false;
        }
        if (sql_str.back() != ';')
        {
            LOG(ERROR) << "DBEngine::ExecSql, Every sql statement must end with ';', sql str is " << sql_str;
            return false;
        }
        holo::int32_t toal_changes_count = -1;
        return execSqlNoResult(sql_str, toal_changes_count) && 0 <= toal_changes_count;
    }

    /**
     * @brief Start a transaction

     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t BeginTransaction()
    {
        if (sqlitedb_ptr_ == nullptr)
        {
            LOG(ERROR) << "DBEngine::BeginTransaction, derlying sqlite db pointer is null.";
            return false;
        }
        if (sqlite3_get_autocommit(sqlitedb_ptr_.get()) == 0)
        {
#if DEBUG_MAP_DATABASE_ENGINE
            LOG(INFO) << "DBEngine::BeginTransaction, db is already in a transaction.";
#endif
            return true;
        }
        return ExecSql("BEGIN TRANSACTION;");
    }

    /**
     * @brief Rollback a transaction

     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t RollbackTransection()
    {
        if (sqlitedb_ptr_ == nullptr)
        {
            LOG(ERROR) << "DBEngine::RollbackTransection, derlying sqlite db pointer is null.";
            return false;
        }
        if (sqlite3_get_autocommit(sqlitedb_ptr_.get()) != 0)
        {
#if DEBUG_MAP_DATABASE_ENGINE
            LOG(INFO) << "DBEngine::RollbackTransection, no transaction is actived before";
#endif
            return true;
        }
        return ExecSql("ROLLBACK;");
    }

    /**
     * @brief Commit a transaction

     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t CommitTransection()
    {
        if (sqlitedb_ptr_ == nullptr)
        {
            LOG(ERROR) << "DBEngine::CommitTransection, derlying sqlite db pointer is null.";
            return false;
        }
        if (sqlite3_get_autocommit(sqlitedb_ptr_.get()) != 0)
        {
#if DEBUG_MAP_DATABASE_ENGINE
            LOG(INFO) << "DBEngine::RollbackTransection, no transaction is actived before";
#endif
            return true;
        }
        return ExecSql("COMMIT TRANSACTION;");
    }

    /**
     * @brief Return last error msg of db running.
     *
     * @return Last error msg of db running.
     */
    std::string LastErrorMsg() const
    {
        if (sqlitedb_ptr_ == nullptr)
        {
            return "DBEngine::LastErrorMsg failed, derlying sqlite db pointer is null.";
        }
        return std::string(sqlite3_errmsg(sqlitedb_ptr_.get()));
    }

    /**
     * @brief Get massage string by sqlite3 result code
     * @details Result code, see: https://www.sqlite.org/rescode.html
     * @param[in] result_code Given result_code
     * @return Massage string
     */
    static std::string GetResultMsgStr(holo::int32_t const result_code)
    {
        return std::string(sqlite3_errstr(result_code));
    }

    /**
     * @brief Get value of column that type is string or blob from executed prepared sql stmt.
     *
     * @param[in] sql_stmt_ptr Executed prepared sql stmt
     * @param[in] col_idx Column index
     * @param[out] str Result column value.
     * @return True if successful,
     *         False if failed, str will be ""
     */
    static holo::bool_t GetColumnVal(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t const col_idx, std::string& str);

    /**
     * @brief Get column value from executed prepared sql stmt.
     * @details Only support floating point type column value.
     *
     * @tparam T Type of column result value, it may different from type of value of target column from database
     * @param[in] sql_stmt_ptr Executed prepared sql stmt
     * @param[in] col_idx Column index
     * @param[out] obj Result column value.
     * @return True if successful,
     *         False if failed.
     */
    template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
    static holo::bool_t GetColumnVal(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t const col_idx, T& obj)
    {
        obj = T{};
        if (sql_stmt_ptr == nullptr)
        {
            LOG(ERROR) << "DBEngine::GetColumnVal failed, prepared sql stmt pointer is null.";
            return false;
        }
        if (!isColumnIdxValid(sql_stmt_ptr, col_idx))
        {
            LOG(ERROR) << "DBEngine::GetColumnVal failed, invalid column index = " << col_idx;
            return false;
        }
        obj = static_cast<T>(sqlite3_column_double(sql_stmt_ptr.get(), col_idx));
        return true;
    }

    /**
     * @brief Get column value from executed prepared sql stmt.
     * @details Only support type that is not floating point
     *
     * @tparam T Type of column result value, it may different from type of value of target column from database
     * @param[in] sql_stmt_ptr Executed prepared sql stmt
     * @param[in] col_idx Column index
     * @tparam[out] obj Result column value.
     * @return True if successful,
     *         False if failed.
     */
    template<typename T, typename std::enable_if<!std::is_floating_point<T>::value>::type* = nullptr>
    static holo::bool_t GetColumnVal(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t const col_idx, T& obj)
    {
        obj = T{};
        if (sql_stmt_ptr == nullptr)
        {
            LOG(ERROR) << "DBEngine::GetColumnVal failed, prepared sql stmt pointer is null.";
            return false;
        }
        if (!isColumnIdxValid(sql_stmt_ptr, col_idx))
        {
            LOG(ERROR) << "DBEngine::GetColumnVal failed, invalid column index = " << col_idx;
            return false;
        }
        obj = static_cast<T>(sqlite3_column_int64(sql_stmt_ptr.get(), col_idx));
        return true;
    }

    /**
     * @brief Set string value to column for prepared sql stmt.
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[in] param_idx Param index
     * @param[in] str String value for target column.
     * @return True if successful,
     *         False if failed.
     */
    static holo::bool_t SetColumnVal(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t const param_idx, std::string const& str);

    /**
     * @brief Set blob value to column for prepared sql stmt.
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[in] param_idx Param index
     * @param[in] blob Blob value for target column.
     * @param[in] blob_size Size of blob value for target column
     * @return True if successful,
     *         False if failed.
     */
    static holo::bool_t SetColumnVal(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t const param_idx,
                                     void const* const blob, holo::int32_t const blob_size);

    /**
     * @brief Set column value for prepared sql stmt.
     * @details Only support type that is not floating point
     *
     * @tparam T Type of value that is used to set target column
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[in] param_idx Param index
     * @param[in] val Value for target column.
     * @return True if successful,
     *         False if failed.
     */
    template<typename T, typename std::enable_if<!std::is_floating_point<T>::value>::type* = nullptr>
    static holo::bool_t SetColumnVal(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t const param_idx, T const& val)
    {
        if (sql_stmt_ptr == nullptr)
        {
            LOG(ERROR) << "DBEngine::SetColumnVal failed, prepared sql stmt pointer is null.";
            return false;
        }
        if (!isParamIdxValid(sql_stmt_ptr, param_idx))
        {
            LOG(ERROR) << "DBEngine::SetColumnVal failed, invalid param index = " << param_idx;
            return false;
        }
        holo::int64_t const col_val = static_cast<holo::int64_t>(val);
        holo::int32_t const error_code = sqlite3_bind_int64(sql_stmt_ptr.get(), param_idx, col_val);
        if (error_code != SQLITE_OK)
        {   
            LOG(ERROR) << "DBEngine::SetColumnVal failed, index = " << param_idx << ", parameter value(in int64_t form) = " << static_cast<int64_t>(val) 
                       << ", parameter value(in uint64_t form) = " << static_cast<uint64_t>(val) 
                       << ", error code is "<< error_code << ", error is " << GetResultMsgStr(error_code)
                       << ", orignal sql is " << std::string(sqlite3_sql(sql_stmt_ptr.get()));
            return false;
        }
        return true;
    }

    /**
     * @brief Set column value for prepared sql stmt.
     * @details Only support type of floating point
     *
     * @tparam T Type of value that is used to set target column
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[in] param_idx Param index
     * @param[in] val Value for target column.
     * @return True if successful,
     *         False if failed.
     */
    template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
    static holo::bool_t SetColumnVal(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t const param_idx, T const& val)
    {
        if (sql_stmt_ptr == nullptr)
        {
            LOG(ERROR) << "DBEngine::SetColumnVal failed, prepared sql stmt pointer is null.";
            return false;
        }
        if (!isParamIdxValid(sql_stmt_ptr, param_idx))
        {
            LOG(ERROR) << "DBEngine::SetColumnVal failed, invalid param index = " << param_idx;
            return false;
        }
        holo::float64_t const col_val = static_cast<holo::float64_t>(val);
        holo::int32_t const error_code = sqlite3_bind_double(sql_stmt_ptr.get(), param_idx, col_val);
        if (error_code != SQLITE_OK)
        {
            std::ostringstream oss;
            oss << std::setprecision(16) << val;
            LOG(ERROR) << "DBEngine::SetColumnVal failed, index = " << param_idx << ", parameter value = " << oss.str()
                       << ", error code is "<< error_code << ", error is " << GetResultMsgStr(error_code)
                       << ", sql is " << std::string(sqlite3_sql(sql_stmt_ptr.get()));
            return false;
        }
        return true;
    }

    /**
     * @brief Prepare given value to prepared sql stmt.
     *
     * @param[in] sql_str Sql str
     * @param[out] prepared_sql_stmt_ptr Result prepared sql stmt.
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t PrepareSqlStmt(std::string const& sql_str, PreparedSqlStmtSPtrType& prepared_sql_stmt_ptr) const;

    /**
     * @brief Bind given param values to prepared sql stmt.
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @tparam[in] param_vals param values.
     * @return True if successful,
     *         False if failed.
     */
    template <typename... Args>
    static holo::bool_t BindPreparedSqlStmt(PreparedSqlStmtSPtrType const sql_stmt_ptr, Args const&... param_vals)
    {
        if (sql_stmt_ptr == nullptr)
        {
            LOG(ERROR) << "DBEngine::BindPreparedSqlStmt failed, prepared sql stmt pointer is null.";
            return false;
        }
        /// Need clear all bindings from that prepared sql stmt
        if (!ClearBindings(sql_stmt_ptr))
        {
            LOG(ERROR) << "DBEngine::BindPreparedSqlStmt failed, can not clear sql stmt bindings.";
            return false;
        }
        holo::uint32_t const params_count = static_cast<holo::uint32_t>(sqlite3_bind_parameter_count(sql_stmt_ptr.get()));
        std::size_t const args_count = sizeof...(param_vals);
        if (args_count != params_count)/// Not match
        {
            LOG(ERROR) << "DBEngine::BindPreparedSqlStmt failed, args number is not equal to params number, params_count = "
                       << params_count << ", args_count = " << args_count;
            return false;
        }
        holo::int32_t const first_param_idx = 1;
        return bindPreparedSqlStmt(sql_stmt_ptr, first_param_idx, param_vals...);
    }

    /**
     * @brief Clear bindings for prepared sql stmt.
     * @details After this operation, values bound to given prepared sql stmt are cleared.
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @return True if successful,
     *         False if failed.
     */
    static holo::bool_t ClearBindings(PreparedSqlStmtSPtrType const sql_stmt_ptr);

    /**
     * @brief Reset prepared sql stmt.
     * @details After this operation, given prepared sql stmt can be executed again.
     * @note Values bound to given prepared sql stmt will not be cleared, this function is different from ClearBindings
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @return True if successful,
     *         False if failed.
     */
    static holo::bool_t ResetPreparedSqlStmt(PreparedSqlStmtSPtrType const sql_stmt_ptr);

    /**
     * @brief Insert record(s) to DB.
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[out] toal_changes_count How many records affected by this operation
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Insert(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t& toal_changes_count) const
    {
        return execSqlNoResult(sql_stmt_ptr, toal_changes_count);
    }

    /**
     * @brief Insert record(s) to DB.
     *
     * @param[in] sql_str Sql str
     * @param[out] toal_changes_count How many records affected by this operation
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Insert(std::string const& sql_str, holo::int32_t& toal_changes_count) const
    {
        if (sql_str.empty())
        {
            LOG(ERROR) << "DBEngine::Insert, empty sql statement.";
            return false;
        }
        if (sql_str.back() != ';')
        {
            LOG(ERROR) << "DBEngine::Insert, Every sql statement must end with ';', sql str is " << sql_str;
            return false;
        }
        return execSqlNoResult(sql_str, toal_changes_count);
    }

    /**
     * @brief Read a record(s) from DB
     * @details Generally, we need something to store results query from DB
     *          results from DB are data of multiple rows, those rows share the same model like:
     *                            [col1, col2, col3...]
     *          each column has its own value and data type.
     *          We can image row model as class in C++, columns as fields of that class, results from DB as objects of that class
     *          So there are a relationship between columns(of row) and fields(of class); in order to store results from DB,
     *          user need provide class and method to describe relationship between its fields and columns
     *          Class here is T, method here is CallBackFuncType, results from DB here is std::vector<T> in this function.
     *
     * @tparam T Type of object used to store row data from DB
     * @tparam CallBackFuncType Method used to set values of fields from object of T by using row data from DB.
     *         Form is:
     *                std::function<holo::bool_t(PreparedSqlStmtSPtrType const, holo::int32_t const, T&)
     *             -- first parameter is executed prepared sql stmt from this Query function, which stores all results read from DB.
     *             -- second parameter is column index used to get column value from first parameter, then use this value to fill third parameter's
     *                (aka a reference to a object of T) field corresponding to column.
     *             -- third parameter is reference of result object of T
     *             -- If successful return true, otherwise return false
     *
     * @param[in] sql_str Sql str
     * @param[in] populate_field_for_T Object of CallBackFuncType
     * @param[out] result Result vector, each element corresponding to one data of row from query result.
     * @return True if successful,
     *         False if failed.
     */
    template <typename T, typename CallBackFuncType = std::function<holo::bool_t(PreparedSqlStmtSPtrType const, holo::int32_t const, T&)>>
    holo::bool_t Query(std::string const& sql_str,
                       CallBackFuncType const& populate_field_for_T,
                       std::vector<T>& result) const
    {
        if (sql_str.empty())
        {
            LOG(ERROR) << "DBEngine::Query, empty sql statement.";
            return false;
        }
        if (sql_str.back() != ';')
        {
            LOG(ERROR) << "DBEngine::Query, Every sql statement must end with ';', sql str is " << sql_str;
            return false;
        }
        return execSqlWithResult(sql_str, populate_field_for_T, result);
    }

    /**
     * @brief Read a record(s) from DB
     * @details Generally, we need something to store results query from DB
     *          results from DB are data of multiple rows, those rows share the same model like:
     *                            [col1, col2, col3...]
     *          each column has its own value and data type.
     *          We can image row model as class in C++, columns as fields of that class, results from DB as objects of that class
     *          So there are a relationship between columns(of row) and fields(of class); in order to store results from DB,
     *          user need provide class and method to describe relationship between its fields and columns
     *          Class here is T, method here is CallBackFuncType, results from DB here is std::vector<T> in this function.
     *
     * @tparam T Type of object used to store row data from DB
     * @tparam CallBackFuncType Method used to set values of fields from object of T by using row data from DB.
     *         Form is:
     *                std::function<holo::bool_t(PreparedSqlStmtSPtrType const, holo::int32_t const, T&)
     *             -- first parameter is executed prepared sql stmt from this Query function, which stores all results read from DB.
     *             -- second parameter is column index used to get column value from first parameter, then use this value to fill third parameter's
     *                (aka a reference to a object of T) field corresponding to column.
     *             -- third parameter is reference of result object of T
     *             -- If successful return true, otherwise return false
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[in] populate_field_for_T Object of CallBackFuncType
     * @param[out] result Result vector, each element corresponding to one data of row from query result.
     * @return True if successful,
     *         False if failed.
     */
    template <typename T, typename CallBackFuncType = std::function<holo::bool_t(PreparedSqlStmtSPtrType const, holo::int32_t const, T&)>>
    holo::bool_t Query(PreparedSqlStmtSPtrType const sql_stmt_ptr,
                       CallBackFuncType const& populate_field_for_T,
                       std::vector<T>& result) const
    {
        return execSqlWithResult(sql_stmt_ptr, populate_field_for_T, result);
    }

    /**
     * @brief Read a record(s) from DB
     * @details Generally, we need something to store results query from DB
     *          results from DB are data of multiple rows, those rows share the same model like:
     *                            [col1, col2, col3...]
     *          each column has its own value and data type.
     *          We can image row model as class in C++, columns as fields of that class, results from DB as objects of that class
     *          So there are a relationship between columns(of row) and fields(of class); in order to store results from DB,
     *          user need provide class and method to describe relationship between its fields and columns
     *          Class here is T, method here is CallBackFuncType, results from DB here is std::vector<T> in this function.
     *
     * @tparam T Type of object used to store row data from DB
     * @tparam CallBackFuncType Method used to set values of fields from object of T by using row data from DB.
     *         Form is:
     *                std::function<holo::bool_t(PreparedSqlStmtSPtrType const, holo::int32_t const, T&)
     *             -- first parameter is executed prepared sql stmt from this Query function, which stores all results read from DB.
     *             -- second parameter is column index used to get column value from first parameter, then use this value to fill third parameter's
     *                (aka a reference to a object of T) field corresponding to column.
     *             -- third parameter is reference of result object of T
     *             -- If successful return true, otherwise return false
     *
     * @param[in] id ID used to query record
     * @param[in] table_name Table name, where result records come from.
     * @param[in] populate_field_for_T Object of CallBackFuncType
     * @param[out] result Result vector, each element corresponding to one data of row from query result.
     * @return True if successful,
     *         False if failed.
     */
    template <typename T, typename CallBackFuncType = std::function<holo::bool_t(PreparedSqlStmtSPtrType const, holo::int32_t const, T&)>>
    holo::bool_t Query(holo::uint64_t const& id, std::string const& table_name,
                       CallBackFuncType const& populate_field_for_T,
                       std::vector<T>& result) const
    {
        std::string sql_str = "SELECT * FROM " + table_name + " WHERE id = " + std::to_string(id) + ";";
        return execSqlWithResult(sql_str, populate_field_for_T, result);
    }

    /**
     * @brief Update record(s) from db
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[out] toal_changes_count How many records affected by this operation
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Update(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t& toal_changes_count) const
    {
        return execSqlNoResult(sql_stmt_ptr, toal_changes_count);
    }

    /**
     * @brief Update record(s) from db
     *
     * @param[in] sql_str Sql str
     * @param[out] toal_changes_count How many records affected by this operation
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Update(std::string const& sql_str, holo::int32_t& toal_changes_count) const
    {
        if (sql_str.empty())
        {
            LOG(ERROR) << "DBEngine::Update, empty sql statement.";
            return false;
        }
        if (sql_str.back() != ';')
        {
            LOG(ERROR) << "DBEngine::Update, Every sql statement must end with ';', sql str is " << sql_str;
            return false;
        }
        return execSqlNoResult(sql_str, toal_changes_count);
    }

    /**
     * @brief Delete record(s) from db
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[out] toal_changes_count How many records affected by this operation
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Delete(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t& toal_changes_count) const
    {
        return execSqlNoResult(sql_stmt_ptr, toal_changes_count);
    }

    /**
     * @brief Delete record(s) from db
     *
     * @param[in] sql_str Sql str
     * @param[out] toal_changes_count How many records affected by this operation
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Delete(std::string const& sql_str, holo::int32_t& toal_changes_count) const
    {
        if (sql_str.empty())
        {
            LOG(ERROR) << "DBEngine::Delete, empty sql statement.";
            return false;
        }
        if (sql_str.back() != ';')
        {
            LOG(ERROR) << "DBEngine::Delete, Every sql statement must end with ';', sql str is " << sql_str;
            return false;
        }
        return execSqlNoResult(sql_str, toal_changes_count);
    }

    /**
     * @brief Delete record from db
     *
     * @param[in] id ID used to delete record from DB.
     * @param[in] table_name Table name where record come from
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t Delete(holo::uint64_t const id, std::string const& table_name) const
    {
        std::string sql_str = "DELETE FROM " + table_name + " WHERE id = " + std::to_string(id) + ";";
        holo::int32_t result_count = -1;
        return execSqlNoResult(sql_str, result_count) && 0 <= result_count;
    }

    /**
     * @brief Get deleter of prepared sql stmt.
     * @details Since we use shared_ptr to manage prepared sql stmt, we need provide deleter to release resource.
     * @note All prepared sql stmts should use this function to get deleter to release resource.
     *
     * @return Deleter
     */
    static std::function<void(sqlite3_stmt*)> GetPreparedSqlStmtDeleter();

private:
    using SqliteDBUPtrType  = std::unique_ptr<sqlite3, std::function<void(sqlite3*)>>;
    using SqliteDBCUPtrType = std::unique_ptr<sqlite3 const, std::function<void(sqlite3*)>>;

    /**
     * @brief Get deleter of sqlite db.
     * @details Since we use shared_ptr to manage sqlite db, we need provide deleter to release resource.
     * @note All sqlite db should use this function to get deleter to release resource.
     *
     * @return Deleter
     */
    static std::function<void(sqlite3*)> getSqliteDBDeleter();

    /**
     * @brief Check if given column index valid from given executed prepared sql stmt.
     *
     * @param[in] sql_stmt_ptr Executed prepared sql stmt
     * @param[in] col_idx Column index
     * @return True if valid, false if invalid.
     */
    static holo::bool_t isColumnIdxValid(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t const col_idx);

    /**
     * @brief Check if given param index valid from given prepared sql stmt.
     *
     * @param[in] sql_stmt_ptr prepared sql stmt
     * @param[in] param_idx Param index
     * @return True if valid, false if invalid.
     */
    static holo::bool_t isParamIdxValid(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t const param_idx);

    /**
     * @brief Bind values to prepared sql stmt.
     * @details This is Base function for bindPreparedSqlStmt template function.
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[in] param_idx Index of parameter from given prepared sql stmt.
     * @return True if successful,
     *         False if failed.
     */
    static holo::bool_t bindPreparedSqlStmt(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t const param_idx)
    {
        (void)sql_stmt_ptr;
        (void)param_idx;
#if DEBUG_MAP_DATABASE_ENGINE
        LOG(INFO) << "DBEngine::bindPreparedSqlStmt finshed! sql str is " << std::string(sqlite3_sql(sql_stmt_ptr.get()));
#endif // DEBUG_MAP_DATABASE_ENGINE
        return true;
    }

    /**
     * @brief Bind values to prepared sql stmt.
     *
     * @tparam T Type of first paramter value from template parameter pacage Args
     * @tparam Args Template parameter pacage
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[in] param_idx Index of parameter from given prepared sql stmt.
     * @param[in] first_param_val Value of first parameter for prepared sql stmt
     * @param[in] rest_param_vals Values of rest parameters for prepared sql stmt
     * @return True if successful,
     *         False if failed.
     */
    template <typename T, typename... Args>
    static holo::bool_t bindPreparedSqlStmt(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t const param_idx,
                                            T const& first_param_val, Args const&... rest_param_vals)
    {
        if (sql_stmt_ptr == nullptr)
        {
            LOG(ERROR) << "DBEngine::bindPreparedSqlStmt failed, prepared sql stmt pointer is null.";
            return false;
        }
        if (!SetColumnVal(sql_stmt_ptr, param_idx, first_param_val))
        {
            LOG(ERROR) << "DBEngine::bindPreparedSqlStmt failed, can not set param val.";
            return false;
        }
        return bindPreparedSqlStmt(sql_stmt_ptr, param_idx + 1, rest_param_vals...);
    }

    /**
     * @brief Execute prepared sql stmt on DB with no result returns.
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[out] toal_changes_count How many records affected by this operation
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t execSqlNoResult(PreparedSqlStmtSPtrType const sql_stmt_ptr, holo::int32_t& toal_changes_count) const;

    /**
     * @brief Execute sql on DB with no result returns
     *
     * @param[in] sql_str Sql str
     * @param[out] toal_changes_count How many records affected by this operation
     * @return True if successful,
     *         False if failed.
     */
    holo::bool_t execSqlNoResult(std::string const& sql_str, holo::int32_t& toal_changes_count) const;

    /**
     * @brief Execute sql on DB with results returns.
     * @details Generally, we need something to store results query from DB
     *          results from DB are data of multiple rows, those rows share the same model like:
     *                            [col1, col2, col3...]
     *          each column has its own value and data type.
     *          We can image row model as class in C++, columns as fields of that class, results from DB as objects of that class
     *          So there are a relationship between columns(of row) and fields(of class); in order to store results from DB,
     *          user need provide class and method to describe relationship between its fields and columns
     *          Class here is T, method here is CallBackFuncType, results from DB here is std::vector<T> in this function.
     *
     * @tparam T Type of object used to store row data from DB
     * @tparam CallBackFuncType Method used to set values of fields from object of T by using row data from DB.
     *         Form is:
     *                std::function<holo::bool_t(PreparedSqlStmtSPtrType const, holo::int32_t const, T&)
     *             -- first parameter is executed prepared sql stmt from this Query function, which stores all results read from DB.
     *             -- second parameter is column index used to get column value from first parameter, then use this value to fill third parameter's
     *                (aka a reference to a object of T) field corresponding to column.
     *             -- third parameter is reference of result object of T
     *             -- If successful return true, otherwise return false
     *
     * @param[in] sql_str Sql str
     * @param[in] populate_field_for_T Object of CallBackFuncType
     * @param[out] result Result vector, each element corresponding to one data of row from query result.
     * @return True if successful,
     *         False if failed.
     */
    template <typename T, typename CallBackFuncType = std::function<holo::bool_t(PreparedSqlStmtSPtrType const, holo::int32_t const, T&)>>
    holo::bool_t execSqlWithResult(std::string const&                     sql_str,
                                   CallBackFuncType const& populate_field_for_T,
                                   std::vector<T>&                        result) const
    {
        result.clear();
        if (sqlitedb_ptr_ == nullptr)
        {
            LOG(ERROR) << "DBEngine::execSqlNoResult failed, database pointer is null.";
            return false;
        }
        sqlite3_stmt* prepared_sqlstmt = nullptr;
        holo::int32_t const error_code = sqlite3_prepare_v2(sqlitedb_ptr_.get(), sql_str.c_str(), sql_str.size() + 1UL, &prepared_sqlstmt, nullptr);
        if (error_code != SQLITE_OK)
        {
            LOG(ERROR) << "DBEngine::execSqlNoResult failed, prepare sql failed, error code is "<< error_code
                       << ", reason is " << LastErrorMsg() << ", sql is " << sql_str;
            return false;
        }
        return execSqlWithResult(PreparedSqlStmtSPtrType(prepared_sqlstmt, GetPreparedSqlStmtDeleter()),
                                 populate_field_for_T, result);
    }

    /**
     * @brief Get name vector of columns from prepared sql stmt
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[out] col_name_vec_str Result name vector of columns.
     * @return True if successful,
     *         False if failed.
     */
    static holo::bool_t getColNameVecStr(PreparedSqlStmtSPtrType const sql_stmt_ptr, std::string& col_name_vec_str);

    /**
     * @brief Execute sql on DB with results returns.
     * @details Generally, we need something to store results query from DB
     *          results from DB are data of multiple rows, those rows share the same model like:
     *                            [col1, col2, col3...]
     *          each column has its own value and data type.
     *          We can image row model as class in C++, columns as fields of that class, results from DB as objects of that class
     *          So there are a relationship between columns(of row) and fields(of class); in order to store results from DB,
     *          user need provide class and method to describe relationship between its fields and columns
     *          Class here is T, method here is CallBackFuncType, results from DB here is std::vector<T> in this function.
     *
     * @tparam T Type of object used to store row data from DB
     * @tparam CallBackFuncType Method used to set values of fields from object of T by using row data from DB.
     *         Form is:
     *                std::function<holo::bool_t(PreparedSqlStmtSPtrType const, holo::int32_t const, T&)
     *             -- first parameter is executed prepared sql stmt from this Query function, which stores all results read from DB.
     *             -- second parameter is column index used to get column value from first parameter, then use this value to fill third parameter's
     *                (aka a reference to a object of T) field corresponding to column.
     *             -- third parameter is reference of result object of T
     *             -- If successful return true, otherwise return false
     *
     * @param[in] sql_stmt_ptr Prepared sql stmt
     * @param[in] populate_field_for_T Object of CallBackFuncType
     * @param[out] result Result vector, each element corresponding to one data of row from query result.
     * @return True if successful,
     *         False if failed.
     */
    template <typename T, typename CallBackFuncType = std::function<holo::bool_t(PreparedSqlStmtSPtrType const, holo::int32_t const, T&)>>
    holo::bool_t execSqlWithResult(PreparedSqlStmtSPtrType const&         sql_stmt_ptr,
                                   CallBackFuncType const& populate_field_for_T,
                                   std::vector<T>&                        result) const
    {
        result.clear();
        if (sqlitedb_ptr_ == nullptr || sql_stmt_ptr == nullptr)
        {
            LOG(ERROR) << "DBEngine::execSqlWithResult failed, database pointer or perpared sql stmt pointer is null.";
            return false;
        }
        holo::int32_t result_code        = -1;
        holo::bool_t  is_column_name_row = true;
        holo::int32_t col_count          = 0;
        while (true)
        {
            result_code = sqlite3_step(sql_stmt_ptr.get());
            if (!(result_code == SQLITE_DONE || result_code == SQLITE_ROW))
            {
                LOG(ERROR) << "DBEngine::execSqlWithResult failed, error code is "<< result_code << ", reason is " << LastErrorMsg()
                           << ", sql is " << std::string(sqlite3_sql(sql_stmt_ptr.get()));
                return false;
            }
            if (result_code == SQLITE_DONE)
            {
                break;
            }
            if (result_code == SQLITE_ROW)
            {
#if DEBUG_MAP_DATABASE_ENGINE
                LOG(INFO) << "DBEngine::execSqlWithResult, access row.";
#endif // DEBUG_MAP_DATABASE_ENGINE
                if (is_column_name_row)
                {
                    col_count = sqlite3_column_count(sql_stmt_ptr.get());
                    std::string column_name_vec_str;
                    if (getColNameVecStr(sql_stmt_ptr, column_name_vec_str))
                    {
#if DEBUG_MAP_DATABASE_ENGINE
                        LOG(INFO) << "DBEngine::execSqlWithResult, columns = " << column_name_vec_str;
#endif // DEBUG_MAP_DATABASE_ENGINE
                    }
                    is_column_name_row = false;
                }
                T object{};
                for (holo::int32_t idx = 0; idx < col_count; ++idx)
                {
                    if (!populate_field_for_T(sql_stmt_ptr, idx, object))
                    {
                        LOG(ERROR) << "DBEngine::execSqlWithResult failed, populate field for T failed, "
                                   << "idx = " << idx << ", error msg is " << LastErrorMsg();
                        result.clear();
                        return false;
                    }
                }
                result.push_back(object);
            }
        }
        if (!ResetPreparedSqlStmt(sql_stmt_ptr))
        {
            LOG(ERROR) << "DBEngine::execSqlWithResult failed, can not reset prepared sql stmt.";
            return false;
        }
        return true;
    }

private:
    /// Internal sqlite db pointer
    SqliteDBUPtrType sqlitedb_ptr_ = nullptr;

};  // Class DBEngine

/// Handy typedefs
using DBEngineUPtrType  = std::unique_ptr<DBEngine>;
using DBEngineCUPtrType = std::unique_ptr<DBEngine const>;

/**
 * @}
 */
}  // namespace map
/**
 * @}
 */
}  // namespace holo

/**
 * Prevent direct initialization with raw pointer only
 * Must initialization with raw pointer and deleter(use GetPreparedSqlStmtDeleter to get deleter)
 * 
 * lisong: 2020-07-29
 * Old version of that code is :
 * 
 * template <>
 * template <>
 * holo::map::DBEngine::PreparedSqlStmtSPtrType::shared_ptr(sqlite3_stmt* ptr) = delete;
 * 
 * template <>
 * template <>
 * holo::map::DBEngine::PreparedSqlStmtCSPtrType::shared_ptr(sqlite3_stmt const* ptr) = delete;
 * 
 * In gcc 5.5 it will cause following complier error:
 *     specialization of ‘template<class _Tp> template<class _Tp1> std::shared_ptr<_Tp>::shared_ptr(_Tp1*)’ in in different namespace [-fpermissive]
 * But in gcc 7.5, it's passed.
 * So to adapt to different version of gcc, make change below.
 */
/**
 * Close for compiling on TDA4 QNX. Because of: "error: template-id 'shared_ptr<>' for 
 * 'std::__1::shared_ptr<sqlite3_stmt>::shared_ptr(sqlite3_stmt*)' does not match any template declaration
 *  holo::map::DBEngine::PreparedSqlStmtSPtrType::shared_ptr(sqlite3_stmt* ptr) = delete;".
 * Author WangHaiYang 2021-06-03
 */
#if 0
namespace std
{
    template <>
    template <>
    holo::map::DBEngine::PreparedSqlStmtSPtrType::shared_ptr(sqlite3_stmt* ptr) = delete;

    template <>
    template <>
    holo::map::DBEngine::PreparedSqlStmtCSPtrType::shared_ptr(sqlite3_stmt const* ptr) = delete;
}
#endif

#endif /* HOLO_MAP_DATABASE_DB_ENGINE_H_ */
