/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2017-09-06
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_UTIL_DEBUG_H_
#define _HOLO_PLANNING_UTIL_DEBUG_H_

#include <math.h>
#include <sstream>
#include <string>
#include <vector>

#include <holo/core/types.h>

namespace holo
{
namespace planning
{

template<typename T>
std::string PosString(const char* name, const T& p)
{
    std::stringstream ss;
    ss << "\n\t" << name << " " << p.x() << " " << p.y();
    return ss.str();
}

template<typename T>
std::string PathPosVecString(const char* name, const std::vector<T>& vec, uint32_t count)
{
    std::stringstream ss;
    ss << " " << name << ": \n";
    for (uint32_t i = 0; i < count && i < vec.size(); ++i)
    {
        ss << "\t" << i << " " << vec[i].point().x() << " " << vec[i].point().y() << "\n";
    }
    return ss.str();
}

template<typename T>
std::string PosVecString(const char* name, const std::vector<T>& vec, uint32_t count)
{
    std::stringstream ss;
    ss << " " << name << ": \n";
    for (uint32_t i = 0; i < count && i < vec.size(); ++i)
    {
        ss << "\t" << i << " " << vec[i].x() << " " << vec[i].y() << "\n";
    }
    return ss.str();
}

template<typename T>
std::string AngleStr(const char* name, const T& p)
{
    std::stringstream ss;
    ss << "\n\t" << name << " " << (p * 180 / M_PI);
    return ss.str();
}

template<typename T>
std::string NumStr(const char* name, T p)
{
    std::stringstream ss;
    ss << "\n\t" << name << " " << p;
    return ss.str();
}

template<typename T>
std::string NumStr2(const char* name, T p)
{
    std::stringstream ss;
    ss << " " << name << " " << p;
    return ss.str();
}

}
}

#define NUMSTR(variate) holo::planning::NumStr(#variate, variate)
#define NUMSTR2(variate) holo::planning::NumStr2(#variate, variate)
#define ANGLESTR(variate) holo::planning::AngleStr(#variate, variate)
#define POSSTR(variate) holo::planning::PosString(#variate, variate)
#define PATHPOSVECSTR(variate, num) holo::planning::PathPosVecString(#variate, variate, num)
#define POSVECSTR(variate, num) holo::planning::PosVecString(#variate, variate, num)

#endif
