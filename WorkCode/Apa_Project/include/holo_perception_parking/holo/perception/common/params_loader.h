/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file params_loader.h
 * @brief This header file defines params struct used in node.
 * @author zhouchengwei (zhouchengwei@holomatic.com)
 * @date "2022-02-17"
 */

#ifndef _HOLO_PERCEPTION_COMMON_PARAMS_LOADER_H_
#define _HOLO_PERCEPTION_COMMON_PARAMS_LOADER_H_

#include <holo/common/extrinsic.h>
#include <holo/io/common/intrinsic.h>
#include <holo/perception/common/box2d.h>
#include <holo/perception/common/box_object.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace perception
{
using IntrinsicBaseType            = holo::common::details::CameraIntrinsicBaseT<float32_t>;
using IntrinsicBaseTypePtr         = std::shared_ptr<IntrinsicBaseType>;
using FisheyeIntrinsicType         = holo::common::details::FisheyeIntrinsicT<float32_t>;
using PinholeIntrinsicType         = holo::common::details::PinholeIntrinsicT<float32_t>;
using OmnidirectionalIntrinsicType = holo::common::details::OmnidirectionalIntrinsicT<float32_t>;

struct CameraParameters
{
    typedef std::shared_ptr<CameraParameters>       Ptr;
    typedef std::shared_ptr<const CameraParameters> ConPtr;
    std::string                                     camera_intrinsic_file;
    std::string                                     body_gnss_extrinsic_file;
    std::string                                     gnss_lidar_extrinsic_file;
    std::string                                     cam_lidar_extrinsic_file;
    std::string                                     direct_mapping_ground_file;
    std::string                                     camera_ground_extrinsic_file;
    std::string                                     ROI_mask_file;
    uint32_t                                        output_mask_offset;
    std::vector<int>                                size;
    std::vector<int>                                resize;
    std::vector<int>                                crop;
    float32_t                                       visible_radius;
    std::vector<float32_t>                          radian_range;
    holo::Extrinsicf                                camera_to_ground_extrinsic;
    IntrinsicBaseTypePtr                            intrinsic;
    cv::Mat                                         ROI_mask;
    int                                             type;

    CameraParameters(const std::string& _camera_intrinsic_file, const std::string& _body_gnss_extrinsic_file,
                     const std::string& _gnss_lidar_extrinsic_file, const std::string& _cam_lidar_extrinsic_file,
                     const std::string& _direct_mapping_ground_file, const std::string& _camera_ground_extrinsic_file,
                     const std::string& _ROI_mask_file, const uint32_t _output_mask_offset,
                     const std::vector<int>& _size, const std::vector<int>& _resize, const std::vector<int>& _crop,
                     const float32_t _visible_radius, const std::vector<float32_t>& _radian_range)
      : camera_intrinsic_file(_camera_intrinsic_file)
      , ROI_mask_file(_ROI_mask_file)
      , output_mask_offset(_output_mask_offset)
      , size(_size)
      , resize(_resize)
      , crop(_crop)
      , visible_radius(_visible_radius)
      , radian_range(_radian_range)
      , body_gnss_extrinsic_file(_body_gnss_extrinsic_file)
      , gnss_lidar_extrinsic_file(_gnss_lidar_extrinsic_file)
      , cam_lidar_extrinsic_file(_cam_lidar_extrinsic_file)
      , direct_mapping_ground_file(_direct_mapping_ground_file)
      , camera_ground_extrinsic_file(_camera_ground_extrinsic_file)
    {
        std::string      intrinsic_path = GetConfigFileAbsolutePath(camera_intrinsic_file);
        holo::yaml::Node intrinsic_node = holo::yaml::LoadFile(intrinsic_path);
        intrinsic                       = CreateCameraIntrinsic(intrinsic_node);
        if (camera_ground_extrinsic_file != "")
        {
            std::string extrinsic_path = GetConfigFileAbsolutePath(camera_ground_extrinsic_file);
            camera_to_ground_extrinsic = holo::Extrinsicf::LoadYaml(extrinsic_path);
            type                       = 2;
        }
        else if (body_gnss_extrinsic_file != "" && gnss_lidar_extrinsic_file != "" && cam_lidar_extrinsic_file != "")
        {
            holo::Extrinsicf bg_extrinsic =
                holo::Extrinsicf::LoadYaml(GetConfigFileAbsolutePath(body_gnss_extrinsic_file));
            holo::Extrinsicf gl_extrinsic =
                holo::Extrinsicf::LoadYaml(GetConfigFileAbsolutePath(gnss_lidar_extrinsic_file));
            holo::Extrinsicf cl_extrinsic =
                holo::Extrinsicf::LoadYaml(GetConfigFileAbsolutePath(cam_lidar_extrinsic_file));

            holo::Extrinsicf::Pose3Type body_cam_pose =
                bg_extrinsic.GetPose() * gl_extrinsic.GetPose() * cl_extrinsic.GetPose().Inverse();
            camera_to_ground_extrinsic =
                holo::Extrinsicf(bg_extrinsic.GetParentCoordinate(), cl_extrinsic.GetParentCoordinate(), body_cam_pose);
            type = 0;
        }
        if (ROI_mask_file != "")
        {
            std::string ROI_mask_path = GetConfigFileAbsolutePath(ROI_mask_file);
            ROI_mask                  = cv::imread(ROI_mask_path, CV_LOAD_IMAGE_GRAYSCALE);
        }
        else
        {
            ROI_mask = cv::Mat::ones(cv::Size(size[0], size[1]), CV_8UC1);
        }
        cv::Mat t[] = {ROI_mask, ROI_mask, ROI_mask};
        cv::merge(t, 3, ROI_mask);

        cv::Mat ROI_mask_resized;
        cv::resize(ROI_mask, ROI_mask_resized, cv::Size(resize[0], resize[1]), 0, 0, cv::INTER_NEAREST);
        cv::Mat ROI_mask_cropped(ROI_mask_resized, cv::Rect(crop[0], crop[1], crop[2], crop[3]));
        ROI_mask = ROI_mask_cropped;
    }
    IntrinsicBaseTypePtr CreateCameraIntrinsic(const holo::yaml::Node& node)
    {
        switch (node["model"].as<uint32_t>())
        {
            case static_cast<uint32_t>(IntrinsicBaseType::Model::PINHOLE):
                return std::make_shared<PinholeIntrinsicType>(node.as<PinholeIntrinsicType>());
            case static_cast<uint32_t>(IntrinsicBaseType::Model::FISHEYE):
                return std::make_shared<FisheyeIntrinsicType>(node.as<FisheyeIntrinsicType>());
            case static_cast<uint32_t>(IntrinsicBaseType::Model::OMNIDIRECTIONAL):
                return std::make_shared<OmnidirectionalIntrinsicType>(node.as<OmnidirectionalIntrinsicType>());
        }
        LOG(ERROR) << "Utility --- CreateCameraIntrinsic, the input source intrinsic "
                      "is invalid! model: "
                   << node["model"].as<uint32_t>();
        throw std::runtime_error("Utility --- CreateCameraIntrinsic, invalid intrinsic");
        return nullptr;
    }
    friend std::ostream& operator<<(std::ostream& os, const CameraParameters& camera_parameters)
    {
        os << "Start Print Camera Info yaml >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>: " << std::endl;
        os << "camera_intrinsic_file: " << camera_parameters.camera_intrinsic_file << std::endl;
        os << "body_gnss_extrinsic_file: " << camera_parameters.body_gnss_extrinsic_file << std::endl;
        os << "gnss_lidar_extrinsic_file: " << camera_parameters.gnss_lidar_extrinsic_file << std::endl;
        os << "cam_lidar_extrinsic_file: " << camera_parameters.cam_lidar_extrinsic_file << std::endl;
        os << "direct_mapping_ground_file: " << camera_parameters.direct_mapping_ground_file << std::endl;
        os << "camera_ground_extrinsic_file: " << camera_parameters.camera_ground_extrinsic_file << std::endl;
        os << "ROI_mask_file: " << camera_parameters.ROI_mask_file << std::endl;
        os << "output_mask_offset: " << camera_parameters.output_mask_offset << std::endl;
        os << "extrinsic type: " << camera_parameters.type << std::endl;
        os << "size: [ ";
        for (size_t i = 0; i < camera_parameters.size.size(); i++)
        {
            os << camera_parameters.size[i] << " ";
        }
        os << "]" << std::endl;
        os << "resize: [ ";
        for (size_t i = 0; i < camera_parameters.resize.size(); i++)
        {
            os << camera_parameters.resize[i] << " ";
        }
        os << "]" << std::endl;
        os << "crop: [ ";
        for (size_t i = 0; i < camera_parameters.crop.size(); i++)
        {
            os << camera_parameters.crop[i] << " ";
        }
        os << "]" << std::endl;
        os << "visible_radius: " << camera_parameters.visible_radius << std::endl;
        os << "radian_range: [ ";
        for (size_t i = 0; i < camera_parameters.radian_range.size(); i++)
        {
            os << camera_parameters.radian_range[i] << " ";
        }
        os << "]" << std::endl;

        os << "Extrinsic: " << camera_parameters.camera_to_ground_extrinsic.ToString() << std::endl;

        // os << "Intrinsic: Mode:" << camera_parameters.intrinsic->GetModel()
        //    << " SensorID:" << camera_parameters.intrinsic->GetSensorId() << std::endl;

        os << "End Print Camera Info yaml <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    }
    static CameraParameters::Ptr LoadFromYaml(const std::string& camera_config_yaml)
    {
        const holo::yaml::Node camera_node               = holo::yaml::LoadFile(camera_config_yaml);
        const std::string      camera_intrinsic_file     = camera_node["camera_intrinsic_file"].as<std::string>();
        const std::string      body_gnss_extrinsic_file  = camera_node["body_gnss_extrinsic_file"].as<std::string>();
        const std::string      gnss_lidar_extrinsic_file = camera_node["gnss_lidar_extrinsic_file"].as<std::string>();
        const std::string      cam_lidar_extrinsic_file  = camera_node["cam_lidar_extrinsic_file"].as<std::string>();
        std::string            direct_mapping_ground_file;
        try
        {
            direct_mapping_ground_file = camera_node["direct_mapping_ground_file"].as<std::string>();
        }
        catch (const std::exception& e)
        {
            direct_mapping_ground_file = "";
            LOG(INFO) << "camera_ground_extrinsic_file is not set.";
        }

        const std::string camera_ground_extrinsic_file = camera_node["camera_ground_extrinsic_file"].as<std::string>();
        const std::string ROI_mask_file                = camera_node["ROI_mask_file"].as<std::string>();
        const uint32_t    output_mask_offset           = camera_node["output_mask_offset"].as<uint32_t>();

        const std::vector<int>       size           = camera_node["size"].as<std::vector<int>>();
        const std::vector<int>       resize         = camera_node["resize"].as<std::vector<int>>();
        const std::vector<int>       crop           = camera_node["crop"].as<std::vector<int>>();
        const float32_t              visible_radius = camera_node["visible_radius"].as<float32_t>();
        const std::vector<float32_t> radian_range   = camera_node["radian_range"].as<std::vector<float32_t>>();
        return std::make_shared<CameraParameters>(
            camera_intrinsic_file, body_gnss_extrinsic_file, gnss_lidar_extrinsic_file, cam_lidar_extrinsic_file,
            direct_mapping_ground_file, camera_ground_extrinsic_file, ROI_mask_file, output_mask_offset, size, resize,
            crop, visible_radius, radian_range);
    }
};

struct FreespaceParameters
{
    uint32_t    debug_image_mode;
    uint32_t    debug_image_skip_frames;
    std::string debug_image_path;
    std::string debug_save_path;

    typedef std::shared_ptr<FreespaceParameters> Ptr;
    FreespaceParameters(const uint32_t _debug_image_mode, const uint32_t _debug_image_skip_frames,
                        const std::string& _debug_image_path, const std::string& _debug_save_path)
      : debug_image_mode(_debug_image_mode)
      , debug_image_skip_frames(_debug_image_skip_frames)
      , debug_image_path(_debug_image_path)
      , debug_save_path(_debug_save_path)
    {
    }
    friend std::ostream& operator<<(std::ostream& os, const FreespaceParameters& freespace_parameters)
    {
        os << "Start Print Freespace Parameters yaml >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>: " << std::endl;
        os << "debug_image_mode: " << freespace_parameters.debug_image_mode << std::endl;
        os << "debug_image_skip_frames: " << freespace_parameters.debug_image_skip_frames << std::endl;
        os << "debug_image_path: " << freespace_parameters.debug_image_path << std::endl;
        os << "debug_save_path: " << freespace_parameters.debug_save_path << std::endl;
        os << "End Print Freespace Parameters yaml <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    }
    static FreespaceParameters::Ptr LoadFromYaml(const std::string& freespace_yaml)
    {
        const holo::yaml::Node freespace_node          = holo::yaml::LoadFile(freespace_yaml);
        const uint32_t         debug_image_mode        = freespace_node["debug_image_mode"].as<uint32_t>();
        const uint32_t         debug_image_skip_frames = freespace_node["debug_image_skip_frames"].as<uint32_t>();
        const std::string      debug_image_path        = freespace_node["debug_image_path"].as<std::string>();
        const std::string      debug_save_path         = freespace_node["debug_save_path"].as<std::string>();
        return std::make_shared<FreespaceParameters>(debug_image_mode, debug_image_skip_frames, debug_image_path,
                                                     debug_save_path);
    }
};

struct DetectionParameters
{
    uint32_t    debug_image_mode;
    uint32_t    debug_image_skip_frames;
    std::string debug_image_path;
    std::string debug_save_path;

    typedef std::shared_ptr<DetectionParameters> Ptr;
    DetectionParameters(const uint32_t _debug_image_mode, const uint32_t _debug_image_skip_frames,
                        const std::string& _debug_image_path, const std::string& _debug_save_path)
      : debug_image_mode(_debug_image_mode)
      , debug_image_skip_frames(_debug_image_skip_frames)
      , debug_image_path(_debug_image_path)
      , debug_save_path(_debug_save_path)
    {
    }
    friend std::ostream& operator<<(std::ostream& os, const DetectionParameters& detection_parameters)
    {
        os << "Start Print Detection Parameters yaml >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>: " << std::endl;
        os << "debug_image_mode: " << detection_parameters.debug_image_mode << std::endl;
        os << "debug_image_skip_frames: " << detection_parameters.debug_image_skip_frames << std::endl;
        os << "debug_image_path: " << detection_parameters.debug_image_path << std::endl;
        os << "debug_save_path: " << detection_parameters.debug_save_path << std::endl;
        os << "End Print Detection Parameters yaml <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    }
    static DetectionParameters::Ptr LoadFromYaml(const std::string& detection_yaml)
    {
        std::cout << "read detection yaml start: " << detection_yaml << std::endl;
        const holo::yaml::Node detection_node = holo::yaml::LoadFile(detection_yaml);
        std::cout << "read detection yaml start: " << detection_yaml << std::endl;
        const uint32_t debug_image_mode = detection_node["debug_image_mode"].as<uint32_t>();
        std::cout << "read detection yaml start: " << detection_yaml << std::endl;
        const uint32_t    debug_image_skip_frames = detection_node["debug_image_skip_frames"].as<uint32_t>();
        const std::string debug_image_path        = detection_node["debug_image_path"].as<std::string>();
        const std::string debug_save_path         = detection_node["debug_save_path"].as<std::string>();
        return std::make_shared<DetectionParameters>(debug_image_mode, debug_image_skip_frames, debug_image_path,
                                                     debug_save_path);
    }
};

struct Parameters
{
    typedef std::shared_ptr<Parameters>                    Ptr;
    std::string                                            inference_yaml;
    std::string                                            freespace_yaml;
    std::string                                            detection_yaml;
    std::string                                            input_check_yaml;
    std::vector<std::string>                               camera_names;
    std::vector<std::string>                               camera_config_files;
    std::vector<float32_t>                                 body_ground_extrinsic;
    std::vector<float32_t>                                 ground_pitch_gradiant_samples;
    std::vector<float32_t>                                 blind_zone_nearst_coeffs;
    std::unordered_map<std::string, CameraParameters::Ptr> camera_infos;
    FreespaceParameters::Ptr                               freespace_param;
    DetectionParameters::Ptr                               detection_param;
    std::string                                            tracking_config_file;
    Parameters(const std::string& _inference_yaml, const std::string _freespace_yaml, const std::string _detection_yaml,
               const std::string _input_check_yaml, const std::vector<std::string>& _camera_names,
               const std::vector<std::string>& _camera_config_files,
               const std::vector<float32_t>&   _body_ground_extrinsic,
               const std::vector<float32_t>&   _ground_pitch_gradiant_samples,
               const std::vector<float32_t>&   _blind_zone_nearest_coeffs)
      : inference_yaml(_inference_yaml)
      , freespace_yaml(_freespace_yaml)
      , detection_yaml(_detection_yaml)
      , input_check_yaml(_input_check_yaml)
      , camera_names(_camera_names)
      , camera_config_files(_camera_config_files)
      , body_ground_extrinsic(_body_ground_extrinsic)
      , ground_pitch_gradiant_samples(_ground_pitch_gradiant_samples)
      , blind_zone_nearst_coeffs(_blind_zone_nearest_coeffs)
    {
        for (size_t i = 0; i < camera_names.size(); i++)
        {
            std::string name            = camera_names[i];
            std::string cam_config_path = GetConfigFileAbsolutePath(camera_config_files[i]);
            camera_infos[name]          = CameraParameters::LoadFromYaml(cam_config_path);
        }
        if (freespace_yaml != "")
        {
            const std::string freespace_yaml_path = GetConfigFileAbsolutePath(freespace_yaml);
            freespace_param                       = FreespaceParameters::LoadFromYaml(freespace_yaml_path);
        }
        if (detection_yaml != "")
        {
            std::cout << "read detection yaml: " << detection_yaml << std::endl;
            const std::string detection_yaml_path = GetConfigFileAbsolutePath(detection_yaml);
            detection_param                       = DetectionParameters::LoadFromYaml(detection_yaml_path);
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const Parameters& parameters)
    {
        os << "Start Print Freespace Lib yaml >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>: " << std::endl;
        os << "inference yaml: " << parameters.inference_yaml << std::endl;
        os << "freespace task yaml: " << parameters.freespace_yaml << std::endl;
        os << "detection task yaml: " << parameters.detection_yaml << std::endl;
        os << "input check config yaml: " << parameters.input_check_yaml << std::endl;
        os << "camera names: " << std::endl;
        for (size_t i = 0; i < parameters.camera_names.size(); i++)
        {
            os << parameters.camera_names[i] << std::endl;
        }
        os << "camera config files: " << std::endl;
        for (size_t i = 0; i < parameters.camera_config_files.size(); i++)
        {
            os << parameters.camera_config_files[i] << std::endl;
        }
        os << "body ground extrinsic: [ ";
        for (size_t i = 0; i < parameters.body_ground_extrinsic.size(); i++)
        {
            os << parameters.body_ground_extrinsic[i] << " ";
        }
        os << "]" << std::endl;
        os << "ground pitch gradiant samples: [ ";
        for (size_t i = 0; i < parameters.ground_pitch_gradiant_samples.size(); i++)
        {
            os << parameters.ground_pitch_gradiant_samples[i] << " ";
        }
        os << "]" << std::endl;
        os << "blind zone nearest coneffs: [ ";
        for (size_t i = 0; i < parameters.blind_zone_nearst_coeffs.size(); i++)
        {
            os << parameters.blind_zone_nearst_coeffs[i] << " ";
        }
        os << "]" << std::endl;
        for (auto& t : parameters.camera_infos)
        {
            os << "camera config: " << t.first << std::endl;
            os << *(t.second) << std::endl;
        }
        os << "freespace param: " << std::endl;
        os << *(parameters.freespace_param) << std::endl;
        os << "End Print Freespace Lib yaml <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    }
    static Parameters::Ptr LoadFromYaml(const std::string& algorithm_lib_yaml)
    {
        const holo::yaml::Node algorithm_node = holo::yaml::LoadFile(algorithm_lib_yaml);
        const std::string      inference_yaml = algorithm_node["inference_yaml"].as<std::string>();
        std::string            freespace_yaml;
        std::string            detection_yaml;
        std::string            input_check_yaml;
        try
        {
            freespace_yaml = algorithm_node["freespace_yaml"].as<std::string>();
        }
        catch (const std::exception& e)
        {
            freespace_yaml = "";
        }
        try
        {
            detection_yaml = algorithm_node["detection_yaml"].as<std::string>();
        }
        catch (const std::exception& e)
        {
            detection_yaml = "";
        }
        try
        {
            input_check_yaml = algorithm_node["input_check_yaml"].as<std::string>();
        }
        catch (const std::exception& e)
        {
            detection_yaml = "";
        }

        const std::vector<std::string> camera_names = algorithm_node["camera_names"].as<std::vector<std::string>>();
        const std::vector<std::string> camera_config_files =
            algorithm_node["camera_config_files"].as<std::vector<std::string>>();
        const std::vector<float32_t> body_ground_extrinsic =
            algorithm_node["body_ground_extrinsic"].as<std::vector<float32_t>>();
        const std::vector<float32_t> ground_pitch_gradiant_samples =
            algorithm_node["ground_pitch_gradiant_samples"].as<std::vector<float32_t>>();
        const std::vector<float32_t> blind_zone_nearst_coeffs =
            algorithm_node["blind_zone_nearst_coeffs"].as<std::vector<float32_t>>();
        auto a = std::make_shared<Parameters>(inference_yaml, freespace_yaml, detection_yaml, input_check_yaml,
                                              camera_names, camera_config_files, body_ground_extrinsic,
                                              ground_pitch_gradiant_samples, blind_zone_nearst_coeffs);
        a->tracking_config_file = algorithm_node["tracking_config_file"].as<std::string>();
        return a;
    }
};  // namespace perception

///////////////////////////////////////////////////////    result struct     ///////////////////////////////////////////
struct Srv_Result
{
    using Plane   = std::array<holo::float32_t, 3U>;
    using Frustum = std::array<Plane, 4U>;
    typedef std::shared_ptr<Srv_Result> Ptr;

    std::vector<std::string>                         process_names;
    holo::common::Timestamp                          time_stamp_last;
    std::unordered_map<std::string, Eigen::Matrix3f> camera_newK;

    std::unordered_map<std::string, cv::Mat> cameras_debug_image_container;
    uint32_t                                 debug_num;
    bool                                     freespace_debug_flag;
    bool                                     detection_debug_flag;

    bool                 freespace_flag;
    bool                 detection_flag;
    std::vector<cv::Mat> freespace_result;

    std::vector<std::list<holo::perception::BoxObjectf>> detection_obs_results;

    std::vector<std::vector<std::vector<float>>>  srv_psd_results;

    std::unordered_map<std::string, Frustum> camera_frustums_;

    Srv_Result()
      : freespace_debug_flag(false), detection_debug_flag(false), freespace_flag(false), detection_flag(false){};
};

}  // namespace perception
}  // namespace holo
#endif
