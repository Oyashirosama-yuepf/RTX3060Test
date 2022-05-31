/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lidar_utils.h
 * @brief This header file defines lidar_utils
 * @author zhangtongyang(zhangtongyang@holomaitc.com)
 * @date 2021/09/01
 */

#ifndef HOLO_SENSORS_UTILS_LIDAR_UTILS_H_
#define HOLO_SENSORS_UTILS_LIDAR_UTILS_H_

#include <holo/core/types.h>
#include <holo/log/hololog.h>
#include <holo/os/time.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/lidar/libply/libply.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo_c/core/types.h>
#include <lz4.h>
#include <map>

#if defined(MDC_PRODUCTION_MDC610)
#include <holo/sensors/utils/mdc610_utils.h>
#endif

namespace holo
{
namespace sensors
{
using LidarCompressAlgorithm = DataCompressAlgorithm;

static constexpr uint32_t NSEC_PER_SEC = 1000000000;

void CompressCalChecksum(const uint8_t* data, uint32_t bytes, uint8_t& ck_a, uint8_t& ck_b);
// std::shared_ptr<char> CompressInterface(const uint8_t* input_data, const uint32_t input_size, uint32_t& output_size,
// int32_t accel);

void CompressCalChecksum(const uint8_t* data, uint32_t bytes, uint8_t& ck_a, uint8_t& ck_b);

bool_t TimeCheck(const holo::common::Timestamp& header_timestamp, uint32_t scan_rate);

class CompressUtils
{
public:
    CompressUtils(size_t compressed_capacity)
      : compressed_data_(new char[compressed_capacity](), std::default_delete<char[]>())
      , compressed_capacity_(compressed_capacity)
    {
    }
    std::shared_ptr<char> CompressInterface(const uint8_t* input_data, const uint32_t input_size, uint32_t& output_size,
                                            int32_t accel);

private:
    std::shared_ptr<char> compressed_data_;
    size_t                compressed_capacity_;
};

class LidarUtils
{
    enum class NameFormat
    {
        W8 = 0,
        TS = 1,
    };

public:
    using PointType      = holo::point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType = holo::point_cloud::PointCloudT<PointType, std::numeric_limits<size_t>::max(),
                                                          sizeof(PointType), holo::point_cloud::UnorganizedLayoutTag>;

    LidarUtils();
    void          SetPlyNameFormat(const std::string& fmt);
    void          SavePlyFile(PointCloudType& pcd, uint32_t cnt = 0, const std::string& path = ".", bool_t ascii = false);
    void          ResetFileNameCnt();
    static bool_t LidarScanRateIsValid(uint32_t scan_rate);

private:
    static const uint16_t SUPPORT_SCAN_RATE_NUM = 6;
    static const uint32_t lidar_scan_rate[SUPPORT_SCAN_RATE_NUM];

private:
    std::string                       ply_name_fmt_;
    std::map<std::string, NameFormat> map_format_;
    uint32_t                          file_name_cnt_;
};

}  // namespace sensors
}  // namespace holo

#endif