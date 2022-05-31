#include <assert.h>
#include <holo/pcapng/block/enhanced_packet_block.h>

namespace holo
{
namespace pcapng
{
EnhancedPacketBlock::EnhancedPacketBlock() noexcept
  : Block{BlockType::EPB}
  , interface_id_{0U}
  , timestamp_{0U}
  , captured_packet_length_{0U}
  , original_packet_length_{0U}
  , packet_data_{}
  , tlv_buffer_(TLV_BUFFER_SIZE, 0U)
{
}

void EnhancedPacketBlock::WriteToStream(std::fstream& stream, holo::bool_t is_network_byte_order)
{
    holo::uint32_t id{interface_id_};
    holo::uint64_t timestamp{timestamp_};
    holo::uint32_t captured_length = packet_data_.size();
    holo::uint32_t original_length{original_packet_length_};

    if (!is_network_byte_order)
    {
        size_t size{Block::GetSerializedSize<4U>()};
        size += holo::serialization::SerializedSize<4U>(id, timestamp, captured_length, original_length);
        size += holo::serialization::AlignedSize<4U>(captured_length);
        TlvSequenceType<false> tlv_sequence{&tlv_buffer_[0], tlv_buffer_.size()};
        size += tlv_sequence.GetSerializedSize<4U>();
        size += 4U;

        Block::SetLength(size);
        Block::WriteToStream(stream, is_network_byte_order);

        captured_packet_length_       = packet_data_.size();
        original_packet_length_       = captured_packet_length_;
        holo::uint32_t timestamp_high = static_cast<holo::uint32_t>(timestamp >> 32);
        holo::uint32_t timestamp_low  = static_cast<holo::uint32_t>(timestamp);

        (void)stream.write(reinterpret_cast<holo::char_t*>(&interface_id_), sizeof(interface_id_));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&timestamp_high), sizeof(timestamp_high));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&timestamp_low), sizeof(timestamp_low));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&captured_packet_length_), sizeof(captured_packet_length_));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&original_packet_length_), sizeof(original_packet_length_));
        if (packet_data_.size() > 0U)
        {
            (void)stream.write(&packet_data_[0], packet_data_.size());
        }
        (void)stream.write(reinterpret_cast<holo::char_t const*>(tlv_sequence.GetData()), tlv_sequence.GetLength());

        holo::uint32_t length{Block::GetLength()};
        (void)stream.write(reinterpret_cast<holo::char_t*>(&length), sizeof(length));
    }
    else
    {
        size_t size{Block::GetSerializedSize<4U>()};
        size += holo::serialization::SerializedSize<4U>(id, timestamp, captured_length, original_length);
        size += holo::serialization::AlignedSize<4U>(captured_length);
        TlvSequenceType<true> tlv_sequence{&tlv_buffer_[0], tlv_buffer_.size()};
        size += tlv_sequence.GetSerializedSize<4U>();
        size += 4U;

        Block::SetLength(size);
        Block::WriteToStream(stream, is_network_byte_order);

        captured_packet_length_       = packet_data_.size();
        original_packet_length_       = captured_packet_length_;
        holo::uint32_t timestamp_high = static_cast<holo::uint32_t>(timestamp >> 32);
        holo::uint32_t timestamp_low  = static_cast<holo::uint32_t>(timestamp);
        timestamp_high                = holo::core::hton32(timestamp_high);
        timestamp_low                 = holo::core::hton32(timestamp_low);

        holo::uint32_t interface_id{holo::core::hton32(id)};
        holo::uint32_t captured_packet_length{holo::core::hton32(captured_packet_length_)};
        holo::uint32_t original_packet_length{holo::core::hton32(original_packet_length_)};

        (void)stream.write(reinterpret_cast<holo::char_t*>(&interface_id), sizeof(interface_id));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&timestamp_high), sizeof(timestamp_high));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&timestamp_low), sizeof(timestamp_low));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&captured_packet_length), sizeof(captured_packet_length));
        (void)stream.write(reinterpret_cast<holo::char_t*>(&original_packet_length), sizeof(original_packet_length));
        if (packet_data_.size() > 0U)
        {
            (void)stream.write(&packet_data_[0], packet_data_.size());
        }
        (void)stream.write(reinterpret_cast<holo::char_t const*>(tlv_sequence.GetData()), tlv_sequence.GetLength());

        holo::uint32_t length{Block::GetLength()};
        length = holo::core::hton32(length);
        (void)stream.write(reinterpret_cast<holo::char_t*>(&length), sizeof(length));
    }
}

void EnhancedPacketBlock::ReadFromStream(std::fstream& stream, holo::bool_t is_network_byte_order)
{
    Block::ReadFromStream(stream, is_network_byte_order);

    holo::uint32_t timestamp_high{0};
    holo::uint32_t timestamp_low{0};
    (void)stream.read(reinterpret_cast<holo::char_t*>(&interface_id_), sizeof(interface_id_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&timestamp_high), sizeof(timestamp_high));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&timestamp_low), sizeof(timestamp_low));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&captured_packet_length_), sizeof(captured_packet_length_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&original_packet_length_), sizeof(original_packet_length_));

    if (is_network_byte_order)
    {
        interface_id_           = holo::core::hton32(interface_id_);
        timestamp_high          = holo::core::hton32(timestamp_high);
        timestamp_low           = holo::core::hton32(timestamp_low);
        captured_packet_length_ = holo::core::hton32(captured_packet_length_);
        original_packet_length_ = holo::core::hton32(original_packet_length_);
    }

    timestamp_ = (static_cast<holo::uint64_t>(timestamp_high) << 32) | static_cast<holo::uint64_t>(timestamp_low);

    if (captured_packet_length_ > 0U)
    {
        packet_data_.resize(captured_packet_length_);
        (void)stream.read(&packet_data_[0], captured_packet_length_);
    }

    holo::uint32_t captured_length{captured_packet_length_};
    holo::uint32_t block_length{Block::GetLength()};
    size_t         fixed_size{Block::GetSerializedSize<4U>()};
    fixed_size += holo::serialization::SerializedSize<4U>(interface_id_, timestamp_, captured_packet_length_,
                                                          original_packet_length_, block_length);
    fixed_size += holo::serialization::AlignedSize<4U>(captured_length);

    assert(block_length > fixed_size);
    holo::uint32_t tlv_length = block_length - fixed_size;

    if (tlv_length > tlv_buffer_.size())
    {
        tlv_buffer_.resize(tlv_length);
    }
    (void)stream.read(reinterpret_cast<holo::char_t*>(&tlv_buffer_[0]), tlv_length);
}

void EnhancedPacketBlock::ReadHeaderFromStream(std::fstream& stream, holo::bool_t is_network_byte_order)
{
    Block::ReadFromStream(stream, is_network_byte_order);

    holo::uint32_t timestamp_high{0};
    holo::uint32_t timestamp_low{0};
    (void)stream.read(reinterpret_cast<holo::char_t*>(&interface_id_), sizeof(interface_id_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&timestamp_high), sizeof(timestamp_high));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&timestamp_low), sizeof(timestamp_low));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&captured_packet_length_), sizeof(captured_packet_length_));
    (void)stream.read(reinterpret_cast<holo::char_t*>(&original_packet_length_), sizeof(original_packet_length_));

    if (is_network_byte_order)
    {
        interface_id_           = holo::core::hton32(interface_id_);
        timestamp_high          = holo::core::hton32(timestamp_high);
        timestamp_low           = holo::core::hton32(timestamp_low);
        captured_packet_length_ = holo::core::hton32(captured_packet_length_);
        original_packet_length_ = holo::core::hton32(original_packet_length_);
    }

    timestamp_ = (static_cast<holo::uint64_t>(timestamp_high) << 32) | static_cast<holo::uint64_t>(timestamp_low);
}

void EnhancedPacketBlock::ReadPacketDataFromStream(std::fstream& stream, holo::bool_t is_network_byte_order)
{
    (void)is_network_byte_order;

    holo::uint32_t captured_length{captured_packet_length_};

    holo::uint32_t block_length{Block::GetLength()};
    size_t         header_size{Block::GetSerializedSize<4U>()};
    header_size +=
        holo::serialization::SerializedSize<4U>(interface_id_, timestamp_, captured_length, original_packet_length_);

    assert(block_length > header_size);
    (void)block_length;
    (void)stream.seekg(header_size, std::ios_base::cur);

    packet_data_.resize(captured_length);
    (void)stream.read(&packet_data_[0], captured_packet_length_);
}

void EnhancedPacketBlock::ReadTlvFromStream(std::fstream& stream, holo::bool_t is_network_byte_order)
{
    (void)is_network_byte_order;
    holo::uint32_t captured_length{captured_packet_length_};
    holo::uint32_t block_length{Block::GetLength()};
    size_t         header_size{Block::GetSerializedSize<4U>()};
    header_size +=
        holo::serialization::SerializedSize<4U>(interface_id_, timestamp_, captured_length, original_packet_length_);

    assert(block_length > header_size + captured_length);
    (void)stream.seekg(header_size + captured_length, std::ios_base::cur);

    size_t length_size{holo::serialization::SerializedSize<4U>(block_length)};
    assert(block_length > header_size + captured_length + length_size);
    holo::uint32_t tlv_length = block_length - header_size - captured_length - length_size;

    if (tlv_length > tlv_buffer_.size())
    {
        tlv_buffer_.resize(tlv_length);
    }
    (void)stream.read(reinterpret_cast<holo::char_t*>(&tlv_buffer_[0]), tlv_length);
}
}  // namespace pcapng
}  // namespace holo
