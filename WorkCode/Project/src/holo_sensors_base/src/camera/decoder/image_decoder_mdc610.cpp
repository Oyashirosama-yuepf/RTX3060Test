/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_decoder_mdc610.cpp
 * @brief Image decoder lib on mdc610
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-08-20
 */

#include <holo/sensors/camera/decoder/image_decoder_mdc610.h>

namespace holo
{
namespace sensors
{
namespace camera
{
ImageDecoderDvpp::ImageDecoderDvpp(const uint16_t cols, const uint16_t rows)
{
    if ((cols < MIN_IMAGE_WIDTH) || (cols > MAX_IMAGE_WIDTH) || (rows < MIN_IMAGE_HIGHT) || (rows > MAX_IMAGE_HIGHT))
    {
        std::ostringstream oss;
        oss << "wrong width and height set";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    struct Adsfi::HafContextParameters haf_context_parameters;
    haf_context_parameters.deviceId = 0;
    if (Adsfi::HAF_ERROR == HafInitialize(haf_context_, haf_context_parameters))
    {
        std::string error = "failed to init mpi";
        LOG(INFO) << error << ": " << strerror(errno);
        throw std::runtime_error(error);
    }

    decoder_ = std::make_shared<Adsfi::HafVdec>(cols, rows);

    for (current_channel_id_ = MIN_VDEC_CHANNEL_ID; current_channel_id_ <= MAX_VDEC_CHANNEL_ID; ++current_channel_id_)
    {
        Adsfi::HafStatus status = decoder_->Init(REF_FRAME_NUM, DISPLAY_FRAME_NUM, current_channel_id_);
        if (status != Adsfi::HafStatus::HAF_SUCCESS)
        {
            continue;
        }
        break;
    }

    if ((MAX_VDEC_CHANNEL_ID + 1) == current_channel_id_)
    {
        std::string error = "failed to init mdc610 dvpp decoder";
        LOG(INFO) << errno;
        throw std::runtime_error(error);
    }

    LOG(INFO) << "current chanel id: " << current_channel_id_;
}

ImageDecoderDvpp::~ImageDecoderDvpp()
{
    vdec_stream_.streamAddr = nullptr;
    vdec_frame_.frameAddr   = nullptr;
    (void)HafRelease(haf_context_);
}

bool_t ImageDecoderDvpp::DecodeH265Data(const ImagePacket& image_packet, uint8_t** data)
{
    (void)std::memset(&vdec_stream_, 0x00, sizeof(vdec_stream_));
    vdec_stream_.isEndOfStream = false;
    if (image_packet.size <= decoder_->GetBufferSize())
    {
        vdec_stream_.streamLen = image_packet.size;
    }
    else
    {
        LOG(ERROR) << "error too long data for decoder decode";

        return false;
    }
#if (MDC610_VERSION_NUM == 20210430)
    vdec_stream_.timeStamp =
        ((static_cast<uint64_t>(image_packet.received_stamp.GetSec()) << 32) + image_packet.received_stamp.GetNsec()) /
        1000;
#else
    vdec_stream_.timestamp =
        ((static_cast<uint64_t>(image_packet.received_stamp.GetSec()) << 32) + image_packet.received_stamp.GetNsec()) /
        1000;
#endif
    vdec_stream_.milliSec     = 0;
    vdec_stream_.streamAddr   = image_packet.data;
    Adsfi::HafStatus send_ret = decoder_->SendStream(vdec_stream_);
    if (Adsfi::HAF_ERROR == send_ret)
    {
        LOG(ERROR) << "Error sending a vdec_stream for decoding";

        return false;
    }

    (void)std::memset(&vdec_frame_, 0x00, sizeof(vdec_frame_));
    vdec_frame_.milliSec      = 0;
    vdec_frame_.frameAddr     = nullptr;
    Adsfi::HafStatus recv_ret = decoder_->GetFrame(vdec_frame_);
    if (Adsfi::HAF_ERROR == recv_ret)
    {
        LOG(ERROR) << "Error receiving a vdec_frame for decoding";
    }

    if (vdec_frame_.decFlag)
    {
        LOG(ERROR) << "An invalid frame was received";
    }

    *data                 = vdec_frame_.frameAddr;
    vdec_frame_.frameAddr = nullptr;
    return true;
}
}  // namespace camera
}  // namespace sensors
}  // namespace holo