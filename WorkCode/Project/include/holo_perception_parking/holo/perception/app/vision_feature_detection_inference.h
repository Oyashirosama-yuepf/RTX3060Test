/*!
 *  \brief
 *  \author tanghui (tanghui@holomatic.com)
 *  \date 2022-03-21
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_APP_VISOIN_MODEL_INFERENCE_H_
#define HOLO_PERCEPTION_APP_VISOIN_MODEL_INFERENCE_H_
#include <holo/common/chassis_state.h>
#include <holo/common/details/timestamp.h>
#include <holo/common/extrinsic.h>
#include <holo/common/image.h>
#include <holo/common/intrinsic.h>
#include <holo/common/odometry.h>
#include <holo/common/path.h>
#include <holo/common/sensor_id.h>
#include <holo/map/current_route_info.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/parking/sensors/front_nocopy_image.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/obstacle/obstacle_vision.h>
#include <holo/perception/algorithm/ipm.h>
#include <holo/perception/algorithm/tracking/bbox_kf_tracker.h>
#include <holo/perception/app/obstacle_detection_parameter.h>
#include <holo/perception/common/safe_msg_data_container.h>
#include <holo/perception/utils/class_registry.h>
#include <holo/perception/utils/worker.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <sys/time.h>

#include <mutex>
#include <queue>
#include <string>

#include "holo/perception/common/camera_config_ex.h"

namespace holo
{
namespace perception
{
struct Feature
{
    cv::Point2f              image_point;          ///< 2d point detected on image
    boost::optional<cv::Mat> optional_descriptor;  ///< an optional descriptor of this point
    float32_t                score;                ///< feature score
    uint16_t                 camera_id;  /// @brief camera id. indicate which camera does this feature comes from

    /**
     * @brief constructor
     * @param _image_point 2d point coordinate on image
     * @param _optional_descriptor optional descriptor
     * @param _camera_id camera id
     * @param _score feature score
     ＊
     */
    Feature(const cv::Point2f& _image_point, const boost::optional<cv::Mat> _optional_descriptor = boost::none,
            const float32_t _score = 1.0, const uint16_t _camera_id = 0)
      : image_point(_image_point), optional_descriptor(_optional_descriptor), score(_score), camera_id(_camera_id)
    {
    }
};

class FeaturePoint
{
public:
    int   x;
    int   y;
    float score;
    float descriptor_data_[128];
};

/**
 * @brief define the VisionModelInferenceApp class
 */
class VisionFeatureDetectionInferenceApp : public VisionDet
{
public:
    using Features          = std::vector<holo::perception::Feature>;
    typedef std::function<int32_t(const Features&, const Timestamp&)> FeaturesCallback;
    FeaturesCallback                                                  features_callback_;

    typedef holo::Point2f Point2Type;

    /**
     * @brief the constructor
     * @param cfg_file the config file path.
     * @param hz the running frequency.
     */
    VisionFeatureDetectionInferenceApp(const std::string cfg_file);

    /**
     * @brief set callback
     * @param cb the calllback function.
     */
    int32_t SetFeaturesCallback(const FeaturesCallback& cb);

    void ReceiveImageFromCamera(const holo::Image& image, const std::string& camera_name);

    /**
     * @brief
     *
     * @param msg
     * @return bool_t
     */
    bool_t ReceiveImageFromCamera(holo::parking::sensors::FrontNocopyImage<2u> msg);


    bool                                  DoWork();

    
    void SetWorkState(uint8_t work_state);

private:
/**
     * @brief init the instance with given config file.
     * @param cfg_file the config file path.
     */
    void InitFeatureDetection(const std::string cfg_file);

    void PostProcess(std::vector<std::vector<FeaturePoint>>& fd_res);



    /// params
    float32_t                                 hz_;
    std::string                               tidl_cfg_file_;
    holo::common::Timestamp                                  fp_time_stamp_last_;
    std::mutex receiver_protector_;

    // Fp camera image
    holo::Image current_image_;
    int32_t                                   input_width_;
    int32_t                                   input_height_;
    int32_t                                   image_width_;
    int32_t                                   image_height_;
    bool                     camera_update_flag_;

    std::shared_ptr<holo::dnn::DnnInterface> dnn_interface_ptr_fp_;
    bool has_image;

    //
    std::uint8_t fd_work_state_;
};

}  // namespace perception
}  // namespace holo

#endif