/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file data_package.h
 * @brief Define a package for transforming data between map local client and server.
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-11"
 */

#ifndef HOLO_MAP_SERVICE_DATA_PACKAGE_H_
#define HOLO_MAP_SERVICE_DATA_PACKAGE_H_

#include <vector>

#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/serialization/deserializer.h>
#include <holo/serialization/serializer.h>

namespace holo
{
namespace map
{
namespace service
{
namespace io
{

/**
 * @addtogroup session
 * @{
 *
 */

/**
 * @brief Data package for transforming map data from map local server to map local client.
 * 
 * @detail Map object will be serialized as byte stream, and the length of byte stream is various,
 *         maybe very small or maybe very large, if the length is small, we can transforming multiple
 *         map objects in a data package, but the max length must be less than the available capacity
 *         of the package payload.
 * 
 * @verbatim
 * +------+-------+-------+------+----------+----------+----------+---------+----------+----------+----------+--------+---------------+------+-------|
 * |Status|Pattern|TokenId|TileId|SequenceId|SliceIndex|SliceCount|ItemCount|ItemItemId|ItemStatus|ItemOffset|ItemSize|ItemFeatureType|......|Payload|
 * +------+-------+-------+------+----------+----------+----------+---------+----------+----------+----------+--------+---------------+------|-------|
 * |1     |1      |8      |8     |8         |4         |4         |4        |8         |1         |4         |4       |1              |      |       |
 * +------+-------+-------+------+----------+----------+----------+---------+----------+----------+----------+--------+---------------+------+-------|
 * @endverbatim
 * 
 * Unit: Byte.
 * Status: Define the status of this current package, 0 for success, others for failure.
 * TokenId: UUID for map local client, Different token has different privilege for accessing
 *          map data. This id is generated and managed by map department.
 * TileId: Tile id, refer to NDS Format Specification for details.
 * SequenceId: UUID for a single request(Package), and it must be unique in map client.
 * ItemCount: Item count in the package.
 * ItemStatus: Package item status, if 0, the item data is valid, otherwise the item data is invalid.
 * ItemOffset: Real data offset of a package item in the payload.
 * ItemSize: Real data size of a package item in the payload.
 * FeatureDataType: Feature type of map object, refer to holo::map::format::Base::FeatureDataType for details.
 * Others: A empty package occupies 20 bytes. If a package with only one item, the header will occupy
 *         56 bytes(39 + 1*(26))=(1+1+8+8+8+4+4+4+1*(8+1+4+4+1)).
 * 
 * @tparam N The max size of package buffer.
 * @tparam Buffer Container of byte stream buffer.
 */
template <size_t N = 512, typename Buffer = holo::container::Vector<holo::uint8_t, N>>
class DataPackage
{ 
public:
    /// Redefine types for internal enumeration.
    using StatusValueType   = holo::uint8_t;
    using PatternValueType  = holo::uint8_t;
    using TypeValueType     = holo::uint8_t;

    /**
     * @brief Status for DataPackage.
     */
    enum class Status : StatusValueType
    {
        STATUS_OK               = 0,    ///< No error.
        STATUS_SINGLE,                  ///< Single package contains complete data.
        STATUS_MULTIPLE,                ///< A data is sliced into multiple packages.
        STATUS_HEARTBEAT,               ///< Heartbeat package for keep the link between server and clients.
        STATUS_UNAUTHORIZED,            ///< Invalid token id.
        STATUS_REQUEST_INVALID,         ///< Bad request.
        STATUS_REQUEST_TIMEOUT,         ///< Request timeout.
        STATUS_INTERNAL_ERROR,          ///< Internal error in server.
        STATUS_OTHER_SDK_ERROR,         ///< External error in server. 
    };

    /**
     * @brief pattern for LMS(LocalMapService).
     */
    enum class Pattern : PatternValueType
    {
        /// If under REGION pattern, client request and receive map data by Region(default:
        /// radius 1000m).
        PATTERN_REGION  = 0,
        /// If under ROUTING pattern, client request and receive map data by routing path(
        /// Main path and sub paths).
        PATTERN_ROUTING,
    };

    /**
     * @brief Package item type.
     */
    enum class FeatureType : TypeValueType
    {
        ///< Placeholder.
        TYPE_UNKNOWN        = 0,
        /// For transporting an odometry between server and client in map local service,
        /// if the item type is TYPE_ODOMETRY, the current package must contains only
        /// one odometry.
        TYPE_ODOMETRY,
        TYPE_TILE,
        TYPE_ROAD,
        TYPE_LANE,
        TYPE_LANE_GROUP,
        TYPE_LANE_BOUNDARY,
        TYPE_SD_NODE,
        TYPE_SD_ROAD,
        TYPE_INTERSECTION,
        TYPE_OBJECT,
        TYPE_OBJECT_LINEAR_INFO,
        TYPE_OBJECT_REGIONAL_INFO,
        TYPE_OBJECT_PEDESTRIAN_CROSSING,
        TYPE_OBJECT_STOP_LINE,
        TYPE_OBJECT_TRAFFIC_LIGHT,
        TYPE_OBJECT_TRAFFIC_LIGHT_GROUP,
        TYPE_OBJECT_TRAFFIC_SIGN,
        TYPE_GEOFENCE,
        TYPE_ROUTING_PATH,
        TYPE_OBJECT_PARKING_LOT,
        TYPE_OBJECT_PARKING_FLOOR,
        TYPE_OBJECT_PARKING_BACKGROUND,
        TYPE_OBJECT_PARKING_POI,
        TYPE_OBJECT_PARKING_SPACE,
        TYPE_QUASI_DYNAMIC_LANE,
        TYPE_QUASI_DYNAMIC_LANE_GROUP,
        TYPE_QUASI_DYNAMIC_REGION,
    };

    /**
     * @brief Status for every package element.
     */
    enum class ItemStatus : StatusValueType
    {
        STATUS_OK           = 0,    ///< No error.
        STATUS_FORBIDDEN,           ///< Restrained item, no permission to access.
        STATUS_NOT_FOUND,           ///< Not exist.
        STATUS_FORCING_UPDATING,    ///< Client must update this item if it already exist.
    };

    /// Redefine inner type for package header elements.
    using StatusType            = Status;
    using PatternType           = Pattern;
    using TileIdType            = holo::uint64_t;
    using TokenIdType           = holo::uint64_t;
    using SequenceIdType        = holo::uint64_t;
    using SliceIndexType        = holo::uint32_t;
    using SliceCountType        = holo::uint32_t;
    using ItemIdType            = holo::uint64_t;
    using ItemCountType         = holo::uint32_t;
    using ItemOffsetType        = holo::uint32_t;
    using ItemStatusType        = ItemStatus;
    using ItemFeatureType       = FeatureType;

    /**
     * @brief Description for data item contained in current package.
     */
    struct ItemType
    {
        /// Data item feature type, refer to holo::map::format::Base::Feature for detail.
        ItemFeatureType     type    = ItemFeatureType::TYPE_UNKNOWN;
        /// Data item id.
        ItemIdType          id      = 0;
        /// Data item status, if not STATUS_OK, this item is invalid.
        ItemStatusType      status  = ItemStatusType::STATUS_OK;
        /// Data item offset in byte stream buffer. As input of Add(), the value is 0.
        ItemOffsetType      offset  = 0;
        /// Data item playload size.
        ItemOffsetType      size    = 0;
    };

    /// Redefine sequence type for ItemType.
    using ItemVectorType = std::vector<ItemType>;
    
    /**
     * @brief Copy assignment.
     * 
     * @param s Another object of class DataPackage.
     * @return Reference to the current package object.
     */
    DataPackage<N, Buffer>& operator = (DataPackage<N, Buffer> const& s)
    {
        if (&s == this)
        {
            return *this;
        }

        this->status_       = s.status_;
        this->pattern_      = s.pattern_;
        this->token_id_     = s.token_id_;
        this->tile_id_      = s.tile_id_;
        this->sequence_id_  = s.sequence_id_;
        this->slice_index_  = s.slice_index_;
        this->slice_count_  = s.slice_count_;
        this->items_        = s.items_;

        this->data_.clear();
        this->data_ = s.data_;

        return *this;
    }

    /**
     * @brief Copy constructor, just statement when operator = exist.
     */
    DataPackage<N, Buffer>(DataPackage<N, Buffer> const& s) = default;

    /**
     * @brief Copy constructor, just statement when operator = exist.
     */
    DataPackage<N, Buffer>() = default;

    /**
     * @brief Access the max capacity of a package object.
     * 
     * @return The max capacity value.
     */
    static std::size_t GetRawCapacity()
    {
        return N;
    }

    /**
     * @brief Access the availabe capacity of a package object.
     * 
     * @detail Available payload capacity equals raw capacity subtract header size of a package.
     * @param[in] count Item count, suppose items in buffer.
     * @return Availabe payload capacity.
     */
    static std::size_t GetRawAvailableCapacity(std::size_t const count = 1)
    {
        std::size_t const header = getHeaderSize(count);
        if (header > GetRawCapacity())
        {
            throw holo::exception::OutOfRangeException("Payload");
        }
        return GetRawCapacity() - header;
    }

    /**
     * @brief Access status value.
     * 
     * @return Status, 0: No error.
     */
    StatusType GetStatus() const noexcept
    {
        return this->status_;
    }

    /**
     * @brief Assign status value.
     * 
     * @param s Package status, 0: No error.
     */
    void SetStatus(StatusType const s) noexcept
    {
        this->status_ = s;
    }

    /**
     * @brief Access pattern value.
     * 
     * @return Pattern value.
     */
    PatternType GetPattern() const noexcept
    {
        return this->pattern_;
    }

    /**
     * @brief Assign pattern value. 
     *
     * @param[in] p Pattern value.
     */
    void SetPattern(PatternType const p) noexcept
    {
        this->pattern_ = p; 
    }

    /**
     * @brief Access token id.
     * 
     * @return Token id.
     */
    TokenIdType GetTokenId() const noexcept
    {
        return this->token_id_;
    }

    /**
     * @brief Assign token id.
     * 
     * @param t Token id.
     */
    void SetTokenId(TokenIdType const t) noexcept
    {
        this->token_id_ = t;
    }

    /**
     * @brief Access tile id.
     * 
     * @return Tile id, refer to NDS Format Specification for details.
     */
    TileIdType GetTileId() const noexcept
    {
        return this->tile_id_;
    }

    /**
     * @brief Assign tile id.
     * 
     * @param[in] id. A tile id.
     */
    void SetTileId(TileIdType const id) noexcept
    {
        this->tile_id_ = id;
    }

    /**
     * @brief Access sequence id.
     * 
     * @return Sequence id.
     */
    SequenceIdType GetSequenceId() const noexcept
    {
        return this->sequence_id_;
    }

    /**
     * @brief Assign sequence id.
     * 
     * @param[in] id Sequence id.
     */
    void SetSequenceId(SequenceIdType const id) noexcept
    {
        this->sequence_id_ = id;
    }

    /**
     * @brief Access slice index.
     * 
     * @return Slice index.
     */
    SliceIndexType GetSliceIndex() const noexcept
    {
        return this->slice_index_;
    }

    /**
     * @brief Assign slice index.
     * 
     * @param[in] index Slice index.
     */
    void SetSliceIndex(SliceIndexType const index) noexcept
    {
        this->slice_index_ = index;
    }

    /**
     * @brief Access slice count.
     * 
     * @return Slice count.
     */
    SliceCountType GetSliceCount() const noexcept
    {
        return this->slice_count_;
    }

    /**
     * @brief Assign slice count.
     * 
     * @param[in] Count Slice count.
     */
    void SetSliceCount(SliceCountType const count) noexcept
    {
        this->slice_count_ = count;
    }

    /**
     * @brief Access max available item count.
     * 
     * @param[in] size Data size of package item.
     * @retrun Max available item count.
     */
    static std::size_t GetMaxAvailableCount(std::size_t const size = 0)
    {
        std::size_t const header = getCommonHeaderSize();
        if (header > GetRawCapacity())
        {
            throw holo::exception::OutOfRangeException("MaxAvailableCount");
        }

        std::size_t const available = GetRawCapacity() - header;
        return (available / (getItemHeaderSize() + size));
    }

    /**
     * @brief Access data item count.
     * 
     * @return Data item count.
     */
    std::size_t GetCount() const
    {
        return this->items_.size();
    }

    /**
     * @brief Access item by index.
     * 
     * @param[in] index Index must be less than item count, otherwise will throw
     *            a OutOfRangeException.
     * @return An item value.
     */
    ItemType const& operator [] (std::size_t const index) const
    {
        std::size_t const count = this->items_.size();
        if (index >= count)
        {
            throw holo::exception::OutOfRangeException("Item");
        }
        return this->items_[index];
    }

    /**
     * @brief Access available capacity of payload buffer.
     * 
     * @return Available capacity size.
     */
    std::size_t GetAvailableCapacity() const
    {
        std::size_t const size = this->getHeaderSize(this->items_.size() + 1);
        std::size_t const capacity = (this->data_.capacity() > this->data_.size()
            ? (this->data_.capacity() - this->data_.size()) : 0);
        return (capacity > size ? (capacity - size) : 0);
    }

    /**
     * @brief Access data stream size.
     * 
     * * @detail Data stream is the slice of serialized map object.
     * 
     * @return Data stream size.
     */
    std::size_t GetDataSize() const
    {
        return this->data_.size();
    }

    /**
     * @brief Access data stream pointer.
     * 
     * @detail Data stream is the slice of serialized map object.
     * 
     * @return Data stream pointer.
     */
    holo::uint8_t const* GetData() const
    {
        return this->data_.data();
    }

    /**
     * @brief Add feature data to a package.
     * 
     * @param[in] id Payload data id.
     * @param[in] status Payload data status, 0: No error.
     * @param[in] type Data type, refer to holo::map::format::Base::FeatureType for details.
     * @param[in] d A pointer to a slice of a serialized map object.
     * @param[in] s Size of the slice, it must less equal than the capacity
     *          of data buffer(GetDataCapacity());
     */
    void AddData(ItemIdType const id, ItemStatusType const status, ItemFeatureType const type,
        holo::uint8_t const* d, std::size_t const s)
    {
        if (s > this->GetAvailableCapacity())
        {
            throw holo::exception::OutOfRangeException("Buffer");
        }
        if (s > std::numeric_limits<ItemOffsetType>::max())
        {
            throw holo::exception::OutOfRangeException("Parameter");
        }

        ItemType header;
        header.id       = id;
        header.status   = status;
        header.offset   = this->data_.size();
        header.size     = s;
        header.type     = type;
        this->items_.push_back(header);

        if (s > 0)
        {
            for (std::size_t i = 0; i < s; ++i)
            {
                this->data_.push_back(d[i]);
            }
        }
    }

    /**
     * @brief Clear the package.
     */
    void Clear()
    {
        this->status_         = StatusType::STATUS_OK;
        this->pattern_        = PatternType::PATTERN_REGION;
        this->token_id_       = 0;
        this->tile_id_        = 0;
        this->sequence_id_    = 0;
        this->items_.clear();
        this->data_.resize(0);
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 1U>
    size_t GetSerializedSize() const noexcept
    {
        holo::uint32_t const aligned_size = holo::serialization::AlignedSize<ALIGN>(
            this->getHeaderSize(this->items_.size()) + this->data_.size());
        return aligned_size;
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::exception::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        ItemCountType const count = static_cast<ItemCountType>(this->items_.size());
        serializer << holo::serialization::align
                   << static_cast<StatusValueType>(this->status_)
                   << static_cast<PatternValueType>(this->pattern_)
                   << this->token_id_  << this->tile_id_ << this->sequence_id_ 
                   << this->slice_index_ << this->slice_count_ << count;

        for (ItemType const& item : this->items_)
        {
            serializer << item.id << static_cast<StatusValueType>(item.status)
                << item.offset << item.size << static_cast<TypeValueType>(item.type);
        }

        //holo::uint8_t const* data = this->GetData();
        std::size_t const size =  this->data_.size();
        for (std::size_t i = 0; i < size; ++i)
        {
            serializer << this->data_[i];
        }
        serializer << holo::serialization::align;
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
        ItemCountType count = 0;
        StatusValueType status = 0;
        PatternValueType pattern = 0;

        deserializer >> holo::serialization::align >> status >> pattern >> this->token_id_ >> this->tile_id_
                     >> this->sequence_id_ >> this->slice_index_ >> this->slice_count_ >> count;

        this->status_ = static_cast<StatusType>(status);
        this->pattern_ = static_cast<PatternType>(pattern);

        this->items_.clear();
        this->items_.resize(count);

        std::size_t size = 0;
        for (std::size_t i = 0; i < count; ++i)
        {
            TypeValueType type = 0;

            deserializer >> this->items_[i].id  >> status >> this->items_[i].offset >>  this->items_[i].size >> type;

             this->items_[i].status = static_cast<ItemStatusType>(status);
             this->items_[i].type = static_cast<ItemFeatureType>(type);
            size += this->items_[i].size;
        }

        this->data_.resize(0);
        if (size > this->data_.capacity())
        {
            throw  holo::exception::OutOfRangeException("Buffer");
        }

        for (std::size_t i = 0; i < size; ++i)
        {
            holo::uint8_t data;
            deserializer >> data;
            this->data_.push_back(data);
        }
        deserializer >> holo::serialization::align;
    }

private:
    /**
     * @brief Access the header size.
     * 
     * @param[in] count Item count, suppose items in buffer.
     * @return The header size.
     */
    static std::size_t getHeaderSize(std::size_t const count)
    {
        return getCommonHeaderSize() + (count * getItemHeaderSize());
    }

    /**
     * @brief Access common header size.
     * 
     * @return Common header size.
     */
    static std::size_t getCommonHeaderSize()
    {
        return sizeof(StatusType) + sizeof(PatternType) + sizeof(TokenIdType) + sizeof(TileIdType) + 
            sizeof(SequenceIdType) + sizeof(SliceIndexType) + sizeof(SliceIndexType) + sizeof(ItemCountType);
    }

    /**
     * @brief Access package item header size.
     * 
     * @return Package item header size.
     */
    static std::size_t getItemHeaderSize()
    {
        return sizeof(ItemIdType) + sizeof(ItemStatusType) + sizeof(ItemOffsetType)*2 +
            sizeof(ItemFeatureType);
    }

private:
    /// Status of current package, if not STATUS_OK, this package is invalid.
    StatusType      status_      = StatusType::STATUS_OK;
    /// Pattern of current package, different patterns correspond to different behaviors
    /// on the client side.
    PatternType     pattern_     = PatternType::PATTERN_REGION;
    /// Token id, user identifier.
    TokenIdType     token_id_    = 0;
    /// Tile id, all the features in current package are contained in this map tile.
    TileIdType      tile_id_     = 0;
    /// UUID for data package.
    SequenceIdType  sequence_id_ = 0;
    /// Package slice index, work with data package status of STATUS_MULTIPLE. 
    SliceIndexType  slice_index_ = 0;
    /// Package slice count, work with data package status of STATUS_MULTIPLE,
    /// if with STATUS_SINGLE, this value is always 1.
    SliceCountType  slice_count_ = 0;
    /// Description of map data payload.
    ItemVectorType  items_;
    /// Map data payload.
    Buffer          data_;
}; ///< End of class DataPackage.

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo


#endif /* HOLO_MAP_SERVICE_DATA_PACKAGE_H_ */
