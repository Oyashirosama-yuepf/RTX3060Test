#ifndef HOLO_IO_COMMON_INTRINSIC_H_
#define HOLO_IO_COMMON_INTRINSIC_H_

#include <holo/common/intrinsic.h>
#include <holo/io/numerics/matrix.h>
#include <holo/io/numerics/vector.h>

namespace YAML
{
template <typename T>
struct convert<holo::common::PinholeIntrinsicT<T>>
{
    using ScalarType = T;
    using ValueType  = holo::common::PinholeIntrinsicT<ScalarType>;
    using Model      = typename holo::common::details::CameraIntrinsicBaseT<ScalarType>::Model;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["model"]     = static_cast<uint32_t>(Model::PINHOLE);
        node["sensor_id"] = static_cast<uint32_t>(rhs.GetSensorId());
        node["width"]     = rhs.GetWidth();
        node["height"]    = rhs.GetHeight();
        node["k"]         = rhs.GetK();
        node["d"]         = rhs.GetD();
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            if (node["model"].as<uint32_t>() != static_cast<uint32_t>(Model::PINHOLE))
            {
                std::cout << "Invalid camera model, want " << static_cast<uint32_t>(Model::PINHOLE)
                          << ", which is PINHOLE, but given model is " << node["model"].as<uint32_t>() << "\n";
                return false;
            }

            rhs.SetSensorId(node["sensor_id"].as<uint32_t>());
            rhs.SetDimension(node["width"].as<uint32_t>(), node["height"].as<uint32_t>());
            rhs.k_ = node["k"].as<typename ValueType::Matrix33Type>();
            rhs.d_ = node["d"].as<typename ValueType::Vector5Type>();
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};

template <typename T>
struct convert<holo::common::FisheyeIntrinsicT<T>>
{
    using ScalarType = T;
    using ValueType  = holo::common::FisheyeIntrinsicT<ScalarType>;
    using Model      = typename holo::common::details::CameraIntrinsicBaseT<ScalarType>::Model;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["model"]     = static_cast<uint32_t>(Model::FISHEYE);
        node["sensor_id"] = static_cast<uint32_t>(rhs.GetSensorId());

        node["fx"]   = rhs.GetK()(0, 0);
        node["fy"]   = rhs.GetK()(1, 1);
        node["cx"]   = rhs.GetK()(0, 2);
        node["cy"]   = rhs.GetK()(1, 2);
        node["skew"] = rhs.GetK()(0, 1);

        node["k1"] = rhs.GetD()[0];
        node["k2"] = rhs.GetD()[1];
        node["k3"] = rhs.GetD()[2];
        node["k4"] = rhs.GetD()[3];

        node["width"]  = rhs.GetWidth();
        node["height"] = rhs.GetHeight();

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            if (node["model"].as<uint32_t>() != static_cast<uint32_t>(Model::FISHEYE))
            {
                std::cout << "Invalid camera model, want " << static_cast<uint32_t>(Model::FISHEYE)
                          << ", which is FISHEYE, but given model is " << node["model"].as<uint32_t>() << "\n";
                return false;
            }

            rhs.SetSensorId(node["sensor_id"].as<uint32_t>());
            rhs.SetDimension(node["width"].as<uint32_t>(), node["height"].as<uint32_t>());
            rhs.SetPrinciplePoint(node["cx"].as<ScalarType>(), node["cy"].as<ScalarType>());
            rhs.SetSkew(node["skew"].as<ScalarType>());
            rhs.SetFocalLength(node["fx"].as<ScalarType>(), node["fy"].as<ScalarType>());
            rhs.SetDistortionParameter(node["k1"].as<ScalarType>(), node["k2"].as<ScalarType>(),
                                       node["k3"].as<ScalarType>(0.0), node["k4"].as<ScalarType>(0.0));
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};

template <typename T>
struct convert<holo::common::OmnidirectionalIntrinsicT<T>>
{
    using ScalarType = T;
    using ValueType  = holo::common::OmnidirectionalIntrinsicT<ScalarType>;
    using Model      = typename holo::common::details::CameraIntrinsicBaseT<ScalarType>::Model;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["model"]     = static_cast<uint32_t>(Model::OMNIDIRECTIONAL);
        node["sensor_id"] = static_cast<uint32_t>(rhs.GetSensorId());
        node["width"]     = rhs.GetWidth();
        node["height"]    = rhs.GetHeight();
        node["cx"]        = rhs.cx_;
        node["cy"]        = rhs.cy_;

        node["c"] = rhs.c_;
        node["d"] = rhs.d_;
        node["e"] = rhs.e_;

        node["a0"] = rhs.unproject_poly_[0];
        node["a1"] = rhs.unproject_poly_[1];
        node["a2"] = rhs.unproject_poly_[2];
        node["a3"] = rhs.unproject_poly_[3];
        node["a4"] = rhs.unproject_poly_[4];

        node["p0"]  = rhs.proj_poly_[0];
        node["p1"]  = rhs.proj_poly_[1];
        node["p2"]  = rhs.proj_poly_[2];
        node["p3"]  = rhs.proj_poly_[3];
        node["p4"]  = rhs.proj_poly_[4];
        node["p5"]  = rhs.proj_poly_[5];
        node["p6"]  = rhs.proj_poly_[6];
        node["p7"]  = rhs.proj_poly_[7];
        node["p8"]  = rhs.proj_poly_[8];
        node["p9"]  = rhs.proj_poly_[9];
        node["p10"] = rhs.proj_poly_[10];
        node["p11"] = rhs.proj_poly_[11];
        node["p12"] = rhs.proj_poly_[12];
        node["p13"] = rhs.proj_poly_[13];
        node["p14"] = rhs.proj_poly_[14];

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            if (node["model"].as<uint32_t>() != static_cast<uint32_t>(Model::OMNIDIRECTIONAL))
            {
                std::cout << "Invalid camera model, want " << static_cast<uint32_t>(Model::OMNIDIRECTIONAL)
                          << ", which is OMNIDIRECTIONAL, but given model is " << node["model"].as<uint32_t>() << "\n";
                return false;
            }

            rhs.SetSensorId(node["sensor_id"].as<uint32_t>());
            rhs.SetDimension(node["width"].as<uint32_t>(), node["height"].as<uint32_t>());
            rhs.SetPrinciplePoint(node["cx"].as<ScalarType>(), node["cy"].as<ScalarType>());
            rhs.SetAffineTransformation(node["c"].as<ScalarType>(), node["d"].as<ScalarType>(),
                                        node["e"].as<ScalarType>());

            // unproject_poly
            ScalarType a0 = node["a0"].as<ScalarType>();
            ScalarType a1 = node["a1"].as<ScalarType>();
            ScalarType a2 = node["a2"].as<ScalarType>();
            ScalarType a3 = node["a3"].as<ScalarType>();
            ScalarType a4 = node["a4"].as<ScalarType>();

            // project_poly
            ScalarType p0  = node["p0"].as<ScalarType>();
            ScalarType p1  = node["p1"].as<ScalarType>();
            ScalarType p2  = node["p2"].as<ScalarType>();
            ScalarType p3  = node["p3"].as<ScalarType>();
            ScalarType p4  = node["p4"].as<ScalarType>();
            ScalarType p5  = node["p5"].as<ScalarType>();
            ScalarType p6  = node["p6"].as<ScalarType>();
            ScalarType p7  = node["p7"] ? node["p7"].as<ScalarType>() : 0.0;
            ScalarType p8  = node["p8"] ? node["p8"].as<ScalarType>() : 0.0;
            ScalarType p9  = node["p9"] ? node["p9"].as<ScalarType>() : 0.0;
            ScalarType p10 = node["p10"] ? node["p10"].as<ScalarType>() : 0.0;
            ScalarType p11 = node["p11"] ? node["p11"].as<ScalarType>() : 0.0;
            ScalarType p12 = node["p12"] ? node["p12"].as<ScalarType>() : 0.0;
            ScalarType p13 = node["p13"] ? node["p13"].as<ScalarType>() : 0.0;
            ScalarType p14 = node["p14"] ? node["p14"].as<ScalarType>() : 0.0;

            // set unproject_poly and project_poly
            rhs.SetUnprojectPolynomial({a0, a1, a2, a3, a4},
                                       {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14});
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};

}  // namespace YAML

#endif
