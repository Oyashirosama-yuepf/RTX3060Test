#ifndef HOLO_IO_COMMON_APP_STATUS_H_
#define HOLO_IO_COMMON_APP_STATUS_H_

#include <holo/io/utils/utils.h>
#include <holo/io/common/timestamp.h>
#include <holo/common/app_status.h>

namespace YAML
{
template <>
struct convert<holo::common::AppStatus>
{
    using ValueType = holo::common::AppStatus;
    using Timestamp = holo::common::Timestamp;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["timestamp"] = rhs.GetTimestamp();
        node["node_id"]   = static_cast<holo::uint16_t>(rhs.GetNodeId());
        for (size_t i = 0; i < rhs.size(); ++i)
        {
            node["status_code"].push_back(static_cast<holo::uint16_t>(rhs[i]));
        }
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetTimestamp(node["timestamp"].as<Timestamp>());
            rhs.SetNodeId(static_cast<holo::uint8_t>(node["node_id"].as<holo::uint16_t>()));
            rhs.clear();
            for (YAML::const_iterator it = node["status_code"].begin(); it != node["status_code"].end(); ++it)
            {
                rhs.push_back(static_cast<holo::uint8_t>(it->as<holo::uint16_t>()));
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