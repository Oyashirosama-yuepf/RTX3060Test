#ifndef HOLO_IO_COMMON_TIMESTAMP_H_
#define HOLO_IO_COMMON_TIMESTAMP_H_

#include <holo/common/timestamp.h>
#include <holo/utils/yaml.h>

namespace YAML
{
template <>
struct convert<holo::common::Duration>
{
    using ValueType = holo::common::Duration;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["sec"]  = rhs.GetSec();
        node["nsec"] = rhs.GetNsec();
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetSec(node["sec"].as<int32_t>());
            rhs.SetNsec(node["nsec"].as<int32_t>());
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};
template <>
struct convert<holo::common::Timestamp>
{
    using ValueType = holo::common::Timestamp;

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["sec"]  = rhs.GetSec();
        node["nsec"] = rhs.GetNsec();
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            uint32_t sec = 0, nsec = 0;
            sec  = node["sec"].as<uint32_t>();
            nsec = node["nsec"].as<uint32_t>();

            rhs.SetSec(sec);
            rhs.SetNsec(nsec);
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