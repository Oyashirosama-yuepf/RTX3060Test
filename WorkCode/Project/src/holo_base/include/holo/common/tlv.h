/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tlv.h
 * @brief This header file defines TlvT and TlvSequenceBaseT Object.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-12-12
 */

#ifndef HOLO_COMMON_TLV_H_
#define HOLO_COMMON_TLV_H_

#include <holo/core/exception.h>
#include <holo/core/types.h>

#include <iterator>
#include <type_traits>

namespace holo
{
namespace common
{
/**
 * @addtogroup common
 * {
 */

template <typename TlvT>
class[[deprecated]] TlvSequenceBaseT;

/**
 * @brief TlvT class defines a Type-Length-Value tuple.
 *
 * @details TlvT is a Type-Length-Value tuple. This data structure can be used
 * to represent dynamic data types. @n TlvT consist of three parts: Type, Length
 * and Value. @n Type: Type of data. @n Length: Length of tlv value. (Not the
 * whole Tlv block) @n Value: Value of data. @n
 *
 * @tparam TypeT Type of TlvT type.
 * @tparam LengthT Type of TlvT length.
 * @tparam ValueT Type of TlvT value.
 *
 * @note TlvT class cannot be created individually. It can only be extracted
 * from TlvSequenceBaseT object.
 */
template <typename TypeT, typename LengthT, typename ValueT, uint8_t Alignment,
          typename std::enable_if<std::is_arithmetic<ValueT>::value, ValueT>::type* = nullptr>
class TlvT
{
public:
    using TypeType   = TypeT;
    using LengthType = LengthT;
    using ValueType  = ValueT;

    static uint8_t const ALIGNMENT = Alignment;

    /**
     * @brief Get type of TlvT.
     *
     * @return Type of Tlv.
     *
     * @exceptsafe No throw
     */
    TypeType GetType() const noexcept
    {
        return type_;
    }

    /**
     * @brief Get length of TlvT value.
     *
     * @return Length of TlvT value.
     *
     * @exceptsafe No throw
     */
    LengthType GetLength() const noexcept
    {
        return length_;
    }

    /**
     * @brief Get value of TlvT value as CastValueType.
     *
     * @details Get value of TlvT value as CastValueType.
     * If this tlv is an array, only the first element of array is returned.
     * If tlv has no value field holo::exception::OutOfRangeException will be
     * thrown. If size of CastValueType is larger than tlv length,
     * holo::exception::OutOfRangeException will be thrown.
     *
     * @tparam CastValueType Value type of Tlv value.
     *
     * @return The first element of tlv value.
     *
     * @throws holo::exception::OutofRangeException if size of CastValueType is
     * larger than Tlv value length.
     *
     * @exceptsafe Strong garantee
     */
    template <typename CastValueType                                                                  = ValueType,
              typename std::enable_if<std::is_arithmetic<CastValueType>::value, CastValueType>::type* = nullptr>
    CastValueType const& GetValue() const
    {
        if (sizeof(CastValueType) > length_)
        {
            throw holo::exception::OutOfRangeException("Tlv element access index out of range.");
        }
        return *reinterpret_cast<CastValueType const*>(value_);
    }

    /**
     * @brief Get Tlv value.
     *
     * @details Get Tlv value. If this tlv is an array, only the first element
     * of array is returned.
     *
     * @tparam CastValueType Value type of Tlv value.
     *
     * @return The first element of tlv value.
     *
     * @throws holo::exception::OutofRangeException if size of CastValueType is
     * larger than Tlv value length.
     *
     * @exceptsafe Strong garantee
     */
    template <typename CastValueType                                                                  = ValueType,
              typename std::enable_if<std::is_arithmetic<CastValueType>::value, CastValueType>::type* = nullptr>
    CastValueType& GetValue()
    {
        if (sizeof(CastValueType) > length_)
        {
            throw holo::exception::OutOfRangeException("Tlv element access index out of range.");
        }
        return *reinterpret_cast<CastValueType*>(value_);
    }

    /**
     * @brief Get nth element of Tlv value.
     *
     * @tparam CastValueType Value type of Tlv value.
     * @param index index of element.
     *
     * @return The nth element of tlv value.
     *
     * @throws holo::exception::OutofRangeException if size of CastValueType *
     * index is larger than Tlv value length.
     *
     * @exceptsafe Strong garantee
     */
    template <typename CastValueType                                                                  = ValueType,
              typename std::enable_if<std::is_arithmetic<CastValueType>::value, CastValueType>::type* = nullptr>
    CastValueType const& At(size_t index) const
    {
        if (sizeof(CastValueType) * index > length_)
        {
            throw holo::exception::OutOfRangeException("Tlv element access index out of range.");
        }
        return reinterpret_cast<CastValueType const*>(value_)[index];
    }

    /**
     * @brief Get nth element of Tlv value.
     *
     * @tparam CastValueType Value type of Tlv value.
     * @param index index of element.
     *
     * @return The nth element of tlv value.
     *
     * @throws holo::exception::OutofRangeException if size of CastValueType *
     * index is larger than Tlv value length.
     *
     * @exceptsafe Strong garantee
     */
    template <typename CastValueType                                                                  = ValueType,
              typename std::enable_if<std::is_arithmetic<CastValueType>::value, CastValueType>::type* = nullptr>
    CastValueType& At(size_t index)
    {
        if (sizeof(CastValueType) * index > length_)
        {
            throw holo::exception::OutOfRangeException("Tlv element access index out of range.");
        }
        return reinterpret_cast<CastValueType*>(value_)[index];
    }

    /**
     * @brief Get nth element of Tlv value with no bound check.
     *
     * @param index index of element.
     *
     * @return The nth element of tlv value.
     *
     * @exceptsafe No throw
     *
     * @note The behaviour is undefined if index is out of tlv value address
     * range.
     */
    ValueType const& operator[](size_t index) const noexcept
    {
        return value_[index];
    }

    /**
     * @brief Get nth element of Tlv value with no bound check.
     *
     * @param index index of element.
     *
     * @return The nth element of tlv value.
     *
     * @exceptsafe No throw
     *
     * @note The behaviour is undefined if index is out of tlv value address
     * range.
     */
    ValueType& operator[](size_t index) noexcept
    {
        return ((ValueType*)value_)[index];
    }

    /**
     * @brief Cast value type of this tlv block to CastValueType.
     *
     * @tparam CastValueType Type of tlv value.
     *
     * @exceptsafe No throw
     *
     * @return Reference to tlv object.
     */
    template <typename CastValueType>
    TlvT<TypeType, LengthType, CastValueType, ALIGNMENT> const& As() const noexcept
    {
        return *reinterpret_cast<TlvT<TypeType, LengthType, CastValueType, ALIGNMENT>*>(this);
    }

    /**
     * @brief Cast value type of this tlv block to CastValueType.
     *
     * @tparam CastValueType Type of tlv value.
     *
     * @exceptsafe No throw
     *
     * @return Reference to tlv object.
     */
    template <typename CastValueType>
    TlvT<TypeType, LengthType, CastValueType, ALIGNMENT>& As() noexcept
    {
        return *reinterpret_cast<TlvT<TypeType, LengthType, CastValueType, ALIGNMENT>*>(this);
    }

    friend class TlvSequenceBaseT<TlvT>;  // TlvSequenceBaseT class can visit
                                          // private member of this class.

private:
    TypeType   type_;
    LengthType length_;
    uint8_t    value_[0];

    /**
     * @brief Default construct
     *
     * @exceptsafe No throw
     */
    TlvT() noexcept : type_(static_cast<TypeType>(0U)), length_(0U)
    {
    }

    /**
     * @brief Construct with tlv type and one tlv value element.
     *
     * @tparam CastValueType Type of tlv value
     *
     * @param type Type of TlvT.
     * @param value Value of TlvT.
     *
     * @exceptsafe No throw
     */
    template <typename CastValueType,
              typename std::enable_if<std::is_arithmetic<CastValueType>::value, CastValueType>::type* = nullptr>
    TlvT(TypeType type, CastValueType value) noexcept : type_(type), length_(sizeof(CastValueType))
    {
        *(reinterpret_cast<CastValueType*>(value_)) = value;
    }

    /**
     * @brief Construct with tlv type and tlv value array.
     *
     * @tparam CastValueType Type of tlv value
     *
     * @param type Type of TlvT.
     * @param value Address of first value of TlvT.
     * @param count Number of values.
     *
     * @exceptsafe No throw
     */
    template <typename CastValueType,
              typename std::enable_if<std::is_arithmetic<CastValueType>::value, CastValueType>::type* = nullptr>
    TlvT(TypeType type, CastValueType* value, size_t count = 0) noexcept
      : type_(type), length_(sizeof(CastValueType) * count)
    {
        CastValueType* ptr = (reinterpret_cast<CastValueType*>(value_));
        for (size_t i = 0; i < count; ++i)
        {
            *ptr++ = value[i];
        }
    }

    /**
     * @brief Construct with only type. This will construct a tlv with only type
     * tag.
     *
     * @param type Type of TlvT
     */
    TlvT(TypeType type) noexcept : type_(type), length_(0)
    {
    }

    /**
     * @brief Copy construct is disabled
     */
    TlvT(TlvT const&) = delete;

    /**
     * @brief Copy assign operator is disabled
     */
    TlvT& operator=(TlvT const&) = delete;
};

/**
 * @brief Base template class represents a sequence of tlvs.
 *
 *
 * @tparam TlvT Type of Tlv in this tlv sequence.
 */
template <typename TlvT>
class TlvSequenceBaseT
{
public:
    using value_type      = TlvT;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = value_type const&;
    using pointer         = value_type*;
    using const_pointer   = value_type const*;
    template <bool_t CONST = false>
    class Iterator;
    using iterator       = Iterator<false>;
    using const_iterator = Iterator<true>;

    using TypeType                 = typename TlvT::TypeType;
    using LengthType               = typename TlvT::LengthType;
    const static uint8_t ALIGNMENT = TlvT::ALIGNMENT;

    /**
     * @brief Default constructor.
     *
     * @exceptsafe No throw.
     */
    TlvSequenceBaseT() noexcept : buffer_(nullptr), buffer_size_(0), tail_(0)
    {
    }

    /**
     * @brief Construct with a data buffer.
     *
     * @param buffer The data buffer.
     * @param buffer_size Size of the data buffer.
     * @param tail tail of TlvSequence
     *
     * @exceptsafe No throw.
     */
    TlvSequenceBaseT(uint8_t* buffer, size_t buffer_size, size_t tail = 0) noexcept
      : buffer_(buffer), buffer_size_(buffer_size), tail_(tail)
    {
    }

    /**
     * @brief Destructor
     */
    virtual ~TlvSequenceBaseT() noexcept
    {
    }

    /**
     * @brief Bind a buffer to TlvSequenceBaseT
     *
     * @param buffer The data buffer.
     * @param buffer_size Size of the data buffer.
     *
     * @exceptsafe No throw.
     */
    void BindBuffer(uint8_t* buffer, size_t buffer_size) noexcept
    {
        buffer_      = buffer;
        buffer_size_ = buffer_size;
        tail_        = findTail();
    }

    /**
     * @brief Get iterator to the first tlv block.
     *
     * @return Iterator pointing to the first tlv block.
     *
     * @exceptsafe No throw.
     */
    iterator begin() noexcept
    {
        return iterator(buffer_);
    }

    /**
     * @brief Get iterator to past-the-end tlv block.
     *
     * @return Iterator pointing to the past-the-end tlv block.
     *
     * @exceptsafe No throw.
     */
    iterator end() noexcept
    {
        return iterator(buffer_ + tail_);
    }

    /**
     * @brief Get const iterator to the first tlv block.
     *
     * @return Const iterator pointing to the first tlv block.
     *
     * @exceptsafe No throw.
     */
    const_iterator begin() const noexcept
    {
        return const_iterator(buffer_);
    }

    /**
     * @brief Get const iterator to the first tlv block.
     *
     * @return Const iterator pointing to the first tlv block.
     *
     * @exceptsafe No throw.
     */
    const_iterator end() const noexcept
    {
        return const_iterator(buffer_ + tail_);
    }

    /**
     * @brief Get const iterator to the first tlv block.
     *
     * @return Const iterator pointing to the first tlv block.
     *
     * @exceptsafe No throw.
     */
    const_iterator cbegin() const noexcept
    {
        return const_iterator(buffer_);
    }

    /**
     * @brief Get const iterator to the first tlv block.
     *
     * @return Const iterator pointing to the first tlv block.
     *
     * @exceptsafe No throw.
     */
    const_iterator cend() const noexcept
    {
        return const_iterator(buffer_ + tail_);
    }

    /**
     * @brief Construct a tlv block at the end of tlv sequence emplace.
     *
     * @tparam ValueType
     *
     * @param type Type of Tlv.
     * @param value Value of Tlv.
     *
     * @return Iterator to the inserted Tlv block.
     *
     * @throws holo::exception::BadAllocException if there is no enough space
     * for emplaced tlv block.
     *
     * @exceptsafe Basic
     */
    template <typename TlvValueType,
              typename std::enable_if<std::is_arithmetic<TlvValueType>::value, TlvValueType>::type* = nullptr>
    iterator emplace_back(TypeType type, TlvValueType value)
    {
        uint32_t current_tail     = tail_;
        size_t   tlv_size         = sizeof(TlvValueType) + sizeof(value_type);
        size_t   aligned_tlv_size = alignedSize(tlv_size);

        if (tail_ + aligned_tlv_size > buffer_size_)
        {
            throw holo::exception::BadAllocException();
        }
        (void)new (reinterpret_cast<value_type*>(buffer_ + tail_)) value_type(type, value);
        tail_ += aligned_tlv_size;
        return iterator(buffer_ + current_tail);
    }

    /**
     * @brief Construct a tlv block at the end of tlv sequence emplace.
     *
     * @tparam ValueType
     *
     * @param type Type of Tlv.
     * @param value Address of first value of Tlv.
     * @param count Number of values.
     *
     * @return Iterator to the emplaced Tlv block.
     *
     * @throws holo::exception::BadAllocException if there is no enough space
     * for emplaced tlv block.
     *
     * @exceptsafe Basic
     */
    template <typename TlvValueType,
              typename std::enable_if<std::is_arithmetic<TlvValueType>::value, TlvValueType>::type* = nullptr>
    iterator emplace_back(TypeType type, TlvValueType* value, size_t count = 0)
    {
        uint32_t current_tail     = tail_;
        size_t   tlv_size         = sizeof(TlvValueType) * count + sizeof(value_type);
        size_t   aligned_tlv_size = alignedSize(tlv_size);

        if (tail_ + aligned_tlv_size > buffer_size_)
        {
            throw holo::exception::BadAllocException();
        }
        (void)new (reinterpret_cast<value_type*>(buffer_ + tail_)) value_type(type, value, count);
        tail_ += aligned_tlv_size;
        return iterator(buffer_ + current_tail);
    }

    /**
     * @brief Construct a tlv block at the end of tlv sequence emplace.
     *
     * @param type Type of Tlv.
     *
     * @return Iterator to the emplaced Tlv block.
     */
    iterator emplace_back(TypeType type)
    {
        uint32_t current_tail     = tail_;
        size_t   aligned_tlv_size = alignedSize(sizeof(value_type));

        if (tail_ + aligned_tlv_size > buffer_size_)
        {
            throw holo::exception::BadAllocException();
        }
        (void)new (reinterpret_cast<value_type*>(buffer_ + tail_)) value_type(type);
        tail_ += aligned_tlv_size;
        return iterator(buffer_ + current_tail);
    }

    /**
     * @brief Clear all tlv blocks.
     *
     * @exceptsafe No throw.
     */
    void clear() noexcept
    {
        tail_ = 0;
    }

    /**
     * @brief Get number of tlv blocks in tlv sequence.
     *
     * @return Number of tlv blocks.
     */
    size_t size() const noexcept
    {
        size_t size = 0;
        for (auto it = begin(); it != end(); ++it)
        {
            size++;
        }
        return size;
    }

    /**
     * @brief Get Tlv buffer.
     *
     * @return Pointer to Tlv buffer.
     *
     * @exceptsafe No throw.
     */
    uint8_t const* GetBuffer() const noexcept
    {
        return buffer_;
    }

    /**
     * @brief Get number of bytes used in Tlv buffer.
     *
     * @return Number of bytes used in Tlv buffer.
     *
     * @exceptsafe No throw.
     */
    size_t GetBufferSize() const noexcept
    {
        return tail_;
    }

    /**
     * @brief Get total number of bytes of Tlv buffer.
     *
     * @return Number of bytes of Tlv buffer.
     */
    size_t GetBufferCapacity() const noexcept
    {
        return buffer_size_;
    }

    /**
     * @brief Forward iterator of TlvSequenceBaseT
     *
     * @tparam CONST Whether it is a const iterator.
     */
    template <bool_t CONST>
    class Iterator
    {
    public:
        using difference_type   = TlvSequenceBaseT::difference_type;
        using value_type        = TlvSequenceBaseT::value_type;
        using reference_type    = typename std::conditional<CONST, typename TlvSequenceBaseT::const_reference,
                                                         typename TlvSequenceBaseT::reference>::type;
        using pointer_type      = typename std::conditional<CONST, typename TlvSequenceBaseT::const_pointer,
                                                       typename TlvSequenceBaseT::pointer>::type;
        using iterator_category = std::forward_iterator_tag;

        /**
         * @brief Default constructor.
         */
        Iterator() noexcept : p_tlv_(nullptr)
        {
        }

        /**
         * @brief Construct with tlv pointer
         *
         * @param p_tlv Pointer to base address of a Tlv.
         */
        Iterator(uint8_t* p_tlv) noexcept : p_tlv_(p_tlv)
        {
        }

        /**
         * @brief  Check if two iterators are equal.
         *
         * @tparam InputConst Whether input iterator is a const iterator.
         * @param other The input iterator.
         *
         * @return Whether the two iterators are pointing to the same tlv.
         */
        template <bool_t InputConst>
        bool_t operator==(Iterator<InputConst> const& other) const noexcept
        {
            return p_tlv_ == other.p_tlv_;
        }

        /**
         * @brief  Check if two iterators are not equal.
         *
         * @tparam InputConst Whether input iterator is a const iterator.
         * @param other The input iterator.
         *
         * @return Whether the two iterators are pointing to different tlvs.
         */
        template <bool_t InputConst>
        bool_t operator!=(Iterator<InputConst> const& other) const noexcept
        {
            return !(*this == other);
        }

        /**
         * @brief Prefix increament operator
         *
         * @return iterator pointing to the next tlv block.
         */
        Iterator& operator++() noexcept
        {
            p_tlv_ +=
                TlvSequenceBaseT::alignedSize(reinterpret_cast<value_type*>(p_tlv_)->GetLength() + sizeof(value_type));
            return *this;
        }

        /**
         * @brief Surfix increament operator.
         *
         * @param int Parameter used for function polymorphism.
         *
         * @return iterator pointing to current tlv block.
         */
        Iterator operator++(int)
        {
            Iterator tmp(*this);
            p_tlv_ +=
                TlvSequenceBaseT::alignedSize(reinterpret_cast<value_type*>(p_tlv_)->GetLength() + sizeof(value_type));
            return tmp;
        }

        /**
         * @brief Dereferencing operator
         *
         * @return reference to the tlv pointed by this iterator.
         */
        reference_type operator*() const noexcept
        {
            return *reinterpret_cast<value_type*>(p_tlv_);
        }

        /**
         * @brief Access member via iterator.
         *
         * @return Pointer to tlv.
         */
        pointer_type operator->() const noexcept
        {
            return reinterpret_cast<value_type*>(p_tlv_);
        }

        friend class Iterator<!CONST>;

    private:
        uint8_t* p_tlv_;
    };

protected:
    /**
     * @brief Try to find the last position of a tlv sequence from buffer.
     *
     * @details This function is responsible of search the tlv sequence buffer
     * and recognize the last tlv from buffer. Returns the offset of end of last
     * tlv block address. If the buffer is malformed or search passed the end of
     * the buffer, this function should return 0.
     *
     * @return Tlv sequence tail offset.
     */
    virtual size_t findTail() const noexcept
    {
        return 0;
    }

    /**
     * @brief Get tail offset of buffer.
     *
     * @return Offset of tail.
     */
    size_t getTail() const noexcept
    {
        return tail_;
    }

    /**
     * @brief Set tail offset of buffer.
     *
     * @param tail Offset of tail.
     */
    void setTail(size_t tail) noexcept
    {
        tail_ = tail;
    }

    /**
     * @brief Round up size to ALIGNMENT aligned buffer size.
     *
     * @param size input size.
     *
     * @return aligned size.
     */
    static size_t alignedSize(size_t size) noexcept
    {
        return (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
    }

private:
    uint8_t* buffer_;
    size_t   buffer_size_;
    size_t   tail_;
};

/**
 * @}
 */

}  // namespace common
}  // namespace holo

#endif
