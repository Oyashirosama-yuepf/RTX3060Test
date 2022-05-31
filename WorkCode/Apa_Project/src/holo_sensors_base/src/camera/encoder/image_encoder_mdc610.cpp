/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file image_encoder_mdc610.h
 * @brief Image Encoder on mdc610 platform
 * @author guoguangchao(guoguangchao@holomatic.com).
 * @date 2021-06-07
 */
#include <holo/sensors/camera/encoder/image_encoder_mdc610.h>

namespace holo
{
namespace sensors
{
namespace camera
{
template <holo::Image::Encoding InType>
ImageEncoderDvpp<InType>::ImageEncoderDvpp(uint32_t cols, uint32_t rows, uint32_t fps)
  : ImageEncoderBase(cols, rows, fps, ImageType::H265)
  , data_(new uint8_t[1024 * 1024](), std::default_delete<uint8_t[]>())
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

    for (current_channel_id_ = MIN_VDEC_CHANNEL_ID; current_channel_id_ <= MAX_VDEC_CHANNEL_ID; ++current_channel_id_)
    {
        try
        {
            encoder_ = std::make_shared<Adsfi::HafVenc>(cols, rows, current_channel_id_);
            Adsfi::HafStatus status = encoder_->Init();
            if (status != Adsfi::HafStatus::HAF_SUCCESS)
            {
                std::ostringstream oss;
                oss << "current chanel id: " << current_channel_id_ << " is using";
                throw std::invalid_argument(oss.str());
            }
            break;
        }
        catch (const std::exception& e)
        {
            continue;
        }
    }

    if ((MAX_VDEC_CHANNEL_ID + 1) == current_channel_id_)
    {
        std::string error = "failed to init mdc610 dvpp decoder";
        LOG(INFO) << errno;
        throw std::runtime_error(error);
    }

    LOG(INFO) << "current chanel id: " << current_channel_id_;
}

template <holo::Image::Encoding InType>
ImageEncoderDvpp<InType>::~ImageEncoderDvpp()
{
    (void)HafRelease(haf_context_);
}

template <holo::Image::Encoding InType>
bool_t ImageEncoderDvpp<InType>::Encode(const Image& image)
{
    Adsfi::ImageData img;
    img.width      = cols_;
    img.height     = rows_;
    img.dataSize   = static_cast<uint32_t>(cols_ * rows_ * 1.5f);
    img.bufferType = Adsfi::HafBufferType::HAF_BUFFER_CPU;
    img.imageType  = Adsfi::HafImageType::HAF_IMAGE_YUV420SP_NV12_UINT8;
    img.seq        = frame_index_++;
    img.rawData    = const_cast<uint8_t*>(image.GetData());

    // 1.Call the function interface for sending the image to be encoded
    if (Adsfi::HafStatus::HAF_SUCCESS != encoder_->SendFrame(img))
    {
        LOG(ERROR) << "send frame to encoder failed!";
        return false;
    }
#if (MDC610_VERSION_NUM == 20211130)
    // 2.Call the code stream output interface function after encoding in a loop
    hi_venc_stream out;
    if (Adsfi::HafStatus::HAF_SUCCESS != encoder_->GetStream(out))
    {
        LOG(ERROR) << "get stream from encoder failed!";
        return false;
    }

    uint64_t data_length = 0;
    for (uint32_t i = 0; i < out.pack_cnt; i++)
    {
        data_length += out.pack[i].len - out.pack[i].offset;
    }
    /*******Store the coded image stream data of one frame in the array******/

    (void)std::memset(data_.get(), 0, data_length);
    uint8_t* data_move     = data_.get();
    uint64_t packet_length = 0;
    uint8_t* data_addr     = NULL;
    for (uint32_t i = 0; i < out.pack_cnt; i++)
    {
        data_addr     = out.pack[i].addr + out.pack[i].offset;
        packet_length = out.pack[i].len - out.pack[i].offset;
        memcpy(data_move, data_addr, packet_length);
        data_move += packet_length;
    }
    /**************************************************************/
    if (ImageEncoderBase::single_data_sender_)
    {
        if ((hi_venc_h265_nalu_type::HI_VENC_H265_NALU_I_SLICE == out.pack->data_type.h265_type) || 
            (hi_venc_h265_nalu_type::HI_VENC_H265_NALU_IDR_SLICE  == out.pack->data_type.h265_type))
        {
            encoded_data_.frame_type = (uint8_t)FrameType::I;
        }
        else
        {
            encoded_data_.frame_type = (uint8_t)FrameType::P;
        }
        encoded_data_.image_type     = ImageType::H265;
        encoded_data_.cols           = cols_;
        encoded_data_.rows           = rows_;
        encoded_data_.seq            = out.seq;
        encoded_data_.received_stamp = holo::common::Timestamp(uint64_t(out.pack[0].pts) * 1000);
        encoded_data_.trigger_stamp  = holo::common::Timestamp(uint64_t(out.pack[0].pts) * 1000);
        encoded_data_.size           = data_length;
        encoded_data_.data           = data_.get();
        ImageEncoderBase::single_data_sender_(encoded_data_);
    }
#elif (MDC610_VERSION_NUM == 20211231) || (MDC610_VERSION_NUM == 20220228)
    // 2.Call the code stream output interface function after encoding in a loop
    hi_venc_stream out;
    if (Adsfi::HafStatus::HAF_SUCCESS != encoder_->GetStream(out))
    {
        LOG(ERROR) << "get stream from encoder failed!";
        return false;
    }

    uint64_t data_length = 0;
    for (uint32_t i = 0; i < out.pack_cnt; i++)
    {
        data_length += out.pack[i].len - out.pack[i].offset;
    }
    /*******Store the coded image stream data of one frame in the array******/

    (void)std::memset(data_.get(), 0, data_length);
    uint8_t* data_move     = data_.get();
    uint64_t packet_length = 0;
    uint8_t* data_addr     = NULL;
    for (uint32_t i = 0; i < out.pack_cnt; i++)
    {
        data_addr     = out.pack[i].addr + out.pack[i].offset;
        packet_length = out.pack[i].len - out.pack[i].offset;
        memcpy(data_move, data_addr, packet_length);
        data_move += packet_length;
    }
    /**************************************************************/
    if (ImageEncoderBase::single_data_sender_)
    {
        if ((hi_venc_h265_nalu_type::HI_VENC_H265_NALU_I_SLICE == out.pack->data_type.h265_type) || 
            (hi_venc_h265_nalu_type::HI_VENC_H265_NALU_IDR_SLICE  == out.pack->data_type.h265_type))
        {
            encoded_data_.frame_type = (uint8_t)FrameType::I;
        }
        else
        {
            encoded_data_.frame_type = (uint8_t)FrameType::P;
        }
        encoded_data_.image_type     = ImageType::H265;
        encoded_data_.cols           = cols_;
        encoded_data_.rows           = rows_;
        encoded_data_.seq            = out.seq;
        encoded_data_.received_stamp = holo::common::Timestamp(uint64_t(out.pack[0].pts) * 1000);
        encoded_data_.trigger_stamp  = holo::common::Timestamp(uint64_t(out.pack[0].pts) * 1000);
        encoded_data_.size           = data_length;
        encoded_data_.data           = data_.get();
        ImageEncoderBase::single_data_sender_(encoded_data_);
    }
#else
    // 2.Call the code stream output interface function after encoding in a loop
    VENC_STREAM_S out;
    if (Adsfi::HafStatus::HAF_SUCCESS != encoder_->GetStream(out))
    {
        LOG(ERROR) << "get stream from encoder failed!";
        return false;
    }

    uint64_t data_length = 0;
    for (uint32_t i = 0; i < out.u32PackCount; i++)
    {
        data_length += out.pstPack[i].u32Len - out.pstPack[i].u32Offset;
    }
    /*******Store the coded image stream data of one frame in the array******/

    (void)std::memset(data_.get(), 0, data_length);
    uint8_t* data_move     = data_.get();
    uint64_t packet_length = 0;
    uint8_t* data_addr     = NULL;
    for (uint32_t i = 0; i < out.u32PackCount; i++)
    {
        data_addr     = out.pstPack[i].pu8Addr + out.pstPack[i].u32Offset;
        packet_length = out.pstPack[i].u32Len - out.pstPack[i].u32Offset;
        memcpy(data_move, data_addr, packet_length);
        data_move += packet_length;
    }
    /**************************************************************/
    if (ImageEncoderBase::single_data_sender_)
    {
        if ((hiH265E_NALU_TYPE_E::H265E_NALU_ISLICE == out.pstPack->DataType.enH265EType) || 
            (hiH265E_NALU_TYPE_E::H265E_NALU_IDRSLICE  == out.pstPack->DataType.enH265EType))
        {
            encoded_data_.frame_type = (uint8_t)FrameType::I;
        }
        else
        {
            encoded_data_.frame_type = (uint8_t)FrameType::P;
        }
        encoded_data_.image_type     = ImageType::H265;
        encoded_data_.cols           = cols_;
        encoded_data_.rows           = rows_;
        encoded_data_.seq            = out.u32Seq;
        encoded_data_.received_stamp = holo::common::Timestamp(uint64_t(out.pstPack[0].u64PTS) * 1000);
        encoded_data_.trigger_stamp  = holo::common::Timestamp(uint64_t(out.pstPack[0].u64PTS) * 1000);
        encoded_data_.size           = data_length;
        encoded_data_.data           = data_.get();
        ImageEncoderBase::single_data_sender_(encoded_data_);
    }
#endif
    // 3.release the stream
    encoder_->ReleaseStream(out);
    return true;
}
template class ImageEncoderDvpp<holo::Image::Encoding::NV12>;

}  // namespace camera
}  // namespace sensors
}  // namespace holo
