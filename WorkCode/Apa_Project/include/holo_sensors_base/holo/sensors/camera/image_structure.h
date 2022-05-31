/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_structure.h
 * @brief Image Structures.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-04.
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_STRUCTURE_H
#define _HOLO_SENSORS_CAMERA_IMAGE_STRUCTURE_H

#include <holo/common/image.h>
#include <holo/common/sensor_id.h>
#include <holo/core/types.h>
#include <holo/log/hololog.h>
#include <holo/sensors/format/holosync.h>
#include <holo/serialization/serialization.h>
#include <functional>
#include <memory>
#include <string>

namespace holo
{
namespace sensors
{
namespace camera
{
using SensorId      = holo::common::SensorId;
using TimestampPair = std::pair<holo::common::Timestamp, holo::common::Timestamp>;

static constexpr uint32_t IMAGE_ENCODE_SIZE_MAX = 1920 * 1080 * 2 + 256;
static constexpr uint32_t IMAGE_RAW_SIZE_MAX    = 1920 * 1080 * 2 + 256;

/**
 * @brief the pixel format
 */
enum PixelType : uint8_t
{
    BGR       = 0,
    RGB       = 1,
    YUV       = 2,
    GRAYSCALE = 3,
    YUYV      = 4,
    NV12      = 5,
};

/**
 * @brief h26x frame type
 *
 */
enum FrameType : uint8_t
{
    UNKNOWN = 0,
    P       = 1,
    I       = 19,
};

/**
 * @brief the type of image after compression
 */
enum ImageType : uint8_t
{
    JPEG     = 0,
    H264     = 1,
    H265     = 2,
    RAW_YUYV = 3,
    INVALID  = 255
};

/**
 * @brief stream buffer from hardware
 */
struct StreamBuffer
{
    bool_t   init;
    void*    start;
    uint32_t capacity;
    uint32_t size;
};

/**
 * @brief compress data for image which would be used for ROS message to record
 */
struct ImagePacket
{
    template <typename S>
    bool_t Serialize(S& serializer) const
    {
        try
        {
            serializer << (uint32_t)seq << received_stamp << trigger_stamp << frame_type << (uint32_t)cols
                       << (uint32_t)rows << (uint8_t)image_type << (uint32_t)size;
            serializer.Write(data, size);
            serializer << holo::serialization::align;
        }
        catch (holo::serialization::SerializationBufferOverflowException& e)
        {
            std::string error = "serialization buffer size error: ";
            LOG(ERROR) << error << e.what();
            return false;
        }
        catch (...)
        {
            LOG(ERROR) << "serialization Unexpected exception caught";
            return false;
        }
        return true;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        uint8_t  _image_type = 0;
        uint32_t serial_size = holo::serialization::AlignedSize<ALIGN>(sizeof(uint32_t)) +
                               received_stamp.GetSerializedSize<ALIGN>() + trigger_stamp.GetSerializedSize<ALIGN>() +
                               holo::serialization::SerializedSize<ALIGN>(frame_type, cols, rows, _image_type) +
                               sizeof(size) + size;
        return holo::serialization::AlignedSize<ALIGN>(serial_size);
    }

    template <typename D>
    bool_t Deserialize(D& deserializer)
    {
        uint8_t                 _image_type, _frame_type;
        uint32_t                _seq, _cols, _rows, _size;
        holo::common::Timestamp _recv_stamp, _trigger_stamp;
        try
        {
            deserializer >> _seq;
            deserializer >> _recv_stamp;
            deserializer >> _trigger_stamp;
            deserializer >> _frame_type;
            deserializer >> _cols;
            deserializer >> _rows;
            deserializer >> _image_type;
            deserializer >> _size;
            deserializer.Read(data, _size);
            deserializer >> holo::serialization::align;
        }
        catch (holo::serialization::DeserializationBufferUnderflowException& e)
        {
            std::ostringstream oss;
            oss << "deserialization buffer size error!";
            LOG(ERROR) << oss.str();
            return false;
        }
        catch (...)
        {
            LOG(ERROR) << "deserialization Unexpected exception caught";
            return false;
        }
        image_type     = static_cast<ImageType>(_image_type);
        cols           = _cols;
        rows           = _rows;
        size           = _size;
        frame_type     = _frame_type;
        seq            = _seq;
        received_stamp = _recv_stamp;
        trigger_stamp  = _trigger_stamp;
        return true;
    }

    uint32_t                seq;
    holo::common::Timestamp received_stamp;
    holo::common::Timestamp trigger_stamp;
    ImageType               image_type;
    uint8_t                 reserved[2];
    uint8_t                 frame_type;
    uint32_t                cols;
    uint32_t                rows;
    uint32_t                size;
    uint8_t*                data;
};

class ImageWrapper : public holo::Image
{
public:
    ImageWrapper() : holo::Image()
    {
    }

    ImageWrapper(const holo::Image& image) : holo::Image(image)
    {
    }

    const holo::Image& GetImage() const
    {
        return *this;
    }

    uint32_t GetSize() const noexcept
    {
        if (GetEncoding() == Image::Encoding::RGB || GetEncoding() == Image::Encoding::BGR)
        {
            return GetWidth() * GetHeight() * 3;
        }
        else if (GetEncoding() == Image::Encoding::GRAYSCALE)
        {
            return GetWidth() * GetHeight();
        }
        else if ((GetEncoding() == Image::Encoding::YUYV) || (GetEncoding() == Image::Encoding::UYVY) ||
                 (GetEncoding() == Image::Encoding::YUV422P))
        {
            return GetWidth() * GetHeight() * 2;
        }
        else if ((GetEncoding() == Image::Encoding::YU12) || (GetEncoding() == Image::Encoding::YV12) ||
                 (GetEncoding() == Image::Encoding::NV12) || (GetEncoding() == Image::Encoding::NV21))
        {
            return GetWidth() * GetHeight();
        }
        else
        {
            return GetWidth() * GetHeight() * 4;
        }
    }

    template <size_t ALIGN = 4U>
    uint32_t GetSerializedSize() const noexcept
    {
        uint32_t size = holo::serialization::AlignedSize<ALIGN>(sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint8_t)) +
                        GetTriggerStamp().GetSerializedSize<ALIGN>() + GetReceivedStamp().GetSerializedSize<ALIGN>() +
                        holo::serialization::AlignedSize<ALIGN>(GetSize());
        return size;
    }

    template <typename S>
    bool_t Serialize(S& serializer) const
    {
        try
        {
            uint16_t real_height = GetHeight();
            if ((GetEncoding() == Image::Encoding::YU12) || (GetEncoding() == Image::Encoding::YV12) ||
                (GetEncoding() == Image::Encoding::NV12) || (GetEncoding() == Image::Encoding::NV21))
            {
                real_height = GetHeight() * 2 / 3;
            }
            serializer << GetWidth() << real_height << (uint8_t)GetEncoding() << GetTriggerStamp()
                       << GetReceivedStamp();
            serializer.Write(GetData(), GetSize());
            serializer << holo::serialization::align;
        }
        catch (holo::serialization::SerializationBufferOverflowException& e)
        {
            std::string error = "serialization buffer size error: ";
            LOG(ERROR) << error << e.what();
            return false;
        }
        catch (...)
        {
            LOG(ERROR) << "serialization Unexpected exception caught";
            return false;
        }
        return true;
    }

    template <typename D>
    bool_t Deserialize(D& deserializer)
    {
        holo::common::Timestamp trigger_stamp;
        holo::common::Timestamp recv_stamp;
        uint8_t                 encoding_type;
        uint16_t                width;
        uint16_t                height;
        try
        {
            deserializer >> width;
            deserializer >> height;
            deserializer >> encoding_type;
            this->ConfigImage(width, height, static_cast<holo::Image::Encoding>(encoding_type));
            deserializer >> trigger_stamp;
            deserializer >> recv_stamp;
            deserializer.Read(GetData(), GetSize());
            deserializer >> holo::serialization::align;
        }
        catch (holo::serialization::DeserializationBufferUnderflowException& e)
        {
            std::ostringstream oss;
            oss << "deserialization buffer size error!";
            LOG(ERROR) << oss.str();
            return false;
        }
        catch (...)
        {
            LOG(ERROR) << "deserialization Unexpected exception caught";
            return false;
        }
        SetTriggerStamp(trigger_stamp);
        SetReceivedStamp(recv_stamp);
        return true;
    }
};

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  // _HOLO_SENSORS_CAMERA_IMAGE_STRUCTURES_H
