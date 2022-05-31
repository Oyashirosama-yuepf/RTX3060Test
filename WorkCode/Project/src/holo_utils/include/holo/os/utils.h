#ifndef HOLO_OS_UTILS_H
#define HOLO_OS_UTILS_H

#include <holo/core/types.h>

namespace holo
{
namespace os
{
class Utils
{
public:
    static holo::int32_t GetTid();
    static holo::int32_t GetPid();
    static holo::int32_t GetPpid();
};
}  // namespace os
}  // namespace holo

#endif
