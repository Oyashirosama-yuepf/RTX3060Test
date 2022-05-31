/*!
 * \brief Gaussian filter
 * \author Yuchao Hu (huyuchao@holomatic.com)
 * \date 2019-07-19
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <cmath>
#include <vector>

#include <holo/log/hololog.h>

#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>


namespace holo
{
namespace map
{
template <typename T>
GaussianFilter<T>::GaussianFilter(const T _half_window_length, const T _sigma)
  : half_window_length_(_half_window_length), sigma_(_sigma)
{
}

template <typename T>
bool GaussianFilter<T>::Filter(const ::std::vector<T>& _x,
                               const ::std::vector<T>& _t,
                               ::std::vector<T>& _result)
{
    _result.clear();

    if (_x.size() != _t.size())
    {
        LOG(WARNING) << "The signal's size, which is " << _x.size()
                     << ", and the time's size, which is " << _t.size()
                     << ", are not same.";
        return false;
    }
    if (::std::fabs(sigma_) < 1e-3)
    {
        LOG(WARNING) << "Sigma, which is " << sigma_ << ", is too small.";
        return false;
    }

    const T c = 1.0 / (::std::sqrt(2 * M_PI) * sigma_);
    const T d = -1.0 / (2 * sigma_ * sigma_);
    auto func_g = [c, d](const T _x) { return c * ::std::exp(d * _x * _x); };

    _result.reserve(_t.size());
    for (::std::size_t i = 0; i < _x.size(); ++i)
    {
        T sum = 0;
        T sum_g = 0;
        for (::std::size_t j = i; j >= 0; --j)
        {
            if ((_t.at(i) - _t.at(j)) <= half_window_length_)
            {
                const T g = func_g(_t.at(j) - _t.at(i));
                sum_g += g;
                sum += g * _x.at(j);
            }
            else
            {
                break;
            }
            if (0 == j)
            {
                break;
            }
        }
        for (::std::size_t j = i + 1; j < _t.size(); ++j)
        {
            if (_t.at(j) - _t.at(i) < half_window_length_)
            {
                const T g = func_g(_t.at(j) - _t.at(i));
                sum_g += g;
                sum += g * _x.at(j);
            }
            else
            {
                break;
            }
        }
        _result.push_back(sum / sum_g);
    }
    return true;
}
}  // namespace map
}  // namespace holo
