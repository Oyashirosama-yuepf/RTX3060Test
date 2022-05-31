#include <holo/os/shared_memory_block.h>
#include <holo/os/utils.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h> /* For O_* constants */
#include <signal.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

namespace holo
{
namespace os
{
SharedMemoryBlockBase::SharedMemoryBlockBase(std::string const& name) noexcept : header_{nullptr}, name_{name}, pid_{0}
{
    pid_ = holo::os::Utils::GetPid();
}

SharedMemoryBlockBase::~SharedMemoryBlockBase() noexcept
{
    Destroy();
}

void SharedMemoryBlockBase::Destroy()
{
    if (header_)
    {
        holo::uint32_t size = sizeof(Header) + sizeof(ChunkHeader) * header_->block_count +
                              header_->block_capacity * header_->block_count;
        munmap(header_, size);
        shm_unlink(name_.c_str());
        header_ = nullptr;
    }
}

std::string SharedMemoryBlockBase::GetName() const noexcept
{
    return name_;
}

holo::uint32_t SharedMemoryBlockBase::GetBlockCount()
{
    if (nullptr == header_ && !tryOpen(true))
    {
        return 0U;
    }

    return header_->block_count;
}

holo::uint32_t SharedMemoryBlockBase::GetBlockDataCapacity()
{
    if (nullptr == header_ && !tryOpen(true))
    {
        return 0U;
    }

    return header_->block_capacity;
}

void SharedMemoryBlockBase::create(holo::uint32_t const block_capacity, holo::uint32_t const block_count)
{
    if (0U == block_capacity || 0U == block_count)
    {
        std::string error_info = GetName();
        error_info += "  block_capacity:";
        error_info += std::to_string(GetBlockDataCapacity());
        error_info += "  block_count:";
        error_info += std::to_string(GetBlockCount());
        error_info += "  block_capacity & block_count Must be greater than 0";
        throw BlockSizeException{error_info};
    }

    holo::int32_t fd = shm_open(name_.c_str(), O_RDWR, 0666);
    if (fd > 0)
    {
        close(fd);
        return;
    }

    fd = shm_open(name_.c_str(), O_CREAT | O_RDWR, 0666);
    if (fd < 0)
    {
        std::string error_info = name_;
        error_info += "  open this file error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    holo::uint32_t size = sizeof(Header) + sizeof(ChunkHeader) * block_count + block_capacity * block_count;
    holo::int32_t  ret  = ftruncate(fd, size);
    if (ret < 0)
    {
        close(fd);
        std::string error_info = name_;
        error_info += "  ftruncate error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    struct stat st;
    if ((fstat(fd, &st)) == -1)
    {
        close(fd);
        std::string error_info = name_;
        error_info += "  fstat failed!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    if (st.st_size < size)
    {
        close(fd);
        std::string error_info = name_;
        error_info += "  failed to validate shm size!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    void* addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, SEEK_SET);
    if (nullptr == addr)
    {
        close(fd);
        std::string error_info = name_;
        error_info += "  mmap error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    close(fd);

    memset(addr, 0, size);
    Header* header = static_cast<Header*>(addr);
    initHeader(header, block_capacity, block_count);
    initChunkHeader(header);

    munmap(addr, size);
}

void SharedMemoryBlockBase::open(holo::bool_t const read_only)
{
    holo::int32_t fd = shm_open(name_.c_str(), O_RDWR, 0666);
    if (fd < 0)
    {
        std::string error_info = name_;
        error_info += "  open this file error!";
        error_info += strerror(errno);
        throw UninitializedException{error_info};
    }

    struct stat st;
    if ((fstat(fd, &st)) == -1)
    {
        close(fd);
        std::string error_info = name_;
        error_info += "  fstat failed!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    void* addr = nullptr;
    if (read_only)
    {
        addr = mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, SEEK_SET);
    }
    else
    {
        addr = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, SEEK_SET);
    }

    if (nullptr == addr)
    {
        close(fd);
        std::string error_info = name_;
        error_info += "  mmap failed!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    close(fd);

    Header* header = static_cast<Header*>(addr);
    if (!checkFlag(header))
    {
        munmap(header, st.st_size);
        shm_unlink(name_.c_str());

        std::string error_info = name_;
        error_info += "  This is NOT a SharedMemoryBlockBase format file!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    if (!read_only)
    {
        becomeOwner(header);
    }

    header_ = header;
}

SharedMemoryBlockBase::ChunkHeader* SharedMemoryBlockBase::getChunkHeader(holo::uint32_t const index)
{
    if (nullptr == header_ && !tryOpen(true))
    {
        return nullptr;
    }

    return getChunkHeader(header_, index);
}

holo::uint8_t* SharedMemoryBlockBase::getChunkData(holo::uint32_t const index)
{
    if (nullptr == header_ && !tryOpen(true))
    {
        return nullptr;
    }

    return getChunkData(header_, index);
}

holo::bool_t SharedMemoryBlockBase::tryOpen(holo::bool_t const read_only)
{
    try
    {
        open(read_only);
    }
    catch (UninitializedException const& e)
    {
        return false;
    }

    return true;
}

void SharedMemoryBlockBase::initHeader(Header* header, holo::uint32_t const block_capacity,
                                       holo::uint32_t const block_count)
{
    becomeOwner(header);

    holo::char_t const* flag = SHARED_MEMORY_BLOCK_FLAG;
    strncpy(header->flag, flag, BLOCK_FLAG_SIZE);

    header->start          = sizeof(Header) + sizeof(ChunkHeader) * block_count;
    header->block_capacity = block_capacity;
    header->block_count    = block_count;
}

void SharedMemoryBlockBase::initChunkHeader(Header* header)
{
    for (holo::uint32_t i = 0U; i < header->block_count; ++i)
    {
        ChunkHeader* chunk_header  = getChunkHeader(header, i);
        chunk_header->data_size    = 0U;
        chunk_header->data_version = 0U;
    }
}

SharedMemoryBlockBase::ChunkHeader* SharedMemoryBlockBase::getChunkHeader(Header* header, holo::uint32_t const index)
{
    if (index >= header->block_count)
    {
        throw holo::exception::OutOfRangeException{
            "SharedMemoryBlockBase::getChunkHeader failed! index is out of range!"};
    }

    return reinterpret_cast<ChunkHeader*>(reinterpret_cast<holo::uint8_t*>(header) + sizeof(Header) +
                                          sizeof(ChunkHeader) * index);
}

holo::uint8_t* SharedMemoryBlockBase::getChunkData(Header* header, holo::uint32_t const index)
{
    if (index >= header->block_count)
    {
        throw holo::exception::OutOfRangeException{"SharedMemoryBlockBase::get chunk failed! index is out of range!"};
    }

    return (reinterpret_cast<holo::uint8_t*>(header) + header->start + header->block_capacity * index);
}

holo::bool_t SharedMemoryBlockBase::checkFlag(Header* header) const
{
    return (0 == strncmp(header->flag, SHARED_MEMORY_BLOCK_FLAG, BLOCK_FLAG_SIZE));
}

void SharedMemoryBlockBase::becomeOwner(Header* header)
{
    if (header->owner_pid > 0U && header->owner_pid != static_cast<holo::uint32_t>(pid_) &&
        isProcessAlive(header->owner_pid))
    {
        throw OwnershipException{"SharedMemoryBlockBase::becomeOwner failed! Writer already exists!"};
    }

    header->owner_pid = pid_;
}

holo::bool_t SharedMemoryBlockBase::isProcessAlive(holo::uint32_t const pid) const
{
    return !kill(pid, 0);
}

SharedMemoryBlockWriter::SharedMemoryBlockWriter(std::string const& name) noexcept : SharedMemoryBlockBase{name}
{
}

void SharedMemoryBlockWriter::Init(holo::uint32_t const block_capacity, holo::uint32_t const block_count)
{
    create(block_capacity, block_count);

    open(false);

    if (block_capacity != GetBlockDataCapacity() || block_count != GetBlockCount())
    {
        std::string error_info = GetName();
        error_info += "  already exists! block_capacity:";
        error_info += std::to_string(GetBlockDataCapacity());
        error_info += "  block_count:";
        error_info += std::to_string(GetBlockCount());
        error_info += "  your expectations:";
        error_info += "  block_capacity:";
        error_info += std::to_string(block_capacity);
        error_info += "  block_count:";
        error_info += std::to_string(block_count);
        throw BlockSizeException{error_info};
    }
}

holo::uint32_t SharedMemoryBlockWriter::Write(holo::uint8_t const* data, holo::uint32_t const data_size,
                                              holo::uint32_t const index)
{
    assert(nullptr != data && data_size > 0U);

    ChunkHeader*   chunk_header = getChunkHeader(index);
    holo::uint8_t* chunk_data   = getChunkData(index);

    holo::uint32_t chunk_size = GetBlockDataCapacity();
    if (data_size > chunk_size)
    {
        std::string error_info = "data size too big! data_size:";
        error_info += std::to_string(data_size);
        error_info += "  block_capacity:";
        error_info += std::to_string(chunk_size);
        throw BlockSizeException{error_info};
    }

    chunk_header->data_version++;

    memcpy(chunk_data, data, data_size);
    chunk_header->data_size = data_size;

    return data_size;
}

holo::uint32_t SharedMemoryBlockWriter::Write(holo::uint32_t& data_version, holo::uint8_t const* data,
                                              holo::uint32_t const data_size, holo::uint32_t const index)
{
    assert(nullptr != data && data_size > 0U);

    ChunkHeader*   chunk_header = getChunkHeader(index);
    holo::uint8_t* chunk_data   = getChunkData(index);

    holo::uint32_t chunk_size = GetBlockDataCapacity();
    if (data_size > chunk_size)
    {
        std::string error_info = "data size too big! data_size:";
        error_info += std::to_string(data_size);
        error_info += "  block_capacity:";
        error_info += std::to_string(chunk_size);
        throw BlockSizeException{error_info};
    }

    chunk_header->data_version++;

    memcpy(chunk_data, data, data_size);
    chunk_header->data_size = data_size;
    data_version            = chunk_header->data_version;

    return data_size;
}

holo::uint8_t* SharedMemoryBlockWriter::GetBlockData(holo::uint32_t const index)
{
    return getChunkData(index);
}

holo::uint32_t SharedMemoryBlockWriter::GetBlockDataSize(holo::uint32_t const index)
{
    ChunkHeader* chunk_header = getChunkHeader(index);

    return chunk_header->data_size;
}

void SharedMemoryBlockWriter::SetBlockDataSize(holo::uint32_t const size, holo::uint32_t const index)
{
    ChunkHeader* chunk_header = getChunkHeader(index);

    chunk_header->data_size = size;
}

holo::uint32_t SharedMemoryBlockWriter::GetBlockDataVersion(holo::uint32_t const index)
{
    ChunkHeader* chunk_header = getChunkHeader(index);

    return chunk_header->data_version;
}

void SharedMemoryBlockWriter::UpdateBlockDataVersion(holo::uint32_t const index)
{
    ChunkHeader* chunk_header = getChunkHeader(index);

    chunk_header->data_version++;
}

SharedMemoryBlockReader::SharedMemoryBlockReader(std::string const& name) noexcept : SharedMemoryBlockBase{name}
{
}

holo::uint32_t SharedMemoryBlockReader::Read(holo::uint8_t* buffer, holo::uint32_t const buffer_size,
                                             holo::uint32_t const index)
{
    assert(nullptr != buffer && buffer_size > 0U);

    ChunkHeader* chunk_header = getChunkHeader(index);
    if (nullptr == chunk_header)
    {
        return 0U;
    }

    holo::uint8_t* chunk_data = getChunkData(index);
    if (nullptr == chunk_data)
    {
        return 0U;
    }

    holo::uint32_t data_size = chunk_header->data_size;
    if (0U == data_size)
    {
        return 0U;
    }

    if (buffer_size < data_size)
    {
        std::string error_info = "buffer size too small! buffer_size:";
        error_info += std::to_string(buffer_size);
        error_info += "  data_size:";
        error_info += std::to_string(data_size);
        throw BlockSizeException{error_info};
    }

    memcpy(buffer, chunk_data, data_size);

    return data_size;
}

holo::uint32_t SharedMemoryBlockReader::Read(holo::uint8_t* buffer, holo::uint32_t const buffer_size,
                                             holo::uint32_t const index, holo::uint32_t const expected_version)
{
    assert(nullptr != buffer && buffer_size > 0U);

    ChunkHeader* chunk_header = getChunkHeader(index);
    if (nullptr == chunk_header)
    {
        return 0U;
    }

    holo::uint8_t* chunk_data = getChunkData(index);
    if (nullptr == chunk_data)
    {
        return 0U;
    }

    if (expected_version != chunk_header->data_version)
    {
        std::string error_info = "data version different!!! ";
        error_info += "  data version:";
        error_info += std::to_string(chunk_header->data_version);
        error_info += "  expected version:";
        error_info += std::to_string(expected_version);
        throw DataVersionException{error_info};
    }

    holo::uint32_t data_size = chunk_header->data_size;
    if (0U == data_size)
    {
        return 0U;
    }

    if (buffer_size < data_size)
    {
        std::string error_info = "buffer size too small! buffer_size:";
        error_info += std::to_string(buffer_size);
        error_info += "  data_size:";
        error_info += std::to_string(data_size);
        throw BlockSizeException{error_info};
    }

    memcpy(buffer, chunk_data, data_size);

    if (expected_version != chunk_header->data_version)
    {
        std::string error_info = "data version different!!! ";
        error_info += "  data version:";
        error_info += std::to_string(chunk_header->data_version);
        error_info += "  expected version:";
        error_info += std::to_string(expected_version);
        throw DataVersionException{error_info};
    }

    return data_size;
}

holo::uint8_t const* SharedMemoryBlockReader::GetBlockData(holo::uint32_t const index)
{
    return getChunkData(index);
}

holo::uint32_t SharedMemoryBlockReader::GetBlockDataSize(holo::uint32_t const index)
{
    ChunkHeader* chunk_header = getChunkHeader(index);
    if (chunk_header)
    {
        return chunk_header->data_size;
    }
    else
    {
        return 0U;
    }
}

holo::uint32_t SharedMemoryBlockReader::GetBlockDataVersion(holo::uint32_t const index)
{
    ChunkHeader* chunk_header = getChunkHeader(index);
    if (chunk_header)
    {
        return chunk_header->data_version;
    }
    else
    {
        return 0U;
    }
}

}  // namespace os
}  // namespace holo
