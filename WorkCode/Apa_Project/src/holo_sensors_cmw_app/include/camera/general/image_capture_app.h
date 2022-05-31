/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_capture_app.h.
 * @brief Image Capture APP.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-12.
 */
#ifndef _HOLO_CMW_APPS_IMAGE_CAPTURE_H
#define _HOLO_CMW_APPS_IMAGE_CAPTURE_H

#include <holo/core/types.h>
#include <holo/os/time.h>
#include <holo/sensors/camera/capture/image_capture_encoded.h>
#include <holo/sensors/camera/capture/image_capture_raw.h>
#include <holo/sensors/camera/capture/image_capture_rgb.h>
#include <holo/sensors/camera/decoder/image_decoder.h>
#include <holo/sensors/camera/encoder/image_encoder.h>
#include <holo/sensors/interface/virtual_camera_interface.h>
#include <holo/sensors/image/resize/image_resize.h>
#include <holo/serialization/serialization.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#if defined(CMW_WRAPPER_ENABLE_ROS)
#include <holo_base_msg/ros_msg/image/image_packet_traits.h>
#endif
#include <holo_c/core/types.h>
#include <interface/interface_wrapper.h>
#include <unistd.h>
#include <exception>
#include <functional>
#include <memory>

#ifdef Status
#undef Status
#endif

#ifdef Success
#undef Success
#endif

#include <cmw_wrapper/cmw_bus.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
#include <traits.h>
#else
#include <holo_base_msg/traits.h>
#endif

namespace holo_cmw
{
using holo::common::SensorId;
using holo::common::Timestamp;
using holo::sensors::camera::Bayer8Converter;
using holo::sensors::camera::DummyEncoder;
using holo::sensors::camera::H264Encoder;
using holo::sensors::camera::H265ToNv12Decoder;
using holo::sensors::camera::IMAGE_ENCODE_SIZE_MAX;
using holo::sensors::camera::IMAGE_RAW_SIZE_MAX;
using holo::sensors::camera::ImageCaptureBasic;
using holo::sensors::camera::ImageCaptureEncoded;
using holo::sensors::camera::ImageCaptureRaw;
using holo::sensors::camera::ImageCaptureRgbT;
using holo::sensors::camera::ImageCaptureVirtual;
using holo::sensors::camera::ImageConverterBase;
using holo::sensors::camera::ImageEncoderBase;
using holo::sensors::camera::ImagePacket;
using holo::sensors::camera::ImageIpc;
using holo::sensors::camera::ImageTimestamperT;
using holo::sensors::camera::ImageType;
using holo::sensors::camera::StreamBuffer;
using holo::sensors::camera::YuyvConverter;
using holo::sensors::format::HoloSyncDiffPacket;
using holo::sensors::format::HoloSyncPacket;
using holo::sensors::interface::VirtCamInterface;
using holo::sensors::camera::RawToNv12Converter;

enum class SaveType : uint8_t
{
    DONT_SAVE = 0,
    SAVE_NEW,
    SAVE_ALL,
    SAVE_FILE
};

/**
 * @brief      This class describes an image capture application base.
 */
class ImageCaptureAppBase
{
public:
using LiveCallbackType    = std::function<void(uint32_t, uint32_t)>;

    ImageCaptureAppBase(int32_t id, std::string const& ns) 
      : frames_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
        bus0_ = std::make_shared<cmw_wrapper::BusType>(id, ns);
    }
    ImageCaptureAppBase(std::shared_ptr<cmw_wrapper::BusType> bus) 
      : bus0_(bus)
      , frames_(0)
      , thread_(nullptr)
      , live_callback_(nullptr)
    {
    }

    virtual ~ImageCaptureAppBase()
    {
        if (thread_ && thread_->joinable())
        {
            thread_->join();
        }
    }

    void InstallLiveCallback(const LiveCallbackType& handler) noexcept
    {
        live_callback_ = handler;
    }
    virtual void Setup(const std::string& config_file, const std::string& save_image, const std::string& output_video_size = "", bool_t blocking_mode = true) = 0;
    bool_t GetOutputVideoSize(const std::string& output_video_size, uint32_t& output_video_cols, uint32_t& output_video_rows);

protected:
    void GetParameters(const std::string& config_file);
    void BackgroundImageCapBase()
    {
        uint32_t    frames_last = 0;
        holo::Timer timer(1.0f);
        while (cmw_wrapper::BusType::IsRunning())
        {
            timer.Start();
            uint32_t frames_this = frames_;
            if (live_callback_)
            {
                live_callback_(0, frames_this - frames_last);
            }
            LOG(INFO) << "data hz = " << frames_this - frames_last;
            frames_last = frames_this;
            timer.Stop();
        }
    }

protected:
    // cmw_wrapper::BusType bus0_;
    std::shared_ptr<cmw_wrapper::BusType>          bus0_;
    std::string                                    topic_name_;
    uint32_t                                       sensor_id_;
    uint32_t                                       cols_;
    uint32_t                                       rows_;
    uint32_t                                       fps_;
    bool                                           trigger_mode_;
    bool                                           show_image_;
    bool                                           use_ipc_;
    std::atomic<uint32_t>                          frames_;
    std::shared_ptr<std::thread>                   thread_;
    LiveCallbackType                               live_callback_;
};

template <typename T>
class ImageCaptureSyncBaseT
{
public:
    ImageCaptureSyncBaseT() = default;
    virtual ~ImageCaptureSyncBaseT() = default;

public:
    void TimeSyncHandler(std::shared_ptr<ImageTimestamperT<T>> driver, const T& data);
};

template <typename Tcam>
class ImageCaptureRawApp : public ImageCaptureAppBase, public ImageCaptureSyncBaseT<HoloSyncPacket>
{
public:
    ImageCaptureRawApp(int32_t id, std::string const& ns)
      : ImageCaptureAppBase(1, ns)  // "1" means tcp connection
      , ImageCaptureSyncBaseT<HoloSyncPacket>()
      , output_{new uint8_t[IMAGE_RAW_SIZE_MAX](), std::default_delete<uint8_t[]>()}
    {
        (void)id;
    }
    ImageCaptureRawApp(std::shared_ptr<cmw_wrapper::BusType> bus)
      : ImageCaptureAppBase(bus)
      , ImageCaptureSyncBaseT<HoloSyncPacket>()
      , output_{new uint8_t[IMAGE_RAW_SIZE_MAX](), std::default_delete<uint8_t[]>()}
    {
    }

    void SetTimeSyncData(const HoloSyncPacket& data);
    void Setup(const std::string& config_file, const std::string& save_image, const std::string& output_video_size = "", bool_t blocking_mode = true) override;

private:
    void ImageRawHandler(const ImagePacket& raw_image);

private:
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    cmw_wrapper::BusType::WriterType<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>> pub_raw_;
#else
    cmw_wrapper::BusType::WriterType<uint8_t*>                                                       pub_raw_;
#endif
    std::shared_ptr<uint8_t>                              output_;
    std::shared_ptr<ImageCaptureRaw<ImageType::RAW_YUYV>> driver_;
    std::shared_ptr<V4l2Interface<Tcam>>                  data_interface_;
    std::shared_ptr<UdpInterface<HoloSyncPacket>>         sync_interface_;
};

template <typename Tcvt, typename Tenc = DummyEncoder>
class ImageCaptureMdc610App : public ImageCaptureAppBase
{
public:
    ImageCaptureMdc610App(int32_t id, std::string const& ns)
      : ImageCaptureAppBase(id, ns), counter_(0), output_{new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>()}
    {
    }
    ImageCaptureMdc610App(std::shared_ptr<cmw_wrapper::BusType> bus)
      : ImageCaptureAppBase(bus), output_{new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>()}
    {
    }
    ~ImageCaptureMdc610App() = default;

    void Background(const std::string& config_file);
    void Setup(const std::string& config_file, const std::string& save_image, const std::string& output_video_size = "", bool_t blocking_mode = true) override;

private:
    void ImageH265EncoderHandler(const ImagePacket& encoded_image);
    void ImageNV12DataHandler(const holo::Image& img, SaveType save_type);

private:
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    cmw_wrapper::BusType::WriterType<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>        pub_info_;
    cmw_wrapper::BusType::WriterType<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>> pub_encoded_;
#else
    cmw_wrapper::BusType::WriterType<uint64_t> pub_info_;
    cmw_wrapper::BusType::WriterType<uint8_t*> pub_encoded_;
#endif

    uint32_t                                       counter_;
    std::shared_ptr<uint8_t>                       output_;
    std::shared_ptr<ImageCaptureBasic<Tcvt, Tenc>> nv12_driver_;
    std::shared_ptr<ImageCaptureEncoded<>>         h265_driver_;
    std::shared_ptr<ImageIpc>                      ipc_;

    static constexpr int32_t MIN_NV12_CHANNEL_ID = 21;
    static constexpr int32_t MAX_NV12_CHANNEL_ID = 34;
    static constexpr int32_t MIN_H265_CHANNEL_ID = 71;
    static constexpr int32_t MAX_H265_CHANNEL_ID = 84;
};

template <typename Tcam, typename Tcvt, typename Tenc = DummyEncoder, typename Tsync = HoloSyncDiffPacket>
class ImageCaptureRgbAppT : public ImageCaptureAppBase, public ImageCaptureSyncBaseT<Tsync>
{
public:
    ImageCaptureRgbAppT(int32_t id, std::string const& ns)
      : ImageCaptureAppBase(id, ns)
      , ImageCaptureSyncBaseT<Tsync>()
      , counter_(0)
      , output_{new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>()}
    {
    }
    ImageCaptureRgbAppT(std::shared_ptr<cmw_wrapper::BusType> bus)
      : ImageCaptureAppBase(bus)
      , ImageCaptureSyncBaseT<Tsync>()
      , output_{new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>()}
    {
    }
    void SetTimeSyncData(const Tsync& data);

    void Setup(const std::string& config_file, const std::string& save_image, const std::string& output_video_size = "", bool_t blocking_mode = true) override;

private:
    void ImageDataHandler(const holo::Image& img, SaveType save_type);
    void ImageEncoderHandler(const ImagePacket& encoded_image);

private:
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    cmw_wrapper::BusType::WriterType<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>        pub_info_;
    cmw_wrapper::BusType::WriterType<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>> pub_encoded_;
#elif defined(CMW_WRAPPER_ENABLE_ROS)
    cmw_wrapper::BusType::WriterType<uint64_t>                                                       pub_info_;
    cmw_wrapper::BusType::WriterType<ImagePacket, ros_wrapper::DefaultConversionTraits<ImagePacket>> pub_encoded_;
#else
    cmw_wrapper::BusType::WriterType<uint64_t> pub_info_;
    cmw_wrapper::BusType::WriterType<uint8_t*> pub_encoded_;
#endif
    uint32_t                                             counter_;
    std::shared_ptr<uint8_t>                             output_;
    std::shared_ptr<ImageCaptureRgbT<Tcvt, Tenc, Tsync>> driver_;
    std::shared_ptr<V4l2Interface<Tcam>>                 data_interface_;
    std::shared_ptr<UdpInterface<Tsync>>                 sync_interface_;
    std::shared_ptr<ImageIpc>                            ipc_;

private:
    static constexpr typename std::enable_if<std::is_base_of<ImageConverterBase, Tcvt>::value, void>::type* NULLPTR0 =
        nullptr;
    static constexpr typename std::enable_if<std::is_base_of<ImageEncoderBase, Tenc>::value, void>::type* NULLPTR1 =
        nullptr;
};

template <typename Tdec>
class ImageCaptureEncodedApp : public ImageCaptureAppBase
{
public:
    ImageCaptureEncodedApp(int32_t id, std::string const& ns)
      : ImageCaptureAppBase(id, ns), output_{new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>()}
    {
        LOG(INFO) << "construct image capture basic app";
    }
    ImageCaptureEncodedApp(std::shared_ptr<cmw_wrapper::BusType> bus)
      : ImageCaptureAppBase(bus), counter_(0), output_{new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>()}
    {
        LOG(INFO) << "construct image capture basic app";
    }
    ~ImageCaptureEncodedApp() = default;

    void Setup(const std::string& config_file, const std::string& save_image, const std::string& output_video_size = "", bool_t blocking_mode = true) override;

private:
    void ImageEncoderHandler(const ImagePacket& encoded_image);
    void ImageDataHandler(const holo::Image& img, SaveType save_type);

private:
    uint32_t                                   counter_;
    std::shared_ptr<uint8_t>                   output_;
    std::shared_ptr<ImageCaptureEncoded<Tdec>> driver_;
    std::shared_ptr<ImageIpc>                  ipc_;

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    cmw_wrapper::BusType::WriterType<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>        pub_info_;
    cmw_wrapper::BusType::WriterType<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>> pub_encoded_;
#else
    cmw_wrapper::BusType::WriterType<uint64_t> pub_info_;
    cmw_wrapper::BusType::WriterType<uint8_t*> pub_encoded_;
#endif

#if defined(ENABLE_MDC610_CAMERA_INTERFACE)
    std::shared_ptr<Mdc610CameraInterface<holo_cmw::encodedProxy>> interface_;
#endif

private:
    static constexpr int32_t MIN_NV12_CHANNEL_ID = 21;
    static constexpr int32_t MAX_NV12_CHANNEL_ID = 34;
    static constexpr int32_t MIN_H265_CHANNEL_ID = 71;
    static constexpr int32_t MAX_H265_CHANNEL_ID = 84;
};

template <typename Tcvt, typename Tenc = DummyEncoder>
class ImageCaptureVirtAppT : public ImageCaptureAppBase
{
public:
    ImageCaptureVirtAppT(int32_t id, std::string const& ns)
      : ImageCaptureAppBase(id, ns), output_{new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>()}
    {
    }

    void Setup(const std::string& config_file, const std::string& save_image, const std::string& output_video_size = "", bool_t blocking_mode = true) override;

private:
    void ImageCounterHandler(uint32_t counter);

private:
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    cmw_wrapper::BusType::WriterType<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>        pub_info_;
    cmw_wrapper::BusType::WriterType<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>> pub_encoded_;
#else
    cmw_wrapper::BusType::WriterType<uint64_t> pub_info_;
    cmw_wrapper::BusType::WriterType<uint8_t*> pub_encoded_;
#endif
    std::shared_ptr<uint8_t>                         output_;
    std::shared_ptr<ImageCaptureVirtual<Tcvt, Tenc>> driver_;
    std::shared_ptr<VirtCamInterface>                data_interface_;
};
}  // namespace holo_cmw

#endif  // _HOLO_CMW_APPS_IMAGE_CAPTURE_H
