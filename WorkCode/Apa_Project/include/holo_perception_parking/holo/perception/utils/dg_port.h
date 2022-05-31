/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file dg_port.h
 * @brief Header file for helping port perception_parking to dg
 * @author lizhijian (lizhijian@holomatic.com)
 * @date "2020-11-18"
 */
#ifndef HOLO_PERCEPTION_LIB_DG_PORT_H_
#define HOLO_PERCEPTION_LIB_DG_PORT_H_

#include <holo/common/extrinsic.h>
#include <holo/common/intrinsic.h>
#include <sys/time.h>

#include <Eigen/Eigen>
#include <stdexcept>
#include <vector>

#include "holo/common/timestamp.h"

namespace holo
{
using HoloException = std::runtime_error;
// using Extrinsicd    = ExtrinsicT<float32_t>;

template <typename HMType>
Eigen::MatrixXf holo2eigen(HMType hm)
{
    size_t          row = hm.GetRows();
    size_t          col = hm.GetCols();
    Eigen::MatrixXf em  = Eigen::MatrixXf::Zero(row, col);
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            em(i, j) = hm(i, j);
        }
    }
    return em;
}

template <typename HMType>
HMType eigen2holo(Eigen::MatrixXf em)
{
    size_t row = em.rows();
    size_t col = em.cols();
    HMType hm  = HMType::Identity();
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            hm(i, j) = em(i, j);
        }
    }
    return hm;
}

#define H2E(x) holo::holo2eigen(x)
#define E2H(x) holo::eigen2holo(x)

class DGPort
{
public:
    static holo::common::Timestamp TimestampNow()
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return holo::common::Timestamp(tv.tv_sec, tv.tv_usec * 1000);
    }
};

}  // namespace holo
#endif  /// HOLO_PERCEPTION_LIB_DG_PORT_H_
