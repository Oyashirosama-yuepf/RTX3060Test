/*!
 *  \brief
 *  \author liwenjun (liwenjun@holomatic.ai)
 *  \date Jul 14, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _POLYNOMIAL_XD_H_
#define _POLYNOMIAL_XD_H_

#include <vector>

#include <holo/core/types.h>

namespace holo
{
namespace planning
{
/**
 * @brief      Data PolynomialXd.
 * @details    Polynomial a0 + a1 * x + a2 * x^2 + ... and maximum order is 5
 */
class PolynomialXd
{
public:
    PolynomialXd() = default;
    explicit PolynomialXd(const uint32_t order);
    explicit PolynomialXd(const std::vector<float64_t>& params);
    float64_t operator()(const float64_t value) const;
    float64_t operator[](const uint32_t index) const;
    void      SetParams(const std::vector<float64_t>& params);

    static PolynomialXd DerivedFrom(const PolynomialXd& base);

    uint32_t                      order() const;
    const std::vector<float64_t>& params() const;

private:
    std::vector<float64_t> params_;
};

}  // namespace planning
}  // namespace holo

#endif  // _POLYNOMIAL_XD_H_
