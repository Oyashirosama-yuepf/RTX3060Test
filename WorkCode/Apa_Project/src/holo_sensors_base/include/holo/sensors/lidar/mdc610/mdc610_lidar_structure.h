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

#include <holo/common/timestamp.h>
#include <holo/log/hololog.h>
#include <functional>

namespace holo
{
namespace sensors
{
namespace mdc610
{
namespace huawei
{
template <typename DataType>
struct Point3D
{
    static_assert(std::is_pod<DataType>::value, "DataType must be a POD type.");
    DataType x{};
    DataType y{};
    DataType z{};
    Point3D() = default;
    Point3D(const DataType& valueX, const DataType& valueY, const DataType& valueZ) : x(valueX), y(valueY), z(valueZ)
    {
    }
    Point3D operator+(const Point3D& rightValue) const
    {
        return Point3D(x + rightValue.x, y + rightValue.y, z + rightValue.z);
    }
    Point3D operator-(const Point3D& rightValue) const
    {
        return Point3D(x - rightValue.x, y - rightValue.y, z - rightValue.z);
    }
};
using Point3i = Point3D<int32_t>;
using Point3f = Point3D<float32_t>;
using Point3d = Point3D<float64_t>;

struct PointXYZIRT : public Point3D<float32_t>
{
    PointXYZIRT() : Point3D<float32_t>(), intensity(0U), ring(0U), latency(0U)
    {
    }
    PointXYZIRT(float32_t x, float32_t y, float32_t z, uint8_t i, uint16_t r, uint32_t t)
      : Point3D<float32_t>(x, y, z), intensity(i), ring(r), latency(t)
    {
    }
    uint16_t intensity;
    uint16_t ring;
    uint32_t latency;  // Delay from the first scan point of the current frame
};

template <typename T>
struct LidarFrame
{
    struct HafTime
    {
        HafTime(const uint32_t s = 0U, const uint32_t ns = 0U) : sec(s), nsec(ns)
        {
        }

        HafTime()  = default;
        ~HafTime() = default;

        uint32_t sec;
        uint32_t nsec;
    };

    HafTime        timestamp;
    uint32_t       seq;
    std::string    frameID;
    std::vector<T> pointCloud;
};
}  // namespace huawei

class Mdc610Scan
{
public:
    Mdc610Scan(uint32_t coord = 0, std::shared_ptr<const huawei::LidarFrame<huawei::PointXYZIRT>> frame = nullptr)
      : coord_(coord), timestamp_(0, 0), seq_(0), point_cloud_(nullptr), frame_(frame)
    {
        if (frame != nullptr)
        {
            timestamp_   = holo::common::Timestamp(frame_->timestamp.sec, frame_->timestamp.nsec);
            seq_         = frame_->seq;
            point_cloud_ = const_cast<std::vector<huawei::PointXYZIRT>*>(&frame_->pointCloud);
        }
        else
        {
            point_cloud_ = new std::vector<huawei::PointXYZIRT>;
        }
    }

    ~Mdc610Scan()
    {
        if (frame_ == nullptr && point_cloud_ != nullptr)
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

    void SetCoordinate(uint32_t coord)
    {
        coord_ = coord;
    }

    void SetTimestamp(holo::common::Timestamp& timestamp)
    {
        timestamp_ = timestamp;
    }

    void SetSeq(uint32_t seq)
    {
        seq_ = seq;
    }

    const std::vector<huawei::PointXYZIRT>* GetPointCloud()
    {
        return point_cloud_;
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

    const huawei::PointXYZIRT& operator[](size_t index) const
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
                serializer.Write(&(*point_cloud_)[i], sizeof(huawei::PointXYZIRT));
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

            point_cloud_->reserve(point_size);
            point_cloud_->resize(point_size);
            for (uint32_t i = 0; i < point_size; i++)
            {
                deserializer.Read(&(*point_cloud_)[i], sizeof(huawei::PointXYZIRT));
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
    uint32_t                                                       coord_;
    holo::common::Timestamp                                        timestamp_;
    uint32_t                                                       seq_;
    std::vector<huawei::PointXYZIRT>*                              point_cloud_;
    std::shared_ptr<const huawei::LidarFrame<huawei::PointXYZIRT>> frame_;
};

}  // namespace mdc610
}  // namespace sensors
}  // namespace holo

#endif
