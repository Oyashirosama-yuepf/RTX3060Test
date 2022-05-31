/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_mask.cpp
 * @brief mask unit test
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#include <gtest/gtest.h>

#include <holo/localization/vision/common/mask.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, DefaultConstructorAndDestructor)
{
    const holo::localization::Mask* mask = new holo::localization::Mask();

    // check result
    ASSERT_TRUE(mask->IsEmpty());
    ASSERT_EQ(0u, mask->GetWidth());
    ASSERT_EQ(0u, mask->GetHeight());
    delete mask;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, ConstructFromWidthAndHeight)
{
    // construct mask
    const uint16_t width  = 20u;
    const uint16_t height = 40u;

    const holo::localization::Mask mask(width, height);

    // check result
    ASSERT_FALSE(mask.IsEmpty());
    ASSERT_EQ(width, mask.GetWidth());
    ASSERT_EQ(height, mask.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, ConstructFromMat)
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
    holo::localization::Mat mat(image);

    // construct mask
    const holo::localization::Mask mask(mat);

    // check results
    ASSERT_EQ(320u, mask.GetWidth());
    ASSERT_EQ(240u, mask.GetHeight());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, ConstructFromMatInvalid)
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

    // construct mask and check result
    ASSERT_THROW(const holo::localization::Mask mask(mat), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, CopyConstructor)
{
    // construct mask
    const uint16_t width  = 2u;
    const uint16_t height = 4u;
    const uint8_t  value  = 100u;

    const holo::localization::Mask mask(width, height, value);

    // check result
    const holo::localization::Mask other(mask);

    ASSERT_FALSE(mask.IsEmpty());
    ASSERT_EQ(width, mask.GetWidth());
    ASSERT_EQ(height, mask.GetHeight());
    ASSERT_FALSE(other.IsEmpty());
    ASSERT_EQ(width, other.GetWidth());
    ASSERT_EQ(height, other.GetHeight());
    for (uint16_t i = 0u; i < height; i++)
    {
        for (uint16_t j = 0u; j < width; j++)
        {
            ASSERT_EQ(value, mask.At(i, j));
            ASSERT_EQ(value, other.At(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, AssignmentOperator)
{
    // construct mask
    const uint16_t width  = 20u;
    const uint16_t height = 40u;
    const uint8_t  value  = 100u;

    const holo::localization::Mask mask(width, height, value);

    // check result
    holo::localization::Mask other;
    other = mask;

    ASSERT_FALSE(mask.IsEmpty());
    ASSERT_EQ(width, mask.GetWidth());
    ASSERT_EQ(height, mask.GetHeight());
    ASSERT_FALSE(other.IsEmpty());
    ASSERT_EQ(width, other.GetWidth());
    ASSERT_EQ(height, other.GetHeight());
    for (uint16_t i = 0u; i < height; i++)
    {
        for (uint16_t j = 0u; j < width; j++)
        {
            ASSERT_EQ(value, mask.At(i, j));
            ASSERT_EQ(value, other.At(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, AssignmentOperator2)
{
    // construct mask
    const uint16_t width  = 20u;
    const uint16_t height = 40u;
    const uint8_t  value  = 100u;

    holo::localization::Mask mask(width, height, value);

    // check result
    const uint8_t new_value = 100u;
    mask                    = new_value;

    for (uint16_t i = 0u; i < height; i++)
    {
        for (uint16_t j = 0u; j < width; j++)
        {
            ASSERT_EQ(new_value, mask.At(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, RangeROI)
{
    // construct mask
    const uint16_t width  = 20u;
    const uint16_t height = 40u;
    const uint8_t  value  = 100u;

    const holo::localization::Mask mask(width, height, value);

    // construct range
    const holo::localization::RangeInt row_range(25, 30);
    const holo::localization::RangeInt col_range(10, 15);

    // call method
    const uint8_t new_value    = 200u;
    mask(row_range, col_range) = new_value;

    // check result
    for (uint16_t i = 0u; i < height; i++)
    {
        for (uint16_t j = 0u; j < width; j++)
        {
            uint8_t expected = value;
            if ((i < row_range.GetEnd() && i >= row_range.GetStart()) &&
                (j < col_range.GetEnd() && j >= col_range.GetStart()))
            {
                expected = new_value;
            }
            ASSERT_EQ(expected, mask.At(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, RectROI)
{
    // construct mask
    const uint16_t width  = 20u;
    const uint16_t height = 40u;
    const uint8_t  value  = 100u;

    const holo::localization::Mask mask(width, height, value);

    // construct range
    const holo::localization::Rect2i rect(10u, 20u, 5u, 10u);

    // call method
    const uint8_t new_value = 200u;
    mask(rect)              = new_value;

    // check result
    for (uint16_t i = 0u; i < height; i++)
    {
        for (uint16_t j = 0u; j < width; j++)
        {
            uint8_t expected = value;
            if ((i < rect.GetBottomRightY() && i >= rect.GetTopLeftY()) &&
                (j < rect.GetBottomRightX() && j >= rect.GetTopLeftX()))
            {
                expected = new_value;
            }
            ASSERT_EQ(expected, mask.At(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, At)
{
    // construct mask
    const uint16_t width  = 2u;
    const uint16_t height = 4u;
    const uint8_t  value  = 100u;

    holo::localization::Mask mask(width, height, value);

    // check getter
    for (uint16_t i = 0u; i < height; i++)
    {
        for (uint16_t j = 0u; j < width; j++)
        {
            ASSERT_EQ(value, mask.At(i, j));
        }
    }

    // check setter
    for (uint16_t i = 0u; i < height; i++)
    {
        for (uint16_t j = 0u; j < width; j++)
        {
            // set to new value
            mask.At(i, j) = 200u;
            ASSERT_EQ(200u, mask.At(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Mask, SetTo)
{
    // construct mask
    const uint16_t width  = 20u;
    const uint16_t height = 40u;
    const uint8_t  value  = 100u;

    holo::localization::Mask mask(width, height, value);

    // call method
    const uint8_t new_value = 200u;
    mask.SetTo(new_value);

    for (uint16_t i = 0u; i < height; i++)
    {
        for (uint16_t j = 0u; j < width; j++)
        {
            ASSERT_EQ(new_value, mask.At(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
