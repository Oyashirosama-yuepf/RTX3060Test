/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_capture_rgb.h
 * @brief Image rgb driver
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2020-09-27
 */

#include <holo/sensors/camera/capture/image_capture_rgb.h>

namespace holo
{
namespace sensors
{
namespace camera
{
template <typename Tcvt, typename Tenc>
ImageCaptureBasic<Tcvt, Tenc>::ImageCaptureBasic(SensorId sensor_id, uint32_t cols, uint32_t rows, uint32_t fps,
                                                 bool_t show_image)
  : Tcvt(cols, rows)
  , Tenc(cols, rows, fps)
  , cols_(cols)
  , rows_(rows)
  , output_video_cols_(cols)
  , output_video_rows_(rows)
  , sensor_id_(sensor_id)
  , show_image_(show_image)
  , image_callback_(nullptr)
  , image_counter_callback_(nullptr)
{
    /* image */
    rgb_image_.ConfigImage(cols, rows, Tcvt::GetEncoding());
}

template <typename Tcvt, typename Tenc>
void ImageCaptureBasic<Tcvt, Tenc>::SetImageCallback(const ImageCallbackType& handler) noexcept
{
    image_callback_ = handler;
}

template <typename Tcvt, typename Tenc>
void ImageCaptureBasic<Tcvt, Tenc>::SetImageCounterCallback(const CounterCallbackType& handler) noexcept
{
    image_counter_callback_ = handler;
}

template <typename Tcvt, typename Tenc>
void ImageCaptureBasic<Tcvt, Tenc>::ParseData(const StreamBuffer& buffer, const Timestamp& received_stamp,
                                              const Timestamp& trigger_stamp)
{
    (void)Tcvt::Convert(buffer, rgb_image_);

    rgb_image_.SetReceivedStamp(received_stamp);
    rgb_image_.SetTriggerStamp(trigger_stamp);

#if defined(HOLO_PLATFORM_MDC610)
    holo::Image output_image(output_video_cols_, output_video_rows_, holo::Image::Encoding::NV12);
#else
    holo::Image output_image(output_video_cols_, output_video_rows_, holo::Image::Encoding::RGB);
#endif

    if ((output_video_cols_ != cols_) || (output_video_rows_ != rows_))
    {
#if defined(HOLO_PLATFORM_MDC610)
        holo::sensors::image::NV12Resize(rgb_image_, output_image);
        output_image.SetReceivedStamp(rgb_image_.GetReceivedStamp());
        output_image.SetTriggerStamp(rgb_image_.GetReceivedStamp());
#else
        holo::sensors::image::RGB24Resize(rgb_image_, output_image);
        output_image.SetReceivedStamp(rgb_image_.GetReceivedStamp());
        output_image.SetTriggerStamp(rgb_image_.GetReceivedStamp());
#endif
    }
    else
    {
        output_image = rgb_image_;
    }

    if (image_callback_)
    {
        image_callback_(output_image);
    }

    /* encode */
    if (Tenc::GetOutputType() != ImageType::INVALID)
    {
        (void)Tenc::Encode(rgb_image_);
    }
    /* show */
    if (show_image_)
    {
        cv::Mat image;
        if (Tcvt::GetEncoding() == Image::Encoding::RGB)
        {
            cv::cvtColor(Image2Mat(output_image), image, CV_RGB2BGR);
        }
        else if (Tcvt::GetEncoding() == Image::Encoding::NV12)
        {
            cv::cvtColor(Image2Mat(output_image), image, CV_YUV2BGR_NV12);
        }
        else if (Tcvt::GetEncoding() == Image::Encoding::BGR)
        {
            // Don't have to convert
        }
        else
        {
            std::string error = "failed to show image";
            LOG(ERROR) << error;
            throw std::runtime_error(error);
        }
        cv::imshow("capture driver", image);
        (void)cvWaitKey(10);
    }
}

template <typename Tcvt, typename Tenc>
void ImageCaptureBasic<Tcvt, Tenc>::SetOutputVideoSize(uint32_t output_video_cols, uint32_t output_video_rows)
{
    output_video_cols_ = output_video_cols;
    output_video_rows_ = output_video_rows;
}

template <typename Tcvt, typename Tenc, typename Tsync>
ImageCaptureRgbT<Tcvt, Tenc, Tsync>::ImageCaptureRgbT(SensorId sensor_id, uint32_t cols, uint32_t rows, uint32_t fps,
                                                      bool_t trigger_mode, bool_t show_image)
  : ImageCaptureBasic<Tcvt, Tenc>(sensor_id, cols, rows, fps, show_image), ImageTimestamperT<Tsync>(fps, trigger_mode)
{
}

template <typename Tcvt, typename Tenc, typename Tsync>
void ImageCaptureRgbT<Tcvt, Tenc, Tsync>::ParseData(const StreamBuffer& buffer, const Timestamp& image_stamp)
{
    Timestamp received_stamp;
    Timestamp trigger_stamp = image_stamp;
    if (false == ImageTimestamperT<Tsync>::UpdateTimestamp(received_stamp, trigger_stamp))
    {
        LOG(WARNING) << "timestamp is not sync";
        return;
    }
    ImageCaptureBasic<Tcvt, Tenc>::ParseData(buffer, received_stamp, trigger_stamp);
}

template <typename Tcvt, typename Tenc>
ImageCaptureVirtual<Tcvt, Tenc>::ImageCaptureVirtual(SensorId sensor_id, uint32_t cols, uint32_t rows, uint32_t fps,
                                                     bool_t show_image)
  : ImageCaptureBasic<Tcvt, Tenc>(sensor_id, cols, rows, fps, show_image)
{
}

template <typename Tcvt, typename Tenc>
void ImageCaptureVirtual<Tcvt, Tenc>::ParseData(const StreamBuffer& buffer, const Timestamp& received_stamp,
                                                const Timestamp& trigger_stamp)
{
    ImageCaptureBasic<Tcvt, Tenc>::ParseData(buffer, received_stamp, trigger_stamp);
}

template class ImageCaptureBasic<Bayer8Converter, H264Encoder>;
template class ImageCaptureBasic<YuyvConverter, H264Encoder>;
template class ImageCaptureBasic<Bayer8Converter, DummyEncoder>;
template class ImageCaptureBasic<YuyvConverter, DummyEncoder>;
template class ImageCaptureBasic<RawToNv12Converter, DummyEncoder>;
template class ImageCaptureBasic<UyvyToNv12Converter, DummyEncoder>;
template class ImageCaptureBasic<Nv12ToBgrConverter, DummyEncoder>;

template class ImageCaptureRgbT<Bayer8Converter, H264Encoder, HoloSyncPacket>;
template class ImageCaptureRgbT<YuyvConverter, H264Encoder, HoloSyncPacket>;
template class ImageCaptureRgbT<Bayer8Converter, DummyEncoder, HoloSyncPacket>;
template class ImageCaptureRgbT<YuyvConverter, DummyEncoder, HoloSyncPacket>;
template class ImageCaptureRgbT<RawToNv12Converter, DummyEncoder, HoloSyncPacket>;
template class ImageCaptureRgbT<UyvyToNv12Converter, DummyEncoder, HoloSyncPacket>;
template class ImageCaptureRgbT<Nv12ToBgrConverter, DummyEncoder, HoloSyncPacket>;

template class ImageCaptureRgbT<Bayer8Converter, H264Encoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbT<YuyvConverter, H264Encoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbT<Bayer8Converter, DummyEncoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbT<YuyvConverter, DummyEncoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbT<RawToNv12Converter, DummyEncoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbT<UyvyToNv12Converter, DummyEncoder, HoloSyncDiffPacket>;
template class ImageCaptureRgbT<Nv12ToBgrConverter, DummyEncoder, HoloSyncDiffPacket>;

template class ImageCaptureVirtual<RawToNv12Converter, DummyEncoder>;

}  // namespace camera
}  // namespace sensors
}  // namespace holo