/*
 * @Author: zhouchengwei
 */

#ifndef _TEST_TIDL_INFERENCE_FREESPACE_
#define _TEST_TIDL_INFERENCE_FREESPACE_

#include <holo/perception/app/test_tidl_inference.h>
#include <glog/logging.h>

namespace holo
{
namespace perception
{
class TidlInferenceFs : public TidlInferenceDet
{
public:
    TidlInferenceFs(std::string cfg_file) : TidlInferenceDet(cfg_file)
    {
        LOG(INFO) << "create tidlInferenceFs" << std::endl;
    }
    bool decode(const std::vector<cv::Mat*>& mask_ptrs, std::vector<std::vector<std::vector<cv::Point>>>& contours,
                std::vector<std::vector<cv::Vec4i>>& hierarchy, int index, std::string output_name, int num,
                int save_res = 0);
    void ApplyMaskOnDebugImg(int index, cv::Mat class_image);
    std::vector<cv::Mat> debug_imgs_;
};

}  // namespace perception
}  // namespace holo

#endif
