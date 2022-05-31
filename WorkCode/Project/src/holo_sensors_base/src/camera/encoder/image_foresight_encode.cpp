/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_foresight_encode.cpp
 * @brief Image Foresight Encode
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-11
 */

#include <holo/sensors/camera/encoder/image_foresight_encode.h>

namespace holo
{
namespace sensors
{
namespace camera
{
ImageForesightEncode::ImageForesightEncode(uint32_t fps, uint32_t bitrate)
  : ImageEncoderBase(SRC_WIDTH, SRC_HEIGHT, fps, holo::sensors::camera::ImageType::H264)
  , Tda4EncodeVxContext(1)
  , counter_(0)
  , output_{new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>()}
{
    object_.encodeObject.node_dst_width  = DST_WIDTH;
    object_.encodeObject.node_dst_height = DST_HEIGHT;
    object_.encodeObject.node_src_width  = SRC_WIDTH;
    object_.encodeObject.node_src_height = SRC_HEIGHT;
    object_.encodeObject.bitrate         = bitrate;
    object_.encodeObject.fps             = fps;

    resize_encode_app_init(&object_, Tda4EncodeVxContext::GetContext());
}

ImageForesightEncode::~ImageForesightEncode()
{
    resize_encode_app_deinit(&object_);
}

bool_t ImageForesightEncode::Encode(const std::list<holo::Image> image_list)
{
    object_.encodeObject.node_src_data_ptr = const_cast<uint8_t*>(image_list.front().GetData());
    if (VX_SUCCESS != resize_encode_app_run(&object_))
    {
        LOG(ERROR) << "TDA4 ImageForesightEncode encode failed !";
        return false;
    }

    ImagePacket packet;
    packet.image_type     = ImageType::H264;
    packet.cols           = DST_WIDTH;
    packet.rows           = DST_HEIGHT;
    packet.seq            = counter_++;
    packet.received_stamp = image_list.front().GetReceivedStamp();
    packet.trigger_stamp  = image_list.front().GetTimestamp();
    packet.size           = object_.encodeObject.node_bitstream_size;
    packet.data           = object_.encodeObject.node_bitstream;

    holo::serialization::Serializer<false, 4> serializer(output_.get(), IMAGE_ENCODE_SIZE_MAX);
    if (packet.Serialize(serializer))
    {
        if (ImageEncoderBase::mutil_data_sender_ != nullptr)
        {
            ImageEncoderBase::mutil_data_sender_(serializer.GetData(), serializer.GetSize());
        }
    }

    return true;
}
}  // namespace camera
}  // namespace sensors
}  // namespace holo