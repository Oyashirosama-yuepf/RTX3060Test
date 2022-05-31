/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_navigation_request.h
 * @brief map navigation request
 * @author zhouhuishuang(zhouhuishuang@holomaitc.com)
 * @date "2021-08-31"
 */

#ifndef HOLO_MAP_MAP_NAVIGATION_REQUEST_H_
#define HOLO_MAP_MAP_NAVIGATION_REQUEST_H_

#include <holo/common/coordinate.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/geometry/point3.h>

namespace holo
{
namespace map
{
class NavigationPoint
{
public:
    /**
     * @brief map layer id
     */
    enum class LayerId : holo::uint8_t
    {
        UNKNOWN       = 0U,
        POI           = 1U,
        ROAD          = 2U,
        PARKING_FLOOR = 3U,
        PARKING_LOT   = 4U,
        PARKING_SPACE = 5U,
        RESERVED_1    = 200U,
        RESERVED_2    = 201U,
        RESERVED_3    = 202U,
        RESERVED_4    = 203U,
        RESERVED_5    = 204U
    };

    /**
     * @brief default constructor
     */
    NavigationPoint() : layer_id_{LayerId::UNKNOWN}, element_id_{}, coordinate_{0}, position_{}
    {
    }

    /**
     * @brief Construct a new NavigationPoint object
     *
     * @param layer_id layer id
     * @param element_id element id
     * @param coordinate coordinate
     * @param position position
     */
    NavigationPoint(LayerId layer_id, holo::uint64_t element_id, holo::common::Coordinate coordinate,
                    holo::geometry::Point3f position)
      : layer_id_{layer_id}, element_id_{element_id}, coordinate_{coordinate}, position_{position}
    {
    }

    /**
     * @brief Set layer id
     *
     * @param layer_id
     */
    void SetLayerId(LayerId const layer_id) noexcept
    {
        layer_id_ = layer_id;
    }

    /**
     * @brief Get layer id
     *
     * @return LayerId
     */
    LayerId GetLayerId() const noexcept
    {
        return layer_id_;
    }

    /**
     * @brief Set element id
     *
     * @param element_id
     */
    void SetElementId(holo::uint64_t const element_id) noexcept
    {
        element_id_ = element_id;
    }

    /**
     * @brief Get element id
     *
     * @return holo::uint64_t
     */
    holo::uint64_t GetElementId() const noexcept
    {
        return element_id_;
    }

    /**
     * @brief Set coordinate
     *
     * @param coordinate
     */
    void SetCoordinate(holo::common::Coordinate const coordinate) noexcept
    {
        coordinate_ = coordinate;
    }

    /**
     * @brief Get coordinate
     *
     * @return Coordinate
     */
    holo::common::Coordinate GetCoordinate() const noexcept
    {
        return coordinate_;
    }

    /**
     * @brief Set position
     *
     * @param Position
     */
    void SetPosition(holo::geometry::Point3f const position) noexcept
    {
        position_ = position;
    }

    /**
     * @brief Get position
     *
     * @return holo::geometry::Point3f
     */
    holo::geometry::Point3f GetPosition() const noexcept
    {
        return position_;
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
        return holo::serialization::SerializedSize<ALIGN>(static_cast<holo::uint8_t>(layer_id_), element_id_) +
               coordinate_.GetSerializedSize<ALIGN>() + position_.GetSerializedSize<ALIGN>();
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
        serializer << holo::serialization::align << static_cast<holo::uint8_t>(layer_id_) << element_id_ << coordinate_
                   << position_;
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
        holo::uint8_t layer_id;
        deserializer >> holo::serialization::align >> layer_id >> element_id_ >> coordinate_ >> position_;

        layer_id_ = static_cast<LayerId>(layer_id);
    }

private:
    LayerId                  layer_id_;
    holo::uint64_t           element_id_;
    holo::common::Coordinate coordinate_;
    holo::geometry::Point3f  position_;
};

template <size_t POINT_SIZE>
class RoutingSearchRequestT : public holo::container::details::VectorBase<NavigationPoint, POINT_SIZE>
{
public:
    using Base = holo::container::details::VectorBase<NavigationPoint, POINT_SIZE>;

    /**
     * @brief policy
     */
    enum class Policy : holo::uint8_t
    {
        DEFAULT                    = 0U,
        SHORTEST_DISTANCE          = 1U,
        SHORTEST_TIME              = 2U,
        SHORTEST_TOLL              = 3U,
        SHORTEST_HIGHWAY           = 4U,
        SHORTEST_MORE_PARKINGSPACE = 5U
    };

    /**
     * @brief default constructor
     */
    RoutingSearchRequestT() : request_id_{0}, policy_{Policy::DEFAULT}
    {
    }

    /**
     * @brief Construct a new RoutingSearchRequestT object
     *
     * @param request_id request id
     * @param policy policy
     */
    RoutingSearchRequestT(holo::uint64_t request_id, Policy policy) : request_id_{request_id}, policy_{policy}
    {
    }

    /**
     * @brief Set request id
     *
     * @param request_id
     */
    void SetRequestId(holo::uint64_t const request_id) noexcept
    {
        request_id_ = request_id;
    }

    /**
     * @brief Get request id
     *
     * @return uint64_t
     */
    holo::uint64_t GetRequestId() const noexcept
    {
        return request_id_;
    }

    /**
     * @brief Set policy
     *
     * @param policy
     */
    void SetPolicy(Policy const policy) noexcept
    {
        policy_ = policy;
    }

    /**
     * @brief Get policy
     *
     * @return Policy
     */
    Policy GetPolicy() const noexcept
    {
        return policy_;
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
        return Base::template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(request_id_, static_cast<holo::uint8_t>(policy_));
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
        serializer << request_id_ << static_cast<holo::uint8_t>(policy_) << holo::serialization::align;
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
        holo::uint8_t policy;
        Base::Deserialize(deserializer);
        deserializer >> request_id_ >> policy >> holo::serialization::align;
        policy_ = static_cast<Policy>(policy);
    }

private:
    holo::uint64_t request_id_;
    Policy         policy_;
};
}  // namespace map
}  // namespace holo

#endif
