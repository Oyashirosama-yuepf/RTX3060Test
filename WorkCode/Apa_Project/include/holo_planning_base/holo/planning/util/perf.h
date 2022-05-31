/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2017-11-22
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_PERF_H_
#define _HOLO_PLANNING_PERF_H_

#include <chrono>
#include <string>

#include <holo/core/types.h>

#define ADD_PERF(desc) holo::planning::Perf perf(std::string(desc));
#define ADD_PERF2(desc, threshold) holo::planning::Perf perf(std::string(desc), threshold);

namespace holo
{
namespace planning
{

class Perf
{
public:
    Perf(const std::string& desc, float64_t threshold = 0.0);
    ~Perf();

private:
    std::string description_;
    std::chrono::duration<float64_t> threshold_;
    std::chrono::system_clock::time_point start_;
};

}
}

#endif