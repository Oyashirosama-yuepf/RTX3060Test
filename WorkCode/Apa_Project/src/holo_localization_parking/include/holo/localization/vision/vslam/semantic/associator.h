/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file associator.h
 * @brief this file defines data association for semantic slam
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @author Changxi Cheng (chengchangxi@holomatic.com)
 * @date 2021-02-25
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_ASSOCIATOR_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_ASSOCIATOR_H_

#include <holo/localization/vision/vslam/semantic/association_metric.h>
#include <holo/localization/vision/vslam/semantic/common_types.h>
#include <holo/localization/vision/vslam/semantic/hungarian_optimizer.h>
#include <holo/localization/vision/vslam/semantic/visualizer.h>

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
 * @brief this class define associator
 *
 */
class Associator
{
public:
    using Ptr      = std::shared_ptr<Associator>;
    using ConstPtr = std::shared_ptr<const Associator>;
    using VisualizationCallback =
        std::function<void(const std::vector<ParkingSlotType>&, const std::vector<ParkingSlotType>&, const MatrixX&,
                           const std::vector<int32_t>&)>;

    static const int32_t UNASSIGNED_VALUE = -1;

    /**
     * @brief Construct a new Associator object
     *
     */
    Associator() : visualization_callback_(nullptr)
    {
    }

    /**
     * @brief Destroy the Associator object
     *
     */
    virtual ~Associator()
    {
    }

    /**
     * @brief core algorithm happens here
     *
     * @param left parking slot at timestamp t_k
     * @param rTl frame pose that transforms parking slot from left to right
     * @param right parking slot at timestamp t_{k+1}
     * @return std::vector<int32_t>
     */
    virtual std::vector<int32_t> Run(const std::vector<ParkingSlotType>& left, const Pose3& rTl,
                                     const std::vector<ParkingSlotType>& right) const = 0;

    /**
     * @brief Set the Visualization Callback object
     *
     * @param cb
     */
    void SetVisualizationCallback(const VisualizationCallback& cb)
    {
        visualization_callback_ = cb;
    }

protected:
    VisualizationCallback visualization_callback_;
};

/**
 * @brief associator with hungarian algorithm
 *
 */
template <typename MetricType>
class HungarianAssociator : public Associator
{
public:
    /**
     * @brief Construct a new Hungarian Associator object
     */
    HungarianAssociator() : Associator()
    {
    }

    /**
     * @brief Destroy the Hungarian Associator object
     *
     */
    virtual ~HungarianAssociator()
    {
    }

    /**
     * @brief run hungarian algorithm
     *
     * @param left parking slot at timestamp t_{k}
     * @param rTl frame pose that transforms parking slot from left to right
     * @param right parking slot at timestamp t_{k+1}
     * @return std::vector<int32_t> it has the same size as left
     */
    virtual std::vector<int32_t> Run(const std::vector<ParkingSlotType>& left, const Pose3& rTl,
                                     const std::vector<ParkingSlotType>& right) const override
    {
        // make a prediction
        std::vector<ParkingSlotType> prediction;
        for (const auto& parking_slot : left)
        {
            prediction.emplace_back(Utility::TransformParkingSlot(parking_slot, rTl));
        }

        // compute distance matrix
        const MatrixX dist_mat = metric_(prediction, right);

        // compute assignment
        const std::vector<int32_t> result =
            HungarianOptimizer().FindOptimalAssignment(dist_mat, HungarianOptimizer::TMethod::DEFAULT_ASSIGNMENT);

        // visualization
        if (visualization_callback_)
        {
            visualization_callback_(prediction, right, dist_mat, result);
        }

        return result;
    }

private:
    MetricType metric_;
};

/**
 * @brief
 *
 * @todo IcpAssociator
 *
 */

}  // namespace semantic

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_ASSOCIATOR_H_