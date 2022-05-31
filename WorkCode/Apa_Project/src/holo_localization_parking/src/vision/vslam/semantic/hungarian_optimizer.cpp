/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hungarian_optimizer.hpp
 * @brief This header file defines hungarian algorithm.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @author duyanwei(duyanwei@holomatic.com)
 * @author chengchangxi(chengchangxi@holomatic.com)
 * @date 2021-03-31
 */

#include <glog/logging.h>
#include <holo/core/epsilon.h>
#include <holo/localization/vision/vslam/semantic/hungarian_optimizer.h>

#include <cmath>

// @todo let's remove this MACRO from original code once it is fixed
#define CHECK_FOR_INF  ///< Flag about if inf checking is needed

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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const HungarianOptimizer::TDtype HungarianOptimizer::INF_VALUE_FACTOR = static_cast<TDtype>(10);
const HungarianOptimizer::TDtype HungarianOptimizer::DIST_INF_VALUE   = std::numeric_limits<TDtype>::infinity();
const HungarianOptimizer::TAtype HungarianOptimizer::UNASSIGNED_VALUE = static_cast<TAtype>(-1);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<HungarianOptimizer::TAtype>
HungarianOptimizer::FindOptimalAssignment(const numerics::MatrixXT<TDtype>& dist_matrix_in, TMethod method)
{
    // input arguments check
    num_rows_ = dist_matrix_in.GetRows();
    num_cols_ = dist_matrix_in.GetCols();

    if (num_rows_ == 0U || num_cols_ == 0U)
    {
        throw std::runtime_error("invalid distance matrix for hungarian");
    }
    for (DimType i = 0U; i < num_rows_; i++)
    {
        for (DimType j = 0U; j < num_cols_; j++)
        {
            TDtype value = dist_matrix_in(i, j);

            if (value < static_cast<TDtype>(0))
            {
                throw std::runtime_error("all matrix elements have to be non-negative");
            }
        }
    }

    // Output arguments initialization
    assignment_ = std::vector<TAtype>(num_rows_, UNASSIGNED_VALUE);

    switch (method)
    {
        case TMethod::DEFAULT_ASSIGNMENT:
            AssignOptimal(dist_matrix_in);
            break;
        case TMethod::MANY_FORBIDDEN_ASSIGNMENT:
            AssignSubOptimalV1(dist_matrix_in);
            break;
        case TMethod::WITHOUT_FORBIDDEN_ASSIGNMENT:
            AssignSubOptimalV2(dist_matrix_in);
            break;
    }

    return assignment_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HungarianOptimizer::TDtype HungarianOptimizer::AssignOptimal(const numerics::MatrixXT<TDtype>& dist_matrix_in)
{
    InitDistMatrix(dist_matrix_in);
#ifdef CHECK_FOR_INF
    TDtype max_finite_value;
    bool_t infinite_value_found = FindMaxFiniteValueInDistMatrix(max_finite_value);

    if (infinite_value_found)
    {
        // all elements are infinite
        // if (max_finite_value == -1)
        if (fabs(max_finite_value + 1) < EpsilonT<TDtype>::value)
        {
            return static_cast<TDtype>(0);
        }
        ReplaceInfiniteValueInDistMatrix(max_finite_value);
    }
#endif
    covered_columns_ = std::vector<bool_t>(num_cols_, false);
    covered_rows_    = std::vector<bool_t>(num_rows_, false);
    star_matrix_     = std::vector<std::vector<bool_t>>(num_rows_, std::vector<bool_t>(num_cols_, false));
    prime_matrix_    = std::vector<std::vector<bool_t>>(num_rows_, std::vector<bool_t>(num_cols_, false));
    new_star_matrix_ = std::vector<std::vector<bool_t>>(num_rows_, std::vector<bool_t>(num_cols_, false));
    // preliminary steps
    if (num_rows_ <= num_cols_)
    {
        min_dim_ = num_rows_;
        SubtractMinValueEachRow();
        CoverColumnZeros();
    }
    else
    {
        min_dim_ = num_cols_;
        SubtractMinValueEachColumn();
        CoverRowZeros();
        covered_rows_ = std::vector<bool_t>(num_rows_, false);
    }
    // move to step 2b
    Step2b();

    // compute cost and remove invalid assignment_s
    return ComputeAssignmentCost(dist_matrix_in);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::InitDistMatrix(const numerics::MatrixXT<TDtype>& dist_matrix_in)
{
    dist_matrix_.Resize(num_rows_, num_cols_);
    dist_matrix_ = dist_matrix_in;  // dist_matrix_ will be modified later.

    // for (DimType i = 0U; i < num_rows_; i++)
    // {
    //     for (DimType j = 0U; j < num_cols_; j++)
    //     {
    //         TDtype value = dist_matrix_in(i, j);

    //         if (value < static_cast<TDtype>(0))
    //         {
    //             LOG(ERROR) << "All matrix elements have to be non-negative.";
    //             value = DIST_INF_VALUE;
    //         }

    //         dist_matrix_(i, j) = value;  // dist_matrix_ will be modified later
    //     }
    // }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t HungarianOptimizer::FindMaxFiniteValueInDistMatrix(TDtype& max_finite_value)
{
    max_finite_value            = -1;
    bool_t infinite_value_found = false;

    for (DimType row = 0U; row < num_rows_; row++)
    {
        for (DimType col = 0U; col < num_cols_; col++)
        {
            TDtype value = dist_matrix_(row, col);

            if (IsFinite(value))
            {
                if (value > max_finite_value)
                {
                    max_finite_value = value;
                }
            }
            else
            {
                infinite_value_found = true;
            }
        }
    }

    return infinite_value_found;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::ReplaceInfiniteValueInDistMatrix(const TDtype max_finite_value)
{
    // set all infinite elements to big finite value
    TDtype inf_value;
    if (max_finite_value > static_cast<TDtype>(1e-3))
    {
        inf_value = INF_VALUE_FACTOR * max_finite_value * num_rows_ * num_cols_;
    }
    else
    {
        inf_value = INF_VALUE_FACTOR;
    }

    for (DimType row = 0U; row < num_rows_; row++)
    {
        for (DimType col = 0U; col < num_cols_; col++)
        {
            if (std::isinf(dist_matrix_(row, col)))
            {
                dist_matrix_(row, col) = inf_value;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::SubtractMinValueEachRow()
{
    TDtype min_value;
    for (DimType row = 0U; row < num_rows_; row++)
    {
        // find the smallest element in the row
        min_value = dist_matrix_(row, 0U);

        for (DimType col = 1U; col < num_cols_; col++)
        {
            TDtype value = dist_matrix_(row, col);

            if (value < min_value)
            {
                min_value = value;
            }
        }

        // subtract the smallest element from each element of the row
        // dist_matrix_.GetRow(row) -= holo::VectorXT<TDtype>::Constant(num_cols_, min_value).Transpose();
        MatrixBlockType added_block = MatrixBlockType::Constant(1, num_cols_, -min_value);
        AddBlockToMatrix(added_block, row, 0, 1, num_cols_, dist_matrix_);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::CoverColumnZeros()
{
    // steps 1 and 2a
    for (DimType row = 0U; row < num_rows_; row++)
    {
        for (DimType col = 0U; col < num_cols_; col++)
        {
            if (dist_matrix_(row, col) < EpsilonT<TDtype>::value)
            {
                if (covered_columns_[col] == false)
                {
                    star_matrix_[row][col] = true;
                    covered_columns_[col]  = true;
                    break;
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::SubtractMinValueEachColumn()
{
    TDtype min_value;
    for (DimType col = 0U; col < num_cols_; col++)
    {
        // find the smallest element in the column
        min_value = dist_matrix_(0, col);

        for (DimType row = 1U; row < num_rows_; row++)
        {
            TDtype value = dist_matrix_(row, col);

            if (value < min_value)
            {
                min_value = value;
            }
        }

        // subtract the smallest element from each element of the column
        // dist_matrix_.GetCol(col) -= holo::VectorXT<TDtype>::Constant(num_rows_, min_value);
        MatrixBlockType added_block = MatrixBlockType::Constant(num_rows_, 1, -min_value);
        AddBlockToMatrix(added_block, 0, col, num_rows_, 1, dist_matrix_);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::CoverRowZeros()
{
    // Steps 1 and 2a
    for (DimType col = 0U; col < num_cols_; col++)
    {
        for (DimType row = 0U; row < num_rows_; row++)
        {
            if (dist_matrix_(row, col) < EpsilonT<TDtype>::value)
            {
                if (covered_rows_[row] == false)
                {
                    star_matrix_[row][col] = true;
                    covered_columns_[col]  = true;
                    covered_rows_[row]     = true;
                    break;
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::BuildAssignmentVector()
{
    for (DimType row = 0U; row < num_rows_; row++)
    {
        for (DimType col = 0U; col < num_cols_; col++)
        {
            if (star_matrix_[row][col])
            {
                assignment_[row] = col;
                // LOG(ERROR) << "row and col num  " << num_rows_ << "  " << num_cols_;
                // LOG(ERROR) << col;
                break;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HungarianOptimizer::TDtype
HungarianOptimizer::ComputeAssignmentCost(const holo::numerics::MatrixXT<TDtype>& dist_matrix)
{
    // LOG(INFO) << "final";
    // LOG(INFO) << "\n" << dist_matrix_;
    TDtype cost = static_cast<TDtype>(0);

    for (DimType row = 0U; row < num_rows_; row++)
    {
        TAtype col = assignment_[row];

        if (col >= static_cast<TAtype>(0))
        {
#ifdef CHECK_FOR_INF
            TDtype value = dist_matrix(row, col);

            if (IsFinite(value))
            {
                cost += value;
            }
            else
            {
                assignment_[row] = UNASSIGNED_VALUE;
            }

#else
            cost += dist_matrix(row, col);
#endif
        }
    }
    return cost;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::Step2a()
{
    // cover every column containing a starred zero
    for (DimType col = 0U; col < num_cols_; col++)
    {
        for (DimType row = 0U; row < num_rows_; row++)
        {
            if (star_matrix_[row][col])
            {
                covered_columns_[col] = true;
                break;
            }
        }
    }

    // move to step 3
    Step2b();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::Step2b()
{
    // count covered columns
    DimType num_covered_cols = 0U;

    for (DimType col = 0U; col < num_cols_; col++)
    {
        if (covered_columns_[col])
        {
            num_covered_cols++;
        }
    }

    if (num_covered_cols == min_dim_)
    {
        // algorithm finished
        // LOG(ERROR) << "min_dim  " << min_dim_ << "  num covered cols " << num_covered_cols;
        BuildAssignmentVector();
    }
    else
    {
        // move to step 3
        Step3();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::Step3()
{
    bool_t  zeros_found = true;
    DimType star_col;

    while (zeros_found)
    {
        zeros_found = false;

        for (DimType col = 0U; col < num_cols_; col++)
        {
            if (covered_columns_[col] == false)
            {
                for (DimType row = 0U; row < num_rows_; row++)
                {
                    if (((covered_rows_[row] == false) && (dist_matrix_(row, col) < EpsilonT<TDtype>::value)))
                    {
                        // prime zero
                        prime_matrix_[row][col] = true;

                        // find starred zero in current row
                        for (star_col = 0U; star_col < num_cols_; star_col++)
                        {
                            if (star_matrix_[row][star_col])
                            {
                                break;
                            }
                        }

                        // no starred zero found
                        if (star_col == num_cols_)
                        {
                            // move to step 4
                            Step4(row, col);
                            return;
                        }
                        else
                        {
                            covered_rows_[row]         = true;
                            covered_columns_[star_col] = false;
                            zeros_found                = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    // move to step 5
    Step5();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::Step4(const DimType row, const DimType col)
{
    DimType star_row, star_col, prime_row, prime_col;

    // generate temporary copy of start_matrix
    new_star_matrix_ = star_matrix_;

    // star current zero
    new_star_matrix_[row][col] = true;

    // find starred zero in current column
    star_col = col;

    for (star_row = 0U; star_row < num_rows_; star_row++)
    {
        if (star_matrix_[star_row][star_col])
        {
            break;
        }
    }

    while (star_row < num_rows_)
    {
        // unstar the starred zero
        new_star_matrix_[star_row][star_col] = false;

        // find primed zero in current row
        prime_row = star_row;

        for (prime_col = 0U; prime_col < num_cols_; prime_col++)
        {
            if (prime_matrix_[prime_row][prime_col])
            {
                break;
            }
        }

        // star the primed zero
        new_star_matrix_[prime_row][prime_col] = true;

        // find starred zero in current column
        star_col = prime_col;

        for (star_row = 0U; star_row < num_rows_; star_row++)
        {
            if (star_matrix_[star_row][star_col])
            {
                break;
            }
        }
    }

    // use temporary copy as new start_matrix
    // delete all primes, uncover all rows
    prime_matrix_ = std::vector<std::vector<bool_t>>(num_rows_, std::vector<bool_t>(num_cols_, false));
    star_matrix_  = new_star_matrix_;
    covered_rows_ = std::vector<bool_t>(num_rows_, false);

    // move to step 2a
    Step2a();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::Step5()
{
    // find smallest uncovered element h
    TDtype h = static_cast<TDtype>(1e10);

    for (DimType row = 0U; row < num_rows_; row++)
    {
        if (covered_rows_[row] == false)
        {
            for (DimType col = 0U; col < num_cols_; col++)
            {
                if (covered_columns_[col] == false)
                {
                    TDtype value = dist_matrix_(row, col);

                    if (value < h)
                    {
                        h = value;
                    }
                }
            }
        }
    }

    // if (h == 1e10)
    // {
    //     for (row = 0U; row < num_rows_; row++)
    //     {
    //         if (covered_rows_[row] == false)
    //         {
    //             for (col = 0U; col < num_cols_; col++)
    //             {
    //                 if (covered_columns_[col] == false)
    //                 {
    //                     TDtype value = dist_matrix_(row, col);
    //                 }
    //             }
    //         }
    //     }
    // }

    // add h to each covered row
    for (DimType row = 0U; row < num_rows_; row++)
    {
        if (covered_rows_[row])
        {
            // dist_matrix_.GetRow(row) += holo::VectorXT<TDtype>::Constant(num_cols_, h).Transpose();
            MatrixBlockType added_block = MatrixBlockType::Constant(1, num_cols_, h);
            AddBlockToMatrix(added_block, row, 0, 1, num_cols_, dist_matrix_);
        }
    }

    // subtract h from each uncovered column
    for (DimType col = 0U; col < num_cols_; col++)
    {
        if (covered_columns_[col] == false)
        {
            // dist_matrix_.GetCol(col) -= holo::VectorXT<TDtype>::Constant(num_rows_, h);
            MatrixBlockType added_block = MatrixBlockType::Constant(num_rows_, 1, -h);
            AddBlockToMatrix(added_block, 0, col, num_rows_, 1, dist_matrix_);
        }
    }

    // move to step 3
    Step3();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool HungarianOptimizer::IsFinite(const TDtype value)
{
    return (std::isfinite(value));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::AddBlockToMatrix(const MatrixBlockType& added_block, const DimType i, const DimType j,
                                          const DimType rows, const DimType cols, numerics::MatrixXT<TDtype>& matrix)
{
    MatrixBlockType block = matrix.GetBlock(i, j, rows, cols);
    block += added_block;
    matrix.SetBlock(i, j, block);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HungarianOptimizer::TDtype HungarianOptimizer::AssignSubOptimalV1(const numerics::MatrixXT<TDtype>& dist_matrix_in)
{
    suboptimal_cost_ = static_cast<TDtype>(0);

    // make working copy of distance matrix
    InitDistMatrix(dist_matrix_in);

    // compute number of validations
    num_observations_                   = std::vector<int>(num_rows_, 0);
    num_tracks_                         = std::vector<int>(num_cols_, 0);
    std::vector<bool_t> is_value_found_ = std::vector<bool_t>(2, false);  // [finite_value, infinite_value];
    ComputeNumOfValidation(is_value_found_);

    bool_t finite_value_found   = is_value_found_[0];
    bool_t infinite_value_found = is_value_found_[1];

    if (infinite_value_found)
    {
        if (!finite_value_found)
        {
            return static_cast<TDtype>(0);
        }

        bool repeat_steps = true;
        while (repeat_steps)
        {
            repeat_steps = false;
            AssignSingleValidObservation(repeat_steps);
            AssignSingleValidTrack(repeat_steps);
        }
        ChooseMinDistanceObservation();
        ChooseMinDistanceTrack();
    }
    FindMinAndAssign();

    return suboptimal_cost_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HungarianOptimizer::TDtype HungarianOptimizer::AssignSubOptimalV2(const numerics::MatrixXT<TDtype>& dist_matrix_in)
{
    suboptimal_cost_ = static_cast<TDtype>(0);

    // make working copy of distance Matrix
    InitDistMatrix(dist_matrix_in);

    // recursively search for the minimum element and do the assignment
    FindMinAndAssign();

    return suboptimal_cost_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::ComputeNumOfValidation(std::vector<bool_t>& is_value_found_)
{
    for (DimType row = 0U; row < num_rows_; row++)
    {
        for (DimType col = 0U; col < num_cols_; col++)
        {
            if (IsFinite(dist_matrix_(row, col)))
            {
                num_observations_[row] += 1;
                num_tracks_[col] += 1;

                is_value_found_[0] = true;  // finite value found
            }
            else
            {
                is_value_found_[1] = true;  // infinite_value_found
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::AssignSingleValidObservation(bool_t& repeat_steps)
{
    for (size_t col = 0U; col < num_cols_; col++)
    {
        bool_t single_validation_found = false;
        for (size_t row = 0U; row < num_rows_; row++)
        {
            if (IsFinite(dist_matrix_(row, col)) && (1 == num_observations_[row]))
            {
                single_validation_found = true;
                break;
            }

            if (single_validation_found)
            {
                for (size_t row = 0U; row < num_rows_; row++)
                    if ((num_observations_[row] > 1) && IsFinite(dist_matrix_(row, col)))
                    {
                        dist_matrix_(row, col) = DIST_INF_VALUE;
                        num_observations_[row] -= 1;
                        num_tracks_[col] -= 1;
                        repeat_steps = true;
                    }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::AssignSingleValidTrack(bool_t& repeat_steps)
{
    if (num_cols_ > 1)
    {
        for (size_t row = 0U; row < num_rows_; row++)
        {
            bool_t single_validation_found = false;
            for (size_t col = 0U; col < num_cols_; col++)
            {
                if (IsFinite(dist_matrix_(row, col)) && (1 == num_tracks_[col]))
                {
                    single_validation_found = true;
                    break;
                }
            }

            if (single_validation_found)
            {
                for (size_t col = 0U; col < num_cols_; col++)
                {
                    if ((num_tracks_[col] > 1) && IsFinite(dist_matrix_(row, col)))
                    {
                        dist_matrix_(row, col) = DIST_INF_VALUE;
                        num_observations_[row] -= 1;
                        num_tracks_[col] -= 1;
                        repeat_steps = true;
                    }
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::ChooseMinDistanceObservation()
{
    for (size_t row = 0U; row < num_rows_; row++)
    {
        if (num_observations_[row] > 1)
        {
            bool_t all_singly_validated = true;
            TDtype minValue             = DIST_INF_VALUE;
            size_t tmpCol               = 0U;
            for (size_t col = 0U; col < num_cols_; col++)
            {
                const TDtype value = dist_matrix_(row, col);
                if (IsFinite(value))
                {
                    if (num_tracks_[col] > 1)
                    {
                        all_singly_validated = false;
                        break;
                    }
                    else if ((1 == num_tracks_[col]) && (value < minValue))
                    {
                        tmpCol   = col;
                        minValue = value;
                    }
                }
            }

            if (all_singly_validated)
            {
                assignment_[row] = static_cast<TAtype>(tmpCol);
                suboptimal_cost_ += minValue;
                for (size_t n = 0U; n < num_rows_; n++)
                {
                    dist_matrix_(n, tmpCol) = DIST_INF_VALUE;
                }
                for (size_t n = 0U; n < num_cols_; n++)
                {
                    dist_matrix_(row, n) = DIST_INF_VALUE;
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::ChooseMinDistanceTrack()
{
    for (size_t col = 0U; col < num_cols_; col++)
    {
        if (num_tracks_[col] > 1)
        {
            bool_t all_singly_validated = true;
            TDtype minValue             = DIST_INF_VALUE;
            size_t tmpRow               = 0U;
            for (size_t row = 0U; row < num_rows_; row++)
            {
                const TDtype value = dist_matrix_(row, col);
                if (IsFinite(value))
                {
                    if (num_observations_[row] > 1)
                    {
                        all_singly_validated = false;
                        break;
                    }
                    else if ((1 == num_observations_[row]) && (value < minValue))
                    {
                        tmpRow   = row;
                        minValue = value;
                    }
                }
            }

            if (all_singly_validated)
            {
                assignment_[tmpRow] = static_cast<TAtype>(col);
                suboptimal_cost_ += minValue;
                for (size_t n = 0U; n < num_rows_; n++)
                {
                    dist_matrix_(n, col) = DIST_INF_VALUE;
                }
                for (size_t n = 0U; n < num_cols_; n++)
                {
                    dist_matrix_(tmpRow, n) = DIST_INF_VALUE;
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HungarianOptimizer::FindMinAndAssign()
{
    for (;;)
    {
        // find minimum distance observation-to-track pair
        TDtype minValue = DIST_INF_VALUE;
        size_t tmpRow   = 0U;
        size_t tmpCol   = 0U;
        for (size_t row = 0U; row < num_rows_; row++)
        {
            for (size_t col = 0U; col < num_cols_; col++)
            {
                const TDtype value = dist_matrix_(row, col);
                if (IsFinite(value) && (value < minValue))
                {
                    minValue = value;
                    tmpRow   = row;
                    tmpCol   = col;
                }
            }
        }

        if (IsFinite(minValue))
        {
            assignment_[tmpRow] = static_cast<TAtype>(tmpCol);
            suboptimal_cost_ += minValue;
            for (size_t n = 0U; n < num_rows_; n++)
            {
                dist_matrix_(n, tmpCol) = DIST_INF_VALUE;
            }
            for (size_t n = 0U; n < num_cols_; n++)
            {
                dist_matrix_(tmpRow, n) = DIST_INF_VALUE;
            }
        }
        else
        {
            break;
        }
    }
}

}  // namespace semantic
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo