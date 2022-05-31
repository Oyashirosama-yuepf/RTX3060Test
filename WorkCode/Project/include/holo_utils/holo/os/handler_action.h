#ifndef HOLO_OS_HANDLER_ACTION_H
#define HOLO_OS_HANDLER_ACTION_H

#include <holo/core/types.h>

namespace holo
{
namespace os
{
enum class HandlerAction : holo::int32_t
{
    CONTINUE = 0U,
    BREAK    = 1U,
};

}  // namespace os
}  // namespace holo

#endif
