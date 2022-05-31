/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_panoramic_encode.cpp
 * @brief Image Panoramic Encode
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-11
 */

#include <holo/sensors/camera/encoder/image_panoramic_encode.h>

namespace holo
{
namespace sensors
{
namespace camera
{
ImagePanoramicEncode::ImagePanoramicEncode(uint32_t fps, uint32_t bitrate)
  : ImageEncoderBase(SRC_WIDTH, SRC_HEIGHT, fps, holo::sensors::camera::ImageType::H264)
  , Tda4EncodeVxContext(2)
  , counter_(0)
  , output0_{new uint8_t[IMAGE_ENCODE_SIZE_MAX * 2](), std::default_delete<uint8_t[]>()}
  , output1_(nullptr)
{
    object_.encodeObject.node0_src_width  = SRC_WIDTH;
    object_.encodeObject.node0_src_height = SRC_HEIGHT;
    object_.encodeObject.node1_src_width  = SRC_WIDTH;
    object_.encodeObject.node1_src_height = SRC_HEIGHT;
    object_.encodeObject.bitrate          = bitrate;
    object_.encodeObject.fps              = fps;

    sync_encode_app_init(&object_, Tda4EncodeVxContext::GetContext());
}

ImagePanoramicEncode::~ImagePanoramicEncode()
{
    sync_encode_app_deinit(&object_);
}

bool_t ImagePanoramicEncode::Encode(const std::list<holo::Image> image_list)
{
    object_.encodeObject.node00_src_data_ptr = const_cast<uint8_t*>(image_list.begin()->GetData());
    object_.encodeObject.node01_src_data_ptr = const_cast<uint8_t*>((++image_list.begin())->GetData());
    object_.encodeObject.node10_src_data_ptr = const_cast<uint8_t*>((--(--image_list.end()))->GetData());
    object_.encodeObject.node11_src_data_ptr = const_cast<uint8_t*>((--image_list.end())->GetData());

    if (VX_SUCCESS != sync_encode_app_run(&object_))
    {
        LOG(ERROR) << "TDA4 ImagePanoramicEncode encode failed !";
        return false;
    }

    ImagePacket packet0;
    packet0.image_type     = ImageType::H264;
    packet0.cols           = SRC_WIDTH;
    packet0.rows           = SRC_HEIGHT;
    packet0.seq            = counter_++;
    packet0.received_stamp = image_list.begin()->GetReceivedStamp();
    packet0.trigger_stamp  = image_list.begin()->GetTimestamp();
    packet0.size           = object_.encodeObject.node0_bitstream_size;
    packet0.data           = object_.encodeObject.node0_bitstream;

    ImagePacket packet1;
    packet1.image_type     = ImageType::H264;
    packet1.cols           = SRC_WIDTH;
    packet1.rows           = SRC_HEIGHT;
    packet1.seq            = counter_++;
    packet1.received_stamp = image_list.begin()->GetReceivedStamp();
    packet1.trigger_stamp  = image_list.begin()->GetTimestamp();
    packet1.size           = object_.encodeObject.node1_bitstream_size;
    packet1.data           = object_.encodeObject.node1_bitstream;

    if (nullptr == output0_)
    {
        LOG(INFO) << "output is nullptr";
        return false;
    }
    holo::serialization::Serializer<false, 4> serializer0(output0_.get(), IMAGE_ENCODE_SIZE_MAX);
    holo::bool_t                              packet0_serialze_result = packet0.Serialize(serializer0);
    output1_                                                          = output0_.get() + serializer0.GetSize();
    holo::serialization::Serializer<false, 4> serializer1(output1_, IMAGE_ENCODE_SIZE_MAX);
    holo::bool_t                              packet1_serialze_result = packet1.Serialize(serializer1);
    if (packet0_serialze_result && packet1_serialze_result)
    {
        if (ImageEncoderBase::mutil_data_sender_ != nullptr)
        {
            ImageEncoderBase::mutil_data_sender_(serializer0.GetData(), serializer0.GetSize() + serializer1.GetSize());
        }
    }

    return true;
}
}  // namespace camera
}  // namespace sensors
}  // namespace holo