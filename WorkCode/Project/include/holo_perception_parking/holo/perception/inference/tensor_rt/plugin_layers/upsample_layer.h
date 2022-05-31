/*!
 *  \brief upsample layer for TensorRT
 *  \author wentian
 *  \date 2019-01-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_DETECTION_TENSORRT_PLUGIN_LAYERS_UPSAMPLE_LAYER_H_
#define HOLO_PERCEPTION_DETECTION_TENSORRT_PLUGIN_LAYERS_UPSAMPLE_LAYER_H_

#include <cublas_v2.h>

#include "holo/perception/inference/cuda/plugin_layers.h"
#include "holo/perception/inference/tensor_rt/common.h"

namespace holo
{
namespace perception
{
// TODO(haowentian): only support batch size == 1
class UpsampleLayer : public nvinfer1::IPluginExt
{
public:
    /// @brief create the plugin by scale factor
    UpsampleLayer(const float32_t scale);

    /// @brief create the plugin at runtime from a byte stream
    UpsampleLayer(const void* data, size_t length);

    virtual ~UpsampleLayer() = default;

    int getNbOutputs() const override
    {
        return 1;
    }

    nvinfer1::Dims getOutputDimensions(int index, const nvinfer1::Dims* inputs, int nbInputDims) override;

    void configureWithFormat(const nvinfer1::Dims* inputDims, int nbInputs, const nvinfer1::Dims* outputDims,
                             int nbOutputs, nvinfer1::DataType type, nvinfer1::PluginFormat format,
                             int maxBatchSize) override
    {
        (void)inputDims;
        (void)nbInputs;
        (void)outputDims;
        (void)nbOutputs;
        (void)format;
        (void)maxBatchSize;
        data_type_ = type;
    }

    int initialize() override
    {
        return 0;
    }

    void terminate() override{};

    size_t getWorkspaceSize(int maxBatchSize) const override
    {
        (void)maxBatchSize;
        return 0;
    }

    int enqueue(int batchSize, const void* const* inputs, void** outputs, void* workspace,
                cudaStream_t stream) override;

    size_t getSerializationSize() override
    {
        return sizeof(input_dim_) + sizeof(data_type_) + sizeof(scale_) + sizeof(output_height_) +
               sizeof(output_width_);
    }

    void serialize(void* buffer) override;

    bool supportsFormat(nvinfer1::DataType type, nvinfer1::PluginFormat format) const override
    {
        return (type == nvinfer1::DataType::kFLOAT || type == nvinfer1::DataType::kHALF ||
                type == nvinfer1::DataType::kINT8) &&
               format == nvinfer1::PluginFormat::kNCHW;
    }

private:
    nvinfer1::Dims     input_dim_;
    nvinfer1::DataType data_type_;
    float              scale_;
    int                output_height_;
    int                output_width_;

    void* input_buffer_;
    void* output_buffer_;
};

}  // namespace perception
}  // namespace holo

#endif  /// HOLO_PERCEPTION_DETECTION_TENSORRT_PLUGIN_LAYERS_UPSAMPLE_LAYER_H_
