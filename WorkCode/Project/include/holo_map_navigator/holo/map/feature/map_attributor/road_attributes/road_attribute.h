/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_attribute.h
 * @brief Attributes of HD Map.
 * @author wanghaiyang(wanghaiyang@holomaitc.com)
 * @date "2020-07-16"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ATTRIBUTE_ROAD_ATTRIBUTE_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ATTRIBUTE_ROAD_ATTRIBUTE_H_

#include <vector>

#include <holo/geometry/point3.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace attributes
{

/**
 * @addtogroup attributes
 * @{
 *
 */

/**
 * @brief Attributes of road.
 *
 * @note Reference to: https://holomatic.feishu.cn/docs/doccn9ynSedyL6uy7qUbUo5HHrb
 */
class RoadAttribute
{
public:
    /**
     * @brief Redefine external types.
     */
    using PointType  = holo::geometry::Point3d;
    using ScalarType = holo::float32_t;
    using VectorType = std::vector<RoadAttribute>;

    /**
     * @brief Marshal a road attribute to a JSON string.
     *
     * @param[in] attribute A RoadAttribute object.
     * @return A JSON string.
     */
    static std::string FormatToString(RoadAttribute const& attribute);

    /**
     * @brief Marshal an array of road attributes to a JSON string.
     *
     * @param[in] attributes An array of road attributes.
     * @return A JSON string.
     */
    static std::string FormatToString(RoadAttribute::VectorType const& attributes);

    /**
     * @brief Value of super elevation(Unit: %).
     *
     * @note Detail info: https://holomatic.feishu.cn/docs/doccn9ynSedyL6uy7qUbUo5HHrb
     */
    enum class Superelevation : holo::int8_t
    {
        FLAT                    =  0,      ///< Superelevation < 4%, means flat.
        LEFT_MORE_THAN_RIGHT_4  =  4,      ///< Superelevation in range: [4%, 6%).
        LEFT_MORE_THAN_RIGHT_6  =  6,      ///< Superelevation in range: [6%, 8%).
        LEFT_MORE_THAN_RIGHT_8  =  8,      ///< Superelevation > 8%.
        RIGHT_MORE_THAN_LEFT_4  = -4,      ///< Superelevation in range: [4%, 6%)
        RIGHT_MORE_THAN_LEFT_6  = -6,      ///< Superelevation in range: [6%, 8%)
        RIGHT_MORE_THAN_LEFT_8  = -8,      ///< Superelevation > 8%.
        UNKNOWN                 = 127      ///< Placeholder.
    };

    /**
     * @brief Access ref point.
     *
     * @return Point3d.
     */
    PointType& GetRefPoint() noexcept
    {
        return this->point_;
    }

    /**
     * @brief Access ref point with coordinate reference system of WGS84-UTM.
     *
     * @return Point3d.
     */
    PointType const& GetRefPoint() const noexcept
    {
        return this->point_;
    }

    /**
     * @brief Assign a new ref point
     *
     * @param[in] p A new ref point with coordinate reference system of WGS84-UTM.
     * @return Nothing.
     */
    void SetRefPoint(PointType const& p) noexcept
    {
        this->point_ = p;
    }

    /**
     * @brief Access the relative distance between current car postion and ref point on map.
     *
     * @return Relative distance(Unit: meter).
     */
    ScalarType GetRelativeDistance() const noexcept
    {
        return this->distance_;
    }

    /**
     * @brief Assign the relative distance(Uint: meter).
     *
     * @param[in] d Relative distance between current car position and ref point on map.
     * @return Nothing.
     */
    void SetRelativeDistance(ScalarType const d) noexcept
    {
        this->distance_ = d;
    }

    /**
     * @brief Access slope(Unit: radian).
     *
     * @return A slope value.
     */
    ScalarType GetSlope() const noexcept
    {
        return this->slope_;
    }

    /**
     * @brief Assign slope(Unit: radian).
     *
     * @param[in] slope A new slope value.
     * @return Nothing
     */
    void SetSlope(ScalarType const slope) noexcept
    {
        this->slope_ = slope;
    }

    /**
     * @brief Access curvature radius(Unit: meter).
     *
     * @details If the curvature is 0, then the radius will be maximum value
     *
     * @return A curvature value.
     */
    ScalarType GetCurvatureRadius() const noexcept
    {
        return curvature_;
    }

    /**
     * @brief Assign curvature radius(Unit: meter).
     *
     * @param[in] c A curvature radius value.
     * @return Nothong.
     */
    void SetCurvatureRadius(ScalarType const c) noexcept
    {
        this->curvature_ = c;
    }

    /**
     * @brief Access super elevation(Unit: Enum).
     *
     * @return A super elevation value.
     */
    Superelevation GetSuperelevation() const noexcept
    {
        return this->super_elevation_;
    }

    /**
     * @brief Assign super elevation(Unit: enum).
     *
     * @param [in] s Superelevation， detail info: https://holomatic.feishu.cn/docs/doccn9ynSedyL6uy7qUbUo5HHrb
     * @return Nothing.
     */
    void SetSuperelevation(Superelevation const s) noexcept
    {
        this->super_elevation_ = s;
    }

private:
    PointType       point_;                                     ///< Reference point on road, Unit: meter.
    ScalarType      distance_        = 0.0f;                    ///< Reference point distance to current car postion. Unit: meter
    ScalarType      slope_           = 0.0f;                    ///< Vertical slope, Unit: radian.
    ScalarType      curvature_       = 0.0f;                    ///< Curvature radius, Unit: meter.
    Superelevation  super_elevation_ = Superelevation::UNKNOWN; ///< Horizontal slope, Unit: enum.
}; ///< End of class RoadAttribute

/**
 * @}
 *
 */

} ///< namespace attributes
} ///< namespace navigator
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ATTRIBUTE_ROAD_ATTRIBUTE_H_ */
