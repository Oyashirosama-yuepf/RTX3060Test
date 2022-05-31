/*!
 *  \brief
 *  \author pengcheng (pengcheng@holomatic.com)
 *  \date 2019-08-22
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_COMMON_IMAGEBBOX2D_CONVERT_H_
#define HOLO_PERCEPTION_COMMON_IMAGEBBOX2D_CONVERT_H_

#include "holo/perception/common/image_bbox2d.h"
#include <holo/obstacle/obstacle_vision.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_list.h>

namespace holo
{
namespace perception
{

void Convert(const ImageBBox2D<holo::float32_t>& input, ObstacleVisionT<holo::float32_t> &output);

void Convert(const ObstacleVisionT<holo::float32_t> input, ImageBBox2D<holo::float32_t> &output);
}
}


#endif