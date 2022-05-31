/*!
 *  \brief hard nms
 *  \author huanglihong
 *  \date 20180109
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_DETECTION_HARD_NMS_H_
#define HOLO_PERCEPTION_DETECTION_HARD_NMS_H_

#include "holo/perception/detection/nms.h"

namespace holo
{
namespace perception
{

template <typename Scalar>
class HardNMS : public NMS<Scalar>
{
public:

    /// @brief smart pointer
    using Ptr = std::shared_ptr<HardNMS>;
    using ConstPtr = std::shared_ptr<const HardNMS>;
    
    explicit HardNMS(float32_t threshold) : NMS<Scalar>(threshold) {}

    virtual void Compute(std::list<ImageBBox2f>& boxes, bool is_sorted = false) const;
};

}   /// end namespace perception
}   /// end namespace holo

#endif
