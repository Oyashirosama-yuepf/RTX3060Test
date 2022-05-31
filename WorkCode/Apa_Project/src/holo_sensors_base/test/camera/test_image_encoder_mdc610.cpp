#include <cstdio>
#include <memory>
#if defined(HOLO_PLATFORM_MDC610)
#include <core/core.h>
#include <core/logger.h>
#endif
#include <gtest/gtest.h>
#include <holo/sensors/camera/encoder/image_encoder_mdc610.h>

using namespace holo::sensors::camera;

FILE* src_image;
FILE* dst_image;

void save_dst_image(const ImagePacket& packet)
{
    static int i = 0;
    dst_image = fopen((std::string("./h265/") + std::to_string(++i) + ".h265").c_str(), "wb");
    fwrite(packet.data, packet.size, 1, dst_image);
    // dst_image = fopen("dst.h265", "a+");
    // fwrite(packet.data, 1, packet.size, dst_image);
    fclose(dst_image);
}

std::function<void(const ImagePacket&)> callback = save_dst_image;

TEST(ImageEncoder, Constructor)
{
#if defined(HOLO_PLATFORM_MDC610)
#if (MDC610_VERSION_NUM == 20210430)
    Adsfi::AdsfiLogger::GetInstance().InitLogging(std::string("test_image_encoder_"), std::string("test"), 4, 6, std::string("./log/holo_sensors/"));
    Adsfi::AdsfiLogger::GetInstance().CreateLogger(std::string("test_image_encoder_"),std::string("test"), 4);
#else
    Adsfi::AdsfiLogger::GetInstance().InitLogging(std::string("test_image_encoder_"), std::string("test"), static_cast<Adsfi::HafLogLevelType>(4), static_cast<Adsfi::HafLogModeType>(6), std::string("./log/holo_sensors/"));
    Adsfi::AdsfiLogger::GetInstance().CreateLogger(std::string("test_image_encoder_"),std::string("test"), static_cast<Adsfi::HafLogLevelType>(4));
#endif
#endif

    ImageEncoderDvpp<holo::Image::Encoding::NV12> encoder(1920, 1080, 25);

    for(int i = 1; i <= 110; ++i)
    {
        src_image = fopen(std::to_string(i).c_str(), "rb");
        holo::Image image(1920, 1080, holo::Image::Encoding::NV12);
        fread(image.GetData(), 1920 * 1080 * 3 / 2, 1, src_image);
        encoder.SetSender(callback);
        encoder.Encode(image);
        fclose(src_image);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}