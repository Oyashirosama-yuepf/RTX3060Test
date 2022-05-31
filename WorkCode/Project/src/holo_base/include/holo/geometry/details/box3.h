/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box3.h
 * @brief this class represents a box in 3d.
 * @author jiaxing.zhao
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date Sep-27-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_BOX3_H_
#define HOLO_GEOMETRY_DETAILS_BOX3_H_

#include <limits>
#include <string>
#include <vector>

#include <holo/core/exception.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/numerics/vector.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace geometry
{
namespace details
{
/**
 * @addtogroup geometry
 * @{
 *
 */

/**
 * @brief define box3
 *
 * @details In box3 local frame,
 *     depth(length) is aligned with x-axis,
 *     width is aligned with y-axis,
 *     height is aligned with z-axis
 *
 * @verbatim
 *                      *                     *
 *     top-down view    *      front-view     *    side-view
 *            x         *           z         *         z
 *            ^         *           ^         *         ^
 *            |         *           |         *         |
 *            | depth   *           | height  *  height |
 *   y <------o         *  y <------o         *         o------->x
 *      width           *      width          *            depth
 *                      *                     *
 *
 * @endverbatim
 * @tparam T float32_t or float64_t
 */
template <typename T>
class Box3T
{
public:
    using ScalarType                = T;
    using Point3Type                = Point3T<ScalarType>;
    using Vector3Type               = holo::numerics::Vector3T<ScalarType>;
    using Rot3Type                  = Rot3T<ScalarType>;
    using Pose3Type                 = Pose3T<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    /**
     * @brief default constructor
     *
     * @details an unit box is constructed
     */
    Box3T() noexcept;

    /**
     * @brief constructor from diagonal points
     *
     * @param p1 point1
     * @param p2 point2
     * @throw std::runtime_error if p1 and p2 does NOT form a box
     */
    Box3T(Point3Type const& p1, Point3Type const& p2);

    /**
     * @brief constructor from dimension vector and pose
     *
     * @param dim dimension in order of (width, height, depth)
     * @param pose box pose
     * @throw std::runtime_error if initialization fails
     */
    Box3T(Vector3Type const& dim, Pose3Type const& pose = Pose3Type::Identity());

    /**
     * @brief constructor from each dimension scalar and pose
     *
     * @param width box width
     * @param height box height
     * @param depth box depth
     * @param pose pose
     * @throw std::runtime_error if initialization fails
     */
    Box3T(ScalarType const width, ScalarType const height, ScalarType const depth,
          Pose3Type const& pose = Pose3Type::Identity());

    /**
     * @brief constructor from width, height, depth, center, roll, pitch, yaw
     *
     * @param width box width
     * @param height box height
     * @param depth box depth
     * @param center box center
     * @param roll angle in radian
     * @param pitch angle in radian
     * @param yaw angle in radian
     * @throw std::runtime_error if initialization fails
     */
    Box3T(ScalarType const width, ScalarType const height, ScalarType const depth, Point3Type const& center,
          ScalarType const roll = 0.0, ScalarType const pitch = 0.0, ScalarType const yaw = 0.0);

    /**
     * @brief copy constructor
     *
     * @param other box
     */
    Box3T(Box3T const& other) noexcept;

    /**
     * @brief destructor
     */
    ~Box3T() noexcept;

    /**
     * @brief assignment operator
     *
     * @param other box
     */
    Box3T& operator=(Box3T const& other) noexcept;

    /**
     * @brief operator ==
     *
     * @param other box
     * @return true of false
     */
    bool_t operator==(Box3T const& other) const noexcept;

    /**
     * @brief cast to a different type
     *
     * @return new box
     */
    template <typename OutputScalar>
    explicit operator Box3T<OutputScalar>() const noexcept
    {
        return Cast<OutputScalar>();
    }

    /**
     * @brief output stream
     *
     * @param os std::ostream
     * @param box box3
     * @return std::ostream
     */
    friend std::ostream& operator<<(std::ostream& os, Box3T const& box) noexcept
    {
        os << box.ToString();
        return os;
    }

    /**
     * @brief convert to string
     *
     * @return string
     */
    std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "box3: (width: " << width_ << ", height: " << height_ << ", depth: " << depth_ << ", pose3: " << pose_
           << ")" << std::endl;
        return ss.str();
    }

    /**
     * @brief cast to a different type
     *
     * @return new box
     */
    template <typename OutputScalar>
    Box3T<OutputScalar> Cast() const noexcept
    {
        return Box3T<OutputScalar>(static_cast<OutputScalar>(width_), static_cast<OutputScalar>(height_),
                                   static_cast<OutputScalar>(depth_), pose_.template Cast<OutputScalar>());
    }

    /**
     * @brief check whehter a point is contained in the box
     *
     * @param pt point
     * @param tol tolerance
     * @return true of false
     */
    bool_t Contains(Point3Type const& pt, const ScalarType tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief check if two boxes are equal
     *
     * @param other box3
     * @param tol tolerance
     * @return true of false
     */
    bool_t IsEqual(Box3T const& other, const ScalarType tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief check valid
     *
     * @return true of false
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief return the minimum and maximum corner points of the box in
     *        world coordinate, completely and uniquely enclosed the box by
     *        coordinates parallel to the axis.
     *
     * @param min_pt minimum point
     * @param max_pt maximum point
     */
    void GetAxisAlignedExternalBox(Point3Type& min_pt, Point3Type& max_pt) const noexcept;

    /**
     * @brief Get the Corner Points object in global frame
     *
     * @return std::vector<Point3Type>
     *        {xmin, ymin, zmin}
     *        {xmax, ymin, zmin}
     *        {xmax, ymax, zmin}
     *        {xmin, ymax, zmin}
     *        {xmin, ymax, zmax}
     *        {xmin, ymin, zmax}
     *        {xmax, ymin, zmax}
     *        {xmax, ymax, zmax}
     */
    std::vector<Point3Type> GetCornerPoints() const noexcept;

    /**
     * @brief get volume
     */
    inline ScalarType GetVolume() const noexcept
    {
        return GetWidth() * GetHeight() * GetDepth();
    }

    /**
     * @brief get width
     */
    inline ScalarType GetWidth() const noexcept
    {
        return width_;
    }

    /**
     * @brief get height
     */
    inline ScalarType GetHeight() const noexcept
    {
        return height_;
    }

    /**
     * @brief get depth
     */
    inline ScalarType GetDepth() const noexcept
    {
        return depth_;
    }

    /**
     * @brief get pose
     */
    inline Pose3Type const& GetPose() const noexcept
    {
        return pose_;
    }

    /**
     * @brief center
     */
    Point3Type GetCenter() const noexcept;

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
        return holo::serialization::SerializedSize<ALIGN>(width_, height_, depth_) +
               pose_.template GetSerializedSize<ALIGN>();
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
        serializer << holo::serialization::align << width_ << height_ << depth_ << pose_;
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
        deserializer >> holo::serialization::align >> width_ >> height_ >> depth_ >> pose_;
    }

protected:
    ScalarType width_;
    ScalarType height_;
    ScalarType depth_;

    /**
     * @brief pose in the world frame
     */
    Pose3Type pose_;

};  // Box3T

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "./impl/box3.hpp"

#endif  // HOLO_GEOMETRY_DETAILS_BOX3_H_
