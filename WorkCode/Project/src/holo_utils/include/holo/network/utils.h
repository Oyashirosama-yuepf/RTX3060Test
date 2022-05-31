#ifndef HOLO_NETWORK_UTILS_H
#define HOLO_NETWORK_UTILS_H

#include <holo/core/types.h>
#include <string>
#include <vector>

namespace holo
{
namespace network
{
class Utils
{
public:
    static std::vector<holo::uint8_t> GetMacAddress(std::string const& device);
    static std::vector<holo::uint8_t> GetFirstIpv4MacAddress();
    static std::string                GetHostname();
    static holo::uint32_t             GetHostId();
};

}  // namespace network
}  // namespace holo

#endif
