#include <holo/pcapng/pcapng_file.h>

using namespace holo::pcapng;

#define NETWORK_BYTE_ORDER true

int main()
{
    if (1)
    {
        PcapngFile file("test.file", OpenMode::RETAIN);

        if (1)
        {
            SectionHeaderBlock block;
            block.SetMajorVersion(0x02);
            block.SetMinorVersion(0x03);
            SectionHeaderBlock::TlvSequenceType<NETWORK_BYTE_ORDER> tlv_write_sequence{
                block.GetTlvSequence<NETWORK_BYTE_ORDER>()};
            SectionHeaderBlock::TlvSequenceType<NETWORK_BYTE_ORDER>::iterator iter_write = tlv_write_sequence.begin();
            iter_write->Set(0x08, "hello world");
            ++iter_write;
            iter_write->Set(0x09, "heduo");
            ++iter_write;
            iter_write->Set(0x05, "test section header block ");
            ++iter_write;
            iter_write->Set(0);

            file.PushBack(block, NETWORK_BYTE_ORDER);
        }

        if (1)
        {
            EnhancedPacketBlock epb_block;
            epb_block.SetInterfaceID(0x9988);
            epb_block.SetTimestamp(0x2233445566778899);
            EnhancedPacketBlock::TlvSequenceType<NETWORK_BYTE_ORDER> tlv_write_sequence{
                epb_block.GetTlvSequence<NETWORK_BYTE_ORDER>()};
            EnhancedPacketBlock::TlvSequenceType<NETWORK_BYTE_ORDER>::iterator iter_write = tlv_write_sequence.begin();
            iter_write->Set(0x22, "test xxx  mmm xxx");
            ++iter_write;
            iter_write->Set(0x33, "heduo he he he");
            ++iter_write;
            iter_write->Set(0x44, "test enhanced packet block");
            ++iter_write;
            iter_write->Set(0);

            file.PushBack(epb_block, NETWORK_BYTE_ORDER);
        }

        if (1)
        {
            EnhancedPacketBlock epb_block;
            epb_block.SetInterfaceID(0x9988);
            epb_block.SetTimestamp(0x2233445566778899);
            EnhancedPacketBlock::TlvSequenceType<NETWORK_BYTE_ORDER> tlv_write_sequence{
                epb_block.GetTlvSequence<NETWORK_BYTE_ORDER>()};
            EnhancedPacketBlock::TlvSequenceType<NETWORK_BYTE_ORDER>::iterator iter_write = tlv_write_sequence.begin();
            iter_write->Set(0x22, "test xxx  mmm xxx");
            ++iter_write;
            iter_write->Set(0x33, "heduo he he he");
            ++iter_write;
            iter_write->Set(0x44, "test enhanced packet block");
            ++iter_write;
            iter_write->Set(0);

            file.PushBack(epb_block, NETWORK_BYTE_ORDER);
        }

        if (1)
        {
            InterfaceDescriptionBlock idb_block;
            idb_block.SetLinkType(0x99);
            idb_block.SetSnapLen(0x33);
            InterfaceDescriptionBlock::TlvSequenceType<NETWORK_BYTE_ORDER> tlv_write_sequence{
                idb_block.GetTlvSequence<NETWORK_BYTE_ORDER>()};
            InterfaceDescriptionBlock::TlvSequenceType<NETWORK_BYTE_ORDER>::iterator iter_write =
                tlv_write_sequence.begin();
            iter_write->Set(0x55, "test code      sdfsd");
            ++iter_write;
            iter_write->Set(0x66, "heduo   duo   he ");
            ++iter_write;
            iter_write->Set(0x77, "test interface description block    ");
            ++iter_write;
            iter_write->Set(0);

            file.PushBack(idb_block, NETWORK_BYTE_ORDER);
        }

        if (1)
        {
            InterfaceDescriptionBlock idb_block;
            idb_block.SetLinkType(0x99);
            idb_block.SetSnapLen(0x33);
            InterfaceDescriptionBlock::TlvSequenceType<NETWORK_BYTE_ORDER> tlv_write_sequence{
                idb_block.GetTlvSequence<NETWORK_BYTE_ORDER>()};
            InterfaceDescriptionBlock::TlvSequenceType<NETWORK_BYTE_ORDER>::iterator iter_write =
                tlv_write_sequence.begin();
            iter_write->Set(0x55, "test code      sdfsd");
            ++iter_write;
            iter_write->Set(0x66, "heduo   duo   he ");
            ++iter_write;
            iter_write->Set(0x77, "test interface description block    ");
            ++iter_write;
            iter_write->Set(0);

            file.PushBack(idb_block, NETWORK_BYTE_ORDER);
        }

        if (1)
        {
            EnhancedPacketBlock epb_block;
            epb_block.SetInterfaceID(0x9988);
            epb_block.SetTimestamp(0x2233445566778899);
            EnhancedPacketBlock::TlvSequenceType<NETWORK_BYTE_ORDER> tlv_write_sequence{
                epb_block.GetTlvSequence<NETWORK_BYTE_ORDER>()};
            EnhancedPacketBlock::TlvSequenceType<NETWORK_BYTE_ORDER>::iterator iter_write = tlv_write_sequence.begin();
            iter_write->Set(0x22, "test xxx  mmm xxx");
            ++iter_write;
            iter_write->Set(0x33, "heduo he he he");
            ++iter_write;
            iter_write->Set(0x44, "test enhanced packet block");
            ++iter_write;
            iter_write->Set(0);

            file.PushBack(epb_block, NETWORK_BYTE_ORDER);
        }

        if (1)
        {
            EnhancedPacketBlock epb_block;
            epb_block.SetInterfaceID(0x9988);
            epb_block.SetTimestamp(0x2233445566778899);
            EnhancedPacketBlock::TlvSequenceType<NETWORK_BYTE_ORDER> tlv_write_sequence{
                epb_block.GetTlvSequence<NETWORK_BYTE_ORDER>()};
            EnhancedPacketBlock::TlvSequenceType<NETWORK_BYTE_ORDER>::iterator iter_write = tlv_write_sequence.begin();
            iter_write->Set(0x22, "test xxx  mmm xxx");
            ++iter_write;
            iter_write->Set(0x33, "heduo he he he");
            ++iter_write;
            iter_write->Set(0x44, "test enhanced packet block");
            ++iter_write;
            iter_write->Set(0);

            file.PushBack(epb_block, NETWORK_BYTE_ORDER);
        }
    }

    if (1)
    {
        PcapngFile   file("test.file", OpenMode::RETAIN);
        holo::bool_t is_network_byte_order = false;

        for (PcapngFile::const_iterator it = file.cbegin(); it < file.cend(); ++it)
        {
            Block const& base_block = *it;
            std::cout << std::hex << "type:" << static_cast<holo::uint32_t>(base_block.GetType()) << std::endl;
            std::cout << "length:" << base_block.GetLength() << std::endl;
            if (base_block.GetType() == BlockType::SHB)
            {
                std::shared_ptr<SectionHeaderBlock> block = it.CreateSHB();
                std::cout << std::hex << "type:" << static_cast<holo::uint32_t>(block->GetType()) << std::endl;
                std::cout << "length:" << block->GetLength() << std::endl;
                std::cout << "section_length:" << block->GetSectionLength() << std::endl;
                std::cout << "major:" << block->GetMajorVersion() << std::endl;
                std::cout << "minor:" << block->GetMinorVersion() << std::endl;
                std::cout << "order:" << block->GetByteOrder() << std::endl;
                is_network_byte_order = (SectionHeaderBlock::BYTE_ORDER_MAGIC != block->GetByteOrder());
                std::cout << "is_network_byte_order:" << is_network_byte_order << std::endl;

                if (is_network_byte_order)
                {
                    SectionHeaderBlock::TlvSequenceType<true> tlv_read_sequence{block->GetTlvSequence<true>()};
                    for (SectionHeaderBlock::TlvSequenceType<true>::const_iterator iter = tlv_read_sequence.cbegin();
                         iter != tlv_read_sequence.cend(); ++iter)
                    {
                        std::cout << "option{type:" << iter->GetType() << "   value:" << iter->GetValue<std::string>()
                                  << "}" << std::endl;
                    }
                }
                else
                {
                    SectionHeaderBlock::TlvSequenceType<false> tlv_read_sequence{block->GetTlvSequence<false>()};
                    for (SectionHeaderBlock::TlvSequenceType<false>::const_iterator iter = tlv_read_sequence.cbegin();
                         iter != tlv_read_sequence.cend(); ++iter)
                    {
                        std::cout << "option{type:" << iter->GetType() << "   value:" << iter->GetValue<std::string>()
                                  << "}" << std::endl;
                    }
                }
            }
            else if (base_block.GetType() == BlockType::IDB)
            {
                std::shared_ptr<InterfaceDescriptionBlock> block = it.CreateIDB();
                std::cout << std::hex << "type:" << static_cast<holo::uint32_t>(block->GetType()) << std::endl;
                std::cout << "length:" << block->GetLength() << std::endl;
                std::cout << "link_type:" << block->GetLinkType() << std::endl;
                std::cout << "snap_len:" << block->GetSnapLen() << std::endl;

                if (is_network_byte_order)
                {
                    SectionHeaderBlock::TlvSequenceType<true> tlv_read_sequence{block->GetTlvSequence<true>()};
                    for (SectionHeaderBlock::TlvSequenceType<true>::const_iterator iter = tlv_read_sequence.cbegin();
                         iter != tlv_read_sequence.cend(); ++iter)
                    {
                        std::cout << "option{type:" << iter->GetType() << "   value:" << iter->GetValue<std::string>()
                                  << "}" << std::endl;
                    }
                }
                else
                {
                    SectionHeaderBlock::TlvSequenceType<false> tlv_read_sequence{block->GetTlvSequence<false>()};
                    for (SectionHeaderBlock::TlvSequenceType<false>::const_iterator iter = tlv_read_sequence.cbegin();
                         iter != tlv_read_sequence.cend(); ++iter)
                    {
                        std::cout << "option{type:" << iter->GetType() << "   value:" << iter->GetValue<std::string>()
                                  << "}" << std::endl;
                    }
                }
            }
            else if (base_block.GetType() == BlockType::EPB)
            {
                std::shared_ptr<EnhancedPacketBlock> block = it.CreateEPB();
                std::cout << std::hex << "type:" << static_cast<holo::uint32_t>(block->GetType()) << std::endl;
                std::cout << "length:" << block->GetLength() << std::endl;
                std::cout << "interface id:" << block->GetInterfaceID() << std::endl;
                std::cout << "timestamp:" << block->GetTimestamp() << std::endl;
                std::cout << "capture_packet_length:" << block->GetCapturedPacketLength() << std::endl;
                std::cout << "original_packet_length:" << block->GetOriginalPacketLength() << std::endl;

                if (is_network_byte_order)
                {
                    SectionHeaderBlock::TlvSequenceType<true> tlv_read_sequence{block->GetTlvSequence<true>()};
                    for (SectionHeaderBlock::TlvSequenceType<true>::const_iterator iter = tlv_read_sequence.cbegin();
                         iter != tlv_read_sequence.cend(); ++iter)
                    {
                        std::cout << "option{type:" << iter->GetType() << "   value:" << iter->GetValue<std::string>()
                                  << "}" << std::endl;
                    }
                }
                else
                {
                    SectionHeaderBlock::TlvSequenceType<false> tlv_read_sequence{block->GetTlvSequence<false>()};
                    for (SectionHeaderBlock::TlvSequenceType<false>::const_iterator iter = tlv_read_sequence.cbegin();
                         iter != tlv_read_sequence.cend(); ++iter)
                    {
                        std::cout << "option{type:" << iter->GetType() << "   value:" << iter->GetValue<std::string>()
                                  << "}" << std::endl;
                    }
                }
            }
            else
            {
            }
        }
    }

    return 0;
}
