/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hmm_matcher.h
 * @brief Definition for MapMatcher with Hidden Markov Model.
 * @author wanghaiyang(wanghaiyang@holomaitc.com)
 * @date "2021-11-11"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_MATCHER_HMM_MATCHER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_MATCHER_HMM_MATCHER_H_

#include <memory>

#include <holo/map/service/client/matcher/results.h>
#include <holo/map/service/client/engine/retriever.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace matcher
{

/**
 * @addtogroup matcher
 * @{
 *
 */

/**
 * @brief Map matcher algorithm with Hidden Markov Model.
 * 
 */
class HmmMapMatcher
{
public:
    // Redefine retriver types for inner members.
    using RetrieverType     = holo::map::service::client::engine::Retriever;
    using RetrieverSPtrType = holo::map::service::client::engine::RetrieverSPtrType;

    // Redefine profile type for matching level.
    using ProfileType       = RetrieverType::ProfileType;

    /**
     * @brief Default constructor.
     */
    HmmMapMatcher();

    /**
     * @brief Default deconstructor.
     */
    virtual ~HmmMapMatcher();

    HmmMapMatcher(HmmMapMatcher const&) = delete;
    HmmMapMatcher(HmmMapMatcher&&) = delete;

    HmmMapMatcher& operator=(HmmMapMatcher const&) = delete;
    HmmMapMatcher& operator=(HmmMapMatcher&&) = delete;

    // Redefine value type for matching reference.
    using MatchingReferenceValue = holo::uint8_t;

    /**
     * @brief Matching reference type, 
     * 
     * @detail 1) If we set multiple type at same time, position matching will calculate
     *            all the reference lines.
     *         2) If a map feature without boundaries, we will match position with middle
     *            line.
     */
    enum class MatchingReferenceType : MatchingReferenceValue
    {
        /// Match position with middle line of map feature.
        MRT_MIDDLE_LINE     = 0X01,
        /// Match position with left boundary line of map feature.
        MRT_LEFT_BOUNDARY   = 0X02,
        /// Matching position with right boundary line of map feature.
        MRT_RIGHT_BOUNDARY  = 0X04,
    };

    /**
     * @brief Access matching level.
     * 
     * @return Matching level, default: kLANE_GROUP.
     */
    ProfileType GetLevel() const noexcept;

    /**
     * @brief Assign matching level.
     * 
     * @param[in] type Matching level, default: kLANE_GROUP, only support
     *            kROAD and kLANE_GROUP.
     */
    void SetLevel(ProfileType const type) noexcept;

    /**
     * @brief Access verbose flag.
     * 
     * @return Verbose flag.
     */
    holo::bool_t GetVerbose() const noexcept;

    /**
     * @brief Assign verbose flag.
     * 
     * @param[in] v If true, HmmMatcher object will print debug log;
     *              If false, HmmMatcher object will not print debug log;
     */
    void SetVerbose(holo::bool_t const v) noexcept;

    /**
     * @brief Access matching reference.
     * 
     * @return Matching reference.
     */
    MatchingReferenceValue GetReference() const noexcept;

    /**
     * @brief Assign matching reference.
     * 
     * @param[in] r Matching reference value, default: MRT_LEFT_BOUNDARY|MRT_RIGHT_BOUNDARY.
     */
    void SetReference(MatchingReferenceValue const r) noexcept;

    /**
     * @brief Init HmmMatcher object.
     * 
     * @param[in] ret Map data retriever handle.
     * @return If true: No error;
     *         If false: An error occurs in this function.
     */
    holo::bool_t Init(RetrieverSPtrType ret);

    /**
     * @brief Reset HmmMatcher object status and clear history info.
     */
    void Reset();

    /**
     * @brief Define matching result reason.
     */
    enum class MatchingResultReason : holo::uint8_t
    {
        /// No exception.
        MRR_NONE = 0,
        /// Invalid input odometry with invalid position value.
        MRR_INVALID_POSITION = 1,
        /// Invalid input odometry with invalid timestamp value.
        MRR_INVALID_TIMESTAMP = 2,
    };

    /**
     * @brief Define input struct for map matching algorithm.
     */
    struct Input
    {
        /// Redefine odometry type for inner members.
        using OdometryType = holo::common::Odometryd;
        /// Odometry from message queue with 1HZ.
        OdometryType odo;
    };

    /**
     * @brief Define output struct for map matching algorithm.
     */
    struct Output
    {
        /// Redefine matching result type for inner members.
        using MatchingResultType    = holo::map::service::client::matcher::MatchingResult;
        /// Redefine matching results type for inner members.
        using MatchingResultsType   = holo::map::service::client::matcher::MatchingResults;

        /// Matching result.
        MatchingResultsType results;
        /// Reason for mathing result.
        MatchingResultReason reason = MatchingResultReason::MRR_NONE;
    };

    /**
     * @brief Format input object to JSON string.
     * 
     * @param[in] in An input object.
     * @return A JSON string.
     */
    static std::string FormatToString(Input const& in);

    /**
     * @brief Format output object to JSON string.
     * 
     * @param[in] in An output object.
     * @return A JSON string.
     */
    static std::string FormatToString(Output const& in);

    /**
     * @brief Match a position to map features with time series.
     * 
     * @param[in] input Input parameters.
     * @param[out] output Output paramters.
     * @return true: No error.
     *         false: An error occurs in this function, refer to logs for
     *                for more details.
     */
    holo::bool_t Process(Input const& input, Output& output);

    /**
     * @brief Match a position to map features with time series.
     * 
     * @param[in] input Input parameters.
     * @param[out] output Output paramters.
     * @return true: No error.
     *         false: An error occurs in this function, refer to logs for
     *                for more details.
     */
    holo::bool_t operator () (Input const& input, Output& output);

private:
    /// Inner class for HmmMapMatcher.
    class HmmMapMatcherInner;
    /// A handle of inner HmmMapMatcher.
    std::unique_ptr<HmmMapMatcherInner> inner_;
};

/**
 * @}
 *
 */

} ///< namespace matcher
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_MATCHER_HMM_MATCHER_H_ */