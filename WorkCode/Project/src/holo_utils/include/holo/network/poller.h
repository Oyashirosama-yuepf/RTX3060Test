#ifndef HOLO_NETWORK_POLLER_H
#define HOLO_NETWORK_POLLER_H

#include <poll.h>
#include <mutex>
#include <vector>

#include <holo/core/types.h>

#include "common.h"
#include "socket.h"

namespace holo
{
namespace network
{
class Poller
{
public:
    static constexpr holo::int32_t DEFAULT_MAX_EVENTS{1024};

    Poller() noexcept;
    explicit Poller(holo::int32_t const max_events) noexcept;
    ~Poller() noexcept;

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
    holo::int32_t getPollEvent(holo::int32_t const events);

    std::vector<struct pollfd> getEvents();

private:
    holo::bool_t                      is_init_;
    holo::int32_t                     max_events_;
    holo::int32_t                     current_event_size_;
    std::vector<struct pollfd>        events_;
    mutable std::mutex                events_mutex_;
    std::function<void(Socket const)> read_event_callback_;
    std::function<void(Socket const)> write_event_callback_;
    std::function<void(Socket const)> error_event_callback_;
    std::function<void(Socket const)> hangup_event_callback_;
};

}  // namespace network
}  // namespace holo
#endif
