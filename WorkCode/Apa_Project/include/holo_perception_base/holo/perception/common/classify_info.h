/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file classify_info.h
 * @brief This header file defines the basic classify info.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2020-09-07"
 */

#ifndef HOLO_PERCEPTION_COMMON_CLASSIFY_INFO_H_
#define HOLO_PERCEPTION_COMMON_CLASSIFY_INFO_H_

#include <holo/core/types.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup common
 *
 * @{
 */

/**
 * @brief define Base ClassifyInfo
 */
class ClassifyInfo
{
public:
    /**
     * @brief Default Constructor
     *
     */
    ClassifyInfo() noexcept : category_id_(0U), confidence_(0.0f)
    {
    }

    /**
     * @brief Constructor
     *
     * @param category_id , idx in classification results
     * @param confidence, classify result confidence
     * @throw std::range_error throw, if confidence is not in [0.0f, 1.0f]
     */
    ClassifyInfo(uint32_t const category_id, float32_t const confidence)
      : category_id_(category_id), confidence_(confidence)
    {
        if (confidence_ < 0.0f || confidence > 1.0f)
        {
            throw std::range_error("Confidence should be between 0.0 and 1.0 !");
        }
    }

    /**
     * @brief assign operator
     *
     * @param classify_info, another classify_info
     * @return ClassifyInfo&
     */
    ClassifyInfo& operator=(ClassifyInfo const& classify_info) noexcept
    {
        category_id_ = classify_info.category_id_;
        confidence_  = classify_info.confidence_;
        return *this;
    }

    /**
     * @brief equal operator
     *
     * @param classify_info, another classify_info
     * @return bool_t, true for same, false for different
     */
    bool_t operator==(ClassifyInfo const& classify_info) const noexcept
    {
        float32_t err_confidence = std::abs(confidence_ - classify_info.confidence_);
        return (err_confidence <= holo::EpsilonT<float32_t>::value) && (category_id_ == classify_info.category_id_);
    }

    /**
     * @brief Get the CategoryId
     *
     * @return uint32_t
     */
    uint32_t GetCategoryId() const noexcept
    {
        return category_id_;
    }

    /**
     * @brief Set the CategoryId
     *
     * @param category_id
     */
    void SetCategoryId(uint32_t const category_id) noexcept
    {
        category_id_ = category_id;
    }

    /**
     * @brief Get the Confidence
     *
     * @return Scalar
     */
    float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }

    /**
     * @brief Set the Confidence
     *
     * @param confidence
     * @throw std::range_error throw, if confidence is not in [0.0f, 1.0f]
     */
    void SetConfidence(float32_t const confidence)
    {
        if (confidence < 0.0f || confidence > 1.0f)
        {
            throw std::range_error("Confidence should be between 0.0 and 1.0 !");
        }
        confidence_ = confidence;
    }

private:
    uint32_t  category_id_;  ///< category idx
    float32_t confidence_;   ///< confidence of object
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_COMMON_CLASSIFY_INFO_H_
