#ifndef HOLO_PCAPNG_BLOCK_BLOCK_H_
#define HOLO_PCAPNG_BLOCK_BLOCK_H_

#include <holo/core/endian.h>
#include <holo/core/types.h>
#include <holo/pcapng/block_type.h>
#include <holo/serialization/serialization.h>
#include <fstream>

namespace holo
{
namespace pcapng
{
class Block
{
public:
    explicit Block(BlockType type) noexcept : type_{type}, length_{0U}
    {
    }

    virtual ~Block() noexcept = default;

    BlockType GetType() const noexcept
    {
        return type_;
    }

    holo::uint32_t GetLength() const noexcept
    {
        return length_;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(static_cast<holo::uint32_t>(type_), length_);
    }

    void WriteToStream(std::fstream& stream, holo::bool_t is_network_byte_order = false)
    {
        if (!is_network_byte_order)
        {
            (void)stream.write(reinterpret_cast<holo::char_t*>(&type_), sizeof(type_));
            (void)stream.write(reinterpret_cast<holo::char_t*>(&length_), sizeof(length_));
        }
        else
        {
            holo::uint32_t type{holo::core::hton32(static_cast<holo::uint32_t>(type_))};
            holo::uint32_t length{holo::core::hton32(length_)};
            (void)stream.write(reinterpret_cast<holo::char_t*>(&type), sizeof(type));
            (void)stream.write(reinterpret_cast<holo::char_t*>(&length), sizeof(length));
        }
    }

    void ReadFromStream(std::fstream& stream, holo::bool_t is_network_byte_order = false)
    {
        (void)stream.read(reinterpret_cast<holo::char_t*>(&type_), sizeof(type_));
        (void)stream.read(reinterpret_cast<holo::char_t*>(&length_), sizeof(length_));

        if (is_network_byte_order)
        {
            holo::uint32_t type{holo::core::hton32(static_cast<holo::uint32_t>(type_))};
            type_   = static_cast<BlockType>(type);
            length_ = holo::core::hton32(length_);
        }
    }

    Block(Block const&) = default;
    Block(Block&&)      = default;
    Block& operator=(Block const&) = default;
    Block& operator=(Block&&) = default;

protected:
    void SetType(BlockType const type) noexcept
    {
        type_ = type;
    }

    void SetLength(holo::uint32_t const length) noexcept
    {
        length_ = length;
    }

private:
    BlockType      type_;
    holo::uint32_t length_;
};

}  // namespace pcapng
}  // namespace holo

#endif
