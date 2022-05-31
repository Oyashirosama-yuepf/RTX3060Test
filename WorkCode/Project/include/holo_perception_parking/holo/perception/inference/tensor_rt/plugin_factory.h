/*!
 *  \brief self defined layers, need register in the plugin factory
 *  \author huanglihong
 *  \date 20180509
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_DETECTION_TENSORRT_PLUGIN_FACTORY_H_
#define HOLO_PERCEPTION_DETECTION_TENSORRT_PLUGIN_FACTORY_H_

#include <NvInferPlugin.h>
#include <cuda_runtime_api.h>
#include <cudnn.h>
#include <holo/core/exception.h>

#include <memory>
#include <string>

#include "holo/perception/inference/tensor_rt/common.h"
#include "holo/perception/inference/tensor_rt/plugin_layers/argmax_layer.h"
#include "holo/perception/inference/tensor_rt/plugin_layers/interpolate_plugin.h"
#include "holo/perception/inference/tensor_rt/plugin_layers/resample_layer.h"
#include "holo/perception/inference/tensor_rt/plugin_layers/reshape.h"
#include "holo/perception/inference/tensor_rt/plugin_layers/slice_layer.h"
#include "holo/perception/inference/tensor_rt/plugin_layers/transpose_layer.h"
#include "holo/perception/inference/tensor_rt/plugin_layers/upsample_layer.h"
#include "holo/perception/inference/tensor_rt/plugin_layers/yolov3_decoder.h"

namespace holo
{
namespace perception
{
/// @brief plugin factory
class PluginFactory : public nvinfer1::IPluginFactory, public nvcaffeparser1::IPluginFactoryExt
{
public:
    /// @brief constructor
    virtual nvinfer1::IPlugin* createPlugin(const char* layerName, const nvinfer1::Weights* weights,
                                            int nbWeights) override;

    /// @brief constructor
    nvinfer1::IPlugin* createPlugin(const char* layerName, const void* serialData, size_t serialLength) override;

    /// @brief check the name whether is a plugin
    bool isPlugin(const char* name) override;
    bool isPluginExt(const char* name) override;

    /// @brief destroy the plugin
    void destroyPlugin();

    /// @brief config for specific plugin layer(s) when needed
    void configResample(const int output_height, const int output_width)
    {
        output_height_ = output_height;
        output_width_  = output_width;
    };

private:
    /// @brief check whether it is upsample layer (with specific scale)
    bool isUpsample(const char* name);
    bool isUpsample8(const char* name);
    bool isUpsample4(const char* name);

    /// @brief check whether it is resample layer
    bool isResample(const char* name);

    /// @brief check whether it is resample layer
    bool isArgmax(const char* name);

    /// @brief check whether it is transpose(BHWC2BCHW) layer
    bool isBHWC2BCHW(const char* name);

    /// @brief check whether it is slice layer
    bool isSlice(const char* name);

private:
    /// self defined plugins need be registered here
    std::unique_ptr<Reshape<85>>                p_plugin_reshape85_      = nullptr;
    std::unique_ptr<YoloV3Decoder>              p_plugin_yolov3_decoder_ = nullptr;
    std::vector<std::unique_ptr<UpsampleLayer>> ps_plugin_upsample_;
    std::unique_ptr<ResampleLayer>              p_plugin_resample_  = nullptr;
    std::unique_ptr<ArgmaxLayer>                p_plugin_argmax_    = nullptr;
    std::unique_ptr<BHWC2BCHWLayer>             p_plugin_bhwc2bchw_ = nullptr;
    std::unique_ptr<SliceLayer>                 p_plugin_slice_     = nullptr;

    std::unique_ptr<InterpolatePlugin> p_plugin_interpolate_1_    = nullptr;
    std::unique_ptr<InterpolatePlugin> p_plugin_interpolate_2_    = nullptr;
    std::unique_ptr<InterpolatePlugin> p_plugin_interpolate_3_    = nullptr;
    std::unique_ptr<InterpolatePlugin> p_plugin_interpolate_4_    = nullptr;
    std::unique_ptr<InterpolatePlugin> p_plugin_interpolate_5_    = nullptr;
    std::unique_ptr<InterpolatePlugin> p_plugin_interpolate_6_    = nullptr;
    std::unique_ptr<InterpolatePlugin> p_plugin_interpolate_test_ = nullptr;

    void (*nvPluginDeleter)(nvinfer1::plugin::INvPlugin*){[](nvinfer1::plugin::INvPlugin* ptr) { ptr->destroy(); }};
    std::unique_ptr<nvinfer1::plugin::INvPlugin, decltype(nvPluginDeleter)> p_region_proposal_roi_{nullptr,
                                                                                                   nvPluginDeleter};

    static const size_t                              kPluginNum = 20;
    static const std::array<std::string, kPluginNum> kStringPlugin;

    /// parameters for specific layer(s)
    // upsample scale for upsample layer, default is 2
    float upsample_scale_ = 2;
    // output height/width for resample layer
    int output_height_ = 0;
    int output_width_  = 0;
};

}  // namespace perception
}  // namespace holo

#endif
