/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_image.cpp
 * @brief image unit test
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#include <gtest/gtest.h>

#include <holo/common/image.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Image, Constructor)
{
    const holo::Image image;

    // check result
    ASSERT_EQ(holo::Timestamp(), image.GetTriggerStamp());
    ASSERT_EQ(holo::Timestamp(), image.GetReceivedStamp());
    ASSERT_EQ(holo::Timestamp(), image.GetTimestamp());
    ASSERT_EQ(0u, image.GetWidth());
    ASSERT_EQ(0u, image.GetHeight());
    ASSERT_EQ(holo::Image::Encoding::UNKNOWN, image.GetEncoding());

    const holo::Image new_image(320u, 240u, holo::Image::Encoding::YUYV);

    ASSERT_EQ(holo::Timestamp(), new_image.GetTriggerStamp());
    ASSERT_EQ(holo::Timestamp(), new_image.GetReceivedStamp());
    ASSERT_EQ(320u, new_image.GetWidth());
    ASSERT_EQ(240u, new_image.GetHeight());
    ASSERT_EQ(holo::Image::Encoding::YUYV, new_image.GetEncoding());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Image, ConstructorWithExternalBuffer)
{
    const uint32_t              width       = 100u;
    const uint32_t              height      = 200u;
    const holo::Image::Encoding encoding    = holo::Image::Encoding::RGB;
    const uint32_t              buffer_size = width * height * 3u;
    uint8_t                     buffer[buffer_size];

    // construct image with external buffer
    const holo::Image image0(width, height, encoding, buffer, buffer_size);

    // construct image without external buffer
    const holo::Image image1(width, height, encoding);

    // check result
    ASSERT_EQ(holo::Timestamp(), image0.GetTriggerStamp());
    ASSERT_EQ(holo::Timestamp(), image0.GetReceivedStamp());
    ASSERT_EQ(holo::Timestamp(), image0.GetTimestamp());
    ASSERT_EQ(width, image0.GetWidth());
    ASSERT_EQ(height, image0.GetHeight());
    ASSERT_EQ(holo::Image::Encoding::RGB, image0.GetEncoding());
    ASSERT_EQ(buffer, image0.GetData());

    ASSERT_EQ(holo::Timestamp(), image1.GetTriggerStamp());
    ASSERT_EQ(holo::Timestamp(), image1.GetReceivedStamp());
    ASSERT_EQ(holo::Timestamp(), image1.GetTimestamp());
    ASSERT_EQ(width, image1.GetWidth());
    ASSERT_EQ(height, image1.GetHeight());
    ASSERT_EQ(holo::Image::Encoding::RGB, image1.GetEncoding());
    ASSERT_NE(buffer, image1.GetData());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Image, ConstructorWithExternalBuffer_InvalidSize)
{
    const uint32_t              width       = 100u;
    const uint32_t              height      = 200u;
    const holo::Image::Encoding encoding    = holo::Image::Encoding::RGB;
    const uint32_t              buffer_size = width * height * 1u;
    uint8_t                     buffer[buffer_size];

    // construct image with external buffer
    ASSERT_THROW(holo::Image(width, height, encoding, buffer, buffer_size), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Image, Update)
{
    holo::Image image;

    // prepare data
    const holo::Image::Encoding encoding    = holo::Image::Encoding::RGB;
    const holo::uint16_t        width       = 320u;
    const holo::uint16_t        height      = 240u;
    const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height * 3u;
    holo::uint8_t               buffer[buffer_size];

    image.ConfigImage(width, height, encoding);

    image.UpdateData(buffer, buffer_size);

    ASSERT_EQ(320u, image.GetWidth());
    ASSERT_EQ(240u, image.GetHeight());
    ASSERT_EQ(holo::Image::Encoding::RGB, image.GetEncoding());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Image, Timestamp)
{
    holo::Image image;

    // set timestamp
    image.SetTriggerStamp(holo::Timestamp(100.0));
    image.SetReceivedStamp(holo::Timestamp(200.0));

    // check result
    ASSERT_EQ(holo::Timestamp(100.0), image.GetTriggerStamp());
    ASSERT_EQ(holo::Timestamp(200.0), image.GetReceivedStamp());
    ASSERT_EQ(holo::Timestamp(100.0), image.GetTimestamp());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Image, Grayscale)
{
    holo::Image image;

    // prepare data
    const holo::Image::Encoding encoding    = holo::Image::Encoding::GRAYSCALE;
    const holo::uint16_t        width       = 320u;
    const holo::uint16_t        height      = 240u;
    const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height;
    holo::uint8_t               buffer[buffer_size];

    // set image data
    image.SetData(buffer, buffer_size, width, height, encoding);

    // check result
    ASSERT_EQ(encoding, image.GetEncoding());
    ASSERT_EQ(width, image.GetWidth());
    ASSERT_EQ(height, image.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Image, RGB)
{
    holo::Image image;

    // prepare data
    const holo::Image::Encoding encoding    = holo::Image::Encoding::RGB;
    const holo::uint16_t        width       = 320u;
    const holo::uint16_t        height      = 240u;
    const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height * 3u;
    holo::uint8_t               buffer[buffer_size];

    // set image data
    image.SetData(buffer, buffer_size, width, height, encoding);

    // check result
    ASSERT_EQ(encoding, image.GetEncoding());
    ASSERT_EQ(width, image.GetWidth());
    ASSERT_EQ(height, image.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Image, YUYV)
{
    holo::Image image;

    // prepare data
    const holo::Image::Encoding encoding    = holo::Image::Encoding::YUYV;
    const holo::uint16_t        width       = 320u;
    const holo::uint16_t        height      = 240u;
    const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height * 2u;
    holo::uint8_t               buffer[buffer_size];

    // set image data
    image.SetData(buffer, buffer_size, width, height, encoding);

    // check result
    ASSERT_EQ(encoding, image.GetEncoding());
    ASSERT_EQ(width, image.GetWidth());
    ASSERT_EQ(height, image.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Image, InvalidType)
{
    holo::Image image;

    // prepare data
    const holo::Image::Encoding encoding    = holo::Image::Encoding::UNKNOWN;
    const holo::uint16_t        width       = 320u;
    const holo::uint16_t        height      = 240u;
    const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height;
    holo::uint8_t               buffer[buffer_size];

    // set image data
    holo::bool_t is_exception_caught = false;
    try
    {
        image.SetData(buffer, buffer_size, width, height, encoding);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        is_exception_caught = true;
    }

    // check result
    ASSERT_TRUE(is_exception_caught);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Image, InvalidBuffer)
{
    holo::Image image;

    // prepare data
    const holo::Image::Encoding encoding    = holo::Image::Encoding::GRAYSCALE;
    const holo::uint16_t        width       = 320u;
    const holo::uint16_t        height      = 240u;
    const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height * 3u;
    holo::uint8_t               buffer[buffer_size];

    // set image data
    holo::bool_t is_exception_caught = false;
    try
    {
        image.SetData(buffer, buffer_size, width, height, encoding);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        is_exception_caught = true;
    }

    // check result
    ASSERT_TRUE(is_exception_caught);
}

TEST(Image, CopyConstructor)
{
    const holo::Image image(320u, 240u, holo::Image::Encoding::YUYV);
    const holo::Image image2(image);
}

TEST(Image, OperatorEqual)
{
    holo::Image image, image2;
    image2 = image;
}

TEST(Image, Clone)
{
    const holo::Image image(320u, 240u, holo::Image::Encoding::YUYV);
    const holo::Image image2 = image.Clone();
}

TEST(Image, CopyTo)
{
    holo::Image image(320u, 240u, holo::Image::Encoding::YUYV);
    holo::Image image2;
    image.CopyTo(image2);
}

TEST(Image, GetData_const)
{
    const holo::Image image(320u, 240u, holo::Image::Encoding::YUYV);
    auto              value = image.GetData();
}

TEST(Image, GetData)
{
    holo::Image image(320u, 240u, holo::Image::Encoding::YUYV);
    auto        value = image.GetData();
}

TEST(Image, Constructor_2)
{
    const holo::Image image1(320u, 240u, holo::Image::Encoding::RGB);
    const holo::Image image2(320u, 240u, holo::Image::Encoding::GRAYSCALE);
    const holo::Image image4(0u, 1u, holo::Image::Encoding::YU12);
    const holo::Image image5(1u, 0u, holo::Image::Encoding::YU12);
    try
    {
        const holo::Image image6(1u, 1u, holo::Image::Encoding::YU12);
    }
    catch (...)
    {
    }

    try
    {
        const holo::Image image6(1u, 1u, holo::Image::Encoding::UNKNOWN);
    }
    catch (...)
    {
    }
}

TEST(Image, ConfigImage)
{
    holo::Image image;

    image.ConfigImage(320u, 320u, holo::Image::Encoding::RGB);
    image.ConfigImage(320u, 320u, holo::Image::Encoding::GRAYSCALE);
    image.ConfigImage(320u, 320u, holo::Image::Encoding::YUYV);
    image.ConfigImage(0u, 1u, holo::Image::Encoding::YU12);
    image.ConfigImage(1u, 0u, holo::Image::Encoding::YU12);

    {
        uint8_t buffer[10u];
        image.ConfigImage(2u, 5u, holo::Image::Encoding::GRAYSCALE, buffer, 10u);
    }

    try
    {
        image.ConfigImage(1u, 1u, holo::Image::Encoding::YU12);
    }
    catch (...)
    {
    }

    try
    {
        image.ConfigImage(1u, 1u, holo::Image::Encoding::UNKNOWN);
    }
    catch (...)
    {
    }

    try
    {
        uint8_t buffer[1u];
        image.ConfigImage(1u, 10u, holo::Image::Encoding::RGB, buffer, 1u);
    }
    catch (...)
    {
    }
}

TEST(Image, SetData)
{
    holo::Image image;

    // prepare data
    const holo::uint16_t width       = 320u;
    const holo::uint16_t height      = 240u;
    const holo::uint64_t buffer_size = static_cast<uint64_t>(width) * height;
    holo::uint8_t        buffer[buffer_size];
    image.SetData(buffer, 6, 2u, 2u, holo::Image::Encoding::YU12);

    try
    {
        image.SetData(buffer, 9, 3u, 3u, holo::Image::Encoding::NV21);
    }
    catch (...)
    {
    }

    try
    {
        image.SetData(buffer, 9, 2u, 3u, holo::Image::Encoding::YU12);
    }
    catch (...)
    {
    }
}

TEST(Image, Update_2)
{
    holo::Image image;

    // prepare data
    const holo::Image::Encoding encoding    = holo::Image::Encoding::RGB;
    const holo::uint16_t        width       = 320u;
    const holo::uint16_t        height      = 240u;
    const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height * 3u;
    holo::uint8_t               buffer[buffer_size];

    try
    {
        image.UpdateData(buffer, 3);
    }
    catch (...)
    {
    }

    try
    {
        image.ConfigImage(width, height, encoding);
        image.UpdateData(buffer, 3);
    }
    catch (...)
    {
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
