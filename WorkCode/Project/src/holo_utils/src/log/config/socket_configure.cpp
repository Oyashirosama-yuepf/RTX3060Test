#include <holo/log/config/socket_configure.h>

namespace holo
{
namespace log
{
SocketConfigure::SocketConfigure(YAML::Node const& config_node) : Configure(config_node)
{
    parse(config_node);
}

SocketConfigure::SocketConfigure(YAML::Node const& root_node, YAML::Node const& config_node) : Configure(root_node)
{
    Configure::parse(config_node);
    parse(config_node);
}

void SocketConfigure::parse(YAML::Node const& config_node)
{
    std::string name = extractValue<std::string>(config_node, std::string("name"));
    host_            = extractValue<std::string>(config_node, std::string("host"), host_);
    port_            = extractValue<holo::uint32_t>(config_node, std::string("port"), port_);
    server_name_     = extractValue<std::string>(config_node, std::string("server_name"), server_name_);
    ipv6_            = extractValue<holo::bool_t>(config_node, std::string("ipv6_enable"), ipv6_);

    std::string spaces(" \t\f\v\n\r");
    std::size_t found = name.find_first_not_of(spaces);
    if (found == std::string::npos)
    {
        ConfigureNameException e{config_node["name"].Mark()};
        throw e;
    }
    setName(name);
}

}  // namespace log

}  // namespace holo

