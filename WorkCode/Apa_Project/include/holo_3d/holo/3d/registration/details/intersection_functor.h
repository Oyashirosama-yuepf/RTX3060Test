/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intersection_functor.h
 * @brief This header file defines intersection functor
 * @author zhaojiaxing(zhaojiaxing@holomaitc.com)
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-03-25
 */
#ifndef HOLO_3D_REGISTRATION_DETAILS_INTERSECTION_FUNCTOR_H_
#define HOLO_3D_REGISTRATION_DETAILS_INTERSECTION_FUNCTOR_H_

#include <set>

#include <holo/3d/registration/details/intersection_node.h>
#include <holo/geometry/box3.h>
#include <holo/geometry/sphere.h>

namespace holo
{
namespace pointcloud
{
namespace internal
{
/**
 * @brief box-sphere intersection function
 * @ref A Simple Method for Box-Sphere Intersection Testing,  Graphics Gems, p. 335-339, code: p. 730-732, BoxSphere.c.
 *
 * @tparam T
 * @param sphere
 * @param box
 * @return bool_t
 */

template <typename T>
bool_t IntersectSphere3AndBox(geometry::Sphere3T<T> const& sphere, geometry::Box3T<T> const& box)
{
    assert(box.GetPose().GetRotation() == Rot3T<T>::Identity());

    using Point3Type = geometry::Point3T<T>;
    Point3Type        half(box.GetWidth() / 2, box.GetHeight() / 2, box.GetDepth() / 2);
    Point3Type const& bcenter = box.GetCenter();
    Point3Type const& scenter = sphere.GetCenter();

    Point3Type min  = bcenter - half;
    Point3Type max  = bcenter + half;
    Point3Type smin = scenter - min;
    Point3Type smax = scenter - max;

    Point3Type sqmin(smin[0] * smin[0], smin[1] * smin[1], smin[2] * smin[2]);
    Point3Type sqmax(smax[0] * smax[0], smax[1] * smax[1], smax[2] * smax[2]);

    T dist_min = 0.0;

    for (size_t i = 0; i < Point3Type::Dim(); ++i)
    {
        if (scenter[i] < min[i])
        {
            dist_min += sqmin[i];
        }

        if (scenter[i] > max[i])
        {
            dist_min += sqmin[i];
        }
    }

    T sqr_radius = sphere.GetRadius() * sphere.GetRadius();
    T max_sum    = std::max(sqmin[0], sqmax[0]) + std::max(sqmin[1], sqmax[1]) + std::max(sqmin[2], sqmax[2]);

    return dist_min < sqr_radius && sqr_radius < max_sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t IntersectSphere3AndBox(geometry::Sphere3T<T> const& sphere, geometry::Point3T<T> const& p,
                              T const half_edge_length)
{
    using Point3Type = geometry::Point3T<T>;

    Point3Type         half(half_edge_length, half_edge_length, half_edge_length);
    geometry::Box3T<T> box(p - half, p + half);

    return IntersectSphere3AndBox<T>(sphere, box);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t IntersectSphere3AndPoint(geometry::Sphere3T<T> const& sphere, geometry::Point3T<T> const& p, T const epsilon)
{
    return std::pow((p.Dist(sphere.GetCenter()) - sphere.GetRadius()), 2) < std::pow(epsilon, 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t IntersectSphere3AndPoint(geometry::Point3T<T> const& center, T const& radius, geometry::Point3T<T> const& p,
                                T const epsilon)
{
    return std::pow(p.Dist(center) - radius, 2) < std::pow(epsilon, 2);
}

/**
 * @brief Extract pairs of points by rasterizing primitives and collect points
 *
 */
class IntersectionFunctor
{
public:
    using Scalar      = float64_t;
    using Point3Type  = geometry::Point3T<Scalar>;
    using Sphere3Type = geometry::Sphere3T<Scalar>;

    using Ptr      = std::shared_ptr<IntersectionFunctor>;
    using ConstPtr = std::shared_ptr<const IntersectionFunctor>;

    /**
     * @brief Construct a new Intersection Functor object
     *
     */
    IntersectionFunctor()
    {
    }

    /**
     * @brief Destroy the Intersection Functor object
     *
     */
    virtual ~IntersectionFunctor()
    {
    }

    /**
     * @brief Intersection process function
     *
     * @tparam ProcessingFunctor
     * @param[in] min_node_size Min number of points in nodes
     * @param[in] functor ProcessingFunctor
     * @param[out] epsilon ntersection accuracy in [0:1]
     */
    template <typename ProcessingFunctor>
    void Process(size_t const min_node_size, ProcessingFunctor& functor, Scalar& epsilon)
    {
        std::vector<Sphere3Type> const& primitives = functor.primitives;
        std::vector<Point3Type> const&  points     = functor.points;
        size_t const                    num_points = points.size();
        int32_t                         level_max  = 0;

        epsilon              = GetRoundedEpsilonValue(epsilon, &level_max);
        size_t current_level = 0;

        std::vector<IntersectionNode>  ping, pong;
        std::vector<IntersectionNode>* nodes       = &ping;
        std::vector<IntersectionNode>* child_nodes = &pong;

        std::vector<std::pair<IntersectionNode, Scalar>> early_nodes;

        if (functor.ids.size() != num_points)
        {
            functor.ids.clear();

            for (size_t i = 0; i < num_points; ++i)
            {
                functor.ids.push_back(i);
            }
        }

        // build root node in the child node, will be copied to the current nodes
        child_nodes->push_back(IntersectionNode::BuildUnitRootNode(points, functor.ids));

        Scalar edge_length      = 0.0;
        Scalar edge_half_length = 0.0;

        while (current_level != static_cast<size_t>(level_max) - 1)
        {
            if (child_nodes->empty())
            {
                break;
            }

            edge_length      = 1.0 / std::pow(2, current_level);
            edge_half_length = edge_length / 2.0;

            // swap pointers
            std::swap(nodes, child_nodes);
            child_nodes->clear();

            for (std::vector<IntersectionNode>::iterator it_node = nodes->begin(); it_node != nodes->end(); ++it_node)
            {
                IntersectionNode& node = *it_node;

                // check if the current node intersect one of the primitives
                // in this case, subdivide, store new nodes and stop the loop
                for (std::vector<Sphere3Type>::const_iterator it_primitive = primitives.begin();
                     it_primitive != primitives.end(); it_primitive++)
                {
                    if (IntersectSphere3AndBox(*it_primitive, node.Center(), edge_half_length + epsilon))
                    {
                        // there is two options now: either there is already few points in the
                        // current node, in that case we stop splitting it, or we split.
                        if (node.RangeLength() > int32_t(min_node_size))
                        {
                            node.Split(edge_half_length, *child_nodes);
                        }
                        else
                        {
                            early_nodes.emplace_back(node, edge_half_length + epsilon);
                        }

                        break;
                    }
                }
            }

            current_level++;
        }

        size_t primitive_id = 0;

        for (std::vector<Sphere3Type>::const_iterator it_primitive = primitives.begin();
             it_primitive != primitives.end(); it_primitive++, primitive_id++)
        {
            // add childs
            for (std::vector<IntersectionNode>::const_iterator it_inode = child_nodes->begin();
                 it_inode != child_nodes->end(); it_inode++)
            {
                if (IntersectSphere3AndBox(*it_primitive, (*it_inode).Center(), epsilon * 2.0))
                {
                    for (int32_t i = 0; i != (*it_inode).RangeLength(); i++)
                    {
                        if (primitive_id > (*it_inode).IdInRange(i) &&
                            IntersectSphere3AndPoint(*it_primitive, (*it_inode).PointInRange(i), epsilon))
                        {
                            functor.ProcessPairs(primitive_id, (*it_inode).IdInRange(i));
                        }
                    }
                }
            }

            // add other leafs
            for (std::vector<std::pair<IntersectionNode, Scalar>>::const_iterator it_pairs = early_nodes.begin();
                 it_pairs != early_nodes.end(); it_pairs++)
            {
                if (IntersectSphere3AndBox(*it_primitive, (*it_pairs).first.Center(), (*it_pairs).second))
                {
                    for (int32_t i = 0; i != (*it_pairs).first.RangeLength(); i++)
                    {
                        if (primitive_id > (*it_pairs).first.IdInRange(i) &&
                            IntersectSphere3AndPoint(*it_primitive, (*it_pairs).first.PointInRange(i), epsilon))
                        {
                            functor.ProcessPairs(primitive_id, (*it_pairs).first.IdInRange(i));
                        }
                    }
                }
            }
        }
    }

    static Scalar GetRoundedEpsilonValue(Scalar epsilon, int32_t* level = nullptr)
    {
        int32_t const level_max = -std::log2(epsilon);

        if (level != nullptr)
        {
            *level = level_max;
        }

        return 1.0 / std::pow(2, level_max);
    }
};
}  // namespace internal
}  // namespace pointcloud
}  // namespace holo

#endif  // HOLO_3D_REGISTRATION_DETAILS_INTERSECTION_FUNCTOR_H_
