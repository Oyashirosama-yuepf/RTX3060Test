/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file samplingpathplan.h
 * @brief the class of sampling path plan
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-05-06
 */

#ifndef _SAMPLINGPATHPLAN_H
#define _SAMPLINGPATHPLAN_H

#include <holo/hpp/parkingplan/commonfunction.h>
#include <holo/planning/util/collision_checker.h>

namespace holo
{
namespace planning
{
typedef std::vector<CurvePoint> SamplingPathVector;

int32_t const   SINGLE_SAMPLING_LENGTH = 4;     ///< single sampling path length threshold
int32_t const   LOCAL_PATH_LENGTH      = 4;     ///< local planning path length
int32_t const   MULTI_SAMPLING_TIMES   = 2;     ///< multi-stage sampling times
float64_t const OFFSET_DISTENCE        = 0.15;  ///< single offset distance
/// the number of unilateral lateral deviation paths when multi-stage sampling
int32_t const MULTI_OFFSET_PATH_NUMBER = 8;

struct PathSamplingData
{
    int32_t   segpoint[MULTI_SAMPLING_TIMES + 2];
    int32_t   offsetnum;
    float64_t deltx;
    float64_t delty;

    PathSamplingData()
    {
        for (int32_t i = 0; i < MULTI_SAMPLING_TIMES + 2; i++)
        {
            segpoint[i] = 0;
        }
        offsetnum = 0;
        deltx     = 0;
        delty     = 0;
    }

    void clear()
    {
        for (int32_t i = 0; i < MULTI_SAMPLING_TIMES + 2; i++)
        {
            segpoint[i] = 0;
        }
        offsetnum = 0;
        deltx     = 0;
        delty     = 0;
    }
};

class SamplingPathPlan
{
private:
    PathSamplingData                                  sampdata_;    ///< store the data structure of the sampling class
    SamplingPathVector                                samplepath_;  ///< output result of sampling path planning method
    std::vector<std::vector<geometry::Point2>> const* freespace_ = nullptr;
    int32_t          last_best_localpath_num_                    = 0;  ///< store the best local path selected last time
    CollisionChecker collision_checker_;
    int8_t           parkinglot_type_ = 2;  /// 1:vertical,2:parallel

    /**
     * @brief clear variables
     */
    void ClearVariable();

    /**
     * @brief  main process of multi-stage sampling path planning method
     *
     * @param[in] path global path
     *
     * @return output result of sampling path planning method
     */
    SamplingPathVector PathMutipleSampling(SamplingPathVector& path);

    /**
     * @brief  mark the path in segments as required
     *
     * @param[in] path global path
     *
     * @return global path marked in segments as required
     */
    SamplingPathVector CalcuPathLength(SamplingPathVector const& path);

    /**
     * @brief calculate the offset in the x and y directions
     *
     * @param[in] path global path
     */
    void CalcuDelt(SamplingPathVector const& path);

    /**
     * @brief  create offset path
     *
     * @param[in] path original path
     * @param[in] m offset scale
     *
     * @return the offset path after the calculation of the corresponding offset scale
     */
    SamplingPathVector CreateOffsetPath(SamplingPathVector const& path, int32_t m);

    /**
     * @brief  evaluate the optimal local path
     *
     * @param[in] mutilocalpath sampling path cluster
     * @param[in] navipath global path
     *
     * @return the number of the best path
     */
    int32_t EvaluBestLocalPath(std::vector<SamplingPathVector> mutilocalpath, SamplingPathVector navipath);

    /**
     * @brief  calculate the distance between two paths
     *
     * @param[in] localpath local path
     * @param[in] navipath global path
     *
     * @return The distance between the two paths
     */
    float64_t CalcuMinDis(SamplingPathVector localpath, SamplingPathVector navipath);

public:
    /**
     * @brief  collision checking for path
     *
     * @param[in] path  path
     * @param[in] collision_checker collision checker class
     * @param[in] interval  collision checking interval
     *
     * @return whether there is a collision
     */
    bool_t CollisionChecking4Path(SamplingPathVector const& path,
                                  CollisionChecker          collision_checker,
                                  float64_t                 interval = 0.5);

    /**
     * @brief  collision checking for path
     *
     * @param[in] path  path
     * @param[in] collision_checker collision checker class
     * @param[in] interval  collision checking interval
     *
     * @return CollisionCheckingDistance
     */
    float64_t CollisionCheckingDistance4Path(SamplingPathVector const& path,
                                             CollisionChecker          collision_checker,
                                             float64_t                 interval = 0.5);

    /**
     * @brief  external interface function
     *
     * @param[in] path global path
     * @param[in] freespace freespace
     *
     * @return output result of sampling path planning method
     */
    SamplingPathVector GetSamplingPath(SamplingPathVector&                               path,
                                       std::vector<std::vector<geometry::Point2>> const* freespace);

    /**
     * @brief  set parkinglot type
     *
     * @param[in] parkinglot_type parkinglot_type
     */
    void SetParkinglotType(int8_t parkinglot_type)
    {
        parkinglot_type_ = parkinglot_type;
    }

    /**
     * @brief constructor.
     */
    SamplingPathPlan()
    {
    }

    /**
     * @brief destroys the object.
     */
    ~SamplingPathPlan() = default;
};

}  // namespace planning
}  // namespace holo

#endif
