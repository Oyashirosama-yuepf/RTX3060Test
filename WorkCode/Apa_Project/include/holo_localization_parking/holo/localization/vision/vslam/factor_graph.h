/*!
 * \brief VSLAM factor graph class header file
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Jan-15-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_FACTOR_GRAPH_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_FACTOR_GRAPH_H_

#include <gtsam/nonlinear/NonlinearFactorGraph.h>

#include <holo/localization/vision/vslam/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
///////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup localization
 * @brief this class defines the structure of factor graph that is used in
 *        VSLAM sliding window optimization
 *
 * @details typedef gtsam::NonlinearFactorGraph
 */

typedef gtsam::NonlinearFactorGraph FactorGraph;

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_FACTOR_GRAPH_H_
