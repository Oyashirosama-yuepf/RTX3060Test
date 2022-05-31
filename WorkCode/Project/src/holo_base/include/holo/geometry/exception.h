/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file exception.h
 * @brief This header file defines exceptions related to geometry module.
 * @author ZhangJiannan(zhangjiannan@holomatic.com)
 * @date 2020-05-22
 */

#ifndef HOLO_GEOMETRY_EXCEPTION_H_
#define HOLO_GEOMETRY_EXCEPTION_H_

#include <holo/core/exception.h>

namespace holo
{
namespace exception
{
class BadCurveStateException : public std::exception
{
};
}  // namespace exception
}  // namespace holo

#endif
