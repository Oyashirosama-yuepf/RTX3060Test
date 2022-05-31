/*!
 *  \brief common define for cuda
 *  \author wentian
 *  \date 2019-01-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTION_CUDA_COMMON_H_
#define HOLO_PERCEPTION_CUDA_COMMON_H_

#include <cuda_runtime_api.h>
#include <glog/logging.h>
#if 0
#include <stdexcept>
#endif

namespace holo
{
namespace perception
{

/// CUDA: various checks for different function calls
#define CUDACHECK(condition) \
  do { \
    cudaError_t error = condition; \
    CHECK_EQ(error, cudaSuccess) << " " << cudaGetErrorString(error); \
  } while (0)

/// CUDA: grid stride loop
#ifndef CUDA_KERNEL_LOOP
#define CUDA_KERNEL_LOOP(i, n) \
    for (int i = blockIdx.x * blockDim.x + threadIdx.x; \
        i < (n); \
        i += blockDim.x * gridDim.x)
#endif

/// CUDA: check for error after kernel execution
#define CUDA_POST_KERNEL_CHECK CUDACHECK(cudaPeekAtLastError())

/// CUDA: use 512 threads per block
/// TODO(haowentian): different platform may have different number of threads
const int CUDA_NUM_THREADS = 512;

/// CUDA: number of blocks for threads.
inline int CUDA_GET_BLOCKS(const int N) {
  return (N + CUDA_NUM_THREADS - 1) / CUDA_NUM_THREADS;
}

/// Definition of resample type
enum class ResampleType : uint8_t
{
    NEAREST = 0,
    CUBIC = 1,
    LINEAR = 2,
    BOX = 3
};



}   /// end namespace perception
}   /// end namespace holo

#endif  /// HOLO_PERCEPTION_CUDA_COMMON_H_
