/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file optional.h
 * @brief optional header file
 * @author duyanwei@holomatic.com
 * @date 2019-09-24
 */

#ifndef HOLO_LOCALIZATION_COMMON_OPTIONAL_H_
#define HOLO_LOCALIZATION_COMMON_OPTIONAL_H_

#include <cstddef>
#include <stdexcept>

#include <holo/core/types.h>

namespace holo
{
/**
 * @addtogroup common
 * @{
 */

/**
 * @brief define a none type from general optional
 *
 * @details one may return Optional::none to indicate an empty OptionalT object
 */
namespace optional
{
struct NoneType
{
};

const static NoneType none;
};  // namespace optional

/**
 * @brief optional object
 *
 * @tparam T T must be a basic measurement type.
 *
 * @todo !!! Please be noticed, pointer type of T has not be fully tested yet !!!
 */
template <typename T>
class OptionalT
{
public:
    /**
     * @brief default constructor
     *
     */
    OptionalT() noexcept : is_valid_(false)
    {
    }

    /**
     * @brief construct with data
     *
     * @param data internal data
     */
    OptionalT(const T& data) noexcept : is_valid_(true), data_(data)
    {
    }

    /**
     * @brief construct with a Optional::NoneType object
     */
    OptionalT(const optional::NoneType&) noexcept : OptionalT()
    {
    }

    /**
     * @brief Construct a new OptionalT object
     *
     * @param other optional object
     */
    OptionalT(const OptionalT& other) noexcept : is_valid_(other.is_valid_), data_(other.data_)
    {
    }

    /**
     * @brief assignment operator
     *
     * @param other optional object
     * @return OptionalT&
     */
    OptionalT& operator=(const OptionalT& other) noexcept
    {
        this->is_valid_ = other.is_valid_;
        this->data_     = other.data_;
        return *this;
    }

    // @todo move constructor and move operator

    /**
     * @brief return is valid
     *
     * @return bool_t
     */
    bool_t IsValid() const noexcept
    {
        return is_valid_;
    }

    /**
     * @brief return data
     *
     * @todo throw a more specific exception
     * @throw throw exception if data is in valid
     * @note Exception safety
     * @return const T&
     */
    const T& GetData() const
    {
        if (!IsValid())
        {
            throw std::runtime_error("accessing invalid data");
        }
        return data_;
    }

    /**
     * @brief return data
     *
     * @todo throw a more specific exception
     * @throw throw exception if data is in valid
     * @note Exception safety
     * @return const T&
     */
    T& GetData()
    {
        if (!IsValid())
        {
            throw std::runtime_error("accessing invalid data");
        }
        return data_;
    }

    /**
     * @brief operator bool
     *
     * @return true
     * @return false
     */
    operator bool() const noexcept
    {
        return IsValid();
    }

    /**
     * @brief operator !
     *
     * @return bool_t
     */
    bool_t operator!() const noexcept
    {
        return !IsValid();
    }

    /**
     * @brief operator *
     *
     * @throw throw exception if data is invalid
     * @note Exception safety
     * @return const T&
     */
    const T& operator*() const
    {
        return GetData();
    }

    /**
     * @brief operator *
     *
     * @throw throw exception if data is invalid
     * @note Exception safety
     * @return const T&
     */
    T& operator*()
    {
        return GetData();
    }

    /**
     * @brief operator ->
     *
     * @todo throw a more specific exception
     * @throw throw exception if data is invalid
     * @note Exception safety
     * @return const T*
     */
    const T* operator->() const
    {
        if (!IsValid())
        {
            throw std::runtime_error("accessing invalid data");
        }
        return &data_;
    }

    /**
     * @brief operator ->
     *
     * @todo throw a more specific exception
     * @throw throw exception if data is invalid
     * @note Exception safety
     * @return const T*
     */
    T* operator->()
    {
        if (!IsValid())
        {
            throw std::runtime_error("accessing invalid data");
        }
        return &data_;
    }

private:
    /**
     * @brief internal data
     *
     */
    bool_t is_valid_;
    T      data_;

};  // class OptionalT

/**
 * @brief handy function to create OptionalT object
 *
 * @tparam T data type
 * @tparam Args args to contruct T
 * @return OptionalT<T>
 */
template <typename T, typename... Args>
OptionalT<T> make_optional(Args&&... args)
{
    return OptionalT<T>(T(std::forward<Args>(args)...));
}

/**
 * @}
 */

}  // namespace holo

#endif  // HOLO_LOCALIZATION_COMMON_OPTIONAL_H_
