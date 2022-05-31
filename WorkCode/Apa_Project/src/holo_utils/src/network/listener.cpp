#include <arpa/inet.h> /* for inet_addr*/
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>

#include <holo/network/exception.h>
#include <holo/network/listener.h>

namespace holo
{
namespace network
{
Listener::Listener(holo::int32_t const domain, holo::int32_t const type) noexcept
  : domain_{domain}
  , type_{type}
  , io_multiplexer_{MultiplexerType::DEFAULT_MAX_EVENTS}
  , listen_info_{}
  , new_connection_callback_{nullptr}
{
}

Listener::~Listener() noexcept
{
    Destroy();
}

void Listener::Init()
{
    io_multiplexer_.SetReadEventCallback(std::bind(&Listener::readEventCallback, this, std::placeholders::_1));
    io_multiplexer_.SetWriteEventCallback(std::bind(&Listener::writeEventCallback, this, std::placeholders::_1));
    io_multiplexer_.SetErrorEventCallback(std::bind(&Listener::errorEventCallback, this, std::placeholders::_1));
    io_multiplexer_.SetHangupEventCallback(std::bind(&Listener::hangupEventCallback, this, std::placeholders::_1));
    io_multiplexer_.Open();
}

void Listener::Destroy()
{
    delAll();

    io_multiplexer_.Close();
}

void Listener::SetNewConnectionCallback(
    std::function<void(Socket const, std::string const&, holo::int32_t const)> const& callback)
{
    new_connection_callback_ = callback;
}

void Listener::Add(std::string const& ip, holo::int32_t const port)
{
    std::pair<std::string, holo::int32_t> addr{ip, port};

    std::lock_guard<std::mutex> locker{listen_info_mutex_};

    auto it = listen_info_.find(addr);
    if (it != listen_info_.end())
    {
        return;
    }

    Socket listen_socket;
    listen_socket.Open(domain_, type_);
    listen_socket.SetNonBlock(true);
    listen_socket.SetReuseAddr();

    if (ip.empty())
    {
        listen_socket.Bind(port);
    }
    else
    {
        listen_socket.Bind(ip, port);
    }

    listen_socket.Listen();

    listen_info_.emplace(addr, listen_socket);
    io_multiplexer_.AddEvent(listen_socket, NetEvent::READ | NetEvent::ERROR);
}

void Listener::Add(holo::int32_t const port)
{
    Add("", port);
}

void Listener::Del(std::string const& ip, holo::int32_t const port)
{
    std::pair<std::string, holo::int32_t> addr{ip, port};

    std::lock_guard<std::mutex> locker{listen_info_mutex_};

    auto it = listen_info_.find(addr);
    if (it != listen_info_.end())
    {
        io_multiplexer_.DelEvent(it->second, NetEvent::READ | NetEvent::ERROR);
        it->second.Close();
        (void)listen_info_.erase(it);
    }
}

void Listener::Del(holo::int32_t const port)
{
    Del("", port);
}

void Listener::addSocket(Socket const listen_socket)
{
    std::string   ip;
    holo::int32_t port;

    holo::bool_t ret = listen_socket.GetSockName(ip, port);
    if (false == ret)
    {
        std::string error_info = "Listener addSocket, GetSockName error!";
        error_info += strerror(errno);
        throw std::runtime_error{error_info};
    }

    std::pair<std::string, holo::int32_t> addr{ip, port};

    std::lock_guard<std::mutex> locker{listen_info_mutex_};

    auto it = listen_info_.find(addr);
    if (it != listen_info_.end())
    {
        return;
    }

    listen_info_.emplace(addr, listen_socket);
    io_multiplexer_.AddEvent(listen_socket, NetEvent::READ | NetEvent::ERROR);
}

void Listener::delSocket(Socket const listen_socket)
{
    std::string   ip;
    holo::int32_t port;

    holo::bool_t ret = listen_socket.GetSockName(ip, port);
    if (false == ret)
    {
        std::string error_info = "Listener delSocket, GetSockName error!";
        error_info += strerror(errno);
        throw std::runtime_error{error_info};
    }

    std::pair<std::string, holo::int32_t> addr{ip, port};

    std::lock_guard<std::mutex> locker{listen_info_mutex_};

    auto it = listen_info_.find(addr);
    if (it != listen_info_.end())
    {
        io_multiplexer_.DelEvent(it->second, NetEvent::READ | NetEvent::ERROR);
        (void)listen_info_.erase(it);
    }
}

void Listener::delAll()
{
    std::lock_guard<std::mutex> locker{listen_info_mutex_};

    for (auto it = listen_info_.begin(); it != listen_info_.end(); ++it)
    {
        io_multiplexer_.DelEvent(it->second, NetEvent::READ | NetEvent::ERROR);
        it->second.Close();
    }
    listen_info_.clear();
}

void Listener::ProcessEventOnce()
{
    holo::int32_t milliseconds{1000};
    io_multiplexer_.ProcessEventOnce(milliseconds);
}

void Listener::readEventCallback(Socket const socket)
{
    std::string   ip{};
    holo::int32_t port{0};

    Socket client_socket = socket.Accept(ip, port);

    assert(nullptr != new_connection_callback_);
    new_connection_callback_(client_socket, ip, port);
}

void Listener::writeEventCallback(Socket const socket)
{
    delSocket(socket);
    socket.Close();
}

void Listener::errorEventCallback(Socket const socket)
{
    delSocket(socket);
    socket.Close();
}

void Listener::hangupEventCallback(Socket const socket)
{
    delSocket(socket);
    socket.Close();
}

size_t Listener::initPairHash::operator()(std::pair<std::string, holo::int32_t> const& key) const noexcept
{
    holo::int32_t ip = ::inet_addr(key.first.c_str());
    return ip * 13 + key.second;
}

}  // namespace network
}  // namespace holo
