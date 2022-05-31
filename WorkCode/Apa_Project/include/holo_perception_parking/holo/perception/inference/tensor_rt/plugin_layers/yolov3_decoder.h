/*!
 *  \brief inference yolov3 decoder, it is not implemented yet.
 *  \author huanglihong
 *  \date 20180109
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_DETECTION_TENSORRT_PLUGIN_LAYERS_YOLOV3_DECODER_H_
#define HOLO_PERCEPTION_DETECTION_TENSORRT_PLUGIN_LAYERS_YOLOV3_DECODER_H_

#include <cuda_runtime_api.h>
#include <cudnn.h>

#include "holo/perception/inference/cuda/plugin_layers.h"
#include "holo/perception/inference/tensor_rt/common.h"

namespace holo
{
namespace perception
{
class YoloV3Decoder : public nvinfer1::IPlugin
{
public:
    YoloV3Decoder()
    {
    }

    /// no parameter need to init
    YoloV3Decoder(const void*, size_t)
    {
    }

    /// @brief get output tensor number
    inline int getNbOutputs() const override
    {
        return 1;
    }

    /// @brief get output dimension
    nvinfer1::Dims getOutputDimensions(int, const nvinfer1::Dims*, int) override
    {
        return nvinfer1::DimsCHW(0, 0, 0);
    }

    /// @brief init the model
    inline int initialize() override
    {
        return 0;
    }

    /// @brief terminate the plugin
    inline void terminate() override
    {
    }

    /// @brief get work space size
    inline size_t getWorkspaceSize(int) const override
    {
        return 0;
    }

    /// do computaion
    int enqueue(int, const void* const*, void**, void*, cudaStream_t) override
    {
        return 0;
    }

    /// @brief load the serialization size
    inline size_t getSerializationSize() override
    {
        return 0;
    }

    /// @brief serialize the model
    void serialize(void*) override
    {
    }

    /// @brief config the model
    void configure(const nvinfer1::Dims*, int, const nvinfer1::Dims*, int, int) override
    {
    }

protected:
    size_t tensor_size_;
};

}  // namespace perception
}  // namespace holo

#endif
