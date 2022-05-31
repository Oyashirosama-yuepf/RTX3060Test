#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>

#include <holo/network/exception.h>
#include <holo/network/poller.h>

namespace holo
{
namespace network
{
Poller::Poller() noexcept
  : is_init_{false}
  , max_events_{DEFAULT_MAX_EVENTS}
  , current_event_size_{0}
  , events_{}
  , read_event_callback_{nullptr}
  , write_event_callback_{nullptr}
  , error_event_callback_{nullptr}
  , hangup_event_callback_{nullptr}
{
}

Poller::Poller(holo::int32_t const max_events) noexcept
  : is_init_{false}
  , max_events_{max_events}
  , current_event_size_{0}
  , events_{}
  , read_event_callback_{nullptr}
  , write_event_callback_{nullptr}
  , error_event_callback_{nullptr}
  , hangup_event_callback_{nullptr}
{
    assert(max_events > 0);
}

Poller::~Poller() noexcept
{
    Close();
}

void Poller::Open()
{
    if (is_init_)
    {
        return;
    }

    is_init_ = true;

    current_event_size_ = 0;

    events_.resize(max_events_);
    for (auto& event : events_)
    {
        event.fd      = -1;
        event.events  = 0;
        event.revents = 0;
    }
}

void Poller::Close()
{
    if (!is_init_)
    {
        return;
    }

    is_init_ = false;
}

holo::int32_t Poller::getPollEvent(holo::int32_t const events)
{
    holo::int32_t ev{0U};

    if (events & NetEvent::READ)
    {
        ev |= POLLIN;
    }

    if (events & NetEvent::WRITE)
    {
        ev |= POLLOUT;
    }

    if (events & NetEvent::ERROR)
    {
        ev |= POLLERR;
    }

    if (0U == ev)
    {
        throw std::runtime_error{"event not set!"};
    }

    return ev;
}

void Poller::AddEvent(Socket const socket, holo::int32_t const events)
{
    holo::int32_t index           = 0;
    holo::int32_t find_idle_index = -1;
    holo::int32_t poll_ev         = getPollEvent(events);
    holo::int32_t fd              = socket.GetFd();

    assert(current_event_size_ < max_events_);

    std::lock_guard<std::mutex> locker{events_mutex_};
    for (; index < current_event_size_; ++index)
    {
        if (events_[index].fd == fd)
        {
            events_[index].events |= poll_ev;
            return;
        }
        else if (-1 == find_idle_index)
        {
            if (0 > events_[index].fd)
            {
                find_idle_index = index;
            }
        }
    }

    struct pollfd event;
    event.fd      = fd;
    event.events  = poll_ev;
    event.revents = 0;

    if (0 <= find_idle_index)
    {
        events_[find_idle_index] = event;
    }
    else
    {
        events_[index] = event;
    }

    current_event_size_++;
}

void Poller::ModEvent(Socket const socket, holo::int32_t const events)
{
    holo::int32_t index   = 0;
    holo::int32_t poll_ev = getPollEvent(events);
    holo::int32_t fd      = socket.GetFd();

    assert(current_event_size_ < max_events_);

    std::lock_guard<std::mutex> locker{events_mutex_};
    for (; index < current_event_size_; ++index)
    {
        if (events_[index].fd == fd)
        {
            events_[index].events = poll_ev;
            return;
        }
    }
}

void Poller::DelEvent(Socket const socket, holo::int32_t const events)
{
    holo::int32_t index   = 0;
    holo::int32_t poll_ev = getPollEvent(events);
    holo::int32_t fd      = socket.GetFd();

    assert(current_event_size_ < max_events_);

    std::lock_guard<std::mutex> locker{events_mutex_};
    for (; index < current_event_size_; ++index)
    {
        if (events_[index].fd == fd)
        {
            events_[index].events &= ~poll_ev;
            if (0 == events_[index].events)
            {
                events_[index].fd = -1;
            }
            return;
        }
    }
}

std::vector<struct pollfd> Poller::getEvents()
{
    holo::int32_t              index = 0;
    std::vector<struct pollfd> valid_events{};

    std::lock_guard<std::mutex> locker{events_mutex_};
    for (; index < current_event_size_; ++index)
    {
        if (0 <= events_[index].fd)
        {
            valid_events.emplace_back(events_[index]);
        }
    }

    return valid_events;
}

void Poller::ProcessEventOnce(holo::int32_t const milliseconds)
{
    int                        ret         = -1;
    std::vector<struct pollfd> events_set  = getEvents();
    int                        event_count = events_set.size();

    do
    {
        ret = ::poll(&(events_set[0]), event_count, milliseconds);
    } while (ret < 0 && errno == EINTR);

    if (0 < ret)
    {
        for (holo::int32_t i = 0; i < event_count; ++i)
        {
            if (0 == events_set[i].revents)
            {
                continue;
            }

            Socket        socket = Socket(events_set[i].fd);
            holo::int32_t events = events_set[i].revents;

            if (events & POLLIN)
            {
                read_event_callback_(socket);
            }
            else if (events == POLLOUT)
            {
                write_event_callback_(socket);
            }
            else if (events & POLLERR)
            {
                error_event_callback_(socket);
            }
            else if ((events == POLLHUP) || (events == (POLLHUP | POLLOUT)))
            {
                hangup_event_callback_(socket);
            }
            else if (events & POLLOUT)
            {
                write_event_callback_(socket);
            }
            else
            {
            }
        }
    }
    else if (0 == ret)
    {
        return;
    }
    else
    {
        std::string error_info = "poller: poll event error!";
        error_info += strerror(errno);
        throw SocketIOException{error_info};
    }
}

void Poller::SetReadEventCallback(std::function<void(Socket const)> const& callback)
{
    read_event_callback_ = callback;
}

void Poller::SetWriteEventCallback(std::function<void(Socket const)> const& callback)
{
    write_event_callback_ = callback;
}

void Poller::SetErrorEventCallback(std::function<void(Socket const)> const& callback)
{
    error_event_callback_ = callback;
}

void Poller::SetHangupEventCallback(std::function<void(Socket const)> const& callback)
{
    hangup_event_callback_ = callback;
}

}  // namespace network
}  // namespace holo
