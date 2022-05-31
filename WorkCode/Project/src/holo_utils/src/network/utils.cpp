#include <ifaddrs.h> /*for getifaddrs freeifaddrs*/
#include <net/if.h>  /*for struct ifreq*/
#include <string.h>
#include <sys/ioctl.h>  /*for SIOCGIFHWADDR ioctl*/
#include <sys/socket.h> /*for socket*/
#include <sys/types.h>  /*for socket*/
#include <unistd.h>     /*for gethostid...*/
#include <functional>
#include <stdexcept>

#include <holo/network/exception.h>
#include <holo/network/utils.h>

#ifndef SIOCGIFHWADDR
#define SIOCGIFHWADDR 0x8927 /* Get hardware address */
#endif

namespace holo
{
namespace network
{
std::vector<holo::uint8_t> Utils::GetMacAddress(std::string const& device)
{
    holo::int32_t fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == fd)
    {
        throw holo::exception::RuntimeErrorException{"GetMacAddress: create socket failed!"};
    }

    struct ifreq ifr_mac;
    memset(&ifr_mac, 0, sizeof(ifr_mac));
    strncpy(ifr_mac.ifr_name, device.c_str(), sizeof(ifr_mac.ifr_name) - 1);

    if ((ioctl(fd, SIOCGIFHWADDR, &ifr_mac)) < 0)
    {
        close(fd);
        throw IoctlException{"GetMacAddress: ioctl mac failed!"};
    }

    close(fd);

    std::vector<holo::uint8_t> mac_addr(6U);
    for (holo::uint32_t i = 0U; i < 6U; ++i)
    {
#if defined(__linux__)
        mac_addr[i] = (holo::uint8_t)ifr_mac.ifr_hwaddr.sa_data[i];
#else
        mac_addr[i] = 'A';
#endif
    }

    return mac_addr;
}

std::vector<holo::uint8_t> Utils::GetFirstIpv4MacAddress()
{
#if defined(__QNX__)
    std::vector<holo::uint8_t> qnx_mac_addr(6U);
    for (holo::uint32_t i = 0U; i < 6U; ++i)
    {
        qnx_mac_addr[i] = 'A';
    }
    return qnx_mac_addr;
#endif

    struct ifaddrs* interface_address{nullptr};

    getifaddrs(&interface_address);

    struct ifaddrs* ifa = interface_address;
    while (nullptr != ifa)
    {
        if ((nullptr != ifa->ifa_addr) && (ifa->ifa_addr->sa_family == AF_INET))
        {
            std::string                name{ifa->ifa_name};
            std::vector<holo::uint8_t> mac_addr;

            try
            {
                mac_addr = GetMacAddress(ifa->ifa_name);
            }
            catch (IoctlException const& e)
            {
                continue;
            }

            for (holo::uint32_t i = 0U; i < mac_addr.size(); ++i)
            {
                if (0U != mac_addr[i])
                {
                    freeifaddrs(interface_address);
                    return mac_addr;
                }
            }
        }

        ifa = ifa->ifa_next;
    }

    if (nullptr != interface_address)
    {
        freeifaddrs(interface_address);
    }

    throw holo::exception::RuntimeErrorException{"GetFirstIpv4MacAddress() failed!"};
}

std::string Utils::GetHostname()
{
    holo::char_t hostname[128];

    gethostname(hostname, sizeof(hostname));

    return hostname;
}

holo::uint32_t Utils::GetHostId()
{
#if defined(__linux__)
    return gethostid();
#else
    std::string hostname = GetHostname();
    std::size_t hostname_hash_value = std::hash<std::string>{}(hostname);
    return hostname_hash_value;
#endif
}

}  // namespace network
}  // namespace holo
