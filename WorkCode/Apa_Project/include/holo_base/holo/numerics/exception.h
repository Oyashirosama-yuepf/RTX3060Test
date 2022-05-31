/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file exception.h
 * @brief This header file defines exceptions about numerics module
 * @author ZhangJiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-18
 */

#ifndef HOLO_NUMERICS_EXCEPTION_H_
#define HOLO_NUMERICS_EXCEPTION_H_

#include <exception>

namespace holo
{
namespace exception
{
/**
 * @brief Thrown when a spline contains incorrect knot number.
 */
class BadKnotNumberException : public std::exception
{
};

/**
 * @brief Thrown when knots of a spline are in incorrect order.
 */
class BadKnotOrderException : public std::exception
{
};

/**
 * @brief Thrown when a spline contains incorrect control point number.
 */
class BadControlPointNumberException : public std::exception
{
};

}  // namespace exception
}  // namespace holo

#endif
