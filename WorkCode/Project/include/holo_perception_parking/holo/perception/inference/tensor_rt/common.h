/*!
 *  \brief common functions used by TensorRT
 *  \author huanglihong
 *  \date JUNE 4, 2018
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_DETECTION_TENSORRT_COMMON_H_
#define HOLO_PERCEPTION_DETECTION_TENSORRT_COMMON_H_

#include <NvCaffeParser.h>
#include <NvInfer.h>
#include <cublas_v2.h>
#include <cuda_runtime_api.h>
#include <cudnn.h>

#include "holo/core/exception.h"
#include "holo/core/types.h"
#include "holo/perception/inference/cuda/common.h"

namespace holo
{
namespace perception
{
/// Logger for GIE info/warning/errors
class Logger : public nvinfer1::ILogger
{
public:
    /// @brief this class mainly used by TensorRT's IBuilder
    void log(nvinfer1::ILogger::Severity severity, const char* msg) override;
    
    Logger(Severity severity = Severity::kWARNING)
        : mReportableSeverity(severity)
    {
    }
    
    //!
    //! \enum TestResult
    //! \brief Represents the state of a given test
    //!
    enum class TestResult
    {
        kRUNNING, //!< The test is running
        kPASSED,  //!< The test passed
        kFAILED,  //!< The test failed
        kWAIVED   //!< The test was waived
    };

    //!
    //! \brief Forward-compatible method for retrieving the nvinfer::ILogger associated with this Logger
    //! \return The nvinfer1::ILogger associated with this Logger
    //!
    //! TODO Once all samples are updated to use this method to register the logger with TensorRT,
    //! we can eliminate the inheritance of Logger from ILogger
    //!
    nvinfer1::ILogger& getTRTLogger()
    {
        return *this;
    }
    
    Severity getReportableSeverity() const
    {
        return mReportableSeverity;
    }
    
    Severity mReportableSeverity;

};

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

// TODO(haowentian): how about int8?
inline size_t Type2Size(nvinfer1::DataType type)
{
    return type == nvinfer1::DataType::kHALF ? sizeof(__half) : sizeof(float);
}

// TODO(haowentian): how about int8?
inline void CopyTensorsOnGPU(const void* const* inputs, void** outputs, cudaStream_t stream, const size_t input_index,
                             const size_t output_index, const size_t inputs_offset, const size_t outputs_offset,
                             const size_t data_size, const nvinfer1::DataType data_type)
{
    switch (data_type)
    {
        case nvinfer1::DataType::kHALF: {
            cudaMemcpyAsync((void*)((__half*)(outputs[output_index]) + outputs_offset),
                            (void*)((__half*)(inputs[input_index]) + inputs_offset), data_size * sizeof(__half),
                            cudaMemcpyDeviceToDevice, stream);
            break;
        }
        default: {
            cudaMemcpyAsync((void*)((float*)(outputs[output_index]) + outputs_offset),
                            (void*)((float*)(inputs[input_index]) + inputs_offset), data_size * sizeof(float),
                            cudaMemcpyDeviceToDevice, stream);
            break;
        }
    }
}

}  // namespace perception
}  // namespace holo

#endif
