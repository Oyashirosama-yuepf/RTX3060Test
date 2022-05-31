/*!
 *  \brief
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2018-05-17
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_TRACKING_BBOX_TRACKER_H_
#define HOLO_PERCEPTION_TRACKING_BBOX_TRACKER_H_

#include <memory>
#include <vector>

#include <holo/perception/common/box2d.h>
#include <holo/perception/common/image_bbox2d.h>

namespace holo
{

namespace perception
{

enum class TrackState
{
    INIT,
    MATCHED,
    LOST
};

class BBoxTrackerBase
{
public:
    /// @brief constructor
    BBoxTrackerBase() {}

    /// @brief deconstructor
    ~BBoxTrackerBase() {}

    /// @brief smart pointer
    using Ptr = std::shared_ptr<BBoxTrackerBase>;
    using ConstPtr = std::shared_ptr<const BBoxTrackerBase>;

    virtual bool Tracking(ImageBBoxList& in_boxes, ImageBBoxList& out_boxes) = 0;
    virtual void SetMinIOU(float32_t min_iou) = 0;
};

}   /// end namespace perception
}   /// end namespace holo

#endif  /// HOLO_PERCEPTION_TRACKING_BBOX_TRACKER_H_