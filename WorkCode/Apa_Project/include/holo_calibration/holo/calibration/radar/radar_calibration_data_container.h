/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/*!
 * @file radar_calibration_data_container.h
 * @brief the definition of radar data container
 * @author yangpeiwen@holomatic.com
 * @date 2020-10-26
 */

#ifndef HOLO_CALIBRATION_RADAR_RADAR_CALIBRATION_DATA_CONTAINER_H_
#define HOLO_CALIBRATION_RADAR_RADAR_CALIBRATION_DATA_CONTAINER_H_

#include <holo/calibration/common/data_container_base.h>
#include <holo/calibration/radar/types.h>
#include <holo/common/optional.h>

namespace holo
{
namespace calibration
{
namespace radar
{
/**
 * @addtogroup radar
 * @{
 *
 */

///////////////////////////////////////////////////////////////////////////////
/**
 * @ingroup calibration
 * @brief Radar Data Container
 * @details The data of vehicle chassis and radar are stored, preprocessed and segmented reasonably
 */
class RadarDataContainer : public DataContainerBaseT<RadarFrames, ChassisState>
{
public:
    using Base = DataContainerBaseT<RadarFrames, ChassisState>;

    /// @brief smart pointer
    using Ptr      = std::shared_ptr<RadarDataContainer>;
    using ConstPtr = std::shared_ptr<const RadarDataContainer>;

    using Base::extrinsic_;
    using Base::GetExtrinsic;

    /**
     * @brief parameters
     */
    struct Parameters
    {
        /**
         * @brief max lateral acceleration unit in m/s2
         */
        Scalar lat_acc_max = Scalar(0.15);

        /**
         * @brief chassis min speed unit in m/s
         */
        Scalar chassis_speed_min = Scalar(22);

        /**
         * @brief max yawrate unit in rad/s
         */
        Scalar yawrate_max = Scalar(0.2);

        /**
         * @brief max steer angle unit in radian
         */
        Scalar steer_angle_max = Scalar(0.02);

        /**
         * @brief threshold of static object speed between chassis speed unit in m/s
         * @details compare abs(radar_point_speed - chassis_speed) as one condition of static object filtering
         */
        Scalar thresh_static_object_speed_diff_chassis_speed_max = Scalar(0.5);

        /**
         * @brief mininum frame num for a segemented points cloud
         *
         */
        uint32_t min_frame_num = uint32_t(1024);
    };

    /**
     * @brief Default constructor was disable
     *
     */
    RadarDataContainer() = delete;

    /**
     * @brief Construct a new Radar Data Container object
     *
     * @param radar_frames radar's point cloud measurement
     * @param chassis_states car chassis states measurement
     * @param paramters
     * @throw std::invalid_argument if chassis_states size is less than two
     */
    RadarDataContainer(RadarFrames const& radar_frames, std::vector<ChassisState> const& chassis_states,
                       Parameters const& params);

    /**
     * @brief Destroy the Radar Data Container object
     *
     */
    virtual ~RadarDataContainer()
    {
    }

    /**
     * @brief the size of points cloud
     */
    virtual uint16_t GetDataSize() const override;

    /**
     * @brief get ith element in sources
     *
     * @throws std::out_of_range Thrown if index >= size()
     */
    virtual const RadarFrames& GetSource(uint16_t const index) const override;

    /**
     * @brief get ith element in sources
     *
     * @throws std::out_of_range Thrown if index >= size()
     */
    virtual RadarFrames& GetSource(uint16_t const index) override;

    /**
     * @brief get sources
     */
    const std::vector<RadarFrames>& GetSource() const;

    /**
     * @brief get sources
     */
    std::vector<RadarFrames>& GetSource();

    /**
     * @brief get ith element in targets
     * @note this function is pure virtual functions in base, this class is not used it.
     * @throws std::out_of_range Thrown if index >= size()
     */
    virtual const ChassisState& GetTarget(uint16_t const index) const override;

    /**
     * @brief get ith element in targets
     * @note this function is pure virtual functions in base, this class is not used it.
     * @throws std::out_of_range Thrown if index >= size()
     */
    virtual ChassisState& GetTarget(uint16_t const index) override;

    /**
     * @brief get targets
     * @note this function is pure virtual functions in base, this class is not used it.
     */
    const std::vector<ChassisState>& GetTarget() const;

    /**
     * @brief get targets
     * @note this function is pure virtual functions in base, this class is not used it.
     */
    std::vector<ChassisState>& GetTarget();

    /**
     * @brief update status
     */
    virtual void UpdateStatus() override;

    /**
     * @brief Get the Filtered Segmented Radar Points Size object
     *
     * @return uint8_t
     */
    uint8_t GetFilteredSegPointsSize() const noexcept;

    /**
     * @brief get the filtered segmented radar points
     *
     * @return std::vector<std::vector<RadarPoint>> const&
     */
    std::vector<std::vector<RadarPoint>> const& GetFilteredSegPoints() const noexcept;

    /**
     * @brief get the index filtered segmented radar points
     *
     * @params i segmented radar points index
     * @return std::vector<RadarPoint> const&
     */
    std::vector<RadarPoint> const& GetFilteredSegPoints(uint8_t const i) const;

private:
    /**
     * @brief get the radar points cloud
     *
     * @return RadarFrames const&
     */
    RadarFrames const& getRadarFrames() const noexcept;

    /**
     * @brief filter every frame's points according to chassis state
     *
     * @param radar_frames all radar frames
     * @return std::vector<RadarPoint> const&
     */
    std::vector<RadarPoint> filterFramePoints(RadarFrames const& radar_frames);

    /**
     * @brief Get the Chassis State object at searched time
     *
     * @param search_time
     * @return OptionalT<ChassisState>
     */
    OptionalT<ChassisState> getChassisState(Timestamp const& search_time);

    /**
     * @brief linear interpolation for chassis state
     *
     * @param left
     * @param right
     * @return OptionalT<ChassisState>
     */
    OptionalT<ChassisState> linearInterpolation(ChassisState const& left, ChassisState const& right,
                                                Timestamp const& inter_time);

    /**
     * @brief segment all radar measurement to multi slice
     *
     * @param radar_frames
     */
    void segmentRadarFrames(RadarFrames const& radar_frames);

    /**
     * @brief all radar points
     *
     */
    RadarFrames radar_frames_;

    /**
     * @brief all radar points are segmented
     */
    std::vector<RadarFrames> segmented_radar_frames_;

    /**
     * @brief all static object points, filtered by motion parameter
     *
     */
    std::vector<std::vector<RadarPoint>> filtered_segmented_points_;

    /**
     * @brief car chassis status
     */
    std::vector<ChassisState> chassis_states_;

    /**
     * @brief save chassis state timestamps from low to high in unit sec
     */
    std::vector<Scalar> chassis_state_timestamps_;

    /**
     * @brief parameters
     */
    Parameters params_;

    friend class RadarDataContainerTester;
};  // RadarDataContainer

/**
 * @}
 *
 */
}  // namespace radar

}  // namespace calibration

}  // namespace holo

#endif /* ----- #ifndef HOLO_CALIBRATION_RADAR_RADAR_CALIBRATION_DATA_CONTAINER_H_  ----- */
