/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_status.h
 * @brief Definition of map status
 * @author wanghaiyang(wanghaiyang@holomatic.com)
 * @date 2019-12-13
 */

#ifndef HOLO_MAP_COMMON_CLASSES_MAP_STATUS_H_
#define HOLO_MAP_COMMON_CLASSES_MAP_STATUS_H_

#include <holo/common/timestamp.h>
#include <holo/map/map_app_status.h>

namespace holo
{
namespace map
{
/**
 * @addtogroup map
 * @{
 *
 */

/**
 * @brief MapStatus is an object descripting a inner map error.
 */
class MapStatus final
{
public:
    /// Redefine Timestamp type for inner members.
    using TimestampType = holo::common::Timestamp;
    /**
     * @brief Default constructor.
     */
    MapStatus() = default;

    /**
     * @brief Default destructor.
     */
    ~MapStatus() = default;

    /**
     * @brief Constructs a object with an error code. 
     * 
     * @param[in] code A status value.
     * @return Return nothing.
     */
    explicit MapStatus(const MapStatusCode code) : code_(code) 
    {}

    /**
     * @brief Constructs a object with an error code and a timestamp. 
     * 
     * @param[in] code A status value.
     * @param[in] ts A timestamp object.
     * @return Return nothing.
     */
    MapStatus(const MapStatusCode code, const TimestampType& ts) : code_(code), time_stamp_(ts) 
    {}
    
    /**
     * @brief Copy constructor.
     * 
     * @param[in] Another object.
     * @return Returns nothing.
     */
    MapStatus(const MapStatus& ms) noexcept
    {
        this->code_ = ms.code_;
        this->time_stamp_ = ms.time_stamp_;
    }

    /**
     * @brief Move constructor.
     * 
     * @param[in] ms Another object.
     * @return Returns nothing.
     */
    MapStatus(MapStatus&& ms) noexcept
    {
        this->code_ = ms.code_;
        this->time_stamp_ = ms.time_stamp_;
    }

    /**
     * @brief Copy assignment.
     * 
     * @param[in] ms Another MapStatus object of the same type, whose contents are copied.
     * @return Returns *this.
     */
    MapStatus& operator= (const MapStatus& ms) noexcept
    {
        if (&ms != this)
        {
            this->code_ = ms.code_;
            this->time_stamp_ = ms.time_stamp_;
        }
        return *this;
    }

    /**
     * @brief Move assignment.
     * 
     * @param[in] ms Another MapStatus object of the same type, whose contents are acquired.
     * @return Returns *this.
     */
    MapStatus& operator= (MapStatus&& ms) noexcept
    {
        if (&ms != this)
        {
            this->code_ = ms.code_;
            this->time_stamp_ = ms.time_stamp_;
        }
        return *this;
    }

    /**
     * @brief Check if the status without error.
     * 
     * @return Returns true, no error with this status;
     *         Returns false, otherwise.
     */
    bool operation() const noexcept
    { 
        return MapStatusCode::K_OK == this->code_ ;
    }

    /**
     * @brief Access status code.
     * 
     * @return Returns a value to the status code.
     */
    MapStatusCode GetStatusCode() const noexcept
    { 
        return this->code_;
    }

    /**
     * @brief Assigns status code.
     * 
     * @param[in] code A status value.
     * @return Returns nothing.
     */
    void SetStatusCode(const MapStatusCode code) noexcept
    { 
        this->code_ = code; 
    }

    /**
     * @brief Access timestamp.
     * 
     * @return Returns a reference to the TimeStamp object.
     */
    const TimestampType& GetErrorTimeStamp() const noexcept
    { 
        return this->time_stamp_;
    }

    /**
     * @brief Assigns timestamp.
     * 
     * @param[in] A timestamp.
     * @return Returns nothing.
     */
    void SetErrorTimeStamp(const TimestampType& ts) noexcept
    {
        this->time_stamp_ = ts;
    }

private:
    MapStatusCode code_ = MapStatusCode::K_OK;
    TimestampType time_stamp_;
};

/**
 * @}
 */
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_COMMON_CLASSES_MAP_STATUS_H_ */
