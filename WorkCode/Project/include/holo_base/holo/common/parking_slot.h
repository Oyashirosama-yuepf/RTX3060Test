/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_slot.h
 * @brief this file defines parking slot
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @author Changsong Yu (yuchangsong@holomatic.com)
 * @date 2021-03-17
 */

#ifndef HOLO_COMMON_PARKING_SLOT_H_
#define HOLO_COMMON_PARKING_SLOT_H_

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/geometry/point3.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace common
{
/**
 * @brief parking slot definition
 *
 * @details the distribution of vertices of parking slot
 * @verbatim
 *
 *         left perpendicular            -++----++--                right perpendicular
 *                                       -  head   -
 *      [3]------------------[0]         -         -             [1]------------------[2]
 *       | [0] ------------->            - vehicle -                <------------- [1] |
 *       |  |  ------------->            -         -                <-------------  |  |
 *       |  |    left slot               -         -                   right slot   |  |
 *       | [1] ------------->            -  tail   -                <------------- [0] |
 *      [2]------------------[1]         - ------- -             [0]------------------[3]
 *
 *        left parallel                  back angle                  right parallel
 *         [3]------[0]                 [0]       [1]                 [1]------[2]
 *          |   ^                        |    ^     |                       ^   |
 *          |   |                         |    |     |                      |   |
 *          |   |                          |    |     |                     |   |
 *          |   |                           |    |     |                    |   |
 *          |   |                            | [0]-[1]  |                   |   |
 *         [2]------[1]                      [3] ------ [2]           [0]------[3]
 * @endverbatim
 * @tparam T floating type required
 */
template <typename T>
struct ParkingSlotT
{
    using ScalarType = T;
    using Point3Type = geometry::Point3T<ScalarType>;

    static const uint32_t VERTEX_NUM         = 4u;
    static const uint32_t STOPPER_VERTEX_NUM = 2u;

    /**
     * @brief define type of parking slot
     */
    enum class Type : uint32_t
    {
        PERPENDICULAR = 0,
        PARALLEL      = 1,
        ANGLE         = 2,
    };

    /**
     * @brief define the position of parking slot
     *
     */
    enum class Position : uint32_t
    {
        LEFT  = 0,
        RIGHT = 1,
        FRONT = 2,
        BACK  = 3,
    };

    /**
     * @brief define the
     *
     */
    enum class Status : uint32_t
    {
        UNKNOWN  = 0,
        FREE     = 1,
        OCCUPIED = 2,
    };

    uint64_t   id                       = 0u;                   ///< parking slot id if any
    bool_t     is_valid                 = false;                ///< whether the slot detection is valid
    Type       type                     = Type::PERPENDICULAR;  ///< parking slot type
    Position   position                 = Position::FRONT;      ///< parking slot position
    Status     status                   = Status::UNKNOWN;      ///< parking slot status
    ScalarType width                    = -1.0;                 ///< bounding box width of the parking slot
    ScalarType height                   = -1.0;                 ///< bounding box height of the parking slot
    ScalarType angle                    = 0.0;                  ///< bounding box angle of the parking slot
    ScalarType confidence               = 0.0;                  ///< detection confidence [0, 1]
    bool_t     is_rear_vertex_available = false;      ///< whether the rear vertices 2 && 3 are available in detection
    Point3Type vertices[VERTEX_NUM];                  ///< vertices coordinate
    bool_t     is_center_vertex_available = false;    ///< whether the center vertex is avaialbe
    Point3Type center_vertex;                         ///< center vertex coordinate
    bool_t     is_stopper_available = false;          ///< whether the stopper is available in detection
    Point3Type stopper_vertices[STOPPER_VERTEX_NUM];  ///< stopper vertices coordinate

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
        return holo::serialization::SerializedSize<ALIGN>(
                   is_valid, is_rear_vertex_available, is_center_vertex_available, is_stopper_available, id,
                   static_cast<uint32_t>(type), static_cast<uint32_t>(position), static_cast<uint32_t>(status), width,
                   height, angle, confidence) +
               vertices[0].template GetSerializedSize<ALIGN>() + vertices[1].template GetSerializedSize<ALIGN>() +
               vertices[2].template GetSerializedSize<ALIGN>() + vertices[3].template GetSerializedSize<ALIGN>() +
               center_vertex.template GetSerializedSize<ALIGN>() +
               stopper_vertices[0].template GetSerializedSize<ALIGN>() +
               stopper_vertices[1].template GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::exception::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << is_valid << is_rear_vertex_available << is_center_vertex_available << is_stopper_available << id
                   << static_cast<uint32_t>(type) << static_cast<uint32_t>(position) << static_cast<uint32_t>(status)
                   << width << height << angle << confidence << vertices[0] << vertices[1] << vertices[2] << vertices[3]
                   << center_vertex << stopper_vertices[0] << stopper_vertices[1];
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t _type     = 0u;
        uint32_t _position = 0u;
        uint32_t _status   = 0u;

        deserializer >> is_valid >> is_rear_vertex_available >> is_center_vertex_available >> is_stopper_available >>
            id >> _type >> _position >> _status >> width >> height >> angle >> confidence >> vertices[0] >>
            vertices[1] >> vertices[2] >> vertices[3] >> center_vertex >> stopper_vertices[0] >> stopper_vertices[1];

        type     = static_cast<Type>(_type);
        position = static_cast<Position>(_position);
        status   = static_cast<Status>(_status);
    }
};

using ParkingSlotf = ParkingSlotT<float32_t>;
using ParkingSlotd = ParkingSlotT<float64_t>;
using ParkingSlot  = ParkingSlotd;

/**
 * @brief define ParkingSlotFrame type
 *
 * @details a ParkingSlotFrame contains many parking slots
 *
 * @tparam T floating type required
 */
template <typename T, size_t SIZE = std::numeric_limits<size_t>::max()>
class ParkingSlotFrameT : public container::details::VectorBase<ParkingSlotT<T>, SIZE>
{
public:
    using ScalarType      = T;
    using ParkingSlotType = ParkingSlotT<ScalarType>;
    using Base            = container::details::VectorBase<ParkingSlotT<T>, SIZE>;

    /**
     * @brief Construct a new Parking Slot Frame object
     *
     * @param timestamp timestamp
     * @param coordinate coordinate
     */
    ParkingSlotFrameT(Timestamp const& timestamp = Timestamp(0, 0), Coordinate const& coordinate = Coordinate::UNKNOWN)
      : Base(), timestamp_(timestamp), coordinate_(coordinate)
    {
    }

    /**
     * @brief Get the Timestamp object
     *
     * @return Timestamp timestamp
     */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set the Timestamp object
     *
     * @param timestamp timestamp
     */
    void SetTimestamp(Timestamp const& timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Get the Coordinate object
     *
     * @return Coordinate coordinate
     */
    Coordinate GetCoordinate() const noexcept
    {
        return coordinate_;
    }

    /**
     * @brief Set the Coordinate object
     *
     * @param coordiante coordinate
     */
    void SetCoordinate(Coordinate const& coordinate) noexcept
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
        size_t aligned_size = timestamp_.GetSerializedSize<ALIGN>() +
                              holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(coordinate_),
                                                                         static_cast<uint32_t>(this->size()));
        for (auto const& ps : (*this))
        {
            aligned_size += ps.template GetSerializedSize<ALIGN>();
        }
        return aligned_size;
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::exception::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << static_cast<uint32_t>(coordinate_) << static_cast<uint32_t>(this->size());
        for (auto const& ps : (*this))
        {
            serializer << ps;
        }
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t coord;
        uint32_t size;
        deserializer >> timestamp_ >> coord >> size;
        coordinate_ = coord;
        this->resize(size);
        for (auto& ps : (*this))
        {
            deserializer >> ps;
        }
    }

private:
    Timestamp  timestamp_;   ///< timestamp
    Coordinate coordinate_;  ///< coordinate
};

using ParkingSlotFramef = ParkingSlotFrameT<float32_t>;
using ParkingSlotFramed = ParkingSlotFrameT<float64_t>;
using ParkingSlotFrame  = ParkingSlotFramed;

}  // namespace common
}  // namespace holo

#endif  // HOLO_COMMON_PARKING_SLOT_H_