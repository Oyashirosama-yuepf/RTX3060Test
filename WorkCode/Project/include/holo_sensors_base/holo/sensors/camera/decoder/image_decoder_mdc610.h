/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_decoder_mdc610.h
 * @brief Image decoder lib on mdc610
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-08-20
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_DECODER_MDC610_H
#define _HOLO_SENSORS_CAMERA_IMAGE_DECODER_MDC610_H

#include <core/core.h>
#include <core/logger.h>
#include <holo/sensors/camera/image_structure.h>
#include <video/haf_vdec.h>
#include <csignal>
#include <memory>

namespace holo
{
namespace sensors
{
namespace camera
{
class ImageDecoderDvpp
{
public:
    ImageDecoderDvpp(const uint16_t cols, const uint16_t rows);
    virtual ~ImageDecoderDvpp();
    void   DestroyMdcDecoderChannel(int sig);
    bool_t DecodeH265Data(const ImagePacket& image_packet, uint8_t** data);

protected:
    static constexpr int32_t MIN_VDEC_CHANNEL_ID = 25;
    static constexpr int32_t MAX_VDEC_CHANNEL_ID = 46;
    static constexpr int32_t MIN_IMAGE_WIDTH     = 128;
    static constexpr int32_t MAX_IMAGE_WIDTH     = 4096;
    static constexpr int32_t MIN_IMAGE_HIGHT     = 128;
    static constexpr int32_t MAX_IMAGE_HIGHT     = 4096;
    static constexpr int32_t MIN_I_FRAME_SIZE    = 50000;
    static constexpr int32_t REF_FRAME_NUM       = 5;
    static constexpr int32_t DISPLAY_FRAME_NUM   = 3;

private:
    std::shared_ptr<Adsfi::HafVdec> decoder_;
    Adsfi::VdecStream               vdec_stream_;
    Adsfi::VdecFrame                vdec_frame_;
    int32_t                         current_channel_id_;
    struct Adsfi::HafContext        haf_context_;
};
}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_IMAGE_DECODER_MDC610_H