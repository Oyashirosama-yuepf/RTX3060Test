/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_kd_tree.h
 * @brief KD-tree implement for Point2f.
 * @author wenxunzhe@holomatic.com
 * @date Apirl-26-2022
 */
#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING__KDTREE_H__
#define HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING__KDTREE_H__

#include <holo/obstacle/details/obstacle_vision.h>

#include <cmath>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

namespace holo
{
namespace perception
{
using Scalar         = holo::float32_t;
using VisionObstacle = holo::obstacle::details::ObstacleVisionT<Scalar, 8U>;

struct Node
{
    Point2f point;
    int     id;
    Node*   left;
    Node*   right;

    Node(Point2f arr, int setId) : point(arr), id(setId), left(nullptr), right(nullptr)
    {
    }
};

struct KdTree
{
    Node* root;

    KdTree() : root(nullptr)
    {
    }

    void insertRecursive(Node*& node, uint depth, Point2f point, int id)
    {
        if (node == nullptr)
            node = new Node(point, id);
        else
        {
            uint ui = depth % 2;
            if (point[ui] < node->point[ui])
                insertRecursive(node->left, depth + 1, point, id);
            else
                insertRecursive(node->right, depth + 1, point, id);
        }
    }

    void insert(Point2f point, int id)
    {
        insertRecursive(root, 0, point, id);
    }

    bool checkInTargetBox(Point2f src, Point2f dst, Scalar d)
    {
        if ((src.GetX() >= (dst.GetX() - d)) && (src.GetX() <= (dst.GetX() + d)) && (src.GetY() >= (dst.GetY() - d)) &&
            (src.GetY() <= (dst.GetY() + d)))
        {
            return true;
        }

        return false;
    }

    Scalar getDistance(Point2f src, Point2f dst)
    {
        return src.Dist(dst);
    }

    void searchRecursive(Node* node, Point2f target, int depth, Scalar distance_thres, std::vector<int>& index)
    {
        if (node != NULL)
        {
            if (checkInTargetBox(node->point, target, distance_thres))
            {
                if (getDistance(node->point, target) < distance_thres)
                    index.push_back(node->id);
            }

            if (target[depth % 2] - distance_thres < node->point[depth % 2])
                searchRecursive(node->left, target, depth + 1, distance_thres, index);
            if (target[depth % 2] + distance_thres > node->point[depth % 2])
                searchRecursive(node->right, target, depth + 1, distance_thres, index);
        }
    }

    std::vector<int> search(Point2f const& target, Scalar const& distance_thres)
    {
        std::vector<int> index;
        searchRecursive(root, target, 0, distance_thres, index);
        return index;
    }
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif
