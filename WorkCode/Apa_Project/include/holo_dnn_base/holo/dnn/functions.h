/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file functions.h
 * @brief functions.h
 * @author wanggang(wanggang@holomatic.com)
 * @date "2021-06-01"
 */
#include <holo/perception/common/box2d.h>
#include <holo/perception/common/box_object.h>

#include <iostream>
namespace holo
{
namespace dnn
{
typedef holo::perception::BoxObjectf   BoxObject;
typedef holo::perception::Box2Df       BBox;
typedef holo::perception::ClassifyInfo ClassifyInfo;

/**
 * @brief truncated bbox
 *
 * @param x1 left-top coordinate x
 * @param y1 left-top coordinate y
 * @param x2 right-bottom coordinate x
 * @param y2 right-bottom coordinate y
 * @param crop_width crop_width
 * @param crop_height crop_height

 * @return
 */
void TruncatedBbox(float32_t& x1, float32_t& y1, float32_t& x2, float32_t& y2, size_t const& crop_width,
                   size_t const& crop_height);

struct GridAndStride
{
    int32_t grid0;
    int32_t grid1;
    int32_t stride;
};

/**
 * @brief generste the grid with each strid
 * @param target_size_w the taget width of the grid's
 * @param target_size_h the taget height of the grid's
 * @param strides the strides
 * @param grid_strides the output
 */
void GenerateGridsAndStride(int32_t const target_size_w, int32_t const target_size_h, std::vector<int32_t>& strides,
                            std::vector<GridAndStride>& grid_strides);

/**
 * @brief generate the proposal from yolox's head
 * @param grid_strides the grid of each strides
 * @param feat_ptr the ptr of yolox's head output
 * @param pro_threshold the score threshold
 * @param object output
 * @param num_calss the number of category that the model can predict
 * @param num_calss2 the number of category(additional), for multi task
 */
void GenerateYoloxProposals(std::vector<GridAndStride> grid_strides, const float32_t* feat_ptr,
                            float32_t prob_threshold, std::vector<BoxObject>& objects, int32_t const num_class = 13U,
                            int32_t const num_class2 = 0U);

/**
 * @brief generate the proposal from yolox's head
 * @param grid_strides the grid of each strides
 * @param feat_ptr the ptr of yolox's head output
 * @param pro_threshold the score threshold
 * @param object output
 * @param num_calss the number of category that the model can predict
 */
void GenerateYoloxProposalsWithKeypoints(std::vector<GridAndStride> grid_strides, const float32_t* feat_ptr,
                                         float32_t prob_threshold, std::vector<BoxObject>& objects,
                                         int32_t const num_class);
/**
 * @brief sort bbox in descending order with quick sort algorithm
 * @param faceobjects inputs
 * @param left the left point
 * @param right the right point
 */
void QsortDescentInplace(std::vector<BoxObject>& faceobjects, int32_t left, int32_t right);

/**
 * @brief sort bbox in descending order with quick sort algorithm
 * @param faceobjects inputs
 */
void QsortDescentInplace(std::vector<BoxObject>& objects);

/**
 * @brief nms algoritm
 * @param faceobjects the proposal bbox
 * @param picked the reamin bbox
 * @param nms_threshold the threshold of nms algoritm
 */
void NmsSortedBboxes(const std::vector<BoxObject>& faceobjects, std::vector<int32_t>& picked, float32_t nms_threshold);

}  // namespace dnn
}  // namespace holo
