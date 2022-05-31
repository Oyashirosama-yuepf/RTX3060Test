#ifndef HOLO_NETWORK_SELECTOR_H
#define HOLO_NETWORK_SELECTOR_H

#include <sys/select.h>
#include <mutex>
#include <set>

#include <holo/core/types.h>

#include "common.h"
#include "socket.h"

namespace holo
{
namespace network
{
// TODO There are some problems.  i will Fix it in the future.

class Selector
{
public:
    static constexpr holo::int32_t DEFAULT_MAX_EVENTS{1024};

    Selector() noexcept;
    explicit Selector(holo::int32_t const max_events) noexcept;
    ~Selector() noexcept;

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
    void addSelectEvent(Socket const socket, holo::int32_t const events);
    void setSelectEvent(Socket const socket, holo::int32_t const events);
    void delSelectEvent(Socket const socket, holo::int32_t const events);

    void                    addFd(holo::int32_t const fd);
    void                    delFd(holo::int32_t const fd);
    std::set<holo::int32_t> getFds();

private:
    holo::bool_t                      is_init_;
    holo::int32_t                     max_fd_;
    holo::int32_t                     max_events_;
    fd_set                            read_events_set_;
    fd_set                            write_events_set_;
    fd_set                            error_events_set_;
    std::set<holo::int32_t>           fds_;
    mutable std::mutex                fds_mutex_;
    std::function<void(Socket const)> read_event_callback_;
    std::function<void(Socket const)> write_event_callback_;
    std::function<void(Socket const)> error_event_callback_;
    std::function<void(Socket const)> hangup_event_callback_;
};

}  // namespace network
}  // namespace holo
#endif
