/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mls_filter.hpp
 * @brief Implementation of mls filter
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-06-16
 */

#ifndef HOLO_3D_FILTER_MLS_FILTER_HPP_
#define HOLO_3D_FILTER_MLS_FILTER_HPP_

#include <holo/3d/filter/mls_filter.h>
#include <holo/numerics/utility.h>

namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
MlsFilterT<PointT>::MlsFilterT(Parameters const& params) : params_(params), grid_res_inverse_(1.0 / params.grid_size)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
typename MlsFilterT<PointT>::PointCloudPtr MlsFilterT<PointT>::Compute()
{
    if (!PreCompute())
    {
        std::string s = "!PreCompute";
        LOG(ERROR) << s;
        return nullptr;
    }

    // assign each point to grid
    computeGrids();

    // compute grid seeds
    std::vector<GridPtr> grid_seeds;
    computeSeeds(grid_seeds);

    int32_t seed_counter = 0;
    Index   seed         = grid_seeds[seed_counter]->index;
    Scalar  grid_size    = params_.grid_size;

    // region grow by mls fitting
    std::queue<Index> seeds;
    seeds.push(seed);

    while (!seeds.empty())
    {
        Index curr_seed = seeds.front();
        seeds.pop();

        GridPtr& curr_grid = grid_map_[curr_seed];

        std::vector<PointT> neighbor_pts(curr_grid->neighbors.size());

        for (size_t i = 0; i < curr_grid->neighbors.size(); ++i)
        {
            neighbor_pts[i] = grid_map_[curr_grid->neighbors[i]]->ground_pt;
        }

        //@TODO use different weight
        Eigen::VectorXd weight(neighbor_pts.size());
        weight.setConstant(1.0);
        Eigen::VectorXd surface_params;

        fitPolynominalSurface(params_.order, neighbor_pts, weight, surface_params);

        size_t i_nghr = 0;
        while (i_nghr < grid_map_[curr_seed]->neighbors.size())
        {
            Index index = curr_grid->neighbors[i_nghr];

            // continue if processed
            if (grid_labels_[index] != -1)
            {
                i_nghr++;
                continue;
            }

            bool_t      is_a_seed         = false;
            bool_t      belongs_to_ground = false;
            auto const& pt_neighbor       = grid_map_[index]->ground_pt;

            Scalar distance = 0.0, z_fit = 0.0;
            distance = computeDistanceToSurface(pt_neighbor, params_.order, surface_params, z_fit);

            if (distance < params_.max_distance_to_surface &&
                grid_map_[index]->neighbors.size() > params_.min_seed_neighbors)
            {
                is_a_seed         = true;
                belongs_to_ground = true;
            }

            // interpolate ground point if grid not belong to ground point
            if (!belongs_to_ground)
            {
                PointT p;
                p[0] = index(0) * grid_size + 0.5 * grid_size;
                p[1] = index(1) * grid_size + 0.5 * grid_size;
                p[2] = z_fit;

                grid_map_[index]->ground_pt = p;

                i_nghr++;
                continue;
            }

            grid_labels_[index] = 1;

            if (is_a_seed)
            {
                seeds.push(index);
            }

            i_nghr++;
        }
    }

    // process grid labels
    PointCloudPtr output(new PointCloud);
    kept_indices_.clear();
    removed_indices_.clear();

    for (auto iter = grid_labels_.begin(); iter != grid_labels_.end(); ++iter)
    {
        std::vector<size_t> const& indices = grid_map_[iter->first]->indices;

        if (iter->second != -1)
        {
            PointT& ground_pt = grid_map_[iter->first]->ground_pt;

            for (auto const& idx : indices)
            {
                if (std::fabs(cloud_->at(idx).GetZ() - ground_pt.GetZ()) < params_.max_distance_to_surface)
                {
                    kept_indices_.push_back(idx);
                }
                else
                {
                    removed_indices_.push_back(idx);
                }
            }
        }
        else
        {
            std::copy(indices.begin(), indices.end(), std::back_inserter(removed_indices_));
        }
    }

    CopyPointCloud(*cloud_, kept_indices_, *output);

    if (!PostCompute())
    {
        std::string s = "!PostCompute";
        LOG(ERROR) << s;
        return nullptr;
    }

    return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void MlsFilterT<PointT>::computeGrids()
{
    // assign points to grid
    for (size_t i = 0; i < cloud_->size(); ++i)
    {
        const PointT& pt         = cloud_->at(i);
        Index         grid_index = getGridIndex(pt);

        if (!grid_map_[grid_index])
        {
            grid_map_[grid_index].reset(new Grid(grid_index));
            grid_map_[grid_index]->ground_pt = pt;
        }

        GridPtr& grid = grid_map_[grid_index];

        if (grid->ground_pt.GetZ() > pt.GetZ())
        {
            grid->ground_pt = pt;
        }

        grid->z_values.push_back(pt.GetZ());
        grid->indices.push_back(i);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void MlsFilterT<PointT>::computeSeeds(std::vector<GridPtr>& grid_seeds)
{
    grid_seeds.clear();
    int32_t half_size = params_.half_window_size;

    for (auto iter = grid_map_.begin(); iter != grid_map_.end(); ++iter)
    {
        Index grid_index = iter->first;

        GridPtr& grid = iter->second;

        grid_labels_[grid_index] = -1;

        // compute z sigmas
        Scalar z_mean, z_sigma;
        numerics::ComputeMeanAndStdev(grid->z_values, z_mean, z_sigma);
        grid->z_sigma = z_sigma;

        // compute neighbors
        Index min_bound = grid_index - Index(half_size, half_size);
        Index max_bound = grid_index + Index(half_size, half_size);

        for (int32_t x = min_bound(0); x <= max_bound(0); ++x)
        {
            for (int32_t y = min_bound(1); y <= max_bound(1); ++y)
            {
                Index neighbor(x, y);

                auto iter = grid_map_.find(neighbor);
                if (iter != grid_map_.end())
                {
                    grid->neighbors.push_back(neighbor);
                }
            }
        }

        grid_seeds.push_back(grid);
    }

    // sort grid by z sigmas
    std::sort(grid_seeds.begin(), grid_seeds.end(), [](GridPtr const& i, GridPtr const& j) {
        return i->z_sigma < j->z_sigma && i->indices.size() > j->indices.size();
    });
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
void MlsFilterT<PointT>::fitPolynominalSurface(int32_t const order, std::vector<PointT> const& points,
                                               Eigen::VectorXd const& weight, Eigen::VectorXd& surface_params)
{
    int32_t nr_coeff = (order + 1) * (order + 2) / 2;

    Eigen::VectorXd f_vec(points.size());
    Eigen::MatrixXd B(points.size(), nr_coeff);
    Eigen::MatrixXd Bt_weight;

    Eigen::MatrixXd Bt_weight_B(nr_coeff, nr_coeff);
    Eigen::VectorXd b(nr_coeff);
    Eigen::VectorXd ans(nr_coeff);

    float64_t u_coord, v_coord, u_pow, v_pow;
    for (size_t i = 0; i < points.size(); ++i)
    {
        u_coord  = points[i][0];
        v_coord  = points[i][1];
        f_vec[i] = points[i][2];

        int32_t j = 0;
        u_pow     = 1;

        for (int32_t ui = 0; ui <= order; ++ui)
        {
            v_pow = 1;
            for (int32_t vi = 0; vi <= order - ui; ++vi)
            {
                B(i, j++) = u_pow * v_pow;
                v_pow *= v_coord;
            }
            u_pow *= u_coord;
        }
    }

    Bt_weight   = B.transpose() * weight.asDiagonal();
    Bt_weight_B = Bt_weight * B;
    b           = Bt_weight * f_vec;

    ans = Bt_weight_B.llt().solve(b);
    ans.swap(surface_params);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
typename MlsFilterT<PointT>::Scalar MlsFilterT<PointT>::computeDistanceToSurface(PointT const& pt, int32_t order,
                                                                                 Eigen::VectorXd const& surface_params,
                                                                                 Scalar&                z_fit)
{
    Scalar          x        = pt[0];
    Scalar          y        = pt[1];
    Scalar          z        = pt[2];
    int32_t         nr_coeff = surface_params.size();
    Eigen::VectorXd val(nr_coeff);

    Scalar u_pow, v_pow;
    u_pow     = 1;
    int32_t j = 0;

    for (int32_t ui = 0; ui <= order; ++ui)
    {
        v_pow = 1;
        for (int32_t vi = 0; vi <= order - ui; ++vi)
        {
            val(j++) = u_pow * v_pow;
            v_pow *= y;
        }
        u_pow *= x;
    }

    z_fit = val.dot(surface_params);

    return std::fabs(z - z_fit);
}
}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_FILTER_MLS_FILTER_HPP_
