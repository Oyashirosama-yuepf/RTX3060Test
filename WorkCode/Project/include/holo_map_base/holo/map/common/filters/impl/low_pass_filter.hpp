/*!
 * \brief Low pass filter
 * \author Yuchao Hu (huyuchao@holomatic.com)
 * \date 2019-02-25
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/core/types.h>
// #include <holo/numerics/common.h>
#include <cmath>

namespace holo
{
namespace map
{
template <typename T>
LowPassFilter<T>::LowPassFilter() : state_(0)
{
}

template <typename T>
void LowPassFilter<T>::Reset()
{
    state_ = 0;
}

template <typename T>
T LowPassFilter<T>::Update(const T _sample, const T _cutoff_frequency,
                           const T _delta_time)
{
    if (_cutoff_frequency <= 0 || _delta_time <= 0)
    {
        state_ = _sample;
        return state_;
    }

    const ::holo::float64_t b = 2.0 * M_PI * _cutoff_frequency * _delta_time;
    const ::holo::float64_t a = b / (1.0 + b);
    state_ = a * _sample + (1.0 - a) * state_;
    return state_;
}

template <typename T>
T LowPassFilter<T>::GetState() const
{
    return state_;
}

template <typename T>
void LowPassFilter<T>::SetState(const T _state)
{
    state_ = _state;
}

}  // namespace map
}  // namespace holo
