/*!
 *  \brief SQLite DataBase interface
 *  \author jiangdianqin(jiangdianqin@holomaitc.com)
 *  \date 2018-04-04
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */
#ifndef HOLO_MAP_DATABASE_RETRIEVER_SQLITEDB
#define HOLO_MAP_DATABASE_RETRIEVER_SQLITEDB

#include <holo/log/hololog.h>
#include <iostream>
#include <memory>
#include <string>

#include <holo/map/common_def.h>
#include <holo/map/database/db.h>
#include <sqlite3.h>

namespace holo
{
namespace map
{
template <typename DataType>
class SQLiteDB : public DB<DataType>
{
public:
    /**
     * @brief SQLite constructor
     */
    SQLiteDB() = default;
    /**
     * @brief SQLite destructor
     */
    ~SQLiteDB() = default;
    /**
     * @brief Open a new SQLiteDB,suit for file DB
     *
     * @param[in] _data_db_path db file path
     * @return true          Open db handle success
     * @return false         Otherwise
     */
    bool Open(const char* _data_db_path)
    {
        // int rtn = sqlite3_open(_data_db_path, &db_); /* old api can not support open status*/
        int rtn = sqlite3_open_v2(_data_db_path, &db_, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
        if (SQLITE_OK != rtn) {
          LOG(ERROR) << "Open fail, sqlite3_open fail, db=" << _data_db_path
                     << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
          return false;
        }

        //create table if not exist;
        if (!this->CreateTable())
        {
            LOG(ERROR) << "Open fail, CreateTable fail, db=" << _data_db_path;
            this->Close();
            return false;
        }

        bool ok = true;
        auto prepare = [&ok] (sqlite3* db, sqlite3_stmt** stmt,  std::string const sql) -> void {
            int const rtn = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), stmt, nullptr);
            if (SQLITE_OK != rtn)
            {
                LOG(ERROR) << "Open fail, sqlite3_prepare_v2 fail, sql=" << sql << " rtn=" << rtn
                           << " err=" << sqlite3_errstr(rtn);
            }
            ok = (SQLITE_OK != rtn) ? false : ok;
        };

        //prepare handle at first;
        prepare(this->db_, &stmt_counts_ptr_, stat_count_);
        prepare(this->db_, &stmt_read_ptr_, stat_read_);
        prepare(this->db_, &stmt_read_header_ptr_, stat_read_header_);
        prepare(this->db_, &stmt_key_scale_ptr_, stat_key_scale_);
        prepare(this->db_, &stmt_write_ptr_, stat_write_);
        prepare(this->db_, &stmt_update_ptr_, stat_update_);
        prepare(this->db_, &stmt_delete_ptr_, stat_delete_);
        prepare(this->db_, &stmt_delete_header_ptr_, stat_delete_header_);
        prepare(this->db_, &stmt_exist_ptr_, stat_exist_);
        prepare(this->db_, &stmt_exist_header_ptr_, stat_exist_header_);
        prepare(this->db_, &stmt_read_keys_ptr_, stat_read_keys_);

        if (!ok)
        {
            this->Close();
            return false;
        }
        return true;
    }

    /**
     * @brief Get the Counts object
     *
     * @param[out] _num
     * @return true
     * @return false
     */
    bool GetCounts(int& _num)
    {
        _num = 0;

        int const rtn = sqlite3_step(stmt_counts_ptr_);
        if (SQLITE_ROW != rtn)
        {
            LOG(ERROR) << "GetCounts fail, sqlite3_step fail, rtn =" << rtn << " err=" << sqlite3_errstr(rtn);
            return false;
        }

        _num = sqlite3_column_int(stmt_counts_ptr_,0);
        return true;
    }

    /**
     * @brief Get the Key Range object
     *
     * @param[out] _max_key
     * @param[out] _min_key
     * @return true
     * @return false
     */
    bool GetKeyRange(MapFeatureIdType& _max_key, MapFeatureIdType& _min_key)
    {
        _max_key = 0;
        _min_key = 0;
    
        // Run this sqlite statement
        int const rtn = sqlite3_step(stmt_key_scale_ptr_);
        if (SQLITE_ROW != rtn)
        {
            LOG(ERROR) << "GetKeyRange fail, sqlite3_step fail, rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
            return false;
        }
        
        _max_key = sqlite3_column_int64(stmt_key_scale_ptr_, 0);
        _min_key = sqlite3_column_int64(stmt_key_scale_ptr_, 1);

        return true;
    }

    bool GetKeys(std::vector<KeyType>* vec_key) {
      vec_key->clear();
      while (SQLITE_ROW == sqlite3_step(stmt_read_keys_ptr_)) {
        vec_key->emplace_back(sqlite3_column_int64(stmt_read_keys_ptr_, 0));
      }
      return true;
    }

    int StartTransaction()
    {
      int rtn = sqlite3_get_autocommit(db_);
      if (0 == rtn) {
        LOG(INFO) << "Start transaction failed, already start transaction";
        return 1;
        }
        rtn = sqlite3_exec(db_, "begin", nullptr, nullptr, nullptr);
        if (SQLITE_OK != rtn)
        {
            LOG(ERROR) << "Start transaction failed, sqlite3_exec(begin) failed, errcode=" << sqlite3_errcode(db_)
                       << " errstr=" << sqlite3_errstr(rtn) << " class=" << DataType::GetClassName();
            return -1;
        }

        return 0;
    }

    bool CommitTransaction()
    {
        int rtn = sqlite3_exec(db_, "commit", nullptr, nullptr, nullptr);
        if (SQLITE_OK != rtn)
        {
            LOG(ERROR) << "Commit transaction failed, sqlite3_exec(commit) failed, errcode=" << sqlite3_errcode(db_)
                       << " errstr=" << sqlite3_errstr(rtn) << " class=" << DataType::GetClassName();
            return false;
        }

        return true;
    }

    bool RollbackTransaction()
    {
        int rtn = sqlite3_exec(db_, "rollback", nullptr, nullptr, nullptr);
        if (SQLITE_OK != rtn) {
            LOG(ERROR) << "Rollback transaction failed, sqlite3_exec(commit) failed, errcode=" << sqlite3_errcode(db_)
                       << " errstr=" << sqlite3_errstr(rtn) << " class=" << DataType::GetClassName();
            return false;
        }

        return true;
    }

    /**
     * @brief Create a Index object
     *
     * @return true   Create index successfully
     * @return false  Otherwise
     */
    bool CreateIndex()
    {
        int const rtn = sqlite3_exec(db_, stat_create_index_.c_str(), nullptr, nullptr, nullptr);
        if (SQLITE_OK != rtn)
        {
            LOG(ERROR) << "CreateIndex fail, sqlite3_exec fail, rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
            LOG(INFO) << "Create index fail!";
            return false;
        }
        return true;
    }

    /**
     * @defgroup holo_sqlite_V3_API custom commit granularity,use V3 because * V2 occupied by ReadV2
     * @{
     */

    /**
     * @brief write a record
     * 
     * @param key 
     * @param valueptr 
     * @return true 
     * @return false 
     */
    bool WriteV3(const KeyType key, const std::shared_ptr<DataType>& valueptr)
    {
        if (!valueptr) {
            LOG(ERROR) << "WriteV2 failed, the data is null";
            return false;
        }

        // sqlite3_prepare16_v2()
        auto data = valueptr->GetDataBlock();
        int rtn   = sqlite3_bind_int64(stmt_write_ptr_, 1, static_cast<::holo::int64_t>(key));
        if (SQLITE_OK != rtn) {
            LOG(ERROR) << "WriteV2 failed, sqlite3_bind_int64 failed, key=" << key << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn) << " class=" << DataType::GetClassName();
            ResetStmt(stmt_write_ptr_);
            return false;
        }

        rtn = sqlite3_bind_blob(stmt_write_ptr_, 2, (void*)(data.pointer), data.size, SQLITE_STATIC);
        if (SQLITE_OK != rtn) {
            LOG(ERROR) << "WriteV2 failed, sqlite3_bind_blob failed, key=" << key << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn) << " class=" << DataType::GetClassName();
            ResetStmt(stmt_write_ptr_);
            return false;
        }

        rtn = sqlite3_step(stmt_write_ptr_);
        if (SQLITE_DONE != rtn) {
            LOG(ERROR) << "WriteV2 fail, sqlite3_step fail, key=" << key << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn) << " class=" << DataType::GetClassName();
            ResetStmt(stmt_write_ptr_);
            return false;
        }

        ResetStmt(stmt_write_ptr_);
        return true;
    }

    /**
     * @brief update a record
     * 
     * @param key 
     * @param valueptr 
     * @return true 
     * @return false 
     */
    bool UpdateV3(const KeyType key, const std::shared_ptr<DataType>& valueptr)
    {
        if (!valueptr) {
            LOG(ERROR) << "UpdateV2 failed, the data is null, class=" << DataType::GetClassName() << " key=" << key;
            return false;
        }

        auto data = valueptr->GetDataBlock();
        int rtn   = sqlite3_bind_int64(stmt_update_ptr_, 2, static_cast<::holo::int64_t>(key));
        if (rtn != SQLITE_OK) {
            LOG(ERROR) << "UpdateV2 failed, sqlite3_bind_int64 failed, class=" << DataType::GetClassName()
                       << " key=" << key << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
            ResetStmt(stmt_update_ptr_);
            return false;
        }

        rtn = sqlite3_bind_blob(stmt_update_ptr_, 1, (void*)(data.pointer), data.size, SQLITE_STATIC);
        if (rtn != SQLITE_OK) {
            LOG(ERROR) << "UpdateV2 failed, sqlite3_bind_blob failed, class=" << DataType::GetClassName()
                       << " key=" << key << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
            ResetStmt(stmt_update_ptr_);
            return false;
        }

        // Call sqlite3_step() to run the virtual machine. Since the SQL being
        // executed is not a SELECT statement, we assume no data will be returned.
        rtn = sqlite3_step(stmt_update_ptr_);
        if (SQLITE_DONE != rtn) {
            LOG(ERROR) << "UpdateV2 failed, sqlite3_step fail, class=" << DataType::GetClassName() << " key=" << key
                       << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);

            ResetStmt(stmt_update_ptr_);
            return false;
        }

        ResetStmt(stmt_update_ptr_);
        return true;
    }

    /**
     * @brief delete a record
     * 
     * @param key 
     * @return true 
     * @return false 
     */
    bool DeleteV3(const KeyType key)
    {
      sqlite3_stmt* stmt_ptr =
          key == 0 ? stmt_delete_header_ptr_ : stmt_delete_ptr_;

      int rtn =
          sqlite3_bind_int64(stmt_ptr, 1, static_cast<::holo::int64_t>(key));
      if (SQLITE_OK != rtn) {
        LOG(ERROR) << "Delete failed, sqlite3_bind_int64 fail, key=" << key
                   << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
        ResetStmt(stmt_ptr);
        return false;
        }

        rtn = sqlite3_step(stmt_ptr);
        if (SQLITE_DONE != rtn) {
            LOG(ERROR) << "Delete fail, sqlite3_step fail, key=" << key << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn);

            ResetStmt(stmt_ptr);
            return false;
        }

        ResetStmt(stmt_ptr);
        return true;
    }

    /**
     * @brief read a record
     * 
     * @param key 
     * @param valueptr 
     * @param valid 
     * @return true 
     * @return false 
     */
    bool ReadV3(const KeyType key, std::shared_ptr<DataType>& valueptr, bool* valid)
    {
        assert(valid);

        *valid = false;

        if (!valueptr) {
            LOG(ERROR) << "ReadV3 failed, invalid parameter, key=" << key << " class=" << DataType::GetClassName();
            return false;
        }

        // if key == 0, will read header
        sqlite3_stmt* stmt_ptr =
            ((key == 0) && (valueptr->GetClassName() == "Header"))
                ? stmt_read_header_ptr_
                : stmt_read_ptr_;

        // Complete the sqlite statement defined above
        int rtn = sqlite3_bind_int64(stmt_ptr, 1, static_cast<::holo::int64_t>(key));
        if (SQLITE_OK != rtn) {
            LOG(ERROR) << "ReadV3 failed, sqlite3_bind_int64 failed, key=" << key
                       << " class=" << DataType::GetClassName() << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
            ResetStmt(stmt_ptr);
            return false;
        }

        // Run this sqlite statement
        rtn = sqlite3_step(stmt_ptr);
        if (SQLITE_DONE == rtn) {
            LOG(INFO) << "ReadV3 failed, sqlite3_step failed, key=" << key << " class=" << DataType::GetClassName()
                      << " this data is not existed";
            ResetStmt(stmt_ptr);
            return true;
        }

        if (rtn != SQLITE_ROW) {
            LOG(ERROR) << "ReadV3 failed, sqlite fail, key=" << key << " rtn=" << rtn
                       << " name=" << valueptr->GetClassName() << " err=" << sqlite3_errstr(rtn);

            ResetStmt(stmt_ptr);
            return false;
        }

        int const size = sqlite3_column_bytes(stmt_ptr, 0);
        if (size <= 0) {
            LOG(ERROR) << "ReadV3 fail, cloumn size=0, key=" << key << " rtn=" << rtn
                       << " name=" << valueptr->GetClassName() << " err=" << sqlite3_errstr(rtn);

            ResetStmt(stmt_ptr);
            return false;
        }

        ::std::size_t const usize = static_cast<::std::size_t>(size);
        std::shared_ptr<unsigned char> dataptr(new unsigned char[usize],
                                               [](unsigned char* _data_ptr) { delete[] _data_ptr; });
        if (dataptr != nullptr) {
            memcpy((void*)(dataptr.get()), (void*)sqlite3_column_blob(stmt_ptr, 0), usize);
            format::Base::DataBlock block;
            block.size    = usize;
            block.pointer = (const char*)(dataptr.get());
            valueptr->SetDataBlock(block);
            *valid = true;
        }

        ResetStmt(stmt_ptr);
        return true;
    }
    /**@}*/

    /**
     * @brief Write a record into db
     *
     * @param[in] _zKey    key assignments
     * @param[in] _value_ptr   value assignments
     * @return true    write success
     * @return false   otherwise
     */
    bool Write(const MapFeatureIdType _key, const std::shared_ptr<DataType>& _value_ptr)
    {
        if (_value_ptr.get() == nullptr)
        {
            LOG(ERROR) << "Write fail, invalid parameter, key=" << _key;
            return false;
        }

        // To guarantee atomic;
        int rtn = sqlite3_exec(db_, "begin", nullptr, nullptr, nullptr);
        if (SQLITE_OK != rtn)
        {
            LOG(ERROR) << "Write fail, sqlite3_exec(begin) fail, key=" << _key << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn) << " class=" << DataType::GetClassName();
            return false;
        }
        
        /* Compile the INSERT statement into a virtual machine. */
        /* Bind the key and value data for the new table entry to SQL variables
        ** (the ? characters in the sql statement) in the compiled INSERT
        ** statement.
        **
        ** NOTE: variables are numbered from left to right from 1 upwards.
        ** Passing 0 as the second parameter of an sqlite3_bind_XXX() function
        ** is an error.
        */
        auto data = _value_ptr->GetDataBlock();
        sqlite3_bind_int64(stmt_write_ptr_, 1, static_cast<::holo::int64_t>(_key));
        sqlite3_bind_blob(stmt_write_ptr_, 2, (void*)(data.pointer), data.size, SQLITE_STATIC);

        /* Call sqlite3_step() to run the virtual machine. Since the SQL being
        ** executed is not a SELECT statement, we assume no data will be
        *returned.
        */
        rtn = sqlite3_step(stmt_write_ptr_);
        if (SQLITE_DONE != rtn)
        {
            LOG(ERROR) << "Write fail, sqlite3_step fail, key=" << _key << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn) << " class=" << DataType::GetClassName();
            rtn = sqlite3_exec(db_, "rollback", nullptr, nullptr, nullptr);
            if (SQLITE_OK != rtn)
            {
                LOG(ERROR) << "Write fail, sqlite3_exec(rollback) fail, key=" << _key << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn) << " class=" << DataType::GetClassName();
            }
            ResetStmt(stmt_write_ptr_);
            return false;
        }

        rtn = sqlite3_exec(db_, "commit", nullptr, nullptr, nullptr);
        if (SQLITE_OK != rtn)
        {
            LOG(ERROR) << "Write fail, sqlite3_exec(commit) fail, key=" << _key << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn) << " class=" << DataType::GetClassName();
            ResetStmt(stmt_write_ptr_);
            return false;
        }

        ResetStmt(stmt_write_ptr_);
        return true;
    }

    /**
     * @brief Read a record from db
     *
     * @note If a target data is not in database actually, it will return
     *       false.
     * @param[in]  key     key assignments
     * @param[out] value   out value
     * @return true     read success
     * @return false    otherwis
     */
    bool Read(MapFeatureIdType const key, std::shared_ptr<DataType> const & value)
    {
        bool valid = false;
        const bool ok = this->ReadV2(key, value, valid);
        return ok && valid;
    }

    /**
     * @brief Read a record from db.
     *
     * @note If a target data is not in database actually, it will return
     *       true, but the valid will be set false.
     * @param[in]  key       key assignments
     * @param[out] value_ptr out value
     * @param[out] valid      Whether or not the value is valid.
     * @return true No error, even though the target object not in database 
     *              actually, valid will be false, if should check it.
     * @return false An error occurs in this function.
     */
    bool ReadV2(MapFeatureIdType const key, std::shared_ptr<DataType> const & value , bool& valid)
    {
        valid = false;
        if (value.get() == nullptr)
        {
            LOG(ERROR) << "ReadV2 fail, invalid parameter, key=" << key << " class="
                       << DataType::GetClassName();
            return false;
        }

        //if key == 0, will read header
        sqlite3_stmt* stmt_ptr = ((key == 0) && (value->GetClassName() == "Header"))
            ? stmt_read_header_ptr_ : stmt_read_ptr_;
        
        // improve read and write speed;
        int rtn = sqlite3_exec(db_, "begin", nullptr, nullptr, nullptr);
        if (rtn != SQLITE_OK)
        {
            LOG(ERROR) << "ReadV2 fail, sqlite3_exec(begin) fail, key=" << key << " class="
                       << DataType::GetClassName() << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
            return false;
        }

        // Complete the sqlite statement defined above
        sqlite3_bind_int64(stmt_ptr, 1, static_cast<::holo::int64_t>(key));

        // Run this sqlite statement
        rtn = sqlite3_step(stmt_ptr);
        if (SQLITE_DONE == rtn)
        {
            rtn = sqlite3_exec(db_, "commit", nullptr, nullptr, nullptr);
            if (SQLITE_OK != rtn)
            {
                LOG(ERROR) << "ReadV2 fail, sqlite3_exec(commit) fail, key=" << key << " class="
                           << DataType::GetClassName() << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
            }

	        ResetStmt(stmt_ptr);
            return true; // The target data is not in database.
        }

        if (rtn != SQLITE_ROW)
        {
            LOG(ERROR) << "ReadV2 fail, Sqlite fail, key=" << key << " rtn=" << rtn
                       << " name=" << value->GetClassName() << " err=" << sqlite3_errstr(rtn);

            rtn = sqlite3_exec(db_, "rollback", nullptr, nullptr, nullptr);
            if (SQLITE_OK != rtn)
            {
                LOG(ERROR) << "ReadV2 fail, sqlite3_exec(rollback) fail, key=" << key << " rtn=" << rtn
                           << " name=" << value->GetClassName() << " err=" << sqlite3_errstr(rtn);
            }

            ResetStmt(stmt_ptr);
            return false;
        }

        int const size = sqlite3_column_bytes(stmt_ptr, 0);
        if (size <= 0)
        {
            LOG(ERROR) << "ReadV2 fail, Sqlite fail, key=" << key << " rtn=" << rtn
                       << " name=" << value->GetClassName() << " err=" << sqlite3_errstr(rtn);

            rtn = sqlite3_exec(db_, "rollback", nullptr, nullptr, nullptr);
            if (SQLITE_OK != rtn)
            {
                LOG(ERROR) << "ReadV2 fail, sqlite3_exec(rollback), key=" << key << " rtn=" << rtn
                           << " err=" << sqlite3_errstr(rtn) << " name=" << value->GetClassName();
            }

            ResetStmt(stmt_ptr);
            return false;
        }
        
        ::std::size_t const usize = static_cast<::std::size_t>(size);
        std::shared_ptr<unsigned char> dataptr(
            new unsigned char[usize], [](unsigned char* _data_ptr) { delete[] _data_ptr; });
        if (dataptr != nullptr)
        {
            memcpy((void*)(dataptr.get()), (void*)sqlite3_column_blob(stmt_ptr, 0), usize);
            format::Base::DataBlock block;
            block.size = usize;
            block.pointer = (const char*)(dataptr.get());
            value->SetDataBlock(block);
            valid = true;
        }

        rtn = sqlite3_exec(db_, "commit", nullptr, nullptr, nullptr);
        if (SQLITE_OK != rtn)
        {
            LOG(ERROR) << "ReadV2 fail, sqlite3_exec(commit) fail, key=" << key << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn) << " class=" << DataType::GetClassName();
            ResetStmt(stmt_ptr);
            return false;
        }

        ResetStmt(stmt_ptr);
        return true;
    }

    /**
     * @brief update
     *
     * @param[in] _key
     * @param[in] _value_ptr
     * @return true
     * @return false
     */
    bool Update(const MapFeatureIdType _key,
                const std::shared_ptr<DataType>& _value_ptr)
    {
        if (_value_ptr.get() == nullptr)
        {
            LOG(ERROR) << "Update fail, invalid parameter, class=" << DataType::GetClassName()
                      << " key=" << _key;
            return false;
        }

        // To guarantee atomic.
        int rtn = sqlite3_exec(db_, "begin", nullptr, nullptr, nullptr);
        if (SQLITE_OK != rtn)
        {
            LOG(ERROR) << "Update fail, sqlite3_exec(begin) fail, class=" << DataType::GetClassName()
                      << " key=" << _key << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
            return false;
        }

        /* Bind the key and value data for the new table entry to SQL variables
        ** (the ? characters in the sql statement) in the compiled INSERT
        ** statement.
        **
        ** NOTE: variables are numbered from left to right from 1 upwards.
        ** Passing 0 as the second parameter of an sqlite3_bind_XXX() function
        ** is an error.
        */
        auto data = _value_ptr->GetDataBlock();
        sqlite3_bind_blob(stmt_update_ptr_, 1, (void*)(data.pointer), data.size, SQLITE_STATIC);
        sqlite3_bind_int64(stmt_update_ptr_, 2, static_cast<::holo::int64_t>(_key));

        // Call sqlite3_step() to run the virtual machine. Since the SQL being
        // executed is not a SELECT statement, we assume no data will be returned.
        rtn = sqlite3_step(stmt_update_ptr_);
        if (SQLITE_DONE != rtn)
        {
            LOG(ERROR) << "Update fail, sqlite3_step fail, class=" << DataType::GetClassName()
                      << " key=" << _key << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);

            rtn = sqlite3_exec(db_, "rollback", nullptr, nullptr, nullptr);
            if (SQLITE_OK != rtn)
            {
                LOG(ERROR) << "Update fail, sqlite3_exec(rollback) fail, class=" << DataType::GetClassName()
                           << " key=" << _key << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
            }

            ResetStmt(stmt_update_ptr_);
            return false;
        }

        rtn = sqlite3_exec(db_, "commit", nullptr, nullptr, nullptr);
        if (rtn != SQLITE_OK)
        {
            LOG(ERROR) << "Update fail, sqlite3_exec(commit) fail, class=" << DataType::GetClassName()
                      << " key=" << _key << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
            ResetStmt(stmt_update_ptr_);
            return false;
        }

        ResetStmt(stmt_update_ptr_);
        return true;
    }

    /**
     * @brief
     *
     * @param[in] _key
     * @return true
     * @return false
     */
    bool Delete(const MapFeatureIdType _key)
    {
        sqlite3_stmt *stmt_ptr = _key == 0 ? stmt_delete_header_ptr_ : stmt_delete_ptr_;
        
        // To guarantee atomic.
        int rtn = sqlite3_exec(db_, "begin", 0, 0, 0);
        if (SQLITE_OK != rtn)
        {
            LOG(ERROR) << "Delete fail, sqlite3_exec(begin) fail," << " key=" << _key << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn);
            return false;
        }

        /* Compile the INSERT statement into a virtual machine. */
        /* Bind the keyfor the new table entry to SQL variables
        ** (the ? characters in the sql statement) in the compiled INSERT
        ** statement.
        **
        ** NOTE: variables are numbered from left to right from 1 upwards.
        ** Passing 0 as the second parameter of an sqlite3_bind_XXX() function
        ** is an error.
        */
        sqlite3_bind_int64(stmt_ptr, 1, static_cast<::holo::int64_t>(_key));

        /* Call sqlite3_step() to run the virtual machine. Since the SQL being
        ** executed is not a SELECT statement, we assume no data will be
        *returned.
        */
        rtn = sqlite3_step(stmt_ptr);
        if (SQLITE_DONE != rtn)
        {
            LOG(ERROR) << "Delete fail, sqlite3_step fail, key=" << _key << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn);

            rtn = sqlite3_exec(db_, "rollback", nullptr, nullptr, nullptr);
            if (SQLITE_OK != rtn)
            {
                LOG(ERROR) << "Delete fail, sqlite3_exec(rollback) fail, key=" << _key << " rtn=" << rtn
                           << " err=" << sqlite3_errstr(rtn);
            }
            ResetStmt(stmt_ptr);
            return false;
        }

        rtn = sqlite3_exec(db_, "commit", nullptr, nullptr, nullptr);
        if (SQLITE_OK != rtn)
        {
            LOG(ERROR) << "Delete fail, sqlite3_exec(commit) fail," << " key=" << _key  << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn);
            ResetStmt(stmt_ptr);
            return false;
        }

        ResetStmt(stmt_ptr);
        return true;
    }

    /**
     * @brief  Close db
     *
     * @return true  close success
     * @return false otherwise
     */
    bool Close()
    {
        bool ok = true;
        auto finalize = [&ok] (sqlite3_stmt* stmt, std::string const& name) -> void {
            if (nullptr != stmt)
            {
                int const rtn = sqlite3_finalize(stmt);
                if (SQLITE_OK != rtn)
                {
                    LOG(ERROR) << "Close fail, sqlite3_finalize(" << name << ") fail, rtn=" << rtn
                               << " err=" << sqlite3_errstr(rtn);
                }
                ok = (SQLITE_OK != rtn) ? false : ok;
            }
        };
        
        finalize(stmt_counts_ptr_, "stmt_counts_ptr_");
        stmt_counts_ptr_ = nullptr;
        finalize(stmt_read_ptr_, "stmt_read_ptr_");
        stmt_read_ptr_ = nullptr;
        finalize(stmt_read_header_ptr_, "stmt_read_header_ptr_");
        stmt_read_header_ptr_ = nullptr;
        finalize(stmt_key_scale_ptr_, "stmt_key_scale_ptr_");
        stmt_key_scale_ptr_ = nullptr;
        finalize(stmt_write_ptr_, "stmt_write_ptr_");
        stmt_write_ptr_ = nullptr;
        finalize(stmt_update_ptr_, "stmt_update_ptr_");
        stmt_update_ptr_ = nullptr;
        finalize(stmt_delete_ptr_, "stmt_delete_ptr_");
        stmt_delete_ptr_ = nullptr;
        finalize(stmt_delete_header_ptr_, "stmt_delete_header_ptr_");
        stmt_delete_header_ptr_ = nullptr;
        finalize(stmt_exist_ptr_, "stmt_exist_ptr_");
        stmt_exist_ptr_ = nullptr;
        finalize(stmt_exist_header_ptr_, "stmt_exist_header_ptr_");
        stmt_exist_header_ptr_ = nullptr;
        finalize(stmt_read_keys_ptr_, "stmt_read_keys_ptr_");
        stmt_read_keys_ptr_ = nullptr;

        //close db;
        if (nullptr != this->db_)
        {
            int const rtn = sqlite3_close(this->db_);
            if (SQLITE_OK != rtn)
            {
                LOG(ERROR) << "Close fail, rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
            }
            ok = (SQLITE_OK != rtn) ? false : ok;
            this->db_ = nullptr;   
        }
        
        return ok;
    }

    /**
     * @brief judge if a recors exist
     *
     * @param[in] _key
     * @return true record exist
     * @return false record doesn't exist
     */
    bool Exist(const MapFeatureIdType _key)
    {
        sqlite3_stmt *stmt_ptr = _key == 0 ? stmt_exist_header_ptr_ : stmt_exist_ptr_;

        // Complete the sqlite statement defined above
        int rtn = sqlite3_bind_int64(stmt_ptr, 1, static_cast<::holo::int64_t>(_key));
        if (SQLITE_OK != rtn)
        {
            LOG(ERROR) << "Exist fail, sqlite3_exec fail, key=" << _key << " rtn=" << rtn
                       << " msg=" << sqlite3_errstr(rtn);
            return false;
        }

        // Run this sqlite statement
        rtn = sqlite3_step(stmt_ptr);
        if (SQLITE_ROW != rtn)
        {
            LOG(ERROR) << "Exist fail, sqlite3_step fail, key=" << _key << " rtn=" << rtn
                       << " err=" << sqlite3_errstr(rtn);
            ResetStmt(stmt_ptr);
            return false;
        }

        std::int64_t const num = sqlite3_column_int64(stmt_ptr, 0);
        if (num == 0)
        {
            ResetStmt(stmt_ptr);
            return false;
        }
        else
        {
            ResetStmt(stmt_ptr);
            return true;
        }
    }

private:

    /**
     * @brief Create a Table
     *
     * @return true          Create Table success
     * @return false         Otherwise
     */
    bool CreateTable()
    {
        int const rtn = sqlite3_exec(db_, stat_create_table_.c_str(), nullptr, nullptr, nullptr);
        if (rtn != SQLITE_OK)
        {
            LOG(ERROR) << "CreateTable fail, sqlite3_exec fail, sql=" << this->stat_create_table_
                       << " rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
            return false;
        }
        return true;
    }

    /**
     * @brief reset stmt
     *
     * @param[in|out] _stmt_ptr
     */
    void ResetStmt(sqlite3_stmt *&_stmt_ptr)
    {
        int rtn = sqlite3_reset(_stmt_ptr);
        if (SQLITE_OK != rtn)
        {
            LOG(ERROR) << "ResetStmt fail, sqlite3_reset fail, rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
        }

        rtn = sqlite3_clear_bindings(_stmt_ptr);
        if (SQLITE_OK != rtn)
        {
            LOG(ERROR) << "ResetStmt fail, sqlite3_clear_bindings fail, rtn=" << rtn << " err=" << sqlite3_errstr(rtn);
        }
    }

private:
    sqlite3* db_ = nullptr;
    //sql statement
    const ::std::string stat_create_table_ =  "CREATE TABLE IF NOT EXISTS blobs(key BIGINT "
                                        "PRIMARY "
                                        "KEY,value BLOB)";
    const ::std::string stat_create_index_ =  "CREATE UNIQUE INDEX blob_index ON blobs(KEY)";
    const ::std::string stat_write_   =   "INSERT INTO blobs(key, value) VALUES (?,?)";
    const ::std::string stat_read_    =   "SELECT value FROM blobs WHERE key = ?";
    const ::std::string stat_read_header_ =   "SELECT value FROM blobs";
    const ::std::string stat_update_  =   "UPDATE blobs SET value = ? WHERE key = ?";
    const ::std::string stat_delete_  =   "DELETE FROM blobs WHERE key = ?";
    const ::std::string stat_delete_header_   =   "DELETE FROM blobs";
    const ::std::string stat_key_scale_   =   "SELECT MAX(key),MIN(key) FROM blobs";
    const ::std::string stat_exist_   =   "SELECT count(*) FROM blobs WHERE key = ?";
    const ::std::string stat_exist_header_    =   "SELECT count(*) FROM blobs";
    const ::std::string stat_count_   =   "SELECT count(*) FROM blobs";
    const ::std::string stat_read_keys_ = "select key from blobs order by key";
    // sql handle
    sqlite3_stmt *stmt_counts_ptr_          = nullptr;
    sqlite3_stmt *stmt_write_ptr_           = nullptr;
    sqlite3_stmt *stmt_update_ptr_          = nullptr;
    sqlite3_stmt *stmt_delete_ptr_          = nullptr;
    sqlite3_stmt *stmt_delete_header_ptr_   = nullptr;
    sqlite3_stmt *stmt_key_scale_ptr_       = nullptr;
    sqlite3_stmt *stmt_exist_ptr_           = nullptr;
    sqlite3_stmt *stmt_exist_header_ptr_    = nullptr;
    sqlite3_stmt *stmt_read_ptr_            = nullptr;
    sqlite3_stmt *stmt_read_header_ptr_     = nullptr;
    sqlite3_stmt* stmt_read_keys_ptr_       = nullptr;
};  ///< End of class SqliteDB

}  ///< namespace map
}  ///< namespace holo

#endif /* HOLO_MAP_DATABASE_RETRIEVER_SQLITEDB */
