#ifndef HOLO_NETWORK_EXCEPTION_H
#define HOLO_NETWORK_EXCEPTION_H

#include <holo/core/exception.h>
#include <stdexcept>
#include <string>

namespace holo
{
namespace network
{
class SocketIOException : public holo::exception::RuntimeErrorException
{
public:
    explicit SocketIOException(std::string const& what) : holo::exception::RuntimeErrorException{what}
    {
    }
};

class IoctlException : public holo::exception::RuntimeErrorException
{
public:
    explicit IoctlException(std::string const& what) : holo::exception::RuntimeErrorException{what}
    {
    }
};

}  // namespace network
}  // namespace holo

#endif
