#include <assert.h>
#include <holo/pcapng/block/interface_description_block.h>

namespace holo
{
namespace pcapng
{
InterfaceDescriptionBlock::InterfaceDescriptionBlock() noexcept
  : Block{BlockType::IDB}, link_type_{0U}, reserved_{0U}, snap_len_{0U}, tlv_buffer_(TLV_BUFFER_SIZE, 0U)
{
}

void InterfaceDescriptionBlock::WriteToStream(std::fstream& stream, holo::bool_t is_network_byte_order)
{
    holo::uint16_t link_type{link_type_};
    holo::uint16_t reserved{reserved_};
    holo::uint32_t snap_len{snap_len_};

    if (!is_network_byte_order)
    {
        size_t size{Block::GetSerializedSize<4U>()};
        size += holo::serialization::SerializedSize<4U>(link_type, reserved, snap_len);
        TlvSequenceType<false> tlv_sequence{&tlv_buffer_[0], tlv_buffer_.size()};
        size += tlv_sequence.GetSerializedSize<4U>();
        size += 4U;

        Block::SetLength(size);
        Block::WriteToStream(stream, is_network_byte_order);

        (void)stream.write(reinterpret_cast<holo::char_t*>(&link_type), sizeof(link_type));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&reserved), sizeof(reserved));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&snap_len), sizeof(snap_len));
        (void)stream.write(reinterpret_cast<holo::char_t const*>(tlv_sequence.GetData()), tlv_sequence.GetLength());

        holo::uint32_t length{Block::GetLength()};
        (void)stream.write(reinterpret_cast<holo::char_t*>(&length), sizeof(length));
    }
    else
    {
        size_t size{Block::GetSerializedSize<4U>()};
        size += holo::serialization::SerializedSize<4U>(link_type, reserved, snap_len);
        TlvSequenceType<true> tlv_sequence{&tlv_buffer_[0], tlv_buffer_.size()};
        size += tlv_sequence.GetSerializedSize<4U>();
        size += 4U;

        Block::SetLength(size);
        Block::WriteToStream(stream, is_network_byte_order);

        link_type = holo::core::hton16(link_type);
        reserved  = holo::core::hton16(reserved);
        snap_len  = holo::core::hton32(snap_len);

        (void)stream.write(reinterpret_cast<holo::char_t*>(&link_type), sizeof(link_type));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&reserved), sizeof(reserved));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&snap_len), sizeof(snap_len));
        (void)stream.write(reinterpret_cast<holo::char_t const*>(tlv_sequence.GetData()), tlv_sequence.GetLength());

        holo::uint32_t length{Block::GetLength()};
        length = holo::core::hton32(length);
        (void)stream.write(reinterpret_cast<holo::char_t*>(&length), sizeof(length));
    }
}

void InterfaceDescriptionBlock::ReadFromStream(std::fstream& stream, holo::bool_t is_network_byte_order)
{
    Block::ReadFromStream(stream, is_network_byte_order);

    (void)stream.read(reinterpret_cast<holo::char_t*>(&link_type_), sizeof(link_type_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&reserved_), sizeof(reserved_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&snap_len_), sizeof(snap_len_));

    if (is_network_byte_order)
    {
        link_type_ = holo::core::hton16(link_type_);
        reserved_  = holo::core::hton16(reserved_);
        snap_len_  = holo::core::hton32(snap_len_);
    }

    holo::uint32_t block_length{Block::GetLength()};
    size_t         fixed_size{Block::GetSerializedSize<4U>()};
    fixed_size += holo::serialization::SerializedSize<4U>(link_type_, reserved_, snap_len_, block_length);

    assert(block_length > fixed_size);
    holo::uint32_t tlv_length = block_length - fixed_size;

    if (tlv_length > tlv_buffer_.size())
    {
        tlv_buffer_.resize(tlv_length);
    }
    (void)stream.read(reinterpret_cast<holo::char_t*>(&tlv_buffer_[0]), tlv_length);
}

void InterfaceDescriptionBlock::ReadHeaderFromStream(std::fstream& stream, holo::bool_t is_network_byte_order)
{
    Block::ReadFromStream(stream, is_network_byte_order);

    (void)stream.read(reinterpret_cast<holo::char_t*>(&link_type_), sizeof(link_type_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&reserved_), sizeof(reserved_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&snap_len_), sizeof(snap_len_));

    if (is_network_byte_order)
    {
        link_type_ = holo::core::hton16(link_type_);
        reserved_  = holo::core::hton16(reserved_);
        snap_len_  = holo::core::hton32(snap_len_);
    }
}

void InterfaceDescriptionBlock::ReadTlvFromStream(std::fstream& stream, holo::bool_t is_network_byte_order)
{
    (void)is_network_byte_order;

    holo::uint32_t block_length{Block::GetLength()};
    size_t         header_size{Block::GetSerializedSize<4U>()};
    header_size += holo::serialization::SerializedSize<4U>(link_type_, reserved_, snap_len_);

    assert(block_length > header_size);
    (void)stream.seekg(header_size, std::ios_base::cur);

    size_t length_size{holo::serialization::SerializedSize<4U>(block_length)};
    assert(block_length > header_size + length_size);
    holo::uint32_t tlv_length = block_length - header_size - length_size;

    if (tlv_length > tlv_buffer_.size())
    {
        tlv_buffer_.resize(tlv_length);
    }
    (void)stream.read(reinterpret_cast<holo::char_t*>(&tlv_buffer_[0]), tlv_length);
}

}  // namespace pcapng
}  // namespace holo
