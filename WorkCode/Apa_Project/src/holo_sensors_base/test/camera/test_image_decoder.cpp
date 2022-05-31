#include <gtest/gtest.h>
#include <holo/sensors/camera/decoder/image_decoder.h>
#include <unistd.h>
#include <iostream>
#include <chrono>

using namespace holo::sensors::camera;

static constexpr int      MIN_SIZE              = 1;
static constexpr int      MAX_SIZE              = 1198;
static constexpr uint32_t IMAGE_WIDTH  = 3840;
static constexpr uint32_t IMAGE_HEIGHT = 2160;
static constexpr uint32_t FPS          = 30;
static constexpr uint32_t IMAGE_ENCODE_SIZE_MAX = IMAGE_WIDTH * IMAGE_HEIGHT * 2 + 256;
static constexpr uint32_t IMAGE_RAW_SIZE_MAX    = IMAGE_WIDTH * IMAGE_HEIGHT * 2 + 256;

unsigned long getFileSize(const char* file_name)
{
    struct stat buffer;
    if (stat(file_name, &buffer) < 0)
    {
        return 0;
    }

    return (unsigned long)buffer.st_size;
}

void imageDataHandler(const holo::Image& img)
{
    cv::Mat image;
    cv::cvtColor(img.GetCvType(), image, CV_YUV2BGR_NV12);
    std::string name = "";
    name += std::to_string(img.GetTimestamp().ToSec());
    name += ".jpg";
    cv::imwrite(name.c_str(), image);
}

std::function<void(const holo::Image&)> handler = std::bind(&imageDataHandler, std::placeholders::_1);

TEST(ImageDecoder, Constructor)
{
    ImagePacket              compress_data;
    std::shared_ptr<uint8_t> decode_buffer(new uint8_t[IMAGE_WIDTH * IMAGE_HEIGHT * 2 + 256](), std::default_delete<uint8_t[]>());
    compress_data.data = decode_buffer.get();
    std::shared_ptr<holo::sensors::camera::H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>> image_decoder;
    image_decoder = std::make_shared<holo::sensors::camera::H26xDecoder<ImageType::H265, holo::Image::Encoding::NV12>>(
        51381647, IMAGE_WIDTH, IMAGE_HEIGHT, FPS, false);
    image_decoder->SetImageCallback(handler);

    for (int i = MIN_SIZE; i <= MAX_SIZE; ++i)
    {
        std::shared_ptr<uint8_t> data(new uint8_t[IMAGE_WIDTH * IMAGE_HEIGHT * 2 + 256](), std::default_delete<uint8_t[]>());
        FILE*         file      = fopen((std::to_string(i) + std::string(".h264_packet")).c_str(), "rb");
        unsigned long file_size = getFileSize((std::to_string(i) + std::string(".h264_packet")).c_str());
        fread(data.get(), file_size, 1, file);

        size_t                              capacity    = file_size;
        size_t                              buffer_size = file_size;
        holo::serialization::Deserializer<false, 4> deserializer(const_cast<uint8_t*>(data.get()), buffer_size);
        if (compress_data.Deserialize(deserializer))
        {
            LOG(INFO) << "count :" << i << "[trigger_stamp:" << compress_data.trigger_stamp.ToString()
                      << "|receive_stamp:" << compress_data.received_stamp.ToString() << "]";
            LOG(INFO) << "current frame type: " << compress_data.frame_type;
            std::chrono::high_resolution_clock::time_point decode_frame_start =  std::chrono::high_resolution_clock::now();
            image_decoder->Decode(compress_data);
            std::chrono::high_resolution_clock::time_point decode_frame_end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<int, std::ratio<1, 1000000000>> decode_frame_time = decode_frame_end - decode_frame_start;
            LOG(INFO) << "it takes" << decode_frame_time.count() << "nanoseconds to decode a frame of image";
        }
        fclose(file);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}