/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_object.h
 * @brief Object.
 * @author leo(jiangdianqin@holomaitc.com) zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-11-26"
 */

#ifndef HOLO_BASE_INCLUDE_HOLO_MAP_COMMON_OBJECT_H_
#define HOLO_BASE_INCLUDE_HOLO_MAP_COMMON_OBJECT_H_

#include <vector>

#include "holo/geometry/point3.h"
#include <holo/map/common_def.h>
#include <holo/map/map_enum.h>
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
class CommonObject
{
public:
    /**
     * @brief Constructor
     *
     */
    CommonObject() noexcept : object_id_(0U), object_type_(::holo::map::ObjectType::TYPE_CURB)
    {
    }

    /**
     * @brief Destroy
     *
     */
    ~CommonObject() noexcept
    {
    }

    /**
     * @brief Copy construct
     *
     * @param[in] other
     */
    CommonObject(const CommonObject& other) noexcept
    : object_id_(other.object_id_)
    , object_type_(other.object_type_)
    , bottom_point_(other.bottom_point_)
    , out_line_(other.out_line_)
    {
    }

    /**
     * @brief Move copy construct
     *
     * @param[in] other
     */
    CommonObject(CommonObject&& other) noexcept
    : object_id_(other.object_id_)
    , object_type_(other.object_type_)
    , bottom_point_(other.bottom_point_)
    , out_line_(std::move(other.out_line_))
    {
    }
    /**
     * @brief Assignment operator
     *
     * @param[in] other
     * @return CommonObject
     */
    CommonObject operator=(const CommonObject& other) noexcept
    {
        if (this != &other)
        {
            object_id_    = other.object_id_;
            object_type_  = other.object_type_;
            bottom_point_ = other.bottom_point_;
            out_line_     = other.out_line_;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator
     *
     * @param[in] other
     * @return CommonObject
     */
    CommonObject operator=(CommonObject&& other) noexcept
    {
        if (this != &other)
        {
            object_id_    = other.object_id_;
            object_type_  = other.object_type_;
            bottom_point_ = other.bottom_point_;
            out_line_     = ::std::move(other.out_line_);
        }
        return *this;
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
        uint32_t point_count = out_line_.size();
        uint8_t  cur_object_type = static_cast<uint8_t>(object_type_);

        size_t aligned_size  = holo::serialization::SerializedSize<ALIGN>(object_id_, static_cast<uint8_t>(object_type_), point_count) +
                               bottom_point_.GetSerializedSize<ALIGN>();
        if(out_line_.size() > 0)
        {
            aligned_size += out_line_.size() * out_line_[0].GetSerializedSize<ALIGN>();
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
    template<typename S>
    void Serialize(S& serializer) const
    {
        uint32_t point_count = out_line_.size();
        serializer << static_cast<uint64_t>(object_id_) << static_cast<uint8_t>(object_type_) << point_count << bottom_point_
                   << holo::serialization::align;
        for (uint32_t i = 0; i < point_count; ++i)
        {
            serializer << out_line_[i];
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
        uint64_t        cur_key_value   = 0U;
        uint8_t         cur_object_type = 0u;
        uint32_t        point_count     = 0U;
        deserializer >> cur_key_value >> cur_object_type >> point_count >> bottom_point_ >> holo::serialization::align;

        object_id_   = (KeyValue)cur_key_value;
        object_type_ = (ObjectType)cur_object_type;
        out_line_.resize(point_count);

        for (uint32_t i = 0U; i < point_count; ++i)
        {
            deserializer >> out_line_[i];
        }    
    }

    /**
     * @brief Set the Object Id object
     *
     * @param[in] object_id
     */
    void SetObjectId(const KeyValue object_id) noexcept
    {
        object_id_ = object_id;
    }

    /**
     * @brief Set the Object Type
     *
     * @param[in] object_type
     */
    void SetObjectType(const ObjectType& object_type) noexcept
    {
        object_type_ = object_type;
    }

    /**
     * @brief set object's bottom point
     *
     * @param[in] bottom_point
     */
    void SetBottomPoint(const holo::geometry::Point3d& bottom_point) noexcept
    {
        bottom_point_ = bottom_point;
    }

    /**
     * @brief set object's outline
     *
     * @param[in] out_line
     */
    void SetOutLine(const std::vector<holo::geometry::Point3d>& out_line) noexcept
    {
        out_line_ = out_line;
    }

    /**
     * @brief Set object's outline
     *
     * @param[in] out_line
     */
    void SetOutLine(std::vector<holo::geometry::Point3d>&& out_line) noexcept
    {
        ::std::swap(out_line_, out_line);
    }

    /**
     * @brief Get the Object Id
     *
     * @return KeyValue
     */
    KeyValue GetObjectId() const noexcept
    {
        return object_id_;
    }

    /**
     * @brief Get object's type
     *
     * @return ObjectType
     */
    ObjectType GetObjectType() const noexcept
    {
        return object_type_;
    }

    /**
     * @brief Get object's bottom point
     *
     * @return const Point3d&
     */
    const holo::geometry::Point3d& GetBottomPoint() const noexcept
    {
        return bottom_point_;
    }

    /**
     * @brief Get object's outline
     *
     * @return const std::vector<Point3d>*
     */
    const std::vector<holo::geometry::Point3d>& GetOutLine() const noexcept
    {
        return out_line_;
    }

private:
    /// object's id
    KeyValue object_id_{0U};
    /// object's type
    ObjectType object_type_{::holo::map::ObjectType::TYPE_CURB};
    /// object's bottom point
    holo::geometry::Point3d bottom_point_;
    /// object's outline
    std::vector<holo::geometry::Point3d> out_line_;
};

/**
 * @}
 *
 */
}  // namespace map
}  // namespace holo
#endif
