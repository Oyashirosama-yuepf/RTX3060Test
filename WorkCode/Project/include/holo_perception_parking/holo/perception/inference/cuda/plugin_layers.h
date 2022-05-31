/*!
 *  \brief GPU implementation of plugin layers for TensorRT
 *  \author wentian
 *  \date 2019-01-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_CUDA_PLUGIN_LAYERS_H_
#define HOLO_PERCEPTION_CUDA_PLUGIN_LAYERS_H_

#include "holo/perception/inference/cuda/common.h"

// TODO(haowentian): multi-batch needs to be tested
namespace holo
{
namespace perception
{
/**
 * @brief argmax layer in gpu for argmax along channel axis
 *
 * @param input [in] pointer of input buffer in NCHW format
 * @param output [out] pointer of output buffer in NCHW format
 * @param batch_size [in] batch size
 * @param input_channels [in] channel size of input feature map
 * @param input_height [in] height of input feature map
 * @param input_width [in] width of input feature map
 */
void ArgmaxGPU(const float* input,
               float* output,
               const int batch_size,
               const int input_channels,
               const int input_height,
               const int input_width);

/**
 * @brief resample layer in gpu for nearest/cubic/linear/box interpolation,
 *        given input and output size of feature maps
 *
 * @param input [in] pointer of input buffer in NCHW format
 * @param output [out] pointer of output buffer in NCHW format
 * @param batch_size [in] batch size
 * @param input_channels [in] channel size of input feature map
 * @param input_height [in] height of input feature map
 * @param input_width [in] width of input feature map
 * @param output_channels [in] channel size of output feature map
 * @param output_height [in] height of output feature map
 * @param output_width [in] width of output feature map
 * @param resample_type [in] resample type, NEAREST/CUBIC/LINEAR/BOX
 * @param is_antialias [in] if antialias while down sampling or not
 */
void ResampleGPU(const float* input,
                 float* output,
                 const int batch_size,
                 const int input_channels,
                 const int input_height,
                 const int input_width,
                 const int output_channels,
                 const int output_height,
                 const int output_width,
                 const ResampleType resample_type,
                 const bool is_antialias = false);

/**
 * @brief upsample layer in gpu for nearest upsample, given upsample scale
 * 
 * @param input [in] pointer of input buffer in NCHW format
 * @param output [out] pointer of output buffer in NCHW format
 * @param batch_size [in] batch size
 * @param output_channels [in] channel size of output feature maps
 * @param output_height [in] height of output feature map
 * @param output_width [in] width of output feature map
 * @param scale [in] upsample scale
 */
void UpsampleGPU(const float* input,
                 float* output,
                 const int batch_size,
                 const int output_channels,
                 const int output_height,
                 const int output_width,
                 const int scale);

/**
 * @brief transpose dataset channel orders function util, init some info, 
 * 
 * @param batch_size [in] batch size
 * @param height [in] height size of data's feature map
 * @param width[in] width size of data's feature map
 * @param channel [in] channel szie of data's feature map
 */
void ConvtChannelInit(const int batch_size,
                      const int height,
                      const int width,
                      const int channel);

/**
 * @brief transpose dataSet channel order form BHWC to BCHW
 *
 * @param input [in] pointer of input buffer in BCHW format
 * @param output [out] pointer of output buffer in BCHW format
 * @param batch_size [in] batch size
 * @param channels [in] channel size of dataSet's feature maps
 * @param height [in] height of dataSet's feature map
 * @param width [in] width of dataSet's feature map
 * @param init [in] Whether to call the initialization function(ConvtChannelInit)
 */
template<typename T>
void ConvtBHWC2BCHWGPU(const u_char* input,
                       T* output,
                       const int batch_szie,
                       const int height,
                       const int width,
                       const int channel,
                       const bool init);
}


}

#endif  /// HOLO_PERCEPTION_CUDA_PLUGIN_LAYERS_H_
