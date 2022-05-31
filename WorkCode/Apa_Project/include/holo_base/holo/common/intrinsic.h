/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intrinsic.h
 * @brief This header file define camera intrinsic
 * @author lichao@holomatic.com
 * @date Sep 02, 2019
 */

#ifndef HOLO_COMMON_INTRINSIC_H_
#define HOLO_COMMON_INTRINSIC_H_

#include <holo/common/details/intrinsic.h>
#include <holo/core/types.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace common
{
/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief This class represents a pinhole camera intrinsic
 */
template <typename T>
using PinholeIntrinsicT = details::PinholeIntrinsicT<T>;

/**
 * @brief This class represents a pinhole camera intrinsic with accuracy of float32_t
 */
using PinholeIntrinsicf = PinholeIntrinsicT<float32_t>;

/**
 * @brief This class represents a pinhole camera intrinsic with accuracy of float64_t
 */
using PinholeIntrinsicd = PinholeIntrinsicT<float64_t>;

/**
 * @brief This class represents a fisheye camera intrinsic
 */
template <typename T>
using FisheyeIntrinsicT = details::FisheyeIntrinsicT<T>;

/**
 * @brief This class represents a fisheye camera intrinsic with accuracy of float32_t
 */
using FisheyeIntrinsicf = FisheyeIntrinsicT<float32_t>;

/**
 * @brief This class represents a fisheye camera intrinsic with accuracy of float64_t
 */
using FisheyeIntrinsicd = FisheyeIntrinsicT<float64_t>;

/**
 * @brief This class represents an omnidirectional camera intrinsic
 */
template <typename T>
using OmnidirectionalIntrinsicT = details::OmnidirectionalIntrinsicT<T>;

/**
 * @brief This class represents an omnidirectional camera intrinsic with accuracy of float32_t
 */
using OmnidirectionalIntrinsicf = OmnidirectionalIntrinsicT<float32_t>;

/**
 * @brief This class represents an omnidirectional camera intrinsic with accuracy of float64_t
 */
using OmnidirectionalIntrinsicd = OmnidirectionalIntrinsicT<float64_t>;

/**
 * @}
 *
 */
}  // namespace common

/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief Camera model definition
 *
 */
enum CameraModel : uint32_t[[deprecated]]{
    PINHOLE = 0x0000,
    FISHEYE = 0x0010,
    UNKNOWN = 0xFFFF,
}; /* enum CameraModel */

/**
 * @brief This class to held intrisic parameter for camera
 */
template <typename T>
class [[deprecated]] IntrinsicT {
public:
    using ScalarType            = T;
    using Matrix3[[deprecated]] = holo::numerics::MatrixT<ScalarType, 3, 3>;
    using Vector2[[deprecated]] = holo::numerics::VectorT<ScalarType, 2>;
    using Vector8[[deprecated]] = holo::numerics::VectorT<ScalarType, 8>;

    using Matrix3Type = holo::numerics::MatrixT<ScalarType, 3, 3>;
    using Vector2Type = holo::numerics::VectorT<ScalarType, 2>;
    using Vector8Type = holo::numerics::VectorT<ScalarType, 8>;

    /**
     * @brief disable default constructor
     */
    IntrinsicT();

    /**
     * @brief constructor
     * @param model camera model
     * @param size image size
     * @param K intrinsic parameter
     * @param D distortion coefficients the order is [k1,k2,p1,p2,k3,k4,k5,k6]
     */
    IntrinsicT(CameraModel model, const Vector2Type& size, const Matrix3Type& K, const Vector8Type& D);

    /**
     * @brief camera model
     *
     * @return camera model
     */
    CameraModel GetModel() const;

    /**
     * @brief intrinsic matrix k
     *
     * @return Matrix3Type
     */
    Matrix3Type GetK() const;

    /**
     * @brief distortion parameter d
     *
     * @return Vector8Type the order is [k1,k2,p1,p2,k3,k4,k5,k6]
     */
    Vector8Type GetD() const;

    /**
     * @brief image width and height
     *
     * @return size
     */
    Vector2Type GetDimension() const;

    /**
     * @brief intrinsic to string
     * @todo (lichao@holomatic.com) to be implemented in the future.
     *
     * @return string
     */
    std::string ToString() const;

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
        return holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(model_), width_, height_, fx_, fy_, cx_,
                                                          cy_, skew_, k1_, k2_, k3_, k4_, k5_, k6_, p1_, p2_);
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
    void Serialize(S & serializer) const
    {
        serializer << holo::serialization::align << static_cast<uint32_t>(model_) << width_ << height_ << fx_ << fy_
                   << cx_ << cy_ << skew_ << k1_ << k2_ << k3_ << k4_ << k5_ << k6_ << p1_ << p2_
                   << holo::serialization::align;
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
    void Deserialize(D & deserializer)
    {
        uint32_t m = 0xFFFF;

        deserializer >> holo::serialization::align >> m >> width_ >> height_ >> fx_ >> fy_ >> cx_ >> cy_ >> skew_ >>
            k1_ >> k2_ >> k3_ >> k4_ >> k5_ >> k6_ >> p1_ >> p2_ >> holo::serialization::align;

        model_ = (CameraModel)(m);
    }

    /**
     * @brief Save intrinsic to yaml file
     *
     * @param fn file name
     * @param in intrinsic
     * @param verbose verbosity
     * @return true if success to save to yaml file
     * @return false if failed to save to yaml file
     */
    static bool_t SaveYaml(const std::string& fn, const IntrinsicT& in, bool_t verbose = true);

    /**
     * @brief Load intrinsic from yaml file
     *
     * @param fn file name
     * @param verbose verbosity
     * @return Intrinsic loaded intrinsic file
     * @throws std::runtime_error if the file does not exist
     */
    static IntrinsicT LoadYaml(const std::string& fn, bool_t verbose = true);

private:
    /**
     * @brief camera model
     */
    CameraModel model_;

    /**
     * @brief fx
     */
    ScalarType fx_;

    /**
     * @brief fy
     */
    ScalarType fy_;

    /**
     * @brief cx
     */
    ScalarType cx_;

    /**
     * @brief cy
     */
    ScalarType cy_;

    /**
     * @brief skew
     */
    ScalarType skew_;

    /**
     * @brief k1
     */
    ScalarType k1_;

    /**
     * @brief k2
     */
    ScalarType k2_;

    /**
     * @brief k3
     */
    ScalarType k3_;

    /**
     * @brief k4
     */
    ScalarType k4_;

    /**
     * @brief k5
     */
    ScalarType k5_;

    /**
     * @brief k6
     */
    ScalarType k6_;

    /**
     * @brief p1
     */
    ScalarType p1_;

    /**
     * @brief p2
     */
    ScalarType p2_;

    /**
     * @brief image width
     */
    uint32_t width_;

    /**
     * @brief image height
     */
    uint32_t height_;
};

using Intrinsicf[[deprecated]] = IntrinsicT<float32_t>;
using Intrinsicd[[deprecated]] = IntrinsicT<float64_t>;

/**
 * @}
 *
 */

}  // namespace holo

#endif /* ----- #ifndef HOLO_COMMON_INTRINSIC_H_  ----- */
