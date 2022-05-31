/*!
 *  \brief
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2018-05-17
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_DETECTION_IMAGE_DETECTOR_H_
#define HOLO_PERCEPTION_DETECTION_IMAGE_DETECTOR_H_

#include <memory>
#include <vector>

#include <opencv2/features2d.hpp>

#include <holo/perception/common/object2d.h>
#include "holo/perception/common/image_bbox2d.h"
#include <holo/obstacle/obstacle_vision.h>
#include <holo/obstacle/obstacle_list.h>
#include <list>

namespace holo
{

namespace perception
{

template <typename Scalar>
class ImageDetectorBase
{
public:

    /// @brief smart pointer
    using Ptr = std::shared_ptr<ImageDetectorBase>;
    using ConstPtr = std::shared_ptr<const ImageDetectorBase>;

    using ImageBBox2DType = ImageBBox2D<Scalar>;

    using ObstacleVision = ObstacleVisionT<Scalar>;
    using ObstacleVisionPtr = std::shared_ptr<ObstacleVisionT<Scalar> >;
    typedef typename holo::ObstaclePtrListT<ObstacleVisionT< Scalar>, holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY> CameraObstacleList;
    typedef std::list<ObstacleVisionPtr> ObstacleCameraPtrList;
    typedef std::function<void(CameraObstacleList&)> ObstacleDetectionCallback;

    /// @brief constructor
    ImageDetectorBase(){};

    /// @brief deconstructor
    virtual ~ImageDetectorBase(){};

    /// detect with single image
    virtual bool Detect(const cv::Mat&, std::vector<ImageBBox2DType>&)
    {
        return true;
    }

    /// detect with multi-images
    virtual bool Detect(const std::vector<cv::Mat>& ,std::vector<CameraObstacleList>& )
    {
        return true;
    };
};

}   /// end namespace perception
}   /// end namespace holo

#endif  /// HOLO_PERCEPTION_DETECTION_IMAGE_DETECTOR_H_
