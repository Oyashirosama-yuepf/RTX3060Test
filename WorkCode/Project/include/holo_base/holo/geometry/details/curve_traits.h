/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file curve_traits.h
 * @brief This header file defines Curve type traits.
 * @author ZhangJiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-18
 */

#ifndef HOLO_GEOMETRY_DETAILS_CURVE_TRAITS_H_
#define HOLO_GEOMETRY_DETAILS_CURVE_TRAITS_H_

namespace holo
{
namespace geometry
{
/**
 * @brief Tag indicate the curve is a parametric form curve.
 */
struct CurveParametricTag
{
};

/**
 * @brief Tag indicate the curve is a explicit form curve.
 */
struct CurveExplicitTag
{
};

template <typename Curve>
struct CurveTraits
{
    using PointType  = typename Curve::PointType;
    using ScalarType = typename Curve::ScalarType;
    using TagType    = typename Curve::TagType;

    static size_t const SIZE_VALUE = Curve::SIZE_VALUE;
};

}  // namespace geometry
}  // namespace holo
#endif
