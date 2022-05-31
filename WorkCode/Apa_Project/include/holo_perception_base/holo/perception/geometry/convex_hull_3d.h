/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file convex_hull_3d.h
 * @brief This header file defines how points store convex3d class.
 * @author wupeng(wupeng@holomatic.com)
 * @date "2020-10-10"
 */

#ifndef HOLO_PERCEPTION_NEXT_CONVEX_HULL_3D_H_
#define HOLO_PERCEPTION_NEXT_CONVEX_HULL_3D_H_

#include <iomanip>
#include <numeric>
#include <vector>

#include <holo/core/types.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>

namespace holo
{
namespace perception
{
namespace next
{
/**
 * @addtogroup geometry.
 *
 * @{
 */

/**
 * @brief This class solve points to convex3d transform.
 *
 * @note the convex3d receive cloud of cluster to compute convex(2d)
 *       however store every convex range for max-3d coord.
 *
 *
 * @details This class receive points from clusters, compute every cluster to convex3d points.
 *
 * @tparam T data type.
 */

template <typename T>
class ConvexHull3DT
{
public:
    using Scalar           = T;
    using ConvexHull3DType = ConvexHull3DT<Scalar>;

    /**
     * @brief Default Constructor
     *
     */
    ConvexHull3DT() noexcept
      : center_(static_cast<Scalar>(0.0), static_cast<Scalar>(0.0), static_cast<Scalar>(0.0))
      , lowest_z_(static_cast<Scalar>(0.0))
      , highest_z_(static_cast<Scalar>(0.0))
      , length_z_(static_cast<Scalar>(0.0))
    {
    }

    /**
     * @brief Construct a new Convex 3d object
     *
     * @param[in] center the convex center x, y, z coord.
     * @param[in] lowest_z the convex with the scope lowest z coord.
     * @param[in] highest_z the convex with the scope highest z coord.
     * @param[in] length_z the convex with the scope depth z length.
     * @throw std::out_of_range, if the length_z is negative.
     */
    ConvexHull3DT(holo::geometry::Point3T<Scalar> center, Scalar lowest_z, Scalar highest_z, Scalar length_z,
                  std::vector<holo::geometry::Point3T<Scalar>>& convexhull_points)
      : center_(center)
      , lowest_z_(lowest_z)
      , highest_z_(highest_z)
      , length_z_(length_z)
      , convexhull_points_(convexhull_points)
    {
        if (length_z_ < static_cast<Scalar>(0.0))
        {
            throw std::out_of_range("the depth of z range should be greater than zero.");
        }
    }

    /**
     * @brief Copy constructor
     *
     * @param other
     */
    ConvexHull3DT(ConvexHull3DType const& other) noexcept;

    /**
     * @brief Move constructor
     *
     * @param other
     */
    ConvexHull3DT(ConvexHull3DType&& other) noexcept;

    /**
     * @brief Destructor
     *
     */
    ~ConvexHull3DT() = default;

    /**
     * @brief assignment operator
     *
     * @param convex3d
     * @return ConvexHull3DType&
     */
    ConvexHull3DType& operator=(ConvexHull3DType const& convex3d) noexcept;

    /**
     * @brief move assignment
     *
     * @param convex3d
     * @return ConvexHull3DType&
     */
    ConvexHull3DType& operator=(ConvexHull3DType&& convex3d) noexcept;

    /**
     * @brief Set the Center X object
     *
     * @param center_x
     */
    void SetCenterX(Scalar const center_x) noexcept
    {
        center_.SetX(center_x);
    }

    /**
     * @brief Set the Center Y object
     *
     * @param center_y
     */
    void SetCenterY(Scalar const center_y) noexcept
    {
        center_.SetY(center_y);
    }

    /**
     * @brief Set the Center Z object
     *
     * @param center_z
     */
    void SetMediumZ(Scalar const center_z) noexcept
    {
        center_.SetZ(center_z);
    }

    /**
     * @brief Set the Depth Z Lowest object
     *
     * @param lowest_z
     */
    void SetLowestZ(Scalar const lowest_z) noexcept
    {
        lowest_z_ = lowest_z;
    }

    /**
     * @brief Set the Depth Z Highest object
     *
     * @param highest_z
     */
    void SetHighestZ(Scalar const highest_z) noexcept
    {
        highest_z_ = highest_z;
    }

    /**
     * @brief Set the Depth Z object
     *
     * @param length_z, should be a non-negative value
     * @throw std::out of range throw, if height is negative
     */
    void SetLengthZ(Scalar const length_z)
    {
        if (length_z < static_cast<Scalar>(0.0))
        {
            throw std::out_of_range("the depth of z range should be greater than zero.");
        }
        length_z_ = length_z;
    }

    /**
     * @brief Get the Center X object
     *
     * @return Scalar
     */
    Scalar GetCenterX() const noexcept
    {
        return center_.GetX();
    }

    /**
     * @brief Get the Center Y object
     *
     * @return Scalar
     */
    Scalar GetCenterY() const noexcept
    {
        return center_.GetY();
    }

    /**
     * @brief Get the Center Z object
     *
     * @return Scalar
     */
    Scalar GetMediumZ() const noexcept
    {
        return center_.GetZ();
    }

    /**
     * @brief Get the Center Point object
     *
     * @return holo::geometry::Point3T<Scalar> const&
     */
    holo::geometry::Point3T<Scalar> const& GetCenterPoint() const noexcept
    {
        return center_;
    }

    /**
     * @brief Get the Depth Z Lowest object
     *
     * @return Scalar
     */
    Scalar GetLowestZ() const noexcept
    {
        return lowest_z_;
    }

    /**
     * @brief Get the Depth Z Highest object
     *
     * @return Scalar
     */
    Scalar GetHighestZ() const noexcept
    {
        return highest_z_;
    }

    /**
     * @brief Get the Length Z object
     *
     * @return Scalar
     */
    Scalar GetLengthZ() const noexcept
    {
        return length_z_;
    }

    /**
     * @brief Get the Convex Points object
     *
     * @return std::vector<holo::geometry::Point3T<Scalar>> const&
     */
    std::vector<holo::geometry::Point3T<Scalar>> const& GetConvexPoints() const noexcept
    {
        return convexhull_points_;
    }

    /**
     * @brief check whether convex3d is valid.
     *
     * @note valid convex3d the length_z should be greater than zero.
     *       If the length_z is equals to zero, you should compute the cluster,
     *       because it only initialize, shoule using compute function to get result.
     *
     * @return bool_t, true for valid, false for invalid.
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief the cluster 3d points to compute convex 2d points and the depth z message. the result is 3d straight
     * prism.
     *
     * @note the convexhull() is output convex-points is anti-clockwise direction default. meanwhile, the convex_cluster
     *       has store point3 with every point of size lowest/highest * 2, and the all convexhull points.
     * @example p0(a, b) p1(c, d) --> p0(a, b, lowest_z), p0(a, b, highest_z), p1(c, d, lowest_z), p1(c, d, highest_z)
     *
     * @param[in] cluster the input 3d points from cluster algorithm.
     * @param[out] convex_cluster the convex cluster points result. convex_cluster z message is default
     * lowest_z/highest_z.
     * @return bool_t true for conpute succ, false for compute failed.
     */
    bool_t Compute3dPrism(std::vector<holo::geometry::Point3T<Scalar>> const& cluster,
                          std::vector<holo::geometry::Point3T<Scalar>>&       convex_cluster);

    /**
     * @brief static compute 3d convexhull prism API.
     *
     * @param[in] cluster the input every cluster points.
     * @param[out] out the output convex .
     * @return bool_t true is valid, false is invalid.
     */
    static bool_t Compute(std::vector<holo::geometry::Point3T<Scalar>> const& cluster, ConvexHull3DType& out);

    /**
     * @brief output stream.
     *
     * @param[in] os std::ostream.
     * @param[in] in convex3d
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, ConvexHull3DType const& in)
    {
        os << in.ToString();
        return os;
    }

    /**
     * @brief convert string to readable.
     *
     * @return std::string
     */
    virtual std::string ToString() const
    {
        std::stringstream ss;
        ss << "ConvexHull3DT: center_x = " << std::setiosflags(std::ios_base::fixed) << std::setprecision(2)
           << center_.GetX() << ", center_y = " << center_.GetY() << ", center_z = " << center_.GetZ()
           << ", lowest_z = " << lowest_z_ << ", highest_z = " << highest_z_ << ", length_z = " << length_z_;
        return ss.str();
    }

private:
    holo::geometry::Point3T<Scalar> center_;  ///< center which store x, y center point coord, And convex range of all z
                                              ///< medium center point coord.

    Scalar lowest_z_;   ///< every cluster for search the lowest z coord.
    Scalar highest_z_;  ///< every cluster for search the highest z coord.
    Scalar length_z_;   ///< every cluster for convex3d-prism z-axis length.

    std::vector<holo::geometry::Point3T<Scalar>> convexhull_points_;  ///< every cluster for store convexhull 3d points.
};

/**
 * @}
 */

}  // namespace next
}  // namespace perception
}  // namespace holo

#endif