#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>

#include <holo/network/connection_monitor.h>
#include <holo/network/exception.h>

namespace holo
{
namespace network
{
ConnectionMonitor::ConnectionMonitor() noexcept
  : io_multiplexer_{MultiplexerType::DEFAULT_MAX_EVENTS}
  , uninitialized_callback_{nullptr}
  , connected_callback_{nullptr}
  , read_callback_{nullptr}
  , closed_callback_{nullptr}
  , write_callback_{nullptr}
{
}

ConnectionMonitor::~ConnectionMonitor() noexcept
{
    Destroy();
}

void ConnectionMonitor::Init()
{
    io_multiplexer_.SetReadEventCallback(std::bind(&ConnectionMonitor::readEventCallback, this, std::placeholders::_1));
    io_multiplexer_.SetWriteEventCallback(
        std::bind(&ConnectionMonitor::writeEventCallback, this, std::placeholders::_1));
    io_multiplexer_.SetErrorEventCallback(
        std::bind(&ConnectionMonitor::errorEventCallback, this, std::placeholders::_1));
    io_multiplexer_.SetHangupEventCallback(
        std::bind(&ConnectionMonitor::hangupEventCallback, this, std::placeholders::_1));
    io_multiplexer_.Open();
}

void ConnectionMonitor::Destroy()
{
    io_multiplexer_.Close();
}

void ConnectionMonitor::SetUninitializedCallback(std::function<void(Socket const)> const& callback)
{
    uninitialized_callback_ = callback;
}

void ConnectionMonitor::SetConnectedCallback(std::function<void(Socket const)> const& callback)
{
    connected_callback_ = callback;
}

void ConnectionMonitor::SetReadCallback(std::function<void(Socket const)> const& callback)
{
    read_callback_ = callback;
}

void ConnectionMonitor::SetClosedCallback(std::function<void(Socket const)> const& callback)
{
    closed_callback_ = callback;
}

void ConnectionMonitor::SetWriteCallback(std::function<void(Socket const)> const& callback)
{
    write_callback_ = callback;
}

void ConnectionMonitor::AddConnection(Socket const socket)
{
    socket.SetNonBlock(true);
    socket.SetReuseAddr();
    socket.SetKeepAlive();
    socket.SetCloseWait(Socket::CloseWaitState::NO_WAIT);

    io_multiplexer_.AddEvent(socket, NetEvent::READ | NetEvent::WRITE | NetEvent::ERROR);
}

void ConnectionMonitor::DelConnection(Socket const socket)
{
    io_multiplexer_.DelEvent(socket, NetEvent::READ | NetEvent::WRITE | NetEvent::ERROR);
}

void ConnectionMonitor::ProcessEventOnce()
{
    holo::int32_t milliseconds{1000};
    io_multiplexer_.ProcessEventOnce(milliseconds);
}

void ConnectionMonitor::readEventCallback(Socket const socket)
{
    if (socket.IsReadable())
    {
        assert(nullptr != read_callback_);
        read_callback_(socket);
    }
    else
    {
        DelConnection(socket);
        assert(nullptr != closed_callback_);
        closed_callback_(socket);
    }
}

void ConnectionMonitor::writeEventCallback(Socket const socket)
{
    io_multiplexer_.ModEvent(socket, NetEvent::READ | NetEvent::ERROR);
    assert(nullptr != connected_callback_);
    connected_callback_(socket);
}

void ConnectionMonitor::errorEventCallback(Socket const socket)
{
    DelConnection(socket);
    assert(nullptr != closed_callback_);
    closed_callback_(socket);
}

void ConnectionMonitor::hangupEventCallback(Socket const socket)
{
    assert(nullptr != uninitialized_callback_);
    uninitialized_callback_(socket);
}

}  // namespace network
}  // namespace holo
