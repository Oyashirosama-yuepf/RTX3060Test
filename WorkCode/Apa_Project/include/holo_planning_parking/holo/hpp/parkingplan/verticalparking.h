/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file verticalparking.h
 * @brief the class processes decision making & path planning of vertical parking
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-03-13
 */

#ifndef _VERTICALPARKING_H_
#define _VERTICALPARKING_H_

#include <holo/hpp/parkingplan/parkingbase.h>
#include <array>
#include <functional>

namespace holo
{
namespace planning
{
/**
 * @brief  main class of vetical parking path plan
 *
 * @details a class, which includes vetical parking state decision
 * and vetical parking path plan
 */
class VerticalParking : public ParkingBase
{
public:
    /**
     * @brief constructor.
     */
    VerticalParking()
    {
    }

    /**
     * @brief destroys the object.
     */
    ~VerticalParking() = default;

    /**
     * @brief cycle run
     *
     * @details vertical parking process management
     */
    virtual void RunOnce() override;

    /**
     * @brief reset vertical used variables
     */
    void Reset4Next();

    /**
     * @brief Return whether is the herringbone mode or not
     */
    bool_t IsHerringboneMode();

private:
    /**
     * @brief forward path plan outside parkinglot
     */
    virtual void ExcuteOutsideForward() override;

    /**
     * @brief backward path plan outside parkinglot
     */
    virtual void ExcuteOutsideBackward() override;

    /**
     * @brief forward path plan inside parkinglot
     */
    virtual void ExcuteInsideForward() override;

    /**
     * @brief backward path plan inside parkinglot
     */
    virtual void ExcuteInsideBackward() override;

    /**
     * @brief parking succeed
     */
    virtual void CompleteParking() override;

    /**
     * @brief parking failed
     */
    virtual void ParkingFailed() override;

    /**
     * @brief decision making when execute forward path plan outside parkinglot
     */
    void ReasonOutsideForwardAdjust();

    /**
     * @brief decision making when execute backward path plan outside parkinglot
     */
    void ReasonOutsideBackwardAdjust();

    /**
     * @brief decision making when execute forward path plan inside parkinglot
     */
    void ReasonInsideForwardAdjust();

    /**
     * @brief decision making when execute backward path plan inside parkinglot
     */
    void ReasonInsideBackwardAdjust();

    /**
     * @brief decision making when parking succeed
     */
    void ReasonCompleteParking()
    {
    }

    /**
     * @brief decision making when parking failed
     */
    void ReasonParkingFailed()
    {
    }

    /**
     * @brief whether the front is restricted by obstacle or lot
     */
    bool_t IsForwardLimited();

    /**
     * @brief  whether the back is restricted by obstacle or lot
     */
    bool_t IsBackwardLimited();

    /**
     * @brief whether the front is restricted by lot
     */
    bool_t IsParkingSpaceLimitedForVertical(const float64_t dist_to_middle) const;

    enum class VerticalParkingState
    {
        OUTSIDE_FORWARD,
        OUTSIDE_BACKWARD,
        INSIDE_FORWARD,
        INSIDE_BACKWARD,
        PARKING_COMPLETE,
        PARKING_FAILED
    };
    VerticalParkingState current_status_ = VerticalParkingState::OUTSIDE_FORWARD;

    using StatesExcuteFunc = std::array<std::function<void()>, 6>;

    StatesExcuteFunc ExcuteFunc = {{std::bind(&VerticalParking::ExcuteOutsideForward, this),
                                    std::bind(&VerticalParking::ExcuteOutsideBackward, this),
                                    std::bind(&VerticalParking::ExcuteInsideForward, this),
                                    std::bind(&VerticalParking::ExcuteInsideBackward, this),
                                    std::bind(&VerticalParking::CompleteParking, this),
                                    std::bind(&VerticalParking::ParkingFailed, this)}};

    using StatesReasonFunc = std::array<std::function<void()>, 6>;

    StatesReasonFunc ReasonFunc = {{std::bind(&VerticalParking::ReasonOutsideForwardAdjust, this),
                                    std::bind(&VerticalParking::ReasonOutsideBackwardAdjust, this),
                                    std::bind(&VerticalParking::ReasonInsideForwardAdjust, this),
                                    std::bind(&VerticalParking::ReasonInsideBackwardAdjust, this),
                                    std::bind(&VerticalParking::ReasonCompleteParking, this),
                                    std::bind(&VerticalParking::ReasonParkingFailed, this)}};

    bool_t is_first_outside_forward_adjust_  = true;
    bool_t is_first_outside_backward_adjust_ = true;
    bool_t is_first_inside_forward_adjust_   = true;
    bool_t is_first_inside_backward_adjust_  = true;
    bool_t herringbone_mode_                 = false;
    bool_t insideforward_limit_              = true;
};

}  // namespace planning
}  // namespace holo

#endif
