#ifndef HOLO_NETWORK_EPOLLER_H
#define HOLO_NETWORK_EPOLLER_H

#include <sys/epoll.h>
#include <vector>

#include <holo/core/types.h>

#include "common.h"
#include "socket.h"

namespace holo
{
namespace network
{
class Epoller
{
public:
    static constexpr holo::int32_t DEFAULT_MAX_EVENTS{128};

    explicit Epoller(holo::int32_t const max_events) noexcept;
    ~Epoller() noexcept;

    void Open();
    void Close();

    void AddEvent(Socket const socket, holo::int32_t const events);
    void ModEvent(Socket const socket, holo::int32_t const events);
    void DelEvent(Socket const socket, holo::int32_t const events);

    void ProcessEventOnce(holo::int32_t const milliseconds);

    void SetReadEventCallback(std::function<void(Socket const)> const& callback);
    void SetWriteEventCallback(std::function<void(Socket const)> const& callback);
    void SetErrorEventCallback(std::function<void(Socket const)> const& callback);
    void SetHangupEventCallback(std::function<void(Socket const)> const& callback);

private:
    holo::int32_t getEpollEvent(holo::int32_t const events);
    holo::int32_t control(Socket const socket, holo::int32_t const events, holo::int32_t const operation);

private:
    holo::int32_t                     epoll_fd_;
    holo::int32_t                     max_events_;
    std::vector<struct epoll_event>   events_;
    std::function<void(Socket const)> read_event_callback_;
    std::function<void(Socket const)> write_event_callback_;
    std::function<void(Socket const)> error_event_callback_;
    std::function<void(Socket const)> hangup_event_callback_;
};

}  // namespace network
}  // namespace holo
#endif
