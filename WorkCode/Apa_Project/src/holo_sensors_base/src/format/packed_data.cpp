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

#include <holo/sensors/format/packed_data.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace sensors
{
namespace format
{
/**
 * @brief      Constructs a new instance.
 *
 */
template <uint32_t PayloadCapacity>
SensorCompressedPacket<PayloadCapacity>::SensorCompressedPacket()
  : allocated_capacity_(PACKET_INFO_SIZE + PayloadCapacity + 4)
  , allocated_(new uint8_t[allocated_capacity_](), std::default_delete<uint8_t[]>())
{
    /* construct default object */
    (void)std::memset(allocated_.get(), 0, allocated_capacity_);
    data_                     = reinterpret_cast<struct sensors_packed_data*>(allocated_.get());
    data_->header             = 0xFFFF;
    data_->version            = 0x0001;
    data_->compress_algorithm = DataCompressAlgorithm::NONE;
}

template <uint32_t PayloadCapacity>
SensorCompressedPacket<PayloadCapacity>::SensorCompressedPacket(uint16_t header, uint16_t version, uint32_t sensor_id,
                                                                uint32_t raw_data_len, uint32_t compress_data_len,
                                                                DataCompressAlgorithm compress_algorithm)
  : allocated_capacity_(PACKET_INFO_SIZE + PayloadCapacity + 4)
  , allocated_(new uint8_t[allocated_capacity_](), std::default_delete<uint8_t[]>())
{
    (void)std::memset(allocated_.get(), 0, allocated_capacity_);
    data_                     = reinterpret_cast<struct sensors_packed_data*>(allocated_.get());
    data_->header             = header;
    data_->version            = version;
    data_->sensor_id          = sensor_id;
    data_->raw_data_len       = raw_data_len;
    data_->compress_data_len  = compress_data_len;
    data_->compress_algorithm = compress_algorithm;
}

/**
 * @brief      Set data packet Header.
 *
 * @param[in]  header The packeddata header.
 */
template <uint32_t PayloadCapacity>
void SensorCompressedPacket<PayloadCapacity>::SetHeader(uint16_t header) noexcept
{
    data_->header = header;
}

/**
 * @brief      Set data packet Version.
 *
 * @param[in]  version The packeddata version.
 */
template <uint32_t PayloadCapacity>
void SensorCompressedPacket<PayloadCapacity>::SetVersion(uint16_t version) noexcept
{
    data_->version = version;
}

/**
 * @brief      Set data packet SensorId.
 *
 * @param[in]  sensor_id The packeddata sensor_id
 */
template <uint32_t PayloadCapacity>
void SensorCompressedPacket<PayloadCapacity>::SetSensorId(uint32_t sensor_id) noexcept
{
    data_->sensor_id = sensor_id;
}

/**
 * @brief      Set data compress algorithm.
 *
 * @param[in]  compress_algorithm The packeddata compress_algorithm
 */
template <uint32_t PayloadCapacity>
void SensorCompressedPacket<PayloadCapacity>::SetCompressAlgorithm(DataCompressAlgorithm compress_algorithm)
{
    data_->compress_algorithm = compress_algorithm;
}

/**
 * @brief      Set data compress desc.
 *
 * @param[in]  compress_level The packeddata compress_desc
 */
template <uint32_t PayloadCapacity>
void SensorCompressedPacket<PayloadCapacity>::SetCompressAlgorithmDesc(uint8_t index, uint8_t data)
{
    data_->compress_algorithm_desc[index] = data;
}

/**
 * @brief      Set data length before compression.
 *
 * @param[in]  raw_data_len The packeddata raw_data_len
 */
template <uint32_t PayloadCapacity>
void SensorCompressedPacket<PayloadCapacity>::SetRawDataLen(uint32_t raw_data_len) noexcept
{
    data_->raw_data_len = raw_data_len;
}

/**
 * @brief      Set data length after compression.
 *
 * @param[in]  compress_data_len The packeddata compress_data_len
 *
 * @return     True/False set successfully
 */
template <uint32_t PayloadCapacity>
bool SensorCompressedPacket<PayloadCapacity>::SetCompressDataLen(uint32_t compress_data_len) noexcept
{
    if (compress_data_len > PayloadCapacity)
    {
        return false;
    }
    data_->compress_data_len = compress_data_len;
    return true;
}

/**
 * @brief      Set data packet check sum.
 *
 * @param[in]  checksum_crc The packeddata checksum_crc
 */
template <uint32_t PayloadCapacity>
void SensorCompressedPacket<PayloadCapacity>::UpdateCrc32() noexcept
{
    uint32_t  checksum_crc = CalculateCrc32();
    uint32_t* tmp          = reinterpret_cast<uint32_t*>(data_->checksum_crc);
    *tmp                   = checksum_crc;
}

/**
 * @brief      Get data packet Header.
 *
 * @return     The packeddata header
 */
template <uint32_t PayloadCapacity>
uint16_t SensorCompressedPacket<PayloadCapacity>::GetHeader() const noexcept
{
    return data_->header;
}

/**
 * @brief      Get data packet Version.
 *
 * @return     The packeddata version
 */
template <uint32_t PayloadCapacity>
uint16_t SensorCompressedPacket<PayloadCapacity>::GetVersion() const noexcept
{
    return data_->version;
}

/**
 * @brief      Get data packet SensorId.
 *
 * @return     The packeddata sensor_id
 */
template <uint32_t PayloadCapacity>
uint32_t SensorCompressedPacket<PayloadCapacity>::GetSensorsId() const noexcept
{
    return data_->sensor_id;
}

/**
 * @brief      Get data compress algorithm.
 *
 * @return     The packeddata compress_algorithm
 */
template <uint32_t PayloadCapacity>
DataCompressAlgorithm SensorCompressedPacket<PayloadCapacity>::GetCompressAlgorithm() const noexcept
{
    return data_->compress_algorithm;
}

/**
 * @brief      Get data compress level.
 *
 * @return     The packeddata compress_level
 */
template <uint32_t PayloadCapacity>
uint8_t SensorCompressedPacket<PayloadCapacity>::GetCompressAlgorithmDesc(uint8_t index) const noexcept
{
    return data_->compress_algorithm_desc[index];
}

/**
 * @brief      Get data length before compression.
 *
 * @return     The packeddata raw_data_len
 */
template <uint32_t PayloadCapacity>
uint32_t SensorCompressedPacket<PayloadCapacity>::GetRawDataLen() const noexcept
{
    return data_->raw_data_len;
}

/**
 * @brief      Get data compress algorithm.
 *
 * @return     The packeddata compress_data_len
 */
template <uint32_t PayloadCapacity>
uint32_t SensorCompressedPacket<PayloadCapacity>::GetCompressDataLen() const noexcept
{
    return data_->compress_data_len;
}

/**
 * @brief      Get payload data length.
 *
 * @return     The packeddata compress_data_len or raw_data_length
 */
template <uint32_t PayloadCapacity>
uint32_t SensorCompressedPacket<PayloadCapacity>::GetPayloadLength() const noexcept
{
    uint32_t data_len = 0;
    if (DataCompressAlgorithm::NONE == data_->compress_algorithm)
    {
        data_len = data_->raw_data_len;
    }
    else
    {
        data_len = data_->compress_data_len;
    }
    return data_len;
}

/**
 * @brief      Get data packet check sum.
 *
 * @return     The packeddata checksum_crc
 */
template <uint32_t PayloadCapacity>
uint32_t SensorCompressedPacket<PayloadCapacity>::GetCrc32() const noexcept
{
    return *(uint32_t*)data_->checksum_crc;
}

/**
 * @brief      Get data packet PayloadCapacity.
 *
 * @return     The packeddata PayloadCapacity
 */
template <uint32_t PayloadCapacity>
uint32_t SensorCompressedPacket<PayloadCapacity>::GetPayloadCapacity() const noexcept
{
    return PayloadCapacity;
}

/**
 * @brief      Calculate CRC for sensors_packed_data.
 *
 * @return     the CRC result
 */
template <uint32_t PayloadCapacity>
uint32_t SensorCompressedPacket<PayloadCapacity>::CalculateCrc32()
{
    return CalcCRC32(reinterpret_cast<uint8_t*>(data_), PACKET_INFO_SIZE + GetPayloadLength(), 0);
}

/**
 * @brief      Check if the data is valid.
 *
 * @return     True/False valid data
 */
template <uint32_t PayloadCapacity>
bool SensorCompressedPacket<PayloadCapacity>::IsValid()
{
    uint32_t src_crc = GetCrc32();
    return CalculateCrc32() == src_crc;
}

/**
 * @brief      Set data packet Payload.
 *
 * @param[in]  offset  The payload offset
 * @param[in]  data    The source data address
 * @param[in]  length  The source data length
 *
 * @return     Payload length set this time
 */
template <uint32_t PayloadCapacity>
uint32_t SensorCompressedPacket<PayloadCapacity>::SetPayload(uint32_t offset, const uint8_t* const data,
                                                             uint32_t length, bool_t calculate_crc32) noexcept
{
    /* check input data */
    assert(data);

    if ((offset + length) > PayloadCapacity)
    {
        LOG(ERROR) << "unable to set payload: out of range";
        return 0;
    }
    /* copy data */
    (void)std::memcpy(data_->payload + offset, data, length);

    /* set crc32 */
    if (true == calculate_crc32)
    {
        UpdateCrc32();
    }

    return length;
}

/**
 * @brief      Gets the payload.
 *
 * @param[in]  offset  The payload offset
 * @param        data      The target data address
 * @param[in]  length  The target data length
 *
 * @return     The payload size
 */
template <uint32_t PayloadCapacity>
uint32_t SensorCompressedPacket<PayloadCapacity>::GetPayload(uint32_t offset, uint8_t* data, uint32_t length) const
    noexcept
{
    /* check input data */
    assert(data);

    if (offset >= PayloadCapacity)
    {
        LOG(ERROR) << "unable to get payload: out of range";
        return 0;
    }
    /* copy data */
    auto len = std::min<uint32_t>(length, PayloadCapacity - offset);
    (void)std::memcpy(data, data_->payload + offset, len);
    return len;
}

template <uint32_t PayloadCapacity>
uint8_t const* SensorCompressedPacket<PayloadCapacity>::GetPayload() const noexcept
{
    return reinterpret_cast<uint8_t const*>(data_->payload);
}

/* serializedSize */

template <uint32_t PayloadCapacity>
uint32_t SensorCompressedPacket<PayloadCapacity>::GetSerializedSize() const noexcept
{
    /* HEADER + DATA + CRC */
    return PACKET_INFO_SIZE + GetPayloadLength() + 4;
}

template <uint32_t PayloadCapacity>
uint32_t SensorCompressedPacket<PayloadCapacity>::Serialize(uint8_t* data, uint32_t length) const noexcept
{
    if (data == nullptr)
    {
        return 0;
    }
    uint32_t total_length = GetSerializedSize();
    if (length < total_length)
    {
        LOG(ERROR) << "Data Buffer is to small!";
        return 0;
    }
    /* HEADER + DATA */
    (void)std::memcpy(data, &data_[0], total_length - 4);
    /* CRC */
    (void)std::memcpy(&data[total_length - 4], data_->checksum_crc, 4);
    return total_length;
}

template <uint32_t PayloadCapacity>
uint32_t SensorCompressedPacket<PayloadCapacity>::Deserialize(const uint8_t* data, uint32_t length)
{
    if (data == nullptr)
    {
        return 0;
    }
    auto     ptr         = reinterpret_cast<const sensors_packed_data*>(data);
    uint32_t data_length = 0;
    if (DataCompressAlgorithm::NONE == ptr->compress_algorithm)
    {
        data_length = PACKET_INFO_SIZE + ptr->raw_data_len + 4;
    }
    else
    {
        data_length = PACKET_INFO_SIZE + ptr->compress_data_len + 4;
    }
    if (length < data_length)
    {
        LOG(ERROR) << "unable to deserialize: bad data";
        return 0;
    }
    /* HEADER + DATA */
    (void)std::memcpy(&data_[0], data, data_length - 4);
    /* CRC */
    (void)std::memcpy(data_->checksum_crc, &data[data_length - 4], 4);

    /* InValid */
    if (!IsValid())
    {
        LOG(ERROR) << "SensorCompressedPacket Data Crc Invalid!";
        return 0;
    }
    return data_length;
}

template class holo::sensors::format::SensorCompressedPacket<1024 * 1024 * 4>;

}  // namespace format
}  // namespace sensors
}  // namespace holo