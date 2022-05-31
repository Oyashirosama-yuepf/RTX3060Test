/*!
 * @file diagnostics.h
 * @brief This header file define the diagnostics of algorithm
 * @author lichao@holomatic.com
 * @date Sep 24, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_LOCALIZATION_COMMON_DIAGNOSTICS_H_
#define HOLO_LOCALIZATION_COMMON_DIAGNOSTICS_H_

#include <holo/common/timestamp.h>

namespace holo
{
namespace localization
{
/**
 * @ingroup localization
 * @brief diagnostics class
 *
 * @details this class mainly aims at holding all of diagnostics information in
 * localization module.
 */
class Diagnostics
{
public:
    using Timestamp = holo::common::Timestamp;

    /**
     * @brief constructor
     */
    Diagnostics() : Timestamp_(0, 0), system_timestamp_(0, 0), status_(0)
    {
    }

    /**
     * @brief destructor
     */
    virtual ~Diagnostics() noexcept
    {
    }

    /**
     * @brief Get the Timestamp object
     *
     * @return const Timestamp& Timestamp
     */
    const Timestamp& GetTimestamp() const
    {
        return Timestamp_;
    }

    /**
     * @brief Get the Timestamp object
     *
     * @return Timestamp& Timestamp
     */
    Timestamp& GetTimestamp()
    {
        return Timestamp_;
    }

    /**
     * @brief Set the Timestamp object
     *
     * @param Timestamp
     */
    void SetTimestamp(const Timestamp& Timestamp)
    {
        Timestamp_ = Timestamp;
    }

    /**
     * @brief Get the System Timestamp object
     *
     * @return const Timestamp& system Timestamp
     */
    const Timestamp& GetSystemTimestamp() const noexcept
    {
        return system_timestamp_;
    }

    /**
     * @brief Get the System Timestamp object
     *
     * @return Timestamp& system Timestamp
     */
    Timestamp& GetSystemTimestamp() noexcept
    {
        return system_timestamp_;
    }

    /**
     * @brief Set the System Timestamp object
     *
     * @param system_timestamp system Timestamp
     */
    void SetSystemTimestamp(const Timestamp& system_timestamp) noexcept
    {
        system_timestamp_ = system_timestamp;
    }

    /**
     * @brief Get the Status object reference
     *
     * @return uint32_t& diagnostics status reference
     */
    uint32_t& GetStatus()
    {
        return status_;
    }

    /**
     * @brief Get the Status object
     *
     * @return uint32_t& diagnostics status
     */
    uint32_t GetStatus() const
    {
        return status_;
    }

    /**
     * @brief Set the Status object
     *
     * @param status diagnostics status
     */
    void SetStatus(const uint32_t status)
    {
        status_ = status;
    }

    /**
     * @brief Convert diagnostics status to string
     *
     * @return std::string string of diagnostics
     */
    std::string ToString() const
    {
        std::string result;
        if (status_ == kGood_)
        {
            result.append("Good");
        }
        else
        {
            if (status_ & kImuNotGood_)
            {
                result.append("ImuNotGood;");
            }
            if (status_ & kGpsNotGood_)
            {
                result.append("GpsNotGood;");
            }
            if (status_ & kImageNotGood_)
            {
                result.append("ImageNotGood;");
            }
            if (status_ & kChassisStateNotGood_)
            {
                result.append("ChassisStateNotGood;");
            }
        }

        // convert state
        if (status_ & kWaitState_)
        {
            result.append("Wait;");
        }
        else if (status_ & kReadyState_)
        {
            result.append("Ready;");
        }
        else if (status_ & kIdleState_)
        {
            result.append("Idle;");
        }
        else if (status_ & kRunState_)
        {
            result.append("Run;");
        }
        return result;
    }

    static const uint32_t kGood_                = 0x0000; /* all good */
    static const uint32_t kImuNotGood_          = 0x0001; /* no good imu measurement */
    static const uint32_t kGpsNotGood_          = 0x0002; /* no good gps measurement */
    static const uint32_t kImageNotGood_        = 0x0004; /* no good image measurement */
    static const uint32_t kChassisStateNotGood_ = 0x0008; /* no good chassis state measurement */
    static const uint32_t kWaitState_           = 0x1000; /* wait state */
    static const uint32_t kReadyState_          = 0x2000; /* ready state */
    static const uint32_t kIdleState_           = 0x4000; /* idle state */
    static const uint32_t kRunState_            = 0x8000; /* run state */

private:
    Timestamp Timestamp_;        /* the Timestamp of measurement */
    Timestamp system_timestamp_; /* the Timestamp of system */
    uint32_t  status_;           /* diagnostics status */

};  // class Diagnostics

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_COMMON_DIAGNOSTICS_H_
