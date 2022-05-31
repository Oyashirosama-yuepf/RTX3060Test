/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file types.h
 * @brief The define of common types
 * @author Li Chao (lichao@holomatic.com)
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @author Li Yue (liyue@holomatic.com)
 * @date Dec 28, 2021
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_TYPES_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_TYPES_H_

#include <holo/localization/common/types.h>
#include <holo/localization/tightly_coupled_fusion/map/map_service_client_base.h>
#include <holo/localization/vision/common/mat.h>
#include <holo/vision/image_objects.h>
#include <holo/vision/keypoint2.h>
#include <holo/vision/object.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
namespace sign
{
/**
 * @addtogroup sign
 * @{
 *
 */
using KeyPoint2Type               = holo::vision::KeyPoint2f;
using ObjectKeyPoint2Type         = holo::vision::ObjectT<KeyPoint2Type>;
using ImageObjectsType            = holo::vision::ImageObjectsT<ObjectKeyPoint2Type>;
using MapObjectType               = holo::localization::tightly_coupled_fusion::map::MapServiceClientBase::MapObject;
using LineCorrespondence          = holo::localization::LaneCorrespondences;
using PointCorrespondence         = holo::localization::PointCorrespondence;
using StampedAdvancedNavstateType = StampedT<AdvancedNavstateType>;

/**
 * @brief define struct to store semantic raw measurements for visual semantic processor
 *
 */
struct VisualSemanticRawMeasurement
{
    ImageObjectsType image_objects_measurement;  ///< image object measurement

    ///< The predicted fusion NavState based on the last smoothing result and Imu preintegration
    StampedAdvancedNavstateType predicted_fusion_navstate;
};

/**
 * @brief Define struct to store semantic and map objects for data association
 *
 */
struct VisualSemanticMeasurement
{
    ImageObjectsType           image_objects;     ///< image object
    std::vector<MapObjectType> map_objects;       ///< vector of map object
    AdvancedNavstateType       current_navstate;  ///< current navstate
};

/**
 * @brief Define struct to store image object
 *
 */
struct ImageObjectsInfo
{
    std::vector<Point2Type>              centroid_buffer;  ///< centroid buffer of image object
    std::vector<std::vector<Point2Type>> contour_buffer;   ///< contour buffer of image object
};

/**
 * @brief Define struct to store map object
 *
 */
struct MapObjectsInfo
{
    std::vector<Point3Type>              centroid_buffer;             ///< centroid buffer of map object
    std::vector<Point2Type>              projection_centroid_buffer;  ///< projection centroid buffer of map object
    std::vector<std::vector<Point3Type>> contour_buffer;              ///< contour buffer of map object
};

/**
 * @}
 *
 */
}  // namespace sign

}  // namespace tightly_coupled_fusion

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_SIGN_SIGN_PROCESSOR_H_
