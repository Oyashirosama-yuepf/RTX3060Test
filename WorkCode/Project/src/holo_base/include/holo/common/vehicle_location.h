/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_location.h
 * @brief This header file defines VehicleLocation class
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-11
 */

#ifndef HOLO_COMMON_VEHICLE_LOCATION_H_
#define HOLO_COMMON_VEHICLE_LOCATION_H_

#include <holo/core/types.h>

namespace holo
{
namespace common
{
/**
 * @brief VehicleLocation object represents a location in a vehicle.
 *
 * @details A location of a vehicle is represented as a `plane id`, `coordinate-x` and `coordinate-y` on that plane.
 *
 * @f[
 * \begin{bytefield}{16}
 *   \bitheader{0-15} \\
 *   \bitbox{8}{plane\_id} & \bitbox{4}{X} & \bitbox{4}{Y}
 * \end{bytefield}
 * @f]
 *
 * @todo Insert a picture here to illustrate the coordinate for each plane.
 *
 * `plane-id`: A 8 bit value indicates a plane on a vehicle. See VehicleLocation::Plane for possible values.
 *
 * `coordinate-x`: A 4-bit value indicating position in X-axis. 0x0 is reserved as unknown position.
 *
 * `coordinate-y`:A 4-bit value indicating position in Y-axis. 0x0 is reserved as unknown position.
 *
 * In this codec way, each vehicle plane is marked with a 15x15 grid. To simply the usage for ordinary cases,
 * VehicleLocation::Location is defined for most commonly used locations.
 *
 * For instance a VehicleLocation 0x018F means the top center of a vehicle's front side plane.
 * A VehicleLocation 0x038C means the middle front of vehicle's left side plane.
 *
 */
class VehicleLocation
{
public:
    enum class Plane : uint8_t
    {
        UNKNOWN      = 0x00,
        FRONT        = 0x01,
        REAR         = 0x02,
        LEFT         = 0x03,
        RIGHT        = 0x04,
        FRONT_WINDOW = 0x05,
        REAR_WINDOW  = 0x06,
        LEFT_WINDOW  = 0x07,
        RIGHT_WINDOW = 0x08,
        EIGINE_HOOD  = 0x09,
        ROOF         = 0x0a,
        TRUNK_DOOR   = 0x0b,
        CHASSIS      = 0x0c,
        TRUNK        = 0x0d,
        COCKPIT      = 0x0e,
        GROUND       = 0x0f,
    };

    enum class Location : uint8_t
    {
        UNKNOWN     = 0x0,
        BOTTOM_MOST = 0x1,
        REAR_MOST   = 0x1,
        LEFT_MOST   = 0x1,
        BOTTOM      = 0x4,
        REAR        = 0x4,
        LEFT        = 0x4,
        MIDDLE      = 0x8,
        CENTER      = 0x8,
        TOP         = 0xc,
        FRONT       = 0xc,
        RIGHT       = 0xc,
        TOP_MOST    = 0xf,
        FRONT_MOST  = 0xf,
        RIGHT_MOST  = 0xf,
    };

    VehicleLocation() noexcept : y_(0), x_(0), plane_(0)
    {
    }

    VehicleLocation(uint16_t value) noexcept : y_(value & 0x0f), x_((value >> 4) & 0x0f), plane_((value >> 8) & 0xff)
    {
    }

    VehicleLocation(Plane plane, Location x = Location::UNKNOWN, Location y = Location::UNKNOWN) noexcept
      : y_(static_cast<uint8_t>(y)), x_(static_cast<uint8_t>(x)), plane_(static_cast<uint8_t>(plane))
    {
    }

    VehicleLocation& operator=(uint16_t value)
    {
        plane_ = value >> 8;
        x_     = value >> 4;
        y_     = value;
        return *this;
    }

    operator uint16_t() const noexcept
    {
        return static_cast<uint16_t>(static_cast<uint16_t>(plane_) << 8) |
               static_cast<uint16_t>(static_cast<uint16_t>(x_) << 4) | y_;
    }

    void SetPlane(Plane value) noexcept
    {
        plane_ = static_cast<uint8_t>(value);
    }

    Plane GetPlane() const noexcept
    {
        return static_cast<Plane>(plane_);
    }

    void SetLocation(Location x, Location y)
    {
        x_ = static_cast<uint8_t>(x);
        y_ = static_cast<uint8_t>(y);
    }

    void SetLocationX(Location x)
    {
        x_ = static_cast<uint8_t>(x);
    }

    void SetLocationY(Location y)
    {
        y_ = static_cast<uint8_t>(y);
    }

    Location GetLocationX() const noexcept
    {
        return static_cast<Location>(x_);
    }

    Location GetLocationY() const noexcept
    {
        return static_cast<Location>(y_);
    }

private:
    uint16_t y_ : 4;
    uint16_t x_ : 4;
    uint16_t plane_ : 8;
};

}  // namespace common
}  // namespace holo

#endif
