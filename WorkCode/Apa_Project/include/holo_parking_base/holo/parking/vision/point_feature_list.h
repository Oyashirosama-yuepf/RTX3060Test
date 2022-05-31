/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_feature_list.h
 * @brief This header file defines PointFeaturePtrListT.
 * @author lifeng(lifeng@holomaitc.com)
 * @date 2021-01-07
 */

#ifndef HOLO_PARKING_VISION_POINT_FEATURE_PTR_LIST_H_
#define HOLO_PARKING_VISION_POINT_FEATURE_PTR_LIST_H_

#include <vector>

#include <holo/common/sensor_id.h>
#include <holo/common/timestamp.h>
#include <holo/parking/vision/point_feature.h>

namespace holo
{
namespace parking
{
namespace vision
{
/**
 * @addtogroup parking
 *
 * @{
 */

/**
 * @brief This class holds list of point features and a message header.
 *
 * @tparam T Obstacle type
 * @todo (lifeng@holomatic.com 2021-01-07) we should limite the max size of this list.
 */
template <typename T>
class PointFeaturePtrListT
{
public:
    using Timestamp               = holo::common::Timestamp;
    using SensorId                = holo::common::SensorId;
    using PointFeaturePtrListType = std::vector<std::shared_ptr<T>>;

    /**
     * @brief Default constructor
     */
    PointFeaturePtrListT()
    {
    }

    /**
     * @brief Constructor with params
     *
     * @param timestamp time stamp
     * @param coord coordinate
     * @param sensor_id from which sensor
     * @param size number of obstacles in array
     * @param perception_ability perception ability
     * @param obstacle_list obstacles ptr
     */
    PointFeaturePtrListT(const Timestamp& timestamp, const SensorId& sensor_id,
                         const PointFeaturePtrListType& point_feature_list)
      : timestamp_(timestamp)
      , sensor_id_(sensor_id)
      , size_(point_feature_list.size())
      , point_feature_list_(point_feature_list)
    {
    }

    /**
     * @brief Get timestamp
     *
     * @return timestamp of obstacle list
     */
    const Timestamp& GetTimestamp() const
    {
        return timestamp_;
    }

    /**
     * @brief Set timestamp
     *
     * @param timestamp timestmap of obstacle list
     */
    void SetTimestamp(const Timestamp& timestamp)
    {
        this->timestamp_ = timestamp;
    }

    /**
     * @brief Get information of point feature from which sensor
     *
     * @return sensor id
     */
    const SensorId& GetSensorId() const
    {
        return sensor_id_;
    }

    /**
     * @brief Set sensor id
     *
     * @param sensor_id sensor id
     */
    void SetSensorId(const SensorId& sensor_id)
    {
        this->sensor_id_ = sensor_id;
    }

    /**
     * @brief Get size
     *
     * @param size point feature list size
     */
    uint32_t GetSize() const
    {
        return size_;
    }

    /**
     * @brief Set size
     *
     * @param size point feature list size
     */
    void SetSize(const uint32_t& size)
    {
        this->size_ = size;
    }

    /**
     * @brief Get obstacle ptr list
     *
     * @return obstacle ptr list
     */
    const PointFeaturePtrListType& GetPointFeatureList() const
    {
        return point_feature_list_;
    }

    /**
     * @brief Get obstacle ptr list non const reference
     *
     * @return obstacle ptr list
     */
    PointFeaturePtrListType& GetPointFeatureList()
    {
        return point_feature_list_;
    }

    /**
     * @brief Set obstacle ptr list
     *
     * @param obstacle_list obstacle ptr list
     */
    void SetPointFeatureList(const PointFeaturePtrListType& point_feature_list)
    {
        this->point_feature_list_ = point_feature_list;
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
        size_t aligned_size = timestamp_.template GetSerializedSize<ALIGN>() +
                              holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(sensor_id_), size_);
        for (size_t i = 0U; i < size_; ++i)
        {
            aligned_size += point_feature_list_[i]->template GetSerializedSize<ALIGN>();
        }
        return aligned_size;
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
        serializer << timestamp_ << static_cast<uint32_t>(sensor_id_) << size_;
        for (uint32_t i = 0; i < size_; i++)
        {
            serializer << *(point_feature_list_[i]);
        }
        serializer << holo::serialization::align;
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
        uint32_t sensor_id = 0U;
        deserializer >> timestamp_ >> sensor_id >> size_;
        point_feature_list_.resize(size_);
        for (uint32_t i = 0U; i < size_; ++i)
        {
            std::shared_ptr<T> ptr_point_feature = std::make_shared<T>();
            deserializer >> *(ptr_point_feature);
            point_feature_list_[i] = ptr_point_feature;
        }
        deserializer >> holo::serialization::align;
        sensor_id_ = static_cast<SensorId>(sensor_id);
    }

private:
    /**
     * @brief timestamp
     */
    Timestamp timestamp_;

    /**
     * @brief sensor id indicate which sensor this message comes from
     */
    SensorId sensor_id_;

    /**
     * @brief the size of point feature list
     */
    uint32_t size_;

    /**
     * @brief point feature list
     */
    PointFeaturePtrListType point_feature_list_;
};  // class PointFeaturePtrListT

/**
 * @brief Define a list of point feature whose dimention of descriptor is  and with accuracy of float32_t
 */
using PointFeaturePtrListf = PointFeaturePtrListT<PointFeaturef>;

/**
 * @brief Define a list of point feature whose dimention of descriptor is  and with accuracy of float64_t
 */
using PointFeaturePtrListd = PointFeaturePtrListT<PointFeatured>;

/**
 * @}
 */
}  // namespace vision
}  // namespace parking
}  // namespace holo

#endif  // !HOLO_PARKING_VISION_POINT_FEATURE_PTR_LIST_H_
