#ifndef HOLO_OS_SHARED_MEMORY_BLOCK_H
#define HOLO_OS_SHARED_MEMORY_BLOCK_H

#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

#include <string>

namespace holo
{
namespace os
{
class BlockSizeException : public holo::exception::RuntimeErrorException
{
public:
    explicit BlockSizeException(const std::string& what_arg) noexcept : holo::exception::RuntimeErrorException{what_arg}
    {
    }
};

class DataVersionException : public holo::exception::RuntimeErrorException
{
public:
    explicit DataVersionException(const std::string& what_arg) noexcept
      : holo::exception::RuntimeErrorException{what_arg}
    {
    }
};

class OwnershipException : public holo::exception::RuntimeErrorException
{
public:
    explicit OwnershipException(const std::string& what_arg) noexcept : holo::exception::RuntimeErrorException{what_arg}
    {
    }
};

class UninitializedException : public holo::exception::RuntimeErrorException
{
public:
    explicit UninitializedException(const std::string& what_arg) noexcept
      : holo::exception::RuntimeErrorException{what_arg}
    {
    }
};

/**
 * @brief 共享内存通知消息 配合SharedMemoryBlock使用
 *
 * 可以使用中间件holo_cmw把该消息发送出去，或者通过自定义的ipc发送出去
 */
struct SharedMemoryNotification
{
    static constexpr holo::int32_t BLOCK_NAME_MAX_LENGTH{128};

    holo::uint32_t block_index;
    holo::uint32_t block_version;
    holo::char_t   block_name[BLOCK_NAME_MAX_LENGTH];

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(block_index, block_version) +
               holo::serialization::AlignedSize<ALIGN>(sizeof(block_name));
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << block_index << block_version << holo::serialization::align;
        serializer.Write(block_name, sizeof(block_name));
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> holo::serialization::align >> block_index >> block_version >> holo::serialization::align;
        deserializer.Read(block_name, sizeof(block_name));
    }
};

/**
 * @brief 共享内存读写块, 数据结构是一个类似数组的结构, 内部不会提供读写同步机制
 *
 * 注意：同时只能有一个进程进行写入，多个进程同时写入，会抛出异常
 * 因为这里不提供读写同步机制
 * 同一进程内，多个线程写入，用户需要自己做好同步机制，避免数据出错
 *
 * 使用方法：
 * 写进程写入数据后，把写入的位置index告诉其他读进程（通过socket, opendds, pps等通知对方）
 * 读进程根据index，去读取对应位置的数据
 * 数据的时效性由写进程决定
 *
 * 读写函数都提供了data_version，来提供对数据版本的检测, 检测数据的有效性, 如果data_version不一致，说明数据被修改了
 *
 */

class SharedMemoryBlockBase
{
public:
    static constexpr holo::char_t const* SHARED_MEMORY_BLOCK_FLAG{"holo"};
    static constexpr holo::int32_t       BLOCK_FLAG_SIZE{4};
    static constexpr holo::int32_t       INVALID_BLOCK_ID{-1};

    explicit SharedMemoryBlockBase(std::string const& name) noexcept;
    virtual ~SharedMemoryBlockBase() noexcept;

    void Destroy();

    std::string    GetName() const noexcept;
    holo::uint32_t GetBlockCount();
    holo::uint32_t GetBlockDataCapacity();

protected:
    struct ChunkHeader
    {
        holo::uint32_t data_size;
        holo::uint32_t data_version;
    };

    void create(holo::uint32_t const block_capacity, holo::uint32_t const block_count);
    void open(holo::bool_t const read_only);

    ChunkHeader*   getChunkHeader(holo::uint32_t const index);
    holo::uint8_t* getChunkData(holo::uint32_t const index);

private:
    struct Header
    {
        holo::char_t   flag[BLOCK_FLAG_SIZE];
        holo::uint32_t owner_pid;
        holo::uint32_t start;
        holo::uint32_t block_capacity;
        holo::uint32_t block_count;
    };

    SharedMemoryBlockBase(SharedMemoryBlockBase const&) = delete;
    SharedMemoryBlockBase(SharedMemoryBlockBase&&)      = delete;
    SharedMemoryBlockBase& operator=(SharedMemoryBlockBase const&) = delete;
    SharedMemoryBlockBase& operator=(SharedMemoryBlockBase&&) = delete;

    holo::bool_t tryOpen(holo::bool_t const read_only);

    void           initHeader(Header* header, holo::uint32_t const block_capacity, holo::uint32_t const block_count);
    void           initChunkHeader(Header* header);
    ChunkHeader*   getChunkHeader(Header* header, holo::uint32_t const index);
    holo::uint8_t* getChunkData(Header* header, holo::uint32_t const index);
    holo::bool_t   checkFlag(Header* header) const;
    void           becomeOwner(Header* header);
    holo::bool_t   isProcessAlive(holo::uint32_t const pid) const;

private:
    Header*       header_;
    std::string   name_;
    holo::int32_t pid_;
};

class SharedMemoryBlockWriter : public SharedMemoryBlockBase
{
public:
    explicit SharedMemoryBlockWriter(std::string const& name) noexcept;

    /**
     * @brief If shared memory does not exist, create shared memory
     *
     * @param block_capacity
     * @param block_count
     */
    void Init(holo::uint32_t const block_capacity, holo::uint32_t const block_count);

    /**
     * @brief Use the memcpy() method to copy data into the shared memory buffer specified by index.
     * If the data size is larger than the shared memory buffer size, an BlockSizeException is thrown.
     *
     * @param in data
     * @param in data_size
     * @param in index  index start from 0
     *
     * @return  return the number of bytes successfully written
     */
    holo::uint32_t Write(holo::uint8_t const* data, holo::uint32_t const data_size, holo::uint32_t const index);

    /**
     * @brief Use the memcpy() method to copy data into the shared memory buffer specified by index, and the data
     * version number is saved in data_version.
     * If the data size is larger than the shared memory buffer size, an BlockSizeException is thrown.
     *
     * @param out data_version  return data_version
     * @param in  data
     * @param in  data_size
     * @param in  index  index start from 0
     *
     * @return  return the number of bytes successfully written
     */
    holo::uint32_t Write(holo::uint32_t& data_version, holo::uint8_t const* data, holo::uint32_t const data_size,
                         holo::uint32_t const index);

    holo::uint8_t* GetBlockData(holo::uint32_t const index);
    holo::uint32_t GetBlockDataSize(holo::uint32_t const index);
    void           SetBlockDataSize(holo::uint32_t const size, holo::uint32_t const index);
    holo::uint32_t GetBlockDataVersion(holo::uint32_t const index);
    void           UpdateBlockDataVersion(holo::uint32_t const index);
};

class SharedMemoryBlockReader : public SharedMemoryBlockBase
{
public:
    explicit SharedMemoryBlockReader(std::string const& name) noexcept;

    /**
     * @brief Use the memcpy() method to copy the shared memory data into the user's buffer
     *
     * @param out buffer
     * @param in  buffer_size
     * @param in  index  index start from 0
     *
     * @return  return the number of bytes successfully read
     */
    holo::uint32_t Read(holo::uint8_t* buffer, holo::uint32_t const buffer_size, holo::uint32_t const index);

    /**
     * @brief Use the memcpy() method to copy the shared memory data into the user's buffer and check the data version
     * number
     *
     * @param out buffer
     * @param in  buffer_size
     * @param in  index  index start from 0
     * @param in  expected_version  expected data version (if care)
     *
     * @return  return the number of bytes successfully read
     */
    holo::uint32_t Read(holo::uint8_t* buffer, holo::uint32_t const buffer_size, holo::uint32_t const index,
                        holo::uint32_t const expected_version);

    holo::uint8_t const* GetBlockData(holo::uint32_t const index);
    holo::uint32_t       GetBlockDataSize(holo::uint32_t const index);
    holo::uint32_t       GetBlockDataVersion(holo::uint32_t const index);
};

}  // namespace os
}  // namespace holo

#endif
