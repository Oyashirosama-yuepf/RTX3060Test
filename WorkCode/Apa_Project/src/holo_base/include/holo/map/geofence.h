/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geofence.h
 * @brief Define geofence message info
 * @author wanghaiyang@holomatic.com
 * @date "2020-02-27"
 */

#ifndef HOLO_MAP_GEOFENCE_H_
#define HOLO_MAP_GEOFENCE_H_

#include <vector>

#include <holo/common/timestamp.h>
#include <holo/map/common_def.h>

namespace holo
{
namespace map
{

/**
 * @addtogroup map
 * @{
 *
 */

/**
 * @brief Define the geofence of Holo.
 *
 * @Note Reference to: https://holomatic.feishu.cn/docs/doccnViiddBLGJ7sxIAq0KbLOPb#
 *
 * @verbatim
 * Three things will happen here with current car position and the range of a geofence.
 *
 * C: Current car position;
 * S: Start position of a geofence in relation to the driving direction;
 * E: End position of a geofence in relation to the driving direction;
 *
 * | >>>>>>>>>>>>>>>>>>>>> Driving Direction >>>>>>>>>>>>>>>>>>>>>>> |
 *
 * |C ------------->--------------- S ------------->--------------- E|
 * Start distance(CS) and End distance(CE) are both positive;
 *
 * |S ------------->--------------- C ------------->--------------- E|
 * Start distance(CS) is negative and End distance(CE) is positive;
 *
 * |S ------------->--------------- E ------------->--------------- C|
 * Start distance(CS) and End distance(CE) are both negative.
 * @endverbatim
 */
class Geofence
{
public:

    /**
     * @brief Enumerate all the sub functions which are related to geofence.
     */
    enum class Function : uint8_t
    {
        UNKNOWN         = 0, ///< Function with an invalid type.
        HSA,                 ///< Highway Switch Assist.
        ICP,                 ///< Intelligent Cruise Pilot.
        TJP,                 ///< Traffic Jam Pilot.
        LC,                  ///< Lane Change
        EMSS,                ///< Emergency Lane Safe Stop.
        FUNCTION_MAX         ///< Total number of function type.
    };

    /**
     * @brief Access geofence id.
     *
     * @return Geofence ID.
     */
    uint64_t GetId() const noexcept
    {
        return this->id_;
    }

    /**
     * @brief Assign a new geofence id.
     *
     * @param[in] id Geofence ID.
     * @return Nothing.
     */
    void SetId(const uint64_t id) noexcept
    {
        this->id_ = id;
    }

    /**
     * @brief Access sub function type.
     *
     * @return Function type value.
     */
    Function GetFunction() const noexcept
    {
        return this->function_;
    }

    /**
     * @brief Assign a new sub function type.
     *
     * @param[in] f A function type value.
     * @return Nothing.
     */
    void SetFunction(const Function f) noexcept
    {
        this->function_ = f;
    }

    /**
     * @brief Access start distance.
     *
     * @return Start distance value.
     */
    int32_t GetStartDistance() const noexcept
    {
        return this->start_distance_;
    }

    /**
     * @brief Assign a new start distance value.
     *
     * @param[in] distance Distance betweed current car position and start position of a geofence
     *                     on the motorway.
     * @return Nothing.
     */
    void SetStartDistance(const int32_t distance) noexcept
    {
        this->start_distance_ = distance;
    }

    /**
     * @brief Access end distance.
     *
     * @return End distance value.
     */
    int32_t GetEndDistance() const noexcept
    {
        return this->end_distance_;
    }

    /**
     * @brief Assign a new end distance value.
     *
     * @param[in] distance Distance betweed current car position and end position of a geofence
     *                     on the motorway.
     * @return Nothing.
     */
    void SetEndDistance(const int32_t distance) noexcept
    {
        this->end_distance_ = distance;
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
        return holo::serialization::SerializedSize<ALIGN>(id_, static_cast<uint8_t>(function_), 
                                                  start_distance_, end_distance_);
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
    template<typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << id_ << static_cast<uint8_t>(function_) 
                   << start_distance_ << end_distance_ << holo::serialization::align;
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
    template<typename D>
    void Deserialize(D& deserializer)
    {
        uint8_t function_val = 0;
        deserializer >> holo::serialization::align >> id_ >> function_val >> start_distance_ 
                     >> end_distance_ >> holo::serialization::align;

        function_ = static_cast<Function>(function_val);
    }

private:
    uint64_t id_             = 0UL;                 ///< Geofence id.
    Function function_       = Function::UNKNOWN;   ///< Sub function type of a geofence.
    int32_t  start_distance_ = 0U;                  ///< Distance(Unit: meters) between current position and start position of a geofence on the motorway.
    int32_t  end_distance_   = 0U;                  ///< Distance(Unit: meters) between current position and end position of a geofence on the motorway.
};

/**
 * @brief Geofences around current car position.
 */
class Geofences
{
public:
    using Timestamp = holo::common::Timestamp;
    /**
     * @brief Access timestamp.
     *
     * @return A reference of Timestamp.
     */
    Timestamp& GetTimestamp() noexcept
    {
        return this->timestamp_;
    }

    /**
     * @brief Access timestamp.
     *
     * @return A reference of Timestamp.
     */
    const Timestamp& GetTimestamp() const noexcept
    {
        return this->timestamp_;
    }

    /**
     * @brief Assign a new timestamp.
     *
     * @param[in] t A timestamp value.
     * @return Nothing.
     */
    void SetTimestamp(const Timestamp& t)
    {
        this->timestamp_ = t;
    }

    /**
     * @brief Access all available geofences.
     *
     * @return A reference of a geofence array.
     */
    const std::vector<Geofence>& GetGeofences() const noexcept
    {
        return this->geofences_;
    }

    /**
     * @brief Assign geofences.
     *
     * @param[in] fences A reference of new geofences.
     * @return Nothing.
     */
    void SetGeofences(const std::vector<Geofence>& fences)
    {
        this->geofences_ = fences;
    }

    /**
     * @brief Assign geofences.
     *
     * @param[in] fences A reference of new geofences.
     * @return Nothing.
     */
    void SetGeofences(std::vector<Geofence>&& fences)
    {
        this->geofences_ = std::move(fences);
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
        size_t align_size = timestamp_.GetSerializedSize<ALIGN>() + 
                            holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(geofences_.size()));
        for (std::size_t i = 0; i < geofences_.size(); ++i)
        {
            align_size += geofences_[i].GetSerializedSize<ALIGN>();
        }
        return align_size;
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
    template<typename S>
    void Serialize(S& serializer) const
    {
        uint32_t const count = geofences_.size();
        serializer << timestamp_ << count << holo::serialization::align;
        for (std::size_t i = 0; i < count; i++)
        {
            serializer << geofences_[i];
        }
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
    template<typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t count = 0;
        deserializer >> timestamp_ >> count >> holo::serialization::align;
        geofences_.resize(count);

        for (std::size_t i = 0; i < count; i++)
        {
            deserializer >> geofences_[i];
        }
    }

private:
    Timestamp                timestamp_; ///< Timestamp.
    std::vector<Geofence>    geofences_; ///< All the geofences within 3km.
};

/**
 * @}
 *
 */

} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_GEOFENCE_H_ */
