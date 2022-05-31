/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2019-09-27
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_COMMAND_H_
#define _HOLO_PLANNING_COMMAND_H_

#include <holo/planning/common/headers.h>

namespace holo
{
namespace planning
{
/**
 * @brief      This enum keeps all the control active state value
 */
enum ACTIVATE_COMMAND
{
    AC_UNACTIVE        = 0,
    AC_INTEGRATED_MODE = 1,
    AC_SINGLE_MODE     = 2,
    AC_UNKNOWN         = 3,
};

struct Command
{
    uint32_t activate;  // activate command

    Command()
    {
        activate = AC_UNKNOWN;
    }
};

}  // namespace planning
}  // namespace holo
#endif