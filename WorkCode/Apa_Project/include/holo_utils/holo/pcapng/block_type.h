#ifndef HOLO_PCAPNG_BLOCK_TYPE_H_
#define HOLO_PCAPNG_BLOCK_TYPE_H_

#include <holo/core/types.h>

namespace holo
{
namespace pcapng
{
enum class BlockType : holo::uint32_t
{
    SHB = 0x0A0D0D0AU,
    IDB = 0x00000001U,
    EPB = 0x00000006U,
};

}  // namespace pcapng

}  // namespace holo

#endif
