/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file format.h
 * @brief define the base format class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-07-24
 */

#ifndef _HOLO_SENSORS_FORMAT_FORMAT_H
#define _HOLO_SENSORS_FORMAT_FORMAT_H

#include <holo/core/types.h>

namespace holo
{
namespace sensors
{
namespace format
{
class FormatBase
{
public:
    FormatBase() = default;
 
    virtual ~FormatBase() noexcept
    {
    }
    virtual uint32_t GetSerializedSize() const noexcept                      = 0;
    virtual uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept = 0;
    virtual uint32_t Deserialize(const uint8_t* data, uint32_t bytes)        = 0;
};

}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif
