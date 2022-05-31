/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file quaternion.h
 * @brief holo quaternion type
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date Oct-10-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_QUATERNION_H_
#define HOLO_GEOMETRY_DETAILS_QUATERNION_H_

#include <memory>

#include <holo/core/types.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace geometry
{
namespace details
{
/**
 * @addtogroup geometry
 * @{
 *
 */

/**
 * @brief define quaternion class
 *
 * @note the quaternion is normalized internally
 *
 * @tparam T float32_t or float64_t
 */
template <typename T>
class QuaternionT
{
public:
    using ScalarType     = T;
    using QuaternionType = QuaternionT<ScalarType>;
    using Matrix3Type    = holo::numerics::MatrixT<ScalarType, 3, 3>;
    using Vector3Type    = holo::numerics::VectorT<ScalarType, 3>;
    static_assert(std::is_floating_point<ScalarType>::value, "QuaternionT needs to take floating type");

    /**
     * @brief default constructor
     *
     * @throw std::bad_alloc if initialization fails
     */
    QuaternionT();

    /**
     * @brief Construct a new Quaternion T object with scalars
     *
     * @param w w value
     * @param x x value
     * @param y y value
     * @param z z value
     * @throw std::bad_alloc if initialization fails
     */
    QuaternionT(ScalarType const w, ScalarType const x, ScalarType const y, ScalarType const z);

    /**
     * @brief Construct a new Quaternion T object with raw data
     *
     * @param array raw data array in [x, y, z, w] order !!!
     * @param array_size array size must be 4 !!!
     * @throw std::out_of_range if array_size is not 4
     */
    QuaternionT(ScalarType const* array, uint32_t const array_size);

    /**
     * @brief Construct a new Quaternion T object from matrix
     *
     * @details this matrix must be a rotation matrix, i.e. \f $SO3$ \f
     * @param matrix matrix
     * @throw std::bad_alloc if initialization fails
     */
    QuaternionT(Matrix3Type const& matrix);

    /**
     * @brief copy constructor
     *
     * @param other quaternion
     * @throw std::bad_alloc if initialization fails
     */
    QuaternionT(QuaternionT const& other);

    /**
     * @brief Destroy the Quaternion T object
     */
    ~QuaternionT() noexcept;

    /**
     * @brief assignment operator
     *
     * @param other quaternion
     * @return QuatenrionT&
     * @throw std::bad_alloc if initialization fails
     */
    QuaternionT& operator=(QuaternionT const& other);

    /**
     * @brief output streame
     *
     * @tparam T
     * @param os std::os
     * @param quaternion quaternion
     * @return std::ostream&
     */
    template <typename InputScalar>
    friend std::ostream& operator<<(std::ostream& os, QuaternionT<InputScalar> const& quaternion) noexcept;

    /**
     * @brief cast quaternion to a different floating type
     * @tparam OutputScalar float32_t or float64_t
     *
     * @return QuaternionT<OutputScalar>
     */
    template <typename OutputScalar>
    QuaternionT<OutputScalar> Cast() const noexcept;

    /**
     * @brief convert quaternion to rotation matrix
     *
     * @return Matrix3Type
     */
    Matrix3Type ToRotationMatrix() const noexcept;

    /**
     * @brief return the squared norm of quaternion
     *
     * @return ScalarType
     */
    ScalarType GetSquaredNorm() const noexcept;

    /**
     * @brief return the norm of quaternion
     *
     * @return ScalarType
     */
    ScalarType GetNorm() const noexcept;

    /**
     * @brief return the inverse of a quaternion
     *
     * @return QuaternionT
     */
    QuaternionT Inverse() const noexcept;

    /**
     * @brief return the conjugate of a quaternion
     *
     * @return QuaternionT
     */
    QuaternionT GetConjugate() const noexcept;

    /**
     * @brief quaternion slerp
     *
     * @param t ratio
     * @param other quaternion
     * @return QuaternionT
     * @throw std::out_of_range if t is out of range [0, 1]
     */
    QuaternionT Slerp(ScalarType const t, QuaternionT const& other) const;

    /**
     * @brief return the w value of quaternion
     *
     * @return ScalarType
     */
    ScalarType GetW() const noexcept;

    /**
     * @brief return the x value of quaternion
     *
     * @return ScalarType
     */
    ScalarType GetX() const noexcept;

    /**
     * @brief return the y value of quaternion
     *
     * @return ScalarType
     */
    ScalarType GetY() const noexcept;

    /**
     * @brief return the z value of quaternion
     *
     * @return ScalarType
     */
    ScalarType GetZ() const noexcept;

    /**
     * @brief return the vector part of quaternion
     *
     * @return Vector3Type
     */
    Vector3Type GetVector() const noexcept;

    /**
     * @brief set the quaternion to identity
     *
     */
    void SetIdentity() noexcept;

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
        ScalarType w, x, y, z;
        return holo::serialization::SerializedSize<ALIGN>(w, x, y, z);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << GetW() << GetX() << GetY() << GetZ() << holo::serialization::align;
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
        ScalarType w, x, y, z;
        deserializer >> holo::serialization::align >> w >> x >> y >> z >> holo::serialization::align;
        impl_ptr_.reset(new Implementation(w, x, y, z));
    }

    /**
     * @brief return an identity quaternion
     *
     * @return QuaternionT
     */
    static QuaternionT Identity() noexcept;

private:
    /**
     * @brief normalize a quaternion
     *
     */
    void Normalize() noexcept;

    /**
     * @brief forward declaration of class Implementation
     */
    struct Implementation;

    /**
     * @brief Construct a new QuaternionT object from impl
     *
     * @param impl
     */
    QuaternionT(Implementation const& impl) noexcept;

    /**
     * @brief real implementation
     */
    std::unique_ptr<Implementation> impl_ptr_;

};  // QuaternionT

/**
 * @}
 *
 */

}  // namespace details
}  // namespace geometry
}  // namespace holo

#include "./impl/quaternion.hpp"

#endif  // HOLO_GEOMETRY_DETAILS_QUATERNION_H_
