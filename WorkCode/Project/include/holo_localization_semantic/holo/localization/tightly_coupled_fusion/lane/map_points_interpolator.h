/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_points_interpolator.h
 * @brief the definition of map points interpolator class
 * @author Yuan Shuai
 * @author Zhang Yelin(zhangyelin@holomatic.com)
 * @date 2020-07-11
 */

#ifndef HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_MAP_POINTS_INTERPOLATOR
#define HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_MAP_POINTS_INTERPOLATOR

#include <holo/localization/tightly_coupled_fusion/lane/types.h>
#include <holo/numerics/spline.h>

namespace holo
{
namespace localization
{
namespace tightly_coupled_fusion
{
namespace lane
{
/**
 * @brief This class defines map points interpolator for interpolationed map points
 *
 */
class MapPointsInterpolator
{
public:
    /**
     * @brief define type name
     */
    using MapPoint   = Point3Type;
    using MapPoints  = std::vector<MapPoint>;
    using PoseSpline = holo::Spline3;

    /**
     * @brief define shared pointer type name
     */
    using Ptr           = std::shared_ptr<MapPointsInterpolator>;
    using ConstPtr      = std::shared_ptr<const MapPointsInterpolator>;
    using PoseSplinePtr = PoseSpline::Ptr;

    /**
     * @brief Define parameters
     *
     */
    struct Parameters
    {
        /// @brief max distance of lane for use, unit(m)
        Scalar max_distance = 80.0;

        /// @brief map point interval, unit(m)
        Scalar map_point_interval = 1.0;

        /// @brief control parameter of log info
        bool_t verbose = false;

        /**
         * @brief generate example parameters
         *
         * @return Parameters example parameters
         */
        static Parameters GenerateExample()
        {
            Parameters params;

            params.max_distance       = 80.0;
            params.map_point_interval = 1.0;
            params.verbose            = false;

            return params;
        }

        /**
         * @brief output stream for lane processor parameters
         *
         * @param[in] os std::ostream&
         * @param[in] parameters parameters
         * @return std::ostream& contains content of the given parameters
         */
        friend std::ostream& operator<<(std::ostream& os, Parameters const& parameters)
        {
            os << "MapPointsInterpolator::Parameters :"
               << "\n max_distance = " << parameters.max_distance
               << "\n map_point_interval = " << parameters.map_point_interval << "\n verbose = " << parameters.verbose
               << std::endl;
            return os;
        }

        /**
         * @brief Static method to load parameters from yaml
         *
         * @param[in] node Yaml node
         * @return the loaded parameters
         */
        static Parameters LoadFromYaml(holo::yaml::Node const& node);
    };

    /**
     * @brief disable the default constructor
     */
    MapPointsInterpolator() = delete;

    /**
     * @brief constructor
     * @param[in] parameters input parameters
     */
    MapPointsInterpolator(const Parameters& parameters) : parameters_(parameters){};

    /**
     * @brief default destructor
     */
    virtual ~MapPointsInterpolator();

    /**
     * @brief get interpolated map points
     * @param[in] map_points initial map points before interpolate
     * @return interpolated map points
     */
    MapPoints Run(const MapPoints& map_points) const;

private:
    /**
     * @brief initialize pose spline of map lane points
     * @param[in] map_points initial map points before interpolate
     * @param[out] arc_length arc length of input map points
     * @return initialized pose spline of map lane points
     */
    PoseSplinePtr initializePoseSpline(const MapPoints& map_points, Scalar& arc_length) const;

    /**
     * @brief interpolate map points
     * @param[in] pose_spline pose spline
     * @param[in] arc_length arc length of input map points
     */
    MapPoints interpolateMapPoints(const PoseSplinePtr& pose_spline, const Scalar arc_length) const;

    /// @brief parameters
    Parameters parameters_;

};  // MapPointsInterpolator class

}  // namespace lane
}  // namespace tightly_coupled_fusion
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TIGHTLY_COUPLED_FUSION_LANE_MAP_POINTS_INTERPOLATOR