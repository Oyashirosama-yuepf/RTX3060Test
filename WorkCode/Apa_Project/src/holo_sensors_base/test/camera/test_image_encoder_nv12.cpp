#include <gtest/gtest.h>
#include<holo/os/time.h>
#include <holo/sensors/camera/encoder/image_encoder_h26x.h>

using namespace holo;
using namespace holo::sensors::camera;

static void Callback0(const ImagePacket& packet, bool& called)
{
    (void)packet;
    called = true;
}

TEST(ImageEncoder, Constructor)
{
    bool              called = false;
    Nv12ToH264Encoder encoder(1280, 1440, 10);
    encoder.SetSender(std::bind(&Callback0, std::placeholders::_1, std::ref(called)));
    holo::Image in0(1280, 1440, holo::Image::Encoding::NV12);
    encoder.Encode(in0);
    ASSERT_EQ(called, true);
    for (size_t i = 0; i < 10000; ++i)
    {
        holo::os::Sleep(0.1);
        called = false;
        encoder.Encode(in0);
        ASSERT_EQ(called, true);
    }
    // called = false;
    // holo::Image in1(1280, 720, holo::Image::Encoding::NV12);
    // encoder.Encode(in1);
    // ASSERT_EQ(called, true);
    std::cout << "1" << std::endl;

    bool called2 = false;
    Nv12ToH264Encoder encoder2(1280, 720, 10);
    encoder2.SetSender(std::bind(&Callback0, std::placeholders::_1, std::ref(called2)));
    holo::Image in2(1280, 720, holo::Image::Encoding::NV12);
    encoder2.Encode(in2);
    ASSERT_EQ(called2, true);

    std::cout << "2" << std::endl;

    bool called3 = false;
    Nv12ToH264Encoder encoder3(1280, 720, 10);
    encoder3.SetSender(std::bind(&Callback0, std::placeholders::_1, std::ref(called3)));
    holo::Image in3(1280, 720, holo::Image::Encoding::NV12);
    encoder3.Encode(in3);
    ASSERT_EQ(called3, true);

    std::cout << "3" << std::endl;

    bool called4 = false;
    Nv12ToH264Encoder encoder4(1280, 720, 10);
    encoder4.SetSender(std::bind(&Callback0, std::placeholders::_1, std::ref(called4)));
    holo::Image in4(1280, 720, holo::Image::Encoding::NV12);
    encoder4.Encode(in4);
    ASSERT_EQ(called4, true);

    std::cout << "4" << std::endl;

    // bool called4 = false;
    // Nv12ToH264Encoder encoder4(1280, 720, 10);
    // encoder4.SetSender(std::bind(&Callback0, std::placeholders::_1, std::ref(called4)));
    // holo::Image in4(1280, 720, holo::Image::Encoding::NV12);
    // encoder4.Encode(in4);
    // ASSERT_EQ(called4, true);

    // EXPECT_ANY_THROW(Nv12ToH264Encoder encoder5(1280, 720, 10));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
