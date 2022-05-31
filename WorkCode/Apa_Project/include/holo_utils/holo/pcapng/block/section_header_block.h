#ifndef HOLO_PCAPNG_BLOCK_SECTION_HEADER_BLOCK_H_
#define HOLO_PCAPNG_BLOCK_SECTION_HEADER_BLOCK_H_

#include <holo/core/types.h>
#include <holo/pcapng/block/block.h>
#include <holo/pcapng/block_type.h>
#include <holo/utils/tlv.h>
#include <vector>

namespace holo
{
namespace pcapng
{
class SectionHeaderBlock : public Block
{
public:
    static constexpr holo::uint32_t BYTE_ORDER_MAGIC{0x1A2B3C4DU};
    static constexpr holo::uint32_t TLV_BUFFER_SIZE{2048U};

    using TypeType   = holo::uint16_t;
    using LengthType = holo::uint16_t;

    template <holo::bool_t IsNetworkByteOrder = false>
    using TlvType = holo::utils::TlvT<TypeType, LengthType, IsNetworkByteOrder>;

    template <holo::bool_t IsNetworkByteOrder = false>
    using TlvSequenceType = holo::utils::TlvSequence<TlvType<IsNetworkByteOrder>>;

    SectionHeaderBlock() noexcept;
    ~SectionHeaderBlock() noexcept override = default;

    SectionHeaderBlock(SectionHeaderBlock const&) = default;
    SectionHeaderBlock(SectionHeaderBlock&&)      = default;
    SectionHeaderBlock& operator=(SectionHeaderBlock const&) = default;
    SectionHeaderBlock& operator=(SectionHeaderBlock&&) = default;

    holo::uint32_t GetByteOrder() const noexcept
    {
        return byte_order_magic_;
    }

    void SetMajorVersion(holo::uint16_t const version) noexcept
    {
        major_version_ = version;
    }

    holo::uint16_t GetMajorVersion() const noexcept
    {
        return major_version_;
    }

    void SetMinorVersion(holo::uint16_t const version) noexcept
    {
        minor_version_ = version;
    }

    holo::uint16_t GetMinorVersion() const noexcept
    {
        return minor_version_;
    }

    void SetSectionLength(holo::int64_t const length) noexcept
    {
        section_length_ = length;
    }

    holo::int64_t GetSectionLength() const noexcept
    {
        return section_length_;
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
    void ReadFromStream(std::fstream& stream);
    void ReadHeaderFromStream(std::fstream& stream);
    void ReadTlvFromStream(std::fstream& stream);

private:
    holo::uint32_t             byte_order_magic_;
    holo::uint16_t             major_version_;
    holo::uint16_t             minor_version_;
    holo::int64_t              section_length_;
    std::vector<holo::uint8_t> tlv_buffer_;
};

}  // namespace pcapng
}  // namespace holo

#endif
