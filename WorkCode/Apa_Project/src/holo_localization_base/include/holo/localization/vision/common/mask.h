/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mask.h
 * @brief mask header file
 * @author duyanwei@holomatic.com
 * @date 2019-11-29
 */

#ifndef HOLO_LOCALIZATION_VISION_COMMON_MASK_H_
#define HOLO_LOCALIZATION_VISION_COMMON_MASK_H_

#include <holo/localization/vision/common/mat.h>

namespace holo
{
namespace localization
{
/**
 * @brief define mask class
 *
 * @details internally it uses cv::Mat from opencv and has a size of (width * height), each element is a unit8_t type,
 *          value that is greater than zero means a region of interest
 *
 */
class Mask : public Mat
{
public:
    using Base = Mat;

    /**
     * @brief default constructor
     *
     */
    Mask();

    /**
     * @brief constructor
     *
     * @param width mask width
     * @param height mask height
     * @param value initial value of each element in mask
     * @throw std::bad_alloc if initialization fails
     */
    Mask(const uint16_t width, const uint16_t height, const uint8_t value = 0u);

    /**
     * @brief construct from Mat
     *
     * @param mat holo mat
     * @throw std::runtime_error if the element in mat is NOT type of uint8_t
     */
    Mask(const Mat& mat);

    /**
     * @brief copy constructor (shallow copy)
     *
     * @param other other mask
     */
    Mask(const Mask& other);

    /**
     * @brief assignment operator (shallow copy)
     *
     * @param other other mask
     * @return mask copied mask
     * @throw std::bad_alloc if initialization fails
     */
    Mask& operator=(const Mask& other);

    /**
     * @brief this operation assigns all the elements in mat to the same value
     *
     * @details only supports element type of uint8_t
     * @param value element value
     */
    void operator=(const uint8_t value) noexcept;

    /**
     * @brief destructor
     *
     * @throw std::bad_alloc if memory fails to release
     */
    virtual ~Mask() noexcept;

    /**
     * @brief get element at specific position
     *
     * @param row row of element
     * @param col col of element
     * @throw std::out_of_range if row or col is out of mask range (width orheight)
     *
     */
    uint8_t At(const uint16_t row, const uint16_t col) const;

    /**
     * @brief get element at specific position
     *
     * @param row row of element
     * @param col col of element
     * @throw std::out_of_range if row or col is out of mask range (width or height)
     *
     */
    uint8_t& At(const uint16_t row, const uint16_t col);

    /**
     * @brief set the whole mask to some value
     *
     * @param value value
     */
    void SetTo(const uint8_t value) noexcept;

protected:
    using Base::mat_;

};  // class Mask

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_COMMON_MASK_H_
