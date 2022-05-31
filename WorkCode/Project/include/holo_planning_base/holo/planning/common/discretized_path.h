/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file discretized_path.h
 * @brief the header of discretized path
 * @author Zhang Yuchen(zhangyuchen@holomatic.com)
 * @date 2021-07-28
 */

#ifndef _HOLO_PLANNING_COMMON_DISCRETIZED_PATH_H_
#define _HOLO_PLANNING_COMMON_DISCRETIZED_PATH_H_

#include <vector>

#include <holo/common/path.h>
#include <holo/planning/common/curve_point.h>

namespace holo
{
namespace planning
{
/**
 * @brief class of discretized path
 */
class DiscretizedPath : public std::vector<CurvePoint>
{
public:
    /**
     * @brief default constructor
     */
    DiscretizedPath() = default;

    /**
     * @brief constructor
     *
     * @param points the discretized point list
     */
    explicit DiscretizedPath(std::vector<CurvePoint> const& points) : std::vector<CurvePoint>(points)
    {
    }

    /**
     * @brief default destructor
     */
    ~DiscretizedPath() = default;

    /**
     * @brief get curve point at s
     *
     * @details if input s is smaller than the first point's s, return the first point, else if the input s is @n
     * larger than the last point's s, return the last point, else return the point which is calculated by the first @n
     * point whose s is larger than input s and its precursor @n
     *
     * @param s the path s
     *
     * @return the curve point
     */
    CurvePoint Evaluate(float64_t s) const;

    /**
     * @brief get the length of the discretized path
     *
     * @return the length of the discretized path
     */
    float64_t GetLength() const;
};

}  // namespace planning
}  // namespace holo

#endif
