/*!
 *  \brief memcache module ,specify by the concrete DataType
 *  \author daizhen(daizhen@holomaitc.com)
 *  \date 2017-09-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_MAP_RETRIEVER_MEMCACHE_H_
#define HOLO_MAP_RETRIEVER_MEMCACHE_H_
#include <stdio.h>
#include <unistd.h>

#include <deque>

#ifdef HOLO_MAP_MULTITHREADS
#include <mutex>
#endif

#include <holo/map/common/common_type_define.h>

#include <holo/map/database/db.h>
#include <holo/map/database/sqlite/sqlitedb.h>

namespace holo
{
namespace map
{
template <typename TypeKey, typename TypeData>
class MemCache
{
public:
    typedef std::shared_ptr<TypeData> TypeDataPointer;
    typedef std::unordered_map<TypeKey, TypeDataPointer> TypeHashmap;

    /// Redefine size type for MemCache.
    using SizeType = std::size_t;

    /// Define the max capacity for inner memery cache.
    static SizeType constexpr MAX_MEM_CACHE_CAPACITY = std::numeric_limits<SizeType>::max();

    /**
     * @brief Construct a new Mem Cache object
     *
     * @param[in] _max_size maximum size of cache, if it equals to MAX_MEM_CACHE_CAPACITY, the MemCache works
     *                      with [Unlimited] mode.
     * @param[in] _map_directory  physical storage directory
     * @param[in] _read_local_db If fasle, we will return false directly when a target object is not in the 
     *                           current cache;
     *                           If true, we will read target object from local database when the target object 
     *                           is not in the current cache.
     * 
     * @return Nothing.
     */
    MemCache(const SizeType _max_size, const std::string& _map_directory, const holo::bool_t _read_local_db = true)
    {
        this->max_size_      = _max_size;
        this->read_local_db_ = _read_local_db;

        if (this->read_local_db_)
        {
            const std::string dt_name = TypeData::GetClassName();
            const std::string speparator = (!_map_directory.empty() && _map_directory[_map_directory.size()-1] != '/') ? "/" : "";
            const std::string tile_db_path = _map_directory + speparator + dt_name + "_blob.db";

            OpenDatabase(tile_db_path.c_str());
        }
    }

    /**
     * @brief Destroy the Mem Cache object
     *
     */
    ~MemCache()
    {
        Reset();

        if (this->read_local_db_)
        {
            CloseDatabase();
        }
    }

    /**
     * @brief reset
     *
     */
    void Reset()
    {
#ifdef HOLO_MAP_MULTITHREADS
        std::lock_guard<std::mutex> lg(this->mutex_);
#endif
        // map didn't provide the func like below,but our shared_ptr can help us
        // release the RAM.
        this->hashmap_.clear();
        // In C++11,we can use shrink_to_fit() to destory the RAM in
        // stl::string、deque and vector after clear();
        this->keys_.clear();
        this->keys_.shrink_to_fit();
    }

    /**
     * @brief Get current element count from the mem cache.
     * 
     * @return Current element count.
     */
    SizeType GetCount() const noexcept
    {
#ifdef HOLO_MAP_MULTITHREADS
        std::lock_guard<std::mutex> lg(this->mutex_);
#endif /* HOLO_MAP_MULTITHREADS */

        return this->hashmap_.size();
    }

    /**
     * @brief Check if a feature exists.
     *
     * @note If the memcache doesn't work with local database, it only check if the target feature
     *       exists in memory cache.
     * @param[in] _key Feature id.
     * @return true: Target feature does exist;
               false: Otherwise.
     */
    holo::bool_t Exist(const MapFeatureIdType _key)
    {
#ifdef HOLO_MAP_MULTITHREADS
        std::lock_guard<std::mutex> lock(this->mutex_);
#endif

        typename TypeHashmap::const_iterator itr = hashmap_.find(_key);
        if (itr != hashmap_.end())
        {
            return true;
        }

        // If not work with local database, Memcache is just a memory cache, will not
        // read real database.
        if (!this->read_local_db_)
        {
            return false;
        }

        if (nullptr == this->db_)
        {
            return false;
        }

        return this->db_->Exist(_key);
    }

    /**
     * @brief remove an element
     *
     * @param[in] _key TypeKey
     * @param[in] _lock If true, lock the mutex.
     * @param[in] _sync If true, try to sync the this->hashmap_ and this->keys_;
                        otherwise the caller should sync the this->keys_ manually.
     */
    void RemoveElement(const TypeKey& _key, const holo::bool_t _lock = true, const holo::bool_t _sync = true)
    {
#ifdef HOLO_MAP_MULTITHREADS
        if (_lock)
        {
            mutex_.lock();
        }
#else
        (void)_lock;
#endif
        
        typename TypeHashmap::const_iterator it = this->hashmap_.find(_key);
        if (it != this->hashmap_.end())
        {
            this->hashmap_.erase(it);
        }
        
        // If not works with [Unlimited] mode, we should update Keys_, sync all the elements
        // both in this->hashmap_ and this->keys_.
        if (_sync && !this->isUnlimitedMode())
        {
            auto iterator = std::find(this->keys_.cbegin(), this->keys_.cend(), _key);
            if (this->keys_.cend() != iterator)
            {
                this->keys_.erase(iterator);
            }
        }

#ifdef SHOW_DEBUG_MESSAGE_MAP_MEMCACHE_INTERNAL_USE_ONLY
        ShowCache();
#endif

#ifdef HOLO_MAP_MULTITHREADS
        if (_lock)
        {
            this->mutex_.unlock();
        }
#endif
    }

    /**
     * @brief pop the front element
     *
     * @note PopElement only support [Limited] mode, if Memcache work with [Unlimited] mode,
     *       this function will do nothing.
     * @param[in] _lock If true, lock the mutex.
     */
    void PopElement(const holo::bool_t _lock = true)
    {
#ifdef HOLO_MAP_MULTITHREADS
        if (_lock)
        {
            this->mutex_.lock();
        }
#else
        (void)_lock;
#endif

        // If Memecache works with [Unlimited] mode, this->keys_ is empty.
        if (!this->isUnlimitedMode())
        {
            const TypeKey& front_key = this->keys_.front();
            this->RemoveElement(front_key, false, false);
            this->keys_.pop_front();
        }

#ifdef SHOW_DEBUG_MESSAGE_MAP_MEMCACHE_INTERNAL_USE_ONLY
        ShowCache();
#endif

#ifdef HOLO_MAP_MULTITHREADS
        if (_lock)
        {
            this->mutex_.unlock();
        }
#endif
    }

    /**
     * @brief push an element in front
     *
     * @param[in] _pointer_to_data  pointer to data
     * @param[in] _lock If true, lock the mutex.
     * @return true if push success
     * @return false otherwise
     */
    holo::bool_t PushElement(TypeDataPointer& _pointer_to_data, const holo::bool_t _lock = true)
    {
        if (nullptr == _pointer_to_data)
        {
            LOG(ERROR) << "PushElement fail, invalid parameter";
            return false;
        }

#ifdef HOLO_MAP_MULTITHREADS
        if (_lock)
        {
            this->mutex_.lock();
        }
#else
        (void)_lock;
#endif

        if (this->hashmap_.size() >= this->max_size_)
        {
            // If use local db, the memache(500) is enough for manage data.
            if (!this->read_local_db_)
            {
                LOG(ERROR) << "PushElement fail, out of range, type=" << static_cast<int>(_pointer_to_data->GetFeatureType())
                           << " name=" << _pointer_to_data->GetClassName() << " key=" << _pointer_to_data->GetPrimaryKey()
                           << " size=" << this->keys_.size() << " max_size=" << this->max_size_;

#ifdef HOLO_MAP_MULTITHREADS
                if (_lock)
                {
                    this->mutex_.unlock();
                }
#endif
                return false;
            }
            this->PopElement(false);
        }

        auto it = this->hashmap_.find(_pointer_to_data->GetPrimaryKey());
        if (this->hashmap_.cend() == it && !this->isUnlimitedMode())
        {
            // The this->keys_ only work with [Limited] mode, if under [Unlimited] mode, the this->keys_
            // will do nothing.
            this->keys_.push_back(_pointer_to_data->GetPrimaryKey());
        }

        // Even if an element already existed, we must replace it, because the element
        // may has beed updated.
        this->hashmap_[_pointer_to_data->GetPrimaryKey()] = _pointer_to_data;

#ifdef SHOW_DEBUG_MESSAGE_MAP_MEMCACHE_INTERNAL_USE_ONLY
        ShowCache();
#endif
        const holo::bool_t rtn = (this->isUnlimitedMode() || (this->keys_.size() == this->hashmap_.size()));

#ifdef HOLO_MAP_MULTITHREADS
        if (_lock)
        {
            this->mutex_.unlock();
        }
#endif
        return rtn;
    }

    /**
     * @brief Get target element from memcache, if it not in memcache, read it
     *        from database and cache it.
     *
     * @note If the target element neither in memcache nor in database actually,
     *       this function will return false.
     * @param[in] _key typekey
     * @param[in,out] _pointer_to_data Target data object should be allocated 
     *                outside of this function.
     * @return true if get the element
     * @return false otherwise
     */
    holo::bool_t GetElement(TypeKey const& _key, TypeDataPointer& _pointer_to_data)
    {
        holo::bool_t valid = false;
        holo::bool_t const ok = this->GetElementV2(_key, _pointer_to_data, valid);
        return ok && valid;
    }

    /**
     * @brief Get target element from memcache, if it not in memcache, read it
     *        from database and cache it.
     *
     * @note If the target element neither in memcache nor in database actually,
     *       this function will return true, but _valid will be set false.
     * @param[in] _key typekey
     * @param[in,out] _pointer_to_data Target data object should be allocated 
     *                outside of this function.
     * @return true No error, but if the target element is not existence actually,
     *              _valid will be false.
     * @return false An error occurs in this function.
     */
    holo::bool_t GetElementV2(TypeKey const & _key, TypeDataPointer& _pointer_to_data, bool& _valid)
    {
        _valid = false;

#ifdef HOLO_MAP_MULTITHREADS
        std::lock_guard<std::mutex> lg(mutex_);
#endif

        typename TypeHashmap::const_iterator itr = hashmap_.find(_key);
        if (itr != hashmap_.end())
        {
            _valid = true;
            _pointer_to_data = (*itr).second;
#ifdef SHOW_DEBUG_MESSAGE_MAP_MEMCACHE_INTERNAL_USE_ONLY
            ShowCache();
#endif
            return true;
        }
        else if (this->read_local_db_)
        {
            if (nullptr == db_)
            {
                LOG(ERROR) << "GetElement fail, invalid database handle, key=" << _key;
                return false;
            }

            if (!db_->ReadV2(_key, _pointer_to_data, _valid))
            {
                LOG(ERROR) << "GetElement fail, ReadV2 fail, key=" << _key;
                return false;
            }

            if (!_valid)
            {
                return true;
            }

            if (!this->PushElement(_pointer_to_data, false))
            {
                LOG(WARNING) << "GetElement fail, PushElement fail, key=" << _key;
            }
            return true;
        }

        // If the memcache doesn't work with local database, this function should return true,
        // if an element not exist in cache
        return true;
    }

    /**
     * @brief Get the cached data ids object
     *
     * @param ids vector of typekey id
     * @return true if get
     * @return false otherwise
     */
    holo::bool_t GetCachedDataIds(std::vector<TypeKey>& _ids)
    {
        _ids.clear();

#ifdef HOLO_MAP_MULTITHREADS
        std::lock_guard<std::mutex> lg(mutex_);
#endif
        _ids.reserve(this->hashmap_.size());
        for (typename TypeHashmap::const_iterator itr = hashmap_.begin();
             itr != hashmap_.end(); ++itr)
        {
            _ids.push_back((*itr).first);
        }
        return !_ids.empty();
    }

private:
    /**
     * @brief open physical database
     *
     * @param _data_db_path data db path
     * @return true if open success
     * @return false otherwise
     */
    holo::bool_t OpenDatabase(const char* _data_db_path)
    {
        if (access(_data_db_path, F_OK))
        {
            LOG(WARNING) << "OpenDatabase warning, this file does not exist. path: " << _data_db_path;
            db_ = nullptr;
            return false;
        }
        db_ = std::make_shared<SQLiteDB<TypeData> >();
        return db_->Open(_data_db_path);
    }
    /**
     * @brief close physical database
     *
     * @return true if close success
     * @return false otherwise
     */
    holo::bool_t CloseDatabase()
    {
        if (db_ == nullptr)
        {
            return true;
        }
        return db_->Close();
    }

private:

#ifdef SHOW_DEBUG_MESSAGE_MAP_MEMCACHE_INTERNAL_USE_ONLY
    /**
     * @brief show cache
     *
     */
    void ShowCache()
    {
        std::cout << "----------------------------------------------------------------" << std::endl;
        for (typename TypeHashmap::const_iterator itr = hashmap_.begin();
             itr != hashmap_.end(); ++itr)
        {
            std::cout << "id = " << (*itr).first
                      << " count =" << (*itr).second.use_count() << std::endl;
        }
    }
#endif

    /**
     * @brief Check if the memory cache is in Unlimited mode.
     *
     * @details If memory cache work with [Unlimited] mode, we will not pop element automatically,
     *          the cache should be mangered by user. So in [Unlimited] mode, the keys_(inner member)
     *          will not be used.
     * @return
     */
    holo::bool_t isUnlimitedMode() const noexcept
    {
        return MAX_MEM_CACHE_CAPACITY == this->max_size_;
    }

private:
    SizeType max_size_ = 0;
    
    TypeHashmap                         hashmap_;
    std::deque<TypeKey>                 keys_;
    std::shared_ptr<SQLiteDB<TypeData>> db_ = nullptr;

    /// If true, we will read data from local database(Holo NDS sqlite database),
    /// Otherwise, we will reture false directly when the target object is not in the memcache.
    holo::bool_t read_local_db_ = false; 

#ifdef HOLO_MAP_MULTITHREADS
    std::mutex mutex_;
#endif
};

}  ///< namespace map
}  ///< namespace holo

#endif /* HOLO_MAP_RETRIEVER_MEMCACHE_H_ */