#ifndef HOLO_PCAPNG_PCAPNG_FILE_H_
#define HOLO_PCAPNG_PCAPNG_FILE_H_

#include <holo/core/types.h>
#include <holo/pcapng/block.h>
#include <holo/pcapng/open_mode.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

namespace holo
{
namespace pcapng
{
class PcapngFile final
{
public:
    using value_type      = Block;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = value_type const&;
    using pointer         = value_type*;
    using const_pointer   = value_type const*;
    using pos_type        = std::fstream::pos_type;

    using PosType = pos_type;

    template <bool Const>
    class Iterator;

    using const_iterator         = Iterator<true>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    explicit PcapngFile(std::string const& file, OpenMode const mode = OpenMode::TRUNC);
    ~PcapngFile() noexcept;

    void PushBack(SectionHeaderBlock& block, holo::bool_t is_network_byte_order = false);
    void PushBack(InterfaceDescriptionBlock& block, holo::bool_t is_network_byte_order = false);
    void PushBack(EnhancedPacketBlock& block, holo::bool_t is_network_byte_order = false);

    const_iterator cbegin() noexcept
    {
        return const_iterator{fstream_ptr_, 0};
    }

    const_iterator cend() noexcept
    {
        return const_iterator{fstream_ptr_, EOF};
    }

    template <bool Const>
    class Iterator final
    {
    public:
        using value_type        = PcapngFile::value_type;
        using difference_type   = PcapngFile::difference_type;
        using iterator_category = std::bidirectional_iterator_tag;
        using pos_type          = PcapngFile::pos_type;

        using pointer = typename std::conditional<Const, PcapngFile::const_pointer, PcapngFile::pointer>::type;

        using reference = typename std::conditional<Const, PcapngFile::const_reference, PcapngFile::reference>::type;

        using ValueType      = value_type;
        using Pointer        = pointer;
        using Reference      = reference;
        using DifferenceType = difference_type;
        using PosType        = pos_type;

        template <bool>
        friend class Iterator;

        Iterator(std::shared_ptr<std::fstream> const& stream, PosType const cur_pos)
          : fstream_ptr_{stream}
          , cur_pos_{cur_pos}
          , block_length_{0U}
          , is_network_byte_order_{false}
          , cur_block_{BlockType::SHB}
        {
        }

        ~Iterator() noexcept = default;

        Iterator(Iterator const& that) noexcept
          : fstream_ptr_{that.fstream_ptr_}
          , cur_pos_{that.cur_pos_}
          , block_length_{that.block_length_}
          , is_network_byte_order_{that.is_network_byte_order_}
          , cur_block_{that.cur_block_}
        {
        }

        Iterator(Iterator<!Const> const& that) noexcept
          : fstream_ptr_{that.fstream_ptr_}
          , cur_pos_{that.cur_pos_}
          , block_length_{that.block_length_}
          , is_network_byte_order_{that.is_network_byte_order_}
          , cur_block_{that.cur_block_}
        {
        }

        Iterator(Iterator&& that) noexcept
          : fstream_ptr_{std::move(that.fstream_ptr_)}
          , cur_pos_{that.cur_pos_}
          , block_length_{that.block_length_}
          , is_network_byte_order_{that.is_network_byte_order_}
          , cur_block_{std::move(that.cur_block_)}
        {
        }

        Iterator(Iterator<!Const>&& that) noexcept
          : fstream_ptr_{std::move(that.fstream_ptr_)}
          , cur_pos_{that.cur_pos_}
          , block_length_{that.block_length_}
          , is_network_byte_order_{that.is_network_byte_order_}
          , cur_block_{std::move(that.cur_block_)}
        {
        }

        Iterator& operator=(Iterator const& that) & noexcept
        {
            fstream_ptr_           = that.fstream_ptr_;
            cur_pos_               = that.cur_pos_;
            block_length_          = that.block_length_;
            is_network_byte_order_ = that.is_network_byte_order_;
            cur_block_             = that.cur_block_;
            return *this;
        }

        Iterator& operator=(Iterator<!Const> const& that) & noexcept
        {
            fstream_ptr_           = that.fstream_ptr_;
            cur_pos_               = that.cur_pos_;
            block_length_          = that.block_length_;
            is_network_byte_order_ = that.is_network_byte_order_;
            cur_block_             = that.cur_block_;
            return *this;
        }

        Iterator& operator=(Iterator&& that) & noexcept
        {
            fstream_ptr_           = std::move(that.fstream_ptr_);
            cur_pos_               = that.cur_pos_;
            block_length_          = that.block_length_;
            is_network_byte_order_ = that.is_network_byte_order_;
            cur_block_             = std::move(that.cur_block_);
            return *this;
        }

        Iterator& operator=(Iterator<!Const>&& that) & noexcept
        {
            fstream_ptr_           = std::move(that.fstream_ptr_);
            cur_pos_               = that.cur_pos_;
            block_length_          = that.block_length_;
            is_network_byte_order_ = that.is_network_byte_order_;
            cur_block_             = std::move(that.cur_block_);
            return *this;
        }

        Iterator& operator++()
        {
            (void)fstream_ptr_->seekg(cur_pos_);
            cur_block_.ReadFromStream(*(fstream_ptr_.get()), is_network_byte_order_);

            block_length_ = cur_block_.GetLength();

            if (BlockType::SHB == cur_block_.GetType())
            {
                (void)fstream_ptr_->seekg(cur_pos_);

                SectionHeaderBlock section_block{};
                section_block.ReadHeaderFromStream(*(fstream_ptr_.get()));

                block_length_          = section_block.GetLength();
                is_network_byte_order_ = (SectionHeaderBlock::BYTE_ORDER_MAGIC != section_block.GetByteOrder());
            }

            cur_pos_ += block_length_;

            (void)fstream_ptr_->seekg(cur_pos_);
            if (fstream_ptr_->peek() == EOF)
            {
                cur_pos_ = EOF;
            }

            return *this;
        }

        Iterator& operator--()
        {
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator old(*this);
            ++(*this);
            return old;
        }

        Iterator operator--(int)
        {
            Iterator old(*this);
            --(*this);
            return old;
        }

        Iterator& operator+=(DifferenceType n) & noexcept
        {
            for (DifferenceType i = 0; i < n; i++)
            {
                ++(*this);
            }
            return *this;
        }

        Iterator& operator-=(DifferenceType n) & noexcept
        {
            for (DifferenceType i = 0; i < n; i++)
            {
                --(*this);
            }
            return *this;
        }

        template <bool Const_>
        bool operator==(Iterator<Const_> const& that) const
        {
            return cur_pos_ == that.cur_pos_;
        }

        template <bool Const_>
        bool operator!=(Iterator<Const_> const& that) const
        {
            return !(*this == that);
        }

        template <bool Const_>
        bool operator<=(Iterator<Const_> const& that) const
        {
            return static_cast<size_t>(cur_pos_) <= static_cast<size_t>(that.cur_pos_);
        }

        template <bool Const_>
        bool operator>=(Iterator<Const_> const& that) const
        {
            return static_cast<size_t>(cur_pos_) >= static_cast<size_t>(that.cur_pos_);
        }

        template <bool Const_>
        bool operator<(Iterator<Const_> const& that) const
        {
            return static_cast<size_t>(cur_pos_) < static_cast<size_t>(that.cur_pos_);
        }

        template <bool Const_>
        bool operator>(Iterator<Const_> const& that) const
        {
            return static_cast<size_t>(cur_pos_) > static_cast<size_t>(that.cur_pos_);
        }

        Reference operator*()
        {
            fstream_ptr_->clear(std::ios_base::eofbit);
            (void)fstream_ptr_->seekg(cur_pos_);
            cur_block_.ReadFromStream(*(fstream_ptr_.get()), is_network_byte_order_);
            return cur_block_;
        }

        Pointer operator->()
        {
            fstream_ptr_->clear(std::ios_base::eofbit);
            (void)fstream_ptr_->seekg(cur_pos_);
            cur_block_.ReadFromStream(*(fstream_ptr_.get()), is_network_byte_order_);
            return &cur_block_;
        }

        std::shared_ptr<SectionHeaderBlock> CreateSHB()
        {
            fstream_ptr_->clear(std::ios_base::eofbit);
            (void)fstream_ptr_->seekg(cur_pos_);

            std::shared_ptr<SectionHeaderBlock> block = std::make_shared<SectionHeaderBlock>();
            block->ReadFromStream(*(fstream_ptr_.get()));

            block_length_          = block->GetLength();
            is_network_byte_order_ = (SectionHeaderBlock::BYTE_ORDER_MAGIC != block->GetByteOrder());

            return block;
        }

        std::shared_ptr<InterfaceDescriptionBlock> CreateIDB()
        {
            fstream_ptr_->clear(std::ios_base::eofbit);
            (void)fstream_ptr_->seekg(cur_pos_);

            std::shared_ptr<InterfaceDescriptionBlock> block = std::make_shared<InterfaceDescriptionBlock>();
            block->ReadFromStream(*(fstream_ptr_.get()), is_network_byte_order_);

            return block;
        }

        std::shared_ptr<EnhancedPacketBlock> CreateEPB()
        {
            fstream_ptr_->clear(std::ios_base::eofbit);
            (void)fstream_ptr_->seekg(cur_pos_);

            std::shared_ptr<EnhancedPacketBlock> block = std::make_shared<EnhancedPacketBlock>();
            block->ReadFromStream(*(fstream_ptr_.get()), is_network_byte_order_);

            return block;
        }

        std::shared_ptr<SectionHeaderBlock> CreateSHBHeader()
        {
            fstream_ptr_->clear(std::ios_base::eofbit);
            (void)fstream_ptr_->seekg(cur_pos_);

            std::shared_ptr<SectionHeaderBlock> block = std::make_shared<SectionHeaderBlock>();
            block->ReadHeaderFromStream(*(fstream_ptr_.get()));

            block_length_          = block->GetLength();
            is_network_byte_order_ = (SectionHeaderBlock::BYTE_ORDER_MAGIC != block->GetByteOrder());

            return block;
        }

        std::shared_ptr<InterfaceDescriptionBlock> CreateIDBHeader()
        {
            fstream_ptr_->clear(std::ios_base::eofbit);
            (void)fstream_ptr_->seekg(cur_pos_);

            std::shared_ptr<InterfaceDescriptionBlock> block = std::make_shared<InterfaceDescriptionBlock>();
            block->ReadHeaderFromStream(*(fstream_ptr_.get()), is_network_byte_order_);

            return block;
        }

        std::shared_ptr<EnhancedPacketBlock> CreateEPBHeader()
        {
            fstream_ptr_->clear(std::ios_base::eofbit);
            (void)fstream_ptr_->seekg(cur_pos_);

            std::shared_ptr<EnhancedPacketBlock> block = std::make_shared<EnhancedPacketBlock>();
            block->ReadHeaderFromStream(*(fstream_ptr_.get()), is_network_byte_order_);

            return block;
        }

    private:
        std::shared_ptr<std::fstream> fstream_ptr_;
        PosType                       cur_pos_;
        holo::uint32_t                block_length_;
        holo::bool_t                  is_network_byte_order_;
        ValueType                     cur_block_;
    };

private:
    std::shared_ptr<std::fstream> fstream_ptr_;
    SectionHeaderBlock            current_section_;
    std::string                   file_;
    PosType                       current_section_pos_;
    holo::bool_t                  is_network_byte_order_;
    holo::bool_t                  is_written_;
};

}  // namespace pcapng
}  // namespace holo

#endif
