/*!
 *  \brief inference class warp of tensorrt
 *         this class accepts multi inputs and outputs
 *  \author huanglihong
 *  \date 20180109
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_TENSORRT_INFERENCE_H_
#define HOLO_PERCEPTION_TENSORRT_INFERENCE_H_

#include <NvCaffeParser.h>
#include <NvInfer.h>
#include <cuda_runtime_api.h>
#include <cudnn.h>

#include <array>
#include <memory>
#include <string>
#include <unordered_map>

#include "holo/core/types.h"
#include "holo/perception/inference/tensor_rt/calibrator.h"
#include "holo/perception/inference/tensor_rt/common.h"
#include "holo/perception/inference/tensor_rt/plugin_factory.h"
#include "NvOnnxParser.h"
#include "tensor_rt.pb.h"

namespace holo
{
namespace perception
{
/// manage input and output gpu buffer
class Tensor
{
public:
    /// smart pointor
    typedef std::shared_ptr<Tensor>       Ptr;
    typedef std::shared_ptr<const Tensor> ConstPtr;

    /// constuctor
    Tensor()
    {
    }
    Tensor(std::string name, size_t channel, size_t height, size_t width, size_t index, void* p_gpu_buffer)
      : name_(name), channel_(channel), height_(height), width_(width), index_(index), p_gpu_buffer_(p_gpu_buffer)
    {
    }

    /// getter and setter
    inline const std::string& name() const noexcept
    {
        return name_;
    }

    inline void name(std::string name)
    {
        name_ = name;
    }

    inline size_t channel() const noexcept
    {
        return channel_;
    }

    inline void channel(size_t channel)
    {
        channel_ = channel;
    }

    inline size_t height() const noexcept
    {
        return height_;
    }

    inline void height(size_t height)
    {
        height_ = height;
    }

    inline size_t width() const noexcept
    {
        return width_;
    }

    inline void width(size_t width)
    {
        width_ = width;
    }

    inline size_t index() const noexcept
    {
        return index_;
    }

    inline void index(size_t index)
    {
        index_ = index;
    }

    inline void* p_gpu_buffer() const noexcept
    {
        return p_gpu_buffer_;
    }

    inline void p_gpu_buffer(void* p_gpu_buffer)
    {
        p_gpu_buffer_ = p_gpu_buffer;
    }

    /// one batch size, note it is the ele num not the buffer size
    inline size_t Size() const
    {
        return channel_ * height_ * width_;
    }

private:
    std::string name_;
    size_t      channel_;
    size_t      height_;
    size_t      width_;
    size_t      index_;         /// index managemented in TensorRT
    void*       p_gpu_buffer_;  /// gpu memory in TensorRT
};

class TRTInference
{
public:
    /// smart pointor
    typedef std::shared_ptr<TRTInference>       Ptr;
    typedef std::shared_ptr<const TRTInference> ConstPtr;

    /**
     * @brief construct with config file
     *
     * @param config config path
     *
     * @return
     */
    explicit TRTInference(const TensorRTConfig& config);

    virtual ~TRTInference();

    /// inner data type of TensorRT
    /// need GPU support
    enum TensorType : uint8_t
    {
        UNKNOWN = 1,
        FLOAT,
        HALF,
        INT8
    };
    typedef typename std::underlying_type<TensorType>::type TensorTypeUnderlying;

    /// data bytes
    static const size_t                              kTensorTypeNum = 4;
    static const std::array<uint8_t, kTensorTypeNum> kTensorTypeBytes;

    inline TensorTypeUnderlying tensor_type() const
    {
        return tensor_type_;
    }

    inline void tensor_type(TensorType tensor_type)
    {
        tensor_type_ = tensor_type;
    }

    inline void tensor_type(uint8_t tensor_type)
    {
        tensor_type_ = static_cast<TensorType>(tensor_type);
    }

    const Tensor& GetTensor(const std::string& tensor_name);

    /**
     * @brief public api used by outside
     *
     * @param deployFile name for caffe prototxt
     * @param modelFile name for model
     * @param outputs network outputs
     * @param maxBatchSize batch size
     * @param pluginFactory factory for plugin layers
     * @param calibrator calibrator for int8 mode
     * @param gieModelStream output stream for the GIE model
     *
     * @return
     */
    void CaffeToGIEModel(const std::string& deployFile, const std::string& modelFile,
                         const std::vector<std::string>& outputs, unsigned int maxBatchSize,
                         nvcaffeparser1::IPluginFactory* pluginFactory, nvinfer1::IInt8Calibrator* calibrator,
                         nvinfer1::IHostMemory** gieModelStream, std::string serialized_file_path);
    /**
     * @brief 
     * 
     * @param modelFile 
     * @param maxBatchSize 
     * @param trtModelStream 
     * @param serialized_model_file 
     * @return true 
     * @return false 
     */
    bool onnxToTRTModel(const std::string& modelFile, // name of the onnx model
                                  unsigned int maxBatchSize,    // batch size - NB must be at least as large as the batch we want to run with
                                  nvinfer1::IHostMemory*& trtModelStream,
                                  std::string serialized_model_file); // output buffer for the TensorRT model


    /**
     * @brief do inference, host memory must be initialized outside
     *
     * @param inputs cpu inputs memory
     * @param outputs cpu outputs memory
     *
     * @return whether sccuess
     */
    void Inference(const std::vector<std::pair<std::string, const void* const> >& inputs,
                   const std::vector<std::pair<std::string, void*> >&             outputs);

private:
    /// TensorRT objects
    Logger                       gLogger_;
    nvinfer1::IRuntime*          runtime_;
    nvinfer1::ICudaEngine*       engine_;
    nvinfer1::IExecutionContext* context_;
    cudaStream_t                 stream_;
    PluginFactory                plugin_factory_;

    /// buffers
    std::unordered_map<std::string, Tensor> tensors_;

    /// data type
    TensorType tensor_type_;

    /// gpu buffers pointor, used by TensorRT
    void** p_gpu_buffers_;

    /// config object, generated by protobuf
    TensorRTConfig config_;
};

}  // namespace perception
}  // namespace holo

#endif
