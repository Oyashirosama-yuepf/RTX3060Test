/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file csc_matrix.h
 * @brief the header of CSCMatrix struct
 * @author jiangshunchang(jiangshunchang@holomatic.com)
 * @date 2021-11-27
 */

#ifndef _HOLO_PLANNING_COMMON_CSC_MATRIX_H_
#define _HOLO_PLANNING_COMMON_CSC_MATRIX_H_

#include <vector>

#include <holo/core/types.h>

namespace holo
{
namespace planning
{
struct CSCMatrix
{
    std::vector<uint32_t>  indptr;   ///< The indptr of CSC matrix.
    std::vector<uint32_t>  indices;  ///< The indices of CSC matrix.
    std::vector<float64_t> data;     ///< The data of CSC matrix.
};

}  // namespace planning
}  // namespace holo

#endif  // _HOLO_PLANNING_COMMON_CSC_MATRIX_H_
