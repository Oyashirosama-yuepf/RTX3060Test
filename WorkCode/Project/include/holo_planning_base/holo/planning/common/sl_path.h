/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2018-01-18
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_SL_PATH_H_
#define _HOLO_PLANNING_SL_PATH_H_

#include <holo/core/types.h>

#include <algorithm>
#include <functional>
#include <vector>

namespace holo
{
namespace planning
{
class SLPoint
{
public:
    SLPoint(){};
    SLPoint(float64_t _s, float64_t _l)
    {
        s_ = _s;
        l_ = _l;
    }
    float64_t s() const
    {
        return s_;
    }
    void s(const float64_t _s)
    {
        s_ = _s;
    }
    float64_t l() const
    {
        return l_;
    }
    void l(const float64_t _l)
    {
        l_ = _l;
    }

private:
    float64_t s_;
    float64_t l_;
};

class SLPath
{
public:
    const std::vector<SLPoint>& point_list() const
    {
        return point_list_;
    }

    std::vector<SLPoint>& point_list()
    {
        return point_list_;
    }

    void point_list(const std::vector<SLPoint>& point_list)
    {
        std::function<bool(SLPoint const&, SLPoint const&)> SortByASC = [](SLPoint const& s1, SLPoint const& s2) {
            return s1.s() < s2.s();
        };

        point_list_.assign(point_list.begin(), point_list.end());
        std::sort(point_list_.begin(), point_list_.end(), SortByASC);
    }

    SLPoint NearestPoint(const float64_t s) const
    {
        float64_t min = std::numeric_limits<float64_t>::max();
        for (size_t i = 0; i < point_list_.size(); ++i)
        {
            if (fabs(point_list_[i].s() - s) < min)
            {
                min = fabs(point_list_[i].s() - s);
            }
            else
            {
                return point_list_[i - 1];
            }
        }
        return point_list_[point_list_.size() - 1];
    }

private:
    std::vector<SLPoint> point_list_;
};

}  // namespace planning
}  // namespace holo

#endif  //_HOLO_PLANNING_COMMON_H_