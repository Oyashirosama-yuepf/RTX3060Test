/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_decoder_app.h.
 * @brief Image Decoder APP.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-12.
 */
#ifndef _HOLO_CMW_APPS_IMAGE_DECODER_H
#define _HOLO_CMW_APPS_IMAGE_DECODER_H

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

template <typename Tdec>
class ImageDecoderAppT
{
public:
    ImageDecoderAppT(int32_t id, std::string const& ns, uint32_t thread_num)
      : bus0_{id, ns}
      , counter_(0)
      , decode_buffer_{new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>()}
      , found_first_key_frame_{false}
      , use_ipc_(true)
      , start_compare_timestamp_(false)
      , runing_(true)
    {
        decode_thread_          = std::make_shared<std::thread>(std::bind(&ImageDecoderAppT<Tdec>::DecodeThread, this));
        save_image_thread_pool_ = std::make_shared<holo::thread::ThreadPool>(thread_num);
    }

    ~ImageDecoderAppT()
    {
        runing_ = false;
        if (decode_thread_ && (decode_thread_->joinable()))
        {
            decode_thread_->join();
        }
    }

    bool_t GetOutputVideoSize(const std::string& output_video_size, uint32_t& output_video_cols, uint32_t& output_video_rows);
    void Setup(const std::string& config_file, const std::string& save_image = std::string(""),
               const std::string& save_encoded_data = std::string(""), const std::string& output_video_size = std::string(""));

private:
    void GetParameters(const std::string& config_file);
    void ImageDecoderHandler(const uint8_t* data, size_t size);
    void ImageDataHandler(const holo::Image& img, SaveType save_type);
    void DecodeThread();
    void SaveImageThread(std::shared_ptr<uint8_t> data, uint64_t size, int code, SaveType save_type);

private:
    cmw_wrapper::BusType bus0_;
    std::string          topic_name_;
    uint32_t             sensor_id_;
    uint32_t             cols_;
    uint32_t             rows_;
    uint32_t             fps_;
    uint32_t             counter_;
    bool                 show_image_;
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    cmw_wrapper::BusType::WriterType<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>        pub_info_;
    cmw_wrapper::BusType::ReaderType<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>> sub_encoded_;
#else
    cmw_wrapper::BusType::WriterType<uint64_t> pub_info_;
    cmw_wrapper::BusType::ReaderType<uint8_t*> sub_encoded_;
#endif
    std::shared_ptr<Tdec>                                   image_decoder_;
    std::shared_ptr<uint8_t>                                decode_buffer_;
    ImagePacket                                             compress_data_;
    bool_t                                                  found_first_key_frame_;
    bool_t                                                  use_ipc_;
    ImagePacket                                             last_compress_data_;
    holo::bool_t                                            start_compare_timestamp_;
    SaveType                                                save_encoded_data_type_;
    holo::common::details::Duration                         time_fps_;
    std::queue<std::pair<std::shared_ptr<uint8_t>, size_t>> encoded_data_cache_;
    std::shared_ptr<std::thread>                            decode_thread_;
    std::shared_ptr<holo::thread::ThreadPool>               save_image_thread_pool_;
    std::mutex                                              encoded_data_mutex_;
    std::mutex                                              image_mutex_;
    holo::bool_t                                            runing_;
    std::shared_ptr<ImageIpc>                               ipc_;

private:
    static constexpr typename std::enable_if<std::is_base_of<ImageDecoderBase, Tdec>::value, void>::type* Ptr = nullptr;
    static constexpr uint64_t FRAME_TIME_SLOT       = 2 * 1000000000;
    static constexpr uint64_t MAX_ENCODED_DATA_SIZE = 3840 * 2160;
    static constexpr uint64_t IMAGE_SIZE_MAX        = 3840 * 2160 * 3;
};

}  // namespace holo_cmw

#endif  // _HOLO_CMW_APPS_IMAGE_ENCODER_H
