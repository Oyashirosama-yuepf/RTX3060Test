/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lidar_utils.cpp
 * @brief This source file lidar_utils
 * @author zhangtongyang(zhangtongyang@holomaitc.com)
 * @date 2021/09/01
 */

#include <holo/sensors/utils/lidar_utils.h>

namespace holo
{
namespace sensors
{
const uint32_t LidarUtils::lidar_scan_rate[SUPPORT_SCAN_RATE_NUM] = {1, 5, 10, 20, 50, 100};

LidarUtils::LidarUtils()
{
    map_format_["w8"] = NameFormat::W8;
    map_format_["ts"] = NameFormat::TS;
    file_name_cnt_    = 0;
}

void LidarUtils::SetPlyNameFormat(const std::string& fmt)
{
    ply_name_fmt_ = fmt;
}

void LidarUtils::SavePlyFile(PointCloudType& pcd, uint32_t cnt, const std::string& path, bool_t ascii)
{
    std::string                                 file_name;
    std::map<std::string, NameFormat>::iterator iter = map_format_.find(ply_name_fmt_);
    if (iter == map_format_.end())
    {
        LOG(ERROR) << "check your input output_name is right?";
        return;
    }

    switch (iter->second)
    {
        case NameFormat::W8:
        {
            std::stringstream ss;
            if (cnt == 0)
            {
                ss << std::setw(8) << std::setfill('0') << file_name_cnt_++;
            }
            else
            {
                ss << std::setw(8) << std::setfill('0') << cnt;
            }
            file_name = ss.str() + ".ply";
            break;
        }
        case NameFormat::TS:
        {
            file_name = std::to_string(pcd.GetTimestamp().ToSec()) + ".ply";
            break;
        }
        default:
            break;
    }
    (void)holo::sensors::PlyConverter<PointCloudType>::Save(pcd, file_name, path, ascii);
}

void LidarUtils::ResetFileNameCnt()
{
    file_name_cnt_ = 0;
}

bool_t LidarUtils::LidarScanRateIsValid(uint32_t scan_rate)
{
    for (int i = 0; i < SUPPORT_SCAN_RATE_NUM; i++)
    {
        if (lidar_scan_rate[i] == scan_rate)
        {
            return true;
        }
    }
    return false;
}

void CompressCalChecksum(const uint8_t* data, uint32_t bytes, uint8_t& ck_a, uint8_t& ck_b)
{
    ck_a = 0;
    ck_b = 0;

    for (uint32_t i = 0; i < bytes; ++i)
    {
        ck_a = ck_a + data[i];
        ck_b = ck_b + ck_a;
    }
}

std::shared_ptr<char> CompressUtils::CompressInterface(const uint8_t* input_data, const uint32_t input_size,
                                                       uint32_t& output_size, int32_t accel)
{
    /* check sum before compress */
    uint8_t checksum_a;
    uint8_t checksum_b;
    holo::sensors::CompressCalChecksum(input_data, input_size, checksum_a, checksum_b);

    /* compress */

    int32_t ComOutSize = LZ4_compress_fast(reinterpret_cast<const char*>(input_data), compressed_data_.get(),
                                           input_size, compressed_capacity_, accel);

    if (0 != ComOutSize)
    {
        compressed_data_.get()[ComOutSize]     = (input_size >> 0) & 0xff;
        compressed_data_.get()[ComOutSize + 1] = (input_size >> 8) & 0xff;
        compressed_data_.get()[ComOutSize + 2] = (input_size >> 16) & 0xff;
        compressed_data_.get()[ComOutSize + 3] = (input_size >> 24) & 0xff;
        compressed_data_.get()[ComOutSize + 4] = checksum_a;
        compressed_data_.get()[ComOutSize + 5] = checksum_b;

        /* publish data format:
        -------------------------------------------------------------
        |      Compressed size   |   Byte[0..3]   | 1 Byte | 1 Byte |
        -------------------------------------------------------------
        |      Compressed data   |  pcl data size | chk_a  | chk_b  |
        -------------------------------------------------------------
        */
        output_size = ComOutSize + 6;
        return compressed_data_;
    }
    else
    {
        output_size = 0;
        return nullptr;
    }
}

bool_t TimeCheck(const holo::common::Timestamp& header_timestamp, uint32_t scan_rate)
{
    uint32_t sec, nsec;
#if defined(HOLO_PLATFORM_MDC610)
    holo::common::Timestamp ts;
    holo::mdc610::GetManagmentLevelTime(ts);
    sec  = ts.GetSec();
    nsec = ts.GetNsec();
#else
    (void)holo::os::GetSystemTime(sec, nsec);
#endif

    holo::common::Timestamp sys_time(sec, nsec);
    int64_t                 theoretical_time_ns = sys_time.ToNsec() - holo::sensors::NSEC_PER_SEC / scan_rate;
    if (std::abs(theoretical_time_ns - header_timestamp.ToNsec()) >= holo::sensors::NSEC_PER_SEC / (2 * scan_rate))
    {
        LOG(ERROR) << "Not correct lidar time, lidar time =" << header_timestamp.ToNsec();
        return false;
    }
    return true;
}

}  // namespace sensors
}  // namespace holo