/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file cloud_path_info.h
 * @brief This header file defines cloud path info
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021-09-27
 */

#ifndef HOLO_PARKING_BASE_SYSTEM_CLOUD_PATH_INFO_H_
#define HOLO_PARKING_BASE_SYSTEM_CLOUD_PATH_INFO_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace system
{
/**
 * @brief This class defines cloud path info
 */
class CloudPathInfo
{
public:
    struct PathInfo
    {
        uint8_t     path_num;
        uint8_t     path_type;
        uint8_t     lot_type;
        uint8_t     path_state;
        uint8_t     path_learning_rate;
        uint8_t     path_source;
        uint16_t    path_distance;
        float64_t   longitude;
        float64_t   latitude;
        std::string start_image_address;
        std::string end_image_address;
        std::string route_name;
    };

    struct PathInfoList
    {
        PathInfo path_info[10];
    };

    /**
     * @brief default constructor
     */
    CloudPathInfo() noexcept : timestamp_(), path_info_list_()
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

    /* path_num */
    uint8_t GetPathNum(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_num;
    }

    void SetPathNum(uint8_t const path_num, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_num = path_num;
    }

    /* path_type */
    uint8_t GetPathType(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_type;
    }

    void SetPathType(uint8_t const path_type, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_type = path_type;
    }

    /* lot_type */
    uint8_t GetLotType(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].lot_type;
    }

    void SetLotType(uint8_t const lot_type, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].lot_type = lot_type;
    }

    /* path_state */
    uint8_t GetPathState(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_state;
    }

    void SetPathState(uint8_t const path_state, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_state = path_state;
    }

    /* path_learning_rate */
    uint8_t GetPathLearningRate(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_learning_rate;
    }

    void SetPathLearningRate(uint8_t const path_learning_rate, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_learning_rate = path_learning_rate;
    }

    /* path_source */
    uint8_t GetPathSource(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_source;
    }

    void SetPathSource(uint8_t const path_source, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_source = path_source;
    }

    /* path_distance */
    uint16_t GetPathDistance(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].path_distance;
    }

    void SetPathDistance(uint16_t const path_distance, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].path_distance = path_distance;
    }

    /* longitude */
    float64_t GetLongitude(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].longitude;
    }

    void SetLongitude(float64_t const longitude, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].longitude = longitude;
    }

    /* latitude */
    float64_t GetLatitude(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].latitude;
    }

    void SetLatitude(float64_t const latitude, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].latitude = latitude;
    }

    /* start_image_address */
    std::string GetStartImageAddress(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].start_image_address;
    }

    void SetStartImageAddress(std::string const start_image_address, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].start_image_address = start_image_address;
    }

    /* end_image_address */
    std::string GetEndImageAddress(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].end_image_address;
    }

    void SetEndImageAddress(std::string const end_image_address, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].end_image_address = end_image_address;
    }

    /* route_name */
    std::string GetRouteName(uint8_t const array_number) const noexcept
    {
        return path_info_list_.path_info[array_number].route_name;
    }

    void SetRouteName(std::string const route_name, uint8_t const array_number)
    {
        path_info_list_.path_info[array_number].route_name = route_name;
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
        size_t aligned_size = timestamp_.GetSerializedSize<ALIGN>();
        for (size_t i = 0U; i < 10U; i++)
        {
            aligned_size += holo::serialization::SerializedSize<ALIGN>(path_info_list_.path_info[i].path_num);
            aligned_size += holo::serialization::SerializedSize<ALIGN>(path_info_list_.path_info[i].path_type);
            aligned_size += holo::serialization::SerializedSize<ALIGN>(path_info_list_.path_info[i].lot_type);
            aligned_size += holo::serialization::SerializedSize<ALIGN>(path_info_list_.path_info[i].path_state);
            aligned_size += holo::serialization::SerializedSize<ALIGN>(path_info_list_.path_info[i].path_learning_rate);
            aligned_size += holo::serialization::SerializedSize<ALIGN>(path_info_list_.path_info[i].path_source);
            aligned_size += holo::serialization::SerializedSize<ALIGN>(path_info_list_.path_info[i].path_distance);
            aligned_size += holo::serialization::SerializedSize<ALIGN>(path_info_list_.path_info[i].longitude);
            aligned_size += holo::serialization::SerializedSize<ALIGN>(path_info_list_.path_info[i].latitude);
            aligned_size +=
                holo::serialization::SerializedSize<ALIGN>(path_info_list_.path_info[i].start_image_address.length());
            aligned_size +=
                holo::serialization::SerializedSize<ALIGN>(path_info_list_.path_info[i].end_image_address.length());
            aligned_size +=
                holo::serialization::SerializedSize<ALIGN>(path_info_list_.path_info[i].route_name.length());
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
        /* serialize data */
        serializer << timestamp_;
        for (size_t i = 0U; i < 10U; i++)
        {
            serializer << path_info_list_.path_info[i].path_num;
            serializer << path_info_list_.path_info[i].path_type;
            serializer << path_info_list_.path_info[i].lot_type;
            serializer << path_info_list_.path_info[i].path_state;
            serializer << path_info_list_.path_info[i].path_learning_rate;
            serializer << path_info_list_.path_info[i].path_source;
            serializer << path_info_list_.path_info[i].path_distance;
            serializer << path_info_list_.path_info[i].longitude;
            serializer << path_info_list_.path_info[i].latitude;
            serializer << path_info_list_.path_info[i].start_image_address;
            serializer << path_info_list_.path_info[i].end_image_address;
            serializer << path_info_list_.path_info[i].route_name;
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
        /* deserialize data */
        deserializer >> timestamp_;
        for (size_t i = 0U; i < 10U; i++)
        {
            deserializer >> path_info_list_.path_info[i].path_num;
            deserializer >> path_info_list_.path_info[i].path_type;
            deserializer >> path_info_list_.path_info[i].lot_type;
            deserializer >> path_info_list_.path_info[i].path_state;
            deserializer >> path_info_list_.path_info[i].path_learning_rate;
            deserializer >> path_info_list_.path_info[i].path_source;
            deserializer >> path_info_list_.path_info[i].path_distance;
            deserializer >> path_info_list_.path_info[i].longitude;
            deserializer >> path_info_list_.path_info[i].latitude;
            deserializer >> path_info_list_.path_info[i].start_image_address;
            deserializer >> path_info_list_.path_info[i].end_image_address;
            deserializer >> path_info_list_.path_info[i].route_name;
        }
        deserializer >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp
    PathInfoList            path_info_list_;
};

}  // namespace system
}  // namespace parking
}  // namespace holo

#endif
