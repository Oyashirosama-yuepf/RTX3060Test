/*!
 *  \brief
 *  \author lihong (lihong@holomatic.com)
 *  \date 2018-05-17
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_COMMON_OBJECT2D_H_
#define HOLO_PERCEPTION_COMMON_OBJECT2D_H_

#include <boost/format.hpp>
#include "holo/core/types.h"
#include "holo/common/classification.h"
#include "holo/perception/common/box2d.h"
#include "holo/perception/common/impl/box2d.hpp"

namespace holo
{
namespace perception
{

template <typename Scalar>
class Object2D
{
public:

    typedef Box2DT<Scalar> Box2DType;

    /// @brief smart pointer
    using Ptr = std::shared_ptr<Object2D>;
    using ConstPtr = std::shared_ptr<const Object2D>;

    /// @brief constructor
    Object2D()
     : box2d_ (Box2DType(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)),
       confidence_ (0),
       classification_ (Classification(Classification::MainType::UNKNOWN, Classification::SubType::UNKNOWN))
    {

    }
    
    Object2D(Box2DType box2d = Box2DType(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), Scalar confidence = 0, Classification classification = Classification(Classification::MainType::UNKNOWN , Classification::SubType::UNKNOWN))
     : box2d_ (box2d),
       confidence_ (confidence),
       classification_ (classification)
    {

    }

    /// @brief return x
    inline const Box2DType& box2d() const noexcept
    {
        return box2d_;
    }

    /// @brief return y
    inline Scalar confidence() const noexcept
    {
        return confidence_;
    }

    /// @brief return width
    inline Classification classification() const noexcept
    {
        return classification_;
    }

    /// @brief set x
    inline void box2d(const Box2DT<Scalar>& box2d)
    {
        box2d_ = box2d;
    }

    /// @brief set y
    inline void confidence(Scalar c)
    {
        confidence_ = c;
    }

    /// @brief set width
    inline void classification(Classification c)
    {
        classification_ = c;
    }

    /// compare confidence
    inline bool operator<(const Object2D& object) const
    {  
        return confidence_ < object.confidence();
    }

    /// @brief output stream
    friend std::ostream& operator<<(std::ostream& os, const Object2D &in)
    {
        os << in.String();
        return os;
    }

    /// @brief string
    virtual std::string String() const
    {
        boost::format fmt("Object2D: box = (%|1|), confidence = (%|1|), classification = (%|1|)");
        return (fmt % box2d() % confidence() % classification()).str();
    }

private:
    Box2DType box2d_;
    Scalar confidence_;
    Classification classification_;
};

/// @brief handy typedefs
typedef Object2D<float32_t> object2f;
typedef Object2D<float64_t> object2d;

}   /// end namespace perception
}   /// end namespace holo

#endif 
