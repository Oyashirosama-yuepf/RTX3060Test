/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file reader.h
 * @brief Reader interface.
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-12"
 */

#ifndef HOLO_MAP_SERVICE_IO_READER_H_
#define HOLO_MAP_SERVICE_IO_READER_H_

#include <memory>
#include <queue>
#include <sstream>
#include <string>

#include <holo/log/hololog.h>
#include <holo/map/common/classes/auto_spin_mutex.h>
#include <holo/map/service/io/io_rw.h>

namespace holo
{
namespace map
{
namespace service
{
namespace io
{

/**
 * @addtogroup io
 * @{
 *
 */

/**
 * @brief Reader interface.
 */
class ReaderBase : virtual public IORW
{
public:
    /// Redefine inner type for DataPackage pointer.
    using DataPackagePtrType    = IOBase::DataPackageType*;

    /// Redefine middle buffer type for message cache.
    using ContainerType     = std::vector<holo::uint8_t>;
    using BufferType        = ContainerType*;
    using BufferSizeType    = ContainerType::size_type;

    /**
     * @brief Constructor.
     */
    ReaderBase() : IORW()
    {
        this->buffer_capacity_ = this->max_protocol_capacity_;
        this->buffer_ = new RawBufferValueType[this->buffer_capacity_];
    }

    /**
     * @brief Destructor.
     */
    virtual ~ReaderBase()
    {
        this->raw_reader_counter_ = 0;
        this->real_reader_counter_ = 0;
        
        delete [] this->buffer_;
        this->buffer_ = nullptr;

        this->releaseDataPackages();
    }

    ReaderBase(ReaderBase const&) = delete;
    ReaderBase(ReaderBase&&) = delete;
    ReaderBase& operator = (ReaderBase const&) = delete;
    ReaderBase& operator = (ReaderBase&&) = delete;

    /**
     * @brief Access the reader status info.
     * 
     * @return Status info with json format.
     */
    virtual std::string Status() override
    {
        std::size_t busy_package_queue_size = 0;
        std::size_t free_package_queue_size = 0;

        {
            holo::map::AutoSpinMutex lock(this->package_queue_mutex_);
            busy_package_queue_size = this->busy_package_queue_.size();
            free_package_queue_size = this->free_package_queue_.size();
        }

        std::stringstream stream;
        {
            stream << "{\"busy_package_queue_size\":" << busy_package_queue_size
                   << ", \"free_package_queue_size\":" << free_package_queue_size
                   << ", \"raw_reader_counter\":" << this->raw_reader_counter_
                   << ", \"real_reader_counter\":" << this->real_reader_counter_
                   << ", \"token_id\":" << this->token_id_
                   << "}";
        }
        return stream.str();
    }

    /**
     * @brief Read session data from current cache, if no valid session, empty flag will true.
     * 
     * @note If the second output(empty) is true, we should stop calling this function, if it is
     *       false, the inner cache maybe have many ready sessions, we should try to call it again.
     *       
     * @param[out] session Session object, if the inner cache is not empty, it will be set valid data.
     * @param[out] empty A flag for the output session, if the session is valid, it will be false.
     */
    virtual void Read(DataPackageType& package, holo::bool_t& empty)
    {
        package.Clear();
        empty = true;
        this->readFromLocal(package, empty);
        return;
    }

    /**
     * @brief Release free buffer by size.
     * 
     * @param[in] size A size for release free buffer.
     */
    virtual void ReleaseFreeBuffer(std::size_t const size)
    {
        holo::map::AutoSpinMutex lock(this->package_queue_mutex_);
        std::size_t count = 0;
        while (count < size && !this->free_package_queue_.empty())
        {
            DataPackagePtrType ptr = this->free_package_queue_.front();
            this->free_package_queue_.pop();
            delete ptr;
            ++count;
        }
    }

    /**
     * @brief Get free buffer size.
     * 
     * @return Free buffer size.
     */
    virtual std::size_t GetFreeBufferSize()
    {
        holo::map::AutoSpinMutex lock(this->package_queue_mutex_);
        return this->free_package_queue_.size();
    }

    /**
     * @brief Get busy buffer size.
     * 
     * @return Busy buffer size.
     */
    virtual std::size_t GetBusyBufferSize()
    {
        holo::map::AutoSpinMutex lock(this->package_queue_mutex_);
        return this->busy_package_queue_.size();
    }

protected:
    /**
     * @brief AddData to DataPackage and cache the DataPackage pointer.
     * 
     * @param[in] buffer DataPackage buffer.
     * @param[in] size Buffer size.
     */
    void CallbackRawBufferDirectToDataPackage(RawBufferConstType buffer, RawBufferSizeType const size)
    {
        if (size > this->max_package_capacity_ || size <= 0)
        {
            LOG(ERROR) << "ReaderBase::CallbackDataPackage fail, un-expected package,"
                       << " size=" << size << " capacity=" << this->max_package_capacity_;
            return;
        }

        DataPackagePtrType ptr = this->getDataPackage();

        // direct store ehp raw package in datapackage
        ptr->Clear();
        ptr->AddData(0, 
                    IOBase::DataPackageType::ItemStatusType::STATUS_OK, 
                    IOBase::DataPackageType::FeatureType::TYPE_UNKNOWN,
                    buffer, size);

        if (this->verbose_)
        {
            LOG(INFO) << "ReaderBase::CallbackDataPackage debug, package_size=" << size
                      << " token_id=" << ptr->GetTokenId()  << " sequence_id=" << ptr->GetSequenceId()
                      << " item_count=" << ptr->GetCount() << " data_size=" << ptr->GetDataSize()
                      << " raw_reader_counter=" << this->raw_reader_counter_
                      << " real_reader_counter=" << this->real_reader_counter_;
        }

        this->setDataPackage(ptr, true);
    }

    /**
     * @brief Deserialize DataPackage and cache the DataPackage pointer.
     * 
     * @param[in] buffer DataPackage buffer.
     * @param[in] size Buffer size.
     */
    void CallbackDataPackage(RawBufferConstType buffer, RawBufferSizeType const size)
    {
        if (size > this->max_package_capacity_ || size <= 0)
        {
            LOG(ERROR) << "ReaderBase::CallbackDataPackage fail, un-expected package,"
                       << " size=" << size << " capacity=" << this->max_package_capacity_;
            return;
        }

        DataPackagePtrType ptr = this->getDataPackage();

        holo::serialization::Deserializer<true, 1> deserializer(buffer, size);
        ptr->Deserialize(deserializer);

        if (this->verbose_)
        {
            LOG(INFO) << "ReaderBase::CallbackDataPackage debug, package_size=" << size
                      << " token_id=" << ptr->GetTokenId()  << " sequence_id=" << ptr->GetSequenceId()
                      << " item_count=" << ptr->GetCount() << " data_size=" << ptr->GetDataSize()
                      << " raw_reader_counter=" << this->raw_reader_counter_
                      << " real_reader_counter=" << this->real_reader_counter_;
        }

        this->setDataPackage(ptr, true);
    }

private:
    /**
     * @brief Get or create a DataPackage pointer.
     * 
     * @return DataPackage Pointer.
     */
    DataPackagePtrType getDataPackage()
    {
        DataPackagePtrType ptr = nullptr;
        {
            holo::map::AutoSpinMutex guard(this->package_queue_mutex_);
            if (this->free_package_queue_.empty())
            {
                ptr = new DataPackageType();
            }
            else
            {
                ptr = this->free_package_queue_.front();
                this->free_package_queue_.pop();
            }
        }
        return ptr;
    }

    /**
     * @brief Put DataPackage pointer back to free or busy queue.
     * 
     * @param[in] ptr DataPackage pointer.
     * @param[in] valid If true, put the pointer into busy queue.
     *                  If false, put the pointer into free queue.
     */
    void setDataPackage(DataPackagePtrType ptr, holo::bool_t const valid)
    {
        holo::map::AutoSpinMutex lock(this->package_queue_mutex_);
        if (valid)
        {
            this->busy_package_queue_.push(ptr);
        }
        else
        {
            this->free_package_queue_.push(ptr);
        }

        ++this->real_reader_counter_;
    }

    /**
     * @brief Release DataPackage and clear cache queue.
     */
    void releaseDataPackages()
    {
        holo::map::AutoSpinMutex lock(this->package_queue_mutex_);

        while (!this->busy_package_queue_.empty())
        {
            DataPackagePtrType ptr = this->busy_package_queue_.front();
            this->busy_package_queue_.pop();
            delete ptr;
        }

        while (!this->free_package_queue_.empty())
        {
            DataPackagePtrType ptr = this->free_package_queue_.front();
            this->free_package_queue_.pop();
            delete ptr;
        }
    }

    /**
     * @brief Get DataPackage from cache queue.
     * 
     * @param[in] package DataPackage object.
     * @param[in] empty If true, this DataPackage object is valid.
     */
    void readFromLocal(DataPackageType& package, holo::bool_t& empty)
    {
        empty = true;

        DataPackagePtrType ptr = nullptr;
        {
            holo::map::AutoSpinMutex guard(this->package_queue_mutex_);
            if (this->busy_package_queue_.empty())
            {
                empty = true;
                return;
            }
            ptr = this->busy_package_queue_.front();
            this->busy_package_queue_.pop();
        }

        package = *ptr;
        empty = false;

        {
            holo::map::AutoSpinMutex guard(this->package_queue_mutex_);
            this->free_package_queue_.push(ptr);
        }
    }

protected:
    /// Mutex for free and busy session buffer.
    holo::map::SpinMutex            package_queue_mutex_;
    /// All the new session data in this buffer.
    std::queue<DataPackagePtrType>  busy_package_queue_;
    /// All the dirty session data in this buffer.
    std::queue<DataPackagePtrType>  free_package_queue_;

    /// Data buffer for caching serialized DataPackage.
    RawBufferType               buffer_             = nullptr;
    /// The max capacity of data buffer.
    RawBufferSizeType           buffer_capacity_    = 0;

    /// Counter for reding messages from message queue.
    std::size_t                 raw_reader_counter_ = 0;
    /// Counter for reading datapackage from cache queue.
    std::size_t                 real_reader_counter_ = 0;
}; ///< End of class ReaderBase

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_READER_H_ */
