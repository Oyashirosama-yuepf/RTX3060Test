/*!
 * \brief Gaussian filter
 * \author Yuchao Hu (huyuchao@holomatic.com)
 * \date 2019-07-19
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_MAP_FEATURE_FILTERS_GAUSSIAN_FILTER_H_
#define HOLO_MAP_FEATURE_FILTERS_GAUSSIAN_FILTER_H_

#include <vector>

namespace holo
{
namespace map
{
///
/// @brief Gaussian filter
///
/// @tparam T
///
template <typename T>
class GaussianFilter
{
public:
    GaussianFilter() = delete;
    GaussianFilter(const GaussianFilter&) = delete;
    GaussianFilter& operator=(const GaussianFilter&) = delete;

    ///
    /// @brief Constructor
    /// @tparam T
    /// @param[in] _half_window_length Half length of window
    /// @param[in] _sigma Sigma value of Gaussian distribution
    ///
    GaussianFilter(const T _half_window_length, const T _sigma);

    ~GaussianFilter() = default;

    ///
    /// @brief Filter
    /// @tparam T
    /// @param[in] _x A series of signal
    /// @param[in] _t A series of time
    /// @param[out] _result A series of filtered signal
    /// @return True if succeeded
    ///
    bool Filter(const ::std::vector<T>& _x, const ::std::vector<T>& _t,
                ::std::vector<T>& _result);

private:
    T half_window_length_;
    T sigma_;
};  // class GaussianFilter
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_FILTERS_GAUSSIAN_FILTER_H_
