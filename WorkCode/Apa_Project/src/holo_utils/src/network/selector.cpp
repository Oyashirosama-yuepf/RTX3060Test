#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <stdexcept>

#include <holo/network/exception.h>
#include <holo/network/selector.h>

namespace holo
{
namespace network
{
Selector::Selector() noexcept
  : is_init_{false}
  , max_fd_{Socket::INVALID_FD}
  , max_events_{DEFAULT_MAX_EVENTS}
  , read_events_set_{}
  , write_events_set_{}
  , error_events_set_{}
  , fds_{}
  , read_event_callback_{nullptr}
  , write_event_callback_{nullptr}
  , error_event_callback_{nullptr}
  , hangup_event_callback_{nullptr}
{
}

Selector::Selector(holo::int32_t const max_events) noexcept
  : is_init_{false}
  , max_fd_{Socket::INVALID_FD}
  , max_events_{max_events}
  , read_events_set_{}
  , write_events_set_{}
  , error_events_set_{}
  , fds_{}
  , read_event_callback_{nullptr}
  , write_event_callback_{nullptr}
  , error_event_callback_{nullptr}
  , hangup_event_callback_{nullptr}
{
    assert(max_events > 0);
}

Selector::~Selector() noexcept
{
    Close();
}

void Selector::Open()
{
    if (is_init_)
    {
        return;
    }

    is_init_ = true;

    FD_ZERO(&read_events_set_);
    FD_ZERO(&write_events_set_);
    FD_ZERO(&error_events_set_);
}

void Selector::Close()
{
    if (!is_init_)
    {
        return;
    }

    is_init_ = false;
}

void Selector::addSelectEvent(Socket const socket, holo::int32_t const events)
{
    holo::int32_t fd = socket.GetFd();
    if (events & NetEvent::READ)
    {
        FD_SET(fd, &read_events_set_);
    }

    if (events & NetEvent::WRITE)
    {
        FD_SET(fd, &write_events_set_);
    }

    if (events & NetEvent::ERROR)
    {
        FD_SET(fd, &error_events_set_);
    }
}

void Selector::setSelectEvent(Socket const socket, holo::int32_t const events)
{
    holo::int32_t fd = socket.GetFd();
    if (events & NetEvent::READ)
    {
        FD_SET(fd, &read_events_set_);
    }
    else if (FD_ISSET(fd, &read_events_set_))
    {
        FD_CLR(fd, &read_events_set_);
    }

    if (events & NetEvent::WRITE)
    {
        FD_SET(fd, &write_events_set_);
    }
    else if (FD_ISSET(fd, &write_events_set_))
    {
        FD_CLR(fd, &write_events_set_);
    }

    if (events & NetEvent::ERROR)
    {
        FD_SET(fd, &error_events_set_);
    }
    else if (FD_ISSET(fd, &error_events_set_))
    {
        FD_CLR(fd, &error_events_set_);
    }
}

void Selector::delSelectEvent(Socket const socket, holo::int32_t const events)
{
    holo::int32_t fd = socket.GetFd();
    if ((events & NetEvent::READ) && FD_ISSET(fd, &read_events_set_))
    {
        FD_CLR(fd, &read_events_set_);
    }

    if ((events & NetEvent::WRITE) && FD_ISSET(fd, &write_events_set_))
    {
        FD_CLR(fd, &write_events_set_);
    }

    if ((events & NetEvent::ERROR) && FD_ISSET(fd, &error_events_set_))
    {
        FD_CLR(fd, &error_events_set_);
    }
}

void Selector::AddEvent(Socket const socket, holo::int32_t const events)
{
    addSelectEvent(socket, events);
    addFd(socket.GetFd());
}

void Selector::ModEvent(Socket const socket, holo::int32_t const events)
{
    setSelectEvent(socket, events);
}

void Selector::DelEvent(Socket const socket, holo::int32_t const events)
{
    delSelectEvent(socket, events);
    delFd(socket.GetFd());
}

void Selector::addFd(holo::int32_t const fd)
{
    std::lock_guard<std::mutex> locker{fds_mutex_};
    fds_.emplace(fd);
    max_fd_ = std::max(max_fd_, fd);
}

void Selector::delFd(holo::int32_t const fd)
{
    std::lock_guard<std::mutex> locker{fds_mutex_};
    auto                        it = fds_.find(fd);
    if (it != fds_.end())
    {
        it = fds_.erase(it);
    }
}

std::set<holo::int32_t> Selector::getFds()
{
    std::lock_guard<std::mutex> locker{fds_mutex_};
    return fds_;
}

void Selector::ProcessEventOnce(holo::int32_t const milliseconds)
{
    int            count{-1};
    struct timeval time_out;
    time_out.tv_sec  = milliseconds / 1'000;
    time_out.tv_usec = (milliseconds % 1'000) * 1'000;

    fd_set tmp_read_events_set;
    fd_set tmp_write_events_set;
    fd_set tmp_error_events_set;

    do
    {
        tmp_read_events_set  = read_events_set_;
        tmp_write_events_set = write_events_set_;
        tmp_error_events_set = error_events_set_;

        count = ::select(1 + max_fd_, &tmp_read_events_set, nullptr, &tmp_error_events_set, &time_out);

    } while (count < 0 && errno == EINTR);

    std::cout << "select count=" << count << std::endl;

    if (0 < count)
    {
        std::set<holo::int32_t>           fds = getFds();
        std::set<holo::int32_t>::iterator it  = fds.begin();
        std::cout << "select fd=" << *it << std::endl;
        for (; it != fds.end(); it++)
        {
            holo::int32_t fd     = *it;
            holo::int32_t events = 0;

            if (FD_ISSET(fd, &tmp_read_events_set))
            {
                events |= NetEvent::READ;
                std::cout << "read event; select fd=" << fd << std::endl;
                // read_event_callback_(Socket(fd));
            }

#if 0
            if (FD_ISSET(fd, &tmp_write_events_set))
            {
                events |= NetEvent::WRITE;
                std::cout << "write event; select fd=" << fd << std::endl;
                // write_event_callback_(Socket(fd));
            }
#endif

            if (FD_ISSET(fd, &tmp_error_events_set))
            {
                events |= NetEvent::ERROR;
                std::cout << "error event; select fd=" << fd << std::endl;
                // error_event_callback_(Socket(fd));
            }

            std::cout << "events=" << events << "; select fd=" << fd << std::endl;
            if (NetEvent::READ == events)
            {
                Socket socket{fd};
                if (socket.IsReadable())
                {
                    std::cout << "can read data; select fd = " << fd << std::endl;
                    read_event_callback_(Socket(fd));
                }
                else
                {
                    std::cout << "hangup event; select fd=" << fd << std::endl;
                    hangup_event_callback_(Socket(fd));
                }
            }
            else
            {
                error_event_callback_(Socket(fd));
            }
            // std::cout << "hangup event; select fd=" << fd << std::endl;
            // hangup_event_callback_(Socket(fd));
        }
    }
    else if (0 == count)
    {
        std::cout << "select timeout" << std::endl;
        return;
    }
    else
    {
        std::string error_info = "selector: select event error!";
        error_info += strerror(errno);
        throw SocketIOException{error_info};
    }
}

void Selector::SetReadEventCallback(std::function<void(Socket const)> const& callback)
{
    read_event_callback_ = callback;
}

void Selector::SetWriteEventCallback(std::function<void(Socket const)> const& callback)
{
    write_event_callback_ = callback;
}

void Selector::SetErrorEventCallback(std::function<void(Socket const)> const& callback)
{
    error_event_callback_ = callback;
}

void Selector::SetHangupEventCallback(std::function<void(Socket const)> const& callback)
{
    hangup_event_callback_ = callback;
}

}  // namespace network
}  // namespace holo
