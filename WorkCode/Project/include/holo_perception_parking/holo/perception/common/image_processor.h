/*!
 *  \brief class for image processing
 *  \author haowentian
 *  \date 2019.04.22
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_COMMON_IMAGE_PROCESSOR_H_
#define HOLO_PERCEPTION_COMMON_IMAGE_PROCESSOR_H_

#include <numeric>
#include <string>
#include <vector>
#include <glog/logging.h>
#include <opencv2/opencv.hpp>
#include "holo/core/exception.h"
#include "holo/core/types.h"

namespace holo
{
namespace perception
{

class ImageProcessor
{
public:
// Image info
struct ImageInfo
    {
        // absolute paths for images
        std::vector<std::string> paths;
        // image loaded height
        size_t height;
        // image loaded width
        size_t width;
        // scale
        float32_t scale = 1 / 255.0;
        // mean value in RGB order
        std::vector<float32_t> mean = {0.0, 0.0, 0.0};
        // deviation value in RGB order
        std::vector<float32_t> dev = {0.0, 0.0, 0.0};
        // value which will be padded (to loaded size)
        float32_t padding_with = 0.0;
    };

explicit ImageProcessor(ImageInfo _image_info):image_info_(_image_info) {};

/**
* @brief load image from path for tensorrt, output size should not be smaller than
*        original image; if output size is larger than input size, extra pixels will
*        be padded
*
* @param [out] output data in NCHW order
* @param [in] in_RGB_order if in_RGB_order is true, the order of image will be
              converted into RGB regardless of original image form; otherwise
              keep original image form
*
* @return
*/
bool LoadImageAsNCHW(std::vector<holo::float32_t>& output,
					 const bool in_RGB_order=true);

private:
    ImageInfo image_info_;
};

}   /// end namespace perception
}   /// end namespace holo

#endif
