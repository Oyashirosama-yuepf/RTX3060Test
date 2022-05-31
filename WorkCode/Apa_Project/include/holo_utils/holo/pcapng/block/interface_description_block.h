#ifndef HOLO_PCAPNG_BLOCK_INTERFACE_DESCRIPTION_BLOCK_H_
#define HOLO_PCAPNG_BLOCK_INTERFACE_DESCRIPTION_BLOCK_H_

#include <holo/core/types.h>
#include <holo/pcapng/block/block.h>
#include <holo/pcapng/block_type.h>
#include <holo/utils/tlv.h>
#include <vector>

namespace holo
{
namespace pcapng
{
class InterfaceDescriptionBlock : public Block
{
public:
    static constexpr holo::uint32_t TLV_BUFFER_SIZE{2048U};

    using TypeType   = holo::uint16_t;
    using LengthType = holo::uint16_t;

    template <holo::bool_t IsNetworkByteOrder = false>
    using TlvType = holo::utils::TlvT<TypeType, LengthType, IsNetworkByteOrder>;

    template <holo::bool_t IsNetworkByteOrder = false>
    using TlvSequenceType = holo::utils::TlvSequence<TlvType<IsNetworkByteOrder>>;

    InterfaceDescriptionBlock() noexcept;
    ~InterfaceDescriptionBlock() noexcept override = default;

    InterfaceDescriptionBlock(InterfaceDescriptionBlock const&) = default;
    InterfaceDescriptionBlock(InterfaceDescriptionBlock&&)      = default;
    InterfaceDescriptionBlock& operator=(InterfaceDescriptionBlock const&) = default;
    InterfaceDescriptionBlock& operator=(InterfaceDescriptionBlock&&) = default;

    void SetLinkType(holo::uint16_t const link_type) noexcept
    {
        link_type_ = link_type;
    }

    holo::uint16_t GetLinkType() const noexcept
    {
        return link_type_;
    }

    void SetSnapLen(holo::uint32_t const snap_len) noexcept
    {
        snap_len_ = snap_len;
    }

    holo::uint32_t GetSnapLen() const noexcept
    {
        return snap_len_;
    }

    holo::uint32_t GetTlvBufferSize() const noexcept
    {
        return tlv_buffer_.size();
    }

    void ResizeTlvBuffer(holo::uint32_t const size)
    {
        tlv_buffer_.resize(size);
    }

    template <holo::bool_t IsNetworkByteOrder = false>
    TlvSequenceType<IsNetworkByteOrder> GetTlvSequence() noexcept
    {
        return TlvSequenceType<IsNetworkByteOrder>{&tlv_buffer_[0U], tlv_buffer_.size()};
    }

    void WriteToStream(std::fstream& stream, holo::bool_t is_network_byte_order = false);
    void ReadFromStream(std::fstream& stream, holo::bool_t is_network_byte_order = false);
    void ReadHeaderFromStream(std::fstream& stream, holo::bool_t is_network_byte_order = false);
    void ReadTlvFromStream(std::fstream& stream, holo::bool_t is_network_byte_order = false);

private:
    holo::uint16_t             link_type_;
    holo::uint16_t             reserved_;
    holo::uint32_t             snap_len_;
    std::vector<holo::uint8_t> tlv_buffer_;
};

}  // namespace pcapng
}  // namespace holo

#endif
