#ifndef HOLO_3D_FILTER_APPROXIMATE_PROGRESSIVE_MORPHOLOGICAL_FILTER_HPP
#define HOLO_3D_FILTER_APPROXIMATE_PROGRESSIVE_MORPHOLOGICAL_FILTER_HPP

#include <holo/3d/common/common.h>
#include <holo/3d/filter/progressive_morphological_filter.h>

#include <Eigen/Dense>
#include <numeric>
namespace holo
{
namespace pointcloud
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
ProgressiveMorphologicalFilterT<PointT>::ProgressiveMorphologicalFilterT(const Parameters& params) : params_(params)
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
ProgressiveMorphologicalFilterT<PointT>::~ProgressiveMorphologicalFilterT()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
bool_t ProgressiveMorphologicalFilterT<PointT>::PreCompute()
{
    if (!Base::PreCompute())
    {
        return false;
    }

    indices_.resize(cloud_->size());
    std::iota(indices_.begin(), indices_.end(), 0);

    removed_indices_.clear();
    kept_indices_.clear();
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
bool_t ProgressiveMorphologicalFilterT<PointT>::PostCompute()
{
    return Base::PostCompute();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename PointT>
typename ProgressiveMorphologicalFilterT<PointT>::PointCloudPtr ProgressiveMorphologicalFilterT<PointT>::Compute()
{
    if (!PreCompute())
    {
        LOG(ERROR) << "PreCompute failed.";
        return nullptr;
    }

    // Compute the series of window sizes and height thresholds
    std::vector<Scalar>  height_thresholds;
    std::vector<Scalar>  window_sizes;
    std::vector<int32_t> half_sizes;

    int32_t iteration        = 0;
    int32_t half_size        = 0;
    Scalar  window_size      = 0.0;
    Scalar  height_threshold = 0.0;

    while (window_size < params_.max_window_size)
    {
        half_size = static_cast<int32_t>(std::pow(2.0, iteration));

        window_size = 2 * half_size + 1;

        if (iteration == 0)
        {
            height_threshold = params_.initial_distance;
        }
        else
        {
            height_threshold = params_.slope * (window_size - window_sizes[iteration - 1]) * params_.cell_size +
                               params_.initial_distance;
        }

        // Enforce max distance on height threshold
        if (height_threshold > params_.max_distance)
        {
            height_threshold = params_.max_distance;
        }

        half_sizes.push_back(half_size);
        window_sizes.push_back(window_size);
        height_thresholds.push_back(height_threshold);

        iteration++;
    }

    // setup grid based on scale and extents
    PointT          global_max, global_min;
    BBox<PointT, 3> bbox;
    bbox(*cloud_, global_min, global_max);

    Scalar x_extent = global_max.GetX() - global_min.GetX();
    Scalar y_extent = global_max.GetY() - global_min.GetY();

    int32_t rows = static_cast<int32_t>(std::floor(y_extent / params_.cell_size) + 1);
    int32_t cols = static_cast<int32_t>(std::floor(x_extent / params_.cell_size) + 1);

    // A stores the minimum z value of points in the grid
    Eigen::MatrixXf A(rows, cols);
    A.setConstant(std::numeric_limits<float32_t>::quiet_NaN());

    // Z stores the minimum z value of points in the window
    Eigen::MatrixXf Z(rows, cols);
    Z.setConstant(std::numeric_limits<float32_t>::quiet_NaN());

    // Zf stores the maximum z value of points in the window
    Eigen::MatrixXf Zf(rows, cols);
    Zf.setConstant(std::numeric_limits<float32_t>::quiet_NaN());

    for (size_t i = 0; i < cloud_->size(); ++i)
    {
        const PointT& p = cloud_->at(i);

        int32_t row = std::floor((p.GetY() - global_min.GetY()) / params_.cell_size);
        int32_t col = std::floor((p.GetX() - global_min.GetX()) / params_.cell_size);

        if (p.GetZ() < A(row, col) || std::isnan(A(row, col)))
        {
            A(row, col) = p.GetZ();
        }
    }

    removed_indices_ = indices_;

    // Progressively filter ground returns using morphological open
    for (size_t i = 0; i < window_sizes.size(); ++i)
    {
        PointCloudPtr cloud(new PointCloud);
        CopyPointCloud(*cloud_, removed_indices_, *cloud);

        // Erosion
        for (int32_t row = 0; row < rows; ++row)
        {
            int32_t rs, re;
            rs = ((row - half_sizes[i]) < 0) ? 0 : row - half_sizes[i];
            re = ((row + half_sizes[i]) > (rows - 1)) ? (rows - 1) : row + half_sizes[i];

            for (int32_t col = 0; col < cols; ++col)
            {
                int32_t cs, ce;
                cs = ((col - half_sizes[i]) < 0) ? 0 : col - half_sizes[i];
                ce = ((col + half_sizes[i]) > (cols - 1)) ? (cols - 1) : col + half_sizes[i];

                float32_t min_coeff = std::numeric_limits<float32_t>::max();

                for (int32_t j = rs; j < (re + 1); ++j)
                {
                    for (int32_t k = cs; k < (ce + 1); ++k)
                    {
                        if (A(j, k) != std::numeric_limits<float32_t>::quiet_NaN())
                        {
                            if (A(j, k) < min_coeff)
                            {
                                min_coeff = A(j, k);
                            }
                        }
                    }
                }

                if (min_coeff != std::numeric_limits<float32_t>::quiet_NaN())
                {
                    Z(row, col) = min_coeff;
                }
            }
        }

        // Dilate
        for (int32_t row = 0; row < rows; ++row)
        {
            int32_t rs, re;
            rs = ((row - half_sizes[i]) < 0) ? 0 : row - half_sizes[i];
            re = ((row + half_sizes[i]) > (rows - 1)) ? (rows - 1) : row + half_sizes[i];

            for (int32_t col = 0; col < cols; ++col)
            {
                int32_t cs, ce;
                cs = ((col - half_sizes[i]) < 0) ? 0 : col - half_sizes[i];
                ce = ((col + half_sizes[i]) > (cols - 1)) ? (cols - 1) : col + half_sizes[i];

                float32_t max_coeff = -std::numeric_limits<float32_t>::max();

                for (int32_t j = rs; j < (re + 1); ++j)
                {
                    for (int32_t k = cs; k < (ce + 1); ++k)
                    {
                        if (Z(j, k) != std::numeric_limits<float32_t>::quiet_NaN())
                        {
                            if (Z(j, k) > max_coeff)
                            {
                                max_coeff = Z(j, k);
                            }
                        }
                    }
                }

                if (max_coeff != -std::numeric_limits<float32_t>::quiet_NaN())
                {
                    Zf(row, col) = max_coeff;
                }
            }
        }

        std::vector<size_t> pt_indices;
        for (size_t p_idx = 0; p_idx < removed_indices_.size(); ++p_idx)
        {
            const PointT& p   = cloud->at(p_idx);
            int32_t       row = static_cast<int32_t>(std::floor((p.GetY() - global_min.GetY()) / params_.cell_size));
            int32_t       col = static_cast<int32_t>(std::floor((p.GetX() - global_min.GetX()) / params_.cell_size));

            float32_t diff = p.GetZ() - Zf(row, col);

            if (diff < height_thresholds[i])
            {
                pt_indices.push_back(removed_indices_[p_idx]);
            }
        }

        A.swap(Zf);

        removed_indices_.swap(pt_indices);
    }

    PointCloudPtr filtered_cloud(new PointCloud);
    filtered_cloud->reserve(cloud_->size());

    std::set_difference(indices_.begin(), indices_.end(), removed_indices_.begin(), removed_indices_.end(),
                        std::inserter(kept_indices_, kept_indices_.begin()));

    CopyPointCloud(*cloud_, kept_indices_, *filtered_cloud);

    if (!PostCompute())
    {
        LOG(ERROR) << "PostCompute failed.";
        return nullptr;
    }

    return filtered_cloud;
}

}  // namespace pointcloud
}  // namespace holo

#endif
