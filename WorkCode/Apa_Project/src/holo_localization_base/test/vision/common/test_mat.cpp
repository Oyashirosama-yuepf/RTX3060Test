/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_mat.cpp
 * @brief mat unit test
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/common/mat.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mat, DefaultConstructorAndDestructor)
{
    const holo::localization::Mat* mat = new holo::localization::Mat();

    // check result
    ASSERT_TRUE(mat->IsEmpty());
    ASSERT_EQ(0u, mat->GetWidth());
    ASSERT_EQ(0u, mat->GetHeight());
    delete mat;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mat, ConstructFromGrayscaleImage)
{
    // construct image
    holo::Image image;
    {
        // prepare data
        const holo::Image::Encoding encoding    = holo::Image::Encoding::GRAYSCALE;
        const holo::uint16_t        width       = 320u;
        const holo::uint16_t        height      = 240u;
        const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height;
        holo::uint8_t               buffer[buffer_size];
        image.ConfigImage(width, height, encoding);
        image.UpdateData(buffer, buffer_size);
    }

    // construct mat
    const holo::localization::Mat mat(image);

    // check result
    ASSERT_FALSE(mat.IsEmpty());
    ASSERT_EQ(320u, mat.GetWidth());
    ASSERT_EQ(240u, mat.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mat, ConstructFromRgbImage)
{
    // construct image
    holo::Image image;
    {
        // prepare data
        const holo::Image::Encoding encoding    = holo::Image::Encoding::RGB;
        const holo::uint16_t        width       = 320u;
        const holo::uint16_t        height      = 240u;
        const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height * 3u;
        holo::uint8_t               buffer[buffer_size];
        image.ConfigImage(width, height, encoding);
        image.UpdateData(buffer, buffer_size);
    }

    // construct mat
    const holo::localization::Mat mat(image);

    // check result
    ASSERT_FALSE(mat.IsEmpty());
    ASSERT_EQ(320u, mat.GetWidth());
    ASSERT_EQ(240u, mat.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mat, CopyConstructor)
{
    // construct image
    holo::Image image;
    {
        // prepare data
        const holo::Image::Encoding encoding    = holo::Image::Encoding::GRAYSCALE;
        const holo::uint16_t        width       = 320u;
        const holo::uint16_t        height      = 240u;
        const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height;
        holo::uint8_t               buffer[buffer_size];

        // set image data
        image.ConfigImage(width, height, encoding);
        image.UpdateData(buffer, buffer_size);
    }

    // construct mat
    const holo::localization::Mat mat(image);

    // call method
    const holo::localization::Mat other(mat);

    // check result
    ASSERT_FALSE(mat.IsEmpty());
    ASSERT_EQ(320u, mat.GetWidth());
    ASSERT_EQ(240u, mat.GetHeight());
    ASSERT_FALSE(other.IsEmpty());
    ASSERT_EQ(320u, other.GetWidth());
    ASSERT_EQ(240u, other.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mat, AssignmentOperator)
{
    // construct image
    holo::Image image;
    {
        // prepare data
        const holo::Image::Encoding encoding    = holo::Image::Encoding::GRAYSCALE;
        const holo::uint16_t        width       = 320u;
        const holo::uint16_t        height      = 240u;
        const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height;
        holo::uint8_t               buffer[buffer_size];

        // set image data
        image.ConfigImage(width, height, encoding);
        image.UpdateData(buffer, buffer_size);
    }

    // construct mat
    const holo::localization::Mat mat(image);

    // call method
    holo::localization::Mat other;
    other = mat;

    // check result
    ASSERT_FALSE(mat.IsEmpty());
    ASSERT_EQ(320u, mat.GetWidth());
    ASSERT_EQ(240u, mat.GetHeight());
    ASSERT_FALSE(other.IsEmpty());
    ASSERT_EQ(320u, other.GetWidth());
    ASSERT_EQ(240u, other.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, AssignmentOperator2)
{
    // construct image
    holo::Image image;
    {
        // prepare data
        const holo::Image::Encoding encoding    = holo::Image::Encoding::GRAYSCALE;
        const holo::uint16_t        width       = 2u;
        const holo::uint16_t        height      = 4u;
        const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height;
        holo::uint8_t               buffer[buffer_size];

        // set image data
        image.ConfigImage(width, height, encoding);
        image.UpdateData(buffer, buffer_size);
    }

    // construct mat
    holo::localization::Mat mat(image);

    // call method
    const uint8_t value = 100u;
    mat                 = value;

    ASSERT_FALSE(mat.IsEmpty());
    ASSERT_EQ(2u, mat.GetWidth());
    ASSERT_EQ(4u, mat.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, AssignmentOperator2Invalid)
{
    // construct image
    holo::Image image;
    {
        // prepare data
        const holo::Image::Encoding encoding    = holo::Image::Encoding::RGB;
        const holo::uint16_t        width       = 320u;
        const holo::uint16_t        height      = 240u;
        const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height * 3u;
        holo::uint8_t               buffer[buffer_size];
        image.ConfigImage(width, height, encoding);
        image.UpdateData(buffer, buffer_size);
    }

    // construct mat
    holo::localization::Mat mat(image);

    // check result
    ASSERT_THROW(mat = 100u, std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mat, RangeROI)
{
    // construct image
    holo::Image image;
    {
        // prepare data
        const holo::Image::Encoding encoding    = holo::Image::Encoding::GRAYSCALE;
        const holo::uint16_t        width       = 320u;
        const holo::uint16_t        height      = 240u;
        const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height;
        holo::uint8_t               buffer[buffer_size];

        // set image data
        image.ConfigImage(width, height, encoding);
        image.UpdateData(buffer, buffer_size);
    }

    // construct mat
    const holo::localization::Mat mat(image);

    // construct range
    const holo::localization::RangeInt row_range(100, 150);
    const holo::localization::RangeInt col_range(50, 200);

    // call method
    const holo::localization::Mat roi = mat(row_range, col_range);

    // check result
    ASSERT_FALSE(mat.IsEmpty());
    ASSERT_EQ(320u, mat.GetWidth());
    ASSERT_EQ(240u, mat.GetHeight());
    ASSERT_FALSE(roi.IsEmpty());
    ASSERT_EQ(150u, roi.GetWidth());
    ASSERT_EQ(50u, roi.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mat, RectROI)
{
    // construct image
    holo::Image image;
    {
        // prepare data
        const holo::Image::Encoding encoding    = holo::Image::Encoding::GRAYSCALE;
        const holo::uint16_t        width       = 320u;
        const holo::uint16_t        height      = 240u;
        const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height;
        holo::uint8_t               buffer[buffer_size];

        // set image data
        image.ConfigImage(width, height, encoding);
        image.UpdateData(buffer, buffer_size);
    }

    // construct mat
    const holo::localization::Mat mat(image);

    // construct rect
    const holo::localization::Rect2i rect(10, 20, 100, 150);

    // call method
    const holo::localization::Mat roi = mat(rect);

    // check result
    ASSERT_FALSE(mat.IsEmpty());
    ASSERT_EQ(320u, mat.GetWidth());
    ASSERT_EQ(240u, mat.GetHeight());
    ASSERT_FALSE(roi.IsEmpty());
    ASSERT_EQ(100u, roi.GetWidth());
    ASSERT_EQ(150u, roi.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mat, CopyTo)
{
    // construct image
    holo::Image image;
    {
        // prepare data
        const holo::Image::Encoding encoding    = holo::Image::Encoding::GRAYSCALE;
        const holo::uint16_t        width       = 320u;
        const holo::uint16_t        height      = 240u;
        const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height;
        holo::uint8_t               buffer[buffer_size];

        // set image data
        image.ConfigImage(width, height, encoding);
        image.UpdateData(buffer, buffer_size);
    }

    // construct mat
    const holo::localization::Mat mat(image);

    // call method
    holo::localization::Mat other;
    mat.CopyTo(other);

    // check result
    ASSERT_FALSE(mat.IsEmpty());
    ASSERT_EQ(320u, mat.GetWidth());
    ASSERT_EQ(240u, mat.GetHeight());
    ASSERT_FALSE(other.IsEmpty());
    ASSERT_EQ(320u, other.GetWidth());
    ASSERT_EQ(240u, other.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mat, Clone)
{
    // construct image
    holo::Image image;
    {
        // prepare data
        const holo::Image::Encoding encoding    = holo::Image::Encoding::GRAYSCALE;
        const holo::uint16_t        width       = 320u;
        const holo::uint16_t        height      = 240u;
        const holo::uint64_t        buffer_size = static_cast<uint64_t>(width) * height;
        holo::uint8_t               buffer[buffer_size];

        // set image data
        image.ConfigImage(width, height, encoding);
        image.UpdateData(buffer, buffer_size);
    }

    // construct mat
    const holo::localization::Mat mat(image);

    // call method
    holo::localization::Mat other = mat.Clone();

    // check result
    ASSERT_FALSE(mat.IsEmpty());
    ASSERT_EQ(320u, mat.GetWidth());
    ASSERT_EQ(240u, mat.GetHeight());
    ASSERT_FALSE(other.IsEmpty());
    ASSERT_EQ(320u, other.GetWidth());
    ASSERT_EQ(240u, other.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
