/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file curve_descriptor.h
 * @brief This header file defines CurveDescriptorT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-11
 */

#ifndef HOLO_GEOMETRY_DETAILS_CURVE_DESCRIPTOR_H_
#define HOLO_GEOMETRY_DETAILS_CURVE_DESCRIPTOR_H_

#include <limits>
#include <string>

#include <holo/core/types.h>

namespace holo
{
namespace geometry
{
namespace details
{
/**
 * @addtogroup geometry
 *
 * @{
 */

/**
 * @brief Base class of different kind curve, polynomial curve and bezier curve
 *
 * @tparam T support float32_t and float64_t
 */
template <typename T>
class CurveDescriptorT
{
public:
    /**
     * @brief enum of curve type, support polynomial and bezier curve
     */
    enum class CurveDescriptorType : uint8_t
    {
        POLYNOMIAL2D = 0U,
        POLYNOMIAL3D = 1U,
        BEZIER2D     = 2U,
        BEZIER3D     = 3U,
    };

public:
    /**
     * @brief Default constructor
     */
    CurveDescriptorT() noexcept;

    /**
     * @brief Destructor
     */
    virtual ~CurveDescriptorT() noexcept;

    /**
     * @brief Get curve descriptor type
     *
     * @return curve descriptor type
     */
    virtual CurveDescriptorType GetCurveType() const noexcept = 0;

    /**
     * @brief Serialize content to string
     *
     * @return serialized string
     */
    virtual std::string ToString() const noexcept = 0;

};

/**
 * @}
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "./impl/curve_descriptor.hpp"

#endif  // !HOLO_GEOMETRY_DETAILS_CURVE_DESCRIPTOR
