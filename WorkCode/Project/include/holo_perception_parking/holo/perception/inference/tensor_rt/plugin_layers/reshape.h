/*!
 *  \brief reshape layer for TensorRT
 *  \author huanglihong
 *  \date 20180509
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_DETECTION_TENSORRT_PLUGIN_LAYERS_RESHAPE_H_
#define HOLO_PERCEPTION_DETECTION_TENSORRT_PLUGIN_LAYERS_RESHAPE_H_

#include <cuda_runtime_api.h>
#include <cudnn.h>

#include "holo/perception/inference/cuda/plugin_layers.h"
#include "holo/perception/inference/tensor_rt/common.h"

namespace holo
{
namespace perception
{
template <int OutC>
class Reshape : public nvinfer1::IPlugin
{
public:
    Reshape()
    {
    }

    /// no parameter need to init
    Reshape(const void* buffer, size_t size)
    {
        (void)size;
        (void)buffer;
    }

    /// @brief get output tensor number
    inline int getNbOutputs() const override
    {
        return 1;
    }

    /// @brief get output dimension
    nvinfer1::Dims getOutputDimensions(int index, const nvinfer1::Dims* inputs, int nbInputDims) override;

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

    /// currently it is not possible for a plugin to execute "in place"
    /// therefore we memcpy the data from the input to the output buffer
    int enqueue(int batchSize, const void* const* inputs, void** outputs, void*, cudaStream_t stream) override;

    /// @brief load the serialization size
    inline size_t getSerializationSize() override
    {
        return 0;
    }

    /// @brief serialize the model
    void serialize(void* buffer) override;

    /// @brief config the model
    void configure(const nvinfer1::Dims* inputs, int nbInputs, const nvinfer1::Dims* outputs, int nbOutputs,
                   int) override;

protected:
    size_t tensor_size_;
};

}  // namespace perception
}  // namespace holo

#endif
