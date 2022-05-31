/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file hpa_path.h
 * @brief This header file defines hpa_path
 * @author fanhaowei(fanhaowei@holomaitc.com)
 * @date 2022-04-02
 */

#ifndef HOLO_PARKING_BASE_PLANNING_PATH_H_
#define HOLO_PARKING_BASE_PLANNING_PATH_H_

#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/parking/planning/pathattribute.h>
#include <holo/parking/planning/pathpoint.h>

namespace holo
{
namespace parking
{
namespace planning
{
/**
 * @brief This class defines hpa_path
 */
using PathPointType = holo::container::Vector<holo::parking::planning::PathPoint, 40>;
class Path
{
public:
    /**
     * @brief default constructor
     */
    // using PathPointType = holo::container::Vector<holo::parking::planning::PathPoint>;
    Path() noexcept : path_attribute_(), path_point_()
    {
    }

    /* timestamp_ */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    void SetTimestamp(Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    /*  pathattribute  */
    HpaPathAttribute GetPathAttribute() const noexcept
    {
        return path_attribute_;
    }
    void SetPathAttribute(HpaPathAttribute const path_attribute)
    {
        path_attribute_ = path_attribute;
    }

    /*  pathpoint  */
    const PathPointType& GetPathPoint() const noexcept
    {
        return path_point_;
    }
    void SetPathPoint(const PathPointType&  path_point) noexcept
    {
        path_point_ = path_point;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(path_attribute_, path_point_);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        /* serialize data */
        serializer << timestamp_ << path_attribute_ << path_point_ << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        /* deserialize data */
        deserializer >> timestamp_ >> path_attribute_ >> path_point_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    ///  the path attribute is valid when path id not 0
    holo::parking::planning::HpaPathAttribute path_attribute_;  ///< path_gear, path_id, path_type, pathsize....
    PathPointType                             path_point_;      ///< vmax, curv, x, y, yaw, lamp
};

}  // namespace planning
}  // namespace parking
}  // namespace holo

#endif
