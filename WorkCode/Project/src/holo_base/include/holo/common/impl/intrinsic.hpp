/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intrinsic.hpp
 * @brief the implementation of template class intrinsic
 * @author lichao@holomatic.com
 * @date Aug 24, 2019
 */

#include <holo/log/hololog.h>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <holo/common/intrinsic.h>
#include <holo/utils/yaml.h>

namespace holo
{
template <typename T>
IntrinsicT<T>::IntrinsicT()
  : IntrinsicT(CameraModel::UNKNOWN, Vector2Type::One(), Matrix3Type::Identity(),
               Vector8Type::Zero())
{
}

template <typename T>
IntrinsicT<T>::IntrinsicT(CameraModel model, const Vector2Type& size,
                          const Matrix3Type& K, const Vector8Type& D)
  : model_(model)
{
    fx_     = K(0, 0);
    fy_     = K(1, 1);
    cx_     = K(0, 2);
    cy_     = K(1, 2);
    skew_   = K(0, 1);
    k1_     = D(0);
    k2_     = D(1);
    p1_     = D(2);
    p2_     = D(3);
    k3_     = D(4);
    k4_     = D(5);
    k5_     = D(6);
    k6_     = D(7);
    width_  = size(0);
    height_ = size(1);
}

template <typename T>
CameraModel IntrinsicT<T>::GetModel() const
{
    return model_;
}

template <typename T>
typename IntrinsicT<T>::Matrix3Type IntrinsicT<T>::GetK() const
{
    Matrix3Type K = Matrix3Type(1, 0, 0, 0, 1, 0, 0, 0, 1);
    K(0, 0)       = fx_;
    K(1, 1)       = fy_;
    K(0, 2)       = cx_;
    K(1, 2)       = cy_;
    K(0, 1)       = skew_;
    return K;
}

template <typename T>
typename IntrinsicT<T>::Vector8Type IntrinsicT<T>::GetD() const
{
    Vector8Type D;
    D(0) = k1_;
    D(1) = k2_;
    D(2) = p1_;
    D(3) = p2_;
    D(4) = k3_;
    D(5) = k4_;
    D(6) = k5_;
    D(7) = k6_;
    return D;
}

template <typename T>
typename IntrinsicT<T>::Vector2Type IntrinsicT<T>::GetDimension() const
{
    Vector2Type size;
    size(0) = width_;
    size(1) = height_;
    return size;
}

template <typename T>
std::string IntrinsicT<T>::ToString() const
{
    const uint8_t     p = 12u;
    std::stringstream ss;
    (void)ss.setf(std::ios_base::scientific, std::ios_base::floatfield);
    (void)std::setprecision(p);

    ss << "Intrinsic --- " << std::endl
       << "model: " << static_cast<uint32_t>(model_) << std::endl
       << "fx : " << fx_ << std::endl
       << "fy : " << fy_ << std::endl
       << "cx : " << cx_ << std::endl
       << "cy : " << cy_ << std::endl
       << "skew : " << skew_ << std::endl
       << "k1 : " << k1_ << std::endl
       << "k2 : " << k2_ << std::endl
       << "p1 : " << p1_ << std::endl
       << "p2 : " << p2_ << std::endl
       << "k3 : " << k3_ << std::endl
       << "k4 : " << k4_ << std::endl
       << "k5 : " << k5_ << std::endl
       << "k6 : " << k6_ << std::endl
       << "width : " << width_ << std::endl
       << "height : " << height_ << std::endl;

    return ss.str();
}

template <typename T>
bool_t IntrinsicT<T>::SaveYaml(const std::string& fn, const IntrinsicT& in, bool_t verbose)
{
    const uint8_t     p    = 12u;
    const Matrix3Type K    = in.GetK();
    const Vector8Type D    = in.GetD();
    const Vector2Type size = in.GetDimension();

    yaml::Emitter emitter;
    (void)emitter.SetFloatPrecision(p);
    emitter << yaml::BeginMap
            << yaml::Key << "model" << yaml::Value << static_cast<uint32_t>(in.GetModel()) << yaml::Key << "fx"
            << yaml::Value << K(0u, 0u) << yaml::Key << "fy" << yaml::Value << K(1u, 1u) << yaml::Key << "cx"
            << yaml::Value << K(0u, 2u) << yaml::Key << "cy" << yaml::Value << K(1u, 2u) << yaml::Key << "skew"
            << yaml::Value << K(0u, 1u) << yaml::Key << "k1" << yaml::Value << D(0u) << yaml::Key << "k2" << yaml::Value
            << D(1u) << yaml::Key << "p1" << yaml::Value << D(2u) << yaml::Key << "p2" << yaml::Value << D(3u)
            << yaml::Key << "k3" << yaml::Value << D(4u) << yaml::Key << "k4" << yaml::Value << D(5u) << yaml::Key
            << "k5" << yaml::Value << D(6u) << yaml::Key << "k6" << yaml::Value << D(7u) << yaml::Key << "width"
            << yaml::Value << static_cast<uint32_t>(size(0u)) << yaml::Key << "height" << yaml::Value
            << static_cast<uint32_t>(size(1u)) << yaml::EndMap;

    std::ofstream out(fn.c_str());
    out << emitter.c_str();
    out.close();

    LOG_IF(INFO, verbose) << "Saved intrinsic to " << fn;

    return true;
}

template <typename T>
IntrinsicT<T> IntrinsicT<T>::LoadYaml(const std::string& fn, bool_t verbose)
{
    if (access(fn.c_str(), R_OK) != 0)
    {
        std::stringstream ss;
        ss << fn << " dose not exist";
        LOG(ERROR) << ss.str();
        throw std::runtime_error(ss.str());
    }

    /// @brief define variable for intrinsic
    uint32_t   model  = 0xFFFF;
    ScalarType fx     = 0.0f;
    ScalarType fy     = 0.0f;
    ScalarType cx     = 0.0f;
    ScalarType cy     = 0.0f;
    ScalarType skew   = 0.0f;
    ScalarType k1     = 0.0f;
    ScalarType k2     = 0.0f;
    ScalarType p1     = 0.0f;
    ScalarType p2     = 0.0f;
    ScalarType k3     = 0.0f;
    ScalarType k4     = 0.0f;
    ScalarType k5     = 0.0f;
    ScalarType k6     = 0.0f;
    uint32_t   width  = 0u;
    uint32_t   height = 0u;

    /// @brief try to load parameters from yaml
    try
    {
        yaml::Node node_root = yaml::LoadFile(fn);

        model  = node_root["model"].as<uint32_t>();
        fx     = node_root["fx"].as<ScalarType>();
        fy     = node_root["fy"].as<ScalarType>();
        cx     = node_root["cx"].as<ScalarType>();
        cy     = node_root["cy"].as<ScalarType>();
        skew   = node_root["skew"].as<ScalarType>();
        k1     = node_root["k1"].as<ScalarType>();
        k2     = node_root["k2"].as<ScalarType>();
        p1     = node_root["p1"] ? node_root["p1"].as<ScalarType>() : 0.0f;
        p2     = node_root["p2"] ? node_root["p2"].as<ScalarType>() : 0.0f;
        k3     = node_root["k3"] ? node_root["k3"].as<ScalarType>() : 0.0f;
        k4     = node_root["k4"] ? node_root["k4"].as<ScalarType>() : 0.0f;
        k5     = node_root["k5"] ? node_root["k5"].as<ScalarType>() : 0.0f;
        k6     = node_root["k6"] ? node_root["k6"].as<ScalarType>() : 0.0f;
        width  = node_root["width"].as<uint32_t>();
        height = node_root["height"].as<uint32_t>();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        LOG(FATAL) << "Load extrinsic yaml failure: " << fn << "\n" << e.what();
    }

    /// @brief construct intrinsic
    Vector2Type size(width, height);

    Matrix3Type K = Matrix3Type::Identity();
    K(0u, 0u)     = fx;
    K(1u, 1u)     = fy;
    K(0u, 2u)     = cx;
    K(1u, 2u)     = cy;
    K(0u, 1u)     = skew;

    Vector8Type D;
    D(0u) = k1;
    D(1u) = k2;
    D(2u) = p1;
    D(3u) = p2;
    D(4u) = k3;
    D(5u) = k4;
    D(6u) = k5;
    D(7u) = k6;

    IntrinsicT intrinsic(static_cast<holo::CameraModel>(model), size, K, D);
    LOG_IF(INFO, verbose) << "Loaded intrinsic from " << fn << "\n" << intrinsic.ToString();
    return intrinsic;
}

} /* namespace holo */
