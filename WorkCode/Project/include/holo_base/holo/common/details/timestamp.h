/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file timestamp.h
 * @brief This header file defines Timestamp class and Duration Class
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-03
 */

#ifndef HOLO_COMMON_DETAILS_TIMESTAMP_H_
#define HOLO_COMMON_DETAILS_TIMESTAMP_H_

#include <cmath>
#include <limits>
#include <sstream>
#include <stdexcept>

#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace common
{
namespace details
{
/**
 * @brief This class represents a overflow exception
 *
 */
class OverflowException : public std::exception
{
};

/**
 * @brief This class represents a period of time.
 *
 */
class Duration
{
public:
    /**
     * @brief default constructor
     *
     * Constructor with no parameter
     */
    Duration() : sec_{0}, nsec_{0}
    {
    }

    /**
     * @brief Constructor
     *
     * Construct from sec and nsec
     * @param sec [in] seconds
     * @param nsec [in] nanoseconds
     *
     * @throws holo::common::OverflowException if
     * (sec * NSEC_PER_SEC + nsec) > DURATION_MAX_NSEC
     * or (sec * NSEC_PER_SEC + nsec) < DURATION_MIN_NSEC
     */
    Duration(int32_t sec, int32_t nsec)
    {
        int64_t value = static_cast<int64_t>(sec) * NSEC_PER_SEC + nsec;
        assignFromNsecValue(value);
    }

    /**
     * @brief Constructor
     *
     * Construct from float64_t second
     * @param[in] t seconds
     *
     * @throws holo::common::OverflowException if
     * t > DURATION_MAX_NSEC or t < DURATION_MIN_NSEC
     */
    explicit Duration(float64_t t)
    {
        sec_  = 0;
        nsec_ = 0;
        if ((t >= static_cast<float64_t>(DURATION_MAX_NSEC / NSEC_PER_SEC + 1)) ||
            (t < static_cast<float64_t>(DURATION_MIN_NSEC / NSEC_PER_SEC)))
        {
            throw OverflowException();
        }
        else
        {
            float64_t nsec  = t * NSEC_PER_SEC;
            int64_t   value = static_cast<int64_t>(nsec);
            value           = value > DURATION_MAX_NSEC ? DURATION_MAX_NSEC : value;
            assignFromNsecValue(value);
        }
    }

    /**
     * @brief Constructor
     *
     * Construct from int64_t nano second
     * @param[in] t nano seconds
     *
     * @throws holo::common::OverflowException if
     * t > DURATION_MAX_NSEC or t < DURATION_MIN_NSEC
     */
    explicit Duration(int64_t t)
    {
        assignFromNsecValue(t);
    }

    /**
     * @brief add two durations.
     *
     * @param rhs right hand side duration object
     * @return Duration
     *
     */
    Duration operator+(Duration const& rhs) const
    {
        int64_t out = this->ToNsec() + rhs.ToNsec();
        return Duration(out);
    }

    /**
     * @brief substract two durations.
     *
     * @param rhs right hand side duration object
     * @return Duration
     */
    Duration operator-(Duration const& rhs) const
    {
        int64_t out = this->ToNsec() - rhs.ToNsec();
        return Duration(out);
    }

    /**
     * @brief negate duration
     *
     * @return Duration
     */
    Duration operator-() const
    {
        return Duration(-sec_, -nsec_);
    }

    /**
     * @brief scale duration
     *
     * @param rhs the scale factor
     * @return Duration
     */
    Duration operator*(float64_t rhs) const
    {
        int64_t out = this->ToNsec() * rhs;
        return Duration(out);
    }

    /**
     * @brief multiply a scalar with a Duration
     *
     * @param lhs a scalar
     * @param rhs a Duration
     * @return Duration
     */
    friend Duration operator*(float64_t lhs, Duration const& rhs)
    {
        int64_t out = rhs.ToNsec() * lhs;
        return Duration(out);
    }

    /**
     * @brief += operator overloading
     *
     * @param rhs right hand side duration object
     * @return Duration&
     *
     * @throws holo::common::OverflowException if
     * (this->ToNsec() + rhs.ToNsec()) > DURATION_MAX_NSEC
     * or (this->ToNsec() + rhs.ToNsec()) < DURATION_MIN_NSEC
     */
    Duration& operator+=(Duration const& rhs)
    {
        int64_t out = this->ToNsec() + rhs.ToNsec();
        assignFromNsecValue(out);
        return *this;
    }

    /**
     * @brief -= operator overloading
     *
     * @param rhs right hand side duration object
     * @return Duration&
     *
     * @throws holo::common::OverflowException if
     * (this->ToNsec() - rhs.ToNsec()) > DURATION_MAX_NSEC
     * or (this->ToNsec() - rhs.ToNsec()) < DURATION_MIN_NSEC
     */
    Duration& operator-=(Duration const& rhs)
    {
        int64_t out = this->ToNsec() - rhs.ToNsec();
        assignFromNsecValue(out);
        return *this;
    }

    /**
     * @brief *= operator overloading
     *
     * @param scale the scale factor
     * @return Duration&
     *
     * @throws holo::common::OverflowException if
     * (this->ToNsec() * scale) > DURATION_MAX_NSEC
     * or (this->ToNsec() * scale) < DURATION_MIN_NSEC
     */
    Duration& operator*=(float64_t scale)
    {
        int64_t out = this->ToNsec() * scale;
        assignFromNsecValue(out);
        return *this;
    }

    /**
     * @brief == operator overloading
     *
     * @param rhs right hand side duration object
     * @return true if the duration is equivalent to another.
     * @return false if the duration isn't equivalent to another.
     */
    bool_t operator==(Duration const& rhs) const
    {
        return this->ToNsec() == rhs.ToNsec();
    }

    /**
     * @brief != operator overloading
     *
     * @param rhs right hand side duration object
     * @return true if the duration isn't equivalent to another.
     * @return false if the duration is equivalent to another.
     */
    bool_t operator!=(Duration const& rhs) const
    {
        return !(*this == rhs);
    }

    /**
     * @brief > operator overloading
     *
     * @param rhs right hand side duration object
     * @return true if lhs is larger than rhs.
     * @return false if lhs isn't larger than rhs.
     */
    bool_t operator>(Duration const& rhs) const
    {
        return this->ToNsec() > rhs.ToNsec();
    }

    /**
     * @brief < operator overloading
     *
     * @param rhs right hand side duration object
     * @return true if lhs is less than rhs.
     * @return false if lhs isn't less than rhs.
     */
    bool_t operator<(Duration const& rhs) const
    {
        return this->ToNsec() < rhs.ToNsec();
    }

    /**
     * @brief >= operator overloading
     *
     * @param rhs right hand side duration object
     * @return true if lhs isn't less than rhs.
     * @return false if lhs is less than rhs.
     */
    bool_t operator>=(Duration const& rhs) const
    {
        return !(*this < rhs);
    }

    /**
     * @brief < operator overloading
     *
     * @param rhs right hand side duration object
     * @return true if lhs isn't larger than rhs.
     * @return false if lhs is larger than rhs.
     */
    bool_t operator<=(Duration const& rhs) const
    {
        return !(*this > rhs);
    }

    /**
     * @brief Convert Duration to float64_t second
     * @return float64_t second
     * @note This conversion may cause precision loss
     */
    float64_t ToSec() const
    {
        return (static_cast<float64_t>(this->ToNsec())) / NSEC_PER_SEC;
    }

    /**
     * @brief Convert Duration to nanoseconds
     * @return int64_t nanoseconds
     */
    int64_t ToNsec() const
    {
        return static_cast<int64_t>(this->sec_) * NSEC_PER_SEC + this->nsec_;
    }

    /**
     * @brief check if the duration is equal to zero
     *
     * @return true the duration is equal to zero
     * @return false the duration isn't equal to zero
     */
    bool_t IsZero() const
    {
        return this->ToNsec() == 0;
    }

    /**
     * @brief Determine if two Durations are equal.
     * @param[in] rhs Right hand side
     * @param tolerance_nsec tolerance nanoseconds, default 0.
     * @return Return true if the absolute value of difference between
     * this and rhs is less than tolerance_nsec nanoseconds. Otherwise false.
     */
    bool_t IsEqual(Duration const& rhs, uint32_t tolerance_nsec = 0) const
    {
        return std::abs(this->ToNsec() - rhs.ToNsec()) <= tolerance_nsec;
    }

    /**
     * @brief Get second field of duration object.
     *
     * @return int32_t second
     */
    int32_t GetSec() const
    {
        int32_t sec = this->sec_;
        if (this->nsec_ < 0)
        {
            sec -= 1;
        }
        return sec;
    }

    /**
     * @brief Set second field of duration object.
     *
     * @param seconds
     *
     * @throws holo::common::OverflowException  if
     * (seconds * NSEC_PER_SEC + this->nsec_) > DURATION_MAX_NSEC
     * or (seconds * NSEC_PER_SEC + this->nsec_) < DURATION_MIN_NSEC
     */
    void SetSec(int32_t const seconds)
    {
        int64_t nsec = seconds * NSEC_PER_SEC + this->nsec_;
        checkValue(nsec);
        this->sec_ = seconds;
    }

    /**
     * @brief Get nano second field of duration object.
     *
     * @return int32_t
     */
    int32_t GetNsec() const
    {
        int32_t nsec = this->nsec_;
        if (nsec < 0)
        {
            nsec += NSEC_PER_SEC;
        }
        return nsec;
    }

    /**
     * @brief Set nano second field of duration object.
     *
     * @param nseconds second
     * @throws holo::common::OverflowException if
     * nseconds > (NSEC_PER_SEC - 1) or nseconds < (-NSEC_PER_SEC + 1)
     */
    void SetNsec(int32_t const nseconds)
    {
        if (nseconds > (NSEC_PER_SEC - 1) || nseconds < (-NSEC_PER_SEC + 1))
        {
            throw OverflowException();
        }
        else
        {
            this->nsec_ = nseconds;
        }
    }

    /**
     * @brief Convert duration to string
     *
     * @return std::string
     */
    std::string ToString() const
    {
        std::stringstream ss;
        ss << "Duration: (" << this->GetSec() << ", " << this->GetNsec() << ")" << std::endl;
        return ss.str();
    }

    /**
     * @brief The conversion between sec and nsec
     */
    static int32_t const NSEC_PER_SEC = 1000000000;

    /**
     * @brief Maximum nsec value of duration
     */
    static int64_t const DURATION_MAX_NSEC =
        static_cast<int64_t>(std::numeric_limits<int32_t>::max()) * 1000000000 + 999999999;

    /**
     * @brief Minimum nsec value of duration
     */
    static int64_t const DURATION_MIN_NSEC = static_cast<int64_t>(std::numeric_limits<int32_t>::min()) * 1000000000;

private:
    int32_t sec_;
    int32_t nsec_;

    /**
     * @brief check the value is within the limits or not
     *
     * @param value the value needs to be checked
     *
     * @throws holo::common::OverflowException if
     * value > DURATION_MAX_NSEC or size < DURATION_MIN_NSEC
     *
     */
    static void checkValue(int64_t const value)
    {
        if (value > DURATION_MAX_NSEC || value < DURATION_MIN_NSEC)
        {
            throw OverflowException();
        }
    }

    /**
     * @brief assign From Nsec
     *
     * @param value Nsec value
     *
     */
    void assignFromNsecValue(int64_t value)
    {
        checkValue(value);
        this->sec_  = value / NSEC_PER_SEC;
        this->nsec_ = value % NSEC_PER_SEC;
    }
};

/**
 * @brief This class represents a time point in nanosecond precision.
 */
class Timestamp
{
public:
    /**
     * @brief Constructor
     *
     * Constructor with no argument
     */
    Timestamp() : sec_{0}, nsec_{0}
    {
    }

    /**
     * @brief Constructor
     *
     * Constructor with sec and nsec.
     * @param[in] sec seconds
     * @param[in] nsec nanoseconds
     *
     * @throws holo::common::OverflowException if
     * (sec * NSEC_PER_SEC + nsec) > TIMESTAMP_MAX_NSEC
     * or (sec * NSEC_PER_SEC + nsec) < TIMESTAMP_MIN_NSEC
     */
    Timestamp(uint32_t sec, uint32_t nsec)
    {
        sec_          = 0U;
        nsec_         = 0U;
        int64_t value = static_cast<int64_t>(sec) * NSEC_PER_SEC + nsec;
        assignFromNsecValue(value);
    }

    /**
     * @brief Contruct from float64_t seconds
     * @param[in] t seconds
     *
     * @throws holo::common::OverflowException if
     * (t * NSEC_PER_SEC) > TIMESTAMP_MAX_NSEC
     * or (t * NSEC_PER_SEC) < TIMESTAMP_MIN_NSEC
     * or t > TIMESTAMP_MAX_SEC or t < TIMESTAMP_MIN_SEC
     */
    explicit Timestamp(float64_t t)
    {
        sec_  = 0U;
        nsec_ = 0U;
        if (t >= static_cast<float64_t>(TIMESTAMP_MAX_NSEC / NSEC_PER_SEC + 1U))
        {
            throw OverflowException();
        }
        else
        {
            float64_t nsec  = t * NSEC_PER_SEC;
            int64_t   value = static_cast<int64_t>(nsec);
            value           = value > TIMESTAMP_MAX_NSEC ? TIMESTAMP_MAX_NSEC : value;
            assignFromNsecValue(value);
        }
    }

    /**
     * @brief Contruct from uint64_t nano seconds
     * @param[in] t nano seconds
     *
     * @throws holo::common::OverflowException if
     * t > TIMESTAMP_MAX_NSEC or t < TIMESTAMP_MIN_NSEC
     */
    explicit Timestamp(uint64_t t)
    {
        assignFromNsecValue(static_cast<int64_t>(t));
    }

    /**
     * @brief Timestamp subtract timestamp
     *
     * @param rhs right hand side timestamp object
     * @return Duration
     */
    Duration operator-(Timestamp const& rhs) const
    {
        int64_t out = this->ToNsec() - rhs.ToNsec();
        return Duration(out);
    }

    /**
     * @brief Timestamp add duration
     *
     * @param rhs right hand side duration object
     * @return Timestamp
     */
    Timestamp operator+(Duration const& rhs) const
    {
        int64_t out = this->ToNsec() + rhs.ToNsec();
        return Timestamp(static_cast<uint64_t>(out));
    }

    /**
     * @brief Timestamp subtract duration
     *
     * @param rhs right hand side duration object
     * @return Timestamp
     */
    Timestamp operator-(Duration const& rhs) const
    {
        int64_t out = this->ToNsec() - rhs.ToNsec();
        return Timestamp(static_cast<uint64_t>(out));
    }

    /**
     * @brief += operator overloading
     *
     * @param rhs right hand side duration object
     * @return Timestamp&
     *
     * @throws holo::common::OverflowException if
     * (this->ToNsec() + rhs.ToNsec()) > TIMESTAMP_MAX_NSEC
     * or (this->ToNsec() + rhs.ToNsec()) < TIMESTAMP_MIN_NSEC
     */
    Timestamp& operator+=(Duration const& rhs)
    {
        int64_t out = this->ToNsec() + rhs.ToNsec();
        assignFromNsecValue(out);
        return *this;
    }

    /**
     * @brief -= operator overloading
     *
     * @param rhs right hand side duration object
     * @return Timestamp&
     *
     * @throws holo::common::OverflowException if
     * (this->ToNsec() - rhs.ToNsec()) > TIMESTAMP_MAX_NSEC
     * or (this->ToNsec() - rhs.ToNsec()) < TIMESTAMP_MIN_NSEC
     */
    Timestamp& operator-=(Duration const& rhs)
    {
        int64_t out = this->ToNsec() - rhs.ToNsec();
        assignFromNsecValue(out);
        return *this;
    }

    /**
     * @brief == operator overloading
     *
     * @param rhs right hand side timestamp object
     * @return true if the timestamp is equivalent to another.
     * @return false if the timestamp isn't equivalent to another.
     */
    bool_t operator==(Timestamp const& rhs) const
    {
        return this->ToNsec() == rhs.ToNsec();
    }

    /**
     * @brief != operator overloading
     *
     * @param rhs right hand side timestamp object
     * @return true if the timestamp isn't equivalent to another.
     * @return false if the timestamp is equivalent to another.
     */
    bool_t operator!=(Timestamp const& rhs) const
    {
        return !(*this == rhs);
    }

    /**
     * @brief > operator overloading
     *
     * @param rhs right hand side duration object
     * @return true if lhs is larger than rhs.
     * @return false if lhs isn't larger than rhs.
     */
    bool_t operator>(Timestamp const& rhs) const
    {
        return this->ToNsec() > rhs.ToNsec();
    }

    /**
     * @brief < operator overloading
     *
     * @param rhs right hand side duration object
     * @return true if lhs is less than rhs.
     * @return false if lhs isn't less than rhs.
     */
    bool_t operator<(Timestamp const& rhs) const
    {
        return this->ToNsec() < rhs.ToNsec();
    }

    /**
     * @brief >= operator overloading
     *
     * @param rhs right hand side duration object
     * @return true if lhs isn't less than rhs.
     * @return false if lhs is less than rhs.
     */
    bool_t operator>=(Timestamp const& rhs) const
    {
        return !(*this < rhs);
    }

    /**
     * @brief <= operator overloading
     *
     * @param rhs right hand side duration object
     * @return true if lhs isn't larger than rhs.
     * @return false if lhs is larger than rhs.
     */
    bool_t operator<=(Timestamp const& rhs) const
    {
        return !(*this > rhs);
    }

    /**
     * @brief check if the timestamp is equal to zero
     *
     * @return true the timestamp is equal to zero
     * @return false the timestamp isn't equal to zero
     */
    bool_t IsZero() const
    {
        return this->ToNsec() == 0;
    }

    /**
     * @brief Determine if two Timestamps are equal.
     * @param[in] rhs Right hand side
     * @param tolerance_nsec tolerance nanoseconds, default 0.
     * @return Return true if the absolute value of difference between
     * this and rhs is less than tolerance_nsec nanoseconds. Otherwise false.
     */
    bool_t IsEqual(Timestamp const& rhs, uint32_t tolerance_nsec = 0) const
    {
        return std::abs(ToNsec() - rhs.ToNsec()) <= tolerance_nsec;
    }

    /**
     * @brief Convert Timestamp to float64_t second
     * @return float64_t second
     * @note This conversion may cause precision loss
     */
    float64_t ToSec() const
    {
        return (static_cast<float64_t>(this->ToNsec())) / NSEC_PER_SEC;
    }

    /**
     * @brief Convert Timestamp to nanoseconds
     * @return uint64_t nanoseconds
     */
    int64_t ToNsec() const
    {
        return static_cast<int64_t>(this->sec_) * NSEC_PER_SEC + this->nsec_;
    }

    /**
     * @brief Construct GPS Timestamp from UTC Timestamp
     * @param[in] utc UTC Timestamp
     * @param[out] gps GPS Timestamp
     * @return true of the conversion is valid otherwise return false
     */
    static bool UtcToGps(Timestamp const& utc, Timestamp& gps)
    {
        bool ret = false;
        gps      = Timestamp(0, 0);
        if (utc.GetSec() > kLatestLeapSecondUtc)
        {
            gps = Timestamp(utc.GetSec() - kUtcGpsGap + kLatestLeapSecond, utc.GetNsec());
            ret = true;
        }
        return ret;
    }

    /**
     * @brief Construct UTC Timestamp from GPS Timestamp
     * @param[in] gps GPS Timestamp
     * @param[out] utc UTC Timestamp
     * @return true of the conversion is valid otherwise return false
     */
    static bool GpsToUtc(Timestamp const& gps, Timestamp& utc)
    {
        bool ret = false;
        utc      = Timestamp(0, 0);
        if (gps.GetSec() > kLatestLeapSecondGps)
        {
            utc = Timestamp(gps.GetSec() - kLatestLeapSecond + kUtcGpsGap, gps.GetNsec());
            ret = true;
        }
        return ret;
    }

    /**
     * @brief Construct GPS Timestamp from NTP Timestamp
     * @deprecated Deprecated NtpToGps function
     * @param[in] ntp NTP Timestamp
     * @param[out] gps GPS Timestamp
     * @return true of the conversion is valid otherwise return false
     */
    [[deprecated]] static bool NtpToGps(Timestamp const& ntp, Timestamp& gps)
    {
        Timestamp utc(0, 0);
        if (ntp.GetSec() > kNtpUtcGap)
        {
            utc = Timestamp(ntp.GetSec() - kNtpUtcGap, ntp.GetNsec());
        }
        return UtcToGps(utc, gps);
    }

    /**
     * @brief Get the Sec object
     *
     * @return uint32_t
     */
    uint32_t GetSec() const
    {
        return this->sec_;
    }

    /**
     * @brief Set the Sec object
     *
     * @param seconds
     */
    void SetSec(uint32_t const seconds)
    {
        this->sec_ = seconds;
    }

    /**
     * @brief Get the Nsec object
     *
     * @return uint32_t
     */
    uint32_t GetNsec() const
    {
        return this->nsec_;
    }

    /**
     * @brief Set the Nsec object
     *
     * @param nseconds nano second of timestamp
     *
     * @throws holo::common::OverflowException if nseconds >= NSEC_PER_SEC
     */
    void SetNsec(uint32_t const nseconds)
    {
        if (nseconds >= NSEC_PER_SEC)
        {
            throw OverflowException();
        }
        else
        {
            this->nsec_ = nseconds;
        }
    }

    /**
     * @brief Convert timestamp to string
     *
     * @return std::string
     */
    std::string ToString() const
    {
        std::stringstream ss;
        ss << "Timestamp: (" << GetSec() << ", " << GetNsec() << ")" << std::endl;
        return ss.str();
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(sec_, nsec_);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << sec_ << nsec_ << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> holo::serialization::align >> sec_ >> nsec_ >> holo::serialization::align;
    }

    /**
     * @brief The conversion between sec and nsec
     */
    static int32_t const NSEC_PER_SEC = 1000000000;

    /**
     * @brief Maximum nsec value of timestamp
     */
    static int64_t const TIMESTAMP_MAX_NSEC =
        static_cast<int64_t>(std::numeric_limits<uint32_t>::max()) * 1000000000 + 999999999;

    /**
     * @brief Minimum nsec value of timestamp
     */
    static int64_t const TIMESTAMP_MIN_NSEC = 0;

private:
    uint32_t sec_;
    uint32_t nsec_;

    /**
     * @brief check the value is within the limits or not
     *
     * @param value the value needs to be checked
     *
     * @throws holo::common::OverflowException if
     * value > TIMESTAMP_MAX_NSEC or size < TIMESTAMP_MIN_NSEC
     *
     */
    static void checkValue(int64_t const value)
    {
        if (value > TIMESTAMP_MAX_NSEC || value < TIMESTAMP_MIN_NSEC)
        {
            throw OverflowException();
        }
    }

    /**
     * @brief assign From Nsec
     *
     * @param value Nsec value
     *
     */
    void assignFromNsecValue(int64_t value)
    {
        checkValue(value);
        this->sec_  = value / NSEC_PER_SEC;
        this->nsec_ = value % NSEC_PER_SEC;
    }

    /**
     * utc timestamp represents the seconds since 1970-01-01 00:00:00 without
     *considering leap second gps timestamp represents the seconds since
     *1980-01-06 00:00:00 considering leap second ntp timestamp represents the
     *seconds since 1900-01-01 00:00:00 without considering leap second
     *
     * leap second: an intercalary second added to Coordinated Universal Time
     * to compensate for the slowing of the earth's rotation and
     * keep Coordinated Universal Time in synchrony with solar time
     *
     * leap second could be positive and also be negative
     * there is no rules to find out if we need to update leap second, therefore
     *we first set it to a constant value for now
     **/

    // time diff between gps and utc timesamp without leap second: gps - utc
    static uint32_t const kUtcGpsGap = 315964800;
    // time diff between utc and ntp timesamp without leap second: utc - ntp
    static uint32_t const kNtpUtcGap = 2208988800;
    // leap second to 2016-12-31 23:59:59
    static uint32_t const kLatestLeapSecond = 18;
    // the utc second since the latest leap second changed;
    static uint32_t const kLatestLeapSecondUtc = 1467331199;
    // the gps second since the latest leap second changed;
    static uint32_t const kLatestLeapSecondGps = 1151366416;
};

}  // namespace details
}  // namespace common
}  // namespace holo

#endif /* HOLO_COMMON_DETAILS_TIMESTAMP_H_ */
