#ifndef HOLO_LOG_CONFIG_SOCKET_CONFIGURE_H_
#define HOLO_LOG_CONFIG_SOCKET_CONFIGURE_H_

#include <holo/log/config/configure.h>

namespace holo
{
namespace log
{
class SocketConfigure : public Configure
{
public:
    SocketConfigure(std::string const& name, std::string const& host, holo::uint32_t port)
      : Configure(name), host_(host), port_(port)
    {
    }

    SocketConfigure(YAML::Node const& config_node);
    SocketConfigure(YAML::Node const& root_node, YAML::Node const& config_node);

    virtual ~SocketConfigure() noexcept
    {
    }

    void SetHost(std::string const& host)
    {
        host_ = host;
    }

    std::string GetHost() const
    {
        return host_;
    }

    void SetPort(holo::uint32_t port)
    {
        port_ = port;
    }

    holo::uint32_t GetPort() const
    {
        return port_;
    }

    void SetServerName(std::string const& server_name)
    {
        server_name_ = server_name;
    }

    std::string GetServerName() const
    {
        return server_name_;
    }

    void SetIpv6(holo::bool_t value)
    {
        ipv6_ = value;
    }

    holo::bool_t GetIpv6() const
    {
        return ipv6_;
    }

private:
    /**
     * @brief parse configure form yaml node
     *
     * @param node YAML::Node
     */
    void parse(YAML::Node const& node);

private:
    std::string    host_;
    holo::uint32_t port_;
    std::string    server_name_{};
    holo::bool_t   ipv6_{false};
};

}  // namespace log

}  // namespace holo

#endif
