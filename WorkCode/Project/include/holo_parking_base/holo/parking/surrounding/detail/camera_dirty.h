/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_conver.h
 * @brief This header file defines camera dirty infomation, camera view is split into 
 *        pieces to caculate the dirty condition, camera dirty container class to store 
 *        all the camera dirty info.
 * @author chengxiang(chengxiang@holomaitc.com)
 * @date 2021-08-04
 */

#ifndef HOLO_PARKING_BASE_SURROUNDING_DETAIL_CAMERA_DIRTY_H_
#define HOLO_PARKING_BASE_SURROUNDING_DETAIL_CAMERA_DIRTY_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/container/vector.h>

namespace holo
{
namespace parking
{
namespace surroundings
{

struct dumb_camera_dirty_trait {};

/**
 * @brief This class defines camera dirty infomation,
 *        defines dirty degree to descripte view clearity,
 *        defines camera id to descripte which camera conver info it describes.
 *        the template arguments :
 *        `XDIMENSION`  : means camera view split count in x-axis,
 *        `YDIMENSION`  : means camera view split count in y-axis,
 *        `BLOCK_WIDTH` : means camera view splited pieces block width,
 *        `BLOCK_HEIGHT`: means camera view splited pieces block height.
 *        Extend class `Vector` to store camera split pieces dirty infomation.
 */
template<size_t XDIMENSION, size_t YDIMENSION, size_t BLOCK_WIDTH, size_t BLOCK_HEIGHT>
class CameraDirty : public holo::container::Vector<uint8_t, XDIMENSION * YDIMENSION>
{
public:
    ///< describes the camera area block
    enum DirtyDegree: uint8_t
    {
        CLEAR        = 0x00,    ///< camera view is clear 
        TRANSPARENT  = 0x01,    ///< coverage is transparent, clear view
        TRANSLUCENT  = 0x02,    ///< semi-transparent, view not clear enough
        DIRTY        = 0x03     ///< whole camera covered, without useful view
    };

    ///< which camera this objects represent.
    enum CameraId : uint8_t
    {
        FRONT_WIDE_ANGLE_CAMREA = 0x00,    ///< front wide-angle camera  
        FRONT_FISHEYE_CAMERA    = 0x01,    ///< front fisheye camera
        LEFT_FISHEYE_CAMERA     = 0x02,    ///< left fisheye camera
        RIGHT_FISHEYE_CAMERA    = 0x03,    ///< right fisheye camera
        REAR_FISHEYE_CAMERA     = 0x04,    ///< rear fisheye camera
        CAMERA_COUNTS           = 0x05     ///< camera counts
    };

    using CameraDirtyTraits = dumb_camera_dirty_trait;
    using Base              = holo::container::Vector<uint8_t, XDIMENSION * YDIMENSION>;

public:
    explicit CameraDirty()
        :timestamp_()
        ,camera_id_(FRONT_WIDE_ANGLE_CAMREA)
    {}

    holo::common::Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    void SetTimestamp(holo::common::Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    CameraId GetCameraId() const noexcept 
    {
        return camera_id_;
    }

    void SetCameraId( CameraId camera_id )
    {
        camera_id_ = camera_id;
    }

    static inline size_t GetXDimension() 
    {
        return XDIMENSION;
    }

    static inline size_t GetYDimension()
    {
        return YDIMENSION;
    }

    static inline size_t GetBlockWidth()
    {
        return BLOCK_WIDTH;
    }

    static inline size_t GetBlockHeight()
    {
        return BLOCK_HEIGHT;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     * @tparam ALIGN Byte alignment value
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        uint8_t id = static_cast<uint8_t>(camera_id_);
        size_t total_size = timestamp_.GetSerializedSize<ALIGN>()
                + holo::serialization::SerializedSize<ALIGN>(id)
                + Base::template GetSerializedSize<ALIGN>();
        return total_size;
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     * @param serializer The buffer to serializer.
     * @return none.
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_<< static_cast<uint8_t>(camera_id_);
        Base::template Serialize<S>(serializer);

        serializer << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     * @param deserializer The buffer to deserialize from.
     * @return none.
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint8_t ui_camera_id    = 0;

        deserializer >> timestamp_ >> ui_camera_id;
        Base::template Deserialize<D>(deserializer);
        deserializer >> holo::serialization::align;
        
        camera_id_ = static_cast<CameraId>(ui_camera_id);
    }

private:
    holo::common::Timestamp timestamp_;      ///< sensor collection timestamp
    CameraId                camera_id_;      ///< which camera, this object describes
};

/**
 * @brief This class defines the camera dirty info container, 
 *        it contains all cameras's dirty information, around the vehicle,
 *        aditional for timestamp represent the camera views deal time.
 */
template <typename CameraDirtyType>
class CamerasDirtyVector 
    : public holo::container::Vector<CameraDirtyType, static_cast<size_t>(CameraDirtyType::CAMERA_COUNTS)>
{
private:
    ///< template parameter validate check.
    using dumb = typename std::enable_if< std::is_same<
                    typename CameraDirtyType::CameraDirtyTraits, 
                    dumb_camera_dirty_trait>::value >::type;

public:
    using CameraDirty = CameraDirtyType;
    using Base = holo::container::Vector<CameraDirtyType, static_cast<size_t>(CameraDirtyType::CAMERA_COUNTS)>;

public:
    explicit CamerasDirtyVector()
    :timestamp_()
    {}

    holo::common::Timestamp GetTimestamp() const noexcept 
    {
        return timestamp_;
    }

    void SetTimestamp(holo::common::Timestamp const & timestamp)
    {
        timestamp_ = timestamp;
    }

    static inline size_t GetCameraXDimention()
    {
        return CameraDirty::GetXDimention();
    }

    static inline size_t GetCameraYDimention()
    {
        return CameraDirty::GetXDimention();
    }

    static inline size_t GetCameraBlockWidth()
    {
        return CameraDirty::GetBlockWidth();
    }

    static inline size_t GetCameraBlockHeight()
    {
        return CameraDirty::GetBlockHeight();
    }

    /**
     * @brief Get serialized size at give byte alignment value
     * @tparam ALIGN Byte alignment value
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.template GetSerializedSize<ALIGN>() + Base::template GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     * @param serializer The buffer to serializer.
     * @return none.
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_;
        Base::template Serialize<S>(serializer);
        serializer << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     * @param deserializer The buffer to deserialize from.
     * @return none.
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> timestamp_;
        Base::template Deserialize<D>(deserializer);
        deserializer >> holo::serialization::align;
    }

private:
    holo::common::Timestamp  timestamp_;                ///< timestamp after deal with camera view
};

}  // namespace surroundings
}  // namespace parking
}  // namespace holo

#endif
