
/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file 4pcs_base.h
 * @brief This header file defines fpcs base class
 * @author zhaojiaxing(zhaojiaxing@holomatic.com)
 * @author mengzhili(mengzhili@holomatic.com)
 * @date 2021-03-01
 */

#ifndef HOLO_3D_REGISTRATION_FPCS_BASE_H_
#define HOLO_3D_REGISTRATION_FPCS_BASE_H_

#include <array>
#include <random>
#include <utility>
#include <vector>

#include <holo/3d/common/common.h>
#include <holo/3d/registration/registration.h>

#include <holo/geometry/angle.h>
#include <holo/geometry/point3.h>
#include <holo/os/tictoc_timer.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief this class aims at implementation of the 4-points Congruent Sets (4PCS) algorithm base class.
 * @details Given two sets of points in 3-space, P(target) and Q(source), using an efficient method based on invariants,
 * to find the set of all 4-points in Q that can be matched by rigid transformation to a given set of 4-points in P
 * called a base. The algorithm allows registering raw noisy data, possibly contaminated with outliers, without
 * pre-filtering or denoising the data. Further, the  method significantly reduces the number of trials required to
 * establish a reliable registration between the underlying surfaces in the presence of noise, without any assumptions
 * about starting alignment.
 * @ref 4-points Congruent Sets for Robust Surface Registration Dror Aiger, Niloy J. Mitra, Daniel Cohen-Or ACM SIGGRAPH
 * 2008 and ACM Transaction of Graphics.
 *
 * @tparam PointSourceT source point type
 * @tparam PointTargetT target point type
 * @tparam Scalar scalar type
 */
template <typename PointSourceT, typename PointTargetT, typename Scalar = float64_t>
class FPCSBaseT : public RegistrationBaseT<PointSourceT, PointTargetT, Scalar>
{
public:
    typedef RegistrationBaseT<PointSourceT, PointTargetT, Scalar> Base;

    // point cloud
    using typename Base::PointCloudSource;
    using typename Base::PointCloudSourceConstPtr;
    using typename Base::PointCloudSourcePtr;
    using typename Base::PointCloudTarget;
    using typename Base::PointCloudTargetConstPtr;
    using typename Base::PointCloudTargetPtr;

    // kdtree
    using typename Base::KdTreeSource;
    using typename Base::KdTreeSourceConstPtr;
    using typename Base::KdTreeSourcePtr;
    using typename Base::KdTreeTarget;
    using typename Base::KdTreeTargetConstPtr;
    using typename Base::KdTreeTargetPtr;

    // numerics and geometry
    using typename Base::CorrespondenceVector;
    using typename Base::Matrix4Type;
    using typename Base::Point3Type;
    using typename Base::Pose3Type;
    using typename Base::Vector3Type;

    // member variables
    using Base::correspondences_;
    using Base::final_transformation_;
    using Base::indices_source_;
    using Base::indices_target_;
    using Base::max_iterations_;
    using Base::source_;
    using Base::target_;
    using Base::transformation_;
    using Base::transformation_estimation_;
    using Base::tree_source_;
    using Base::tree_target_;

    using PairsVector         = std::vector<std::pair<size_t, size_t>>;
    using DistributionType    = std::uniform_int_distribution<size_t>;
    using DistributionTypePtr = std::shared_ptr<DistributionType>;

    struct Parameters
    {
        /// @brief The delta for the LCP(Largest Common Point),used to extract pair distance, validate transformation
        Scalar delta = 5.0;
        /// @brief The factor on delta, give more tolerant on selected pairs and transformation validation
        Scalar distance_factor = 2.0;
        /// @brief Estimated overlap between source and target
        Scalar approximate_overlap = 0.5;
        /// @brief Expected overlap between source and target
        Scalar expected_overlap = 1.0;
        /// @brief The number of sample points in the source
        size_t sample_size = 200;
        /// @brief Proportion of target diameter that the fourth quadrilateral point not too close to the other 3
        Scalar base_diameter_fraction = 0.2;
        /// @brief Maximum normal difference
        Scalar max_normal_diff = -1;
        /// @brief Maximum translation distance
        Scalar max_translation_distance = -1;
        /// @brief Maximum angle between segments
        Scalar max_angle = -1;
        /// @brief The minimum distance threshold for selecting coplanar quadrilateral point
        Scalar min_distance_threshold = 0.05;
        /// @brief The Number of diameter trials
        size_t num_diameter_trials = 1000;
        /// @brief The compute time threshold in seconds
        float64_t max_time_elapsed = 100.0;
        /// @brief Verbose flag, print some intermediate result
        bool_t verbose = false;
    };

    /**
     * @brief Construct a new FPCSBase  object
     *
     * @param[in] params
     */
    FPCSBaseT(Parameters const& params = Parameters());

    /**
     * @brief Destroy the FPCSBase object
     *
     */
    virtual ~FPCSBaseT();

    /**
     * @brief Compute transformation
     *
     * @param[in] guess initial transformation between source and target point cloud
     * @return bool
     */
    virtual bool_t Compute(Pose3Type const& guess = Pose3Type::Identity()) override;

    /**
     * @brief Get the Best LCP (Largest Common Point) (overlap score in [0,1])
     *
     * @return Scalar
     */
    Scalar GetBestLCP() const;

protected:
    /**
     * @brief quadrilateral structure contains 4 points index of point cloud
     *
     */
    struct Quadrilateral
    {
        /**
         * @brief default constuctor
         *
         */
        Quadrilateral();

        /**
         * @brief constructor from point indices
         *
         * @param[in] vertex0 vertex 0 indices
         * @param[in] vertex1 vertex 1 indices
         * @param[in] vertex2 vertex 2 indices
         * @param[in] vertex3 vertex 3 indices
         * @param[in] invariant0 the first invariant of quadrilateral
         * @param[in] invariant1 the second invariant of quadrilateral
         */
        Quadrilateral(size_t const vertex0, size_t const vertex1, size_t const vertex2, size_t const vertex3,
                      Scalar const invariant0, Scalar const invariant1);

        /**
         * @brief operator =
         *
         * @param[in] q quadrilateral rhs
         * @return Quadrilateral&
         */
        Quadrilateral& operator=(Quadrilateral const& q);

        /**
         * @brief operator [] const
         *
         * @param[in] idx vertex id in quadrilateral, should be one of {0,1,2,3}
         * @return size_t vertex index in point cloud
         */
        size_t operator[](size_t const idx) const;

        /**
         * @brief operator []
         *
         * @param[in] idx vertex id in quadrilateral, should be one of {0,1,2,3}
         * @return size_t& vertex index in point cloud
         */
        size_t& operator[](size_t const idx);

        std::vector<size_t>   vertices;    ///< vertices indices vector
        std::array<Scalar, 2> invariants;  //< invariants

        friend std::ostream& operator<<(std::ostream& os, Quadrilateral const& q)
        {
            os << "[" << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << "]";
            return os;
        }
    };

protected:
    /**
     * @brief pre-computation before main algorithm
     *
     * @return bool_t
     */
    virtual bool_t preCompute() override;

    /**
     * @brief post-computation after main algorithm
     *
     * @return bool_t
     */
    virtual bool_t postCompute() override;

    /**
     * @brief selects a quadrilateral from source and returns the corresponding invariants and point indices
     *
     * @param[out] q quadrilateral base
     * @return bool_t return true if a quadrilateral has been found, false otherwise.
     */
    bool_t selectQuadrilateralBase(Quadrilateral& q);

    /**
     * @brief constructs pairs of points in source, corresponding to a single pair base in target
     *
     * @param[in] base_index1 the index of the first point in target
     * @param[in] base_index2 the index of the second point in target
     * @param[out] pairs a set of pairs in source that match the pair in target
     */
    virtual void extractPairs(size_t base_index1, size_t base_index2, PairsVector& pairs) const = 0;

    /**
     * @brief find congruent candidates in the source, given the invariants.
     *
     * @param[in] invariant1 the first invariant
     * @param[in] invariant2 the second invariant
     * @param[in] pairs1 the first set of pairs
     * @param[in] pairs2 the second set of pairs
     * @param[out] quadrilaterals the set of congruent quadrilateral.
     * @return bool_t return true if a non-empty set can be found. false otherwise
     */
    virtual bool_t findCongruentQuadrilaterals(Scalar invariant1, Scalar invariant2, PairsVector const& pairs1,
                                               PairsVector const&          pairs2,
                                               std::vector<Quadrilateral>& quadrilaterals) const = 0;

    /**
     * @brief loop over the set of congruent 4-points and test compatibility with the input base
     *
     * @param[in] quad_base quadrilateral base of target
     * @param[in] congruent_quads vector of candidate matches w.r.t the base
     * @return bool_t
     */
    bool_t tryCongruentSet(Quadrilateral const& quad_base, std::vector<Quadrilateral> const& congruent_quads);

    /**
     * @brief selects a random triangle in the target.
     * @details We apply a simple heuristic that works in most practical cases. The idea is to accept maximum distance,
     * computed by the estimate overlap, multiplied by the diameter of target, and try to have a triangle with all three
     * edges close to this distance. Wide triangles helps to make the transformation robust while too large triangles
     * makes the probability of having all points in the inliers small so we try to trade-off.
     *
     * @param[out] base1 triangle point index1 in target
     * @param[out] base2 triangle point index2 in target
     * @param[out] base3 triangle point index3 in target
     * @return bool_t true if select triangle success
     */
    bool_t selectRandomTriangle(size_t& base1, size_t& base2, size_t& base3);

    /**
     * @brief takes quadrilateral as a base, computes robust intersection point and returns the invariants corresponding
     * to the two selected lines. reorder quadrilateral indices in target_
     *
     * @param[in,out] q quadrilateral in target point cloud
     */
    void tryQuadrilateral(Quadrilateral& q);

    /**
     * @brief compute the closest points on both segments, the corresponding invariants and the distance between the
     * closest points.
     *
     * @param[in] p1 the first point of segment one
     * @param[in] p2 the second point of segment one
     * @param[in] q1 the first point of segment two
     * @param[in] q2 the second point of segment two
     * @param[out] invariant1 the first invariant
     * @param[out] invariant2 the second invariant
     * @param[out] dist the smallest distance between two segments
     */
    void distSegmentToSegment(PointTargetT const& p1, PointTargetT const& p2, PointTargetT const& q1,
                              PointTargetT const& q2, Scalar& invariant1, Scalar& invariant2, Scalar& dist);

    /**
     * @brief verify a given transformation by computing the fitness between source and target point cloud within given
     * distance
     *
     * @param[in] transformation the current transformation between source and target point cloud
     * @return Scalar the current overlap(LCP)
     */
    Scalar verify(Pose3Type const& transformation) const;

protected:
    /// @brief params
    Parameters params_;

    /// @brief the quadrilateral point index in target point cloud
    Quadrilateral quad_base_;

    /// @brief estimated diameter of the target point cloud
    Scalar diameter_target_;

    /// @brief maximum base diameter. It is computed from the diameter of target and the estimated overlap and used to
    /// limit the distance between the points in the base in target so that the probability to have all point in the
    /// base as inliers is increased.
    Scalar max_base_diameter_sqr_;

    /// @brief minimum base diameter fraction squared distance, used to make sure the fourth point not too close to the
    /// other three.
    Scalar base_diameter_fraction_sqr_;

    /// @brief the distance threshold for matching middle point due to the invariants
    Scalar coincidence_distance_limit_;

    /// @brief Maximal mean squared errors of a transformation calculated from a candidate match
    Scalar max_mse_;

    /// @brief Maximal squared point distance between source and target points to count as inlier.
    Scalar max_inlier_dist_sqr_;

    /// @brief the best LCP (Largest Common Point) fraction so far.
    Scalar best_lcp_;

    std::mt19937            re_;                ///> random engine
    DistributionTypePtr     distribution_;      ///> uniform int distribution
    std::function<size_t()> random_generator_;  ///> random function

    /// @brief record time
    TicTocTimer timer_;

};  // FourPCSBaseT

}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_REGISTRATION_FPCS_BASE_H_
