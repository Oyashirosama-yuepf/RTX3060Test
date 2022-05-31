/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file holo_can_format.h
 * @brief define the holo can structure format class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-07-24
 */

#ifndef _HOLO_SENSORS_FORMAT_RAWBUF_H
#define _HOLO_SENSORS_FORMAT_RAWBUF_H

#include <holo/core/types.h>
#include <holo/sensors/format/format.h>
#include <holo/container/vector.h>

#include <cstring>
#include <memory>
#include <stdexcept>

namespace holo
{
namespace sensors
{
namespace format
{
template <uint32_t SIZE>
class Rawbuffer : public holo::container::Vector<uint8_t, SIZE>, public FormatBase
{
public:
    Rawbuffer() : holo::container::Vector<uint8_t, SIZE>()
    {
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return this->size();
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < this->GetSerializedSize())
        {
            return 0;
        }
        (void)std::memcpy(data, this->data(), this->size());
        return this->size();
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes) noexcept
    {
        if (bytes > SIZE)
        {
            return 0;
        }
        this->resize(bytes);
        (void)std::memcpy(this->data(), data, bytes);
        return bytes;
    }
};

}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif
