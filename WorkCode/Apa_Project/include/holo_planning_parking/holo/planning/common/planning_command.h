/*!
 *  \brief
 *  \author Bu Dapeng (budapeng@holomatic.com)
 *  \date July 5, 2018
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_PLANNING_COMMAND_H_
#define _HOLO_PLANNING_PLANNING_COMMAND_H_

namespace holo
{
namespace planning
{

enum class PlanningCommand
{
    DISABLE_CONTROL = 0,
    ENABLE_CONTROL,
    PARK,
};

} // namespace planning
} // namespace holo

#endif
