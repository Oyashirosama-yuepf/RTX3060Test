/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_lidar_structure.h
 * @brief This header file define the structures of mdc610 structure
 * @author wujie@holomatic.com
 * @date 2022-03-09
 */

#ifndef _HOLO_SENSORS_BASE_LIDAR_MDC610_STRUCTURE_H
#define _HOLO_SENSORS_BASE_LIDAR_MDC610_STRUCTURE_H

#include <adsf/lidar_receive_base.h>
#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <functional>

namespace holo
{
namespace sensors
{
namespace mdc610
{
class Mdc610Scan
{
public:
    Mdc610Scan(uint32_t coord = 0, std::shared_ptr<const Adsfi::LidarFrame<Adsfi::PointXYZIRT>> frame = nullptr)
      : coord_(coord), timestamp_(0, 0), seq_(0), is_frame_mem_(false), point_cloud_(nullptr)
    {
        if (frame != nullptr)
        {
            timestamp_    = holo::common::Timestamp(frame->timestamp.sec, frame->timestamp.nsec);
            seq_          = frame->seq;
            is_frame_mem_ = true;
            point_cloud_  = const_cast<std::vector<Adsfi::PointXYZIRT>*>(&frame->pointCloud);
        }
    }

    ~Mdc610Scan()
    {
        if (!is_frame_mem_ && point_cloud_ != nullptr)
        {
            delete point_cloud_;
            point_cloud_ = nullptr;
        }
    }

    uint32_t GetCoordinate() const noexcept
    {
        return coord_;
    }

    const holo::common::Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    uint32_t GetSeq() const noexcept
    {
        return seq_;
    }

    size_t Size() const noexcept
    {
        if (point_cloud_ == nullptr)
        {
            LOG(ERROR) << "point_cloud_ is nullptr!";
            return -1;
        }
        return point_cloud_->size();
    }

    const Adsfi::PointXYZIRT& operator[](size_t index) const
    {
        if (point_cloud_ == nullptr)
        {
            std::string error = "failed point_cloud_ addr";
            throw std::runtime_error(error);
        }
        return point_cloud_->at(index);
    }

    template <typename S>
    bool_t Serialize(S& serializer) const
    {
        try
        {
            if (point_cloud_ == nullptr)
            {
                LOG(ERROR) << "point_cloud_ is nullptr!";
                return false;
            }
            uint32_t point_size = point_cloud_->size();
            serializer << coord_ << timestamp_ << seq_ << point_size << holo::serialization::align;

            for (uint32_t i = 0; i < point_size; i++)
            {
                serializer.Write(&(*point_cloud_)[i], sizeof(Adsfi::PointXYZIRT));
            }
        }
        catch (holo::serialization::SerializationBufferOverflowException& e)
        {
            LOG(ERROR) << "serialization overflow: " << e.what();
            return false;
        }
        catch (...)
        {
            LOG(ERROR) << "serialization unexpected exception";
            return false;
        }
        return true;
    }

    template <typename D>
    bool_t Deserialize(D& deserializer)
    {
        try
        {
            uint32_t point_size;
            deserializer >> coord_ >> timestamp_ >> seq_ >> point_size >> holo::serialization::align;

            point_cloud_ = new std::vector<Adsfi::PointXYZIRT>;
            point_cloud_->reserve(point_size);
            point_cloud_->resize(point_size);
            for (uint32_t i = 0; i < point_size; i++)
            {
                deserializer.Read(&(*point_cloud_)[i], sizeof(Adsfi::PointXYZIRT));
            }
        }
        catch (holo::serialization::DeserializationBufferUnderflowException& e)
        {
            LOG(ERROR) << "deserialization overflow: " << e.what();
            return false;
        }
        catch (...)
        {
            LOG(ERROR) << "deserialization unexpected exception";
            return false;
        }
        return true;
    }

private:
    uint32_t                         coord_;
    holo::common::Timestamp          timestamp_;
    uint32_t                         seq_;
    bool_t                           is_frame_mem_;
    std::vector<Adsfi::PointXYZIRT>* point_cloud_;
};

}  // namespace mdc610
}  // namespace sensors
}  // namespace holo

#endif
