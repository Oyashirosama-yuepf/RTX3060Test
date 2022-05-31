/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file measurements_manager_base.h
 * @brief define measurements_manager class
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#ifndef HOLO_LOCALIZATION_COMMON_MEASUREMENT_MANAGER_BASE_H_
#define HOLO_LOCALIZATION_COMMON_MEASUREMENT_MANAGER_BASE_H_

#include <memory>
#include <mutex>
#include <vector>

#include <holo/common/chassis_state.h>
#include <holo/container/details/ordered_buffer.h>
#include <holo/localization/common/types.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief base class for measurements manager
 */
class MeasurementsManagerBase
{
public:
    /**
     * @brief define measurements buffer size
     *
     */
    const static std::size_t kImuBufferSize              = 1000u;
    const static std::size_t kOdometryBufferSize         = 1000u;
    const static std::size_t kPositionBufferSize         = 100u;
    const static std::size_t kRoadFrameBufferSize        = 20u;
    const static std::size_t kStampedRouteInfoBufferSize = 5u;
    const static std::size_t kChassisStateBufferSize     = 500u;
    const static std::size_t kImageBufferSize            = 100u;
    const static std::size_t kGnssPvtBufferSize          = 10u;

    // handy typedefs
    template <typename Key, std::size_t N, typename Compare = std::less<Key> >
    using OrderedBuffer       = container::details::OrderedBuffer<Key, N, Compare>;
    using ImuBufferType       = OrderedBuffer<ImuType, kImuBufferSize, StampedTimeCompareT<ImuType> >;
    using OdometryBufferType  = OrderedBuffer<OdometryType, kOdometryBufferSize, StampedTimeCompareT<OdometryType> >;
    using PositionBufferType  = OrderedBuffer<GnssPosition, kPositionBufferSize, StampedTimeCompareT<GnssPosition> >;
    using RoadFrameBufferType = OrderedBuffer<RoadFrame, kRoadFrameBufferSize, StampedTimeCompareT<RoadFrame> >;

    /* the compare functor is redundant for a StampedT type, but it helps save one template parameter @line303 */
    /* duyanwei@holomatic.com */
    using StampedRouteInfoBufferType =
        OrderedBuffer<StampedRouteInfoType, kStampedRouteInfoBufferSize, StampedTimeCompareT<StampedRouteInfoType> >;
    using ChassisStateBufferType =
        OrderedBuffer<ChassisState, kChassisStateBufferSize, StampedTimeCompareT<ChassisState> >;
    using ImageBufferType   = OrderedBuffer<ImageType, kImageBufferSize, StampedTimeCompareT<ImageType> >;
    using GnssPvtBufferType = OrderedBuffer<GnssPvtType, kGnssPvtBufferSize, StampedTimeCompareT<GnssPvtType> >;

    using Ptr      = std::shared_ptr<MeasurementsManagerBase>;
    using ConstPtr = std::shared_ptr<const MeasurementsManagerBase>;

    /**
     * @brief constructor
     */
    MeasurementsManagerBase();

    /**
     * @brief destructor
     */
    virtual ~MeasurementsManagerBase() noexcept;

    /**
     * @brief reset function
     *
     * @details all measurements stored in each buffer will be cleared.
     *          You may call this function whenever reboot the entire system.
     */
    virtual void Reset();

    /**
     * @brief add ground truth
     *
     * @param m ground truth measurement
     * @return bool_t it returns false when fails to add the measurement
     */
    virtual bool_t AddGroundTruth(const OdometryType& m);

    /**
     * @brief add imu measurement
     *
     * @param m imu measurement
     * @return bool_t it returns false when fails to add the measurement
     */
    virtual bool_t AddMeasurement(const ImuType& m);

    /**
     * @brief add odometry measurement
     *
     * @param m odometry measurement
     * @return bool_t it returns false when fails to add the measurement
     */
    virtual bool_t AddMeasurement(const OdometryType& m);

    /**
     * @brief add gnss position
     *
     * @param m position measurement
     * @return bool_t it returns false when fails to add the measurement
     */
    virtual bool_t AddMeasurement(const GnssPosition& m);

    /**
     * @brief Add gnss pvt
     *
     * @param m Gnss pvt measurement
     * @return bool_t it returns false when fails to add the measurement
     */
    virtual bool_t AddMeasurement(const GnssPvtType& m);

    /**
     * @brief add road frame measurements
     *
     * @param m road frame measurement
     * @return bool_t it returns false when fails to add the measurement
     */
    virtual bool_t AddMeasurement(const RoadFrame& m);

    /**
     * @brief add stamped route info measurements
     *
     * @param m stamped route info measurement
     * @return bool_t it returns false when fails to add the measurement
     */
    virtual bool_t AddMeasurement(const StampedRouteInfoType& m);

    /**
     * @brief add chassis state measurements
     *
     * @param[in] m chassis state measurement
     * @return bool_t it returns false when fails to add the measurement
     */
    virtual bool_t AddMeasurement(const ChassisState& m);

    /**
     * @brief add image measurements
     *
     * @param[in] m image measurement
     * @return bool_t it returns false when fails to add the measurement
     */
    virtual bool_t AddMeasurement(const ImageType& m);

    /**
     * @brief get latest ground truth of the queue
     *
     * @param m ground truth measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetLatestGroundTruth(OdometryType& m);

    /**
     * @brief get latest ImuType of the queue
     *
     * @param m imu measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetLatestMeasurement(ImuType& m);

    /**
     * @brief get latest odometry of the queue
     *
     * @param m odometry measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetLatestMeasurement(OdometryType& m);

    /**
     * @brief get latest gnss position of the queue
     *
     * @param m position measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetLatestMeasurement(GnssPosition& m);

    /**
     * @brief get latest gnss pvt of the queue
     *
     * @param m Gnss pvt measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetLatestMeasurement(GnssPvtType& m);

    /**
     * @brief get latest road frame of the queue
     *
     * @param m road frame measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetLatestMeasurement(RoadFrame& m);

    /**
     * @brief get the latest chassis state of the queue
     *
     * @param[in] m chassis state measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetLatestMeasurement(ChassisState& m);

    /**
     * @brief get the latest image of the queue
     *
     * @param[in] m image measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetLatestMeasurement(ImageType& m);

    /**
     * @brief get and pop oldest road frame of the queue
     *
     * @param m road frame measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetAndPopOldestMeasurement(RoadFrame& m);

    /**
     * @brief get nearest ground truth of the queue with a timestamp
     *
     * @param t timestamp
     * @param m ground truth measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetNearestGroundTruth(const Timestamp& t, OdometryType& m);

    /**
     * @brief get nearest imu of the queue with a timestamp
     *
     * @param t timestamp
     * @param m imu measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetNearestMeasurement(const Timestamp& t, ImuType& m);

    /**
     * @brief get nearest odometry of the queue with a timestamp
     *
     * @param t timestamp
     * @param m odometry measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetNearestMeasurement(const Timestamp& t, OdometryType& m);

    /**
     * @brief get nearest route info of the queue with a timestamp
     *
     * @param t timestamp
     * @param m stamped route info measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetNearestMeasurement(const Timestamp& t, StampedRouteInfoType& m);

    /**
     * @brief get the nearest chassis state of the queue with a timestamp
     *
     * @param[in] t the given timestamp
     * @param[in] m chassis state measurement at t
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetNearestMeasurement(const Timestamp& t, ChassisState& m);

    /**
     * @brief get the nearest image of the queue with a timestamp
     *
     * @param[in] t the given timestamp
     * @param[in] m image measurement near t
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetNearestMeasurement(const Timestamp& t, ImageType& m);

    /**
     * @brief get the nearest gnss pvt of the queue with a timestamp
     *
     * @param[in] t the given timestamp
     * @param[in] m gnss pvt measurement near t
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetNearestMeasurement(const Timestamp& t, GnssPvtType& m);

    /**
     * @brief get ground truth at current timestamp
     *
     * @param t timestamp
     * @param m ground truth measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetCurrentGroundTruth(const Timestamp& t, OdometryType& m);

    /**
     * @brief get odometry at current timestamp
     *
     * @param t timestamp
     * @param m odometry measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetCurrentMeasurement(const Timestamp& t, OdometryType& m);

    /**
     * @brief get chassis at current timestamp
     *
     * @param[in] t the given timestamp
     * @param[in] m chassis state measurement at t
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetCurrentMeasurement(const Timestamp& t, ChassisState& m);

    /**
     * @brief get gnss pvt at current timestamp. If there is no such measurement in the buffer, we will get it by
     * interpolation or exterpolation.
     *
     * @param t timestamp
     * @param m odometry measurement
     * @return bool_t it returns false when fails to find such a measurement
     */
    virtual bool_t GetCurrentMeasurement(const Timestamp& t, GnssPvtType& m);

    /**
     * @brief Get imus between two timestamps
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param imus imu measurements
     * @return bool_t it returns false when fails to find such measurements
     */
    virtual bool_t GetMeasurementsBetween(const Timestamp& left, const Timestamp& right, std::vector<ImuType>& imus);

    /**
     * @brief Get odometries between two timestamps
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param odometries odometries
     * @return bool_t it returns false when fails to find such measurements
     */
    virtual bool_t GetMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                          std::vector<OdometryType>& odometries);

    /**
     * @brief Get positions between two timestamps
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param positions position measurements
     * @return bool_t it returns false when fails to find such measurements
     */
    virtual bool_t GetMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                          std::vector<GnssPosition>& positions);

    /**
     * @brief Get gnss pvt measurements between two timestamps
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param gnss_pvts gnss pvt measurements
     * @return bool_t it returns false when fails to find such measurements
     */
    virtual bool_t GetMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                          std::vector<GnssPvtType>& gnss_pvts);

    /**
     * @brief Get road frame between two timestamps
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param road_frames road frame measurements
     * @return bool_t it returns false when fails to find such measurements
     */
    virtual bool_t GetMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                          std::vector<RoadFrame>& road_frames);

    /**
     * @brief Get chassis states between two timestamps
     *
     * @param left left timestamp
     * @param right right timestamp
     * @param chassis_states chassis state measurement
     * @return bool_t it returns false when fails to find such measurements
     */
    virtual bool_t GetMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                          std::vector<ChassisState>& chassis_states);

    /**
     * @brief Get aligned imus between two timestamps
     *
     * @note measurements at boundary are either interpolated or extrapolated
     * @todo add boundary stamp checking and output detailed failure reason
     * @param left left timestamp
     * @param right right timestamp
     * @param imus imus
     * @return bool_t it returns false when fails to find such measurements
     */
    virtual bool_t GetAlignedMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                 std::vector<ImuType>& imus);

    /**
     * @brief Get aligned odometries between two timestamps
     *
     * @note measurements at boundary are either interpolated or extrapolated
     * @todo add boundary stamp checking and output detailed failure reason
     * @param left left timestamp
     * @param right right timestamp
     * @param odometries interpolated odometries
     * @return bool_t it returns false when fails to find such measurements
     */
    virtual bool_t GetAlignedMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                 std::vector<OdometryType>& odometries);

    /**
     * @brief Get aligned gnss pvt measurements between two timestamps
     *
     * @note measurements at boundary are either interpolated or extrapolated
     * @todo add boundary stamp checking and output detailed failure reason
     * @param left left timestamp
     * @param right right timestamp
     * @param gnss_pvts interpolated gnss pvt measurments
     * @return bool_t it returns false when fails to find such measurements
     */
    virtual bool_t GetAlignedMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                 std::vector<GnssPvtType>& gnss_pvts);

    /**
     * @brief Get the aligned chassis state measurements between timestamps
     *
     * @note measurements at boundary are either interpolated or extrapolated
     * @todo add boundary stamp checking and output detailed failure reason
     * @param left left timestamp
     * @param right right timestamp
     * @param chassis_states interpolated chassis state measurments
     * @return bool_t it returns false when fails to find such measurements
     */
    virtual bool_t GetAlignedMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                 std::vector<ChassisState>& chassis_states);

    /**
     * @brief return ground truth number
     */
    inline uint16_t GetGroundTruthNum() const
    {
        return static_cast<uint16_t>(ground_truth_buffer_.size());
    }

    /**
     * @brief return imu number
     */
    inline uint16_t GetImuNum() const
    {
        return static_cast<uint16_t>(imu_buffer_.size());
    }

    /**
     * @brief return odometry number
     */
    inline uint16_t GetOdometryNum() const
    {
        return static_cast<uint16_t>(odometry_buffer_.size());
    }

    /**
     * @brief return position number
     */
    inline uint16_t GetPositionNum() const
    {
        return static_cast<uint16_t>(position_buffer_.size());
    }

    /**
     * @brief return gnss pvt number
     */
    inline uint16_t GetGnssPvtNum() const
    {
        return static_cast<uint16_t>(gnss_pvt_buffer_.size());
    }

    /**
     * @brief return road frame number
     */
    inline uint16_t GetRoadFrameNum() const
    {
        return static_cast<uint16_t>(road_frame_buffer_.size());
    }

    /**
     * @brief return chassis state number
     */
    inline uint16_t GetChassisStateNum() const
    {
        return static_cast<uint16_t>(chassis_state_buffer_.size());
    }

    /**
     * @brief return image number
     */
    inline uint16_t GetImageNum() const
    {
        return static_cast<uint16_t>(image_buffer_.size());
    }

    // @TODO move these function outside, and provide a interpolater for each type lishuaijie@holomatic.com
    //       currently, its coding style is wrong, it should be fixed when tightly coupled fusion works well
    /**
     * @brief interpolate measurement, need specialization for specific measurement
     *
     * @tparam T measurement type
     * @param T left timestamp
     * @param T right timestamp
     * @param Timestamp interpolated timestamp
     * @return MeasurementType
     */
    template <typename T>
    static T interpolateT(const T&, const T&, const Timestamp&)
    {
        throw std::runtime_error("InterpolateT: unsupported MeasurementType !!!");
        return T();
    }

    /**
     * @brief extrapolate measurment, needs specialization for specific measurement
     *
     * @tparam T measurement type
     * @param T left timestamp
     * @param T right timestamp
     * @param T extrapolated timestamp
     * @return MeasurementType
     */
    template <typename T>
    static T extrapolateT(const T&, const T&, const Timestamp&)
    {
        throw std::runtime_error("ExtrapolateT: unsupported MeasurementType !!!");
        return T();
    }

    /**
     * @brief linear interpolation
     *
     * @details interpolated_data = (1.0 - ratio) * left + ratio * right
     * @param[in] left left data
     * @param[in] right right data
     * @param[in] ratio interpolated ratio
     * @return interpolated data
     */
    template <typename T>
    static T linearInterpolationT(const T& left, const T& right, const Scalar ratio)
    {
        return ((1.0 - ratio) * left + ratio * right);
    }

protected:
    /**
     * @brief insert measurement m with timestamp t to proper position in queue
     *
     * @tparam T measurement type
     * @tparam SIZE buffer size
     * @param m measurement
     * @param buffer measurement buffer
     * @return bool_t it returns false when fails to insert the measurement
     */
    template <typename T, std::size_t SIZE>
    bool_t insertMeasurementT(const T& m, OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >& buffer);

    /**
     * @brief get latest measurement of the queue
     *
     * @tparam T measurement type
     * @tparam SIZE buffer size
     * @param[in] buffer the circular buffer of the measurements
     * @param[out] m the measurement which is latest to the timestamp
     * @return bool_t it returns false when fails to find such a measurement
     */
    template <typename T, std::size_t SIZE>
    bool_t getLatestMeasurementT(const OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >& buffer, T& m) const;

    /**
     * @brief get nearest measurement of the queue with a timestamp
     *
     * @tparam T measurement type
     * @tparam SIZE buffer size
     * @param[in] t the query timestamp
     * @param[in] buffer the circular buffer of the measurements
     * @param[out] m the measurement which is nearest to the timestamp
     * @return bool_t it returns false when fails to find such a measurement
     */
    template <typename T, std::size_t SIZE>
    bool_t getNearestMeasurementT(const Timestamp& t, const OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >& buffer,
                                  T& m) const;

    /**
     * @brief get current measurement of the queue with current timestamp
     *
     * @details interpolation or extrapolation is conducted when necessary
     * @tparam T measurement type
     * @tparam SIZE buffer size
     * @param[in] t the query timestamp
     * @param[in] buffer the circular buffer of the measurements
     * @param[out] m the measurement which is nearest to the timestamp
     * @return bool_t it returns false when fails to find such a measurement
     */
    template <typename T, std::size_t SIZE>
    bool_t getCurrentMeasurementT(const Timestamp& t, const OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >& buffer,
                                  T& m) const;

    /**
     * @brief get measurements between two timestamps
     *
     * @tparam T measurement type
     * @tparam SIZE buffer size
     * @param[in] start the left boundary of timestamp
     * @param[in] end the right boundary of timestamp
     * @param[in] buffer the circular buffer of the measurements
     * @param[out] measurements the measurements which are between these timestamps
     * @return bool_t it returns false when fails to find such measurements
     */
    template <typename T, std::size_t SIZE>
    bool_t getMeasurementsBetweenT(const Timestamp& start, const Timestamp& end,
                                   const OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >& buffer,
                                   std::vector<T>&                                        measurements) const;

    /**
     * @brief get aligned measurements between two timestamps
     *
     * @tparam T measurement type
     * @tparam SIZE buffer size
     * @note measurements at boundary is either interpolated or extrapolated
     * @param[in] start the left boundary of timestamp
     * @param[in] end the right boundary of timestamp
     * @param[in] buffer the circular buffer of the measurements
     * @param[out] measurements the measurements which are between these timestamps
     * @return bool_t it returns false when fails to find such measurements
     */
    template <typename T, std::size_t SIZE>
    bool_t getAlignedMeasurementsBetweenT(const Timestamp& start, const Timestamp& end,
                                          const OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >& buffer,
                                          std::vector<T>&                                        measurements) const;

    /**
     * @brief define mutex for multi-thread support
     *
     */
    std::mutex ground_truth_buffer_mutex_;
    std::mutex imu_buffer_mutex_;
    std::mutex odometry_buffer_mutex_;
    std::mutex position_buffer_mutex_;
    std::mutex road_frame_buffer_mutex_;
    std::mutex chassis_state_buffer_mutex_;
    std::mutex stamped_route_info_buffer_mutex_;
    std::mutex image_buffer_mutex_;
    std::mutex gnss_pvt_mutex_;

    /**
     * @brief internal data declaration
     *
     */
    OdometryBufferType         ground_truth_buffer_;
    ImuBufferType              imu_buffer_;
    OdometryBufferType         odometry_buffer_;
    PositionBufferType         position_buffer_;
    RoadFrameBufferType        road_frame_buffer_;
    ChassisStateBufferType     chassis_state_buffer_;
    StampedRouteInfoBufferType stamped_route_info_buffer_;
    ImageBufferType            image_buffer_;
    GnssPvtBufferType          gnss_pvt_buffer_;

};  // class MeasurementsManagerBase

// partial specialization
template <>
ImuType MeasurementsManagerBase::interpolateT<ImuType>(const ImuType& left, const ImuType& right,
                                                       const Timestamp& stamp);

template <>
OdometryType MeasurementsManagerBase::interpolateT<OdometryType>(const OdometryType& left, const OdometryType& right,
                                                                 const Timestamp& stamp);

template <>
ChassisState MeasurementsManagerBase::interpolateT<ChassisState>(const ChassisState& left, const ChassisState& right,
                                                                 const Timestamp& stamp);

template <>
ImuType MeasurementsManagerBase::extrapolateT<ImuType>(const ImuType& left, const ImuType& right,
                                                       const Timestamp& stamp);

template <>
OdometryType MeasurementsManagerBase::extrapolateT<OdometryType>(const OdometryType& left, const OdometryType& right,
                                                                 const Timestamp& stamp);

template <>
ChassisState MeasurementsManagerBase::extrapolateT<ChassisState>(const ChassisState& left, const ChassisState& right,
                                                                 const Timestamp& stamp);
/**
 * @}
 */

}  // namespace localization
}  // namespace holo

#include <holo/localization/common/impl/measurements_manager_base.hpp>

#endif  // HOLO_LOCALIZATION_COMMON_MEASUREMENTS_MANAGER_BASE_H_
