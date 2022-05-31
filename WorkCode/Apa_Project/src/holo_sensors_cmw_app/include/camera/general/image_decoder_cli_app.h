/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_decoder_cli_app.h.
 * @brief Image Decoder APP.
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-12-24.
 */

#ifndef _HOLO_CMW_APPS_IMAGE_DECODER_CLI_APP_H
#define _HOLO_CMW_APPS_IMAGE_DECODER_CLI_APP_H

#include <cstring>
#include <exception>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

#include <cmw_wrapper/cmw_bus.h>
#include <holo/core/types.h>
#include <holo/os/time.h>
#include <holo/sensors/camera/decoder/image_decoder.h>
#include <holo/thread/thread_pool.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_c/core/types.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
#include <traits.h>
#else
#include <holo_base_msg/traits.h>
#endif

namespace holo_cmw
{
using holo::sensors::camera::H26xDecoder;
using holo::sensors::camera::IMAGE_ENCODE_SIZE_MAX;
using holo::sensors::camera::ImageDecoderBase;
using holo::sensors::camera::ImagePacket;
using holo::sensors::camera::ImageType;
using holo::sensors::camera::ImageIpc;

enum class SaveType : uint8_t
{
    DONT_SAVE = 0,
    SAVE_NEW,
    SAVE_ALL,
    SAVE_FILE
};

struct ImageDecoderCliAppParam
{
    int                   domain_id;
    std::string           node_name;
    uint32_t              sensor_id;
    uint32_t              fps;
    holo::bool_t          show_image;
    holo::bool_t          use_ipc;
    std::string           topic_name;
    holo::Image::Encoding output_image_type;
    SaveType              save_image_data_type;
    SaveType              save_encoded_data_type;
    std::string           save_data_path;
    uint32_t              threads_num;
    std::string           output_video_size;
};

class ImageDecoderCliApp
{
public:
    ImageDecoderCliApp(const struct ImageDecoderCliAppParam& param);
    ~ImageDecoderCliApp();
private:
    bool_t GetOutputVideoSize(const std::string& output_video_size, uint32_t& output_video_cols, uint32_t& output_video_rows);
    void ImageDecoderHandler(const uint8_t* data, size_t size);
    void ImageDataHandler(const holo::Image& img);
    void SetupDecoder();
    void SaveEncodedDataFile(std::string name, std::string mode);
    void DecodeThread();
    void SaveImageThread(std::shared_ptr<uint8_t> data, uint64_t size, int code);
private:
    cmw_wrapper::BusType                                    bus_;
    uint32_t                                                sensor_id_;
    uint32_t                                                cols_;
    uint32_t                                                rows_;
    uint32_t                                                counter_;
    uint32_t                                                output_video_cols_;
    uint32_t                                                output_video_rows_;
    uint32_t                                                fps_;
    uint32_t                                                threads_num_;
    holo::bool_t                                            show_image_;
    std::string                                             topic_name_;
    SaveType                                                save_image_data_type_;
    ImageType                                               compress_data_image_type_;
    holo::Image::Encoding                                   output_image_type_;
    SaveType                                                save_encoded_data_type_;
    std::string                                             save_data_path_;
    std::shared_ptr<ImageDecoderBase>                       image_decoder_;
    std::shared_ptr<uint8_t>                                decode_buffer_;
    ImagePacket                                             compress_data_;
    bool_t                                                  sutup_decoder_;
    bool_t                                                  found_first_key_frame_;
    bool_t                                                  use_ipc_;
    ImagePacket                                             last_compress_data_;
    holo::bool_t                                            start_compare_timestamp_;
    holo::common::details::Duration                         time_fps_;
    std::queue<std::pair<std::shared_ptr<uint8_t>, size_t>> encoded_data_cache_;
    std::shared_ptr<std::thread>                            decode_thread_;
    std::shared_ptr<holo::thread::ThreadPool>               save_image_thread_pool_;
    std::shared_ptr<ImageIpc>                               ipc_;
    std::mutex                                              encoded_data_mutex_;
    std::mutex                                              image_mutex_;
    holo::bool_t                                            runing_;
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    cmw_wrapper::BusType::WriterType<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>        pub_info_;
    cmw_wrapper::BusType::ReaderType<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>> sub_encoded_;
#else
    cmw_wrapper::BusType::WriterType<uint64_t>              pub_info_;
    cmw_wrapper::BusType::ReaderType<uint8_t*>              sub_encoded_;
#endif

private:
    static constexpr uint64_t FRAME_TIME_SLOT       = 2 * 1000000000;
    static constexpr uint64_t MAX_ENCODED_DATA_SIZE = 3840 * 2160;
    static constexpr uint64_t IMAGE_SIZE_MAX        = 3840 * 2160 * 3;
};

}  // namespace holo_cmw

#endif  //_HOLO_CMW_APPS_IMAGE_DECODER_CLI_APP_H