#ifndef HOLO_NETWORK_COMMON_H
#define HOLO_NETWORK_COMMON_H

#include <holo/core/types.h>

namespace holo
{
namespace network
{
struct NetEvent
{
    static constexpr holo::int32_t READ{0x01};
    static constexpr holo::int32_t WRITE{0x04};
    static constexpr holo::int32_t ERROR{0x08};
};

}  // namespace network
}  // namespace holo
#endif
