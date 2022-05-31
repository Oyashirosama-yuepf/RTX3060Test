/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gtsam_helper.h
 * @brief This header file defines .
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2021-06-11"
 */

#ifndef HOLO_PERCEPTION_3D_UTILS_GTSAM_HELPER_H_
#define HOLO_PERCEPTION_3D_UTILS_GTSAM_HELPER_H_

#include <holo/perception/factor_graph/advanced_types.h>

namespace holo
{
namespace perception
{
class GtsamHelper
{
public:
    static void AnalyzeGraph(NonlinearFactorGraph const& graph, Values const& values)
    {
        graph.print("original graph");
        values.print("linearization graph");

        auto const gaussian_graph = graph.linearize(values);

        Matrix const Hb = gaussian_graph->augmentedHessian();

        {
            uint32_t const dim     = Hb.rows() - 1U;
            Matrix const   hessian = Hb.topLeftCorner(dim, dim);

            Eigen::SelfAdjointEigenSolver<Matrix> eh(hessian);
            LOG(INFO) << "eigen values of hessian = " << eh.eigenvalues().transpose();

            LOG(INFO) << "determinant of hessian = " << hessian.determinant();
        }

        (gaussian_graph->optimizeDensely()).print("manually dense optimization");
    }
};

}  // namespace perception
}  // namespace holo

#endif  // HOLO_PERCEPTION_3D_UTILS_GTSAM_HELPER_H_
