/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file hpa_grid_map.h
 * @brief This header file defines grid map
 * @author chengxiang(chengxiang@holomatic.com)
 * @date 2021-09-18
 */

#ifndef HOLO_PARKING_BASE_SYSTEM_HPA_GRID_MAP_H_
#define HOLO_PARKING_BASE_SYSTEM_HPA_GRID_MAP_H_

#include <holo/container/vector.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace system 
{

/**
 * @brief Defines freespace grid map data structure. In contrust to GH idl 
 *        HPA_FreespaceGridMap definenation.
 * 
 * @author chengxiang (chengxiang@holomatic.com)
 * @date   2021-09-18
 */
class FreespaceGridMap
{
public:
    static holo::int32_t const s_space_size = 200 * 250;

    using CharVector = holo::container::Vector<char, s_space_size >;
    using  Timestamp = holo::common::Timestamp;

public:
    FreespaceGridMap()
    : timestamp_()
    , frame_index_(0)
    , reserved_(0)
    , char_freespace_()
    {}

    Timestamp GetTimestamp() const noexcept 
    {
        return timestamp_;
    }

    void SetTimestamp( Timestamp const & timestamp ) noexcept
    {
        timestamp_ = timestamp;
    }

    holo::uint32_t GetFrameIndex() const noexcept 
    {
        return frame_index_;
    }

    void SetFrameIndex( holo::uint32_t const frame_index ) noexcept
    {
        frame_index_ = frame_index;
    }

    holo::float32_t GetReserved() const noexcept
    {
        return reserved_;
    }

    void SetReserved( holo::uint32_t const reserved ) noexcept
    {
        reserved_ = reserved;
    }

    CharVector GetFreespaceVector() const 
    {
        return char_freespace_;
    }

    void SetFreespaceVector( CharVector const& freespace_vect )
    {
        char_freespace_ = freespace_vect;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.template GetSerializedSize<ALIGN>()
               + holo::serialization::SerializedSize<ALIGN>( frame_index_, reserved_)
               + char_freespace_.template GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << frame_index_ 
                   << reserved_ << char_freespace_
                   << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> timestamp_ >> frame_index_ 
                     >> reserved_  >> char_freespace_ 
                     >> holo::serialization::align;
    }

    

private:
    Timestamp                timestamp_;

    holo::uint32_t           frame_index_;
    holo::uint32_t           reserved_;
    CharVector               char_freespace_;
};


} ///< system
} ///< parking
} ///< holo

#endif ///< HOLO_PARKING_BASE_SYSTEM_HPA_GRID_MAP_H_



