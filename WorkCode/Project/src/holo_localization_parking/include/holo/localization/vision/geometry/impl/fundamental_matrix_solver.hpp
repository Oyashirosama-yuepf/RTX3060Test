/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fundamental_matrix_solver.hpp
 * @brief implementation file  of fundamental matrix solver class
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-07-03"
 */

namespace holo
{
namespace localization
{
namespace vision
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
FundamentalMatrixSolverT<T>::FundamentalMatrixSolverT(const MethodType& method_type) noexcept
  : method_type_(method_type)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
FundamentalMatrixSolverT<T>::~FundamentalMatrixSolverT() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t FundamentalMatrixSolverT<T>::ComputeModels(const std::vector<std::pair<Point2, Point2> >& pairs,
                                                  std::vector<Matrix3>&                          models) const
{
    bool_t is_success = false;

    if (method_type_ == MethodType::FM_8POINT)
    {
        models.resize(1u);
        FundamentalMatrix8Points fm8;
        is_success = fm8(pairs, models[0u]);
    }
    else
    {
        throw std::runtime_error("invalid method used to conpute fundamental matrix");
    }

    return is_success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
typename FundamentalMatrixSolverT<T>::MethodType FundamentalMatrixSolverT<T>::GetMethodType() const noexcept
{
    return method_type_;
}
}  // namespace vision
}  // namespace localization
}  // namespace holo
