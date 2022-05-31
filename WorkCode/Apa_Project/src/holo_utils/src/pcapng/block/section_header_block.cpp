#include <assert.h>
#include <holo/pcapng/block/section_header_block.h>

namespace holo
{
namespace pcapng
{
SectionHeaderBlock::SectionHeaderBlock() noexcept
  : Block{BlockType::SHB}
  , byte_order_magic_{BYTE_ORDER_MAGIC}
  , major_version_{0x01U}
  , minor_version_{0x00U}
  , section_length_{-1}
  , tlv_buffer_(TLV_BUFFER_SIZE, 0)
{
}

void SectionHeaderBlock::WriteToStream(std::fstream& stream, holo::bool_t is_network_byte_order)
{
    holo::uint32_t byte_order_magic{byte_order_magic_};
    holo::uint16_t major_version{major_version_};
    holo::uint16_t minor_version{minor_version_};
    holo::int64_t  section_length{section_length_};

    if (!is_network_byte_order)
    {
        size_t size{Block::GetSerializedSize<4U>()};
        size += holo::serialization::SerializedSize<4U>(byte_order_magic, major_version, minor_version, section_length);
        TlvSequenceType<false> tlv_sequence{&tlv_buffer_[0], tlv_buffer_.size()};
        size += tlv_sequence.GetSerializedSize<4U>();
        size += 4U;

        Block::SetLength(size);
        Block::WriteToStream(stream, is_network_byte_order);

        (void)stream.write(reinterpret_cast<holo::char_t*>(&byte_order_magic), sizeof(byte_order_magic));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&major_version), sizeof(major_version));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&minor_version), sizeof(minor_version));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&section_length), sizeof(section_length));
        (void)stream.write(reinterpret_cast<holo::char_t const*>(tlv_sequence.GetData()), tlv_sequence.GetLength());

        holo::uint32_t length{Block::GetLength()};
        (void)stream.write(reinterpret_cast<holo::char_t*>(&length), sizeof(length));
    }
    else
    {
        size_t size{Block::GetSerializedSize<4U>()};
        size += holo::serialization::SerializedSize<4U>(byte_order_magic, major_version, minor_version, section_length);
        TlvSequenceType<true> tlv_sequence{&tlv_buffer_[0], tlv_buffer_.size()};
        size += tlv_sequence.GetSerializedSize<4U>();
        size += 4U;

        Block::SetLength(size);
        Block::WriteToStream(stream, is_network_byte_order);

        byte_order_magic = holo::core::hton32(byte_order_magic);
        major_version    = holo::core::hton16(major_version);
        minor_version    = holo::core::hton16(minor_version);
        section_length   = holo::core::hton64(section_length);

        (void)stream.write(reinterpret_cast<holo::char_t*>(&byte_order_magic), sizeof(byte_order_magic));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&major_version), sizeof(major_version));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&minor_version), sizeof(minor_version));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&section_length), sizeof(section_length));
        (void)stream.write(reinterpret_cast<holo::char_t const*>(tlv_sequence.GetData()), tlv_sequence.GetLength());

        holo::uint32_t length{Block::GetLength()};
        length = holo::core::hton32(length);
        (void)stream.write(reinterpret_cast<holo::char_t*>(&length), sizeof(length));
    }
}

void SectionHeaderBlock::ReadFromStream(std::fstream& stream)
{
    holo::uint32_t block_type{0};
    holo::uint32_t block_length{0};
    (void)stream.read(reinterpret_cast<holo::char_t*>(&block_type), sizeof(block_type));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&block_length), sizeof(block_length));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&byte_order_magic_), sizeof(byte_order_magic_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&major_version_), sizeof(major_version_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&minor_version_), sizeof(minor_version_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&section_length_), sizeof(section_length_));

    if (BYTE_ORDER_MAGIC != byte_order_magic_)
    {
        block_type      = holo::core::hton32(block_type);
        block_length    = holo::core::hton32(block_length);
        major_version_  = holo::core::hton16(major_version_);
        minor_version_  = holo::core::hton16(minor_version_);
        section_length_ = holo::core::hton64(section_length_);
    }

    Block::SetType(static_cast<BlockType>(block_type));
    Block::SetLength(block_length);

    size_t fixed_size = holo::serialization::SerializedSize<4U>(
        block_type, block_length, byte_order_magic_, major_version_, minor_version_, section_length_, block_length);

    assert(block_length > fixed_size);
    holo::uint32_t tlv_length = block_length - fixed_size;

    if (tlv_length < tlv_buffer_.size())
    {
        tlv_buffer_.resize(tlv_length);
    }
    (void)stream.read(reinterpret_cast<holo::char_t*>(&tlv_buffer_[0]), tlv_length);
}

void SectionHeaderBlock::ReadHeaderFromStream(std::fstream& stream)
{
    holo::uint32_t block_type{0};
    holo::uint32_t block_length{0};
    (void)stream.read(reinterpret_cast<holo::char_t*>(&block_type), sizeof(block_type));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&block_length), sizeof(block_length));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&byte_order_magic_), sizeof(byte_order_magic_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&major_version_), sizeof(major_version_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&minor_version_), sizeof(minor_version_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&section_length_), sizeof(section_length_));

    if (BYTE_ORDER_MAGIC != byte_order_magic_)
    {
        block_type      = holo::core::hton32(block_type);
        block_length    = holo::core::hton32(block_length);
        major_version_  = holo::core::hton16(major_version_);
        minor_version_  = holo::core::hton16(minor_version_);
        section_length_ = holo::core::hton64(section_length_);
    }

    Block::SetType(static_cast<BlockType>(block_type));
    Block::SetLength(block_length);
}

void SectionHeaderBlock::ReadTlvFromStream(std::fstream& stream)
{
    holo::uint32_t block_length{Block::GetLength()};
    size_t         header_size{Block::GetSerializedSize<4U>()};
    header_size +=
        holo::serialization::SerializedSize<4U>(byte_order_magic_, major_version_, minor_version_, section_length_);

    assert(block_length > header_size);
    (void)stream.seekg(header_size, std::ios_base::cur);

    size_t length_size{holo::serialization::SerializedSize<4U>(block_length)};
    assert(block_length > header_size + length_size);
    holo::uint32_t tlv_length = block_length - header_size - length_size;

    if (tlv_length < tlv_buffer_.size())
    {
        tlv_buffer_.resize(tlv_length);
    }
    (void)stream.read(reinterpret_cast<holo::char_t*>(&tlv_buffer_[0]), tlv_length);
}

}  // namespace pcapng
}  // namespace holo
