/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hungarian_optimizer.h
 * @brief This header file defines hungarian algorithmn.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2019-12-09"
 */

#ifndef HOLO_PERCEPTION_TRACKING_HUNGARIAN_OPTIMIZER_H_
#define HOLO_PERCEPTION_TRACKING_HUNGARIAN_OPTIMIZER_H_

#include <limits>
#include <vector>

#include <holo/core/types.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup tracking
 *
 * @{
 */

/**
 * @brief This class define hungarian algorithm
 *
 * @tparam TAtype data type of assignment vector
 * @tparam TDtype data type of distance matrix
 */
template <typename TAtype, typename TDtype>
class HungarianOptimizer
{
public:
    using DimType         = typename numerics::MatrixBaseT<TDtype, -1, -1>::RowSizeType;
    using MatrixBlockType = numerics::MatrixT<TDtype, -1, -1>;

    enum class TMethod
    {
        DEFAULT_ASSIGNMENT,
        MANY_FORBIDDEN_ASSIGNMENT,
        WITHOUT_FORBIDDEN_ASSIGNMENT
    };

    /**
     * @brief Compute optimal assignment based on dist_matrix.
     *
     * @param dist_matrix distance matrix, with shape NxM.
     * @return std::vector<TAtype> optimal assignment vector with shape Nx1.Vector value < 0 means not match, else value
     * means index of matched column.
     *
     * @throw std::runtime_error when receive invalid dist_matrix
     */
    std::vector<TAtype> FindOptimalAssignment(const numerics::MatrixXT<TDtype>& dist_matrix,
                                              TMethod                           method = TMethod::DEFAULT_ASSIGNMENT);

    /**
     * @brief get unassigned value
     *
     * @return const TAtype
     */
    static const TAtype GetUnassignedValue()
    {
        return UNASSIGNED_VALUE;
    }

    /**
     * @brief Get the Dist Inf Vale object
     *
     * @return const TDtype
     */
    static const TDtype GetDistInfVale()
    {
        return DIST_INF_VALUE;
    }

private:
    /**
     * @brief Act as a main function.
     *
     * @param dist_matrix distance matrix
     *
     * @return TDtype cost of optimal assignment
     */
    TDtype AssignOptimal(const numerics::MatrixXT<TDtype>& dist_matrix);
    /**
     * @brief Initilize dist_matrix_ by copy dist_matrix_in with data check
     *
     * @param dist_matrix_in input distance matrix
     */
    void InitDistMatrix(const numerics::MatrixXT<TDtype>& dist_matrix_in);

    /**
     * @brief Find max finite value in dist_matrix_
     *
     * @param max_finite_value max finite value in dist_matrix_
     * @return bool_t if there is infinity value in dist_matrix_
     */
    bool_t FindMaxFiniteValueInDistMatrix(TDtype& max_finite_value);

    /**
     * @brief set all infinite elements to big finite value in dist_matrix_
     *
     * @param max_finite_value max finite value in dist matrix
     */
    void ReplaceInfiniteValueInDistMatrix(const TDtype max_finite_value);

    /**
     * @brief Subtract minimal value for each row in dist_matrix_
     */
    void SubtractMinValueEachRow();

    /**
     * @brief cover zero for each column
     */
    void CoverColumnZeros();

    /**
     * @brief subtract minial value for each column in dist_matrix_
     */
    void SubtractMinValueEachColumn();

    /**
     * @brief cover zero for each row
     */
    void CoverRowZeros();

    /**
     * @brief build optimal assignment vector.
     */
    void BuildAssignmentVector();

    /**
     * @brief compute assignment cost
     *
     * @param dist_matrix distance matrix
     *
     * @return TDtype cost of current assignment cost
     */
    TDtype ComputeAssignmentCost(const numerics::MatrixXT<TDtype>& dist_matrix);

    /**
     * @brief cover every column containing a star zero. Following steps are used in optimal assignment searching.
     * @todo need reference
     */
    void Step2a();

    /**
     * @brief count covered columns and determine whether algorithm is finished.
     * @todo need reference
     */
    void Step2b();

    /**
     * @brief find zeros in uncovered elements.
     * @todo need reference
     */
    void Step3();

    /**
     * @brief generate star matrix.
     * @todo need reference
     *
     * @param row row index
     * @param col column index
     */
    void Step4(const DimType row, const DimType col);

    /**
     * @brief find smallest uncovered element and adjust dist_matrix_
     * @todo need reference
     */
    void Step5();

    /**
     * @brief whether the input value is a finite number.
     *
     * @param value input value
     * @return bool_t true if value is a finite number else false.
     */
    bool_t IsFinite(const TDtype value);

    /**
     * @brief add a block to matrix
     *
     * @param added_block the block to be added
     * @param i start row of the block in the matrix
     * @param j start column of the block in the matrix
     * @param rows rows of the block
     * @param cols columns of the block
     * @param matrix the matrix
     */
    void AddBlockToMatrix(const MatrixBlockType& added_block, const DimType i, const DimType j, const DimType rows,
                          const DimType cols, numerics::MatrixXT<TDtype>& matrix);

    /**
     * @brief Computes a suboptimal solution. Good for cases with many forbidden assignments
     *
     * @param dist_matrix
     * @return TDtype cost of optimal assignment
     */
    TDtype AssignSubOptimalV1(const numerics::MatrixXT<TDtype>& dist_matrix);

    /**
     * @brief Computes a suboptimal solution. Good for cases without forbidden assignments
     *
     * @param dist_matrix
     * @return TDtype cost of optimal assignment
     */
    TDtype AssignSubOptimalV2(const numerics::MatrixXT<TDtype>& dist_matrix);

    /**
     * @brief compute number of validations observations and tracks
     *
     * @return std::vector<bool_t> is finite value and infinite value found or not
     */
    void ComputeNumOfValidation(std::vector<bool_t>& is_value_found);

    /**
     * @brief reject assignments of multiply validated tracks to singly validated observations
     *
     * @param repeat_steps repeat steps or not
     */
    void AssignSingleValidObservation(bool_t& repeat_steps);

    /**
     * @brief reject assignments of multiply validated observations to singly validated tracks
     *
     * @param repeat_steaps repeat steps or not
     */
    void AssignSingleValidTrack(bool_t& repeat_steps);

    /**
     * @brief for each multiply validated track that validates only with singly validated observations, choose the
     * observation with minimum distance
     *
     */
    void ChooseMinDistanceObservation();

    /**
     * @brief for each multiply validated observation that validates only with singly validated  track, choose the track
     * with minimum distance
     *
     */
    void ChooseMinDistanceTrack();

    /**
     * @brief recursively search for the minimum element and do the assignment
     *
     */
    void FindMinAndAssign();

private:
    std::vector<TAtype>              assignment_;
    numerics::MatrixXT<TDtype>       dist_matrix_;
    std::vector<std::vector<bool_t>> star_matrix_;
    std::vector<std::vector<bool_t>> new_star_matrix_;
    std::vector<std::vector<bool_t>> prime_matrix_;
    std::vector<bool_t>              covered_rows_;
    std::vector<bool_t>              covered_columns_;
    DimType                          num_rows_;
    DimType                          num_cols_;
    DimType                          min_dim_;
    std::vector<int>                 num_observations_;
    std::vector<int>                 num_tracks_;
    TDtype                           suboptimal_cost_;

    // static members
    static const TDtype INF_VALUE_FACTOR;  ///< a factor used to set all infinite elements to big finite value in
                                           ///< dist_matrix_
    static const TDtype DIST_INF_VALUE;    ///< numeric infinity value of dist_matrix_ data type
    static const TAtype UNASSIGNED_VALUE;  ///< a value indicate the object is not matched
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_HUNGARIAN_OPTIMIZER_H_
