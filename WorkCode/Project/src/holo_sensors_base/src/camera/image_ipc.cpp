/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_ipc.cpp.
 * @brief Image IPC.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-04.
 */

#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <holo/sensors/camera/image_ipc.h>
#include <holo/sensors/camera/image_structure.h>

namespace holo
{
namespace sensors
{
namespace camera
{
ImageIpcBase::ImageIpcBase(uint32_t rows, uint32_t cols, Image::Encoding encoding) : cols_(cols), rows_(rows), encoding_(encoding), image_size_(0)
{
    if ((encoding_ == holo::Image::Encoding::RGB) || (encoding_ == holo::Image::Encoding::BGR))
    {
        image_size_ = cols * rows * 3;
    }
    else if (encoding_ == holo::Image::Encoding::GRAYSCALE)
    {
        image_size_ = cols * rows * 1;
    }
    else if ((encoding_ == holo::Image::Encoding::YUYV) || (encoding_ == holo::Image::Encoding::UYVY) ||
             (encoding_ == holo::Image::Encoding::YUV422P))
    {
        image_size_ = cols * rows * 2;
    }
    else if ((encoding_ == holo::Image::Encoding::YU12) || (encoding_ == holo::Image::Encoding::YV12) ||
             (encoding_ == holo::Image::Encoding::NV12) || (encoding_ == holo::Image::Encoding::NV21))
    {
        image_size_ = cols * rows * 1.5;
    }
    else if (encoding_ == holo::Image::Encoding::RGBA)
    {
        image_size_ = cols * rows * 4;
    }
    else
    {
        std::ostringstream oss;
        oss << "unsupported encoding type = " << static_cast<uint32_t>(encoding_);
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }
}

uint32_t ImageIpcBase::GetCols() const noexcept
{
    return cols_;
}
uint32_t ImageIpcBase::GetRows() const noexcept
{
    return rows_;
}
Image::Encoding ImageIpcBase::GetEncoding() const noexcept
{
    return encoding_;
}
uint32_t ImageIpcBase::GetImageSize() const noexcept
{
    return image_size_;
}

void ImageIpc::OpenShmFd()
{
    /* create a new memory object */
    fd_ = shm_open(shmem_name_.c_str(), O_CREAT | O_RDWR, 0666);
    if (fd_ == -1)
    {
        std::string error = "failed to open share memory";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    /* set the memory object's size */
    struct stat shm_stat1;
    if (0 != fstat(fd_, &shm_stat1))
    {
        std::string error = "failed to get share memory status";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    if (shm_stat1.st_size == 0)
    {
        if (ftruncate(fd_, shmem_size_))
        {
            std::string error = "failed to set share memory size";
            LOG(INFO) << error << ": " << strerror(errno);
            throw std::runtime_error(error);
        }
    }
    /* check size */
    struct stat shm_stat2;
    if (0 != fstat(fd_, &shm_stat2))
    {
        std::string error = "failed to get share memory status";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    if (shm_stat2.st_size < shmem_size_)
    {
        std::string error = "failed to validate shm size";
        LOG(INFO) << error << ": " << shm_stat2.st_size << ", assert value: " << shmem_size_;
        throw std::runtime_error(error);
    }
}

ImageIpc::ImageIpc(SensorId sensor_id) : ImageIpcBase(0, 0, Image::Encoding::RGB)
 , shmem_size_(OFFSET + sizeof(holo::common::Timestamp) * 2 + sizeof(Image::Encoding) + image_size_)
 , fd_(-1)
 , shm_sem_(nullptr)
 , shm_data_(nullptr)
{
    std::string shmem_name("cam." + std::to_string(static_cast<uint32_t>(sensor_id)));
    /* create a new memory object */
    int fd0 = shm_open(shmem_name.c_str(), O_RDONLY, 0666);
    if (fd0 == -1)
    {
        std::string error = "failed to open share memory: " + shmem_name;
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    /* check size */
    const size_t shm_header_size = 33;  // 33 = 12 + 4 + 8 + 8 + 1
    struct stat  shm_stat2;
    if (0 != fstat(fd0, &shm_stat2))
    {
        (void)close(fd0);
        std::string error = "failed to get share memory status";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    if (shm_stat2.st_size < static_cast<int32_t>(shm_header_size))
    {
        (void)close(fd0);
        std::string error = "failed to validate shm size";
        LOG(INFO) << error << ": " << shm_stat2.st_size << ", assert more than " << shm_header_size;
        throw std::runtime_error(error);
    }
    /* map the memory object */
    void* shm_data = mmap(0, shm_header_size, PROT_READ, MAP_SHARED, fd0, 0);
    if (shm_data == MAP_FAILED)
    {
        (void)close(fd0);
        std::string error = "failed to map share memory";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    uint32_t        rows     = static_cast<uint32_t*>(shm_data)[1];
    uint32_t        cols     = static_cast<uint32_t*>(shm_data)[2];
    Image::Encoding encoding = static_cast<Image::Encoding>(static_cast<uint8_t*>(shm_data)[32]);
    (void)munmap(shm_data, shm_header_size);
    (void)close(fd0);
    
    (void)new(this) ImageIpc(sensor_id, rows, cols, encoding);
    
    LOG(INFO) << "image ipc client info: size=" << rows << "x" << cols
              << ", encoding=" << static_cast<uint32_t>(encoding);
}

ImageIpc::ImageIpc(SensorId sensor_id, uint32_t rows, uint32_t cols, Image::Encoding encoding)
  : ImageIpcBase(rows, cols, encoding)
  , sensor_id_(sensor_id)
  , shmem_size_(OFFSET + sizeof(holo::common::Timestamp) * 2 + sizeof(Image::Encoding) + image_size_)
  , fd_(-1)
  , shm_sem_(nullptr)
  , shm_data_(nullptr)
  , shsem_name_(std::to_string(static_cast<uint32_t>(sensor_id_)))
  , shmem_name_("cam." + std::to_string(static_cast<uint32_t>(sensor_id_)))
{
    /* mutex for safety */
    shm_sem_ = sem_open(shsem_name_.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, 1);
    if (!shm_sem_)
    {
        std::string error = "failed to open semaphore of share memory";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }

    OpenShmFd();

    /* map the memory object */
    shm_data_ = mmap(0, shmem_size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
    if (shm_data_ == MAP_FAILED)
    {
        std::string error = "failed to map share memory";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    /* x */
    if (sem_wait(shm_sem_) == -1)
    {
        std::string error = "failed to wait shm semaphore";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    const uint32_t init_data[3] = {static_cast<uint32_t>(sensor_id), rows, cols};
    if (std::memcmp(shm_data_, init_data, sizeof(init_data)))
    {
        (void)std::memcpy(shm_data_, init_data, sizeof(init_data));
        static_cast<uint8_t*>(shm_data_)[32] = static_cast<uint8_t>(encoding_);
        static_cast<uint32_t*>(shm_data_)[3] = 1;
    }
    else
    {
        static_cast<uint32_t*>(shm_data_)[3] += 1;
    }
    (void)sem_post(shm_sem_);
    LOG(INFO) << "image ipc initialized: " << shmem_name_;
}

ImageIpc::~ImageIpc() noexcept
{
    (void)sem_wait(shm_sem_);
    uint32_t refs = --static_cast<uint32_t*>(shm_data_)[3];
    (void)sem_post(shm_sem_);
    if (shm_data_ != MAP_FAILED)
    {
        (void)munmap(shm_data_, shmem_size_);
        if (fd_ != -1)
        {
            (void)close(fd_);
        }
        if (refs == 0)
        {
            (void)shm_unlink(shmem_name_.c_str());
        }
    }
    if (shm_sem_)
    {
        (void)sem_close(shm_sem_);
        if (refs == 0)
        {
            (void)sem_unlink(shsem_name_.c_str());
        }
    }
}

SensorId ImageIpc::GetSensorId() const noexcept
{
    return sensor_id_;
}

bool_t ImageIpc::GetImageData(Image& image)
{
    if (sem_wait(shm_sem_) == -1)
    {
        LOG(ERROR) << "image ipc mutex wait failed: " << strerror(errno);
        return false;
    }
    image.ConfigImage(cols_, rows_, encoding_);
    /* get */
    uint32_t offset = OFFSET;
    uint32_t sec_nsec[4];
    (void)std::memcpy((uint8_t*)sec_nsec, (uint8_t*)shm_data_ + offset, 4 * sizeof(uint32_t));
    image.SetReceivedStamp(holo::common::Timestamp(sec_nsec[0], sec_nsec[1]));
    image.SetTriggerStamp(holo::common::Timestamp(sec_nsec[2], sec_nsec[3]));
    offset += 4 * sizeof(uint32_t);
    offset += sizeof(Image::Encoding);
    image.UpdateData((uint8_t*)shm_data_ + offset, image_size_);

    (void)sem_post(shm_sem_);
    return true;
}

bool_t ImageIpc::SetDataSizeList(uint32_t* data_size_list, uint32_t buffers_size)
{   
    if ((encoding_ == holo::Image::Encoding::RGB) || (encoding_ == holo::Image::Encoding::BGR))
    {
        if (buffers_size != 1)
        {
            LOG(ERROR) << "mismatch image encoding and buffers.size";
            LOG(ERROR) << "buffers with size 1 should be provieded to RGB/BGR format image";
            return false;
        }
        data_size_list[0] = image_size_;
    }
    else if (encoding_ == holo::Image::Encoding::NV12)
    {
        if (buffers_size != 2)
        {
            LOG(ERROR) << "mismatch image encoding and buffers.size";
            LOG(ERROR) << "buffers with size 2 should be provieded to NV12 format image";
            return false;
        }
        data_size_list[0] = cols_ * rows_;
        data_size_list[1] = cols_ * rows_ / 2;
    }
    else
    {
        LOG(ERROR) << "image type unsupported by this api: " << static_cast<uint8_t>(encoding_);
        return false;
    }
    return true;
}

bool_t ImageIpc::GetImageData(holo::common::Timestamp& received_stamp, holo::common::Timestamp& trigger_stamp,
                              holo::Image::Encoding& encoding, std::vector<StreamBuffer>& buffers)
{
    uint32_t data_size_list[2] = {0};
    
    if (!SetDataSizeList(data_size_list, buffers.size()))
    {
        return false;
    }

    /* check memory buffers */
    for (uint32_t i = 0; i < buffers.size(); i++)
    {
        if (buffers[i].init != true)
        {
            LOG(ERROR) << "buffer[" << uint32_t(i) << "] should set .init to true";
            return false;
        }
        if (buffers[i].start == nullptr)
        {
            LOG(ERROR) << "buffer[" << uint32_t(i) << "] should set .start to target address";
            return false;
        }
        if (buffers[i].capacity < data_size_list[i])
        {
            LOG(ERROR) << "buffer[" << uint32_t(i) << "] capacity " << buffers[i].capacity << " is less than wanted "
                       << data_size_list[i];
            return false;
        }
    }
    /* read */
    if (sem_wait(shm_sem_) == -1)
    {
        LOG(ERROR) << "image ipc mutex wait failed: " << strerror(errno);
        return false;
    }
    /* get */
    uint32_t        offset   = OFFSET;
    const uint32_t* sec_nsec = const_cast<const uint32_t*>(static_cast<uint32_t*>(shm_data_) + offset);
    received_stamp           = holo::common::Timestamp(sec_nsec[0], sec_nsec[1]);
    trigger_stamp            = holo::common::Timestamp(sec_nsec[2], sec_nsec[3]);
    offset += 4 * sizeof(uint32_t);
    (void)std::memcpy((uint8_t*)&encoding, (uint8_t*)shm_data_ + offset, sizeof(Image::Encoding));
    offset += sizeof(Image::Encoding);
    for (uint32_t i = 0; i < buffers.size(); i++)
    {
        (void)std::memcpy(buffers[i].start, static_cast<uint8_t*>(shm_data_) + offset, data_size_list[i]);
        buffers[i].size = data_size_list[i];
        offset += data_size_list[i];
    }
    (void)sem_post(shm_sem_);
    return true;
}

bool_t ImageIpc::SetImageData(const Image& image)
{
    if (encoding_ != image.GetEncoding())
    {
        LOG(ERROR) << "image type mismatch";
        return false;
    }

    if (sem_wait(shm_sem_) == -1)
    {
        LOG(ERROR) << "image ipc mutex wait failed: " << strerror(errno);
        return false;
    }
    /* set */
    uint32_t                offset = OFFSET;
    int32_t                 sec = 0, nsec = 0;
    holo::common::Timestamp time_stamp = image.GetReceivedStamp();
    sec                                = time_stamp.GetSec();
    nsec                               = time_stamp.GetNsec();
    (void)std::memcpy((uint8_t*)shm_data_ + offset, &sec, sizeof(int32_t));
    offset += sizeof(int32_t);
    (void)std::memcpy((uint8_t*)shm_data_ + offset, &nsec, sizeof(int32_t));
    offset += sizeof(int32_t);
    time_stamp = image.GetTriggerStamp();
    sec        = time_stamp.GetSec();
    nsec       = time_stamp.GetNsec();
    (void)std::memcpy((uint8_t*)shm_data_ + offset, &sec, sizeof(int32_t));
    offset += sizeof(int32_t);
    (void)std::memcpy((uint8_t*)shm_data_ + offset, &nsec, sizeof(int32_t));
    offset += sizeof(int32_t);
    (void)std::memcpy((uint8_t*)shm_data_ + offset, (uint8_t*)&encoding_, sizeof(Image::Encoding));
    offset += sizeof(Image::Encoding);
    (void)std::memcpy((uint8_t*)shm_data_ + offset, (const uint8_t*)image.GetData(), image_size_);

    (void)sem_post(shm_sem_);
    return true;
}

}  // namespace camera
}  // namespace sensors
}  // namespace holo