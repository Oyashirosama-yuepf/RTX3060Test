/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mask.cpp
 * @brief mask implementation
 * @author duyanwei@holomatic.com
 * @date 2019-11-29
 */

#include <holo/localization/vision/common/mask.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mask::Mask() : Base()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mask::Mask(const uint16_t width, const uint16_t height, const uint8_t value) : Base()
{
    mat_.create(static_cast<int32_t>(height), static_cast<int32_t>(width), CV_8UC1);
    (void)mat_.setTo(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mask::Mask(const Mat& mat) : Base(mat)
{
    if (mat_.type() != CV_8UC1)
    {
        throw std::runtime_error("mask initialized from mat only supports element type of uint8_t");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mask::Mask(const Mask& other) : Base(other)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mask& Mask::operator=(const Mask& other)
{
    mat_ = other.mat_;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mask::operator=(const uint8_t value) noexcept
{
    Base::operator=(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mask::~Mask()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t Mask::At(const uint16_t row, const uint16_t col) const
{
    return *(mat_.ptr(row, col));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t& Mask::At(const uint16_t row, const uint16_t col)
{
    return *(mat_.ptr(row, col));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mask::SetTo(const uint8_t value) noexcept
{
    (void)mat_.setTo(value);
}

}  // namespace localization
}  // namespace holo
