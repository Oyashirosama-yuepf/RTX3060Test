/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_property.h
 * @brief This header file defines obstacle property for fusion.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-06-23"
 */

#ifndef HOLO_PERCEPTION_UTILS_OBSTACLE_PROPERTY_H_
#define HOLO_PERCEPTION_UTILS_OBSTACLE_PROPERTY_H_

#include <holo/common/classification.h>
#include <holo/common/timestamp.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup utils
 *
 * @{
 */

/**
 * @brief obstacle common properties
 *
 * @tparam T scalar type
 */
template <typename T>
class ObstacleProperty
{
public:
    using Scalar         = T;
    using Timestamp      = holo::common::details::Timestamp;
    using Classification = holo::common::Classification;

    ObstacleProperty()
      : x(0.0)
      , y(0.0)
      , z(0.0)
      , vx(0.0)
      , vy(0.0)
      , ax(0.0)
      , ay(0.0)
      , length(1.0)
      , width(1.0)
      , height(1.0)
      , yaw(0.0)
      , cls()
      , t()
      , obstacle_exist_score(0.0)
    {
    }

    Scalar         x;       ///< position x
    Scalar         y;       ///< position y
    Scalar         z;       ///< position z
    Scalar         vx;      ///< velocity x
    Scalar         vy;      ///< velocity y
    Scalar         ax;      ///< acceleration x
    Scalar         ay;      ///< acceleration y
    Scalar         length;  ///< length
    Scalar         width;   ///< width
    Scalar         height;  ///< height
    Scalar         yaw;     ///< yaw angel (radius)
    Classification cls;     ///< classification
    Timestamp      t;       ///< timestamp
    Scalar         obstacle_exist_score;
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif
