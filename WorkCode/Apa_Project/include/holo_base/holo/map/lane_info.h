/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_info.h
 * @brief lane_info: provide lane info .
 * @author zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-11-26"
 */

#ifndef HOLO_BASE_INCLUDE_HOLO_MAP_LANE_INFO_H_
#define HOLO_BASE_INCLUDE_HOLO_MAP_LANE_INFO_H_

#include <limits>
#include <memory>
#include <vector>

#include <holo/map/lane_mark_info.h>
#include <holo/map/map_enum.h>
#include <holo/map/map_msg_base.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace map
{
/**
 * @addtogroup map
 * @{
 *
 */
class LaneInfo : public MapMsgBase
{
public:
    using PtrLaneInfo      = ::std::shared_ptr<LaneInfo>;
    using ConstPtrLaneInfo = ::std::shared_ptr<LaneInfo const>;

public:
    /**
     * @brief Constructor
     *
     */
    LaneInfo() noexcept
    : MapMsgBase(kLaneInfoIndicatorSize,
                static_cast<::holo::uint8_t>(LaneInfoValueUint32::LANE_INFO_VALUE_UINT32_MAX),
                static_cast<::holo::uint8_t>(LaneInfoValueFloat32::LANE_INFO_VALUE_FLOAT32_MAX))
    {
    }

    /**
     * @brief Destroy the lane info
     *
     */
    ~LaneInfo() noexcept
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param[in] other
     */
    LaneInfo(const LaneInfo& other) noexcept
    : MapMsgBase(other)
    , id_(other.id_)
    , seq_(other.seq_)
    , type_(other.type_)
    , left_mark_info_(other.left_mark_info_)
    , right_mark_info_(other.right_mark_info_)
    , vec_succ_ids_(other.vec_succ_ids_)
    , vec_pre_ids_(other.vec_pre_ids_)
    , vec_points_(other.vec_points_)
    {
    }

    /**
     * @brief Copy constructor as rvalue
     *
     * @param[in] other
     */
    LaneInfo(LaneInfo&& other) noexcept
    : MapMsgBase(::std::move(other))
    , id_(other.id_)
    , seq_(other.seq_)
    , type_(other.type_)
    , left_mark_info_(std::move(other.left_mark_info_))
    , right_mark_info_(std::move(other.right_mark_info_))
    , vec_succ_ids_(std::move(other.vec_succ_ids_))
    , vec_pre_ids_(std::move(other.vec_pre_ids_))
    , vec_points_(std::move(other.vec_points_))
    {
    }

    /**
     * @brief Assignment operator
     *
     * @param[in] other
     * @return LaneInfo&
     */
    LaneInfo& operator=(const LaneInfo& other) noexcept
    {
        if (this != &other)
        {
            MapMsgBase::operator   =(other);
            this->id_              = other.id_;
            this->seq_             = other.seq_;
            this->type_            = other.type_;
            this->left_mark_info_  = other.left_mark_info_;
            this->right_mark_info_ = other.right_mark_info_;
            this->vec_succ_ids_    = other.vec_succ_ids_;
            this->vec_pre_ids_     = other.vec_pre_ids_;
            this->vec_points_      = other.vec_points_;
        }
        return *this;
    }

    /**
     * @brief Assignment operator as rvalue
     *
     * @param[in] other
     * @return LaneInfo&
     */
    LaneInfo& operator=(LaneInfo&& other) noexcept
    {
        if (this != &other)
        {
            MapMsgBase::operator   =(::std::move(other));
            this->id_              = other.id_;
            this->seq_             = other.seq_;
            this->type_            = other.type_;
            this->left_mark_info_  = ::std::move(other.left_mark_info_);
            this->right_mark_info_ = ::std::move(other.right_mark_info_);
            ::std::swap(this->vec_succ_ids_, other.vec_succ_ids_);
            ::std::swap(this->vec_pre_ids_, other.vec_pre_ids_);
            ::std::swap(this->vec_points_, other.vec_points_);
        }
        return *this;
    }

    /**
     * @brief Set ID
     *
     * @param[in] id
     */
    void SetId(const KeyValue id) noexcept
    {
        this->id_ = id;
    }

    /**
     * @brief Get id
     *
     */
    KeyValue GetId() const noexcept
    {
        return this->id_;
    }

    /**
     * @brief Set the sequence starting from 0
     *
     * @param[in] seq
     */
    void SetSeq(const SeqValue seq) noexcept
    {
        this->seq_ = seq;
    }

    /**
     * @brief Get the seq
     *
     * @return SeqValue
     */
    SeqValue GetSeq() const noexcept
    {
        return this->seq_;
    }

    /**
     * @brief Set the max speed limit, unit is m/s
     *
     * @param[in] speed
     */
    void SetMaxSpeedLimit(const ::holo::float32_t speed) noexcept
    {
        this->float32_values_[static_cast<::std::size_t>(LaneInfoValueFloat32::LANE_INFO_VALUE_MAX_LIMIT_SPEED)] =
            speed;
    }

    /**
     * @brief Get the max speed limit, unit is m/s
     *
     * @return ::holo::float32_t
     */
    ::holo::float32_t GetMaxSpeedLimit() const noexcept
    {
        return this->float32_values_[static_cast<::std::size_t>(LaneInfoValueFloat32::LANE_INFO_VALUE_MAX_LIMIT_SPEED)];
    }

    /**
     * @brief Set the min speed limit, unit is m/s
     *
     * @param[in] speed
     */
    void SetMinSpeedLimit(const ::holo::float32_t speed) noexcept
    {
        this->float32_values_[static_cast<::std::size_t>(LaneInfoValueFloat32::LANE_INFO_VALUE_MIN_LIMIT_SPEED)] =
            speed;
    }

    /**
     * @brief Get the min speed limit, unit is m/s
     *
     * @return ::holo::float32_t
     */
    ::holo::float32_t GetMinSpeedLimit() const noexcept
    {
        return this->float32_values_[static_cast<::std::size_t>(LaneInfoValueFloat32::LANE_INFO_VALUE_MIN_LIMIT_SPEED)];
    }

    /**
     * @brief Set the width, unit is m
     *
     * @param[in] width
     */
    void SetWidth(const ::holo::float32_t width) noexcept
    {
        this->float32_values_[static_cast<::std::size_t>(LaneInfoValueFloat32::LANE_INFO_VALUE_WIDTH)] = width;
    }

    /**
     * @brief Get the width, unit is m
     *
     * @return ::holo::float32_t
     */
    ::holo::float32_t GetWidth() const noexcept
    {
        return this->float32_values_[static_cast<::std::size_t>(LaneInfoValueFloat32::LANE_INFO_VALUE_WIDTH)];
    }

    /**
     * @brief Set the length, unit is m
     *
     * @param[in] length
     */
    void SetLength(const ::holo::float32_t length) noexcept
    {
        this->float32_values_[static_cast<::std::size_t>(LaneInfoValueFloat32::LANE_INFO_VALUE_LENGTH)] = length;
    }

    /**
     * @brief Get the length, unit is m
     *
     * @return ::holo::float32_t
     */
    ::holo::float32_t GetLength() const noexcept
    {
        return this->float32_values_[static_cast<::std::size_t>(LaneInfoValueFloat32::LANE_INFO_VALUE_LENGTH)];
    }
    
    /**
     * @brief Set the type
     *
     * @param[in] type
     */
    void SetType(const ::holo::map::CommonLaneType type) noexcept
    {
        this->type_ = type;
    }

    /**
     * @brief Get the type
     *
     * @return CommonLaneType
     */
    ::holo::map::CommonLaneType GetType() const noexcept
    {
        return this->type_;
    }

    /**
     * @brief Set the left mark
     *
     * @param[in] info
     */
    void SetLeftMark(const LaneMarkInfo& info) noexcept
    {
        this->left_mark_info_ = info;
    }

    /**
     * @brief Set the left mark as rvalue
     *
     * @param[in] info
     */
    void SetLeftMark(LaneMarkInfo&& info) noexcept
    {
        if (&this->left_mark_info_ != &info)
        {
            this->left_mark_info_ = ::std::move(info);
        }
    }

    /**
     * @brief Get the left mark
     *
     * @return const LaneMarkInfo&
     */
    const LaneMarkInfo& GetLeftMark() const noexcept
    {
        return this->left_mark_info_;
    }

    /**
     * @brief Set the right mark
     *
     * @param[in] info
     */
    void SetRightMark(const LaneMarkInfo& info) noexcept
    {
        this->right_mark_info_ = info;
    }

    /**
     * @brief Set the right mark as rvalue
     *
     * @param[in] info
     */
    void SetRightMark(LaneMarkInfo&& info) noexcept
    {
        if (&this->right_mark_info_ != &info)
        {
            this->right_mark_info_ = ::std::move(info);
        }
    }

    /**
     * @brief Get the right mark
     *
     * @return const LaneMarkInfo&
     */
    const LaneMarkInfo& GetRightMark() const noexcept
    {
        return this->right_mark_info_;
    }

    /**
     * @brief Set the succ lane ids
     *
     * @param[in] ids
     */
    void SetSuccLaneIds(const ::std::vector<KeyValue>& ids) noexcept
    {
        this->vec_succ_ids_ = ids;
    }

    /**
     * @brief Set the succ lane ids as rvalue
     *
     * @param[in] ids
     */
    void SetSuccLaneIds(::std::vector<KeyValue>&& ids) noexcept
    {
        ::std::swap(this->vec_succ_ids_, ids);
    }

    /**
     * @brief Get the succ lane ids
     *
     * @return const ::std::vector<KeyValue>&
     */
    const ::std::vector<KeyValue>& GetSuccLaneIds() const noexcept
    {
        return this->vec_succ_ids_;
    }

    /**
     * @brief Set the pre lane ids
     *
     * @param[in] ids
     */
    void SetPreLaneIds(const ::std::vector<KeyValue>& ids) noexcept
    {
        this->vec_pre_ids_ = ids;
    }

    /**
     * @brief Set the pre lane ids as rvalue
     *
     * @param[in] ids
     */
    void SetPreLaneIds(::std::vector<KeyValue>&& ids) noexcept
    {
        ::std::swap(this->vec_pre_ids_, ids);
    }

    /**
     * @brief Get the pre lane ids
     *
     * @return const ::std::vector<KeyValue>&
     */
    const ::std::vector<KeyValue>& GetPreLaneIds() const noexcept
    {
        return this->vec_pre_ids_;
    }

    /**
     * @brief Set the reference points
     *
     * @param[in] points
     */
    void SetRefPoints(const ::std::vector<::holo::geometry::Point3d>& points) noexcept
    {
        this->vec_points_ = points;
    }

    /**
     * @brief Set the reference points
     *
     * @param[in] points
     */
    void SetRefPoints(::std::vector<::holo::geometry::Point3d>&& points) noexcept
    {
        ::std::swap(this->vec_points_, points);
    }

    /**
     * @brief Get the reference points
     *
     * @return const ::std::vector<::holo::geometry::Point3d>&
     */
    const ::std::vector<::holo::geometry::Point3d>& GetRefPoints() const noexcept
    {
        return this->vec_points_;
    }
    
    /**
     * @brief Serialize all elements to string
     *
     * @return ::std::string
     */
    ::std::string ToString() const noexcept
    {
        // TODO zhaofx 2019-08-23: Need to serialize all elements.
        ::std::ostringstream oss;
        oss << "Id:" << GetId() << "; ";
        oss << "Seq:" << static_cast<int>(GetSeq()) << "; ";
        oss << "MaxSpeed:" << GetMaxSpeedLimit() << "; ";
        oss << "MinSpeed:" << GetMinSpeedLimit() << "; ";
        oss << "Width:" << GetWidth() << "; ";
        oss << "Length:" << GetLength() << "; ";
        oss << "Type:" << GetType() << "; ";
        oss << "Point size:" << GetRefPoints().size() << "; ";
        oss << " \n LeftMark:" << left_mark_info_.ToString() << "; ";
        oss << " \n RightMark:" << right_mark_info_.ToString() << "; ";
        return oss.str();
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
        uint32_t aligned_size = MapMsgBase::GetSerializedSize<ALIGN>();
        aligned_size += holo::serialization::SerializedSize<ALIGN>(static_cast<uint64_t>(id_), static_cast<uint8_t>(seq_),
                                                           static_cast<uint8_t>(type_));
        aligned_size += left_mark_info_.GetSerializedSize<ALIGN>() + right_mark_info_.GetSerializedSize<ALIGN>();
        aligned_size += holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(vec_succ_ids_.size()));
        aligned_size += holo::serialization::AlignedSize<ALIGN>(vec_succ_ids_.size() * sizeof(KeyValue));
        aligned_size += holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(vec_pre_ids_.size()));
        aligned_size += holo::serialization::AlignedSize<ALIGN>(vec_pre_ids_.size() * sizeof(KeyValue));
        aligned_size += holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(vec_points_.size()));
        if (vec_points_.size() > 0)
        {
            aligned_size += vec_points_.size() * vec_points_[0].GetSerializedSize<ALIGN>();
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
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        uint32_t vec_succ_ids_size = static_cast<uint32_t>(vec_succ_ids_.size());
        uint32_t vec_pre_ids_size  = static_cast<uint32_t>(vec_pre_ids_.size());
        uint32_t vec_points_size   = static_cast<uint32_t>(vec_points_.size());

        MapMsgBase::Serialize(serializer);
        serializer << holo::serialization::align << static_cast<uint64_t>(id_) << static_cast<uint8_t>(seq_)
                   << static_cast<uint8_t>(type_) << left_mark_info_ << right_mark_info_;

        serializer << vec_succ_ids_size;
        for (uint32_t i = 0; i < vec_succ_ids_size; ++i)
        {
            serializer << static_cast<uint64_t>(vec_succ_ids_[i]);
        }

        serializer << vec_pre_ids_size;
        for (uint32_t i = 0; i < vec_pre_ids_size; ++i)
        {
            serializer << static_cast<uint64_t>(vec_pre_ids_[i]);
        }
        serializer << vec_points_size;
        for (uint32_t i = 0; i < vec_points_size; ++i)
        {
            serializer << vec_points_[i];
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
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        ::holo::uint32_t i                 = 0;
        ::holo::uint64_t id                = 0;
        ::holo::uint8_t  seq               = 0;
        ::holo::uint8_t  type              = 0;
        ::holo::uint32_t vec_succ_ids_size = 0;
        ::holo::uint32_t vec_pre_ids_size  = 0;
        ::holo::uint32_t vec_points_size   = 0;

        MapMsgBase::Deserialize(deserializer);
        deserializer >> id >> seq >> type >> left_mark_info_ >> right_mark_info_ >> vec_succ_ids_size;
        vec_succ_ids_.resize(vec_succ_ids_size);
        for (i = 0; i < vec_succ_ids_size; ++i)
        {
            uint64_t cur_val = 0;
            deserializer >> cur_val;
            vec_succ_ids_[i] = static_cast<KeyValue>(cur_val);
        }
        deserializer >> vec_pre_ids_size;
        vec_pre_ids_.resize(vec_pre_ids_size);
        for (i = 0; i < vec_pre_ids_size; ++i)
        {
            uint64_t cur_val = 0;
            deserializer >> cur_val;
            vec_pre_ids_[i] = static_cast<KeyValue>(cur_val);
        }
        deserializer >> vec_points_size;
        vec_points_.resize(vec_points_size);
        for (i = 0; i < vec_points_size; ++i)
        {
            deserializer >> vec_points_[i];
        }
        deserializer >> holo::serialization::align;

        id_   = static_cast<KeyValue>(id);
        seq_  = static_cast<SeqValue>(seq);
        type_ = static_cast<CommonLaneType>(type);
    }

private:
    // Use to limit MapMsgBase indicators valid size.
    static const ::holo::uint8_t kLaneInfoIndicatorSize = 0U;
    /// record all uint32 type element
    enum class LaneInfoValueUint32 : ::holo::uint8_t
    {
        LANE_INFO_VALUE_UINT32_MAX  ///< the size of uint32 type element used to resize vector member in constructor.
    };

    /// record all float32 type element
    enum class LaneInfoValueFloat32 : ::holo::uint8_t
    {
        LANE_INFO_VALUE_WIDTH = 0,        ///< lane width
        LANE_INFO_VALUE_LENGTH,           ///< lane length
        LANE_INFO_VALUE_MAX_LIMIT_SPEED,  ///< lane max speed limit
        LANE_INFO_VALUE_MIN_LIMIT_SPEED,  ///< lane min speed limit

        LANE_INFO_VALUE_FLOAT32_MAX  ///< the size of float32 type element used to resize vector member in constructor.
    };

private:
    /// id
    KeyValue id_{::std::numeric_limits<KeyValue>::max()};
    /// seq
    SeqValue seq_{::std::numeric_limits<SeqValue>::max()};
    /// type
    CommonLaneType type_{CommonLaneType::LANE_TYPE_UNDEFINED};
    /// left lane mark
    LaneMarkInfo left_mark_info_;
    /// rigth lane mark
    LaneMarkInfo right_mark_info_;
    /// succ ids
    ::std::vector<KeyValue> vec_succ_ids_;
    /// pre ids
    ::std::vector<KeyValue> vec_pre_ids_;
    /// reference points
    ::std::vector<::holo::geometry::Point3d> vec_points_;
};

/**
 * @}
 *
 */
}  // namespace map
}  // namespace holo
#endif  // HOLO_BASE_INCLUDE_HOLO_MAP_LANE_INFO_H_
