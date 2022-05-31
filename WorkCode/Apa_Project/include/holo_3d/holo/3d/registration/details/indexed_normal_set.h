/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file indexed_normal_set.h
 * @brief This header file defines indexed normal set class
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-03-25
 */

#ifndef HOLO_3D_REGISTRATION_DETAILS_INDEXED_NORMAL_SET_H_
#define HOLO_3D_REGISTRATION_DETAILS_INDEXED_NORMAL_SET_H_

#include <array>
#include <set>
#include <vector>

#include <holo/geometry/point3.h>
#include <holo/geometry/quaternion.h>

namespace holo
{
namespace pointcloud
{
namespace internal
{
/**
 * @brief Compile time pow function
 *
 * @tparam baseT
 * @tparam expoT
 * @param[in] base base
 * @param[in] expo exponent
 * @return constexpr baseT
 */
template <typename baseT, typename expoT>
constexpr baseT Pow(baseT base, expoT expo)
{
    return (expo != 0) ? base * Pow(base, expo - 1) : 1;
}

/**
 * @brief Convert a normalized n-d vector to a linear index in a uniform regular grid This function is recursive, and
 * unrolled at compile time (loop over n).
 *
 * @tparam ndIndexT PointT type
 * @tparam IndexT Index type
 * @tparam SizeT Size type
 * @param[in] coord Input coordinates defined in the normalized n-hypercube.
 * @param[in] cdim  Working dimension, must be called with n.
 * @param[in] gsize Dimension of the grid, must be consistent in all dimensions
 * @return constexpr IndexT
 */
template <typename ndIndexT, typename IndexT, typename SizeT>
constexpr inline IndexT UnrollIndexLoop(ndIndexT const& coord, IndexT cdim, SizeT gsize)
{
    return (cdim != 0) ? IndexT(coord[cdim]) * Pow(gsize, cdim) + UnrollIndexLoop(coord, cdim - 1, gsize) :
                         IndexT(coord[cdim]);
}

/**
 * @brief Normal set indexed by a position in euclidean space. The size used to hash the normals in an euclidean cell
 is defined at compile time
 * @ref https://github.com/nmellado/Super4PCS/blob/master/src/super4pcs/accelerators/normalset.h
 *
 * @tparam PointT Type of point to work with
 * @tparam dim Number of dimension in ambient space
 * @tparam size Normal grid size in 1 dimension
 * @tparam Scalar Scalar type
 */
template <typename PointT, int32_t dim = 3, int32_t size = 7, typename Scalar = float64_t>
class IndexedNormalSetT
{
public:
    using Point3Type     = geometry::Point3T<Scalar>;
    using AngularGrid    = std::array<std::vector<size_t>, Pow(size, dim)>;
    using AngularGridPtr = std::shared_ptr<AngularGrid>;
    using EigenVector3   = Eigen::Matrix<Scalar, 3, 1>;

public:
    /**
     * @brief Construct a new Indexed Normal Set object
     *
     * @param[in] epsilon normalized distance threshold epsilon
     */
    IndexedNormalSetT(Scalar const epsilon) : nepsilon_(1.0 / static_cast<Scalar>(size) + 0.00001), epsilon_(epsilon)
    {
        int32_t const grid_depth = -std::log2(epsilon);
        eg_size_                 = std::pow(2, grid_depth);
        epsilon_                 = 1.f / eg_size_;

        grids_.resize(std::pow(eg_size_, dim), nullptr);
        grid_size_ = static_cast<int32_t>(grids_.size());
    }

    /**
     * @brief Destroy the Indexed Normal Set object
     *
     */
    virtual ~IndexedNormalSetT()
    {
    }

    /**
     * @brief Add a new couple pos/normal, and its associated id
     *
     * @param[in] p input point
     * @param[in] n input point's normal
     * @param[in] id input point's id
     * @return bool_t
     */
    bool_t AddElement(Point3Type const& p, Point3Type const& n, size_t id)
    {
        int32_t const p_id = indexPos(p);
        if (p_id >= grid_size_)
        {
            return false;
        }

        int32_t const n_id = indexNormal(n);
        if (n_id == -1)
        {
            return false;
        }

        if (grids_[p_id] == nullptr)
        {
            grids_[p_id].reset(new AngularGrid);
        }

        grids_[p_id]->at(n_id).push_back(id);
        return true;
    }

    /**
     * @brief Get the Angular Grid at point
     *
     * @param[in] p input point
     * @return AngularGridPtr
     */
    AngularGridPtr GetAngularGrid(Point3Type const& p)
    {
        int32_t const index = indexPos(p);
        if (index >= grid_size_)
        {
            return nullptr;
        }

        return grids_[index];
    }

    /**
     * @brief Get closest points in euclidean space
     *
     * @param[in] p input point
     * @param[out] nei output neighbor indices
     */
    void GetNeighbors(Point3Type const& p, std::vector<size_t>& nei)
    {
        AngularGridPtr grid = GetAngularGrid(p);

        if (grid == nullptr)
        {
            return;
        }

        for (auto iter = grid->cbegin(); iter != grid->cend(); ++iter)
        {
            std::vector<size_t> const& lnei = *iter;
            nei.insert(nei.end(), lnei.begin(), lnei.end());
        }
    }

    /**
     * @brief Get closest points in euclidean an normal space
     *
     * @param[in] p input point
     * @param[in] n input normal
     * @param[out] nei outpt neighbor indices
     */
    void GetNeighbors(Point3Type const& p, Point3Type const& n, std::vector<size_t>& nei)
    {
        AngularGridPtr grid = GetAngularGrid(p);

        if (grid == nullptr)
        {
            return;
        }

        std::vector<size_t> const& lnei = grid->at(indexNormal(n));
        nei.insert(nei.end(), lnei.begin(), lnei.end());
    }

    /**
     * @brief Get closest poitns in euclidean an normal space with angular deviation
     *
     * @param[in] p input point
     * @param[in] n input normal
     * @param[in] cos_alpha angular deviation
     * @param[out] nei output neighbor indices
     * @param[in] try_reverse try reverse or not
     */
    void GetNeighbors(Point3Type const& p, Point3Type const& n, Scalar cos_alpha, std::vector<size_t>& nei,
                      bool try_reverse = false)
    {
        AngularGridPtr grid = GetAngularGrid(p);

        if (grid == nullptr)
        {
            return;
        }

        Scalar const alpha      = std::acos(cos_alpha);
        Scalar const perimeter  = Scalar(2) * M_PI * std::atan(alpha);
        size_t const num_sample = 2 * std::ceil(perimeter * Scalar(size) / Scalar(2.));
        Scalar const angle_step = Scalar(2) * M_PI / Scalar(num_sample);
        Scalar const sin_alpha  = std::sin(alpha);

        Eigen::Quaternion<Scalar> q;
        q.setFromTwoVectors(EigenVector3(0., 0., 1.), EigenVector3(n[0], n[1], n[2]));

        std::set<size_t> colored;

        // Do the rendering independently of the content
        for (size_t a = 0; a != num_sample; ++a)
        {
            Scalar             theta = Scalar(a) * angle_step;
            const EigenVector3 dir =
                (q * EigenVector3(sin_alpha * std::cos(theta), sin_alpha * std::sin(theta), cos_alpha)).normalized();

            Point3Type direction(dir[0], dir[1], dir[2]);

            int id = indexNormal(direction);

            if (grid->at(id).size() != 0)
            {
                colored.insert(id);
            }

            if (try_reverse)
            {
                id = indexNormal(-direction);

                if (grid->at(id).size() != 0)
                {
                    colored.insert(id);
                }
            }
        }

        for (std::set<size_t>::const_iterator it = colored.cbegin(); it != colored.cend(); ++it)
        {
            std::vector<size_t> const& lnei = grid->at(*it);
            nei.insert(nei.end(), lnei.begin(), lnei.end());
        }
    }

private:
    /**
     * @brief Get the index corresponding to position p
     *
     * @param[in] p input point
     * @return int32_t
     */
    int32_t indexPos(Point3Type const& p) const
    {
        return UnrollIndexLoop(coordinatesPos(p), dim - 1, eg_size_);
    }

    /**
     * @brief Get the index corresponding to normal n
     *
     * @param[in] n the input normal
     * @return int32_t
     */
    int32_t indexNormal(Point3Type const& n) const
    {
        return UnrollIndexLoop(coordinatesNormal(n), dim - 1, size);
    }

    /**
     * @brief Get the index corresponding to position p
     *
     * @param[in] p input point
     * @return int32_t
     */
    int32_t indexCoordinatesPos(Point3Type const& p) const
    {
        return UnrollIndexLoop(p, dim - 1, eg_size_);
    }

    /**
     * @brief Get the index corresponding to normal n
     *
     * @param[in] n the input normal
     * @return int32_t
     */
    int32_t indexCoordinatesNormal(Point3Type const& n) const
    {
        return UnrollIndexLoop(n, dim - 1, size);
    }

    /**
     * @brief Get the coordinates corresponding to position p
     *
     * @param[in] p input point
     * @return Point3Type
     */
    Point3Type coordinatesPos(Point3Type const& p) const
    {
        return p / epsilon_;
    }

    /**
     * @brief Get the index corresponding to normal n
     *
     * @param[in] n input normal
     * @return Point3Type
     */
    Point3Type coordinatesNormal(Point3Type const& n) const
    {
        static Point3Type half(0.5, 0.5, 0.5);
        return (n / 2.0 + half) / nepsilon_;
    }

private:
    Scalar                      nepsilon_;   ///< grid size epsilon
    Scalar                      epsilon_;    ///< normalized euclidean grid epsilon
    int32_t                     eg_size_;    ///< size of the euclidean grid for each dimension
    int32_t                     grid_size_;  /// size of angular grids
    std::vector<AngularGridPtr> grids_;      ///< angular grids
};
}  // namespace internal
}  // namespace pointcloud
}  // namespace holo
#endif  // HOLO_3D_REGISTRATION_DETAILS_INDEXED_NORMAL_SET_H_
