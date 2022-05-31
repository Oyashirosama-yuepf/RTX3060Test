/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_panoramic_decode.h
 * @brief Image Panoramic Decode
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-11
 */

#include <holo/sensors/camera/decoder/image_panoramic_decode.h>

namespace holo
{
namespace sensors
{
namespace camera
{
ImagePanoramicDecode::ImagePanoramicDecode()
  : ImageDecoderBase()
  , Tda4DecodeVxContext(2)
  , decode_buffer_(new uint8_t[IMAGE_ENCODE_SIZE_MAX](), std::default_delete<uint8_t[]>())
  , skip_this_frame_(true)
  , finish_flag_(false)
{
    memset(decode_buffer_.get(), 0, IMAGE_ENCODE_SIZE_MAX);
    compress_data_.data = decode_buffer_.get();

    object_.decodeObject.node0_dst_width  = DST_WIDTH;
    object_.decodeObject.node0_dst_height = DST_HEIGHT;
    object_.decodeObject.node1_dst_width  = DST_WIDTH;
    object_.decodeObject.node1_dst_height = DST_HEIGHT;

    sync_decode_app_init(&object_, Tda4DecodeVxContext::GetContext());
}

ImagePanoramicDecode::~ImagePanoramicDecode()
{
    sync_decode_app_deinit(&object_);
}

bool_t ImagePanoramicDecode::Decode(const uint8_t* data, const size_t size)
{
    holo::serialization::Deserializer<false, 4> deserializer(const_cast<uint8_t*>(data), size);
    std::shared_ptr<uint8_t>                    compress_data_cache(new uint8_t[IMAGE_ENCODE_SIZE_MAX](),
                                                 std::default_delete<uint8_t[]>());

    finish_flag_ = false;
    while (compress_data_.Deserialize(deserializer))
    {
        LOG(INFO) << "deserializer";
        // LOG(INFO) << "packet.image_type     = " << compress_data.image_type;
        // LOG(INFO) << "packet.cols           = " << compress_data.cols;
        // LOG(INFO) << "packet.rows           = " << compress_data.rows;
        // LOG(INFO) << "packet.seq            = " << compress_data.seq;
        // LOG(INFO) << "packet.received_stamp = " << compress_data.received_stamp.ToString();
        // LOG(INFO) << "packet.trigger_stamp  = " << compress_data.trigger_stamp.ToString();
        // LOG(INFO) << "packet.size           = " << compress_data.size;
        // LOG(INFO) << "packet.data           = " << compress_data.data;

        if (finish_flag_)
        {
            the_last_image1_.SetReceivedStamp(compress_data_.received_stamp);
            the_last_image1_.SetTriggerStamp(compress_data_.trigger_stamp);

            object_.decodeObject.node1_bitstream_size = compress_data_.size;
            object_.decodeObject.node1_bitstream      = compress_data_.data;

            holo::Image image0(OUT_WIDTH, OUT_HEIGHT, holo::Image::Encoding::NV12);
            holo::Image image1(OUT_WIDTH, OUT_HEIGHT, holo::Image::Encoding::NV12);
            holo::Image image2(OUT_WIDTH, OUT_HEIGHT, holo::Image::Encoding::NV12);
            holo::Image image3(OUT_WIDTH, OUT_HEIGHT, holo::Image::Encoding::NV12);

            object_.decodeObject.node00_dst_data_ptr = image0.GetData();
            object_.decodeObject.node01_dst_data_ptr = image1.GetData();
            object_.decodeObject.node10_dst_data_ptr = image2.GetData();
            object_.decodeObject.node11_dst_data_ptr = image3.GetData();
            sync_decode_app_run(&object_);

            if (skip_this_frame_)
            {
                skip_this_frame_ = false;
                finish_flag_     = false;
                continue;
            }

            image0.SetReceivedStamp(the_last_image0_.GetReceivedStamp());
            image0.SetTriggerStamp(the_last_image0_.GetTriggerStamp());
            image1.SetReceivedStamp(the_last_image0_.GetReceivedStamp());
            image1.SetTriggerStamp(the_last_image0_.GetTriggerStamp());

            image2.SetReceivedStamp(the_last_image1_.GetReceivedStamp());
            image2.SetTriggerStamp(the_last_image1_.GetTriggerStamp());
            image3.SetReceivedStamp(the_last_image1_.GetReceivedStamp());
            image3.SetTriggerStamp(the_last_image1_.GetTriggerStamp());

            image_list_.push_back(image0);
            image_list_.push_back(image1);
            image_list_.push_back(image2);
            image_list_.push_back(image3);

            if (ImageDecoderBase::image_list_callback_)
            {
                ImageDecoderBase::image_list_callback_(image_list_);
            }

            finish_flag_ = false;
        }
        else
        {
            the_last_image0_.SetReceivedStamp(compress_data_.received_stamp);
            the_last_image0_.SetTriggerStamp(compress_data_.trigger_stamp);

            image_list_.clear();

            memset(compress_data_cache.get(), 0x00, IMAGE_ENCODE_SIZE_MAX);
            memcpy(compress_data_cache.get(), compress_data_.data, compress_data_.size);

            object_.decodeObject.node0_bitstream_size = compress_data_.size;
            object_.decodeObject.node0_bitstream      = compress_data_cache.get();

            finish_flag_ = true;
        }
    }

    return true;
}

ImageType ImagePanoramicDecode::GetImageType() const noexcept
{
    return ImageType::H264;
}

holo::Image::Encoding ImagePanoramicDecode::GetEncoding() const noexcept
{
    return holo::Image::Encoding::NV12;
}


}  // namespace camera
}  // namespace sensors
}  // namespace holo