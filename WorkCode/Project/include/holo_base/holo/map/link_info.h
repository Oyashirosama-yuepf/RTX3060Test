/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file link_info.h
 * @brief link_info: provide link info.
 * @author zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-11-26"
 */

#ifndef HOLO_BASE_INCLUDE_HOLO_MAP_LINK_INFO_H_
#define HOLO_BASE_INCLUDE_HOLO_MAP_LINK_INFO_H_

#include <memory>
#include <vector>

#include <holo/map/common_def.h>
#include <holo/map/lane_info.h>
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
class LinkInfo : public MapMsgBase
{
public:
    using PtrLinkInfo      = ::std::shared_ptr<LinkInfo>;
    using ConstPtrLinkInfo = ::std::shared_ptr<LinkInfo const>;

public:
    /**
     * @brief Construct a new Link Info
     *
     */
    LinkInfo() noexcept
    : MapMsgBase(static_cast<::holo::uint8_t>(LinkInfoValueBool::LINK_INFO_INDICATOR_MAX),
                static_cast<::holo::uint8_t>(LinkInfoValueUint32::LINK_INFO_VALUE_UINT32_MAX),
                static_cast<::holo::uint8_t>(LinkInfoValueFloat32::lINK_INFO_VALUE_FLOAT_MAX))
    {
    }

    /**
     * @brief Destroy the Link Info
     *
     */
    ~LinkInfo() noexcept
    {
    }

    /**
     * @brief Construct a new Link Info
     *
     * @param[in] other
     */
    LinkInfo(const LinkInfo& other) noexcept
    : MapMsgBase(other)
    , link_id_(other.link_id_)
    , lane_count_(other.lane_count_)
    , vec_lanes_info_(other.vec_lanes_info_)
    , ref_points_(other.ref_points_)
    {
    }

    /**
     * @brief Construct a new link info as rvalue
     *
     * @param[in] other
     */
    LinkInfo(LinkInfo&& other) noexcept
    : MapMsgBase(::std::move(other))
    , link_id_(other.link_id_)
    , lane_count_(other.lane_count_)
    , vec_lanes_info_(std::move(other.vec_lanes_info_))
    , ref_points_(std::move(other.ref_points_))
    {
    }

    /**
     * @brief Assignment operator
     *
     * @param[in] other
     * @return LinkInfo&
     */
    LinkInfo& operator=(const LinkInfo& other) noexcept
    {
        if (this != &other)
        {
            MapMsgBase::operator  =(other);
            this->link_id_        = other.link_id_;
            this->lane_count_     = other.lane_count_;
            this->vec_lanes_info_ = other.vec_lanes_info_;
            this->ref_points_     = other.ref_points_;
        }
        return *this;
    }

    /**
     * @brief  Assignment operator as rvalue
     *
     * @param[in] other
     * @return LinkInfo&
     */
    LinkInfo& operator=(LinkInfo&& other) noexcept
    {
        if (this != &other)
        {
            MapMsgBase::operator=(::std::move(other));
            this->link_id_      = other.link_id_;
            this->lane_count_   = other.lane_count_;
            ::std::swap(this->vec_lanes_info_, other.vec_lanes_info_);
            ::std::swap(this->ref_points_, other.ref_points_);
        }
        return *this;
    }

    /**
     * @brief Set current link id
     *
     * @param[in] id
     */
    void SetID(const KeyValue id) noexcept
    {
        this->link_id_ = id;
    }

    /**
     * @brief Get current link id
     *
     * @return KeyValue
     */
    KeyValue GetID() const noexcept
    {
        return this->link_id_;
    }

    /**
     * @brief Set the max speed limit, unit is m/s
     *
     * @param[in] speed
     */
    void SetMaxSpeedLimit(const ::holo::float32_t speed) noexcept
    {
        this->float32_values_[static_cast<::std::size_t>(LinkInfoValueFloat32::LINK_INFO_VALUE_MAX_LIMIT_SPEED)] =
            speed;
    }

    /**
     * @brief Get the max speed limit, unit is m/s
     *
     * @return ::holo::float32_t
     */
    ::holo::float32_t GetMaxSpeedLimit() const noexcept
    {
        return this->float32_values_[static_cast<::std::size_t>(LinkInfoValueFloat32::LINK_INFO_VALUE_MAX_LIMIT_SPEED)];
    }

    /**
     * @brief Set the min speed limit, unit is m/s
     *
     * @param[in] speed
     */
    void SetMinSpeedLimit(const ::holo::float32_t speed) noexcept
    {
        this->float32_values_[static_cast<::std::size_t>(LinkInfoValueFloat32::LINK_INFO_VALUE_MIN_LIMIT_SPEED)] =
            speed;
    }

    /**
     * @brief Get the min speed limit, unit is m/s
     *
     * @return ::holo::float32_t
     */
    ::holo::float32_t GetMinSpeedLimit() const noexcept
    {
        return this->float32_values_[static_cast<::std::size_t>(LinkInfoValueFloat32::LINK_INFO_VALUE_MIN_LIMIT_SPEED)];
    }

    /**
     * @brief Set the width, unit is m
     *
     * @param[in] width
     */
    void SetWidth(const ::holo::float32_t width) noexcept
    {
        this->float32_values_[static_cast<::std::size_t>(LinkInfoValueFloat32::LINK_INFO_VALUE_WIDTH)] = width;
    }

    /**
     * @brief Get the width, unit is m
     *
     * @return ::holo::float32_t
     */
    ::holo::float32_t GetWidth() const noexcept
    {
        return this->float32_values_[static_cast<::std::size_t>(LinkInfoValueFloat32::LINK_INFO_VALUE_WIDTH)];
    }

    /**
     * @brief Set the length, unit is m
     *
     * @param[in] length
     */
    void SetLength(const ::holo::float32_t length) noexcept
    {
        this->float32_values_[static_cast<::std::size_t>(LinkInfoValueFloat32::LINK_INFO_VALUE_LENGTH)] = length;
    }

    /**
     * @brief Get the length, unit is m
     *
     * @return ::holo::float32_t
     */
    ::holo::float32_t GetLength() const noexcept
    {
        return this->float32_values_[static_cast<::std::size_t>(LinkInfoValueFloat32::LINK_INFO_VALUE_LENGTH)];
    }

    /**
     * @brief Set the lane count
     *
     * @param[in] count
     */
    void SetLaneCount(const ::holo::uint8_t count) noexcept
    {
        this->lane_count_ = count;
    }

    /**
     * @brief Get the lane count
     *
     * @return ::holo::uint8_t
     */
    ::holo::uint8_t GetLaneCount() const noexcept
    {
        return this->lane_count_;
    }

    /**
     * @brief Set the lane infos, index from 0 to (lane_count -1)
     *
     * @param[in] info
     */
    void SetLaneInfos(const ::std::vector<LaneInfo>& info) noexcept
    {
        this->vec_lanes_info_ = info;
    }

    /**
     * @brief Set the lane infos as rvalue, index from 0 to (lane_count -1)
     *
     * @param[in] info
     */
    void SetLaneInfos(::std::vector<LaneInfo>&& info) noexcept
    {
        ::std::swap(this->vec_lanes_info_, info);
    }

    /**
     * @brief Get the lane infos, index from 0 to (lane_count-1)
     *
     * @return const ::std::vector<LaneInfo>&
     */
    const ::std::vector<LaneInfo>& GetLaneInfos() const noexcept
    {
        return this->vec_lanes_info_;
    }

    /**
     * @brief Set the reference points
     *
     * @param[in] points
     */
    void SetRefPoints(const ::std::vector<::holo::geometry::Point3d>& points) noexcept
    {
        this->ref_points_ = points;
    }

    /**
     * @brief Set the reference points as rvalue
     *
     * @param[in] points
     */
    void SetRefPoints(::std::vector<::holo::geometry::Point3d>&& points) noexcept
    {
        ::std::swap(this->ref_points_, points);
    }

    /**
     * @brief Get the reference points
     *
     * @return const ::std::vector<::holo::geometry::Point3d>&
     */
    const ::std::vector<::holo::geometry::Point3d>& GetRefPoints() const noexcept
    {
        return this->ref_points_;
    }

    /**
     * @brief check is on route, true on main road false on ramp
     * @return true/false
     */
    bool IsOnRoute() const noexcept
    {
        return this->indicators_.test(static_cast<::std::size_t>(LinkInfoValueBool::IS_ON_ROUTE));
    }

    /**
     * @brief set is on the route
     * @param[in] a is on the route
     */
    void SetIsOnRoute(const bool a) noexcept
    {
        (void)this->indicators_.set(static_cast<::std::size_t>(LinkInfoValueBool::IS_ON_ROUTE), a);
    }

    /**
     * @brief check ego car is on bifurcation
     * @param[in] a ego car is on bifurcation
     */
    void SetIsOnBifurcation(const bool a) noexcept
    {
        (void)this->indicators_.set(static_cast<::std::size_t>(LinkInfoValueBool::IS_ON_BIFURCATION_AREA), a);
    }

    /**
     * @brief check ego car is on bifurcation
     * @return true/false
     */
    bool IsOnBifurcation() const noexcept
    {
        return this->indicators_.test(static_cast<::std::size_t>(LinkInfoValueBool::IS_ON_BIFURCATION_AREA));
    }
    
    /**
     * @brief Serialize all elements to string.
     *
     * @return ::std::string
     */
    ::std::string ToString() const noexcept
    {
        // TODO zhaofx 2019-08-23: Need to serialize all elements.
        ::std::ostringstream oss;
        oss << "LinkId:" << GetID() << "; ";
        oss << "Width:" << GetWidth() << "; ";
        oss << "Length:" << GetLength() << "; ";
        oss << "MaxLimitSpeed:" << GetMaxSpeedLimit() << "; ";
        oss << "MinLimitSpeed:" << GetMinSpeedLimit() << "; ";
        oss << "LaneNum:" << static_cast<int>(GetLaneCount()) << "; ";
        oss << "Point size:" << GetRefPoints().size() << "; ";

        for (const auto& iter : GetLaneInfos())
        {
            oss << " \n Lane:" << iter.ToString() << "; ";
        }

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
        aligned_size += holo::serialization::SerializedSize<ALIGN>(static_cast<uint64_t>(link_id_), lane_count_);
        aligned_size += holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(vec_lanes_info_.size()));
        if (vec_lanes_info_.size() > 0)
        {
            for (size_t i = 0; i < vec_lanes_info_.size(); ++i)
            {
                aligned_size += vec_lanes_info_[i].GetSerializedSize<ALIGN>();
            }
        }

        aligned_size += holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(ref_points_.size()));
        if (ref_points_.size() > 0)
        {
            aligned_size += ref_points_.size() * ref_points_[0].GetSerializedSize<ALIGN>();
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
        uint32_t i        = 0;
        uint32_t vec_size = static_cast<uint32_t>(vec_lanes_info_.size());
        MapMsgBase::Serialize(serializer);
        serializer << static_cast<uint64_t>(link_id_) << lane_count_ << vec_size;
        for (i = 0; i < vec_size; ++i)
        {
            serializer << vec_lanes_info_[i];
        }
        vec_size = static_cast<uint32_t>(ref_points_.size());
        serializer << vec_size;
        for (i = 0; i < vec_size; ++i)
        {
            serializer << ref_points_[i];
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
        ::holo::uint32_t i        = 0;
        ::holo::uint64_t link_id  = 0;
        ::holo::uint32_t vec_size = 0;
        MapMsgBase::Deserialize(deserializer);
        deserializer >> link_id >> lane_count_ >> vec_size;
        vec_lanes_info_.resize(vec_size);
        for (i = 0; i < vec_size; ++i)
        {
            deserializer >> vec_lanes_info_[i];
        }
        deserializer >> vec_size;
        ref_points_.resize(vec_size);
        for (i = 0; i < vec_size; ++i)
        {
            deserializer >> ref_points_[i];
        }
        deserializer >> holo::serialization::align;

        link_id_ = static_cast<KeyValue>(link_id);
    }

private:
    enum class LinkInfoValueFloat32 : ::holo::uint8_t
    {
        LINK_INFO_VALUE_WIDTH = 0,        ///< link width
        LINK_INFO_VALUE_LENGTH,           ///< link length
        LINK_INFO_VALUE_MAX_LIMIT_SPEED,  ///< link max limit
        LINK_INFO_VALUE_MIN_LIMIT_SPEED,  ///< link min limit

        lINK_INFO_VALUE_FLOAT_MAX  ///< max size of value_list_float32_ used to resize the vector in constructor
    };

    enum class LinkInfoValueUint32 : ::holo::uint8_t
    {
        LINK_INFO_VALUE_UINT32_MAX  ///< max size of value_list_uint32_ used to resize the vector in constructor
    };
    /**
     * @brief Enumerate some link indicators
     *
     */
    enum class LinkInfoValueBool : ::holo::uint8_t
    {
        IS_ON_ROUTE            = 0,  ///< Incidcate current link status, true on main road, false on ramp
        IS_ON_BIFURCATION_AREA = 1,  ///< if current link is bifurcation area

        LINK_INFO_INDICATOR_MAX  ///< max value of "LinkInfoValueBool"
    };

private:
    /// link id
    KeyValue link_id_{0U};
    /// total number of lanes on this link
    ::holo::uint8_t lane_count_{0U};
    /// lane info
    ::std::vector<LaneInfo> vec_lanes_info_;
    /// reference points
    ::std::vector<::holo::geometry::Point3d> ref_points_;
};

/**
 * @}
 *
 */
}  // namespace map
}  // namespace holo
#endif  // HOLO_BASE_INCLUDE_HOLO_MAP_LINK_INFO_H_
