#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>

#include <holo/network/epoller.h>
#include <holo/network/exception.h>

namespace holo
{
namespace network
{
Epoller::Epoller(holo::int32_t const max_events) noexcept
  : epoll_fd_{Socket::INVALID_FD}
  , max_events_{max_events}
  , events_{}
  , read_event_callback_{nullptr}
  , write_event_callback_{nullptr}
  , error_event_callback_{nullptr}
  , hangup_event_callback_{nullptr}
{
    assert(max_events > 0);
}

Epoller::~Epoller() noexcept
{
    Close();
}

void Epoller::Open()
{
    if (Socket::INVALID_FD != epoll_fd_)
    {
        return;
    }

    events_.resize(max_events_);

    epoll_fd_ = ::epoll_create(max_events_);

    if (Socket::INVALID_FD == epoll_fd_)
    {
        std::string error_info = "epoll_create error!";
        error_info += strerror(errno);
        throw std::runtime_error{error_info};
    }
}

void Epoller::Close()
{
    if (Socket::INVALID_FD == epoll_fd_)
    {
        return;
    }

    ::close(epoll_fd_);
    epoll_fd_ = Socket::INVALID_FD;
}

holo::int32_t Epoller::getEpollEvent(holo::int32_t const events)
{
    holo::int32_t ev{0U};

    if (events & NetEvent::READ)
    {
        ev |= EPOLLIN;
    }

    if (events & NetEvent::WRITE)
    {
        ev |= EPOLLOUT;
    }

    if (events & NetEvent::ERROR)
    {
        ev |= EPOLLERR;
    }

    if (0U == ev)
    {
        throw std::runtime_error{"event not set!"};
    }

    return ev;
}

holo::int32_t Epoller::control(Socket const socket, holo::int32_t const events, holo::int32_t const operation)
{
    holo::int32_t ep_events = events | EPOLLET;

    struct epoll_event ev;
    ev.data.fd = socket.GetFd();
    ev.events  = ep_events;

    return ::epoll_ctl(epoll_fd_, operation, socket.GetFd(), &ev);
}

void Epoller::AddEvent(Socket const socket, holo::int32_t const events)
{
    if (-1 == control(socket, getEpollEvent(events), EPOLL_CTL_ADD))
    {
        if (EEXIST != errno)
        {
            std::string error_info = "Epoller AddEvent error!";
            error_info += strerror(errno);
            throw std::runtime_error{error_info};
        }
    }
}

void Epoller::ModEvent(Socket const socket, holo::int32_t const events)
{
    if (-1 == control(socket, getEpollEvent(events), EPOLL_CTL_MOD))
    {
        if (ENOENT != errno)
        {
            std::string error_info = "Epoller ModEvent error!";
            error_info += strerror(errno);
            throw std::runtime_error{error_info};
        }
    }
}

void Epoller::DelEvent(Socket const socket, holo::int32_t const events)
{
    (void)control(socket, getEpollEvent(events), EPOLL_CTL_DEL);
}

void Epoller::ProcessEventOnce(holo::int32_t const milliseconds)
{
    int count{-1};
    do
    {
        count = ::epoll_wait(epoll_fd_, &(events_[0]), max_events_, milliseconds);

    } while (count < 0 && errno == EINTR);

    if (0 < count)
    {
        for (holo::int32_t i = 0; i < count; ++i)
        {
            Socket        socket = Socket(events_[i].data.fd);
            holo::int32_t events = events_[i].events;

            if (events & EPOLLIN)
            {
                read_event_callback_(socket);
            }
            else if (events == EPOLLOUT)
            {
                write_event_callback_(socket);
            }
            else if (events & EPOLLERR)
            {
                error_event_callback_(socket);
            }
            else if ((events == EPOLLHUP) || (events == (EPOLLHUP | EPOLLOUT)))
            {
                hangup_event_callback_(socket);
            }
            else if (events & EPOLLOUT)
            {
                write_event_callback_(socket);
            }
            else
            {
            }
        }
    }
    else if (0 == count)
    {
        return;
    }
    else
    {
        std::string error_info = "epoller: epoll_wait event error!";
        error_info += strerror(errno);
        throw SocketIOException{error_info};
    }
}

void Epoller::SetReadEventCallback(std::function<void(Socket const)> const& callback)
{
    read_event_callback_ = callback;
}

void Epoller::SetWriteEventCallback(std::function<void(Socket const)> const& callback)
{
    write_event_callback_ = callback;
}

void Epoller::SetErrorEventCallback(std::function<void(Socket const)> const& callback)
{
    error_event_callback_ = callback;
}

void Epoller::SetHangupEventCallback(std::function<void(Socket const)> const& callback)
{
    hangup_event_callback_ = callback;
}

}  // namespace network
}  // namespace holo
