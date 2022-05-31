/**
 * @file vision_freespace_avm_tidl_inference.h
 * @brief This header file defines tidl inference class for freespace avm.
 * @author zhouchengwei (zhouchengwei@holomatic.com)
 * @date "2021-04-27"
 */

#ifndef _HOLO_PERCEPTION_FREESPACE_AVM_TIDL_INFERENCE_
#define _HOLO_PERCEPTION_FREESPACE_AVM_TIDL_INFERENCE_

#include <holo/perception/app/test_tidl_inference.h>
#include <glog/logging.h>

namespace holo
{
namespace perception
{
namespace tools
{
class GetTimeDiffApp
{
public:
    struct timeval start, end;
    void           StartTiming()
    {
        gettimeofday(&start, NULL);
    }
    float GetTimeDiff()  // ms
    {
        gettimeofday(&end, NULL);
        return (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_usec - start.tv_usec) / 1e3;
    }
};
}  // namespace tools

class TidlInferenceDetFs : public TidlInferenceDet
{
public:
    TidlInferenceDetFs(std::string cfg_file) : TidlInferenceDet(cfg_file)
    {
        LOG(INFO) << "create freespace avm tidl inference." << std::endl;
    }

    bool init(cv::Mat& mask, int split_num)
    {
        LOG(INFO) << "start to init freespace infer.";
        initImageBoundaryPoints();
        LOG(INFO) << "finish boundary init.";
        initImagePointsQuadrantMap(mask, split_num);
        LOG(INFO) << "finish map init.";
        return true;
    }

    bool JudgeCenterMax(int index_c, int index_h, int index_w, FeatureMap& hm_feature);

    bool decode(std::vector<std::vector<std::vector<float>>>& det_result, int split_num, float confidence_threshold,
                bool nms_flag, bool background_flag);
    // void ApplyMaskOnDebugImg(int index, cv::Mat class_image);
    // std::vector<cv::Mat> debug_imgs_;

private:
    struct edge_point
    {
        int x;
        int y;
    };
    std::vector<std::vector<int>>                             per_sector_index_mask_;
    std::vector<std::vector<edge_point>>                      image_boundary_points_;
    std::vector<std::vector<std::vector<std::vector<float>>>> points_quadrants_map_;
    void                                                      initImageBoundaryPoints();
    void                                                      initImagePointsQuadrantMap(cv::Mat& mask, int split_num);
};

}  // namespace perception
}  // namespace holo

#endif
