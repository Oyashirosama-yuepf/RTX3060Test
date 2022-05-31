/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file association_metric.h
 * @brief this file defines association metric for parking slot association
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @author Changxi Cheng (chengchangxi@holomatic.com)
 * @date 2021-04-02
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_ASSOCIATION_METRIC_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_ASSOCIATION_METRIC_H_

#include <holo/localization/vision/vslam/semantic/common_types.h>
#include <holo/localization/vision/vslam/semantic/hungarian_optimizer.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
namespace semantic
{
/**
 * @addtogroup semantic
 * @{
 *
 */

/**
 * @brief This class define association metric
 *
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct AssociationMetric
{
    using Ptr      = std::shared_ptr<AssociationMetric>;
    using ConstPtr = std::shared_ptr<const AssociationMetric>;

    /**
     * @brief Destroy the Association Metric object
     *
     */
    virtual ~AssociationMetric()
    {
    }

    /**
     * @brief
     *
     * @param left
     * @param right
     * @return Matrix (size(left) x size(right))
     */
    virtual MatrixX operator()(const std::vector<ParkingSlotType>& left,
                               const std::vector<ParkingSlotType>& right) const = 0;
};

/**
 * @brief define iou metric
 *
 * @details it only supports parallel box
 *
 */
struct IouMetric : public AssociationMetric
{
    using Box2Type = geometry::Box2T<Scalar>;

    /**
     * @brief Destroy the Iou Metric object
     *
     */
    virtual ~IouMetric()
    {
    }

    /**
     * @brief compute distance matrix in the same coordinate
     *
     * @details
     * 1. The inputs are assumed in the same coordinate and only contain valid parking slots
     * 2. In the returned matrix, each row represents an ordered element in left, each col represents an ordered element
     *    in right
     *
     * @param left
     * @param right
     * @return Matrix
     */
    virtual MatrixX operator()(const std::vector<ParkingSlotType>& left,
                               const std::vector<ParkingSlotType>& right) const override
    {
        static const Scalar kMinIou = 0.05;  // IOU

        // construct prediction box2
        std::vector<Box2Type> prediction;
        for (const auto& parking_slot : left)
        {
            prediction.emplace_back(constructBox(parking_slot));
        }

        //　constrcut detection box2
        std::vector<Box2Type> detection;
        for (const auto& parking_slot : right)
        {
            detection.emplace_back(constructBox(parking_slot));
        }

        // construct distance matrix
        MatrixX dist_mat(prediction.size(), detection.size());
        for (size_t i = 0u; i < prediction.size(); i++)
        {
            for (size_t j = 0u; j < detection.size(); j++)
            {
                // @todo Instead of throwing an exception, Box2 returns 0.0 when its angle is NOT zero
                Scalar const iou = prediction.at(i).ComputeIntersectionOverUnion(detection.at(j));
                dist_mat(i, j)   = (iou >= kMinIou) ? 1.0 - iou : HungarianOptimizer::DIST_INF_VALUE;
            }
        }
        return dist_mat;
    }

private:
    /**
     * @brief construct a box2
     *
     * @param parking_slot
     * @return Box2Type
     */
    Box2Type constructBox(const ParkingSlotType& parking_slot) const
    {
        // @todo is it the right way to construct a box (duyanwei@holomatic.com)
        // @todo it can cause severe issue if they do not share the same definitions !!!
        return Box2Type(parking_slot.center_vertex.GetPointXY(), parking_slot.width, parking_slot.height,
                        parking_slot.angle);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief define distance metric
 *
 * @details compute the average distance of vertices
 *
 */
struct DistanceMetric : public AssociationMetric
{
    /**
     * @brief Destroy the Iou Metric object
     *
     */
    virtual ~DistanceMetric()
    {
    }

    /**
     * @brief compute distance matrix in the same coordinate
     *
     * @details
     * 1. The inputs are assumed in the same coordinate and only contain valid parking slots
     * 2. In the returned matrix, each row represents an ordered element in left, each col represents an ordered element
     *    in right
     *
     * @param left
     * @param right
     * @return Matrix
     */
    virtual MatrixX operator()(const std::vector<ParkingSlotType>& left,
                               const std::vector<ParkingSlotType>& right) const override
    {
        static const Scalar kMaxDist = 2.0;  // meter @todo

        MatrixX dist_mat(left.size(), right.size());
        for (size_t i = 0u; i < left.size(); i++)
        {
            for (size_t j = 0u; j < right.size(); j++)
            {
                const Scalar dist = computeDistance(left.at(i), right.at(j));
                dist_mat(i, j)    = dist < kMaxDist ? dist : HungarianOptimizer::DIST_INF_VALUE;
            }
        }
        return dist_mat;
    }

private:
    /**
     * @brief compute the distance between two parking slot
     *
     * @param left
     * @param right
     * @todo Complex calculation methods will be used in the future (chengchangxi@holomatic.com)
     * @return Scalar
     */
    Scalar computeDistance(const ParkingSlotType& left, const ParkingSlotType& right) const
    {
        Scalar sum = left.vertices[0].Dist(right.vertices[0]);
        sum += left.vertices[1].Dist(right.vertices[1]);
        Scalar num = 2.0;

        if (left.is_center_vertex_available && right.is_center_vertex_available)
        {
            sum += left.center_vertex.Dist(right.center_vertex);
            num += 1.0;
        }
        return sum / num;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace semantic

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_ASSOCIATION_METRIC_H_