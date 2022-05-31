/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box2.h
 * @brief box in 2D space
 * @author duyanwei@holomatic.com
 * @date Sep-25-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_BOX2_H_
#define HOLO_GEOMETRY_DETAILS_BOX2_H_

#include <holo/core/types.h>
#include <holo/geometry/line2.h>
#include <holo/geometry/line_segment2.h>
#include <holo/geometry/pose2.h>
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
 * @brief define box2
 *
 * @details in box local frame, width is aligned with x-axis and height with y-axis
 *
 * @verbatim
 *   Box2 lcoal frame
 *          y
 *          ^
 *          |
 *   height |
 *          o------->x
 *            width
 * @endverbatim
 * @tparam T float32_t or float64_t
 */
template <typename T>
class Box2T
{
public:
    using ScalarType                = T;
    using Point2Type                = Point2T<ScalarType>;
    using Pose2Type                 = Pose2T<ScalarType>;
    using Rot2Type                  = Rot2T<ScalarType>;
    using Vector2Type               = holo::numerics::Vector2T<ScalarType>;
    using Line2Type                 = Line2T<ScalarType>;
    using LineSegment2Type          = LineSegment2T<ScalarType>;
    using EpsilonType[[deprecated]] = EpsilonT<ScalarType>;

    /**
     * @brief default constructor
     *
     * @details an unit box is constructed
     */
    Box2T() noexcept;

    /**
     * @brief constructor from diagonal points
     *
     * @param pt1 point1
     * @param pt2 point2
     * @throw std::runtime_error if pt1 and pt2 does NOT form a box
     */
    Box2T(Point2Type const& pt1, Point2Type const& pt2);

    /**
     * @brief constructor from a center point, width, height and and orientation (radian)
     *
     * @param center center point
     * @param width box width
     * @param height box height
     * @param theta box orientation
     * @throw std::runtime_error if they do NOT form a box
     */
    Box2T(Point2Type const& center, ScalarType const width, ScalarType const height, ScalarType const theta);

    /**
     * @brief constructor from width, height and pose directly
     *
     * @param width box width
     * @param height box height
     * @param pose box pose
     * @throw std::runtime_error if initialization fails
     */
    Box2T(ScalarType const width, ScalarType const height, const Pose2Type& pose);

    /**
     * @brief copy constructor
     *
     * @param box box
     */
    Box2T(Box2T const& box) noexcept;

    /**
     * @brief destructor
     */
    ~Box2T() noexcept;

    /**
     * @brief assignment operator
     *
     * @param box box
     */
    Box2T& operator=(Box2T const& box) noexcept;

    /**
     * @brief cast to different type
     *
     * @return new type of box2
     */
    template <typename OutputScalar>
    explicit operator Box2T<OutputScalar>() const noexcept
    {
        return Cast<OutputScalar>();
    }

    /**
     * @brief operator ==, check if two boxes are equal
     *
     * @param box box
     * @return true or false
     */
    bool_t operator==(Box2T const& box) const noexcept;

    /**
     * @brief output stream
     *
     * @param os std::ostream
     * @param box box
     * @return std::ostream
     */
    friend std::ostream& operator<<(std::ostream& os, Box2T const& box) noexcept
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
        ss << "box2: width: (" << width_ << "), height: (" << height_ << "), " << pose_;
        return ss.str();
    }

    /**
     * @brief cast to different type
     */
    template <typename OutputScalar>
    Box2T<OutputScalar> Cast() const noexcept
    {
        return Box2T<OutputScalar>(static_cast<OutputScalar>(width_), static_cast<OutputScalar>(height_),
                                   pose_.template Cast<OutputScalar>());
    }

    /**
     * @brief check if box contains a point
     *
     * @param pt point
     * @param tol tolerance
     *
     * @return true or false
     */
    bool_t Contains(Point2Type const& pt, ScalarType const tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief check if box contains a linesegment
     *
     * @return true or false
     */
    bool_t Contains(LineSegment2Type const& ls,
                    ScalarType const        tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const noexcept;

    /**
     * @brief check if two boxes are equal
     *
     * @param box box
     * @param tol tolerance
     *
     * @return true or false
     */
    bool_t IsEqual(Box2T const& box, ScalarType const tol = ScalarEqualT<ScalarType>().GetEpsilonValue()) const
        noexcept;

    /**
     * @brief check valid
     *
     * @return true or false
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief find the intersections of a line segment and box
     *
     * @param ls line segment
     * @param pt1 intersected point1 if any
     * @param pt2 intersected point2 if any
     * @return the number of intersected points, could be 0, 1 or 2
     */
    uint8_t Intersect(const LineSegment2Type& ls, Point2Type& pt1, Point2Type& pt2) const noexcept;

    /**
     * @brief return the four corner points of the box in world frame
     *
     * @verbatim box in its local frame
     *            y
     *            ^
     *            |
     *
     *          (tl)  top  (tr)
     *            ***********
     *      left  *         *  right
     *            ***********    --->x
     *         (bl) bottom (br)
     * @endverbatim
     *
     * @param bl bottom left point
     * @param br bottom right point
     * @param tr top right point
     * @param tl top left point
     * @return void
     */
    void GetCornerPoints(Point2Type& bl, Point2Type& br, Point2Type& tr, Point2Type& tl) const noexcept;

    /**
     * @brief return the four edges of box in world frame
     *
     * @verbatim box in its local frame
     *            y
     *            ^
     *            |
     *
     *          (tl)  top  (tr)
     *            ***********
     *      left  *         *  right
     *            ***********    --->x
     *         (bl) bottom (br)
     *
     * @param bottom bottom line segment
     * @param right right line segment
     * @param top top line segment
     * @param left left line segment
     * @return void
     */
    void GetEdges(LineSegment2Type& bottom, LineSegment2Type& right, LineSegment2Type& top,
                  LineSegment2Type& left) const noexcept;

    /**
     * @brief return minimum and maximum points of the box that is aligned with world-axis
     *
     * @param min_pt minimum point
     * @param max_pt maximum point
     * @return void
     */
    void GetAxisAlignedExternalBox(Point2Type& min_pt, Point2Type& max_pt) const noexcept;

    /**
     * @brief compute IOU(Intersection Over Union) of two boxes
     *
     * @note current version does NOT support oriented box
     * @ref http://www.pyimagesearch.com/2016/11/07/intersection-over-union-iou-for-object-detection/
     * @param box box
     * @return the value of IOU
     */
    ScalarType ComputeIntersectionOverUnion(Box2T const& box) const noexcept;

    /**
     * @brief return the area of box
     */
    inline ScalarType GetArea() const noexcept
    {
        return width_ * height_;
    }

    /**
     * @brief return width
     */
    inline ScalarType GetWidth() const noexcept
    {
        return width_;
    }

    /**
     * @brief return height
     */
    inline ScalarType GetHeight() const noexcept
    {
        return height_;
    }

    /**
     * @brief return the pose of box
     */
    inline Pose2Type const& GetPose() const noexcept
    {
        return pose_;
    }

    /**
     * @brief set width
     *
     * @param width box width
     * @return void
     */
    void SetWidth(ScalarType const width) noexcept;

    /**
     * @brief set height
     *
     * @param height box height
     * @return void
     */
    void SetHeight(ScalarType const height) noexcept;

    /**
     * @brief set the pose of box
     *
     * @param pose box pose
     * @return void
     */
    void SetPose(Pose2Type const& pose) noexcept;

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
        return holo::serialization::SerializedSize<ALIGN>(width_, height_) + pose_.template GetSerializedSize<ALIGN>();
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
        serializer << holo::serialization::align << width_ << height_ << pose_;
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
        deserializer >> holo::serialization::align >> width_ >> height_ >> pose_;
    }

private:
    /**
     * @brief dimension of the box
     */
    ScalarType width_;
    ScalarType height_;

    /**
     * @brief pose in the world frame
     */
    Pose2Type pose_;

};  // Box2T

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "./impl/box2.hpp"

#endif  // HOLO_GEOMETRY_DETAILS_BOX2_H_
