/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_encoder_gpu.cpp.
 * @brief Image Encoder.
 * @author lanpade(yangpeiwen@holomatic.com).
 * @date 2020-07-31.
 */
#include <holo/sensors/camera/encoder/image_encoder_xavier.h>

namespace holo
{
namespace sensors
{
namespace camera
{
const int32_t                      ImageXavierEncoder::START_SKIPPED_FRAMES = 10;
int32_t                            ImageXavierEncoder::frame_index_ = 0;
ImageXavierEncoder::TimeStampsList ImageXavierEncoder::time_stamp_queue_;
CompressDataSender                 ImageXavierEncoder::encoded_sender_ = nullptr;
ImagePacket                        ImageXavierEncoder::encoded_data_;
NvVideoEncoder*                    ImageXavierEncoder::enc_ = NULL;

ImageXavierEncoder::ImageXavierEncoder(uint32_t cols, uint32_t rows, uint32_t fps) : ImageEncoderBase(cols, rows, fps, ImageType::H264)
{
    if (cudaMalloc((void**)&cuda_yuv_, rows_ * cols_ * 1.5) != cudaSuccess)
    {
        std::string error = "could not set cuda yuv memory";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
    if (cudaMalloc((void**)&cuda_rgb_, rows_ * cols_ * 3) != cudaSuccess)
    {
        std::string error = "could not set cuda rgb memory";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
    yuv_image_data_          = (uint8_t*)malloc(cols_ * rows_ * 2);
    encoded_data_.cols       = cols;
    encoded_data_.rows       = rows;
    encoded_data_.image_type = ImageType::H264;
    if (!InitEncoder())
    {
        std::string error = "failed to init h264 encoder ";
        LOG(ERROR) << error;
        throw std::runtime_error(error);
    }
}

ImageXavierEncoder::~ImageXavierEncoder()
{
    free(yuv_image_data_);
}

void ImageXavierEncoder::SetSender(const CompressDataSender& handler) noexcept
{
    encoded_sender_ = handler;
}

bool_t ImageXavierEncoder::InitEncoder()
{
    eglDisplay_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglDisplay_ != EGL_NO_DISPLAY)
    {
        if (!eglInitialize(eglDisplay_, NULL, NULL))
        {
            LOG(ERROR) << "init EGL display failed";
            return false;
        }
    }
    else
    {
        LOG(WARNING) << "Could not get EGL display connection";
    }

    enc_ = NvVideoEncoder::createVideoEncoder("enc0");
    if (!enc_)
    {
        LOG(ERROR) << "Could not create encoder ";
        return false;
    }

    int32_t ret = 0;

    ret = enc_->setCapturePlaneFormat(V4L2_PIX_FMT_H264, cols_, rows_, 2 * 1024 * 1024);

    if (ret < 0)
    {
        LOG(ERROR) << "Could not set capture plane format";
        return false;
    }

    ret = enc_->setOutputPlaneFormat(V4L2_PIX_FMT_YUV420M, cols_, rows_);

    if (ret < 0)
    {
        LOG(ERROR) << "Could not set output plane format";
        return false;
    }

    ret = enc_->setBitrate(4 * 1024 * 1024);

    if (ret < 0)
    {
        LOG(ERROR) << "Could not set bitrate";
        return false;
    }

    ret = enc_->setProfile(V4L2_MPEG_VIDEO_H264_PROFILE_HIGH);

    if (ret < 0)
    {
        LOG(ERROR) << "Could not set profile";
        return false;
    }

    ret = enc_->setLevel(V4L2_MPEG_VIDEO_H264_LEVEL_5_0);
    if (ret < 0)
    {
        LOG(ERROR) << "Could bnot set encoder level";
        return false;
    }

    ret = enc_->setFrameRate(1, fps_);
    if (ret < 0)
    {
        LOG(ERROR) << "Could bnot set encoder level";
        return false;
    }

    ret = enc_->setIDRInterval(10);
    if (ret < 0)
    {
        LOG(ERROR) << "Could not set i frame ";
        return false;
    }

    ret = enc_->setInsertSpsPpsAtIdrEnabled(true);
    if (ret < 0)
    {
        LOG(ERROR) << "Could not set pps";
        return false;
    }

    ret = enc_->output_plane.setupPlane(V4L2_MEMORY_MMAP, 10, true, false);
    if (ret < 0)
    {
        LOG(ERROR) << "Could bnot set encoder level";
        return false;
    }

    ret = enc_->capture_plane.setupPlane(V4L2_MEMORY_MMAP, 10, true, false);
    if (ret < 0)
    {
        LOG(ERROR) << "Could bnot set encoder level";
        return false;
    }

    ret = enc_->output_plane.setStreamStatus(true);
    if (ret < 0)
    {
        LOG(ERROR) << "Could bnot set encoder level";
        return false;
    }

    ret = enc_->capture_plane.setStreamStatus(true);
    if (ret < 0)
    {
        LOG(ERROR) << "Could bnot set encoder level";
        return false;
    }

    enc_->capture_plane.setDQThreadCallback(&DqCallback);
    enc_->capture_plane.startDQThread(enc_);
    for (uint32_t i = 0; i < enc_->capture_plane.getNumBuffers(); i++)
    {
        struct v4l2_buffer v4l2_buf;
        struct v4l2_plane  planes[MAX_PLANES];

        (void)std::memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        (void)std::memset(planes, 0, MAX_PLANES * sizeof(struct v4l2_plane));

        v4l2_buf.index    = i;
        v4l2_buf.m.planes = planes;

        ret = enc_->capture_plane.qBuffer(v4l2_buf, NULL);
        if (ret < 0)
        {
            LOG(ERROR) << "Error while queueing buffer at capture plane";
            return false;
        }
    }

    LOG(INFO) << "xavier encoder init successfully";
    return true;
}

bool_t ImageXavierEncoder::Encode(const Image& rgb_image)
{
    CudaRGBToYUV(cols_, rows_, cuda_rgb_, cuda_yuv_, rgb_image.GetData(), yuv_image_data_);
    if (frame_index_ == 0)
    {
        for (uint32_t i = 0; i < enc_->output_plane.getNumBuffers(); i++)
        {
            struct v4l2_buffer v4l2_buf;
            struct v4l2_plane  planes[MAX_PLANES];
            NvBuffer*          buffer = enc_->output_plane.getNthBuffer(i);
            (void)std::memset(&v4l2_buf, 0, sizeof(v4l2_buf));
            (void)std::memset(planes, 0, MAX_PLANES * sizeof(struct v4l2_plane));
            v4l2_buf.index      = i;
            v4l2_buf.m.planes   = planes;
            size_t   yuv_offset = 0;
            uint32_t j;
            char*    data;
            for (uint32_t m = 0; m < buffer->n_planes; m++)
            {
                NvBuffer::NvBufferPlane& plane         = buffer->planes[m];
                uint32_t                 bytes_to_read = plane.fmt.bytesperpixel * plane.fmt.width;
                data                                   = (char*)plane.data;
                plane.bytesused                        = 0;
                for (j = 0; j < plane.fmt.height; j++)
                {
                    memcpy(data, yuv_image_data_ + yuv_offset, bytes_to_read);
                    data += plane.fmt.stride;
                    yuv_offset += bytes_to_read;
                }
                plane.bytesused = plane.fmt.stride * plane.fmt.height;
            }
            int32_t ret = enc_->output_plane.qBuffer(v4l2_buf, NULL);
            if (ret < 0)
            {
                LOG(ERROR) << "Error while queueing buffer at output plane " << i;
                return false;
            }
            if (v4l2_buf.m.planes[0].bytesused == 0)
            {
                LOG(INFO) << "done frame";
                break;
            }
        }
    }
    else
    {
        if (frame_index_ >= START_SKIPPED_FRAMES)
        {
            TimestampPair timestamp_pair(rgb_image.GetTriggerStamp(), rgb_image.GetReceivedStamp());
            time_stamp_queue_.push(timestamp_pair);
        }
        struct v4l2_buffer v4l2_buf;
        struct v4l2_plane  planes[MAX_PLANES];
        NvBuffer*          buffer;
        (void)std::memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        (void)std::memset(planes, 0, sizeof(planes));
        v4l2_buf.m.planes = planes;
        if (enc_->output_plane.dqBuffer(v4l2_buf, &buffer, NULL, 10) < 0)
        {
            LOG(ERROR) << "ERROR while DQing buffer at output plane";
            return false;
        }
        size_t   yuv_offset = 0;
        uint32_t j;
        char*    data;
        for (uint32_t i = 0; i < buffer->n_planes; i++)
        {
            NvBuffer::NvBufferPlane& plane         = buffer->planes[i];
            uint32_t                 bytes_to_read = plane.fmt.bytesperpixel * plane.fmt.width;
            data                                   = (char*)plane.data;
            plane.bytesused                        = 0;
            for (j = 0; j < plane.fmt.height; j++)
            {
                memcpy(data, yuv_image_data_ + yuv_offset, bytes_to_read);
                data += plane.fmt.stride;
                yuv_offset += bytes_to_read;
            }
            plane.bytesused = plane.fmt.stride * plane.fmt.height;
        }

        int32_t ret = enc_->output_plane.qBuffer(v4l2_buf, NULL);
        if (ret < 0)
        {
            LOG(ERROR) << "Error while queueing buffer at output plane";
            return false;
        }
    }
    return true;
}

bool_t ImageXavierEncoder::DqCallback(struct v4l2_buffer* v4l2_buf, NvBuffer* buffer, NvBuffer* shared_buffer,
                                      void* arg)
{
    NvVideoEncoder* enc = (NvVideoEncoder*)arg;
    (void)enc;
    (void)shared_buffer;

    if (!v4l2_buf)
    {
        LOG(ERROR) << "Failed to dequeue buffer from encoder capture plane";
        return false;
    }

    // drop front 10 frame h264 data
    if (frame_index_ > START_SKIPPED_FRAMES)
    {
        holo::common::Timestamp trigger_stamp, rev_stamp;
        if (time_stamp_queue_.size() > 0)
        {
            trigger_stamp = time_stamp_queue_.front().first;
            rev_stamp     = time_stamp_queue_.front().second;
            time_stamp_queue_.pop();
        }
        if (encoded_sender_)
        {
            encoded_data_.seq            = frame_index_;
            encoded_data_.received_stamp = rev_stamp;
            encoded_data_.trigger_stamp  = trigger_stamp;
            encoded_data_.size           = buffer->planes[0].bytesused;
            encoded_data_.data           = buffer->planes[0].data + buffer->planes[0].mem_offset;
            encoded_data_.frame_type     = (uint8_t)FrameType::UNKNOWN;
            encoded_sender_(encoded_data_);
        }
    }
    frame_index_++;
    if (enc_->capture_plane.qBuffer(*v4l2_buf, NULL) < 0)
    {
        LOG(ERROR) << "Error while Qing buffer at capture plane";
        return false;
    }
    // GOT EOS from encoder. Stop dqthread.
    if (buffer->planes[0].bytesused == 0)
    {
        return false;
    }
    return true;
}

}  // namespace camera
}  // namespace sensors
}  // namespace holo
