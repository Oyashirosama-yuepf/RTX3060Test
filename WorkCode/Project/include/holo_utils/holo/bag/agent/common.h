#ifndef HOLO_BAG_AGENT_COMMON_H
#define HOLO_BAG_AGENT_COMMON_H

#include <holo/core/types.h>
#include <chrono>

namespace holo
{
namespace bag
{
namespace agent
{
// using DataSequenceType = holo::container::Vector<uint8_t, std::numeric_limits<size_t>::max()>;
// using DataSequenceType = holo::container::Vector<::holo::uint8_t, 1048576>;
using DataSequenceType = std::vector<holo::char_t>;
// using ClockType        = std::chrono::steady_clock;
// using ClockType = std::chrono::high_resolution_clock;
using ClockType = std::chrono::system_clock;

}  // namespace agent
}  // namespace bag
}  // namespace holo

#endif
