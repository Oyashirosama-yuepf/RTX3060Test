/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_encoder.cpp.
 * @brief Image Encoder.
 * @author guoguangchao(guoguangchao@holomatic.com)
 * @date 2021-03-12
 */

#include <holo/log/hololog.h>
#include <holo/sensors/camera/encoder/image_encoder_h26x.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace sensors
{
namespace camera
{
AVCodec* H26xEncoderCodecFinder<ImageType::H264>::FindEncoder()
{
    AVCodec* codec = nullptr;
#if defined(HOLO_CAMERA_USE_CUDA)
    codec = avcodec_find_encoder_by_name("h264_nvenc");
#else
    codec = avcodec_find_encoder(AV_CODEC_ID_H264);
#endif
    if (!codec)
    {
        LOG(ERROR) << "failed to init Encoder";
    }
    else
    {
        LOG(INFO) << "Encoder is: " << codec->name;
    }
    return codec;
}

AVCodec* H26xEncoderCodecFinder<ImageType::H265>::FindEncoder()
{
    AVCodec* codec = nullptr;
#if defined(HOLO_CAMERA_USE_CUDA)
    codec = avcodec_find_encoder_by_name("hevc_nvenc");
#else
    codec = avcodec_find_encoder(AV_CODEC_ID_H265);
#endif
    if (!codec)
    {
        LOG(ERROR) << "failed to init Encoder";
    }
    else
    {
        LOG(INFO) << "Encoder is: " << codec->name;
    }
    return codec;
}

template class H26xEncoderCodecFinder<ImageType::H264>;
template class H26xEncoderCodecFinder<ImageType::H265>;

/* ImageEncoder */
template <holo::Image::Encoding InType, ImageType OutType>
ImageEncoder<InType, OutType>::ImageEncoder(uint32_t cols, uint32_t rows, uint32_t fps, uint32_t bitrate)
  : H26xEncoderCodecFinder<OutType>()
  , ImageEncoderBase(cols, rows, fps, OutType)
  , counter_(0)
  , pts_counter_(0)
  , out_buf_(nullptr)
  , frame_buf_(nullptr)
#if defined(HOLO_CAMERA_USE_CUDA)
  , cuda_yuv_(nullptr)
  , cuda_rgb_(nullptr)
#endif
{
#if defined(HOLO_CAMERA_USE_CUDA)
    if (cudaMalloc((void**)&cuda_yuv_, rows * cols * 2) != cudaSuccess)
    {
        std::string error = "could not set cuda yuyv memory";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
    if (cudaMalloc((void**)&cuda_rgb_, rows * cols * 3) != cudaSuccess)
    {
        std::string error = "could not set cuda rgb memory";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
#endif

    av_register_all();
    avcodec_register_all();

    codec_ = H26xEncoderCodecFinder<OutType>::FindEncoder();

    /*find the mp2 encoder*/
    if (!codec_)
    {
        std::string error = "failed to init avcodec encoder";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
    codec_context_ = avcodec_alloc_context3(codec_);
    if (!codec_context_)
    {
        std::string error = "failed to alloc avcodec context";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
    pkt_ = av_packet_alloc();
    if (!pkt_)
    {
        std::string error = "failed to alloc avcodec packet";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
    /*put parameters*/

    codec_context_->bit_rate = bitrate ? bitrate : ((cols_ * rows_ < IMAGE_PIXELS_NUM_8MP) ? H26X_BIT_RATE_UNDER_8MP : H26X_BIT_RATE_8MP);
    codec_context_->height = rows_;
    codec_context_->width  = cols_;
    AVRational rate;
    rate.num                     = 1;
    rate.den                     = fps_;
    codec_context_->time_base    = rate;
    codec_context_->gop_size     = 1; /* emit one intra frame every 1 frame(s) */
    codec_context_->max_b_frames = 0;
    codec_context_->pix_fmt      = AV_PIX_FMT_YUV420P;

    AVDictionary* dictParam = 0;
    //! We use fixed bit rates. These settings are complementary to the
    //! compression performance. preset: compression speed, "tune": compression
    //! latency, "profile": compression quality
    (void)av_dict_set(&dictParam, "preset", "medium", 0);
    (void)av_dict_set(&dictParam, "tune", "zerolatency", 0);
    (void)av_dict_set(&dictParam, "profile", "main", 0);
    (void)av_opt_set(codec_context_->priv_data, "tune", "zerolatency", 0);

    codec_context_->thread_count = ENCODE_THREAD_NUM;
    if (codec_->capabilities | AV_CODEC_CAP_FRAME_THREADS)
    {
        codec_context_->thread_type = FF_THREAD_FRAME;
    }
    else if (codec_->capabilities | AV_CODEC_CAP_SLICE_THREADS)
    {
        codec_context_->thread_type = FF_THREAD_SLICE;
    }
    else
    {
        codec_context_->thread_count = 1;
    }

    /*open it*/
    if (avcodec_open2(codec_context_, codec_, NULL) < 0)
    {
        std::string error = "failed to open avcodec context";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
    av_frame_ = av_frame_alloc();
    if (!av_frame_)
    {
        std::string error = "failed to allocate video frame";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }

    av_frame_->format = codec_context_->pix_fmt;
    av_frame_->width  = codec_context_->width;
    av_frame_->height = codec_context_->height;
    /* allocate new buffer(s) for audio or video data */
    if (av_frame_get_buffer(av_frame_, 0) < 0)
    {
        std::string error = "failed to get frame buffer";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
    LOG(INFO) << "h26x encoder initialized: " << cols_ << ", " << rows_ << ", " << static_cast<uint32_t>(fps_);
}

template <>
bool_t ImageEncoder<holo::Image::Encoding::RGB, ImageType::H264>::Image2Ffmpeg(const Image& image)
{
    const uint8_t* rgb_data = image.GetData();
#if defined(HOLO_CAMERA_USE_CUDA)
    CudaRGBToYUV(cols_, rows_, cuda_rgb_, cuda_yuv_, rgb_data, av_frame_->data[0], av_frame_->data[1],
                 av_frame_->data[2]);
#else
    Rgb2Nv12(rgb_data, cols_, rows_, av_frame_->data[0], av_frame_->data[1], av_frame_->data[2]);
#endif
    av_frame_->pts = pts_counter_++;
    return 0;
}

template <>
bool_t ImageEncoder<holo::Image::Encoding::RGB, ImageType::H265>::Image2Ffmpeg(const Image& image)
{
    const uint8_t* rgb_data = image.GetData();
#if defined(HOLO_CAMERA_USE_CUDA)
    CudaRGBToYUV(cols_, rows_, cuda_rgb_, cuda_yuv_, rgb_data, av_frame_->data[0], av_frame_->data[1],
                 av_frame_->data[2]);
#else
    Rgb2Nv12(rgb_data, cols_, rows_, av_frame_->data[0], av_frame_->data[1], av_frame_->data[2]);
#endif
    av_frame_->pts = pts_counter_++;
    return 0;
}

template <>
bool_t ImageEncoder<holo::Image::Encoding::NV12, ImageType::H264>::Image2Ffmpeg(const Image& image)
{
    const uint8_t* ydata = image.GetData();
    uint32_t       ysize = cols_ * rows_;
    (void)std::memcpy(av_frame_->data[0], ydata, ysize);
    const uint8_t* uvdata = ydata + ysize;
    uint32_t       uvsize = cols_ * rows_ / 4;
    for (uint32_t i = 0; i < uvsize; i++)
    {
        av_frame_->data[1][i] = uvdata[i * 2];
        av_frame_->data[2][i] = uvdata[i * 2 + 1];
    }
    av_frame_->pts = pts_counter_++;
    return 0;
}

template <>
bool_t ImageEncoder<holo::Image::Encoding::NV12, ImageType::H265>::Image2Ffmpeg(const Image& image)
{
    const uint8_t* ydata = image.GetData();
    uint32_t       ysize = cols_ * rows_;
    (void)std::memcpy(av_frame_->data[0], ydata, ysize);
    const uint8_t* uvdata = ydata + ysize;
    uint32_t       uvsize = cols_ * rows_ / 4;
    for (uint32_t i = 0; i < uvsize; i++)
    {
        av_frame_->data[1][i] = uvdata[i * 2];
        av_frame_->data[2][i] = uvdata[i * 2 + 1];
    }
    av_frame_->pts = pts_counter_++;
    return 0;
}

template <holo::Image::Encoding InType, ImageType OutType>
bool_t ImageEncoder<InType, OutType>::FfmpegEncode(AVFrame* frame)
{
    int32_t ret;
    /* send the frame to the encoder */
    ret = avcodec_send_frame(codec_context_, frame);
    if (ret < 0)
    {
        timestamp_queue_.pop();
        LOG(ERROR) << "error sending a frame for encoding";
        return false;
    }

    while (ret >= 0)
    {
        ret = avcodec_receive_packet(codec_context_, pkt_);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        {
            return true;
        }
        else if (ret < 0)
        {
            LOG(ERROR) << "failed to read date from encoder, error code:" << ret;
            return false;
        }

        int is_key_frame = (1 == frame->key_frame) || (AV_PICTURE_TYPE_I == frame->pict_type);
        if (is_key_frame)
        {
            encoded_data_.frame_type = (uint8_t)FrameType::I;
        }
        else
        {
            encoded_data_.frame_type = (uint8_t)FrameType::P;
        }

        encoded_data_.image_type     = OutType;
        encoded_data_.cols           = cols_;
        encoded_data_.rows           = rows_;
        encoded_data_.seq            = counter_++;
        encoded_data_.received_stamp = timestamp_queue_.front().second;
        encoded_data_.trigger_stamp  = timestamp_queue_.front().first;
        encoded_data_.size           = pkt_->size;
        encoded_data_.data           = pkt_->data;
        timestamp_queue_.pop();

        if (ImageEncoderBase::single_data_sender_)
        {
            ImageEncoderBase::single_data_sender_(encoded_data_);
        }

        av_packet_unref(pkt_);
    }
    return true;
}

template <holo::Image::Encoding InType, ImageType OutType>
bool_t ImageEncoder<InType, OutType>::Encode(const Image& image)
{
    if (av_frame_make_writable(av_frame_) < 0)
    {
        LOG(INFO) << "the frame data is un writable ";
        return false;
    }

    Image2Ffmpeg(image);

    TimestampPair timestamp_pair(image.GetTriggerStamp(), image.GetReceivedStamp());
    timestamp_queue_.push(timestamp_pair);

    return FfmpegEncode(av_frame_);
}

template <holo::Image::Encoding InType, ImageType OutType>
ImageEncoder<InType, OutType>::~ImageEncoder() noexcept
{
    /* flush the encoder */
    FfmpegEncode(NULL);
    avcodec_free_context(&codec_context_);
    av_frame_free(&av_frame_);
    av_packet_free(&pkt_);

#if defined(HOLO_CAMERA_USE_CUDA)
    if (cuda_rgb_)
    {
        cudaFree(cuda_rgb_);
    }
    if (cuda_yuv_)
    {
        cudaFree(cuda_yuv_);
    }
#endif
}

template class ImageEncoder<holo::Image::Encoding::RGB, ImageType::H264>;
template class ImageEncoder<holo::Image::Encoding::RGB, ImageType::H265>;
template class ImageEncoder<holo::Image::Encoding::NV12, ImageType::H264>;
template class ImageEncoder<holo::Image::Encoding::NV12, ImageType::H265>;

#if defined(HOLO_PLATFORM_TDA4)

// std::mutex Tda4VxContext::mutex_;
// int32_t    Tda4VxContext::refnum_;
// vx_context Tda4VxContext::context_;

// Tda4VxContext::Tda4VxContext()
// {
//     std::lock_guard<std::mutex> guard(mutex_);
//     if (refnum_ == 0)
//     {
//         if (appCommonInit() != 0)
//         {
//             std::string info = "tda4 vx context: app common init failed";
//             LOG(ERROR) << info;
//             throw std::runtime_error(info);
//         }
//         tivxInit();
//         tivxHostInit();
//         context_ = vxCreateContext();
//         tivxHwaLoadKernels(context_);
//         refnum_++;
//         return;
//     }
//     if (refnum_ >= 4)
//     {
//         std::string info = "tda4 vx context: refnum = " + std::to_string(refnum_);
//         LOG(ERROR) << info;
//         throw std::runtime_error(info);
//     }
//     refnum_++;
// }

// vx_context Tda4VxContext::GetContext() const noexcept
// {
//     return context_;
// }

// Tda4VxContext::~Tda4VxContext()
// {
//     std::lock_guard<std::mutex> guard(mutex_);
//     if (--refnum_ == 0)
//     {
//         tivxHwaUnLoadKernels(context_);
//         vxReleaseContext(&context_);
//         context_ = nullptr;
//         tivxHostDeInit();
//         tivxDeInit();
//         appCommonDeInit();
//     }
// }

Tda4ImageEncoder::Tda4ImageEncoder(uint32_t cols, uint32_t rows, uint32_t fps)
  : ImageEncoderBase(cols, rows, fps, ImageType::H264)
  , Tda4EncodeVxContext(1)
  , counter_(0)
  , iperiod_(DEFAULT_IPERIOD)
  , bitrate_(DEFAULT_BITRATE)
{
    app_encode_init(&enc_, Tda4EncodeVxContext::GetContext(), cols, rows, fps, iperiod_, bitrate_);
}

bool_t Tda4ImageEncoder::Encode(const Image& image)
{
    const uint32_t size = cols_ * rows_;
    (void)std::memcpy(enc_.encodeObj.data_ptr_y, image.GetData(), size);
    (void)std::memcpy(enc_.encodeObj.data_ptr_uv, image.GetData() + size, size / 2);
    if (VX_SUCCESS != app_encode_run(&enc_))
    {
        return false;
    }
    encoded_data_.image_type     = ImageType::H264;
    encoded_data_.cols           = cols_;
    encoded_data_.rows           = rows_;
    encoded_data_.seq            = counter_++;
    encoded_data_.received_stamp = image.GetReceivedStamp();
    encoded_data_.trigger_stamp  = image.GetTimestamp();
    encoded_data_.size           = enc_.encodeObj.bitstream_size;
    encoded_data_.data           = enc_.encodeObj.bitstream;

    if (ImageEncoderBase::single_data_sender_)
    {
        ImageEncoderBase::single_data_sender_(encoded_data_);
    }
    return true;
}

Tda4ImageEncoder::~Tda4ImageEncoder()
{
    app_encode_deinit(&enc_);
}
#endif

}  // namespace camera
}  // namespace sensors
}  // namespace holo
