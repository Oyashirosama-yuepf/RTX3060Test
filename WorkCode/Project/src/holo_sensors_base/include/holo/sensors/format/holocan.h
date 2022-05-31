/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file holo_can_format.h
 * @brief define the holo can structure format class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-07-24
 */

#ifndef _HOLO_SENSORS_FORMAT_HOLOCAN_H
#define _HOLO_SENSORS_FORMAT_HOLOCAN_H

#include <holo/sensors/format/format.h>
#include <holo/serialization/serialization.h>
#include <holo_c/core/static_assert.h>
#include <cstring>

namespace holo
{
namespace sensors
{
namespace format
{
const static uint8_t NORMAL_CAN_MAX_DLC = 8u;
template <bool_t IsCanfdPacket = false>
class HoloCanPacketT : public FormatBase
{
public:
    HoloCanPacketT() noexcept
      : header_{0, 0, 0, 0}
      , channel_(0)
      , source_(0)
      , dlc_(0)
      , unused0_(0)
      , id_(0)
      , sec_(0)
      , nsec_(0)
      , SIZE(IsCanfdPacket ? 84u : 28u)
    {
        std::memset(data_, 0, sizeof(data_));
    }

    HoloCanPacketT(const HoloCanPacketT<IsCanfdPacket>& other) noexcept
      : header_{other.header_[0], other.header_[1], other.header_[2], other.header_[3]}
      , channel_(other.channel_)
      , source_(other.source_)
      , dlc_(other.dlc_)
      , unused0_(other.unused0_)
      , id_(other.id_)
      , sec_(other.sec_)
      , nsec_(other.nsec_)
      , SIZE(other.SIZE)
    {
        std::memcpy(data_, other.data_, sizeof(data_));
    }

    HoloCanPacketT& operator=(const HoloCanPacketT<IsCanfdPacket>& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        std::memcpy(header_, other.header_, sizeof(header_));
        channel_ = other.channel_;
        source_  = other.source_;
        dlc_     = other.dlc_;
        unused0_ = other.unused0_;
        id_      = other.id_;
        sec_     = other.sec_;
        nsec_    = other.nsec_;
        SIZE     = other.SIZE;
        std::memcpy(data_, other.data_, sizeof(data_));
        return *this;
    }

    bool_t IsValid() const noexcept
    {
        return static_cast<bool_t>(!std::memcmp(header_, "##@!", 4));
    }

    uint8_t GetChannel() const noexcept
    {
        return channel_;
    }

    uint8_t GetSource() const noexcept
    {
        return source_;
    }

    uint32_t GetId() const noexcept
    {
        return id_;
    }

    uint8_t GetDlc() const noexcept
    {
        uint8_t ret = 0;
        if (IsCanfdPacket)
        {
            ret = dlc_;
        }
        else
        {
            ret = (dlc_ > NORMAL_CAN_MAX_DLC) ? NORMAL_CAN_MAX_DLC : dlc_;
        }
        return ret;
    }

    uint8_t* GetData() noexcept
    {
        return data_;
    }

    const uint8_t* GetData() const noexcept
    {
        return data_;
    }

    uint32_t GetSec() const noexcept
    {
        return sec_;
    }

    uint32_t GetNsec() const noexcept
    {
        return nsec_;
    }

    void SetHeaderDefault() noexcept
    {
        (void)std::memcpy(header_, "##@!", 4);
    }

    void SetChannel(uint8_t channel) noexcept
    {
        channel_ = channel;
    }

    void SetSource(uint8_t source) noexcept
    {
        source_ = source;
    }

    void SetId(uint32_t id) noexcept
    {
        id_ = id;
    }

    void SetDlc(uint8_t dlc) noexcept
    {
        if (IsCanfdPacket)
        {
             dlc_ = dlc;
        }
        else
        {
            dlc_ = (dlc > NORMAL_CAN_MAX_DLC) ? NORMAL_CAN_MAX_DLC : dlc;
        }
    }

    void SetSec(uint32_t sec) noexcept
    {
        sec_ = sec;
    }

    void SetNsec(uint32_t nsec) noexcept
    {
        nsec_ = nsec;
    }

    uint32_t GetSerializedSize() const noexcept
    {
        return SIZE;
    }

    uint32_t Serialize(uint8_t* data, uint32_t bytes) const noexcept
    {
        if (bytes < SIZE)
        {
            return 0;
        }
        uint8_t                                  buffer[SIZE];
        holo::serialization::Serializer<true, 4> serializer(buffer, SIZE);
        try
        {
            serializer << header_[0] << header_[1] << header_[2] << header_[3] << channel_ << source_ << dlc_
                       << unused0_ << id_;
            serializer.Write(data_, IsCanfdPacket ? 64u : 8u);
            serializer << sec_ << nsec_ << holo::serialization::align;
            (void)std::memcpy(data, serializer.GetData(), serializer.GetSize());
        }
        catch (const std::exception& e)
        {
            (void)e;
            return 0;
        }
        return serializer.GetSize();
    }

    uint32_t Deserialize(const uint8_t* data, uint32_t bytes)
    {
        if (bytes < SIZE)
        {
            return 0;
        }
        holo::serialization::Deserializer<true, 4> deserializer(data, SIZE);
        try
        {
            uint8_t                                    header[4];
            deserializer >> header[0] >> header[1] >> header[2] >> header[3];
            if (std::memcmp(header, "##@!", 4))
            {
                return 0;
            }
            (void)std::memcpy(header_, header, 4);
            deserializer >> channel_ >> source_ >> dlc_ >> unused0_ >> id_;
            deserializer.Read(data_, IsCanfdPacket ? 64u : 8u);
            deserializer >> sec_ >> nsec_ >> holo::serialization::align;
        }
        catch (const std::exception& e)
        {
            (void)e;
            return 0;
        }
        return deserializer.GetOffset();
    }

private:
    uint8_t  header_[4];  //!< const string '##@!'
    uint8_t  channel_;    //!< the hardware chn
    uint8_t  source_;     //!< the messages source
    uint8_t  dlc_;        //!< data length code
    uint8_t  unused0_;    //!< unused byte
    uint32_t id_;         //!< can message identifier
    uint8_t  data_[64];   //!< can message data
    uint32_t sec_;        //!< timestamp sec
    uint32_t nsec_;       //!< timestamp usec

private:
    uint32_t SIZE;
};

using HoloCanPacket   = HoloCanPacketT<false>;
using HoloCanfdPacket = HoloCanPacketT<true>;

}  // namespace format
}  // namespace sensors
}  // namespace holo

#endif
