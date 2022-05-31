/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_raw_measurement.h
 * @brief This header file define Raw Measurement of GNSS
 * @author houyujian@holomatic.com
 * @date Dec 18, 2019
 */

#ifndef HOLO_COMMON_GNSS_RAW_MEASUREMENT_H_
#define HOLO_COMMON_GNSS_RAW_MEASUREMENT_H_

#include <exception>

#include <holo/common/timestamp.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>

namespace holo
{
namespace common
{
/**
 * @addtogroup common
 * @{
 *
 */

class GnssRawMeasurement
{
public:
    static size_t const MAX_SATELLITE_NUM = 40U;
    static size_t const SEC_PER_WEEK      = 604800U;

    /**
     * @brief pseudorange, Doppler, carrier phase, phase lock and signal quality
            information for GNSS satellites once signal
     *
     */
    struct RawMeasurementBlock
    {
        float64_t pseudorange_measurement;           ///< Pseudorange measurement
        float64_t carrier_phase_measurement;         ///< Carrier phase measurement
        float32_t doppler_measurement;               ///< Doppler measurement
        uint8_t   gnss_identifier;                   ///< GNSS identifier
        uint8_t   satellite_identifier;              ///< Satellite identifier
        uint8_t   frequence_identifier;              ///< Only used for GLONASS
        uint16_t  carrier_phase_locktime;            ///< Carrier phase locktime counter
        uint8_t   carrier_noise_ratio;               ///< Carrier-to-noise density ratio
        uint8_t   pseudorange_standard_deviation;    ///< Estimated pseudorange measurement standard deviation
        uint8_t   carrier_phase_standard_deviation;  ///< Estimated carrier phase measurement standard deviation
        uint8_t   doppler_standard_deviation;        ///< Estimated Doppler measurement standard deviation
        uint8_t   tracking_status;                   ///< Tracking status bitfield

        template <size_t ALIGN = 4U>
        size_t GetSerializedSize() const noexcept
        {
            return holo::serialization::SerializedSize<ALIGN>(
                pseudorange_measurement, carrier_phase_measurement, doppler_measurement, gnss_identifier,
                satellite_identifier, frequence_identifier, carrier_phase_locktime, carrier_noise_ratio,
                pseudorange_standard_deviation, carrier_phase_standard_deviation, doppler_standard_deviation,
                tracking_status);
        }

        template <typename S>
        void Serialize(S& serializer) const
        {
            serializer << holo::serialization::align << pseudorange_measurement << carrier_phase_measurement
                       << doppler_measurement << gnss_identifier << satellite_identifier << frequence_identifier
                       << carrier_phase_locktime << carrier_noise_ratio << pseudorange_standard_deviation
                       << carrier_phase_standard_deviation << doppler_standard_deviation << tracking_status
                       << holo::serialization::align;
        }

        template <typename D>
        void Deserialize(D& deserializer)
        {
            deserializer >> holo::serialization::align >> pseudorange_measurement >> carrier_phase_measurement >>
                doppler_measurement >> gnss_identifier >> satellite_identifier >> frequence_identifier >>
                carrier_phase_locktime >> carrier_noise_ratio >> pseudorange_standard_deviation >>
                carrier_phase_standard_deviation >> doppler_standard_deviation >> tracking_status >>
                holo::serialization::align;
        }
    };
    static_assert(sizeof(RawMeasurementBlock) == 32U, "");

    /**
     * @brief GNSS Type Id
     *
     */
    enum class GnssId : uint8_t
    {
        GPS     = 0U,
        SBAS    = 1U,
        GALILEO = 2U,
        BEIDOU  = 3U,
        IMES    = 4U,
        QZSS    = 5U,
        GLONASS = 6U
    };

    /**
     * @brief default constructor
     */
    GnssRawMeasurement() noexcept
      : gps_second_(0.0f)      ///< measurement time of week
      , gps_week_(0u)          ///< gps week number
      , leap_second_(0u)       ///< gps leap seconds
      , satellite_number_(0u)  ///< number of measurements to follow
      , pdop_(0u)              ///< position Dop
      , raw_block_{}
    {
    }

    /**
     * @brief get Timestamp
     *
     * @return Reference to timestamp
     */
    Timestamp GetTimestamp() const noexcept
    {
        float64_t gnss_sec = gps_week_ * SEC_PER_WEEK + gps_second_;
        Timestamp stamp;
        stamp.SetSec((uint32_t)gnss_sec);
        return stamp;
    }

    /**
     * @brief return Measurement time of week
     *
     * @return gps_second
     */
    float64_t GetGpsSec() const noexcept
    {
        return gps_second_;
    }

    /**
     * @brief set Measurement time of week
     *
     * @param[in] gps_second
     */
    void SetGpsSec(const float64_t gps_second) noexcept
    {
        this->gps_second_ = gps_second;
    }

    /**
     * @brief return GPS week number
     *
     * @return gps_week
     */
    uint16_t GetGpsWeek() const noexcept
    {
        return gps_week_;
    }

    /**
     * @brief set GPS week number
     *
     * @param[in] gps_week
     */
    void SetGpsWeek(const uint16_t gps_week) noexcept
    {
        this->gps_week_ = gps_week;
    }

    /**
     * @brief return GPS leap seconds
     *
     * @return leap_second
     */
    int8_t GetLeapSec() const noexcept
    {
        return leap_second_;
    }

    /**
     * @brief set GPS leap seconds
     *
     * @param[in] leap_second
     */
    void SetLeapSec(const int8_t leap_second) noexcept
    {
        this->leap_second_ = leap_second;
    }

    /**
     * @brief return the Number of measurements to follow
     *
     * @return satellite_number
     */
    uint8_t GetSatelliteNumber() const noexcept
    {
        return satellite_number_;
    }

    /**
     * @brief set the Number of measurements to follow
     *
     * @param[in] satellite_number
     */
    void SetSatelliteNumber(const uint8_t satellite_number) noexcept
    {
        this->satellite_number_ = satellite_number;
    }

    /**
     * @brief return Position Dop
     *
     * @return pDop
     */
    float32_t GetPDop() const noexcept
    {
        return pdop_;
    }

    /**
     * @brief set Position Dop
     *
     * @param[in] pDop
     */
    void SetPDop(const float32_t pDop) noexcept
    {
        this->pdop_ = pDop;
    }

    /**
     * @brief Get the Raw Measurement Block object
     *
     * @param raw_block
     * @param index
     */
    void GetRawMeasurementBlock(struct RawMeasurementBlock& raw_block, const uint32_t index) const
    {
        if (index >= GetSatelliteNumber())
        {
            throw holo::exception::OutOfRangeException("Invalid RawBlock index!");
        }

        raw_block = raw_block_[index];
    }

    /**
     * @brief Set the Raw Measurement Block object
     *
     * @param raw_block
     * @param index
     */
    void SetRawMeasurementBlock(struct RawMeasurementBlock const& raw_block, const uint32_t index)
    {
        if (index >= GetSatelliteNumber())
        {
            throw holo::exception::OutOfRangeException("Invalid RawBlock index!");
        }

        raw_block_[index] = raw_block;
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
        size_t align_size =
            holo::serialization::SerializedSize<ALIGN>(gps_second_, gps_week_, leap_second_, satellite_number_, pdop_);
        if (satellite_number_ > 0)
        {
            align_size += satellite_number_ * raw_block_[0].GetSerializedSize<ALIGN>();
        }
        return align_size;
    }

    /**
     * @brief Serialize to buffer.
     *
     * @tparam S Serializer type.
     * @param serializer The serializer object.
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << gps_second_ << gps_week_ << leap_second_ << satellite_number_
                   << pdop_;
        for (uint32_t i = 0; i < satellite_number_; i++)
        {
            serializer << raw_block_[i];
        }
    }

    /**
     * @brief Deserialize from buffer.
     *
     * @tparam D Deserializer type.
     * @param Deserializer The deserializer object.
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> holo::serialization::align >> gps_second_ >> gps_week_ >> leap_second_ >> satellite_number_ >>
            pdop_;
        for (uint32_t i = 0; i < satellite_number_; i++)
        {
            deserializer >> raw_block_[i];
        }
    }

private:
    float64_t           gps_second_;        ///< measurement time of week
    uint16_t            gps_week_;          ///< gps week number
    int8_t              leap_second_;       ///< gps leap seconds
    uint8_t             satellite_number_;  ///< number of measurements to follow
    float32_t           pdop_;              ///< position Dop
    RawMeasurementBlock raw_block_[MAX_SATELLITE_NUM];
};

/**
 * @}
 *
 */

}  // namespace common
}  // namespace holo

#endif /* HOLO_COMMON_GNSS_RAWDATA_H */
