/*!
 *  \brief batch stream class for int8 mode
 *  \author wentian
 *  \date 2019-01-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_TENSORRT_BATCH_STREAM_H_
#define HOLO_PERCEPTION_TENSORRT_BATCH_STREAM_H_

#include <NvInfer.h>
#include <assert.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <vector>

#include "holo/perception/common/image_processor.h"
#include "holo/perception/inference/tensor_rt/common.h"

namespace holo
{
namespace perception
{
// TODO(haowentian): we may use TensorRT inner type of batch stream to replace this file
class BatchStream
{
public:
    BatchStream(std::string calibration_list, int32_t firstBatch, int32_t batchSize, int32_t maxBatches,
                ImageProcessor::ImageInfo image_info);
    BatchStream(){};

    void reset(int32_t firstBatch);

    bool next();

    void skip(int32_t skipCount);

    inline float32_t* getBatch()
    {
        return batch_.data();
    }
    // float32_t *getLabels() { return labels_.data(); }
    inline int32_t getBatchesRead() const
    {
        return batch_count_;
    }
    inline int32_t getBatchSize() const
    {
        return batch_size_;
    }
    inline nvinfer1::DimsNCHW getDims() const
    {
        return dims_;
    }

private:
    inline float32_t* getFileBatch()
    {
        return file_batch_.data();
    }
    // inline float32_t* getFileLabels() { return file_labels_.data(); }
    bool update();

private:
    // calibration list
    std::string calibration_list_;
    // batch size
    int32_t batch_size_;
    // max batches
    int32_t max_batches_;
    // Image info
    ImageProcessor::ImageInfo image_info_;
    // Dimension in NCHW format
    nvinfer1::DimsNCHW dims_;
    // Image size
    int32_t image_size_;
    // batch counter
    int32_t batch_count_;
    // file counter
    int32_t file_count_;
    // counter for current batch position
    int32_t file_batch_pos_;
    // images batch buffer
    std::vector<float32_t> batch_;
    // file batch (bath_size * image_size) buffer
    std::vector<float32_t> file_batch_;
};

}  // namespace perception
}  // namespace holo

#endif
