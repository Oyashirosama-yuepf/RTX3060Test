/*!
 *  \brief transpose (BHWC2BHCHW) layer for TensorRT
 *  \author pengcheng
 *  \date 2019-06-18
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_DETECTION_TENSORRT_PLUGIN_LAYERS_TRANSPOSE_LAYER_H_
#define HOLO_PERCEPTION_DETECTION_TENSORRT_PLUGIN_LAYERS_TRANSPOSE_LAYER_H_

#include <iostream>

#include "holo/perception/inference/cuda/plugin_layers.h"
#include "holo/perception/inference/tensor_rt/common.h"

namespace holo
{
namespace perception
{
class BHWC2BCHWLayer : public nvinfer1::IPluginExt
{
public:
    BHWC2BCHWLayer();
    BHWC2BCHWLayer(const void* data, size_t length);
    ~BHWC2BCHWLayer() = default;
    int getNbOutputs() const override
    {
        return 1;
    }
    nvinfer1::Dims getOutputDimensions(int index, const nvinfer1::Dims* inputs, int nbInputDims) override;
    void           configureWithFormat(const nvinfer1::Dims* inputDims, int nbInputs, const nvinfer1::Dims* outputDims,
                                       int nbOutputs, nvinfer1::DataType type, nvinfer1::PluginFormat format, int maxBatchSize)
    {
        (void)inputDims;
        (void)nbInputs;
        (void)outputDims;
        (void)nbOutputs;
        (void)format;
        (void)maxBatchSize;

        dataType = type;
    }

    int initialize() override
    {
        return 0;
    }
    void terminate() override
    {
    }

    size_t getWorkspaceSize(int maxBatchSize) const
    {
        (void)maxBatchSize;
        return 0;
    }

    int enqueue(int batchSize, const void* const* inputs, void** outputs, void* workspace,
                cudaStream_t stream) override;

    size_t getSerializationSize() override
    {
        return sizeof(dataType) + sizeof(height_) + sizeof(width_) + sizeof(channel_) + sizeof(input_dims_);
    }

    void serialize(void* buffer) override;

    bool supportsFormat(nvinfer1::DataType type, nvinfer1::PluginFormat format) const override
    {
        return (nvinfer1::DataType::kFLOAT == type || nvinfer1::DataType::kHALF == type ||
                nvinfer1::DataType::kINT8 == type || nvinfer1::DataType::kINT32 == type) &&
               nvinfer1::PluginFormat::kNCHW == format;
    }

private:
    nvinfer1::DataType dataType;
    nvinfer1::Dims     input_dims_;
    int                height_;
    int                width_;
    int                channel_;
};
}  // namespace perception
}  // namespace holo

#endif