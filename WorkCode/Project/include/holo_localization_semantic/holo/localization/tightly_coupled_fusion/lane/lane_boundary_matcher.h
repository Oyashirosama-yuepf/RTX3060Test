/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_boundary_matcher.h
 * @brief the definition of lane boundary matcher class
 * @author Wenzhi Liu (liuwenzhi@holomatic.com)
 * @date 2021-07-07
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_LANE_BOUNDARY_MATCHER_H_
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_LANE_BOUNDARY_MATCHER_H_

#include <holo/localization/tightly_coupled_fusion/lane/curve_fitter.h>
#include <holo/localization/tightly_coupled_fusion/lane/types.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
namespace lane
{
/**
 * @addtogroup lane
 * @{
 *
 */

/**
 * @brief define lane boundary matcher
 * @note
 * 1,in this class, we will define the calculation process of lane boundary matching.
 * 2,in this class, we declare a class of EmSolver.
 */
class LaneBoundaryMatcher
{
public:
    using Ptr      = std::shared_ptr<LaneBoundaryMatcher>;
    using ConstPtr = std::shared_ptr<const LaneBoundaryMatcher>;
    /**
     * @brief define EmSolver parameters
     *
     */
    struct EmSolverParameters
    {
        uint32_t min_num_iterations;  ///< minimum number of iterations
        uint32_t max_num_iterations;  ///< maximum number of iterations
        Scalar   max_solver_time;     ///< maximum solution time (unit: second)
        Scalar   gradient_tolerance;  ///< Tolerance of descent gradient, if the descent gradient is less than this
                                      ///< value, the optimization iteration stops

        ///< threshold of association probability for adding cost function, note: the purpose of setting this parameter
        ///< is to speed up the solver.
        Scalar threshold_of_association_probability_for_adding_cost_function;

        ///< number of iteration of solver tends to converge, note: the purpose of setting this parameter is to
        ///< remove the wrong detection information.
        uint32_t number_of_iteration_of_solver_tends_to_converge;

        ///< max distance between detected lane boundary and map lane boundary (unit: metre), if the distance between
        ///< the two lane boundaries with the strongest correlation is greater than this value, we will delete the
        ///< detected lane boundary information.
        Scalar max_distance_between_detected_lane_boundary_and_map_lane_boundary;

        ///< weight value of prior information, the greater the value, the greater the value of the prior information
        ///< weight.
        Scalar prior_information_weight;

        /**
         * @brief generate example parameters
         *
         * @return Parameters example parameters
         */
        static EmSolverParameters GenerateExample();

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static EmSolverParameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief output stream for EmSolver parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, EmSolverParameters const& parameters);
    };

    /**
     * @brief define parameters
     *
     */
    struct Parameters
    {
        ///< control parameter of log info
        bool_t verbose;
        ///< projection length threshold of 3d pose x-axis on X-O-Y plane.
        Scalar minimum_projection_length_of_3d_axis;

        /**
         * @brief parameters for detected lane boundary
         *
         */
        ///< The length threshold of the detected lane boundary(unit: m). if lenght of detected lane boundary is smaller
        ///< it, the detected lane boundary is invalid.
        Scalar minimum_length_of_detected_lane_boundary;
        ///< max sampling length of detected lane boundary, (unit: m)
        Scalar maximum_sampling_length;
        ///< max sampling length of detected lane boundary when the car on the side road (unit: m)
        Scalar maximum_sampling_length_on_side_road;
        ///< sample length interval of detected lane boundary. (unit: m)
        Scalar sampling_interval_distance;

        /**
         * @brief parameters for map lane boundary
         *
         */
        ///< distance threshold from vehicle to lane boundary. (unit: m)
        Scalar maximum_distance_from_vehicle_to_lane_boundary;
        ///< distance threshold of lane boundary in front of map. (unit: m)
        Scalar minimum_distance_of_lane_boundary_in_front_of_map;
        ///< distance threshold of lane boundary in rear of map. (unit: m)
        Scalar minimum_distance_of_lane_boundary_in_rear_of_map;

        /**
         * @brief parameters for variance setting of sampling points
         *
         */
        ///< base variance of lane boundary detection
        Scalar detection_variance;
        ///< piecewise value of lateral distance variance scale calculation function, this value is a segmented value
        ///< that sets the variance scale for the distance from the detected lane boundary to the body.
        ///< eg. piecewise_value_of_lateral_distance_variance_scale_calculation_function = 1.5, then the variance scale
        ///< of distance within 1.5 is 1. if distance = 3, the scale = (3/1.5)^2 = 4.
        Scalar piecewise_value_of_lateral_distance_variance_scale_calculation_function;
        ///< piecewise value of detection length variance scale calculation function, this value is a segmented value
        ///< that sets the variance scale for the length of detected lane boundary.
        ///< eg. piecewise_value_of_longitudinal_distance_variance_scale_calculation_function = 10, when the detection
        ///< length is greater than 10, the variance scale is 1, if length = 5, the scale = (2.0 - 5 / 10)^2 = 2.25.
        Scalar piecewise_value_of_longitudinal_distance_variance_scale_calculation_function;
        ///< scale value of longitudinal distance variance calculation function, this value is the variance scale factor
        ///< based on the square of the distance between the detected lane boundary point and the front of the vehicle.
        ///< eg. scale_value_of_longitudinal_distance_variance_calculation_function = 0.1, distance = 5,
        ///< scale = 1.0 + 0.1*5^2 = 3.5.
        Scalar scale_value_of_longitudinal_distance_variance_calculation_function;

        /**
         * @brief detected lane boundary self inspection parameters
         *
         */
        ///< max distance between detected lane boundary and map lane boundary in initial state. (unit: m) If the
        ///< distance between the two lane boundaries is greater than this value, the detected lane boundary will be
        ///< considered invalid.
        Scalar maximum_distance_between_detected_lane_boundary_and_map_lane_boundary_in_initial_state;

        /**
         * @brief other parameters
         *
         */
        ///< distance threshold of lane boundary matching. (unit: m) we determine the data association pair according to
        ///< the distance matrix returned from EmSolver. When the association distance of the best match is less than
        ///< this value, we consider it as an effective association.
        Scalar matching_distance_threshold;
        ///< emalgorihmer parameters
        EmSolverParameters emsolver_parameters;
        ///< curve fitter parameters
        CurveFitter::Parameters curve_fitter_parameters;

        /**
         * @brief generate example parameters
         *
         * @return Parameters example parameters
         */
        static Parameters GenerateExample();

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);

        /**
         * @brief output stream for lane boundary matcher parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters);
    };

    /**
     * @brief Construct a new Lane Boundary Matcher
     *
     * @param _parameters parameters
     */
    LaneBoundaryMatcher(Parameters const& _parameters);

    /**
     * @brief Destroy the Lane Boundary Matcher
     *
     */
    ~LaneBoundaryMatcher() = default;

    /**
     * @brief run lane boundary matcher main function
     * @details
     * 1,vehicle pose3d -> pose2d.
     * 2,the detected lane boundaries are discretized into points, and the variance of each point is set.
     * 3,processing map lane boundary information, it includes, screening and fitting map lane boundaries.
     * 4,EmSolver computes lane boundaries association.
     * 5,determine the final lane boundary association.
     * @param detected_lane_raw_measurement lane boundary detection raw data
     * @param multi_map_lane_boundary_points map lane boundary points.
     * @param is_on_main_road is it on the main road
     * @param lane_boundary_association lane boundary association result, the first value of each element in the
     * container represents the index of the detected lane boundary, and the second value represents the index of the
     * map lane boundary.
     * @param  association_probability association probability corresponding to lane_boundary_association, Its size is
     * equal to that of lane_boundary_association.
     * @return bool_t return false if can not get data association
     */
    bool_t Run(LaneRawMeasurement const&         detected_lane_raw_measurement,
               std::vector<MapPointsType> const& multi_map_lane_boundary_points, bool_t const is_on_main_road,
               std::vector<std::pair<uint32_t, uint32_t>>& lane_boundary_association,
               std::vector<Scalar>&                        association_probability) const;

protected:
    /**
     * @brief define detected lane boundary points type
     *
     */
    struct DetectedLaneBoundaryPointsType
    {
        bool_t                  is_valid = true;         ///< valid flag, default true.
        Scalar                  lane_boundary_variance;  ///< variance of lane boundary
        std::vector<Point2Type> lane_boundary_points;    ///< points vector of lane boundary
        std::vector<Scalar>     points_variance;         ///< points variance
        std::vector<Scalar>     points_weight;           ///< points weight, note: sum of all these weight is 1.
    };

    class EmSolver;
    using EmSolverPtr = std::shared_ptr<EmSolver>;

    /**
     * @brief Check the validity of the input data
     *
     * @param detected_lane_raw_measurement lane boundary detection raw data
     * @param multi_map_lane_boundary_points map lane boundary points.
     * @return bool_t return false if the inpute data is invalid
     */
    bool_t checkInputData(LaneRawMeasurement const&         detected_lane_raw_measurement,
                           std::vector<MapPointsType> const& multi_map_lane_boundary_points) const;

    /**
     * @brief convert pose3d to pose2d
     * @note
     * in this function, Pose2d represents the 2D pose of the vehicle in the world coordinate system, and
     * pose2d_covariance_in_Temporary represents the pose uncertainty of the vehicle's 2D pose in the temporary
     * coordinate system.
     * @details
     * 1,project the x-axis of the vehicle pose3d onto the X-O-Y plane in the world coordinate system and normalize.
     * 2,the x-axis has been determined. according to the right-hand rule, determined the y-axis.
     * 3,in the process of covariance transformation, we do not consider the correlation between variables, so we only
     *   take the diagonal elements of pose3d covariance matrix to form a new pose2d covariance matrix.
     * @param pose3d 3d pose
     * @param pose3d_covariance 3d pose covariance
     * @param pose2d 2d pose
     * @param pose2d_covariance_in_temporary 2d pose covariance in temporary coordinate system, the order of the
     * covariance is (x, y, yaw)
     * @return bool_t return false if the projection length of the x-axis of the 3d pose on the X-O-Y plane is less than
     * the minimum_projection_length_of_3d_axis.
     */
    bool_t convertPose3dToPose2d(Pose3Type const& pose3d, Matrix6Type const& pose3d_covariance, Pose2Type& pose2d,
                                 Matrix3Type& pose2d_covariance_in_temporary) const;

    /**
     * @brief convert lane boundary to detected lane boundary points
     * @details
     * 1,here we are going to separate the lane curves by a certain distance.
     * 2,we will project these points into the 2d vehicle coordinate system.
     * 3,compute sigma of these points. See computeDetectedLaneBoundaryPointSigma function for details.
     * 4,compute variance of this lane boundary. variance = 1/(1/sigma0^2 + 1/sigma1^2 + 1/sigma2^2 + ...)
     * 5,compute weight of these points, note: sum of all these weight is 1.
     * @param detected_lane_boundary detected lane boundary
     * @param maximum_sampling_length maximum sampling length
     * @param wR3b vehicle 3d rotation
     * @param wR2t vehicle 2d rotation
     * @param pose2d_covariance_in_temporary vehicle pose covariance in temporary coordinate system
     * @param lane_boundary_points converted lane boundary type
     * @return bool_t return false if it can not be converted.
     */
    bool_t convertLaneBoundaryToDetectedLaneBoundaryPoints(CameraLaneBoundaryType const& detected_lane_boundary,
                                                           Scalar const maximum_sampling_length, Rot3Type const& wR3b,
                                                           Rot2Type const&    wR2t,
                                                           Matrix3Type const& pose2d_covariance_in_temporary,
                                                           DetectedLaneBoundaryPointsType& lane_boundary_points) const;

    /**
     * @brief compute detected lane boundary point variance
     * @details
     * 1,we will give the variance of the detection point in the temporary coordinate system(the coordinate system of
     *   the initial position of the vehicle) according to the pose variance of the vehicle.
     * 2,we will compute a variance scale coefficient according to the length of the detected lane boundary and the
     * distance to the vehicle.
     * @param pose2d_covariance_in_temporary vehicle pose covariance in temporary coordinate system
     * @param detected_lane_boundary_point detected lane boundary point
     * @param detection_scale detection scale which is computed from function computeDetectionVarianceScale
     * @return Scalar return lane boundary point variance
     */
    Scalar computeVarianceOfDetectedLaneBoundaryPoint(Matrix3Type const& pose2d_covariance_in_temporary,
                                                      Point2Type const&  detected_lane_boundary_point,
                                                      Scalar const       detection_scale) const;

    /**
     * @brief compute detection variance scale
     *
     * @param lateral_distance lateral distance from lane boundary to vehicle
     * @param detection_length the length of the detected lane boundary
     * @return Scalar the scale of detection variance
     */
    Scalar computeDetectionVarianceScale(Scalar const lateral_distance, Scalar const detection_length) const;

    /**
     * @brief process map lane boundary information
     * @note in this function， we will have the operation of lane boundary screening and lane boundary fitting. the
     * details of its implementation are in function isMapLaneBoundaryValid and class CurveFitter.
     * @param map_lane_boundary map lane boundary points
     * @param wT2b vehicle pose
     * @param map_lane_boundary_curve fitted map lane boundary
     * @return bool_t return false if map lane boundary is invalid or lane boundary can not be fitted.
     */
    bool_t processMapPoints(MapPointsType const& map_lane_boundary, Pose2Type const& wT2b,
                            VectorXType& map_lane_boundary_curve) const;

    /**
     * @brief Get the Valid Map Lane Boundary In Vehicle Coordinate object
     * @details in this function, we will check the validity of the map lane boundary,and get the valid map lane
     * boundary points in vehicle coordinate.
     * so we will do the follow step:
     * 1. transform map lane boundary points to vehicle coordinate
     * 2. find the nearest cross point between each map boundary points and y-axis
     * 3. search the valid map lane boundary range,which must meet the following requirements:
     * - map lane boundary point must at the range between min rear param and min front param from params
     * - the distance from ending map lane points to nearest cross point must bigger than the setting distance by params
     * param
     * 4. get valid map lane boundary points in vehicle coordinate
     * @param[in] map_lane_boundary map lane boundary points vector
     * @param[in] wT2b vehicle pose
     * @return std::vector<Point2Type> if the map lane boundary is valid,return the valid map lane boundary in vehicle
     * coordinate,otherwise reture empty points vector
     */
    std::vector<Point2Type> getValidMapLaneBoundaryInVehicleCoordinate(MapPointsType const& map_lane_boundary,
                                                                       Pose2Type const&     wT2b) const;

    /**
     * @brief transform map lane boundary to temporary coordinate system
     *
     * @param[in] map_lane_boundary map lane boundary
     * @param[in] wT2b vehicle pose
     * @param[out] points map lane boundary points in temporary coordinate system
     * @return bool_t return false if convert failed.
     */
    bool_t transformMapLaneBoundaryPointsToTemporaryCoordinateSystem(MapPointsType const&     map_lane_boundary,
                                                                     Pose2Type const&         wT2b,
                                                                     std::vector<Point2Type>& points) const;

    /**
     * @brief  find the nearest cross point to vehicle.
     * @note in this function,we define the valid y-axis line segment which create by params,and cross with each line segment which between with map points.
     * and than find the nearest cross point to vehicle.
     * @param[in] map_points_in_temporary_coordinate_system map lane boundary points in temporary coordinate system
     * @param[out] nearest_index_pair  both sides index  of nearest cross point if return true
     * @param[out] nearest_cross_point the result nearest cross point if return true
     * @return bool_t return true if find the nearest cross point
     */
    bool_t findNearestCrossPointToVehicle(std::vector<Point2Type> const& map_points_in_temporary_coordinate_system,
                                          std::pair<uint32_t, uint32_t>& nearest_index_pair,
                                          Point2Type&                    nearest_cross_point) const;

    /**
     * @brief   search from nearest cross point to ending point,to get the nearest valid index
     * @note in this fuction, we will search from nearest cross point to ending point,and accumulate the distance of
     * each seaching point.when the accumulate distance is bigger than the min_distance which setting by params,then
     * return true and get the valid index point index ,other return false.
     * noting that this function can search to front point or back point,which depend on is_search_front.
     * @param[in] start_index the first index of point which need to be accumulate.
     * @param[in] nearest_cross_point the nearest cross point which on the map point line segment
     * @param[in] map_points_in_temporary_coordinate_system the map points in temporary coordinate system,and it has been
     * sorted,front point is to rear of car,back point is to front of car.
     * @param[in] is_search_to_front to define the search direction,true is from vehicle to front ,false is from vehicle to rear.
     * @param[out] valid_index the valid point index result if return true.
     * @return bool_t return true if accumulate distance is bigger than the param,otherwise return false.
     */
    bool_t searchValidIndexRangeInMapBoundary(uint32_t const start_index, Point2Type const& nearest_cross_point,
                                              std::vector<Point2Type> const& map_points_in_temporary_coordinate_system,
                                              bool_t const is_search_to_front, uint32_t& valid_index) const;

    /**
     * @brief check whether the detected lane boundaris is valid and remove the invalid lane boundaries.
     *
     * @param map_lane_boundary_curves curves of lane boundaries of map
     * @param multi_detected_lane_boundary_points detected lane boundaries
     * @param valid_detected_lane_boundary_index valid index of detected lane boundary
     * @return bool_t now only return true
     */
    bool_t checkDetectedLaneBoundariesAndRemoveInvalidOnes(
        std::vector<VectorXType> const&              map_lane_boundary_curves,
        std::vector<DetectedLaneBoundaryPointsType>& multi_detected_lane_boundary_points,
        std::vector<uint32_t>&                       valid_detected_lane_boundary_index) const;

    /**
     * @brief mark detected lane boundaries that are far from the map lane boundaries
     *
     * @param map_lane_boundary_curves curves of lane boundaries of map
     * @param multi_detected_lane_boundary_points detected lane boundaries
     * @return bool_t return false if map_lane_boundary_curves is empty.
     */
    bool_t markDetectedLaneBoundariesFarFromMapLaneBoundaries(
        std::vector<VectorXType> const&              map_lane_boundary_curves,
        std::vector<DetectedLaneBoundaryPointsType>& multi_detected_lane_boundary_points) const;

    /**
     * @brief compute the distance between detected lane boundary and map lane boundary
     * @details
     * distance = weight_0*p_0_to_line + weight_1*p_1_to_line + weight_2*p_2_to_line + ...
     * weight_i is the weight of the i-th detected lane boundary point
     * p_i_to_line is the distance from the i-th detected lane boundary point to the map lane boundary
     * @param detected_lane_boundary detected lane boundary
     * @param map_lane_boundary map lane boundary
     * @param distance distance between detected lane boundary and map lane boundary
     * @return bool_t return false if detected lane boundary points is empty.
     */
    bool_t computeDistanceBetweenDetectedLaneBoundaryAndMapLaneBoundary(
        DetectedLaneBoundaryPointsType const& detected_lane_boundary, VectorXType const& map_lane_boundary,
        Scalar& distance) const;

    /**
     * @brief remove invalid detected lane boundaries
     *
     * @param multi_detected_lane_boundary_points detected lane boundaries
     * @param valid_detected_lane_boundary_index valid index of detected lane boundary
     * @return bool_t return false if the two input vectors are different in size.
     */
    bool_t removeInvalidDetectedLaneBoundaries(
        std::vector<DetectedLaneBoundaryPointsType>& multi_detected_lane_boundary_points,
        std::vector<uint32_t>&                       valid_detected_lane_boundary_index) const;

    /**
     * @brief find best match
     *
     * @param association_matrix association matrix
     * association_matrix = p00 p01 p02 p03 ...
     *                      p10 p11 p12 p13 ...
     *                      p20 p21 p22 p23 ...
     *                      ...
     * the number of rows of the matrix represents the index of the detected lane boundary, and the number of cols of
     * the matrix represents the index of the map lane boundary.
     * @param distance_matrix distance matrix
     * distance_matrix = d00 d01 d02 d03 ...
     *                   d10 d11 d12 d13 ...
     *                   d20 d21 d22 d23 ...
     *                   ...
     * the number of rows of the matrix represents the index of the detected lane boundary, and the number of cols of
     * the matrix represents the index of the map lane boundary.
     * @param valid_detected_lane_boundary_index valid index of detected lane boundary
     * @param valid_map_lane_boundary_index valid index of map lane boundary
     * @param lane_boundary_association lane boundary association pair
     * @param  association_probability association probability corresponding to lane_boundary_association
     * @return bool_t return false if not found.
     */
    bool_t findBestMatch(MatrixXType const& association_matrix, MatrixXType const& distance_matrix,
                         std::vector<uint32_t> const&                valid_detected_lane_boundary_index,
                         std::vector<uint32_t> const&                valid_map_lane_boundary_index,
                         std::vector<std::pair<uint32_t, uint32_t>>& lane_boundary_association,
                         std::vector<Scalar>&                        association_probability) const;

private:
    Parameters       parameters_;        ///< parameters
    CurveFitter::Ptr curve_fitter_ptr_;  ///< pointer of curve fitter
    EmSolverPtr      em_solver_ptr_;     ///< pointer of em solver

};  // class LaneBoundaryMatcher

/**
 * @brief define em solver
 * @note
 * 1, L(x) = prior(x) + sum(i)sum(j)sum(k)(pij*log(P(zik|aij, x))). this formula is the expected function,
 *    x means vehicle pose
 *    prior(x) means prior pose of vehicle
 *    i is the index of detected lane boundary,
 *    j is the index of map lane boundary,
 *    k is the index of detected lane boundary points,
 *    pij means matching probability between the i-th detected lane boundary and the j-th map lane boundary,
 *    zik means observation of the k-th point in the i-th detected lane boundary
 *    aij means the i-th detected lane boundary is associated with the j-th map lane boundary.
 *    P(zik|aij, x) means the observation probability of the k-the point in the i-th detected lane boundary when the
 *                  vehicle pose is x and the i-th lane boundary is associated with the j-th map lane boundary. this
 *                  probability is in the form of Gaussian distribution.
 * 2, our goal is to maximize this expectation function, because this function is nonlinear, we need to solve it
 *    iteratively.
 * 3, E step is to construct the linear expression of the expected function, and M step is to maximize the
 *    linear expected function.
 * 4, the optimization process is similar to the GaussNewton method for solving the least squares problem.
 *    residual = f(x, aij) - zik
 *    Jacobian = delta(residual)/delta(x)
 *    H = sum(i)sum(j)sum(k)(Jacobian^T* weight * Jacobian)
 *    b = sum(i)sum(j)sum(k)(Jacobian^T* weight * residual)
 *    weight = pij / variance. where pij has been explained above, and variance is detection variance.
 *    delta = -H^-1*b
 *    x = x + delta
 */
class LaneBoundaryMatcher::EmSolver
{
    friend class LaneBoundaryMatcher;

public:
    /**
     * @brief Construct a new Em solver
     *
     * @param _parameters parameters
     */
    EmSolver(EmSolverParameters const& _parameters) : parameters_(_parameters)
    {
    }

    /**
     * @brief Destroy the Em solver
     *
     */
    ~EmSolver() = default;

    /**
     * @brief Get the Association Matrix
     * @note the data association is based on the distance between the detected lane boundary and the map lane boundary.
     * @param multi_detected_lane_boundary_points detected lane boundary points vector
     * @param map_lane_boundary_curves map lane boundary polynomial vector
     * @param pose_covariance vehicle pose covariance
     * @param association_matrix association matrix, the number of rows represents the number of lane boundaries
     * detected,
     * @param distance_matrix the number of cols represents the number of map lane boundaries.
     * @return bool_t return false if all lane boundaries can not build association.
     */
    bool_t Run(std::vector<DetectedLaneBoundaryPointsType> const& multi_detected_lane_boundary_points,
               std::vector<VectorXType> const& map_lane_boundary_curves, Matrix3Type const& pose_covariance,
               MatrixXType& association_matrix, MatrixXType& distance_matrix);

protected:
    /**
     * @brief define solver state
     *
     */
    struct State
    {
        TicTocTimer solver_timer;  ///< solver timer
        uint32_t    iterations;    ///< iterations of solver
        Pose2Type   tT2b;          ///< relative pose between temporary coordinate system and optimized car body
                                   ///< coordinate system
        MatrixXType                          association_matrix;  ///< association matrix
        MatrixXType                          distance_matrix;     ///< distance matrix
        std::vector<std::vector<Point2Type>> multi_detected_lane_boundary_points_after_optimized;  ///< optimized
                                                                                                   ///< detected lane
                                                                                                   ///< boundary points
        std::vector<bool_t> multi_detected_lane_boundaries_states;  ///< state of detected lane boundary, false means
                                                                    ///< false detection.
    };

    /**
     * @brief main function of em solver
     *
     * @param pose_covariance prior vehicle pose covariance
     * @param solver_state the state of solver
     * @return bool_t return false if algorithm can not complete.
     */
    bool_t run(Matrix3Type const& pose_covariance, State& solver_state) const;

    /**
     * @brief add prior factor
     *
     * @param solver_state the state of solver
     * @param pose_information_matrix vehicle prior pose information matrix
     * @param H_matrix hessian matrix
     * @param b_vector b vector
     */
    void addPriorInformation(State const& solver_state, Matrix3Type const& pose_information_matrix,
                             Matrix3Type& H_matrix, Vector3Type& b_vector) const;

    /**
     * @brief E step
     * @details
     * 1, compute distribution of hidden variables(lane boundary association).
     * 2, build expectation function.
     * @param solver_state the state of solver
     * @param H_matrix hessian matrix
     * @param b_vector b vector
     * @return bool_t return false if can not be computed.
     */
    bool_t executeEstep(State& solver_state, Matrix3Type& H_matrix, Vector3Type& b_vector) const;

    /**
     * @brief check size of all data
     *
     * @param solver_state the state of solver
     * @return bool_t return false if the size of all data dose not meet the requirements of the algorithm.
     */
    bool_t checkDataSize(State const& solver_state) const;

    /**
     * @brief compute distance matrix
     * @note
     * 1, we will compute the distance between each detected lane boundary and each map lane boundary.
     * 2, distance = point0_to_line_distance * point0_weight + point1_to_line_distance * point1_weight + ...
     * @param solver_state the state of solver
     */
    void computeDistanceMatrix(State& solver_state) const;

    /**
     * @brief compute distance from detected lane boundary to map lane boundaries.
     * @details
     * expected_distance = weight0*distance0 + weight1*distance1 + ...
     * @param multi_lane_boundary_points detected lane boundary points vector
     * @param multi_detected_lane_boundary_points_weight detected lane boundary points weight
     * @param expected_distance_vector expected distance from detected lane boundary to map lane boundaries
     * @return bool_t return false if can not computed.
     */
    bool_t computeDistanceBetweenTwoLine(std::vector<Point2Type> const& multi_lane_boundary_points,
                                         std::vector<Scalar> const&     multi_detected_lane_boundary_points_weight,
                                         std::vector<Scalar>&           expected_distance_vector) const;

    /**
     * @brief compute association matrix
     * @note Here, we assume that lane association is independent, different detected lane boundaries can be associated
     * with the same map lane boundary. So our data association distribution only depends on the distance between the
     * detected lane boundary and the map lane boundary.
     * @param solver_state the state of solver
     */
    void computeAssociationMatrix(State& solver_state) const;

    /**
     * @brief reject unreasonable detected lane boundary
     * @note
     * 1, reject lane boundaries which are false detection.
     * 2, this fuction has to be executed when the algorithm tends to converge.
     * 3, we assume that the number of correct lane boundary detection is more than the number of wrong lane boundary
     * detection.
     * @param solver_state the state of solver
     * @return bool_t return false if no lane boundaries to be removed.
     */
    bool_t rejectUnreasonableDetectedLaneBoundary(State& solver_state) const;

    /**
     * @brief compute cost function
     *
     * @param solver_state the state of solver
     * @param H_matrix hessian matrix
     * @param b_vector b vector
     */
    void computeCostfunction(State const& solver_state, Matrix3Type& H_matrix, Vector3Type& b_vector) const;

    /**
     * @brief compute Jacobian and residual of the distance between detected lane boundary point and map lane
     * boundaries.
     * @details
     * residual = f(point_x) - point_y.
     * Jacobian = delta(residual)/delta(pose).
     * H += Jacobian^T * (weight/variance) * Jacobian
     * b += Jacobian^T * (weight/variance) * residual
     * @param solver_state the state of solver
     * @param detected_point_in_body_coordinate detected lane boundary point in body coordinate system
     * @param detected_point_in_temporary_coordinate detected lane boundary point in temporary coordinate system
     * @param variance variance of point
     * @param line_to_line_matching_probability lane boundary association distribution
     * @param H_matrix hessian matrix
     * @param b_vector b vector
     */
    void computePointToCurveMatchInfo(State const& solver_state, Point2Type const& detected_point_in_body_coordinate,
                                      Point2Type const& detected_point_in_temporary_coordinate, Scalar const variance,
                                      VectorXType const& line_to_line_matching_probability, Matrix3Type& H_matrix,
                                      Vector3Type& b_vector) const;

    /**
     * @brief Get the Polynomial Value
     *
     * @param coefficients lane boundary curve polynomial coefficients
     * @param x the value of the argument
     * @return Scalar the value of function
     */
    inline Scalar getPolynomialValue(VectorXType const& coefficients, Scalar const x) const
    {
        Scalar result = 0.0;
        Scalar x_exp  = 1.0;

        for (size_t i = 0; i < coefficients.GetSize(); i++)
        {
            result += x_exp * coefficients.At(i);
            x_exp *= x;
        }

        return result;
    }

    /**
     * @brief Get the Polynomial Derivative
     * @param coefficients lane boundary curve polynomial coefficients
     * @param x the value of the argument
     * @return Scalar derivative value of function
     */
    inline Scalar getPolynomialDerivative(VectorXType const& coefficients, Scalar const x) const
    {
        Scalar result = 0.0;
        Scalar x_exp  = 1.0;

        for (size_t i = 1u; i < coefficients.GetSize(); i++)
        {
            result += x_exp * coefficients.At(i) * static_cast<Scalar>(i);
            x_exp *= x;
        }

        return result;
    }

    /**
     * @brief M step
     * @details delta = -H^-1*b.
     * @param H_matrix hessian matrix
     * @param b_vector b vector
     * @param delta optimization state increment
     * @return bool_t return false if the hessian matrix is not of rank
     */
    bool_t executeMstep(Matrix3Type const& H_matrix, Vector3Type const& b_vector, Vector3Type& delta) const;

    /**
     * @brief update solver state
     *
     * @param delta change value of optimization state
     * @param solver_state the state of solver
     * @return bool_t return false if the module of delta too large.
     */
    bool_t updateState(Vector3Type const& delta, State& solver_state) const;

private:
    EmSolverParameters                          parameters_;                           ///< parameters
    std::vector<DetectedLaneBoundaryPointsType> multi_detected_lane_boundary_points_;  ///< detected lane boundary
                                                                                       ///< points vector
    std::vector<VectorXType> map_lane_boundary_curves_;  ///< map lane boundary polynomial vector

};  // class EmSolver

/**
 * @}
 *
 */
}  // namespace lane
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_LANE_BOUNDARY_MATCHER_H_
