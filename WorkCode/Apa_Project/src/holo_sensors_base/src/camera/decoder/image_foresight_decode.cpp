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

#include <holo/sensors/camera/decoder/image_foresight_decode.h>

namespace holo
{
namespace sensors
{
namespace camera
{
ImageForesightDecode::ImageForesightDecode()
  : ImageDecoderBase()
  , Tda4DecodeVxContext(1)
  , decode_buffer_(new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>())
  , skip_this_frame_(true)
{
    memset(decode_buffer_.get(), 0, IMAGE_ENCODE_SIZE_MAX);
    compress_data_.data = decode_buffer_.get();

    object_.decodeObject.node_dst_width  = DST_WIDTH;
    object_.decodeObject.node_dst_height = DST_HEIGHT;
    object_.decodeObject.node_src_width  = SRC_WIDTH;
    object_.decodeObject.node_src_height = SRC_HEIGHT;

    resize_decode_app_init(&object_, Tda4DecodeVxContext::GetContext());
}

ImageForesightDecode::~ImageForesightDecode()
{
    resize_decode_app_deinit(&object_);
}

bool_t ImageForesightDecode::Decode(const uint8_t* data, const size_t size)
{
    holo::serialization::Deserializer<false, 4> deserializer(const_cast<uint8_t*>(data), size);

    while (compress_data_.Deserialize(deserializer))
    {
        // LOG(INFO) << "packet.image_type     = " << compress_data.image_type;
        // LOG(INFO) << "packet.cols           = " << compress_data.cols;
        // LOG(INFO) << "packet.rows           = " << compress_data.rows;
        // LOG(INFO) << "packet.seq            = " << compress_data.seq;
        // LOG(INFO) << "packet.received_stamp = " << compress_data.received_stamp.ToString();
        // LOG(INFO) << "packet.trigger_stamp  = " << compress_data.trigger_stamp.ToString();
        // LOG(INFO) << "packet.size           = " << compress_data.size;
        // LOG(INFO) << "packet.data           = " << compress_data.data;
        the_last_image_.SetTriggerStamp(compress_data_.trigger_stamp);
        the_last_image_.SetReceivedStamp(compress_data_.received_stamp);

        holo::Image image(1920, 1080, holo::Image::Encoding::NV12);

        object_.decodeObject.node_bitstream_size = compress_data_.size;
        object_.decodeObject.node_bitstream      = compress_data_.data;
        object_.decodeObject.node_dst_data_ptr   = image.GetData();

        resize_decode_app_run(&object_);
        if (skip_this_frame_)
        {
            skip_this_frame_ = false;
            continue;
        }

        image.SetReceivedStamp(the_last_image_.GetReceivedStamp());
        image.SetTriggerStamp(the_last_image_.GetTriggerStamp());

        image_list_.clear();
        image_list_.push_back(image);

        if (ImageDecoderBase::image_list_callback_)
        {
            ImageDecoderBase::image_list_callback_(image_list_);
        }
    }

    return true;
}

ImageType ImageForesightDecode::GetImageType() const noexcept
{
    return ImageType::H264;
}

holo::Image::Encoding ImageForesightDecode::GetEncoding() const noexcept
{
    return holo::Image::Encoding::NV12;
}


}  // namespace camera
}  // namespace sensors
}  // namespace holo