/*!
 *  \brief
 *  \author lihong (lihong@holomatic.com)
 *  \date 2018-05-17
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_COMMON_IMAGEBBOX2D_H_
#define HOLO_PERCEPTION_COMMON_IMAGEBBOX2D_H_

#include <boost/format.hpp>
#include "holo/core/types.h"
#include "holo/common/classification.h"
#include "holo/numerics/vector.h"
#include "holo/perception/common/box2d.h"
#include "holo/perception/common/camera_detected_object.h"

namespace holo
{
namespace perception
{

template <typename Scalar>
class ImageBBox2D
{
public:
    typedef Box2DT<Scalar> Box2DType;
    typedef CameraDetectedObjectT<Scalar> CameraDetectedObjectType;

    typedef holo::Vector3T<Scalar> Vector3;

    /// @brief smart pointer
    using Ptr = std::shared_ptr<ImageBBox2D>;
    using ConstPtr = std::shared_ptr<const ImageBBox2D>;

    /// @brief constructor
    ImageBBox2D()
     : box2d_ (Box2DType(0, 0, 0, 0, 0)),
       camera_object_(),
       confidence_ (0),
       classification_ (Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN)),
       id_(0),
       position_(0.0, 0.0, 0.0),
       velocity_(0.0, 0.0, 0.0),
       size_(1.0, 1.0, 1.0)
    {

    }
    
    ImageBBox2D(Box2DType box2d , CameraDetectedObjectType camera_object, Scalar confidence,
                Classification classification = Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN), 
                const uint64_t id = 0, const Vector3& pos = Vector3(0.0, 0.0, 0.0), const Vector3& vel = Vector3(0.0, 0.0, 0.0))
     : box2d_ (box2d),
       camera_object_(camera_object),
       confidence_ (confidence),
       classification_ (classification),
       id_(id),
       position_(pos),
       velocity_(vel)
    {

    }

    /// @brief return id
    inline uint64_t id() const noexcept
    {
        return id_;
    }

    /// @brief return box2d
    inline const Box2DType& box2d() const noexcept
    {
        return box2d_;
    }

    /// @brief return camera object
    inline const CameraDetectedObjectT<Scalar>& camera_object()
    {
        return camera_object_;
    }

    /// @brief return confidence
    inline Scalar confidence() const noexcept
    {
        return confidence_;
    }

    /// @brief return width
    inline Classification classification() const noexcept
    {
        return classification_;
    }

    inline Vector3 position() const
    {
        return position_;
    }

    inline Vector3 velocity() const
    {
        return velocity_;
    }

    /**
     * @brief 3D bounding box size
     *    [width, height, length/depth]
     */
    inline Vector3 size() const
    {
        return size_;
    }

    inline void id(const int64_t id)
    {
        id_ = id;
    }

    /// @brief set box2d
    inline void box2d(const Box2DT<Scalar>& box2d)
    {
        box2d_ = box2d;
    }

    /// @brief set camera object
    inline void camera_object(const CameraDetectedObjectT<Scalar>& camera_object)
    {
        camera_object_ = camera_object;
    }

    /// @brief set confidence
    inline void confidence(Scalar c)
    {
        confidence_ = c;
    }

    /// @brief set width
    inline void classification(Classification c)
    {
        classification_ = c;
    }

    inline void position(const Vector3& position)
    {
        position_ = position;
    }

    inline void velocity(const Vector3& velocity)
    {
        velocity_ = velocity;
    }

    /**
     * @brief 3D bounding box size
     *  [width, height, length/depth]
     */
    inline void size(const Vector3& size)
    {
        size_ = size;
    }

    /// compare confidence
    inline bool operator<(const ImageBBox2D& object) const
    {  
        return confidence_ < object.confidence();
    }

    /// @brief output stream
    friend std::ostream& operator<<(std::ostream& os, const ImageBBox2D &in)
    {
        os << in.String();
        return os;
    }

    /// @brief string
    virtual std::string String() const
    {
        boost::format fmt("ImageBBox2D: box = (%|1|), confidence = (%|1|), classification = (%|1|)");
        return (fmt % box2d() % confidence() % classification()).str();
    }

    /// whether box is valid
    inline bool IsValid()
    {
        return box2d_.IsValid();
    }

private:
    Box2DType box2d_;
    CameraDetectedObjectType camera_object_;
    Scalar confidence_;
    Classification classification_;
    uint64_t id_;
    Vector3 position_;
    Vector3 velocity_;
    Vector3 size_;
};

/// @brief handy typedefs
typedef ImageBBox2D<float32_t> ImageBBox2f;
typedef ImageBBox2D<float64_t> ImageBBox2d;
using ImageBBoxList = std::vector<ImageBBox2f>;

}   /// end namespace perception
}   /// end namespace holo

#endif 