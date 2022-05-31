/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_ipc.h.
 * @brief Image IPC.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-04.
 */

#ifndef _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_IPC_H
#define _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_IPC_H

#include <iostream>
#include <string>
#include <vector>

#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>

#include <holo/os/predefine.h>
#if defined(HOLO_PLATFORM_LINUX)
#include <fcntl.h>
#include <semaphore.h>  // semaphore
#include <sys/mman.h>   // shm_open, shm_ctl, mmap, shum_unlink
#include <sys/stat.h>   // fstat
#include <unistd.h>     // fruncate
#elif defined(HOLO_PLATFORM_QNX)
#include <fcntl.h>
#include <semaphore.h>  // semaphore
#include <sys/mman.h>   // shm_open, shm_ctl, mmap, shum_unlink
#include <unistd.h>     // fruncate( get file descriptor for file that you want to truncate and set memorey object size)
#else
#error "HOLO_BUILD_PLATFORM is wrong, please check it."
#endif

#include <holo/common/image.h>
#include <holo/core/types.h>
#include <holo/sensors/camera/image_structure.h>

namespace holo
{
namespace sensors
{
namespace camera
{
class ImageIpcBase
{
public:
    ImageIpcBase(uint32_t rows, uint32_t cols, Image::Encoding encoding);
    virtual ~ImageIpcBase() = default;
    uint32_t        GetCols() const noexcept;
    uint32_t        GetRows() const noexcept;
    Image::Encoding GetEncoding() const noexcept;
    uint32_t        GetImageSize() const noexcept;

protected:
    uint32_t        cols_;
    uint32_t        rows_;
    Image::Encoding encoding_;
    uint32_t        image_size_;
};

class ImageIpc : public ImageIpcBase
{
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  sensor_id  The sensor identifier
     */
    ImageIpc(SensorId sensor_id);

    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  sensor_id  The sensor identifier
     * @param[in]  rows       The rows
     * @param[in]  cols       The cols
     * @param[in]  encoding   The encoding
     */
    ImageIpc(SensorId sensor_id, uint32_t rows, uint32_t cols, Image::Encoding encoding = Image::Encoding::RGB);

    /**
     * @brief      destructor
     */
    ~ImageIpc() noexcept;

    /**
     * @brief      Gets the sensor_id.
     *
     * @return     The sensor_id.
     */
    SensorId GetSensorId() const noexcept;

    /**
     * @brief      this function is used to get one image from shared memory
     *
     * @param[out] image  the image got from shared memory
     *
     * @return     Result: true if successfully, false otherwise
     */
    bool_t GetImageData(Image& image);

    /**
     * @brief      this function is used to get raw image elements from shared memory
     *
     * @param      received_stamp  The received stamp
     * @param      trigger_stamp   The trigger stamp
     * @param      encoding        The encoding
     * @param      buffers         The buffer list including target addresses
     * @note       each buffer.init should be set to 'true' to indicate it is valid, and
     *             the buffer.start and buffer.capacity should be set to indicate the target memory, and
     *             the buffer.size will be set to real data size after function called with a 'true' returned.
     *
     * @return     Result: true if successfully, otherwise false
     */
    bool_t GetImageData(holo::common::Timestamp& received_stamp, holo::common::Timestamp& trigger_stamp,
                        holo::Image::Encoding& encoding, std::vector<StreamBuffer>& buffers);

    /**
     * @brief      this function is used set one image to shared memory usually
     *             the server would use this function
     *
     * @param[out] image  the image set to shared memory
     *
     * @return     true if the image is successfully set otherwise return false
     */
    bool_t SetImageData(const Image& image);

private:
    void   OpenShmFd();
    bool_t SetDataSizeList(uint32_t* data_size_list, uint32_t buffers_size);

private:
    static constexpr uint32_t OFFSET = 16u;

private:
    SensorId    sensor_id_;
    uint32_t    shmem_size_;
    int32_t     fd_;
    sem_t*      shm_sem_;
    void*       shm_data_;
    std::string shsem_name_;
    std::string shmem_name_;
};

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  // _HOLO_SENSORS_CAMERA_CAPTURE_IMAGE_IPC_H