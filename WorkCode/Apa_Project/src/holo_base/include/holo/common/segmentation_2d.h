/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file segmentation_2d.h
 * @brief This header file defines class Segmentation2DT.
 * @author liufangyuan(liufangyuan@holomaitc.com)
 * @date "2019-12-26"
 */

#ifndef HOLO_COMMON_SEGMENTATION_2D_H_
#define HOLO_COMMON_SEGMENTATION_2D_H_

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include <holo/common/sensor_id.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/geometry/point2.h>

namespace holo
{
/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief Segmentation2D general type
 *
 * @tparam T segmentation2D type
 */
template <typename T>
class Segmentation2DT
{
public:
    using Scalar     = T;
    using InstanceId = uint8_t;
    using Confidence = float32_t;
    using SensorId   = holo::common::SensorId;
    using Point2Type = holo::geometry::Point2T<Scalar>;
    using Contour    = std::vector<Point2Type>;
    using Contours   = std::vector<Contour>;
    using Timestamp  = holo::common::Timestamp;
    /**
     * @brief Definition of CategoryId
     */
    enum CategoryId : uint8_t
    {
        BACK_GROUND   = 0U,
        TRAFFIC_BOARD = 1U
    };

    /**
     * @brief Definition of Info
     */
    struct Info
    {
        SensorId sensor_id;
        uint32_t num_classes;
        uint32_t height;
        uint32_t width;
    };

    /**
     * @brief Definition of SemanticSegment
     */
    struct SemanticSegment
    {
        CategoryId category_id;
        InstanceId instance_id;
        Confidence confidence;
        Contours   contours;
    };
    using SemanticSegments = std::vector<SemanticSegment>;

    /**
     * @brief Construct a new Segmentation2DT object without parameters
     */
    Segmentation2DT() = default;

    /**
     * @brief Construct a new Segmentation2DT object
     *
     * @param stamp timestamp
     * @param info info
     * @param semantic_segments segmentations result
     */
    Segmentation2DT(const Timestamp& stamp, const Info& info, const SemanticSegments& semantic_segments)
      : stamp_(stamp), info_(info), semantic_segments_(semantic_segments)
    {
    }

    /**
     * @brief get const stamp_
     *
     * @return const Timestamp&
     */
    const Timestamp& GetTimestamp() const noexcept
    {
        return stamp_;
    }

    /**
     * @brief get stamp_
     *
     * @return Timestamp&
     */
    Timestamp& GetTimestamp() noexcept
    {
        return stamp_;
    }

    /**
     * @brief set stamp_ by gave timestamp
     *
     * @param stamp
     */
    void SetTimestamp(const Timestamp& stamp) noexcept
    {
        stamp_ = stamp;
    }

    /**
     * @brief get const info_
     *
     * @return const Info&
     */
    const Info& info() const noexcept
    {
        return info_;
    }

    /**
     * @brief get info_
     *
     * @return Info&
     */
    Info& info() noexcept
    {
        return info_;
    }

    /**
     * @brief set info_ by gave info
     *
     * @param info
     */
    void info(const Info& info) noexcept
    {
        info_ = info;
    }

    /**
     * @brief swap info_ with gave info
     *
     * @param info
     */
    void info(Info&& info)
    {
        std::swap(info_, info);
    }

    /**
     * @brief get const semantic_segments_
     *
     * @return const SemanticSegments&
     */
    const SemanticSegments& semantic_segments() const noexcept
    {
        return semantic_segments_;
    }

    /**
     * @brief get semantic_segments_
     *
     * @return SemanticSegments&
     */
    SemanticSegments& semantic_segments() noexcept
    {
        return semantic_segments_;
    }

    /**
     * @brief set semantic_segments_ by gave semantic_segments_
     *
     * @param semantic_segments
     */
    void semantic_segments(const SemanticSegments& semantic_segments)
    {
        semantic_segments_ = semantic_segments;
    }

    /**
     * @brief swap semantic_segments_ with gave semantic_segments
     *
     * @param semantic_segments
     */
    void semantic_segments(SemanticSegments&& semantic_segments)
    {
        std::swap(semantic_segments_, semantic_segments);
    }

private:
    /**
     * @brief Timestamp
     */
    Timestamp stamp_;
    /**
     * @brief Info of segmentation image
     */
    Info info_;
    /**
     * @brief Semantic segments results in 2D
     */
    SemanticSegments semantic_segments_;
};

/**
 * @brief handy typedefs
 */
using Segmentation2Df = Segmentation2DT<float32_t>;
using Segmentation2Dd = Segmentation2DT<float64_t>;
using Segmentation2D  = Segmentation2DT<float64_t>;

/**
 * @}
 */
}  // namespace holo
#endif  // !HOLO_VERSION_SEGMENTATION_2D_H_
