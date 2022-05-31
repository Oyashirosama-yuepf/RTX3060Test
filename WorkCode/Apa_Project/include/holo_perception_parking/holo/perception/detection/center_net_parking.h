/*!
 *  \brief CenterNetParking inference
 *  \author pengcheng
 *  \date 20190606
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_PERCEPTON_DETECTION_CenterNetParking_H_
#define HOLO_PERCEPTON_DETECTION_CenterNetParking_H_
#include "holo/perception/detection/image_detector.h"
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "holo/perception/common/image_bbox2d.h"
#include "holo/perception/detection/hard_nms.h"
#include <centerNet.pb.h>

namespace holo
{
namespace perception
{
/**
 * @brief define CenterNetParking class
 */
template <typename Scalar>
class CenterNetParking : public ImageDetectorBase<Scalar>
{
public:
    using Ptr      = std::shared_ptr<CenterNetParking>;
    using ConstPtr = std::shared_ptr<const CenterNetParking>;
    typedef ImageBBox2D<Scalar>          ImageBBox2DType;
    typedef Box2DT<Scalar>               Box2DType;
    typedef HardNMS<Scalar>              HardNMSType;
    typedef std::shared_ptr<HardNMSType> HardNMSTypePtr;
    using ObstacleCamera    = ObstacleVisionT<Scalar>;
    using ObstacleCameraPtr = std::shared_ptr<ObstacleVisionT<Scalar>>;
    typedef typename holo::ObstaclePtrListT<ObstacleVisionT<Scalar>, holo::VISION_OBSTACLE_LIST_COMMON_CAPACITY>
                                                     CameraObstacleList;
    typedef std::list<ObstacleCameraPtr>             ObstacleCameraPtrList;
    typedef std::function<void(CameraObstacleList&)> ObstacleDetectionCallback;

    std::vector<std::vector<cv::Point2f>> hm_pts_;
    std::vector<std::vector<int>>         hm_cls_;
    std::vector<std::vector<cv::Point2f>> hm_keypoints_;
    /**
     * @brief the constructor.
     * @param cfg_file the path of the config file.
     */
    explicit CenterNetParking(const std::string& config_path);
    virtual ~CenterNetParking();

    /**
     * @brief Detect objects from images.
     * @param images images that to be inferenced by DNN.
     * @param [out] objects objects which are detected from the input images.
     */
    virtual bool Detect(const std::vector<cv::Mat>& images, std::vector<std::list<ImageBBox2DType>>& objects);

    virtual bool DetectKeypoints(const std::vector<cv::Mat>& images, std::vector<std::list<ImageBBox2DType>>& objects);
    
    // virtual bool DetectKeypoints(const std::vector<cv::Mat>& images, std::vector<std::vector<float>>& det_result);
    virtual bool DetectKeypoints(const std::vector<cv::Mat>&  images,
                                 const std::vector<std::string>& camera_inference_list,
                                 std::map<std::string, std::vector<std::vector<float>>>& det_result);

private:
    /**
     * @brief Decode the featuremap into objects.
     * @param [out] objects objects which are detected from the input images.
     */
    void Decode(std::vector<std::list<ImageBBox2DType>>& objects);

    /**
     * @brief Decode the featuremap into objects.
     * @param [out] objects objects which are detected from the input images.
     */
    void DecodeKeypoints(std::vector<std::list<ImageBBox2DType>>& objects, std::vector<std::vector<int>> img_wh);

    
    /**
     * @brief NMS filter the detected objects.
     * @param sigmoid_hm sigmoid features from the dnn output.
     * @param max_pool_hm max_pooling features from the dnn output.
     * @param wh width-height features from the dnn output.
     * @param reg xy modifier from the dnn output.
     * @param [out] objects objects which are detected from the input images.
     */
    void NMS(float32_t* sigmoid_hm, float32_t* max_pool_hm, float32_t* wh, float32_t* reg,
             std::vector<std::list<ImageBBox2DType>>& objects);
    void NMS(float32_t* sigmoid_hm, float32_t* max_pool_hm, float32_t* wh, float32_t* reg, float32_t* theta,
             float32_t* keypoints, float32_t* sigmoid_hm_keypoints, float32_t* max_pool_hm_keypoints,
             std::vector<std::list<ImageBBox2DType>>& objects, std::vector<std::vector<int>> img_wh);

    CenterNetConfig config_;
    // RTInference::Ptr p_trt_inference_;  //fix
    void*          p_trt_inference_;
    size_t         batchsize;
    size_t         real_batch_size;
    size_t         cnn_input_width_;
    size_t         cnn_input_height_;
    size_t         cnn_input_channel_;
    float32_t*     cnn_input_data_;
    size_t         cnn_output_feature_map_height_;
    size_t         cnn_output_feature_map_width_;
    float32_t      score_threshold;
    size_t         cnn_output_channel_;
    size_t         down_ratio_;
    size_t         image_height_;
    size_t         image_width_;
    HardNMSTypePtr nms_;

    std::vector<std::pair<std::string, float32_t*>> inputs_;
    std::vector<std::pair<std::string, float32_t*>> outputs_;

    void InitConfig(const std::string& config_path);
    /// do computation, inputs_ -> outputs_
    void Inference(void);
    /// resize image and copy data to inputs_
    void PreProcess(const std::vector<cv::Mat>& images);
    /// save input and out put
    void                 SaveFeature(const std::string& save_dir);
    holo::Classification getClassesMaping(size_t idx);
    void                 Publish();
};


class FeatureMap
{
   public:
      float* data;
      int channel_;
      int height_;
      int width_;
      int data_len_;
      FeatureMap();
      FeatureMap(float* data_tmp, int channel, int height, int width);
      virtual ~FeatureMap();
      bool JudgeCenterMax(int index);
      float GetDataElement(int index_c, int index_h, int index_w);
    //   void StoreFeauremapData(std::string file_tmp);
};


}  // namespace perception
}  // namespace holo

#endif
