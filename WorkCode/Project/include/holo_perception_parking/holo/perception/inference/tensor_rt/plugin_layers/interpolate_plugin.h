/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common.h
 * @brief Header file of tensorrt plugins
 * @author lizhijian (lizhijian@holomatic.com)
 * @date "2020-11-18"
 */

#ifndef _RESIZE_PLUGIN_H_
#define _RESIZE_PLUGIN_H_

#include <NvCaffeParser.h>
#include <NvInfer.h>
#include <cuda_fp16.h>
#include <cuda_runtime_api.h>
#include <cudnn.h>
#include <stdio.h>

#include <cassert>
#include <cstring>
#include <iostream>

template <typename T>
void IGNORED(T& t)
{
    (void)t;
}

template <typename T>
inline void Serialize(char*& buffer, const T& val)
{
    *reinterpret_cast<T*>(buffer) = val;
    buffer += sizeof(T);
}

template <typename T>
inline void Deserialize(const char*& buffer, T& val)
{
    val = *reinterpret_cast<const T*>(buffer);
    buffer += sizeof(T);
}

/* Nearest Neighbor Plugin for TRT  */
class InterpolatePlugin : public nvinfer1::IPlugin
{
public:
    // can eb acquired from getOutputDimensions's inputs
    int old_w_, old_h_;  // old dimensions
    int channel_size_;
    int new_h_, new_w_;  // new dimensions

    void setOutputShape(int new_h, int new_w)
    {
        new_h_ = new_h;
        new_w_ = new_w;

        // status_ |= 1;
    }
    /*
    bool supportsFormat(nvinfer1::DataType type,
                        nvinfer1::PluginFormat format) const override
    {
        return (type == nvinfer1::DataType::kFLOAT ||
                type == nvinfer1::DataType::kHALF ||
                type == nvinfer1::DataType::kINT8 ) &&
                format == nvinfer1::PluginFormat::kNCHW;
    }
    */

    InterpolatePlugin(const nvinfer1::Weights* weights, int nbWeights);
    InterpolatePlugin(const void* data, size_t length);

    int getNbOutputs() const override
    {
        return 1;
    }
    nvinfer1::Dims getOutputDimensions(int index, const nvinfer1::Dims* inputs, int nbInputDims) override;
    void           configure(const nvinfer1::Dims* inputs, int nbInputs, const nvinfer1::Dims* outputs, int nbOutputs,
                             int) override;
    int            initialize() override;
    virtual void   terminate() override;

    virtual size_t getWorkspaceSize(int) const override
    {
        return 0;
    }
    virtual int    enqueue(int batchSize, const void* const* inputs, void** outputs, void* workspace,
                           cudaStream_t stream) override;
    virtual size_t getSerializationSize() override;
    virtual void   serialize(void* buffer) override;

private:
    // int _ndims;
    // float _scale[nvinfer1::Dims::MAX_DIMS];
    // nvinfer1::Dims _output_dims;

    // bool status_;

    // float h_coord_[1980];
    // float w_coord_[1980];
};

#endif