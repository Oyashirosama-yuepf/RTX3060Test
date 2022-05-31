/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file verticalpullingout.h
 * @brief the class of vertical pullingout
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-03-18
 */

#ifndef _VERTICALPULLINGOUT_H_
#define _VERTICALPULLINGOUT_H_

#include <holo/hpp/parkingplan/pullingoutbase.h>
//#include <holo/hpp/parkingplan/samplingpathplan.h>

namespace holo
{
namespace planning
{
/**
 * @brief  main class of veticallot pullingout path plan
 *
 * @details a class, which includes veticallot pullingout state decision
 * and veticallot pullingout path plan
 */
class VerticalPullingOut : public PullingOutBase
{
public:
    /**
     * @brief constructor.
     */
    VerticalPullingOut() = default;

    /**
     * @brief destroys the object.
     */
    ~VerticalPullingOut() = default;

    /**
     * @brief generate global path for verticallot pullingout
     *
     * @param[in] reference_line reference path for pulling out
     * @param[out] pullout_path global path for verticallot pullingout
     */
    void GenerateGlobalPathForPullOut(std::vector<CurvePoint> const& reference_line,
                                      std::vector<CurvePoint>&       pullout_path);

    /**
     * @brief generate pursuit global path for verticallot pullingout
     *
     * @param[in] reference_line reference path for pulling out
     * @param[out] pullout_path pursuit global path for verticallot pullingout
     */
    void GeneratePursuitPathForPullOut(std::vector<CurvePoint> const& reference_line,
                                       std::vector<CurvePoint>&       pullout_path);

    /**
     * @brief cycle run
     *
     * @details veticallot pullingout process management
     */
    virtual void RunOnce() override;

private:
    /**
     * @brief what to do when complete pullingout
     */
    virtual void CompletePullOut() override;

    /**
     * @brief ready for pullout
     */
    void ExcuteReadyForPullOut()
    {
    }

    /**
     * @brief forward search for verticallot pullingout
     */
    void ExcuteForwardSearch();

    /**
     * @brief backward adjustment for verticallot pullingout
     */
    void ExcuteBackwardAdjust();

    /**
     * @brief first backward adjustment for verticallot pullingout
     */
    void ExcuteFirstBackwardAdjust();

    /**
     * @brief pull out failed
     */
    void PullOutFailed();

    /**
     * @brief  reason ready for pullout
     */
    void ReasonReadyForPullOut();

    /**
     * @brief reason forward search for verticallot pullingout
     */
    void ReasonForwardSearch();

    /**
     * @brief reason backward adjustment for verticallot pullingout
     */
    void ReasonBackwardAdjust();

    /**
     * @brief reason first backward adjustment for verticallot pullingout
     */
    void ReasonFirstBackwardAdjust();

    /**
     * @brief reason pull out complete
     */
    void ReasonCompletePullOut()
    {
    }

    /**
     * @brief reason pull out failed
     */
    void ReasonPullOutFailed()
    {
    }

    /**
     * @brief whether forward limited
     */
    bool_t IsForwardLimited();

    /**
     * @brief whether backward limited
     */
    bool_t IsBackwardLimited();

    /**
     * @brief reset used variables
     */
    void Reset4Next();

private:
    bool_t  is_first_backward_adjust_  = true;  ///< whether first backward adjustment
    int32_t pull_out_backward_counter_ = 0;     ///< counter of the number of backward

    float64_t    distance_verticalpullout_  = 0;  ///< vertical pullout retreat distance
    unsigned int forward_obstacle_counter_  = 0;  ///< counter when there is forward obstacle
    unsigned int backward_obstacle_counter_ = 0;  ///< counter when there is backward obstacle

    bool_t using_fsm_ = true;

    enum class VerticalPullingOutState
    {
        READY_FOR_PULLOUT,
        FIRST_BACKWARD,
        FORWARD_SEARCH,
        BACKWARD_ADJUST,
        PULLOUT_COMPLETE,
        PULLOUT_FAILED
    };
    VerticalPullingOutState current_status_ = VerticalPullingOutState::READY_FOR_PULLOUT;
    /// state function binding definition to eliminate switch-case operation
    using StatesExcuteFunc = std::array<std::function<void()>, 6>;

    StatesExcuteFunc ExcuteFunc = {{std::bind(&VerticalPullingOut::ExcuteReadyForPullOut, this),
                                    std::bind(&VerticalPullingOut::ExcuteFirstBackwardAdjust, this),
                                    std::bind(&VerticalPullingOut::ExcuteForwardSearch, this),
                                    std::bind(&VerticalPullingOut::ExcuteBackwardAdjust, this),
                                    std::bind(&VerticalPullingOut::CompletePullOut, this),
                                    std::bind(&VerticalPullingOut::PullOutFailed, this)}};

    using StatesReasonFunc = std::array<std::function<void()>, 6>;

    StatesReasonFunc ReasonFunc = {{std::bind(&VerticalPullingOut::ReasonReadyForPullOut, this),
                                    std::bind(&VerticalPullingOut::ReasonFirstBackwardAdjust, this),
                                    std::bind(&VerticalPullingOut::ReasonForwardSearch, this),
                                    std::bind(&VerticalPullingOut::ReasonBackwardAdjust, this),
                                    std::bind(&VerticalPullingOut::ReasonCompletePullOut, this),
                                    std::bind(&VerticalPullingOut::ReasonPullOutFailed, this)}};
};

}  // namespace planning
}  // namespace holo

#endif
