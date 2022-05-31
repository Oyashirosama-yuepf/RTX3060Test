/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parkingpath.h
 * @brief the header of parking path plan
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-07-06
 */

#ifndef _PARKINGTPATH_H_
#define _PARKINGTPATH_H_

#include <holo/hpp/parkingplan/commonfunction.h>

namespace holo
{
namespace planning
{
class ParkingPath
{
private:
    float64_t radius1_ = 5;    ///< Turning radius at first reversing in basic paradigm
    float64_t radius2_ = 5;    ///< Turning radius at first forward adjustment in base paradigm
    float64_t x_f0_    = 0;    ///< x of switch point coordinates for the first time in the basic paradigm
    float64_t y_f0_    = 0;    ///< y of switch point coordinates for the first time in the basic paradigm
    float64_t epsilon_ = 0.0;  ///< The anti-collision threshold of the first reversing and the corner point of the
                               ///< garage in the basic paradigm.
    float64_t delta_ = 0;  ///< Whether there is an intersection between the circle with O1 as the center and radius_1_
                           ///< as the radius and the edge of the parkinglot
    float64_t delta_dot_ =
        0;  ///< Whether there is an intersection between the circle with O2 as the center and radius_2_ as the radius
            ///< and the straight line offset by R from the longitudinal axis of the parkinglot
    bool_t once_backward_in_ = false;  ///< The flag that can be parked in at one time
    bool_t simple_mode_      = false;  ///< Flag when it cannot be calculated exactly

public:
    /**
     * @brief constructor
     */
    ParkingPath() = default;

    /**
     * @brief destroys the object
     */
    ~ParkingPath() = default;

    /**
     * @brief return the flag whether it can be calculated exactly
     *
     * @return the flag whether it can be calculated exactly
     */
    bool_t GetSimpleMode();

    /**
     * @brief set the flag whether it can be calculated exactly
     *
     * @param[in] option: the flag whether it can be calculated exactly
     */
    void SetSimpleMode(bool_t option);

    /**
     * @brief Plan the first reversing adjustment path of vertical parking out
     *
     * @param[out] gpath  planned path
     *
     */
    void GenerateFirstBackAdjustPathForAPAPullOut_Vertical(PathData* gpath) const;

    /**
     * @brief Plan the reversing adjustment path of vertical parking out
     *
     * @param[out] gpath  planned path
     *
     */
    void GenerateBackAdjustPathForAPAPullOut_Vertical(PathData* gpath, float64_t direction) const;

    /**
     * @brief Plan the first reversing adjustment path of parallel parking out
     *
     * @param[out] gpath  planned path
     *
     */
    void GenerateFirstBackwardPathForPullOut_Parallel(PathData* gpath) const;

    /**
     * @brief Plan the reversing adjustment path of parallel parking out
     *
     * @param[out] gpath  planned path
     *
     */
    void GenerateBackAdjustPathForAPAPullOut_Parallel(PathData* gpath, float64_t direction) const;

    /**
     * @brief Plan the path for forward scanning of parking spaces
     *
     * @param[out] gpath  planned path
     *
     */
    void GenerateScaningForwardPath(PathData* gpath) const;

    /**
     * @brief Plan the first segment of the path to park
     *
     * @param[in] lot  given lot
     * @param[in] d  the space between the edge of the car outline and the boundary
     * @param[out] gpath  planned path
     *
     */
    void GenerateFisrtPathForParking_ParallelandVerticle(SingleParkingLot* lot, float64_t d, PathData* gpath);

    /**
     * @brief Plan the first backward turning segment of the path to park in vertical parkinglot
     *
     * @param[in] lot  given lot
     * @param[out] gpath  planned path
     *
     */
    void GenerateBackwardPathForParking_Verticle(SingleParkingLot* lot, PathData* gpath);

    /**
     * @brief Plan the forward adjust segment of the path to park in vertical parkinglot
     *
     * @param[in] lot  given lot
     * @param[out] gpath  planned path
     *
     * @return whether succeed
     */
    bool_t GenerateInsideForwardPathForParking_Verticle(SingleParkingLot* lot, PathData* gpath);

    /**
     * @brief Plan the inside backward segment of the path to park in vertical parkinglot
     *
     * @param[in] lot  given lot
     * @param[out] gpath  planned path
     *
     */
    void GenerateInsideBackwardPathForParking_Verticle(SingleParkingLot* lot, PathData* gpath);

    /**
     * @brief Plan the clothoid-based curve for incoming parkinglot
     *
     * @param[in] lot  given lot
     * @param[out] gpath  planned path
     *
     * @return whether succeed
     */
    bool_t GeneratePathUsingClothoidCurve(SingleParkingLot* lot, float64_t radius, PathData* gpath) const;

    /**
     * @brief Plan the inside backward adjust segment of the path to park in vertical parkinglot
     *
     * @param[in] lot  given lot
     * @param[out] gpath  planned path
     *
     */
    void GenerateBackwardAdjustPath(SingleParkingLot* lot, PathData* gpath) const;

    /**
     * @brief Plan the forward adjust segment of the path to park in vertical parkinglot
     *
     * @param[in] lot  given lot
     * @param[out] gpath  planned path
     *
     */
    void GenerateForwardAdjustPath(SingleParkingLot* lot, PathData* gpath) const;

    /**
     * @brief Plan the first path for the herringbone paradigm with precise calculation
     *
     * @param[in] lot  given lot
     * @param[out] gpath  planned path
     * @param[in] dis_x  distance from the target edge
     *
     * @return whether succeed
     */
    bool_t GenerateHerringbonePathForParking_Verticle(SingleParkingLot* lot, PathData* gpath, float64_t dis_x);

    /**
     * @brief Plan the first path for the herringbone paradigm without precise calculation
     *
     * @param[in] lot  given lot
     * @param[out] gpath  planned path
     * @param[in] dis_x  distance from the target edge
     *
     */
    void GenerateHerringboneForwardAdjustPath(SingleParkingLot* lot, PathData* gpath, float64_t dis_x) const;
};

}  // namespace planning
}  // namespace holo
#endif
