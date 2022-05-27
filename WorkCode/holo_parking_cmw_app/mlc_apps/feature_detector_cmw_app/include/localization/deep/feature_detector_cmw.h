/*!
 * \brief holo cmw wrapper of the features extracted by superpoint
 * \author Heiko Yu, yuchangsong@holomatic.com
 * \date Jan-11-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_CMW_APPS_LOCALIZATION_DEEP_FEATURE_DETECTOR_CMW_H_
#define HOLO_CMW_APPS_LOCALIZATION_DEEP_FEATURE_DETECTOR_CMW_H_

#include <cmw_wrapper/cmw_bus.h>

#include <holo/log/hololog.h>
#include <holo/localization/deep/deepslam_base.h>

#include <holo/localization/deep/common_types.h>
#include <holo/localization/deep/visualizer.h>
#include <holo/parking/vision/point_feature_list.h>
#include <holo/sensors/camera/image_ipc.h>
#include <holo_parking_msg/traits.h>

namespace deep = holo::localization::deep;

namespace holo_cmw
{
/**
 * @brief Feature detector CMW
 *
 */
class FeatureDetectorCmw
{
public:
    /**
     * @brief handy type define
     *
     */
    using Scalar              = deep::Scalar;
    using float32_t           = deep::float32_t;
    using BusType             = cmw_wrapper::BusType;
    using PointFeature        = holo::parking::vision::PointFeatureT<float32_t>;
    using PointFeaturePtrList = holo::parking::vision::PointFeaturePtrListT<PointFeature>;
    using CameraParameters    = deep::CameraParameters;
    using DescriptorType      = PointFeature::DescriptorType;
    using Node                = deep::Node;
    using DeepSLAMBase        = deep::DeepSLAMBase;
    using Features            = deep::Features;
    using Image               = deep::Image;
    using Intrinsic           = deep::Intrinsic;
    using Timestamp           = deep::Timestamp;
    using Point2f             = deep::Point2f;
    using Point2d             = deep::Point2d;
    using Visualizer          = holo::localization::deep::Visualizer;

    /**
     * @brief constructor
     *
     */
    FeatureDetectorCmw(const std::string& config_file, const uint32_t domain_id, const std::string& ns);

    /**
     * @brief destructor
     *
     */
    ~FeatureDetectorCmw();

    /**
     * @brief spin the node
     * @param[in] num_threads Number of threads
     */
    void Spin(holo::uint16_t const num_threads = 1u);

    /**
     * @brief stop the node
     *
     */
    void Stop();

private:
    /******** @brief methods ****************/
    /**
     * @brief setup
     */
    void SetUp(const std::string& config_file);

    /**
     * @brief input image callback
     *
     */
    void InputImageCallback(holo::uint32_t msg, uint16_t camera_index);

    /**
     * @brief publish features extracted by superpoint
     *
     */
    holo::int32_t OutputFeatureLists(const Features& input_features, const Timestamp& timestamp);

    /// @brief subscribed and published topic
    struct Topics
    {
        /// @brief subscribed image topics
        const std::vector<std::string> input_images;

        /// @brief published features extraced by superpoint
        const std::string output_features;

        /// @brief constructor
        Topics(const std::vector<std::string>& _input_images = {}, const std::string& _output_features = {})
          : input_images(_input_images), output_features(_output_features)
        {
        }

        /// @brief output stream
        friend std::ostream& operator<<(std::ostream& os, const Topics& topics)
        {
            os << "\n Topics: ";

            if (!topics.input_images.empty())
            {
                os << "\n input_images:";

                for (const auto& image_topic : topics.input_images)
                {
                    os << image_topic;
                }
            }

            os << "\n output_features: " << topics.output_features << std::endl;
            return os;
        }

        /// @brief load from yaml
        static Topics LoadFromYaml(const holo::yaml::Node& node)
        {
            const std::vector<std::string> input_images =
                node["input_images"].as<std::vector<std::string>>(std::vector<std::string>{});
            const std::string output_features = node["output_features"].as<std::string>();
            return Topics(input_images, output_features);
        }
    };

    ///@brief cmw reader and writer wrapper
    struct CmwReadersWriter
    {
        /// @brief cmw reader
        std::vector<BusType::ReaderType<holo::uint32_t>> images_reader;

        /// @brief cmw writer
        BusType::WriterType<PointFeaturePtrList, BusType::DefaultConversionTraitsType<PointFeaturePtrList>>
            point_feature_writer;
    };

    /// @brief holo cmw
    BusType bus_;

    /// @brief cmw readers and writers
    CmwReadersWriter cmw_readers_writers_;

    /// @brief superpoint
    std::shared_ptr<DeepSLAMBase> deepslam_base_;

    /// @brief camera parameters
    CameraParameters::Ptr camera_parameters_;

    /// @brief the image ipc client which helps load image
    ///        from driver or other image source
    std::vector<std::shared_ptr<holo::sensors::camera::ImageIpc>> image_ipcs_;

    /// @brief visualizer
    std::shared_ptr<Visualizer> visualizer_;

    /// @brief input_image_callback_counter
    uint32_t input_image_callback_counter;

    /// @brief output_features_callback_counter
    uint32_t output_features_callback_counter;

    /// @brief camera parameters
    CameraParameters::Ptr camera_params_;

};  // FeatureDetectorCmw

}  // namespace holo_cmw

#endif  // HOLO_CMW_APPS_LOCALIZATION_DEEP_FEATURE_DETECTOR_CMW_H_
