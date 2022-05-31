/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_navigation_response.h
 * @brief map navigation response
 * @author zhouhuishuang(zhouhuishuang@holomaitc.com)
 * @date "2021-12-22"
 */

#ifndef HOLO_MAP_MAP_NAVIGATION_RESPONSE_H_
#define HOLO_MAP_MAP_NAVIGATION_RESPONSE_H_

#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/map/common_def.h>

namespace holo
{
namespace map
{
/**
 * @brief RoutingSearchItem is used to describe a link or lane of routing path
 */
struct RoutingSearchItem
{
    /**
     * @brief Default constructor
     */
    RoutingSearchItem(): id{0}
    {
    }
    
    /**
     * @brief Constructor
     *
     * @param value Road id or lane id
     */
    RoutingSearchItem(KeyType value)
    {
        this->id = value;
    }

    KeyType id;  ///< road id or lane id

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
        return holo::serialization::SerializedSize<ALIGN>(id);
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
        serializer << holo::serialization::align << id << holo::serialization::align;
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
        deserializer >> holo::serialization::align >> id >> holo::serialization::align;
    }
};

/**
 * @brief The response of map navigation request
 * @ref Reference to: https://holomatic.feishu.cn/docs/doccn1NicKHSitx6iXW4ZagNZ2e
 *
 * @tparam size  Size of routing search item 
 */
template <size_t SIZE>
class RoutingSearchResponseT : public container::details::VectorBase<RoutingSearchItem, SIZE>
{
public:
    using Base = holo::container::details::VectorBase<RoutingSearchItem, SIZE>;

    /**
     * @brief Routing Status
     */
    enum class Status : uint8_t
    {
        UNKNOWN  = 0U,  ///< unknown
        STARTING = 1U,  ///< routing start
        RUNNING  = 2U,  ///< routing running
        YAWING   = 3U,  ///< yaw
        ENDING   = 4U,  ///< routing end
    };

    /**
     * @brief Routing Mode
     */
    enum class Mode : uint8_t
    {
        UNKNOWN    = 0U,
        NAVIGATION = 1U,
        CRUISE     = 2U,
    };

    /**
     * @brief routing data type
     */
    enum class RoutingType : uint8_t
    {
        UNKNOWN = 0U,
        LINK    = 1U,
        LANE    = 2U,
    };

    enum class RoutingErrorCode : uint16_t
    {
        NO_ERROR                  = 0U,
        RETRIEVER_ERROR           = 1U,   ///< retriever error
        REQUEST_PARAM_ERROR       = 2U,   ///< request parameter error
        REQUEST_POSITION_ERROR    = 3U,   ///< wrong start and end
        ROAD_CONNECT_ERROR        = 4U,   ///< road route is incorrectly connected
        FOUND_POI_ERROR           = 5U,   ///< found POI error
        FOUND_PARKING_SPACE       = 6U,   ///< found parking space error
        FOUND_ROAD_ERROR          = 7U,   ///< found road error
        FOUND_PARKING_LOT_ERROR   = 8U,   ///< found parking lot error
        FOUND_PARKING_FLOOR_ERROR = 9U,   ///< found parking floor error
        OTHER_ERROR               = 10U,  ///< other error
    };

    /**
     * @brief default constructor
     */
    RoutingSearchResponseT()
      : Base{}
      , response_id_{}
      , total_count_{}
      , start_index_{}
      , error_code_{RoutingErrorCode::NO_ERROR}
      , routing_type_{RoutingType::UNKNOWN}
      , status_{Status::UNKNOWN}
      , mode_{Mode::UNKNOWN}
      , rolling_counter_{}
      , timestamp_{}
    {
    }

    /**
     * @brief Set response id
     *
     * @param response_id
     */
    void SetResponseId(holo::uint64_t const response_id) noexcept
    {
        response_id_ = response_id;
    }

    /**
     * @brief Get response id
     *
     * @return uint64_t
     */
    holo::uint64_t GetResponseId() const noexcept
    {
        return response_id_;
    }

    /**
     * @brief Set link total count
     *
     * @param total_count
     */
    void SetTotalCount(holo::uint64_t const total_count) noexcept
    {
        total_count_ = total_count;
    }

    /**
     * @brief Get link total count
     *
     * @return uint64_t
     */
    holo::uint64_t GetTotalCount() const noexcept
    {
        return total_count_;
    }

    /**
     * @brief Set start index
     *
     * @param start_index
     */
    void SetStartIndex(holo::uint64_t const start_index) noexcept
    {
        start_index_ = start_index;
    }

    /**
     * @brief Get start index
     *
     * @return uint64_t
     */
    holo::uint64_t GetStartIndex() const noexcept
    {
        return start_index_;
    }

    /**
     * @brief Set routing type
     *
     * @param routing_type
     */
    void SetRoutingType(RoutingType const routing_type) noexcept
    {
        routing_type_ = routing_type;
    }

    /**
     * @brief Get routing type
     *
     * @return RoutingType
     */
    RoutingType GetRoutingType() const noexcept
    {
        return routing_type_;
    }

    /**
     * @brief Set routing status
     *
     * @param routing_type
     */
    void SetStatus(Status const status) noexcept
    {
        status_ = status;
    }

    /**
     * @brief Get routing status
     *
     * @return Status
     */
    Status GetStatus() const noexcept
    {
        return status_;
    }

    /**
     * @brief Set routing mode
     *
     * @param mode
     */
    void SetMode(Mode const mode) noexcept
    {
        mode_ = mode;
    }

    /**
     * @brief Get routing mode
     *
     * @return Mode
     */
    Mode GetMode() const noexcept
    {
        return mode_;
    }

    /**
     * @brief Set routing error code
     *
     * @param error_code
     */
    void SetRoutingErrorCode(RoutingErrorCode const error_code) noexcept
    {
        error_code_ = error_code;
    }

    /**
     * @brief Get routing error code
     *
     * @return RoutingErrorCode
     */
    RoutingErrorCode GetRoutingErrorCode() const noexcept
    {
        return error_code_;
    }

    /**
     * @brief Set rolling counter
     *
     * @param rolling_counter
     */
    void SetRollingCounter(holo::uint8_t const rolling_counter) noexcept
    {
        rolling_counter_ = rolling_counter;
    }

    /**
     * @brief Get rolling counter
     *
     * @return uint8_t
     */
    holo::uint8_t GetRollingCounter() const noexcept
    {
        return rolling_counter_;
    }

    /**
     * @brief Set timestamp
     *
     * @param timestamp
     */
    void SetTimestamp(Timestamp const timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Get timestamp
     *
     * @return Timestamp
     */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
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
               holo::serialization::SerializedSize<ALIGN>(
                   response_id_, total_count_, start_index_, static_cast<holo::uint16_t>(error_code_),
                   static_cast<holo::uint8_t>(routing_type_), static_cast<holo::uint8_t>(status_),
                   static_cast<holo::uint8_t>(mode_), rolling_counter_) +
               timestamp_.GetSerializedSize<ALIGN>();
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
        Base::template Serialize(serializer);
        serializer << response_id_ << total_count_ << start_index_ << static_cast<holo::uint16_t>(error_code_)
                   << static_cast<holo::uint8_t>(routing_type_) << static_cast<holo::uint8_t>(status_)
                   << static_cast<holo::uint8_t>(mode_) << rolling_counter_ << timestamp_;
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
        holo::uint16_t error_code   = 0U;
        holo::uint8_t  routing_type = 0U;
        holo::uint8_t  status       = 0U;
        holo::uint8_t  mode         = 0U;

        Base::template Deserialize(deserializer);
        deserializer >> response_id_ >> total_count_ >> start_index_ >> error_code >> routing_type >> status >> mode >>
            rolling_counter_ >> timestamp_;

        error_code_   = static_cast<RoutingErrorCode>(error_code);
        routing_type_ = static_cast<RoutingType>(routing_type);
        status_       = static_cast<Status>(status);
        mode_         = static_cast<Mode>(mode);
    }

private:
    holo::uint64_t   response_id_;      ///< response id
    holo::uint64_t   total_count_;      ///< link total count
    holo::uint64_t   start_index_;      ///< index of the current data starting point
    RoutingErrorCode error_code_;       ///< routing error code
    RoutingType      routing_type_;     ///< routing data type
    Status           status_;           ///< routing status
    Mode             mode_;             ///< routing mode
    holo::uint8_t    rolling_counter_;  ///< rolling counter
    Timestamp        timestamp_;        ///< timestamp
};
}  // namespace map
}  // namespace holo

#endif
