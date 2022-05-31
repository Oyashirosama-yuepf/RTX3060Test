/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_mark_info.h
 * @brief lane_mark_info: provide lane mark info.
 * @author zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-11-26"
 */

#ifndef HOLO_BASE_INCLUDE_HOLO_MAP_LANE_MARK_INFO_H_
#define HOLO_BASE_INCLUDE_HOLO_MAP_LANE_MARK_INFO_H_

#include <memory>
#include <vector>

#include <holo/geometry/point3.h>
#include <holo/map/common_def.h>
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
class LaneMarkInfo : public MapMsgBase
{
public:
    using PtrLaneMarkInfo      = ::std::shared_ptr<LaneMarkInfo>;
    using ConstPtrLaneMarkInfo = ::std::shared_ptr<LaneMarkInfo const>;

public:
    /**
     * @brief Constructor
     *
     */
    LaneMarkInfo() noexcept
    : MapMsgBase(kLaneMarkInfoIndicatorSize,
                static_cast<::holo::uint8_t>(LaneMarkInfoValueUint32::LANE_MARK_INFO_VALUE_UINT32_MAX),
                static_cast<::holo::uint8_t>(LaneMarkInfoValueFloat32::LANE_MARK_INFO_VALUE_FLOAT32_MAX))
    {
        this->ref_points_.clear();
    }

    /**
     * @brief Destroy the lane mark info
     *
     */
    ~LaneMarkInfo() noexcept
    {
    }
    /**
     * @brief Copy construct a new lane mark info
     *
     * @param[in] other
     */
    LaneMarkInfo(const LaneMarkInfo& other) noexcept
      : MapMsgBase(other)
      , mark_type_(other.mark_type_)
      , mark_color_(other.mark_color_)
      , mark_material_(other.mark_material_)
      , mark_rhombus_makring_(other.mark_rhombus_makring_)
      , ref_points_(other.ref_points_)
    {
    }

    /**
     * @brief Copy construct a new lane mark info as rvalue
     *
     * @param[in] other
     */
    LaneMarkInfo(LaneMarkInfo&& other) noexcept
      : MapMsgBase(::std::move(other))
      , mark_type_(other.mark_type_)
      , mark_color_(other.mark_color_)
      , mark_material_(other.mark_material_)
      , mark_rhombus_makring_(other.mark_rhombus_makring_)
      , ref_points_(std::move(other.ref_points_))
    {
    }

    /**
     * @brief Assignment operator
     *
     * @param[in] other
     * @return LaneMarkInfo&
     */
    LaneMarkInfo& operator=(const LaneMarkInfo& other) noexcept
    {
        if (this != &other)
        {
            MapMsgBase::operator        =(other);
            this->mark_type_            = other.mark_type_;
            this->mark_color_           = other.mark_color_;
            this->mark_material_        = other.mark_material_;
            this->mark_rhombus_makring_ = other.mark_rhombus_makring_;
            this->ref_points_           = other.ref_points_;
        }
        return *this;
    }

    /**
     * @brief Assignment operator as rvalue
     *
     * @param[in] other
     * @return LaneMarkInfo&
     */
    LaneMarkInfo& operator=(LaneMarkInfo&& other) noexcept
    {
        if (this != &other)
        {
            MapMsgBase::operator        =(::std::move(other));
            this->mark_type_            = other.mark_type_;
            this->mark_color_           = other.mark_color_;
            this->mark_material_        = other.mark_material_;
            this->mark_rhombus_makring_ = other.mark_rhombus_makring_;
            ::std::swap(this->ref_points_, other.ref_points_);
        }
        return *this;
    }

    /**
     * @brief Set the mark type
     *
     * @param[in] type
     */
    void SetMarkType(const CommonMarkType type) noexcept
    {
        this->mark_type_ = type;
    }

    /**
     * @brief Get the mark type
     *
     * @return CommonMarkType
     */
    CommonMarkType GetMarkType() const noexcept
    {
        return this->mark_type_;
    }

    /**
     * @brief Set the mark color
     *
     * @param[in] color
     */
    void SetMarkColor(const CommonMarkColor color) noexcept
    {
        this->mark_color_ = color;
    }

    /**
     * @brief Get the mark color
     *
     * @return CommonMarkColor
     */
    CommonMarkColor GetMarkColor() const noexcept
    {
        return this->mark_color_;
    }

    /**
     * @brief Set the mark material
     *
     * @param[in] material
     */
    void SetMarkMaterial(const CommonMarkMaterial material) noexcept
    {
        this->mark_material_ = material;
    }

    /**
     * @brief Get the mark material
     *
     * @return CommonMarkMaterial
     */
    CommonMarkMaterial GetMarkMaterial() const noexcept
    {
        return this->mark_material_;
    }

    /**
     * @brief Set the rhombus deceleration marking
     *
     * @param[in] rh
     */
    void SetRhombusDecelerationMarking(const CommonRhombusDecelerationMarking rh) noexcept
    {
        this->mark_rhombus_makring_ = rh;
    }

    /**
     * @brief Get the rhombus deceleration marking
     *
     * @return CommonRhombusDecelerationMarking
     */
    CommonRhombusDecelerationMarking GetRhombusDecelerationMarking() const noexcept
    {
        return this->mark_rhombus_makring_;
    }

    /**
     * @brief Set the mark width, unit is m
     *
     * @param[in] width
     */
    void SetMarkWidth(const ::holo::float32_t width) noexcept
    {
        this->float32_values_[static_cast<::std::size_t>(LaneMarkInfoValueFloat32::LANE_MARK_INFO_VALUE_MARK_WIDTH)] =
            width;
    }

    /**
     * @brief Get the mark width, unit is m
     *
     * @return float32_t
     */
    ::holo::float32_t GetMarkWidth() const noexcept
    {
        return this
            ->float32_values_[static_cast<::std::size_t>(LaneMarkInfoValueFloat32::LANE_MARK_INFO_VALUE_MARK_WIDTH)];
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
     * @brief Serialize all elements to string
     *
     * @return ::std::string
     */
    ::std::string ToString() const noexcept
    {
        // TODO zhaofx 2019-08-23: Need to serialize all elements.
        ::std::ostringstream oss;
        oss << "Type:" << static_cast<int>(GetMarkType()) << "; ";
        oss << "Color:" << static_cast<int>(GetMarkColor()) << "; ";
        oss << "Width:" << static_cast<int>(GetMarkWidth()) << "; ";
        oss << "Point size:" << GetRefPoints().size() << "; ";
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
        uint32_t aligned_size = MapMsgBase::GetSerializedSize<ALIGN>() +
                                holo::serialization::SerializedSize<ALIGN>(
                                    static_cast<uint8_t>(mark_type_), static_cast<uint8_t>(mark_color_),
                                    static_cast<uint8_t>(mark_material_), static_cast<uint8_t>(mark_rhombus_makring_),
                                    static_cast<uint32_t>(ref_points_.size()));
        if (ref_points_.size() > 0)
        {
            aligned_size += ref_points_.size() * ref_points_[0].template GetSerializedSize<ALIGN>();
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
        MapMsgBase::Serialize(serializer);
        serializer << holo::serialization::align << static_cast<uint8_t>(mark_type_) << static_cast<uint8_t>(mark_color_)
                   << static_cast<uint8_t>(mark_material_) << static_cast<uint8_t>(mark_rhombus_makring_)
                   << static_cast<uint32_t>(ref_points_.size()) << holo::serialization::align;
        for (uint32_t i = 0; i < (uint32_t)(ref_points_.size()); ++i)
        {
            serializer << ref_points_[i];
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
    template <typename D>
    void Deserialize(D& deserializer)
    {
        ::holo::uint8_t  mark_type            = 0;
        ::holo::uint8_t  mark_color           = 0;
        ::holo::uint8_t  mark_material        = 0;
        ::holo::uint8_t  mark_rhombus_makring = 0;
        ::holo::uint32_t i                    = 0;
        ::holo::uint32_t vec_size             = 0;

        MapMsgBase::Deserialize(deserializer);
        deserializer >> holo::serialization::align >> mark_type >> mark_color >> mark_material >> mark_rhombus_makring >>
            vec_size >> holo::serialization::align;

        ref_points_.resize(vec_size);
        for (i = 0; i < vec_size; ++i)
        {
            deserializer >> ref_points_[i];
        }

        mark_type_            = static_cast<CommonMarkType>(mark_type);
        mark_color_           = static_cast<CommonMarkColor>(mark_color);
        mark_material_        = static_cast<CommonMarkMaterial>(mark_material);
        mark_rhombus_makring_ = static_cast<CommonRhombusDecelerationMarking>(mark_rhombus_makring);
    }

private:
    // Use to limit MapMsgBase indicators valid size.
    static const ::holo::uint8_t kLaneMarkInfoIndicatorSize = 0U;
    // Cover all uint32 type element, for reserving
    enum class LaneMarkInfoValueUint32 : ::holo::uint8_t
    {
        LANE_MARK_INFO_VALUE_UINT32_MAX  ///< max size of value_uint32_ used to resize the vector in constructor
    };

    // Cover all float32 type element, for reserving
    enum class LaneMarkInfoValueFloat32 : ::holo::uint8_t
    {
        LANE_MARK_INFO_VALUE_MARK_WIDTH = 0,  ///< mark width

        LANE_MARK_INFO_VALUE_FLOAT32_MAX  ///< max size of value_float32_ used to resize the vector in constructor
    };

private:
    /// mark type
    CommonMarkType mark_type_{CommonMarkType::MARK_TYPE_NOT_INVESTIGATED};
    /// mark color
    CommonMarkColor mark_color_{CommonMarkColor::MARK_COLOR_NOT_APPLICABLE};
    /// mark material
    CommonMarkMaterial mark_material_{CommonMarkMaterial::MARK_MATERIAL_NOT_APPLICABLE};
    /// mark rhombus deceleration marking
    CommonRhombusDecelerationMarking mark_rhombus_makring_{
        CommonRhombusDecelerationMarking::RHOMBUS_DECELERATION_MARKING_NOT_APPLICABLE};
    /// mark reference points
    ::std::vector<::holo::geometry::Point3d> ref_points_;
};

/**
 * @}
 *
 */
}  // namespace map
}  // namespace holo
#endif  // HOLO_BASE_INCLUDE_HOLO_MAP_LANE_MARK_INFO_H_
