/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fast.h
 * @brief This file defines fast class used to extract fast corner
 * @author Evan. Du
 * @date "2017-12-21"
 */

#ifndef HOLO_LOCALIZATION_VISION_FEATURE_FAST_H_
#define HOLO_LOCALIZATION_VISION_FEATURE_FAST_H_

#include <holo/localization/vision/feature/feature2d.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup vision
 * @{
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief this class aims to detect fast corner from a given image
 * @ref https://docs.opencv.org/3.3.1/df/d74/classcv_1_1FastFeatureDetector.html
 */
class FAST : public FeatureDetector
{
public:
    /// @brief using base types
    using Base = FeatureDetector;
    using Base::KeyPoint2f;
    using Base::Mask;
    using Base::Mat;

    /**
     * @brief fast feature type
     */
    enum class Type : uint8_t
    {
        TYPE_9_16 = 0u,
        TYPE_7_12 = 1u,
        TYPE_5_8  = 2u,
    };  // enum Type

    /**
     * @brief constructor
     *
     * @param[in] threshold pixel threshold for fast corner detection
     * @param[in] non_max_suppression whether do non maximum suppression
     * @param[in] type fast type
     * @throw when the given type is invalid
     */
    FAST(const int32_t threshold = 10, const bool_t non_max_suppression = true, const Type type = Type::TYPE_9_16);

    /**
     * @brief copy constructor
     *
     * @param[in] other the given FAST object
     */
    FAST(const FAST& other);

    /**
     * @brief destructor
     */
    ~FAST() noexcept;

    /**
     * @brief assign the other fast object  to *this
     *
     * @param[in] other the other fast object
     */
    void operator=(const FAST& other);

    /**
     * @brief detect fast corner
     *
     * @param[in] image the given image
     * @param[out] keypoints detected key points
     * @param[in] mask image mask used to constraint key points' location
     * @return bool_t true if the key points are detected successfully, false otherwise
     */
    virtual bool_t Detect(const Mat& image, std::vector<KeyPoint2f>& keypoints,
                          const holo::OptionalT<Mask>& mask = holo::optional::none) const override;

    /**
     * @brief set the threshold for fast corner detection
     *
     * @param[in] threshold threshold (Unit[pixel])
     */
    void SetThreshold(const int32_t threshold) noexcept;

    /**
     * @brief get the threshold
     *
     * @return int32_t threshold in pixel
     */
    int32_t GetThreshold() const noexcept;

    /**
     * @brief set whether do nonmax suppression
     *
     * @param[in] non_max_suppression true means do nonmax suppression
     */
    void SetNonmaxSuppression(const bool_t non_max_suppression) noexcept;

    /**
     * @brief get the nonmax suppression flag
     *
     * @return bool_t it returns true if the fast detector does nonmax suppression
     */
    bool_t GetNonmaxSuppression() const noexcept;

    /**
     * @brief set the type of fast corner
     *
     * @param[in] type fast type TYPE_9_16 TYPE_7_12 TYPE_5_8
     * @throw when the given type is invalid
     */
    void SetType(const Type type);

    /**
     * @brief get the fast corner type
     *
     * @return Type fast corner type
     */
    Type GetType() const noexcept;

private:
    /**
     * @brief forward declaration for struct Implementation
     */
    struct Implementation;

    /**
     * @brief implementation ptr
     */
    std::unique_ptr<Implementation> impl_ptr_;
};  // class FAST

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo
#endif  // HOLO_LOCALIZATION_VISION_FEATURE_FAST_H_
