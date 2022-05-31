/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_app_status.h
 * @brief Map app status message
 * @author wanghaiyang(wanghaiyang@holomaitc.com)
 * @date "2019-12-18"
 */

#ifndef HOLO_MAP_MAP_APP_STATUS_H_
#define HOLO_MAP_MAP_APP_STATUS_H_

#include <vector>

#include <holo/common/timestamp.h>

namespace holo
{
namespace map
{
/**
 * @addtogroup map
 * @{
 *
 */

#define MAP_CODE (0X00000002 << 28)

typedef uint32_t MapCodeType;

/**
 * @brief Document: https://wiki.holomatic.cn/display/HOLO/Map+System+APP+Status
 */
enum class MapModuleCode : MapCodeType
{
    K_COMMON      = MAP_CODE | (0X00000000 << 20),
    K_NAVIGATOR   = MAP_CODE | (0X00000001 << 20),
    K_LANE_FUSION = MAP_CODE | (0X00000002 << 20),
    K_FREE_SPACE  = MAP_CODE | (0X00000003 << 20),
    K_MAX_VALUE   = 0X00000001 << 28,
};

/**
 * @brief Document: https://wiki.holomatic.cn/display/HOLO/Map+System+APP+Status
 */
enum class MapStatusCode : MapCodeType
{
    /// Common error code(Level 1).
    K_OK                         = 0X00000000,
    K_COMMON_IO_ERROR            ,
    K_COMMON_MEMARY_ERROR        ,
    K_COMMON_NETWORK_ERROR       ,
    K_COMMON_NDS_SDK_ERROR       ,
    K_COMMON_MAP_COMPILING_ERROR ,
    K_COMMON_MAP_DATA_ERROR      ,
    K_COMMON_MAP_MATCHING_ERROR  ,
    K_COMMON_MAP_ROUTING_ERROR   ,

    /// Common error code(Level 2).
    K_MAP_MATCHING_UNRELIABLE    ,
    K_MAP_MATCHING_NOT_ON_MAP    ,
    K_MAP_ROUTING_VARIATION      ,
    
    /// Navigator error code.
    K_NAVIGATOR_ADVISOR_ERROR    ,

    /// LaneFusion error code.
    
    /// Freespace error code.
    K_FREESPACE_PREPARAION_ERROR ,
    K_FREESPACE_INDICATOR_ERROR  ,
    K_FREESPACE_BUILDER_ERROR    ,

    K_MAX_VALUE                  = 0X00000001 << 20,
};

/**
 * @brief MapAppStatus is a object representing error message from map app node.
 */
class MapAppStatus final
{
public:
    typedef std::vector<MapAppStatus> Array;
    using Timestamp = holo::common::Timestamp;
    
    /**
     * @brief Default constructor.
     * 
     * @return Returns nothing.
     */
    MapAppStatus() = default;

    /**
     * @brief Default destructor.
     * 
     * @return Returns nothing.
     */
    ~MapAppStatus() = default;

    /**
     * @brief Copy constructor.
     * 
     * @return Returns nothing.
     */
    MapAppStatus(const MapAppStatus&) = default;

    /**
     * @brief Move constructor.
     * 
     * @return Returns nothing.
     */
    MapAppStatus(MapAppStatus&&) = default;

    /**
     * @brief Copy assignment.
     *
     * @param [in] s A object of the same type. 
     * @return Returns *this.
     */
    MapAppStatus& operator= (const MapAppStatus& s) = default;

    /**
     * @brief Move assignment.
     * 
     * @param[in] s A objec of the same type.
     * @return Returns *this.
     */
    MapAppStatus& operator= (MapAppStatus&& s) = default;

    /**
     * @brief Test whether status without error.
     * 
     * @return Returns true: if current status without error;
     *         Returns false: otherwise.
     */
    explicit operator bool() const noexcept
    {
        return this->IsWorking();
    }

    /**
     * @brief Test whether status without error.
     * 
     * @return Returns true: if current status without error;
     *         Returns false: otherwise.
     */
    bool IsWorking() const noexcept
    {
        return (this->code_ & (~(0XFFFFFFFF << 20))) ==  static_cast<MapCodeType>(MapStatusCode::K_OK);
    }

    /**
     * @brief Access message timestamp.
     * 
     * @return Returns a message timestamp.
     */
    const Timestamp& GetTimestamp() const noexcept
    {
        return this->timestamp_;
    }

    /**
     * @brief Assign message timestamp.
     * 
     * @param[in] header A timestamp object.
     * @return Returns nothing.
     */
    void SetTimestamp(const Timestamp& header) noexcept
    {
        this->timestamp_ = header;
    }

    /**
     * @brief Access status code value.
     * 
     * @return Returns a code value.
     */
    MapCodeType GetStatusCode() const noexcept
    {
        return this->code_;
    }

    /**
     * @brief Assign code value to current status.
     * 
     * @param[in] code Code value.
     * @return Returns nothing.
     */
    void SetStatusCode(const MapCodeType code) noexcept
    {
        this->code_ = code;
    }
    
private:
    /// Message stamp
    Timestamp timestamp_;
    /// Code value
    MapCodeType code_ = 0U;
};

/**
 * @}
 */
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_MAP_APP_STATUS_H_ */
