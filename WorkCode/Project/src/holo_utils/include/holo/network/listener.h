#ifndef HOLO_NETWORK_LISTENER_H
#define HOLO_NETWORK_LISTENER_H

#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include <holo/core/types.h>

#include "common.h"
#include "poller.h"
#include "selector.h"
#include "socket.h"

#if defined(__linux__)
#include "epoller.h"
#endif

namespace holo
{
namespace network
{
class Listener : public std::enable_shared_from_this<Listener>
{
public:
#if defined(__linux__)
    using MultiplexerType = Epoller;
#else
    using MultiplexerType = Poller;
#endif

    // using MultiplexerType = Selector;

    Listener(holo::int32_t const domain, holo::int32_t const type) noexcept;
    virtual ~Listener() noexcept;

    void Init();
    void Destroy();

    void SetNewConnectionCallback(
        std::function<void(Socket const, std::string const&, holo::int32_t const)> const& callback);

    void Add(std::string const& ip, holo::int32_t const port);
    void Add(holo::int32_t const port);

    void Del(std::string const& ip, holo::int32_t const port);
    void Del(holo::int32_t const port);

    void ProcessEventOnce();

private:
    void readEventCallback(Socket const socket);
    void writeEventCallback(Socket const socket);
    void errorEventCallback(Socket const socket);
    void hangupEventCallback(Socket const socket);

    void addSocket(Socket const listen_socket);
    void delSocket(Socket const listen_socket);
    void delAll();

    struct initPairHash
    {
        size_t operator()(std::pair<std::string, holo::int32_t> const& key) const noexcept;
    };

private:
    holo::int32_t                                                                   domain_;
    holo::int32_t                                                                   type_;
    MultiplexerType                                                                 io_multiplexer_;
    mutable std::mutex                                                              listen_info_mutex_;
    std::unordered_map<std::pair<std::string, holo::int32_t>, Socket, initPairHash> listen_info_;
    std::function<void(Socket const, std::string const&, holo::int32_t const)>      new_connection_callback_;
};

}  // namespace network
}  // namespace holo

#endif
