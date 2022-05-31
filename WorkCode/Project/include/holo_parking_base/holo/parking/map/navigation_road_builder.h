/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_navi_road.h
 * @brief Define navi road info
 * @author wangminghui@holomatic.com
 * @date "2021-08-04"
 */

#ifndef HOLO_MAP_NAVI_ROAD_POINT_ATTRIBUTES_H_
#define HOLO_MAP_NAVI_ROAD_POINT_ATTRIBUTES_H_

#include <holo/common/coordinate.h>
#include <holo/common/road_frame2.h>
#include <holo/common/road_type.h>
#include <holo/common/timestamp.h>
#include <holo/container/details/vector.h>
#include <holo/core/epsilon.h>
#include <holo/core/types.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>

#include <cmath>
#include <limits>
#include <utility>
#include <vector>
namespace holo
{
namespace map
{
/**
 * @brief  Road point Attributes.
 *
 * @ref Reference to: https://holomatic.feishu.cn/docs/doccnLDJc6cBpsxHELL5YO8RYkg#
 */
class NavigationRoadPoint
{
public:
    using ScalarType = holo::float64_t;
    using PointType  = holo::geometry::Point3T<ScalarType>;
    /**
     * @brief Default constructer
     */
    NavigationRoadPoint() = default;

    /**
     * @brief Constructer with parameters
     *
     * @param[in] point lane mid point
     * @param[in] left_extend_area_width unit:m
     * @param[in] right_extend_area_width unit:m
     * @param[in] left_available_width unit:m
     * @param[in] right_available_width unit:m
     * @param[in] slope Slope, unit: radian
     * @param[in] curvature_radius Curvature radius, unit: meter
     * @param[in] horizontal_slope unit: radian
     * @param[in] start_distance  start distance of target point. unit:m
     */
    NavigationRoadPoint(PointType const& point, ScalarType const left_extend_area_width,
                        ScalarType const right_extend_area_width, ScalarType const left_available_width,
                        ScalarType const right_available_width, holo::bool_t curvature_flag,
                        ScalarType curvature_radius, holo::bool_t slope_flag, ScalarType const slope,
                        holo::bool_t horizontal_slope_flag, ScalarType horizontal_slope,
                        ScalarType start_distance) noexcept
      : ref_point_(point)
      , left_extend_area_width_(left_extend_area_width)
      , right_extend_area_width_(right_extend_area_width)
      , left_available_width_(left_available_width)
      , right_available_width_(right_available_width)
      , curvature_flag_(curvature_flag)
      , curvature_radius_(curvature_radius)
      , slope_flag_(slope_flag)
      , slope_(slope)
      , horizontal_slope_flag_(horizontal_slope_flag)
      , horizontal_slope_(horizontal_slope)
      , start_distance_(start_distance)
    {
    }

    void SetRefPoint(PointType& ref_point)
    {
        ref_point_ = ref_point;
    }
    /**
     * @brief Get ref point.
     *
     * @return A  reference of PointType object.
     */
    PointType const& GetRefPoint() const
    {
        return ref_point_;
    }

    void SetStartDistance(ScalarType& start_distance)
    {
        start_distance_ = start_distance;
    }
    /**
     * @brief 获取当前点到起点距离(单位:米)
     * @return 当前点到起点距离
     */
    ScalarType const& GetStartDistance() const
    {
        return start_distance_;
    }
    /**
     * @brief 获取左侧可扩展区域(单位:米)
     * @return 左侧可扩展区域
     */
    ScalarType const& GetLeftExtendAreaWidth() const
    {
        return left_extend_area_width_;
    }

    /**
     * @brief 获取右侧可扩展区域(单位:米)
     * @return 右侧可扩展区域
     */
    ScalarType const& GetRightExtendAreaWidth() const
    {
        return right_extend_area_width_;
    }

    void SetLeftAvailableWidth(ScalarType& value)
    {
        left_available_width_ = value;
    }
    /**
     * @brief 获取左侧非避让可用宽度(单位:米)
     * @return 左侧非避让可用宽度
     */
    ScalarType const& GetLeftAvailableWidth() const
    {
        return left_available_width_;
    }

    void SetRightAvailableWidth(ScalarType& value)
    {
        right_available_width_ = value;
    }
    /**
     * @brief 获取右侧非避让可用宽度(单位:米)
     * @return 左侧非避让可用宽度
     */
    ScalarType const& GetRightAvailableWidth() const
    {
        return right_available_width_;
    }

    /**
     * @brief 取得CurvatureFlag
     *
     * @return 该Point是否有曲率值
     */
    holo::bool_t const& GetCurvatureFlag() const
    {
        return curvature_flag_;
    }

    /**
     * @brief Set curvature radius (Unit: meter).
     *
     * @param[in] curvature A curvature radius value.
     */
    void SetCurvatureRadius(ScalarType const curvature_radius) noexcept
    {
        this->curvature_radius_ = curvature_radius;
    }

    /**
     * @brief Get curvature radius (Unit: meter).
     *
     * @return A curvature radius value.
     */
    ScalarType const& GetCurvatureRadius() const
    {
        return curvature_radius_;
    }

    /**
     * @brief 取得SlopeFlag
     *
     * @return 该Point是否有纵坡
     */
    holo::bool_t const& GetSlopeFlag() const
    {
        return slope_flag_;
    }

    /**
     * @brief 取得纵坡坡度信息(单位:弧度)
     *
     * @return 该Point对应的纵坡值
     */
    ScalarType const& GetSlope() const
    {
        return slope_;
    }

    /**
     * @brief 取得 横坡坡度信息(单位:弧度)
     *
     * @return 该Point是否有横坡
     */
    holo::bool_t const& GetHorizontalSlopeFlag() const
    {
        return horizontal_slope_flag_;
    }

    /**
     * @brief 取得横坡坡度信息(单位:弧度)
     *
     * @return 该Point对应的横坡坡度值
     */
    ScalarType const& GetHorizontalSlope() const
    {
        return horizontal_slope_;
    }

    /**
     * @brief Set slope(Unit: radian).
     *
     * @param[in] slope A new slope value.
     */
    void SetSlope(ScalarType const slope)
    {
        slope_ = slope;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(ref_point_, left_extend_area_width_, right_extend_area_width_,
                                                          left_available_width_, right_available_width_,
                                                          curvature_flag_, curvature_radius_, slope_flag_, slope_,
                                                          horizontal_slope_flag_, horizontal_slope_, start_distance_);
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << ref_point_ << left_extend_area_width_ << right_extend_area_width_ << left_available_width_
                   << right_available_width_ << curvature_flag_ << curvature_radius_ << slope_flag_ << slope_
                   << horizontal_slope_flag_ << horizontal_slope_ << start_distance_ << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> ref_point_ >> left_extend_area_width_ >> right_extend_area_width_ >> left_available_width_ >>
            right_available_width_ >> curvature_flag_ >> curvature_radius_ >> slope_flag_ >> slope_ >>
            horizontal_slope_flag_ >> horizontal_slope_ >> start_distance_ >> holo::serialization::align;
    }

private:
    PointType    ref_point_;                        ///< Ref point.
    ScalarType   left_extend_area_width_  = 0.0f;   ///< Unit: m.
    ScalarType   right_extend_area_width_ = 0.0f;   ///< Unit: m.
    ScalarType   left_available_width_    = 0.0f;   ///< Unit: m.
    ScalarType   right_available_width_   = 0.0f;   ///< Unit: m.
    holo::bool_t curvature_flag_          = false;  /// curvature flag
    ScalarType   curvature_radius_        = 0.0f;   ///< Unit: meter.
    holo::bool_t slope_flag_              = false;  ///< slope flag exist
    ScalarType   slope_                   = 0.0f;   ///< Unit: radian.
    holo::bool_t horizontal_slope_flag_   = false;  ///<  horizontal slope exist
    ScalarType   horizontal_slope_        = 0.0f;   ///< Unit: radian.
    ScalarType   start_distance_          = 0.0f;   ///< Unit: m.
};

class NavigationRoadBuilder
{
public:
    using ScalarType    = holo::float64_t;
    using PointType     = holo::geometry::Point3T<ScalarType>;
    using Distance      = holo::float64_t;
    using CurveType     = holo::geometry::CurveBezier<PointType, 1024U, 3U>;
    using RoadFrameType = holo::common::RoadFrame<CurveType, 1024>;
    /**
     * @brief Input paramters for current algorithm.
     */
    struct Input
    {
        /// Define types for inner members.
        // start distance of target point.
        Distance start_distance = 0.0;
        // road length Unit: m.
        Distance length = 0.0;
        // point interval, intervalconst variable is greater than zero Unit: m.
        Distance intervalconst = 0.0;
        // A buffer length value,if insert point to front or back point length less than the buffer length, will not
        // insert the point., tolerance variable is greater than or equal to zero
        Distance tolerance = 0.0;
    };

    /**
     * @brief Output parameters for current algorithm.
     */
    struct Output
    {
        // Vector of NavigationRoadPoint
        std::vector<NavigationRoadPoint> navigation_points;
    };

    /**
     * @brief Mashal the input to a JSON string.
     *
     * @param[in] input Input parameters.
     * @return A Json string.
     */
    static std::string FormatToString(Input const& input);

    /**
     * @brief Mashal the input to a JSON string.
     *
     * @param[in] ouput Output parameters.
     * @return A Json string.
     */
    static std::string FormatToString(Output const& output);

    /**
     * @brief Default Constructor.
     */
    NavigationRoadBuilder();

    /**
     * @brief Default Destructor.
     */
    virtual ~NavigationRoadBuilder();

    void SetRoadFrame(RoadFrameType const& road_frame);
    /**
     * @brief Access verbose flag.
     *
     * @return Verbose flag.
     */
    holo::bool_t GetVerbose() const noexcept;

    /**
     * @brief Assing verbose flag.
     *
     * @param[in] true: Print detail debug logs.
     *            false: Close detail debug logs(default value).
     */
    void SetVerbose(holo::bool_t const v) const;

    /**
     * @brief Extract left and right special road boundaries close to
     *        target point.
     *
     * @param[in] input Input parameters.
     * @param[out] output Output paramters.
     * @return true: No error.
     *         false: An error occurs in this function, refer to logs for
     *                for more details.
     */
    holo::bool_t Process(Input const& input, Output& output);

    /**
     * @brief Extract left and right special road boundaries close to
     *        target point.
     *
     * @param[in] input Input parameters.
     * @param[out] output Output paramters.
     * @return true: No error.
     *         false: An error occurs in this function, refer to logs for
     *                for more details.
     */
    holo::bool_t operator()(Input const& input, Output& output);

private:
    /// Implemention of NavigationRoadBuilderInner.
    class NavigationRoadBuilderInner;
    /// A smart pointer of NavigationRoadBuilderInner.
    std::unique_ptr<NavigationRoadBuilderInner> inner_;
};

}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_ROAD_REF_POINT_ATTRIBUTES_H_ */
