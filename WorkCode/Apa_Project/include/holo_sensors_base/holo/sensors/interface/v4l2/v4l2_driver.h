/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_capture.cpp.
 * @brief Image Capture Driver.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-05.
 */

#ifndef HOLO_SENSORS_CMW_APP_INTERFACE_V4L2_V4L2_DRIVER_H
#define HOLO_SENSORS_CMW_APP_INTERFACE_V4L2_V4L2_DRIVER_H

#include <fcntl.h>
#include <holo/common/sensor_id.h>
#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <holo/os/time.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/camera/image_utils.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/utils/yaml.h>
#include <linux/usb/video.h>
#include <linux/uvcvideo.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace holo
{
namespace sensors
{
namespace interface
{
//! stream buffer request num
static constexpr uint32_t STREAM_BUFFER_REQNUM = 2u;
//! uvc trigger reg address
static constexpr uint16_t UVC_TRIGGER_ENABLE = 0x0b00;
//! uvc reg read & write adddress
static constexpr uint16_t UVC_REG_RW = 0x0e00;
//! disable auto exposure address and value
static constexpr uint16_t UVC_AR0231_DIS_AE  = 0xc8bc;
static constexpr uint16_t UVC_AR0231_DIS_VAL = 0x2000;
//! refresh command address and value
static constexpr uint16_t UVC_AR0231_REF_CMD = 0x0040;
static constexpr uint16_t UVC_AR0231_REF_VAL = 0x8606;
//! change exposure value address
static constexpr uint16_t UVC_AR0231_CHA_EXP = 0xc8c0;
//! enable exposure address and value
static constexpr uint16_t UVC_AR0231_ENB_EXP = 0xc842;
static constexpr uint16_t UVC_AR0231_ENB_VAL = 0x0100;

class CameraV4l2General
{
public:
    using PixelType              = holo::sensors::camera::PixelType;
    using StreamBuffer           = holo::sensors::camera::StreamBuffer;
    using Timestamp              = holo::common::Timestamp;
    using BufferCallbackType     = std::function<void(const StreamBuffer&)>;
    using BufferTimeCallbackType = std::function<void(const StreamBuffer&, const Timestamp&)>;

    CameraV4l2General() : fd_(-1), buffer_callback_(nullptr), buffer_time_callback_(nullptr)
    {
        for (uint32_t i = 0; i < STREAM_BUFFER_REQNUM; ++i)
        {
            stream_buffer_[i].init = false;
        }
    }

    virtual ~CameraV4l2General() = default;

    int32_t GetFd() const noexcept
    {
        return fd_;
    }

    void SetCallback(const BufferCallbackType& handler)
    {
        buffer_callback_ = handler;
    }

    void SetCallback(const BufferTimeCallbackType& handler)
    {
        buffer_time_callback_ = handler;
    }

    bool Open(const std::string& name)
    {
        struct stat st;
        if (stat(name.c_str(), &st) == -1)
        {
            LOG(ERROR) << "cannot identify ' " << name << "': " << errno << " " << strerror(errno);
            return false;
        }
        if (!S_ISCHR(st.st_mode))
        {
            LOG(ERROR) << name << " is not a character device";
            return false;
        }
        fd_ = open(name.c_str(), O_RDWR | O_NONBLOCK, 0);  // non-block
        if (fd_ == -1)
        {
            LOG(ERROR) << "could not open device " << errno << " " << strerror(errno);
            return false;
        }
        return true;
    }

    bool Init(uint32_t cols, uint32_t rows, PixelType pixel_format)
    {
        struct v4l2_capability cap;                       // some basic parameters
        if (HoloIoctl(fd_, VIDIOC_QUERYCAP, &cap) == -1)  // check if the device can be used as image capturing
        {
            if (EINVAL == errno)
            {
                LOG(ERROR) << "device is not V4L2 device";
            }
            else
            {
                LOG(ERROR) << "failed to check devive's capability";
            }
            return false;
        }

        if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
        {
            LOG(ERROR) << "device is not a video capture device";
            return false;
        }

        /* Select video input, video standard and tune here. */
        struct v4l2_cropcap cropcap;  // this is used to set the capature ability of camera
        (void)std::memset(&cropcap, 0, sizeof(cropcap));
        cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        HoloIoctl(fd_, VIDIOC_CROPCAP, &cropcap);

        struct v4l2_crop crop;
        (void)std::memset(&crop, 0, sizeof(crop));
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c    = cropcap.defrect; /* reset to default */

        struct v4l2_format fmt;  // this is used to set the format of camera
        (void)std::memset(&fmt, 0, sizeof(fmt));
        fmt.type           = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.width  = cols;
        fmt.fmt.pix.height = rows;
        std::string sformat;
        switch (pixel_format)
        {
            case PixelType::YUV:
                fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YYUV;
                sformat                 = "YYUV";
                break;
            case PixelType::YUYV:
                fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
                sformat                 = "YUYV";
                break;
            case PixelType::RGB:
                fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
                sformat                 = "RGB24";
                break;
            case PixelType::BGR:
                fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_BGR24;
                sformat                 = "BGR24";
                break;
            default:
                fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
                sformat                 = "YUYV";
                break;
        }
        LOG(INFO) << "pixel format set to value: " << sformat;
        fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
        HoloIoctl(fd_, VIDIOC_S_FMT, &fmt);

        /* fix possiable errors? */
        fmt.fmt.pix.bytesperline = std::max(fmt.fmt.pix.bytesperline, fmt.fmt.pix.width);
        fmt.fmt.pix.sizeimage    = std::max(fmt.fmt.pix.sizeimage, fmt.fmt.pix.bytesperline * fmt.fmt.pix.height);

        return true;
    }

    bool InitMmap()
    {
        /* apply device memory */
        struct v4l2_requestbuffers req;
        (void)std::memset(&req, 0, sizeof(req));
        req.count  = STREAM_BUFFER_REQNUM;         // first apply n sizes of spaces from device memory
        req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;  // for video capture
        req.memory = V4L2_MEMORY_MMAP;             // the memory is memory map from device memory
        if (HoloIoctl(fd_, VIDIOC_REQBUFS, &req) == -1)
        {
            if (EINVAL == errno)
            {
                LOG(ERROR) << "device dose not support memory maping";
            }
            else
            {
                LOG(ERROR) << "failed to map memory";
            }
            return false;
        }
        LOG(INFO) << "request " << static_cast<uint32_t>(req.count) << " buffers";
        for (size_t j = 0; j < req.count; ++j)
        {
            struct v4l2_buffer buf;
            (void)std::memset(&buf, 0, sizeof(buf));
            buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index  = j;
            HoloIoctl(fd_, VIDIOC_QUERYBUF, &buf);
            stream_buffer_[j].capacity = buf.length;
            stream_buffer_[j].start    = mmap(NULL,                               /* start anywhere */
                                           buf.length, PROT_READ | PROT_WRITE, /* required */
                                           MAP_SHARED,                         /* recommended */
                                           fd_, buf.m.offset);
            if (stream_buffer_[j].start == MAP_FAILED)
            {
                LOG(ERROR) << "failed to mmap: " << static_cast<uint32_t>(j);
                continue;
            }
            stream_buffer_[j].init = true;
        }
        bool retcode = false;
        for (uint32_t k = 0; k < STREAM_BUFFER_REQNUM; ++k)
        {
            retcode |= stream_buffer_[k].init;
        }
        return retcode;
    }

    void Close()
    {
        /* munmap */
        for (uint32_t i = 0; i < STREAM_BUFFER_REQNUM; ++i)
        {
            if (stream_buffer_[i].init)
            {
                stream_buffer_[i].init = false;
                munmap(stream_buffer_[i].start, stream_buffer_[i].capacity);
            }
        }
        /* close fd */
        if (fd_ > 0)
        {
            close(fd_);
        }
    }

    void StartCapture()
    {
        for (uint32_t i = 0; i < STREAM_BUFFER_REQNUM; i++)
        {
            if (stream_buffer_[i].init)
            {
                struct v4l2_buffer buf;
                (void)std::memset(&buf, 0, sizeof(buf));
                buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory = V4L2_MEMORY_MMAP;
                buf.index  = i;
                HoloIoctl(fd_, VIDIOC_QBUF, &buf);
            }
        }
        enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        HoloIoctl(fd_, VIDIOC_STREAMON, &type);
    }

    bool ReadFrame()
    {
        struct v4l2_buffer buf;
        (void)std::memset(&buf, 0, sizeof(buf));
        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        HoloIoctl(fd_, VIDIOC_DQBUF, &buf);
        stream_buffer_[buf.index].size = buf.bytesused;
        Timestamp image_timestamp_from_v4l2;
        image_timestamp_from_v4l2.SetSec(buf.timestamp.tv_sec);
        image_timestamp_from_v4l2.SetNsec(buf.timestamp.tv_usec * 1e3);
        if (!stream_buffer_[buf.index].init)
        {
            LOG(ERROR) << "seems invalid stream buffer index: " << static_cast<uint32_t>(buf.index);
            return false;
        }
        /* read frame */
        if (buffer_callback_)
        {
            buffer_callback_(stream_buffer_[buf.index]);
        }
        if (buffer_time_callback_)
        {
            buffer_time_callback_(stream_buffer_[buf.index], image_timestamp_from_v4l2);
        }
        /* start again */
        HoloIoctl(fd_, VIDIOC_QBUF, &buf);
        return true;
    }

protected:
    int32_t HoloIoctl(int32_t fd, int32_t id, void* arg, int32_t tries = 3) noexcept
    {
        int32_t ret = 0;
        do
        {
            ret = ioctl(fd, id, arg);
        } while (tries-- && ret);
        if (ret)
        {
            LOG(ERROR) << "HoloIoctl " << id << " failed: " << strerror(errno);
        }
        return ret;
    }

    bool SetRegValue(uint16_t reg_addr, uint16_t reg_value)
    {
        // define the value array for storage
        // the setting and getting configuration value
        uint8_t value[64] = {0};
        // define the xu query struct
        struct uvc_xu_control_query xu_query;
        xu_query.unit     = 3;  // has to be unit 3
        xu_query.data     = value;
        xu_query.selector = UVC_REG_RW >> 8;
        xu_query.query    = UVC_SET_CUR;
        xu_query.size     = 5;
        // setting the read configuration
        value[0] = 1;  // indicate for write
        value[1] = static_cast<uint8_t>(reg_addr >> 8) & 0xff;
        value[2] = static_cast<uint8_t>(reg_addr >> 0) & 0xff;
        value[3] = static_cast<uint8_t>(reg_value >> 8) & 0xff;
        value[4] = static_cast<uint8_t>(reg_value >> 0) & 0xff;
        HoloIoctl(fd_, UVCIOC_CTRL_QUERY, &xu_query);
        return true;
    }

    bool GetRegValue(uint16_t reg_addr, uint16_t& reg_value)
    {
        // define the value array for storage
        // the setting and getting configuration value
        uint8_t value[64] = {0};

        // define the xu query struct
        struct uvc_xu_control_query xu_query;
        xu_query.unit     = 3;  // has to be unit 3
        xu_query.data     = value;
        xu_query.selector = UVC_REG_RW >> 8;
        xu_query.query    = UVC_SET_CUR;
        xu_query.size     = 5;
        // setting the read configuration
        value[0] = 0;  // indicate for read
        value[1] = static_cast<uint8_t>(reg_addr >> 8) & 0xff;
        value[2] = static_cast<uint8_t>(reg_addr >> 0) & 0xff;
        HoloIoctl(fd_, UVCIOC_CTRL_QUERY, &xu_query);
        // getting the value
        xu_query.query = UVC_GET_CUR;
        value[0]       = 0;
        value[3]       = 0;
        value[4]       = 0;
        HoloIoctl(fd_, UVCIOC_CTRL_QUERY, &xu_query);
        reg_value = (uint16_t)(value[3] << 8) + (uint16_t)value[4];
        return true;
    }

public:
    virtual bool SetExposure(uint32_t exposure)
    {
        (void)exposure;
        return true;
    }

    virtual bool SetGain(uint32_t gain)
    {
        (void)gain;
        return true;
    }

    virtual bool SetTrigger(bool trigger_mode)
    {
        (void)trigger_mode;
        return true;
    }

protected:
    int32_t                fd_;
    BufferCallbackType     buffer_callback_;
    BufferTimeCallbackType buffer_time_callback_;
    StreamBuffer           stream_buffer_[STREAM_BUFFER_REQNUM];
};

class CameraM021 : public CameraV4l2General
{
public:
    CameraM021() : CameraV4l2General()
    {
    }

    bool SetExposure(uint32_t exposure) override
    {
        struct v4l2_control ctrl;
        (void)std::memset(&ctrl, 0, sizeof(ctrl));
        ctrl.id    = V4L2_CID_EXPOSURE_ABSOLUTE;
        ctrl.value = exposure;
        if (HoloIoctl(fd_, VIDIOC_S_CTRL, &ctrl) != 0)
        {
            LOG(ERROR) << "m021 camera exposure setting error";
            return false;
        }
        return true;
    }

    bool SetGain(uint32_t gain) override
    {
        struct v4l2_control ctrl;
        (void)std::memset(&ctrl, 0, sizeof(ctrl));
        ctrl.id    = V4L2_CID_GAIN;
        ctrl.value = gain;
        if (HoloIoctl(fd_, VIDIOC_S_CTRL, &ctrl) != 0)
        {
            LOG(ERROR) << "m021 camera gain setting error";
            return false;
        }
        return true;
    }
};

class CameraAR0231 : public CameraV4l2General
{
public:
    CameraAR0231() : CameraV4l2General()
    {
    }

    bool SetExposure(uint32_t exposure) override
    {
        /* disable auto exposure */
        if (!SetRegValue(UVC_AR0231_DIS_AE, UVC_AR0231_DIS_VAL))
        {
            return false;
        }
        /* refresh command */
        if (!SetRegValue(UVC_AR0231_REF_CMD, UVC_AR0231_REF_VAL))
        {
            return false;
        }
        /*change exposure value*/
        if (!SetRegValue(UVC_AR0231_CHA_EXP, static_cast<uint16_t>(exposure)))
        {
            LOG(ERROR) << "failed to change ar0231 exposure value";
            return false;
        }
        /*exposure request*/
        if (!SetRegValue(UVC_AR0231_ENB_EXP, UVC_AR0231_ENB_VAL))
        {
            LOG(ERROR) << "failed to request exposure change";
            return false;
        }
        return true;
    }

    bool SetTrigger(bool trigger_mode) override
    {
        uint8_t                     value[64] = {0};
        struct uvc_xu_control_query xu_query;
        xu_query.unit     = 3;  // has to be unit 3
        xu_query.data     = value;
        xu_query.selector = UVC_TRIGGER_ENABLE >> 8;
        xu_query.query    = UVC_SET_CUR;
        xu_query.size     = 2;
        value[0]          = trigger_mode;
        value[1]          = 0x00;
        if (HoloIoctl(fd_, UVCIOC_CTRL_QUERY, &xu_query) != 0)
        {
            LOG(ERROR) << "could not trigger camera";
            return false;
        }
        LOG(INFO) << "set trigger model: " << (trigger_mode ? "external trigger" : "inside trigger");
        return true;
    }
};

class CameraOV490 : public CameraV4l2General
{
public:
    CameraOV490() : CameraV4l2General()
    {
    }

    bool SetTrigger(bool trigger_mode) override
    {
        uint8_t                     value[64] = {0};
        struct uvc_xu_control_query xu_query;
        xu_query.unit     = 3;  // has to be unit 3
        xu_query.data     = value;
        xu_query.selector = UVC_TRIGGER_ENABLE >> 8;
        xu_query.query    = UVC_SET_CUR;
        xu_query.size     = 2;
        value[0]          = trigger_mode;
        value[1]          = 0x00;
        if (HoloIoctl(fd_, UVCIOC_CTRL_QUERY, &xu_query) != 0)
        {
            LOG(ERROR) << "could not trigger camera";
            return false;
        }
        LOG(INFO) << "set trigger model: " << (trigger_mode ? "external trigger" : "inside trigger");
        return true;
    }
};

class CameraAP020 : public CameraV4l2General
{
public:
    CameraAP020() : CameraV4l2General()
    {
    }

    bool SetTrigger(bool trigger_mode) override
    {
        uint8_t                     value[64] = {0};
        struct uvc_xu_control_query xu_query;
        xu_query.unit     = 3;  // has to be unit 3
        xu_query.data     = value;
        xu_query.selector = UVC_TRIGGER_ENABLE >> 8;
        xu_query.query    = UVC_SET_CUR;
        xu_query.size     = 2;
        value[0]          = trigger_mode;
        value[1]          = 0x00;
        if (HoloIoctl(fd_, UVCIOC_CTRL_QUERY, &xu_query) != 0)
        {
            LOG(ERROR) << "could not trigger camera";
            return false;
        }
        LOG(INFO) << "set trigger model: " << (trigger_mode ? "external trigger" : "inside trigger");
        return true;
    }
};
}  // namespace interface
}  // namespace sensors
}  // namespace holo

#endif
