/*!
 *  \brief
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2018-05-17
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_TRACKING_BBOX_KF_TRACKER_H_
#define HOLO_PERCEPTION_TRACKING_BBOX_KF_TRACKER_H_

#include <memory>
#include <mutex>
#include <vector>
#include <holo/numerics/vector.h>
// #include "holo/numerics/impl/vector.hpp"
#include <holo/numerics/matrix.h>
// #include "holo/numerics/impl/matrix.hpp"

#include <boost/circular_buffer.hpp>
// #include <gtest/gtest.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>
#include <holo/perception/utils/uid_generator.h>
#include <holo/perception/common/box2d.h>
#include <holo/perception/algorithm/tracking/bbox_tracker.h>
#include <holo/perception/utils/utility.h>
#include <holo/perception/common/impl/box2d.hpp>
#include <holo/perception/tracking/impl/hungarian_optimizer.hpp>

namespace holo 
{

/// define template of variable-length vectors
template<typename Scalar> using EigenVectorT = Eigen::Matrix<Scalar, Eigen::Dynamic, 1, Eigen::ColMajor>;
typedef int32_t TAtype;

namespace perception
{
    typedef holo::perception::Box2DT<float32_t> BBox2f;
class KFTrackingBBox
{
public:
    KFTrackingBBox(ImageBBox2f& box);
    KFTrackingBBox(const KFTrackingBBox& instance)
    {
        *this = instance;
    }
    ~KFTrackingBBox()
    {
    }

    ImageBBox2f Predict();

    void Update(ImageBBox2f& box);

    inline uint64_t GetId() const noexcept;

    ImageBBox2f GetBox();

    inline uint32_t time_since_update() const
    {
        return time_since_update_;
    }

    inline uint32_t hits() const
    {
        return hits_;
    }

    inline uint32_t hit_streak() const
    {
        return hit_streak_;
    }

    inline uint32_t age() const
    {
        return age_;
    }

    inline holo::Classification classification() const
    {
        return classification_;
    }

    inline float32_t confidence() const
    {
        return confidence_;
    }

private:
    void Init(ImageBBox2f& box);

private:
    std::shared_ptr<cv::KalmanFilter> kf_;

    /// [x, y, s, r, d_x, d_y, d_s], s=w*h, r=w/h
    uint16_t kf_state_num_;

    /// [x, y, s, r]
    uint16_t kf_measure_num_;

    /// no control
    uint16_t kf_control_num_;

    /// uid
    uint64_t id_;

    /// param in sort
    uint32_t                            time_since_update_;  /// default 0
    uint32_t                            hits_;               /// default 0
    uint32_t                            hit_streak_;         /// default 0
    uint32_t                            age_;                /// default 0
    boost::circular_buffer<ImageBBox2f> history_boxes_;
    ImageBBox2f                         current_box_;
    holo::Classification                classification_;
    float32_t                           confidence_;

    TrackState state_;
};

using KFBBoxList = std::vector<KFTrackingBBox>;

class BBoxKFTracker : public BBoxTrackerBase
{
public:
    /// @brief constructor
    BBoxKFTracker();

    /// @brief deconstructor

    ~BBoxKFTracker()
    {
    }

    /// @brief smart pointer
    using Ptr      = std::shared_ptr<BBoxKFTracker>;
    using ConstPtr = std::shared_ptr<const BBoxKFTracker>;

    virtual bool Tracking(ImageBBoxList& in_boxes, ImageBBoxList& out_boxes);
    void         SetMinIOU(float32_t min_iou);

private:
    // holo::VectorXT<int32_t> Associate(ImageBBoxList& trks, ImageBBoxList& dets);
    // EigenVectorT<int32_t> Associate(ImageBBoxList& trks, ImageBBoxList& dets);
    std::vector<TAtype> Associate(ImageBBoxList& trks, ImageBBoxList& dets);
    

private:
    // HungarianOptimizer<float32_t, float32_t> hungarian_optimizer_;
    holo::perception::HungarianOptimizer<holo::int32_t, holo::float32_t> hungarian_optimizer_;

    uint32_t   max_age_;
    uint32_t   min_hits_;
    KFBBoxList trackers_;
    uint32_t   frame_count_;
    float32_t  min_iou_;
};

}  // namespace perception
}  // namespace holo

#endif  /// HOLO_PERCEPTION_TRACKING_BBOX_KF_TRACKER_H_
