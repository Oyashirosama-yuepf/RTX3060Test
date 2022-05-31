/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file smart_camera_calibration_data_container.h
 * @author jiaxing. zhao(zhaojiaxing@holomatic.com)
 * @brief main function for smart camera calibration
 * @date 2019-11-28
 */

#ifndef HOLO_CALIBRATION_CAMERA_ONLINE_SMART_CAMERA_CALIBRATION_DATA_CONTAINER_H_
#define HOLO_CALIBRATION_CAMERA_ONLINE_SMART_CAMERA_CALIBRATION_DATA_CONTAINER_H_

#include <holo/calibration/camera/online/types.h>
#include <holo/calibration/common/data_container_base.h>
#include <holo/common/optional.h>

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

///////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup calibration
 * @brief SmartCamera Data Container
 * @details This class aims at providing multiple smart lane sample frames in 3D,
 *          and holo cmaera detected lane in 2D.
 */
class SmartCameraDataContainer : public DataContainerBaseT<SmartLanePoints, HoloLane2D>
{
public:
    using Base = DataContainerBaseT<SmartLanePoints, HoloLane2D>;

    /// @brief smart pointer
    using Ptr      = std::shared_ptr<SmartCameraDataContainer>;
    using ConstPtr = std::shared_ptr<const SmartCameraDataContainer>;

    using Base::extrinsic_;
    using Base::GetExtrinsic;

    /**
     * @brief parameters
     */
    struct Parameters
    {
        /**
         * @brief height from body to ground unit in [m]
         */
        Scalar body_to_ground = Scalar(-0.28);

        /**
         * @brief sample distance in metre
         * @details 1.smart camera lane model in 3D: y = c3*x*x*x + c2*x*x + c1*x + c0
         *          2.foreach x_start = lane.start to x_end = x_start + sample_distance
         *            to compute y.
         */
        Scalar sample_distance = Scalar(20.0);

        /**
         * @brief sample step
         */
        Scalar_32_t sample_step = Scalar_32_t(1.0);

        /**
         * @brief the threshold of smart lane confidence, [min, max]=>[0, 100]
         */
        Scalar thresh_smart_lane_confidence = Scalar(0);

        /**
         * @brief verbose
         */
        bool_t verbose = false;

    };  // Parameters

    /**
     * @brief Construct a new Smart Camera Data Container object
     */
    SmartCameraDataContainer() = delete;

    /**
     * @brief Construct a new Smart Camera Data Container object
     *
     * @param smart_lanes
     * @param lanes
     * @param params
     */
    SmartCameraDataContainer(std::vector<RoadFrameType> const& smart_lanes, std::vector<HoloLane2D> const& lanes,
                             Parameters const& params);

    /**
     * @brief Destroy the Smart Camera Data Container object
     */
    virtual ~SmartCameraDataContainer()
    {
    }

    /**
     * @brief the size of data
     */
    virtual uint16_t GetDataSize() const override;

    /**
     * @brief get ith element in sources
     *
     * @throws std::out_of_range Thrown if index >= size()
     */
    virtual const SmartLanePoints& GetSource(uint16_t const index) const override;

    /**
     * @brief get ith element in sources
     *
     * @throws std::out_of_range Thrown if index >= size()
     */
    virtual SmartLanePoints& GetSource(uint16_t const index) override;

    /**
     * @brief get sources
     */
    const std::vector<SmartLanePoints>& GetSource() const;

    /**
     * @brief get sources
     */
    std::vector<SmartLanePoints>& GetSource();

    /**
     * @brief get ith element in targets
     *
     * @throws std::out_of_range Thrown if index >= size()
     */
    virtual const HoloLane2D& GetTarget(uint16_t const index) const override;

    /**
     * @brief get ith element in targets
     *
     * @throws std::out_of_range Thrown if index >= size()
     */
    virtual HoloLane2D& GetTarget(uint16_t const index) override;

    /**
     * @brief get targets
     */
    const std::vector<HoloLane2D>& GetTarget() const;

    /**
     * @brief get targets
     */
    std::vector<HoloLane2D>& GetTarget();

    /**
     * @brief update status
     */
    virtual void UpdateStatus() override;

protected:
    /**
     * @brief sample one smart line points
     */
    std::vector<Point3Type> sampleSmartLanePoints(LaneBoundaryType const& lane, Parameters const& param);

    /**
     * @brief sample smart lanes points
     *
     * @param lane_boundaries
     * @param param
     * @return SmartLanePoints
     */
    SmartLanePoints extractSmartLanePoints(RoadFrameType const& lane_boundaries, Parameters const& param);

    std::vector<SmartLanePoints> smart_lane_frames_;
    std::vector<HoloLane2D>      holo_lane_frames_;
    const Parameters             params_;

private:
};  // SmartCameraDataContainer

/**
 * @}
 *
 */
}  // namespace camera

}  // namespace calibration

}  // namespace holo

#endif /* ----- #ifndef HOLO_CALIBRATION_CAMERA_ONLINE_SMART_CAMERA_CALIBRATION_DATA_CONTAINER_H_  ----- */
