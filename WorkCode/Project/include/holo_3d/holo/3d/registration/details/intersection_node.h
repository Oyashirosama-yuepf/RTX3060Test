/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intersection_node.h
 * @brief This header file defines intersection node class
 * @author zhaojiaxing(zhaojiaxing@holomatic.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-03-25
 */

#ifndef HOLO_3D_REGISTRATION_DETAILS_INTERSECTION_NODE_H_
#define HOLO_3D_REGISTRATION_DETAILS_INTERSECTION_NODE_H_

#include <vector>
#include <ostream>

#include <holo/log/hololog.h>

#include <holo/geometry/point3.h>

namespace holo
{
namespace pointcloud
{
namespace internal
{
/**
 * @brief Multidimensional node used for intersection query
 *
 */
class IntersectionNode
{
public:
    using Scalar     = float64_t;
    using Point3Type = geometry::Point3T<Scalar>;
    using Ptr        = std::shared_ptr<IntersectionNode>;
    using ConstPtr   = std::shared_ptr<const IntersectionNode>;

    /**
     * @brief Construct a new Intersection Node
     *
     * @param[in] points Input points. Needed to compute split
     * @param[in] center Center of the node in the nd-space
     * @param[in] ids Ids used to access _points[_ids[i]]
     * @param[in] begin First element id in the node
     * @param[in] end Last element id in the node
     */
    IntersectionNode(std::vector<Point3Type> const& points, Point3Type const& center, std::vector<size_t> const& ids,
                     size_t const begin, size_t const end)
      : points_(points), center_(center), ids_(ids), begin_(begin), end_(end), dim_(Point3Type::Dim())
    {
    }

    /**
     * @brief Construct a new Intersection Node
     *
     * @param rhs
     */
    IntersectionNode(IntersectionNode const& rhs)
      : points_(rhs.points_), center_(rhs.center_), ids_(rhs.ids_), begin_(rhs.begin_), end_(rhs.end_), dim_(rhs.dim_)
    {
    }

    /**
     * @brief operator =
     *
     * @param rhs
     * @return IntersectionNode&
     */
    IntersectionNode& operator=(IntersectionNode const& rhs)
    {
        points_ = rhs.points_;
        center_ = rhs.center_;
        ids_    = rhs.ids_;
        begin_  = rhs.begin_;
        end_    = rhs.end_;
        dim_    = rhs.dim_;

        return *this;
    }

    /**
     * @brief Destroy the Intersection Node object
     *
     */
    virtual ~IntersectionNode()
    {
    }

    /**
     * @brief Length of the range covered by this node in the id array
     *
     * @return int32_t
     */
    int32_t RangeLength() const
    {
        return static_cast<int32_t>(end_ - begin_);
    }

    /**
     * @brief First position in the id array defining the current instance range
     *
     * @return size_t
     */
    size_t RangeBegin() const
    {
        return begin_;
    }

    /**
     * @brief Last position in the id array defining the current instance range
     *
     * @return size_t
     */
    size_t RangeEnd() const
    {
        return end_;
    }

    /**
     * @brief Access to the i-element point in the node.
     *
     * @param[in] i index
     * @return Point3Type const&
     */
    Point3Type const& PointInRange(size_t i) const
    {
        if (i + begin_ > end_)
        {
            LOG(ERROR) << "point out of range";
        }

        return points_[ids_[i + begin_]];
    }

    /**
     * @brief Access to the i-element point in the node.
     *
     * @param i index
     * @return size_t
     */
    size_t IdInRange(size_t i) const
    {
        if (i + begin_ > end_)
        {
            LOG(ERROR) << "point out of range";
        }

        return ids_[i + begin_];
    }

    /**
     * @brief Center of the current node
     *
     * @return Point3Type const&
     */
    Point3Type const& Center() const
    {
        return center_;
    }

    /**
     * @brief Split the node and compute child nodes
     *
     * @param[in] root_edge_half_length
     * @param[out] childs
     */
    void Split(Scalar root_edge_half_length, std::vector<IntersectionNode>& childs)
    {
        // compute number of childs at compile time
        size_t const num_nodes = std::pow(2, dim_);
        size_t const offset    = childs.size();

        // init all potential nodes using the root values
        childs.resize(offset + num_nodes, *this);

        // split successively along all the dimensions of the ambiant apace
        for (size_t i = 0; i < dim_; ++i)
        {
            size_t const num_interval  = std::pow(2, i + 1);
            size_t const num_split     = num_interval / 2;
            size_t const interval_node = num_nodes / num_split;
            size_t const mid_node      = num_nodes / num_interval;

            for (size_t j = 0; j != num_split; ++j)
            {
                size_t const begin_node_id  = j * interval_node + offset;
                size_t const end_node_id    = (j + 1) * interval_node + offset;
                Scalar       current_center = childs[begin_node_id].Center()[i];

                size_t const split_id      = splitNode(childs[begin_node_id].RangeBegin(),
                                                  childs[end_node_id - 1].RangeEnd(), i, current_center);
                Scalar const before_center = current_center - root_edge_half_length / 2;
                Scalar const after_center  = current_center + root_edge_half_length / 2;

                // transmit the split to the related nodes
                for (size_t k = begin_node_id; k != begin_node_id + mid_node; ++k)
                {
                    childs[k].center_[i] = before_center;
                    childs[k].end_       = split_id;
                }

                for (size_t k = begin_node_id + mid_node; k != end_node_id; ++k)
                {
                    childs[k].center_[i] = after_center;
                    childs[k].begin_     = split_id;
                }
            }
        }

        // remove childs not containing any element
        if (!childs.empty())
        {
            childs.erase(std::remove_if(childs.begin(), childs.end(),
                                        [](IntersectionNode const& node) { return node.RangeLength() == 0; }),
                         childs.end());
        }

        for (size_t i = offset; i < childs.size(); ++i)
        {
            childs[i].ids_ = ids_;
        }
    }

    /**
     * @brief Build unit root node
     *
     * @param[in] points input points
     * @param[in] ids input point indices
     * @return IntersectionNode
     */
    static IntersectionNode BuildUnitRootNode(std::vector<Point3Type> const& points, std::vector<size_t> const& ids)
    {
        return IntersectionNode(points, Point3Type(0.5, 0.5, 0.5), ids, 0, ids.size());
    }

    /**
     * @brief IntersectionNode operator<<
     *
     * @param[in] os ostream
     * @param[in] node intersection node
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, IntersectionNode const& node)
    {
        os << "IntersectionNode: (";
        os << node.Center() << ", ";

        for (int32_t i = 0; i < node.RangeLength(); ++i)
        {
            os << node.IdInRange(i) << " ";
        }

        os << "). ";
        return os;
    }

protected:
    /**
     * @brief split node
     *
     * @param[in] start start index
     * @param[in] end end index
     * @param[in] dim dimension
     * @param[in] split_value split value
     * @return size_t
     */
    size_t splitNode(size_t start, size_t end, size_t dim, Scalar split_value)
    {
        int32_t left  = static_cast<int32_t>(start);
        int32_t right = static_cast<int32_t>(end - 1);

        for (; left < right; ++left, --right)
        {
            while (left < static_cast<int32_t>(end) && points_[ids_[left]][dim] < split_value)
            {
                left++;
            }
            while (right >= static_cast<int32_t>(start) && points_[ids_[right]][dim] >= split_value)
            {
                right--;
            }

            if (left > right)
            {
                break;
            }

            std::swap(ids_[left], ids_[right]);
        }

        if (left >= static_cast<int32_t>(end))
        {
            return end;
        }

        return points_[ids_[left]][dim] < split_value ? static_cast<size_t>(left + 1) : static_cast<size_t>(left);
    }

protected:
    std::vector<Point3Type> points_;
    Point3Type              center_;
    std::vector<size_t>     ids_;
    size_t                  begin_;
    size_t                  end_;
    size_t                  dim_;
};
}  // namespace internal
}  // namespace pointcloud
}  // namespace holo
#endif  // HOLO_3D_REGISTRATION_DETAILS_INTERSECTION_NODE_H_
