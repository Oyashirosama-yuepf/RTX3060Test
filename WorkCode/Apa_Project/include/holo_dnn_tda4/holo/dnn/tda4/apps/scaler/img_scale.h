
#include <math.h>
#include <sys/time.h>

#include <atomic>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
class GraphConfig;

class ImgScaleConvert
{
public:
    ImgScaleConvert(int width, int height, int crop_start_x, int crop_start_y, int crop_width, int crop_height,
                    int dl_width, int dl_height);
    ~ImgScaleConvert();
    void GetScaleData(uint64_t y_arr, uint64_t uv_arr, uint8_t*& result_data, int index, bool is_common_copy);
    void GetResData(const std::vector<cv::Mat>& img_src, std::vector<cv::Mat>& img_res, bool is_common_copy = true);

private:
    void* graph_config_;
    int   width_, height_;
    int   output_width_, output_height_;

    std::vector<cv::Mat> img_res_;
};
