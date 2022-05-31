#ifndef HOLO_IO_COMMON_SENSOR_ID_H_
#define HOLO_IO_COMMON_SENSOR_ID_H_

#include <holo/common/sensor_id.h>
#include <holo/io/common/vehicle_location.h>
#include <holo/utils/yaml.h>
#include <holo/io/utils/utils.h>

namespace YAML
{
template <>
struct convert<holo::common::SensorId>
{
    using ValueType       = holo::common::SensorId;
    using Model           = typename ValueType::Model;
    using Category        = typename ValueType::Category;
    using VehicleLocation = holo::common::VehicleLocation;

    static std::vector<std::pair<std::string, Model> > const& ModelStringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, Model> > model_type_str = {
            {"UNKNOWN", Model::UNKNOWN},
            {"GNSS_UNKNOWN", Model::GNSS_UNKNOWN},
            {"GNSS_NOVATEL", Model::GNSS_NOVATEL},
            {"GNSS_XSENS", Model::GNSS_XSENS},
            {"GNSS_UBLOX_M8L", Model::GNSS_UBLOX_M8L},
            {"GNSS_UBLOX_M8T", Model::GNSS_UBLOX_M8T},
            {"GNSS_UBLOX_M8Z", Model::GNSS_UBLOX_M8Z},
            {"GNSS_UBLOX_F9", Model::GNSS_UBLOX_F9},
            {"GNSS_QIANXU", Model::GNSS_QIANXU},
            {"GNSS_SCT_LANETO", Model::GNSS_SCT_LANETO},
            {"GNSS_SPATIAL", Model::GNSS_SPATIAL},
            {"GNSS_UNICORE", Model::GNSS_UNICORE},
            {"GNSS_BDSTAR_NPOS220", Model::GNSS_BDSTAR_NPOS220},

            {"IMU_UNKNOWN", Model::IMU_UNKNOWN},
            {"IMU_NOVATEL", Model::IMU_NOVATEL},
            {"IMU_XSENS", Model::IMU_XSENS},
            {"IMU_UBLOX_M8L", Model::IMU_UBLOX_M8L},
            {"IMU_UBLOX_F9K", Model::IMU_UBLOX_F9K},
            {"IMU_ACEINNA_305", Model::IMU_ACEINNA_305},
            {"IMU_ACEINNA_330", Model::IMU_ACEINNA_330},
            {"IMU_MURATA_2230", Model::IMU_MURATA_2230},

            {"CAMERA_UNKNOWN", Model::CAMERA_UNKNOWN},
            {"CAMERA_MOBILEYE_EQ3", Model::CAMERA_MOBILEYE_EQ3},
            {"CAMERA_MOBILEYE_EQ4", Model::CAMERA_MOBILEYE_EQ4},
            {"CAMERA_BOSCH_MPC", Model::CAMERA_BOSCH_MPC},
            {"CAMERA_DELPHI_IFV300", Model::CAMERA_DELPHI_IFV300},
            {"CAMERA_CALMCAR", Model::CAMERA_CALMCAR},
            {"CAMERA_ENTRON_F001R", Model::CAMERA_ENTRON_F001R},
            {"CAMERA_ENTRON_S001R", Model::CAMERA_ENTRON_S001R},
            {"CAMERA_LEOPARD_M021", Model::CAMERA_LEOPARD_M021},
            {"CAMERA_LEOPARD_AR0231", Model::CAMERA_LEOPARD_AR0231},
            {"CAMERA_LEOPARD_OV490", Model::CAMERA_LEOPARD_OV490},
            {"CAMERA_LEOPARD_AP020", Model::CAMERA_LEOPARD_AP020},

            {"RADAR_UNKNOWN", Model::RADAR_UNKNOWN},
            {"RADAR_CONTI_308", Model::RADAR_CONTI_308},
            {"RADAR_CONTI_408", Model::RADAR_CONTI_408},
            {"RADAR_CONTI_430", Model::RADAR_CONTI_430},
            {"RADAR_BOSCH_MRR4", Model::RADAR_BOSCH_MRR4},
            {"RADAR_DELPHI_ESR", Model::RADAR_DELPHI_ESR},
            {"RADAR_DELPHI_RSDS", Model::RADAR_DELPHI_RSDS},

            {"USS_UNKNOWN", Model::USS_UNKNOWN},
            {"USS_BOSCH", Model::USS_BOSCH},
            {"USS_IS", Model::USS_IS},
            {"USS_SOFTEC", Model::USS_SOFTEC},

            {"LIDAR_UNKNOWN", Model::LIDAR_UNKNOWN},
            {"LIDAR_IBEO_SCALA", Model::LIDAR_IBEO_SCALA},
            {"LIDAR_IBEO_LUX", Model::LIDAR_IBEO_LUX},
            {"LIDAR_VLP_16L", Model::LIDAR_VLP_16L},
            {"LIDAR_VLP_16L_HRS", Model::LIDAR_VLP_16L_HRS},
            {"LIDAR_VLP_32L", Model::LIDAR_VLP_32L},
            {"LIDAR_PANDAR_40L", Model::LIDAR_PANDAR_40L},
            {"LIDAR_LIVOX_MID40", Model::LIDAR_LIVOX_MID40},
            {"LIDAR_LIVOX_MID100", Model::LIDAR_LIVOX_MID100},
            {"LIDAR_LEISHEN_8L", Model::LIDAR_LEISHEN_8L},
            {"LIDAR_LEISHEN_16L", Model::LIDAR_LEISHEN_16L},
            {"LIDAR_BENEWAKE", Model::LIDAR_BENEWAKE},
            {"LIDAR_OUSTER", Model::LIDAR_OUSTER},
            {"LIDAR_SURESTAR", Model::LIDAR_SURESTAR},
            {"LIDAR_ROBOSENSE", Model::LIDAR_ROBOSENSE},

            {"AUDIO_UNKNOWN", Model::AUDIO_UNKNOWN},

            {"JOYSTICK_UNKNOWN", Model::JOYSTICK_UNKNOWN},
            {"JOYSTICK_BETOP", Model::JOYSTICK_BETOP}};
        return model_type_str;
    };

    static std::vector<std::pair<std::string, Category> > const& CategoryStringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, Category> > category_type_str = {
            {"UNKNOWN", Category::UNKNOWN}, {"GNSS", Category::GNSS},   {"IMU", Category::IMU},
            {"CAMERA", Category::CAMERA},   {"RADAR", Category::RADAR}, {"USS", Category::USS},
            {"LIDAR", Category::LIDAR},     {"AUDIO", Category::AUDIO}, {"JOYSTICK", Category::JOYSTICK},
        };
        return category_type_str;
    }

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["location"] = rhs.GetLocation();

        for (auto const& value : ModelStringTypePairs())
        {
            if (value.second == rhs.GetModel())
            {
                node["model"] = value.first;
            }
        }

        for (auto const& value : CategoryStringTypePairs())
        {
            if (value.second == rhs.GetCategory())
            {
                node["category"] = value.first;
            }
        }

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            if (node.Type() == YAML::NodeType::Scalar)
            {
                rhs = ValueType(node.as<uint32_t>());
            }
            else if (node.Type() == YAML::NodeType::Map)
            {
                rhs.SetLocation(node["location"].as<VehicleLocation>());

                bool location_flag = false;
                for (auto const& value : ModelStringTypePairs())
                {
                    if (value.first == node["model"].as<std::string>())
                    {
                        rhs.SetModel(value.second);
                        location_flag = true;
                    }
                }
                if (!location_flag)
                {
                    if (IsDigit(node["model"].as<std::string>()))
                    {
                        Model model = static_cast<Model>(node["model"].as<holo::uint16_t>());
                        rhs.SetModel(model);
                    }
                    else
                    {
                        return false;
                    }                        
                }

                bool category_flag = false;
                for (auto const& value : CategoryStringTypePairs())
                {
                    if (value.first == node["category"].as<std::string>())
                    {
                        rhs.SetCategory(value.second);
                        category_flag = true;
                    }
                }
                if(!category_flag)
                {
                    if (IsDigit(node["category"].as<std::string>()))
                    {
                        Category category = static_cast<Category>(node["category"].as<holo::uint16_t>());
                        rhs.SetCategory(category);
                    }
                    else
                    {
                        return false;
                    }
                }
            }
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