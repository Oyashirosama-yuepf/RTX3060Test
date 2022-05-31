#ifndef HOLO_IO_COMMON_ROAD_CATEGORY_H_
#define HOLO_IO_COMMON_ROAD_CATEGORY_H_

#include <holo/common/road_category.h>
#include <holo/io/utils/utils.h>
#include <holo/utils/yaml.h>

namespace YAML
{
template <>
struct convert<holo::common::RoadCategory>
{
    using ValueType = holo::common::RoadCategory;

    static std::vector<std::pair<std::string, holo::uint16_t> > const& CategoryStringCategoryPairs() noexcept
    {
        static const std::vector<std::pair<std::string, holo::uint16_t> > category_category_str = {
            {"UNKNOWN", 0}, {"MAINROAD", 1}, {"RAMP", 2}};
        return category_category_str;
    };

    static std::vector<std::pair<std::string, holo::uint32_t> > const& TagStringCategoryPairs() noexcept
    {
        static const std::vector<std::pair<std::string, holo::uint32_t> > tag_category_str = {{"TUNNEL", 0x01},
                                                                                              {"TOLL", 0x02}};
        return tag_category_str;
    };

    static Node encode(ValueType const& rhs)
    {
        Node node;

        if (rhs.IsCategoryUnknown())
        {
            node["category"] = "UNKNOWN";
        }
        else if (rhs.IsCategoryMainRoad())
        {
            node["category"] = "MAINROAD";
        }
        else if (rhs.IsCategoryRamp())
        {
            node["category"] = "RAMP";
        }

        if (rhs.HasTagTunnel())
        {
            node["tags"].push_back("TUNNEL");
        }
        if (rhs.HasTagToll())
        {
            node["tags"].push_back("TOLL");
        }

        return node;
    };

    static void SetCategoryValue(ValueType& rhs, std::string category)
    {
        if (category == "UNKNOWN")
        {
            rhs.SetCategoryUnknown();
        }
        else if (category == "MAINROAD")
        {
            rhs.SetCategoryMainRoad();
        }
        else if (category == "RAMP")
        {
            rhs.SetCategoryRamp();
        }
    };

    static void SetTagValue(ValueType& rhs, std::string tag)
    {
        if (tag == "TUNNEL")
        {
            rhs.SetTagTunnel();
        }
        if (tag == "TOLL")
        {
            rhs.SetTagToll();
        }
    };

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            if (node.Type() == YAML::NodeType::Scalar)
            {
                if (YAML::IsDigit(node.as<std::string>()))
                {
                    rhs = ValueType(node.as<holo::uint32_t>());
                }
            }
            else if (node.Type() == YAML::NodeType::Map)
            {
                if (node["category"].Type() == YAML::NodeType::Scalar)
                {
                    if (YAML::IsDigit(node["category"].as<std::string>()))
                    {
                        for (auto const& value : CategoryStringCategoryPairs())
                        {
                            if (value.second == node["category"].as<holo::uint16_t>())
                            {
                                SetCategoryValue(rhs, value.first);
                            }
                        }
                    }
                    else
                    {
                        SetCategoryValue(rhs, node["category"].as<std::string>());
                    }
                }

                rhs.ResetTagTunnel();
                rhs.ResetTagToll();
                if (node["tags"].Type() == YAML::NodeType::Sequence)
                {
                    for (std::size_t i = 0; i < node["tags"].size(); i++)
                    {
                        if (YAML::IsDigit(node["tags"][i].as<std::string>()))
                        {
                            for (auto const& value : TagStringCategoryPairs())
                            {
                                if (value.second == node["tags"][i].as<std::uint32_t>())
                                {
                                    SetTagValue(rhs, value.first);
                                }
                            }
                        }
                        else
                        {
                            SetTagValue(rhs, node["tags"][i].as<std::string>());
                        }
                    }
                }
            }
            return true;
        }
        catch (...)
        {
            return false;
        }
    };
};

template <>
struct convert<holo::common::LaneCategory>
{
    using ValueType = holo::common::LaneCategory;

    static std::vector<std::pair<std::string, holo::uint16_t> > const& CategoryStringCategoryPairs() noexcept
    {
        static const std::vector<std::pair<std::string, holo::uint16_t> > category_category_str = {
            {"UNKNOWN", 0}, {"REGULAR", 1}, {"ACCELERATION", 2}, {"DECELERATION", 3}, {"EMERGENCY", 4}};
        return category_category_str;
    };

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["tags"] = rhs.GetValue() & 0x0fff;

        if (rhs.IsCategoryUnknown())
        {
            node["category"] = "UNKNOWN";
        }
        else if (rhs.IsCategoryRegular())
        {
            node["category"] = "REGULAR";
        }
        else if (rhs.IsCategoryAcceleration())
        {
            node["category"] = "ACCELERATION";
        }
        else if (rhs.IsCategoryDeceleration())
        {
            node["category"] = "DECELERATION";
        }
        else if (rhs.IsCategoryEmergency())
        {
            node["category"] = "EMERGENCY";
        }
        return node;
    }

    static void SetCategoryValue(ValueType& rhs, std::string category)
    {
        if (category == "UNKNOWN")
        {
            rhs.SetCategoryUnknown();
        }
        else if (category == "REGULAR")
        {
            rhs.SetCategoryRegular();
        }
        else if (category == "ACCELERATION")
        {
            rhs.SetCategoryAcceleration();
        }
        else if (category == "DECELERATION")
        {
            rhs.SetCategoryDeceleration();
        }
        else if (category == "EMERGENCY")
        {
            rhs.SetCategoryEmergency();
        }
    };

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            if (node.Type() == YAML::NodeType::Scalar)
            {
                if (YAML::IsDigit(node.as<std::string>()))
                {
                    rhs = ValueType(node.as<holo::uint32_t>());
                }
            }
            else if (node.Type() == YAML::NodeType::Map)
            {
                rhs.SetValue(node["tags"].as<holo::uint32_t>());

                if (node["category"].Type() == YAML::NodeType::Scalar)
                {
                    if (YAML::IsDigit(node["category"].as<std::string>()))
                    {
                        for (auto const& value : CategoryStringCategoryPairs())
                        {
                            if (value.second == node["category"].as<holo::uint16_t>())
                            {
                                SetCategoryValue(rhs, value.first);
                            }
                        }
                    }
                    else
                    {
                        SetCategoryValue(rhs, node["category"].as<std::string>());
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
