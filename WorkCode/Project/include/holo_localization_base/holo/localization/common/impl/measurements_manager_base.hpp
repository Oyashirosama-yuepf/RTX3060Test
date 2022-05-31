/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file measurements_manager_base.hpp
 * @brief define measurements_manager class
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#ifndef HOLO_LOCALIZATION_COMMON_MEASUREMENT_MANAGER_BASE_HPP_
#define HOLO_LOCALIZATION_COMMON_MEASUREMENT_MANAGER_BASE_HPP_

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t SIZE>
bool_t MeasurementsManagerBase::insertMeasurementT(const T& m, OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >& buffer)
{
    const std::pair<typename OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >::iterator, bool_t> result =
        buffer.insert(m);
    return result.second;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t SIZE>
bool_t MeasurementsManagerBase::getLatestMeasurementT(const OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >& buffer,
                                                      T&                                                     m) const
{
    if (buffer.size() == 0u)
    {
        return false;
    }
    m = buffer.back();
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t SIZE>
bool_t MeasurementsManagerBase::getNearestMeasurementT(const Timestamp&                                       t,
                                                       const OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >& buffer,
                                                       T&                                                     m) const
{
    if (buffer.empty())
    {
        return false;
    }

    /// if the time is not latter than all of elements, get the front of buffer
    if (t <= buffer.front().GetTimestamp())
    {
        m = buffer.front();
        return true;
    }

    /// if the time is not earlier than all of elements, get the back of buffer
    if (t >= buffer.back().GetTimestamp())
    {
        m = buffer.back();
        return true;
    }

    T left, right;

    /// get the element which is the first greater than t
    auto r = std::upper_bound(buffer.begin(), buffer.end(), t, StampedTimeCompareT<T>());

    /// get the left and right neighbors of t
    left  = *(r - 1);
    right = *r;

    /// get the element from the nearest one from left and right
    m = std::fabs((t - left.GetTimestamp()).ToSec()) < std::fabs((right.GetTimestamp() - t).ToSec()) ? left : right;

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t SIZE>
bool_t MeasurementsManagerBase::getCurrentMeasurementT(const Timestamp&                                       t,
                                                       const OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >& buffer,
                                                       T&                                                     m) const
{
    /// case 1 the measurements is empty
    if (buffer.size() < 1u)
    {
        LOG(WARNING) << "empty buffer";
        return false;
    }

    /// case 2 query time is earlier than all the measurements
    ///   |b-------e
    ///   |
    ///   |
    /// t
    if (t < buffer.front().GetTimestamp())
    {
        if (buffer.size() < 2u)
        {
            LOG(WARNING)
                << "query time is earlier than all the measurements and the extrapolation condition is not satisfied";
            return false;
        }

        m = extrapolateT<T>(*buffer.begin(), *(buffer.begin() + 1), t);
        return true;
    }

    /// case 3 query time is later than all the measurements
    /// b-------e|
    ///          |
    ///          |
    ///            t
    if (t > buffer.back().GetTimestamp())
    {
        if (buffer.size() < 2u)
        {
            LOG(WARNING)
                << "query time is later than all the measurements and the extrapolation condition is not satisfied";
            return false;
        }

        m = extrapolateT<T>(*(buffer.end() - 2), *(buffer.end() - 1), t);
        return true;
    }

    /// case 4 query time is equal to the front of measurements
    /// |b-------e|
    /// |         |
    /// |         |
    /// t
    if (t == buffer.front().GetTimestamp())
    {
        m = buffer.front();
        return true;
    }

    /// case 5 query time is equal to the back of measurements
    /// |b-------e|
    /// |         |
    /// |         |
    ///           t
    if (t == buffer.back().GetTimestamp())
    {
        m = buffer.back();
        return true;
    }

    /// case 6 query time is inside the measurements
    /// |b-------e|
    /// |         |
    /// |         |
    ///      t
    /* find upper boundary */
    typename OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >::const_iterator upper_position =
        std::upper_bound(buffer.begin(), buffer.end(), t, StampedTimeCompareT<T>());

    if (upper_position == buffer.end())
    {
        return false;
    }

    const T left  = *(upper_position - 1);
    const T right = *upper_position;
    m             = interpolateT<T>(left, right, t);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t SIZE>
bool_t MeasurementsManagerBase::getMeasurementsBetweenT(const Timestamp& start, const Timestamp& end,
                                                        const OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >& buffer,
                                                        std::vector<T>& measurements) const
{
    if (buffer.size() <= 0u)
    {
        return false;
    }

    if (end <= start)
    {
        return false;
    }

    if (start > buffer.back().GetTimestamp())
    {
        return false;
    }

    if (end < buffer.front().GetTimestamp())
    {
        return false;
    }

    /* find left and right boundary */
    typename OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >::const_iterator left =
        std::lower_bound(buffer.begin(), buffer.end(), start, StampedTimeCompareT<T>());
    typename OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >::const_iterator right =
        std::upper_bound(buffer.begin(), buffer.end(), end, StampedTimeCompareT<T>());

    /* insert to output measurements */
    measurements.clear();
    (void)std::copy(left, right, std::back_inserter(measurements));

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t SIZE>
bool_t
MeasurementsManagerBase::getAlignedMeasurementsBetweenT(const Timestamp& start, const Timestamp& end,
                                                        const OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >& buffer,
                                                        std::vector<T>& measurements) const
{
    measurements.clear();
    if (buffer.size() <= 0u)
    {
        LOG(WARNING) << "empty buffer";
        return false;
    }
    if (end <= start)
    {
        LOG(WARNING) << "first timestamp is not smaller than last timestamp";
        return false;
    }

    /* compare with start time */
    typename OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >::const_iterator left =
        std::lower_bound(buffer.begin(), buffer.end(), start, StampedTimeCompareT<T>());

    /// case 1
    ///         |s-------e
    ///         |
    ///         |
    /// [x x x x]
    if (left == buffer.end())
    {
        std::string s = "all of measurements are earlier than start time.";
        LOG(ERROR) << s;
        return false;
    }

    /// case 2: the iterator is equal to the start time
    ///        s-------e
    ///        |
    ///        |
    /// [x x x x]
    if (left->GetTimestamp() == start)
    {
        /// do nothing
    }
    else if (left != buffer.begin())
    {
        /// case 3 the iterator isn't equal to the start time, and it isn't the
        /// first measurement
        ///       s-------e
        ///        |
        ///       *|
        /// [x x x x]
        DLOG(INFO) << "Interpolate measurement to the start time";
        measurements.emplace_back(interpolateT<T>(*(left - 1), *left, start));
    }
    else if ((left + 1) != buffer.end())
    {
        /// case 4 the iterator isn't equal to the start time, and it is the
        /// first measurement
        /// s-------e
        ///  |
        /// *|
        /// [x x x x]
        DLOG(INFO) << "Extrapolate measurement to the start time";
        measurements.emplace_back(extrapolateT<T>(*left, *(left + 1), start));
    }
    else
    {
        /// case 5 only one measurement, could not be extrapolated
        return false;
    }

    /// first greater than end time
    /// s-------e
    ///          |
    ///          |
    ///     [x x x x]
    typename OrderedBuffer<T, SIZE, StampedTimeCompareT<T> >::const_iterator right =
        std::upper_bound(buffer.begin(), buffer.end(), end, StampedTimeCompareT<T>());

    /// case 6 the previous of iterator is equal to the end time
    /// s-------e
    ///          |
    ///          |
    ///         [x x x x]
    if (right == buffer.begin())
    {
        std::string s = "all of measurements are later than end time";
        LOG(ERROR) << s;
        measurements.clear();
        return false;
    }

    /// copy the measurement between left and right to the measurements vector
    (void)std::copy(left, right, std::back_inserter(measurements));

    /// right boundary
    /// case 7 the previous of iterator is equal to the end time
    /// s-------e
    ///         ^ |
    ///         ^ |
    ///    [x x x x]
    if ((right - 1)->GetTimestamp() == end)
    {
        /// do nothing
    }
    else if (right != buffer.end())
    {
        /// case 8 the previous of iterator isn't equal to the end time, and
        /// it isn't the last measurement
        /// s-------e
        ///          |
        ///         *|
        ///   [x x x x]
        DLOG(INFO) << "Interpolate measurement to the end time";
        measurements.emplace_back(interpolateT<T>(*(right - 1), *right, end));
    }
    else if ((right - 1) != buffer.begin())
    {
        /// case 9 the previous of iterator isn't equal to the end time, and
        /// it is the last measurement
        ///   s-------e
        ///         |
        ///         | *
        /// [x x x x]
        DLOG(INFO) << "Extrapolate measurement to the end time";
        measurements.emplace_back(extrapolateT<T>(*(right - 2), *(right - 1), end));
    }
    else
    {
        /// case 10 only one measurement, could not be extrapolated
        return false;
    }

    return true;
}

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_COMMON_MEASUREMENTS_MANAGER_BASE_HPP_
