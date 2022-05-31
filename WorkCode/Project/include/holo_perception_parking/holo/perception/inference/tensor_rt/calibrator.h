/*!
 *  \brief calibrator class for int8 mode
 *  \author wentian
 *  \date 2019-01-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_TENSORRT_CALIBRATOR_H_
#define HOLO_PERCEPTION_TENSORRT_CALIBRATOR_H_

#include <NvInfer.h>
#include <cuda_runtime_api.h>

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "holo/perception/inference/tensor_rt/batch_stream.h"

namespace holo
{
namespace perception
{
class Int8CacheCalibrator : public nvinfer1::IInt8EntropyCalibrator
{
public:
    Int8CacheCalibrator(BatchStream& stream, int32_t firstBatch, std::string calibrationTableName,
                        bool readCache = true);

    virtual ~Int8CacheCalibrator()
    {
        CUDACHECK(cudaFree(device_input_));
    }

    int getBatchSize() const;

    bool getBatch(void* bindings[], const char* names[], int nbBindings) override;

    const void* readCalibrationCache(size_t& length) override;

    void writeCalibrationCache(const void* cache, size_t length) override;

private:
    BatchStream       stream_;
    std::string       calibration_table_name_;
    bool              read_cache_;
    size_t            input_count_;
    void*             device_input_;
    std::vector<char> calibration_cache_;
};

}  // namespace perception
}  // namespace holo

#endif  /// HOLO_PERCEPTION_TENSORRT_CALIBRATOR_H_
