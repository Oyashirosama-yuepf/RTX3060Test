#include <gtest/gtest.h>
#include <holo/sensors/camera/encoder/image_encoder.h>
#include <unistd.h>
#include <iostream>
#include <chrono>

using namespace holo::sensors::camera;

using ImagePacket       = holo::sensors::camera::ImagePacket;
using Image             = holo::Image;
using Nv12ToH265Encoder = holo::sensors::camera::Nv12ToH265Encoder;
using Nv12ToH264Encoder = holo::sensors::camera::Nv12ToH264Encoder;

static constexpr int      MIN_SIZE     = 1;
static constexpr int      MAX_SIZE     = 1198;
static constexpr uint32_t IMAGE_WIDTH  = 3840;
static constexpr uint32_t IMAGE_HEIGHT = 2160;
static constexpr uint32_t FPS          = 30;
static constexpr uint32_t BIT_RETE     = 100000000;

void EncodedDataHandler(ImagePacket const& packet)
{
    FILE* file = fopen("encoded_data.image_packet", "a+");
    fwrite(packet.data, 1, packet.size, file);
    fclose(file);
}

std::function<void(ImagePacket const&)> handler = std::bind(&EncodedDataHandler, std::placeholders::_1);

TEST(ImageEncoder, Constructor)
{
    std::shared_ptr<Nv12ToH265Encoder> image_encoder = std::make_shared<Nv12ToH265Encoder>(IMAGE_WIDTH, IMAGE_HEIGHT, FPS);
    image_encoder->SetSender(handler);
    Image image(IMAGE_WIDTH, IMAGE_HEIGHT, holo::Image::Encoding::NV12);

    for (int i = MIN_SIZE; i <= MAX_SIZE; ++i)
    {
        std::shared_ptr<uint8_t> data(new uint8_t[IMAGE_WIDTH * IMAGE_HEIGHT * 3 / 2](), std::default_delete<uint8_t[]>());
        FILE*                    file      = fopen(std::to_string(i).c_str(), "rb");
        fread(image.GetData(), IMAGE_WIDTH * IMAGE_HEIGHT * 3 / 2, 1, file);

        std::chrono::high_resolution_clock::time_point decode_frame_start =  std::chrono::high_resolution_clock::now();
        image_encoder->Encode(image);
        std::chrono::high_resolution_clock::time_point decode_frame_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<int, std::ratio<1, 1000000000>> decode_frame_time = decode_frame_end - decode_frame_start;
        LOG(INFO) << "it takes" << decode_frame_time.count() << "nanoseconds to encode a frame of image";

        fclose(file);
    }
}   

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}