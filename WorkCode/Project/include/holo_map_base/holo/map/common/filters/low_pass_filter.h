/*!
 * \brief Low pass filter
 * \author Yuchao Hu (huyuchao@holomatic.com)
 * \date 2019-02-25
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_MAP_FEATURE_FILTERS_LOW_PASS_FILTER_H_
#define HOLO_MAP_FEATURE_FILTERS_LOW_PASS_FILTER_H_

namespace holo
{
namespace map
{
///
/// @brief Low pass filter
///
/// @tparam T
///
template <typename T>
class LowPassFilter
{
public:
    LowPassFilter(const LowPassFilter&) = delete;
    LowPassFilter& operator=(const LowPassFilter&) = delete;

    ///
    /// @brief Constructor
    ///
    LowPassFilter();

    ~LowPassFilter() = default;

    ///
    /// @brief Reset filter state
    ///
    /// @return Nothing
    ///
    void Reset();

    ///
    /// @brief Update
    ///
    /// @param[in] _sample
    /// @param[in] _cutoff_frequency
    /// @param[in] _delta_time
    /// @return State
    ///
    T Update(const T _sample, const T _cutoff_frequency, const T _delta_time);

    ///
    /// @brief Get state
    ///
    /// @return State
    ///
    T GetState() const;

    ///
    /// @brief Set state
    ///
    /// @return Nothing
    ///
    void SetState(const T _state);

private:
    T state_;
};  // class LowPassFilter
}  // namespace map
}  // namespace holo

#endif  //  HOLO_MAP_FEATURE_FILTERS_LOW_PASS_FILTER_H_
