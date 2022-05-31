/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_types.h
 * @brief this file defines common_types for semantic slam
 * @author Yanwei Du (duyanwei@holomatic.com), Heiko Yu (yuchangsong@holomatic.com), Changxi
 * Cheng(chengchangxi@holomatic.com)
 * @date 2021-02-25
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_COMMON_TYPES_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_COMMON_TYPES_H_

#include <holo/localization/vision/vslam/common_types.h>
#include <holo/localization/vision/vslam/semantic/parking_slot_track.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
namespace semantic
{
/**
 * @addtogroup semantic
 * @{
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define birdview parameters
 *
 * @details explain the relationship between ground frame and body frame
 *
 *  body frame                                ground plane
 *        x                                      o----->x
 *        ^                                      |
 *        |    -> t(ymax, -xmin, -height)        |
 *        |    -> Rz(-90.0deg)Rx(180.0deg)       v
 *        |                                      y
 *  y<----o
 *
 */
struct BirdviewParameters
{
    Scalar pixel_per_meter = 1.0;                ///< the resolution of the bird view image (unit meter)
    Pose3  bEg             = Pose3::Identity();  ///< extrinsic parameters between ground and body

    /**
     * @brief convert Point2 in image frame to Point3 in body frame
     *
     * @param pti point on image plane
     * @return Point3
     */
    Point3 convertToBody(const Point2& pti) const;

    /**
     * @brief convert Point3 in body frame to Point2 in image frame
     *
     * @param ptb point in body frame
     * @param downscale downscale coefficient
     * @return Point3 point in image frame
     */
    Point3 convertToImage(const Point3& ptb, const Scalar downscale = 1.0) const;

    /**
     * @brief output stream for Parameters
     *
     * @param os std::ostream&
     * @param params parameters
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const BirdviewParameters& params)
    {
        os << "BirdviewParameters:"
           << "\n pixel_per_meter = " << params.pixel_per_meter << "\n extrinsic_from_ground_to_body = " << params.bEg;

        return os;
    }

    // generate parameters
    static BirdviewParameters GenerateExample();

    // load from yaml
    static BirdviewParameters LoadFromYaml(const yaml::Node& node);
};

/**
 * @brief define plane
 */
struct Plane
{
    int64_t               id = -1;
    gtsam::OrientedPlane3 data;
    Pose3                 reference_pose;

    /**
     * @brief Construct a new Plane object\
     *
     */
    Plane() : id(-1)
    {
    }

    /**
     * @brief Create a Plane object
     *
     * @param data
     * @return Plane
     */
    static Plane Create(const gtsam::OrientedPlane3& data, const Pose3& reference_pose)
    {
        return Plane(next_id++, data, reference_pose);
    }

private:
    /**
     * @brief Construct a new Plane object
     *
     * @param _id
     * @param _data
     */
    Plane(int64_t _id, const gtsam::OrientedPlane3& _data, const Pose3& _reference_pose)
      : id(_id), data(_data), reference_pose(_reference_pose)
    {
    }

    // @todo needs to be reset
    static int64_t next_id;
};

/**
 * @brief utility function
 *
 */
class Utility
{
public:
    /**
     * @brief transform ParkingSlot from source to target
     *
     * @param in parking slot in source frame
     * @param tTs transformation that transforms pose from source to target
     * @return ParkingSlotType in target frame
     */
    static ParkingSlotType TransformParkingSlot(const ParkingSlotType& in, const Pose3& tTs);

    /**
     * @brief transform ParkingSlotFrame from source to target
     *
     * @param in parking slot frame in source frame
     * @param tTs transformation that transforms pose from source to target
     * @return ParkingSlotFrameType in target frame
     */
    static ParkingSlotFrameType TransformParkingSlotFrame(const ParkingSlotFrameType& in, const Pose3& tTs);

    /**
     * @brief convert parkingslot to a vector of points for easy computation
     *
     * @param in parking slot
     * @return std::vector<Point3>
     */
    static std::vector<Point3> ConvertToVector(const ParkingSlotType& in);

    /**
     * @brief Generate sample point on line between start and end
     *
     * @param start start point
     * @param end end point
     * @return the generated sample point in line
     */
    static void GeneratePointOnLine(const Point3& start, const Point3& end, std::vector<Point3>& pts);

    /**
     * @brief convert slot map and vehicle pose to pointcloud for futher visualize with pcl
     *
     * @param slot_map slot_map
     * @param trajectory vehicle trajectory
     * @return pointcloud
     */
    static PointCloudXYZIRRgbSt ConvertToPointCloud(const std::unordered_map<int64_t, ParkingSlotType>& slot_map,
                                                    const std::vector<Pose3>&                           trajectory);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @}
 *
 */

}  // namespace semantic

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_COMMON_TYPES_H_
