#ifndef HOLO_PCAPNG_BLOCK_ENHANCED_PACKET_BLOCK_H_
#define HOLO_PCAPNG_BLOCK_ENHANCED_PACKET_BLOCK_H_

#include <holo/core/types.h>
#include <holo/pcapng/block/block.h>
#include <holo/pcapng/block_type.h>
#include <holo/utils/tlv.h>
#include <vector>

namespace holo
{
namespace pcapng
{
class EnhancedPacketBlock : public Block
{
public:
    static constexpr holo::uint32_t TLV_BUFFER_SIZE{2048U};

    using TypeType   = holo::uint16_t;
    using LengthType = holo::uint16_t;

    template <holo::bool_t IsNetworkByteOrder = false>
    using TlvType = holo::utils::TlvT<TypeType, LengthType, IsNetworkByteOrder>;

    template <holo::bool_t IsNetworkByteOrder = false>
    using TlvSequenceType = holo::utils::TlvSequence<TlvType<IsNetworkByteOrder>>;

    EnhancedPacketBlock() noexcept;
    ~EnhancedPacketBlock() noexcept override = default;

    EnhancedPacketBlock(EnhancedPacketBlock const&) = default;
    EnhancedPacketBlock(EnhancedPacketBlock&&)      = default;
    EnhancedPacketBlock& operator=(EnhancedPacketBlock const&) = default;
    EnhancedPacketBlock& operator=(EnhancedPacketBlock&&) = default;

    void SetInterfaceID(holo::uint32_t const id) noexcept
    {
        interface_id_ = id;
    }

    holo::uint32_t GetInterfaceID() const noexcept
    {
        return interface_id_;
    }

    void SetTimestamp(holo::uint64_t const& timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    holo::uint64_t GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    size_t GetCapturedPacketLength() const noexcept
    {
        return packet_data_.size();
    }

    holo::uint32_t GetOriginalPacketLength() const noexcept
    {
        return original_packet_length_;
    }

    std::vector<holo::char_t>& GetPacketDataReference() noexcept
    {
        return packet_data_;
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
    void ReadPacketDataFromStream(std::fstream& stream, holo::bool_t is_network_byte_order = false);
    void ReadTlvFromStream(std::fstream& stream, holo::bool_t is_network_byte_order = false);

private:
    holo::uint32_t             interface_id_;
    holo::uint64_t             timestamp_;
    holo::uint32_t             captured_packet_length_;
    holo::uint32_t             original_packet_length_;
    std::vector<holo::char_t>  packet_data_;
    std::vector<holo::uint8_t> tlv_buffer_;
};

}  // namespace pcapng
}  // namespace holo

#endif
