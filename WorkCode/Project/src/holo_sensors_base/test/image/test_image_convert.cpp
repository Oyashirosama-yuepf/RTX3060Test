#include <cstdio>
#include <iostream>
#include <gtest/gtest.h>
#include <holo/sensors/image/convert/image_color_convert.hpp>

using namespace holo::sensors::image;

static constexpr uint32_t MIN_IMAGE_NUM = 0;
static constexpr uint32_t MAX_IMAGE_NUM = 1200;

TEST(ImageDecoder, Constructor)
{
	FILE* src_image;
	FILE* dst_image;
	holo::Image src_holo_image(1920, 1080, holo::Image::Encoding::NV12);
	holo::Image dst_holo_image(1920, 1080, holo::Image::Encoding::BGR);

	for (int i = MIN_IMAGE_NUM; i <= MAX_IMAGE_NUM; ++i)
	{
		src_image = fopen((std::string("./nv12/") + std::to_string(i)).c_str(), "rb");
		dst_image = fopen((std::string("./bgr24/") + std::to_string(i)).c_str(), "wb");

		fread(src_holo_image.GetData(), 1, 1920 * 1080 * 3 / 2, src_image);
		NV12ToBGR24(src_holo_image, dst_holo_image);
		fwrite(dst_holo_image.GetData(), 1, 1920 * 1080 * 3, dst_image);

		fclose(src_image);
		fclose(dst_image);
	}
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}