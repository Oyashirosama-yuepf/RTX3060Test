#ifndef HOLO_PCAPNG_OPEN_MODE_H_
#define HOLO_PCAPNG_OPEN_MODE_H_

#include <holo/core/types.h>

namespace holo
{
namespace pcapng
{
enum class OpenMode : holo::uint8_t
{
    TRUNC  = 0U,
    RETAIN = 1U,
};

}  // namespace pcapng

}  // namespace holo

#endif
