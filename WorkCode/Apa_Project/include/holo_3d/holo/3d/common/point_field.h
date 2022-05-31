/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_field.h
 * @brief This header file defines point field of point types
 * @author luopei(luopei@holomaitc.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-10-14
 */

#ifndef HOLO_3D_COMMON_POINT_FIELD_H_
#define HOLO_3D_COMMON_POINT_FIELD_H_

#include <iostream>
#include <memory>
#include <string>

#include <holo/log/hololog.h>
#include <holo/3d/common/point_types.h>
#include <holo/core/types.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief PointField class
 *
 */
class PointField
{
public:
    enum class Type : uint32_t
    {
        INT8      = 0x0001,
        UINT8     = 0x0002,
        INT16     = 0x0004,
        UINT16    = 0x0008,
        INT32     = 0x0010,
        UINT32    = 0x0020,
        FLOAT32   = 0x0040,
        FLOAT64   = 0x0080,
        TIMESTAMP = 0x0100,
        UNKNOWN   = 0xffff,
    };

    using Ptr      = std::shared_ptr<PointField>;
    using ConstPtr = std::shared_ptr<PointField const>;

    /**
     * @brief Default constructor
     */
    PointField() : name_(), offset_(0), type_(Type::UNKNOWN), count_(0)
    {
    }

    /**
     * @brief Constructor
     *
     * @param[in] name field name
     * @param[in] offset field offset from start
     * @param[in] type field data type
     * @param[in] count field data size
     */
    PointField(const std::string& name, uint32_t offset, Type type, uint32_t count)
      : name_(name), offset_(offset), type_(type), count_(count)
    {
    }

    /**
     * @brief Get field name
     *
     * @return const std::string&
     */
    const std::string& GetName() const noexcept
    {
        return name_;
    }

    /**
     * @brief Set field name
     *
     * @param[in] name
     */
    void SetName(std::string const& name) noexcept
    {
        name_ = name;
    }

    /**
     * @brief Get offset in bytes
     *
     * @return uint32_t
     */
    uint32_t GetOffset() const noexcept
    {
        return offset_;
    }

    /**
     * @brief Set offset
     *
     * @param[in] offset
     */
    void SetOffset(uint32_t offset) noexcept
    {
        offset_ = offset;
    }

    /**
     * @brief Get data type
     *
     * @return Type
     */
    Type GetType() const noexcept
    {
        return type_;
    }

    /**
     * @brief Set data type
     *
     * @param[in] type
     */
    void SetType(Type const& type) noexcept
    {
        type_ = type;
    }

    /**
     * @brief Get data type size
     *
     * @return uint32_t
     */
    uint32_t GetCount() const noexcept
    {
        return count_;
    }

    /**
     * @brief Set data type size
     *
     * @param[in] count
     */
    void SetCount(uint32_t count) noexcept
    {
        count_ = count;
    }

private:
    std::string name_;    ///< field name eg. x
    uint32_t    offset_;  ///< offset bytes from the address of the point
    Type        type_;    ///< field data type
    uint32_t    count_;   ///< type size
};

/**
 * @brief Get the field value
 *
 * @tparam PointT
 * @tparam T
 * @param[in] p input point
 * @param[in] field input point field
 * @param[out] value field value
 */
template <typename PointT, typename T>
void GetFieldValue(PointT const& p, PointField const& field, T& value)
{
    assert(sizeof(T) == field.GetCount());

    uint8_t const* data_ptr = reinterpret_cast<uint8_t const*>(&p) + field.GetOffset();
    value                   = *reinterpret_cast<T const*>(data_ptr);
}

/**
 * @brief Set the field value
 *
 * @tparam PointT
 * @tparam T
 * @param[in,out] p point
 * @param[in] field point field
 * @param[in] value field value
 */
template <typename PointT, typename T>
void SetFieldValue(PointT& p, const PointField& field, T const& value)
{
    assert(sizeof(T) == field.GetCount());
    uint32_t offset                 = field.GetOffset();
    uint8_t* data_ptr               = reinterpret_cast<uint8_t*>(&p) + offset;
    *reinterpret_cast<T*>(data_ptr) = value;
}

/**
 * @brief Functor to get point field of PointT
 *
 * @tparam PointT
 */
template <typename PointT>
struct GetFields
{
    std::vector<PointField> operator()()
    {
        std::vector<PointField> fields;
        LOG(ERROR) << "The point type is not supported";
        return fields;
    }
};

/**
 * @brief Specialization for PointXYZIRSt<float32_t>
 *
 * @tparam
 */
template <>
struct GetFields<PointXYZIRSt<float32_t> >
{
    std::vector<PointField> operator()()
    {
        using Type     = PointField::Type;
        uint32_t count = sizeof(float32_t);
        Type     type  = Type::FLOAT32;

        std::vector<PointField> fields;
        fields.emplace_back(PointField("x", 0U, type, count));
        fields.emplace_back(PointField("y", count, type, count));
        fields.emplace_back(PointField("z", 2 * count, type, count));
        fields.emplace_back(PointField("intensity", 4 * count, type, count));
        fields.emplace_back(PointField("ring", 4 * count + 4, Type::UINT32, 4U));
        fields.emplace_back(PointField("timestamp", 4 * count + 8, Type::TIMESTAMP, 8U));

        return fields;
    }
};

/**
 * @brief Specialization for PointXYZIRSt<float64_t>
 *
 * @tparam
 */
template <>
struct GetFields<PointXYZIRSt<float64_t> >
{
    std::vector<PointField> operator()()
    {
        using Type     = PointField::Type;
        uint32_t count = sizeof(float64_t);
        Type     type  = Type::FLOAT64;

        std::vector<PointField> fields;
        fields.emplace_back(PointField("x", 0U, type, count));
        fields.emplace_back(PointField("y", count, type, count));
        fields.emplace_back(PointField("z", 2 * count, type, count));
        fields.emplace_back(PointField("intensity", 4 * count, type, count));
        fields.emplace_back(PointField("ring", 5 * count, Type::UINT32, 4U));
        fields.emplace_back(PointField("timestamp", 5 * count + 4, Type::TIMESTAMP, 8U));

        return fields;
    }
};

/**
 * @brief Specialization for Point3f
 *
 * @tparam
 */
template <>
struct GetFields<geometry::Point3f>
{
    std::vector<PointField> operator()()
    {
        uint32_t         count = sizeof(float32_t);
        PointField::Type type  = PointField::Type::FLOAT32;

        std::vector<PointField> fields;
        fields.emplace_back(PointField("x", 0U, type, count));
        fields.emplace_back(PointField("y", count, type, count));
        fields.emplace_back(PointField("z", 2 * count, type, count));

        return fields;
    }
};

/**
 * @brief Specialization for Point3d
 *
 * @tparam
 */
template <>
struct GetFields<geometry::Point3d>
{
    std::vector<PointField> operator()()
    {
        uint32_t         count = sizeof(float64_t);
        PointField::Type type  = PointField::Type::FLOAT64;

        std::vector<PointField> fields;
        fields.emplace_back(PointField("x", 0U, type, count));
        fields.emplace_back(PointField("y", count, type, count));
        fields.emplace_back(PointField("z", 2 * count, type, count));

        return fields;
    }
};

/**
 * @brief Specialization for PointXYZNormalt<float32_t>
 *
 * @tparam
 */
template <>
struct GetFields<PointXYZNormalt<float32_t> >
{
    std::vector<PointField> operator()()
    {
        using Type     = PointField::Type;
        uint32_t count = sizeof(float32_t);
        Type     type  = Type::FLOAT32;

        std::vector<PointField> fields;
        fields.emplace_back(PointField("x", 0U, type, count));
        fields.emplace_back(PointField("y", count, type, count));
        fields.emplace_back(PointField("z", 2 * count, type, count));
        fields.emplace_back(PointField("nx", 4 * count, type, count));
        fields.emplace_back(PointField("ny", 5 * count, type, count));
        fields.emplace_back(PointField("nz", 6 * count, type, count));

        return fields;
    }
};

/**
 * @brief Specialization for PointXYZNormalt<float64_t>
 *
 * @tparam
 */
template <>
struct GetFields<PointXYZNormalt<float64_t> >
{
    std::vector<PointField> operator()()
    {
        using Type     = PointField::Type;
        uint32_t count = sizeof(float64_t);
        Type     type  = Type::FLOAT64;

        std::vector<PointField> fields;
        fields.emplace_back(PointField("x", 0U, type, count));
        fields.emplace_back(PointField("y", count, type, count));
        fields.emplace_back(PointField("z", 2 * count, type, count));
        fields.emplace_back(PointField("nx", 4 * count, type, count));
        fields.emplace_back(PointField("ny", 5 * count, type, count));
        fields.emplace_back(PointField("nz", 6 * count, type, count));

        return fields;
    }
};

/**
 * @brief Specialization for PointXYZIRRgbSt<float32_t>
 *
 * @tparam
 */
template <>
struct GetFields<PointXYZIRRgbSt<float32_t> >
{
    std::vector<PointField> operator()()
    {
        using Type     = PointField::Type;
        uint32_t count = sizeof(float32_t);
        Type     type  = Type::FLOAT32;

        std::vector<PointField> fields;
        fields.emplace_back(PointField("x", 0U, type, count));
        fields.emplace_back(PointField("y", count, type, count));
        fields.emplace_back(PointField("z", 2 * count, type, count));
        fields.emplace_back(PointField("intensity", 4 * count, type, count));
        fields.emplace_back(PointField("ring", 4 * count + 4U, Type::UINT32, 4U));
        fields.emplace_back(PointField("r", 5 * count + 4U, Type::UINT8, 1U));
        fields.emplace_back(PointField("g", 5 * count + 5U, Type::UINT8, 1U));
        fields.emplace_back(PointField("b", 5 * count + 6U, Type::UINT8, 1U));
        fields.emplace_back(PointField("timestamp", 5 * count + 8U, Type::TIMESTAMP, 8U));

        return fields;
    }
};

/**
 * @brief Specialization for PointXYZIRRgbSt<float64_t>
 *
 * @tparam
 */
template <>
struct GetFields<PointXYZIRRgbSt<float64_t> >
{
    std::vector<PointField> operator()()
    {
        using Type     = PointField::Type;
        uint32_t count = sizeof(float64_t);
        Type     type  = Type::FLOAT64;

        std::vector<PointField> fields;
        fields.emplace_back(PointField("x", 0U, type, count));
        fields.emplace_back(PointField("y", count, type, count));
        fields.emplace_back(PointField("z", 2 * count, type, count));
        fields.emplace_back(PointField("intensity", 4 * count, type, count));
        fields.emplace_back(PointField("ring", 5 * count, Type::UINT32, 4U));
        fields.emplace_back(PointField("r", 5 * count + 4U, Type::UINT8, 1U));
        fields.emplace_back(PointField("g", 5 * count + 5U, Type::UINT8, 1U));
        fields.emplace_back(PointField("b", 5 * count + 6U, Type::UINT8, 1U));
        fields.emplace_back(PointField("timestamp", 5 * count + 8U, Type::TIMESTAMP, 8U));

        return fields;
    }
};

}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_COMMON_POINT_FIELD_H_
