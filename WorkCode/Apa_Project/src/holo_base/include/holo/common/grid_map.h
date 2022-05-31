/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file grid_map.h
 * @brief This header file defines GridMap class
 * @author zhouhuishuang(zhouhuishuang@holomaitc.com)
 * @date "2022-02-22"
 */

#ifndef HOLO_COMMON_GRID_MAP_H_
#define HOLO_COMMON_GRID_MAP_H_

#include <holo/common/classification.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/geometry/point2.h>
#include <holo/obstacle/obstacle_base.h>

namespace holo
{
namespace common
{
/**
 * @brief This class is used to describe a grid map
 *
 * @tparam Cell the grid map cell type
 * @tparam W grid map width size
 * @tparam H grid map height size
 */
template <typename Cell, size_t W, size_t H>
class GridMap
{
public:
    static size_t const WIDTH_VALUE  = W;
    static size_t const HEIGHT_VALUE = H;

    using CellType      = Cell;
    using Point2Type    = holo::geometry::Point2f;
    using TimestampType = holo::common::Timestamp;

    /**
     * @brief default constructor
     * @note resolution default value is 0.1f
     */
    GridMap() : timestamp_{0U, 0U}, resolution_{0.1f}, origin_x_{0U}, origin_y_{0U}, cells_{W * H}
    {
        initialize();
    }

    /**
     * @brief Constructor
     *
     * @param timestamp  timestamp
     * @param resolution  the length of each grid map cell
     * @param origin_x
     * @param origin_y
     */
    GridMap(TimestampType timestamp, float32_t resolution, uint32_t origin_x, uint32_t origin_y)
      : timestamp_{timestamp}, resolution_{resolution}, cells_{}
    {
        SetOrigin(origin_x, origin_y);
        initialize();
    }

    /**
     * @brief Get const reference of Timestamp
     *
     * @return const reference of Timestamp
     */
    TimestampType const& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set Timestamp
     *
     * @param timestamp
     */
    void SetTimestamp(TimestampType const& timestamp)
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Get resolution value
     *
     * @return resolution
     */
    float32_t GetResolution() const noexcept
    {
        return resolution_;
    }

    /**
     * @brief Set resolution value.
     *
     * @param resolution resolution value.
     */
    void SetResolution(float32_t const resolution) noexcept
    {
        resolution_ = resolution;
        initialize();
    }

    /**
     * @brief Get origin x
     *
     * @return origin x
     */
    uint32_t GetOriginX() const noexcept
    {
        return origin_x_;
    }

    /**
     * @brief Get origin y
     *
     * @return origin y
     */
    uint32_t GetOriginY() const noexcept
    {
        return origin_y_;
    }

    /**
     * @brief Set origin value.
     *
     * @param origin_x origin x value.
     * @param origin_y origin y value.
     * @throw holo::exception::OutOfRangeException when origin_x >= HEIGHT_VALUE or origin_y >= WIDTH_VALUE
     */
    void SetOrigin(uint32_t const origin_x, uint32_t const origin_y)
    {
        if (origin_x >= HEIGHT_VALUE || origin_y >= WIDTH_VALUE)
        {
            throw holo::exception::OutOfRangeException("");
        }
        origin_x_ = origin_x;
        origin_y_ = origin_y;
        initialize();
    }

    /**
     * @brief access grid map cell without bounds check.
     *
     * @param x query x index cell of the grid map
     * @param y query y index cell of the grid map
     *
     * @return const reference to CellType object
     * @throw std::out_of_range when query index out of range
     */
    CellType const& operator()(uint32_t const x, uint32_t const y) const
    {
        uint64_t index = y + x * WIDTH_VALUE;
        return cells_[index];
    }

    /**
     * @brief access grid map cell without bounds check.
     *
     * @param x query x index cell of the grid map
     * @param y query y index cell of the grid map
     *
     * @return reference to CellType object
     * @throw std::out_of_range when query index out of range
     */
    CellType& operator()(uint32_t const x, uint32_t const y)
    {
        uint64_t index = y + x * WIDTH_VALUE;
        return cells_[index];
    }

    /**
     * @brief access grid map cell with bounds check.
     *
     * @param x query x index cell of the grid map
     * @param y query y index cell of the grid map
     *
     * @return const reference to CellType object
     * @throw holo::exception::OutOfRangeException if x >= HEIGHT_VALUE or y >= WIDTH_VALUE
     */
    CellType const& At(uint32_t const x, uint32_t const y) const
    {
        if (x >= HEIGHT_VALUE || y >= WIDTH_VALUE)
        {
            throw holo::exception::OutOfRangeException("");
        }
        uint64_t index = y + x * WIDTH_VALUE;
        return cells_[index];
    }

    /**
     * @brief access grid map cell with bounds check.
     *
     * @param x query x index cell of the grid map
     * @param y query y index cell of the grid map
     *
     * @return reference to CellType object
     * @throw holo::exception::OutOfRangeException if x >= HEIGHT_VALUE or y >= WIDTH_VALUE
     */
    CellType& At(uint32_t const x, uint32_t const y)
    {
        if (x >= HEIGHT_VALUE || y >= WIDTH_VALUE)
        {
            throw holo::exception::OutOfRangeException("");
        }
        uint64_t index = y + x * WIDTH_VALUE;
        return cells_.at(index);
    }

    /**
     * @brief access grid map cell in vehicle coordinate system
     *
     * @param coor coordinate value
     *
     * @return const reference to CellType object
     * @throw holo::exception::OutOfRangeException when query index out of range
     */
    CellType const& GetCell(Point2Type const& coor) const
    {
        int32_t x_index = origin_x_ + floor(coor.GetX() / resolution_);
        int32_t y_index = origin_y_ + floor(coor.GetY() / resolution_);
        if (x_index < 0 || y_index < 0)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return At(static_cast<uint32_t>(x_index), static_cast<uint32_t>(y_index));
    }

    /**
     * @brief access grid map cell in vehicle coordinate
     *
     * @param coor coordinate value
     *
     * @return reference to CellType object
     * @throw holo::exception::OutOfRangeException when query index out of range
     */
    CellType& GetCell(Point2Type const& coor)
    {
        int32_t x_index = origin_x_ + floor(coor.GetX() / resolution_);
        int32_t y_index = origin_y_ + floor(coor.GetY() / resolution_);
        if (x_index < 0 || y_index < 0)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return At(static_cast<uint32_t>(x_index), static_cast<uint32_t>(y_index));
    }

    /**
     * @brief access grid map cell index pair in vehicle coordinate
     *
     * @param coor coordinate value
     *
     * @return grid map cell index pair
     * @throw holo::exception::OutOfRangeException when query cell out of range
     */
    std::pair<uint32_t, uint32_t> const CellIndex(Point2Type const& coor) const
    {
        int32_t x_index = origin_x_ + floor(coor.GetX() / resolution_);
        int32_t y_index = origin_y_ + floor(coor.GetY() / resolution_);
        if (x_index < 0 || y_index < 0)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return {x_index, y_index};
    }

    /**
     * @brief access grid map cell index pair in vehicle coordinate
     *
     * @param coor coordinate value
     *
     * @return grid map cell index pair
     * @throw holo::exception::OutOfRangeException when query cell out of range
     */
    std::pair<uint32_t, uint32_t> CellIndex(Point2Type const& coor)
    {
        int32_t x_index = origin_x_ + floor(coor.GetX() / resolution_);
        int32_t y_index = origin_y_ + floor(coor.GetY() / resolution_);
        if (x_index < 0 || y_index < 0)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return {x_index, y_index};
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
               holo::serialization::SerializedSize<ALIGN>(resolution_, origin_x_, origin_y_) +
               cells_.template GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        timestamp_.Serialize(serializer);
        serializer << resolution_ << origin_x_ << origin_y_ << cells_;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        timestamp_.Deserialize(deserializer);
        deserializer >> resolution_ >> origin_x_ >> origin_y_ >> cells_;
    }

private:
    /**
     * @brief Initialize grid map
     */
    void initialize()
    {
        for (size_t x = 0U; x < HEIGHT_VALUE; ++x)
        {
            for (size_t y = 0U; y < WIDTH_VALUE; ++y)
            {
                operator()(x, y).Initialize(resolution_, {origin_x_, origin_y_}, {x, y});
            }
        }
    }

    TimestampType                            timestamp_;
    float32_t                                resolution_;
    uint32_t                                 origin_x_;
    uint32_t                                 origin_y_;
    holo::container::Vector<CellType, W * H> cells_;
};

/**
 * @brief This class is used to describe a grid map cell
 */
class GridMapCell
{
public:
    using ClassificationType = holo::common::Classification;
    using MotionStatusType   = holo::obstacle::MotionStatus;
    using Point2Type         = holo::geometry::Point2f;

    /**
     * @brief default constructor
     */
    GridMapCell()
      : center_{}
      , relative_velocity_{}
      , classification_{}
      , obstacle_id_{0U}
      , is_occupied_{false}
      , motion_status_{MotionStatusType::UNKNOWN}
    {
    }

    /**
     * @brief Initialize cell
     *
     * @param resolution  the length of cell
     * @param origin  origin value
     * @param index  index of cell in grid map
     */
    void Initialize(float32_t const resolution, std::pair<uint32_t, uint32_t> const& origin,
                    std::pair<uint32_t, uint32_t> const& index)
    {
        int32_t offset_x = index.first - origin.first;
        int32_t offset_y = index.second - origin.second;

        float32_t x_coor = static_cast<float32_t>((offset_x + 0.5) * resolution);
        float32_t y_coor = static_cast<float32_t>((offset_y + 0.5) * resolution);
        SetCenter(Point2Type{x_coor, y_coor});
    }

    /**
     * @brief Get const reference to center of grid cell
     *
     * @return const reference to center of grid cell
     */
    Point2Type const& GetCenter() const noexcept
    {
        return center_;
    }

    /**
     * @brief Set center of grid cell
     *
     * @param center center of grid cell
     */
    void SetCenter(Point2Type const& center)
    {
        center_ = center;
    }

    /**
     * @brief Get const reference of relative velocity
     *
     * @return const reference of relative velocity
     */
    Point2Type const& GetRelativeVelocity() const noexcept
    {
        return relative_velocity_;
    }

    /**
     * @brief Set relative velocity
     *
     * @param velocity relative velocity
     */
    void SetRelativeVelocity(Point2Type const& velocity)
    {
        relative_velocity_ = velocity;
    }

    /**
     * @brief Get obstacle classification
     *
     * @return classification of obstacle
     */
    ClassificationType const& GetClassification() const noexcept
    {
        return classification_;
    }

    /**
     * @brief Set obstacle classfication
     *
     * @param classification classification of obstacle
     */
    void SetClassification(ClassificationType const& classification) noexcept
    {
        classification_ = classification;
    }

    /**
     * @brief Get obstacle id
     *
     * @return obstacle id
     */
    uint32_t GetObstacleId() const noexcept
    {
        return obstacle_id_;
    }

    /**
     * @brief Set obstacle id
     *
     * @param obstacle_id obstacle id
     */
    void SetObstacleId(uint32_t const obstacle_id) noexcept
    {
        obstacle_id_ = obstacle_id;
    }

    /**
     * @brief Check if the cell is occupied.
     *
     * @return true for occupied.
     * @return false for not occupied.
     */
    bool_t IsOccupied() const noexcept
    {
        return is_occupied_;
    }

    /**
     * @brief Set cell occupancy status
     *
     * @param status cell occupancy status
     */
    void SetOccupiedStatus(bool_t const status)
    {
        is_occupied_ = status;
    }

    /**
     * @brief Get obstacle motion status
     *
     * @return obstalce motion status
     */
    MotionStatusType GetMotionStatus() const noexcept
    {
        return motion_status_;
    }

    /**
     * @brief Set obstacle motion status
     *
     * @param motion_status obstacle motion status
     */
    void SetMotionStatus(MotionStatusType const motion_status) noexcept
    {
        motion_status_ = motion_status;
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
        return center_.GetSerializedSize<ALIGN>() + relative_velocity_.GetSerializedSize<ALIGN>() +
               classification_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(obstacle_id_, is_occupied_,
                                                          static_cast<uint8_t>(motion_status_));
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << center_ << relative_velocity_ << classification_ << obstacle_id_ << is_occupied_
                   << static_cast<uint8_t>(motion_status_) << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint8_t motion_status = 0U;
        deserializer >> center_ >> relative_velocity_ >> classification_ >> obstacle_id_ >> is_occupied_ >>
            motion_status >> holo::serialization::align;

        motion_status_ = static_cast<MotionStatusType>(motion_status);
    }

private:
    Point2Type         center_;  ///< the coordinates of the center of grid in body coordinate, unit:m
    Point2Type         relative_velocity_;
    ClassificationType classification_;
    uint32_t           obstacle_id_;
    bool_t             is_occupied_;
    MotionStatusType   motion_status_;
};
}  // namespace common
}  // namespace holo

#endif /* HOLO_COMMON_GRID_MAP_H_ */
