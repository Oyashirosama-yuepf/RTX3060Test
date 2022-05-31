#include <holo/pcapng/pcapng_file.h>

namespace holo
{
namespace pcapng
{
PcapngFile::PcapngFile(std::string const& file, OpenMode const mode)
  : fstream_ptr_{nullptr}
  , current_section_{}
  , file_{file}
  , current_section_pos_{0U}
  , is_network_byte_order_{false}
  , is_written_{false}
{
    if (mode == OpenMode::TRUNC)
    {
        fstream_ptr_ = std::make_shared<std::fstream>(file, std::fstream::binary | std::fstream::trunc |
                                                                std::fstream::in | std::fstream::out);
    }
    else
    {
        fstream_ptr_ = std::make_shared<std::fstream>(file, std::fstream::binary | std::fstream::app |
                                                                std::fstream::in | std::fstream::ate);
    }

    if (!fstream_ptr_->is_open())
    {
        std::runtime_error e{"Pcapng File Open Error!"};
        throw e;
    }
}

PcapngFile::~PcapngFile()
{
    if (is_written_)
    {
        current_section_.SetSectionLength(fstream_ptr_->tellg() - current_section_pos_);
        fstream_ptr_->close();

        fstream_ptr_ =
            std::make_shared<std::fstream>(file_, std::fstream::binary | std::fstream::in | std::fstream::out);

        (void)fstream_ptr_->seekg(current_section_pos_);
        current_section_.WriteToStream(*(fstream_ptr_.get()), is_network_byte_order_);
    }
}

void PcapngFile::PushBack(SectionHeaderBlock& block, holo::bool_t is_network_byte_order)
{
    current_section_     = block;
    current_section_pos_ = fstream_ptr_->tellg();
    block.WriteToStream(*(fstream_ptr_.get()), is_network_byte_order);
    is_written_            = true;
    is_network_byte_order_ = is_network_byte_order;
}

void PcapngFile::PushBack(InterfaceDescriptionBlock& block, holo::bool_t is_network_byte_order)
{
    block.WriteToStream(*(fstream_ptr_.get()), is_network_byte_order);
}

void PcapngFile::PushBack(EnhancedPacketBlock& block, holo::bool_t is_network_byte_order)
{
    block.WriteToStream(*(fstream_ptr_.get()), is_network_byte_order);
}

}  // namespace pcapng
}  // namespace holo
