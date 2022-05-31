/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_decoder.cpp.
 * @brief Image Decoder.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2019-12-11.
 */

#include <holo/log/hololog.h>
#include <holo/os/time.h>
#include <holo/sensors/camera/decoder/image_decoder_h26x.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/utils/yaml.h>
#include <fstream>
namespace holo
{
namespace sensors
{
namespace camera
{
AVCodec* H26xDecoderCodecFinder<ImageType::H264>::FindDecoder()
{
#ifdef HOLO_CAMERA_USE_CUDA
    LOG(INFO) << "find GPU version decoder";
    auto codec = avcodec_find_decoder_by_name("h264_cuvid");
#else
    LOG(INFO) << "find CPU version decoder";
    auto codec = avcodec_find_decoder(AV_CODEC_ID_H264);
#endif
    if (nullptr == codec)
    {
        LOG(ERROR) << "failed to init decoder";
    }
    else
    {
        LOG(INFO) << "decoder's name:" << codec->name;
    }

    return codec;
}

AVCodec* H26xDecoderCodecFinder<ImageType::H265>::FindDecoder()
{
#ifdef HOLO_CAMERA_USE_CUDA
    LOG(INFO) << "find GPU version decoder";
    auto codec = avcodec_find_decoder_by_name("hevc_cuvid");
#else
    LOG(INFO) << "find CPU version decoder";
    auto codec = avcodec_find_decoder(AV_CODEC_ID_H265);
#endif

    if (nullptr == codec)
    {
        LOG(ERROR) << "failed to init decoder";
    }
    else
    {
        LOG(INFO) << "decoder's name:" << codec->name;
    }

    return codec;
}

template class H26xDecoderCodecFinder<ImageType::H264>;
template class H26xDecoderCodecFinder<ImageType::H265>;

template <ImageType InType, holo::Image::Encoding OutType>
H26xDecoderBase<InType, OutType>::H26xDecoderBase(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps,
                                                  bool_t show_image)
  : ImageDecoderBase(), ImageDecoderData(id, cols, rows, fps, OutType, show_image), H26xDecoderCodecFinder<InType>()
{
    ImageDecoderBase::SetOutputVideoSize(cols, rows);

    av_register_all();
    avcodec_register_all();
    pkt_ = av_packet_alloc();
    if (!pkt_)
    {
        std::string error = "failed to alloc avcodec packet";
        LOG(ERROR) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    codec_ = H26xDecoderCodecFinder<InType>::FindDecoder();
    if (!codec_)
    {
        std::string error = "failed to find avcodec decoder";
        LOG(ERROR) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    codec_context_ = avcodec_alloc_context3(codec_);
    if (!codec_context_)
    {
        std::string error = "failed to init code context";
        LOG(ERROR) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    if (avcodec_open2(codec_context_, codec_, NULL) < 0)
    {
        std::string error = "failed to open avcodec";
        LOG(ERROR) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    frame_ = av_frame_alloc();
    if (!frame_)
    {
        std::string error = "failed to init av frame";
        LOG(ERROR) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }
    InitYuvTable();
}

template <ImageType InType, holo::Image::Encoding OutType>
H26xDecoderBase<InType, OutType>::~H26xDecoderBase() noexcept
{
    if (codec_context_)
    {
        (void)avcodec_send_packet(codec_context_, NULL);
        avcodec_free_context(&codec_context_);
    }
    if (frame_)
    {
        av_frame_free(&frame_);
    }
    if (pkt_)
    {
        av_packet_free(&pkt_);
    }
}

template class H26xDecoderBase<ImageType::H264, holo::Image::Encoding::RGB>;
template class H26xDecoderBase<ImageType::H265, holo::Image::Encoding::RGB>;
template class H26xDecoderBase<ImageType::H264, holo::Image::Encoding::BGR>;
template class H26xDecoderBase<ImageType::H265, holo::Image::Encoding::BGR>;
template class H26xDecoderBase<ImageType::H264, holo::Image::Encoding::NV12>;
template class H26xDecoderBase<ImageType::H265, holo::Image::Encoding::NV12>;

template <ImageType InType, holo::Image::Encoding OutType>
ImageType H26xDecoder<InType, OutType>::GetImageType() const noexcept
{
    return InType;
}

template <ImageType InType, holo::Image::Encoding OutType>
holo::Image::Encoding H26xDecoder<InType, OutType>::GetEncoding() const noexcept
{
    return OutType;
}

template <ImageType InType, holo::Image::Encoding OutType>
ImageType H26xDecoder<InType, OutType>::GetInputType()
{
    return InType;
}

template <ImageType InType, holo::Image::Encoding OutType>
holo::Image::Encoding H26xDecoder<InType, OutType>::GetOutputType()
{
    return OutType;
}

template <ImageType InType>
H26xDecoder<InType, holo::Image::Encoding::RGB>::H26xDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps,
                                                             bool_t show_image)
  : H26xDecoderBase<InType, holo::Image::Encoding::RGB>(id, cols, rows, fps, show_image)
{
    BASE::out_image_.ConfigImage(cols, rows, holo::Image::Encoding::RGB);
}

template <ImageType InType>
ImageType H26xDecoder<InType, holo::Image::Encoding::RGB>::GetImageType() const noexcept
{
    return InType;
}

template <ImageType InType>
holo::Image::Encoding H26xDecoder<InType, holo::Image::Encoding::RGB>::GetEncoding() const noexcept
{
    return holo::Image::Encoding::RGB;
}

template <ImageType InType>
ImageType H26xDecoder<InType, holo::Image::Encoding::RGB>::GetInputType()
{
    return InType;
}

template <ImageType InType>
holo::Image::Encoding H26xDecoder<InType, holo::Image::Encoding::RGB>::GetOutputType()
{
    return holo::Image::Encoding::RGB;
}

template <ImageType InType>
bool_t H26xDecoder<InType, holo::Image::Encoding::RGB>::Decode(const ImagePacket& image_packet)
{
    BASE::pkt_->size = image_packet.size;
    BASE::pkt_->data = image_packet.data;
    BASE::pkt_->pts  = image_packet.trigger_stamp.ToNsec();
    (void)BASE::timestamp_map_.insert(
        std::make_pair(image_packet.trigger_stamp.ToNsec(), image_packet.received_stamp.ToNsec()));
    int32_t ret = avcodec_send_packet(BASE::codec_context_, BASE::pkt_);
    if (ret < 0)
    {
        LOG(ERROR) << "error sending a packet for decoding";
        BASE::pkt_->size = 0;
        BASE::pkt_->data = nullptr;
        return false;
    }
    while (ret >= 0)
    {
        ret = avcodec_receive_frame(BASE::codec_context_, BASE::frame_);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        {
            return true;
        }
        else if (ret < 0)
        {
            LOG(ERROR) << "error during decoding: " << stderr;
            BASE::pkt_->size = 0;
            BASE::pkt_->data = nullptr;
            return false;
        }
        // LOG(INFO) << std::fixed << std::setprecision(3) << BASE::timestamp_pair_.first.ToSec();
        BASE::out_image_.SetTriggerStamp(Timestamp(static_cast<uint64_t>(BASE::frame_->pts)));
        BASE::out_image_.SetReceivedStamp(Timestamp(static_cast<uint64_t>(BASE::timestamp_map_[BASE::frame_->pts])));
        (void)BASE::timestamp_map_.erase(BASE::frame_->pts);
        // LOG(INFO) << frame_->width << ", " << frame_->height << ", " << int(frame_->format);
#ifdef HOLO_CAMERA_USE_CUDA
        Nv122Rgb(BASE::frame_->data[0], BASE::frame_->data[1], (uint8_t*)BASE::out_image_.GetData(), BASE::cols_,
                 BASE::rows_);
#else
        Nv122Rgb(BASE::frame_->data[0], BASE::frame_->data[1], BASE::frame_->data[2],
                 (uint8_t*)BASE::out_image_.GetData(), BASE::cols_, BASE::rows_);
#endif

        holo::Image output_image(BASE::output_video_cols_, BASE::output_video_rows_, holo::Image::Encoding::RGB);
        if ((BASE::output_video_cols_ != BASE::cols_) || (BASE::output_video_rows_ != BASE::rows_))
        {
            holo::sensors::image::RGB24Resize(BASE::out_image_, output_image);
            output_image.SetTriggerStamp(BASE::out_image_.GetTriggerStamp());
            output_image.SetReceivedStamp(BASE::out_image_.GetReceivedStamp());
        }
        else
        {
            output_image = BASE::out_image_;
        }

        if (BASE::image_callback_)
        {
            BASE::image_callback_(output_image);
        }

        /* show */
        if (BASE::show_image_)
        {
            cv::Mat image;
            cv::cvtColor(Image2Mat(output_image), image, CV_RGB2BGR);
            cv::imshow("image" + std::to_string(static_cast<uint32_t>(BASE::sensor_id_)), image);
            (void)cvWaitKey(1);
        }
    }
    return true;
}

template <ImageType InType>
H26xDecoder<InType, holo::Image::Encoding::BGR>::H26xDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps,
                                                             bool_t show_image)
  : H26xDecoderBase<InType, holo::Image::Encoding::BGR>(id, cols, rows, fps, show_image)
{
    BASE::out_image_.ConfigImage(cols, rows, holo::Image::Encoding::BGR);
}

template <ImageType InType>
ImageType H26xDecoder<InType, holo::Image::Encoding::BGR>::GetImageType() const noexcept
{
    return InType;
}

template <ImageType InType>
holo::Image::Encoding H26xDecoder<InType, holo::Image::Encoding::BGR>::GetEncoding() const noexcept
{
    return holo::Image::Encoding::BGR;
}

template <ImageType InType>
ImageType H26xDecoder<InType, holo::Image::Encoding::BGR>::GetInputType()
{
    return InType;
}

template <ImageType InType>
holo::Image::Encoding H26xDecoder<InType, holo::Image::Encoding::BGR>::GetOutputType()
{
    return holo::Image::Encoding::BGR;
}

template <ImageType InType>
bool_t H26xDecoder<InType, holo::Image::Encoding::BGR>::Decode(const ImagePacket& image_packet)
{
    BASE::pkt_->size = image_packet.size;
    BASE::pkt_->data = image_packet.data;
    BASE::pkt_->pts  = image_packet.trigger_stamp.ToNsec();
    (void)BASE::timestamp_map_.insert(
        std::make_pair(image_packet.trigger_stamp.ToNsec(), image_packet.received_stamp.ToNsec()));
    int32_t ret = avcodec_send_packet(BASE::codec_context_, BASE::pkt_);
    if (ret < 0)
    {
        LOG(ERROR) << "error sending a packet for decoding";
        BASE::pkt_->size = 0;
        BASE::pkt_->data = nullptr;
        return false;
    }
    while (ret >= 0)
    {
        ret = avcodec_receive_frame(BASE::codec_context_, BASE::frame_);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        {
            return true;
        }
        else if (ret < 0)
        {
            LOG(ERROR) << "error during decoding: " << stderr;
            BASE::pkt_->size = 0;
            BASE::pkt_->data = nullptr;
            return false;
        }
        // LOG(INFO) << std::fixed << std::setprecision(3) << BASE::timestamp_pair_.first.ToSec();
        BASE::out_image_.SetTriggerStamp(Timestamp(static_cast<uint64_t>(BASE::frame_->pts)));
        BASE::out_image_.SetReceivedStamp(Timestamp(static_cast<uint64_t>(BASE::timestamp_map_[BASE::frame_->pts])));
        (void)BASE::timestamp_map_.erase(BASE::frame_->pts);
        // LOG(INFO) << frame_->width << ", " << frame_->height << ", " << int(frame_->format);
#ifdef HOLO_CAMERA_USE_CUDA
        Nv122Bgr(BASE::frame_->data[0], BASE::frame_->data[1], (uint8_t*)BASE::out_image_.GetData(), BASE::cols_,
                 BASE::rows_);
#else
        Nv122Bgr(BASE::frame_->data[0], BASE::frame_->data[1], BASE::frame_->data[2],
                 (uint8_t*)BASE::out_image_.GetData(), BASE::cols_, BASE::rows_);
#endif

        holo::Image output_image(BASE::output_video_cols_, BASE::output_video_rows_, holo::Image::Encoding::BGR);
        if ((BASE::output_video_cols_ != BASE::cols_) || (BASE::output_video_rows_ != BASE::rows_))
        {
            holo::sensors::image::BGR24Resize(BASE::out_image_, output_image);
            output_image.SetTriggerStamp(BASE::out_image_.GetTriggerStamp());
            output_image.SetReceivedStamp(BASE::out_image_.GetReceivedStamp());
        }
        else
        {
            output_image = BASE::out_image_;
        }

        if (BASE::image_callback_)
        {
            BASE::image_callback_(output_image);
        }

        /* show */
        if (BASE::show_image_)
        {
            cv::imshow("image" + std::to_string(static_cast<uint32_t>(BASE::sensor_id_)),
                       Image2Mat(output_image));
            (void)cvWaitKey(1);
        }
    }
    return true;
}

template <ImageType InType>
H26xDecoder<InType, holo::Image::Encoding::NV12>::H26xDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps,
                                                              bool_t show_image)
  : H26xDecoderBase<InType, holo::Image::Encoding::NV12>(id, cols, rows, fps, show_image)
{
    BASE::out_image_.ConfigImage(cols, rows, holo::Image::Encoding::NV12);
}

template <ImageType InType>
ImageType H26xDecoder<InType, holo::Image::Encoding::NV12>::GetImageType() const noexcept
{
    return InType;
}

template <ImageType InType>
holo::Image::Encoding H26xDecoder<InType, holo::Image::Encoding::NV12>::GetEncoding() const noexcept
{
    return holo::Image::Encoding::NV12;
}

template <ImageType InType>
ImageType H26xDecoder<InType, holo::Image::Encoding::NV12>::GetInputType()
{
    return InType;
}

template <ImageType InType>
holo::Image::Encoding H26xDecoder<InType, holo::Image::Encoding::NV12>::GetOutputType()
{
    return holo::Image::Encoding::NV12;
}

template <ImageType InType>
bool_t H26xDecoder<InType, holo::Image::Encoding::NV12>::Decode(const ImagePacket& image_packet)
{
    BASE::pkt_->size = image_packet.size;
    BASE::pkt_->data = image_packet.data;
    BASE::pkt_->pts  = image_packet.trigger_stamp.ToNsec();
    (void)BASE::timestamp_map_.insert(
        std::make_pair(image_packet.trigger_stamp.ToNsec(), image_packet.received_stamp.ToNsec()));
    int32_t ret = avcodec_send_packet(BASE::codec_context_, BASE::pkt_);
    if (ret < 0)
    {
        LOG(ERROR) << "error sending a packet for decoding";
        BASE::pkt_->size = 0;
        BASE::pkt_->data = nullptr;
        return false;
    }
    while (ret >= 0)
    {
        ret = avcodec_receive_frame(BASE::codec_context_, BASE::frame_);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        {
            return true;
        }
        else if (ret < 0)
        {
            LOG(ERROR) << "error during decoding: " << stderr;
            BASE::pkt_->size = 0;
            BASE::pkt_->data = nullptr;
            return false;
        }
        // LOG(INFO) << std::fixed << std::setprecision(3) << BASE::timestamp_pair_.first.ToSec();
        BASE::out_image_.SetTriggerStamp(Timestamp(static_cast<uint64_t>(BASE::frame_->pts)));
        BASE::out_image_.SetReceivedStamp(Timestamp(static_cast<uint64_t>(BASE::timestamp_map_[BASE::frame_->pts])));
        (void)BASE::timestamp_map_.erase(BASE::frame_->pts);
        // LOG(INFO) << BASE::frame_->width << ", " << BASE::frame_->height << ", " << int(BASE::frame_->format);
        const uint32_t size = BASE::frame_->width * BASE::frame_->height;
        (void)std::memcpy(BASE::out_image_.GetData(), BASE::frame_->data[0], size);

#ifdef HOLO_CAMERA_USE_CUDA
        (void)std::memcpy(BASE::out_image_.GetData() + size, BASE::frame_->data[1], size / 2);
#else
        const uint32_t qsize = size / 4;
        for (uint32_t i = 0; i < qsize; ++i)
        {
            BASE::out_image_.GetData()[size + i * 2]     = BASE::frame_->data[1][i];
            BASE::out_image_.GetData()[size + i * 2 + 1] = BASE::frame_->data[2][i];
        }
#endif

        holo::Image output_image(BASE::output_video_cols_, BASE::output_video_rows_, holo::Image::Encoding::NV12);
        if ((BASE::output_video_cols_ != BASE::cols_) || (BASE::output_video_rows_ != BASE::rows_))
        {
            holo::sensors::image::NV12Resize(BASE::out_image_, output_image);
            output_image.SetTriggerStamp(BASE::out_image_.GetTriggerStamp());
            output_image.SetReceivedStamp(BASE::out_image_.GetReceivedStamp());
        }
        else
        {
            output_image = BASE::out_image_;
        }

        if (BASE::image_callback_)
        {
            BASE::image_callback_(output_image);
        }

        /* show */
        if (BASE::show_image_)
        {
            cv::Mat image;
            cv::cvtColor(Image2Mat(BASE::out_image_), image, CV_YUV2BGR_NV12);
            cv::imshow("image" + std::to_string(static_cast<uint32_t>(BASE::sensor_id_)), image);
            (void)cvWaitKey(1);
        }
    }
    return true;
}
#if defined(HOLO_PLATFORM_TDA4)
    H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>::H26xDecoder(SensorId id, uint16_t cols, uint16_t rows, uint32_t fps, bool_t show_image)
      : ImageDecoderBase()
      , ImageDecoderData(id, cols, rows, fps, holo::Image::Encoding::NV12, show_image)
      , Tda4DecodeVxContext(1)
      , skip_this_frame_(true)
    {
        ImageDecoderBase::SetOutputVideoSize(cols, rows);
        ImageDecoderData::out_image_.ConfigImage(cols, rows, holo::Image::Encoding::NV12);
        app_init_resource(&dec_, cols, rows);
    }

    H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>::~H26xDecoder()
    {
        app_decode_deinit(&dec_);
        // tivxHostDeInit();
        // tivxDeInit();
        // appCommonDeInit();
    }

ImageType H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>::GetImageType() const noexcept
{
    return ImageType::H264;
}

holo::Image::Encoding H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>::GetEncoding() const noexcept
{
    return holo::Image::Encoding::NV12;
}

ImageType H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>::GetInputType()
{
    return ImageType::H264;
}

holo::Image::Encoding H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>::GetOutputType()
{
    return holo::Image::Encoding::NV12;
}

bool_t H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>::Decode(const ImagePacket& image_packet)
{
    timestamp_cache_.push(std::make_pair(image_packet.trigger_stamp, image_packet.received_stamp));

    dec_.decodeObj.info.bitstream_sizes = image_packet.size;
    (void)std::memcpy(dec_.decodeObj.info.streambuf, image_packet.data, image_packet.size);
    app_run_decode(&dec_);
    if (skip_this_frame_)
    {
        skip_this_frame_ = false;
        return false;
    }
    static const uint32_t size = ImageDecoderData::cols_ * ImageDecoderData::rows_;
    ImageDecoderData::out_image_.SetTriggerStamp(timestamp_cache_.front().first);
    ImageDecoderData::out_image_.SetReceivedStamp(timestamp_cache_.front().second);
    timestamp_cache_.pop();
    (void)std::memcpy(ImageDecoderData::out_image_.GetData(), dec_.decodeObj.info.ptr_y, size);
    (void)std::memcpy(ImageDecoderData::out_image_.GetData() + size, dec_.decodeObj.info.ptr_uv, size / 2);

    holo::Image output_image(ImageDecoderBase::output_video_cols_, ImageDecoderBase::output_video_rows_, holo::Image::Encoding::NV12);
    if ((ImageDecoderBase::output_video_cols_ != ImageDecoderData::cols_) || (ImageDecoderBase::output_video_rows_ != ImageDecoderData::rows_))
    {
        holo::sensors::image::NV12Resize(ImageDecoderData::out_image_, output_image);
        output_image.SetTriggerStamp(ImageDecoderData::out_image_.GetTriggerStamp());
        output_image.SetReceivedStamp(ImageDecoderData::out_image_.GetReceivedStamp());
    }
    else
    {
        output_image = ImageDecoderData::out_image_;
    }

    if (ImageDecoderBase::image_callback_)
    {
        ImageDecoderBase::image_callback_(output_image);
    }

    /* show */
    if (ImageDecoderData::show_image_)
    {
        cv::Mat image;
        cv::cvtColor(Image2Mat(ImageDecoderData::out_image_), image, CV_YUV2BGR_NV12);
        cv::imshow("image" + std::to_string(static_cast<uint32_t>(ImageDecoderData::sensor_id_)), image);
        (void)cvWaitKey(1);
    }

    return true;
}
#endif

#ifdef HOLO_PLATFORM_MDC610
H26xDecoder<ImageType::H265, holo::Image::Encoding::RGB>::H26xDecoder(SensorId id, uint16_t cols, uint16_t rows,
                                                                      uint32_t fps, bool_t show_image)
  : ImageDecoderBase()
  , ImageDecoderData(id, cols, rows, fps, holo::Image::Encoding::RGB, show_image)
  , ImageDecoderDvpp(cols, rows)
  , found_first_key_frame_(false)
{
    ImageDecoderBase::SetOutputVideoSize(cols, rows);
    ImageDecoderData::out_image_.ConfigImage(cols, rows, holo::Image::Encoding::RGB);
}

ImageType H26xDecoder<ImageType::H265, holo::Image::Encoding::RGB>::GetImageType() const noexcept
{
    return ImageType::H265;
}

holo::Image::Encoding H26xDecoder<ImageType::H265, holo::Image::Encoding::RGB>::GetEncoding() const noexcept
{
    return holo::Image::Encoding::RGB;
}

ImageType H26xDecoder<ImageType::H265, holo::Image::Encoding::RGB>::GetInputType()
{
    return ImageType::H265;
}

holo::Image::Encoding H26xDecoder<ImageType::H265, holo::Image::Encoding::RGB>::GetOutputType()
{
    return holo::Image::Encoding::RGB;
}

bool_t H26xDecoder<ImageType::H265, holo::Image::Encoding::RGB>::Decode(const ImagePacket& image_packet)
{
    if (!found_first_key_frame_)
    {
        if (((uint8_t)FrameType::I != image_packet.frame_type))
        {
            if ((image_packet.size < ImageDecoderDvpp::MIN_I_FRAME_SIZE))
            {
                return false;
            }
        }
    }

    found_first_key_frame_ = true;

    uint8_t* yuv_data      = nullptr;
    bool_t   decode_result = ImageDecoderDvpp::DecodeH265Data(image_packet, &yuv_data);
    if (!decode_result)
    {
        return false;
    }

    timestamp_cache_.push(std::make_pair(image_packet.trigger_stamp, image_packet.received_stamp));

    if (nullptr == yuv_data)
    {
        return false;
    }

    ImageDecoderData::out_image_.SetTriggerStamp(timestamp_cache_.front().first);
    ImageDecoderData::out_image_.SetReceivedStamp(timestamp_cache_.front().second);
    timestamp_cache_.pop();

    const uint32_t size = ImageDecoderData::cols_ * ImageDecoderData::rows_;

    Nv122Rgb(yuv_data, yuv_data + size, (uint8_t*)ImageDecoderData::out_image_.GetData(), ImageDecoderData::cols_,
             ImageDecoderData::rows_);
    free(yuv_data);
    yuv_data = nullptr;

    holo::Image output_image(ImageDecoderBase::output_video_cols_, ImageDecoderBase::output_video_rows_, holo::Image::Encoding::RGB);
    if ((ImageDecoderBase::output_video_cols_ != ImageDecoderData::cols_) || (ImageDecoderBase::output_video_rows_ != ImageDecoderData::rows_))
    {
        holo::sensors::image::RGB24Resize(ImageDecoderData::out_image_, output_image);
        output_image.SetTriggerStamp(ImageDecoderData::out_image_.GetTriggerStamp());
        output_image.SetReceivedStamp(ImageDecoderData::out_image_.GetReceivedStamp());
    }
    else
    {
        output_image = ImageDecoderData::out_image_;
    }

    if (ImageDecoderBase::image_callback_)
    {
        ImageDecoderBase::image_callback_(output_image);
    }

    /* show */
    if (ImageDecoderData::show_image_)
    {
        cv::Mat image;
        cv::cvtColor(Image2Mat(ImageDecoderData::out_image_), image, CV_YUV2BGR_NV12);
        cv::imshow("image" + std::to_string(static_cast<uint32_t>(ImageDecoderData::sensor_id_)), image);
        (void)cvWaitKey(1);
    }

    return true;
}

H26xDecoder<ImageType::H265, holo::Image::Encoding::BGR>::H26xDecoder(SensorId id, uint16_t cols, uint16_t rows,
                                                                      uint32_t fps, bool_t show_image)
  : ImageDecoderBase()
  , ImageDecoderData(id, cols, rows, fps, holo::Image::Encoding::BGR, show_image)
  , ImageDecoderDvpp(cols, rows)
  , found_first_key_frame_(false)
{
    ImageDecoderBase::SetOutputVideoSize(cols, rows);
    ImageDecoderData::out_image_.ConfigImage(cols, rows, holo::Image::Encoding::BGR);
}

ImageType H26xDecoder<ImageType::H265, holo::Image::Encoding::BGR>::GetImageType() const noexcept
{
    return ImageType::H265;
}

holo::Image::Encoding H26xDecoder<ImageType::H265, holo::Image::Encoding::BGR>::GetEncoding() const noexcept
{
    return holo::Image::Encoding::BGR;
}

ImageType H26xDecoder<ImageType::H265, holo::Image::Encoding::BGR>::GetInputType()
{
    return ImageType::H265;
}

holo::Image::Encoding H26xDecoder<ImageType::H265, holo::Image::Encoding::BGR>::GetOutputType()
{
    return holo::Image::Encoding::BGR;
}

bool_t H26xDecoder<ImageType::H265, holo::Image::Encoding::BGR>::Decode(const ImagePacket& image_packet)
{
    if (!found_first_key_frame_)
    {
        if (((uint8_t)FrameType::I != image_packet.frame_type))
        {
            if ((image_packet.size < ImageDecoderDvpp::MIN_I_FRAME_SIZE))
            {
                return false;
            }
        }
    }

    found_first_key_frame_ = true;

    uint8_t* yuv_data      = nullptr;
    bool_t   decode_result = ImageDecoderDvpp::DecodeH265Data(image_packet, &yuv_data);
    if (!decode_result)
    {
        return false;
    }

    timestamp_cache_.push(std::make_pair(image_packet.trigger_stamp, image_packet.received_stamp));

    if (nullptr == yuv_data)
    {
        return false;
    }

    ImageDecoderData::out_image_.SetTriggerStamp(timestamp_cache_.front().first);
    ImageDecoderData::out_image_.SetReceivedStamp(timestamp_cache_.front().second);
    timestamp_cache_.pop();

    const uint32_t size = ImageDecoderData::cols_ * ImageDecoderData::rows_;

    Nv122Bgr(yuv_data, yuv_data + size, (uint8_t*)ImageDecoderData::out_image_.GetData(), ImageDecoderData::cols_,
             ImageDecoderData::rows_);
    free(yuv_data);
    yuv_data = nullptr;

    holo::Image output_image(ImageDecoderBase::output_video_cols_, ImageDecoderBase::output_video_rows_, holo::Image::Encoding::BGR);
    if ((ImageDecoderBase::output_video_cols_ != ImageDecoderData::cols_) || (ImageDecoderBase::output_video_rows_ != ImageDecoderData::rows_))
    {
        holo::sensors::image::BGR24Resize(ImageDecoderData::out_image_, output_image);
        output_image.SetTriggerStamp(ImageDecoderData::out_image_.GetTriggerStamp());
        output_image.SetReceivedStamp(ImageDecoderData::out_image_.GetReceivedStamp());
    }
    else
    {
        output_image = ImageDecoderData::out_image_;
    }

    if (ImageDecoderBase::image_callback_)
    {
        ImageDecoderBase::image_callback_(output_image);
    }

    /* show */
    if (ImageDecoderData::show_image_)
    {
        cv::Mat image;
        cv::cvtColor(Image2Mat(ImageDecoderData::out_image_), image, CV_YUV2BGR_NV12);
        cv::imshow("image" + std::to_string(static_cast<uint32_t>(ImageDecoderData::sensor_id_)), image);
        (void)cvWaitKey(1);
    }

    return true;
}

H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>::H26xDecoder(SensorId id, uint16_t cols, uint16_t rows,
                                                                       uint32_t fps, bool_t show_image)
  : ImageDecoderBase()
  , ImageDecoderData(id, cols, rows, fps, holo::Image::Encoding::NV12, show_image)
  , ImageDecoderDvpp(cols, rows)
  , found_first_key_frame_(false)
{
    ImageDecoderBase::SetOutputVideoSize(cols, rows);
    ImageDecoderData::out_image_.ConfigImage(cols, rows, holo::Image::Encoding::NV12);
}

ImageType H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>::GetImageType() const noexcept
{
    return ImageType::H265;
}

holo::Image::Encoding H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>::GetEncoding() const noexcept
{
    return holo::Image::Encoding::NV12;
}

ImageType H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>::GetInputType()
{
    return ImageType::H265;
}

holo::Image::Encoding H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>::GetOutputType()
{
    return holo::Image::Encoding::NV12;
}

bool_t H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>::Decode(const ImagePacket& image_packet)
{
    if (!found_first_key_frame_)
    {
        if (((uint8_t)FrameType::I != image_packet.frame_type))
        {
            if ((image_packet.size < ImageDecoderDvpp::MIN_I_FRAME_SIZE))
            {
                return false;
            }
        }
    }

    found_first_key_frame_ = true;

    uint8_t* yuv_data      = nullptr;
    bool_t   decode_result = ImageDecoderDvpp::DecodeH265Data(image_packet, &yuv_data);
    if (!decode_result)
    {
        return false;
    }

    timestamp_cache_.push(std::make_pair(image_packet.trigger_stamp, image_packet.received_stamp));

    if (nullptr == yuv_data)
    {
        return false;
    }

    ImageDecoderData::out_image_.SetTriggerStamp(timestamp_cache_.front().first);
    ImageDecoderData::out_image_.SetReceivedStamp(timestamp_cache_.front().second);
    timestamp_cache_.pop();

    const uint32_t size = ImageDecoderData::cols_ * ImageDecoderData::rows_;

    (void)std::memcpy(ImageDecoderData::out_image_.GetData(), yuv_data, size * 3 / 2);
    free(yuv_data);
    yuv_data = nullptr;

    holo::Image output_image(ImageDecoderBase::output_video_cols_, ImageDecoderBase::output_video_rows_, holo::Image::Encoding::NV12);
    if ((ImageDecoderBase::output_video_cols_ != ImageDecoderData::cols_) || (ImageDecoderBase::output_video_rows_ != ImageDecoderData::rows_))
    {
        holo::sensors::image::NV12Resize(ImageDecoderData::out_image_, output_image);
        output_image.SetTriggerStamp(ImageDecoderData::out_image_.GetTriggerStamp());
        output_image.SetReceivedStamp(ImageDecoderData::out_image_.GetReceivedStamp());
    }
    else
    {
        output_image = ImageDecoderData::out_image_;
    }

    if (ImageDecoderBase::image_callback_)
    {
        ImageDecoderBase::image_callback_(output_image);
    }

    /* show */
    if (ImageDecoderData::show_image_)
    {
        cv::Mat image;
        cv::cvtColor(Image2Mat(ImageDecoderData::out_image_), image, CV_YUV2BGR_NV12);
        cv::imshow("image" + std::to_string(static_cast<uint32_t>(ImageDecoderData::sensor_id_)), image);
        (void)cvWaitKey(1);
    }

    return true;
}
#endif

template class H26xDecoder<ImageType::H264, holo::Image::Encoding::RGB>;
template class H26xDecoder<ImageType::H265, holo::Image::Encoding::RGB>;

template class H26xDecoder<ImageType::H264, holo::Image::Encoding::BGR>;
template class H26xDecoder<ImageType::H265, holo::Image::Encoding::BGR>;

template class H26xDecoder<ImageType::H264, holo::Image::Encoding::NV12>;
template class H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>;

}  // namespace camera
}  // namespace sensors
}  // namespace holo
