/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file serialization.h
 * @brief Session serialization interface.
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-12"
 */

#ifndef HOLO_MAP_SERVICE_SESSION_SERIALIZATION_H_
#define HOLO_MAP_SERVICE_SESSION_SERIALIZATION_H_

#include <vector>
#include <memory>

#include <holo/log/hololog.h>

#include <holo/map/common/types.h>
#include <holo/map/service/io/types.h>
#include <holo/map/service/session/utility.h>

namespace holo
{
namespace map
{
namespace service
{
namespace session
{

/**
 * @addtogroup session
 * @{
 *
 */

/**
 * @brief Map data package header.
 * 
 */
struct Header
{
    /// Redefine data package type for inner members.
    using DataType              = holo::map::service::session::SessionType;
    using StatusType            = DataType::StatusType;
    using PatternType           = DataType::PatternType;
    using TileIdType            = DataType::TileIdType;
    using TokenIdType           = DataType::TokenIdType;
    using SequenceIdType        = DataType::SequenceIdType;
    using SliceIndexType        = DataType::SliceIndexType;
    using SliceCountType        = DataType::SliceCountType;
    using ItemIdType            = DataType::ItemIdType;
    using ItemSliceIndexType    = DataType::ItemCountType;
    using ItemSliceCountType    = DataType::ItemCountType;
    using ItemStatusType        = DataType::ItemStatusType;
    using ItemFeatureType       = DataType::ItemFeatureType;
    using SessionType           = DataType;

    /// Session status, if is STATUS_OK, this session is valid.
    StatusType             status              = StatusType::STATUS_OK;
    PatternType            pattern             = PatternType::PATTERN_REGION;
    /// Tile id.
    TileIdType             tile_id             = 0;
    /// Token id.
    TokenIdType            token_id            = 0;
    /// Data package sequence id.
    SequenceIdType         sequence_id         = 0;
    SliceIndexType         slice_index         = 0;
    SliceCountType         slice_count         = 0;

    ItemIdType             item_id             = 0;
    ItemStatusType         item_status         = ItemStatusType::STATUS_OK;
    ItemFeatureType        item_type           = ItemFeatureType::TYPE_UNKNOWN;

    /**
     * @brief Marshal a header to a JSON string.
     * 
     * @return A JSON string.
     */
    static std::string FormatToString(Header const& header);
};

/**
 * @brief Session serialization interface.
 * 
 * @tparam N Buffer size, it must be larger than the biggest single map object.
 */
class Serialization
{
public:
    /// Redefine inner type for inner members.
    using SessionType           = holo::map::service::session::SessionType;
    using SessionPtrType        = holo::map::service::session::SessionPtrType;
    using SessionPtrVectorType  = holo::map::service::session::SessionPtrVectorType;

    /**
     * @brief Constructor.
     */
    Serialization() = default;

    /**
     * @brief Destructor.
     */
    virtual ~Serialization() = default;

    Serialization(Serialization const&) = delete;
    Serialization(Serialization&&) = delete;

    Serialization& operator = (Serialization const&) = delete;
    Serialization& operator = (Serialization&&) = delete;

    /**
     * @brief Clear inner concreate buffer and inner cache.
     */
    virtual void Clear() = 0;

    /**
     * @brief Access the request data buffer capacity.
     * 
     * @return The request data buffer capacity.
     */
    virtual std::size_t GetCapacity() const;

    /**
     * @brief Calculate the required session count for inner concrete data.
     * 
     * @return Required session count.
     */
    virtual std::size_t GetSessionCount() const = 0;

    /**
     * @brief Serialize concreate data to session slices.
     * 
     * @param[in] header Session header information.
     * @param[out] sessions Session slices.
     * 
     * @return true: No error.
     *         false: An error occurs in this function, please refer to the log for the details.
     */
    virtual holo::bool_t Serialize(Header const& header, SessionPtrVectorType& sessions);

    /**
     * @brief Deserialize session slices to map object.
     * 
     * @param[in] sessions A complete data slices.
     * @param[out] header Session header information.
     * 
     * @return true: No error.
     *         false: An error occurs in this function, please refer to the log for the details.
     */
    virtual holo::bool_t Deserialize(SessionPtrVectorType const& sessions, Header& header);

    /**
     * @brief Assign verbose flag.
     * 
     * @param[in] v If true, serializer or deserializer will print debug message to log.
     */
    virtual void SetVerbose(holo::bool_t const v) noexcept;

protected:

    /**
     * @brief Serialize inner data to inner buffer.
     */
    virtual holo::bool_t serialize(Header const& header, SessionPtrType ptr) = 0;

    /**
     * @brief Deserialize inner buffer to inner concrete data.
     */
    virtual holo::bool_t deserialize(SessionPtrType ptr, Header& header) = 0;

protected:
    holo::bool_t                        verbose_ = false;   ///< If true, print debug message to log.
}; ///< End of class Serialization

/**
 * @}
 *
 */

} ///< namespace session
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_SESSION_SERIALIZATION_H_ */
