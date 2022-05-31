/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file packeddata.h
 * @brief the packed data definition
 * @author wujie@holomatic.com
 * @date 2021-8-26
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#ifndef HOLO_SENSORS_FORMAT_PACKEDDATA_H
#define HOLO_SENSORS_FORMAT_PACKEDDATA_H

#include <assert.h>
#include <holo/core/types.h>
#include <holo/os/endian.h>
#include <holo/sensors/format/format.h>
#include <holo/sensors/utils/livox_crc.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <cstring>
#include <memory>

namespace holo
{
namespace sensors
{
namespace format
{
/**
 * @brief this class describes packed data
 */
template <uint32_t PayloadCapacity>
class SensorCompressedPacket
{
private:
    struct sensors_packed_data
    {
        uint16_t              header;
        uint16_t              version;
        uint32_t              sensor_id;
        uint32_t              raw_data_len;
        uint32_t              compress_data_len;
        DataCompressAlgorithm compress_algorithm;
        uint8_t               compress_algorithm_desc[16];
        uint8_t               payload[PayloadCapacity];
        uint8_t               checksum_crc[4];
    };

public:
    SensorCompressedPacket();
    SensorCompressedPacket(uint16_t header, uint16_t version, uint32_t sensor_id, uint32_t raw_data_len,
                           uint32_t compress_data_len, DataCompressAlgorithm compress_algorithm);

    void     SetHeader(uint16_t header) noexcept;
    void     SetVersion(uint16_t version) noexcept;
    void     SetSensorId(uint32_t sensor_id) noexcept;
    void     SetCompressAlgorithm(DataCompressAlgorithm compress_algorithm);
    void     SetCompressAlgorithmDesc(uint8_t index, uint8_t data);
    void     SetRawDataLen(uint32_t raw_data_len) noexcept;
    bool     SetCompressDataLen(uint32_t compress_data_len) noexcept;
    void     UpdateCrc32() noexcept;
    uint32_t SetPayload(uint32_t offset, const uint8_t* const data, uint32_t length,
                        bool_t calculate_crc32 = false) noexcept;

    uint16_t              GetHeader() const noexcept;
    uint16_t              GetVersion() const noexcept;
    uint32_t              GetSensorsId() const noexcept;
    DataCompressAlgorithm GetCompressAlgorithm() const noexcept;
    uint8_t               GetCompressAlgorithmDesc(uint8_t index) const noexcept;
    uint32_t              GetRawDataLen() const noexcept;
    uint32_t              GetCompressDataLen() const noexcept;
    uint32_t              GetPayloadLength() const noexcept;
    uint32_t              GetCrc32() const noexcept;
    uint32_t              GetPayloadCapacity() const noexcept;
    uint32_t              GetPayload(uint32_t offset, uint8_t* data, uint32_t length) const noexcept;
    uint8_t const*        GetPayload() const noexcept;

    uint32_t GetSerializedSize() const noexcept;
    uint32_t Serialize(uint8_t* data, uint32_t length) const noexcept;
    uint32_t Deserialize(const uint8_t* data, uint32_t length);

    bool IsValid();

private:
    uint32_t CalculateCrc32();

private:
    /* const values for packed data access and default values */
    static constexpr uint32_t PACKET_INFO_SIZE  = 36U;
    static constexpr uint32_t DEFAULT_CRC_VALUE = 0xFFFFFFFEU;

    /* memory aloocated for packet */
    size_t                   allocated_capacity_;
    std::shared_ptr<uint8_t> allocated_;

    /* data struct ptr for fast access */
    struct sensors_packed_data* data_;
};

}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif
