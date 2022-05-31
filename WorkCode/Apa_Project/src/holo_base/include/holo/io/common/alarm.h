#ifndef HOLO_IO_COMMON_ALARM_H_
#define HOLO_IO_COMMON_ALARM_H_

#include <holo/utils/yaml.h>
#include <holo/io/utils/utils.h>
#include <holo/common/alarm.h>

namespace YAML
{
template <>
struct convert<holo::common::Alarm>
{
    using ValueType = holo::common::Alarm;
    using Level = typename holo::common::Alarm::Level;

    static std::vector<std::pair<std::string, Level> > const& StringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, Level> > level_type_str =    
        {
            {"NORMAL" ,Level::NORMAL},
            {"MINOR" ,Level::MINOR},
            {"MODERATE" ,Level::MODERATE},
            {"FATAL_1", Level::FATAL_1},
            {"FATAL_2", Level::FATAL_2}
        };
        return level_type_str;
    };
    
    static Node encode(ValueType const& rhs)
    {
        Node node;
        for (auto const& value : StringTypePairs())
        {
            if (value.second == rhs.GetLevel())
            {
                node["level"] = value.first;
            }
        }
        node["code"] = static_cast<uint16_t>(rhs) & 0x1f; 
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        if (node.Type() == YAML::NodeType::Scalar)
        {
            rhs = ValueType(node.as<uint16_t>());
        }
        else if (node.Type() == YAML::NodeType::Map)
        {

            bool decode_flag = false;
            for (auto const& value : StringTypePairs())
            {
                if (value.first == node["level"].as<std::string>())
                {
                    uint16_t level = static_cast<uint16_t>(value.second);
                    uint16_t code = node["code"].as<uint16_t>();
                    rhs = ValueType(static_cast<uint16_t>((level << 13U) + code));
                    decode_flag = true;
                }
            }
            if(!decode_flag)
            {
                if (IsDigit(node["level"].as<std::string>()))
                {
                    uint16_t level = node["level"].as<uint16_t>();
                    uint16_t code = node["code"].as<uint16_t>();
                    rhs = ValueType(static_cast<uint16_t>((level << 13U) + code));
                }
                else
                {
                    return false;
                }
            }
        }
        return true;
    };
};
};  // namespace YAML

#endif
