/*!
 *  \brief
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2018-08-13
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_COMMON_CAMERA_CONF_HPP_
#define HOLO_PERCEPTION_COMMON_CAMERA_CONF_HPP_

#include "holo/perception/common/camera_conf.h"

namespace holo
{
namespace perception
{

template<typename Scalar>
CameraConf<Scalar>::CameraConf(const std::string& intrinsic_file,
                               const std::string& extrinsic_file)
                            //    const std::string& resolution_file)
{ 
    load_intrinsic_params(intrinsic_file);
    load_extrinsic_params(extrinsic_file);
    // load_resolution_params(resolution_file);
}

template<typename Scalar>
void CameraConf<Scalar>::load_intrinsic_params(const std::string& fn)
{
    holo::Intrinsicf intrinsic_object = holo::Intrinsicf::LoadYaml(fn);
    k_ = intrinsic_object.K().template cast<Scalar>();
    k_inv_ = k_.Inverse();

    holo::yaml::Node node_root = holo::yaml::LoadFile(fn);
    resolution_x_ = node_root["width"].as<int32_t>();
    resolution_y_ = node_root["height"].as<int32_t>();
}

template<typename Scalar>
void CameraConf<Scalar>::load_extrinsic_params(const std::string& fn)
{
    holo::yaml::Node node_root = holo::yaml::LoadFile(fn);
    camera_height_ = node_root["camera_height"].as<Scalar>();
    pitch_degree_ = node_root["pitch"].as<Scalar>();
    yaw_degree_ = node_root["yaw"].as<Scalar>();
    qw_ = node_root["qw"].as<Scalar>();
    qx_ = node_root["qx"].as<Scalar>();
    qy_ = node_root["qy"].as<Scalar>();
    qz_ = node_root["qz"].as<Scalar>();
    x_ = node_root["x"].as<Scalar>();
    y_ = node_root["y"].as<Scalar>();
    z_ = node_root["z"].as<Scalar>();
    pitch_radian_ = holo::Radian(pitch_degree_);
    yaw_radian_ = holo::Radian(yaw_degree_);

    
}

// template<typename Scalar>
// void CameraConf<Scalar>::load_resolution_params(const std::string& fn)
// {
//     YamlNode camera = yaml_load_file(fn);
//     YamlNode resolution = yaml_get(camera, "size");
//     resolution_x_ = yaml_get(resolution, "width").as<int32_t>();
//     resolution_y_ = yaml_get(resolution, "height").as<int32_t>();
// }

}   /// end namespace perception
}   /// end namespace holo

#endif  /// HOLO_PERCEPTION_COMMON_CAMERA_CONF_HPP_
