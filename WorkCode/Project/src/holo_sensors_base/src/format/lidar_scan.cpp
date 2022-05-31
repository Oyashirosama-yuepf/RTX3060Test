/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lidar_scan.h
 * @brief the lidar scan data definition
 * @author wujie@holomatic.com
 * @date 2021-11-02
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#include <holo/sensors/format/lidar_scan.h>

namespace holo
{
namespace sensors
{
namespace format
{
template <uint32_t ScanCapacity>
LidarScan<ScanCapacity>::LidarScan()
  : is_compressed_(false)
  , pub_raw_scan_(false)
  , compress_utils_(nullptr)
  , version_(0x02)
  , type_(LidarType::NONE)
  , params_len_(0)
  , params_{0}
  , time_sync_offsets_{0}
{
}

template <uint32_t ScanCapacity>
LidarScan<ScanCapacity>::LidarScan(LidarType type, bool_t use_compress, const Extrinsicf& extrinsic,
                                   const uint8_t* params, uint32_t bytes)
  : is_compressed_(use_compress)
  , pub_raw_scan_(false)
  , compress_utils_(nullptr)
  , version_(0x02)
  , type_(type)
  , extrinsic_(extrinsic)
  , params_len_(0)
  , time_sync_offsets_{0}
{
    scan_data_.SetSensorId(extrinsic_.GetSensorId());
    (void)SetConverterParams(params, bytes);
}

template <uint32_t ScanCapacity>
LidarScan<ScanCapacity>::LidarScan(LidarType type, bool_t use_compress, const Extrinsicf& extrinsic,
                                   bool_t pub_raw_scan, const uint8_t* params, uint32_t bytes)
  : is_compressed_(use_compress)
  , pub_raw_scan_(pub_raw_scan)
  , compress_utils_(nullptr)
  , version_(0x02)
  , type_(type)
  , extrinsic_(extrinsic)
  , params_len_(0)
  , time_sync_offsets_{0}
{
    (void)SetConverterParams(params, bytes);
}

template <uint32_t ScanCapacity>
uint32_t LidarScan<ScanCapacity>::SetConverterParams(const uint8_t* params, uint32_t bytes)
{
    if ((bytes == 0) || (bytes > MAX_PARAMS_LENGTH))
    {
        return 0;
    }
    (void)std::memcpy(&params_[0], params, bytes);
    params_len_ = bytes;
    return bytes;
}

template <uint32_t ScanCapacity>
void LidarScan<ScanCapacity>::SetTimeOffset0(const int64_t& time_offset0)
{
    time_sync_offsets_[0] = time_offset0;
}

template <uint32_t ScanCapacity>
void LidarScan<ScanCapacity>::SetTimeOffset1(const int64_t& time_offset1)
{
    time_sync_offsets_[1] = time_offset1;
}

template <uint32_t ScanCapacity>
ConverterPtr LidarScan<ScanCapacity>::CreateConverter(LidarType type, std::shared_ptr<DeserializerType> deserializer)
{
    ConverterPtr converter = nullptr;
    switch (type)
    {
        case LidarType::LIVOX:
        {
            using LivoxPacketType   = holo::sensors::format::LivoxPacket<96>;
            using LivoxPcdConverter = holo::sensors::livox::LivoxPcdConverter<LivoxPacketType>;
            uint32_t livox_packet_rate;
            *deserializer >> livox_packet_rate;
            converter = std::make_shared<LivoxPcdConverter>(extrinsic_, livox_packet_rate);
            (void)converters_.insert(std::pair<LidarType, ConverterPtr>(LidarType::LIVOX, converter));
        }
        break;
        case LidarType::LIVOXHAP:
        {
            using HapPacketType   = holo::sensors::format::LivoxHapPacket<1440>;
            using HapPcdConverter = holo::sensors::livox::LivoxPcdConverter<HapPacketType>;
            uint32_t hap_packet_rate;
            *deserializer >> hap_packet_rate;
            converter = std::make_shared<HapPcdConverter>(extrinsic_, hap_packet_rate);
            (void)converters_.insert(std::pair<LidarType, ConverterPtr>(LidarType::LIVOXHAP, converter));
        }
        break;
        case LidarType::PANDAR:
        {
            using PandarPcdConverter = holo::sensors::pandar::PandarPcdConverter;
            holo::sensors::pandar::ConvertParameter    convert_param;
            holo::sensors::pandar::CorrectionParameter correct_param;
            *deserializer >> convert_param >> correct_param;
            converter = std::make_shared<PandarPcdConverter>(convert_param, correct_param, extrinsic_);
            (void)converters_.insert(std::pair<LidarType, ConverterPtr>(LidarType::PANDAR, converter));
        }
        break;
        case LidarType::RSRUBY:
        {
            using RsrubyConverter = holo::sensors::rsruby::RsrubyPcdConverter;
            holo::sensors::rsruby::CorrectionParameter correct_param;
            *deserializer >> correct_param;
            converter = std::make_shared<RsrubyConverter>(extrinsic_, correct_param);
            (void)converters_.insert(std::pair<LidarType, ConverterPtr>(LidarType::RSRUBY, converter));
        }
        break;
        case LidarType::VELODYNE:
        {
            using VelodynePcdConverter = holo::sensors::velodyne::VelodynePcdConverter;
            holo::sensors::velodyne::ConvertParameter    convert_param;
            holo::sensors::velodyne::CorrectionParameter correct_param;
            *deserializer >> convert_param >> correct_param;
            converter = std::make_shared<VelodynePcdConverter>(convert_param, correct_param, extrinsic_);
            (void)converters_.insert(std::pair<LidarType, ConverterPtr>(LidarType::VELODYNE, converter));
        }
        break;
        case LidarType::PANDAR128:
        {
            using Pandar128PcdConverter = holo::sensors::pandar128::Pandar128PcdConverter;
            holo::sensors::pandar128::CorrectionParameter   correct_param;
            holo::sensors::pandar128::LuminousTimeParameter luminous_param;
            *deserializer >> correct_param >> luminous_param;
            converter = std::make_shared<Pandar128PcdConverter>(luminous_param, correct_param, extrinsic_);
            (void)converters_.insert(std::pair<LidarType, ConverterPtr>(LidarType::PANDAR128, converter));
        }
        break;
        case LidarType::RSBPEARL:
        {
            using RsbpearlPcdConverter = holo::sensors::rsbpearl::RsbpearlPcdConverter;
            holo::sensors::rsbpearl::CorrectionParameter correct_param;
            *deserializer >> correct_param;
            converter = std::make_shared<RsbpearlPcdConverter>(extrinsic_, correct_param);
            (void)converters_.insert(std::pair<LidarType, ConverterPtr>(LidarType::RSBPEARL, converter));
        }
        break;
        default:
            break;
    }
    return converter;
}

template <uint32_t ScanCapacity>
ConverterPtr LidarScan<ScanCapacity>::GetConverter(LidarType type)
{
    /* find converter */
    typename std::map<LidarType, ConverterPtr>::iterator iter = converters_.find(type);

    if (iter != converters_.end())
    {
        return iter->second;
    }

    /* create converter */
    ConverterPtr                      converter    = nullptr;
    std::shared_ptr<DeserializerType> deserializer = nullptr;
    if (0 != params_len_)
    {
        try
        {
            deserializer = std::make_shared<DeserializerType>(&params_[0], params_len_);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "Converter params deserializer create failed!: " << e.what();
            LOG(ERROR) << oss.str();
            throw std::runtime_error(oss.str());
        }
    }

    switch (type)
    {
        case LidarType::LIVOX:
        case LidarType::LIVOXHAP:
        case LidarType::PANDAR:
        case LidarType::RSRUBY:
        case LidarType::VELODYNE:
        case LidarType::PANDAR128:
        case LidarType::RSBPEARL:
        {
            if (deserializer == nullptr)
            {
                LOG(ERROR) << "deserializer is nullptr!";
                break;
            }
            converter = CreateConverter(type, deserializer);
        }
        break;
        case LidarType::RSM1:
        {
            using Rsm1Converter = holo::sensors::rsm1::Rsm1PcdConverter;
            converter           = std::make_shared<Rsm1Converter>(extrinsic_);
            (void)converters_.insert(std::pair<LidarType, ConverterPtr>(LidarType::RSM1, converter));
        }
        break;
        case LidarType::MDC610:
        {
            using Mdc610PcdConverter = holo::sensors::mdc610::Mdc610Converter;
            converter                = std::make_shared<Mdc610PcdConverter>(extrinsic_);
            (void)converters_.insert(std::pair<LidarType, ConverterPtr>(LidarType::MDC610, converter));
        }
        break;
        default:
            LOG(ERROR) << "Lidar Type Error!";
            break;
    }
    return converter;
}

template class holo::sensors::format::LidarScan<1024 * 1024 * 4>;

}  // namespace format
}  // namespace sensors
}  // namespace holo