/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file traffic_light.h
 * @brief This header file defines TrafficLight class
 * @author Zhou Huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-20
 */
#ifndef HOLO_COMMON_DETAILS_TRAFFIC_LIGHT_H_
#define HOLO_COMMON_DETAILS_TRAFFIC_LIGHT_H_

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/geometry/box3.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace common
{
namespace details
{
template <size_t LANE_SIZE, size_t SIGNAL_SIZE>
class TrafficLightT
{
public:
    enum class Type : uint8_t
    {
        UNDEFINED          = 0U,
        UNKNOWN            = 1U,
        CIRCLE             = 2U,
        PEDESTRIAN_SIGN    = 3U,
        LEFT               = 4U,
        FORWARD            = 5U,
        RIGHT              = 6U,
        U_TURN             = 7U,
        LEFT_FORWARD       = 8U,
        LEFT_RIGHT         = 9U,
        LEFT_FORWARD_RIGHT = 10U,
        LEFT_U_TURN        = 11U,
        FORWARD_RIGHT      = 12U,
        FORWARD_U_TURN     = 13U,
    };

    /**
     * @brief Traffic Light class enum
     */
    enum class Status : uint8_t
    {
        BLACK  = 0U,
        GREEN  = 1U,
        YELLOW = 2U,
        RED    = 3U,
    };

    struct Signal
    {

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
            return holo::serialization::SerializedSize<ALIGN>(static_cast<holo::uint8_t>(type),
                                                              static_cast<holo::uint8_t>(status));
        }

        template <typename S>
        void Serialize(S& serializer) const
        {
            serializer << holo::serialization::align << static_cast<holo::uint8_t>(type)
                       << static_cast<holo::uint8_t>(status) << holo::serialization::align;
        }

        template <typename D>
        void Deserialize(D& deserializer)
        {
            holo::uint8_t type_temp, status_temp;
            deserializer >> holo::serialization::align >> type_temp >> status_temp >> holo::serialization::align;
            type   = static_cast<Type>(type_temp);
            status = static_cast<Status>(status_temp);
        }

        Type   type;
        Status status;
    };

    /**
     * @brief default constructor
     */
    TrafficLightT()
      : track_id_{0}
      , is_detected_{false}
      , temporary_{false}
      , timer_{-1}
      , confidence_{0.0}
      , bounding_box_{}
      , lane_ids_{}
      , signals_{}
    {
    }

    /**
     * @brief Construct a new Traffic Light object
     *
     * @param track_id
     * @param is_detected
     * @param temporary
     * @param timer
     * @param confidence
     */
    TrafficLightT(holo::uint64_t track_id, holo::bool_t const is_detected, holo::bool_t const temporary,
                  holo::int16_t const timer, float32_t const confidence)
      : track_id_{track_id}
      , is_detected_{is_detected}
      , temporary_{temporary}
      , timer_{timer}
      , confidence_{confidence}
      , bounding_box_{}
      , lane_ids_{}
      , signals_{}
    {
    }

    /**
     * @brief Get the track id
     *
     * @return uint64_t
     */
    holo::uint64_t GetTrackId() const noexcept
    {
        return track_id_;
    }

    /**
     * @brief Set track id
     *
     * @param track_id
     */
    void SetTrackId(holo::uint64_t const track_id) noexcept
    {
        track_id_ = track_id;
    }

    /**
     * @brief Is detected
     *
     * @return true
     * @return false
     */
    holo::bool_t IsDetected() const noexcept
    {
        return is_detected_;
    }

    /**
     * @brief Set the detect flag object
     *
     * @param flag
     */
    void SetDetectFlag(holo::bool_t const flag) noexcept
    {
        is_detected_ = flag;
    }

    /**
     * @brief Is temporary
     *
     * @return true
     * @return false
     */
    holo::bool_t IsTemporary() const noexcept
    {
        return temporary_;
    }

    /**
     * @brief Set the temporary flag object
     *
     * @param flag
     */
    void SetTemporaryFlag(holo::bool_t const flag) noexcept
    {
        temporary_ = flag;
    }

    /**
     * @brief Get the timer object
     *
     * @return int16_t
     */
    holo::int16_t GetTimer() const noexcept
    {
        return timer_;
    }

    /**
     * @brief Set the timer object
     *
     * @param timer
     */
    void SetTimer(holo::int16_t const timer) noexcept
    {
        timer_ = timer;
    }

    /**
     * @brief Get the confidence
     *
     * @return holo::float32_t
     */
    holo::float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    /**
     * @brief Get the confidence
     *
     * @return confidence
     */
    void SetConfidence(holo::float32_t const confidence) noexcept
    {
        confidence_ = confidence;
    }

    /**
     * @brief Get the bounding box object
     *
     * @return holo::geometry::Box3d
     */
    holo::geometry::Box3d const& GetBoundingBox() const noexcept
    {
        return bounding_box_;
    }

    /**
     * @brief Set the bounding box object
     *
     * @param bounding_box
     */
    void SetBoundingBox(holo::geometry::Box3d const& bounding_box) noexcept
    {
        bounding_box_ = bounding_box;
    }

    /**
     * @brief Get the lane ids object
     *
     * @return holo::container::Vector<holo::uint64_t, LANE_SIZE>
     */
    holo::container::Vector<holo::uint64_t, LANE_SIZE> const& GetLaneIds() const noexcept
    {
        return lane_ids_;
    }

    /**
     * @brief Set the lane ids object
     *
     * @param lane_ids
     */
    void SetLaneIds(holo::container::Vector<holo::uint64_t, LANE_SIZE> const& lane_ids) noexcept
    {
        lane_ids_ = lane_ids;
    }

    /**
     * @brief Get the signals object
     *
     * @return holo::container::Vector<signal, SIGNAL_SIZE>
     */
    holo::container::Vector<Signal, SIGNAL_SIZE> const& GetSignals() const noexcept
    {
        return signals_;
    }

    /**
     * @brief Set the signals object
     *
     * @param signals
     */
    void SetSignals(holo::container::Vector<Signal, SIGNAL_SIZE> const& signals) noexcept
    {
        signals_ = signals;
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
        return holo::serialization::SerializedSize<ALIGN>(track_id_, is_detected_, temporary_, timer_, confidence_) +
               bounding_box_.GetSerializedSize<ALIGN>() +
               holo::serialization::AlignedSize<ALIGN>(sizeof(uint32_t) + lane_ids_.size() * sizeof(lane_ids_[0])) +
               signals_.template GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << track_id_ << is_detected_ << temporary_ << timer_ << confidence_
                   << bounding_box_ << static_cast<uint32_t>(lane_ids_.size());
        for (auto const& lane_ids : lane_ids_)
        {
            serializer << lane_ids;
        }
        serializer << signals_;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t lane_ids_size;
        deserializer >> holo::serialization::align >> track_id_ >> is_detected_ >> temporary_ >> timer_ >>
            confidence_ >> bounding_box_ >> lane_ids_size;

        lane_ids_.resize(lane_ids_size);
        for (size_t i = 0U; i < lane_ids_size; ++i)
        {
            deserializer >> lane_ids_[i];
        }
        deserializer >> signals_;
    }

private:
    holo::uint64_t                                     track_id_;
    holo::bool_t                                       is_detected_;
    holo::bool_t                                       temporary_;
    holo::int16_t                                      timer_;
    holo::float32_t                                    confidence_;
    holo::geometry::Box3d                              bounding_box_;
    holo::container::Vector<holo::uint64_t, LANE_SIZE> lane_ids_;
    holo::container::Vector<Signal, SIGNAL_SIZE>       signals_;
};

template <size_t LANE_SIZE, size_t SIGNAL_SIZE, size_t TRAFFIC_LIGHT_SIZE>
class TrafficLightsT
  : public holo::container::details::VectorBase<TrafficLightT<LANE_SIZE, SIGNAL_SIZE>, TRAFFIC_LIGHT_SIZE>
{
public:
    using Base = holo::container::details::VectorBase<TrafficLightT<LANE_SIZE, SIGNAL_SIZE>, TRAFFIC_LIGHT_SIZE>;

    /**
     * @brief default constructor
     */
    TrafficLightsT() : Base{}
    {
    }

    /**
     * @brief Construct a new Traffic Lights object
     *
     * @param timestamp
     * @param coordinate
     */
    TrafficLightsT(Timestamp const timestamp, Coordinate const coordinate)
      : Base{}, timestamp_{timestamp}, coordinate_{coordinate}
    {
    }

    /**
     * @brief Get the timestamp object
     *
     * @return holo::common::Timestamp
     */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set the timestamp object
     *
     * @param timestamp
     */
    void SetTimestamp(Timestamp const timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Get the coordinate object
     *
     * @return holo::common::Coordinate
     */
    Coordinate GetCoordinate() const noexcept
    {
        return coordinate_;
    }

    /**
     * @brief Set the coordinate object
     *
     * @param coordinate
     */
    void SetCoordinate(Coordinate const coordinate) noexcept
    {
        coordinate_ = coordinate;
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
        return Base::template GetSerializedSize<ALIGN>() + timestamp_.GetSerializedSize<ALIGN>() +
               coordinate_.GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        Base::Serialize(serializer);
        serializer << timestamp_ << coordinate_;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        Base::Deserialize(deserializer);
        deserializer >> timestamp_ >> coordinate_;
    }

private:
    Timestamp  timestamp_;
    Coordinate coordinate_;
};
}  // namespace details
}  // namespace common
}  // namespace holo
#endif