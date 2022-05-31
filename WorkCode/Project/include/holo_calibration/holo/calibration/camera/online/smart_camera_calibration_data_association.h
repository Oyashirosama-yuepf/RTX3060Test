/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file smart_camera_calibration_data_association.h
 * @author jiaxing. zhao
 * @brief main function for smart camera calibration
 * @date 2020-08-05
 */

#ifndef HOLO_CALIBRATION_CAMERA_ONLINE_SMART_CAMERA_CALIBRATION_DATA_ASSOCIATION_H_
#define HOLO_CALIBRATION_CAMERA_ONLINE_SMART_CAMERA_CALIBRATION_DATA_ASSOCIATION_H_

#include <holo/calibration/camera/online/smart_camera_calibration_data_container.h>

namespace holo
{
namespace calibration
{
namespace camera
{
/**
 * @addtogroup camera
 * @{
 *
 */

/**
 * @brief This class aims at providing correspondence between smart
 *        camera lane points in 3D and holo camera lane in 2D.
 */
class SmartCameraDataAssociation
{
public:
    using Scalar          = SmartCameraDataContainer::Scalar;
    using Container       = SmartCameraDataContainer;
    using Correspondences = std::vector<Correspondence>;

    /// @brief smart pointer
    using Ptr      = std::shared_ptr<SmartCameraDataAssociation>;
    using ConstPtr = std::shared_ptr<const SmartCameraDataAssociation>;

    /**
     * @brief parameters
     */
    struct Parameters
    {
        /**
         * @brief threshold_diff_time between target and source in sec
         */
        Scalar thresh_diff_time = Scalar(0.1);

        /**
         * @brief verbose
         */
        bool_t verbose = false;

    };  // Parameters

    /**
     * @brief Construct a new Smart Camera Data Association object
     *
     */
    SmartCameraDataAssociation() = delete;

    /**
     * @brief Construct a new Smart Camera Data Association object
     *
     * @param params
     */
    SmartCameraDataAssociation(Parameters const& params);

    /**
     * @brief Destroy the Smart Camera Data Association object
     */
    virtual ~SmartCameraDataAssociation()
    {
    }

    /**
     * @brief compute correspondences
     *
     * @param containers
     * @return std::vector<Correspondences>
     */
    std::vector<Correspondences> ComputeCorrespondences(std::vector<Container> const& containers) const;

private:
    /**
     * @brief the compare operator for sorting data in time order.
     */
    struct StampedTimeCompare
    {
        /**
         * @brief the compare operator for sorting data in ascending time order.
         *
         * @param ls the left timestamp
         *
         * @param rs the right timestamp
         *
         * @return is right order
         */
        bool_t operator()(SmartLanePoints const& ls, SmartLanePoints const& rs) const;

        /**
         * @brief the compare operator for sorting data in ascending time order.
         *
         * @param ls the left timestamp
         *
         * @param rs the right data which contains message header
         *
         * @return is right order
         */
        bool_t operator()(Timestamp const& ls, SmartLanePoints const& rs) const;

        /**
         * @brief the compare operator for sorting data in ascending time order.
         *
         * @param ls the left data which contains message header
         *
         * @param rs the right timestamp
         *
         * @return is right order
         */
        bool_t operator()(SmartLanePoints const& ls, Timestamp const& rs) const;

    };  // StampedTimeCompare

    /**
     * @brief Get the Nearest Element object
     *
     * @param t queried timestamp
     * @param queue SmartLanePoints vector
     * @return SmartLanePoints
     */
    OptionalT<SmartLanePoints> getNearestElement(Timestamp const& t, std::vector<SmartLanePoints> const& queue,
                                                 Parameters const& params) const;

private:
    const Parameters params_;

};  // SmartCameraDataAssociation

/**
 * @}
 *
 */

}  // namespace camera

}  // namespace calibration

}  // namespace holo

#endif /* ----- #ifndef HOLO_CALIBRATION_CAMERA_ONLINE_SMART_CAMERA_CALIBRATION_DATA_ASSOCIATION_H_  ----- */