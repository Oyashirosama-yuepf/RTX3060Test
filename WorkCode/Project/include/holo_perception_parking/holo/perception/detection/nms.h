/*!
 *  \brief
 *  \author huanglihong
 *  \date 20180109
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_DETECTION_NMS_H_
#define HOLO_PERCEPTION_DETECTION_NMS_H_

#include <list>
#include "holo/perception/common/image_bbox2d.h"

namespace holo
{
namespace perception
{

template <typename Scalar>
class NMS
{

public:

    /// @brief smart pointer
    using Ptr = std::shared_ptr<NMS>;
    using ConstPtr = std::shared_ptr<const NMS>;

    /// constructor
    NMS(){}
    explicit NMS(float32_t threshold) : threshold_ (threshold) {}

    inline float32_t threshold() const noexcept
    {
        return threshold_;
    }

    inline void threshold(float32_t threshold)
    {
        threshold_ = threshold;
    }

    virtual void Compute(std::list<ImageBBox2f>& boxes, bool is_sorted = false) const  = 0;

private:

    float32_t threshold_;
};

}   /// end namespace perception
}   /// end namespace holo

#endif
