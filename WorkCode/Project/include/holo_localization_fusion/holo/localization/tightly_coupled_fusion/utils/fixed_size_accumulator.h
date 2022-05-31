/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fixed_size_accumulator.h
 * @brief This file aims to define the FixedSizeAccumulator class which will is used to accumulate the value and get the
 * mean and covariance.
 * @author Lei Gehang(leigehang@holomatic.com)
 * @date Feb 19, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_FIXED_SIZE_ACCUMULATOR_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_FIXED_SIZE_ACCUMULATOR_H_

#include <holo/container/deque.h>
#include <holo/localization/common/types.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
/**
 * @addtogroup utils
 * @{
 *
 */

/**
 * @brief The Sqrt functor
 * @note The template type must has the function "Sqrt()" to get its square root
 *
 * @tparam T The template type
 */
template <typename T>
class SqrtFunctor
{
public:
    T operator()(T const& value) const
    {
        return value.template Sqrt();
    }
};

/**
 * @brief The class specialization of the Sqrt functor for Scalar type.
 *
 */
template <>
class SqrtFunctor<Scalar>
{
public:
    Scalar operator()(Scalar const& value) const
    {
        return std::sqrt(value);
    }
};

/**
 * @brief This class is used to accumulate the value and get the mean and covariance.
 * It maintains a fixed size buffer internally. We will update the buffer every time when data is added, and
 * calculates the corresponding mean and variance.
 *
 * @tparam T the data type. Attention! The T should supports operation: T * T; T / size_t; T - T; T + T. And the T must
 * has the function Sqrt() to get its square root.
 * @tparam N the fixed size
 */
template <typename T, size_t N>
class FixedSizeAccumulator
{
public:
    template <typename Type, size_t Number>
    using DequeType = holo::container::Deque<Type, Number>;

    /**
     * @brief Enable the default constructor
     *
     */
    FixedSizeAccumulator() : fixed_size_buffer_(), mean_(0.0), accumulation_(0.0)
    {
    }

    /**
     * @brief Add the value to the accumulator
     *
     * @param value The added value
     */
    void AddData(const T& value)
    {
        const size_t current_size = fixed_size_buffer_.size();

        /// Step 1: If the buffer is not full, We use the following method to calculate their mean and variance
        if (current_size < N)
        {
            /**
             * @formula For incremental data  E{n} : mean    F{n} : sum(x{i} - E{n})^2
             *  E{n} = E{n-1} + (x{n} - E{n-1}) / n
             *  F{n} = F{n-1} + (x{n} - E{n-1})(x{n} - E{n})
             *  Covariance = F{n}/(n-1)
             */
            /// The size will add 1 when the new data is added to the buffer
            const size_t updated_size = current_size + 1u;
            accumulation_ += 1.0 * (updated_size - 1u) / updated_size * (value - mean_) * (value - mean_);
            mean_ += (value - mean_) / updated_size;
        }
        else  ///< Step 2: Otherwise, we use the following method when the buffer is full.
        {
            /**
             * @formula For fixed size data  E{i:i+n-1} : The mean from the No.i to No.i+n-1 datas, totaling N datas.
             *                               F{i:i+n-1} : sum(x{i:i+n-1} -E{i:i+n-1})^2
             *   E{i+1:i+n} = E{i:i+n-1} - x{i}/n + x{i+n}/n
             *   F{i+1:i+n} = F{i:i+n-1} + -(x{i}-E{i:i+n-1})^2 + (x{i+n}- E{i:i+n-1})^2
             *                  + (E{i:i+n-1}-E{i+1:i+n})(x{i+n} - x{i})
             *   Covariance = F{i+1:i+n}/(n-1)
             */
            const T pre_mean = mean_;
            mean_            = pre_mean - 1.0 * fixed_size_buffer_.front() / N + 1.0 * value / N;
            accumulation_ += -(fixed_size_buffer_.front() - pre_mean) * (fixed_size_buffer_.front() - pre_mean) +
                             (value - pre_mean) * (value - pre_mean) +
                             (pre_mean - mean_) * (value - fixed_size_buffer_.front());

            fixed_size_buffer_.pop_front();  ///< Pop the front element for keep the size is N
        }
        /// Step 3: Add the new data to the buffer tail
        fixed_size_buffer_.push_back(value);
    }

    /**
     * @brief Get the Mean
     *
     * @return The mean value
     */
    T GetMean() const
    {
        return mean_;
    }

    /**
     * @brief Get the Covariance
     *
     * @return The covariance
     */
    T GetCovariance() const
    {
        return (fixed_size_buffer_.size() - 1u < 1u) ? T(0.0) : (accumulation_ / (fixed_size_buffer_.size() - 1u));
    }

    /**
     * @brief Get the Stdandard Deviation
     *
     * @return The Stdandard Deviation
     */
    T GetStdandardDeviation() const
    {
        return SqrtFunctor<T>()(this->GetCovariance());
    }

    /**
     * @brief Get the Buffer Size
     *
     * @return The buffer size
     */
    size_t GetBufferSize() const
    {
        return fixed_size_buffer_.size();
    }

    /**
     * @brief Reset the Accumulator. It will clear the buffer and reset the mean and covariane.
     *
     */
    void Reset()
    {
        fixed_size_buffer_.clear();
        mean_         = T(0.0);
        accumulation_ = T(0.0);
    }

private:
    DequeType<T, N> fixed_size_buffer_;  ///< The buffer to save the data
    T               mean_;               ///< The mean of the datas in the buffer
    T               accumulation_;       ///< The accumulation of sum(x_i - mean)^2 of the datas in the buffer
};

/**
 * @}
 *
 */
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_UTILS_FIXED_SIZE_ACCUMULATOR_H_
