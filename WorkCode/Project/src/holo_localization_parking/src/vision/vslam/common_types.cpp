/*!
 * \brief Vslam common types header file
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Feb-11-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Pose3& VehicleState::Pose() const
{
    return navstate.GetPose();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Vector3& VehicleState::Velocity() const
{
    return navstate.GetVelocity();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector3 VehicleState::VelocityInBody() const
{
    return Rotation().Unrotate(Velocity());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Point3& VehicleState::Translation() const
{
    return navstate.GetPose().GetTranslation();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Rot3& VehicleState::Rotation() const
{
    return navstate.GetPose().GetRotation();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Vector3 VehicleState::AccBias() const
{
    return bias.GetLinearAccelerationBias();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Vector3 VehicleState::GyroBias() const
{
    return bias.GetAngularVelocityBias();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PriorVehicleStateNoise PriorVehicleStateNoise::Example()
{
    return PriorVehicleStateNoise(Vector6(1.0, 1.0, 1.0, 1.0, 1.0, 1.0), Vector3(1.0, 1.0, 1.0),
                                  Vector6(1.0, 1.0, 1.0, 1.0, 1.0, 1.0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PriorVehicleStateNoise PriorVehicleStateNoise::LoadFromYaml(const holo::yaml::Node& node)
{
    Vector6 pose_sigma;
    {
        pose_sigma(0) = node["pose_sigma"][0].as<Scalar>(0.1);
        pose_sigma(1) = node["pose_sigma"][1].as<Scalar>(0.1);
        pose_sigma(2) = node["pose_sigma"][2].as<Scalar>(0.1);
        pose_sigma(3) = node["pose_sigma"][3].as<Scalar>(0.1);
        pose_sigma(4) = node["pose_sigma"][4].as<Scalar>(0.1);
        pose_sigma(5) = node["pose_sigma"][5].as<Scalar>(0.1);
    }

    Vector3 velocity_sigma;
    {
        velocity_sigma(0) = node["velocity_sigma"][0].as<Scalar>(0.1);
        velocity_sigma(1) = node["velocity_sigma"][1].as<Scalar>(0.1);
        velocity_sigma(2) = node["velocity_sigma"][2].as<Scalar>(0.1);
    }

    Vector6 bias_sigma;
    {
        bias_sigma(0) = node["bias_sigma"][0].as<Scalar>(0.1);
        bias_sigma(1) = node["bias_sigma"][1].as<Scalar>(0.1);
        bias_sigma(2) = node["bias_sigma"][2].as<Scalar>(0.1);
        bias_sigma(3) = node["bias_sigma"][3].as<Scalar>(0.1);
        bias_sigma(4) = node["bias_sigma"][4].as<Scalar>(0.1);
        bias_sigma(5) = node["bias_sigma"][5].as<Scalar>(0.1);
    }

    return PriorVehicleStateNoise(pose_sigma, velocity_sigma, bias_sigma);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapPoint::UpdateState()
{
    Scalar mean, cov, square_error_sum = 0, error_sum = 0;

    if (!reprojection_errors.size())
    {
        return;
    }

    for (const auto error : reprojection_errors)
    {
        error_sum += error;
    }
    mean = error_sum / reprojection_errors.size();

    for (const auto error : reprojection_errors)
    {
        square_error_sum += std::pow((error - mean), 2);
    }
    cov = std::sqrt(square_error_sum / reprojection_errors.size());

    if (mean >= 2 || cov >= 2)
    {
        return;
    }
    life_long_states.back() = MapPointState::MATCHED;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapPoint::UpdateRememberRate()
{
    // update life long state of this localization
    UpdateState();

    if (life_long_states.back() == MapPointState::CANDIDATE)
    {
        return;
    }

    const Scalar old_remember_rate = remember_rate;
    const Scalar s_increase_step   = 19;

    uint64_t the_max_not_ob_times_bear = 8;
    uint64_t current_not_ob_times_bear = 0;
    Scalar   not_ob_times              = 0.0;
    Scalar   s_decrease_init           = 0.0;
    Scalar   new_remember_rate         = 0.0;

    uint64_t s_update_times = 0;
    for (uint64_t i = 0; i < life_long_states.size() - 1; i++)
    {
        if (life_long_states[i] != MapPointState::CANDIDATE)
        {
            s_update_times++;
        }
    }
    Scalar old_s = -(s_update_times / std::log(old_remember_rate));

    if (life_long_states.back() == MapPointState::MATCHED)
    {
        Scalar new_s      = old_s + s_increase_step;
        new_remember_rate = std::exp(-((int)s_update_times + 1) / new_s);
        remember_rate     = new_remember_rate;
        return;
    }

    for (int index = life_long_states.size() - 1; index >= 0; index--)
    {
        if (life_long_states[index] != MapPointState::MATCHED)
        {
            not_ob_times = (life_long_states[index] == MapPointState::VISIBLE) ? not_ob_times + 1 : not_ob_times;
            continue;
        }

        if (index <= 10)
        {
            current_not_ob_times_bear = 3;
        }
        else
        {
            uint64_t ob_times = 0;
            for (int i = 0; i <= index; i++)
            {
                if (life_long_states[i] == MapPointState::MATCHED)
                {
                    ob_times++;
                }
            }
            current_not_ob_times_bear = std::floor((ob_times / index) * 10);
        }

        uint64_t bear_times = std::min(the_max_not_ob_times_bear, current_not_ob_times_bear);

        if (not_ob_times > bear_times)
        {
            remember_rate = 0;
            return;
        }
        Scalar s_end_stop = -(int)(index + bear_times) / std::log(0.29);

        if (not_ob_times == 1)
        {
            s_decrease_init = old_s;
        }
        else
        {
            s_decrease_init = (bear_times * old_s - (not_ob_times - 1) * s_end_stop) / (bear_times + 1 - not_ob_times);
        }

        Scalar new_s      = s_decrease_init - (s_decrease_init - s_end_stop) / bear_times * not_ob_times;
        new_remember_rate = std::exp(-((int)s_update_times + 1) / new_s);
        break;
    }
    remember_rate = new_remember_rate;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Pose3 Utility::CompensateT(Pose3 const& initial_T, Vector3 const& delta_rpy)
{
    Vector3 delta_rpy_new      = delta_rpy.GetHead(3u);
    delta_rpy_new(0)           = holo::Radian(delta_rpy(0u));
    delta_rpy_new(1)           = holo::Radian(delta_rpy(1u));
    delta_rpy_new(2)           = holo::Radian(delta_rpy(2u));
    const Rot3   compensated_R = Rot3::RzRyRx(initial_T.GetRotation().RPY() + delta_rpy_new);
    const Point3 compensated_t = initial_T.GetTranslation();
    return Pose3(compensated_R, compensated_t);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Pose3 Utility::ConstructTbc(const std::string lidar_extrinsic_file, const std::string camera_extrinsic_file,
                            const std::string body_gnss_extrinsic_file)
{
    // T_bn (novatel pose in body frame)
    Pose3 T_bn(Rot3::Rz(-M_PI / 2.0), Point3());
    if (body_gnss_extrinsic_file != "")
    {
        T_bn = Extrinsic::LoadYaml(holo::GetConfigFileAbsolutePath(body_gnss_extrinsic_file)).GetPose().Cast<Scalar>();
    }
    else
    {
        LOG(WARNING) << "Utility --- use default extrinsic "
                     << "novatel in body frame(90 degree)";
    }

    // T_nl (lidar pose in novatel frame
    const Pose3 T_nl =
        Extrinsic::LoadYaml(holo::GetConfigFileAbsolutePath(lidar_extrinsic_file)).GetPose().Cast<Scalar>();

    // T_lc (camera pose in lidar frame)
    const Pose3 T_lc =
        Extrinsic::LoadYaml(holo::GetConfigFileAbsolutePath(camera_extrinsic_file)).GetPose().Inverse().Cast<Scalar>();

    // return T_bc
    return T_bn * T_nl * T_lc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Matrix3 Utility::EssentialMatrixFromPoses(const Pose3& pose0, const Pose3& pose1)
{
    Pose3   delta     = pose1.Inverse() * pose0;
    Matrix3 r         = delta.GetRotation().ToMatrix();
    Vector3 t         = delta.GetTranslation().ToVector();
    Matrix3 essential = t.ToSkewSymmetric() * r;
    return essential;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint64_t Utility::HashId(const uint64_t& first_id, const uint64_t& second_id)
{
    const uint64_t unique_id = 0.5 * (first_id + second_id) * (first_id + second_id + 1) + second_id;
    return unique_id;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<uint64_t, uint64_t> Utility::UnHashId(const uint64_t& hashed_id)
{
    uint64_t w         = std::floor(0.5 * (std::sqrt(8 * hashed_id + 1) - 1));
    uint64_t t         = 0.5 * (w * w + w);
    uint64_t second_id = hashed_id - t;
    uint64_t first_id  = w - second_id;

    return std::make_pair(first_id, second_id);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImageUndistortionPtr Utility::CreateImageUndistorter(const IntrinsicBaseTypePtr& intrinsic)
{
    using Model = IntrinsicBaseType::Model;

    if (intrinsic->GetModel() != Model::FISHEYE && intrinsic->GetModel() != Model::PINHOLE)
    {
        return nullptr;
    }

    // convert vslam intrinsic to base intrinsic
    std::shared_ptr<holo::common::details::CameraIntrinsicBaseT<Scalar>> intrinsic_ptr;
    if (intrinsic->GetModel() == Model::PINHOLE)
    {
        PinholeIntrinsicType const* pinhole = dynamic_cast<PinholeIntrinsicType const*>(intrinsic.get());
        holo::common::details::PinholeIntrinsicT<Scalar> pinhole_intrinsic_base;
        pinhole_intrinsic_base.SetSensorId(intrinsic->GetSensorId());
        pinhole_intrinsic_base.SetPrinciplePoint(pinhole->GetK()(0, 2), pinhole->GetK()(1, 2));
        pinhole_intrinsic_base.SetFocalLength(pinhole->GetK()(0, 0), pinhole->GetK()(1, 1));
        pinhole_intrinsic_base.SetSkew(pinhole->GetK()(0, 1));
        pinhole_intrinsic_base.SetDimension(pinhole->GetWidth(), pinhole->GetHeight());
        pinhole_intrinsic_base.SetDistortionParameter(pinhole->GetD()(0), pinhole->GetD()(1), pinhole->GetD()(2),
                                                      pinhole->GetD()(3), pinhole->GetD()(4));
        intrinsic_ptr = std::make_shared<holo::common::details::PinholeIntrinsicT<Scalar>>(pinhole_intrinsic_base);
    }
    else
    {
        FisheyeIntrinsicType const* fisheye = dynamic_cast<FisheyeIntrinsicType const*>(intrinsic.get());
        holo::common::details::FisheyeIntrinsicT<Scalar> fisheye_intrinsic_base;
        fisheye_intrinsic_base.SetSensorId(intrinsic->GetSensorId());
        fisheye_intrinsic_base.SetPrinciplePoint(fisheye->GetK()(0, 2), fisheye->GetK()(1, 2));
        fisheye_intrinsic_base.SetFocalLength(fisheye->GetK()(0, 0), fisheye->GetK()(1, 1));
        fisheye_intrinsic_base.SetSkew(fisheye->GetK()(0, 1));
        fisheye_intrinsic_base.SetDimension(fisheye->GetWidth(), fisheye->GetHeight());
        fisheye_intrinsic_base.SetDistortionParameter(fisheye->GetD()(0), fisheye->GetD()(1), fisheye->GetD()(2),
                                                      fisheye->GetD()(3));
        intrinsic_ptr = std::make_shared<holo::common::details::FisheyeIntrinsicT<Scalar>>(fisheye_intrinsic_base);
    }

    return std::make_shared<ImageUndistortion>(intrinsic_ptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::shared_ptr<IntrinsicBaseType> Utility::CreateCameraIntrinsic(YAML::Node const& node)
{
    switch (node["model"].as<uint32_t>())
    {
        case static_cast<uint32_t>(IntrinsicBaseType::Model::PINHOLE):
            return std::make_shared<PinholeIntrinsicT<T>>(node.as<PinholeIntrinsicT<T>>());

        case static_cast<uint32_t>(IntrinsicBaseType::Model::FISHEYE):
            return std::make_shared<FisheyeIntrinsicT<T>>(node.as<FisheyeIntrinsicT<T>>());

        case static_cast<uint32_t>(IntrinsicBaseType::Model::OMNIDIRECTIONAL):
            return std::make_shared<OmnidirectionalIntrinsicT<T>>(node.as<OmnidirectionalIntrinsicT<T>>());
    }
    LOG(ERROR) << "Utility --- CreateCameraIntrinsic, the input source intrinsic "
                  "is invalid! model: "
               << node["model"].as<uint32_t>();
    throw std::runtime_error("Utility --- CreateCameraIntrinsic, invalid intrinsic");
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<ImageUndistortionPtr> Utility::CreateImageUndistorters(const std::vector<IntrinsicBaseTypePtr>& intrinsics)
{
    std::vector<ImageUndistortionPtr> ret;
    ret.reserve(intrinsics.size());

    for (size_t i = 0; i < intrinsics.size(); i++)
    {
        ret.emplace_back(CreateImageUndistorter(intrinsics.at(i)));
    }

    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IntrinsicBaseTypePtr CameraParameters::LoadIntrinsic(const holo::yaml::Node& node)
{
    const std::string intrinsic_file = holo::GetConfigFileAbsolutePath(node["intrinsic"].as<std::string>());
    LOG(INFO) << "CameraParameters --- Loading intrinsic from " << intrinsic_file << "\n";
    return Utility::CreateCameraIntrinsic<Scalar>(YAML::LoadFile(intrinsic_file));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraParameters::Ptr CameraParameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // local camera number
    const uint16_t camera_number = node["camera_number"].as<uint16_t>(0);

    if (camera_number == 0)
    {
        throw std::runtime_error("CameraParameters --- invalid camera number.\n");
    }

    // load camera coord
    std::vector<std::string> camera_coords =
        node["camera_coords"].as<std::vector<std::string>>(std::vector<std::string>{});
    if (camera_coords.size() != camera_number)
    {
        throw std::runtime_error("CameraParameters --- invalid camera coord.\n");
    }

    // load camera parameters
    std::vector<IntrinsicBaseTypePtr>      intrinsics;
    std::vector<Pose3>                     extrinsics;
    std::vector<Scalar>                    available_fov;
    std::vector<std::pair<Scalar, Scalar>> sigma_uv_and_loss;
    intrinsics.reserve(camera_number);
    extrinsics.reserve(camera_number);
    available_fov.reserve(camera_number);
    sigma_uv_and_loss.reserve(camera_number);

    for (uint16_t i = 0; i < camera_number; i++)
    {
        const std::string coord = camera_coords.at(i);

        // intrinsic
        intrinsics.emplace_back(CameraParameters::LoadIntrinsic(node[coord]));

        // extrinsic
        Pose3 T_bc = Pose3::Identity();

        // trying to load body to camera intrinsic directly
        const std::string body_camera_extrinsic_file = node[coord]["body_camera_extrinsic_file"].as<std::string>("");

        if (!body_camera_extrinsic_file.empty() &&
            boost::filesystem::exists(holo::GetConfigFileAbsolutePath(body_camera_extrinsic_file)))
        {
            T_bc = Extrinsic::LoadYaml(holo::GetConfigFileAbsolutePath(body_camera_extrinsic_file))
                       .GetPose()
                       .Cast<Scalar>();
        }
        else
        {
            LOG(INFO)
                << "CameraParameters --- body to camera extrinsic file does not provided, trying to construct Tbc from "
                   "the three offline calibrated file.";
            /////////////////// !!! @note !!! ////////////////////////////////
            //       construct extrinsic between camera and imu/body        //
            //               T_bc = T_bn * T_nl * T_lc                      //
            /////////////////// !!! @note !!!/////////////////////////////////

            // body_gnss_extrinsic_file (novatel in body frame)
            const std::string body_gnss_extrinsic_file = node["body_gnss_extrinsic_file"].as<std::string>("");
            // lidar_extrinsic_file
            const std::string lidar_extrinsic_file = node["lidar_extrinsic_file"].as<std::string>();
            const std::string lidar_camera_extrinsic_file =
                node[coord]["lidar_camera_extrinsic_file"].as<std::string>("");

            // body to camera bias
            const Scalar camera_extrinsic_bias_r = node[coord]["camera_extrinsic_bias"][0].as<Scalar>(0);
            const Scalar camera_extrinsic_bias_p = node[coord]["camera_extrinsic_bias"][1].as<Scalar>(0);
            const Scalar camera_extrinsic_bias_y = node[coord]["camera_extrinsic_bias"][2].as<Scalar>(0);

            // body to camera
            Vector3 delta_rpy(camera_extrinsic_bias_r, camera_extrinsic_bias_p, camera_extrinsic_bias_y);
            T_bc = Utility::CompensateT(
                Utility::ConstructTbc(lidar_extrinsic_file, lidar_camera_extrinsic_file, body_gnss_extrinsic_file),
                delta_rpy);
        }

        extrinsics.emplace_back(T_bc);

        // available_fov
        available_fov.emplace_back(node[coord]["available_fov"].as<Scalar>(-1.0));

        // sigma uv and loss
        const Scalar sigma_uv   = node[coord]["sigma_uv"].as<Scalar>(1.5);
        const Scalar huber_loss = node[coord]["huber_loss"].as<Scalar>(2.0);
        sigma_uv_and_loss.emplace_back(std::make_pair(sigma_uv, huber_loss));
    }

    return std::make_shared<CameraParameters>(camera_number, camera_coords, intrinsics, extrinsics, available_fov,
                                              sigma_uv_and_loss);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraParameters::Ptr CameraParameters::LoadFromBin(const std::string& params_file)
{
    std::ifstream fin(params_file);

    if (!fin)
    {
        LOG(ERROR) << "CameraParameters --- LoadFromBin, could not open " << params_file;
        return {};
    }

    // total camera number
    uint16_t camera_number;
    fin.read((char*)&camera_number, sizeof(uint16_t));

    // get parent directory of saved file
    const auto dir = holo::GetParentDirectory(params_file);

    // load camera parameters
    std::vector<std::string>               camera_coords;
    std::vector<IntrinsicBaseTypePtr>      intrinsics;
    std::vector<Pose3>                     extrinsics;
    std::vector<Scalar>                    available_fov;
    std::vector<std::pair<Scalar, Scalar>> sigma_uv_and_loss;
    camera_coords.reserve(camera_number);
    intrinsics.reserve(camera_number);
    extrinsics.reserve(camera_number);
    available_fov.reserve(camera_number);
    sigma_uv_and_loss.reserve(camera_number);

    // read data one by one
    for (uint16_t camera_index = 0; camera_index < camera_number; camera_index++)
    {
        // load camera coord
        std::string coord = "";
        uint16_t    len;
        fin.read((char*)&len, sizeof(uint16_t));

        for (uint16_t i = 0; i < len; i++)
        {
            char ch;
            fin.read((char*)&ch, sizeof(char));
            coord.push_back(ch);
        }

        camera_coords.emplace_back(coord);

        // load intrinsic
        std::string intrinsic_file = dir + "/camera_" + std::to_string(camera_index) + ".yaml";
        intrinsics.emplace_back(Utility::CreateCameraIntrinsic<Scalar>(YAML::LoadFile(intrinsic_file)));

        // load extrinsic
        Scalar t_x, t_y, t_z, q_w, q_x, q_y, q_z;
        fin.read((char*)&t_x, sizeof(Scalar));
        fin.read((char*)&t_y, sizeof(Scalar));
        fin.read((char*)&t_z, sizeof(Scalar));
        fin.read((char*)&q_w, sizeof(Scalar));
        fin.read((char*)&q_x, sizeof(Scalar));
        fin.read((char*)&q_y, sizeof(Scalar));
        fin.read((char*)&q_z, sizeof(Scalar));
        extrinsics.emplace_back(Rot3(Quaternion(q_w, q_x, q_y, q_z).ToRotationMatrix()), Point3(t_x, t_y, t_z));

        // load fov
        Scalar fov = -1;
        fin.read((char*)&fov, sizeof(Scalar));
        available_fov.emplace_back(fov);

        // load sigma uv and loss
        Scalar sigma_uv = 1.5, loss = 2.0;
        fin.read((char*)&sigma_uv, sizeof(Scalar));
        fin.read((char*)&loss, sizeof(Scalar));
        sigma_uv_and_loss.emplace_back(std::make_pair(sigma_uv, loss));
    }

    return std::make_shared<CameraParameters>(camera_number, camera_coords, intrinsics, extrinsics, available_fov,
                                              sigma_uv_and_loss);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CameraParameters::SaveParametersToBin(const std::string& params_file) const
{
    std::ofstream file(params_file);

    if (!file)
    {
        LOG(ERROR) << "CameraParameters --- SaveParametersToBin, could not open " << params_file;
        return;
    }

    if (camera_number == 0)
    {
        LOG(ERROR) << "CameraParameters --- SaveParametersToBin, camera number is zero.";
        return;
    }

    // save camera number
    file.write((const char*)&(camera_number), sizeof(uint16_t));

    // get parent directory of saved file
    const auto dir = holo::GetParentDirectory(params_file);

    // save camera parameters one by one
    for (uint16_t camera_index = 0; camera_index < camera_number; camera_index++)
    {
        // save camera coord
        const std::string& coord = camera_coords.at(camera_index);
        uint16_t           len   = coord.length();
        file.write((char*)&len, sizeof(uint16_t));
        file.write((const char*)&(coord), len * sizeof(char));

        // save intrinsic
        YAML::Node  intrinsic_node;
        const auto& intrinsic = intrinsics.at(camera_index);
        if (intrinsic->GetModel() == Model::PINHOLE)
        {
            PinholeIntrinsicType const* pinhole = dynamic_cast<PinholeIntrinsicType const*>(intrinsic.get());
            if (!pinhole)
            {
                LOG(ERROR) << "CameraParameters --- SaveParametersToBin, failed to cast source intrinsic to "
                              "pinhole type";
                throw std::runtime_error(
                    "CameraParameters --- SaveParametersToBin, failed to cast source intrinsic to pinhole type");
            }
            intrinsic_node = *pinhole;
        }
        else if (intrinsic->GetModel() == Model::FISHEYE)
        {
            FisheyeIntrinsicType const* fisheye = dynamic_cast<FisheyeIntrinsicType const*>(intrinsic.get());
            if (!fisheye)
            {
                LOG(ERROR) << "CameraParameters --- SaveParametersToBin, failed to cast source intrinsic to "
                              "fisheye type";
                throw std::runtime_error(
                    "CameraParameters --- SaveParametersToBin, failed to cast source intrinsic to fisheye type");
            }
            intrinsic_node = *fisheye;
        }
        else if (intrinsic->GetModel() == Model::OMNIDIRECTIONAL)
        {
            OmnidirectionalIntrinsicType const* ocam =
                dynamic_cast<OmnidirectionalIntrinsicType const*>(intrinsic.get());
            if (!ocam)
            {
                LOG(ERROR) << "CameraParameters --- SaveParametersToBin, failed to cast source intrinsic to "
                              "ocam type";
                throw std::runtime_error(
                    "CameraParameters --- SaveParametersToBin, failed to cast source intrinsic to ocam type");
            }
        }
        else
        {
            LOG(ERROR) << "CameraParameters --- SaveParametersToBin, the input source intrinsic is invalid! model: "
                       << (intrinsic ? static_cast<uint16_t>(intrinsic->GetModel()) :
                                       static_cast<uint16_t>(Model::UNKNOWN));
            throw std::runtime_error("CameraParameters --- SaveParametersToBin, invalid intrinsic");
        }

        std::string   intrinsic_file_string = dir + "/camera_" + std::to_string(camera_index) + ".yaml";
        std::ofstream intrinsic_file(intrinsic_file_string);
        intrinsic_file << intrinsic_node;
        intrinsic_file.close();

        // save extrinsic
        const auto& T_bc        = extrinsics.at(camera_index);
        Vector3     translation = T_bc.GetTranslation().ToVector();
        Quaternion  quaternion  = T_bc.GetRotation().ToQuaternion();
        Scalar      x           = translation[0];
        Scalar      y           = translation[1];
        Scalar      z           = translation[2];
        Scalar      q_w         = quaternion.GetW();
        Scalar      q_x         = quaternion.GetX();
        Scalar      q_y         = quaternion.GetY();
        Scalar      q_z         = quaternion.GetZ();
        file.write((const char*)&(x), sizeof(Scalar));
        file.write((const char*)&(y), sizeof(Scalar));
        file.write((const char*)&(z), sizeof(Scalar));
        file.write((const char*)&(q_w), sizeof(Scalar));
        file.write((const char*)&(q_x), sizeof(Scalar));
        file.write((const char*)&(q_y), sizeof(Scalar));
        file.write((const char*)&(q_z), sizeof(Scalar));

        // save available_fov
        const Scalar fov = available_fov.at(camera_index);
        file.write((const char*)&(fov), sizeof(Scalar));

        // save sigma uv and loss
        const Scalar sigma_uv = sigma_uv_and_loss.at(camera_index).first;
        const Scalar loss     = sigma_uv_and_loss.at(camera_index).second;
        file.write((const char*)&(sigma_uv), sizeof(Scalar));
        file.write((const char*)&(loss), sizeof(Scalar));
    }

    LOG(ERROR) << "CameraParameters --- SaveParametersToBin done.";
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CameraParameters::Ptr CameraParameters::Example()
{
    const uint16_t           camera_number = 1;
    std::vector<std::string> camera_coords(1, "front_center");

    // generate camera intrinsic
    IntrinsicBaseTypePtr intrinsic;

    std::vector<IntrinsicBaseTypePtr>      intrinsics(1, intrinsic);
    std::vector<Pose3>                     extrinsics(1, Pose3::Identity());
    std::vector<Scalar>                    available_fov(1, 120.0);
    std::vector<std::pair<Scalar, Scalar>> sigma_uv_and_loss(1, std::make_pair(1.5, 2.0));

    return std::make_shared<CameraParameters>(camera_number, camera_coords, intrinsics, extrinsics, available_fov,
                                              sigma_uv_and_loss);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Scalar CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(const IntrinsicBaseTypePtr& intrinsic,
                                                                      const Scalar                pixel_error)
{
    Point3 optical_axis;
    Point3 optical_axis_noise;

    using Model = IntrinsicBaseType::Model;
    if (intrinsic->GetModel() == Model::PINHOLE)
    {
        PinholeIntrinsicType const* pinhole = dynamic_cast<PinholeIntrinsicType const*>(intrinsic.get());

        if (!pinhole)
        {
            LOG(ERROR)
                << "ComputeUnit3ErrorFromPixelErrorAtImageCenter --- failed to cast source intrinsic to pinhole type";
            throw std::runtime_error(
                "ComputeUnit3ErrorFromPixelErrorAtImageCenter --- failed to cast source intrinsic to pinhole type");
        }

        // create the first direction vector by unproject principal point
        const auto&  K  = pinhole->GetK();
        const Scalar cx = K(0, 2), cy = K(1, 2);
        const Point2 principal_point(cx, cy);
        pinhole->Unproject(principal_point, optical_axis);

        // create the second direction vector by unproject principal point + noise
        const Point2 principal_point_noise = principal_point + Point2(pixel_error, 0.0);
        pinhole->Unproject(principal_point_noise, optical_axis_noise);
    }
    else if (intrinsic->GetModel() == Model::FISHEYE)
    {
        FisheyeIntrinsicType const* fisheye = dynamic_cast<FisheyeIntrinsicType const*>(intrinsic.get());

        if (!fisheye)
        {
            LOG(ERROR)
                << "ComputeUnit3ErrorFromPixelErrorAtImageCenter --- failed to cast source intrinsic to fisheye type";
            throw std::runtime_error(
                "ComputeUnit3ErrorFromPixelErrorAtImageCenter --- failed to cast source intrinsic to fisheye type");
        }

        // create the first direction vector by unproject principal point
        const auto&  K  = fisheye->GetK();
        const Scalar cx = K(0, 2), cy = K(1, 2);
        const Point2 principal_point(cx, cy);
        fisheye->Unproject(principal_point, optical_axis);

        // create the second direction vector by unproject principal point + noise
        const Point2 principal_point_noise = principal_point + Point2(pixel_error, 0.0);
        fisheye->Unproject(principal_point_noise, optical_axis_noise);
    }
    else if (intrinsic->GetModel() == Model::OMNIDIRECTIONAL)
    {
        OmnidirectionalIntrinsicType const* ocam = dynamic_cast<OmnidirectionalIntrinsicType const*>(intrinsic.get());

        if (!ocam)
        {
            LOG(ERROR)
                << "ComputeUnit3ErrorFromPixelErrorAtImageCenter --- failed to cast source intrinsic to ocam type";
            throw std::runtime_error(
                "ComputeUnit3ErrorFromPixelErrorAtImageCenter --- failed to cast source intrinsic to ocam type");
        }
        // create the first direction vector by unproject principal point
        const Point2 principal_point = ocam->GetPrinciplePoint();
        ocam->Unproject(principal_point, optical_axis);

        // create the second direction vector by unproject principal point + noise
        const Point2 principal_point_noise = principal_point + Point2(pixel_error, 0.0);
        ocam->Unproject(principal_point_noise, optical_axis_noise);
    }
    else
    {
        LOG(ERROR) << "CameraParameters --- ComputeUnit3ErrorFromPixelErrorAtImageCenter, the input source intrinsic "
                      "is invalid! model: "
                   << (intrinsic ? static_cast<uint16_t>(intrinsic->GetModel()) :
                                   static_cast<uint16_t>(Model::UNKNOWN));
        throw std::runtime_error(
            "CameraParameters --- ComputeUnit3ErrorFromPixelErrorAtImageCenter, invalid intrinsic");
    }

    // construct Unit3 from 3d point
    const gtsam::Unit3 p = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(optical_axis));
    const gtsam::Unit3 q = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(optical_axis_noise));

    return p.errorVector(q).norm();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<cv::Rect2i> CameraParameters::CreateROI(const std::vector<IntrinsicBaseTypePtr>& intrinsics,
                                                    const std::vector<Scalar>&               available_fov) const
{
    std::vector<cv::Rect2i> rois;
    rois.reserve(intrinsics.size());

    for (uint16_t camera_index = 0; camera_index < intrinsics.size(); camera_index++)
    {
        const auto& intrinsic = intrinsics.at(camera_index);
        const auto& fov       = available_fov.at(camera_index);

        if (fov < 0)
        {
            rois.emplace_back(0, 0, intrinsic->GetWidth(), intrinsic->GetHeight());
            continue;
        }
        Point2 principal_point = Point2();
        Scalar cx              = 0.0;
        Scalar cy              = 0.0;
        if (intrinsic->GetModel() == Model::PINHOLE)
        {
            PinholeIntrinsicType const* pinhole = dynamic_cast<PinholeIntrinsicType const*>(intrinsic.get());

            if (!pinhole)
            {
                LOG(ERROR) << "CreateROI --- failed to cast source intrinsic to "
                              "pinhole type";
                throw std::runtime_error("CreateROI --- failed to cast source intrinsic to pinhole type");
            }
            cx              = pinhole->GetK()(0, 2);
            cy              = pinhole->GetK()(1, 2);
            principal_point = Point2(cx, cy);
        }
        else if (intrinsic->GetModel() == Model::FISHEYE)
        {
            FisheyeIntrinsicType const* fisheye = dynamic_cast<FisheyeIntrinsicType const*>(intrinsic.get());

            if (!fisheye)
            {
                LOG(ERROR) << "CreateROI --- failed to cast source intrinsic to "
                              "fisheye type";
                throw std::runtime_error("CreateROI --- failed to cast source intrinsic to fisheye type");
            }
            cx              = fisheye->GetK()(0, 2);
            cy              = fisheye->GetK()(1, 2);
            principal_point = Point2(cx, cy);
        }
        else if (intrinsic->GetModel() == Model::OMNIDIRECTIONAL)
        {
            OmnidirectionalIntrinsicType const* ocam =
                dynamic_cast<OmnidirectionalIntrinsicType const*>(intrinsic.get());

            if (!ocam)
            {
                LOG(ERROR) << "CreateROI --- failed to cast source intrinsic to ocam type";
                throw std::runtime_error("CreateROI --- failed to cast source intrinsic to ocam type");
            }
            principal_point = ocam->GetPrinciplePoint();
            cx              = principal_point.GetX();
            cy              = principal_point.GetY();
        }
        else
        {
            LOG(ERROR) << "CameraParameters --- CreateROI, the input source intrinsic "
                          "is invalid! model: "
                       << (intrinsic ? static_cast<uint16_t>(intrinsic->GetModel()) :
                                       static_cast<uint16_t>(Model::UNKNOWN));
            throw std::runtime_error("CameraParameters --- CreateROI, invalid intrinsic");
        }

        Point3 optical_axis;
        intrinsic->Unproject(principal_point, optical_axis);

        uint16_t x = 0;

        // compute x
        for (; x < cx; x++)
        {
            Point2 pt(x, cy);
            Point3 ptn;
            intrinsic->Unproject(pt, ptn);

            // create Unit3 from 3d point
            const gtsam::Unit3 p = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(ptn));
            const gtsam::Unit3 q = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(optical_axis));

            // compute and ckeck angle between these two vector
            const auto theta = holo::Degree(std::acos(p.dot(q)));

            if (2.0 * theta <= fov)
            {
                break;
            }
        }

        uint16_t y = 0;

        // compute y
        for (; y < cy; y++)
        {
            Point2 pt(cx, y);
            Point3 ptn;
            intrinsic->Unproject(pt, ptn);

            // create Unit3 from 3d point
            const gtsam::Unit3 p = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(ptn));
            const gtsam::Unit3 q = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(optical_axis));

            // compute and ckeck angle between these two vector
            const auto theta = holo::Degree(std::acos(p.dot(q)));

            if (2.0 * theta <= fov)
            {
                break;
            }
        }

        // now (x, y) is the top left point of the roi
        const auto width  = 2 * (cx - x);
        const auto height = 2 * (cy - y);

        if (width > intrinsic->GetWidth() || height > intrinsic->GetHeight())
        {
            LOG(ERROR) << "CameraParameters --- failed to create roi for camera " << camera_index << ", cx: " << cx
                       << ", cy: " << cy << ", x: " << x << ", y: " << y << "\n";
            throw std::runtime_error("CameraParameters --- failed to create roi");
        }

        rois.emplace_back(x, y, width, height);
    }

    return rois;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
